/**********************************************************************
 *spinor_osal.c
 *
 * This file provides definitions for the spinor platform specific functions
 *
 * Copyright (c) 2017-2018 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*======================================================================

                        EDIT HISTORY FOR MODULE


when        who  what, where, why
----------  ---  -----------------------------------------------
2018-03-21  wek  Update cache management logic.
2017-09-15  md   Initial Release based on SPI-NOR driver from Quartz.

==================================================================*/

#include <stdlib.h>
#include "com_dtypes.h"
#include <string.h>
#include "stringl/stringl.h"
#include "spinor_spial.h"
#include "spinor_osal.h"
#include <Library/CacheMaintenanceLib.h>


/* Cache management wrapper */

void spinor_cache_op (void *addr, uint32_t len, uint32_t op)
{
  if(op == INVAL)
    InvalidateDataCacheRange(addr, len);
  else
    WriteBackInvalidateDataCacheRange(addr, len);
}

