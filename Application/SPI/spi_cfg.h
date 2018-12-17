#ifndef SPI_CFG_H_
#define SPI_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	#include "delay_task.h"
	#include "systick_task.h"

	//===定义结构体
	typedef struct _SPI_HandlerType					SPI_HandlerType;

	//===定义指针结构体
	typedef	struct _SPI_HandlerType					*pSPI_HandlerType;

	//===结构定义
	struct _SPI_HandlerType
	{
		GPIO_HandlerType	msgMOSI;					//---MOSI
		GPIO_HandlerType	msgMISO;					//---MISO
		GPIO_HandlerType	msgSCK;						//---SCK
		GPIO_HandlerType	msgCS;						//---CS
		SPI_TypeDef			*msgSPIx;					//---使用的硬件SPI接口
		UINT8_T				msgModelIsHW;				//---工作模式，默认是软件模拟---0，硬件模式---1
		UINT16_T			msgPluseWidth;				//---脉冲宽度，软件模拟使用
		UINT32_T			msgClockSpeed;				//---硬件SPI的时钟速度
		UINT32_T			msgGPIOAlternate;			//---GPIO的复用模式
		UINT32_T			msgStandard;				//---使用的SPI协议
		void(*msgFuncDelay)(UINT32_T delay);			//---延时参数
		UINT32_T(*msgFuncTick)(void);					//---用于超时计数
	};

	//===函数定义
	UINT8_T SPI_MHW_PollMode_Init(SPI_HandlerType *spix, LL_SPI_InitTypeDef SPI_InitStruct);
	UINT8_T SPI_MHW_GPIO_Init(SPI_HandlerType *spix);
	UINT8_T SPI_MSW_GPIO_Init(SPI_HandlerType *spix);
	UINT8_T SPI_GPIO_DeInit(SPI_HandlerType *spix);
	UINT8_T SPI_DeInit(SPI_HandlerType *spix);
	UINT8_T SPI_Clock(SPI_HandlerType *spix, UINT8_T isEnable);
	UINT8_T SPI_MHW_PollMode_WriteByte(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPI_MHW_PollMode_WriteData(SPI_HandlerType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	UINT8_T SPI_MSW_WriteBit(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPI_MSW_SetClock(SPI_HandlerType *spix, UINT32_T clock);
	UINT8_T SPI_MHW_SetClock(SPI_HandlerType *spix, UINT32_T clock);
	UINT8_T SPI_MSW_WriteByte(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPI_MSW_WriteData(SPI_HandlerType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);

	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SPI_CFG_H_ */
