/**
 ******************************************************************************
 * @file    bsp_imu_6axes.h
 * @author  Jason
 * @version V1.0.0
 * @date    22-10-2016
 * @brief   This file contains definitions for the x_nucleo_iks01a1_imu_6axes.c
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_IMU_6AXES_H
#define __BSP_IMU_6AXES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Include nine axes sensor component driver */
#include "lsm6ds3.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup X_NUCLEO_IKS01A1
 * @{
 */

/** @addtogroup X_NUCLEO_IKS01A1_IMU_6AXES
 * @{
 */


/** @defgroup X_NUCLEO_IKS01A1_IMU_6AXES_Exported_Functions X_NUCLEO_IKS01A1_IMU_6AXES_Exported_Functions
 * @{
 */

/* Sensor Configuration Functions */
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_Init(void);

uint8_t BSP_IMU_6AXES_isInitialized(void);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_Read_XG_ID(uint8_t *);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_Check_XG_ID(void);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_X_GetAxes(Axes_TypeDef *pData);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_X_GetAxesRaw(AxesRaw_TypeDef *pData);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_G_GetAxes(Axes_TypeDef *pData);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_G_GetAxesRaw(AxesRaw_TypeDef *pData);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_X_Get_ODR(float *odr);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_X_Set_ODR(float odr);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_X_GetSensitivity(float *pfData);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_X_Get_FS(float *fullScale);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_X_Set_FS(float fullScale);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_G_Get_ODR(float *odr);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_G_Set_ODR(float odr);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_G_GetSensitivity(float *pfData);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_G_Get_FS(float *fullScale);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_G_Set_FS(float fullScale);
IMU_6AXES_ComponentTypeDef BSP_IMU_6AXES_GetComponentType(void);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_Enable_Free_Fall_Detection_Ext(void);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_Disable_Free_Fall_Detection_Ext(void);
IMU_6AXES_StatusTypeDef BSP_IMU_6AXES_Get_Status_Free_Fall_Detection_Ext(uint8_t *status);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __BSP_IMU_6AXES_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
