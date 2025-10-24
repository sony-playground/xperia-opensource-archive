#ifndef __PM_CONFIG_INTERFACE_H__
#define __PM_CONFIG_INTERFACE_H__

/*! \file pm_vrm.h
 *  \n
 *  \brief This file contains PMIC VRM initialization related definitions.
 *  \n  
 *  \n &copy; Copyright 2016 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/rel/aop.ho/5.0/aop_proc/core/settings/pmic/interface/pm_config_interface.h#5 $  

when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
08/29/16   kt     Created
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm.h"
#include "vrm.h"
#include "pm_resources_and_types.h"
#include "rpmh_drv.h"


/*===========================================================================

                     TYPE DEFINITIONS/MACROS

===========================================================================*/

#define PM_MAX_BITMAP_ENTRIES                 32

typedef struct
{
   char* name;
   char* alias_name;
}pm_pwr_resource;

typedef struct
{
   pm_pwr_resource  *parent; // parent resource
   pm_pwr_resource  **children; // array of child resources
   uint32           vreg_child_cnt; // num of vreg children
   uint32           xob_child_cnt; // num of xob children
}pm_pwr_resource_dependency_info;

typedef struct 
{
    unsigned        AccessAllowed:1;        // 0 – No voting Access; 1 – Voting access allowed
    unsigned        RsrcCategory:4;         // Resource category
    unsigned        AlwaysOn:1;             // 0 - allow to be turned off; 1 - always on
    unsigned        MinMode:4;              // 0 - AUTO, 1- IPEAK, 2 - NPM
    unsigned        SafetyHR:22;            // Safety Headroom in mV
    // 32 - bit
    uint16        MinVoltage;          // in mV
    uint16        MaxVoltage;          // in mV
    // 32 - bit
    uint16        EnableFixedTime;            // in micro secs
    uint16        EnableStepperWarmUpTime;    // in micro secs
    // 32 - bit
    uint16        VoltFixedUpTime;            // in micro secs
    uint16        VoltFixedDownTime;          // in micro secs
    // 32 - bit
    uint16        VoltStepperExtraUpTime;     // in micro secs
    uint16        VoltStepperExtraDownTime;   // in micro secs
    // 32 - bit
    uint16        VoltDischargeTime;          // in micro secs
    uint16        ModeFixedTime;              // in micro secs
    // 32 - bit
    unsigned        VregReadyEn:1;          // VREG_READY based settling or not  
    unsigned        VregReadyErrEn:1;       // VREG_READY settling error enabled or not 
    unsigned        VregWdogTimer:5;        // Needed only if VREG_READY settling error enabled
    unsigned        AopHandling:1;          // AopHandling
    uint8        VoltSeqType;          // Voltage sequence type
    uint8        EnableSeqType;        // Enable sequence type
    uint8        ModeSeqType;          // Mode sequence type
    // 32 - bit  
    uint32          DrvOwnMask;          // Owner drv ids mask
    // 32 - bit
    uint32        Reserved;            // Reserved
}pm_vrm_vreg_rail_info_type;

typedef struct 
{
    unsigned        AccessAllowed:1;        // 0 – No voting Access; 1 – Voting access allowed
    unsigned        RsrcCategory:4;         // Resource category
    unsigned        AlwaysOn:1;             // 0 - allow to be turned off; 1 - always on
    uint16          EnableFixedTime;        // in micro secs
    uint8           EnableSeqType;          // Enable sequence type
    unsigned        Reserved:2;             // Reserved
    // 32 - bit  
    uint32          DrvOwnMask;             // Owner drv ids mask
    // 32 - bit
    unsigned        ClkReadyEn:1;           // CLk_READY based settling or not  
    unsigned        ClkReadyErrEn:1;        // CLK_READY settling error enabled or not 
    unsigned        ClkWdogTimer:5;         // Needed only if CLK_READY settling error enabled
    unsigned        Reserved1:25;           // Reserved    
    // 32 - bit
}pm_vrm_clk_info_type;

