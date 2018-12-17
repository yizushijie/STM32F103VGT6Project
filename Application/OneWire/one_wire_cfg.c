#include "one_wire_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_Init(OneWire_HandlerType *OneWirex, void(*msgDelay)(UINT32_T delay))
{
	//---ʹ�ܶ˿�ʱ��
	GPIOTask_Clock(OneWirex->msgPort, 1);
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = OneWirex->msgBit;			//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;					//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;			//---GPIO���ٶ�
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;				//---���ģʽ---��©���
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;						//---����ʹ��

	//---��ʼ���˿�
	LL_GPIO_Init(OneWirex->msgPort, &GPIO_InitStruct);

	//---�˿�����ߵ�ƽ
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);

	//---��ʱ����
	if (msgDelay != NULL)
	{
		OneWirex->msgFuncDelay = msgDelay;
	}
	else
	{
		OneWirex->msgFuncDelay = DelayTask_us;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_DeInit(OneWire_HandlerType *OneWirex)
{
	LL_GPIO_DeInit(OneWirex->msgPort);
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);

	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_START(OneWire_HandlerType *OneWirex)
{
	UINT8_T _return = OK_0;

	//---����Ϊ����������
	GPIO_OUT_0(OneWirex->msgPort, OneWirex->msgBit);

	//>=480
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(500);
	}

	//---����ߵ�ƽ
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);

	//15us~60us֮��
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(50);
	}
	_return = GPIO_GET_STATE(OneWirex->msgPort, OneWirex->msgBit);

	//60us~240us
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(200);
	}
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_WriteBit(OneWire_HandlerType *OneWirex, UINT8_T bitVal)
{
	//---�������ߣ�ǿ������
	GPIO_OUT_0(OneWirex->msgPort, OneWirex->msgBit);

	//=4
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(4);
	}

	//---��������
	if (bitVal)
	{
		//---�ͷ�����
		GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);
	}

	//=60us
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(50);
	}

	//---�ͷ�����
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);

	//=4
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(4);
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_ReadBit(OneWire_HandlerType *OneWirex)
{
	UINT8_T _return = 0;

	//---��������,ǿ������
	GPIO_OUT_0(OneWirex->msgPort, OneWirex->msgBit);

	//=8
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(8);
	}

	//---�ͷ�����
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);

	//=14
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(14);
	}

	//---��ȡ����
	if (GPIO_GET_STATE(OneWirex->msgPort, OneWirex->msgBit))
	{
		_return = 1;
	}

	//=40
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(40);
	}

	//---�ͷ�����
	GPIO_OUT_1(OneWirex->msgPort, OneWirex->msgBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_WriteByte(OneWire_HandlerType *OneWirex, UINT8_T val)
{
	UINT8_T i = 0;
	for (i = 0; i < 8; i++)
	{
		//---�ȷ��͵�λ����
		OneWire_WriteBit(OneWirex, (val & 0x01));
		val >>= 1;
	}
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T OneWire_ReadByte(OneWire_HandlerType *OneWirex)
{
	UINT8_T _return = 0, i = 0;
	for (i = 0; i < 8; i++)
	{
		_return |= (OneWire_ReadBit(OneWirex) << i);
	}

	//=5
	if (OneWirex->msgFuncDelay != NULL)
	{
		OneWirex->msgFuncDelay(5);
	}
	return _return;
}