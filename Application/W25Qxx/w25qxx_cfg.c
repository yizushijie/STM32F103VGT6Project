#include "w25qxx_cfg.h"

//===ȫ�ֱ����Ķ���
W25QXX_HandlerType  g_W25QXXDevice0;
pW25QXX_HandlerType pW25QXXDevice0 = &g_W25QXXDevice0;

//===ͳһ���ͺ���
UINT8_T(*W25QXX_SEND_CMD)(W25QXX_HandlerType *, UINT8_T, UINT8_T *);

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Device0_Init(W25QXX_HandlerType *W25QXXx)
{
	//---CS
	W25QXXx->msgSPI.msgCS.msgGPIOPort = GPIOA;
	W25QXXx->msgSPI.msgCS.msgGPIOBit = LL_GPIO_PIN_4;

	//---SCK
	W25QXXx->msgSPI.msgSCK.msgGPIOPort = GPIOA;
	W25QXXx->msgSPI.msgSCK.msgGPIOBit = LL_GPIO_PIN_5;

	//---MISO
	W25QXXx->msgSPI.msgMISO.msgGPIOPort = GPIOA;
	W25QXXx->msgSPI.msgMISO.msgGPIOBit = LL_GPIO_PIN_6;

	//---MOSI
	W25QXXx->msgSPI.msgMOSI.msgGPIOPort = GPIOA;
	W25QXXx->msgSPI.msgMOSI.msgGPIOBit = LL_GPIO_PIN_7;

	//---����ģʽ
	#ifndef USE_MCU_STM32F1
	W25QXXx->msgSPI.msgGPIOAlternate = LL_GPIO_AF_5;
	#endif

	//---SPI���
	W25QXXx->msgSPI.msgSPIx = SPI1;
	#ifndef USE_MCU_STM32F1

	//---SPI��Э��
	W25QXXx->msgSPI.msgStandard = LL_SPI_PROTOCOL_MOTOROLA;
	#endif

	//---����������
	W25QXXx->msgSPI.msgPluseWidth = 2;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Device1_Init(W25QXX_HandlerType *W25QXXx)
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
UINT8_T W25QXX_SPI_Device2_Init(W25QXX_HandlerType *W25QXXx)
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
UINT8_T W25QXX_SPI_HW_Init(W25QXX_HandlerType *W25QXXx)
{
	//---ע����ǰ����������
	SPITask_DeInit(&(W25QXXx->msgSPI));

	//---Ӳ���˿ڵ�����---Ӳ��ʵ��
	SPITask_MHW_GPIO_Init(&(W25QXXx->msgSPI));

	//---Ӳ��SPI�ĳ�ʼ��
	LL_SPI_InitTypeDef SPI_InitStruct;

	//---SPI��ģʽ����
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_MASTER;						//---����ģʽ
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;				//---8λ����
	SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_HIGH;				//---CLK����ʱΪ�ߵ�ƽ (CLK������ֻ���ǵ͵�ƽ)

	//---Ĭ�϶˿�Ϊ����ߵ�ƽ
	if (SPI_InitStruct.ClockPolarity == LL_SPI_POLARITY_LOW)
	{
		GPIO_OUT_0(W25QXXx->msgSPI.msgSCK.msgGPIOPort, W25QXXx->msgSPI.msgSCK.msgGPIOBit);
		GPIO_OUT_0(W25QXXx->msgSPI.msgMOSI.msgGPIOPort, W25QXXx->msgSPI.msgMOSI.msgGPIOBit);
		GPIO_OUT_0(W25QXXx->msgSPI.msgMISO.msgGPIOPort, W25QXXx->msgSPI.msgMISO.msgGPIOBit);
	}
	SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;							//---�������
	SPI_InitStruct.BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV256;		//---ϵͳʱ��256��Ƶ
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;						//---��λ��ǰ
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;	//---Ӳ��CRC��ʹ��
	SPI_InitStruct.CRCPoly = 7;

	//---��ʼ����ѯ��ʽ��SPI
	SPITask_MHW_PollMode_Init(&(W25QXXx->msgSPI), SPI_InitStruct);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_SW_Init(W25QXX_HandlerType *W25QXXx)
{
	SPITask_DeInit(&(W25QXXx->msgSPI));

	//---Ӳ���˿ڵ�����---���ʵ��
	SPITask_MSW_GPIO_Init(&(W25QXXx->msgSPI));
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_HW_SendCmd(W25QXX_HandlerType *W25QXXx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MHW_PollMode_WriteByte(&(W25QXXx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_SW_SendCmd(W25QXX_HandlerType *W25QXXx, UINT8_T cmd, UINT8_T *pRVal)
{
	//---���ݷ���
	return SPITask_MSW_WriteByteMSB(&(W25QXXx->msgSPI), cmd, pRVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_Init(W25QXX_HandlerType *W25QXXx, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay), UINT32_T(*pTimerTick)(void), UINT8_T isHW)
{
	//---ʹ�õ�DHT11�Ķ˿�
	if ((W25QXXx != NULL) && (W25QXXx == W25QXX_TASK_ONE))
	{
		W25QXX_SPI_Device0_Init(W25QXXx);
	}
	else if ((W25QXXx != NULL) && (W25QXXx == W25QXX_TASK_TWO))
	{
		W25QXX_SPI_Device1_Init(W25QXXx);
	}
	else if ((W25QXXx != NULL) && (W25QXXx == W25QXX_TASK_THREE))
	{
		W25QXX_SPI_Device2_Init(W25QXXx);
	}
	else
	{
		return ERROR_1;
	}

	//---�жϳ�ʼ���ķ�ʽ
	if (isHW != 0)
	{
		W25QXXx->msgSPI.msgModelIsHW = 1;
		W25QXX_SPI_HW_Init(W25QXXx);

		//---�����д
		W25QXX_SEND_CMD = W25QXX_SPI_HW_SendCmd;
	}
	else
	{
		W25QXXx->msgSPI.msgModelIsHW = 0;
		W25QXX_SPI_SW_Init(W25QXXx);

		//---�����д
		W25QXX_SEND_CMD = W25QXX_SPI_SW_SendCmd;
	}

	//---ע��ms����ʱ����
	W25QXXx->msgFuncDelay = Delayms;

	//---ע��us��ʱ����
	W25QXXx->msgSPI.msgFuncDelay = Delayus;

	//---ע��δ���
	W25QXXx->msgSPI.msgFuncTick = pTimerTick;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡ״̬�Ĵ���1
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_ReadRegSR1(W25QXX_HandlerType *W25QXXx)
{
	UINT8_T _return = 0;
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_READ_REG_SR1, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &_return);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��ȡ״̬�Ĵ���2
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_ReadRegSR2(W25QXX_HandlerType *W25QXXx)
{
	UINT8_T _return = 0;
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_READ_REG_SR2, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &_return);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� д��״̬�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WriteRegSR1(W25QXX_HandlerType *W25QXXx, UINT8_T cmd)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_WRITE_REG_SR, NULL);
	W25QXX_SEND_CMD(W25QXXx, cmd, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� д��״̬�Ĵ���
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WriteRegSR2(W25QXX_HandlerType *W25QXXx, UINT8_T cmd)
{
	//---��ȡSR1��ֵ
	UINT8_T _return = W25QXX_SPI_ReadRegSR1(W25QXXx);
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_WRITE_REG_SR, NULL);

	//---дSR1
	W25QXX_SEND_CMD(W25QXXx, _return, NULL);

	//---дSR2
	W25QXX_SEND_CMD(W25QXXx, cmd, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� дʹ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EnableWrite(W25QXX_HandlerType *W25QXXx)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_ENABLE_WRITE, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� д����ʹ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_DisableWrite(W25QXX_HandlerType *W25QXXx)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_DISABLE_WRITE, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�  ��ȡоƬID
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T W25QXX_SPI_ReadID(W25QXX_HandlerType *W25QXXx)
{
	UINT8_T temp = 0;
	UINT16_T  _return = 0;
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡID����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_MANUFACT_DEVICE_ID, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0x00, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0x00, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0x00, NULL);

	//---��ȡ�豸��ID��Ϣ��λֵ
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &temp);
	_return = temp;

	//---��ȡ�豸��ID��Ϣ��λֵ
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &temp);
	_return = (_return << 8) + temp;
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T W25QXX_SPI_WaitBusy(W25QXX_HandlerType *W25QXXx)
{
	//---��ȡ״̬�Ĵ���
	UINT8_T _return = W25QXX_SPI_ReadRegSR1(W25QXXx);
	UINT32_T nowTime = 0;

	//---��ȡ��ǰʱ�����
	if (W25QXXx->msgSPI.msgFuncTick != NULL)
	{
		nowTime = W25QXXx->msgSPI.msgFuncTick();
	}

	//---�ȴ�BUSYλ���
	while ((_return & 0x01) == 0x01)
	{
		_return = W25QXX_SPI_ReadRegSR1(W25QXXx);
		if (W25QXXx->msgSPI.msgFuncTick != NULL)
		{
			if ((W25QXXx->msgSPI.msgFuncTick() - nowTime) > 100)
			{
				//---���ͷ�����ʱ����
				return ERROR_1;
			}
		}
		else
		{
			nowTime++;
			if (nowTime > 100000)
			{
				//---���ͷ�����ʱ����
				return ERROR_2;
			}
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
void W25QXX_SPI_ReadData(W25QXX_HandlerType *W25QXXx, UINT32_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;

	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//----���Ͷ�ȡ����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_READ_DATA, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(addr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(addr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(addr), NULL);

	//---ѭ����ȡ����
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[i]);
	}

	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadFast(W25QXX_HandlerType *W25QXXx, UINT32_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;

	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//----���Ͷ�ȡ����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_READ_FAST, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(addr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(addr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(addr), NULL);

	//---����α�ֽ�
	W25QXX_SEND_CMD(W25QXXx, 0xFF, NULL);

	//---ѭ����ȡ����
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[i]);
	}

	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� дҳ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WritePage(W25QXX_HandlerType *W25QXXx, UINT32_T addr, UINT8_T *pVal, UINT16_T length)
{
	UINT8_T pageIndex = 0;
	UINT16_T i = 0;
	UINT32_T pageAdddr = 0;

	//---�ж�Ҳ���ݵĸ����������256���ֽ�
	if (length > W25QXX_PAGE_BYTE_SIZE)
	{
		length = W25QXX_PAGE_BYTE_SIZE;
	}

	//---У��ҳ��ַ
	pageAdddr = (addr & W25QXX_PAGE_NUM_MASK);

	//---У��ҳ���
	pageIndex = (UINT8_T)(addr & W25QXX_PAGE_BYTE_MASK);

	//---����WEL
	W25QXX_SPI_EnableWrite(W25QXXx);

	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//----����дҳ����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_PAGE_PROGRAM, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(pageAdddr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(pageAdddr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(pageAdddr), NULL);

	//---ѭ��д������
	for (i = pageIndex; i < length; i++)
	{
		W25QXX_SEND_CMD(W25QXXx, pVal[i - pageIndex], NULL);
	}

	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---�ȴ�д�����
	W25QXX_SPI_WaitBusy(W25QXXx);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ��������оƬ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseChip(W25QXX_HandlerType *W25QXXx)
{
	//---����WEL
	W25QXX_SPI_EnableWrite(W25QXXx);

	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25QXXx);
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---����Ƭ��������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_ERASE_CHIP, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25QXXx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����ָ������
//////�������:
//////�������:
//////˵		���������ĵ�ַ��0��511����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseSector(W25QXX_HandlerType *W25QXXx, UINT32_T sectorAddr)
{
	//---����
	sectorAddr <<= 16;

	//---����WEL
	W25QXX_SPI_EnableWrite(W25QXXx);

	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25QXXx);
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_ERASE_SECTOR, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(sectorAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(sectorAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(sectorAddr), NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25QXXx);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseBlock32KB(W25QXX_HandlerType *W25QXXx, UINT32_T blockAddr)
{
	//---����
	blockAddr <<= 7;

	//---����WEL
	W25QXX_SPI_EnableWrite(W25QXXx);

	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25QXXx);
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_ERASE_BLOCK_32KB, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(blockAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(blockAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(blockAddr), NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25QXXx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseBlock64KB(W25QXX_HandlerType *W25QXXx, UINT32_T blockAddr)
{
	//---����
	blockAddr <<= 8;

	//---����WEL
	W25QXX_SPI_EnableWrite(W25QXXx);

	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25QXXx);
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_ERASE_BLOCK_64KB, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(blockAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(blockAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(blockAddr), NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25QXXx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� �������ģʽ
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_PowerDown(W25QXX_HandlerType *W25QXXx)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---���͵�������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_POWER_DOWN, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---TDP
	Delay_us(3);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_WakeUp(W25QXX_HandlerType *W25QXXx)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---���ͻ�������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_RELEASE_POWER_DOWN, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---TRES1
	Delay_us(3);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadUniqueIDNumber(W25QXX_HandlerType *W25QXXx, UINT8_T *pVal)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡID����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_READ_UNIQUE_ID, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0x00, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0x00, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0x00, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0x00, NULL);

	//---��ȡ64Bit��UniqueSerialNumber
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[0]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[1]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[2]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[3]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[4]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[5]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[6]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[8]);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadJEDECID(W25QXX_HandlerType *W25QXXx, UINT8_T *pVal)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡID����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_JEDEC_ID, NULL);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[0]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[1]);
	W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[2]);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EraseSecurityReg(W25QXX_HandlerType *W25QXXx, UINT32_T regAddr)
{
	//---����WEL
	W25QXX_SPI_EnableWrite(W25QXXx);

	//---�ȴ�æ����
	W25QXX_SPI_WaitBusy(W25QXXx);
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//--���Ͷ�ȡ״̬�Ĵ���������
	W25QXX_SEND_CMD(W25QXXx, W25QXX_ERASE_SECURITY_REG, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr), NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---�ȴ���������
	W25QXX_SPI_WaitBusy(W25QXXx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ProgramSecurityReg(W25QXX_HandlerType *W25QXXx, UINT32_T regAddr, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;

	//---�ж�Ҳ���ݵĸ����������256���ֽ�
	if (length > W25QXX_PAGE_BYTE_SIZE)
	{
		length = W25QXX_PAGE_BYTE_SIZE;
	}

	//---����WEL
	W25QXX_SPI_EnableWrite(W25QXXx);

	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//----����дҳ����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_PROGRAM_SECURITY_REG, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr), NULL);

	//---ѭ��д������
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25QXXx, pVal[i], NULL);
	}

	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---�ȴ�д�����
	W25QXX_SPI_WaitBusy(W25QXXx);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_ReadSecurityReg(W25QXX_HandlerType *W25QXXx, UINT32_T regAddr, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;

	//--ʹ��Ƭѡ
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//----���Ͷ�ȡ����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_READ_SECURITY_REG, NULL);

	//----����24bit��ַ
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr >> 16), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr >> 8), NULL);
	W25QXX_SEND_CMD(W25QXXx, (UINT8_T)(regAddr), NULL);

	//---ѭ����ȡ����
	for (i = 0; i < length; i++)
	{
		W25QXX_SEND_CMD(W25QXXx, 0xFF, &pVal[i]);
	}

	//---ȡ��Ƭѡ
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_EnableReset(W25QXX_HandlerType *W25QXXx)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---����ʦ���ܹ���λ����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_ENABLE_RESET, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ� ����
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_Reset(W25QXX_HandlerType *W25QXXx)
{
	GPIO_OUT_0(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);

	//---����ʦ���ܹ���λ����
	W25QXX_SEND_CMD(W25QXXx, W25QXX_RESET, NULL);
	GPIO_OUT_1(W25QXXx->msgSPI.msgCS.msgGPIOPort, W25QXXx->msgSPI.msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ֻд�벻У�������Ƿ����д��Flash
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_OnlyWrite(W25QXX_HandlerType *W25QXXx, UINT32_T addr, UINT8_T* pVal, UINT16_T length)
{
	//---��ҳʣ����ֽ���
	UINT16_T pageByteNum = W25QXX_PAGE_BYTE_SIZE - (UINT8_T)(addr&W25QXX_PAGE_BYTE_MASK);
	if (length < pageByteNum)
	{
		//---������256���ֽ�
		pageByteNum = length;
	}

	//---ѭ��д������
	while (1)
	{
		W25QXX_SPI_WritePage(W25QXXx, addr, pVal, pageByteNum);
		if (length == pageByteNum)
		{
			//---д�������
			break;
		}
		else
		{
			pVal += pageByteNum;
			addr += pageByteNum;

			//---��ȥ�Ѿ�д���˵��ֽ���
			length -= pageByteNum;
			if (length > W25QXX_PAGE_BYTE_SIZE)
			{
				//---һ�ο���д��256���ֽ�
				pageByteNum = W25QXX_PAGE_BYTE_SIZE;
			}
			else
			{
				//---����256���ֽ���
				pageByteNum = length;
			}
		}
	};
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void W25QXX_SPI_CheckWrite(W25QXX_HandlerType *W25QXXx, UINT32_T addr, UINT8_T* pVal, UINT16_T length)
{
	UINT32_T secpos = 0;
	UINT16_T secoff = 0;
	UINT16_T secremain = 0;
	UINT16_T i = 0;

	//---������ַ
	secpos = addr & W25QXX_SECTOR_NUM_MASK;

	//---�������ڵ�ƫ��
	secoff = addr & W25QXX_SECTOR_BYTE_MASK;

	//---����ʣ��ռ��С
	secremain = W25QXX_SECTOR_BYTE_SIZE - secoff;

	if (length <= secremain)
	{
		//---������4096���ֽ�
		secremain = length;
	}

	//---ѭ��д������
	while (1)
	{
		//---������������������
		W25QXX_SPI_ReadData(W25QXXx, secpos * W25QXX_SECTOR_BYTE_SIZE, W25QXXx->msgBuffer, W25QXX_SECTOR_BYTE_SIZE);

		//---У������
		for (i = 0; i < secremain; i++)
		{
			if (W25QXXx->msgBuffer[secoff + i] != 0XFF)
			{
				//---��Ҫ����
				break;
			}
		}

		//---�ж��Ƿ���Ҫ����
		if (i < secremain)
		{
			//---�����������
			W25QXX_SPI_EraseSector(W25QXXx, secpos);

			//---����
			for (i = 0; i < secremain; i++)
			{
				W25QXXx->msgBuffer[i + secoff] = pVal[i];
			}

			//---д����������
			W25QXX_SPI_OnlyWrite(W25QXXx, secpos * W25QXX_SECTOR_BYTE_SIZE, W25QXXx->msgBuffer, W25QXX_SECTOR_BYTE_SIZE);
		}
		else
		{
			//---д�Ѿ������˵�,ֱ��д������ʣ������.
			W25QXX_SPI_OnlyWrite(W25QXXx, addr, pVal, secremain);
		}

		//---�ж��Ƿ�д�����
		if (length == secremain)
		{
			//---д�������
			break;
		}
		else
		{
			//---д��δ����
			//---������ַ��1
			secpos++;

			//---ƫ��λ��Ϊ0
			secoff = 0;

			//---ָ��ƫ��
			pVal += secremain;

			//---д��ַƫ��
			addr += secremain;

			//---�ֽ����ݼ�
			length -= secremain;

			//---�ж���һ�������Ƿ��ܹ�д��
			if (length > W25QXX_SECTOR_BYTE_SIZE)
			{
				//---��һ����������д����
				secremain = 4096;
			}
			else
			{
				//---��һ����������д����
				secremain = length;
			}
		}
	};
}