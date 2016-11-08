/**
  ******************************************************************************
  * @file    platform.h
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
#ifndef __PLATFORM_H_
#define __PLATFORM_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"


/* Debug Switch */
#define PRINTFLOG
#define Debug_BlueNRF
//#define Debug_Sensor_Humidity
//#define Debug_Sensor_Press
//#define Debug_Sensor_Temperature
#define Debug_LedControl
#define DEBUG_TEMPERATURE
//#define DEBUG_KEY_PRESS
#define DEBUG_USER_INTERFACE


/* Shell Switch */
#define SHELL_ENABLE    //Shell使能
#define RTC_SHELL       //注释掉屏蔽RTC Shell功能
#define FATFS_SHELL

#define RXBUFFERSIZE        1
#define OFF					0
#define ON					1


/******** Task define ********************/
//优先级值越大，优先级越高
/* BlueNRG HCI Process Task */
#define Task_BlueNRGHCI_Stack        500    //task stack
#define Task_BlueNRGHCI_Priority     5      //task priority

/* core temperature task define */
#define Task_CoreTemperature_Stack		500
#define Task_CoreTemperature_Priority	3

/* user interface task define */
#define Task_userInterface_Stack        256
#define Task_userInterface_Priority     2

/* NVIC Priority define */
#define PT_EXTI_KEY_PRE_PRIORITY			0x0A
#define PT_EXTI_KEY_SUB_PRIORITY			0


#ifdef PRINTFLOG
    #define Log  printf
#else
    #define Log  USBLog
#endif    

#define VALIDE		true
#define INVALIDE    false


#define SYSCLK_FREQ 84000000
/* define key Long press time */
#define LONG_PRESS_TIME           pdMS_TO_TICKS(2000)    // ms,长按键检测时间
#define KEY_INVALIDE_TIME         pdMS_TO_TICKS(200)     // ms,按键响应间隔时间


/* Definition for USARTx clock resources */
#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE() 

#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA  
#define USARTx_TX_AF                     GPIO_AF7_USART2
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA 
#define USARTx_RX_AF                     GPIO_AF7_USART2


/* Definition for LED Pins */
#define GPIO_PORT_LED_RED_CLK_ENABLE()			__GPIOC_CLK_ENABLE()
#define GPIO_PORT_LED_RED						GPIOC
#define GPIO_PIN_LED_RED						GPIO_PIN_7
#define GPIO_PORT_LED_GREEN_CLK_ENABLE()		__GPIOA_CLK_ENABLE()
#define GPIO_PORT_LED_GREEN						GPIOA
#define GPIO_PIN_LED_GREEN						GPIO_PIN_10
#define GPIO_PORT_LED_BLUE_CLK_ENABLE()			__GPIOA_CLK_ENABLE()
#define GPIO_PORT_LED_BLUE						GPIOA
#define GPIO_PIN_LED_BLUE						GPIO_PIN_9
//#define GPIO_PORT_LED_1_CLK_ENABLE()			__GPIOB_CLK_ENABLE()
//#define GPIO_PORT_LED_1							GPIOA
//#define GPIO_PIN_LED_1							GPIO_PIN_3
//#define GPIO_PORT_LED_2_CLK_ENABLE()			__GPIOB_CLK_ENABLE()
//#define GPIO_PORT_LED_2							GPIOA
//#define GPIO_PIN_LED_2							GPIO_PIN_3

/* Definition for Key Pins */
#define GPIO_PORT_KEY1_CLK_ENABLE()				__GPIOB_CLK_ENABLE()
#define GPIO_PORT_KEY1							GPIOB
#define GPIO_PIN_KEY1							GPIO_PIN_8
#define EXTI_KEY1_IRQn							EXTI9_5_IRQn
#define GPIO_PORT_KEY2_CLK_ENABLE()				__GPIOC_CLK_ENABLE()
#define GPIO_PORT_KEY2							GPIOC
#define GPIO_PIN_KEY2							GPIO_PIN_13
#define EXTI_KEY2_IRQn							EXTI15_10_IRQn
#define EXTI_KEY_PRE_PRIORITY					PT_EXTI_KEY_PRE_PRIORITY
#define EXTI_KEY_SUB_PRIORITY					PT_EXTI_KEY_SUB_PRIORITY


