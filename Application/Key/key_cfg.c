#include "key_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(BINA_CTR_PORT, 1);
	GPIOTask_Clock(BINB_CTR_PORT, 1);
	GPIOTask_Clock(BINC_CTR_PORT, 1);
	GPIOTask_Clock(BIND_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---BINA_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = BINA_CTR_BIT;
	LL_GPIO_Init(BINA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINA_CTR_PORT, BINA_CTR_BIT);

	//---BINB_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = BINB_CTR_BIT;
	LL_GPIO_Init(BINB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINB_CTR_PORT, BINB_CTR_BIT);

	//---BINC_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = BINC_CTR_BIT;
	LL_GPIO_Init(BINC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINC_CTR_PORT, BINC_CTR_BIT);

	//---BIND_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = BIND_CTR_BIT;
	LL_GPIO_Init(BIND_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BIND_CTR_PORT, BIND_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_SOTInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(SOTA_CTR_PORT, 1);
	GPIOTask_Clock(SOTB_CTR_PORT, 1);
	GPIOTask_Clock(SOTC_CTR_PORT, 1);
	GPIOTask_Clock(SOTD_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---SOTA_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = SOTA_CTR_BIT;
	LL_GPIO_Init(SOTA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTA_CTR_PORT, SOTA_CTR_BIT);

	//---SOTB_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = SOTB_CTR_BIT;
	LL_GPIO_Init(SOTB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTB_CTR_PORT, SOTB_CTR_BIT);

	//---SOTC_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = SOTC_CTR_BIT;
	LL_GPIO_Init(SOTC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTC_CTR_PORT, SOTC_CTR_BIT);

	//---SOTD_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = SOTD_CTR_BIT;
	LL_GPIO_Init(SOTD_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTD_CTR_PORT, SOTD_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_EOTInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(EOTA_CTR_PORT, 1);
	GPIOTask_Clock(EOTB_CTR_PORT, 1);
	GPIOTask_Clock(EOTC_CTR_PORT, 1);
	GPIOTask_Clock(EOTD_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---EOTA_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = EOTA_CTR_BIT;
	LL_GPIO_Init(EOTA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTA_CTR_PORT, EOTA_CTR_BIT);

	//---EOTB_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = EOTB_CTR_BIT;
	LL_GPIO_Init(EOTB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTB_CTR_PORT, EOTB_CTR_BIT);

	//---EOTC_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = EOTC_CTR_BIT;
	LL_GPIO_Init(EOTC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTC_CTR_PORT, EOTC_CTR_BIT);

	//---EOTD_CTR_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = EOTD_CTR_BIT;
	LL_GPIO_Init(EOTD_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTD_CTR_PORT, EOTD_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����ɹ���־λ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_DECInit(void)
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(DECA_PASS_CTR_PORT, 1);
	GPIOTask_Clock(DECB_PASS_CTR_PORT, 1);
	GPIOTask_Clock(DECC_PASS_CTR_PORT, 1);
	GPIOTask_Clock(DECD_PASS_CTR_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---DECA_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECA_PASS_CTR_BIT;
	LL_GPIO_Init(DECA_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_PASS_CTR_PORT, DECA_PASS_CTR_BIT);

	//---DECB_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECB_PASS_CTR_BIT;
	LL_GPIO_Init(DECB_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_PASS_CTR_PORT, DECB_PASS_CTR_BIT);

	//---DECC_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECC_PASS_CTR_BIT;
	LL_GPIO_Init(DECC_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_PASS_CTR_PORT, DECC_PASS_CTR_BIT);

	//---DECD_CH_BIT�ĳ�ʼ��
	GPIO_InitStruct.Pin = DECD_PASS_CTR_BIT;
	LL_GPIO_Init(DECD_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_PASS_CTR_PORT, DECD_PASS_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_Init()
{
	Key_BINInit();
	Key_SOTInit();
	Key_EOTInit();
	Key_DECInit();
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡSOT��״̬
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Key_GetSOT(void)
{
	UINT8_T _return = 0;

	//---���SOT
	if (SOTA_CTR_STATE == 0)
	{
		_return |= 0x01;
	}
	if (SOTB_CTR_STATE == 0)
	{
		_return |= 0x02;
	}
	if (SOTC_CTR_STATE == 0)
	{
		_return |= 0x04;
	}
	if (SOTD_CTR_STATE == 0)
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
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T Key_ScanSOT(void)
{
	//---��ȡSOT��״̬
	UINT8_T _return = Key_GetSOT();
	if (_return != 0)
	{
		//---��ʱ�ȴ��������������ͬʱ���ڵȴ�����SITE�Ĵ����źŵĵ���
		DelayTask_ms(10);

		//---��ȡSOT��״̬
		_return = Key_GetSOT();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_EOTSTART(void)
{
	//---��λSOT
	EOTA_CTR_OUT_1;
	EOTB_CTR_OUT_1;
	EOTC_CTR_OUT_1;
	EOTD_CTR_OUT_1;

	//---��λBIN
	BINA_CTR_OUT_1;
	BINB_CTR_OUT_1;
	BINC_CTR_OUT_1;
	BIND_CTR_OUT_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_EOTSTOP(void)
{
	EOTA_CTR_OUT_0;
	EOTB_CTR_OUT_0;
	EOTC_CTR_OUT_0;
	EOTD_CTR_OUT_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINAPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEA�ϸ�
		BINA_CTR_OUT_0;
	}
	else
	{
		//---SITEA���ϸ�
		BINA_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINBPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEB�ϸ�
		BINB_CTR_OUT_0;
	}
	else
	{
		//---SITEB���ϸ�
		BINB_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINCPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEC�ϸ�
		BINC_CTR_OUT_0;
	}
	else
	{
		//---SITEC���ϸ�
		BINC_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void Key_BINDPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITED�ϸ�
		BIND_CTR_OUT_0;
	}
	else
	{
		//---SITED���ϸ�
		BIND_CTR_OUT_1;
	}
}