typedef struct 
{
    char*           pbs_name;         // Resource name
    // 32 - bit
    unsigned        LowVal:8;         // PMIC sequence IDs for PBS sequence
    unsigned        HighVal:8;        // PMIC sequence IDs for PBS sequence 
    unsigned        SettlingTime:16;  // in micro secs
    // 32 - bit
    uint32          DrvOwnMask;    // Owner drv ids mask
    //32 - bit
    unsigned        DefaultVal:8;     // Default PSTM vote
    unsigned        AccessAllowed:1;  // 0 – No voting Access; 1 – Voting access allowed
    unsigned        RsrcCategory:3;   // rsrc category
    uint8           EnableSeqType;    // Enable sequence type
}pm_vrm_pstm_rsrc_info_type;

typedef struct 
{
    unsigned        AccessAllowed:1;        // 0 – No voting Access; 1 – Voting access allowed
    unsigned        SlaveId:4;              // rsrc slave id
    unsigned        BaseAddr:16;            // rsrc base address
    unsigned        RsrcCategory:3;         // rsrc category
    unsigned        EnableAddrOff:8;        // Enable addr offset
    // 32 - bit
    unsigned        EnableFixedTime:16;     // in micro secs
    unsigned        EnableSeqType:8;        // Enable sequence type
    unsigned        ModeAddrOff:8;          // Mode addr offset
    // 32 - bit
    unsigned        ModeFixedTime:8;        // in micro secs
    unsigned        ModeSeqType:8;          // Mode sequence type
    unsigned        VoltAddrOff:8;          // Mode addr offset
    // 32 - bit
    unsigned        VoltFixedTime:8;        // in micro secs
    unsigned        VoltSeqType:8;          // Mode sequence type
    unsigned        MaxVoltage:16;          // Max Voltage
    // 32 - bit
    unsigned        DrvOwnMask:20;          // Owner drv ids mask
    unsigned        Reserved:12;            // Reserved
    // 32 - bit
}pm_vrm_rsrc_info_type;

typedef struct 
{
   char* name;                    // Resource name
   uint32 PmicIndex;              // PMIC index
   pm_vrm_periph_type PeriphType; // PMIC VRM APP peripheral type
   uint32 PeriphId;               // Peripheral Id
   pm_vrm_rsrc_info_type config;
}pm_vrm_target_rsrc_info_type;


extern pm_pwr_resource_dependency_info* smps_dep[];
extern pm_pwr_resource_dependency_info* ldo_dep[];
extern pm_pwr_resource_dependency_info* bob_dep[];
extern pm_pwr_resource_dependency_info* clk_dep[];
extern pm_pwr_resource* smps_rsrc[];
extern pm_pwr_resource* ldo_rsrc[];
extern pm_pwr_resource* bob_rsrc[];
extern pm_pwr_resource* clk_rsrc[];
extern pm_vrm_vreg_rail_info_type* ldo_rail[];
extern pm_vrm_vreg_rail_info_type* smps_rail[];
extern pm_vrm_clk_info_type* clk_info[];
extern pm_vrm_vreg_rail_info_type* bob_rail[];
extern pm_vrm_pstm_rsrc_info_type* pstm_info[];
extern pm_vrm_target_rsrc_info_type target_rsrc_info[];

extern uint32 num_of_target_rsrc[];
extern uint32 num_of_ldo[];        
extern uint32 num_of_smps[];       
extern uint32 num_of_bob[];        
extern uint32 num_of_pstm_seq[];  

extern uint32 rpmh_drv_id[];

extern uint32 kailua_v1p1_wa[];

extern uint32 max_voltage_wa[];

extern uint8 pm_periph_bitmap[][PM_MAX_BITMAP_ENTRIES];

extern pm_pwr_resource* smps7_b_child_dep[];
extern pm_pwr_resource* smps8_b_child_dep[];
extern pm_pwr_resource* smps10_b_child_dep[];

#endif //__PM_CONFIG_INTERFACE_H__
