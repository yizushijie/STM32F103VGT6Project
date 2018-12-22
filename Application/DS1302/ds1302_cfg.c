#include "ds1302_cfg.h"


DS1302_HandlerType		g_DS1302Device0 = {0};
pDS1302_HandlerType		pDS1302Device0=&g_DS1302Device0;


///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_Device0_Init(DS1302_HandlerType *DS1302x)
{
	DS1302x->msgCS.msgGPIOPort = GPIOB;
	DS1302x->msgCS.msgGPIOBit = LL_GPIO_PIN_6;

	DS1302x->msgCLK.msgGPIOPort = GPIOB;
	DS1302x->msgCLK.msgGPIOBit = LL_GPIO_PIN_7;

	DS1302x->msgDAT.msgGPIOPort = GPIOB;
	DS1302x->msgDAT.msgGPIOBit = LL_GPIO_PIN_8;
	
	DS1302x->msgPluseWidth = 2;
	DS1302x->msgFuncDelay = NULL;

	//---ʹ�ܶ˿�ʱ��
	GPIOTask_Clock(DS1302x->msgCS.msgGPIOPort,  1);
	GPIOTask_Clock(DS1302x->msgCLK.msgGPIOPort, 1);
	GPIOTask_Clock(DS1302x->msgDAT.msgGPIOPort, 1);
	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_MEDIUM;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;							//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif
	//---CS�˿ڵĳ�ʼ��
	GPIO_InitStruct.Pin = DS1302x->msgCS.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgCS.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	//---CLK�˿ڵĳ�ʼ��
	GPIO_InitStruct.Pin = DS1302x->msgCLK.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgCLK.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	//---DAT�˿ڵĳ�ʼ��
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
	GPIO_InitStruct.Pin = DS1302x->msgDAT.msgGPIOBit;
	LL_GPIO_Init(DS1302x->msgDAT.msgGPIOPort, &GPIO_InitStruct);
	GPIO_OUT_1(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
UINT8_T DS1302_Device1_Init(DS1302_HandlerType *DS1302x)
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
UINT8_T DS1302_Device2_Init(DS1302_HandlerType *DS1302x)
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
UINT8_T DS1302_Init(DS1302_HandlerType *DS1302x, void(*msgDelay)( UINT32_T delay ))
{
	//---ָ���豸�ĳ�ʼ��
	if (( DS1302x != NULL ) && ( DS1302x == DS1302_TASK_ONE ))
	{
		DS1302_Device0_Init(DS1302x);
	}
	else if (( DS1302x != NULL ) && ( DS1302x == DS1302_TASK_TWO ))
	{
		DS1302_Device1_Init(DS1302x);
	}
	else if (( DS1302x != NULL ) && ( DS1302x == DS1302_TASK_THREE ))
	{
		DS1302_Device2_Init(DS1302x);
	}
	else
	{
		return ERROR_1;
	}
	DS1302x->msgFuncDelay = msgDelay;
	return OK_0;
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������λ��ǰ
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteBitLSB(DS1302_HandlerType *DS1302x, UINT8_T wVal,UINT8_T *pRVal)
{
	//---����1bit������
	if ((wVal & 0x01) == 0x00)
	{
		GPIO_OUT_0(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
	}
	else
	{
		GPIO_OUT_1(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit);
	}

	//---��ȡ1bit������
	if (GPIO_GET_STATE(DS1302x->msgDAT.msgGPIOPort, DS1302x->msgDAT.msgGPIOBit)!= 0)
	{
		if (pRVal != NULL)
		{
			*pRVal |= 0x80;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteByteLSB(DS1302_HandlerType *DS1302x, UINT8_T wVal,UINT8_T *pRVal)
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
			*pRVal >>= 1;
		}
		//---��д1BIT������
		DS1302_WriteBitLSB(DS1302x, wVal, pRVal);
		wVal >>= 1;
		GPIO_OUT_1(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgFuncDelay != NULL)
		{
			DS1302x->msgFuncDelay(DS1302x->msgPluseWidth);
		}
		GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
		if (DS1302x->msgFuncDelay != NULL)
		{
			DS1302x->msgFuncDelay(DS1302x->msgPluseWidth);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat)
{
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort,  DS1302x->msgCS.msgGPIOBit);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	GPIO_OUT_1(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	if (DS1302x->msgFuncDelay != NULL)
	{
		DS1302x->msgFuncDelay(DS1302x->msgPluseWidth);
	}
	DS1302_WriteByteLSB(DS1302x, addr, NULL);
	DS1302_WriteByteLSB(DS1302x, dat, NULL);
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadReg(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal)
{
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	GPIO_OUT_0(DS1302x->msgCLK.msgGPIOPort, DS1302x->msgCLK.msgGPIOBit);
	GPIO_OUT_1(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
	if (DS1302x->msgFuncDelay != NULL)
	{
		DS1302x->msgFuncDelay(DS1302x->msgPluseWidth);
	}
	DS1302_WriteByteLSB(DS1302x, (addr|0x01), pVal);
	GPIO_OUT_0(DS1302x->msgCS.msgGPIOPort, DS1302x->msgCS.msgGPIOBit);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������ʱ��
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T dat)
{
	//---ȡ��д����
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x00);
	//---��ָ����λ��д��ָ��������
	DS1302_WriteReg(DS1302x, addr, dat);
	//---��д����
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x80);
}
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡʱ��
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadTime(DS1302_HandlerType *DS1302x, UINT8_T addr, UINT8_T *pVal)
{
	DS1302_ReadReg(DS1302x, addr, pVal);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		�������ʵʱʱ��
//////////////////////////////////////////////////////////////////////////////
void DS1302_WriteRTC(DS1302_HandlerType *DS1302x, RTC_HandlerType rtcTime)
{
	DS1302x->msgRTC = rtcTime;
	//---ȡ��д����
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x00);
	//---д������
	DS1302_WriteReg(DS1302x, DS1302_REG_SECOND, rtcTime.second);
	//---д������
	DS1302_WriteReg(DS1302x, DS1302_REG_MINUTE, rtcTime.minute);
	//---дʱ����
	DS1302_WriteReg(DS1302x, DS1302_REG_HOUR, rtcTime.hour);
	//---д������
	DS1302_WriteReg(DS1302x, DS1302_REG_DAY, rtcTime.day);
	//---д��������
	DS1302_WriteReg(DS1302x, DS1302_REG_WEEK, rtcTime.week);
	//---д������
	DS1302_WriteReg(DS1302x, DS1302_REG_MONTH, rtcTime.month);
	//---д������
	DS1302_WriteReg(DS1302x, DS1302_REG_YEAR, rtcTime.year);
	//---��д����
	DS1302_WriteReg(DS1302x, DS1302_REG_CONTROL, 0x80);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		������ȡʵʱʱ��
//////////////////////////////////////////////////////////////////////////////
void DS1302_ReadRTC(DS1302_HandlerType *DS1302x)
{
	//---��������
	DS1302_ReadReg(DS1302x, DS1302_REG_SECOND, &(DS1302x->msgRTC.second));
	//---д������
	DS1302_ReadReg(DS1302x, DS1302_REG_MINUTE, &(DS1302x->msgRTC.minute));
	//---дʱ����
	DS1302_ReadReg(DS1302x, DS1302_REG_HOUR, &(DS1302x->msgRTC.hour));
	//---д������
	DS1302_ReadReg(DS1302x, DS1302_REG_DAY, &(DS1302x->msgRTC.day));
	//---д��������
	DS1302_ReadReg(DS1302x, DS1302_REG_WEEK, &(DS1302x->msgRTC.week));
	//---д������
	DS1302_ReadReg(DS1302x, DS1302_REG_MONTH, &(DS1302x->msgRTC.month));
	//---д������
	DS1302_ReadReg(DS1302x, DS1302_REG_YEAR, &(DS1302x->msgRTC.year));
}