#include "systick_cfg.h"

//---��������
SysTick_HandlerType		g_SysTick;
pSysTick_HandlerType	pSysTick = &g_SysTick;

#if defined (USE_HAL_DRIVER)

//---�ⲿ���õ�Hal����ʱ����
extern HAL_TickFreqTypeDef uwTickFreq;
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Suspend(void)
{
	//---��ʹ��ϵͳ�δ�ʱ�����ж�
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Resume(void)
{
	//---ʹ��ϵͳ�δ�ʱ�����ж�
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� SysTickʹ�õĽṹ��ĳ�ʼ��
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���1ms�ĵδ�ʱ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_Init(void)
{
	//---��ʼ���ṹ��
	SysTick_StructInit(pSysTick);

	//---���ܳ�ʼ��
//---����δ�ʱ��
	SysTick_Suspend();

	//---����1ms��ʱ��δ���---�ó�ʼ������û��ע���ж�
	LL_InitTick(SystemCoreClock, 1000);

	//---�����ж���ռ����
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//---���õδ�ʱ���ж�---����Ϊ������ȼ�
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));

	//---ʹ�ܵδ�ʱ���ж�---Ĭ����1ms
	SysTick_Resume();
	#ifdef USE_HAL_DRIVER

	//---Hal��������ʱ����
	uwTickFreq = HAL_TICK_FREQ_DEFAULT;

	//---ע��Hal�������
	pSysTick->msgHalIncTick = HAL_IncTick;
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_DeInit(void)
{
	SysTick_Suspend();
	SysTick_StructInit(pSysTick);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_FuncTick(void(*pFuncTick)(void))
{
	if (pFuncTick != NULL)
	{
		//---ע��������
		pSysTick->msgFuncTick = pFuncTick;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ��ȴ���ʱ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_IRQDecTick(UINT32_T waitDecTick)
{
	//---�жϵ�ǰ��ֵ
	UINT32_T load = SysTick->LOAD + 1;
	UINT32_T val = SysTick->VAL;
	load >>= 1;

	//---����������ʱ
	if (val < load)
	{
		waitDecTick += 1;
	}

	//---��ʱ����
	pSysTick->msgDec = waitDecTick;

	//---�ȴ�ʱ�䵽��
	while (pSysTick->msgDec != 0)
	{
		WDT_RESET();
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTick_GetTick(void)
{
	return pSysTick->msgInc;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_IRQTick(void)
{
	//---�ݼӼ���
	pSysTick->msgInc++;

	//---�ж��Ƿ����
	if (pSysTick->msgInc == 0)
	{
		pSysTick->msgOVF++;
	}

	//---hal��ʱ����
	if (pSysTick->msgHalIncTick != NULL)
	{
		pSysTick->msgHalIncTick();
	}

	//---������
	if (pSysTick->msgFuncTick != NULL)
	{
		pSysTick->msgFuncTick();
	}

	//---�ݼ�����
	if (pSysTick->msgDec != 0)
	{
		pSysTick->msgDec--;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_WaitTick(UINT32_T usTimer)
{
	UINT32_T load = SysTick->LOAD;
	UINT32_T ctrl = SysTick->CTRL;
	UINT32_T val = SysTick->VAL;

	//---�رն�ʱ����ʱ��ѡ��Ϊϵͳʱ�ӣ�������8��Ƶ
	SysTick->CTRL = 0x00000004;

	//---����װ��ֵ
	SysTick->LOAD = usTimer * SYS_CLOCK_MHZ - SYS_CLOCK_ADD;//150;//usTimer*SYS_CLOCK_MHZ - 1;

	//---���������
	SysTick->VAL = 0x00;

	//---ʹ�ܼ���������
	SysTick->CTRL |= 0x01;

	//---�ȴ�������0
	while (!(SysTick->CTRL & 0x00010000))
	{
		WDT_RESET();
	}

	//---�رն�ʱ����ʱ��ѡ��Ϊϵͳʱ�ӣ�������8��Ƶ
	SysTick->CTRL = 0x00000004;

	//---�ָ�װ��ֵ
	SysTick->LOAD = load;

	//---��������������
	SysTick->VAL = val;

	//---�ָ�����������
	SysTick->CTRL = ctrl;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����ж�ϵͳ�δ�ʱ���ǲ���1ms�Ķ�ʱ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SysTick_1msIncTick(void)
{
	//---�ж�ʱ��Դ�Ƿ����8��Ƶ
	if ((SysTick->CTRL&SysTick_CTRL_CLKSOURCE_Msk) != 0)
	{
		//===ʱ��Դû�н���8��Ƶ
		if (SysTick->LOAD != (SYS_CLOCK_KHZ - 1))
		{
			return ERROR_1;
		}
	}
	else
	{
		//===ʱ��Դ����8��Ƶ
		if (SysTick->LOAD != ((SYS_CLOCK_KHZ >> 3) - 1))
		{
			return ERROR_1;
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡ��������Ĵ�С
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T SysTick_GetTickOVF(void)
{
	return pSysTick->msgOVF;
}