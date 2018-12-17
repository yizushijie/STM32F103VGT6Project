#ifndef LED_CFG_H_
#define LED_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#ifdef USE_MCU_STM32
	#include "gpio_task.h"
	#endif
	#include "systick_task.h"

	#define USE_LED_DEBUG

	#ifdef USE_LED_DEBUG
	#define LED_DEBUG_PORT				GPIOA
	#define LED_DEBUG_BIT				LL_GPIO_PIN_11
	#define LED_DEBUG_WRITE				GPIO_SET_WRITE(LED_DEBUG_PORT,LED_DEBUG_BIT)
	#define LED_DEBUG_READ				GPIO_SET_READ(LED_DEBUG_PORT,LED_DEBUG_BIT)
	#define LED_DEBUG_OUT_0				GPIO_OUT_0(LED_DEBUG_PORT,LED_DEBUG_BIT)
	#define LED_DEBUG_OUT_1				GPIO_OUT_1(LED_DEBUG_PORT,LED_DEBUG_BIT)
	#define LED_DEBUG_OUT_C				GPIO_OUT_C(LED_DEBUG_PORT,LED_DEBUG_BIT)
	#endif

	//---重新交换了一下D通道解码成功的端口
	#define LED_WORK_PORT				GPIOB
	#define LED_WORK_BIT				LL_GPIO_PIN_10
	#define LED_WORK_WRITE				GPIO_SET_WRITE(LED_WORK_PORT,LED_WORK_BIT)
	#define LED_WORK_READ				GPIO_SET_READ(LED_WORK_PORT,LED_WORK_BIT)
	#define LED_WORK_OUT_0				GPIO_OUT_0(LED_WORK_PORT,LED_WORK_BIT)
	#define LED_WORK_OUT_1				GPIO_OUT_1(LED_WORK_PORT,LED_WORK_BIT)
	#define LED_WORK_OUT_C				GPIO_OUT_C(LED_WORK_PORT,LED_WORK_BIT)

	//===函数定义
	void LEDWork_Init(void);
	void LEDWork_Task(void);
	#ifdef USE_LED_DEBUG
	void LEDDebug_Init(void);
	#endif
	void LED_Init(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*LED_CFG_H_ */
