/**
 ******************************************************************************
 * @file    core_temperature.c
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
#include "core_temperature.h"

/* private variable declare */
static TimerHandle_t				temSampleTime = NULL;
static TEM_MEASURE_MODE_T			temMeasureMode = CORETEM_MEASURE_MODE; //temperature measure mode


/* private function declare */
static void temperature_sampleTimer_cb(xTimerHandle pxTimer);
static void ref_temperature_rt_sample(uint32_t *Rt);

/**
  * @brief  coreTemperatureTaskHandle
  * @note   Tcore测量任务
  * @param  pvParameters
  * @retval None    
  */
void coreTemperatureTaskHandle(void *pvParameters)
{
	const TickType_t 		xMaxBlockTime = pdMS_TO_TICKS(300); /* 设置最大等待时间为 300ms */
	TEM_MSG_T 				temQueueMsgValue;
	uint32_t                Rt = 0;
	
	/* creat event queue for core temperature */
	coreTemEventQueue = xQueueCreate(CORE_TEMPERATURE_EVENT_QUEUE_SIZE,sizeof(TEM_MSG_T));
	#ifdef DEBUG_TEMPERATURE
		if(coreTemEventQueue == NULL)
		{
			printf("temperature queue creat fail\r\n");
		}
	#endif
		
	/* temperture event queue init */
	temQueueMsgValue.eventID = EVENT_TEMPERATURE_DEFAULT;
	gSubFunc_stat_set(TEMPERATURE_MEASURE_STATUS,OFF);
	
	while(1)
	{
		if(pdPASS == xQueueReceive(coreTemEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime))
		{
			/* 接收到消息，对消息事件进行处理 */
			switch(temQueueMsgValue.eventID)
			{
				case EVENT_START_REFTEM_MEASURE:
				{				
                    #ifdef DEBUG_TEMPERATURE
                        printf("start ref temperature\r\n");
                    #endif
					/* init ref temperature measure arithmetic */
					
					/* start the time for temperature measure freq */
					if(temSampleTime != NULL)
					{
						xTimerDelete(temSampleTime,0);
					}
					temSampleTime = xTimerCreate("temTime",TEM_SAMPLE_PER,pdTRUE,(void *)0,temperature_sampleTimer_cb);
					xTimerStart(temSampleTime,0);
					temperature_measure_mode_set(REFTEM_MEASURE_MODE);
					
					gSubFunc_stat_set(TEMPERATURE_MEASURE_STATUS,ON);
				}
				break;
				case EVENT_GET_REFTEM_RESULT:
				{
                    #ifdef DEBUG_TEMPERATURE
                        printf("get ref temperature\r\n");
                    #endif                    
					if(gSubFunc_stat_get(TEMPERATURE_MEASURE_STATUS) != OFF)
					{
						/* ref temperature sample */
						Rt = 0;
						ref_temperature_rt_sample(&Rt);
//						/* ref temperature measure */
//						ref_temperature_calculate(Rt,&g_refTemVal);
					}
				}
				break;
				case EVENT_STOP_REFTEM_MEASURE:
				{
                    #ifdef DEBUG_TEMPERATURE
                        printf("stop ref temperature\r\n");
                    #endif                    
					xTimerDelete(temSampleTime,0);
					temSampleTime = NULL;
					gSubFunc_stat_set(TEMPERATURE_MEASURE_STATUS,OFF);
				}
				break;
				case EVENT_START_CORETEM_MEASURE:
				{				
                    #ifdef DEBUG_TEMPERATURE
                        printf("start core temperature\r\n");
                    #endif
					/* init ref temperature measure arithmetic */
					
					/* start the time for temperature measure freq */
					if(temSampleTime != NULL)
					{
						xTimerDelete(temSampleTime,0);
					}
					temSampleTime = xTimerCreate("temTime",TEM_SAMPLE_PER,pdTRUE,(void *)0,temperature_sampleTimer_cb);
					xTimerStart(temSampleTime,0);
					temperature_measure_mode_set(CORETEM_MEASURE_MODE);
					
					gSubFunc_stat_set(TEMPERATURE_MEASURE_STATUS,ON);
				}
				break;
				case EVENT_GET_CORETEM_RESULT:
				{
                    #ifdef DEBUG_TEMPERATURE
                        printf("get core temperature\r\n");
                    #endif                    
					if(gSubFunc_stat_get(TEMPERATURE_MEASURE_STATUS) != OFF)
					{
						/* core temperature sample */


						/* core temperature measure */

					}
				}
				break;
				case EVENT_STOP_CORETEM_MEASURE:
				{
                    #ifdef DEBUG_TEMPERATURE
                        printf("stop core temperature\r\n");
                    #endif                    
					xTimerDelete(temSampleTime,0);
					temSampleTime = NULL;
					gSubFunc_stat_set(TEMPERATURE_MEASURE_STATUS,OFF);
				}
				break;                
				default:break;
			}
		}
		
		/* core temperature sample */
		
		/* core temperature measure */
		
		/* update the value */
	}
}
/**
  * @brief  temperature_measure_mode_set
  * @note   设置温度测量模式
  * @param  mode:@REFTEM_MEASURE_MODE,@CORETEM_MEASURE_MODE
  * @retval None    
  */
