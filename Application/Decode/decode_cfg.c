#include "decode_cfg.h"

//===记录高低电平的最小计数值
VLTUINT32_T  decodeMinPulseCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===记录输捕捉寄存器的计数值
VLTUINT32_T  decodeCaptureCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===记录当前上升沿计数值
VLTUINT32_T  decodeRisingPulseCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===记录当前下降沿计数值
VLTUINT32_T  decodeFallingPulseCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===计数器溢出次数
VLTUINT32_T  decodeOverFlowCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===计数器溢出计数的值备份值
VLTUINT32_T  decodeOverFlowCountBKP[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===记录当前的通道捕捉模式  1--- 下降沿 2---上升沿
VLTUINT8_T   decodeIcpMode[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===解码步序
UINT8_T  decodeStep[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===解码位序
UINT16_T decodeBitIndex[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===计算一个脉冲的宽度
UINT32_T decodePulseWidth[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===定时器当前的计数值
UINT32_T decodeNowCount[DECODE_SITE_COUNT] = { 0,0,0,0 };

//===激活的SITE数
UINT8_T  decodeActivateSite[DECODE_SITE_COUNT] = { 0,0,0,0 };

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeLEDInit(void)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(DECA_LED_PORT, 1);
	GPIOTask_Clock(DECB_LED_PORT, 1);
	GPIOTask_Clock(DECC_LED_PORT, 1);
	GPIOTask_Clock(DECD_LED_PORT, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO的速度---中速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---输出模式---推完输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif

	//---DECA_SN_BIT的初始化
	GPIO_InitStruct.Pin = DECA_LED_BIT;
	LL_GPIO_Init(DECA_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_LED_PORT, DECA_LED_BIT);

	//---DECB_SN_BIT的初始化
	GPIO_InitStruct.Pin = DECB_LED_BIT;
	LL_GPIO_Init(DECB_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_LED_PORT, DECB_LED_BIT);

	//---DECC_SN_BIT的初始化
	GPIO_InitStruct.Pin = DECC_LED_BIT;
	LL_GPIO_Init(DECC_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_LED_PORT, DECC_LED_BIT);

	//---DECD_SN_BIT的初始化
	GPIO_InitStruct.Pin = DECD_LED_BIT;
	LL_GPIO_Init(DECD_LED_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_LED_PORT, DECD_LED_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeRSTInit(void)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(DECA_RST_PORT, 1);
	GPIOTask_Clock(DECB_RST_PORT, 1);
	GPIOTask_Clock(DECC_RST_PORT, 1);
	GPIOTask_Clock(DECD_RST_PORT, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO的速度---中速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif

	//---DECA_RST_BIT的初始化
	GPIO_InitStruct.Pin = DECA_RST_BIT;
	LL_GPIO_Init(DECA_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECA_RST_PORT, DECA_RST_BIT);

	//---DECB_RST_BIT的初始化
	GPIO_InitStruct.Pin = DECB_RST_BIT;
	LL_GPIO_Init(DECB_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECB_RST_PORT, DECB_RST_BIT);

	//---DECC_RST_BIT的初始化
	GPIO_InitStruct.Pin = DECC_RST_BIT;
	LL_GPIO_Init(DECC_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECC_RST_PORT, DECC_RST_BIT);

	//---DECD_RST_BIT的初始化
	GPIO_InitStruct.Pin = DECD_RST_BIT;
	LL_GPIO_Init(DECD_RST_PORT, &GPIO_InitStruct);
	GPIO_OUT_1(DECD_RST_PORT, DECD_RST_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeCHInit(void)
{
	//---使能GPIO的时钟
	GPIOTask_Clock(DECA_CH_PORT, 1);
	GPIOTask_Clock(DECB_CH_PORT, 1);
	GPIOTask_Clock(DECC_CH_PORT, 1);
	GPIOTask_Clock(DECD_CH_PORT, 1);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;			//---GPIO的速度---高速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;						//---下拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif

	//---DECA_CH_BIT的初始化
	GPIO_InitStruct.Pin = DECA_CH_BIT;
	LL_GPIO_Init(DECA_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECA_CH_PORT, DECA_CH_BIT);

	//---DECB_CH_BIT的初始化
	GPIO_InitStruct.Pin = DECB_CH_BIT;
	LL_GPIO_Init(DECB_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECB_CH_PORT, DECB_CH_BIT);

	//---DECC_CH_BIT的初始化
	GPIO_InitStruct.Pin = DECC_CH_BIT;
	LL_GPIO_Init(DECC_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECC_CH_PORT, DECC_CH_BIT);

	//---DECD_CH_BIT的初始化
	GPIO_InitStruct.Pin = DECD_CH_BIT;
	LL_GPIO_Init(DECD_CH_PORT, &GPIO_InitStruct);
	GPIO_OUT_0(DECD_CH_PORT, DECD_CH_BIT);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：解码器使用的定时器初始化
//////////////////////////////////////////////////////////////////////////////
void Decode_DecodeTimerInit(void)
{
	//---使能定时器时钟
	TimerTask_Clock(DEC_USE_TIM, 1);

	//---定时器的结构体
	LL_TIM_InitTypeDef TIM_InitStruct = { 0 };

	//---输入捕捉通道的初始化
	LL_TIM_IC_InitTypeDef TIM_ICInitStruct = { 0 };

	//---设置定时器为缺省设置
	LL_TIM_DeInit(DEC_USE_TIM);

	//---自动重载值
	TIM_InitStruct.Autoreload = DECODE_TIM_RELOAD;

	//---预分频的值---计算计数器的时钟频率---1MHz
	TIM_InitStruct.Prescaler = DECODE_TIM_ARR;//71
	TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
	TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;

	//---重复计数的次数
	TIM_InitStruct.RepetitionCounter = 0;

	//---初始化定时器
	LL_TIM_Init(DEC_USE_TIM, &TIM_InitStruct);

	//---不使能自动重载
	LL_TIM_DisableARRPreload(DEC_USE_TIM);

	//--定时器时钟使用内部时钟
	LL_TIM_SetClockSource(DEC_USE_TIM, LL_TIM_CLOCKSOURCE_INTERNAL);

	//---主模式选择复位
	LL_TIM_SetTriggerOutput(DEC_USE_TIM, LL_TIM_TRGO_RESET);

	//---不使能主从模式
	LL_TIM_DisableMasterSlaveMode(DEC_USE_TIM);

	//---直连模式
	TIM_ICInitStruct.ICActiveInput = LL_TIM_ACTIVEINPUT_DIRECTTI;

	//---时钟不分频
	TIM_ICInitStruct.ICPrescaler = LL_TIM_ICPSC_DIV1;

	//---触发模式---上升沿触发
	TIM_ICInitStruct.ICPolarity = LL_TIM_IC_POLARITY_RISING;

	//---触发滤波---8
	TIM_ICInitStruct.ICFilter = LL_TIM_IC_FILTER_FDIV8_N6;

	//---配置输入捕捉通道1
	LL_TIM_IC_Init(DEC_USE_TIM, LL_TIM_CHANNEL_CH1, &TIM_ICInitStruct);

	//---配置输入捕捉通道2
	LL_TIM_IC_Init(DEC_USE_TIM, LL_TIM_CHANNEL_CH2, &TIM_ICInitStruct);

	//---配置输入捕捉通道3
	LL_TIM_IC_Init(DEC_USE_TIM, LL_TIM_CHANNEL_CH3, &TIM_ICInitStruct);

	//---配置输入捕捉通道4
	LL_TIM_IC_Init(DEC_USE_TIM, LL_TIM_CHANNEL_CH4, &TIM_ICInitStruct);

	//---定时器中断等级
	NVIC_SetPriority(DEC_USE_TIM_IRQ, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));

	//---使能定时器中断
	NVIC_EnableIRQ(TIM2_IRQn);

	//---清零标志位
	LL_TIM_ClearFlag(DEC_USE_TIM);

	//---使能输入捕捉通道1的中断
	LL_TIM_EnableIT_CC1(DEC_USE_TIM);

	//---使能输入捕捉通道2的中断
	LL_TIM_EnableIT_CC2(DEC_USE_TIM);

	//---使能输入捕捉通道3的中断
	LL_TIM_EnableIT_CC3(DEC_USE_TIM);

	//---使能输入捕捉通道4的中断
	LL_TIM_EnableIT_CC4(DEC_USE_TIM);

	//---使能更新中断
	LL_TIM_EnableIT_UPDATE(DEC_USE_TIM);

	//---使能定时器
	LL_TIM_EnableCounter(DEC_USE_TIM);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：解码器的初始化
//////////////////////////////////////////////////////////////////////////////
void Decode_Init(void)
{
	Decode_DecodeLEDInit();
	Decode_DecodeRSTInit();
	Decode_DecodeCHInit();
	Decode_DecodeTimerInit();
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：解码器的初始化
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

		//---右移一位
		activateSites >>= 1;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：启动解码器
//////////////////////////////////////////////////////////////////////////////
void Decode_START(void)
{
	DEC_LED_OFF;

	//---清零标志位
	LL_TIM_ClearFlag(DEC_USE_TIM);

	//---清零计数器
	LL_TIM_SetCounter(DEC_USE_TIM, 0);

	//---使能定时器
	LL_TIM_EnableCounter(DEC_USE_TIM);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：关闭解码器
//////////////////////////////////////////////////////////////////////////////
void Decode_STOP(void)
{
	//---使能定时器
	LL_TIM_DisableCounter(DEC_USE_TIM);
	DEC_LED_OFF;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 读取解码的RST信号
//////////////////////////////////////////////////////////////////////////////
UINT8_T Decode_GetRST(void)
{
	UINT8_T _return = 0;

	//---检测SOT
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 扫描解码RST信号
//////////////////////////////////////////////////////////////////////////////
UINT8_T Decode_ScanRST(void)
{
	//---读取RST的状态
	UINT8_T _return = Decode_GetRST();

	//---检查是否有解码信号
	if (_return != 0)
	{
		//---延时等待，用于软件消抖同时用于等待其他SITE的触发信号的到来
		DelayTask_ms(10);

		//---读取RST的状态
		_return = Decode_GetRST();
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 实时解码灯
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 计算高脉冲宽度
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 计算低脉冲宽度
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 输入捕捉的处理
//////////////////////////////////////////////////////////////////////////////
void Decode_CaptureHandler(UINT32_T index, UINT8_T site)
{
	//---清零记录计数器溢出的值
	decodeOverFlowCount[site] = 0;

	//---触发极性的切换
	if (LL_TIM_IC_GetPolarity(DEC_USE_TIM, index) != LL_TIM_IC_POLARITY_RISING)
	{
		//---下降沿
		decodeFallingPulseCount[site] = decodeCaptureCount[site];

		//---捕捉到下降沿
		decodeIcpMode[site] = 1;

		//---切换为上升沿
		LL_TIM_IC_SetPolarity(DEC_USE_TIM, index, LL_TIM_IC_POLARITY_RISING);
	}
	else
	{
		//---上升沿
		decodeRisingPulseCount[site] = decodeCaptureCount[site];

		//---捕捉到上升沿
		decodeIcpMode[site] = 2;

		//---切换为下升沿
		LL_TIM_IC_SetPolarity(DEC_USE_TIM, index, LL_TIM_IC_POLARITY_FALLING);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：关闭解码器
//////////////////////////////////////////////////////////////////////////////
void Decode_IRQTask(void)
{
	VLTUINT8_T site = 0;

	//---发生更新中断
	if (LL_TIM_IsActiveFlag_UPDATE(DEC_USE_TIM))
	{
		//---计数器溢出中断
		for (site = 0; site < DECODE_SITE_COUNT; site++)
		{
			//---记录溢出次数的最大值
			if (decodeOverFlowCount[site] < 5000)
			{
				decodeOverFlowCount[site]++;
			}
			else
			{
				decodeOverFlowCount[site] = 0;
			}
		}

		//---清除中断标志位
		LL_TIM_ClearFlag_UPDATE(DEC_USE_TIM);
	}
	else
	{
		//---输入捕捉1的捕捉中断
		if (LL_TIM_IsActiveFlag_CC1(DEC_USE_TIM) != RESET)
		{
			//---保存超时计数器器
			decodeOverFlowCountBKP[0] = decodeOverFlowCount[0];

			//---保存输入捕捉的值
			decodeCaptureCount[0] = LL_TIM_IC_GetCaptureCH1(DEC_USE_TIM);

			//---处理输入捕捉的值
			Decode_CaptureHandler(LL_TIM_CHANNEL_CH1, 0);

			//---清除中断标志位
			LL_TIM_ClearFlag_CC1(DEC_USE_TIM);
		}

		//---输入捕捉2的捕捉中断
		if (LL_TIM_IsActiveFlag_CC2(DEC_USE_TIM) != RESET)
		{
			//---保存超时计数器器
			decodeOverFlowCountBKP[1] = decodeOverFlowCount[1];

			//---保存输入捕捉的值
			decodeCaptureCount[1] = LL_TIM_IC_GetCaptureCH2(DEC_USE_TIM);

			//---处理输入捕捉的值
			Decode_CaptureHandler(LL_TIM_CHANNEL_CH2, 1);

			//---清除中断标志位
			LL_TIM_ClearFlag_CC2(DEC_USE_TIM);
		}

		//---输入捕捉3的捕捉中断
		if (LL_TIM_IsActiveFlag_CC3(DEC_USE_TIM) != RESET)
		{
			//---保存超时计数器器
			decodeOverFlowCountBKP[2] = decodeOverFlowCount[2];

			//---保存输入捕捉的值
			decodeCaptureCount[2] = LL_TIM_IC_GetCaptureCH3(DEC_USE_TIM);

			//---处理输入捕捉的值
			Decode_CaptureHandler(LL_TIM_CHANNEL_CH3, 2);

			//---清除中断标志位
			LL_TIM_ClearFlag_CC3(DEC_USE_TIM);
		}

		//---输入捕捉4的捕捉中断
		if (LL_TIM_IsActiveFlag_CC4(DEC_USE_TIM) != RESET)
		{
			//---保存超时计数器器
			decodeOverFlowCountBKP[3] = decodeOverFlowCount[3];

			//---保存输入捕捉的值
			decodeCaptureCount[3] = LL_TIM_IC_GetCaptureCH4(DEC_USE_TIM);

			//---处理输入捕捉的值
			Decode_CaptureHandler(LL_TIM_CHANNEL_CH4, 3);

			//---清除中断标志位
			LL_TIM_ClearFlag_CC4(DEC_USE_TIM);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 设置上升沿触发
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 设置下降沿触发
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： 将解码结果加入到解码值存储区
//////////////////////////////////////////////////////////////////////////////
void Decode_AddBit(UINT16_T channel, UINT16_T value)
{
	//---判断解码值
	if (value)
	{
		//---可以添加调试信息
		//LED_DEBUG_OUT_1;
	}
	else
	{
		//---可以添加调试信息
		//LED_DEBUG_OUT_0;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
void Decode_Quency(void)
{
	UINT32_T pulseWidth = 0;
	UINT8_T site = 0;

	//---对四路进行解码
	for (site = 0; site < DECODE_SITE_COUNT; site++)
	{
		if (decodeActivateSite[site] == 1)
		{
			decodeMinPulseCount[site] = MIN(decodeRisingPulseCount[site], decodeFallingPulseCount[site]);

			//---获取当前计数器的值
			decodeNowCount[site] = LL_TIM_GetCounter(DEC_USE_TIM);

			//---计算脉冲宽度
			pulseWidth = decodeOverFlowCount[site]
				? (DECODE_TIM_RELOAD* decodeOverFlowCount[site] - decodeMinPulseCount[site])
				: (decodeNowCount[site] - decodeMinPulseCount[site]);

			//---解码过程
			switch (decodeStep[site])
			{
				case DECODE_STEP_0:

					//---转到解码步序0
					decodeStep[site] = DECODE_STEP_1;

					//---初始化捕捉模式
					decodeIcpMode[site] = 0;

					//---初始化脉冲宽度
					decodePulseWidth[site] = 0;

					//---设置通道上升沿捕捉模式
					Decode_SetPolarityRising(site);
					break;
				case DECODE_STEP_1:

					//---解码位序清0
					decodeBitIndex[site] = 0;
					decodeStep[site] = DECODE_STEP_2;

					//---关闭解码实时灯
					Decode_DecodeLED(site, 0);
					break;
				case DECODE_STEP_2:

					//---验证高电平
					if ((decodeIcpMode[site] & 0x03) == 2)
					{
						//---计算高电平宽度
						decodePulseWidth[site] = Decode_CalcHighPulseWidth(site);

						//---复位沿抓取记录值
						decodeIcpMode[site] = 0;

						//---判断脉冲的宽度
						if ((decodePulseWidth[site] > DECODE_PULSE_WIDTH_MIN) && (decodePulseWidth[site] < DECODE_PULSE_WIDTH_MAX))
						{
							//---验证高电平
							decodeStep[site] = DECODE_STEP_3;
							Decode_AddBit(site, 1);
						}
						else
						{
							//---高电平不符合连续方波的脉宽
							decodeStep[site] = DECODE_STEP_1;
						}
					}
					else
					{
						//---同电平维持时间太长处理
						if ((decodePulseWidth[site] > 0) && (pulseWidth > (decodePulseWidth[site] * 35)))
						{
							decodeStep[site] = DECODE_STEP_0;
						}
					}
					break;
				case DECODE_STEP_3:

					//---验证低电平
					if ((decodeIcpMode[site] & 0x03) == 1)
					{
						//---计算高电平宽度
						decodePulseWidth[site] = Decode_CalcLowPulseWidth(site);

						//---复位沿抓取记录值
						decodeIcpMode[site] = 0;

						//---判断脉冲的宽度
						if ((decodePulseWidth[site] > DECODE_PULSE_WIDTH_MIN) && (decodePulseWidth[site] < DECODE_PULSE_WIDTH_MAX))
						{
							//---验证低电平
							decodeStep[site] = DECODE_STEP_2;
							Decode_AddBit(site, 0);
							if (decodeBitIndex[site] < DECODE_CONTINUE_SQUARE_PASS_COUNT)
							{
								decodeBitIndex[site]++;
							}
							else
							{
								//---解码成功，打开解码实时灯
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
						//---同电平维持时间太长处理
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