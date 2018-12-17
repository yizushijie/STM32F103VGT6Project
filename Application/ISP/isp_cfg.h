#ifndef ISP_CFG_H_
#define ISP_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "spi_task.h"
	#include "systick_task.h"
	#include "delay_task.h"

	//////////////////////////////////////////////////////////////////////////////////////
	//===��̿�ѡ���ʱ��
	#define ISP_SCK_AUTO						0	//---�Զ�
	#define ISP_SCK_KHZ_0_5						1	//---1ms
	#define ISP_SCK_KHZ_1						2	//---500us
	#define ISP_SCK_KHZ_2						3	//---250us
	#define ISP_SCK_KHZ_4						4	//---125us
	#define ISP_SCK_KHZ_8						5	//---64us
	#define ISP_SCK_KHZ_16						6	//---32us
	#define ISP_SCK_KHZ_32						7	//---16us
	#define ISP_SCK_KHZ_64						8	//---8us
	#define ISP_SCK_PRE_256						9	//---84M/256
	#define ISP_SCK_PRE_128						10	//---84M/128
	#define ISP_SCK_PRE_64						11	//---84M/64
	#define ISP_SCK_PRE_32						12	//---84M/32
	#define ISP_SCK_PRE_16						13	//---84M/16
	#define ISP_SCK_PRE_8						14	//---84M/8
	#define ISP_SCK_PRE_4						15	//---84M/4
	#define ISP_SCK_PRE_2						16	//---84M/2

	//===���ı��ʱ��
	#define ISP_SCK_MAX_CLOCK					ISP_SCK_PRE_256
	#define ISP_SCK_AUTO_MAX_COUNT				16

	//===����ṹ��
	typedef struct _ISP_HandlerType				ISP_HandlerType;

	//===����ָ��ṹ��
	typedef	struct _ISP_HandlerType				*pISP_HandlerType;

	//===�ṹ����
	struct _ISP_HandlerType
	{
		UINT8_T msgInit;						//---�ж��Ƿ��ʼ������ 0---δ��ʼ����1---��ʼ��
		UINT8_T msgSetClok;						//---���õı��ʱ��
		UINT8_T msgDelay;						//---���֮�����ʱ��������λ��ms
		UINT8_T msgHideAddr;					//---�Ӵ�64K������
		UINT8_T msgWriteData[4];				//---��������
		UINT8_T msgReadData[4];					//---��ȡ����
		void(*msgFuncDelay)(UINT32_T delay);	//---��ʱ����
		SPI_HandlerType msgSPI;					//---ʹ�õ�SPIģʽ
	};

	#define ISP_TASK_ONE		pISPDevice0
	#define ISP_TASK_TWO		0
	#define ISP_TASK_THREE		0

	//===�ⲿ���ýӿ�
	extern ISP_HandlerType g_ISPDevice0;
	extern pISP_HandlerType pISPDevice0;

	//===��������
	UINT8_T ISP_HW_Init(ISP_HandlerType *ISPx);
	UINT8_T ISP_SW_Init(ISP_HandlerType *ISPx);
	UINT8_T ISP_Init(ISP_HandlerType *ISPx, void(*Delayus)(UINT32_T delay), void(*Delayms)(UINT32_T delay), UINT32_T(*pTimerTick)(void));
	UINT8_T ISP_DeInit(ISP_HandlerType *ISPx);
	UINT8_T ISP_SetClock(ISP_HandlerType *ISPx, UINT8_T clok);
	UINT8_T ISP_SW_SendCmd(ISP_HandlerType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4);
	UINT8_T ISP_HW_SendCmd(ISP_HandlerType *ISPx, UINT8_T val1, UINT8_T Val2, UINT8_T val3, UINT8_T val4);
	UINT8_T ISP_PreEnterProg(ISP_HandlerType *ISPx);
	UINT8_T ISP_EnterProg(ISP_HandlerType *ISPx);
	UINT8_T ISP_ExitProg(ISP_HandlerType *ISPx);
	UINT8_T ISP_ReadReady(ISP_HandlerType *ISPx);
	UINT8_T ISP_EraseChip(ISP_HandlerType *ISPx);
	UINT8_T ISP_ReadChipID(ISP_HandlerType *ISPx, UINT8_T *pVal);
	UINT8_T ISP_ReadChipCalibration(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T length);
	UINT8_T ISP_ReadChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISP_ReadChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal);
	UINT8_T ISP_ReadChipRom(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T addr, UINT16_T length);
	UINT8_T ISP_WriteChipFuse(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T isNeedExternFuse);
	UINT8_T ISP_WriteChipLock(ISP_HandlerType *ISPx, UINT8_T *pVal);
	UINT8_T ISP_ReadChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_ReadChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISP_WriteChipEepromAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_WriteChipEepromLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISP_WriteChipEepromAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_WriteChipEepromLongAddrWithJumpEmpty(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT16_T addr, UINT16_T length);
	UINT8_T ISP_UpdateExternAddr(ISP_HandlerType *ISPx, UINT8_T addr);
	UINT8_T ISP_UpdateExternLongAddr(ISP_HandlerType *ISPx, UINT32_T addr);
	UINT8_T ISP_ReadChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr, UINT16_T length);
	UINT8_T ISP_ReadChipFlashLongAddr(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT32_T addr, UINT16_T length);
	UINT8_T ISP_UpdateChipFlashBuffer(ISP_HandlerType *ISPx, UINT8_T *pVal, UINT8_T index, UINT16_T length);
	UINT8_T ISP_UpdateChipFlashAddr(ISP_HandlerType *ISPx, UINT8_T externAddr, UINT8_T highAddr, UINT8_T lowAddr);
	UINT8_T ISP_UpdateChipFlashLongAddr(ISP_HandlerType *ISPx, UINT32_T addr);

	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*ISP_CFG_H_ */
