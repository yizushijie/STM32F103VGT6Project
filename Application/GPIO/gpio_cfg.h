#ifndef GPIO_CFG_H_
#define GPIO_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	//===ʹ�ð�����ͷ�ļ�
	#include "complier_lib.h"
	//////////////////////////////////////////////////////////////////////////////////////
	//===���ö˿�Ϊ���ģʽ
	#define GPIO_SET_WRITE(	name, index )				LL_GPIO_SetPinMode(		name, index, LL_GPIO_MODE_OUTPUT)

	//===���ö˿�Ϊ����ģʽ
	#define GPIO_SET_READ(	name, index )				LL_GPIO_SetPinMode(		name, index, LL_GPIO_MODE_INPUT)

	//===���ö˿������
	#define GPIO_OUT_1(	name, index )					LL_GPIO_SetOutputPin(   name, index )

	//===���ö˿������
	#define GPIO_OUT_0(	name, index )					LL_GPIO_ResetOutputPin( name, index )

	//===���ö˿����ȡ��
	#define GPIO_OUT_C(	name, index )					LL_GPIO_TogglePin(		name, index )

	//===��ȡ�˿ڵ�����״̬
	#define GPIO_GET_STATE(	name, index )				LL_GPIO_IsInputPinSet(	name, index )

	//===GPIO�Ͱ�λ������
	#define GPIO_L8BITS_OUT( name, val	)				( name->ODR=(name->ODR&0xFF00)|(val&0x00FF) )

	//===GPIO�߰�λ������
	#define GPIO_H8BITS_OUT( name, val	)				( name->ODR=(name->ODR&0x00FF)|((val<<8)&0xFF00) )

	//===GPIO16λ������
	#define GPIO_16BITS_OUT( name, val	)				( name->ODR=(val&0xFFFF) )

	//===����ṹ��
	typedef struct _GPIO_HandlerType					GPIO_HandlerType;

	//===����ָ��ṹ��
	typedef	struct _GPIO_HandlerType					*pGPIO_HandlerType;

	//===�ṹ����
	struct _GPIO_HandlerType
	{
		GPIO_TypeDef	*msgGPIOPort;																			//---�˿�
		UINT32_T		msgGPIOBit;																				//---���
	};


	//===��������
	void GPIO_Clock(GPIO_TypeDef *GPIOx, UINT8_T isEnable);
	void GPIO_Init(void);
	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /* GPIO_CFG_H_ */