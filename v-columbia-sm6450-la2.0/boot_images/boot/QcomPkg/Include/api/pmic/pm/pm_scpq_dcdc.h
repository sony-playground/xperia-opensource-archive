#ifndef __PM_SCPQ_DCDC_H__
#define __PM_SCPQ_DCDC_H__

/*! \file
 *  \n
 *  \brief  pm_scpq_dcdc.h PMIC-SCPQ MODULE RELATED DECLARATION 
 *  \details  This header file contains functions and variable declarations 
 *  to support Qualcomm PMIC SCPQ DCDC (Switch-Mode Battery Charger) module. The 
 *  Switched-Mode Battery Charger (SCPQ DCDC) module includes a buck regulated 
 *  battery charger with integrated switches. The SCPQ DCDC module, along with the 
 *  Over Voltage Proection (OVP) module will majorly be used by charger 
 *  appliation for charging Li-Ion batteries with high current (up to 2A).
 *  \n &copy;
 *  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.  All Rights Reserved. 
 *  Qualcomm Technologies Proprietary and Confidential.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
12/02/19    zzx    Initial revision
========================================================================== */
#include "com_dtypes.h"
#include "pm_err_flags.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
typedef enum
{
  PM_SCPQ_DCDC_OTG_CFG_OTG_EN_SRC_CFG           = 0, //0 = OTG Enable Source Command, 1 = OTG Enable Source Type-C/RID
  PM_SCPQ_DCDC_OTG_CFG_ENABLE_OTG_IN_DEBUG_MODE = 1, //0 = Do not enable OTG in debug mode, 1 = Enable OTG in debug mode
  PM_SCPQ_DCDC_OTG_EN_SOC_BASED_OTG_UVLO        = 4, //0 = SOC based OTG UVLO diabled, 1 = Enable SOC based OTG UVLO
  PM_SCPQ_DCDC_OTG_HICCUP_CNTR_RST_TIMER_SEL    = 5, //0 = 450/840/1700/3500ms (dpenpends on BOOST_LARGE_CAP_SS_TIMEOUT 1 = 40ms
  PM_SCPQ_DCDC_CFG_FASTROLESWAP_START_OPTION    = 6, //0 = Directly switch on boost mode, 1 = Turn off buck and turn on boost
  PM_SCPQ_DCDC_OTG_CFG_INVALID,                      //INVALID
}pm_scpq_dcdc_otg_cfg_type;


//*  OTG status type *
typedef enum
{
  PM_SCPQ_DCDC_OTG_DISABLED,
  PM_SCPQ_DCDC_OTG_EXECUTING_ENABLE_SEQ,
  PM_SCPQ_DCDC_OTG_ENABLED,
  PM_SCPQ_DCDC_OTG_EXECUTING_DISABLE_SEQ,
  PM_SCPQ_DCDC_OTG_ERROR,
  PM_SCPQ_DCDC_OTG_STATUS_INVALID
}pm_scpq_dcdc_otg_status_type;


typedef struct _pm_scpq_dcdc_icl_status_type
{
  uint32 icl_max_status;   //Max ICL value
  uint32 icl_aicl_status;  //ICL status post AICL
  uint32 icl_thm_status;   //ICL status post HW therm adjustment
  uint32 icl_final_status; //ICL status post AICL, HW therm and SW therm adjustment
}pm_scpq_dcdc_icl_status_type, *ppm_scpq_dcdc_icl_status_type;

typedef struct
{
  uint8 valid_input_source : 1;
  uint8 input_ss_done : 1; // switcher softstart complete
  uint8 use_usbin : 1; // Use USBIN to power the internal arbitration VARB circuit
  uint8 use_wls : 1; // Use wireless to power the internal arbitration VARB circuit
  uint8 usbin_suspend : 1;
  uint8 wls_suspend : 1;
  uint8 power_path : 2;  // system powered by: 1-battery, 2-USBIN, 3-Wireless
} pm_scpq_dcdc_power_path_status;

/*===========================================================================

                        SCPQ DCDC DRIVER FUNCTION PROTOTYPES

===========================================================================*/
/**
 * @brief This function enable/disable OTG functionality.
 * 
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] enable:      Whether to enable or disable otg.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_dcdc_otg_enable(uint32 pmic_index,boolean enable);

/**
 * @brief This function configures OTG configuration.
 * 
 * @details
 *  This function configures OTG configuration.
 *  The following can be configured in this API:
 *                1) OTG source
 *                2) OTG in debug mode or not
 *                3) fast role swap start option
 * 
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[in] otg_cfg_type:  which configuration to be configured.
 * @param[in] set_value:     Destinate configure value.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_dcdc_config_otg(uint32 pmic_index, pm_scpq_dcdc_otg_cfg_type otg_cfg_type, boolean set_value);

/**
 * @brief This function returns OTG status.
 * 
 * @details
 *  This function returns OTG status. enabled/disabled/executing enable sequence/executing disable sequence/error
 * 
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[out] otg_status:  Refer #pm_scpq_dcdc_otg_status_type for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_dcdc_get_otg_status(uint32 pmic_index, pm_scpq_dcdc_otg_status_type* otg_status);

/**
 * @brief This function returns ICL status
 *
 * @details
 *  This function returns ICL status
 *
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[out] icl_status:  Refer #pm_scpq_dcdc_icl_status_type for details.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_dcdc_get_icl_status(uint32 pmic_index, pm_scpq_dcdc_icl_status_type *icl_status);

/**
 * @brief This function get charging power path status
 *
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[out] power_path_status:  Refer #pm_scpq_dcdc_power_path_status for details.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_dcdc_get_power_path_status(uint32 pmic_index, pm_scpq_dcdc_power_path_status *power_path_status);


#endif /* __PM_SCPQ_DCDC_H__*/

