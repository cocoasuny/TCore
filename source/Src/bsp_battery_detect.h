/**
  ****************************************************************************************
  * @file    bsp_battery_detect.h
  * @author  Jason
  * @version V1.0.0
  * @date    2016-11-10
  * @brief   header file of bsp_battery_detect.c
  ****************************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 DBGJ Co., Ltd.</center></h2>
  *
  ****************************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_BATTERY_DETECT_H_
#define __BSP_BATTERY_DETECT_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* definitions */

/* function declare */
HAL_StatusTypeDef get_battery_voltage(float *voltage);

#endif /* __BSP_BATTERY_DETECT_H_ */

/************************ (C) COPYRIGHT DBGJ Co., Ltd. *****END OF FILE****/

