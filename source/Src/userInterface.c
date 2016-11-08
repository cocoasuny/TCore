/**
  ****************************************************************************************
  * @file    userInterface.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-8
  * @brief   user interface
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "userInterface.h"


/**
  * @brief  userInterfaceTaskHandle
  * @note   人机交互任务
  * @param  pvParameters
  * @retval None    
  */
void userInterfaceTaskHandle(void *pvParameters)
{
    const TickType_t 		xMaxBlockTime = pdMS_TO_TICKS(300); /* 设置最大等待时间为 300ms */
    USER_INTERFACE_MSG_T    UIQueueMsgValue;
    TEM_MSG_T 				temQueueMsgValue;
    
    /* creat event queue for userInterface */
    userInterFaceEventQueue = xQueueCreate(USER_INTERFACE_EVENT_QUEUE_SIZE,sizeof(USER_INTERFACE_MSG_T));
    #ifdef DEBUG_USER_INTERFACE
		if(coreTemEventQueue == NULL)
		{
			printf("user interface queue creat fail\r\n");
		}
	#endif
		
	/* user interface event queue init */
	UIQueueMsgValue.eventID = EVENT_USER_INTERFACE_DEFAULT;
        
    while(1)
    {
        if(pdPASS == xQueueReceive(userInterFaceEventQueue,(void *)&UIQueueMsgValue,xMaxBlockTime))
        {
            switch(UIQueueMsgValue.eventID)  //消息事件处理
            {
                case EVENT_USER_INTERFACE_SHORT_PRESS:
                {
//                    printf("short press event\r\n");
                    /* 如果在测量中，则停止测量；否则切换测量模式 */
                    if(gSubFunc_stat_get(TEMPERATURE_MEASURE_STATUS) != OFF) //测量运行中
                    {
                        if(temperature_measure_mode_get() == REFTEM_MEASURE_MODE)
                        {
                            //停止参考温度测量
                            temQueueMsgValue.eventID = EVENT_STOP_REFTEM_MEASURE;
                            xQueueSend(coreTemEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime); 
                        }
                        else if(temperature_measure_mode_get() == CORETEM_MEASURE_MODE)
                        {
                            //停止核心温度测量
                            temQueueMsgValue.eventID = EVENT_STOP_CORETEM_MEASURE;
                            xQueueSend(coreTemEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime);                             
                        }
                    }
                    else  //测量处于停止状态,短按按键切换测量模式
                    {
                        if(temperature_measure_mode_get() == REFTEM_MEASURE_MODE)
                        {
                            //切换为核心温度测量模式
                            temperature_measure_mode_set(CORETEM_MEASURE_MODE);
                        }
                        else if(temperature_measure_mode_get() == CORETEM_MEASURE_MODE)
                        {
                            //切换为参考温度测量模式
                            temperature_measure_mode_set(REFTEM_MEASURE_MODE);
                        }
                    }
                }
                break;
                case EVENT_USER_INTERFACE_LONG_PRESS:
                {
                    //printf("long press event\r\n");
                    /* 如果处于停止测量状态，长按则开启测量；如果处于测量状态，则停止测量 */
                    if(gSubFunc_stat_get(TEMPERATURE_MEASURE_STATUS) == OFF) //停止测量状态
                    {
                        if(temperature_measure_mode_get() == REFTEM_MEASURE_MODE)
                        {
                            //开启参考温度测量
                            temQueueMsgValue.eventID = EVENT_START_REFTEM_MEASURE;
                            xQueueSend(coreTemEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime); 
                        }
                        else if(temperature_measure_mode_get() == CORETEM_MEASURE_MODE)
                        {
                            //开启核心温度测量
                            temQueueMsgValue.eventID = EVENT_START_CORETEM_MEASURE;
                            xQueueSend(coreTemEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime);                             
                        }
                    }
                    else  //测量处于测量中,长按按键则停止对于的测量
                    {
                        if(temperature_measure_mode_get() == REFTEM_MEASURE_MODE)
                        {
                            //停止参考温度测量
                            temQueueMsgValue.eventID = EVENT_STOP_REFTEM_MEASURE;
                            xQueueSend(coreTemEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime); 
                        }
                        else if(temperature_measure_mode_get() == CORETEM_MEASURE_MODE)
                        {
                            //停止核心温度测量
                            temQueueMsgValue.eventID = EVENT_STOP_CORETEM_MEASURE;
                            xQueueSend(coreTemEventQueue,(void *)&temQueueMsgValue,xMaxBlockTime);                             
                        }
                    }                    
                }
                break;
                default:break;
            }
            
        }//end of  if(pdPASS == xQueueReceive...)
    }
}



/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT DBGJ Co., Ltd. *****END OF FILE****/

