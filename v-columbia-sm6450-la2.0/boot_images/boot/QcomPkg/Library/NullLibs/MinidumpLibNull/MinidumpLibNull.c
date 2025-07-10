/** @file MinidumpLibNull.c
  
  Stub functions for MinidumpLib

  Copyright (c) 2020-2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 06/22/21   rama    boot_minidump_init params update
 03/30/20   aus     Initial revision

=============================================================================*/


/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"
#include "boot_minidump.h"

/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/ 


boolean boot_minidump_init(uint32 md_ss, uint32 md_ss_enable_status, uint32 encryption_required, uint32 encryption_status)
{
	return TRUE;
}

boolean boot_add_minidump_region(uint32 md_ss, char rg_name[MD_REGION_NAME_LENGTH], uint64 rg_base_addr, uint64 rg_size)
{
	return TRUE;
}




