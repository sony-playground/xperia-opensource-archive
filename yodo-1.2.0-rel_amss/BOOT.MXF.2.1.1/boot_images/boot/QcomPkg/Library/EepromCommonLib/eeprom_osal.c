/**********************************************************************
 *eeprom_osal.c
 *
 * This file provides definitions for the eeprom platform specific functions
 *
 * Copyright (c) 2020 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*===================================================================
 *
 * 					  EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 *
 * when          who     what, where, why
 * ----------	 ---	 ------------------------------------------------
 * 09-10-2020	 eo 	 Initial version
 *=======================================================================*/

#include <stdlib.h>
#include "com_dtypes.h"
#include <string.h>
#include "stringl/stringl.h"
#include "eeprom_osal.h"
#include <Library/CacheMaintenanceLib.h>


/* Cache management wrapper */

void eeprom_cache_op (void *addr, uint32_t len, uint32_t op)
{
  if(op == INVAL)
    InvalidateDataCacheRange(addr, len);
  else
    WriteBackInvalidateDataCacheRange(addr, len);
}

