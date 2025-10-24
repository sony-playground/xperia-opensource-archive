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

typedef enum
{
   NORMAL = 0,
   NSE,
}CACHE_MODE;

typedef enum
{
   ACTIVE = 0,
   GLOBAL,
   PERSISTENT,
   ISLAND,
}SCID_TYPE;

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
#define CAMERA_EXP0    34
#define CPU_HWT        36
#define CAMERA_EXP1    38
#define COMPUTE_HCP    39
#define LCP_DARE       40
#define AUDIO_ENPU     45
#define ISLAND_1       46
#define ISLAND_2       47
#define ISLAND_3       48
#define ISLAND_4       49
#define CAMERA_EXP2    50
#define CAMERA_EXP3    51
#define CAMERA_EXP4    52
#define DISPLAY_WB     53
#define DISPLAY_1      54
#define VIDSC_VSP      64

/* System Cache Table entry */
struct system_cache_table_entry
{
 UINT32 usecase_id;
 UINT32 scid;
 UINT32 max_capacity;
 UINT32 bonus_ways;
 UINT32 reserved_ways;
 UINT32 cache_mode;
 BOOLEAN dis_capacity_alloc;
 BOOLEAN write_scid_en;
 BOOLEAN write_scid_cacheable_en;
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