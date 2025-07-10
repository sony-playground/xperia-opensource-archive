/*=============================================================================

                        SMEM ACCESS CONTROL

 Copyright (c)  2021 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/02/16   ar      Initial version
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <comdef.h>
#include <seclib_ac.h>

#include "smem_type.h"
#include "smem_toc.h"
#include "smem_internal.h"
#include "smem_os.h"
#include "smem_target.h"
#include "smem_xbl_config.h"
/*===========================================================================
                      TYPE DEFINITIONS
===========================================================================*/

#define SMEM_AC_ERROR(...)             SMEM_OS_LOG_ERR(__VA_ARGS__)
#define SMEM_AC_FATAL(...)             SMEM_OS_LOG_FATAL(__VA_ARGS__)

#ifndef UINT_MAX
#define UINT_MAX 0xFFFFFFFF
#endif

/*=============================================================================
                       PUBLIC/GLOBAL DATA DEFINATIONS
=============================================================================*/
/* smem_targ_info_ptr and smem_targ_info_addr are initialized smem_targ_init() */
#if defined(MPROC_BOOT_PROC) 
extern smem_targ_info_type *smem_targ_info_ptr;
extern uint64              smem_targ_info_addr;
#endif /* MPROC_BOOT_PROC */

/* Flag is set to TRUE when access permissions are applied for SMEM partitions */
boolean smem_init_partitions_completed = FALSE;

/*===========================================================================
                      EXTERN FUNCTION PROTOTYPE
===========================================================================*/
extern ACSecDomainId smem_ac_host_to_vm_get(smem_host_type host);

/*===========================================================================
                      FUNCTION DEFINITIONS
===========================================================================*/

/*===========================================================================
FUNCTION      smem_ac_add64
===========================================================================*/
/**
  Returns the sum of two 64bit inputs.
  This function does ERR_FATAL when 64bit integer overflows while doing addition.

  @param[in]  a   First input number.
  @param[in]  b   Second input number.

  @return
  Sum of inputs.
*/
/*=========================================================================*/
static uint64 smem_ac_add64(uint64 a, uint64 b)
{
  if (a > (UINT64_MAX - b))
  {
    SMEM_AC_FATAL(4, "Integer overflow while doing addition(0x%08X%08X, 0x%08X%08X).", 
            (uint32)(a >> 32), (uint32)a, (uint32)(b >> 32), (uint32)b);
  }
  return (a + b);
}

/*===========================================================================
FUNCTION      smem_ac_perms_set
===========================================================================*/
/**
  Sets permission to SMEM partition.

  @param[in] smem_phys_base   SMEM physical base address.
  @param[in] part_offset      SMEM partition offset.
  @param[in] part_size        SMEM partition size.
  @param[in] hosts_perm    Hosts permission for toc_entry partition.

  @return
  None
*/
/*=========================================================================*/
static void smem_ac_perms_set
(
  uint64 smem_phys_base,
  uint32 part_offset,
  uint32 part_size,
  uint32              hosts_perm[SMEM_NUM_HOSTS]
)
{
#ifdef MPROC_BOOT_PROC /* MPROC_BOOT_PROC */
  ACSecDomainPerm               dest_list[SMEM_NUM_HOSTS];
  uint64                        start_addr;
  uint64                        end_addr;
  int                           err_code;
#endif
  uint16                        host;
  ACxPUPermission               permissions;
  uint32                        num_dests;

  memset(dest_list, 0, sizeof(dest_list));
  memset(&start_addr, 0, sizeof(start_addr));
  memset(&end_addr, 0, sizeof(end_addr));

  num_dests = 0;

  for (host = 0; host < SMEM_NUM_HOSTS; host++)
  {
    if ((hosts_perm[host]            == 0) ||
        (smem_ac_host_to_vm_get(host) == AC_SD_END_MARKER))
    {
      continue;
    }

    permissions = 0;
    if (hosts_perm[host] & SMEM_TOC_ENTRY_FLAGS_ENABLE_READ_PROTECTION)
    {
      permissions |= AC_READ_ONLY;
    }
    if (hosts_perm[host] & SMEM_TOC_ENTRY_FLAGS_ENABLE_WRITE_PROTECTION)
    {
      permissions |= AC_READ_WRITE;
    }
    if (permissions == 0)
    {
      continue;
    }
#ifdef MPROC_BOOT_PROC
    dest_list[num_dests].sdId     = smem_ac_host_to_vm_get(host);
    dest_list[num_dests].perm = permissions;
#endif
    if (dest_list[num_dests].sdId == AC_SD_AP_NSEC || dest_list[num_dests].sdId == AC_SD_AP_SEC)
	{
		dest_list[num_dests].lock = true;
	}
    num_dests++;
  }

  if (num_dests == 0)
  {
    /* No hosts needs set access control for this pertition */
    return;
  }

#ifdef MPROC_BOOT_PROC
  start_addr = smem_ac_add64(smem_phys_base, part_offset);
  end_addr = smem_ac_add64(start_addr, part_size);

  /* call API to map XPU partition */
  err_code = ACxBLSCxPUProtectRegion(start_addr,
                        end_addr,
                        &dest_list[0],
                        num_dests,
                        false);
  if (err_code != 0)
  {
    SMEM_AC_FATAL(1, "XBL Permissions assign failed with err=%d", err_code);
  }
#endif
}

