/*=============================================================================
                        Minidump Library common

GENERAL DESCRIPTION
    This file handles the minidump initialization and addition of new regions 
	for Boot.

Copyright 2020-2022 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
10/06/22     rama     Add boot_md_is_valid_global_mdtoc
08/11/22     rama     Fix condition check in boot_add_minidump_region
08/03/22     rama     KW error fix
02/18/22     rama     Cleanup phase 2
10/16/21     yps      Avoid to add duplicate boot minidump regions
08/26/21     rama     added md_ss in boot_add_minidump_region
06/22/21     rama     boot_add_minidump_region-> seq_num is always 0
03/30/20     aus      Initial version
===========================================================================*/

/*==========================================================================

                   INCLUDE FILES

===========================================================================*/
#include <boot_minidump.h>
#include <smem.h>
#include <string.h>

#ifndef SCL_BOOT_MD_COUNT
#define SCL_BOOT_MD_COUNT 100 
#endif

/*===========================================================================
**  Function :  boot_md_is_valid_global_mdtoc(void)
** ==========================================================================
*/
/*!
* 
* @brief
*   This function checks global minidump ToC validity
* 
* @param
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   boot_boolean returns TRUE if global minidump ToC is present and valid
* 
* @par Side Effects
*   None
* 
*/
boot_boolean boot_md_is_valid_global_mdtoc(void)
{
  md_global_toc* md_toc = NULL;
  uint32 md_smem_size = sizeof(md_global_toc);

  md_toc = (md_global_toc *)smem_get_addr( SBL_MINIDUMP_SMEM_ID, &md_smem_size);

  /*Check XBL md_toc init status*/
  if(md_toc == NULL)
  {
    return FALSE;
  }
   /*XBL is setting it to true*/
  else if (md_toc->md_toc_init != TRUE)
  {
    return FALSE;
  }
  else if (md_toc->md_revision != MD_REVISION)
  {
    return FALSE;
  }
  
  /* MINIDUMP global ToC exists and is valid */
  return TRUE;
}

/*===========================================================================
**  Function :  boot_md_get_global_mdtoc_addr
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the global minidump toc if it is initialized
* 
* @param
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   md_global_toc* Pointer to the global minidump toc
* 
* @par Side Effects
*   None
* 
*/
md_global_toc* boot_md_get_global_mdtoc_addr(void)
{
  md_global_toc* md_toc = NULL;
  uint32 md_smem_size = sizeof(md_global_toc);


  if(boot_md_is_valid_global_mdtoc())
  {
    md_toc = (md_global_toc *)smem_get_addr( SBL_MINIDUMP_SMEM_ID, &md_smem_size);
  }

  return md_toc;
}

/*===========================================================================
**  Function :  boot_md_get_subsystem_toc
** ==========================================================================
*/
/*!
* 
* @brief
*   This function returns the global minidump toc if it is initialized
* 
* @param
*   md_subsys_type sub-system index
*        
* @par Dependencies
*   None
*   
* @retval
*   md_ss_toc* Pointer to the sub-system minidump toc
* 
* @par Side Effects
*   None
* 
*/
md_ss_toc* boot_md_get_subsystem_toc(md_subsys_type ss_id)
{
  md_global_toc *md_gtoc = NULL;

  if(ss_id >= MD_SS_MAX)
  {
    return NULL;
  }
  md_gtoc = boot_md_get_global_mdtoc_addr();

  if(md_gtoc != NULL)
  {
    return (&md_gtoc->md_ss_toc[ss_id]);
  }

  return NULL;
}

/*===========================================================================
**  Function :  boot_add_minidump_region
** ==========================================================================
*/
/*!
* 
* @brief
*   This function adds a new minidump region in boot sub-system minidump table
* 
* @param
*   char*  Name of the region
*   uint64 Base address
*   uint64 Size
*        
* @par Dependencies
*   None
*   
* @retval
*   boolean TRUE if region added, FALSE otherwise
* 
* @par Side Effects
*   None
* 
*/
boolean boot_add_minidump_region(md_subsys_type ss_id, char rg_name[MD_REGION_NAME_LENGTH], uint64 rg_base_addr, uint64 rg_size)
{
  md_ss_region *md_rgn = NULL;
  md_ss_toc *ss_toc = NULL;
  uint32 i = 0;
  if(ss_id >= MD_SS_MAX)
  {
    return FALSE;
  }
  ss_toc = boot_md_get_subsystem_toc(ss_id);
  if(ss_toc == (md_ss_toc*)NULL || ss_toc->md_ss_smem_regions_baseptr == 0 || rg_name == NULL)
  {
    return FALSE;
  }
  
  if (ss_toc->ss_region_count >= (uint32)(SCL_BOOT_MD_COUNT))
  {
    return FALSE;
  }
  if (ss_id == MD_SS_BOOT)
  {
    for(i= 0;i< ss_toc->ss_region_count;i++)
    {
      md_rgn = (md_ss_region*)ss_toc->md_ss_smem_regions_baseptr +i;
      if (strcmp((char*)md_rgn->region_name, rg_name) == 0)
          return TRUE;
    }
    md_rgn = (md_ss_region*)ss_toc->md_ss_smem_regions_baseptr + i;
  }
  else
  {
    md_rgn = (md_ss_region*)ss_toc->md_ss_smem_regions_baseptr +  ss_toc->ss_region_count;
  }
  
  //For Boot usecase, there is no need to update sequence number as we do not dump sequenced regions.
  md_rgn->seq_num   =   0;
  md_rgn->md_valid   =  MD_REGION_VALID;
  md_rgn->region_base_address = rg_base_addr;
  md_rgn->region_size = rg_size;
  memscpy(md_rgn->region_name, MD_REGION_NAME_LENGTH, rg_name, MD_REGION_NAME_LENGTH);
  
  /*increment the counter*/
  ss_toc->ss_region_count++;

  return TRUE;
}

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
*   ss_id                 [in]     subsystem index
*   md_ss_enable_status   [in]     subsystem enable status
*   encryption_required   [in]     encryption required status of subsystem
*   encryption_status     [in]     encryption status of sybsystem
*   ss_baseptr            [in]     address of subsystems region table
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
boolean boot_minidump_init(md_subsys_type ss_id, uint32 md_ss_enable_status, uint32 encryption_required, uint32 encryption_status, uintnt ss_baseptr)
{
  md_ss_toc *ss_toc =  NULL;
  md_global_toc *md_gtoc = NULL;

  if(ss_id >= MD_SS_MAX || ss_baseptr == 0)
  {
    return FALSE;
  }
  md_gtoc = boot_md_get_global_mdtoc_addr();
  if(md_gtoc == NULL)
  {
    return FALSE;
  }
  
  ss_toc = boot_md_get_subsystem_toc(ss_id);
  if(ss_toc == NULL)
  {
    return FALSE;
  }

  ss_toc->md_ss_toc_init             = MD_SS_TOC_MAGIC;
  ss_toc->md_ss_enable_status        = md_ss_enable_status;
  ss_toc->encryption_required        = encryption_required;
  ss_toc->encryption_status          = encryption_status;

  ss_toc->md_ss_smem_regions_baseptr = ss_baseptr;

  if(ss_toc->md_ss_smem_regions_baseptr == 0)
  {
    return FALSE;
  }
  /*initialize count to zero*/
  ss_toc->ss_region_count = 0;

  return TRUE;
}