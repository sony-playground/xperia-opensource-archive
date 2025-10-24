#ifndef __PM_APP_CHG_H__
#define __PM_APP_CHG_H__

/*! \file
*  \n
*  \brief  pm_app_chg.h PMIC charger app RELATED DECLARATION 
*  \details  This header file contains functions and variable declarations 
*  to support Qualcomm charger module.
*  \n &copy; Copyright 2020-2022 QUALCOMM Technologies Incorporated, All Rights Reserved.
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who    what, where, why
--------    ---    ---------------------------------------------------------- 
02/20/2020  xp     Initial version. 
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"
#include "pm_dt_parser.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

/*
 * OEMs that don't use slave charger may want to re-use the GPIO reserved for Slave Charger,
 * PSI will read flag and not configure slave charger related.
 */
typedef struct
{
  boolean slave_charger_present;
  uint32  sdam_pmic;
  uint16  sdam_flag_addr;
} pm_chg_slave_charger_config_type;


/*
 * Init for charger application. All the functions here should be called after this.
 */
pm_err_flag_type 
pm_app_chg_init(void);

pm_dt_charger_config *
pm_get_charger_dt_config(void);

/* 
 * Get the debug board id min and max values(in ohms).
 * @param min [out]: Get min value of the debug board id. Caller must allocate the memory for this parameter.
 * @param max [out]: Get max value of the debug board id. Caller must allocate the memory for this parameter.
 * @return:	 		 None
 *
 */
void 
pm_app_chg_get_debug_board_id_min_max(uint32* min, uint32* max);

/* 
 * Check if the battery charge is low and charge to minimum level, if it is true.
 * @param: None
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_app_chg_check_weak_battery_status(void);

/* 
 * To check if debug board is present.
 * @param present [out]: To get if debug board is present. 
 *                       Caller must allocate the memory for this parameter.
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 *
 */
pm_err_flag_type 
pm_app_chg_is_debug_board_present(boolean* present);

/*
 * As a Workaround for Puhi/PM8350B reverse boost OCP issue
 * This change is to limit IBAT to <4A and IOTG to <3A.
 */
pm_err_flag_type 
pm_app_chg_trim_otg_offset_and_gain(void);


/*
 * Configure USB input current limit, except for SDP or DAM cable connected but without battery
 */
pm_err_flag_type 
pm_app_chg_configure_usb_icl(uint32 icl_ma);

/**
 * @brief  Detect battery UV / OC status and recover if it's UV/OC-ed 1S battery
 * 
 * @details
 *  This function detects battery UV/OC status and recover if it's UV/OC-ed 1S battery, set flag but not recover if it's UV/OC-ed 2S battery
 * 
 * @param[out] uv_oc_recover_2s_batt: TRUE = UV/OC-ed 2S battery is detected. Default to FALSE.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_app_chg_battery_uv_oc_detection();

/**
 * @brief  Check whether current power supply needs to do bypass DBC
 * 
 * @details
 *  This function check whether current power supply needs to do bypass DBC
 * 
 * @param bypass_dbc[out]: TRUE ---- needs to bypass DBC
 *                         FALSE---- needs to do DBC
 * 
 * @return PM_ERR_FLAG_SUCCESS if success, otherwise error code.
 */
pm_err_flag_type 
pm_app_chg_dbc_condition_check(boolean* bypass_dbc);

/**
 * @brief  Enable charger watch dog
 * 
 * @details
 *  This function detects battery UV/OC status and recover if it's UV/OC-ed 1S battery, set flag but not recover if it's UV/OC-ed 2S battery
 * 
 * @param[in] enable: TRUE = UEnable charger watch dog.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_app_chg_enable_charger_wdog(boolean enable);

/**
 * @brief  Dead battery charging flow
 * 
 * @details
 *  This function will charge dead battery up when relative dbc config is set
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_app_chg_dead_battery_charging(void);


#endif /*__PM_APP_CHG_H__*/

