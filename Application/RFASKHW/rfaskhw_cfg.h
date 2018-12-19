#ifndef RFASKHW_CFG_H_
#define RFASKHW_CFG_H_
//////////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
	#endif
	//////////////////////////////////////////////////////////////////////////////////////
	#include "complier_lib.h"
	#include "gpio_task.h"
	//////////////////////////////////////////////////////////////////////////////////////
	
	//===YSEL0A
	#define YSEL0A_PORT_D					GPIOE
	#define YSEL0A_BIT_D					LL_GPIO_PIN_7

	//===YSEL1A
	#define YSEL1A_PORT_D					GPIOE
	#define YSEL1A_BIT_D					LL_GPIO_PIN_8

	//===YSEL2A
	#define YSEL2A_PORT_D					GPIOE
	#define YSEL2A_BIT_D					LL_GPIO_PIN_9

	//===YSEL3A
	#define YSEL3A_PORT_D					GPIOE
	#define YSEL3A_BIT_D					LL_GPIO_PIN_10

	//===YSEL0B
	#define YSEL0B_PORT_D					GPIOB
	#define YSEL0B_BIT_D					LL_GPIO_PIN_8

	//===YSEL1B
	#define YSEL1B_PORT_D					GPIOB
	#define YSEL1B_BIT_D					LL_GPIO_PIN_9

	//===YSEL2B
	#define YSEL2B_PORT_D					GPIOE
	#define YSEL2B_BIT_D					LL_GPIO_PIN_0

	//===YSEL3B
	#define YSEL3B_PORT_D					GPIOE
	#define YSEL3B_BIT_D					LL_GPIO_PIN_1

	//===YSEL0C
	#define YSEL0C_PORT_D					GPIOD
	#define YSEL0C_BIT_D					LL_GPIO_PIN_7

	//===YSEL1C
	#define YSEL1C_PORT_D					GPIOD
	#define YSEL1C_BIT_D					LL_GPIO_PIN_6

	//===YSEL2C
	#define YSEL2C_PORT_D					GPIOD	
	#define YSEL2C_BIT_D					LL_GPIO_PIN_5

	//===YSEL3C
	#define YSEL3C_PORT_D					GPIOD
	#define YSEL3C_BIT_D					LL_GPIO_PIN_4

	//===YSEL0D
	#define YSEL0D_PORT_D					GPIOD
	#define YSEL0D_BIT_D					LL_GPIO_PIN_15

	//===YSEL1D
	#define YSEL1D_PORT_D					GPIOD
	#define YSEL1D_BIT_D					LL_GPIO_PIN_14

	//===YSEL2D
	#define YSEL2D_PORT_D					GPIOD
	#define YSEL2D_BIT_D					LL_GPIO_PIN_13

	//===YSEL3D	
	#define YSEL3D_PORT_D					GPIOD
	#define YSEL3D_BIT_D					LL_GPIO_PIN_12

	//===SITEA的SOT，BIN，EOT,RST,DEC配置
	//===开始	
	#define SOTA_PORT_D					GPIOE
	#define	SOTA_BIT_D					LL_GPIO_PIN_11

	//===结束
	#define EOTA_PORT_D					GPIOE
	#define	EOTA_BIT_D					LL_GPIO_PIN_12

	//===结果标志 0---通过，1---失效
	#define BINA_PORT_D					GPIOE
	#define	BINA_BIT_D					LL_GPIO_PIN_13

	//===解码触发，0---触发解码，1---不解码
	#define RSTA_PORT_D					GPIOE	
	#define	RSTA_BIT_D					LL_GPIO_PIN_14

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECA_PASS_PORT_D			GPIOE	
	#define	DECA_PASS_BIT_D				LL_GPIO_PIN_15

	//===SITEB的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTB_PORT_D					GPIOE	
	#define	SOTB_BIT_D					LL_GPIO_PIN_2

	//===结束
	#define EOTB_PORT_D					GPIOE	
	#define	EOTB_BIT_D					LL_GPIO_PIN_3

	//===结果标志 0---通过，1---失效
	#define BINB_PORT_D					GPIOE	
	#define	BINB_BIT_D					LL_GPIO_PIN_4

	//===解码触发，0---触发解码，1---不解码
	#define RSTB_PORT_D					GPIOE
	#define	RSTB_BIT_D					LL_GPIO_PIN_5

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECB_PASS_PORT_D				GPIOE	
	#define	DECB_PASS_BIT_D				LL_GPIO_PIN_6

	//===SITEC的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTC_PORT_D					GPIOD	
	#define	SOTC_BIT_D					LL_GPIO_PIN_3

	//===结束
	#define EOTC_PORT_D					GPIOD	
	#define	EOTC_BIT_D					LL_GPIO_PIN_2

	//===结果标志 0---通过，1---失效
	#define BINC_PORT_D					GPIOD	
	#define	BINC_BIT_D					LL_GPIO_PIN_1

	//===解码触发，0---触发解码，1---不解码
	#define RSTC_PORT_D					GPIOD
	#define	RSTC_BIT_D					LL_GPIO_PIN_0

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECC_PASS_PORT_D				GPIOC	
	#define	DECC_PASS_BIT_D				LL_GPIO_PIN_12

	//===SITED的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTD_PORT_D					GPIOD	
	#define	SOTD_BIT_D					LL_GPIO_PIN_11

	//===结束
	#define EOTD_PORT_D					GPIOD	
	#define	EOTD_BIT_D					LL_GPIO_PIN_10

	//===结果标志 0---通过，1---失效
	#define BIND_PORT_D					GPIOD	
	#define	BIND_BIT_D					LL_GPIO_PIN_9

	//===解码触发，0---触发解码，1---不解码
	#define RSTD_PORT_D					GPIOD
	#define	RSTD_BIT_D					LL_GPIO_PIN_8

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECD_PASS_PORT_D			GPIOB	
	#define	DECD_PASS_BIT_D				LL_GPIO_PIN_15

	//===YSEL0A
	#define YSEL0A_PORT					DECA_PASS_PORT_D
	#define YSEL0A_BIT					DECA_PASS_BIT_D

	//===YSEL1A
	#define YSEL1A_PORT					RSTA_PORT_D
	#define YSEL1A_BIT					RSTA_BIT_D

	//===YSEL2A
	#define YSEL2A_PORT					BINA_PORT_D
	#define YSEL2A_BIT					BINA_BIT_D

	//===YSEL3A
	#define YSEL3A_PORT					EOTA_PORT_D
	#define YSEL3A_BIT					EOTA_BIT_D

	//===YSEL0B
	#define YSEL0B_PORT					DECB_PASS_PORT_D
	#define YSEL0B_BIT					DECB_PASS_BIT_D
	
	//===YSEL1B
	#define YSEL1B_PORT					RSTB_PORT_D
	#define YSEL1B_BIT					RSTB_BIT_D
	
	//===YSEL2B
	#define YSEL2B_PORT					BINB_PORT_D
	#define YSEL2B_BIT					BINB_BIT_D
	
	//===YSEL3B
	#define YSEL3B_PORT					EOTB_PORT_D
	#define YSEL3B_BIT					EOTB_BIT_D

	//===YSEL0C
	#define YSEL0C_PORT					GPIOD
	#define YSEL0C_BIT					LL_GPIO_PIN_7

	//===YSEL1C
	#define YSEL1C_PORT					GPIOD
	#define YSEL1C_BIT					LL_GPIO_PIN_6

	//===YSEL2C
	#define YSEL2C_PORT					GPIOD	
	#define YSEL2C_BIT					LL_GPIO_PIN_5

	//===YSEL3C
	#define YSEL3C_PORT					GPIOD
	#define YSEL3C_BIT					LL_GPIO_PIN_4

	//===YSEL0D
	#define YSEL0D_PORT					GPIOD
	#define YSEL0D_BIT					LL_GPIO_PIN_15

	//===YSEL1D
	#define YSEL1D_PORT					GPIOD
	#define YSEL1D_BIT					LL_GPIO_PIN_14

	//===YSEL2D
	#define YSEL2D_PORT					GPIOD
	#define YSEL2D_BIT					LL_GPIO_PIN_13

	//===YSEL3D	
	#define YSEL3D_PORT					GPIOD
	#define YSEL3D_BIT					LL_GPIO_PIN_12

	//===SITEA的SOT，BIN，EOT,RST,DEC配置
	//===开始	
	#define SOTA_PORT					SOTA_PORT_D
	#define	SOTA_BIT					SOTA_BIT_D

	//===结束
	#define EOTA_PORT					YSEL3A_PORT_D
	#define	EOTA_BIT					YSEL3A_BIT_D

	//===结果标志 0---通过，1---失效
	#define BINA_PORT					YSEL2A_PORT_D
	#define	BINA_BIT					YSEL2A_BIT_D

	//===解码触发，0---触发解码，1---不解码
	#define RSTA_PORT					YSEL1A_PORT_D
	#define	RSTA_BIT					YSEL1A_BIT_D
	
	//===解码成功标志，0---解码成功，1---解码失败
	#define DECA_PASS_PORT				YSEL0A_PORT_D
	#define	DECA_PASS_BIT				YSEL0A_BIT_D

	//===SITEB的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTB_PORT					SOTB_PORT_D
	#define	SOTB_BIT					SOTB_BIT_D
	
	//===结束
	#define EOTB_PORT					YSEL3B_PORT_D
	#define	EOTB_BIT					YSEL3B_BIT_D
	
	//===结果标志 0---通过，1---失效
	#define BINB_PORT					YSEL2B_PORT_D
	#define	BINB_BIT					YSEL2B_BIT_D
	
	//===解码触发，0---触发解码，1---不解 码
	#define RSTB_PORT					YSEL1B_PORT_D
	#define	RSTB_BIT					YSEL1B_BIT_D
	
	//===解码成功标志，0---解码成功，1--- 解码失败
	#define DECB_PASS_PORT				YSEL0B_PORT_D
	#define	DECB_PASS_BIT				YSEL0B_BIT_D

	//===SITEC的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTC_PORT					GPIOD	
	#define	SOTC_BIT					LL_GPIO_PIN_3

	//===结束
	#define EOTC_PORT					GPIOD	
	#define	EOTC_BIT					LL_GPIO_PIN_2

	//===结果标志 0---通过，1---失效
	#define BINC_PORT					GPIOD	
	#define	BINC_BIT					LL_GPIO_PIN_1

	//===解码触发，0---触发解码，1---不解码
	#define RSTC_PORT					GPIOD
	#define	RSTC_BIT					LL_GPIO_PIN_0

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECC_PASS_PORT				GPIOC	
	#define	DECC_PASS_BIT				LL_GPIO_PIN_12

	//===SITED的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTD_PORT					GPIOD	
	#define	SOTD_BIT					LL_GPIO_PIN_11

	//===结束
	#define EOTD_PORT					GPIOD	
	#define	EOTD_BIT					LL_GPIO_PIN_10

	//===结果标志 0---通过，1---失效
	#define BIND_PORT					GPIOD	
	#define	BIND_BIT					LL_GPIO_PIN_9

	//===解码触发，0---触发解码，1---不解码
	#define RSTD_PORT					GPIOD
	#define	RSTD_BIT					LL_GPIO_PIN_8

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECD_PASS_PORT				GPIOB	
	#define	DECD_PASS_BIT				LL_GPIO_PIN_15


	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RFASKHW_CFG_H_ */
