#include "oled_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OLEDLib_I2C_Init(OLED_IIC_HandlerType *OLEDx, void(*msgDelay)( UINT32_T delay ), UINT8_T isHWI2C)
{
	return OLED_I2C_Init(OLEDx, msgDelay, isHWI2C);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OLEDLib_I2C_WriteCmd(OLED_IIC_HandlerType *OLEDx, UINT8_T cmd)
{
	return OLED_I2C_WriteCmd(OLEDx, cmd);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T OLEDLib_I2C_WriteData(OLED_IIC_HandlerType *OLEDx, UINT8_T cmd)
{
	return OLED_I2C_WriteData(OLEDx, cmd);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void OLEDLib_I2C_DisplayON(OLED_IIC_HandlerType *OLEDx)
{
	OLED_I2C_DisplayON(OLEDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void OLEDLib_I2C_DisplayOFF(OLED_IIC_HandlerType *OLEDx)
{
	OLED_I2C_DisplayOFF(OLEDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void OLEDLib_I2C_Fill(OLED_IIC_HandlerType *OLEDx, UINT8_T dat)
{
	OLED_I2C_Fill(OLEDx, dat);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void OLEDLib_I2C_Clear(OLED_IIC_HandlerType *OLEDx)
{
	OLED_I2C_Clear(OLEDx);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void OLEDLib_I2C_SetPos(OLED_IIC_HandlerType *OLEDx, UINT8_T xPos, UINT8_T yPos)
{
	OLED_I2C_SetPos(OLEDx, xPos, yPos);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void OLEDLib_I2C_DrawBMP(OLED_IIC_HandlerType *OLEDx, UINT8_T x0Pos, UINT8_T y0Pos, UINT8_T x1Pos, UINT8_T y1Pos, UINT8_T BMP[])
{
	OLED_I2C_DrawBMP(OLEDx, x0Pos, y0Pos, x1Pos, y1Pos,BMP);
}