#ifndef AT24CXX_LIB_H_
#define AT24CXX_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "at24cxx_cfg.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===º¯Êý¶¨Òå
	UINT8_T AT24CXXLib_Init(AT24CXX_HandlerType *AT24CXXx, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T AT24CXXLib_DeInit(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXXLib_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val);
	UINT8_T AT24CXXLib_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXXLib_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal);
	UINT8_T AT24CXXLib_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* AT24CXX_LIB_H_ */