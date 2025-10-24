#ifndef __PM_SCPQ_MISC_H__
#define __PM_SCPQ_MISC_H__

/*! \file
 *  \n
 *  \brief  pm_scpq_misc.h PMIC-SCPQ MODULE RELATED DECLARATION 
 *  \details  This header file contains functions and variable declarations 
 *  to support Qualcomm PMIC SCPQ OTG (Switch-Mode Battery Charger) module. The 
 *  Switched-Mode Battery Charger (SCPQ OTG) module includes a buck regulated 
 *  battery charger with integrated switches. The SCPQ OTG module, along with the 
 *  Over Voltage Proection (OVP) module will majorly be used by charger 
 *  appliation for charging Li-Ion batteries with high current (up to 2A).
 *  \n &copy;
 *  Copyright (c) 2020-2022 Qualcomm Technologies, Inc.  All Rights Reserved. 
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
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

typedef enum {
  PM_SCPQ_MISC_IRQ_WDOG_SNARL,             //Generated when SNARL watchdog timer expires
  PM_SCP_MISC_IRQ_SMB_EN = PM_SCPQ_MISC_IRQ_WDOG_SNARL,
  PM_SCPQ_MISC_IRQ_WDOG_BARK,              //Generated when BARK watchdog timer expires 
  PM_SCPQ_MISC_IRQ_X2D2_EN = PM_SCPQ_MISC_IRQ_WDOG_BARK,
  PM_SCPQ_MISC_IRQ_AICL_FAIL,              //AICL Fail
  PM_SCPQ_MISC_IRQ_AICL_DONE,              //AICL Done
  PM_SCPQ_MISC_IRQ_IMP_TRIGGER_EN,         //Input Missing Poller trigger
  PM_SCPQ_MISC_IRQ_ALL_CHNL_CONV_DONE,     //All channel down
  PM_SCPQ_MISC_IRQ_TEMPERATURE_CHANGE,     //Change in temperature die or skin
  PM_SCPQ_MISC_IRQ_TEMPERATURE_CHANGE_SMB, //temperature change in SMB
  PM_SCPQ_MISC_IRQ_INVALID,                //Invalid
}pm_scpq_misc_irq_type; 


typedef enum 
{
  PM_SCPQ_MISC_POWER_PATH__NONE,
  PM_SCPQ_MISC_POWER_PATH__BATTERY,
  PM_SCPQ_MISC_POWER_PATH__USBIN,
  PM_SCPQ_MISC_POWER_PATH__DCIN,
  PM_SCPQ_MISC_POWER_PATH__INVALID
}pm_scpq_misc_pwr_pth_type;

typedef enum 
{
  PM_SCPQ_MISC_SYSOK_REASON__NONE,
  PM_SCPQ_MISC_SYSOK_REASON__USBIN,
  PM_SCPQ_MISC_SYSOK_REASON__DCIN,
  PM_SCPQ_MISC_SYSOK_REASON__INVALID
}pm_scpq_misc_sysok_reason_type;

typedef struct {
  boolean thermreg_disabled;         // all 3 temperature monitoring sources (skin, die, junction) are disabled 
  boolean temp_below_range;          // when high, indicates skin, die or junction temperature below temp_1 level
  boolean temp_within_range;         // when high, indicates skin, die or junction temperature between temp_1 level and temp_2 level
  boolean temp_above_range;          // when high, indicates skin, die or junction temperature between temp_2 level and temp_3 level
  boolean alert_level;               // when high, indicates skin, die or junction temperature above temp_3 level
  boolean tlim;                      // when high, indicates junction temp above 140c
  boolean therm_range_active;        // 0 = no thermal regulation, 1 = thermal regulation of icl and/or input voltage (qc)
  boolean therm_range_status_7;      // reserved 
}pm_scpq_misc_temp_range_status; 


typedef struct {
  boolean aicl_done;                 // Aicl Done
  boolean aicl_fail;                 // Aicl Fail
  boolean icl_imin;                  // ICL has collapsed down to ICLmin
  boolean dcin_ch_collapse;          // DC Input Collapse (dg)
  boolean usbin_ch_collapse;         // USB Input Collapse (dg)
  boolean highest_dc;                // Switcher in High Duty Cycle
  boolean soft_limit;                // Switcher Hard/Soft Limiting
  boolean aicl_status_7;             // tbd-reserved 
}pm_scpq_misc_aicl_status; 
typedef enum {
  PM_SCPQ_MISC_AICL_CFG_TREG_ALLOW_DECREASE,  // allow decrease during thermal regulation even if increase was due to high duty cycle
  PM_SCPQ_MISC_AICL_CFG_AICL_HIGH_DC_INC,     //allow aicl to increment input current limit even during high duty cycle
  PM_SCPQ_MISC_AICL_CFG_INVALID
}pm_scpq_misc_aicl_cfg;

typedef enum
{
  PM_SCPQ_MISC_AICL_CMD_RERUN_AICL,
  PM_SCPQ_MISC_AICL_CMD_RESTART_AICL,
  PM_SCPQ_MISC_AICL_CMD_RESTART_THERMAL,
  PM_SCPQ_MISC_AICL_CMD_INVALID
}pm_scpq_misc_aicl_cmd_type;

typedef enum {
  PM_SCPQ_MISC_AICL_RERUN_TIME_3S,
  PM_SCPQ_MISC_AICL_RERUN_TIME_12S,
  PM_SCPQ_MISC_AICL_RERUN_TIME_45S,
  PM_SCPQ_MISC_AICL_RERUN_TIME_3M,
  PM_SCPQ_MISC_AICL_RERUN_TIME_CFG_INVALID, //Invalid
}pm_scpq_misc_aicl_rerun_time_cfg;

typedef enum
{
  PM_SCPQ_MISC_BUCKBOOST_REFRESH_PULSE_1_IN_8,
  PM_SCPQ_MISC_BUCKBOOST_REFRESH_PULSE_1_IN_4,
  PM_SCPQ_MISC_BUCKBOOST_REFRESH_PULSE_INVALID,
}pm_scpq_misc_buckboost_refresh_pulse_type;


typedef enum
{
  PM_SCPQ_MISC_SKIN_ADC_CFG,  //1 TO USE AUX THERM PIN FOR BATTERY TEMPERATURE DETECTION (jeita), 0 FOR SKIN TEMP DETECTION
  PM_SCPQ_MISC_SKIN_ADC_SRC_EN,
  PM_SCPQ_MISC_WLS_ADC_SRC_EN = PM_SCPQ_MISC_SKIN_ADC_SRC_EN, 
  PM_SCPQ_MISC_THERMREG_CONNECTOR_ADC_SRC_EN,
  PM_SCPQ_MISC_THERMREG_USB_CONN_ADC_SRC_EN = PM_SCPQ_MISC_THERMREG_CONNECTOR_ADC_SRC_EN,
  PM_SCPQ_MISC_THERMREG_SMB_ADC_SRC_EN,
  PM_SCPQ_MISC_THERM_SRC_CFG_RESERVED,  //Reserved bit 4
  PM_SCPQ_MISC_DIE_ADC_SRC_EN,
  PM_SCPQ_MISC_DIE_CMP_SRC_EN,
  PM_SCPQ_MISC_THERMREG_SW_ICL_ADJUST,  //only software thermal regulation allowed
  PM_SCPQ_MISC_THERM_SRC_CFG_INVALID,
}pm_scpq_misc_therm_src_cfg_type;


typedef enum 
{
  PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_USB_SNS,
  PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_USB_IN,
  PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_WLS_SNS,
  PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_WLS_IN,
  PM_SCPQ_MISC_VIN_DIV16_MUX_SEL_INVALID
} pm_scpq_misc_vin_div16_mux_sel_type;


/*===========================================================================

                 SCPQ OTG DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/**
 * @brief This function enables the SCPQ irq 
 * 
 * @details
 *  This function enables the SCPQ irq 
 * 
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] irq:         Refer #pm_scpq_misc_irq_type for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_irq_enable(uint32 pmic_index, pm_scpq_misc_irq_type irq, boolean enable);

/**
 * @brief This function clears the SCPQ irq 
 * 
 * @details
 *  This function clears the SCPQ irq 
 * 
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] irq:         Refer #pm_scpq_misc_irq_type for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_irq_clear(uint32  pmic_index, pm_scpq_misc_irq_type irq);

 /**
 * @brief This function configures the SCPQ irq trigger 
 * 
 * @details
 *  This function configures the SCPQ irq trigger 
 * 
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] irq:         Refer #pm_scpq_misc_irq_type for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_irq_set_trigger(uint32 pmic_index, pm_scpq_misc_irq_type irq, pm_irq_trigger_type trigger);

/**
 * @brief This function configures the SCPQ for irq 
 * 
 * @details
 *  This function configures the SCPQ for irq 
 * 
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] irq:         Refer #pm_scpq_misc_irq_type for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_irq_status(uint32 pmic_index, pm_scpq_misc_irq_type irq, pm_irq_status_type type, boolean *status);

/**
 * @brief This function returns sysok reason for device
 * 
 * @details
 *  This function returns sysok reason for device
 * 
 * @param[in] pmic_index:     The pmic_index of charger module.
 * @param[out] sysok_reason:  Refer #pm_scpq_misc_sysok_reason_type for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_get_sysok_reason(uint32 pmic_index, pm_scpq_misc_sysok_reason_type *sysok_reason);

/**
 * @brief This function enables selected misc aicl cmd
 * 
 * @details
 *  This function enables selected misc aicl cmd
 *  AICL_CMD register is write only and only affect when setting each command bit to 1, so default to enable
 * 
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[in] aicl_cmd:      Refer #pm_scpq_misc_aicl_cmd_type for details.
 *                                
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_aicl_cmd_enable(uint32 pmic_index, pm_scpq_misc_aicl_cmd_type cmd);

/**
 * @brief This function configures misc aicl rerun time cfg 
 * 
 * @details
 *  This function configures misc aicl re run time cfg 
 * 
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[in] misc_aicl_cfg: Refer #pm_scpq_misc_aicl_rerun_time_cfg for details.
 *                                
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_set_aicl_rerun_time_cfg(uint32 pmic_index, pm_scpq_misc_aicl_rerun_time_cfg aicl_rerun_time);

/**
 * @brief This API sets thermistor source configuration for charging thermal mitigation (inov)
 *
 * @details
 *  This API sets thermistor source configuration for charging thermal mitigation (inov)
 *
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[in] src_cfg_type:  Refer #pm_scpq_misc_therm_src_cfg_type for details.
 * @param[in] enable:        FALSE: 0, TRUE: 1
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_set_thermreg_src_cfg(uint32 pmic_index, pm_scpq_misc_therm_src_cfg_type src_cfg_type, boolean enable);

/**
 * @brief This API sets the pmic die temp threshold levels 
 *
 * @details
 *  This API sets the pmic die temp threshold levels
 *
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] hot_threshold:      Set the hot threshold.
 * @param[in] too_hot_threshold:  Set too hot threshold.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_set_die_temp_thresholds(uint32 pmic_index, int32 hot_threshold, int32 too_hot_threshold);

/**
 * @brief This API sets ADC Channel ID for Battery Thermistor
 *
 * @details
 *  This API sets ADC Channel ID for Battery Thermistor
 *
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] channel_id:         Channel id.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_misc_set_batt_therm_ch_id_cfg(uint32 pmic_index, uint8 channel_id);

/**
 * @brief This API gets ADC Channel ID for Battery Thermistor
 *
 * @details
 *  This API gets ADC Channel ID for Battery Thermistor
 *
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] channel_id:         Channel id.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_misc_get_batt_therm_ch_id_cfg(uint32 pmic_index, uint8* channel_id);

/**
 * @brief This API sets MUX for VIN ADC Channel
 *
 * @details
 *  This API sets MUX value for VIN ADC Channel. 
 *
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] vin_mux_sel:        The Mux value to select the VIN SRC type before reading the ADC Channel.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_set_vin_adc_mux_sel(uint32 pmic_index, pm_scpq_misc_vin_div16_mux_sel_type vin_mux_sel);


/**
 * @brief Enable or disable therm channel 
 *
 * @details
 *  Enable or disable therm channel.
 *
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] enable:             TRUE --- Enable therm channel. FALSE --- Disable therm channel.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_batt_therm_ch_enable(uint32 pmic_index, boolean enable);




#endif /* __PM_SCPQ_MISC_H__*/

