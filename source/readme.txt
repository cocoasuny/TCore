/**
 ******************************************************************************
 * @file    readme.txt
 * @author  Jason
 * @version V1.0.0
 * @date    2016-11-8
 * @brief   工程说明
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) DBGJ </center></h2>
 *
 ******************************************************************************
 */
 
 硬件版本：V0.0.3版
 MCU：	STM32F401RET6
 RTOS：	FreeRTOS V8.2.1
 
 
 说明：
 1、由于LED1、LED2与主板IIC1接口冲突，主板已使用IIC1，因此取消LED1、LED2.
 2、LED状态指示定义：
	a. 	绿色长亮：处于核心温度模式
	b.	绿色闪烁：核心温度测量中
	c.	蓝色长亮：处于参考温度模式
	d.	蓝色闪烁：参考温度测量中
	e.	红色长亮：
	f.	红色闪烁：
 3、按键操作定义：（针对Key1，Key2暂时未使用）
	a.	按照用于控制参考温度及核心温度的测量及模式切换。
	b.	温度测量停止时：
		1):	长按按键开启温度测量。
		2):	短按按键切换测量模式：参考温度模式下短按按键切换至核心温度测量模式；
			核心温度测量模式下短按按键切换至参考温度测量模式。
	c.	温度测量运行中：
		1):	长/短按按键均停止温度测量。
		
 4、核心温度测量相关定义:
	双探头式核心温度测量模型参见文档《A non-invasive device to continuously determine 
	heat strain in humans》Figure2 in page4.参数定义如下：
	a.	TH1: skin temperature.
	b.	TH2: temperature of the Double Sensor on the side facing away from the skin.
	对应原理图上，P9,1/2引脚为TH1；3/4引脚为TH2。
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	