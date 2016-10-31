/**
 ******************************************************************************
 * @file    ads1118.h
 * @author  Jason
 * @version V1.0.0
 * @date    2016-10-30
 * @brief   This file contains definitions for the ads1118.c
 *          firmware driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 ******************************************************************************
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ADS1118_H
#define __ADS1118_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/*************ADS1118 Control Register Define**************************************/
////Single-end Channel define
#define SingleEndCH0    		0x4000
#define SingleEndCH1    		0x5000
#define SingleEndCH2    		0x6000
#define SingleEndCH3    		0x7000

////Differential Channel define
#define DifferentialCH0_1   	0x0000
#define DifferentialCH0_3   	0x1000
#define DifferentialCH1_3   	0x2000
#define DifferentialCH2_3   	0x3000

////Full scale define
#define FS_6    	0x0000
#define FS_4    	0x0200
#define FS_2    	0x0400
#define FS_1    	0x0600
#define FS_05   	0x0800
#define FS_02   	0x0A00

////Device operating mode
#define ContinuousMode    	0x0000
#define SigleShotMode     	0x0100

////Data rate define
#define DR8SPS        0x0000
#define DR16SPS       0x0020
#define DR32SPS       0x0040
#define DR64SPS       0x0060
#define DR128SPS      0x0080
#define DR250SPS      0x00A0
#define DR475SPS      0x00C0
#define DR860SPS      0x00E0

////Temperature sensor Mode define
#define MODEADC    0x0000
#define MODETS     0x0010

////PULL Up define
#define PULLUPDISABLE    0x0000
#define PULLUPENABLE     0x0008

////No Operature define
#define NOP              0x0000
#define UpdateCR         0x0002

#define ADS1118Start    0x8000|FS_1|SigleShotMode|DR128SPS|MODEADC|PULLUPDISABLE|UpdateCR


/* function declare */
HAL_StatusTypeDef ads1118_init(void);
HAL_StatusTypeDef ads1118_getVal(uint16_t CMD, int16_t * pDatRe);





#endif /* __ADS1118_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
