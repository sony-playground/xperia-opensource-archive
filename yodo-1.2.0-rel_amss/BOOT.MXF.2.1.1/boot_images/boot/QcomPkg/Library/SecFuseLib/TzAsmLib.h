/** @file TzAsmLib.h
  
  TzAsm lib interface

  Copyright (c) 2020, 2022 by Qualcomm Technologies, Inc. 
  All Rights Reserved.
 
**/
/*===========================================================================

                            EDIT HISTORY FOR FILE


when       who      what, where, why
--------   ---      ------------------------------------
11/23/20   cm       Initial version.

===========================================================================*/


#define SET_BIT(num, bit) ((num) |  (1 << (bit)))
#define CLR_BIT(num, bit) ((num) & ~(1 << (bit)))

#define AARCH_BIT 30

#define TZASMLIB_NUM_DIRECT_REQUEST_PARAMETERS     4

/*----------------------------------------------------------------------------
 * ARMv8 Calls
 * -------------------------------------------------------------------------*/
INTN tz_slowcall(const void * cmd_addr);

INTN tz_fastcall(UINT32 id, UINT32 token, UINT32 r0, UINT32 r1, ...);

INTN tz_get_version(UINT32* version);

INTN tz_armv8_smc_call(UINT32 smc_id,
                       UINT32 param_id,
                       UINTN  parameters[4],
                       UINTN *trusted_os_id);