/* Definition for ADS1118 Pins */
#define GPIO_PORT_ADS1118_CS_CLK_ENABLE()		__GPIOB_CLK_ENABLE()
#define	GPIO_PORT_ADS1118_CS					GPIOB
#define GPIO_PIN_ADS1118_CS						GPIO_PIN_12
#define SPI_ADS1118								SPI2
#define ADS1118_SPI_SCK_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define ADS1118_SPI_MISO_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define ADS1118_SPI_MOSI_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define ADS1118_SPI_CLK_ENABLE()				__HAL_RCC_SPI2_CLK_ENABLE()

/* Definition for ADS1118 SPI Pins */
#define ADS1118_SPI_SCK_PIN                     GPIO_PIN_13
#define ADS1118_SPI_SCK_GPIO_PORT               GPIOB
#define ADS1118_SPI_SCK_AF                      GPIO_AF5_SPI2
#define ADS1118_SPI_MISO_PIN                    GPIO_PIN_14
#define ADS1118_SPI_MISO_GPIO_PORT              GPIOB
#define ADS1118_SPI_MISO_AF                     GPIO_AF5_SPI2
#define ADS1118_SPI_MOSI_PIN                    GPIO_PIN_15
#define ADS1118_SPI_MOSI_GPIO_PORT              GPIOB
#define ADS1118_SPI_MOSI_AF                     GPIO_AF5_SPI2

/* Definition for ref temperature channel switch Pins */
#define GPIO_PORT_REF_TEM_CTL0_CLK_ENABLE()		__GPIOB_CLK_ENABLE()
#define	GPIO_PORT_REF_TEM_CTL0					GPIOB
#define GPIO_PIN_REF_TEM_CTL0					GPIO_PIN_0
#define GPIO_PORT_REF_TEM_CTL1_CLK_ENABLE()		__GPIOA_CLK_ENABLE()
#define	GPIO_PORT_REF_TEM_CTL1					GPIOA
#define GPIO_PIN_REF_TEM_CTL1					GPIO_PIN_8

/* Definition for core temperature channel switch Pins */
#define GPIO_PORT_CORE_TEM_CTL0_CLK_ENABLE()		__GPIOA_CLK_ENABLE()
#define	GPIO_PORT_CORE_TEM_CTL0						GPIOA
#define GPIO_PIN_CORE_TEM_CTL0						GPIO_PIN_1
#define GPIO_PORT_CORE_TEM_CTL1_CLK_ENABLE()		__GPIOA_CLK_ENABLE()
#define	GPIO_PORT_CORE_TEM_CTL1						GPIOA
#define GPIO_PIN_CORE_TEM_CTL1						GPIO_PIN_0



/**
* @brief SPI communication details between Nucleo F4 and BlueNRG
*        Expansion Board.
*/
// SPI Instance
#define BNRG_SPI_INSTANCE           SPI1
#define BNRG_SPI_CLK_ENABLE()       __SPI1_CLK_ENABLE()

// SPI Configuration
#define BNRG_SPI_MODE               SPI_MODE_MASTER
#define BNRG_SPI_DIRECTION          SPI_DIRECTION_2LINES
#define BNRG_SPI_DATASIZE           SPI_DATASIZE_8BIT
#define BNRG_SPI_CLKPOLARITY        SPI_POLARITY_LOW
#define BNRG_SPI_CLKPHASE           SPI_PHASE_1EDGE
#define BNRG_SPI_NSS                SPI_NSS_SOFT
#define BNRG_SPI_FIRSTBIT           SPI_FIRSTBIT_MSB
#define BNRG_SPI_TIMODE             SPI_TIMODE_DISABLED
#define BNRG_SPI_CRCPOLYNOMIAL      7
#define BNRG_SPI_BAUDRATEPRESCALER  SPI_BAUDRATEPRESCALER_4
#define BNRG_SPI_CRCCALCULATION     SPI_CRCCALCULATION_DISABLED

// SPI Reset Pin: PB.1
#define BNRG_SPI_RESET_PIN          GPIO_PIN_1
#define BNRG_SPI_RESET_MODE         GPIO_MODE_OUTPUT_PP
#define BNRG_SPI_RESET_PULL         GPIO_PULLUP
#define BNRG_SPI_RESET_SPEED        GPIO_SPEED_LOW
#define BNRG_SPI_RESET_ALTERNATE    0
#define BNRG_SPI_RESET_PORT         GPIOB
#define BNRG_SPI_RESET_CLK_ENABLE() __GPIOB_CLK_ENABLE()

