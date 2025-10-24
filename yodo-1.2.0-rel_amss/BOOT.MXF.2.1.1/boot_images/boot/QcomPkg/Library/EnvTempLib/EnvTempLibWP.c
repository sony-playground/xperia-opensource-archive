/** @file EnvTempLibWP.c
  EnvTemlpLib library .

  Copyright (c) 2020, 2021 Qualcomm Technologies, Inc.  All Rights Reserved.

  Qualcomm Technologies Proprietary and Confidential.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/25/21   ka      Add Dxe heap to list of regions being invalidated
 12/09/20   cm      Initial version
=============================================================================*/

#include <Library/CacheMaintenanceLib.h>

VOID
EnvTempFlush (VOID)
{
  WriteBackInvalidateDataCacheRange((VOID *)0x80C00000,0x02F00000);
  WriteBackInvalidateDataCacheRange((VOID *)0x808B0000,0x00040000);
  WriteBackInvalidateDataCacheRange((VOID *)0x80600000,0x00100000);

  /*Invalidate Dxe Heap region*/
  WriteBackInvalidateDataCacheRange((VOID *)0x8E400000,0x10C00000);
}