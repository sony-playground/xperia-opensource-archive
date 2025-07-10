/*===============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		SystemCacheTargetLib.c
  
  REVISION HISTORY
  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  03/11/21   dais      Created
================================================================================*/

#include "llcc_trp_reg_or.h"
#include "SystemCacheTargetLib.h"

/* SCT table for Palima */

struct system_cache_table_entry system_cache_table[] =
{
    {CPUSS,       1, 2048, 1, FALSE,  0xFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE,  TRUE, TRUE},
    {VIDSC0,      2,  512, 3,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {CPUSS1,      3, 1024, 1,  TRUE,  0xFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {CAMERA_EXP0, 4,  256, 3,  TRUE, 0xF000, 0x0,    CACHE_MODE_NSE, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {CPU_HWT,     5,  512, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE,  TRUE, TRUE},
    {AUDIO,       6, 1024, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE},
    {MDMHP_GROW,  7, 1024, 3, FALSE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {MDMHW,       9, 1024, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {COMPUTE,    10, 4096, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {GPUHTW,     11, 1024, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {GPU,        12, 1024, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE,  TRUE, FALSE,  TRUE, FALSE, TRUE},
    {MMUHWT,     13,  768, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE, FALSE,  TRUE, TRUE},
    {DISPLAY,    16, 4096, 2,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {CVPFW,      17,  512, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {MDM_PAGING, 21, 1024, 0,  TRUE, 0xF000, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {AUDIOHW,    22, 1024, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE},
    {CPU_MTE,    23,  256, 1,  TRUE,  0xFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE, FALSE,  TRUE, TRUE},
    {CAMERA_EXP1,27,  256, 3,  TRUE, 0xF000, 0x0,    CACHE_MODE_NSE, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {CVP,        28,  256, 3,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {MDM_VPE,    29,   64, 1,  TRUE, 0xF000, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE,  TRUE, FALSE, TRUE},
    {WRITE_CACHE,31,  512, 1,  TRUE, 0xFFFF, 0x0, CACHE_MODE_NORMAL, 0, FALSE, FALSE, FALSE, FALSE,  TRUE, TRUE},
};

/*==============================================================================
  FUNCTION      scid_activate

  DESCRIPTION   Function to activate particular SCID

==============================================================================*/

void scid_activate(UINT32 scid)
{
    UINT32 write_val = 0, read_val = 0;

    write_val =  (ACTIVATE_OPCODE << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT)
                  & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK;
    write_val |= TRIGGER_VALUE;
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, write_val);
    /* Clear trigger bit */
    write_val = 0;
    write_val =  (ACTIVATE_OPCODE << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT)
                  & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK;
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, write_val);

    /* Check if activation is complete */
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACTIVE_BMSK);
    while((read_val & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_ACTIVE_BMSK) == 0);
}

/*==============================================================================
  FUNCTION      scid_deactivate

  DESCRIPTION   Function to deactivate particular SCID

==============================================================================*/

void scid_deactivate(UINT32 scid)
{
    UINT32 write_val = 0, read_val = 0;
    write_val =  (DEACTIVATE_OPCODE << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT)
                    & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK;
    write_val |= TRIGGER_VALUE;
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, write_val);
    /* Clear trigger bit */
    write_val = 0;
    write_val =  (DEACTIVATE_OPCODE << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_SHFT)
                    & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OPCODE_BMSK;
    HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_ACT_CTRL_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, write_val);

    /* Check if deactivation is complete */
    read_val = HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_INMI(LLCC_BROADCAST_ORTRP_REG_BASE, scid, HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_DEACTIVE_BMSK);
    while((read_val & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_n_STATUS_DEACTIVE_BMSK) == 0);
}

/*==============================================================================
  FUNCTION      system_cache_table_init

  DESCRIPTION   Function to initialize SCT table

==============================================================================*/
void system_cache_table_init()
{
 UINT8 i = 0;
 UINT32 write_val = 0, write_val1 = 0;
 UINT32 scid = 0;
 UINT32 sct_entries_size = sizeof(system_cache_table)/sizeof(system_cache_table[0]);
 for(i=0 ;i <sct_entries_size; i++)
 {
     scid = system_cache_table[i].scid;
     //Configure ATTRIBUTE0
     write_val = (system_cache_table[i].bonus_ways << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_BONUS_WAYS_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_BONUS_WAYS_BMSK; 
     write_val |= (system_cache_table[i].reserved_ways << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RESRVED_WAYS_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_RESRVED_WAYS_BMSK; 
     HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE0_CFG_OUTI(LLCC_BROADCAST_ORTRP_REG_BASE,scid,write_val);
     //Configure ATTRIBUTE1
     write_val = 0;
     write_val = (system_cache_table[i].cache_mode << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_CACHING_MODE_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_CACHING_MODE_BMSK;
     write_val |= (system_cache_table[i].probe_target_ways_only << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PROBE_TARGET_WAYS_ONLY_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PROBE_TARGET_WAYS_ONLY_BMSK; 
     if(system_cache_table[i].fixedsize)
     {
        write_val |= (1 << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_FIXEDSIZE_SHFT)
        & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_FIXEDSIZE_BMSK;
     }
     write_val |= (system_cache_table[i].priority << HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PRIORITY_SHFT)
     & HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCT_n_ATTRIBUTE1_CFG_PRIORITY_BMSK;

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

     if(system_cache_table[i].dis_capacity_alloc)
     {
        write_val = 0;
        write_val = write_val | (1 << system_cache_table[i].scid);
        HWIO_LLCC_BROADCAST_ORLLCC_TRP_SCID_DISABLE_CAP_ALLOC_OUT(LLCC_BROADCAST_ORTRP_REG_BASE, write_val);
     }
     if(system_cache_table[i].retain_power_collapse)
     {
        write_val = 0;
        write_val = write_val | (1 << system_cache_table[i].scid);
        HWIO_LLCC_BROADCAST_ORLLCC_TRP_PCB_ACT_SCID_MASK_OUT(LLCC_BROADCAST_ORTRP_REG_BASE, write_val);
     }
 }
}





