#include "isp_cfg.h"

//===ȫ�ֱ����Ķ���
ISP_HandlerType  g_ISPDevice0;
pISP_HandlerType pISPDevice0 = &g_ISPDevice0;

//===ͳһ���ͺ���
UINT8_T(*ISP_SEND_CMD)(ISP_HandlerType *, UINT8_T, UINT8_T, UINT8_T, UINT8_T);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_HW_Init(ISP_HandlerType *ISPx)
{
	//---ע����ǰ����������
	SPITask_DeInit(&(ISPx->msgSPI));

	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(ISPx->msgSPI));

	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct;

	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8λ����
	SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;				//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)

	//---Ĭ�϶˿�Ϊ����ߵ�ƽ
	if (SPI_InitStruct.ClockPolarity == LL_SPI_POLARITY_LOW)
	{
		GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
		GPIO_OUT_0(ISPx->msgSPI.msgMOSI.msgGPIOPort, ISPx->msgSPI.msgMOSI.msgGPIOBit);
		GPIO_OUT_0(ISPx->msgSPI.msgMISO.msgGPIOPort, ISPx->msgSPI.msgMISO.msgGPIOBit);
	}
	SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV256;		//---ϵͳʱ��256��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;
	SPITask_MHW_PollMode_Init(&(ISPx->msgSPI), SPI_InitStruct);
	ISPx->msgInit = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SW_Init(ISP_HandlerType *ISPx)
{
	SPITask_DeInit(&(ISPx->msgSPI));

	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(ISPx->msgSPI));

	//---��Ƭѡ�ź�����ߵ�ƽ������˿ڶ�����͵�ƽ��Ĭ�ϵĳ�ʼ���Ǹߵ�ƽ����������Ҫ�Ķ�
	GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	GPIO_OUT_0(ISPx->msgSPI.msgMOSI.msgGPIOPort, ISPx->msgSPI.msgMOSI.msgGPIOBit);
	GPIO_OUT_0(ISPx->msgSPI.msgMISO.msgGPIOPort, ISPx->msgSPI.msgMISO.msgGPIOBit);
	ISPx->msgInit = 1;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Device0_Init(ISP_HandlerType *ISPx)
{
	//---�趨��ʼ��״̬
	ISPx->msgInit = 0;

	//---�趨Ӳ����ʱ��
	ISPx->msgSetClok = ISP_SCK_KHZ_32;//ISP_SCK_PRE_256;//

	//---��ʼ��
	ISPx->msgDelay = 0;

	//---��ʼ��
	ISPx->msgHideAddr = 0;

	//---���㷢�ͻ�����
	memset(ISPx->msgWriteData, 0x00, 4);
	memset(ISPx->msgReadData, 0x00, 4);

	//---CS
	ISPx->msgSPI.msgCS.msgGPIOPort = GPIOA;
	ISPx->msgSPI.msgCS.msgGPIOBit = LL_GPIO_PIN_4;

	//---SCK
	ISPx->msgSPI.msgSCK.msgGPIOPort = GPIOA;
	ISPx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_5;

	//---MISO
	ISPx->msgSPI.msgMISO.msgGPIOPort = GPIOA;
	ISPx->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_6;

	//---MOSI
	ISPx->msgSPI.msgMOSI.msgGPIOPort = GPIOA;
	ISPx->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_7;

	//---����ģʽ
	#ifndef USE_MCU_STM32F1
	ISPx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif

	//---SPI���
	ISPx->msgSPI.msgSPIx = SPI1;
	#ifndef USE_MCU_STM32F1

	//---SPI��Э��
	ISPx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
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
UINT8_T ISP_Device1_Init(ISP_HandlerType *ISPx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Device2_Init(ISP_HandlerType *ISPx)
{
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_Init(ISP_HandlerType *ISPx, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay), UINT32_T(*pTimerTick)(void))
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((ISPx != NULL) && (ISPx == ISP_TASK_ONE))
	{
		ISP_Device0_Init(ISPx);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_TWO))
	{
		ISP_Device1_Init(ISPx);
	}
	else if ((ISPx != NULL) && (ISPx == ISP_TASK_THREE))
	{
		ISP_Device2_Init(ISPx);
	}
	else
	{
		return ERROR_1;
	}

	//---ע��ms����ʱ����
	ISPx->msgFuncDelay = Delayms;

	//---ע��us��ʱ����
	ISPx->msgSPI.msgFuncDelay = Delayus;

	//---ע��δ���
	ISPx->msgSPI.msgFuncTick = pTimerTick;
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_DeInit(ISP_HandlerType *ISPx)
{
	SPITask_DeInit(&(ISPx->msgSPI));
	ISPx->msgInit = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_SetClock(ISP_HandlerType *ISPx, UINT8_T clok)
{
	switch (clok)
	{
		case ISP_SCK_KHZ_0_5:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 1000;
			break;
		case ISP_SCK_KHZ_1:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 500;
			break;
		case ISP_SCK_KHZ_2:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 250;
			break;
		case ISP_SCK_KHZ_4:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 125;
			break;
		case ISP_SCK_KHZ_8:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 64;
			break;
		case ISP_SCK_KHZ_16:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 32;
			break;
		case ISP_SCK_KHZ_32:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 16;
			break;
		case ISP_SCK_KHZ_64:
			ISPx->msgSPI.msgModelIsHW = 0;
			ISPx->msgSPI.msgPluseWidth = 8;
			break;
		case ISP_SCK_PRE_256:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV256;
			break;
		case ISP_SCK_PRE_128:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV128;
			break;
		case ISP_SCK_PRE_64:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV64;
			break;
		case ISP_SCK_PRE_32:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV32;
			break;
		case ISP_SCK_PRE_16:
			#ifdef USE_MCU_STM32
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV16;
			#endif
			break;
		case ISP_SCK_PRE_8:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV8;
			break;
		case ISP_SCK_PRE_4:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV4;
			break;
		case ISP_SCK_PRE_2:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV2;
			break;
		default:
			ISPx->msgSPI.msgModelIsHW = 1;
			ISPx->msgSPI.msgClockSpeed = LL_SPI_BAUDRATEPRESCALER_DIV256;
			break;
	}
	if (ISPx->msgSPI.msgModelIsHW != 1)
	{
		//---��һ����Ҫ��ʼ���˿ڣ������ģ�ⷽʽ�л���Ӳ����ʽ��Ҳ��Ҫ���³�ʼ��һ�¶˿�
		if ((ISPx->msgInit == 0) || (ISP_SEND_CMD == ISP_SW_SendCmd))
		{
			ISP_HW_Init(ISPx);
		}

		//---����SPI��Ӳ��ʱ��
		SPITask_MHW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgClockSpeed);

		//---���ݷ��������
		ISP_SEND_CMD = ISP_HW_SendCmd;
	}
	else
	{
		//---��һ����Ҫ��ʼ���˿ڣ������Ӳ����ʽ�л���ģ�ⷽʽ��Ҳ��Ҫ���³�ʼ��һ�¶˿�
		if ((ISPx->msgInit == 0) || (ISP_SEND_CMD == ISP_HW_SendCmd))
		{
			ISP_SW_Init(ISPx);
		}

		//---�������ģ�������
		SPITask_MSW_SetClock(&(ISPx->msgSPI), ISPx->msgSPI.msgPluseWidth);

		//---���ݷ��������
		ISP_SEND_CMD = ISP_SW_SendCmd;
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
UINT8_T ISP_SW_SendCmd(ISP_HandlerType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4)
{
	//---���㷢�ͻ�����
	memset(ISPx->msgWriteData, 0x00, 4);
	memset(ISPx->msgReadData, 0x00, 4);

	//---��䷢�ͻ�����
	ISPx->msgWriteData[0] = val1;
	ISPx->msgWriteData[1] = Val2;
	ISPx->msgWriteData[2] = val3;
	ISPx->msgWriteData[3] = val4;

	//---���ݷ���
	return SPITask_MSW_WriteData(&(ISPx->msgSPI), ISPx->msgWriteData, ISPx->msgReadData, 4);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_HW_SendCmd(ISP_HandlerType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4)
{
	//---���㷢�ͻ�����
	memset(ISPx->msgWriteData, 0x00, 4);
	memset(ISPx->msgReadData, 0x00, 4);

	//---��䷢�ͻ�����
	ISPx->msgWriteData[0] = val1;
	ISPx->msgWriteData[1] = Val2;
	ISPx->msgWriteData[2] = val3;
	ISPx->msgWriteData[3] = val4;

	//---���ݷ���
	return SPITask_MHW_PollMode_WriteData(&(ISPx->msgSPI), ISPx->msgWriteData, ISPx->msgReadData, 4);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_PreEnterProg(ISP_HandlerType *ISPx)
{
	//---���ö˿�CS�˿�Ϊ���ģʽ
	GPIO_SET_WRITE(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);

	//---��������ʱ����
	GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);

	//---�򿪵�Դ
	//POWER_DUT_ON;
	//---��������ʱ����
	GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	if (ISPx->msgFuncDelay != NULL)
	{
		ISPx->msgFuncDelay(1);
	}
	GPIO_OUT_1(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	if (ISPx->msgFuncDelay != NULL)
	{
		ISPx->msgFuncDelay(1);
	}
	GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
	if (ISPx->msgFuncDelay != NULL)
	{
		ISPx->msgFuncDelay(1);
	}

	//---���64K������
	ISPx->msgHideAddr = 0xFF;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_EnterProg(ISP_HandlerType *ISPx)
{
	UINT8_T count = ISP_SCK_AUTO_MAX_COUNT;

	//---����ʱ��
	ISP_SetClock(ISPx, ISPx->msgSetClok);

	//---���ģʽ׼��
	ISP_PreEnterProg(ISPx);

	//---�Զ���ȡ���ʵ��ٶ�
	while (count--)
	{
		//---���ͱ������
		ISP_SEND_CMD(ISPx, 0xAC, 0x53, 0x00, 0x00);

		//---����Ƿ����ɹ�
		if (ISPx->msgReadData[2] == 0x53)
		{
			return OK_0;
		}

		//---���ٴ���
		if (ISPx->msgSetClok >= ISP_SCK_KHZ_2)
		{
			ISPx->msgSetClok = ISPx->msgSetClok;
		}

		//---����ʱ��
		ISP_SetClock(ISPx, ISPx->msgSetClok);

		//---��λʱ���ߺ�Ƭѡ��
		GPIO_OUT_1(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
		GPIO_OUT_1(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
		if (ISPx->msgFuncDelay != NULL)
		{
			ISPx->msgFuncDelay(1);
		}

		//---����ʱ���ߺ�Ƭѡ��
		GPIO_OUT_0(ISPx->msgSPI.msgSCK.msgGPIOPort, ISPx->msgSPI.msgSCK.msgGPIOBit);
		GPIO_OUT_0(ISPx->msgSPI.msgCS.msgGPIOPort, ISPx->msgSPI.msgCS.msgGPIOBit);
		if (ISPx->msgFuncDelay != NULL)
		{
			ISPx->msgFuncDelay(1);
		}
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ExitProg(ISP_HandlerType *ISPx)
{
	ISP_DeInit(ISPx);

	//---�ָ�ʱ�ӵ��ٶ�
	ISPx->msgSetClok = ISP_SCK_MAX_CLOCK;

	//---���64K������
	ISPx->msgHideAddr = 0xFF;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadReady(ISP_HandlerType *ISPx)
{
	UINT8_T _return = 0;

	//---��ȡʱ���ǩ
	UINT32_T nowTime = 0;
	if (ISPx->msgSPI.msgFuncTick != NULL)
	{
		nowTime = ISPx->msgSPI.msgFuncTick();
	}

	//---��ѯæ��־λ
	while (1)
	{
		//---���Ͷ�ȡæ��־������
		_return = ISP_SEND_CMD(ISPx, 0xF0, 0x00, 0x00, 0x00);

		//---����Ƿ��ȡ��æ��־
		if (_return)
		{
			break;
		}
		else
		{
			if ((ISPx->msgReadData[3] & 0x01) == 0x00)
			{
				_return = OK_0;
				break;
			}
			else
			{
				if (ISPx->msgSPI.msgFuncTick != NULL)
				{
					if ((ISPx->msgSPI.msgFuncTick() - nowTime) > 100)
					{
						//---���ͷ�����ʱ����
						_return = ERROR_2;
						break;
					}
				}
				else
				{
					nowTime++;
					if (nowTime > 100000)
					{
						//---���ͷ�����ʱ����
						_return = ERROR_3;
						break;
					}
				}
			}
		}
		WDT_RESET();
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
UINT8_T ISP_EraseChip(ISP_HandlerType *ISPx)
{
	UINT8_T _return = 0;

	//---���Ͳ�������
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0x80, 0x00, 0x00);
	if (_return == 0)
	{
		//---����֮��ĵȴ���ʱ
		ISPx->msgFuncDelay(10 + ISPx->msgDelay);
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
UINT8_T ISP_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	for (i = 0; i < 3; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0x30, 0x00, i, 0x0);
		if (_return != 0)
		{
			_return = (i + 2);
			break;
		}
		pVal[i] = ISPx->msgReadData[3];
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
UINT8_T ISP_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0x38, 0x00, i, 0x00);
		if (_return != 0)
		{
			_return = (i + 2);
			break;
		}
		pVal[i] = ISPx->msgReadData[3];
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
UINT8_T ISP_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = 0;

	//---��ȡ��˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0x50, 0x00, 0x00, 0x00);
	if (_return != 0x00)
	{
		return ERROR_2;
	}

	//---�����λֵ
	*(pVal++) = ISPx->msgReadData[3];

	//---��ȡ��˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0x58, 0x08, 0x00, 0x00);
	if (_return != 0x00)
	{
		return ERROR_3;
	}

	//---�����λֵ
	*(pVal++) = ISPx->msgReadData[3];

	//---��ȡ��˿λ��չλ
	if (isNeedExternFuse != 0x00)
	{
		//---��ȡ��˿����չλֵ
		_return = ISP_SEND_CMD(ISPx, 0x50, 0x08, 0x00, 0x00);

		//---������չλֵ
		*(pVal) = ISPx->msgReadData[3];
	}
	else
	{
		*pVal = 0xFF;
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
UINT8_T ISP_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	//---��ȡ����λ
	UINT8_T _return = ISP_SEND_CMD(ISPx, 0x58, 0x00, 0x00, 0x00);
	*(pVal) = ISPx->msgReadData[3];
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;

	//---�ж����ݳ����Ƿ���ż��
	if ((length & 0x01) != 0)
	{
		return ERROR_2;
	}

	//---����λ���㵱����2����
	length >>= 1;
	for (i = 0; i < length; i++)
	{
		//---ROMҳ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x30, 0x00, (addr + i), 0x00);
		if (_return != 0)
		{
			return ERROR_3;
		}
		else
		{
			*(pVal++) = ISPx->msgReadData[3];
		}

		//---ROMҳ���ֽ�����
		_return = ISP_SEND_CMD(ISPx, 0x38, 0x00, (addr + i), 0x00);
		if (_return != 0)
		{
			return 4;
		}
		else
		{
			*(pVal++) = ISPx->msgReadData[3];
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
UINT8_T ISP_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse)
{
	UINT8_T _return = 0;

	//---д����˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA0, 0x00, pVal[0]);
	if (_return != 0x00)
	{
		return ERROR_2;
	}

	//---д��֮����ʱ�ȴ�
	if (ISPx->msgFuncDelay != NULL)
	{
		ISPx->msgFuncDelay(6 + ISPx->msgDelay);
	}

	//---�����λֵ
	*(pVal++) = ISPx->msgReadData[3];

	//---��ȡ��˿λ��λ
	//---д����˿λ��λ
	_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA8, 0x00, pVal[1]);
	if (_return != 0x00)
	{
		return ERROR_3;
	}

	//---д��֮����ʱ�ȴ�
	if (ISPx->msgFuncDelay != NULL)
	{
		ISPx->msgFuncDelay(6 + ISPx->msgDelay);
	}

	//---д����˿λ��չλ
	if (isNeedExternFuse != 0x00)
	{
		//---д����չλ
		_return = ISP_SEND_CMD(ISPx, 0xAC, 0xA4, 0x00, pVal[2]);

		//---�ж�д���Ƿ�ɹ�
		if (_return == OK_0)
		{
			//---д��֮����ʱ�ȴ�
			if (ISPx->msgFuncDelay != NULL)
			{
				ISPx->msgFuncDelay(6 + ISPx->msgDelay);
			}
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
UINT8_T ISP_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal)
{
	//---д�����λ
	UINT8_T _return = ISP_SEND_CMD(ISPx, 0xAC, 0xE0, 0x00, pVal[0]);

	//---�ж�д���Ƿ�ɹ�
	if (_return == OK_0)
	{
		//---д��֮����ʱ�ȴ�
		if (ISPx->msgFuncDelay != NULL)
		{
			ISPx->msgFuncDelay(6 + ISPx->msgDelay);
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
UINT8_T ISP_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0xA0, highAddr, lowAddr, 0x00);
		if (_return != OK_0)
		{
			break;
		}

		//---�����ȡ������
		*(pVal++) = ISPx->msgReadData[3];

		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
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
UINT8_T ISP_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_ReadChipEepromAddr(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		_return = ISP_SEND_CMD(ISPx, 0xC0, highAddr, lowAddr, pVal[i]);
		if (_return != OK_0)
		{
			break;
		}

		//---д��֮����ʱ�ȴ�
		if (ISPx->msgFuncDelay != NULL)
		{
			ISPx->msgFuncDelay(5 + ISPx->msgDelay);
		}

		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
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
UINT8_T ISP_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromAddr(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������д��������ǿ����ݣ���ô������д��
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;
	for (i = 0; i < length; i++)
	{
		if (pVal[i] != 0xFF)
		{
			_return = ISP_SEND_CMD(ISPx, 0xC0, highAddr, lowAddr, pVal[i]);
			if (_return != OK_0)
			{
				break;
			}

			//---д��֮����ʱ�ȴ�
			if (ISPx->msgFuncDelay != NULL)
			{
				ISPx->msgFuncDelay(5 + ISPx->msgDelay);
			}
		}

		//---��ַƫ��
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
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
UINT8_T ISP_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length)
{
	return ISP_WriteChipEepromAddrWithJumpEmpty(ISPx, pVal, (UINT8_T)(addr >> 8), (UINT8_T)(addr & 0xFF), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateExternAddr(ISP_HandlerType *ISPx, UINT8_T addr)
{
	UINT8_T _return = OK_0;
	if (ISPx->msgHideAddr != addr)
	{
		ISPx->msgHideAddr = addr;
		_return = ISP_SEND_CMD(ISPx, 0x4D, 0x00, addr, 0x00);
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
UINT8_T ISP_UpdateExternLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISP_UpdateExternAddr(ISPx, (UINT8_T)(addr >> 16));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length)
{
	UINT8_T _return = OK_0;
	UINT16_T i = 0;

	//---�ж����ݳ����Ƿ�Ϊż��
	if ((length & 0x01) != 0)
	{
		return ERROR_2;
	}

	//---����λ���㵱����2����
	length >>= 1;

	//---������չλ
	_return = ISP_UpdateExternAddr(ISPx, externAddr);
	if (_return != OK_0)
	{
		return ERROR_3;
	}
	for (i = 0; i < length; i++)
	{
		//---��ȡ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x20, highAddr, lowAddr, 0x00);
		if (_return != OK_0)
		{
			return ERROR_4;
		}
		else
		{
			*(pVal++) = ISPx->msgReadData[3];
		}

		//---��ȡ��λ����
		_return = ISP_SEND_CMD(ISPx, 0x28, highAddr, lowAddr, 0x00);
		if (_return != 0x00)
		{
			return ERROR_5;
		}
		else
		{
			*(pVal++) = ISPx->msgReadData[3];
		}
		lowAddr++;
		if (lowAddr == 0x00)
		{
			highAddr++;
			if (highAddr == 0x00)
			{
				externAddr++;

				//---������չλ
				_return = ISP_UpdateExternAddr(ISPx, externAddr);
				if (_return != 0x00)
				{
					return ERROR_6;
				}
			}
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
UINT8_T ISP_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length)
{
	return  ISP_ReadChipFlashAddr(ISPx, pVal, (UINT8_T)(addr >> 16), (UINT8_T)(addr >> 8), (UINT8_T)(addr), length);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T ISP_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length)
{
	UINT8_T _return = 0;
	UINT8_T i = 0;

	//---�ж����ݳ����Ƿ�Ϊż��
	if ((length & 0x01) != 0x00)
	{
		return ERROR_2;
	}

	//---����λ���㵱����2����
	length >>= 1;
	for (i = 0; i < length; i++)
	{
		//---���µ�λ��ַ�Ļ�����
		_return = ISP_SEND_CMD(ISPx, 0x40, 0x00, (index + i), *(pVal++));
		if (_return != 0x00)
		{
			return ERROR_3;
		}

		//---���¸�λ��ַ�Ļ�����
		_return = ISP_SEND_CMD(ISPx, 0x48, 0x00, (index + i), *(pVal++));
		if (_return != 0x00)
		{
			return ERROR_4;
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
UINT8_T ISP_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr)
{
	UINT8_T _return = ISP_UpdateExternAddr(ISPx, externAddr);
	if (_return == OK_0)
	{
		_return = ISP_SEND_CMD(ISPx, 0x4C, highAddr, lowAddr, 0x00);
		if (_return == OK_0)
		{
			//---д��֮����ʱ�ȴ�
			if (ISPx->msgFuncDelay != NULL)
			{
				ISPx->msgFuncDelay(5 + ISPx->msgDelay);
			}
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
UINT8_T ISP_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr)
{
	return ISP_UpdateChipFlashAddr(ISPx, (UINT8_T)(addr >> 16), (UINT8_T)(addr >> 8), (UINT8_T)(addr));
}