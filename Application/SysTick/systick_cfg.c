#include "systick_cfg.h"

//---变量定义
SysTick_HandlerType		g_SysTick;
pSysTick_HandlerType	pSysTick = &g_SysTick;

#if defined (USE_HAL_DRIVER)

//---外部调用的Hal库延时变量
extern HAL_TickFreqTypeDef uwTickFreq;
#endif

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Suspend(void)
{
	//---不使能系统滴答定时器的中断
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Resume(void)
{
	//---使能系统滴答定时器的中断
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： SysTick使用的结构体的初始化
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_StructInit(SysTick_HandlerType *sysTickx)
{
	sysTickx->msgInc = 0;
	sysTickx->msgDec = 0;
	sysTickx->msgOVF = 0;
	sysTickx->msgHalIncTick = NULL;
	sysTickx->msgFuncTick = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 最好1ms的滴答定时器
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Init(void)
{
	//---初始化结构体
	SysTick_StructInit(pSysTick);

	//---功能初始化
//---挂起滴答定时器
	SysTick_Suspend();

	//---产生1ms的时间滴答器---该初始化函数没有注册中断
	LL_InitTick(SystemCoreClock, 1000);

	//---设置中断抢占分组
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//---配置滴答定时器中断---设置为最低优先级
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));

	//---使能滴答定时的中断---默认是1ms
	SysTick_Resume();
	#ifdef USE_HAL_DRIVER

	//---Hal库用于延时计算
	uwTickFreq = HAL_TICK_FREQ_DEFAULT;

	//---注册Hal库计数器
	pSysTick->msgHalIncTick = HAL_IncTick;
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_DeInit(void)
{
	SysTick_Suspend();
	SysTick_StructInit(pSysTick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_FuncTick(void(*pFuncTick)(void))
{
	if (pFuncTick != NULL)
	{
		//---注册任务函数
		pSysTick->msgFuncTick = pFuncTick;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：等待延时到达
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_IRQDecTick(UINT32_T waitDecTick)
{
	//---判断当前的值
	UINT32_T load = SysTick->LOAD + 1;
	UINT32_T val = SysTick->VAL;
	load >>= 1;

	//---修正补偿延时
	if (val < load)
	{
		waitDecTick += 1;
	}

	//---计时函数
	pSysTick->msgDec = waitDecTick;

	//---等待时间到达
	while (pSysTick->msgDec != 0)
	{
		WDT_RESET();
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTick_GetTick(void)
{
	return pSysTick->msgInc;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_IRQTick(void)
{
	//---递加计数
	pSysTick->msgInc++;

	//---判断是否溢出
	if (pSysTick->msgInc == 0)
	{
		pSysTick->msgOVF++;
	}

	//---hal延时函数
	if (pSysTick->msgHalIncTick != NULL)
	{
		pSysTick->msgHalIncTick();
	}

	//---任务函数
	if (pSysTick->msgFuncTick != NULL)
	{
		pSysTick->msgFuncTick();
	}

	//---递减计数
	if (pSysTick->msgDec != 0)
	{
		pSysTick->msgDec--;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_WaitTick(UINT32_T usTimer)
{
	UINT32_T load = SysTick->LOAD;
	UINT32_T ctrl = SysTick->CTRL;
	UINT32_T val = SysTick->VAL;

	//---关闭定时器，时钟选择为系统时钟，不进行8分频
	SysTick->CTRL = 0x00000004;

	//---计算装载值
	SysTick->LOAD = usTimer * SYS_CLOCK_MHZ - SYS_CLOCK_ADD;//150;//usTimer*SYS_CLOCK_MHZ - 1;

	//---清零计数器
	SysTick->VAL = 0x00;

	//---使能计数器计数
	SysTick->CTRL |= 0x01;

	//---等待计数到0
	while (!(SysTick->CTRL & 0x00010000))
	{
		WDT_RESET();
	}

	//---关闭定时器，时钟选择为系统时钟，不进行8分频
	SysTick->CTRL = 0x00000004;

	//---恢复装载值
	SysTick->LOAD = load;

	//---计数器继续计数
	SysTick->VAL = val;

	//---恢复计数器配置
	SysTick->CTRL = ctrl;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：判断系统滴答定时器是不是1ms的定时
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_1msIncTick(void)
{
	//---判断时钟源是否进行8分频
	if ((SysTick->CTRL&SysTick_CTRL_CLKSOURCE_Msk) != 0)
	{
		//===时钟源没有进行8分频
		if (SysTick->LOAD != (SYS_CLOCK_KHZ - 1))
		{
			return ERROR_1;
		}
	}
	else
	{
		//===时钟源进行8分频
		if (SysTick->LOAD != ((SYS_CLOCK_KHZ >> 3) - 1))
		{
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 获取溢出计数的大小
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTick_GetTickOVF(void)
{
	return pSysTick->msgOVF;
}