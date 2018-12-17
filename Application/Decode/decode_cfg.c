#include "decode_cfg.h"

//===��¼�ߵ͵�ƽ����С����ֵ
VLTUINT32_T  decodeMinPulseCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===��¼�䲶׽�Ĵ����ļ���ֵ
VLTUINT32_T  decodeCaptureCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===��¼��ǰ�����ؼ���ֵ
VLTUINT32_T  decodeRisingPulseCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===��¼��ǰ�½��ؼ���ֵ
VLTUINT32_T  decodeFallingPulseCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===�������������
VLTUINT32_T  decodeOverFlowCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===���������������ֵ����ֵ
VLTUINT32_T  decodeOverFlowCountBKP[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===��¼��ǰ��ͨ����׽ģʽ  1--- �½��� 2---������
VLTUINT8_T   decodeIcpMode[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===���벽��
UINT8_T  decodeStep[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===����λ��
UINT16_T decodeBitIndex[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===����һ������Ŀ��
UINT32_T decodePulseWidth[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===��ʱ����ǰ�ļ���ֵ
UINT32_T decodeNowCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===�����SITE��
UINT8_T  decodeActivateSite[DECODE_SITE_COUNT] = { 0,0,0,0 };

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeLEDInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(DECA_LED_PORT, 1);
	GPIOTask_Clock(DECB_LED_PORT, 1);
	GPIOTask_Clock(DECC_LED_PORT, 1);
	GPIOTask_Clock(DECD_LED_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---DECA_SN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_LED_BIT;
	LL_GPIO_Init(DECA_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_LED_PORT, DECA_LED_BIT);

	//---DECB_SN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_LED_BIT;
	LL_GPIO_Init(DECB_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_LED_PORT, DECB_LED_BIT);

	//---DECC_SN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_LED_BIT;
	LL_GPIO_Init(DECC_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_LED_PORT, DECC_LED_BIT);

	//---DECD_SN_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_LED_BIT;
	LL_GPIO_Init(DECD_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_LED_PORT, DECD_LED_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeRSTInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(DECA_RST_PORT, 1);
	GPIOTask_Clock(DECB_RST_PORT, 1);
	GPIOTask_Clock(DECC_RST_PORT, 1);
	GPIOTask_Clock(DECD_RST_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---DECA_RST_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_RST_BIT;
	LL_GPIO_Init(DECA_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECA_RST_PORT, DECA_RST_BIT);

	//---DECB_RST_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_RST_BIT;
	LL_GPIO_Init(DECB_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECB_RST_PORT, DECB_RST_BIT);

	//---DECC_RST_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_RST_BIT;
	LL_GPIO_Init(DECC_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECC_RST_PORT, DECC_RST_BIT);

	//---DECD_RST_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_RST_BIT;
	LL_GPIO_Init(DECD_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECD_RST_PORT, DECD_RST_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeCHInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(DECA_CH_PORT, 1);
	GPIOTask_Clock(DECB_CH_PORT, 1);
	GPIOTask_Clock(DECC_CH_PORT, 1);
	GPIOTask_Clock(DECD_CH_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;			//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;						//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---DECA_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_CH_BIT;
	LL_GPIO_Init(DECA_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_CH_PORT, DECA_CH_BIT);

	//---DECB_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_CH_BIT;
	LL_GPIO_Init(DECB_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_CH_PORT, DECB_CH_BIT);

	//---DECC_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_CH_BIT;
	LL_GPIO_Init(DECC_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_CH_PORT, DECC_CH_BIT);

	//---DECD_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_CH_BIT;
	LL_GPIO_Init(DECD_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_CH_PORT, DECD_CH_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����������ʹ�õĶ�ʱ����ʼ��
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeTimerInit(void)
{
	//---ʹ�ܶ�ʱ��ʱ��
	TimerTask_Clock(DEC_USE_TIM, 1);

	//---��ʱ���Ľṹ��
	LL_TIM_InitTypeDef TIM_InitStruct = { 0 };

	//---���벶׽ͨ���ĳ�ʼ��
	LL_TIM_IC_InitTypeDef TIM_ICInitStruct = { 0 };

	//---���ö�ʱ��Ϊȱʡ����
	LL_TIM_DeInit(DEC_USE_TIM);

	//---�Զ�����ֵ
	TIM_InitStruct.Autoreload = DECODE_TIM_RELOAD;

	//---Ԥ��Ƶ��ֵ---�����������ʱ��Ƶ��---1MHz
	TIM_InitStruct.Prescaler = DECODE_TIM_ARR;//71
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;

	//---�ظ������Ĵ���
	TIM_InitStruct.RepetitionCounter = 0;

	//---��ʼ����ʱ��
	LL_TIM_Init(DEC_USE_TIM, &TIM_InitStruct);

	//---��ʹ���Զ�����
	LL_TIM_DisableARRPreload(DEC_USE_TIM);

	//--��ʱ��ʱ��ʹ���ڲ�ʱ��
	LL_TIM_SetClockSource(DEC_USE_TIM, LL_TIM_CLOCKSOURCE_INTERNAL);

	//---��ģʽѡ��λ
	LL_TIM_SetTriggerOutput(DEC_USE_TIM, LL_TIM_TRGO_RESET);

	//---��ʹ������ģʽ
	LL_TIM_DisableMasterSlaveMode(DEC_USE_TIM);

	//---ֱ��ģʽ
	TIM_ICInitStruct.ICActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;

	//---ʱ�Ӳ���Ƶ
	TIM_ICInitStruct.ICPrescaler = LL_TIM_ICPSC_DIV1;

	//---����ģʽ---�����ش���
	TIM_ICInitStruct.ICPolarity = LL_TIM_IC_POLARITY_RISING;

	//---�����˲�---8
	TIM_ICInitStruct.ICFilter = LL_TIM_IC_FILTER_FDIV8_N6;

	//---�������벶׽ͨ��1
	LL_TIM_IC_Init(DEC_USE_TIM, LL_TIM_CHANNEL_CH1, &TIM_ICInitStruct);

	//---�������벶׽ͨ��2
	LL_TIM_IC_Init(DEC_USE_TIM, LL_TIM_CHANNEL_CH2, &TIM_ICInitStruct);

	//---�������벶׽ͨ��3
	LL_TIM_IC_Init(DEC_USE_TIM, LL_TIM_CHANNEL_CH3, &TIM_ICInitStruct);

	//---�������벶׽ͨ��4
	LL_TIM_IC_Init(DEC_USE_TIM, LL_TIM_CHANNEL_CH4, &TIM_ICInitStruct);

	//---��ʱ���жϵȼ�
	NVIC_SetPriority(DEC_USE_TIM_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

	//---ʹ�ܶ�ʱ���ж�
	NVIC_EnableIRQ(TIM2_IRQn);

	//---�����־λ
	LL_TIM_ClearFlag(DEC_USE_TIM);

	//---ʹ�����벶׽ͨ��1���ж�
	LL_TIM_EnableIT_CC1(DEC_USE_TIM);

	//---ʹ�����벶׽ͨ��2���ж�
	LL_TIM_EnableIT_CC2(DEC_USE_TIM);

	//---ʹ�����벶׽ͨ��3���ж�
	LL_TIM_EnableIT_CC3(DEC_USE_TIM);

	//---ʹ�����벶׽ͨ��4���ж�
	LL_TIM_EnableIT_CC4(DEC_USE_TIM);

	//---ʹ�ܸ����ж�
	LL_TIM_EnableIT_UPDATE(DEC_USE_TIM);

	//---ʹ�ܶ�ʱ��
	LL_TIM_EnableCounter(DEC_USE_TIM);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����������ĳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
void Decode_Init(void)
{
	Decode_DecodeLEDInit();
	Decode_DecodeRSTInit();
	Decode_DecodeCHInit();
	Decode_DecodeTimerInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����������ĳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
void  Decode_ActivateSites(UINT8_T activateSites)
{
	UINT8_T i = 0;
	for (i = 0; i < DECODE_SITE_COUNT; i++)
	{
		if ((activateSites & 0x01) != 0)
		{
			decodeActivateSite[i] = 0x01;
		}
		else
		{
			decodeActivateSite[i] = 0x00;
		}

		//---����һλ
		activateSites >>= 1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		��������������
//////////////////////////////////////////////////////////////////////////////
void Decode_START(void)
{
	DEC_LED_OFF;

	//---�����־λ
	LL_TIM_ClearFlag(DEC_USE_TIM);

	//---���������
	LL_TIM_SetCounter(DEC_USE_TIM, 0);

	//---ʹ�ܶ�ʱ��
	LL_TIM_EnableCounter(DEC_USE_TIM);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����رս�����
//////////////////////////////////////////////////////////////////////////////
void Decode_STOP(void)
{
	//---ʹ�ܶ�ʱ��
	LL_TIM_DisableCounter(DEC_USE_TIM);
	DEC_LED_OFF;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��ȡ�����RST�ź�
//////////////////////////////////////////////////////////////////////////////
UINT8_T Decode_GetRST(void)
{
	UINT8_T _return = 0;

	//---���SOT
	if (DECA_RST_STATE == 0)
	{
		_return |= 0x01;
	}
	if (DECB_RST_STATE == 0)
	{
		_return |= 0x02;
	}
	if (DECC_RST_STATE == 0)
	{
		_return |= 0x04;
	}
	if (DECD_RST_STATE == 0)
	{
		_return |= 0x08;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ɨ�����RST�ź�
//////////////////////////////////////////////////////////////////////////////
UINT8_T Decode_ScanRST(void)
{
	//---��ȡRST��״̬
	UINT8_T _return = Decode_GetRST();

	//---����Ƿ��н����ź�
	if (_return != 0)
	{
		//---��ʱ�ȴ��������������ͬʱ���ڵȴ�����SITE�Ĵ����źŵĵ���
		DelayTask_ms(10);

		//---��ȡRST��״̬
		_return = Decode_GetRST();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ʵʱ�����
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeLED(UINT8_T channel, UINT8_T isPass)
{
	switch (channel)
	{
		case 0:
			if (isPass)
			{
				DECA_LED_OUT_1;
			}
			else
			{
				DECA_LED_OUT_0;
			}
			break;
		case 1:
			if (isPass)
			{
				DECB_LED_OUT_1;
			}
			else
			{
				DECB_LED_OUT_0;
			}
			break;
		case 2:
			if (isPass)
			{
				DECC_LED_OUT_1;
			}
			else
			{
				DECC_LED_OUT_0;
			}
			break;
		case 3:
			if (isPass)
			{
				DECD_LED_OUT_1;
			}
			else
			{
				DECD_LED_OUT_0;
			}
			break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����������
//////////////////////////////////////////////////////////////////////////////
UINT32_T Decode_CalcHighPulseWidth(UINT8_T site)
{
	UINT32_T _return = 0;
	if (decodeOverFlowCountBKP[site] != 0)
	{
		_return = (DECODE_TIM_RELOAD* decodeOverFlowCountBKP[site] + decodeRisingPulseCount[site] - decodeFallingPulseCount[site]);
	}
	else
	{
		_return = (decodeRisingPulseCount[site] - decodeFallingPulseCount[site]);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����������
//////////////////////////////////////////////////////////////////////////////
UINT32_T Decode_CalcLowPulseWidth(UINT8_T site)
{
	UINT32_T _return = 0;
	if (decodeOverFlowCountBKP[site] != 0)
	{
		_return = (DECODE_TIM_RELOAD* decodeOverFlowCountBKP[site] + decodeFallingPulseCount[site] - decodeRisingPulseCount[site]);
	}
	else
	{
		_return = (decodeFallingPulseCount[site] - decodeRisingPulseCount[site]);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���벶׽�Ĵ���
//////////////////////////////////////////////////////////////////////////////
void Decode_CaptureHandler(UINT32_T index, UINT8_T site)
{
	//---�����¼�����������ֵ
	decodeOverFlowCount[site] = 0;

	//---�������Ե��л�
	if (LL_TIM_IC_GetPolarity(DEC_USE_TIM, index) != LL_TIM_IC_POLARITY_RISING)
	{
		//---�½���
		decodeFallingPulseCount[site] = decodeCaptureCount[site];

		//---��׽���½���
		decodeIcpMode[site] = 1;

		//---�л�Ϊ������
		LL_TIM_IC_SetPolarity(DEC_USE_TIM, index, LL_TIM_IC_POLARITY_RISING);
	}
	else
	{
		//---������
		decodeRisingPulseCount[site] = decodeCaptureCount[site];

		//---��׽��������
		decodeIcpMode[site] = 2;

		//---�л�Ϊ������
		LL_TIM_IC_SetPolarity(DEC_USE_TIM, index, LL_TIM_IC_POLARITY_FALLING);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����رս�����
//////////////////////////////////////////////////////////////////////////////
void Decode_IRQTask(void)
{
	VLTUINT8_T site = 0;

	//---���������ж�
	if (LL_TIM_IsActiveFlag_UPDATE(DEC_USE_TIM))
	{
		//---����������ж�
		for (site = 0; site < DECODE_SITE_COUNT; site++)
		{
			//---��¼������������ֵ
			if (decodeOverFlowCount[site] < 5000)
			{
				decodeOverFlowCount[site]++;
			}
			else
			{
				decodeOverFlowCount[site] = 0;
			}
		}

		//---����жϱ�־λ
		LL_TIM_ClearFlag_UPDATE(DEC_USE_TIM);
	}
	else
	{
		//---���벶׽1�Ĳ�׽�ж�
		if (LL_TIM_IsActiveFlag_CC1(DEC_USE_TIM) != RESET)
		{
			//---���泬ʱ��������
			decodeOverFlowCountBKP[0] = decodeOverFlowCount[0];

			//---�������벶׽��ֵ
			decodeCaptureCount[0] = LL_TIM_IC_GetCaptureCH1(DEC_USE_TIM);

			//---�������벶׽��ֵ
			Decode_CaptureHandler(LL_TIM_CHANNEL_CH1, 0);

			//---����жϱ�־λ
			LL_TIM_ClearFlag_CC1(DEC_USE_TIM);
		}

		//---���벶׽2�Ĳ�׽�ж�
		if (LL_TIM_IsActiveFlag_CC2(DEC_USE_TIM) != RESET)
		{
			//---���泬ʱ��������
			decodeOverFlowCountBKP[1] = decodeOverFlowCount[1];

			//---�������벶׽��ֵ
			decodeCaptureCount[1] = LL_TIM_IC_GetCaptureCH2(DEC_USE_TIM);

			//---�������벶׽��ֵ
			Decode_CaptureHandler(LL_TIM_CHANNEL_CH2, 1);

			//---����жϱ�־λ
			LL_TIM_ClearFlag_CC2(DEC_USE_TIM);
		}

		//---���벶׽3�Ĳ�׽�ж�
		if (LL_TIM_IsActiveFlag_CC3(DEC_USE_TIM) != RESET)
		{
			//---���泬ʱ��������
			decodeOverFlowCountBKP[2] = decodeOverFlowCount[2];

			//---�������벶׽��ֵ
			decodeCaptureCount[2] = LL_TIM_IC_GetCaptureCH3(DEC_USE_TIM);

			//---�������벶׽��ֵ
			Decode_CaptureHandler(LL_TIM_CHANNEL_CH3, 2);

			//---����жϱ�־λ
			LL_TIM_ClearFlag_CC3(DEC_USE_TIM);
		}

		//---���벶׽4�Ĳ�׽�ж�
		if (LL_TIM_IsActiveFlag_CC4(DEC_USE_TIM) != RESET)
		{
			//---���泬ʱ��������
			decodeOverFlowCountBKP[3] = decodeOverFlowCount[3];

			//---�������벶׽��ֵ
			decodeCaptureCount[3] = LL_TIM_IC_GetCaptureCH4(DEC_USE_TIM);

			//---�������벶׽��ֵ
			Decode_CaptureHandler(LL_TIM_CHANNEL_CH4, 3);

			//---����жϱ�־λ
			LL_TIM_ClearFlag_CC4(DEC_USE_TIM);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���������ش���
//////////////////////////////////////////////////////////////////////////////
void Decode_SetPolarityRising(UINT8_T site)
{
	switch (site)
	{
		case 0:
			LL_TIM_IC_SetPolarity(DEC_USE_TIM, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_RISING);
			break;
		case 1:
			LL_TIM_IC_SetPolarity(DEC_USE_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_RISING);
			break;
		case 2:
			LL_TIM_IC_SetPolarity(DEC_USE_TIM, LL_TIM_CHANNEL_CH3, LL_TIM_IC_POLARITY_RISING);
			break;
		case 3:
			LL_TIM_IC_SetPolarity(DEC_USE_TIM, LL_TIM_CHANNEL_CH4, LL_TIM_IC_POLARITY_RISING);
			break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����½��ش���
//////////////////////////////////////////////////////////////////////////////
void Decode_SetPolarityFalling(UINT8_T site)
{
	switch (site)
	{
		case 0:
			LL_TIM_IC_SetPolarity(DEC_USE_TIM, LL_TIM_CHANNEL_CH1, LL_TIM_IC_POLARITY_FALLING);
			break;
		case 1:
			LL_TIM_IC_SetPolarity(DEC_USE_TIM, LL_TIM_CHANNEL_CH2, LL_TIM_IC_POLARITY_FALLING);
			break;
		case 2:
			LL_TIM_IC_SetPolarity(DEC_USE_TIM, LL_TIM_CHANNEL_CH3, LL_TIM_IC_POLARITY_FALLING);
			break;
		case 3:
			LL_TIM_IC_SetPolarity(DEC_USE_TIM, LL_TIM_CHANNEL_CH4, LL_TIM_IC_POLARITY_FALLING);
			break;
		default:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����������뵽����ֵ�洢��
//////////////////////////////////////////////////////////////////////////////
void Decode_AddBit(UINT16_T channel, UINT16_T value)
{
	//---�жϽ���ֵ
	if (value)
	{
		//---������ӵ�����Ϣ
		//LED_DEBUG_OUT_1;
	}
	else
	{
		//---������ӵ�����Ϣ
		//LED_DEBUG_OUT_0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Decode_Quency(void)
{
	UINT32_T pulseWidth = 0;
	UINT8_T site = 0;

	//---����·���н���
	for (site = 0; site < DECODE_SITE_COUNT; site++)
	{
		if (decodeActivateSite[site] == 1)
		{
			decodeMinPulseCount[site] = MIN(decodeRisingPulseCount[site], decodeFallingPulseCount[site]);

			//---��ȡ��ǰ��������ֵ
			decodeNowCount[site] = LL_TIM_GetCounter(DEC_USE_TIM);

			//---����������
			pulseWidth = decodeOverFlowCount[site]
				? (DECODE_TIM_RELOAD* decodeOverFlowCount[site] - decodeMinPulseCount[site])
				: (decodeNowCount[site] - decodeMinPulseCount[site]);

			//---�������
			switch (decodeStep[site])
			{
				case DECODE_STEP_0:

					//---ת�����벽��0
					decodeStep[site] = DECODE_STEP_1;

					//---��ʼ����׽ģʽ
					decodeIcpMode[site] = 0;

					//---��ʼ��������
					decodePulseWidth[site] = 0;

					//---����ͨ�������ز�׽ģʽ
					Decode_SetPolarityRising(site);
					break;
				case DECODE_STEP_1:

					//---����λ����0
					decodeBitIndex[site] = 0;
					decodeStep[site] = DECODE_STEP_2;

					//---�رս���ʵʱ��
					Decode_DecodeLED(site, 0);
					break;
				case DECODE_STEP_2:

					//---��֤�ߵ�ƽ
					if ((decodeIcpMode[site] & 0x03) == 2)
					{
						//---����ߵ�ƽ���
						decodePulseWidth[site] = Decode_CalcHighPulseWidth(site);

						//---��λ��ץȡ��¼ֵ
						decodeIcpMode[site] = 0;

						//---�ж�����Ŀ��
						if ((decodePulseWidth[site] > DECODE_PULSE_WIDTH_MIN) && (decodePulseWidth[site] < DECODE_PULSE_WIDTH_MAX))
						{
							//---��֤�ߵ�ƽ
							decodeStep[site] = DECODE_STEP_3;
							Decode_AddBit(site, 1);
						}
						else
						{
							//---�ߵ�ƽ��������������������
							decodeStep[site] = DECODE_STEP_1;
						}
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������
						if ((decodePulseWidth[site] > 0) && (pulseWidth > (decodePulseWidth[site] * 35)))
						{
							decodeStep[site] = DECODE_STEP_0;
						}
					}
					break;
				case DECODE_STEP_3:

					//---��֤�͵�ƽ
					if ((decodeIcpMode[site] & 0x03) == 1)
					{
						//---����ߵ�ƽ���
						decodePulseWidth[site] = Decode_CalcLowPulseWidth(site);

						//---��λ��ץȡ��¼ֵ
						decodeIcpMode[site] = 0;

						//---�ж�����Ŀ��
						if ((decodePulseWidth[site] > DECODE_PULSE_WIDTH_MIN) && (decodePulseWidth[site] < DECODE_PULSE_WIDTH_MAX))
						{
							//---��֤�͵�ƽ
							decodeStep[site] = DECODE_STEP_2;
							Decode_AddBit(site, 0);
							if (decodeBitIndex[site] < DECODE_CONTINUE_SQUARE_PASS_COUNT)
							{
								decodeBitIndex[site]++;
							}
							else
							{
								//---����ɹ����򿪽���ʵʱ��
								Decode_DecodeLED(site, 1);
							}
						}
						else
						{
							decodeStep[site] = DECODE_STEP_1;
						}
					}
					else
					{
						//---ͬ��ƽά��ʱ��̫������
						if ((decodePulseWidth[site] > 0) && (pulseWidth > (decodePulseWidth[site] * 35)))
						{
							decodeStep[site] = DECODE_STEP_0;
						}
					}
					break;
				case DECODE_STEP_4:
				default:
					decodeStep[site] = DECODE_STEP_0;
					break;
			}
		}
	}
}