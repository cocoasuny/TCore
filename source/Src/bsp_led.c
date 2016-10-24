/**
******************************************************************************
* @file    bsp_led.c 
* @author  Jason
* @version V1.0.0
* @date    24-10-2016
* @brief   
******************************************************************************
* @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "bsp_led.h"



/**
 * @brief		LEDx_Init,config the led pin 
 * @param[in]	ledcolour:LED_RED/LED_GREEN/LED_BLUE
 * @retval		None
 */
void LEDx_Init(LED_T ledcolour)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	switch(ledcolour)
	{
		case LED_RED:	//red led config
		{
			/* Enable the GPIO_LED clock */
			GPIO_PORT_LED_RED_CLK_ENABLE();

			/* Configure the GPIO_LED pin */
			GPIO_InitStruct.Pin = GPIO_PIN_LED_RED;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

			HAL_GPIO_Init(GPIO_PORT_LED_RED, &GPIO_InitStruct);			
		}
		break;
		case LED_GREEN: //green led config
		{
			/* Enable the GPIO_LED clock */
			GPIO_PORT_LED_GREEN_CLK_ENABLE();

			/* Configure the GPIO_LED pin */
			GPIO_InitStruct.Pin = GPIO_PIN_LED_GREEN;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

			HAL_GPIO_Init(GPIO_PORT_LED_GREEN, &GPIO_InitStruct);				
		}
		break;
		case LED_BLUE:  //blue led config
		{
			/* Enable the GPIO_LED clock */
			GPIO_PORT_LED_BLUE_CLK_ENABLE();

			/* Configure the GPIO_LED pin */
			GPIO_InitStruct.Pin = GPIO_PIN_LED_BLUE;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_PULLUP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

			HAL_GPIO_Init(GPIO_PORT_LED_BLUE, &GPIO_InitStruct);				
		}
		break;
//		case LED_1:    //led1 config
//		{
//			/* Enable the GPIO_LED clock */
//			GPIO_PORT_LED_1_CLK_ENABLE();

//			/* Configure the GPIO_LED pin */
//			GPIO_InitStruct.Pin = GPIO_PIN_LED_1;
//			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//			GPIO_InitStruct.Pull = GPIO_PULLUP;
//			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

//			HAL_GPIO_Init(GPIO_PORT_LED_1, &GPIO_InitStruct);				
//		}
//		break;
//		case LED_2:   //led2 config
//		{
//			/* Enable the GPIO_LED clock */
//			GPIO_PORT_LED_2_CLK_ENABLE();

//			/* Configure the GPIO_LED pin */
//			GPIO_InitStruct.Pin = GPIO_PIN_LED_2;
//			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//			GPIO_InitStruct.Pull = GPIO_PULLUP;
//			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

//			HAL_GPIO_Init(GPIO_PORT_LED_2, &GPIO_InitStruct);		
//		}
//		break;
		default:break;
	}
}	
/**
 * @brief		LEDx_DeInit,deconfig the led pin 
 * @param[in]	ledcolour:LED_RED/LED_GREEN/LED_BLUE
 * @retval		None
 */
