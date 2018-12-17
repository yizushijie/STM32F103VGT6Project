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
	//===����ʹ�õĶ�ʱ��
	#define DEC_USE_TIM									TIM2

	//===���붨ʱ���ж�
	#define DEC_USE_TIM_IRQ								TIM2_IRQn

	//===Aͨ������
	#define DECA_CH_PORT								GPIOA
	#define DECA_CH_BIT									LL_GPIO_PIN_0
	#define DECA_CH_STATE								GPIO_GET_STATE(DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_WRITE								GPIO_SET_WRITE(DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_READ								GPIO_SET_READ( DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_OUT_0								GPIO_OUT_0(    DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_OUT_1								GPIO_OUT_1(    DECA_CH_PORT,DECA_CH_BIT)
	#define DECA_CH_OUT_C								GPIO_OUT_C(    DECA_CH_PORT,DECA_CH_BIT)

	//===Bͨ������
	#define DECB_CH_PORT								GPIOA
	#define DECB_CH_BIT									LL_GPIO_PIN_1
	#define DECB_CH_STATE								GPIO_GET_STATE(DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_WRITE								GPIO_SET_WRITE(DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_READ								GPIO_SET_READ( DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_OUT_0								GPIO_OUT_0(    DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_OUT_1								GPIO_OUT_1(    DECB_CH_PORT,DECB_CH_BIT)
	#define DECB_CH_OUT_C								GPIO_OUT_C(    DECB_CH_PORT,DECB_CH_BIT)

	//===Cͨ������
	#define DECC_CH_PORT								GPIOA
	#define DECC_CH_BIT									LL_GPIO_PIN_2
	#define DECC_CH_STATE								GPIO_GET_STATE(DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_WRITE								GPIO_SET_WRITE(DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_READ								GPIO_SET_READ( DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_OUT_0								GPIO_OUT_0(    DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_OUT_1								GPIO_OUT_1(    DECC_CH_PORT,DECC_CH_BIT)
	#define DECC_CH_OUT_C								GPIO_OUT_C(    DECC_CH_PORT,DECC_CH_BIT)

	//===Dͨ������
	#define DECD_CH_PORT								GPIOA
	#define DECD_CH_BIT									LL_GPIO_PIN_3
	#define DECD_CH_STATE								GPIO_GET_STATE(DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_WRITE								GPIO_SET_WRITE(DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_READ								GPIO_SET_READ( DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_OUT_0								GPIO_OUT_0(    DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_OUT_1								GPIO_OUT_1(    DECD_CH_PORT,DECD_CH_BIT)
	#define DECD_CH_OUT_C								GPIO_OUT_C(    DECD_CH_PORT,DECD_CH_BIT)

	//===Aͨ������ʵʱ��
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

	//===Bͨ������ʵʱ��
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

	//===Cͨ������ʵʱ��
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

	//===Dͨ������ʵʱ��
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

	//===�ر�ʵʱ�����
	#define DEC_LED_OFF									( DECA_LED_OUT_0,DECB_LED_OUT_0,DECC_LED_OUT_0,DECD_LED_OUT_0 )

	//===Aͨ������RST��λ��־
	#define DECA_RST_PORT								GPIOE
	#define DECA_RST_BIT								LL_GPIO_PIN_14
	#define DECA_RST_STATE								GPIO_GET_STATE(DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_WRITE								GPIO_SET_WRITE(DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_READ								GPIO_SET_READ( DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_OUT_0								GPIO_OUT_0(    DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_OUT_1								GPIO_OUT_1(    DECA_RST_PORT,DECA_RST_BIT)
	#define DECA_RST_OUT_C								GPIO_OUT_C(    DECA_RST_PORT,DECA_RST_BIT)

	//===Bͨ������RST��λ��־
	#define DECB_RST_PORT								GPIOE
	#define DECB_RST_BIT								LL_GPIO_PIN_5
	#define DECB_RST_STATE								GPIO_GET_STATE(DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_WRITE								GPIO_SET_WRITE(DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_READ								GPIO_SET_READ( DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_OUT_0								GPIO_OUT_0(    DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_OUT_1								GPIO_OUT_1(    DECB_RST_PORT,DECB_RST_BIT)
	#define DECB_RST_OUT_C								GPIO_OUT_C(    DECB_RST_PORT,DECB_RST_BIT)

	//===Cͨ������RST��λ��־
	#define DECC_RST_PORT								GPIOD
	#define DECC_RST_BIT								LL_GPIO_PIN_0
	#define DECC_RST_STATE								GPIO_GET_STATE(DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_WRITE								GPIO_SET_WRITE(DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_READ								GPIO_SET_READ( DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_OUT_0								GPIO_OUT_0(    DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_OUT_1								GPIO_OUT_1(    DECC_RST_PORT,DECC_RST_BIT)
	#define DECC_RST_OUT_C								GPIO_OUT_C(    DECC_RST_PORT,DECC_RST_BIT)

	//===Dͨ������RST��λ��־
	#define DECD_RST_PORT								GPIOD
	#define DECD_RST_BIT								LL_GPIO_PIN_8
	#define DECD_RST_STATE								GPIO_GET_STATE(DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_WRITE								GPIO_SET_WRITE(DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_READ								GPIO_SET_READ( DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_OUT_0								GPIO_OUT_0(    DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_OUT_1								GPIO_OUT_1(    DECD_RST_PORT,DECD_RST_BIT)
	#define DECD_RST_OUT_C								GPIO_OUT_C(    DECD_RST_PORT,DECD_RST_BIT)

	//===����SITE��
	#define DECODE_SITE_COUNT							4

	//===ռ�ձȽ��������ռ�ձ�1:1=50;1:3==25;3:7=30
	#define DECODE_PULSE_WIDTH_RATE						40

	//===�������С������
	#define DECODE_PULSE_WIDTH							500

	//---������Сֵ
	#define DECODE_PULSE_WIDTH_MAX						( DECODE_PULSE_WIDTH*2*( 100-DECODE_PULSE_WIDTH_RATE )/100 )

	//---�������ֵ
	#define DECODE_PULSE_WIDTH_MIN						( DECODE_PULSE_WIDTH*2*( DECODE_PULSE_WIDTH_RATE )/100 )

	//===֡ͣ��ռ�ձ�ֵ
	#define	DECODE_FRAME_STOP_SCALE						31

	//===��ʱ������װ��ֵ
	#define	DECODE_TIM_RELOAD							(UINT32_T)50000

	//===�������ʱ��Ϊ72MHz, ��������1us; �����������ֵΪ50000��ʱ��1us������¼ͬ��ƽ����ʱ��Ϊ50ms
	#define DECODE_TIM_ARR								(SYS_CLOCK_MHZ-1)

	//===��ʱ����ʱ�ǰ�
	#define DECODE_TIM_OUT								48000

	//===���뻺������С
	#define DECODE_REC_BUFF_SIZE						128

	//===����BITλ�ĸ���
	#define DECODE_BIT_COUNT							24

	//===���������������������
	#define	DECODE_CONTINUE_SQUARE_PASS_COUNT			80

	//===������ݵĺ�����
	#if(DECODE_BIT_COUNT > 24)
	#undef	DECODE_BIT_COUNT
	#define	DECODE_BIT_COUNT							24
	#warning "DECODE_BIT_COUNT���ܴ���24"
		#endif

		//===���벽��
		#define DECODE_STEP_0								0
		#define DECODE_STEP_1								(DECODE_STEP_0 + 1)
		#define DECODE_STEP_2								(DECODE_STEP_1 + 1)
		#define DECODE_STEP_3								(DECODE_STEP_2 + 1)
		#define DECODE_STEP_4								(DECODE_STEP_3 + 1)
		#define DECODE_STEP_5								(DECODE_STEP_4 + 1)
		#define DECODE_STEP_6								(DECODE_STEP_5 + 1)

		//===��������
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