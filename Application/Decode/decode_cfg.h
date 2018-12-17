#ifndef DECODE_CFG_H_
#define DECODE_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "timer_task.h"
	#include "delay_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===解码使用的定时器
	#define DEC_USE_TIM									TIM2

	//===解码定时器中断
	#define DEC_USE_TIM_IRQ								TIM2_IRQn

	//===A通道解码
	#define DECA_CH_PORT								GPIOA
	#define DECA_CH_BIT									LL_GPIO_PIN_0
	#define DECA_CH_STATE								GPIO_GET_STATE(DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_WRITE								GPIO_SET_WRITE(DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_READ								GPIO_SET_READ( DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_OUT_0								GPIO_OUT_0(    DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_OUT_1								GPIO_OUT_1(    DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_OUT_C								GPIO_OUT_C(    DECA_CH_PORT,DECA_CH_BIT)

	//===B通道解码
	#define DECB_CH_PORT								GPIOA
	#define DECB_CH_BIT									LL_GPIO_PIN_1
	#define DECB_CH_STATE								GPIO_GET_STATE(DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_WRITE								GPIO_SET_WRITE(DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_READ								GPIO_SET_READ( DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_OUT_0								GPIO_OUT_0(    DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_OUT_1								GPIO_OUT_1(    DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_OUT_C								GPIO_OUT_C(    DECB_CH_PORT,DECB_CH_BIT)

	//===C通道解码
	#define DECC_CH_PORT								GPIOA
	#define DECC_CH_BIT									LL_GPIO_PIN_2
	#define DECC_CH_STATE								GPIO_GET_STATE(DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_WRITE								GPIO_SET_WRITE(DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_READ								GPIO_SET_READ( DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_OUT_0								GPIO_OUT_0(    DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_OUT_1								GPIO_OUT_1(    DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_OUT_C								GPIO_OUT_C(    DECC_CH_PORT,DECC_CH_BIT)

	//===D通道解码
	#define DECD_CH_PORT								GPIOA
	#define DECD_CH_BIT									LL_GPIO_PIN_3
	#define DECD_CH_STATE								GPIO_GET_STATE(DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_WRITE								GPIO_SET_WRITE(DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_READ								GPIO_SET_READ( DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_OUT_0								GPIO_OUT_0(    DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_OUT_1								GPIO_OUT_1(    DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_OUT_C								GPIO_OUT_C(    DECD_CH_PORT,DECD_CH_BIT)

	//===A通道解码实时灯
	#define DECA_LED_PORT								GPIOB
	#define DECA_LED_BIT								LL_GPIO_PIN_12
	#define DECA_LED_STATE								GPIO_GET_STATE(DECA_LED_PORT,DECA_LED_BIT)
	#define DECA_LED_WRITE								GPIO_SET_WRITE(DECA_LED_PORT,DECA_LED_BIT)
	#define DECA_LED_READ								GPIO_SET_READ( DECA_LED_PORT,DECA_LED_BIT)
	#define DECA_LED_OUT_0								GPIO_OUT_0(    DECA_LED_PORT,DECA_LED_BIT)
	#define DECA_LED_OUT_1								GPIO_OUT_1(    DECA_LED_PORT,DECA_LED_BIT)
	#define DECA_LED_OUT_C								GPIO_OUT_C(    DECA_LED_PORT,DECA_LED_BIT)
	#define DECA_LED_IS_ON								DECA_LED_OUT_1
	#define DECA_LED_IS_OFF								DECA_LED_OUT_0

	//===B通道解码实时灯
	#define DECB_LED_PORT								GPIOB
	#define DECB_LED_BIT								LL_GPIO_PIN_13
	#define DECB_LED_STATE								GPIO_GET_STATE(DECB_LED_PORT,DECB_LED_BIT)
	#define DECB_LED_WRITE								GPIO_SET_WRITE(DECB_LED_PORT,DECB_LED_BIT)
	#define DECB_LED_READ								GPIO_SET_READ( DECB_LED_PORT,DECB_LED_BIT)
	#define DECB_LED_OUT_0								GPIO_OUT_0(    DECB_LED_PORT,DECB_LED_BIT)
	#define DECB_LED_OUT_1								GPIO_OUT_1(    DECB_LED_PORT,DECB_LED_BIT)
	#define DECB_LED_OUT_C								GPIO_OUT_C(    DECB_LED_PORT,DECB_LED_BIT)
	#define DECB_LED_IS_ON								DECB_LED_OUT_1
	#define DECB_LED_IS_OFF								DECB_LED_OUT_0

	//===C通道解码实时灯
	#define DECC_LED_PORT								GPIOB
	#define DECC_LED_BIT								LL_GPIO_PIN_14
	#define DECC_LED_STATE								GPIO_GET_STATE(DECC_LED_PORT,DECC_LED_BIT)
	#define DECC_LED_WRITE								GPIO_SET_WRITE(DECC_LED_PORT,DECC_LED_BIT)
	#define DECC_LED_READ								GPIO_SET_READ( DECC_LED_PORT,DECC_LED_BIT)
	#define DECC_LED_OUT_0								GPIO_OUT_0(    DECC_LED_PORT,DECC_LED_BIT)
	#define DECC_LED_OUT_1								GPIO_OUT_1(    DECC_LED_PORT,DECC_LED_BIT)
	#define DECC_LED_OUT_C								GPIO_OUT_C(    DECC_LED_PORT,DECC_LED_BIT)
	#define DECC_LED_IS_ON								DECC_LED_OUT_1
	#define DECC_LED_IS_OFF								DECC_LED_OUT_0

	//===D通道解码实时灯
	#define DECD_LED_PORT								GPIOB
	#define DECD_LED_BIT								LL_GPIO_PIN_11
	#define DECD_LED_STATE								GPIO_GET_STATE(DECD_LED_PORT,DECD_LED_BIT)
	#define DECD_LED_WRITE								GPIO_SET_WRITE(DECD_LED_PORT,DECD_LED_BIT)
	#define DECD_LED_READ								GPIO_SET_READ( DECD_LED_PORT,DECD_LED_BIT)
	#define DECD_LED_OUT_0								GPIO_OUT_0(    DECD_LED_PORT,DECD_LED_BIT)
	#define DECD_LED_OUT_1								GPIO_OUT_1(    DECD_LED_PORT,DECD_LED_BIT)
	#define DECD_LED_OUT_C								GPIO_OUT_C(    DECD_LED_PORT,DECD_LED_BIT)
	#define DECD_LED_IS_ON								DECD_LED_OUT_1
	#define DECD_LED_IS_OFF								DECD_LED_OUT_0

	//===关闭实时解码灯
	#define DEC_LED_OFF									( DECA_LED_OUT_0,DECB_LED_OUT_0,DECC_LED_OUT_0,DECD_LED_OUT_0 )

	//===A通道解码RST复位标志
	#define DECA_RST_PORT								GPIOE
	#define DECA_RST_BIT								LL_GPIO_PIN_14
	#define DECA_RST_STATE								GPIO_GET_STATE(DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_WRITE								GPIO_SET_WRITE(DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_READ								GPIO_SET_READ( DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_OUT_0								GPIO_OUT_0(    DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_OUT_1								GPIO_OUT_1(    DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_OUT_C								GPIO_OUT_C(    DECA_RST_PORT,DECA_RST_BIT)

	//===B通道解码RST复位标志
	#define DECB_RST_PORT								GPIOE
	#define DECB_RST_BIT								LL_GPIO_PIN_5
	#define DECB_RST_STATE								GPIO_GET_STATE(DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_WRITE								GPIO_SET_WRITE(DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_READ								GPIO_SET_READ( DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_OUT_0								GPIO_OUT_0(    DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_OUT_1								GPIO_OUT_1(    DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_OUT_C								GPIO_OUT_C(    DECB_RST_PORT,DECB_RST_BIT)

	//===C通道解码RST复位标志
	#define DECC_RST_PORT								GPIOD
	#define DECC_RST_BIT								LL_GPIO_PIN_0
	#define DECC_RST_STATE								GPIO_GET_STATE(DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_WRITE								GPIO_SET_WRITE(DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_READ								GPIO_SET_READ( DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_OUT_0								GPIO_OUT_0(    DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_OUT_1								GPIO_OUT_1(    DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_OUT_C								GPIO_OUT_C(    DECC_RST_PORT,DECC_RST_BIT)

	//===D通道解码RST复位标志
	#define DECD_RST_PORT								GPIOD
	#define DECD_RST_BIT								LL_GPIO_PIN_8
	#define DECD_RST_STATE								GPIO_GET_STATE(DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_WRITE								GPIO_SET_WRITE(DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_READ								GPIO_SET_READ( DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_OUT_0								GPIO_OUT_0(    DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_OUT_1								GPIO_OUT_1(    DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_OUT_C								GPIO_OUT_C(    DECD_RST_PORT,DECD_RST_BIT)

	//===解码SITE数
	#define DECODE_SITE_COUNT							4

	//===占空比解码的脉宽占空比1:1=50;1:3==25;3:7=30
	#define DECODE_PULSE_WIDTH_RATE						40

	//===解码的最小脉冲宽度
	#define DECODE_PULSE_WIDTH							500

	//---脉宽最小值
	#define DECODE_PULSE_WIDTH_MAX						( DECODE_PULSE_WIDTH*2*( 100-DECODE_PULSE_WIDTH_RATE )/100 )

	//---脉宽最大值
	#define DECODE_PULSE_WIDTH_MIN						( DECODE_PULSE_WIDTH*2*( DECODE_PULSE_WIDTH_RATE )/100 )

	//===帧停顿占空比值
	#define	DECODE_FRAME_STOP_SCALE						31

	//===定时器重新装载值
	#define	DECODE_TIM_RELOAD							(UINT32_T)50000

	//===解码采样时钟为72MHz, 采样周期1us; 计数器的最大值为50000，时间1us，最大记录同电平保持时间为50ms
	#define DECODE_TIM_ARR								(SYS_CLOCK_MHZ-1)

	//===定时器超时是按
	#define DECODE_TIM_OUT								48000

	//===解码缓存区大小
	#define DECODE_REC_BUFF_SIZE						128

	//===解码BIT位的个数
	#define DECODE_BIT_COUNT							24

	//===定义连续方波的脉冲个数
	#define	DECODE_CONTINUE_SQUARE_PASS_COUNT			80

	//===检查数据的合理性
	#if(DECODE_BIT_COUNT > 24)
	#undef	DECODE_BIT_COUNT
	#define	DECODE_BIT_COUNT							24
	#warning "DECODE_BIT_COUNT不能大于24"
		#endif

		//===解码步序
		#define DECODE_STEP_0								0
		#define DECODE_STEP_1								(DECODE_STEP_0 + 1)
		#define DECODE_STEP_2								(DECODE_STEP_1 + 1)
		#define DECODE_STEP_3								(DECODE_STEP_2 + 1)
		#define DECODE_STEP_4								(DECODE_STEP_3 + 1)
		#define DECODE_STEP_5								(DECODE_STEP_4 + 1)
		#define DECODE_STEP_6								(DECODE_STEP_5 + 1)

		//===函数定义
		void Decode_Init(void);
	void Decode_START(void);
	void Decode_STOP(void);
	void  Decode_ActivateSites(UINT8_T activateSites);
	UINT8_T Decode_ScanRST(void);
	void Decode_IRQTask(void);
	void Decode_Quency(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DECODE_CFG_H_ */