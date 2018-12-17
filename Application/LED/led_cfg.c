#include "led_cfg.h"

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void LEDWork_Init(void)
{
	GPIOTask_Clock(LED_WORK_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = LED_WORK_BIT;								//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;					//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;			//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;						//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;						//---�˿ڸ���ģʽ
	#endif

		//---����ָʾ�Ƶĳ�ʼ��
	LL_GPIO_Init(LED_WORK_PORT, &GPIO_InitStruct);
	LED_WORK_OUT_0;

	//---ע�����Ƴ���
	SysTickTask_FuncTick(LEDWork_Task);
}

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void LEDWork_Task(void)
{
	static UINT32_T ledCount = 0;
	ledCount++;
	if (ledCount > 500)
	{
		ledCount = 0;
		LED_WORK_OUT_C;
	}
}

#ifdef USE_LED_DEBUG
///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void LEDDebug_Init()
{
	GPIOTask_Clock(LED_DEBUG_PORT, 1);

	//---GPIO�Ľṹ��
	LL_GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	//---GPIO�ĳ�ʼ��
	GPIO_InitStruct.Pin = LED_DEBUG_BIT;							//---��Ӧ��GPIO������
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;						//---����״̬Ϊ���ģʽ
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;				//---GPIO���ٶ�---�����豸
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;					//---���ģʽ---�������
	GPIO_InitStruct.Pull = LL_GPIO_PULL_DOWN;						//---����
	#ifndef USE_MCU_STM32F1
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;								//---�˿ڸ���ģʽ
	#endif

		//---����ָʾ�Ƶĳ�ʼ��
	LL_GPIO_Init(LED_DEBUG_PORT, &GPIO_InitStruct);
	LED_DEBUG_OUT_0;
}
#endif

///////////////////////////////////////////////////////////////////////////////
//////��		����
//////��		�ܣ�
//////�������:
//////�������:
//////˵		����
//////////////////////////////////////////////////////////////////////////////
void LED_Init(void)
{
	LEDWork_Init();
	#ifdef USE_LED_DEBUG
	LEDDebug_Init();
	#endif
}