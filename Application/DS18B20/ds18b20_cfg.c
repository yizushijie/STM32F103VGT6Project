#include "ds18b20_cfg.h"

//---��������
DS18B20_HandlerType g_DS18B20Device0;
pDS18B20_HandlerType pDS18B20Device0 = &g_DS18B20Device0;

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Init(DS18B20_HandlerType *DS18B20x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay))
{
	if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_ONE))
	{
		DS18B20_OneWire_Device0_Init(DS18B20x);
	}
	else if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_TWO))
	{
		DS18B20_OneWire_Device1_Init(DS18B20x);
	}
	else if ((DS18B20x != NULL) && (DS18B20x == DS18B20_TASK_THREE))
	{
		DS18B20_OneWire_Device2_Init(DS18B20x);
	}
	else
	{
		return  ERROR_1;
	}

	//---ע����ʱ����
	if (Delayms != NULL)
	{
		DS18B20x->msgFuncDelayms = Delayms;
	}
	else
	{
		DS18B20x->msgFuncDelayms = DelayTask_ms;
	}
	return OneWireTask_Init(&(DS18B20x->msgOneWire), Delayus);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Device0_Init(DS18B20_HandlerType *DS18B20x)
{
	DS18B20x->msgOneWire.msgBit = LL_GPIO_PIN_2;
	DS18B20x->msgOneWire.msgPort = GPIOC;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_Device1_Init(DS18B20_HandlerType *DS18B20x)
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
UINT8_T DS18B20_OneWire_Device2_Init(DS18B20_HandlerType *DS18B20x)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_DeInit(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_DeInit(&(DS18B20x->msgOneWire));
}
///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT8_T Ds18b20Cfg_Start(void)
//////��	   �ܣ� ����Ds18b20Cfg
//////�������:
//////�������: 0---ʧ��;1---��ʾ�ɹ�
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_START(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_START(&(DS18B20x->msgOneWire));
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� void Ds18b20Cfg_WriteByte(UINT8_T val)
//////��	   �ܣ� д��һ�ֽڵ�����
//////�������: д���ֵ
//////�������: ��
//////˵	   ����
///////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_WriteByte(DS18B20_HandlerType *DS18B20x, UINT8_T val)
{
	return OneWireTask_WriteByte(&(DS18B20x->msgOneWire), val);
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT8_T Ds18b20Cfg_ReadByte(void)
//////��	   �ܣ� ��ȡһ�ֽڵ�����
//////�������: ��
//////�������: ��ȡ������
//////˵	   ����
///////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_ReadByte(DS18B20_HandlerType *DS18B20x)
{
	return OneWireTask_ReadByte(&(DS18B20x->msgOneWire));
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS18B20_OneWire_ReadDeviceID(DS18B20_HandlerType *DS18B20x, UINT8_T *id)
{
	UINT8_T i;

	//---���߸�λ
	if (DS18B20_OneWire_START(DS18B20x) == 0)
	{
		return ERROR_1;
	}

	//---������
	DS18B20_OneWire_WriteByte(DS18B20x, 0x33);

	//---��ȡ�豸��ID��Ϣ
	for (i = 0; i < 8; i++)
	{
		id[i] = DS18B20_OneWire_ReadByte(DS18B20x);
	}

	//----���߸�λ
	DS18B20_OneWire_START(DS18B20x);
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ���� UINT16_T DS18B20_GetWenDu(DS18B20_HandlerType *DS18B20HandlerType)
//////��	   �ܣ� ��ȡ�¶�ֵ
//////�������: ��
//////�������: �Ŵ�100��֮����¶ȵ�ֵ
//////˵	   ����
///////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_ReadTemp(DS18B20_HandlerType *DS18B20x)
{
	UINT16_T _return = 0, temH = 0;
	UINT8_T temL;

	//---��ȡ����֮ǰ��������Ϊ������Ч�����������豸ʹ��
	DS18B20x->msgIsPositive = 0;

	//---�����¶ȴ�����---���߸�λ
	DS18B20_OneWire_START(DS18B20x);

	//---���Ե�ַ
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);

	//---����ת��
	DS18B20_OneWire_WriteByte(DS18B20x, 0x44);

	//---��ʱ�ȴ�
	if (DS18B20x->msgFuncDelayms != NULL)
	{
		DS18B20x->msgFuncDelayms(1);
	}

	//---��ʼ���¶ȴ�����---���߸�λ
	DS18B20_OneWire_START(DS18B20x);

	//---���Ե�ַ
	DS18B20_OneWire_WriteByte(DS18B20x, 0xCC);

	//---��ȡ�¶�
	DS18B20_OneWire_WriteByte(DS18B20x, 0xBE);

	//---��ȡ��λ
	temL = DS18B20_OneWire_ReadByte(DS18B20x);

	//---��ȡ��λ
	temH = DS18B20_OneWire_ReadByte(DS18B20x);

	//---��ȡ�¶���ֵ
	_return = (temH << 8) | temL;

	//---�ж��¶�����ֵ���Ǹ�ֵ
	if ((temH & 0x80) == 0)
	{
		//---��ȡ���¶�����ֵ
		DS18B20x->msgIsPositive = 2;
	}
	else
	{
		//===��ȡ���¶��Ǹ�ֵ
		DS18B20x->msgIsPositive = 1;
	}

	//---��ȡ���¶�ֵ
	temH = _return;

	//---������Чλ����
	temH &= 0x0FFF;

	//---��ȡ�¶�ֵ��Ӧ��16���Ƶ�����
	if (DS18B20x->msgIsPositive == 2)
	{
		DS18B20x->msgTempX10000 = temH;
	}
	else
	{
		DS18B20x->msgTempX10000 = 0x1000 - temH;
	}

	//---��ʮ��������ת�����¶�ֵ
	DS18B20x->msgTempX10000 *= 625;

	//---��ȡʵ���¶�ֵ
	DS18B20x->msgTempX100 = (UINT16_T)(DS18B20x->msgTempX10000 / 100);

	//---�����¶����ֵ
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT16_T DS18B20_OneWire_ReadTempByID(DS18B20_HandlerType *DS18B20x, UINT8_T *id)
{
	UINT16_T _return = 0, temH = 0;
	UINT8_T temL = 0, i = 0;

	//---�����¶ȴ�����---���߸�λ
	DS18B20_OneWire_START(DS18B20x);

	//---���Ե�ַ
	DS18B20_OneWire_WriteByte(DS18B20x, 0x55);

	//---д��ROM��ID
	for (i = 0; i < 8; i++)
	{
		DS18B20_OneWire_WriteByte(DS18B20x, id[i]);
	}

	//---����ת��
	DS18B20_OneWire_WriteByte(DS18B20x, 0x44);

	//---��ʱ�ȴ�
	if (DS18B20x->msgFuncDelayms != NULL)
	{
		DS18B20x->msgFuncDelayms(1);
	}

	//---��ʼ���¶ȴ�����---���߸�λ
	DS18B20_OneWire_START(DS18B20x);

	//---���Ե�ַ
	DS18B20_OneWire_WriteByte(DS18B20x, 0x55);

	//---д��ROM��ID
	for (i = 0; i < 8; i++)
	{
		DS18B20_OneWire_WriteByte(DS18B20x, id[i]);
	}

	//---��ȡ�¶�
	DS18B20_OneWire_WriteByte(DS18B20x, 0xBE);

	//---��ȡ��λ
	temL = DS18B20_OneWire_ReadByte(DS18B20x);

	//---��ȡ��λ
	temH = DS18B20_OneWire_ReadByte(DS18B20x);

	//---��ȡ�¶���ֵ
	_return = (temH << 8) | temL;

	//---�ж��¶�����ֵ���Ǹ�ֵ
	if ((temH & 0x80) == 0)
	{
		//---��ȡ���¶�����ֵ
		DS18B20x->msgIsPositive = 0;
	}
	else
	{
		//===��ȡ���¶��Ǹ�ֵ
		DS18B20x->msgIsPositive = 1;
	}

	//---��ȡ���¶�ֵ
	temH = _return;

	//---������Чλ����
	temH &= 0x0FFF;

	//---��ȡ�¶�ֵ��Ӧ��16���Ƶ�����
	if (DS18B20x->msgIsPositive == 0)
	{
		DS18B20x->msgTempX10000 = temH;
	}
	else
	{
		DS18B20x->msgTempX10000 = 4096 - temH;
	}

	//---��ʮ��������ת�����¶�ֵ
	DS18B20x->msgTempX10000 *= 625;

	//---��ȡʵ���¶�ֵ
	DS18B20x->msgTempX100 = (UINT16_T)(DS18B20x->msgTempX10000 / 100);

	//---�����¶����ֵ
	return _return;
}