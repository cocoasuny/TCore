/**
  ****************************************************************************************
  * @file    userInterface.h
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-8
  * @brief   header file of userInterface.c
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USERINTERFACE_H_
#define __USERINTERFACE_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* definitions */
#define USER_INTERFACE_EVENT_QUEUE_SIZE			(10)


/* Type Struct define -----------------------------------------------------------*/
typedef enum
{
	EVENT_USER_INTERFACE_DEFAULT=0,
	EVENT_USER_INTERFACE_LONG_PRESS,
    EVENT_USER_INTERFACE_SHORT_PRESS,
    EVENT_USER_INTERFACE_RED_LED_ON,
    EVENT_USER_INTERFACE_RED_LED_OFF,
    EVENT_USER_INTERFACE_RED_LED_TOGGLE,
    EVENT_USER_INTERFACE_BLUE_LED_ON,
    EVENT_USER_INTERFACE_BLUE_LED_OFF,
    EVENT_USER_INTERFACE_BLUE_LED_TOGGLE,
    EVENT_USER_INTERFACE_GREEN_LED_ON,
    EVENT_USER_INTERFACE_GREEN_LED_OFF,
    EVENT_USER_INTERFACE_GREEN_LED_TOGGLE  
}USER_INTREFACE_EVENT_ID_T;

typedef struct
{
	USER_INTREFACE_EVENT_ID_T		eventID;			
}USER_INTERFACE_MSG_T;


/* function declare */
void userInterfaceTaskHandle(void *pvParameters);

#endif /* __USERINTERFACE_H_ */

/************************ (C) COPYRIGHT DBGJ Co., Ltd. *****END OF FILE****/

