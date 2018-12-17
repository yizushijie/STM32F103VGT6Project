#ifndef USART_CFG_H_
#define USART_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===ͷ�ļ�����
	#include "complier_lib.h"
	#ifdef USE_MCU_STM32
	#include "gpio_task.h"
	#endif
	#include "crc_task.h"

	typedef struct _USART_HandlerType						USART_HandlerType;
	typedef struct _USART_HandlerType						* pUSART_HandlerType;

	//===���ݽṹ��
	typedef struct _USART_HandlerDef						USART_HandlerDef;
	typedef struct _USART_HandlerDef						*pUSART_HandlerDef;

	//===�������ݽṹ��
	typedef struct _USART_HandlerDef						USART_RxHandlerType;
	typedef struct _USART_HandlerDef						*pUSART_RxHandlerType;

	//===�������ݽṹ��
	typedef struct _USART_HandlerDef						USART_TxHandlerType;
	typedef struct _USART_HandlerDef						*pUSART_TxHandlerType;

	//===�������ݽṹ�嶨��
	struct _USART_HandlerDef
	{
		VLTUINT8_T		msgCheckSum;							//---У���
		VLTUINT8_T		msgCRCFlag;								//---У���־λ  0 ---��У�飬1 ---У��ͣ�2---CRC8У�飬3---CRC16У�飬4---CRC32У��
		VLTUINT8_T		msgTaskState;							//---�ж������Ƿ���� 0---δ������1---����
		VLTUINT8_T		msgStep;								//---����
		VLTUINT16_T		msgIndexW;								//---д���
		VLTUINT16_T		msgIndexR;								//---�����
		VLTUINT16_T		msgCount;								//---��д���ݵĳ���
		VLTUINT16_T		msgSize;								//---���ݻ������Ĵ�С
		VLTUINT8_T		msgOverFlow;							//---��ʱ��־λ
		VLTUINT32_T		msgNowTime;								//---��ʱʱ�俪ʼ��
		VLTUINT32_T		msgEndTime;								//---��ʱʱ�����ֵ
		VLTUINT32_T		msgMaxTime;								//---��ʱʱ��
		UINT8_T			*pMsgVal;								//---������(��Ҫ��ǰ��������ݵĻ�����)
	};

	//===����������ж��ж��Ƿ���Ҫ��ʼ��GPIO
	#define  USART_INIT_GPIO

	//===�������ݶ���
	struct _USART_HandlerType
	{
		UINT8_T								msgIndex;			//---USART�˿ڵ�������
		UINT8_T								msgRxID;			//---���ձ�ͷ
		UINT8_T								msgTxID;			//---���ͱ�ͷ
		UINT8_T								msgID;				//---���ID
		UINT8_T								msgIDIndex;			//---�豸ID�������е�λ��
		UINT8_T								msgCmdIndex;		//---�����������е�λ��
		UINT8_T								msgDataOneIndex;	//---����1�������е�λ��
		UINT8_T								msgDataTwoIndex;	//---����2�������е�λ��
		UINT32_T							msgTxBit;			//---����GPIO�˿�
		GPIO_TypeDef						*msgTxPort;			//---USART��GPIO�˿ں�
		UINT32_T							msg485Bit;			//---485��ʹ��GPIO�˿�
		GPIO_TypeDef						*msg485Port;		//---485��ʹ��GPIO�˿�
		USART_TypeDef						*msgUSART;			//---USART�˿�
		USART_TxHandlerType					msgTxHandler;		//---���ͺ���
		USART_RxHandlerType					msgRxHandler;		//---���պ���
		UINT32_T(*msgFuncTick)(void);							//---���ڳ�ʱ����
	};

	//===�Ƿ���ӳ��printf����
	#define USE_USART_PRINTF

	//===��ӳ��printf֮������ݻ�����
	#ifdef USE_USART_PRINTF
	#define USART_PRINTF_SIZE					1024
	#endif

	//===ʹ�õ�У�鷽ʽ
	#define USART_CRC_NONE						0
	#define USART_CRC_CHECKSUM					1

	//===����ӦCRCУ��ȼ�
	#ifdef USE_CRC8
	#define USART_CRC_CRC8						2
	#elif defined(USART_CRC_CHECKSUM)
	#define USART_CRC_CRC8						USART_CRC_CHECKSUM
	#else
	#define USART_CRC_CRC8						USART_CRC_NONE
	#endif

	#ifdef USE_CRC16
	#define USART_CRC_CRC16						3
	#elif defined(USART_CRC_CHECKSUM)
	#define USART_CRC_CRC16						USART_CRC_CHECKSUM
	#else
	#define USART_CRC_CRC16						USART_CRC_NONE
	#endif

	#ifdef USE_CRC32
	#define USART_CRC_CRC32						4
	#elif defined(USART_CRC_CHECKSUM)
	#define USART_CRC_CRC32						USART_CRC_CHECKSUM
	#else
	#define USART_CRC_CRC32						USART_CRC_NONE
	#endif

	//===���Ͷ˿ڵ�����
	#define USART_TXGPIO_SET_INPUT					0
	#define USART_TXGPIO_SET_OUTPUT					1

	//===485���ݶ˿ڵĿ���ʹ��
	#define USART_485_RX_ENABLE						0
	#define USART_485_TX_ENABLE						1

	//===���ڵ�״̬
	#define USART_BUSY								0
	#define USART_OK								1
	#define USART_ERROR								2

	//===�����������
	#define USART_TASK_ONE							pUSART1
	#define USART_TASK_TWO							0
	#define USART_TASK_THREE						0

	//===�ⲿ���ýӿ�
	extern USART_HandlerType						g_USART1;
	extern pUSART_HandlerType						pUSART1;

	//===��������
	UINT8_T  USART_StructInit(USART_HandlerType*  USARTx);
	UINT8_T  USART_Init(USART_HandlerType*  USARTx, UINT16_T rxSize, UINT8_T* pRxVal, UINT8_T rxCRCFlag, UINT16_T txSize, UINT8_T* pTxVal, UINT8_T txCRCFlag, UINT32_T(*pTimerTick)(void));
	UINT8_T  USART_GPIOInit(USART_HandlerType*  USARTx, UINT8_T isInput);
	UINT8_T  USART_485GPIOInit(USART_HandlerType*  USARTx, UINT8_T isEnable);
	UINT8_T  USART_EnableCRC_RX(USART_HandlerType*USARTx, UINT8_T crcFlag);
	UINT8_T  USART_GetCRC_RX(USART_HandlerType*USARTx);
	UINT8_T  USART_EnableCRC_TX(USART_HandlerType*USARTx, UINT8_T crcFlag);
	UINT8_T  USART_GetCRC_TX(USART_HandlerType*USARTx);
	UINT8_T  USART_TimeTick_Init(USART_HandlerType*USARTx, UINT8_T isRx);
	UINT8_T  USART_TimeTick_DeInit(USART_HandlerType*USARTx, UINT8_T isRx);
	UINT8_T  USART_TimeTick_OVF(USART_HandlerType*USARTx, UINT32_T timeOut, UINT8_T isRx);
	UINT8_T  USART_TimeOVFTask(USART_HandlerType*USARTx, UINT8_T isRx);
	UINT8_T  USART_ITRead_8BitsTask(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USART_ITRead_16BitsTask(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USART_ITRead_Task(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USART_GetOVF(USART_HandlerType* USARTx, UINT8_T isRx);
	UINT8_T  USART_ClearOVF(USART_HandlerType* USARTx, UINT8_T isRx);
	UINT8_T  USART_PollMode_WriteByte(USART_HandlerType*USARTx, UINT8_T  val);
	UINT8_T  USART_PollMode_WriteData(USART_HandlerType*USARTx, char *pVal);
	UINT8_T  USART_PollMode_ReadByte(USART_HandlerType*USARTx);
	UINT8_T  USART_PollMode_ReadData(USART_HandlerType*USARTx, char *pVal);
	UINT8_T  USART_ITWrite_TXETask(USART_HandlerType*USARTx);
	UINT8_T  USART_ITWrite_TCTask(USART_HandlerType*USARTx);
	UINT8_T  USART_RealTime_AddByte(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USART_RealTime_AddByteSize(USART_HandlerType*USARTx, UINT16_T val);
	UINT8_T  USART_RealTime_AddByteCRC(USART_HandlerType*USARTx);
	UINT8_T  USART_FillMode_AddByte(USART_HandlerType*USARTx, UINT8_T val);
	UINT8_T  USART_FillMode_AddData(USART_HandlerType*USARTx, UINT8_T *pVal, UINT16_T length);
	UINT8_T  USART_CRCTask_Read(USART_HandlerType*USARTx);
	UINT8_T  USART_CRCTask_Write(USART_HandlerType*USARTx);
	UINT8_T  USART_FillMode_WriteSTART(USART_HandlerType*USARTx, UINT8_T isNeedID);
	UINT8_T  USART_GetReadState(USART_HandlerType* USARTx);
	UINT8_T  USART_ClearReadState(USART_HandlerType* USARTx);
	UINT8_T  USART_GetWriteState(USART_HandlerType* USARTx);
	UINT8_T  USART_ClearWriteState(USART_HandlerType* USARTx);
	UINT8_T  USART_ReadInit(USART_HandlerType*  USARTx);
	UINT8_T  USART_WriteInit(USART_HandlerType*  USARTx);
	UINT8_T USART_DeviceID(USART_HandlerType*USARTx);
	void     USART_Printf(USART_HandlerType*USARTx, char*fmt, ...);
	void	 USART_PrintfClockFreq(USART_HandlerType*USARTx);
	UINT8_T  USART_Clock(USART_TypeDef* USARTx, UINT8_T isEnable);
	UINT8_T  USART_DeInit(USART_HandlerType*USARTx);
	UINT8_T  USART_DeviceInit(USART_HandlerType *USARTx, UINT8_T id, UINT8_T idIndex, UINT8_T cmdIndex, UINT8_T d1Index, UINT8_T d2Index);
	UINT8_T  USART1_Init(USART_HandlerType*USARTx);
	UINT8_T  USART2_Init(USART_HandlerType*USARTx);
	UINT8_T  USART3_Init(USART_HandlerType*USARTx);

	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*USART_CFG_H_ */
