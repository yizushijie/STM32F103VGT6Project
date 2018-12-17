#include "key_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_BINInit(void)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(BINA_CTR_PORT, 1);
	GPIOTask_Clock(BINB_CTR_PORT, 1);
	GPIOTask_Clock(BINC_CTR_PORT, 1);
	GPIOTask_Clock(BIND_CTR_PORT, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO的速度---中速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif

	//---BINA_CTR_BIT的初始化
	GPIO_InitStruct.Pin = BINA_CTR_BIT;
	LL_GPIO_Init(BINA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINA_CTR_PORT, BINA_CTR_BIT);

	//---BINB_CTR_BIT的初始化
	GPIO_InitStruct.Pin = BINB_CTR_BIT;
	LL_GPIO_Init(BINB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINB_CTR_PORT, BINB_CTR_BIT);

	//---BINC_CTR_BIT的初始化
	GPIO_InitStruct.Pin = BINC_CTR_BIT;
	LL_GPIO_Init(BINC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BINC_CTR_PORT, BINC_CTR_BIT);

	//---BIND_CTR_BIT的初始化
	GPIO_InitStruct.Pin = BIND_CTR_BIT;
	LL_GPIO_Init(BIND_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(BIND_CTR_PORT, BIND_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_SOTInit(void)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(SOTA_CTR_PORT, 1);
	GPIOTask_Clock(SOTB_CTR_PORT, 1);
	GPIOTask_Clock(SOTC_CTR_PORT, 1);
	GPIOTask_Clock(SOTD_CTR_PORT, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO的速度---中速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif

	//---SOTA_CTR_BIT的初始化
	GPIO_InitStruct.Pin = SOTA_CTR_BIT;
	LL_GPIO_Init(SOTA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTA_CTR_PORT, SOTA_CTR_BIT);

	//---SOTB_CTR_BIT的初始化
	GPIO_InitStruct.Pin = SOTB_CTR_BIT;
	LL_GPIO_Init(SOTB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTB_CTR_PORT, SOTB_CTR_BIT);

	//---SOTC_CTR_BIT的初始化
	GPIO_InitStruct.Pin = SOTC_CTR_BIT;
	LL_GPIO_Init(SOTC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTC_CTR_PORT, SOTC_CTR_BIT);

	//---SOTD_CTR_BIT的初始化
	GPIO_InitStruct.Pin = SOTD_CTR_BIT;
	LL_GPIO_Init(SOTD_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(SOTD_CTR_PORT, SOTD_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_EOTInit(void)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(EOTA_CTR_PORT, 1);
	GPIOTask_Clock(EOTB_CTR_PORT, 1);
	GPIOTask_Clock(EOTC_CTR_PORT, 1);
	GPIOTask_Clock(EOTD_CTR_PORT, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO的速度---中速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif

	//---EOTA_CTR_BIT的初始化
	GPIO_InitStruct.Pin = EOTA_CTR_BIT;
	LL_GPIO_Init(EOTA_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTA_CTR_PORT, EOTA_CTR_BIT);

	//---EOTB_CTR_BIT的初始化
	GPIO_InitStruct.Pin = EOTB_CTR_BIT;
	LL_GPIO_Init(EOTB_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTB_CTR_PORT, EOTB_CTR_BIT);

	//---EOTC_CTR_BIT的初始化
	GPIO_InitStruct.Pin = EOTC_CTR_BIT;
	LL_GPIO_Init(EOTC_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTC_CTR_PORT, EOTC_CTR_BIT);

	//---EOTD_CTR_BIT的初始化
	GPIO_InitStruct.Pin = EOTD_CTR_BIT;
	LL_GPIO_Init(EOTD_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(EOTD_CTR_PORT, EOTD_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 解码成功标志位
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_DECInit(void)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(DECA_PASS_CTR_PORT, 1);
	GPIOTask_Clock(DECB_PASS_CTR_PORT, 1);
	GPIOTask_Clock(DECC_PASS_CTR_PORT, 1);
	GPIOTask_Clock(DECD_PASS_CTR_PORT, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO的速度---中速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif

	//---DECA_CH_BIT的初始化
	GPIO_InitStruct.Pin = DECA_PASS_CTR_BIT;
	LL_GPIO_Init(DECA_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_PASS_CTR_PORT, DECA_PASS_CTR_BIT);

	//---DECB_CH_BIT的初始化
	GPIO_InitStruct.Pin = DECB_PASS_CTR_BIT;
	LL_GPIO_Init(DECB_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_PASS_CTR_PORT, DECB_PASS_CTR_BIT);

	//---DECC_CH_BIT的初始化
	GPIO_InitStruct.Pin = DECC_PASS_CTR_BIT;
	LL_GPIO_Init(DECC_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_PASS_CTR_PORT, DECC_PASS_CTR_BIT);

	//---DECD_CH_BIT的初始化
	GPIO_InitStruct.Pin = DECD_PASS_CTR_BIT;
	LL_GPIO_Init(DECD_PASS_CTR_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_PASS_CTR_PORT, DECD_PASS_CTR_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_Init()
{
	Key_BINInit();
	Key_SOTInit();
	Key_EOTInit();
	Key_DECInit();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 获取SOT的状态
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T Key_GetSOT(void)
{
	UINT8_T _return = 0;

	//---检测SOT
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T Key_ScanSOT(void)
{
	//---读取SOT的状态
	UINT8_T _return = Key_GetSOT();
	if (_return != 0)
	{
		//---延时等待，用于软件消抖同时用于等待其他SITE的触发信号的到来
		DelayTask_ms(10);

		//---读取SOT的状态
		_return = Key_GetSOT();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_EOTSTART(void)
{
	//---置位SOT
	EOTA_CTR_OUT_1;
	EOTB_CTR_OUT_1;
	EOTC_CTR_OUT_1;
	EOTD_CTR_OUT_1;

	//---置位BIN
	BINA_CTR_OUT_1;
	BINB_CTR_OUT_1;
	BINC_CTR_OUT_1;
	BIND_CTR_OUT_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_EOTSTOP(void)
{
	EOTA_CTR_OUT_0;
	EOTB_CTR_OUT_0;
	EOTC_CTR_OUT_0;
	EOTD_CTR_OUT_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_BINAPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEA合格
		BINA_CTR_OUT_0;
	}
	else
	{
		//---SITEA不合格
		BINA_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_BINBPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEB合格
		BINB_CTR_OUT_0;
	}
	else
	{
		//---SITEB不合格
		BINB_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_BINCPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITEC合格
		BINC_CTR_OUT_0;
	}
	else
	{
		//---SITEC不合格
		BINC_CTR_OUT_1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Key_BINDPass(UINT8_T isPass)
{
	if (isPass == 0)
	{
		//---SITED合格
		BIND_CTR_OUT_0;
	}
	else
	{
		//---SITED不合格
		BIND_CTR_OUT_1;
	}
}