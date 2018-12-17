#include "wm8510_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510Lib_I2C_Init(WM8510_HandlerType *WM8510x, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C)
{
	return WM8510_I2C_Init(WM8510x, msgDelay, isHWI2C);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510Lib_I2C_DeInit(WM8510_HandlerType *WM8510x)
{
	return WM8510_I2C_DeInit(WM8510x);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510Lib_I2C_SetFreqHz(WM8510_HandlerType *WM8510x, UINT32_T freq)
{
	return WM8510_I2C_SetFreqHz(WM8510x, freq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510Lib_I2C_SetFreqKHz(WM8510_HandlerType *WM8510x, float freq)
{
	return WM8510_I2C_SetFreqKHz(WM8510x, freq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510Lib_I2C_SetFreqMHz(WM8510_HandlerType *WM8510x, float freq)
{
	return WM8510_I2C_SetFreqMHz(WM8510x, freq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void WM8510Lib_I2C_Reset(WM8510_HandlerType *WM8510x)
{
	WM8510_I2C_Reset(WM8510x);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510Lib_I2C_SetFreqHzWithAllFreqReg(WM8510_HandlerType *WM8510x, UINT32_T freq)
{
	return WM8510_I2C_SetFreqHzWithAllFreqReg(WM8510x, freq);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510Lib_CalibrateFreqKHzOutPut(WM8510_HandlerType *WM8510x)
{
	return WM8510_CalibrateFreqKHzOutPut(WM8510x);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T WM8510Lib_I2C_SetFreqHzWithAllFreqRegAndCalibrateFreqKHzOutPut(WM8510_HandlerType *WM8510x, UINT32_T freq)
{
	return WM8510_I2C_SetFreqHzWithAllFreqRegAndCalibrateFreqKHzOutPut(WM8510x, freq);
}