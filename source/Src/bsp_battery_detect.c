/**
  ****************************************************************************************
  * @file    bsp_battery_detect.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-10
  * @brief   detect the voltage of the battery
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bsp_battery_detect.h"


/* ADC handler declaration */
static ADC_HandleTypeDef    AdcHandle;


/* private function declare */
static void battery_detect_adc_init(void);
static void battery_detect_adc_deinit(void);
static HAL_StatusTypeDef sample_battery_voltage_once(uint16_t *voltage);


/**
  * @brief  battery_detect_adc_init
  * @note   电池电量检测ADC初始化
  * @param  pvParameters
  * @retval None    
  */
static void battery_detect_adc_init(void)
{
    ADC_ChannelConfTypeDef sConfig;
    
    /*##-1- Configure the ADC peripheral #######################################*/
    AdcHandle.Instance          = ADC_BAT_DETECT;
    if (HAL_ADC_DeInit(&AdcHandle) != HAL_OK)
    {
        /* ADC de-initialization Error */
        App_Error_Check(HAL_ERROR);
    }

    AdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV4;  /* Asynchronous clock mode, input ADC clock not divided */
    AdcHandle.Init.Resolution            = ADC_RESOLUTION_12B;            /* 12-bit resolution for converted data */
    AdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;           /* Right-alignment for converted data */
    AdcHandle.Init.ScanConvMode          = DISABLE;                       /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
    AdcHandle.Init.EOCSelection          = DISABLE;                       /* EOC flag picked-up to indicate conversion end */
    AdcHandle.Init.ContinuousConvMode    = DISABLE;                       /* Continuous mode disabled to have only 1 conversion at each conversion trig */
    AdcHandle.Init.NbrOfConversion       = 1;                             /* Parameter discarded because sequencer is disabled */
    AdcHandle.Init.DiscontinuousConvMode = DISABLE;                       /* Parameter discarded because sequencer is disabled */
    AdcHandle.Init.NbrOfDiscConversion   = 0;                             /* Parameter discarded because sequencer is disabled */
    AdcHandle.Init.ExternalTrigConv      = ADC_SOFTWARE_START;            /* Software start to trig the 1st conversion manually, without external event */
    AdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE; /* Parameter discarded because software trigger chosen */
    AdcHandle.Init.DMAContinuousRequests = DISABLE;                       /* DMA one-shot mode selected (not applied to this example) */


    if (HAL_ADC_Init(&AdcHandle) != HAL_OK)
    {
        /* ADC initialization Error */
        App_Error_Check(HAL_ERROR);
    }

    /*##-2- Configure ADC regular channel ######################################*/
    sConfig.Channel      = ADC_BAT_DETECT_CHANNEL;      /* Sampled channel number */
    sConfig.Rank         = 1;                           /* Rank of sampled channel number ADCx_CHANNEL */
    sConfig.SamplingTime = ADC_SAMPLETIME_15CYCLES;     /* Sampling time (number of clock cycles unit) */
    sConfig.Offset = 0;                                 /* Parameter discarded because offset correction is disabled */

    if (HAL_ADC_ConfigChannel(&AdcHandle, &sConfig) != HAL_OK)
    {
        /* Channel Configuration Error */
        App_Error_Check(HAL_ERROR);
    }    
}
/**
  * @brief  battery_detect_adc_deinit
  * @note   电池电量检测ADC关闭
  * @param  void
  * @retval None    
  */
static void battery_detect_adc_deinit(void)
{
    AdcHandle.Instance          = ADC_BAT_DETECT;
    HAL_ADC_DeInit(&AdcHandle);
}
/**
  * @brief       sample_battery_voltage_once
  * @note        采集一次电池电压
  * @param[out]  *voltage
  * @retval      staus    
  */
static HAL_StatusTypeDef sample_battery_voltage_once(uint16_t *voltage)
{
    HAL_StatusTypeDef       ret = HAL_ERROR;
    
    /*##-1- Start the conversion process #######################################*/
    if (HAL_ADC_Start(&AdcHandle) == HAL_OK)
    {
        /*##-2- Wait for the end of conversion #####################################*/
        if (HAL_ADC_PollForConversion(&AdcHandle, 10) == HAL_OK)
        {
            /* Check if the continuous conversion of regular channel is finished */
            if ((HAL_ADC_GetState(&AdcHandle) & HAL_ADC_STATE_EOC_REG) == HAL_ADC_STATE_EOC_REG)
            {
                /*##-5- Get the converted value of regular channel  ########################*/
                *voltage = HAL_ADC_GetValue(&AdcHandle);
                ret = HAL_OK;
            }    
        }
        else  
        {
            /* End Of Conversion flag not set on time */
            ret = HAL_ERROR;
        }         
    }
    else
    {
        /* Start Conversation Error */
        ret = HAL_ERROR;
    }


    return ret;
}
/**
  * @brief       get_battery_voltage
  * @note        获取电池电压
  * @param[out]  *voltage
  * @retval      staus    
  */
HAL_StatusTypeDef get_battery_voltage(float *voltage)
{
    uint16_t                vol[10] = {0};
    uint16_t                volt = 0;
    uint16_t                max = 0;
    uint16_t                min = 0;
    uint8_t                 i = 0;
    uint8_t                 maxLocation = 0;
    uint8_t                 minLocation = 0;
    uint8_t                 cnt = 0;
    HAL_StatusTypeDef       ret = HAL_ERROR;
    
    /* adc init */
    battery_detect_adc_init();
    
    /* 连续采集10次电池电压 */
    for(i=0;i<10;i++)
    {
        cnt++;
        if(sample_battery_voltage_once(&volt) == HAL_OK)
        {
            vol[i] = volt;
        }
        else
        {
            i--;
        }
    }

    if((cnt-i) > 5)
    {
        //采集10次过程中，至少有5次采集失败
        *voltage = 0;
        ret = HAL_ERROR;
    }
    else
    {
        max = vol[0];
        min = vol[0];
        volt = 0;
        /* 找出最大、最小值 */
        for(i = 0;i < 10;i++)
        {  
            if(max < vol[i])
            {
                max = vol[i];
                maxLocation = i;
            }
            if(min > vol[i])
            {
                min = vol[i];
                minLocation = i;
            }
            volt = volt + vol[i];
//            printf("vol[%d]:%d\r\n",i,vol[i]);
        }
        /* 减去最大、最小值 */
        volt = volt-vol[maxLocation]-vol[minLocation];
        *voltage = (float)(((float) (volt*3.3f/32768))*2) ;  //32768 = 4096*8
        ret = HAL_OK; 
    }
    
    /* adc deinit */
    battery_detect_adc_deinit();
    
    return ret;
}

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT DBGJ Co., Ltd. *****END OF FILE****/
