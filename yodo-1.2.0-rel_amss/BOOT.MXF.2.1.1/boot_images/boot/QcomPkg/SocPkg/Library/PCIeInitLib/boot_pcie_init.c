/*===========================================================================

                         Boot PCIe utility functions

GENERAL DESCRIPTION
 Boot PCIe APIs

Copyright 2021 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

when       who             what, where, why
--------   ---         --------------------------------------------------
07/08/21   ck          Renamed xbl_pcie_dump_enabled to xbl_pcie_fast_boot_enabled
02/10/21   vk          Initial rev

===========================================================================*/

#include <comdef.h>

boolean xbl_pcie_fast_boot_enabled(void);

boolean xbl_pcie_fast_boot_enabled(void)
{
  return FALSE;
}

boolean xbl_pcie_reset_sep_enabled (void)
{
  return FALSE;
}

