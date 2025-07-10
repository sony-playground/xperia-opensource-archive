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
#include "pm_resources_and_types.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

typedef enum {
  PM_SCPQ_MISC_IRQ_WDOG_SNARL,             //Generated when SNARL watchdog timer expires
  PM_SCPQ_MISC_IRQ_WDOG_BARK,              //Generated when BARK watchdog timer expires 
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
  PM_SCPQ_MISC_BARK,
  PM_SCPQ_MISC_BITE,
  PM_SCPQ_MISC_BARK_BITE_INVALID,
}pm_scpq_misc_wdog_status;

typedef struct {
  boolean wdog_timer_en;                  //Watchdog time enable/disable, bit0
  boolean wdog_timer_en_on_plugin;        //All three watchdog timers enable/disable during plugin, bit1
  boolean bark_wdog_int_en;               //BARK watchdog timer expire interrupt enable/disable, bit4
  boolean bite_wdog_int_en;               //BITE watchdog timre expire interrupt enable/disable, bit5
  boolean bite_wdog_disable_charging_cfg; //Controls charging enable/disable after Bite wd timer expires, bit7 
}pm_scpq_misc_wdog_cfg_type;

typedef enum {
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_62P5MS,
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_125MS,
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_250MS,
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_500MS,
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_1S,
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_2S,
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_4S,
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_8S,
  PM_SCPQ_MISC_SNARL_WDOG_TMOUT_INVALID, //Invalid
}pm_scpq_misc_snarl_wdog_timeout; 

typedef enum {
  PM_SCPQ_MISC_BARK_WDOG_TMOUT_16S,
  PM_SCPQ_MISC_BARK_WDOG_TMOUT_32S,
  PM_SCPQ_MISC_BARK_WDOG_TMOUT_64S,
  PM_SCPQ_MISC_BARK_WDOG_TMOUT_128S,
  PM_SCPQ_MISC_BARK_WDOG_TMOUT_INVALID, //Invalid
}pm_scpq_misc_bark_wdog_timeout;

typedef enum {
  PM_SCPQ_MISC_BITE_WDOG_TMOUT_1S,
  PM_SCPQ_MISC_BITE_WDOG_TMOUT_2S,
  PM_SCPQ_MISC_BITE_WDOG_TMOUT_4S,
  PM_SCPQ_MISC_BITE_WDOG_TMOUT_8S,
  PM_SCPQ_MISC_BITE_WDOG_TMOUT_INVALID, //Invalid
}pm_scpq_misc_bite_wdog_timeout;

typedef struct {
  pm_scpq_misc_snarl_wdog_timeout snarl_wdog_timeout; // Snarl watchdog Timeout
  pm_scpq_misc_bark_wdog_timeout  bark_wdog_timeout;  // Bark watchdog Timeout
  pm_scpq_misc_bite_wdog_timeout  bite_wdog_timeout;  // Bite watchdog Timeout 
}pm_scpq_misc_wd_time_sel;

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
  PM_SCPQ_MISC_THERMREG_CONNECTOR_ADC_SRC_EN,
  PM_SCPQ_MISC_THERMREG_SMB_ADC_SRC_EN,
  PM_SCPQ_MISC_THERM_SRC_CFG_RESERVED,  //Reserved bit 4
  PM_SCPQ_MISC_DIE_ADC_SRC_EN,
  PM_SCPQ_MISC_DIE_CMP_SRC_EN,
  PM_SCPQ_MISC_THERMREG_SW_ICL_ADJUST,  //only software thermal regulation allowed
  PM_SCPQ_MISC_THERM_SRC_CFG_INVALID,
}pm_scpq_misc_therm_src_cfg_type;

