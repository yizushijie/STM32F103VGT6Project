#include "timer_cfg.h"

//===ȫ�ֱ�������
CALCFREQ_HandlerType  g_CalcFreq;
pCALCFREQ_HandlerType pCalcFreq = &g_CalcFreq;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �ⲿ����ģʽ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreqMode_Init(void)
{
	LL_TIM_InitTypeDef TIM_InitStruct = { 0 };
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---ʹ�ܶ�ʱ��ʱ��
	Timer_Clock(TIM3, 1);

	//---ʹ�ܶ˿�ʱ��
	GPIO_Clock(GPIOB, 1);

	//---GPIO��ʼ��---PA1ӳ��ΪTim5_CH2
	GPIO_InitStruct.Pin = LL_GPIO_PIN_5 | LL_GPIO_PIN_4;
	#ifdef USE_MCU_STM32F1
	LL_GPIO_AF_RemapPartial_TIM3();

	//GPIO_InitStruct.Mode		= LL_GPIO_MODE_FLOATING;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	#else
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
	#endif
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	//---��������ʱ�ӵ�Ԥ��Ƶ
	TIM_InitStruct.Prescaler = 0;

	//---���ϼ���
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;

	//---�Զ�װ��ֵ���Զ�װ��ֵΪ��ʱ��������������
	TIM_InitStruct.Autoreload = 0xFFFFFFFF;

	//---��ʱ��ʱ�ӷ�Ƶ��
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;

	//---��ʼ����ʱ��
	LL_TIM_Init(TIM3, &TIM_InitStruct);

	//---�����Զ�װ��
	LL_TIM_EnableARRPreload(TIM3);

	//---���ô�������ͨ��
	LL_TIM_SetTriggerInput(TIM3, LL_TIM_TS_TI2FP2);

	//---��������ͨ��
	LL_TIM_IC_SetActiveInput(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_ACTIVEINPUT_DIRECTTI);

	//---�����ʺ�ʱ��Դ
	LL_TIM_SetClockSource(TIM3, LL_TIM_CLOCKSOURCE_EXT_MODE1);

	//---���ò���/�Ƚ�ͨ��
	LL_TIM_CC_DisableChannel(TIM3, LL_TIM_CHANNEL_CH2);

	//---����ͨ�����˲�ʱ��
	LL_TIM_IC_SetFilter(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_IC_FILTER_FDIV1);

	//---ͨ��2�������ش���
	LL_TIM_IC_SetPolarity(TIM3, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);

	//---���ô����жϣ�TIE��
	LL_TIM_DisableIT_TRIG(TIM3);

	//---����DMA�����жϣ�TIE��
	LL_TIM_DisableDMAReq_TRIG(TIM3);

	//---
	LL_TIM_SetTriggerOutput(TIM3, LL_TIM_TRGO_RESET);

	//---��ʹ������ģʽ
	LL_TIM_DisableMasterSlaveMode(TIM3);

	//---ʹ�ܼ�����
	//LL_TIM_EnableCounter(TIM5);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreqMode_DeInit(void)
{
	LL_TIM_DeInit(TIM3);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreq_Init(void)
{
	if (pCalcFreq->msgStep == 0)
	{
		pCalcFreq->msgFreqKHz = 0;
		pCalcFreq->msgFreqMHz = 0;
		pCalcFreq->msgStep = 1;

		//---ʹ�ܼ�����
		LL_TIM_EnableCounter(TIM3);
	}
	else if (pCalcFreq->msgStep == 1)
	{
		//---���������
		LL_TIM_SetCounter(TIM3, 0);
		pCalcFreq->msgStep = 2;
	}
	else if (pCalcFreq->msgStep == 2)
	{
		//---��ʹ�ܼ�����
		LL_TIM_DisableCounter(TIM3);

		//---��ȡ��ǰ�ļ������
		pCalcFreq->msgFreqKHz = LL_TIM_GetCounter(TIM3);
		pCalcFreq->msgStep = 3;
	}
	else
	{
		return;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����Ƶ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_CalcFreq_Task(void)
{
	//---���浱ǰ�δ�ʱ��������
	pCalcFreq->msgFuncTask = pSysTick->msgFuncTick;

	//---����ע�ᵱǰ�δ�ʱ�������񣬻�ȡ�����źŵ�Ƶ��---1ms�ɼ��������صĸ�ʽ������ɼ���1������1KHz���ݲ�֧��1KHzһ�µ��ź�
	SysTickTask_FuncTick(Timer_CalcFreq_Init);

	//---�ȴ��������������
	while (pCalcFreq->msgStep != 3);

	//---�ָ��δ�ʱ��������
	SysTickTask_FuncTick(pCalcFreq->msgFuncTask);

	//---ע��������
	pCalcFreq->msgFuncTask = NULL;

	//---��������
	pCalcFreq->msgStep = 0;
	pCalcFreq->msgFreqMHz = (UINT16_T)(pCalcFreq->msgFreqKHz / 1000);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT32_T Timer_GetFreqKHz(void)
{
	return pCalcFreq->msgFreqKHz;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T Timer_GetFreqMHz(void)
{
	return pCalcFreq->msgFreqMHz;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_Init(void)
{
	Timer_CalcFreqMode_Init();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Timer_Clock(TIM_TypeDef *TIMx, UINT8_T isEnable)
{
	#ifdef TIM1
	if (TIMx == TIM1)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
		}
		return;
	}
	#endif
	#ifdef TIM2
	if (TIMx == TIM2)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
		}
		else
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM2);
		}
		return;
	}
	#endif
	#ifdef TIM3
	if (TIMx == TIM3)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
		}
		return;
	}
	#endif
	#ifdef TIM4
	if (TIMx == TIM4)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
		}
		return;
	}
	#endif
	#ifdef TIM5
	if (TIMx == TIM5)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM5);
		}
		return;
	}
	#endif
	#ifdef TIM6
	if (TIMx == TIM6)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM6);
		}
		return;
	}
	#endif
	#ifdef TIM7
	if (TIMx == TIM7)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
		}
		else
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM7);
		}
		return;
	}
	#endif
	#ifdef TIM8
	if (TIMx == TIM8)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM8);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM8);
		}
		return;
	}
	#endif
	#ifdef TIM9
	if (TIMx == TIM9)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM9);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM9);
		}
		return;
	}
	#endif
	#ifdef TIM10
	if (TIMx == TIM10)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM10);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM10);
		}
		return;
	}
	#endif
	#ifdef TIM11
	if (TIMx == TIM11)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM11);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM11);
		}
		return;
	}
	#endif
	#ifdef TIM12
	if (TIMx == TIM12)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM12);
		}
		else
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM12);
		}
		return;
	}
	#endif
	#ifdef TIM13
	if (TIMx == TIM13)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM13);
		}
		else
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM13);
		}
		return;
	}
	#endif

	#ifdef TIM14
	if (TIMx == TIM14)
	{
		if (isEnable)
		{
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM14);
		}
		else
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_TIM14);
		}
		return;
	}
	#endif
	#ifdef TIM15
	if (TIMx == TIM15)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM15);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM15);
		}
		return;
	}
	#endif
	#ifdef TIM16
	if (TIMx == TIM16)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM16);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM16);
		}
		return;
	}
	#endif
	#ifdef TIM17
	if (TIMx == TIM17)
	{
		if (isEnable)
		{
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM17);
		}
		else
		{
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_TIM17);
		}
		return;
	}
	#endif
}