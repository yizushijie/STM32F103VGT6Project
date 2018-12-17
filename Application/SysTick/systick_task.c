#include "systick_task.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 SysTickTask_Init(void)
{
	return SysTickLib_Init();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 SysTickTask_DeInit(void)
{
	return SysTickLib_DeInit();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 SysTickTask_FuncTick(void(*pFuncTick)(void))
{
	return SysTickLib_FuncTick(pFuncTick);
}

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTickTask_IRQDecTick(UINT32_T waitDecTick)
{
	return SysTickLib_IRQDecTick(waitDecTick);
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTickTask_GetTick(void)
{
	return SysTickLib_GetTick();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 SysTickTask_IRQTick(void)
{
	return SysTickLib_IRQTick();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T	 SysTickTask_WaitTick(UINT32_T usTimer)
{
	return SysTickLib_WaitTick(usTimer);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T  SysTickTask_1msIncTick(void)
{
	return SysTickLib_1msIncTick();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTickTask_GetTickOVF(void)
{
	return SysTickLib_GetTickOVF();
}