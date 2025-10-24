/**********************************************************************
* boot_common_loader.c
*
* Common services for XBL Loader
*
* Copyright (c) 2018,2022 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
*
*
**********************************************************************/

/*=======================================================================
                        Edit History

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/StorageCommonLib/StorageLoaderCommon.c#1 $
$DateTime: 2022/08/18 10:15:46 $

YYYY-MM-DD   who     what, where, why
----------------------------------------------------------------------
2018-06-11   bb      Initial creation
===========================================================================*/

#include <boot_logger_if.h>
#include <boot_timer_if.h>
#include "StorageBootCommon.h"

// Wrapper for UART logging
void boot_common_log_message(char *str)
{
   boot_log_message(str);
}

// Wrapper for Time in us
uint32 boot_common_get_time()
{
  return boot_get_time_count();
}
