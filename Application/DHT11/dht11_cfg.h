#ifndef DHT11_CFG_H_
#define DHT11_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
/////˵��:DHT11����ʱ���Ҫ��Ƚϵĸߣ���ʹ�õ�ʱ��ע����ʱ�����ã��������׳��ִ���
/////���ʱ����ȷ�������������Ӧ���ǳ��ڶ�ȡ���ݵ�ʱ�����ԣ�ʾ����ץȡ���ݶ�ȡ�ĵط�
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===����ṹ��
	typedef struct _DHT11_HandlerType DHT11_HandlerType;

	//===����ָ��ṹ��
	typedef struct _DHT11_HandlerType *pDHT11_HandlerType;

	//===�ṹ�嶨��
	struct _DHT11_HandlerType
	{
		UINT32_T msgTempX1000;                  //---�¶�
		UINT32_T msgHumiX1000;                  //---ʪ��
		UINT32_T msgBit;                        //---�˿����
		GPIO_TypeDef *msgPort;                  //---�˿ں�
		void(*msgFuncDelayus)(UINT32_T delay); //---us��ʱ����
		void(*msgFuncDelayms)(UINT32_T delay); //---ms��ʱ����
	};

	//===�����������
	#define DHT11_TASK_ONE pDHT11Device0
	#define DHT11_TASK_TWO 0
	#define DHT11_TASK_THREE 0

	//===�ⲿ���ýӿ�
	extern DHT11_HandlerType g_DHT11Device0;
	extern pDHT11_HandlerType pDHT11Device0;

	//===��������
	UINT8_T DHT11_Init(DHT11_HandlerType *DHT11x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
	UINT8_T DHT11_Device0_Init(DHT11_HandlerType *DHT11x);
	UINT8_T DHT11_Device1_Init(DHT11_HandlerType *DHT11x);
	UINT8_T DHT11_Device2_Init(DHT11_HandlerType *DHT11x);
	UINT8_T DHT11_DeInit(DHT11_HandlerType *DHT11x);
	UINT8_T DHT11_Read(DHT11_HandlerType *DHT11x);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DHT11_CFG_H_*/