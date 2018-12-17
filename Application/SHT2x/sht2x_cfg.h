#ifndef SHT2X_CFG_H_
#define SHT2X_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "delay_task.h"
	#include "i2c_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	typedef enum
	{
		TRIG_TEMP_MEASUREMENT_HM = 0xE3,    //===触发温度测量，保持主机
		TRIG_HUMI_MEASUREMENT_HM = 0xE5,    //===触发湿度测量，保持主机
		TRIG_TEMP_MEASUREMENT_POLL = 0xF3,  //===触发温度测量，非保持主机
		TRIG_HUMI_MEASUREMENT_POLL = 0xF5,  //===触发温度测量，非保持主机
		USER_WRITE_REG = 0xE6,              //===写用户寄存器
		USER_READ_REG = 0xE7,               //===读用户寄存器
		SOFT_RESET_DEVICE = 0xFE            //===软件复位
	} SHT2XCMD;

	//===测量分辨率
	typedef enum
	{
		RES_12_14BIT = 0x00,  // RH=12bit, T=14bit
		RES_8_12BIT = 0x01,   // RH= 8bit, T=12bit
		RES_10_13BIT = 0x80,  // RH=10bit, T=13bit
		RES_11_11BIT = 0x81,  // RH=11bit, T=11bit
		RES_MASK = 0x81       // Mask for res. bits (7,0) in user reg.
	} SHT2XRES;

	//===电池状态
	typedef enum
	{
		EOB_ON = 0x40,   // end of battery
		EOB_MASK = 0x40  // Mask for EOB bit(6) in user reg.
	} SHT2XEOB;

	//===片上加热器的配置
	typedef enum
	{
		HOT_ON = 0x04,   // heater on
		HOT_OFF = 0x00,  // heater off
		HOT_MASK = 0x04  // Mask for Heater bit(2) in user reg.
	} SHT2xHOT;

	//===测量类型
	typedef enum
	{
		TEMP, HUMI
	} SHT2XType;

	//===结构体定义
	typedef struct _SHT2X_HandlerType SHT2X_HandlerType;

	//===指针结构体定义
	typedef struct _SHT2X_HandlerType *pSHT2X_HandlerType;

	//===SHT2X的数据结构体
	struct _SHT2X_HandlerType
	{
		UINT8_T msgSerialNumber[8 + 4 + 2];  //---设备序列号
		INT16_T msgTempX100;
		INT16_T msgHumiX100;
		I2C_HandlerType msgI2C;  //---使用的I2C
	};

	//===定义的任务函数
	#define SHT2X_TASK_ONE			pSHT2XDevice0
	#define SHT2X_TASK_TWO			0
	#define SHT2X_TASK_THREE		0

	//===外部调用接口
	extern SHT2X_HandlerType g_SHT2XDevice0;
	extern pSHT2X_HandlerType pSHT2XDevice0;

	//===函数定义
	UINT8_T SHT2X_I2C_Init(SHT2X_HandlerType *SHT2x, void(*msgDelay)(UINT32_T delay), UINT8_T isHWI2C);
	UINT8_T SHT2X_I2C_Device0_Init(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_I2C_Device1_Init(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_I2C_Device2_Init(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_I2C_DeInit(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_SWI2C_WriteCmd(SHT2X_HandlerType *SHT2x, UINT8_T cmd);
	UINT8_T SHT2X_HWI2C_WriteCmd(SHT2X_HandlerType *SHT2x, UINT8_T cmd);
	UINT8_T SHT2X_I2C_WriteCmd(SHT2X_HandlerType *SHT2x, UINT8_T cmd);
	UINT8_T SHT2X_I2C_SoftReset(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_SWI2C_GetSerialNumber(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_HWI2C_GetSerialNumber(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_I2C_GetSerialNumber(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_I2C_ReadUserReg(SHT2X_HandlerType *SHT2x, UINT8_T *pReg);
	UINT8_T SHT2X_I2C_WriteUserReg(SHT2X_HandlerType *SHT2x, UINT8_T reg);
	UINT8_T SHT2X_I2C_ReadPoll(SHT2X_HandlerType *SHT2x, UINT16_T *pVal, UINT8_T cmd);
	UINT8_T SHT2X_I2C_ReadTempPoll(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_I2C_ReadHumiPoll(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_I2C_ReadHM(SHT2X_HandlerType *SHT2x, UINT16_T *pVal, UINT8_T cmd);
	UINT8_T SHT2X_I2C_ReadTempHM(SHT2X_HandlerType *SHT2x);
	UINT8_T SHT2X_I2C_ReadHumiHM(SHT2X_HandlerType *SHT2x);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SHT2X_CFG_H_ */