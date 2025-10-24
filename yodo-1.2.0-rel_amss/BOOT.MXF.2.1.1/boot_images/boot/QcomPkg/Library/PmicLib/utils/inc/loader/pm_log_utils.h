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


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/inc/loader/pm_log_utils.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/13/16   aab     Updated logging message size since this Macro is used to handle all SBL logging 
08/05/16   aab     Created 
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include <stdio.h>
#include <stdarg.h>
#include "boot_logger.h"

extern char status_message[];

//This pm_log_message() API will be called in both SBL and CORE
/*
#define pm_log_message(fmt, ...)      \
  do {\
    snprintf((status_message+PM_STATUS_MSG_HEAD_LEN), PM_STATUS_MSG_LEN, fmt, ##__VA_ARGS__); \
    LogMsg(status_message); \
  }while(0)
*/
void pm_log_message(const char* format, ...);

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/



#endif // __PM_LOG_UTILS_H__
