#include "complier_cfg.h"

//===��ȡ��������ں�ʱ��
#ifdef USE_MCU_STM32
const UINT8_T  g_VersionDate[VERSION_DATE_SIZE] = __DATE__;
const UINT8_T  g_VersionTime[VERSION_TIME_SIZE] = __TIME__;
#endif

#ifdef USE_MCU_AVR
PRO_FLASH_UINT8_T  g_VersionDate[VERSION_DATE_SIZE] = __DATE__;
PRO_FLASH_UINT8_T  g_VersionTime[VERSION_TIME_SIZE] = __TIME__;
#endif