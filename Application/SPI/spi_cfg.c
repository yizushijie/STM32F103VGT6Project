#include "spi_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� SPI������ģʽ�Ĳ�ѯ��ʽ��ʼ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_Init(SPI_HandlerType *spix, LL_SPI_InitTypeDef SPI_InitStruct)
{
	//---�ָ���ǰ����Ϊ��ʼֵ
	LL_SPI_DeInit(spix->msgSPIx);

	//---ʹ��SPI��ʱ����
	SPI_Clock(spix, 1);

	//---SPI��ʼ��
	LL_SPI_Init(spix->msgSPIx, &(SPI_InitStruct));
	#ifndef USE_MCU_STM32F1

	//---SPI1�ı�׼Э���֧��
	LL_SPI_SetStandard(spix->msgSPIx, spix->msgStandard);
	#endif

	//---ʹ��SPI
	LL_SPI_Enable(spix->msgSPIx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �˿ڳ�ʼ��
//////�������:
//////�������:
//////˵		���� Ӳ��SPI��Դʱ��GPIO�˿ڳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_GPIO_Init(SPI_HandlerType *spix)
{
	//---�˿�ʱ�ӵ�����
	GPIOTask_Clock(spix->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgMISO.msgGPIOPort, 1);

	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---����Ϊ���
	GPIO_InitStruct.Pin = spix->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = spix->msgGPIOAlternate;
	#endif
	LL_GPIO_Init(spix->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---����Ϊ���
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Pin = spix->msgSCK.msgGPIOBit;
	LL_GPIO_Init(spix->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---����Ϊ���
	GPIO_InitStruct.Pin = spix->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(spix->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = spix->msgMISO.msgGPIOBit;
	LL_GPIO_Init(spix->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(spix->msgCS.msgGPIOPort, spix->msgCS.msgGPIOBit);
	GPIO_OUT_1(spix->msgSCK.msgGPIOPort, spix->msgSCK.msgGPIOBit);
	GPIO_OUT_1(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(spix->msgMISO.msgGPIOPort, spix->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_GPIO_Init(SPI_HandlerType *spix)
{
	//---�˿�ʱ�ӵ�����
	GPIOTask_Clock(spix->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(spix->msgMISO.msgGPIOPort, 1);

	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---����Ϊ���
	GPIO_InitStruct.Pin = spix->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	LL_GPIO_Init(spix->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---����Ϊ���
	GPIO_InitStruct.Pin = spix->msgSCK.msgGPIOBit;
	LL_GPIO_Init(spix->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---����Ϊ���
	GPIO_InitStruct.Pin = spix->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(spix->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---����Ϊ����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_GPIO_DeInit(SPI_HandlerType *spix)
{
	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---����Ϊ���
	GPIO_InitStruct.Pin = spix->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	LL_GPIO_Init(spix->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---����Ϊ���
	GPIO_InitStruct.Pin = spix->msgSCK.msgGPIOBit;
	LL_GPIO_Init(spix->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---����Ϊ���
	GPIO_InitStruct.Pin = spix->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(spix->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = spix->msgMISO.msgGPIOBit;
	LL_GPIO_Init(spix->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(spix->msgCS.msgGPIOPort, spix->msgCS.msgGPIOBit);
	GPIO_OUT_1(spix->msgSCK.msgGPIOPort, spix->msgSCK.msgGPIOBit);
	GPIO_OUT_1(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(spix->msgMISO.msgGPIOPort, spix->msgMISO.msgGPIOBit);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_DeInit(SPI_HandlerType *spix)
{
	//---�ָ���ǰ����Ϊ��ʼֵ
	LL_SPI_DeInit(spix->msgSPIx);

	//---��ʹ��SPI��ʱ����
	SPI_Clock(spix, 0);
	return SPI_GPIO_DeInit(spix);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_Clock(SPI_HandlerType *spix, UINT8_T isEnable)
{
	//---ѡ��SPI�ӿ�
	if (spix->msgSPIx == SPI1)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI1);
		}
	}
	else if (spix->msgSPIx == SPI2)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI2);
		}
	}
	else if (spix->msgSPIx == SPI3)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_SPI3);
		}
	}
	#ifdef SPI4
	else if (spix->msgSPIx == SPI4)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI4);
		}
	}
	#endif
	#ifdef SPI5
	else if (spix->msgSPIx == SPI5)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI5);
		}
	}
	#endif
	#ifdef SPI6
	else if (spix->msgSPIx == SPI6)
	{
		if (isEnable)
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
		else
		{
			//---ʹ��SPI��ʱ����
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_SPI6);
		}
	}
	#endif
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������: 0---�ɹ���!=0---ʧ��
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_WriteByte(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal)
{
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	if (spix->msgFuncTick != NULL)
	{
		nowTime = spix->msgFuncTick();
	}

	//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
	while (!LL_SPI_IsActiveFlag_TXE(spix->msgSPIx))
	{
		if (spix->msgFuncTick != NULL)
		{
			if ((spix->msgFuncTick() - nowTime) > 100)
			{
				//---���ͷ�����ʱ����
				return ERROR_2;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---���ͷ�����ʱ����
				return ERROR_3;
			}
		}
	}

	//---д�����ݼĴ�������Ҫд�������д�뷢�ͻ�����
	LL_SPI_TransmitData8(spix->msgSPIx, wVal);

	//---��ȡ��ǰʱ�����
	if (spix->msgFuncTick != NULL)
	{
		nowTime = spix->msgFuncTick();
	}
	else
	{
		nowTime = 0;
	}

	//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
	while (!LL_SPI_IsActiveFlag_RXNE(spix->msgSPIx))
	{
		if (spix->msgFuncTick != NULL)
		{
			if ((spix->msgFuncTick() - nowTime) > 100)
			{
				//---���ͷ�����ʱ����
				return ERROR_4;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---���ͷ�����ʱ����
				return ERROR_5;
			}
		}
	}

	//---У���ȡ�������Ƿ�Ϊ��
	if (pRVal != NULL)
	{
		//---��ȡ���ݼĴ�������ȡ���ջ���������
		*pRVal = LL_SPI_ReceiveData8(spix->msgSPIx);
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteBit(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal)
{
	//---����1bit������
	if ((wVal & 0x80) == 0x00)
	{
		GPIO_OUT_0(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(spix->msgMOSI.msgGPIOPort, spix->msgMOSI.msgGPIOBit);
	}

	//---��ȡ1bit������
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_SetClock(SPI_HandlerType *spix, UINT32_T clock)
{
	spix->msgPluseWidth = clock;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_SetClock(SPI_HandlerType *spix, UINT32_T clock)
{
	LL_SPI_SetBaudRatePrescaler(spix->msgSPIx, clock);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
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
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteData(SPI_HandlerType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		//---�ж������Ƿ���Ч
		if (pRVal == NULL)
		{
			_return = SPI_MSW_WriteByte(spix, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MSW_WriteByte(spix, pWVal[i], &pRVal[i]);
		}

		//---�ж϶�ȡ��ȷ��
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}