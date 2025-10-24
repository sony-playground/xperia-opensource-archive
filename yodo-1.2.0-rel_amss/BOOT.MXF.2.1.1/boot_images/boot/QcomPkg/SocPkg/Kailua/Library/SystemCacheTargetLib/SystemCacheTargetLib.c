/*===============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		SystemCacheTargetLib.c
  
  REVISION HISTORY
  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  08/11/21   dais      Kailua SCT update and activation/deactivation sequence
  03/11/21   dais      Created
================================================================================*/

#include "llcc_trp_reg_or.h"
#include "SystemCacheTargetLib.h"
#include <Protocol/EFIHWIO.h>
#include <Protocol/EFISystemCache.h>

/* SCT table for Kailua */

struct system_cache_table_entry system_cache_table[] =
{
/*  usecase_id,     scid,  max_cap, bonus_ways, reserved_ways, cache_mode, dis_cap_alloc, write_scid_en, write_scid_cacheable_en, activate_at_boot,   sw_por*/
  {      CPUSS,        1,     5120,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,             TRUE,     TRUE},
  {     VIDSC0,        2,      512,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {      AUDIO,        6,     1024,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  { MDMHP_GROW,       25,     1024,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {      MDMHW,       26,     1024,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {    COMPUTE,       10,     4096,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {     GPUHTW,       11,      512,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {        GPU,        9,     3096,   0xFFFFFF,           0x0,     NORMAL,         FALSE,          TRUE,                    TRUE,            FALSE,     TRUE},
  {     MMUHWT,       18,      512,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,             TRUE,     TRUE},
  {    DISPLAY,       16,     6144,   0xFFFFFF,           0x0,        NSE,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  { MDM_PAGING,       27,     1024,   0xF00000,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {    AUDIOHW,       22,     1024,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {        CVP,        8,      256,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {    MDM_VPE,       29,       64,   0xF00000,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {WRITE_CACHE,       31,      512,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,             TRUE,     TRUE},
  {CAMERA_EXP0,        4,      256,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {    CPU_HWT,        5,      512,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,             TRUE,     TRUE},
  {CAMERA_EXP1,        7,     3200,   0xFFFFFF,           0x0,        NSE,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {COMPUTE_HCP,       17,      256,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {   LCP_DARE,       30,      128,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,             TRUE,     TRUE},
  { AUDIO_ENPU,        3,     3072,   0xFFFF00,           0x0,        NSE,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {   ISLAND_1,       12,     1792,     0xFE00,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {   ISLAND_4,       15,      256,    0x10000,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {CAMERA_EXP2,       19,     3200,   0xFFFFFF,           0x0,        NSE,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {CAMERA_EXP3,       20,     3200,   0xFFFFFF,           0x0,        NSE,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {CAMERA_EXP4,       21,     3200,   0xFFFFFF,           0x0,        NSE,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  { DISPLAY_WB,       23,     1024,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {  DISPLAY_1,       24,     6144,   0xFFFFFF,           0x0,        NSE,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE},
  {  VIDSC_VSP,       28,      256,   0xFFFFFF,           0x0,     NORMAL,         FALSE,         FALSE,                   FALSE,            FALSE,     TRUE}
};


/*==============================================================================
  FUNCTION      scid_activate

  DESCRIPTION   Function to activate particular SCID

==============================================================================*/

void scid_activate(UINT32 scid)
{
    volatile UINT32 write_val = 0, read_val = 0;

    write_val =  (ACTIVATE_OPCODE << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT)
                  & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK;
    write_val |= TRIGGER_VALUE;
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, write_val);
    /* Clear trigger bit */
    write_val = 0;
    write_val =  (ACTIVATE_OPCODE << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT)
                  & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK;
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, write_val);

    /* Check if activation command is finished */
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACT_COMPLETE_BMSK);
    while((read_val & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACT_COMPLETE_BMSK) == 0);

    read_val = 0;
    /* Check if activation is complete */
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACTIVE_BMSK);
    while((read_val & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACTIVE_BMSK) == 0);

    /* Clear ACT_COMPLETE status for next activation/deactivation LLCC_TRP_SCID_n_ACT_CLEAR[ACT_COMPLETE_CLEAR] = 1 */
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, 0x1);
}

/*==============================================================================
  FUNCTION      scid_deactivate

  DESCRIPTION   Function to deactivate particular SCID

==============================================================================*/

void scid_deactivate(UINT32 scid)
{
    volatile UINT32 write_val = 0, read_val = 0;
    write_val =  (DEACTIVATE_OPCODE << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT)
                    & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK;
    write_val |= TRIGGER_VALUE;
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, write_val);
    /* Clear trigger bit */
    write_val = 0;
    write_val =  (DEACTIVATE_OPCODE << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT)
                    & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK;
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, write_val);

    /* Check if de-activation command is finished */
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACT_COMPLETE_BMSK);
    while((read_val & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACT_COMPLETE_BMSK) == 0);

    read_val = 0;
    /* Check if deactivation is complete */
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_DEACTIVE_BMSK);
    while((read_val & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_DEACTIVE_BMSK) == 0);

    /* Clear ACT_COMPLETE status for next activation/deactivation LLCC_TRP_SCID_n_ACT_CLEAR[ACT_COMPLETE_CLEAR] = 1 */
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CLEAR_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, 0x1);
}

/*==============================================================================
  FUNCTION      get_scid_status

  DESCRIPTION   Function to get SCID status

==============================================================================*/

EFI_STATUS get_scid_status(UINT32 scid, SCID_STATUS *scid_status)
{
    volatile UINT32 read_val = 0;
    
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACTIVE_BMSK);
    if((read_val & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACTIVE_BMSK) == 0)
    {
        scid_status->activated = 0;
    }
    else
    {
        scid_status->activated = 1;
    }
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_DEACTIVE_BMSK);
    if((read_val & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_DEACTIVE_BMSK) == 0)
    {
        scid_status->deactivated = 0;
    }
    else
    {
        scid_status->deactivated = 1;
    }
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_MAX_CAP_BMSK);
    read_val = (read_val >> HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_MAX_CAP_SHFT);
    read_val = (read_val * 64);
    read_val = (read_val / 1024);
    scid_status->scid_maximum_capacity = (read_val * 4);
    
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_CURRENT_CAP_BMSK);
    read_val = (read_val >> HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_CURRENT_CAP_SHFT);
    read_val = (read_val * 64);
    read_val = (read_val / 1024);
    scid_status->capacity_in_use = (read_val * 4);
    
    return EFI_SUCCESS;
}

/*==============================================================================
  FUNCTION      config_island_mode

  DESCRIPTION   Function to configure island mode

==============================================================================*/

EFI_STATUS config_island_mode(void)
{
     UINT8 i = 0;
     UINT32 sct_entries_size = sizeof(system_cache_table)/sizeof(system_cache_table[0]);
     for(i=0 ;i <sct_entries_size; i++)
     {
          /* Deactivate SCID's which are activated at boot to configure for island mode */
          if(system_cache_table[i].activate_at_boot)
          {
               scid_deactivate(system_cache_table[i].scid);
          }
     }
     return EFI_SUCCESS;
}

/*==============================================================================
  FUNCTION      system_cache_table_init

  DESCRIPTION   Function to initialize SCT table

==============================================================================*/
void system_cache_table_init()
{
 UINT8 *Addr = NULL;
 EFI_STATUS                  Status = EFI_NOT_FOUND;
 UINT8 i = 0;
 UINT32 write_val = 0, write_val1 = 0;
 UINT32 scid = 0;
 EFI_HWIO_PROTOCOL           *HWIOProtocol = NULL;
 UINT32 sct_entries_size = sizeof(system_cache_table)/sizeof(system_cache_table[0]);
 
 Status = gBS->LocateProtocol(&gEfiHwioProtocolGuid, NULL, (void**)&HWIOProtocol);
 if ((EFI_SUCCESS != Status) || (HWIOProtocol == NULL))
 {
     DEBUG ((EFI_D_ERROR, "ERROR: Failed to locate HWIO Protocol: 0x%08x\n", Status));
     return;
 }
 Status = HWIOProtocol->MapRegion(HWIOProtocol, "+LLCC_BROADCAST_ORLLCC", (UINT8**) &Addr);
  if (EFI_SUCCESS != Status)
 {
  DEBUG ((EFI_D_ERROR, "ERROR: Failed to map LLCC_BROADCAST_ORLLCC base address: 0x%08x\n", Status));
  return;
 }
 
 for(i=0 ;i <sct_entries_size; i++)
 {
     scid = system_cache_table[i].scid;
     /*Configure ATTRIBUTE0*/
     /*write_val = (system_cache_table[i].bonus_ways << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_BONUS_WAYS_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_BONUS_WAYS_BMSK; 
     HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE,scid,write_val);*/
     write_val = 0;
     write_val |= (system_cache_table[i].reserved_ways << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RESRVED_WAYS_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RESRVED_WAYS_BMSK; 
     HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE,scid,write_val);

     /*Configure ATTRIBUTE1*/
     write_val = 0;
     write_val = (system_cache_table[i].cache_mode << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_CACHING_MODE_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_CACHING_MODE_BMSK;
     //write_val |= (system_cache_table[i].probe_target_ways_only << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PROBE_TARGET_WAYS_ONLY_SHFT)
     //& HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PROBE_TARGET_WAYS_ONLY_BMSK; 

     write_val1 = 0;
     /*MAX_CAP is per LLCC instance/channel. if a client owns 1MB, MAX_CAP would be 256KB per channel.*/
     write_val1 = system_cache_table[i].max_capacity / 4;
     /*Convert KB to bytes*/
     write_val1 = write_val1 * 1024;
     /*MAX_CAP = <Max capacity (# cache line; 64B per cache line ) >*/
     write_val1 = write_val1 / 64;
     write_val1 = (write_val1 << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_MAX_CAP_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_MAX_CAP_BMSK;
     write_val = write_val | write_val1;
     HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE,scid,write_val);

     /*Configure ATTRIBUTE2*/
     write_val = 0;
     write_val = (system_cache_table[i].bonus_ways << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_BONUS_WAYS_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_BONUS_WAYS_BMSK; 
     HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE2_CFG_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE,scid,write_val);

     if(system_cache_table[i].dis_capacity_alloc)
     {
        write_val = 0;
        write_val = write_val | (1 << system_cache_table[i].scid);
        HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_OUT(LLCC_BROADCAST_ORTRP_REG_BASE, write_val);
     }
     /*if(system_cache_table[i].retain_power_collapse)
     {
        write_val = 0;
        write_val = write_val | (1 << system_cache_table[i].scid);
        HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_SCID_MASK_OUT(LLCC_BROADCAST_ORTRP_REG_BASE, write_val);
     }
     if(system_cache_table[i].activate_at_boot)
     {
        scid_activate(system_cache_table[i].scid);
     }*/
 }
}





