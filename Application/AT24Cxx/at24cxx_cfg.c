#include "at24cxx_cfg.h"

//===ȫ�ֱ�������
AT24CXX_HandlerType g_AT24CXXDevice0;
pAT24CXX_HandlerType pAT24CXXDevice0 = &g_AT24CXXDevice0;

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ�
//////�������:isHWI2C---1 Ӳ����0 ���
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_Init(AT24CXX_HandlerType *AT24CXXx, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;

	//---ָ���豸�ĳ�ʼ��
	if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_ONE))
	{
		AT24CXX_Device0_Init(AT24CXXx);
	}
	else if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_TWO))
	{
		AT24CXX_Device1_Init(AT24CXXx);
	}
	else if ((AT24CXXx != NULL) && (AT24CXXx == AT24CXX_TASK_THREE))
	{
		AT24CXX_Device2_Init(AT24CXXx);
	}
	else
	{
		return ERROR_1;
	}

	//---�ж���Ӳ��I2C�������I2C
	if (isHWI2C)
	{
		//---��ʼ��Ӳ��I2C
		_return = I2CTask_MHW_Init(&(AT24CXXx->msgI2C));
		AT24CXXx->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---��ʼ�����ģ��I2C
		_return = I2CTask_MSW_Init(&(AT24CXXx->msgI2C), msgDelay);

		//---ע��д����
		AT24CXXx->msgI2C.msgModelIsHW = 0;
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
UINT8_T AT24CXX_Device0_Init(AT24CXX_HandlerType *AT24CXXx)
{
	AT24CXXx->msgAT24CXXType = AT24C16;
	AT24CXXx->msgI2C.msgI2Cx = NULL;
	AT24CXXx->msgI2C.msgSclPort = GPIOB;
	AT24CXXx->msgI2C.msgSdaPort = GPIOB;
	AT24CXXx->msgI2C.msgSclBit = LL_GPIO_PIN_8;
	AT24CXXx->msgI2C.msgSdaBit = LL_GPIO_PIN_9;
	AT24CXXx->msgI2C.msgModelIsHW = 0;
	AT24CXXx->msgI2C.msgPluseWidth = 0;
	AT24CXXx->msgI2C.msgFuncDelay = NULL;
	AT24CXXx->msgI2C.msgAddr = 0xA0;  // PCF8563_WRITE_ADDR;
	AT24CXXx->msgI2C.msgClockSpeed = 0;

	//---����ҳ�����ֽ�����
	if (AT24CXXx->msgAT24CXXType == AT24C01)
	{
		AT24CXXx->msgAT24CXXPageNum = 16;
		AT24CXXx->msgAT24CXXPageByte = 8;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C02)
	{
		AT24CXXx->msgAT24CXXPageNum = 32;
		AT24CXXx->msgAT24CXXPageByte = 8;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C04)
	{
		AT24CXXx->msgAT24CXXPageNum = 32;
		AT24CXXx->msgAT24CXXPageByte = 16;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C08)
	{
		AT24CXXx->msgAT24CXXPageNum = 64;
		AT24CXXx->msgAT24CXXPageByte = 16;
	}
	else if (AT24CXXx->msgAT24CXXType == AT24C16)
	{
		AT24CXXx->msgAT24CXXPageNum = 128;
		AT24CXXx->msgAT24CXXPageByte = 16;
	}
	else
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
UINT8_T AT24CXX_Device1_Init(AT24CXX_HandlerType *AT24CXXx)
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
UINT8_T AT24CXX_Device2_Init(AT24CXX_HandlerType *AT24CXXx)
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
UINT8_T AT24CXX_DeInit(AT24CXX_HandlerType *AT24CXXx)
{
	//---ע��I2C�豸
	if (AT24CXXx->msgI2C.msgModelIsHW == 1)
	{
		return ERROR_1;
	}
	else
	{
		return I2CTask_MSW_DeInit(&(AT24CXXx->msgI2C));
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;

	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;

	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}

		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));

		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);

		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}

	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}

	//---���ݷ���
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), val);

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}
	GoToExit:

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));

	//---�ָ��豸�ĵ�ַ
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24CXXx->msgAT24CXXPageByte)
	{
		length = AT24CXXx->msgAT24CXXPageByte;
	}
	UINT8_T _return = OK_0;

	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;

	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}

		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr >> 8));

		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((pageAddr >> 8) << 1) & 0x0F);

		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}

	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr & 0xFF));

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}

	//---���ݷ���
	for (i = 0; i < length; i++)
	{
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), pVal[i]);

		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));

		//---�ж���ȷ��
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_4;
			goto GoToExit;
		}
	}

	GoToExit:

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));

	//---�ָ��豸�ĵ�ַ
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal,
	UINT16_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_WriteOneByte(AT24CXXx, addr, val);
	}
	else
	{
		return AT24CXX_HWI2C_WriteOneByte(AT24CXXx, addr, val);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_WritePageByte(AT24CXXx, addr, pVal, length);
	}
	else
	{
		return AT24CXX_HWI2C_WritePageByte(AT24CXXx, addr, pVal, length);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��	   ����
//////��	   �ܣ���ȡ�Ĵ���
//////�������:
//////�������:
//////˵	   ����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;

	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;

	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}

		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));

		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);

		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}

	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}

	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}

	//---��ȡ����
	*pVal = I2CTask_MSW_ReadByte(&(AT24CXXx->msgI2C));

	//---���Ͳ�Ӧ���ź�
	I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), 1);
	GoToExit:

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---�ж�ҳ�ź�ҳ�ڵ�����
	if (length > AT24CXXx->msgAT24CXXPageByte)
	{
		length = AT24CXXx->msgAT24CXXPageByte;
	}
	UINT8_T _return = OK_0;

	//---�����豸�ĵ�ַ�����ں���ָ�
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;

	//---����豸����
	if (AT24CXXx->msgAT24CXXType > AT24C16)
	{
		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}

		//---���ͼĴ�����ַ,�ߵ�ַ
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));

		//---��ȡACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---��������ʧ��
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);

		//---����IIC������������ַ��д����
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---����д����ʧ��
			_return = ERROR_2;
			goto GoToExit;
		}
	}

	//---���ͼĴ�����ַ,��λ��ַ
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));

	//---��ȡACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---��������ʧ��
		_return = ERROR_3;
		goto GoToExit;
	}

	//---����IIC������������ַ��������
	_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---����������ʧ��
		_return = ERROR_4;
		goto GoToExit;
	}

	//---ѭ����ȡָ�����ȵ�����
	for (i = 0; i < length; i++)
	{
		//---��ȡ����
		pVal[i] = I2CTask_MSW_ReadByte(&(AT24CXXx->msgI2C));
		if (i == (length - 1))
		{
			_return = 1;
		}

		//---����Ӧ���ź�
		I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), _return);
	}
	_return = OK_0;
	GoToExit:

	//---����ֹͣ�ź�
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_ReadOneByte(AT24CXXx, addr, pVal);
	}
	else
	{
		return AT24CXX_HWI2C_ReadOneByte(AT24CXXx, addr, pVal);
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	if (AT24CXXx->msgI2C.msgModelIsHW == 0)
	{
		return AT24CXX_SWI2C_ReadPageByte(AT24CXXx, addr, pVal, length);
	}
	else
	{
		return AT24CXX_HWI2C_ReadPageByte(AT24CXXx, addr, pVal, length);
	}
}