// SCLK: PA.5
#define BNRG_SPI_SCLK_PIN           GPIO_PIN_5
#define BNRG_SPI_SCLK_MODE          GPIO_MODE_AF_PP
#define BNRG_SPI_SCLK_PULL          GPIO_PULLDOWN
#define BNRG_SPI_SCLK_SPEED         GPIO_SPEED_HIGH
#define BNRG_SPI_SCLK_ALTERNATE     GPIO_AF5_SPI1
#define BNRG_SPI_SCLK_PORT          GPIOA
#define BNRG_SPI_SCLK_CLK_ENABLE()  __GPIOA_CLK_ENABLE()

// MISO (Master Input Slave Output): PA.6
#define BNRG_SPI_MISO_PIN           GPIO_PIN_6
#define BNRG_SPI_MISO_MODE          GPIO_MODE_AF_PP
#define BNRG_SPI_MISO_PULL          GPIO_NOPULL
#define BNRG_SPI_MISO_SPEED         GPIO_SPEED_HIGH
#define BNRG_SPI_MISO_ALTERNATE     GPIO_AF5_SPI1
#define BNRG_SPI_MISO_PORT          GPIOA
#define BNRG_SPI_MISO_CLK_ENABLE()  __GPIOA_CLK_ENABLE()

// MOSI (Master Output Slave Input): PA.7
#define BNRG_SPI_MOSI_PIN           GPIO_PIN_7
#define BNRG_SPI_MOSI_MODE          GPIO_MODE_AF_PP
#define BNRG_SPI_MOSI_PULL          GPIO_NOPULL
#define BNRG_SPI_MOSI_SPEED         GPIO_SPEED_HIGH
#define BNRG_SPI_MOSI_ALTERNATE     GPIO_AF5_SPI1
#define BNRG_SPI_MOSI_PORT          GPIOA
#define BNRG_SPI_MOSI_CLK_ENABLE()  __GPIOA_CLK_ENABLE()

// NSS/CSN/CS: PA.4
#define BNRG_SPI_CS_PIN             GPIO_PIN_4
#define BNRG_SPI_CS_MODE            GPIO_MODE_OUTPUT_PP
#define BNRG_SPI_CS_PULL            GPIO_PULLUP
#define BNRG_SPI_CS_SPEED           GPIO_SPEED_HIGH
#define BNRG_SPI_CS_ALTERNATE       0
#define BNRG_SPI_CS_PORT            GPIOA
#define BNRG_SPI_CS_CLK_ENABLE()    __GPIOA_CLK_ENABLE()

// IRQ: PC.4
#define BNRG_SPI_IRQ_PIN            GPIO_PIN_4
#define BNRG_SPI_IRQ_MODE           GPIO_MODE_IT_RISING
#define BNRG_SPI_IRQ_PULL           GPIO_NOPULL
#define BNRG_SPI_IRQ_SPEED          GPIO_SPEED_HIGH
#define BNRG_SPI_IRQ_ALTERNATE      0
#define BNRG_SPI_IRQ_PORT           GPIOC
#define BNRG_SPI_IRQ_CLK_ENABLE()   __GPIOC_CLK_ENABLE()

// EXTI External Interrupt for SPI
// NOTE: if you change the IRQ pin remember to implement a corresponding handler
// function like EXTI0_IRQHandler() in the user project
#define BNRG_SPI_EXTI_IRQn          EXTI4_IRQn
#define BNRG_SPI_EXTI_IRQHandler    EXTI4_IRQHandler
#define BNRG_SPI_EXTI_PIN           BNRG_SPI_IRQ_PIN
#define BNRG_SPI_EXTI_PORT          BNRG_SPI_IRQ_PORT
#define RTC_WAKEUP_IRQHandler       RTC_WKUP_IRQHandler

//EXTI External Interrupt for user button
#define PUSH_BUTTON_EXTI_IRQHandler EXTI15_10_IRQHandler

#endif /* __PLATFORM_H_ */


