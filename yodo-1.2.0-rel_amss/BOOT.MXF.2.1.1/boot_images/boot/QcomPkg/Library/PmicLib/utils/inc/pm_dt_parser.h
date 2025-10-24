#ifndef __PM_DT_PARSER_H__
#define __PM_DT_PARSER_H__

/*! \file pm_dt_parser.h
 *
 *  \brief  This file contains the function definitions for PMIC device tree
 *
 *  &copy; Copyright 2021-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/inc/pm_dt_parser.h#4 $
$Author: pwbldsvc $
$DateTime: 2022/12/01 01:05:41 $
when       who     what, where, why
________   ___     __________________________________________________________
02/14/21   al      PMIC device tree initial draft
===========================================================================*/

/*=============================================================================

                       DEFINITIONS

=============================================================================*/



/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

#include "comdef.h"
#include "DTBExtnLib.h"

#include "pm_device.h"
#include "SpmiCfg.h"
#include "SpmiBusCfg.h"
#include "pm_resources_and_types.h"
#include "pm_sbl_boot.h"
#include "pm_config_sbl.h"

#define PM_OEM_PSI_SEQ_STEP_LENGTH     9
#define PM_OEM_PSI_CLOGIC_STEP_LENGTH  7


typedef enum
{
  PMIC_DT_NODE_PM_SW_CONFIG,
  PMIC_DT_NODE_PM_PON,
  PMIC_DT_NODE_PM_LDO,
  PMIC_DT_NODE_PM_SMPS,
  PMIC_DT_NODE_PM_BOB,
  PMIC_DT_NODE_PM_CLOCK,
  PMIC_DT_NODE_PM_CHARGER,
  PMIC_DT_NODE_PM_HAPTICS,
  PMIC_DT_NODE_PM_DISPLAY,
  PMIC_DT_NODE_PM_CAMERA,
  PMIC_DT_NODE_ARB_ACCESS,
  PMIC_DT_NODE_ARB_MGPI,
  PMIC_DT_NODE_ARB_PVC,
  PMIC_DT_NODE_OPSI_CONFIG,
  PMIC_DT_NODE_INVALID,
}pmic_dt_node_type;

typedef struct
{
  uint8 busId;
  uint8 slaveId;
  uint8 periphId;
  uint8 operation;
}pm_dt_spmi_cfg;

typedef struct
{
  uint32  busid;
  uint32  sid;
  uint32  periph;
  uint32  value;
}pm_dt_periph_cfg_type;

typedef struct
{
  uint32* none_owner;
  uint32  none_count;
  uint32* apps_owner;
  uint32  apps_count;
  uint32* tz_owner;
  uint32  tz_count;
  uint32* mss_owner;
  uint32  mss_count;
  uint32* adsp_owner;
  uint32  adsp_count;
  uint32* aop_owner;
  uint32  aop_count;
  uint32* ssc_owner;
  uint32  ssc_count;
  uint32* secpro_owner;
  uint32  secpro_count;
  uint32* uefi_owner;
  uint32  uefi_count;
  uint32* invalid_owner;
  uint32  invalid_count;
}pm_access_ctrl_config;


typedef struct
{
  uint32        pvc_port_id;
  uint32        spmi_prioriety;
  SpmiCfg_Ppid  *addr_cfg;
  uint32        addr_cfg_count;
}pm_pvc_node_type;

typedef struct
{
  pm_pvc_node_type *pvc_node;
  uint32           node_count;
}pm_dt_pvc_config;

typedef struct
{
  uint32 *cfg_data;
  uint32 cfg_count;
}pm_dt_mgpi_config;


typedef struct
{
  uint32   verbose;             // for verbose logging
  uint32   apply_rsns_trim;     // Whether to apply rsns trim value
  uint32   rsns_trim_value;     // R-sense trim value
  uint32   primming_enable;		//Primming enable for VDD2L undershoot overshoot
  uint32   *post_driver_init;
  uint32   post_driver_init_count;
}pm_dt_sw_config;

typedef struct
{
  uint32  clogic_version;
  uint32  clogic_count;    
  uint32  *clogic_data;
}pm_dt_psi_cond_config;

typedef struct
{
  uint8  psi_variant_major;
  uint16  psi_variant_minor;  
  uint32  version;
  uint32  settings_count;    
  uint32  *opsi_seq;
  pm_dt_psi_cond_config *clogic;
}pm_dt_psi_config;




