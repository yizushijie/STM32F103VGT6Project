#ifndef TIMER_TASK_H_
#define TIMER_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "timer_lib.h"

	//===��������
	void TimerTask_Init(void);
	void TimerTask_CalcFreq_Task(void);
	UINT32_T TimerTask_GetFreqKHz(void);
	UINT16_T TimerTask_GetFreqMHz(void);
	void TimerTask_Clock(TIM_TypeDef *TIMx, UINT8_T isEnable);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*TIMER_TASK_H_ */