#include "spi_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� SPI������ģʽ�Ĳ�ѯ��ʽ��ʼ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_PollMode_Init(SPI_HandlerType *SPIx, LL_SPI_InitTypeDef SPI_InitStruct)
{
	//---�ָ���ǰ����Ϊ��ʼֵ
	LL_SPI_DeInit(SPIx->msgSPIx);

	//---ʹ��SPI��ʱ����
	SPI_Clock(SPIx, 1);

	//---SPI��ʼ��
	LL_SPI_Init(SPIx->msgSPIx, &(SPI_InitStruct));
	#ifndef USE_MCU_STM32F1

	//---SPI1�ı�׼Э���֧��
	LL_SPI_SetStandard(SPIx->msgSPIx, SPIx->msgStandard);
	#endif

	//---ʹ��SPI
	LL_SPI_Enable(SPIx->msgSPIx);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		���� 
//////��		�ܣ� 
//////�������: 
//////�������: 
//////˵		���� �����Ǹ�λ����ǰ���ǵ�λ��ǰ
//////////////////////////////////////////////////////////////////////////////
void SPI_MHW_SetTransferBitOrder(SPI_HandlerType *SPIx, UINT32_T BitOrder)
{
	LL_SPI_SetTransferBitOrder(SPIx->msgSPIx, BitOrder);
}



///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �˿ڳ�ʼ��
//////�������:
//////�������:
//////˵		���� Ӳ��SPI��Դʱ��GPIO�˿ڳ�ʼ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_GPIO_Init(SPI_HandlerType *SPIx)
{
	//---�˿�ʱ�ӵ�����
	GPIOTask_Clock(SPIx->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMISO.msgGPIOPort, 1);

	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = SPIx->msgGPIOAlternate;
	#endif
	LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---����Ϊ���
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_GPIO_Init(SPI_HandlerType *SPIx)
{
	//---�˿�ʱ�ӵ�����
	GPIOTask_Clock(SPIx->msgCS.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgSCK.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMOSI.msgGPIOPort, 1);
	GPIOTask_Clock(SPIx->msgMISO.msgGPIOPort, 1);

	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_GPIO_DeInit(SPI_HandlerType *SPIx)
{
	//---�˿ڵ�����
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---SS---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgCS.msgGPIOBit;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	#endif
	LL_GPIO_Init(SPIx->msgCS.msgGPIOPort, &GPIO_InitStruct);

	//---SCK---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgSCK.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgSCK.msgGPIOPort, &GPIO_InitStruct);

	//---MOSI---����Ϊ���
	GPIO_InitStruct.Pin = SPIx->msgMOSI.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMOSI.msgGPIOPort, &GPIO_InitStruct);

	//---MISO---����Ϊ����
	GPIO_InitStruct.Pin = SPIx->msgMISO.msgGPIOBit;
	LL_GPIO_Init(SPIx->msgMISO.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(SPIx->msgCS.msgGPIOPort, SPIx->msgCS.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	GPIO_OUT_1(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_DeInit(SPI_HandlerType *SPIx)
{
	//---�ָ���ǰ����Ϊ��ʼֵ
	LL_SPI_DeInit(SPIx->msgSPIx);

	//---��ʹ��SPI��ʱ����
	SPI_Clock(SPIx, 0);
	return SPI_GPIO_DeInit(SPIx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_Clock(SPI_HandlerType *SPIx, UINT8_T isEnable)
{
	//---ѡ��SPI�ӿ�
	if (SPIx->msgSPIx == SPI1)
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
	else if (SPIx->msgSPIx == SPI2)
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
	else if (SPIx->msgSPIx == SPI3)
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
	else if (SPIx->msgSPIx == SPI4)
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
	else if (SPIx->msgSPIx == SPI5)
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
	else if (SPIx->msgSPIx == SPI6)
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
UINT8_T SPI_MHW_PollMode_WriteByte(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---��ȡ��ǰʱ�����
	UINT32_T nowTime = 0;
	if (SPIx->msgFuncTick != NULL)
	{
		nowTime = SPIx->msgFuncTick();
	}

	//---�ȴ����ͻ�����Ϊ�գ�TXE �¼�---TXE=1����ʼ������һ������
	while (!LL_SPI_IsActiveFlag_TXE(SPIx->msgSPIx))
	{
		if (SPIx->msgFuncTick != NULL)
		{
			if ((SPIx->msgFuncTick() - nowTime) > 100)
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
	LL_SPI_TransmitData8(SPIx->msgSPIx, wVal);

	//---��ȡ��ǰʱ�����
	if (SPIx->msgFuncTick != NULL)
	{
		nowTime = SPIx->msgFuncTick();
	}
	else
	{
		nowTime = 0;
	}

	//---�ȴ����ջ������ǿգ�RXNE �¼�---�ȴ�RXNE=1����ȡ�յ�������
	while (!LL_SPI_IsActiveFlag_RXNE(SPIx->msgSPIx))
	{
		if (SPIx->msgFuncTick != NULL)
		{
			if ((SPIx->msgFuncTick() - nowTime) > 100)
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
		*pRVal = LL_SPI_ReceiveData8(SPIx->msgSPIx);
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
UINT8_T SPI_MHW_PollMode_WriteData(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (pRVal == NULL)
		{
			_return = SPI_MHW_PollMode_WriteByte(SPIx, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MHW_PollMode_WriteByte(SPIx, pWVal[i], &pRVal[i]);
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
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteBitMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---����1bit������
	if ((wVal & 0x80) == 0x00)
	{
		GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}

	//---��ȡ1bit������
	if (GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)
	{
		if (pRVal != NULL)
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
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteBitLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	//---����1bit������
	if ((wVal & 0x01) == 0x00)
	{
		GPIO_OUT_0(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(SPIx->msgMOSI.msgGPIOPort, SPIx->msgMOSI.msgGPIOBit);
	}

	//---��ȡ1bit������
	if (GPIO_GET_STATE(SPIx->msgMISO.msgGPIOPort, SPIx->msgMISO.msgGPIOBit) != 0)
	{
		if (pRVal != NULL)
		{
			*pRVal |= 0x80;
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
UINT8_T SPI_MSW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock)
{
	SPIx->msgPluseWidth = clock;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MHW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock)
{
	LL_SPI_SetBaudRatePrescaler(SPIx->msgSPIx, clock);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteByteMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	UINT8_T i = 0;
	if (pRVal != NULL)
	{
		*pRVal = 0;
	}
	for (i = 0; i < 8; i++)
	{
		if (pRVal != NULL)
		{
			*pRVal <<= 1;
		}
		if (SPI_MSW_WriteBitMSB(SPIx, wVal, pRVal) != OK_0)
		{
			return ERROR_1;
		}
		wVal <<= 1;
		GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		if (SPIx->msgFuncDelay != NULL)
		{
			SPIx->msgFuncDelay(SPIx->msgPluseWidth);
		}
		GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		if (SPIx->msgFuncDelay != NULL)
		{
			SPIx->msgFuncDelay(SPIx->msgPluseWidth);
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
UINT8_T SPI_MSW_WriteByteLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal)
{
	UINT8_T i = 0;
	if (pRVal!=NULL)
	{
		*pRVal = 0;
	}
	for (i = 0; i < 8; i++)
	{
		if (pRVal != NULL)
		{
			*pRVal >>= 1;
		}
		if (SPI_MSW_WriteBitLSB(SPIx, wVal, pRVal) != OK_0)
		{
			return ERROR_1;
		}
		wVal >>= 1;
		GPIO_OUT_1(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		if (SPIx->msgFuncDelay != NULL)
		{
			SPIx->msgFuncDelay(SPIx->msgPluseWidth);
		}
		GPIO_OUT_0(SPIx->msgSCK.msgGPIOPort, SPIx->msgSCK.msgGPIOBit);
		if (SPIx->msgFuncDelay != NULL)
		{
			SPIx->msgFuncDelay(SPIx->msgPluseWidth);
		}
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteDataMSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		//---�ж������Ƿ���Ч
		if (pRVal == NULL)
		{
			_return = SPI_MSW_WriteByteMSB(SPIx, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MSW_WriteByteMSB(SPIx, pWVal[i], &pRVal[i]);
		}

		//---�ж϶�ȡ��ȷ��
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
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
UINT8_T SPI_MSW_WriteDataLSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		//---�ж������Ƿ���Ч
		if (pRVal == NULL)
		{
			_return = SPI_MSW_WriteByteLSB(SPIx, pWVal[i], NULL);
		}
		else
		{
			_return = SPI_MSW_WriteByteLSB(SPIx, pWVal[i], &pRVal[i]);
		}

		//---�ж϶�ȡ��ȷ��
		if (_return != OK_0)
		{
			break;
		}
	}
	return _return;
}