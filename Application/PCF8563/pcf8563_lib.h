#ifndef PCF8563_LIB_H_
#define PCF8563_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
//===使用包含的头文件
	#include "pcf8563_cfg.h"

	//---函数定义
	UINT8_T PCF8563Lib_I2C_Init(PCF8563_HandlerType *PCF8563x, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T PCF8563Lib_I2C_DeInit(PCF8563_HandlerType *PCF8563x);
	UINT8_T PCF8563Lib_I2C_ClockOut(PCF8563_HandlerType *PCF8563x, UINT8_T preVal);
	UINT8_T PCF8563Lib_I2C_ReadRTC(PCF8563_HandlerType *PCF8563x);
	UINT8_T PCF8563Lib_I2C_WriteRTC(PCF8563_HandlerType *PCF8563x, RTC_HandlerType rtc);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* PCF8563_LIB_H_ */