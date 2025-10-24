/*=============================================================================

                            SLVCOM OS

 Slave Communication logging

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/inc/slvcom_log.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef SLVCOM_LOG_H
#define SLVCOM_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include <stdarg.h>
#include "stdio.h"
#include "com_dtypes.h"
#include "boot_logger.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/

#define SLVCOM_MAX_LOG_LEN 256

/** Logger macros - mainline will contain required macros 
 *  rest can be enabled by engineer when necessary */

#if 0
#define SLVCOM_LOG_DBG(args, fmt, ...)   do { \
          snprintf(SlvcomLogBuf, SLVCOM_MAX_LOG_LEN, "SLVCOM Debug: " fmt, ##__VA_ARGS__); \
          boot_log_message(SlvcomLogBuf); \
        } while(FALSE)
#else
#define SLVCOM_LOG_DBG(args, fmt, ...)   do { \
        } while(FALSE)
#endif

#if 0
#define SLVCOM_LOG_INFO(args, fmt, ...)   do { \
          snprintf(SlvcomLogBuf, SLVCOM_MAX_LOG_LEN, "SLVCOM Info: " fmt, ##__VA_ARGS__); \
          boot_log_message(SlvcomLogBuf); \
        } while(FALSE)
#else
#define SLVCOM_LOG_INFO(args, fmt, ...)   do { \
        } while(FALSE)
#endif
			 
#define SLVCOM_LOG_WRN(args, fmt, ...)   do { \
          snprintf(SlvcomLogBuf, SLVCOM_MAX_LOG_LEN, "SLVCOM WARN: " fmt, ##__VA_ARGS__); \
          boot_log_message(SlvcomLogBuf); \
        } while(FALSE)
#define SLVCOM_LOG_ERR(args, fmt, ...)   do { \
          snprintf(SlvcomLogBuf, SLVCOM_MAX_LOG_LEN, "SLVCOM Err: " fmt, ##__VA_ARGS__); \
          boot_log_message(SlvcomLogBuf); \
        } while(FALSE)
#define SLVCOM_LOG_FATAL(args, fmt, ...)   do { \
          snprintf(SlvcomLogBuf, SLVCOM_MAX_LOG_LEN, "SLVCOM Fatal: " fmt, ##__VA_ARGS__); \
          boot_log_message(SlvcomLogBuf); \
        } while(FALSE)

#define SLVCOM_LOG_FUNC_START() SLVCOM_LOG_DBG(1, "+ %s.", __FUNCTION__)
#define SLVCOM_LOG_FUNC_END()   SLVCOM_LOG_DBG(1, "- %s.", __FUNCTION__)
#define SLVCOM_LOG_FUNC_START_ARG(str, val) \
    SLVCOM_LOG_DBG(3, "+ %s. %s:%d", __FUNCTION__, str, val)
#define BAM_DMUX_LOG_FUNC_END_ARG(str, val)   \
    SLVCOM_LOG_DBG(3, "- %s. %s:%d", __FUNCTION__, str, val)

#ifndef inline
#define inline __inline
#endif
/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/


/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/

/** Loggers will log into this memory */
extern char SlvcomLogBuf[SLVCOM_MAX_LOG_LEN];

/*=============================================================================

                    PUBLIC FUNCTION DECLARATIONS

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_log_init
=============================================================================*/
/**
 * Initializes logging.
 *
 */
/*===========================================================================*/
static inline void slvcom_log_init(void)
{
}

#ifdef __cplusplus
}
#endif

#endif /* SLVCOM_LOG_H */
