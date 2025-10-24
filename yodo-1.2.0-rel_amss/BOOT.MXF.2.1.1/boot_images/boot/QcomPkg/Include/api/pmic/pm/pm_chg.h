#ifndef __PM_CHG_H__
#define __PM_CHG_H__

/*! \file
*  \n
*  \brief  pm_chg.h PMIC-SCHG MODULE RELATED DECLARATION 
*  \details  This header file contains common functions and variable declarations 
*  to support Qualcomm PMIC charger module.
*  The structure, pm_chg_info_type, defined in this file is shared with XBL Core.
*  \n &copy; Copyright 2016-2022 QUALCOMM Technologies Inc, All Rights Reserved
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who    what, where, why
--------   ---    ---------------------------------------------------------- 
03/05/18   va     adding uefi charger fw mode flag for charger fw
07/01/16   aab    Initial version. 
========================================================================== */
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"


/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

typedef struct
{
  uint32  version;        /**< Version Info */
  int32   sbl_entry_mV;   /**< XBL loader entry Mv*/
  int32   sbl_entry_soc;  /**< XBL loader entry Soc; if in case the integrity bit is already set */
  int32   uefi_entry_mV;  /**< XBL Core Entry Mv*/
  int32   uefi_entry_soc; /**< XBL Core entry Soc */
  int32   uefi_exit_mV;   /**< XBL Core exit Mv*/
  int32   uefi_exit_soc;  /**< XBL Core Exit Soc */
  uint32  uefi_charger_fw_mode; /**< uefi_charger_fw_mode */
}pm_chg_info_type;

typedef enum
{
  PM_CHARGER_PORT_SDP_CHARGER,    // Standard Downstream Port
  PM_CHARGER_PORT_OCP_CHARGER,    // Other charging port
  PM_CHARGER_PORT_CDP_CHARGER,    // Charging Downstream Port
  PM_CHARGER_PORT_DCP_CHARGER,    // Dedicated Charging Port
  PM_CHARGER_PORT_FLOAT_CHARGER,  // Float charging port
  PM_CHARGER_PORT_QC_2P0_CHARGER, // Quick charger 2.0
  PM_CHARGER_PORT_QC_3P0_CHARGER, // Quick charger 3.0
  PM_CHARGER_PORT_TYPE_INVALID
} pm_chg_charger_port_type;

////////////////     Type-C related struct     ////////////////
typedef enum
{
  PM_CHG_TYPEC_ORIENTATION_RESERVED,
  PM_CHG_TYPEC_ORIENTATION_PLUG_UNFLIP,      // CC1 is connected
  PM_CHG_TYPEC_ORIENTATION_PLUG_FLIP,        // CC2 is connected
  PM_CHG_TYPEC_ORIENTATION_PLUG_OPEN,
  PM_CHG_TYPEC_ORIENTATION_PLUG_INVALID
} pm_chg_typec_orientation;

typedef enum
{
  PM_CHG_TYPEC_ROLE_NONE,
  PM_CHG_TYPEC_ROLE_DFP,
  PM_CHG_TYPEC_ROLE_UFP,
  PM_CHG_TYPEC_ROLE_INVALID
} pm_chg_typec_port_role_type;


typedef enum
{
  PM_TYPEC_CURR_ADV_RESERVED,
  PM_TYPEC_CURR_ADV_3A,           // Current advertisement 3.0A
  PM_TYPEC_CURR_ADV_1P5A,         // Current advertisement 1.5A
  PM_TYPEC_CURR_ADV_STD,          // Current advertisement STD TypeC USB Power
  PM_TYPEC_CURR_ADV_INVALID,
}pm_chg_typec_curr_adv_type;

/* For the types that different source (UFP) attached (we are in DFP).
 */
typedef enum
{
  PM_CHG_TYPEC_UFP_RESERVED,
  PM_CHG_TYPEC_UFP_UNATTACHED,                  // OPEN OPEN
  PM_CHG_TYPEC_UFP_ATTACHED,                    // RD OPEN
  PM_CHG_TYPEC_UFP_NOT_ATTACHED_POWER_CABLE,    // RA OPEN
  PM_CHG_TYPEC_UFP_ATTACHED_POWER_CABLE,        // RD RA
  PM_CHG_TYPEC_UFP_AUDIO_ADAPTER,               // RA RA
  PM_CHG_TYPEC_UFP_DEBUG_ACCESSORY,             // RD RD
  PM_CHG_TYPEC_UFP_INVALID
} pm_chg_typec_ufp_type;

