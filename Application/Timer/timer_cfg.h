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

		//===结构体定义
	typedef struct _CALCFREQ_HandlerType				CALCFREQ_HandlerType;

	//===指针结构体定义
	typedef struct _CALCFREQ_HandlerType				*pCALCFREQ_HandlerType;

	//===计算频率的数据结构体
	struct  _CALCFREQ_HandlerType
	{
		VLTUINT8_T  msgStep;			//---操作步序
		VLTUINT16_T	msgFreqMHz;			//---MHz频率
		VLTUINT32_T msgFreqKHz;			//---KHz频率
		void(*msgFuncTask)(void);		//---操作任务
	};

	//===外部调用接口
	extern CALCFREQ_HandlerType g_CalcFreq;
	extern pCALCFREQ_HandlerType pCalcFreq;

	//===函数定义
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
