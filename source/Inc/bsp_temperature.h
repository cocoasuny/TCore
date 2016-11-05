/**
 ******************************************************************************
 * @file    bsp_temperature.h
 * @author  Jason
 * @version V1.0.0
 * @date    2016-11-3
 * @brief   This file contains definitions for the bsp_temperature.c
 *          firmware driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_TEMPERATURE_H
#define __BSP_TEMPERATURE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ads1118.h"

/* typedef struct define */
typedef enum
{
	ChannelA0B0 = 0,
	ChannelA1B1,
	ChannelA2B2,
	ChannelA3B3
}SWITCH_CHANNEL_DEF;


/* function delcare */
void ref_temperature_init(void);
void ref_temperature_sample(float *VSens12,float *VSens23);
void ref_temperature_deinit(void);
void core_temperature_hw_init(void);
void core_ambient_temperature_sample(float *VSens12,float *VSens23);
void core_forehead_temperature_sample(float *VSens12,float *VSens23);
void core_temperature_hw_deinit(void);


#endif /* __BSP_TEMPERATURE_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

