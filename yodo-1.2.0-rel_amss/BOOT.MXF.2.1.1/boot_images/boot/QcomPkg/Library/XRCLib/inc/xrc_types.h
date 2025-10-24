/*=============================================================================

                            XRC TYPES

All data types and structures are declared here.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

#ifndef XRC_TYPES_H
#define XRC_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include <stdint.h>
#include "slvcom.h"
#include "elf.h"

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/
#define BIT32CPU 1

#ifdef BIT32CPU
typedef unsigned int phys_addr_t;
#else
typedef unsigned long phys_addr_t;
#endif

typedef enum{
	SUCCESS = 0,
	FAILURE = -1,
	FAIL_BG_IN_RESET = -2,
	FAIL_CMD_BUF_TOO_SMALL_FOR_CMD_ID = -3,
	FAIL_CMD_RSP_BUFS_TOO_SMALL = -4,
	FAIL_SHARED_BUFF_TOO_SMALL = -5,
	FAIL_MEM_ALLOC = -6,
	FAIL_TZ_AUTHENTICATION = -7,
	FAIL_BL_NOT_WAITING_FOR_RAM_AVAILABLE = -8,
	FAIL_BL_NOT_WAITING_FOR_ELF_HEADER = -9,
	FAIL_BL_NOT_WAITING_FOR_RUN_IMAGE = -10,
	FAIL_CRC_VERIFICATION = -11,
	FAIL_MAIN_IMAGE_NOT_LAUNCHED = -12,
	FAIL_MDT_SIZE_EXCEEDED = -13,
	FAIL_BG_RAM_DUMP = -14,
	FAIL_BG_SOFT_RESET = -15,
	FAIL_TIMEOUT = -16,
	FAIL_SECMODE_ENABLE = -17,
	FAIL_SECMODE_DISABLE = -18,
	FAIL_slvcom_CLIENT_EXISTS = -19,
	FAIL_slvcom_SPI_TRANSFER = -20,
	FAIL_slvcom_BG_NOT_RESPONDING = -21,
	FAIL_slvcom_BG_RESET = -22,
	FAIL_slvcom_GPIO_ERROR = -23,
	FAIL_TLMM_STRING_MISMATCH = -24,
	FAIL_TLMM_KEY_ACQUIRE = -25,
	FAIL_TLMM_KEY_RELEASE = -26,
	FAIL_TLMM_GET_ERROR = -27,
	FAIL_MAIN_IMAGE_CRASHED = -28,
	FAIL_GPIO_ERR = -29,
	FAIL_INVALID_PARAM = -30,
	FAIL_NOT_SUPPORTED = -31,
}status_codes;

typedef enum{
	/*Commands supported from HLOS client*/
	HELIOS_RPROC_RAMDUMP=0,
	HELIOS_RPROC_IMAGE_LOAD=1,
	HELIOS_RPROC_AUTH_MDT=2,
	HELIOS_RPROC_CONTINUE_DOWNLOAD=3,
	HELIOS_RPROC_GET_BG_VERSION=4,
	HELIOS_RPROC_SHUTDOWN=5,
	HELIOS_RPROC_GET_BG_DATA=6,
	HELIOS_RPROC_UP_INFO=7,
	HELIOS_RPROC_RESTART=8,
	HELIOS_RPROC_POWERDOWN=9,
}pil_commands;

typedef struct{
	uint32_t base;
	uint32_t limit;
	uint32_t size;
}memory_map;

#ifdef __cplusplus
}
#endif

#endif 
