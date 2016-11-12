/**
 ******************************************************************************
 * @file    alg_temperature.h
 * @author  Jason
 * @version V1.0.0
 * @date    2016-11-5
 * @brief   The arithmetic of temperature
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ALG_TEMPERATURE_H
#define __ALG_TEMPERATURE_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define NTC_LUT_LEN  (160)   //25.0~40.9℃



/* function declare */
void ntc_temperature_calculate(uint32_t Rt,float *tVal);

#endif /* __ALG_TEMPERATURE_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
