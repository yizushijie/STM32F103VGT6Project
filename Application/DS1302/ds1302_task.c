#include "ds1302_task.h"

UINT8_T DS1302Task_Init(DS1302_HandlerType *DS1302x, void(*msgDelay)(UINT32_T delay))
{
	return DS1302Lib_Init(DS1302x, msgDelay);
}

void DS1302Task_WriteReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat)
{
	DS1302Lib_WriteReg(DS1302x, addr, dat);
}
void DS1302Task_ReadReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal)
{
	DS1302Lib_ReadReg(DS1302x, addr, pVal);
}
void DS1302Task_WriteTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat)
{
	DS1302Lib_WriteTime(DS1302x, addr, dat);
}

void DS1302Task_ReadTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal)
{
	DS1302Lib_ReadTime(DS1302x, addr, pVal);
}
void DS1302Task_WriteRTC(DS1302_HandlerType *DS1302x, RTC_HandlerType rtcTime)
{
	DS1302Lib_WriteRTC(DS1302x, rtcTime);
}
void DS1302Task_ReadRTC(DS1302_HandlerType *DS1302x)
{
	DS1302Lib_ReadRTC(DS1302x);
}