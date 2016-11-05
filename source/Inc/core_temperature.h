/**
 ******************************************************************************
 * @file    core_temperature.h
 * @author  Jason
 * @version V1.0.0
 * @date    2016-11-3
 * @brief   This file contains definitions for the core_temperature.c
 *          firmware driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CORE_TEMPERATURE_H
#define __CORE_TEMPERATURE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* definitions */
#define CORE_TEMPERATURE_EVENT_QUEUE_SIZE			(10)
#define TEM_SAMPLE_PER								pdMS_TO_TICKS(1000) //ms
#define R_CAL										(10000) //Ω

/* type struct define */
typedef enum
{
	EVENT_TEMPERATURE_DEFAULT=0,
	EVENT_START_CORETEM_MEASURE,
	EVENT_GET_CORETEM_RESULT,
	EVENT_STOP_CORETEM_MEASURE,
	EVENT_START_REFTEM_MEASURE,
	EVENT_GET_REFTEM_RESULT,
	EVENT_STOP_REFTEM_MEASURE
}TEM_EVENT_ID_T;

typedef struct
{
	TEM_EVENT_ID_T		eventID;			
}TEM_MSG_T;

typedef enum
{
	REFTEM_MEASURE_MODE = 0,
	CORETEM_MEASURE_MODE
}TEM_MEASURE_MODE_T;

/* function delcare */
void coreTemperatureTaskHandle(void *pvParameters);
void temperature_measure_mode_set(TEM_MEASURE_MODE_T mode);
TEM_MEASURE_MODE_T temperature_measure_mode_get(void);



#endif /* __CORE_TEMPERATURE_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

