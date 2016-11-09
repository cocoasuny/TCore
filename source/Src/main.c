/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
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
#include "main.h"


/* Global variables ----------------------------------------------------------*/
volatile AxesRaw_t 					g_Axes_data = {0, 0, 0};
uint16_t 							g_LedFlashTime = 500;
uint8_t  							g_aRxBuffer[RXBUFFERSIZE] = {0};
QueueHandle_t						coreTemEventQueue = NULL;  //event queue for core temperature
QueueHandle_t                       userInterFaceEventQueue = NULL; //event queue for userInterface
float								g_TemVal = 0;   //参考温度结果值
float								g_coreTemVal = 0;  //核心温度结果值

/* Private variables ---------------------------------------------------------*/
static uint16_t 					gSubFuncState = OFF;
SD_HandleTypeDef hsd;
HAL_SD_CardInfoTypedef SDCardInfo;
char SDPath[4];  /* SD logical drive path */
FATFS SDFatFs;  /* File system object for SD card logical drive */
FIL  MyFile;     /* File object */

/* Private variables ---------------------------------------------------------*/
xTaskHandle  xHandleLedCtl;
xTaskHandle  xHandleBlueNRGHCI;
xTaskHandle  xHandleCoreTemperature;
xTaskHandle  xHandleUserInterface;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void LedCtlTask(void *pvParameters);

/*******************************************************************************
* Function Name  : main函数
* Description    : main函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Bsp Init */
    Bsp_Init();
    
    /* BlueNRG Init */
    BlueNRG_Init();

    /* Create the Tasks */
	key_time_init();
	
    /* Led Control Task */
    xTaskCreate(
                LedCtlTask,                 //任务函数
				"LedCtl",                   //任务名称
                500,                        //stack大小，单位word
                NULL,                       //任务参数
                1,                          //任务优先级
                &xHandleLedCtl);            //任务句柄
                
    /* BlueNRG HCI Task */
    xTaskCreate(
                BlueNRGHCITask,             //任务函数
                "BlueHCI",                  //任务名称
                Task_BlueNRGHCI_Stack,      //stack大小，单位word
                NULL,                       //任务参数
                Task_BlueNRGHCI_Priority,   //任务优先级
                &xHandleBlueNRGHCI);        //任务句柄  

	/* core temperature measure task */
	xTaskCreate(coreTemperatureTaskHandle,"Tcore",Task_CoreTemperature_Stack,NULL,
				Task_CoreTemperature_Priority,&xHandleCoreTemperature);
                
    /* user interface task */
    xTaskCreate(userInterfaceTaskHandle,"UI",Task_userInterface_Stack,NULL,
                Task_userInterface_Priority,&xHandleUserInterface);
                
    /* Start scheduler */
    vTaskStartScheduler();

    /* We should never get here as control is now taken by the scheduler */
	printf("Scheduler Err\r\n");
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    }
    /* USER CODE END 3 */

}

/*******************************************************************************
* Function Name  : LedCtlTask
* Description    : 控制LED
* Input          : pvParameters，创建任务时传入参数
* Output         : None
* Return         : None
*******************************************************************************/
void LedCtlTask(void *pvParameters)
{
	Axes_TypeDef Axes;
	
    BSP_LED_Init();     //Led GPIO Init
    
    while(1)
    {
#ifdef SHELL_ENABLE			
		Shell_ProcessorHandler();     //Shell处理函数
#endif			
        BSP_LED_Toggle();
//        LEDx_Toggle(LED_RED);
		
		memset(&Axes,0,sizeof(Axes));
		BSP_IMU_6AXES_X_GetAxes(&Axes);
        
        /* for test */
        g_Axes_data.AXIS_X = Axes.AXIS_X;
        g_Axes_data.AXIS_Y = Axes.AXIS_Y;
        g_Axes_data.AXIS_Z = Axes.AXIS_Z;
        BlueNRG_Update_Acc((AxesRaw_t*)&g_Axes_data);
        vTaskDelay(g_LedFlashTime);     //控制LDE闪烁频率
    }
}
/**
  * @brief  gSubFunc_stat_set
  * @note   设置测量状态
  * @param  mask,newState
  * @retval None    
  */
void gSubFunc_stat_set(uint16_t mask, uint8_t newState)
{
	gSubFuncState = (newState == OFF)? gSubFuncState & (~mask) : gSubFuncState | mask;
}
/**
  * @brief  gSubFunc_stat_get
  * @note   获取测量状态
  * @param  mask
  * @retval status    
  */
uint16_t gSubFunc_stat_get(uint16_t mask)
{
	return(gSubFuncState & mask);
}
/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

  HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_PLLCLK, RCC_MCODIV_1);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
     PA8   ------> RCC_MCO_1
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
