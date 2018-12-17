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
	#define YSEL0A_PORT	
	#define YSEL0A_BIT	

	//===YSEL1A
	#define YSEL1A_PORT	
	#define YSEL1A_BIT	

	//===YSEL2A
	#define YSEL2A_PORT	
	#define YSEL2A_BIT	

	//===YSEL3A
	#define YSEL3A_PORT	
	#define YSEL3A_BIT	

	//===YSEL0B
	#define YSEL0B_PORT	
	#define YSEL0B_BIT	

	//===YSEL1B
	#define YSEL1B_PORT	
	#define YSEL1B_BIT	

	//===YSEL2B
	#define YSEL2B_PORT	
	#define YSEL2B_BIT	

	//===YSEL3B
	#define YSEL3B_PORT	
	#define YSEL3B_BIT	

	//===YSEL0C
	#define YSEL0C_PORT	
	#define YSEL0C_BIT	

	//===YSEL1C
	#define YSEL1C_PORT	
	#define YSEL1C_BIT	

	//===YSEL2C
	#define YSEL2C_PORT	
	#define YSEL2C_BIT	

	//===YSEL3C
	#define YSEL3C_PORT	
	#define YSEL3C_BIT	

	//===YSEL0D
	#define YSEL0D_PORT	
	#define YSEL0D_BIT	

	//===YSEL1D
	#define YSEL1D_PORT	
	#define YSEL1D_BIT	

	//===YSEL2D
	#define YSEL2D_PORT	
	#define YSEL2D_BIT	

	//===YSEL3D
	#define YSEL3D_PORT	
	#define YSEL3D_BIT	

	//===SITEA的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTA_POTRT
	#define	SOTA_BIT

	//===结束
	#define EOTA_POTRT
	#define	EOTA_BIT

	//===结果标志 0---通过，1---失效
	#define BINA_POTRT
	#define	BINA_BIT

	//===解码触发，0---触发解码，1---不解码
	#define RSTA_POTRT
	#define	RSTA_BIT

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECA_PASS_POTRT
	#define	DECA_PASS_BIT

	//===SITEB的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTB_POTRT
	#define	SOTB_BIT

	//===结束
	#define EOTB_POTRT
	#define	EOTB_BIT

	//===结果标志 0---通过，1---失效
	#define BINB_POTRT
	#define	BINB_BIT

	//===解码触发，0---触发解码，1---不解码
	#define RSTB_POTRT
	#define	RSTB_BIT

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECB_PASS_POTRT
	#define	DECB_PASS_BIT

	//===SITEC的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTC_POTRT
	#define	SOTC_BIT

	//===结束
	#define EOTC_POTRT
	#define	EOTC_BIT

	//===结果标志 0---通过，1---失效
	#define BINC_POTRT
	#define	BINC_BIT

	//===解码触发，0---触发解码，1---不解码
	#define RSTC_POTRT
	#define	RSTC_BIT

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECC_PASS_POTRT
	#define	DECC_PASS_BIT

	//===SITED的SOT，BIN，EOT,RST,DEC配置
	//===开始
	#define SOTD_POTRT
	#define	SOTD_BIT

	//===结束
	#define EOTD_POTRT
	#define	EOTD_BIT

	//===结果标志 0---通过，1---失效
	#define BIND_POTRT
	#define	BIND_BIT

	//===解码触发，0---触发解码，1---不解码
	#define RSTD_POTRT
	#define	RSTD_BIT

	//===解码成功标志，0---解码成功，1---解码失败
	#define DECD_PASS_POTRT
	#define	DECD_PASS_BIT


	//////////////////////////////////////////////////////////////////////////////////////
	#ifdef __cplusplus
}
#endif
//////////////////////////////////////////////////////////////////////////////////////
#endif /*RFASKHW_CFG_H_ */
