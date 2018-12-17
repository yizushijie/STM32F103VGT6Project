#include "i2c_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_Init(I2C_HandlerType *I2Cx, void(*msgDelay)(UINT32_T delay))
{
	//---使能GPIO的时钟
	GPIOTask_Clock(I2Cx->msgSclPort, 1);
	GPIOTask_Clock(I2Cx->msgSdaPort, 1);

	//---SCL和SDA端口输出高电平
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);

	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSclBit;							//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;					//---端口复用模式
	#endif

		//---SCL的初始化
	LL_GPIO_Init(I2Cx->msgSclPort, &GPIO_InitStruct);

	//---SDA的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSdaBit;
	LL_GPIO_Init(I2Cx->msgSdaPort, &GPIO_InitStruct);

	//---注册延时函数
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_DeInit(I2C_HandlerType *I2Cx)
{
	//---GPIO的结构体
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSclBit;							//---对应的GPIO的引脚
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;						//---配置状态为输出模式
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO的速度---低速设备
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;			//---输出模式---开漏输出
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---上拉
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---端口复用模式
	#endif

	//---SCL的初始化
	LL_GPIO_Init(I2Cx->msgSclPort, &GPIO_InitStruct);

	//---SDA的初始化
	GPIO_InitStruct.Pin = I2Cx->msgSdaBit;
	LL_GPIO_Init(I2Cx->msgSdaPort, &GPIO_InitStruct);

	//---SCL和SDA端口输出高电平
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_START(I2C_HandlerType *I2Cx)
{
	//---发送起始条件的数据信号
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---发送起始信号;
	GPIO_OUT_0(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---判断I2C启动信号是否成功，读取SDA的状态信号，成功SDA---0；失败SDA---1
	if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit) != OK_0)
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
UINT8_T I2C_MSW_STOP(I2C_HandlerType *I2Cx)
{
	//---发送停止条件的数据信号
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

	//---判断I2C启动信号是否成功，读取SDA的状态信号，成功SDA---1；失败SDA---0
	if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit) == OK_0)
	{
		return ERROR_1;
	}

	//GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ACK(I2C_HandlerType *I2Cx)
{
	GPIO_OUT_0(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_NACK(I2C_HandlerType *I2Cx)
{
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadACK(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;

	//---读取应答信号
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---延时等待
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---读取SDA的状态信号---ACK状态下SDA为低电平
	if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit) != OK_0)
	{
		_return = ERROR_1;
	}

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_WaitACK(I2C_HandlerType *I2Cx)
{
	UINT8_T i = 0;

	//---读取应答信号
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---等待应答信号
	for (i = 255; i > 0; i--)
	{
		//---读取SDA的状态
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

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
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

	//---一个时钟脉冲
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
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_SendByte(I2C_HandlerType *I2Cx, UINT8_T val)
{
	UINT8_T i = 0;

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		//---读取1Bit的数据
		I2C_MSW_SendBit(I2Cx, val);
		val <<= 1;
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
UINT8_T I2C_MSW_SendBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---计算字节个数
	UINT8_T byteCount = (bitNum / 8);

	//---计算bit个数
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;

	//---发送整数字节的个数
	for (i = 0; i < byteCount; i++)
	{
		I2C_MSW_SendByte(I2Cx, pVal[i]);
	}

	//---数据左移---数据的发送，首先发送高位
	pVal[byteCount] <<= (8 - bitCount);

	//---判断发送数据是不是不满足1字节
	if (byteCount == 0)
	{
		//---清时钟线,钳住I2C总线，准备发送或接收数据
		GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	}

	//---发送指定个数的bit
	for (i = 0; i < bitCount; i++)
	{
		I2C_MSW_SendBit(I2Cx, pVal[byteCount]);
		pVal[byteCount] <<= 1;
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
UINT8_T I2C_MSW_ReadBit(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;

	//---时钟正脉冲
	GPIO_OUT_1(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}

	//---读取数据位
	if (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit))
	{
		_return = ERROR_1;
	}

	//---时钟负脉冲
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	if (I2Cx->msgFuncDelay != NULL)
	{
		I2Cx->msgFuncDelay(I2Cx->msgPluseWidth);
	}
	return  _return;
}

///////////////////////////////////////////////////////////////////////////////
//////函		数：
//////功		能：
//////输入参数:
//////输出参数:
//////说		明：
//////////////////////////////////////////////////////////////////////////////
UINT8_T I2C_MSW_ReadByte(I2C_HandlerType *I2Cx)
{
	UINT8_T i = 0;
	UINT8_T _return = 0;

	//---准备数据的读取
	GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);

	//---清时钟线,钳住I2C总线，准备发送或接收数据
	GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);

	//---发送1字节的数据
	for (i = 0; i < 8; i++)
	{
		_return <<= 1;
		_return |= I2C_MSW_ReadBit(I2Cx);
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
UINT8_T I2C_MSW_ReadBits(I2C_HandlerType *I2Cx, UINT8_T *pVal, UINT8_T bitNum)
{
	//---读取字节个数
	UINT8_T byteCount = (bitNum / 8);

	//---读取bit个数
	UINT8_T bitCount = (bitNum % 8);
	UINT8_T i = 0;

	//---读取整数字节的个数
	for (i = 0; i < byteCount; i++)
	{
		pVal[i] = I2C_MSW_ReadByte(I2Cx);
	}

	//---清零处理
	pVal[byteCount] = 0x00;

	//---判断读取的Bit数据是不是不满足1字节
	if (byteCount == 0)
	{
		//---准备数据的读取
		GPIO_OUT_1(I2Cx->msgSdaPort, I2Cx->msgSdaBit);

		//---清时钟线,钳住I2C总线，准备发送或接收数据
		GPIO_OUT_0(I2Cx->msgSclPort, I2Cx->msgSclBit);
	}

	//---读取指定个数的bit
	for (i = 0; i < bitCount; i++)
	{
		pVal[byteCount] <<= 1;
		pVal[byteCount] |= I2C_MSW_ReadBit(I2Cx);
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
UINT8_T I2C_MSW_CheckDevice(I2C_HandlerType *I2Cx)
{
	UINT8_T _return = OK_0;
	if ((GPIO_GET_STATE(I2Cx->msgSclPort, I2Cx->msgSclBit)) && (GPIO_GET_STATE(I2Cx->msgSdaPort, I2Cx->msgSdaBit)))
	{
		//---发送启动信号
		I2C_MSW_START(I2Cx);

		//---发送读取操作命令
		I2Cx->msgAddr |= 0x01;

		//---发送从机地址
		I2C_MSW_SendByte(I2Cx, (UINT8_T)I2Cx->msgAddr);

		//---读取应答信号
		_return = I2C_MSW_ReadACK(I2Cx);
	}
	else
	{
		_return = ERROR_2;
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
UINT8_T I2C_MSW_SendCMD(I2C_HandlerType *I2Cx, UINT8_T cmd, UINT8_T isStart, UINT8_T isStop)
{
	UINT8_T _return = OK_0;
	if (isStart)
	{
		//---发送启动启动信号
		_return = I2C_MSW_START(I2Cx);
		if (_return)
		{
			I2C_MSW_STOP(I2Cx);
			return ERROR_1;
		}
	}

	//---发送数据
	_return = I2C_MSW_SendByte(I2Cx, cmd);

	//---读取应答
	_return = I2C_MSW_ReadACK(I2Cx);

	//---停止条件的满足
	if ((isStop) || (_return))
	{
		I2C_MSW_STOP(I2Cx);
	}
	return _return;
}