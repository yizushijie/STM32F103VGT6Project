#ifndef SYSTICK_TASK_H_
#define SYSTICK_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
//---ͷ�ļ�����
	#include "systick_lib.h"

	//---��������
	UINT8_T	 SysTickTask_Init(void);
	UINT8_T	 SysTickTask_DeInit(void);
	UINT8_T	 SysTickTask_FuncTick(void(*pFuncTick)(void));
	UINT8_T  SysTickTask_IRQDecTick(UINT32_T waitDecTick);
	UINT32_T SysTickTask_GetTick(void);
	UINT8_T	 SysTickTask_IRQTick(void);
	UINT8_T	 SysTickTask_WaitTick(UINT32_T usTimer);
	UINT8_T  SysTickTask_1msIncTick(void);
	UINT32_T SysTickTask_GetTickOVF(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SYSTICK_TASK_H_ */
