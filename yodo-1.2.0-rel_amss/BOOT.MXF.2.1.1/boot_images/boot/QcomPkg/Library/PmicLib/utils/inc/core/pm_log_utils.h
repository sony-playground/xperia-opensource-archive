#ifndef __PM_LOG_UTILS_H__
#define __PM_LOG_UTILS_H__

/*! \file
 *  
 *  \brief  pm_log_utils.h ----This file contain PMIC wrapper function of DALSYS_Malloc()
 *  \details his file contain PMIC wrapper function of DALSYS_Malloc()
 *  
 *    &copy; Copyright 2012-2021 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/inc/core/pm_log_utils.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
08/05/16   aab     Created

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include <stdio.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>

#include "pm_uefi.h"
#include "CoreVerify.h"
#include "pm_utils.h"

extern char status_message[];

//This pm_log_message() API will be called in both SBL and CORE
//#define pm_log_message(fmt, ...)      \
//  do {\
//    snprintf((status_message+PM_STATUS_MSG_HEAD_LEN), PM_STATUS_MSG_LEN, fmt"\r\n", ##__VA_ARGS__); \
//    DEBUG((EFI_D_ERROR, status_message)); \
//  }while(0)

//Below macro are only applicable for CORE
#define PM_LOG_MSG(...)             DEBUG((EFI_D_WARN,__VA_ARGS__))
#define PM_LOG_MSG_INFO             PM_LOG_MSG
#define PM_LOG_MSG_ERR_FATAL(...)   do{ DEBUG((EFI_D_ERROR,__VA_ARGS__));   \
                                    CORE_VERIFY(0); }while(0)
                                        

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/
void pm_log_message(const char* format, ...);

#endif // __PM_LOG_UTILS_H__
