#ifndef AT24CXX_CFG_H_
#define AT24CXX_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
////如果在单页的范围内，存储地址累加，若超过该页的最大地址，存储地址回到页开始处。
////所以对于连续读和连续写而言，最大的操作字节数为8。
////若需要操作的字节内容超过8字节，则需要进行翻页操作，即写入下一页的起始存储地址
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
	//===支持的系列型号
	#define AT24C01 0  //---16PX8B
	#define AT24C02 1  //---32PX8B
	#define AT24C04 2  //---32PX16B
	#define AT24C08 3  //---64PX16B
	#define AT24C16 4  //---128PX16B
	#define AT24C32 5
	#define AT24C64 6
	#define AT24C128 7
	#define AT24C256 8

	//===结构体定义
	typedef struct _AT24CXX_HandlerType AT24CXX_HandlerType;

	//===指针结构体定义
	typedef struct _AT24CXX_HandlerType *pAT24CXX_HandlerType;

	//===PCF853的数据结构体
	struct _AT24CXX_HandlerType
	{
		UINT8_T msgAT24CXXType;      //---使用的设备
		UINT8_T msgAT24CXXPageNum;   //---页数
		UINT8_T msgAT24CXXPageByte;  //---每页字节数
		I2C_HandlerType msgI2C;      //---使用的I2C
	};

	//===定义的任务函数
	#define AT24CXX_TASK_ONE pAT24CXXDevice0
	#define AT24CXX_TASK_TWO 0
	#define AT24CXX_TASK_THREE 0

	//===外部调用接口
	extern AT24CXX_HandlerType g_AT24CXXDevice0;
	extern pAT24CXX_HandlerType pAT24CXXDevice0;

	//===函数定义
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