typedef struct
{
  boolean pshold_enable;
  uint8   ps_hold_reset_type;

  uint8   enable_smpl;
  uint32  smpl_delay;

  boolean s2_kpdpwr_enable;
  uint8   s2_kpdpwr_reset_type;
  uint32  s2_kpdpwr_s1_ms;
  uint32  s2_kpdpwr_s2_ms;

  boolean s2_kpdpwr_resin_enable;
  uint8   s2_kpdpwr_resin_reset_type;
  uint32  s2_kpdpwr_resin_s1_ms;
  uint32  s2_kpdpwr_resin_s2_ms;

  boolean s2_resin_enable;
  uint8   s2_resin_reset_type;
  uint32  s2_resin_s1_ms;
  uint32  s2_resin_s2_ms;

  boolean s3_enable;
  boolean s3_reset_src;
  uint32  s3_reset_timer_value_ms;

  uint8   uvlo_config_count;
  uint32  *uvlo_cfg;

  uint8   ovlo_config_count;
  uint32  *ovlo_cfg;

  uint32 dbnc_time_ms;
  uint8  dbnc_chk_at;
  uint8  vreg_sp_flag_val;
  uint8  pre_psi_flag_val;
}pm_dt_pon_config;



typedef struct
{
  boolean parallel_charger;
  uint32 charger_pmic_index;
  uint32 loader_dbc_threshold;
  uint32 dbc_sdp_thd_inc;      /* increase threshold to avoid triggering uvlo due to SDP charger can not provide enough power */
  boolean skip_loader_dbc;     /* loader dbc value, skip or not */
  uint32 core_dbc_threshold;
  boolean skip_core_dbc;       /* core dbc value, skip or not */

  uint32 uv_oc_1s_threshold;  //For whole 1S pack
  uint32 uv_oc_2s_threshold;  //This is one cell threshold for 2S on currently solution

  boolean apply_ichg_fs;
  uint32 ichg_fs;

  uint32 batt_2s_option;

  boolean apply_too_hot_afp;
  uint32 too_hot_afp_threshold;

  boolean apply_too_cold_afp;
  int32 too_cold_afp_threshold;

  boolean apply_boot_wo_batt;
  boolean boot_wo_batt;
  uint32 icl_boot_wo_batt;

  boolean apply_float_voltage;
  uint32 float_voltage_mv;

  boolean apply_pre_charge_current;
  uint32 pre_charge_ma;

  boolean apply_fast_charge_current;
  uint32 fast_charge_ma;

  boolean apply_icl;
  uint32 icl_ma;

  boolean apply_float_charger_icl;
  uint32 float_charger_icl_ma;

  boolean apply_vsysmin;
  uint32 vsysmin;

  boolean usb_suspend;

  uint32 wls_usb_prior_swap;

  uint32 batt_detect_src;
  uint32 max_dbg_board_id;
  uint32 min_dbg_board_id;

  boolean detect_jig_by_therm;
  uint32 max_therm;
  uint32 min_therm;
  uint32 jig_icl_ma;
  uint32 uvp_recover_delay;

  boolean ignore_temp_in_dbc;

  uint32 batt_therm_pull_up;

  boolean ibat_via_ext_sense;
  uint32 ext_rsns_adc_scale;

  uint32 vbat_thd_rtc_pon;
  uint32 vsys_min_recover_mv;  
  uint32 vflt_recover_mv;
}pm_dt_charger_config;

typedef struct
{
  uint32 ext_boost_vdd;
  uint32 vmax_hdrm;
  uint32 vmax_mv;
  uint32 tlra_ol;
  uint32 autores_cfg;
  uint32 vbatt_min_mv;			/* Minimum VBATT in mV for haptics to be activated */
  uint32 boost_cfg_bob;
  uint32 lra_resistance;
  uint32 swr_io_volt;
}pm_dt_haptics_config;

typedef struct
{
  uint8   swire_map;
  boolean apply_default_volt;
  int32   default_elvss;
  int32   default_elvdd;
  int32   default_oledb;
}pm_dt_display_config;

typedef struct
{
  uint32 reset_gpio[2];
}pm_dt_camera_config;

/*! \brief
 *  This function returns PMIC DTB node structure
 *  IN argument is property id
 */
void*
pm_dt_get_node( pmic_dt_node_type node );

/*! \brief
 *  This function returns PMIC DTB node property size
 *  IN     : node id, property name
 *  RETURN : size of property 
 */
uint32
pm_dt_get_node_prop_size(uint32 node_id, const char *prop_name);

/*! \brief
 *  This function gives pointer to PMIC DTB node property values
 *  IN     : node id, property name, size of property
 *  OUT    : pointer to the list of property values
 *  RETURN : pm_err_flag_type
 */
pm_err_flag_type
pm_dt_get_node_prop_value(uint32 node_id, const char *prop_name, uint32 size, uint32 *prop_list);


#endif //__PM_DT_PARSER_H__
