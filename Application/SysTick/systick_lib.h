#ifndef SYSTICK_LIB_H_
#define SYSTICK_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
//===使用包含的头文件
	#include "systick_cfg.h"

	//---函数定义
	UINT8_T	 SysTickLib_Init(void);
	UINT8_T	 SysTickLib_DeInit(void);
	UINT8_T	 SysTickLib_FuncTick(void(*pFuncTick)(void));
	UINT8_T  SysTickLib_IRQDecTick(UINT32_T waitDecTick);
	UINT32_T SysTickLib_GetTick(void);
	UINT8_T	 SysTickLib_IRQTick(void);
	UINT8_T	 SysTickLib_WaitTick(UINT32_T usTimer);
	UINT8_T  SysTickLib_1msIncTick(void);
	UINT32_T SysTickLib_GetTickOVF(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* SYSTICK_LIB_H_ */