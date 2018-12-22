#ifndef GPIO_CFG_H_
#define GPIO_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===使用包含的头文件
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===设置端口为输出模式
	#define GPIO_SET_WRITE(	name, index )				LL_GPIO_SetPinMode(		name, index, LL_GPIO_MODE_OUTPUT)

	//===设置端口为输入模式
	#define GPIO_SET_READ(	name, index )				LL_GPIO_SetPinMode(		name, index, LL_GPIO_MODE_INPUT)

	//===设置端口输出高
	#define GPIO_OUT_1(	name, index )					LL_GPIO_SetOutputPin(   name, index )

	//===设置端口输出低
	#define GPIO_OUT_0(	name, index )					LL_GPIO_ResetOutputPin( name, index )

	//===设置端口输出取反
	#define GPIO_OUT_C(	name, index )					LL_GPIO_TogglePin(		name, index )

	//===获取端口的输入状态
	#define GPIO_GET_STATE(	name, index )				LL_GPIO_IsInputPinSet(	name, index )

	//===GPIO低八位的数据
	#define GPIO_L8BITS_OUT( name, val	)				( name->ODR=(name->ODR&0xFF00)|(val&0x00FF) )

	//===GPIO高八位的数据
	#define GPIO_H8BITS_OUT( name, val	)				( name->ODR=(name->ODR&0x00FF)|((val<<8)&0xFF00) )

	//===GPIO16位的数据
	#define GPIO_16BITS_OUT( name, val	)				( name->ODR=(val&0xFFFF) )

	//===定义结构体
	typedef struct _GPIO_HandlerType					GPIO_HandlerType;

	//===定义指针结构体
	typedef	struct _GPIO_HandlerType					*pGPIO_HandlerType;

	//===结构定义
	struct _GPIO_HandlerType
	{
		GPIO_TypeDef	*msgGPIOPort;																			//---端口
		UINT32_T		msgGPIOBit;																				//---序号
	};


	//===函数定义
	void GPIO_Clock(GPIO_TypeDef *GPIOx, UINT8_T isEnable);
	void GPIO_Init(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* GPIO_CFG_H_ */