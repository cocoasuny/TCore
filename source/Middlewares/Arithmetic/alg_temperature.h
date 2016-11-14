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

/***********************  core temperature calculate formula ************************************************/
/*                                                                                                          */
/*				 Ks				  Kiso Aiso_m	TH1+TH2		aTH2 - Ks(TH1-TH2) + Kiso((TH1+TH2)/2)          */
/* Tcore = TH1 + --*(TH1 - TH2) + ----*------*(--------- - --------------------------------------- )        */
/*               Kg                Kg    As        2                       a + Kiso                         */ 
/*                                                                                                          */
/************************************************************************************************************/                                                                                                        

/* function declare */
void ntc_temperature_calculate(uint32_t Rt,float *tVal);
void core_temperature_calculate(float Th1,float Th2, float *coreTem);

#endif /* __ALG_TEMPERATURE_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