/*===========================================================================
FUNCTION      smem_ac_ssr_smem_dump_allow
===========================================================================*/
/**
  Checks whether it is secure device and debug enabled or not. 
  For SSR SMEM dump collection APPS should have read permission to the 
  non-APPS SMEM partitions only for non-secure device and secure device 
  with debug enabled.

  @param
  None
  
  @return
  TRUE, if SSR SMEM dump collection is allowed. Otherwise returns FALSE.
  
*/
/*=========================================================================*/
static boolean smem_ac_ssr_smem_dump_allow(void)
{
  /* Currently disabled for Wildcat since APPS is not registering with the 
     PIL framework to dump SMEM in case of any image's SSR */
  return FALSE;
}

/*===========================================================================
FUNCTION      smem_ac_hosts_perm
===========================================================================*/
/**
  Get the hosts permissions for a SMEM partition.

  @param[in]  toc_entry     Partition entry in TOC
  @param[out] hosts_perm    Hosts permission for toc_entry partition

  @return
  Returns hosts permission for toc_entry partition in hosts_perm.
*/
/*=========================================================================*/
static void smem_ac_hosts_perm
(
  smem_toc_entry_type *toc_entry,
  uint32              hosts_perm[SMEM_NUM_HOSTS]
)
{
  smem_host_type host0 = (smem_host_type)toc_entry->host0;
  smem_host_type host1 = (smem_host_type)toc_entry->host1;
  uint16 host;
  uint32 permissions;

  /* Initialize the hosts permission table */
  memset(hosts_perm, 0, sizeof(uint32) * SMEM_NUM_HOSTS);

  /* If size is 0, there is no partition to configure */
  if (!toc_entry->size)
  {
    return;
  }

  permissions = toc_entry->flags & SMEM_TOC_ENTRY_FLAGS_ENABLE_RW_PROTECTION;

  if ((host0 == SMEM_INVALID_HOST && host1 == SMEM_INVALID_HOST) ||
      (host0 == SMEM_COMMON_HOST  && host1 == SMEM_COMMON_HOST))
  {
    /* Partition is either legacy or common or TOC partition */
    for (host = 0; host < SMEM_NUM_HOSTS; host++)
    {
      hosts_perm[host] = permissions;
    }
  }
  else if (host0 != SMEM_INVALID_HOST && host0 < SMEM_NUM_HOSTS &&
           host1 != SMEM_INVALID_HOST && host1 < SMEM_NUM_HOSTS)
  {
    hosts_perm[host0] = permissions;
    hosts_perm[host1] = permissions;

#ifndef SMEM_TZ_HOST_NOT_SUPPORTED
    /* TZ should have permission to MPSS-SPSS partition */
    if ((host0 == SMEM_MODEM && host1 == SMEM_SPSS_SP) ||
        (host1 == SMEM_MODEM && host0 == SMEM_SPSS_SP))
    {
      hosts_perm[SMEM_TZ] = permissions;
    }
#endif /* SMEM_TZ_HOST_NOT_SUPPORTED */
  }
  
  if (hosts_perm[SMEM_TME] == 0 &&
      hosts_perm[SMEM_MODEM] == 0 &&
	  hosts_perm[SMEM_SPSS_SP] == 0 &&
	  hosts_perm[SMEM_RPM] == 0)
  {
    for (host = 0; host < SMEM_NUM_HOSTS; host++)
    {
      hosts_perm[host] = 0;
    }
  }

  /* Add APSS to list of VMs for RO access */
  if ((TRUE == smem_ac_ssr_smem_dump_allow()) &&
      (hosts_perm[SMEM_APPS] == 0))
  {
    hosts_perm[SMEM_APPS] = SMEM_TOC_ENTRY_FLAGS_ENABLE_READ_PROTECTION;
  }
}
/*===========================================================================
FUNCTION      smem_ac_xbl_validate
===========================================================================*/
/**
  Verifies the SMEM target info and SMEM TOC. Returns the SMEM base
  physical address, SMEM size and SMEM base virtual address.

  @param[out]   smem_phys_base_ret   Returns SMEM base physical address.
  @param[in]    smem_size_ret        Returns SMEM size.

  @return
  Returns SMEM base virtual if validation success otherwise returns NULL.
*/
/*=========================================================================*/
#ifdef MPROC_BOOT_PROC
static uint8 *smem_ac_xbl_validate
(
  uint64 *smem_phys_base_ret,
  uint32 *smem_size_ret
)
{
  uint8  *smem_base;
  uint32 smem_size;
  uint64 smem_phys_base;
  uint32 hosts_perm[SMEM_NUM_HOSTS];
  smem_host_type smem_host;

  smem_phys_base = 0;
  smem_size      = 0;
  smem_base      = NULL;

  /* Initialize the OS specific functionality */
  smem_os_init();

  /* Initialize the target specific functionality */
  smem_targ_init();

  smem_phys_base = smem_targ_info_ptr->smem_base_phys_addr;
  smem_size  = smem_targ_info_ptr->smem_size;
  smem_base      = (uint8 *)smem_os_map_base_va((void *)(uintptr_t)smem_phys_base, smem_size);

  /* Apply Read only permission for SMEM TOC partition */
  for (smem_host = 0; smem_host < SMEM_NUM_HOSTS; smem_host++)
  {
    hosts_perm[smem_host] = SMEM_TOC_ENTRY_FLAGS_ENABLE_READ_PROTECTION;
  }

  smem_ac_perms_set(smem_phys_base,
                    smem_size - SMEM_TOC_SIZE,
                    SMEM_TOC_SIZE,
                    hosts_perm);

  /* Return the SMEM base physical address and SMEM size */
  if (smem_size_ret)
  {
    *smem_size_ret = smem_size;
  }
  if (smem_phys_base_ret)
  {
    *smem_phys_base_ret = smem_phys_base;
  }

  return smem_base;
}
#endif /* MPROC_BOOT_PROC */

