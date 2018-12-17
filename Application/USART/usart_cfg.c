#include "usart_cfg.h"

//===ȫ�ֱ�������
USART_HandlerType  g_USART1;
pUSART_HandlerType pUSART1 = &g_USART1;

#ifdef USE_USART_PRINTF

//===printf����ʹ�õĻ�����
char printfBuffer[USART_PRINTF_SIZE] = { 0 };
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_StructInit(USART_HandlerType*  USARTx)
{
	//---���ڵ����ݴ�������
	USARTx->msgIndex = 0;
	USARTx->msgRxID = 0;
	USARTx->msgTxID = 0;
	USARTx->msgID = 0;
	USARTx->msgIDIndex = 0;
	USARTx->msgCmdIndex = 0;
	USARTx->msgDataOneIndex = 0;
	USARTx->msgDataTwoIndex = 0;
	USARTx->msgTxBit = 0;
	USARTx->msgTxPort = NULL;
	USARTx->msg485Bit = 0;
	USARTx->msg485Port = NULL;
	USARTx->msgUSART = NULL;

	//---���ջ�����
	USARTx->msgRxHandler.msgCheckSum = 0;
	USARTx->msgRxHandler.msgCRCFlag = 0;
	USARTx->msgRxHandler.msgStep = 0;
	USARTx->msgRxHandler.msgIndexW = 0;
	USARTx->msgRxHandler.msgIndexR = 0;
	USARTx->msgRxHandler.msgCount = 0;
	USARTx->msgRxHandler.msgSize = 0;
	USARTx->msgRxHandler.msgTaskState = USART_BUSY;
	USARTx->msgRxHandler.msgOverFlow = 0;
	USARTx->msgRxHandler.msgNowTime = 0;
	USARTx->msgRxHandler.msgEndTime = 0;
	USARTx->msgRxHandler.msgMaxTime = 0;
	USARTx->msgRxHandler.pMsgVal = NULL;

	//---���ͻ�����
	USARTx->msgTxHandler.msgCheckSum = 0;
	USARTx->msgTxHandler.msgCRCFlag = 0;
	USARTx->msgTxHandler.msgStep = 0;
	USARTx->msgTxHandler.msgIndexW = 0;
	USARTx->msgTxHandler.msgIndexR = 0;
	USARTx->msgTxHandler.msgCount = 0;
	USARTx->msgTxHandler.msgSize = 0;
	USARTx->msgTxHandler.msgTaskState = USART_OK;
	USARTx->msgTxHandler.msgOverFlow = 0;
	USARTx->msgTxHandler.msgNowTime = 0;
	USARTx->msgTxHandler.msgEndTime = 0;
	USARTx->msgTxHandler.msgMaxTime = 0;
	USARTx->msgTxHandler.pMsgVal = NULL;

	//---������
	USARTx->msgFuncTick = NULL;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void))
{
	USART_StructInit(USARTx);

	USARTx->msgRxHandler.msgCRCFlag = rxCRCFlag;
	USARTx->msgRxHandler.msgSize = rxSize;
	USARTx->msgRxHandler.pMsgVal = pRxVal;

	USARTx->msgTxHandler.msgCRCFlag = txCRCFlag;
	USARTx->msgTxHandler.msgSize = txSize;
	USARTx->msgTxHandler.pMsgVal = pTxVal;

	//---ע���������
	USARTx->msgFuncTick = pTimerTick;

	//---�˿ڳ�ʼ��
	if ((USARTx != NULL) && (USARTx == USART_TASK_ONE))
	{
		USART1_Init(USARTx);
	}
	else if ((USARTx != NULL) && (USARTx == USART_TASK_TWO))
	{
		USART2_Init(USARTx);
	}
	else if ((USARTx != NULL) && (USARTx == USART_TASK_THREE))
	{
		USART3_Init(USARTx);
	}
	else
	{
		return ERROR_2;
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
UINT8_T  USART_GPIOInit(USART_HandlerType*  USARTx, UINT8_T isInput)
{
	#ifdef USART_INIT_GPIO
	if (USARTx->msgTxPort != NULL)
	{
		if (isInput == USART_TXGPIO_SET_OUTPUT)
		{
			LL_GPIO_SetPinMode(USARTx->msgTxPort, USARTx->msgTxBit, LL_GPIO_MODE_ALTERNATE);
		}
		else
		{
			LL_GPIO_SetPinMode(USARTx->msgTxPort, USARTx->msgTxBit, LL_GPIO_MODE_INPUT);
		}
	}
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
UINT8_T  USART_485GPIOInit(USART_HandlerType*  USARTx, UINT8_T isEnable)
{
	if (USARTx->msg485Port != NULL)
	{
		if (isEnable == USART_485_TX_ENABLE)
		{
			GPIO_OUT_0(USARTx->msg485Port, USARTx->msg485Bit);
		}
		else
		{
			GPIO_OUT_1(USARTx->msg485Port, USARTx->msg485Bit);
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
UINT8_T USART_EnableCRC_RX(USART_HandlerType*USARTx, UINT8_T crcFlag)
{
	USARTx->msgRxHandler.msgCRCFlag = crcFlag;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetCRC_RX(USART_HandlerType*USARTx)
{
	return  USARTx->msgRxHandler.msgCRCFlag;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_EnableCRC_TX(USART_HandlerType*USARTx, UINT8_T crcFlag)
{
	USARTx->msgTxHandler.msgCRCFlag = crcFlag;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetCRC_TX(USART_HandlerType*USARTx)
{
	return  USARTx->msgTxHandler.msgCRCFlag;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_TimeTick_Init(USART_HandlerType*USARTx, UINT8_T isRx)
{
	UINT32_T temp = 0;

	//---��ȡ��ǰʱ��
	if (USARTx->msgFuncTick != NULL)
	{
		temp = USARTx->msgFuncTick();
	}

	//---ʱ��ڵ�
	if (isRx)
	{
		USARTx->msgRxHandler.msgNowTime = temp;

		//---ͬ��ʱ��
		USARTx->msgRxHandler.msgEndTime = USARTx->msgRxHandler.msgNowTime;
	}
	else
	{
		USARTx->msgTxHandler.msgNowTime = temp;

		//---ͬ��ʱ��
		USARTx->msgTxHandler.msgEndTime = USARTx->msgTxHandler.msgNowTime;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�ע����ʱ������
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_TimeTick_DeInit(USART_HandlerType*USARTx, UINT8_T isRx)
{
	if (isRx)
	{
		//---���������־λ
		USARTx->msgRxHandler.msgOverFlow = 0;

		//---���㵱ǰʱ��
		USARTx->msgRxHandler.msgEndTime = 0;

		//---ͬ��ʱ��
		USARTx->msgRxHandler.msgNowTime = USARTx->msgRxHandler.msgEndTime;
	}
	else
	{
		//---���������־λ
		USARTx->msgTxHandler.msgOverFlow = 0;

		//---���㵱ǰʱ��
		USARTx->msgTxHandler.msgEndTime = 0;

		//---ͬ��ʱ��
		USARTx->msgTxHandler.msgNowTime = USARTx->msgTxHandler.msgEndTime;
	}
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ʱ������Ƿ�����ʱ
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_TimeTick_OVF(USART_HandlerType*USARTx, UINT32_T timeOut, UINT8_T isRx)
{
	UINT32_T temp = 0;

	//---��ȡ��ǰʱ��
	if (USARTx->msgFuncTick != NULL)
	{
		temp = USARTx->msgFuncTick() + 2;
	}

	//---ʱ��ڵ�
	if (isRx)
	{
		//---��ȡ��ǰʱ��
		USARTx->msgRxHandler.msgEndTime = temp;

		//---�ж��Ƿ�����ʱ����
		if (USARTx->msgRxHandler.msgEndTime > USARTx->msgRxHandler.msgNowTime)
		{
			//---��ʱ��δ�����������
			if ((USARTx->msgRxHandler.msgEndTime - USARTx->msgRxHandler.msgNowTime) > timeOut)
			{
				USARTx->msgRxHandler.msgOverFlow = 1;
				return ERROR_1;
			}
		}
		else if (USARTx->msgRxHandler.msgEndTime < USARTx->msgRxHandler.msgNowTime)
		{
			//---��ʱ�������������
			if ((0xFFFFFFFF - USARTx->msgRxHandler.msgNowTime + USARTx->msgRxHandler.msgEndTime) > timeOut)
			{
				USARTx->msgRxHandler.msgOverFlow = 1;
				return ERROR_1;
			}
		}
	}
	else
	{
		//---��ȡ��ǰʱ��
		USARTx->msgTxHandler.msgEndTime = temp;

		//---�ж��Ƿ�����ʱ����
		if (USARTx->msgTxHandler.msgEndTime > USARTx->msgTxHandler.msgNowTime)
		{
			//---��ʱ��δ�����������
			if ((USARTx->msgTxHandler.msgEndTime - USARTx->msgTxHandler.msgNowTime) > timeOut)
			{
				USARTx->msgTxHandler.msgOverFlow = 1;
				return ERROR_1;
			}
		}
		else if (USARTx->msgTxHandler.msgEndTime < USARTx->msgTxHandler.msgNowTime)
		{
			//---��ʱ�������������
			if ((0xFFFFFFFF - USARTx->msgTxHandler.msgNowTime + USARTx->msgTxHandler.msgEndTime) > timeOut)
			{
				USARTx->msgTxHandler.msgOverFlow = 1;
				return ERROR_1;
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
UINT8_T  USART_TimeOVFTask(USART_HandlerType*USARTx, UINT8_T isRx)
{
	UINT8_T _return = OK_0;

	//---�ж��ǽ��ջ��Ƿ���
	if (isRx != 0)
	{
		if ((USARTx->msgRxHandler.msgNowTime != 0) && (USARTx->msgRxHandler.msgMaxTime != 0))
		{
			if (USARTx->msgRxHandler.msgNowTime == 0)
			{
				return OK_0;
			}

			//---��ȡ��ʱֵ
			_return = USART_TimeTick_OVF(USARTx, USARTx->msgRxHandler.msgMaxTime, 1);

			//---��ʱ�����ж�
			//if ((_return != OK_0) && (USARTx->msgRxHandler.msgNowTime != 0))
			if ((_return != OK_0))
			{
				//---��ӡ��ʱ�Ĵ�����Ϣ
				USART_Printf(USARTx, "=>>���մ���%d������ʱ����!<<=\r\n", (USARTx->msgIndex - 1));

				//---��λ�������ݻ�����
				USART_ReadInit(USARTx);
			}
		}
	}
	else
	{
		if ((USARTx->msgTxHandler.msgNowTime != 0) && (USARTx->msgTxHandler.msgMaxTime != 0))
		{
			if (USARTx->msgTxHandler.msgNowTime == 0)
			{
				return OK_0;
			}

			//---��ȡ��ʱֵ
			_return = USART_TimeTick_OVF(USARTx, USARTx->msgTxHandler.msgMaxTime, 0);

			//---��ʱ�����жϣ�����ĳЩ״̬�µ�ǰ��¼��ʱ��ֵ�ڸ�дΪ���ʱ��ʱ���¼��û�з���ͬ������
			if ((_return != OK_0) && (USARTx->msgTxHandler.msgNowTime != 0))
			{
				//---��ӡ��ʱ�Ĵ�����Ϣ
				USART_Printf(USARTx, "=>>���ʹ���%d������ʱ����!<<=\r\n", (USARTx->msgIndex - 1));

				//---��λ�������ݻ�����
				USART_WriteInit(USARTx);
			}
			else
			{
				USARTx->msgTxHandler.msgOverFlow = 0;
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
//////˵		���� ���ܵ�������󳤶�ʹ��1�ֽڱ�ʾ
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITRead_8BitsTask(USART_HandlerType*USARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;

	//---���ݽ��ղ���
	switch (USARTx->msgRxHandler.msgStep)
	{
		//---�������ݵı�ͷ
		case 0:
			if (USARTx->msgRxHandler.msgIndexR == 0)
			{
				if (USARTx->msgRxID == tempVal)
				{
					USARTx->msgRxHandler.pMsgVal[0] = tempVal;
					USARTx->msgRxHandler.msgStep = 1;

					//---��¼���ݵĸ���
					USARTx->msgRxHandler.msgCount = 1;

					//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
					USART_TimeTick_Init(USARTx, 1);

					//---���㳬ʱ��־
					USART_ClearOVF(USARTx, 1);
				}
			}
			break;

			//---�������ݵĳ���
		case 1:
			if ((tempVal > 0) && (tempVal < (UINT8_T)(USARTx->msgRxHandler.msgSize & 0xFF)))
			{
				USARTx->msgRxHandler.pMsgVal[1] = tempVal;

				//---��ȡ���ݵĽ��ճ���
				USARTx->msgRxHandler.msgIndexW = tempVal;

				//---��¼���ݵĸ���
				USARTx->msgRxHandler.msgCount += 1;

				//---��һ����
				USARTx->msgRxHandler.msgStep = 2;
			}
			else
			{
				USARTx->msgRxHandler.msgStep = 0;
			}

			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);
			break;

			//---����������Ϣ
		case 2:
			USARTx->msgRxHandler.pMsgVal[USARTx->msgRxHandler.msgIndexR + 2] = tempVal;
			USARTx->msgRxHandler.msgIndexR++;

			//---��¼���ݵĸ���
			USARTx->msgRxHandler.msgCount += 1;

			//---�ж��Ƿ����
			if (USARTx->msgRxHandler.msgIndexR >= USARTx->msgRxHandler.msgSize)
			{
				USARTx->msgRxHandler.msgIndexR = 0;
			}

			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);

			//---�ж��Ƿ�������
			if (USARTx->msgRxHandler.msgIndexR >= USARTx->msgRxHandler.msgIndexW)
			{
				USARTx->msgRxHandler.msgStep = 3;
				USARTx->msgRxHandler.msgTaskState = USART_OK;

				//---���㳬ʱ������
				//USART_TimeTick_DeInit(USARTx, 1);
			}
			break;
		case 3:

			//---���㳬ʱ������
			//USART_TimeTick_DeInit(USARTx,1);
			break;
		default:

			//USARTx->msgRxHandler.msgNowTime = 0;
			break;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ���ܵ�������󳤶�ʹ��2�ֽڱ�ʾ
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITRead_16BitsTask(USART_HandlerType*USARTx, UINT8_T val)
{
	//---��������������
	static UINT8_T tempVal;
	tempVal = val;

	//---���ݽ��ղ���
	switch (USARTx->msgRxHandler.msgStep)
	{
		//---�������ݵı�ͷ
		case 0:
			if (USARTx->msgRxHandler.msgIndexR == 0)
			{
				if (USARTx->msgRxID == tempVal)
				{
					USARTx->msgRxHandler.pMsgVal[0] = tempVal;
					USARTx->msgRxHandler.msgStep = 1;

					//---��¼���ݵĸ���
					USARTx->msgRxHandler.msgCount = 1;

					//---�յ���һ�����ϸ�ʽ�����ݣ�������ʱ������
					USART_TimeTick_Init(USARTx, 1);

					//---���㳬ʱ��־
					USART_ClearOVF(USARTx, 1);
				}
			}
			break;

			//---�������ݵĳ��ȸ�λ
		case 1:
			USARTx->msgRxHandler.pMsgVal[1] = tempVal;
			USARTx->msgRxHandler.msgIndexW = tempVal;
			USARTx->msgRxHandler.msgIndexW <<= 8;
			USARTx->msgRxHandler.msgStep = 2;

			//---��¼���ݵĸ���
			USARTx->msgRxHandler.msgCount += 1;

			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);
			break;

			//---�������ݵĳ��ȵ�λ
		case 2:
			USARTx->msgRxHandler.pMsgVal[2] = tempVal;
			USARTx->msgRxHandler.msgIndexW += tempVal;

			//---��¼���ݵĸ���
			USARTx->msgRxHandler.msgCount += 1;

			//---�ж������Ƿ�Ϸ�
			if ((USARTx->msgRxHandler.msgIndexW > 0) && (USARTx->msgRxHandler.msgIndexW < USARTx->msgRxHandler.msgSize))
			{
				//---��¼���ݵĸ���
				USARTx->msgRxHandler.msgCount = USARTx->msgRxHandler.msgIndexW;

				//---��һ����
				USARTx->msgRxHandler.msgStep = 3;
			}
			else
			{
				USARTx->msgRxHandler.msgStep = 0;
			}

			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);
			break;

			//---����������Ϣ
		case 3:
			USARTx->msgRxHandler.pMsgVal[USARTx->msgRxHandler.msgIndexR + 3] = tempVal;
			USARTx->msgRxHandler.msgIndexR++;

			//---��¼���ݵĸ���
			USARTx->msgRxHandler.msgCount += 1;

			//---�ж��Ƿ����
			if (USARTx->msgRxHandler.msgIndexR >= USARTx->msgRxHandler.msgSize)
			{
				USARTx->msgRxHandler.msgIndexR = 0;
			}

			//---��λ��ʱ������
			USART_TimeTick_Init(USARTx, 1);

			//---�ж��Ƿ�������
			if (USARTx->msgRxHandler.msgIndexR >= USARTx->msgRxHandler.msgIndexW)
			{
				USARTx->msgRxHandler.msgStep = 4;
				USARTx->msgRxHandler.msgTaskState = USART_OK;

				//---���㳬ʱ������
				//USART_TimeTick_DeInit(USARTx, 1);
			}
			break;
		case 4:

			//---���㳬ʱ������
			//USART_TimeTick_DeInit(USARTx,1);
			break;
		default:

			//USARTx->msgRxHandler.msgNowTime = 0;
			break;
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
UINT8_T  USART_ITRead_Task(USART_HandlerType*USARTx, UINT8_T val)
{
	if (USARTx->msgRxHandler.msgSize < 0xFF)
	{
		return USART_ITRead_8BitsTask(USARTx, val);
	}
	else
	{
		return USART_ITRead_16BitsTask(USARTx, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_PollMode_WriteByte(USART_HandlerType*USARTx, UINT8_T  val)
{
	//---��������
	LL_USART_TransmitData8(USARTx->msgUSART, val);

	//---�ȴ��������
	while (LL_USART_IsActiveFlag_TC(USARTx->msgUSART) == RESET)
	{
		WDT_RESET();
	}

	//---���������ɱ�־λ
	LL_USART_ClearFlag_TC(USARTx->msgUSART);
	return OK_0;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� �����ַ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_PollMode_WriteData(USART_HandlerType*USARTx, char *pVal)
{
	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_TX_ENABLE);

	//---�л����Ͷ˿�Ϊ���ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);

	//---�ر��ж�
	CLI();
	while (*pVal != '\0')
	{
		USART_PollMode_WriteByte(USARTx, (UINT8_T)*pVal);
		pVal++;
	}

	//---ʹ���ж�
	SEI();

	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);

	//---�л����Ͷ˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_PollMode_ReadByte(USART_HandlerType*USARTx)
{
	//---�ȴ��������
	while (LL_USART_IsActiveFlag_RXNE(USARTx->msgUSART) != RESET)
	{
		WDT_RESET();
	}
	return LL_USART_ReceiveData8(USARTx->msgUSART);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_PollMode_ReadData(USART_HandlerType*USARTx, char *pVal)
{
	while (*pVal != '\0')
	{
		*pVal = USART_PollMode_ReadByte(USARTx);
		pVal++;
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
UINT8_T  USART_ITWrite_TXETask(USART_HandlerType*USARTx)
{
	if (USARTx->msgTxHandler.msgIndexW != 0)
	{
		if (USARTx->msgTxHandler.msgIndexR != USARTx->msgTxHandler.msgIndexW)
		{
			//---����8Bit������
			LL_USART_TransmitData8(USARTx->msgUSART, USARTx->msgTxHandler.pMsgVal[USARTx->msgTxHandler.msgIndexR]);

			//---���ݻ������������
			USARTx->msgTxHandler.msgIndexR++;

			//---У�黺�����Ƿ����
			if (USARTx->msgTxHandler.msgIndexR >= USARTx->msgTxHandler.msgSize)
			{
				USARTx->msgTxHandler.msgIndexR = 0;
			}

			//---У�������Ƿ����뻺����
			//if (USARTx->msgTxHandler.msgIndexR >= USARTx->msgTxHandler.msgIndexW)
			if ((USARTx->msgTxHandler.msgIndexR >= USARTx->msgTxHandler.msgIndexW) && (USARTx->msgTxHandler.msgCount > 0) && (USARTx->msgTxHandler.msgIndexR >= USARTx->msgTxHandler.msgCount))
			{
				//---�������,�������ݼĴ������жϲ�ʹ��
				LL_USART_DisableIT_TXE(USARTx->msgUSART);

				//---ʹ�ܷ�������жϣ������л�TXD�˿�Ϊ����״̬
				LL_USART_EnableIT_TC(USARTx->msgUSART);
			}
		}
		else
		{
			//---�������,�������ݼĴ������жϲ�ʹ��---����Ƿ�����쳣���رշ������ݼĴ������ж�
			LL_USART_DisableIT_TXE(USARTx->msgUSART);
		}
	}
	else
	{
		//---�������,�������ݼĴ������жϲ�ʹ��---����Ƿ�����쳣���رշ������ݼĴ������ж�
		LL_USART_DisableIT_TXE(USARTx->msgUSART);

		//---������ݷ��ͻ�����
		USART_WriteInit(USARTx);
	}

	//---��λ��ʱ������
	USART_TimeTick_Init(USARTx, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ITWrite_TCTask(USART_HandlerType*USARTx)
{
	//---������485������485��Ӧ���ӳ�����,���ӷ��ͻ��з������ڻ���485����Ӧ
	if ((USARTx->msg485Port != NULL) && (USARTx->msgTxHandler.msgStep == 0))
	{
		//---����8Bit������
		LL_USART_TransmitData8(USARTx->msgUSART, 0x0D);
		USARTx->msgTxHandler.msgStep = 1;
	}
	else if ((USARTx->msg485Port != NULL) && (USARTx->msgTxHandler.msgStep == 1))
	{
		//---����8Bit������
		LL_USART_TransmitData8(USARTx->msgUSART, 0x0A);
		USARTx->msgTxHandler.msgStep = 2;
	}
	else
	{
		//---���㷢�Ͳ���
		USARTx->msgTxHandler.msgStep = 0;

		//---�������,�������ݷ�������жϲ�ʹ��
		LL_USART_DisableIT_TC(USARTx->msgUSART);

		//---������ݷ��ͻ�����
		USART_WriteInit(USARTx);

		//---���㳬ʱ������
		//USART_TimeTick_DeInit(USARTx, 0);
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
UINT8_T USART_RealTime_AddByte(USART_HandlerType*USARTx, UINT8_T val)
{
	if (USARTx->msgTxHandler.pMsgVal != NULL)
	{
		if (USARTx->msgTxHandler.msgIndexW >= USARTx->msgTxHandler.msgSize)
		{
			USARTx->msgTxHandler.msgIndexW = 0;
		}
		USARTx->msgTxHandler.pMsgVal[USARTx->msgTxHandler.msgIndexW] = val;
		USARTx->msgTxHandler.msgIndexW++;

		//---�жϷ��ͼĴ������ж��Ƿ�ʹ��
		if (LL_USART_IsEnabledIT_TXE(USARTx->msgUSART) == 0)
		{
			//---����485Ϊ����ģʽ
			USART_485GPIOInit(USARTx, USART_485_TX_ENABLE);

			//---�л����Ͷ˿�Ϊ���ģʽ
			USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);

			//---ʹ�ܷ��Ϳ��ж�
			LL_USART_EnableIT_TXE(USARTx->msgUSART);
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�����������ݵĴ�С
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_RealTime_AddByteSize(USART_HandlerType*USARTx, UINT16_T val)
{
	UINT8_T _return = ERROR_1;
	if (USARTx->msgTxHandler.pMsgVal != NULL)
	{
		if ((USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CHECKSUM) || (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC8))
		{
			val += 1;
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			val += 2;
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			val += 4;
		}

		//---�ж��Ƿ����豸��ID��Ϣ
		if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
		{
			val += 1;
		}

		//---�ж����ݵĸ�ʽ
		if (USARTx->msgTxHandler.msgSize > 250)
		{
			USART_RealTime_AddByte(USARTx, (UINT8_T)(val >> 8));
			_return = USART_RealTime_AddByte(USARTx, (UINT8_T)(val & 0xFF));
			val += 3;
		}
		else
		{
			_return = USART_RealTime_AddByte(USARTx, (UINT8_T)(val & 0xFF));
			val += 2;
		}

		//---�ж��Ƿ����豸��ID��Ϣ�����ID��Ϣ
		if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
		{
			_return = USART_RealTime_AddByte(USARTx, USARTx->msgID);
		}

		//---���㷢�����ݵĸ���
		USARTx->msgTxHandler.msgCount = val;
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����ʹ��CRC�����ݵı����0��ʼʹ��
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_RealTime_AddByteCRC(USART_HandlerType*USARTx)
{
	//---У��CRC�Ƿ��ʼ��
	if ((USARTx->msgTxHandler.msgCRCFlag != USART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;

		//---�ж�����У��ģʽ
		if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			crcVal = CRCTask_CheckSum(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USART_RealTime_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			crcVal = CRCTask_CRC8(USE_CRC8_07H, USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USART_RealTime_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			crcVal = CRCTask_CRC16(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USART_RealTime_AddByte(USARTx, (UINT8_T)(crcVal >> 8));
			USART_RealTime_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			crcVal = CRCTask_CRC32(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USART_RealTime_AddByte(USARTx, (UINT8_T)(crcVal >> 24));
			USART_RealTime_AddByte(USARTx, (UINT8_T)(crcVal >> 16));
			USART_RealTime_AddByte(USARTx, (UINT8_T)(crcVal >> 8));
			USART_RealTime_AddByte(USARTx, (UINT8_T)crcVal);
		}
		return OK_0;
	}
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������������ڷ���
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_FillMode_AddByte(USART_HandlerType*USARTx, UINT8_T val)
{
	USARTx->msgTxHandler.pMsgVal[USARTx->msgTxHandler.msgIndexW] = val;
	USARTx->msgTxHandler.msgIndexW++;
	if (USARTx->msgTxHandler.msgIndexW >= USARTx->msgTxHandler.msgSize)
	{
		USARTx->msgTxHandler.msgIndexW = 0;
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
UINT8_T USART_FillMode_AddData(USART_HandlerType*USARTx, UINT8_T *pVal, UINT16_T length)
{
	UINT16_T i = 0;
	UINT8_T _return = OK_0;
	for (i = 0; i < length; i++)
	{
		_return = USART_FillMode_AddByte(USARTx, pVal[i]);

		//---�ж������Ƿ������ȷ
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
UINT8_T USART_CRCTask_Read(USART_HandlerType*USARTx)
{
	UINT32_T crcVal = 0;
	UINT32_T crcTemp = 0;

	//---�������ݵĸ���
	UINT16_T length = USARTx->msgRxHandler.msgIndexW;

	//---У��CRC�Ƿ��ʼ��
	if ((USARTx->msgRxHandler.msgCRCFlag != USART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		//---�ж�����У��ģʽ
		if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			length -= 1;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);

				//---��ȡУ���
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];

				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);

				//---��ȡУ���
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 3];

				//---����У��ͼ���������ܳ���
				length += 3;
			}

			//---����У���
			crcVal = CRCTask_CheckSum(USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			length -= 1;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);

				//---��ȡУ���
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];

				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);

				//---��ȡУ���
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 3];

				//---����У��ͼ���������ܳ���
				length += 3;
			}

			//---����CRC8У��ֵ
			crcVal = CRCTask_CRC8(USE_CRC8_07H, USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			length -= 2;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);

				//---��ȡCRC16�ĸ�λֵ
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 1];

				//---��ȡCRC16�ĵ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxHandler.pMsgVal[length + 2];

				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);

				//---��ȡCRC16�ĸ�λֵ
				crcTemp = USARTx->msgRxHandler.pMsgVal[length + 2];

				//---��ȡCRC16�ĵ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxHandler.pMsgVal[length + 3];

				//---����У��ͼ���������ܳ���
				length += 3;
			}

			//---����CRC16У��ֵ
			crcVal = CRCTask_CRC16(USARTx->msgRxHandler.pMsgVal, length);
		}
		else if (USARTx->msgRxHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			length -= 4;
			if (USARTx->msgRxHandler.msgSize < 250)
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length);

				//---��ȡCRC32�����λֵ
				crcTemp = USARTx->msgRxHandler.pMsgVal[length - 1];

				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxHandler.pMsgVal[length];

				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxHandler.pMsgVal[length + 1];

				//---��ȡCRC32�ĵ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxHandler.pMsgVal[length + 2];

				//---����У��ͼ���������ܳ���
				length += 2;
			}
			else
			{
				USARTx->msgRxHandler.pMsgVal[1] = (UINT8_T)(length >> 8);
				USARTx->msgRxHandler.pMsgVal[2] = (UINT8_T)(length);

				//---��ȡCRC32�����λֵ
				crcTemp = USARTx->msgRxHandler.pMsgVal[length];

				//---��ȡCRC32�Ĵθ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxHandler.pMsgVal[length + 1];

				//---��ȡCRC32�Ĵε�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxHandler.pMsgVal[length + 2];

				//---��ȡCRC32�ĵ�λֵ
				crcTemp = (crcTemp << 8) + USARTx->msgRxHandler.pMsgVal[length + 3];
				length += 3;
			}
			crcVal = CRCTask_CRC32(USARTx->msgRxHandler.pMsgVal, length);
		}

		//---�ȶ�CRC��ֵ
		if (crcVal != crcTemp)
		{
			return  ERROR_1;
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
UINT8_T USART_CRCTask_Write(USART_HandlerType*USARTx)
{
	//---У��CRC�Ƿ��ʼ��
	if ((USARTx->msgTxHandler.msgCRCFlag != USART_CRC_NONE) && (CRCTask_Enable() == OK_0))
	{
		UINT32_T crcVal = 0;

		//---���ݴ�С������
		if (USARTx->msgTxHandler.msgSize < 0xFF)
		{
			USARTx->msgTxHandler.pMsgVal[1] = (UINT8_T)(USARTx->msgTxHandler.msgIndexW - 2);
		}
		else
		{
			USARTx->msgTxHandler.pMsgVal[1] = (UINT8_T)((USARTx->msgTxHandler.msgIndexW - 3) >> 8);
			USARTx->msgTxHandler.pMsgVal[2] = (UINT8_T)((USARTx->msgTxHandler.msgIndexW - 3));
		}

		//---�ж�����У��ģʽ
		if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CHECKSUM)
		{
			crcVal = CRCTask_CheckSum(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USART_FillMode_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC8)
		{
			crcVal = CRCTask_CRC8(USE_CRC8_07H, USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USART_FillMode_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC16)
		{
			crcVal = CRCTask_CRC16(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USART_FillMode_AddByte(USARTx, (UINT8_T)(crcVal >> 8));
			USART_FillMode_AddByte(USARTx, (UINT8_T)crcVal);
		}
		else if (USARTx->msgTxHandler.msgCRCFlag == USART_CRC_CRC32)
		{
			crcVal = CRCTask_CRC32(USARTx->msgTxHandler.pMsgVal, USARTx->msgTxHandler.msgIndexW);
			USART_FillMode_AddByte(USARTx, (UINT8_T)(crcVal >> 24));
			USART_FillMode_AddByte(USARTx, (UINT8_T)(crcVal >> 16));
			USART_FillMode_AddByte(USARTx, (UINT8_T)(crcVal >> 8));
			USART_FillMode_AddByte(USARTx, (UINT8_T)crcVal);
		}

		//---�������ݵĴ�С
		USARTx->msgTxHandler.msgCount = USARTx->msgTxHandler.msgIndexW;
		return OK_0;
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
UINT8_T  USART_FillMode_WriteSTART(USART_HandlerType*USARTx, UINT8_T isNeedID)
{
	//---�ȴ��������
	while (USARTx->msgTxHandler.msgTaskState == USART_BUSY)
	{
		WDT_RESET();
	}

	//---���÷���״̬Ϊ������
	USARTx->msgTxHandler.msgTaskState = USART_BUSY;

	//---�ж��Ƿ���Ҫ��䱨ͷ
	if (isNeedID == 1)
	{
		//---��䱨ͷ�����ݳ���
		USARTx->msgTxHandler.pMsgVal[0] = USARTx->msgTxID;
	}

	//---����豸ID
	if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
	{
		USARTx->msgTxHandler.pMsgVal[USARTx->msgIDIndex] = USARTx->msgID;
	}

	//---����CRC����
	USART_CRCTask_Write(USARTx);

	//---���ݴ�С������
	if (USARTx->msgTxHandler.msgSize < 0xFF)
	{
		USARTx->msgTxHandler.pMsgVal[1] = (UINT8_T)(USARTx->msgTxHandler.msgIndexW - 2);
	}
	else
	{
		USARTx->msgTxHandler.pMsgVal[1] = (UINT8_T)((USARTx->msgTxHandler.msgIndexW - 3) >> 8);
		USARTx->msgTxHandler.pMsgVal[2] = (UINT8_T)((USARTx->msgTxHandler.msgIndexW - 3));
	}

	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_TX_ENABLE);

	//---�л����Ͷ˿�Ϊ���ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);

	//---�������ݼĴ������ж�ʹ��
	LL_USART_EnableIT_TXE(USARTx->msgUSART);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��ȡ�����־
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetOVF(USART_HandlerType* USARTx, UINT8_T isRx)
{
	if (isRx)
	{
		return USARTx->msgRxHandler.msgOverFlow;
	}
	else
	{
		return USARTx->msgTxHandler.msgOverFlow;
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� ��������־
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ClearOVF(USART_HandlerType* USARTx, UINT8_T isRx)
{
	if (isRx)
	{
		USARTx->msgRxHandler.msgOverFlow = 0;
	}
	else
	{
		USARTx->msgTxHandler.msgOverFlow = 0;
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
UINT8_T USART_GetReadState(USART_HandlerType* USARTx)
{
	return USARTx->msgRxHandler.msgTaskState;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ClearReadState(USART_HandlerType* USARTx)
{
	USARTx->msgRxHandler.msgTaskState = USART_BUSY;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_GetWriteState(USART_HandlerType* USARTx)
{
	return USARTx->msgTxHandler.msgTaskState;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_ClearWriteState(USART_HandlerType* USARTx)
{
	USARTx->msgTxHandler.msgTaskState = USART_BUSY;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T  USART_ReadInit(USART_HandlerType*  USARTx)
{
	//---����485λ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);

	//---���㲽��
	USARTx->msgRxHandler.msgStep = 0;

	//---���д��������
	USARTx->msgRxHandler.msgIndexW = 0;

	//---�������������
	USARTx->msgRxHandler.msgIndexR = 0;

	//---����������ݸ���
	USARTx->msgRxHandler.msgCount = 0;

	//---���������ɱ�־
	USARTx->msgRxHandler.msgTaskState = USART_BUSY;

	//---���㳬ʱ����
	USARTx->msgRxHandler.msgNowTime = 0;

	//---���㳬ʱ����
	USARTx->msgRxHandler.msgEndTime = 0;

	//---���㳬ʱ��־
	USARTx->msgRxHandler.msgOverFlow = 0;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_WriteInit(USART_HandlerType*  USARTx)
{
	//---���÷���״̬Ϊ�������
	USARTx->msgTxHandler.msgTaskState = USART_OK;

	//---���д��������
	USARTx->msgTxHandler.msgIndexW = 0;

	//---�������������
	USARTx->msgTxHandler.msgIndexR = 0;

	//---���㷢�����ݸ���
	USARTx->msgTxHandler.msgCount = 0;

	//---���㳬ʱ����
	USARTx->msgTxHandler.msgNowTime = 0;

	//---���㳬ʱ����
	USARTx->msgTxHandler.msgEndTime = 0;

	//---���㳬ʱ��־
	USARTx->msgTxHandler.msgOverFlow = 0;

	//---�����������
	USARTx->msgTxHandler.msgStep = 0;

	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);

	//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		���� У���豸��ID��Ϣ
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_DeviceID(USART_HandlerType*USARTx)
{
	if ((USARTx->msgCmdIndex - USARTx->msgIDIndex) != 0)
	{
		if (USARTx->msgRxHandler.pMsgVal[USARTx->msgIDIndex] != USARTx->msgID)
		{
			return ERROR_1;
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
void USART_Printf(USART_HandlerType*USARTx, char*fmt, ...)
{
	#ifdef USE_USART_PRINTF

	//---��鷢�ͼĴ������ж��Ƿ�ʹ��
	if (LL_USART_IsEnabledIT_TXE(USARTx->msgUSART))
	{
		//---�ȴ��������
		while (LL_USART_IsActiveFlag_TXE(USARTx->msgUSART) != RESET)
		{
			WDT_RESET();
		}
	}

	//---��鷢������ж�
	if (LL_USART_IsEnabledIT_TC(USARTx->msgUSART))
	{
		//---�ȴ��������
		while ((LL_USART_IsActiveFlag_TC(USARTx->msgUSART) != RESET) && (USARTx->msgTxHandler.msgStep == 0))
		{
			WDT_RESET();
		}
		LL_USART_ClearFlag_TC(USARTx->msgUSART);
	}

	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_TX_ENABLE);

	//---�л����Ͷ˿�Ϊ���ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_OUTPUT);

	//---��������
	UINT16_T length = 0, i = 0;
	va_list arg_ptr;
	va_start(arg_ptr, fmt);

	//---�������ַ����д�ӡ���ݡ����ݸ�ʽ�û��Զ���;���ز��������������ַ����ĳ���
	length = (UINT16_T)vsnprintf(printfBuffer, USART_PRINTF_SIZE, fmt, arg_ptr);
	va_end(arg_ptr);

	//---���ݷ���
	for (i = 0; i < length; i++)
	{
		//---��ѯ�ķ�ʽ��������
		USART_PollMode_WriteByte(USARTx, printfBuffer[i]);
	}

	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);

	//---���ݷ�����ɣ��л��˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);
	#endif
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ���ӡϵͳʱ��
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void USART_PrintfClockFreq(USART_HandlerType*USARTx)
{
	LL_RCC_ClocksTypeDef rccClock = { 0 };

	//---��ȡϵͳʱ��
	LL_RCC_GetSystemClocksFreq(&rccClock);
	//---��ӡϵͳʱ��
	USART_Printf(USARTx, "SYSCLK=%UHz\r\n", rccClock.SYSCLK_Frequency);
	//---��ӡϵͳʱ��
	USART_Printf(USARTx, "HCLK=%UHz\r\n", rccClock.HCLK_Frequency);
	//---��ӡϵͳʱ��
	USART_Printf(USARTx, "PCLK1=%UHz\r\n", rccClock.PCLK1_Frequency);
	//---��ӡϵͳʱ��
	USART_Printf(USARTx, "PCLK2=%UHz\r\n", rccClock.PCLK2_Frequency);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_Clock(USART_TypeDef* USARTx, UINT8_T isEnable)
{
	if (USARTx == USART1)
	{
		if (isEnable)
		{
			//---ʹ��USART1��ʱ���ź�
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
		}
		else
		{
			//---��ʹ��USART1��ʱ���ź�
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART1);
		}
		return OK_0;
	}
	if (USARTx == USART2)
	{
		if (isEnable)
		{
			//---ʹ��USART2��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
		}
		else
		{
			//---��ʹ��USART2��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART2);
		}
		return OK_0;
	}
	#if defined(USART3)
	if (USARTx == USART3)
	{
		if (isEnable)
		{
			//---ʹ��USART3��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
		}
		else
		{
			//---��ʹ��USART3��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_USART3);
		}
		return OK_0;
	}
	#endif /* USART3 */
	#if defined(USART6)
	if (USARTx == USART6)
	{
		if (isEnable)
		{
			//---ʹ��USART6��ʱ���ź�
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART6);
		}
		else
		{
			//---��ʹ��USART6��ʱ���ź�
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_USART6);
		}
		return OK_0;
	}
	#endif /* USART6 */
	#if defined(UART4)
	if (USARTx == UART4)
	{
		if (isEnable)
		{
			//---ʹ��USART4��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		else
		{
			//---��ʹ��USART4��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART4);
		}
		return OK_0;
	}
	#endif /* UART4 */
	#if defined(UART5)
	if (USARTx == UART5)
	{
		if (isEnable)
		{
			//---ʹ��USART5��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		else
		{
			//---��ʹ��USART5��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART5);
		}
		return OK_0;
	}
	#endif /* UART5 */
	#if defined(UART7)
	if (USARTx == UART7)
	{
		if (isEnable)
		{
			//---ʹ��USART7��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		else
		{
			//---��ʹ��USART7��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART7);
		}
		return OK_0;
	}
	#endif /* UART7 */
	#if defined(UART8)
	if (USARTx == UART8)
	{
		if (isEnable)
		{
			//---ʹ��USART8��ʱ���ź�
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		else
		{
			//---��ʹ��USART8��ʱ���ź�
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_UART8);
		}
		return OK_0;
	}
	#endif /* UART8 */
	#if defined(UART9)
	if (USARTx == UART9)
	{
		if (isEnable)
		{
			//---ʹ��USART9��ʱ���ź�
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		else
		{
			//---��ʹ��USART9��ʱ���ź�
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART9);
		}
		return OK_0;
	}
	#endif /* UART9 */
	#if defined(UART10)
	if (USARTx == UART10)
	{
		if (isEnable)
		{
			//---ʹ��USART10��ʱ���ź�
			LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		else
		{
			//---��ʹ��USART10��ʱ���ź�
			LL_APB2_GRP1_DisableClock(LL_APB2_GRP1_PERIPH_UART10);
		}
		return OK_0;
	}
	#endif /* UART10 */
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_DeInit(USART_HandlerType*USARTx)
{
	LL_USART_DeInit(USARTx->msgUSART);
	USART_Clock(USARTx->msgUSART, 0);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART_DeviceInit(USART_HandlerType *USARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index)
{
	USARTx->msgID = id;
	USARTx->msgIDIndex = idIndex;
	USARTx->msgCmdIndex = cmdIndex;
	USARTx->msgDataOneIndex = d1Index;
	USARTx->msgDataTwoIndex = d2Index;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART1_Init(USART_HandlerType*USARTx)
{
	//---USART1 GPIO Configuration
	//---PA9  ------> USART1_TX---�˿ڸ���Ϊ7
	//---PA10 ------> USART1_RX---�˿ڸ���Ϊ7
	//---ʹ�ܶ˿�ʱ��
	GPIOTask_Clock(GPIOA, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---ģʽ����
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;

	//---�����ٶ�
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;

	//---���ù��ܵ��������
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;

	//---��������ʹ��
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	#ifdef USE_MCU_STM32F1

	//---TX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//---RX
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	#else

	//---�˿ں�
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9 | LL_GPIO_PIN_10;

	//---���ù���ΪUSART1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	#endif

	//---ע�����ڵĳ�ʼ��
	LL_USART_DeInit(USART1);

	//---ʹ��USART1��ʱ���ź�
	USART_Clock(USART1, 1);

	//---USART�Ľӿڽṹ��
	LL_USART_InitTypeDef USART_InitStruct = { 0 };

	//---������
	USART_InitStruct.BaudRate = 115200;

	//---����λ
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;

	//---ֹͣλ
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;

	//---У��λ
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;

	//---����Ϊ�շ�ģʽ
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;

	//---Ӳ��������---Ĭ��Ϊ��
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;

	//---����������
	#if defined(USART_CR1_OVER8)

		//---����������---Ĭ������Ϊ16
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	#endif

	//---��ʼ������
	LL_USART_Init(USART1, &USART_InitStruct);

	//---�����첽ģʽ����
	LL_USART_ConfigAsyncMode(USART1);

	//---USART1_IRQ�ж�����---�жϵȼ�����
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 2, 0));

	//---ʹ���ж�
	NVIC_EnableIRQ(USART1_IRQn);

	//---ʹ�ܽ����ж�
	LL_USART_EnableIT_RXNE(USART1);

	//---ʹ�ܴ���
	LL_USART_Enable(USART1);

	//---������Ϣ�ṹ���е���Ϣ
	USARTx->msgTxPort = GPIOA;
	USARTx->msgTxBit = LL_GPIO_PIN_9;
	USARTx->msgUSART = USART1;

	//---�������
	USARTx->msgIndex = 1 + 1;

	//---У���Ƿ���Ҫ��ʱ����
	if (USARTx->msgFuncTick != NULL)
	{
		USARTx->msgRxHandler.msgMaxTime = 100;
		USARTx->msgTxHandler.msgMaxTime = 100;
	}
	else
	{
		USARTx->msgRxHandler.msgMaxTime = 0;
		USARTx->msgTxHandler.msgMaxTime = 0;
	}

	//---����CRC�ĵȼ�
	USARTx->msgTxHandler.msgCRCFlag = USART_CRC_NONE;

	//---���ñ�ͷ�ͱ�β
	USARTx->msgRxID = 0x55;
	USARTx->msgTxID = 0x5A;

	//---��ʼ��485�˿�--�������ģʽ������Ϊ����ģʽ
	//////
	//----------------
	/////
	//---����485Ϊ����ģʽ
	USART_485GPIOInit(USARTx, USART_485_RX_ENABLE);

	//---����TX�˿�Ϊ����ģʽ
	USART_GPIOInit(USARTx, USART_TXGPIO_SET_INPUT);

	//---��ӡ��ʼ����Ϣ
	USART_Printf(USARTx, "=>>����1�ĳ�ʼ��<<=\r\n");
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T USART2_Init(USART_HandlerType*USARTx)
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
UINT8_T USART3_Init(USART_HandlerType*USARTx)
{
	return OK_0;
}