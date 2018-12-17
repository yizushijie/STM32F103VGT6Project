#ifndef IWDG_TASK_H_
#define IWDG_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
//===定义使用的头文件
	#include "iwdg_lib.h"
		//////////////////////////////////////////////////////////////////////////////////////
	//---函数定义
	UINT8_T IWDGTask_Init(void);
	UINT8_T IWDGTask_DeInit(void);
	UINT8_T IWDGTask_Reset(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*IWDG_TASK_H_ */