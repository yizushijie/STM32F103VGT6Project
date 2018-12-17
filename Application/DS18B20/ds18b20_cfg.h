#ifndef DS18B20_CFG_H_
#define DS18B20_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#ifdef USE_MCU_STM32
	#include "delay_task.h"
	#endif
	#include "one_wire_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===����ṹ��
	typedef struct _DS18B20_HandlerType				DS18B20_HandlerType;

	//===����ָ��ṹ
	typedef struct _DS18B20_HandlerType				*pDS18B20_HandlerType;

	//===�ṹ����
	struct _DS18B20_HandlerType
	{
		UINT8_T					msgIsPositive;						//0---�����ݣ�1---�Ǹ�����2---����ֵ
		UINT16_T				msgTempX100;						//---�¶ȵ�ֵ���Ŵ�100����ֵ
		UINT32_T				msgTempX10000;						//---�¶ȵ�ֵ���Ŵ�1000����ֵ
		OneWire_HandlerType		msgOneWire;							//---һ��ͨ��
		void(*msgFuncDelayms)(UINT32_T delay);						//---ms��ʱ����
	};

	//===�����������
	#define DS18B20_TASK_ONE	pDS18B20Device0
	#define DS18B20_TASK_TWO	0
	#define DS18B20_TASK_THREE	0

	//===�ⲿ���ýӿ�
	extern DS18B20_HandlerType g_DS18B20Device0;
	extern pDS18B20_HandlerType pDS18B20Device0;

	//===�����Ķ���
	UINT8_T  DS18B20_OneWire_Init(DS18B20_HandlerType *DS18B20x, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay));
	UINT8_T  DS18B20_OneWire_Device0_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_Device1_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_Device2_Init(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_DeInit(DS18B20_HandlerType *DS18B20x);
	UINT8_T  DS18B20_OneWire_ReadDeviceID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
	UINT16_T DS18B20_OneWire_ReadTemp(DS18B20_HandlerType *DS18B20x);
	UINT16_T DS18B20_OneWire_ReadTempByID(DS18B20_HandlerType *DS18B20x, UINT8_T *_id);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*DS18B20_CFG_H_ */
