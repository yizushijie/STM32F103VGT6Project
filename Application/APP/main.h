#ifndef MAIN_H_
#define MAIN_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===使用的头文件
	#include "config.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===函数定义
	void SystemClock_Config(void);
	void NVIC_Init(void);
	void Sys_Init(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*MAIN_H_ */