void LEDx_DeInit(LED_T ledcolour)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	switch(ledcolour)
	{
		case LED_RED:	//red led config
		{
			/* Enable the GPIO_LED clock */
			GPIO_PORT_LED_RED_CLK_ENABLE();

			/* Configure the GPIO_LED pin */
			GPIO_InitStruct.Pin = GPIO_PIN_LED_RED;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

			HAL_GPIO_Init(GPIO_PORT_LED_RED, &GPIO_InitStruct);			
		}
		break;
		case LED_GREEN: //green led config
		{
			/* Enable the GPIO_LED clock */
			GPIO_PORT_LED_GREEN_CLK_ENABLE();

			/* Configure the GPIO_LED pin */
			GPIO_InitStruct.Pin = GPIO_PIN_LED_GREEN;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

			HAL_GPIO_Init(GPIO_PORT_LED_GREEN, &GPIO_InitStruct);				
		}
		break;
		case LED_BLUE:  //blue led config
		{
			/* Enable the GPIO_LED clock */
			GPIO_PORT_LED_BLUE_CLK_ENABLE();

			/* Configure the GPIO_LED pin */
			GPIO_InitStruct.Pin = GPIO_PIN_LED_BLUE;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

			HAL_GPIO_Init(GPIO_PORT_LED_BLUE, &GPIO_InitStruct);				
		}
		break;
//		case LED_1:    //led1 config
//		{
//			/* Enable the GPIO_LED clock */
//			GPIO_PORT_LED_1_CLK_ENABLE();

//			/* Configure the GPIO_LED pin */
//			GPIO_InitStruct.Pin = GPIO_PIN_LED_1;
//			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//			GPIO_InitStruct.Pull = GPIO_NOPULL;
//			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

//			HAL_GPIO_Init(GPIO_PORT_LED_1, &GPIO_InitStruct);				
//		}
//		break;
//		case LED_2:   //led2 config
//		{
//			/* Enable the GPIO_LED clock */
//			GPIO_PORT_LED_2_CLK_ENABLE();

//			/* Configure the GPIO_LED pin */
//			GPIO_InitStruct.Pin = GPIO_PIN_LED_2;
//			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//			GPIO_InitStruct.Pull = GPIO_NOPULL;
//			GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

//			HAL_GPIO_Init(GPIO_PORT_LED_2, &GPIO_InitStruct);		
//		}
//		break;
		default:break;
	}
}
/**
 * @brief		LED ON
 * @param[in]	ledcolour:LED_RED/LED_GREEN/LED_BLUE
 * @retval		None
 */
void LEDx_ON(LED_T ledcolour)
{
	switch(ledcolour)
	{
		case LED_RED:	//red led config
		{
			HAL_GPIO_WritePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,GPIO_PIN_RESET);	
		}
		break;
		case LED_GREEN: //green led config
		{
			HAL_GPIO_WritePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,GPIO_PIN_RESET);				
		}
		break;
		case LED_BLUE:  //blue led config
		{
			HAL_GPIO_WritePin(GPIO_PORT_LED_BLUE,GPIO_PIN_LED_BLUE,GPIO_PIN_RESET);				
		}
		break;
		default:break;
	}
}
/**
 * @brief		LED OFF
 * @param[in]	ledcolour:LED_RED/LED_GREEN/LED_BLUE
 * @retval		None
 */
void LEDx_OFF(LED_T ledcolour)
{
	switch(ledcolour)
	{
		case LED_RED:	//red led config
		{
			HAL_GPIO_WritePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED,GPIO_PIN_SET);	
		}
		break;
		case LED_GREEN: //green led config
		{
			HAL_GPIO_WritePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN,GPIO_PIN_SET);				
		}
		break;
		case LED_BLUE:  //blue led config
		{
			HAL_GPIO_WritePin(GPIO_PORT_LED_BLUE,GPIO_PIN_LED_BLUE,GPIO_PIN_SET);				
		}
		break;
		default:break;
	}
}
/**
 * @brief		LED Toggle
 * @param[in]	ledcolour:LED_RED/LED_GREEN/LED_BLUE
 * @retval		None
 */
void LEDx_Toggle(LED_T ledcolour)
{	
	switch(ledcolour)
	{
		case LED_RED:	//red led config
		{
			HAL_GPIO_TogglePin(GPIO_PORT_LED_RED,GPIO_PIN_LED_RED);	
		}
		break;
		case LED_GREEN: //green led config
		{
			HAL_GPIO_TogglePin(GPIO_PORT_LED_GREEN,GPIO_PIN_LED_GREEN);				
		}
		break;
		case LED_BLUE:  //blue led config
		{
			HAL_GPIO_TogglePin(GPIO_PORT_LED_BLUE,GPIO_PIN_LED_BLUE);				
		}
		break;
		default:break;
	}
}








/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

