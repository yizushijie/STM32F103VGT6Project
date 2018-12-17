#include "i2c_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_Init(I2C_HandlerType *I2Cx, void(*msgDelay)(UINT32_T delay))
{
	//---ʹ��GPIO��ʱ��
	GPIOTask_Clock(I2Cx->msgSclPort, 1);
	GPIOTask_Clock(I2Cx->msgSdaPort, 1);

	//---SCL��SDA�˿�����ߵ�ƽ
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSclBit;							//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;					//---�˿ڸ���ģʽ
	#endif

		//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2Cx->msgSclPort, &GPIO_InitStruct);

	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSdaBit;
	LL_GPIO_Init(I2Cx->msgSdaPort, &GPIO_InitStruct);

	//---ע����ʱ����
	if (msgDelay != NULL)
	{
		I2Cx->msgFuncDelay = msgDelay;
	}
	else
	{
		I2Cx->msgFuncDelay = DelayTask_us;
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
UINT8_T I2C_MSW_DeInit(I2C_HandlerType *I2Cx)
{
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSclBit;							//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

	//---SCL�ĳ�ʼ��
	LL_GPIO_Init(I2Cx->msgSclPort, &GPIO_InitStruct);

	//---SDA�ĳ�ʼ��
	GPIO_InitStruct.Pin = I2Cx->msgSdaBit;
	LL_GPIO_Init(I2Cx->msgSdaPort, &GPIO_InitStruct);

	//---SCL��SDA�˿�����ߵ�ƽ
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_START(I2C_HandlerType *I2Cx)
{
	//---������ʼ�����������ź�
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---������ʼ�ź�;
	GPIO_OUT_0(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---0��ʧ��SDA---1
	if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit) != OK_0)
	{
		return ERROR_1;
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
UINT8_T I2C_MSW_STOP(I2C_HandlerType *I2Cx)
{
	//---����ֹͣ�����������ź�
	GPIO_OUT_0(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---�ж�I2C�����ź��Ƿ�ɹ�����ȡSDA��״̬�źţ��ɹ�SDA---1��ʧ��SDA---0
	if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit) == OK_0)
	{
		return ERROR_1;
	}

	//GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ACK(I2C_HandlerType *I2Cx)
{
	GPIO_OUT_0(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_NACK(I2C_HandlerType *I2Cx)
{
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadACK(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;

	//---��ȡӦ���ź�
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---��ʱ�ȴ�
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---��ȡSDA��״̬�ź�---ACK״̬��SDAΪ�͵�ƽ
	if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit) != OK_0)
	{
		_return = ERROR_1;
	}

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_WaitACK(I2C_HandlerType *I2Cx)
{
	UINT8_T i = 0;

	//---��ȡӦ���ź�
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---�ȴ�Ӧ���ź�
	for (i = 255; i > 0; i--)
	{
		//---��ȡSDA��״̬
		if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit))
		{
			break;
		}
	}
	if (i == 0)
	{
		I2C_MSW_STOP(I2Cx);
		return ERROR_1;
	}

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendACK(I2C_HandlerType *I2Cx, UINT8_T isNACK)
{
	if (isNACK)
	{
		return I2C_MSW_NACK(I2Cx);
	}
	else
	{
		return I2C_MSW_ACK(I2Cx);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendBit(I2C_HandlerType *I2Cx, UINT8_T bitVal)
{
	if (bitVal & 0x80)
	{
		GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	}
	else
	{
		GPIO_OUT_0(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	}

	//---һ��ʱ������
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
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
UINT8_T I2C_MSW_SendByte(I2C_HandlerType *I2Cx, UINT8_T val)
{
	UINT8_T i = 0;

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		//---��ȡ1Bit������
		I2C_MSW_SendBit(I2Cx, val);
		val <<= 1;
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
UINT8_T I2C_MSW_SendBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---�����ֽڸ���
	UINT8_T byteCount = (bitNum / 8);

	//---����bit����
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;

	//---���������ֽڵĸ���
	for (i = 0; i < byteCount; i++)
	{
		I2C_MSW_SendByte(I2Cx, pVal[i]);
	}

	//---��������---���ݵķ��ͣ����ȷ��͸�λ
	pVal[byteCount] <<= (8 - bitCount);

	//---�жϷ��������ǲ��ǲ�����1�ֽ�
	if (byteCount == 0)
	{
		//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
		GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	}

	//---����ָ��������bit
	for (i = 0; i < bitCount; i++)
	{
		I2C_MSW_SendBit(I2Cx, pVal[byteCount]);
		pVal[byteCount] <<= 1;
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
UINT8_T I2C_MSW_ReadBit(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;

	//---ʱ��������
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---��ȡ����λ
	if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit))
	{
		_return = ERROR_1;
	}

	//---ʱ�Ӹ�����
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadByte(I2C_HandlerType *I2Cx)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;

	//---׼�����ݵĶ�ȡ
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);

	//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---����1�ֽڵ�����
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= I2C_MSW_ReadBit(I2Cx);
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
UINT8_T I2C_MSW_ReadBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---��ȡ�ֽڸ���
	UINT8_T byteCount = (bitNum / 8);

	//---��ȡbit����
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;

	//---��ȡ�����ֽڵĸ���
	for (i = 0; i < byteCount; i++)
	{
		pVal[i] = I2C_MSW_ReadByte(I2Cx);
	}

	//---���㴦��
	pVal[byteCount] = 0x00;

	//---�ж϶�ȡ��Bit�����ǲ��ǲ�����1�ֽ�
	if (byteCount == 0)
	{
		//---׼�����ݵĶ�ȡ
		GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);

		//---��ʱ����,ǯסI2C���ߣ�׼�����ͻ��������
		GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	}

	//---��ȡָ��������bit
	for (i = 0; i < bitCount; i++)
	{
		pVal[byteCount] <<= 1;
		pVal[byteCount] |= I2C_MSW_ReadBit(I2Cx);
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
UINT8_T I2C_MSW_CheckDevice(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;
	if ((GPIO_GET_STATE(I2Cx->msgSclPort, I2Cx->msgSclBit)) && (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit)))
	{
		//---���������ź�
		I2C_MSW_START(I2Cx);

		//---���Ͷ�ȡ��������
		I2Cx->msgAddr |= 0x01;

		//---���ʹӻ���ַ
		I2C_MSW_SendByte(I2Cx, (UINT8_T)I2Cx->msgAddr);

		//---��ȡӦ���ź�
		_return = I2C_MSW_ReadACK(I2Cx);
	}
	else
	{
		_return = ERROR_2;
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
UINT8_T I2C_MSW_SendCMD(I2C_HandlerType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop)
{
	UINT8_T _return = OK_0;
	if (isStart)
	{
		//---�������������ź�
		_return = I2C_MSW_START(I2Cx);
		if (_return)
		{
			I2C_MSW_STOP(I2Cx);
			return ERROR_1;
		}
	}

	//---��������
	_return = I2C_MSW_SendByte(I2Cx, cmd);

	//---��ȡӦ��
	_return = I2C_MSW_ReadACK(I2Cx);

	//---ֹͣ����������
	if ((isStop) || (_return))
	{
		I2C_MSW_STOP(I2Cx);
	}
	return _return;
}