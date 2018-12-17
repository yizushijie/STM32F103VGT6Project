#ifndef SPI_LIB_H_
#define SPI_LIB_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "spi_cfg.h"

	//===º¯Êý¶¨Òå
	UINT8_T SPILib_MHW_PollMode_Init(SPI_HandlerType *spix, LL_SPI_InitTypeDef SPI_InitStruct);
	UINT8_T SPILib_MHW_GPIO_Init(SPI_HandlerType *spix);
	UINT8_T SPILib_MSW_GPIO_Init(SPI_HandlerType *spix);
	UINT8_T SPILib_GPIO_DeInit(SPI_HandlerType *spix);
	UINT8_T SPILib_DeInit(SPI_HandlerType *spix);
	UINT8_T SPILib_MHW_PollMode_WriteByte(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPILib_MHW_PollMode_WriteData(SPI_HandlerType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	UINT8_T SPILib_MSW_WriteBit(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPILib_MSW_SetClock(SPI_HandlerType *spix, UINT32_T clock);
	UINT8_T SPILib_MHW_SetClock(SPI_HandlerType *spix, UINT32_T clock);
	UINT8_T SPILib_MSW_WriteByte(SPI_HandlerType *spix, UINT8_T wVal, UINT8_T *pRVal);
	UINT8_T SPILib_MSW_WriteData(SPI_HandlerType *spix, UINT8_T *pWVal, UINT8_T *pRVal, UINT16_T length);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*SPI_LIB_H_ */
