/**
 ******************************************************************************
 * @file    ads1118.c
 * @author  Jason
 * @version V1.0.0
 * @date    2016-10-30
 * @brief   This file provides a set of functions needed to manage the ads1118.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 ******************************************************************************
 */
 
/* Includes ------------------------------------------------------------------*/
#include "ads1118.h"


/* Private variables declare */
/* SPI handler declaration */
static SPI_HandleTypeDef ads1118SpiHandle;     //Spi2 for ads1118

/**
  * @brief  ads1118 init
  * @param  None
  * @retval None    
  */
HAL_StatusTypeDef ads1118_init(void)
{
	GPIO_InitTypeDef  		GPIO_InitStruct;
	HAL_StatusTypeDef		ret = HAL_ERROR;
	
	/**************ADS1118 CS Pin Config ***************************************/
	/* Enable the ADS1118 CS Pin Port Clock */
	GPIO_PORT_ADS1118_CS_CLK_ENABLE();

	/* Configure the ADS1118 CS pin */
	GPIO_InitStruct.Pin = GPIO_PIN_ADS1118_CS;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIO_PORT_ADS1118_CS, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIO_PORT_ADS1118_CS, GPIO_PIN_ADS1118_CS, GPIO_PIN_SET);	
	
	/**************ADS1118 SPI  config *****************************************/
	/* Set the SPI parameters */
	ads1118SpiHandle.Instance               = SPI_ADS1118;
	ads1118SpiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	ads1118SpiHandle.Init.Direction         = SPI_DIRECTION_2LINES;
	ads1118SpiHandle.Init.CLKPhase          = SPI_PHASE_2EDGE;
	ads1118SpiHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
	ads1118SpiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
	ads1118SpiHandle.Init.CRCPolynomial     = 7;
	ads1118SpiHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
	ads1118SpiHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
	ads1118SpiHandle.Init.NSS               = SPI_NSS_SOFT;
	ads1118SpiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
	ads1118SpiHandle.Init.Mode 				= SPI_MODE_MASTER;


	ret = HAL_SPI_Init(&ads1118SpiHandle);
	if(ret != HAL_OK)
	{
		/* Initialization Error */
		App_Error_Check(HAL_ERROR);
	}	
	
	return ret;
}
/**
  * @brief  ads1118_getVal
  * @param  CMD,float * pVsens(电压值) 
  * @retval Status
  */
HAL_StatusTypeDef ads1118_getVal(uint16_t CMD, float * pVsens)
{
	uint8_t   					CMD_H=0;
	uint8_t   					CMD_L=0;
	uint8_t   					SPI_Rx_Buf[2]={0};
	HAL_StatusTypeDef			ret = HAL_ERROR;
	uint8_t						aTxBuffer[2] = {0};
	uint8_t						aRxBuffer[2] = {0};

	CMD_H = (uint8_t)(0x00FF & (CMD >> 8));
	CMD_L = (uint8_t)(0x00FF & CMD);
	
	aTxBuffer[0] = CMD_H;
    aTxBuffer[1] = CMD_L;
    
	HAL_GPIO_WritePin(GPIO_PORT_ADS1118_CS, GPIO_PIN_ADS1118_CS, GPIO_PIN_RESET);
	ret = HAL_SPI_TransmitReceive(&ads1118SpiHandle, (uint8_t*)aTxBuffer, (uint8_t *)aRxBuffer, 2, 5000); 

    HAL_GPIO_WritePin(GPIO_PORT_ADS1118_CS, GPIO_PIN_ADS1118_CS, GPIO_PIN_SET);
    
    HAL_Delay(10);

	HAL_GPIO_WritePin(GPIO_PORT_ADS1118_CS, GPIO_PIN_ADS1118_CS, GPIO_PIN_RESET);
	ret = HAL_SPI_TransmitReceive(&ads1118SpiHandle, (uint8_t*)aTxBuffer, (uint8_t *)aRxBuffer, 2, 5000); 

    HAL_GPIO_WritePin(GPIO_PORT_ADS1118_CS, GPIO_PIN_ADS1118_CS, GPIO_PIN_SET);
    
	SPI_Rx_Buf[0] = aRxBuffer[0];
    SPI_Rx_Buf[1] = aRxBuffer[1];
	if(ret != HAL_OK)
	{
		App_Error_Check(HAL_ERROR);
	}
	
#if FULL_SCALE_02
	(*pVsens) = (float)(((SPI_Rx_Buf[0] << 8) | SPI_Rx_Buf[1]) * 0.0078125);//FS02= FS/32768
#elif FULL_SCALE_05
	(*pVsens) = (float)(((SPI_Rx_Buf[0] << 8) | SPI_Rx_Buf[1]) * 0.015625);//FS05 = FS/32768
#elif FULL_SCALE_1
	(*pVsens) = (float)(((SPI_Rx_Buf[0] << 8) | SPI_Rx_Buf[1]) * 0.03125);//FS1 = FS/32768
#elif FULL_SCALE_2
	(*pVsens) = (float)(((SPI_Rx_Buf[0] << 8) | SPI_Rx_Buf[1]) * 0.0625);//FS2 = FS/32768
#endif	
    	
	return(ret); 
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


