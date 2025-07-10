/*===============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
  
  FILE: 		SystemCacheTargetLib.h
  
  REVISION HISTORY
  when       who     what, where, why
  --------   ---     ----------------------------------------------------------
  03/11/21   dais      Created
================================================================================*/
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>

#define CACHE_MODE_NORMAL   0
#define CACHE_MODE_NSE      1
#define ACTIVATE_OPCODE   0x1   // Binary - 01
#define DEACTIVATE_OPCODE 0x2   // Binary - 10
#define TRIGGER_VALUE     0x1

/* USECASE ID */
#define CPUSS           1
#define VIDSC0          2
#define AUDIO           6
#define MDMHP_GROW      7
#define MDMHW           9
#define COMPUTE        10
#define GPUHTW         11
#define GPU            12
#define MMUHWT         13
#define DISPLAY        16
#define MDM_PAGING     21
#define AUDIOHW        22
#define CVP            28
#define MDM_VPE        29
#define WRITE_CACHE    31
#define CVPFW          32
#define CPUSS1         33
#define CAMERA_EXP0    34
#define CPU_MTE        35
#define CPU_HWT        36
#define CAMERA_EXP1    38

/* System Cache Table entry */
struct system_cache_table_entry
{
 UINT32 usecase_id;
 UINT32 scid;
 UINT32 max_capacity;
 UINT32 priority;
 BOOLEAN fixedsize;
 UINT32 bonus_ways;
 UINT32 reserved_ways;
 UINT32 cache_mode;
 UINT32 probe_target_ways_only;
 BOOLEAN dis_capacity_alloc;
 BOOLEAN write_scid_en;
 BOOLEAN write_scid_cacheable_en;
 BOOLEAN retain_power_collapse;
 BOOLEAN activate_at_boot;
 BOOLEAN sw_por;
};

/*==============================================================================
  FUNCTION      system_cache_act_deact

  DESCRIPTION   Function to activate/deactivate particular SCID

==============================================================================*/
void system_cache_table_init();

/*==============================================================================
  FUNCTION      scid_activate

  DESCRIPTION   Function to activate particular SCID

==============================================================================*/
void scid_activate(UINT32 scid);

/*==============================================================================
  FUNCTION      scid_deactivate

  DESCRIPTION   Function to deactivate particular SCID

==============================================================================*/

void scid_deactivate(UINT32 scid);