typedef enum
{
  PM_CHG_POWER_PATH_NONE,
  PM_CHG_POWER_PATH_BATTERY,
  PM_CHG_POWER_PATH_USBIN,
  PM_CHG_POWER_PATH_WIRELESS,
  PM_CHG_POWER_PATH_INVALID
} pm_chg_power_path_type;

/**  TYPEC Port status on attach of USB cable **/
// TODO: Check if all the members are still required
typedef struct
{
  pm_chg_typec_orientation        cc_out_sts;
  pm_chg_typec_curr_adv_type      dfp_curr_adv;
  pm_chg_typec_ufp_type           ufp_conn_type;
  boolean                         vbus_sts;
  boolean                         vbus_err_sts;
  boolean                         debounce_done_sts;
  boolean                         vconn_oc_sts;
  boolean                         ccout_out_hiz_sts;
} pm_chg_typec_status_type;

typedef enum
{
  /*DISABLED*/
  PM_CHG_DIS_VBAT_2S_MID,
  /*enable only one MID measurement*/
  PM_CHG_EN_VBAT_2S_MID1,
  /*enable both MID1 and MID2 measurements*/
  PM_CHG_EN_VBAT_2S_MID1_MID2,
  /*invalid*/
  PM_CHG_VBAT_2S_OPTION_INVALID
} pm_chg_2s_battery_option_type;

typedef enum
{
    PM_CHG_2S_BATT_TYPE,
    PM_CHG_1S_BATT_TYPE,
    PM_CHG_2P_BATT_TYPE,
    PM_CHG_BATT_TYPE_INVALID
}pm_chg_battery_type;

typedef enum
{
  PM_CHG_EXT_RSNS_SCALE_1X,
  PM_CHG_EXT_RSNS_SCALE_2X,
  PM_CHG_EXT_RSNS_SCALE_2P5X,
  PM_CHG_EXT_RSNS_SCALE_INVALID
} pm_chg_ext_rsns_scale_type;

typedef struct
{
  boolean is_1s_battery;
  pm_chg_2s_battery_option_type battery_2s_option;
  pm_param_config_enable_type enable_config;
} pm_chg_battery_config_type;

/* FS: Full Scale. Full scale current type*/
typedef enum
{
  /* 12A ICHG full-scale current and 10A total QBG IBAT full-scale current */
  PM_CHG_FS_12A,
  /* 24A ICHG full-scale current and 20A total QBG IBAT full-scale current */
  PM_CHG_FS_24A,
  PM_CHG_FS_TYPE_INVALID,
} pm_chg_fs_type;

typedef struct
{
  pm_chg_fs_type ichg_fs;
  pm_param_config_enable_type enable_config;
} pm_chg_ichg_fs_config_type;

typedef struct
{
  uint32 min_in_ohm;
  uint32 max_in_ohm;
} pm_chg_debug_board_batt_id_range_type;

typedef struct
{
  int32 too_hot_afp_threshold;
  boolean enable_afp_hot;
  int32 too_cold_afp_threshold;
  boolean enable_afp_cold;
} pm_chg_afp_threshold_type;

typedef struct
{
  boolean boot_without_battery;
  uint32  icl_value;  // if boot_without_battery == TRUE, then need to config icl
  pm_param_config_enable_type enable_config;
} pm_chg_no_battery_config_type;

// For configuring single charger value like voltage threshold or current limit etc
typedef struct
{
  uint32 value;
  pm_param_config_enable_type enable_config;
} pm_chg_value_config_type;

typedef struct
{
  /* The threshold of keep SW charging in SBL. In the unit of mV*/
  uint32 pmic_index_charger;
  uint32 dead_battery_threshold;
  pm_chg_ichg_fs_config_type ichg_fs_config;
  pm_chg_battery_config_type battery_config;
  pm_chg_debug_board_batt_id_range_type debug_board_id_range;
  pm_chg_afp_threshold_type afp;
  pm_chg_no_battery_config_type no_battery_cfg;
  pm_chg_value_config_type float_voltage_mv;
  pm_chg_value_config_type pre_charging_current;
  pm_chg_value_config_type fast_charging_current;
  pm_chg_value_config_type usbin_input_current;
} pm_chg_charger_config_type;

