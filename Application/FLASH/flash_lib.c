#include "flash_lib.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void FLASHLib_ReadHalfWord(UINT32_T readAddr, UINT16_T *pVal, UINT16_T length)
{
	FLASH_ReadHalfWord(readAddr, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void FLASHLib_WriteHalfWord(UINT32_T writeAddr, UINT16_T *pVal, UINT16_T length)
{
	FLASH_WriteHalfWord(writeAddr, pVal, length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void FLASHLib_WriteHalfWordWithErase(UINT32_T writeAddr, UINT16_T *pVal, UINT16_T length)
{
	FLASH_WriteHalfWordWithErase(writeAddr, pVal, length);
}