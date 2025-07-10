/*=============================================================================
                        Minidump Library

GENERAL DESCRIPTION
    This file handles the minidump initialization and addition of new regions 
    for Boot.

Copyright 2020-2021 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
08/26/21     rama     added md_ss in boot_minidump_init
08/09/21     rama     Change signature to pass md_ss to boot_minidump_init
06/22/21     rama     boot_minidump_init pass enable_status, encr_req and encr_status
03/30/20     aus      Initial version
===========================================================================*/

#include "boot_minidump.h"
#include "smem.h"
#include <string.h>

md_global_toc* boot_md_get_global_mdtoc_addr(void);
md_ss_toc* boot_md_get_subsystem_toc(uint32 ss);

/*===========================================================================
**  Function :  boot_minidump_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes Boot minidump sub-system toc
* 
* @param
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   boolean TRUE if init is successful, FALSE otherwise
* 
* @par Side Effects
*   None
* 
*/
boolean boot_minidump_init(uint32 md_ss, uint32 md_ss_enable_status, uint32 encryption_required, uint32 encryption_status)
{
  md_ss_toc *ss_toc =  NULL;
  md_global_toc *md_gtoc = NULL;

  if(md_ss >= MD_SS_MAX)
  {
    return FALSE;
  }
  md_gtoc = boot_md_get_global_mdtoc_addr();
  if(md_gtoc == NULL)
  {
    return FALSE;
  }
  
  ss_toc = boot_md_get_subsystem_toc(md_ss);
  if(ss_toc == NULL)
  {
    return FALSE;
  }

  ss_toc->md_ss_toc_init             = MD_SS_TOC_MAGIC;
  ss_toc->md_ss_enable_status        = md_ss_enable_status;
  ss_toc->encryption_required        = encryption_required;
  ss_toc->encryption_status          = encryption_status;
  if(md_ss == MD_SS_BOOT)
    ss_toc->md_ss_smem_regions_baseptr = (uint64)(SCL_BOOT_MD_BASE);
  if(md_ss == MD_SS_XBL_SC)
    ss_toc->md_ss_smem_regions_baseptr = (uint64)(SCL_XBL_MD_BASE);

  if(ss_toc->md_ss_smem_regions_baseptr == 0)
  {
    return FALSE;
  }
  /*initialize count to zero*/
  ss_toc->ss_region_count = 0;

  return TRUE;
}
