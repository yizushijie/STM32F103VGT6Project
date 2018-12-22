#ifndef SPI_LIB_H_
#define SPI_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "spi_cfg.h"

	//===º¯Êý¶¨Òå
	UINT8_T SPILib_MHW_PollMode_Init(SPI_HandlerType *SPIx, LL_SPI_InitTypeDef SPI_InitStruct);
	void SPILib_MHW_SetTransferBitOrder(SPI_HandlerType *SPIx, UINT32_T BitOrder);
	UINT8_T SPILib_MHW_GPIO_Init(SPI_HandlerType *SPIx);
	UINT8_T SPILib_MSW_GPIO_Init(SPI_HandlerType *SPIx);
	UINT8_T SPILib_GPIO_DeInit(SPI_HandlerType *SPIx);
	UINT8_T SPILib_DeInit(SPI_HandlerType *SPIx);
	UINT8_T SPILib_MHW_PollMode_WriteByte(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPILib_MHW_PollMode_WriteData(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	UINT8_T SPILib_MSW_WriteBitMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPILib_MSW_WriteBitLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPILib_MSW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock);
	UINT8_T SPILib_MHW_SetClock(SPI_HandlerType *SPIx, UINT32_T clock);
	UINT8_T SPILib_MSW_WriteByteMSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPILib_MSW_WriteByteLSB(SPI_HandlerType *SPIx, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPILib_MSW_WriteDataMSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	UINT8_T SPILib_MSW_WriteDataLSB(SPI_HandlerType *SPIx, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SPI_LIB_H_ */
