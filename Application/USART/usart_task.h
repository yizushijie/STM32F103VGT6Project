#ifndef USART_TASK_H_
#define USART_TASK_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===ͷ�ļ�����
	#include "usart_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////����1�����ò�����ʼ//////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//===���建�����Ĵ�С
	#define USART1_RX_BASE_SIZE						1800
	#define USART1_TX_BASE_SIZE						USART1_RX_BASE_SIZE

	//===�����豸�ĵ�ַ�����豸��ʱ��ʹ�ã�0��ʱ����һ��һ
	#define USART1_DEVICE_ID						0x00

	//===�����豸ID������
	#if (USART1_DEVICE_ID!=0)
	#define	USART1_DEVICE_ID_INDEX				1
	#else
	#define	USART1_DEVICE_ID_INDEX				0
	#endif

	//===������CRCʹ�õ���󻺴���,�������ڸ���CRCУ��ĸ�ʽ
	#if defined(USE_CRC32)
	#define USART1_RX_MAX_SIZE						( USART1_RX_BASE_SIZE+4 )
	#elif defined(USE_CRC16)
	#define USART1_RX_MAX_SIZE						( USART1_RX_BASE_SIZE+2 )
	#elif defined(USE_CRC8)||defined(USE_CHECKSUM)
	#define USART1_RX_MAX_SIZE						( USART1_RX_BASE_SIZE+1 )
	#else
	#define USART1_RX_MAX_SIZE						( USART1_RX_BASE_SIZE )
	#endif

	//===������CRCʹ�õ���󻺴���,�������ڸ���CRCУ��ĸ�ʽ
	#if defined(USE_CRC32)
	#define USART1_TX_MAX_SIZE						( USART1_TX_BASE_SIZE+4 )
	#elif defined(USE_CRC16)
	#define USART1_TX_MAX_SIZE						( USART1_TX_BASE_SIZE+2 )
	#elif defined(USE_CRC8)||defined(USE_CHECKSUM)
	#define USART1_TX_MAX_SIZE						( USART1_TX_BASE_SIZE+1 )
	#else
	#define USART1_TX_MAX_SIZE						( USART1_TX_BASE_SIZE )
	#endif

	//===���������еĺ���
	#if (USART1_RX_MAX_SIZE>0xFB)

		//===�豸��ַ�������е�λ��
	#define USART1_ID_INDEX						3

	//===Э���е�����1---������
	#define USART1_CMD_INDEX					( USART1_ID_INDEX+USART1_DEVICE_ID_INDEX)

	//===Э���е�����2---������
	#define USART1_DATA1_INDEX					( USART1_CMD_INDEX+1 )

	//===���ݷ��ص�ֵ---�Խ�����Ч���Է�����Ч
	#define USART1_DATA2_INDEX					( USART1_CMD_INDEX+2 )
	#else

		//===�豸��ַ�������е�λ��
	#define USART1_ID_INDEX						2

	//===Э���е�����1---������
	#define USART1_CMD_INDEX					( USART1_ID_INDEX+USART1_DEVICE_ID_INDEX)

	//===Э���е�����2---����������һ������
	#define USART1_DATA1_INDEX					( USART1_CMD_INDEX+1 )

	//===Э���еĵ�һ�����ݻ���ڶ�����
	#define USART1_DATA2_INDEX					( USART1_CMD_INDEX+2 )
	#endif

	//===�ⲿ���ýӿ�
	extern UINT8_T USART1_RX_BUFFER[USART1_RX_MAX_SIZE];
	extern UINT8_T USART1_TX_BUFFER[USART1_TX_MAX_SIZE];
	//////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////����1�����ò�������//////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//===��������
	UINT8_T  USARTTask_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void));
	UINT8_T  USARTTask_DeInit(USART_HandlerType*  USARTx);
	UINT8_T  USARTTask_DeviceInit(USART_HandlerType *USARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index);
	UINT8_T  USARTTask_ReadInit(USART_HandlerType*  USARTx);
	UINT8_T  USARTTask_GetReadState(USART_HandlerType* USARTx);
	UINT8_T  USARTTask_ClearReadState(USART_HandlerType* USARTx);
	UINT8_T  USARTTask_GetWriteState(USART_HandlerType* USARTx);
	UINT8_T  USARTTask_ClearWriteState(USART_HandlerType* USARTx);
	UINT8_T  USARTTask_TimeOVFTask(USART_HandlerType*USARTx);
	UINT8_T  USARTTask_ITRead_8BitsTask(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USARTTask_ITRead_16BitsTask(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USARTTask_ITRead_Task(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USARTTask_WriteInit(USART_HandlerType*USARTx);
	UINT8_T  USARTTask_ITWrite_TXETask(USART_HandlerType*USARTx);
	UINT8_T  USARTTask_ITWrite_TCTask(USART_HandlerType*USARTx);
	UINT8_T  USARTTask_RealTime_AddByte(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USARTTask_RealTime_AddByteSize(USART_HandlerType*USARTx, UINT16_T val);
	UINT8_T  USARTTask_RealTime_AddByteCRC(USART_HandlerType*USARTx);
	UINT8_T  USARTTask_FillMode_AddByte(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USARTTask_FillMode_AddData(USART_HandlerType*USARTx, UINT8_T *pVal, UINT16_T length);
	UINT8_T  USARTTask_CRCTask_Read(USART_HandlerType*USARTx);
	UINT8_T  USARTTask_CRCTask_Write(USART_HandlerType*USARTx);
	UINT8_T  USARTTask_FillMode_WriteSTART(USART_HandlerType*USARTx, UINT8_T isNeedID);
	UINT8_T  USARTTask_PollMode_WriteByte(USART_HandlerType*USARTx, UINT8_T  val);
	UINT8_T  USARTTask_PollMode_WriteData(USART_HandlerType*USARTx, char *pVal);
	UINT8_T	 USARTTask_DeviceID(USART_HandlerType*USARTx);
	UINT8_T  USARTTask_FuncTask(USART_HandlerType*USARTx, UINT8_T(*pFuncTask)(UINT8_T *, UINT8_T *));
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*USART_LIB_H_ */
