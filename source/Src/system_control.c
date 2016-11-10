/**
  ****************************************************************************************
  * @file    system_control.c
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-10
  * @brief   system control
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "system_control.h"


/**
  * @brief  sysControlTask
  * @note   系统任务处理函数
  * @param  pvParameters
  * @retval None    
  */
void sysControlTask(void *pvParameters)
{
	Axes_TypeDef            Axes;
    float                   batVoltage = 0;
    const TickType_t 		xMaxBlockTime = pdMS_TO_TICKS(300); /* 设置最大等待时间为 300ms */
    USER_INTERFACE_MSG_T    UIQueueMsgValue;
    static bool             flagLowBattery = false;
	
    BSP_LED_Init();     //Led GPIO Init
    
    while(1)
    {
#ifdef SHELL_ENABLE			
		Shell_ProcessorHandler();     //Shell处理函数
#endif			
        BSP_LED_Toggle();
		
		memset(&Axes,0,sizeof(Axes));
		BSP_IMU_6AXES_X_GetAxes(&Axes);
        
        /* for test */
        g_Axes_data.AXIS_X = Axes.AXIS_X;
        g_Axes_data.AXIS_Y = Axes.AXIS_Y;
        g_Axes_data.AXIS_Z = Axes.AXIS_Z;
        BlueNRG_Update_Acc((AxesRaw_t*)&g_Axes_data);
        
        get_battery_voltage(&batVoltage);
        if(batVoltage < 3.0f)
        {
            flagLowBattery = true;
            UIQueueMsgValue.eventID = EVENT_USER_INTERFACE_RED_LED_TOGGLE;
            xQueueSend(userInterFaceEventQueue,(void *)&UIQueueMsgValue,xMaxBlockTime);            
        }
        else if((batVoltage >= 3.3f) && flagLowBattery == true)
        {
            flagLowBattery = false;
            UIQueueMsgValue.eventID = EVENT_USER_INTERFACE_RED_LED_OFF;
            xQueueSend(userInterFaceEventQueue,(void *)&UIQueueMsgValue,xMaxBlockTime);              
        }
        
        vTaskDelay(g_LedFlashTime);     //控制LDE闪烁频率
    }
}



/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT DBGJ Co., Ltd. *****END OF FILE****/