void temperature_measure_mode_set(TEM_MEASURE_MODE_T mode)
{
	temMeasureMode = mode;
}
/**
  * @brief  temperature_measure_mode_get
  * @note   获取温度测量模式
  * @param  None 
  * @retval mode:@REFTEM_MEASURE_MODE,@CORETEM_MEASURE_MODE 
  */
TEM_MEASURE_MODE_T temperature_measure_mode_get(void)
{
	return temMeasureMode;
}

/**
  * @brief  temperature_sampleTimer_cb
  * @note   Tcore测量定时器回调函数，用于控制温度测量频率
  * @param  pxTimer
  * @retval None    
  */
static void temperature_sampleTimer_cb(xTimerHandle pxTimer)
{
	TEM_MSG_T 				temQueueMsgValue;
	TEM_MEASURE_MODE_T      mode = CORETEM_MEASURE_MODE;
	const TickType_t 		xMaxBlockTime = pdMS_TO_TICKS(100); /* 设置最大等待时间为 100ms */
	
	pxTimer = pxTimer;
	    
	portENTER_CRITICAL();
	mode = temperature_measure_mode_get();
	portEXIT_CRITICAL();
	switch(mode)
	{
		case CORETEM_MEASURE_MODE:
		{
			temQueueMsgValue.eventID = EVENT_GET_CORETEM_RESULT;
		}
		break;
		case REFTEM_MEASURE_MODE:
		{
			temQueueMsgValue.eventID = EVENT_GET_REFTEM_RESULT;
		}
		break;
		default:break;
	}
	xQueueSend(coreTemEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime);
}
/**
  * @brief  ref_temperature_measure
  * @note   NTC阻值采集
  * @param  *Rt(Ω)
  * @retval None    
  */
static void ref_temperature_rt_sample(uint32_t *Rt)
{
	float Vsens12 = 0;
	float Vsens23 = 0;
	
	/* init ref temperature measure hw source */
	ref_temperature_init();
	ref_temperature_sample(&Vsens12,&Vsens23);
	#ifdef DEBUG_TEMPERATURE
		printf("ADval[12] :%0.01f,    ADval[23] :%0.01f\r\n",Vsens12,Vsens23);
	#endif
	
	/* calculate the value of Rt */
	*Rt = (uint32_t)(Vsens12 / (Vsens23/R_CAL));
	#ifdef DEBUG_TEMPERATURE
		printf("Rt:%dΩ\r\n",*Rt);
	#endif
	
	/* deinit ref temperature measure hw source */	
	ref_temperature_deinit();
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

