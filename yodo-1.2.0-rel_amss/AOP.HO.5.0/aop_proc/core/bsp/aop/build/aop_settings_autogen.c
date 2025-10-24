/*===========================================================================
                             aop_settings_autogen.c

DESCRIPTION:
  Data for aop settings

Copyright (c) 2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/
//===========================================================================
//                     Includes and Variable Definitions
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "comdef.h"
#include "aop_settings.h"
#include "/local/mnt/workspace/CRMBuilds/AOP.HO.5.0-00285-KAILUA_E-1_20221205_024556/b/HY11_1/aop_proc/core/settings/pmic/interface/pm_config_interface.h"

//---------------------------------------------------------------------------
// Constant / Define Declarations
//--------------------------------------------------------------------------
#define ARRAY_SIZE(arr) sizeof(arr)/sizeof(arr[0])

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Local Object Definitions
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Static Variable Definitions
//---------------------------------------------------------------------------
property_type_t pmic_prop_arr[] = 
{
  {
    .prop_id =  1083086205, /*PM_PROP_SMPS_NUM*/
    .prop_val = (uint32_t)&num_of_smps,
  },
  {
    .prop_id =  3887461134, /*PM_PROP_LDO_NUM*/
    .prop_val = (uint32_t)&num_of_ldo,
  },
  {
    .prop_id =  4154220741, /*PM_PROP_PSTM_SEQ*/
    .prop_val = (uint32_t)&num_of_pstm_seq,
  },
  {
    .prop_id =  1771542602, /*PM_PROP_RPMH_DRV_ID*/
    .prop_val = (uint32_t)&rpmh_drv_id,
  },
  {
    .prop_id =  3225151160, /*PM_PROP_SMPS_RSRC*/
    .prop_val = (uint32_t)&smps_rsrc,
  },
  {
    .prop_id =  2726537294, /*PM_PROP_BOB_RSRC*/
    .prop_val = (uint32_t)&bob_rsrc,
  },
  {
    .prop_id =  574468489, /*PM_PROP_PERIPH_BITMAP*/
    .prop_val = (uint32_t)&pm_periph_bitmap,
  },
  {
    .prop_id =  1288088681, /*PM_PROP_MAX_VOL_WA*/
    .prop_val = (uint32_t)&max_voltage_wa,
  },
  {
    .prop_id =  2026824581, /*PM_PROP_CLK_RSRC*/
    .prop_val = (uint32_t)&clk_rsrc,
  },
  {
    .prop_id =  3924477279, /*PM_PROP_PSTM_INFO*/
    .prop_val = (uint32_t)&pstm_info,
  },
  {
    .prop_id =  3286632528, /*PM_PROP_LDO_DEP*/
    .prop_val = (uint32_t)&ldo_dep,
  },
  {
    .prop_id =  3425736774, /*PM_PROP_CLK_INFO*/
    .prop_val = (uint32_t)&clk_info,
  },
  {
    .prop_id =  1692233251, /*PM_PROP_SMPS_DEP*/
    .prop_val = (uint32_t)&smps_dep,
  },
  {
    .prop_id =  26101631, /*PM_PROP_BOB_DEP*/
    .prop_val = (uint32_t)&bob_dep,
  },
  {
    .prop_id =  305526288, /*PM_PROP_KAILUA_WA*/
    .prop_val = (uint32_t)&kailua_v1p1_wa,
  },
  {
    .prop_id =  800808013, /*PM_PROP_LDO_RAIL*/
    .prop_val = (uint32_t)&ldo_rail,
  },
  {
    .prop_id =  814691694, /*PM_PROP_TARGET_RSRC_NUM*/
    .prop_val = (uint32_t)&num_of_target_rsrc,
  },
  {
    .prop_id =  3859826605, /*PM_PROP_SMPS_RAIL*/
    .prop_val = (uint32_t)&smps_rail,
  },
  {
    .prop_id =  160496984, /*PM_PROP_LDO_RSRC*/
    .prop_val = (uint32_t)&ldo_rsrc,
  },
  {
    .prop_id =  635288609, /*PM_PROP_BOB_NUM*/
    .prop_val = (uint32_t)&num_of_bob,
  },
  {
    .prop_id =  2225604955, /*PM_PROP_BOB_RAIL*/
    .prop_val = (uint32_t)&bob_rail,
  },
  {
    .prop_id =  4027309317, /*PM_PROP_TARGET_RSRC_INFO*/
    .prop_val = (uint32_t)&target_rsrc_info,
  },
  {
    .prop_id =  746413076, /*PM_PROP_CLK_DEP*/
    .prop_val = (uint32_t)&clk_dep,
  },
};

property_type_t ddr_prop_arr[] = 
{
  {
    .prop_id =  902345068, /*mcphy_mipc_en*/
    .prop_val = 0,
  },
};

property_type_t pdc_prop_arr[] = 
{
  {
    .prop_id =  1397337481, /*wlan_pdc_pin_ctrl_sel*/
    .prop_val = 0x393a,
  },
  {
    .prop_id =  2527272689, /*is_wlan_disabled*/
    .prop_val = 0,
  },
};


device_type_t devices[] __attribute__((used)) = {
  {
    .device_id = 1794164735, /*pmic*/
    .num_props_for_device = ARRAY_SIZE(pmic_prop_arr),
    .props = (property_type_t*)&pmic_prop_arr
  },
  {
    .device_id = 251987037, /*ddr*/
    .num_props_for_device = ARRAY_SIZE(ddr_prop_arr),
    .props = (property_type_t*)&ddr_prop_arr
  },
  {
    .device_id = 2124033795, /*pdc*/
    .num_props_for_device = ARRAY_SIZE(pdc_prop_arr),
    .props = (property_type_t*)&pdc_prop_arr
  },
};

__attribute__((section("aop_devcfg_top_sec")))
volatile aop_devcfg_top_t aop_devcfg_top = 
{
  .pDevices = (device_type_t*)(&devices),
  .num_devices = ARRAY_SIZE(devices),
  .cookie = 0xA0DA7A,
};


void aop_settings_init(void)
{ //Need to have some code touching the data else, linker optimizes out.
  aop_devcfg_top.cookie = 0xDEADC0DE;
}
