#ifndef TIMER_CFG_H_
#define TIMER_CFG_H_
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

		//===�ṹ�嶨��
	typedef struct _CALCFREQ_HandlerType				CALCFREQ_HandlerType;

	//===ָ��ṹ�嶨��
	typedef struct _CALCFREQ_HandlerType				*pCALCFREQ_HandlerType;

	//===����Ƶ�ʵ����ݽṹ��
	struct  _CALCFREQ_HandlerType
	{
		VLTUINT8_T  msgStep;			//---��������
		VLTUINT16_T	msgFreqMHz;			//---MHzƵ��
		VLTUINT32_T msgFreqKHz;			//---KHzƵ��
		void(*msgFuncTask)(void);		//---��������
	};

	//===�ⲿ���ýӿ�
	extern CALCFREQ_HandlerType g_CalcFreq;
	extern pCALCFREQ_HandlerType pCalcFreq;

	//===��������
	void Timer_CalcFreq_Task(void);
	UINT32_T Timer_GetFreqKHz(void);
	UINT16_T Timer_GetFreqMHz(void);
	void Timer_Init(void);
	void Timer_Clock(TIM_TypeDef *TIMx, UINT8_T isEnable);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*TIMER_CFG_H_ */
