#include "spi_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明： SPI的主机模式的查询方式初始化
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_Init(SPI_HandlerType *spix, LL_SPI_InitTypeDef SPI_InitStruct)
{
	//---恢复当前配置为初始值
	LL_SPI_DeInit(spix->msgSPIx);

	//---使能SPI的时钟线
	SPI_Clock(spix, 1);

	//---SPI初始化
	LL_SPI_Init(spix->msgSPIx, &(SPI_InitStruct));
	#ifndef USE_MCU_STM32F1

	//---SPI1的标准协议的支持
	LL_SPI_SetStandard(spix->msgSPIx, spix->msgStandard);
	#endif

	//---使能SPI
	LL_SPI_Enable(spix->msgSPIx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能： 端口初始化
//////输入参数:
//////输出参数:
//////说		明： 硬件SPI资源时的GPIO端口初始化
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_GPIO_Init(SPI_HandlerType *spix)
{
	//---端口时钟的配置
	GPIOTask_Clock(spix->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgMISO.msgGPIOPort, 1);

	//---端口的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---设置为输出
	GPIO_InitStruct.Pin = spix->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = spix->msgGPIOAlternate;
	#endif
	LL_GPIO_Init(spix->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---设置为输出
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Pin = spix->msgSCK.msgGPIOBit;
	LL_GPIO_Init(spix->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---设置为输出
	GPIO_InitStruct.Pin = spix->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(spix->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---设置为输入
	GPIO_InitStruct.Pin = spix->msgMISO.msgGPIOBit;
	LL_GPIO_Init(spix->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(spix->msgCS.msgGPIOPort, spix->msgCS.msgGPIOBit);
	GPIO_OUT_1(spix->msgSCK.msgGPIOPort, spix->msgSCK.msgGPIOBit);
	GPIO_OUT_1(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(spix->msgMISO.msgGPIOPort, spix->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_GPIO_Init(SPI_HandlerType *spix)
{
	//---端口时钟的配置
	GPIOTask_Clock(spix->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgMISO.msgGPIOPort, 1);

	//---端口的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---设置为输出
	GPIO_InitStruct.Pin = spix->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	LL_GPIO_Init(spix->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---设置为输出
	GPIO_InitStruct.Pin = spix->msgSCK.msgGPIOBit;
	LL_GPIO_Init(spix->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---设置为输出
	GPIO_InitStruct.Pin = spix->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(spix->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---设置为输入
	GPIO_InitStruct.Pin = spix->msgMISO.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(spix->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(spix->msgCS.msgGPIOPort, spix->msgCS.msgGPIOBit);
	GPIO_OUT_1(spix->msgSCK.msgGPIOPort, spix->msgSCK.msgGPIOBit);
	GPIO_OUT_1(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(spix->msgMISO.msgGPIOPort, spix->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_GPIO_DeInit(SPI_HandlerType *spix)
{
	//---端口的配置
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---设置为输出
	GPIO_InitStruct.Pin = spix->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	LL_GPIO_Init(spix->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---设置为输出
	GPIO_InitStruct.Pin = spix->msgSCK.msgGPIOBit;
	LL_GPIO_Init(spix->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---设置为输出
	GPIO_InitStruct.Pin = spix->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(spix->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---设置为输入
	GPIO_InitStruct.Pin = spix->msgMISO.msgGPIOBit;
	LL_GPIO_Init(spix->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(spix->msgCS.msgGPIOPort, spix->msgCS.msgGPIOBit);
	GPIO_OUT_1(spix->msgSCK.msgGPIOPort, spix->msgSCK.msgGPIOBit);
	GPIO_OUT_1(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(spix->msgMISO.msgGPIOPort, spix->msgMISO.msgGPIOBit);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_DeInit(SPI_HandlerType *spix)
{
	//---恢复当前配置为初始值
	LL_SPI_DeInit(spix->msgSPIx);

	//---不使能SPI的时钟线
	SPI_Clock(spix, 0);
	return SPI_GPIO_DeInit(spix);
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_Clock(SPI_HandlerType *spix, UINT8_T isEnable)
{
	//---选择SPI接口
	if (spix->msgSPIx == SPI1)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
	}
	else if (spix->msgSPIx == SPI2)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
	}
	else if (spix->msgSPIx == SPI3)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
	}
	#ifdef SPI4
	else if (spix->msgSPIx == SPI4)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
	}
	#endif
	#ifdef SPI5
	else if (spix->msgSPIx == SPI5)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
	}
	#endif
	#ifdef SPI6
	else if (spix->msgSPIx == SPI6)
	{
		if (isEnable)
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
		else
		{
			//---使能SPI的时钟线
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
	}
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数: 0---成功，!=0---失败
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_WriteByte(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal)
{
	//---获取当前时间节拍
	UINT32_T nowTime = 0;
	if (spix->msgFuncTick != NULL)
	{
		nowTime = spix->msgFuncTick();
	}

	//---等待发送缓冲区为空，TXE 事件---TXE=1，开始发送下一个数据
	while (!LL_SPI_IsActiveFlag_TXE(spix->msgSPIx))
	{
		if (spix->msgFuncTick != NULL)
		{
			if ((spix->msgFuncTick() - nowTime) > 100)
			{
				//---发送发生超时错误
				return ERROR_2;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---发送发生超时错误
				return ERROR_3;
			}
		}
	}

	//---写入数据寄存器，把要写入的数据写入发送缓冲区
	LL_SPI_TransmitData8(spix->msgSPIx, wVal);

	//---获取当前时间节拍
	if (spix->msgFuncTick != NULL)
	{
		nowTime = spix->msgFuncTick();
	}
	else
	{
		nowTime = 0;
	}

	//---等待接收缓冲区非空，RXNE 事件---等待RXNE=1，读取收到的数据
	while (!LL_SPI_IsActiveFlag_RXNE(spix->msgSPIx))
	{
		if (spix->msgFuncTick != NULL)
		{
			if ((spix->msgFuncTick() - nowTime) > 100)
			{
				//---发送发生超时错误
				return ERROR_4;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---发送发生超时错误
				return ERROR_5;
			}
		}
	}

	//---校验读取缓存区是否为空
	if (pRVal != NULL)
	{
		//---读取数据寄存器，获取接收缓冲区数据
		*pRVal = LL_SPI_ReceiveData8(spix->msgSPIx);
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
UINT8_T SPI_MHW_PollMode_WriteData(SPI_HandlerType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (pRVal == NULL)
		{
			_return = SPI_MHW_PollMode_WriteByte(spix, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MHW_PollMode_WriteByte(spix, pWVal[i], &pRVal[i]);
		}

		if (_return != OK_0)
		{
			break;
		}
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
UINT8_T SPI_MSW_WriteBit(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal)
{
	//---发送1bit的数据
	if ((wVal & 0x80) == 0x00)
	{
		GPIO_OUT_0(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	}

	//---读取1bit的数据
	if (GPIO_GET_STATE(spix->msgMISO.msgGPIOPort, spix->msgMISO.msgGPIOBit) != 0)
	{
		if (*pRVal != NULL)
		{
			*pRVal |= 1;
		}
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
UINT8_T SPI_MSW_SetClock(SPI_HandlerType *spix, UINT32_T clock)
{
	spix->msgPluseWidth = clock;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_SetClock(SPI_HandlerType *spix, UINT32_T clock)
{
	LL_SPI_SetBaudRatePrescaler(spix->msgSPIx, clock);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteByte(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal)
{
	UINT8_T i = 0;
	*pRVal = 0;
	for (i = 0; i < 8; i++)
	{
		*pRVal <<= 1;
		if (SPI_MSW_WriteBit(spix, wVal, pRVal) != OK_0)
		{
			return ERROR_1;
		}
		wVal <<= 1;
		GPIO_OUT_1(spix->msgSCK.msgGPIOPort, spix->msgSCK.msgGPIOBit);
		if (spix->msgFuncDelay != NULL)
		{
			spix->msgFuncDelay(spix->msgPluseWidth);
		}
		GPIO_OUT_0(spix->msgSCK.msgGPIOPort, spix->msgSCK.msgGPIOBit);
		if (spix->msgFuncDelay != NULL)
		{
			spix->msgFuncDelay(spix->msgPluseWidth);
		}
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
UINT8_T SPI_MSW_WriteData(SPI_HandlerType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		//---判断数据是否有效
		if (pRVal == NULL)
		{
			_return = SPI_MSW_WriteByte(spix, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MSW_WriteByte(spix, pWVal[i], &pRVal[i]);
		}

		//---判断读取正确性
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}