/*
 * To get the charger PMIC index.
 *
 * @param pmic_index [out]: The pmic_index parameter is updated with charger pmic index value.
 * Caller is expected to pass a valid pointer.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_chg_get_primary_charger_pmic_index(uint32 *pmic_index);


/* 
 * To check if vbus is present. Even vbus is present, it is possible you get charger type invalid due to APSD unfinished.
 * @param present [out]: To get if vbus is present. 
 *                       Caller must allocate the memory for this parameter.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_chg_is_vbus_present(boolean* present);

/* 
 * To check if battery is present.
 * dependency: pm_bmd_enable should be already called or default enabled in OTP
 * @param present [out]: To get if battery is present. 
 *                       Caller must allocate the memory for this parameter.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_chg_is_battery_present(boolean* present);

/* 
 * To get the charger port type
 * @param charger_type [out]: To carry out the charger type. Caller must allocate the memory for this parameter.
 *                            Check pm_chg_charger_port_type definition for charger port type detail.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 * TODO: If get INVALID type, it is possibe 1) APSD ongoing, 2)USBIN invalid, 3) invalid charger? Need to further check later
 * Is it required to call pm_chg_is_vbus_present and APSD done before calling this API???
 * 
 */
pm_err_flag_type 
pm_chg_get_charger_port_type(pm_chg_charger_port_type* charger_type);

/* 
 * To get the battery voltage in the unit of milli-volt.
 * @param voltage_in_mv [out]: To carry out the value of battery voltage. Caller must allocate the memory for this parameter.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_chg_get_vbatt(uint32* voltage_in_mv);

/* 
 * To get the battery current in the unit of milli-ampere.
 * @param current_in_ma [out]: To carry out the value of battery current. Caller must allocate the memory for this parameter.
 *
 *                       TODO: Validate for negative current case
 *
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_chg_get_ibatt(int32* current_in_ma);

/* 
 * To get the battery open circuit voltage in the unit of milli-volt.
 * @param voltage_in_mv [out]: To carry out the value of battery open circuit voltage. 
 *                       Caller must allocate the memory for this parameter.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_chg_get_battery_ocv(uint32* voltage_in_mv);


/* 
 * To get the type-c port role. DFP or UFP.
 * @param pm_chg_typec_port_role_type [out]: To carry out the type-c role type. 
 *                                           Caller must allocate the memory for this parameter.
 *                                           Check pm_chg_typec_port_role_type structure for role type detail.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_chg_typec_get_port_role(pm_chg_typec_port_role_type* role);

/* 
 * To get the type-c status.
 * @param pm_chg_typec_status_type [out]: To carry out the type-c status. 
 *                                           Caller must allocate the memory for this parameter.
 *                                           Check pm_chg_typec_status_type structure for detail of status.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_chg_get_typec_status(pm_chg_typec_status_type* typec_status);

/*
 * This function read charging status from charger module.
 * @param charging[out]: TRUE ---- charging by USB charger or wireless charger
 *                       FALSE---- not charging
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 */
pm_err_flag_type 
pm_chg_is_charging_ongoing(boolean* charging);

/*
 * Enable/Disable USB charging.
 * @param enable [in]: TRUE ----- enable
 *                     FALSE----- disable
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 */
pm_err_flag_type 
pm_chg_enable_usb_charging(boolean enable);

/*
 * Enable/Disable wireless charging.
 * @param enable [in]: TRUE ----- enable
 *                     FALSE----- disable
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 */
pm_err_flag_type 
pm_chg_enable_wireless_charging(boolean enable);

/*
 * Get if system is powered by battery, USBIN or wireless input. 
 * @param power_path [out]: The system power path.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 */
pm_err_flag_type
pm_chg_get_power_path(pm_chg_power_path_type* power_path);

/*
 * Check if battery is 1S battery or 2S battery. 
 * @param battery_type_is_2s [out]: TRUE ----- 2S battery
                                    FALSE ---- 1S battery
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 */
pm_err_flag_type 
pm_chg_is_2s_batt(boolean* battery_type_is_2s);

#endif /* __PM_CHG_H__ */

