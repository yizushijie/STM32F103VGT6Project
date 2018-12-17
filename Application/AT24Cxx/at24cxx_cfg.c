#include "at24cxx_cfg.h"

//===全局变量定义
AT24CXX_HandlerType g_AT24CXXDevice0;
pAT24CXX_HandlerType pAT24CXXDevice0 = &g_AT24CXXDevice0;

///////////////////////////////////////////////////////////////////////////////
//////函	   数：
//////功	   能：
//////输入参数:isHWI2C---1 硬件，0 软件
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_Init(AT24CXX_HandlerType *AT24CXXx, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C)
{
	UINT8_T _return = OK_0;

	//---指定设备的初始化
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

	//---判断是硬件I2C还是软件I2C
	if (isHWI2C)
	{
		//---初始化硬件I2C
		_return = I2CTask_MHW_Init(&(AT24CXXx->msgI2C));
		AT24CXXx->msgI2C.msgModelIsHW = 1;
	}
	else
	{
		//---初始化软件模拟I2C
		_return = I2CTask_MSW_Init(&(AT24CXXx->msgI2C), msgDelay);

		//---注册写函数
		AT24CXXx->msgI2C.msgModelIsHW = 0;
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

	//---解析页数和字节数据
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_Device1_Init(AT24CXX_HandlerType *AT24CXXx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_Device2_Init(AT24CXX_HandlerType *AT24CXXx)
{
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_DeInit(AT24CXX_HandlerType *AT24CXXx)
{
	//---注销I2C设备
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	UINT8_T _return = OK_0;

	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;

	//---检查设备类型
	if (AT24CXXx->msgAT24CXXType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}

		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));

		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);

		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}

	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}

	//---数据发送
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), val);

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_4;
		goto GoToExit;
	}
	GoToExit:

	//---发送停止信号
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));

	//---恢复设备的地址
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length)
{
	//---判断页号和页内的数据
	if (length > AT24CXXx->msgAT24CXXPageByte)
	{
		length = AT24CXXx->msgAT24CXXPageByte;
	}
	UINT8_T _return = OK_0;

	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;

	//---检查设备类型
	if (AT24CXXx->msgAT24CXXType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}

		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr >> 8));

		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((pageAddr >> 8) << 1) & 0x0F);

		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}

	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(pageAddr & 0xFF));

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}

	//---数据发送
	for (i = 0; i < length; i++)
	{
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), pVal[i]);

		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));

		//---判断正确性
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_4;
			goto GoToExit;
		}
	}

	GoToExit:

	//---发送停止信号
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));

	//---恢复设备的地址
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal,
	UINT16_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函	   数：
//////功	   能：读取寄存器
//////输入参数:
//////输出参数:
//////说	   明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	UINT8_T _return = OK_0;

	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;

	//---检查设备类型
	if (AT24CXXx->msgAT24CXXType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}

		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));

		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);

		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}

	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}

	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}

	//---读取数据
	*pVal = I2CTask_MSW_ReadByte(&(AT24CXXx->msgI2C));

	//---发送不应答信号
	I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), 1);
	GoToExit:

	//---发送停止信号
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}
///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_SWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	//---判断页号和页内的数据
	if (length > AT24CXXx->msgAT24CXXPageByte)
	{
		length = AT24CXXx->msgAT24CXXPageByte;
	}
	UINT8_T _return = OK_0;

	//---保存设备的地址，用于后面恢复
	UINT16_T at24cxxAddr = AT24CXXx->msgI2C.msgAddr;
	UINT16_T i = 0;

	//---检查设备类型
	if (AT24CXXx->msgAT24CXXType > AT24C16)
	{
		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}

		//---发送寄存器地址,高地址
		I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr >> 8));

		//---读取ACK
		_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
		if (_return != OK_0)
		{
			//---发送数据失败
			_return = ERROR_3;
			goto GoToExit;
		}
	}
	else
	{
		AT24CXXx->msgI2C.msgAddr += (((addr >> 8) << 1) & 0x0F);

		//---启动IIC并发送器件地址，写数据
		_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 1);
		if (_return != OK_0)
		{
			//---启动写数据失败
			_return = ERROR_2;
			goto GoToExit;
		}
	}

	//---发送寄存器地址,低位地址
	I2CTask_MSW_SendByte(&(AT24CXXx->msgI2C), (UINT8_T)(addr & 0xFF));

	//---读取ACK
	_return = I2CTask_MSW_ReadACK(&(AT24CXXx->msgI2C));
	if (_return != OK_0)
	{
		//---发送数据失败
		_return = ERROR_3;
		goto GoToExit;
	}

	//---启动IIC并发送器件地址，读数据
	_return = I2CTask_MSW_START(&(AT24CXXx->msgI2C), 0);
	if (_return != OK_0)
	{
		//---启动读数据失败
		_return = ERROR_4;
		goto GoToExit;
	}

	//---循环读取指定长度的数据
	for (i = 0; i < length; i++)
	{
		//---读取数据
		pVal[i] = I2CTask_MSW_ReadByte(&(AT24CXXx->msgI2C));
		if (i == (length - 1))
		{
			_return = 1;
		}

		//---发送应答信号
		I2CTask_MSW_SendACK(&(AT24CXXx->msgI2C), _return);
	}
	_return = OK_0;
	GoToExit:

	//---发送停止信号
	I2CTask_MSW_STOP(&(AT24CXXx->msgI2C));
	AT24CXXx->msgI2C.msgAddr = at24cxxAddr;
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T AT24CXX_HWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length)
{
	return ERROR_1;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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