typedef enum
{
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_ENG_CFLY_REF_CURRENT_SEL,            // 0 = Use schg untrimmed 1uA current as current source, 1 = Use MBG-mirrored
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_SEL_SMB_ITEMP,                       // 0 = Take smb temp sense as voltage input, 1 = Take as current input
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_CFG_EN_BATT_DIFFSENSE,               // 0 = Disable battery differential sensing, 1 = Enable
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_DIS_CBAL_WEAK_PULLDOWN,              // 0 = Enable Cbal weak pulldown (1kohm) in power-off mode, 1 = Disable
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_ENG_EN_CBAL_CYCLE_BY_CYCLE_DIV2,     // 0 = Disable cbal cycle-by-cycle balancing in DIV2 mode, 1 = Enable
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_ENG_EN_CBAL_BANG_BANG_SKIP_MODE,     // 0 = Disable CBAL bang-bang auto-balance during skipmode, 1 = Enable
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_ENG_SEL_CFLY_DIFFSNS_FOR_HARD_FAULT, // 0 = Use traditional single-end Cfly sense for hard fault detection, 1 = Use differential Cfly sense
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_ENG_SELECT_HVOV_VTH,                 // 0 = Lower HVOV range (14.5V or MVOV (above 17V)), 1 = Higher HVOV range (19.5V or 22V)
  PM_SCPQ_MISC_ENG_SDCDC_SPARE_CFG_INVALID
}pm_scpq_misc_eng_sdcdc_spare_cfg_type;

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
 * @brief This function returns When bark/bite watchdog interrupt trips
 * 
 * @details
 *  This function returns returns When bark/bite watchdog interrupt trips,
 *  this status bit can be used to determine which of the two wdog timer expired.
 * 
 * @param[in] pmic_index:      The pmic_index of charger module.
 * @param[out] misc_wdog_sts:  Refer pm_scpq_misc_wdog_status for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_get_misc_wdog_status(uint32 pmic_index, pm_scpq_misc_wdog_status *misc_wdog_sts);


/**
 * @brief Writing to this register will pet (reset) BARK and BITE watchdog timers 
 * 
 * @details
 *  Writing to this register will pet (reset) BARK and BITE watchdog timers 
 * 
 * @param[in] pmic_index:  The pmic_index of charger module.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_bark_bite_wdog_pet(uint32 pmic_index);


/**
 * @brief This function configures the charger watchdog
 * 
 * @details
 *  This function configures the charger watchdog
 * 
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[in] misc_wd_cfg:  Refer #pm_scpq_misc_wdog_cfg_type for details.
 *                                
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_config_wdog(uint32 pmic_index, pm_scpq_misc_wdog_cfg_type misc_wd_cfg);

/**
 * @brief This function gets configures the charger watchdog 
 * 
 * @details
 *  This function gets configures the charger watchdog 
 * 
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[out] misc_wd_cfg:  Refer #pm_scpq_misc_wdog_cfg_type for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_get_config_wdog(uint32 pmic_index, pm_scpq_misc_wdog_cfg_type *misc_wd_cfg);


/**
 * @brief This API configures the charger snarl bark bite watchdog timer selection
 * 
 * @details
 *  his API configures the charger snarl bark bite watchdog timer selection
 * 
 * @param[in] pmic_index:       The pmic_index of charger module.
 * @param[in] misc_wd_sbb_cfg:  Refer #pm_scpq_misc_wd_time_sel for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_set_wd_time_sel(uint32 pmic_index, pm_scpq_misc_wd_time_sel misc_wd_time_sel);


/**
 * @brief This function gets the charger snarl bark bite watchdog timer selection
 * 
 * @details
 *  This function gets the charger snarl bark bite watchdog timer selection
 * 
 * @param[in] pmic_index:        The pmic_index of charger module.
 * @param[out] misc_wd_sbb_cfg:  Refer #pm_scpq_misc_wd_time_sel for details.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_get_wd_time_sel(uint32 pmic_index, pm_scpq_misc_wd_time_sel *misc_wd_time_sel);

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
 * @param[in] data:               Channel id.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_scpq_misc_set_batt_therm_ch_id_cfg(uint32 pmic_index, uint8 channel_id);

/**
 * @brief This API sets the bit of misc eng sdcdc spare register
 *
 * @details
 *  This API sets the bit of misc eng sdcdc spare register
 *
 * @param[in] pmic_index:         The pmic_index of charger module.
 * @param[in] sdcdc_cfg:          Refer #pm_scpq_misc_eng_sdcdc_spare_cfg_type for details.
 * @param[in] set_value:          Set config bit or not.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_misc_set_eng_sdcdc_spare_cfg(uint32 pmic_index, pm_scpq_misc_eng_sdcdc_spare_cfg_type sdcdc_cfg, boolean set_value);

#endif /* __PM_SCPQ_MISC_H__*/

