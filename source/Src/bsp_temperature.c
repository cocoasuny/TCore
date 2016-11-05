/**
 ******************************************************************************
 * @file    bsp_temperature.c
 * @author  Jason
 * @version V1.0.0
 * @date    2016-11-3
 * @brief   This file provides a set of functions needed to measure core temperature.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 ******************************************************************************
 */
 
/* Includes ------------------------------------------------------------------*/
#include "bsp_temperature.h"


/* private function declare */
static void ref_temperature_channel_switch_IO_Init(void);
static void ref_temperature_channel_switch(SWITCH_CHANNEL_DEF channel);
static void core_temperature_channel_switch_IO_Init(void);
static void core_temperature_channel_switch(SWITCH_CHANNEL_DEF channel);

/**
  * @brief  ref_temperature_init
  * @brief  参考温度测量初始化
  * @param  None 
  * @retval None    
  */
void ref_temperature_init(void)
{
	/* channel switch IO Init */
	ref_temperature_channel_switch_IO_Init();
	
	/* ADS1118 Init */
	ads1118_init();
}
/**
  * @brief  ref_temperature_sample
  * @brief  获取参考温度AD电压采样值
  * @param  VSens12, VSens23
  * @retval None    
  */
void ref_temperature_sample(float *VSens12,float *VSens23)
{
	float V_sens = 0;
	
	/* switch the ref temperature chanel */
	ref_temperature_channel_switch(ChannelA0B0);
	ads1118_getVal(ADS1118Start | DifferentialCH2_3, &V_sens);
	*VSens12 = V_sens;
	
	/* switch the ref temperature chanel */
	ref_temperature_channel_switch(ChannelA1B1);
	ads1118_getVal(ADS1118Start | DifferentialCH2_3, &V_sens);
	*VSens23 = V_sens;	
}
/**
  * @brief  ref_temperature_deinit
  * @brief  参考温度测量
  * @param  None 
  * @retval None    
  */
void ref_temperature_deinit(void)
{
	
}

/**
  * @brief  ref_temperature_channel_switch_IO_Init
  * @brief  参考温度测量模拟开关控制IO口初始化
  * @param  None 
  * @retval None    
  */
static void ref_temperature_channel_switch_IO_Init(void)
{
	GPIO_InitTypeDef  		GPIO_InitStruct;
	
	/* Enable the Pin Port Clock */
	GPIO_PORT_REF_TEM_CTL0_CLK_ENABLE();
	GPIO_PORT_REF_TEM_CTL1_CLK_ENABLE();

	/* Configure CTL0 pins */
	GPIO_InitStruct.Pin = GPIO_PIN_REF_TEM_CTL0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;

	HAL_GPIO_Init(GPIO_PORT_REF_TEM_CTL0, &GPIO_InitStruct);
	
	/* Configure CTL1 pins */
	GPIO_InitStruct.Pin = GPIO_PIN_REF_TEM_CTL1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;

	HAL_GPIO_Init(GPIO_PORT_REF_TEM_CTL1, &GPIO_InitStruct);	
}


/**
  * @brief  ref_temperature_channel_switch
  * @brief  控制参考温度测量模拟开关通道
  * @param  channel
  * @retval None    
  */
static void ref_temperature_channel_switch(SWITCH_CHANNEL_DEF channel)
{
	switch(channel)
	{
		case ChannelA0B0:
		{
			HAL_GPIO_WritePin(GPIO_PORT_REF_TEM_CTL0,GPIO_PIN_REF_TEM_CTL0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_PORT_REF_TEM_CTL1,GPIO_PIN_REF_TEM_CTL1,GPIO_PIN_RESET);
		}
		break;
		case ChannelA1B1:
		{
			HAL_GPIO_WritePin(GPIO_PORT_REF_TEM_CTL0,GPIO_PIN_REF_TEM_CTL0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_PORT_REF_TEM_CTL1,GPIO_PIN_REF_TEM_CTL1,GPIO_PIN_RESET);		
		}
		break;
		case ChannelA2B2:
		{
			HAL_GPIO_WritePin(GPIO_PORT_REF_TEM_CTL0,GPIO_PIN_REF_TEM_CTL0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_PORT_REF_TEM_CTL1,GPIO_PIN_REF_TEM_CTL1,GPIO_PIN_SET);		
		}
		break;
		case ChannelA3B3:
		{
			HAL_GPIO_WritePin(GPIO_PORT_REF_TEM_CTL0,GPIO_PIN_REF_TEM_CTL0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_PORT_REF_TEM_CTL1,GPIO_PIN_REF_TEM_CTL1,GPIO_PIN_SET);		
		}
		break;
		default:break;		
	}
}
/**
  * @brief  ref_temperature_deinit
  * @brief  参考温度测量
  * @param  None 
  * @retval None    
  */
