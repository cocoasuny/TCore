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

/* kind of NTC define */
typedef enum
{
	NTC_2K = 0,
	NTC_10K
}NTC_TYPE_T;

#define NTC_LUT_LEN  (160)   //25.0~40.9℃

/* core temperature parameters define */
#define Ks		(50.0f) //the heat transfer coefficient of insulation disk
#define Kg      (50.0f) //the heat transfer coefficient of human tissue
#define Kiso    (50.0f) //he Heat transfer coefficient of the exterior insulation
#define Aiso_m	(1.0f)  //the jacket surface area of the outside insulation
#define As		(1.0f)  //the front area of the Double Sensor, which has the same diameter as the insulation
#define alpha   (20)    //the heat transfer coefficient from the wall to the ambient air witch modified
						//within the range of 10 and 30 W/(m2 K), this does not impact the calculation in 
						//any significant way

/***********************  core temperature calculate formula ************************************************/
/*                                                                                                          */
/*				 Ks				  Kiso Aiso_m	TH1+TH2		aTH2 - Ks(TH1-TH2) + Kiso((TH1+TH2)/2)          */
/* Tcore = TH1 + --*(TH1 - TH2) + ----*------*(--------- - --------------------------------------- )        */
/*               Kg                Kg    As        2                       a + Kiso                         */ 
/*                                                                                                          */
/************************************************************************************************************/                                                                                                        

/* function declare */
void ntc_temperature_calculate(uint32_t Rt,float *tVal,NTC_TYPE_T ntctype);
void alg_core_temperature_calculate_init(void);
void core_temperature_calculate(float Th1,float Th2, float *coreTem);

#endif /* __ALG_TEMPERATURE_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
