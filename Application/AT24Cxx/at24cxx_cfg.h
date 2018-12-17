#ifndef AT24CXX_CFG_H_
#define AT24CXX_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
////����ڵ�ҳ�ķ�Χ�ڣ��洢��ַ�ۼӣ���������ҳ������ַ���洢��ַ�ص�ҳ��ʼ����
////���Զ���������������д���ԣ����Ĳ����ֽ���Ϊ8��
////����Ҫ�������ֽ����ݳ���8�ֽڣ�����Ҫ���з�ҳ��������д����һҳ����ʼ�洢��ַ
/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===֧�ֵ�ϵ���ͺ�
	#define AT24C01 0  //---16PX8B
	#define AT24C02 1  //---32PX8B
	#define AT24C04 2  //---32PX16B
	#define AT24C08 3  //---64PX16B
	#define AT24C16 4  //---128PX16B
	#define AT24C32 5
	#define AT24C64 6
	#define AT24C128 7
	#define AT24C256 8

	//===�ṹ�嶨��
	typedef struct _AT24CXX_HandlerType AT24CXX_HandlerType;

	//===ָ��ṹ�嶨��
	typedef struct _AT24CXX_HandlerType *pAT24CXX_HandlerType;

	//===PCF853�����ݽṹ��
	struct _AT24CXX_HandlerType
	{
		UINT8_T msgAT24CXXType;      //---ʹ�õ��豸
		UINT8_T msgAT24CXXPageNum;   //---ҳ��
		UINT8_T msgAT24CXXPageByte;  //---ÿҳ�ֽ���
		I2C_HandlerType msgI2C;      //---ʹ�õ�I2C
	};

	//===�����������
	#define AT24CXX_TASK_ONE pAT24CXXDevice0
	#define AT24CXX_TASK_TWO 0
	#define AT24CXX_TASK_THREE 0

	//===�ⲿ���ýӿ�
	extern AT24CXX_HandlerType g_AT24CXXDevice0;
	extern pAT24CXX_HandlerType pAT24CXXDevice0;

	//===��������
	UINT8_T AT24CXX_Init(AT24CXX_HandlerType *AT24CXXx, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T AT24CXX_Device0_Init(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXX_Device1_Init(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXX_Device2_Init(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXX_DeInit(AT24CXX_HandlerType *AT24CXXx);
	UINT8_T AT24CXX_SWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val);
	UINT8_T AT24CXX_SWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_HWI2C_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val);
	UINT8_T AT24CXX_HWI2C_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T pageAddr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_WriteOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T val);
	UINT8_T AT24CXX_WritePageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_SWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal);
	UINT8_T AT24CXX_SWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_HWI2C_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal);
	UINT8_T AT24CXX_HWI2C_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);
	UINT8_T AT24CXX_ReadOneByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal);
	UINT8_T AT24CXX_ReadPageByte(AT24CXX_HandlerType *AT24CXXx, UINT16_T addr, UINT8_T *pVal, UINT16_T length);

	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* AT24CXX_CFG_H_ */