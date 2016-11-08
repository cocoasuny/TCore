/**
  ******************************************************************************
  * @file    main.h
  * @author  CL
  * @version V1.0.0
  * @date    04-July-2014
  * @brief   
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
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
#ifndef __MAIN_H_
#define __MAIN_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "fatfs.h"
#include "cmsis_os.h"
#include "usb_device.h"
#include "bsp.h"
#include "platform.h"
#include "bluenrg_interface.h"
#include "hci.h"
#include "bluenrg_utils.h"
#include "bluenrg_service.h"
#include "freertostask.h"
#include "bluenrg_sensor_service.h"
#include "bluenrg_remotecontrol_service.h"
#include "global_typedef.h"
#include "shell.h"
#include "bsp_rtc_calendar.h"
#include "Log.h"
#include "bsp_imu_6axes.h"
#include "core_temperature.h"
#include "bsp_temperature.h"
#include "alg_temperature.h"
#include "userInterface.h"

/* Define sub-function status */
#define TEMPERATURE_MEASURE_STATUS 			(1 << 0)

extern volatile AxesRaw_t 					g_Axes_data;
extern uint16_t 							g_LedFlashTime;
extern uint8_t  							g_aRxBuffer[RXBUFFERSIZE];
extern char 								SDPath[4];  /* SD logical drive path */
extern FATFS 								SDFatFs;  /* File system object for SD card logical drive */
extern FIL  								MyFile;     /* File object */
extern QueueHandle_t						coreTemEventQueue;
extern QueueHandle_t                        userInterFaceEventQueue; //event queue for userInterface
extern float								g_refTemVal;
extern float								g_coreTemVal;  //核心温度结果值

void MX_GPIO_Init(void);
void MX_SDIO_SD_Init(void);
void gSubFunc_stat_set(uint16_t mask, uint8_t newState);
uint16_t gSubFunc_stat_get(uint16_t mask);


#endif /* __MAIN_H_ */