void core_temperature_hw_init(void)
{
	/* channel switch IO Init */
	core_temperature_channel_switch_IO_Init();
	
	/* ADS1118 Init */
	ads1118_init();	
}
/**
  * @brief  core_ambient_temperature_sample
  * @brief  获取核心环境温度AD采样电压值
  * @param[out]  VSens12, VSens23
  * @retval None    
  */
void core_ambient_temperature_sample(float *VSens12,float *VSens23)
{
	float V_sens = 0;
	
	/* switch the core temperature chanel */
	core_temperature_channel_switch(ChannelA0B0);
	ads1118_getVal(ADS1118Start | DifferentialCH2_3, &V_sens);
	*VSens12 = V_sens;
	
	/* switch the core temperature chanel */
	core_temperature_channel_switch(ChannelA1B1);
	ads1118_getVal(ADS1118Start | DifferentialCH2_3, &V_sens);
	*VSens23 = V_sens;	
}
/**
  * @brief  core_forehead_temperature_sample
  * @brief  获取核心额头温度AD采样电压值
  * @param  VSens12, VSens23
  * @retval None    
  */
void core_forehead_temperature_sample(float *VSens12,float *VSens23)
{
	float V_sens = 0;
	
	/* switch the core temperature chanel */
	core_temperature_channel_switch(ChannelA0B0);
	ads1118_getVal(ADS1118Start | DifferentialCH2_3, &V_sens);
	*VSens12 = V_sens;
	
	/* switch the core temperature chanel */
	core_temperature_channel_switch(ChannelA1B1);
	ads1118_getVal(ADS1118Start | DifferentialCH2_3, &V_sens);
	*VSens23 = V_sens;	
}
/**
  * @brief  core_temperature_deinit
  * @brief  核心温度测量
  * @param  None 
  * @retval None    
  */
void core_temperature_hw_deinit(void)
{
	
}
/**
  * @brief  core_temperature_channel_switch_IO_Init
  * @brief  核心温度测量模拟开关控制IO口初始化
  * @param  None 
  * @retval None    
  */
static void core_temperature_channel_switch_IO_Init(void)
{
	GPIO_InitTypeDef  		GPIO_InitStruct;
	
	/* Enable the Pin Port Clock */
	GPIO_PORT_CORE_TEM_CTL0_CLK_ENABLE();
	GPIO_PORT_CORE_TEM_CTL1_CLK_ENABLE();

	/* Configure CTL0 pins */
	GPIO_InitStruct.Pin = GPIO_PIN_CORE_TEM_CTL0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;

	HAL_GPIO_Init(GPIO_PORT_CORE_TEM_CTL0, &GPIO_InitStruct);
	
	/* Configure CTL1 pins */
	GPIO_InitStruct.Pin = GPIO_PIN_CORE_TEM_CTL1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_MEDIUM;

	HAL_GPIO_Init(GPIO_PORT_CORE_TEM_CTL1, &GPIO_InitStruct);	
}
/**
  * @brief  core_temperature_channel_switch
  * @brief  控制核心温度测量模拟开关通道
  * @param  channel
  * @retval None    
  */
static void core_temperature_channel_switch(SWITCH_CHANNEL_DEF channel)
{
	switch(channel)
	{
		case ChannelA0B0:
		{
			HAL_GPIO_WritePin(GPIO_PORT_CORE_TEM_CTL0,GPIO_PIN_CORE_TEM_CTL0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_PORT_CORE_TEM_CTL1,GPIO_PIN_CORE_TEM_CTL1,GPIO_PIN_RESET);
		}
		break;
		case ChannelA1B1:
		{
			HAL_GPIO_WritePin(GPIO_PORT_CORE_TEM_CTL0,GPIO_PIN_CORE_TEM_CTL0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_PORT_CORE_TEM_CTL1,GPIO_PIN_CORE_TEM_CTL1,GPIO_PIN_RESET);		
		}
		break;
		case ChannelA2B2:
		{
			HAL_GPIO_WritePin(GPIO_PORT_CORE_TEM_CTL0,GPIO_PIN_CORE_TEM_CTL0,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIO_PORT_CORE_TEM_CTL1,GPIO_PIN_CORE_TEM_CTL1,GPIO_PIN_SET);		
		}
		break;
		case ChannelA3B3:
		{
			HAL_GPIO_WritePin(GPIO_PORT_CORE_TEM_CTL0,GPIO_PIN_CORE_TEM_CTL0,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIO_PORT_CORE_TEM_CTL1,GPIO_PIN_CORE_TEM_CTL1,GPIO_PIN_SET);		
		}
		break;
		default:break;		
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

