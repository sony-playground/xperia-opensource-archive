/*=============================================================================

                            XRC Logger

 XRC Communication logging

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef XRC_LOG_H
#define XRC_LOG_H

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

#define XRC_MAX_LOG_LEN 256

/** Logger macros - mainline will contain required macros 
 *  rest can be enabled by engineer when necessary */

#define XRC_LOG_INFO(args, fmt, ...)   do { \
          snprintf(XRCLogBuf, XRC_MAX_LOG_LEN, "XRC INFO: " fmt, ##__VA_ARGS__); \
          boot_log_message(XRCLogBuf); \
        } while(FALSE)
			 
#define XRC_LOG_WRN(args, fmt, ...)   do { \
          snprintf(XRCLogBuf, XRC_MAX_LOG_LEN, "XRC WARN: " fmt, ##__VA_ARGS__); \
          boot_log_message(XRCLogBuf); \
        } while(FALSE)

#define XRC_LOG_ERR(args, fmt, ...)   do { \
          snprintf(XRCLogBuf, XRC_MAX_LOG_LEN, "XRC Err: " fmt, ##__VA_ARGS__); \
          boot_log_message(XRCLogBuf); \
        } while(FALSE)

#define XRC_LOG_FATAL(args, fmt, ...)   do { \
          snprintf(XRCLogBuf, XRC_MAX_LOG_LEN, "XRC Fatal: " fmt, ##__VA_ARGS__); \
          boot_log_message(XRCLogBuf); \
        } while(FALSE)

#define XRC_LOG_FUNC_START() XRC_LOG_DBG(1, "+ %s.", __FUNCTION__)
#define XRC_LOG_FUNC_END()   XRC_LOG_DBG(1, "- %s.", __FUNCTION__)
#define XRC_LOG_FUNC_START_ARG(str, val) \
    XRC_LOG_DBG(3, "+ %s. %s:%d", __FUNCTION__, str, val)
	
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
extern char XRCLogBuf[XRC_MAX_LOG_LEN];

#ifdef __cplusplus
}
#endif

#endif /* XRC_LOG_H */
