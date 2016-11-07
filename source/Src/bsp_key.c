/**
******************************************************************************
* @file    bsp_key.c 
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
#include "bsp_key.h"


/* private variables */
static TimerHandle_t s_Key1Timer = NULL;
volatile static bool s_KeyPressStatus = VALIDE;
static TimerHandle_t s_Key2Timer = NULL;

/* privatr function */
static void key_press_time_cb(xTimerHandle pxTimer);


/**
 * @brief		Keyx_Init,config the keys pin 
 * @param[in]	key: KEY0/KEY1
 * @retval		None
 */
void Keyx_Init(KEY_T key)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	switch(key)
	{
		case KEY1:
		{
			/* Enable GPIO clock */
			GPIO_PORT_KEY1_CLK_ENABLE();

			/* Configure Key0 pin as input floating */
			GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStructure.Pull = GPIO_NOPULL;
			GPIO_InitStructure.Pin = GPIO_PIN_KEY1;
			HAL_GPIO_Init(GPIO_PORT_KEY1, &GPIO_InitStructure);

			/* Enable and set EXTI Line Interrupt priority */
			HAL_NVIC_SetPriority(EXTI_KEY1_IRQn, EXTI_KEY_PRE_PRIORITY, EXTI_KEY_SUB_PRIORITY);
			HAL_NVIC_EnableIRQ(EXTI_KEY1_IRQn);	        
		}
		break;
		case KEY2:
		{
			/* Enable GPIO clock */
			GPIO_PORT_KEY2_CLK_ENABLE();

			/* Configure Key1 pin as input floating */
			GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStructure.Pull = GPIO_NOPULL;
			GPIO_InitStructure.Pin = GPIO_PIN_KEY2;
			HAL_GPIO_Init(GPIO_PORT_KEY2, &GPIO_InitStructure);

			/* Enable and set EXTI Line Interrupt priority */
			HAL_NVIC_SetPriority(EXTI_KEY2_IRQn, EXTI_KEY_PRE_PRIORITY, EXTI_KEY_SUB_PRIORITY);
			HAL_NVIC_EnableIRQ(EXTI_KEY2_IRQn);			
		}
		break;
		default:break;
	}
}	
/**
* @brief		Key1_EXTI_Handle,！！！这是一个中断服务函数
 * @param[in]	None
 * @retval		None
 */
void Key1_EXTI_Handle(void)
{
	static bool 				keyPressDectetCtl = true; //true:检测下降沿，false:检测上升沿
	static uint32_t				pressDownTick = 0;
	BaseType_t 					xHigherPriorityTaskWoken = pdFALSE;
	BaseType_t					xResult = pdFAIL;

    
	if(s_KeyPressStatus == INVALIDE)
	{
		keyPressDectetCtl = true;
		pressDownTick = 0;
	}
	else if(s_KeyPressStatus == VALIDE)
	{
		if(keyPressDectetCtl == true) //当次检测下降沿
		{
			keyPressDectetCtl = false; //下次检测上升沿
			if(HAL_GPIO_ReadPin(GPIO_PORT_KEY1,GPIO_PIN_KEY1) == GPIO_PIN_RESET)  //Key1按下
			{
                printf("key1 press down\r\n");
				s_Key1Timer = xTimerCreate("Time",LONG_PRESS_TIME,pdFALSE,(void *)1,key_press_time_cb);
                printf("timer ok\r\n");
                if(s_Key1Timer == NULL)
                {
                    printf("timer err\r\n");
                }
//				xResult = xTimerStartFromISR(s_Key1Timer,&xHigherPriorityTaskWoken);
//				pressDownTick = HAL_GetTick();
//				if(xResult != pdFAIL)
//				{
//					portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
//				}
			}
		}
		else if(keyPressDectetCtl == false) //当次检测上升沿
		{
			keyPressDectetCtl = true; //下次检测下降沿
			if(HAL_GPIO_ReadPin(GPIO_PORT_KEY1,GPIO_PIN_KEY1) == GPIO_PIN_SET)  //Key1松开
			{
				if((HAL_GetTick() - pressDownTick) < LONG_PRESS_TIME)
				{
					printf("Key1 Short Press\r\n");
				}
				else
				{
					printf("Key1 Long Press\r\n");
				}
				xResult = xTimerStopFromISR(s_Key1Timer,&xHigherPriorityTaskWoken);
				if(xResult != pdFAIL)
				{
					portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
				}
				
				s_KeyPressStatus = INVALIDE;
				
				xResult = xTimerChangePeriodFromISR(s_Key1Timer,KEY_INVALIDE_TIME,&xHigherPriorityTaskWoken);
				if(xResult != pdFAIL)
				{
					portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
				}
				xResult = xTimerStartFromISR(s_Key1Timer,&xHigherPriorityTaskWoken);
				if(xResult != pdFAIL)
				{
					portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
				}				
			}
		}
	}
}

/**
 * @brief		Key1_EXTI_Handle，！！！这是一个中断服务函数
 * @param[in]	None
 * @retval		None
 */
void Key2_EXTI_Handle(void)
{

}
 
/**
 * @brief		key_press_time_cb，！！！这是一个中断服务函数
 * @param[in]	None
 * @retval		None
 */ 
static void key_press_time_cb(xTimerHandle pxTimer)
{
	if(s_KeyPressStatus == VALIDE)
	{
		//Valide的情况下，说明按键超时，属于长按键事件
		s_KeyPressStatus = INVALIDE;
		printf("Key1 Long Press\r\n");
		xTimerDelete(s_Key1Timer,0);
	}
	else
	{
		s_KeyPressStatus = VALIDE;
		xTimerDelete(s_Key1Timer,0);
	}
}	
 
 
 
 
 
 
 
 
 
 
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