/*===========================================================================
FUNCTION      smem_init_partitions
===========================================================================*/
/**
  Parses the shared memory table of contents (SMEM TOC) and enables XPU
  protection on regions of SMEM in TZ.

  @return
  none.
*/
/*=========================================================================*/
void smem_init_partitions(void)
{
  smem_toc_type       *toc_header;
  uint8               *smem_base;
  uint64        smem_phys_base;
  uint32              smem_size;
  uint32        entry_indx;
  
  smem_base = smem_ac_xbl_validate(&smem_phys_base, &smem_size);
  if (smem_base == NULL)
  {
    SMEM_AC_FATAL(0, "smem_ac_validate failed!");
    return;
  }

  /* Point to start of TOC */
  toc_header = (smem_toc_type *)(smem_base + smem_size - SMEM_TOC_SIZE);

  /* Apply access permissions for every SMEM partition.
   * Skip TOC partition, as permissions already applied */
  for (entry_indx = 1; entry_indx < toc_header->num_entries; entry_indx++)
    {
    smem_toc_entry_type *toc_entry = &toc_header->entry[entry_indx];
    uint32              hosts_perm[SMEM_NUM_HOSTS];

    /* Get hosts permissions for this partition */
    smem_ac_hosts_perm(toc_entry, hosts_perm);

    /* Set permissions */
    smem_ac_perms_set(smem_phys_base, toc_entry->offset, toc_entry->size, hosts_perm);
  }
  
  smem_init_partitions_completed = TRUE;
}
