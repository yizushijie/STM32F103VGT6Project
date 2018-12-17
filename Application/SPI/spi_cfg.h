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

	//===����ṹ��
	typedef struct _SPI_HandlerType					SPI_HandlerType;

	//===����ָ��ṹ��
	typedef	struct _SPI_HandlerType					*pSPI_HandlerType;

	//===�ṹ����
	struct _SPI_HandlerType
	{
		GPIO_HandlerType	msgMOSI;					//---MOSI
		GPIO_HandlerType	msgMISO;					//---MISO
		GPIO_HandlerType	msgSCK;						//---SCK
		GPIO_HandlerType	msgCS;						//---CS
		SPI_TypeDef			*msgSPIx;					//---ʹ�õ�Ӳ��SPI�ӿ�
		UINT8_T				msgModelIsHW;				//---����ģʽ��Ĭ�������ģ��---0��Ӳ��ģʽ---1
		UINT16_T			msgPluseWidth;				//---�����ȣ����ģ��ʹ��
		UINT32_T			msgClockSpeed;				//---Ӳ��SPI��ʱ���ٶ�
		UINT32_T			msgGPIOAlternate;			//---GPIO�ĸ���ģʽ
		UINT32_T			msgStandard;				//---ʹ�õ�SPIЭ��
		void(*msgFuncDelay)(UINT32_T delay);			//---��ʱ����
		UINT32_T(*msgFuncTick)(void);					//---���ڳ�ʱ����
	};

	//===��������
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
