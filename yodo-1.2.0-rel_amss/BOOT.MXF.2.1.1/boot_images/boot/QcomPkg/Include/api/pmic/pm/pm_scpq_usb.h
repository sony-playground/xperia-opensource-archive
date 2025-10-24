#ifndef __PM_SCPQ_USB_H__
#define __PM_SCPQ_USB_H__

/*! \file
 *  \n
 *  \brief  pm_scpq_usb.h PMIC-SCPQ MODULE RELATED DECLARATION
 *  \details  This header file contains functions and variable declarations
 *  to support Qualcomm PMIC SCPQ (Switch-Mode Battery Charger) module. The
 *  Switched-Mode Battery Charger (SCPQ) module includes a buck regulated
 *  battery charger with integrated switches. The SCPQ module, along with the
 *  Over Voltage Proection (OVP) module will majorly be used by charger
 *  appliation for charging Li-Ion batteries with high current (up to 2A).
 *  \n &copy; Copyright 2020-2022 QUALCOMM Technologies Inc, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
12/02/19    zzx    Initial revision
========================================================================== */
#include "pm_chg.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/


/*! \enum pm_scpq_usb_irq_bit_field_type
   \brief different types of irq bit fields of by smbb irq module
 */
typedef enum
{
  PM_SCPQ_USB_IRQ_USBIN_PLUGIN,         //USBIN plugged in, goes low on un-plug
  PM_SCPQ_USB_IRQ_USBIN_COLLAPSE,       //The USBIN voltage has crossed the collapse threshold
  PM_SCPQ_USB_IRQ_USBIN_UV,             //The USBIN voltage has crossed the under-voltage threshold
  PM_SCPQ_USB_IRQ_USBIN_OV,             //The USBIN voltage has crossed the over-voltage threshold
  PM_SCPQ_USB_IRQ_USBIN_GT_VT,          //The USBIN voltage has crossed the auto-shutdown threshold
  PM_SCPQ_USB_IRQ_USBIN_DRV_ON_EN_SET = PM_SCPQ_USB_IRQ_USBIN_GT_VT, //OVP FET turned ON
  PM_SCPQ_USB_IRQ_USBIN_VOOC,           //Change when data fully received, transmitted or fails
  PM_SCPQ_USB_IRQ_USBIN_ICL_CHANGE,     //Change in USBIN input current limit
  PM_SCPQ_USB_IRQ_USBIN_SOURCE_CHANGE,  //Change to APSD, HVDCP, HVDCP authentication status, HVDCP Change Complete
  PM_SCPQ_USB_IRQ_INVALID,              //INVALID
}pm_scpq_usb_irq_type;


typedef enum
{
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_LV = 0,             // 5V UV - 5V OV
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_RESERVED = 1,
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_MV = 2,             // 9V UV - 15V OV
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_LV_OR_MV = 3,       // (5V UV - 5V OV) or (9V UV - 15V OV)
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_HV = 4,             // 12V UV - 20V OV
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_LV_OR_HV = 5,       // (5V UV - 5V OV) or (12V UV - 20V OV)
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_MV_TO_HV = 6,       // 9V UV -20 OV
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_LV_OR_MV_TO_HV = 7, // (5V UV - 5V OV) or (9V UV -20 OV)
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_LV_TO_MV = 8,       // 5V UV - 15V OV
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_LV_TO_HV = 12,      // 5V UV - 20V OV
  PM_SCPQ_USB_USBIN_ADAPTER_ALLOW_INVALID,
}pm_scpq_usb_usbin_adapter_allowance_type;

typedef enum
{
  /*APSD Detection Done*/
  PM_SCPQ_USB_APSD_STATUS_APSD_DTC_STATUS_DONE,
  /*Quick Charge Detection Done*/
  PM_SCPQ_USB_APSD_STATUS_QC_CHARGER,
  /*QC Authentication Algorithm Done*/
  PM_SCPQ_USB_APSD_STATUS_QC_AUTH_DONE_STATUS,
  /*Adaptive Voltage Change Done after Authentication*/
  PM_SCPQ_USB_APSD_STATUS_VADP_CHANGE_DONE_AFTER_AUTH,
  /*SDP Enumeration Done*/
  PM_SCPQ_USB_APSD_STATUS_ENUMERATION_DONE,
  /*Slow Plugin Timeout Expired*/
  PM_SCPQ_USB_APSD_STATUS_SLOW_PLUGIN_TIMEOUT,
  /* HVDCP detection timeout */
  PM_SCPQ_USB_APSD_STATUS_HVDCP_CKECK_TIMEOUT,
  /*invalid*/
  PM_SCPQ_USB_APSD_STATUS_INVALID,
}pm_scpq_usb_apsd_status_type;

typedef enum
{
  PM_SCPQ_USB_ICL_OPTIONS_CFG_USB3P0_SEL, // 0x0: USB_2P0_SEL  0x1 : USB_3P0_SEL
  PM_SCPQ_USB_ICL_OPTIONS_USB51_MODE,     // 0x0: USB_100_MODE 0x1 : USB_500_MODE
  PM_SCPQ_USB_ICL_OPTIONS_USBIN_MODE_CHG, // 0x0: USB_100_OR_500_MODE 0x1 : USB_HIGH_CURRENT_MODE
  PM_SCPQ_USB_ICL_OPTIONS_INVALID
}pm_scpq_usb_icl_options_type;

typedef enum
{
  QC3_30S_QC2_1MIN  = 0x0,
  QC3_30S_QC2_5MIN  = 0x1,
  QC3_1MIN_QC2_1MIN = 0x2,
  QC3_1MIN_QC2_5MIN = 0x3,
  VADP_DECR_NOT_SEt = 0xFF,
}pm_scpq_usb_inov_vadp_decr_timer_type;

typedef enum
{
  PM_SCPQ_USB_VADP_DECR_TIMER_SEL      = 0,
  PM_SCPQ_USB_VADP_DECR_TIMER_EN       = 3,
  PM_SCPQ_USB_TREG_ALLOW_DECERASE      = 5,
  PM_SCPQ_USB_CABLE_R_SEL              = 6,
  PM_SCPQ_USB_ENABLE_AICL_RERUN_QC_INC = 7,
  PM_SCPQ_USB_INOV_CFG_INVALID,
}pm_scpq_usb_inov_cfg_type;

typedef enum
{
  PM_SCPQ_USB_USBIN_SUSPEND  = 0,
  PM_SCPQ_USB_EXT_BST_ON_USB = 4,
  PM_SCPQ_USB_SUSPEND_ON_COLLAPSE_USBIN = 7,
  PM_SCPQ_USB_USB_SUSPEND_INVALID,
}pm_scpq_usb_usb_suspend_type;

typedef enum
{
  USBIN_COLLAPSE_GF_1MS     = 0x0,
  USBIN_COLLAPSE_GF_5MS     = 0x1,
  USBIN_COLLAPSE_GF_30MS    = 0x2,
  USBIN_COLLAPSE_GF_30US    = 0x3,
  USBIN_COLLAPSE_GF_NOT_SET = 0xFF,
}pm_scpq_usb_aicl_collapse_gf_sel_type;

typedef enum
{
  USBIN_AICL_STEP_5MS     = 0x0,
  USBIN_AICL_STEP_10MS    = 0x1,
  USBIN_AICL_STEP_30MS    = 0x2,
  USBIN_AICL_STEP_40MS    = 0x3,
  USBIN_AICL_STEP_NOT_SET = 0xFF,
}pm_scpq_usb_aicl_step_timming_sel_type;

typedef enum
{
  PM_SCPQ_USB_AICL_START_AT_MAX    = 4,
  PM_SCPQ_USB_AICL_HDC_EN          = 5,
  PM_SCPQ_USB_AICL_EXT_BST_EN      = 6,
  PM_SCPQ_USB_AICL_EN              = 7,
  PM_SCPQ_USB_AICL_INVALID
}pm_scpq_usb_aicl_cfg_type;

typedef enum
{
  PM_SCPQ_USB_INPUT_PRIORITY_WLS,
  PM_SCPQ_USB_INPUT_PRIORITY_USB,
  PM_SCPQ_USB_INPUT_PRIORITY_INVALID
}pm_scpq_usb_input_priority_type;


/*===========================================================================

                 SCPQ DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/**
 * @brief This function enables irq
 *
 * @details
 *  This function enables irq
 *
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] irq:         Refer #pm_scpq_usb_irq_type for details.
 * @param[in] enable:      FALSE: 0, TRUE: 1
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_irq_enable(uint32 pmic_index, pm_scpq_usb_irq_type irq, boolean enable);

/**
 * @brief This function clears the SCPQ irq
 *
 * @param[in] pmic_index: The pmic_index of charger module.
 * @param[in] irq:        Refer #pm_scpq_usb_irq_type for details.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_irq_clear(uint32 pmic_index, pm_scpq_usb_irq_type irq);

/**
 * @brief This function configures the SCPQ irq trigger
 *
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] irq:         Refer #pm_scpq_usb_irq_type for details.
 * @param[in] trigger:     Refer #pm_irq_trigger_type for details.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_irq_set_trigger(uint32 pmic_index, pm_scpq_usb_irq_type irq, pm_irq_trigger_type trigger);

/**
 * @brief This function configures the SCPQ for irq
 *
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] irq:         Refer #pm_Smbb_irq_type for details.
 * @param[in] type:        Refer #pm_irq_status_type for details.
 * @param[out] status:     IRQ status.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_irq_status(uint32 pmic_index, pm_scpq_usb_irq_type irq, pm_irq_status_type type, boolean *status);

/**
 * @brief This function sets the USBIN adapter allowance
 *
 * @details
 *  This function sets the USBIN adapter allowance
 *
 * @param[in] pmic_index:       The pmic_index of charger module.
 * @param[in] adptr_allowance   Refer #pm_scpq_usb_usbin_adapter_allowance_type for details.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_set_usbin_adptr_allowance(uint32 pmic_index, pm_scpq_usb_usbin_adapter_allowance_type adptr_allowance);

/**
 * @brief This function reads the USBIN adapter allowance
 *
 * @details
 *  This function reads the USBIN adapter allowance
 *
 * @param[in] pmic_index:        The pmic_index of charger module.
 * @param[out] adptr_allowance:  Refer #pm_scpq_usb_usbin_adapter_allowance_type for details.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_get_usbin_adptr_allowance(uint32 pmic_index, pm_scpq_usb_usbin_adapter_allowance_type *adptr_allowance);

/**
 * @brief This function returns the APSD status
 *
 * @details
 *  This function reads the USBIN adapter allowance
 *
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[in] apsd_status:  Refer #pm_scpq_usb_apsd_status_type for details.
 * @param[out] result:      Returns low or high
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_get_apsd_status(uint32 pmic_index, pm_scpq_usb_apsd_status_type apsd_status, boolean *result);

/**
 * @brief This function returns the USB charger port types
 *
 * @details
 *  This function reads the USBIN adapter allowance
 *
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[out] apsd_result:  Refer #pm_chg_charger_port_type for details. These value could be OR-ed
 *                           0x1  = PM_SCPQ_USB_APSD_RESULT_STATUS_SDP_CHARGER
 *                           0x2  = PM_SCPQ_USB_APSD_RESULT_STATUS_OCP_CHARGER
 *                           0x4  = PM_SCPQ_USB_APSD_RESULT_STATUS_CDP_CHARGER
 *                           0x8  = PM_SCPQ_USB_APSD_RESULT_STATUS_DCP_CHARGER
 *                           0x10 = PM_SCPQ_USB_APSD_RESULT_STATUS_FLOAT_CHARGER
 *                           0x20 = PM_SCPQ_USB_APSD_RESULT_STATUS_QC_2P0
 *                           0x40 = PM_SCPQ_USB_APSD_RESULT_STATUS_QC_3P0
 *                           0x80 = PM_SCPQ_USB_APSD_RESULT_STATUS_ICL_OVERRIDE_LATCH
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_get_apsd_result_status(uint32 pmic_index, pm_chg_charger_port_type *apsd_result);


/**
 * @brief This function configures various pm_scpq_usb_icl_options_type values
 *
 * @details
 *  This function reads the USBIN adapter allowance
 *
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[in] icl_options:  Refer #pm_scpq_usb_icl_options_type for details.
 * @param[in] set_value:    Value to be set.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_configure_usb_icl_options(uint32 pmic_index, pm_scpq_usb_icl_options_type icl_options, boolean set_value);

/**
 * @brief This function sets the USB input current limit
 *
 * @details
 *  This function reads the USBIN adapter allowance
 *
 * @param[in] pmic_index:           The pmic_index of charger module.
 * @param[in] usbin_current_limit:  USB current to configure. Limits are 0 to 5000mAmp.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_set_icl_cfg(uint32 pmic_index, uint32 usbin_current_limit);

/**
 * @brief This function configures APSD cfg
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
pm_scpq_usb_rerun_apsd(uint32 pmic_index);

/**
 * @brief This function configures usbin INOV cfg
 *
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] inov_cfg:    usbin inov cfg
 * @param[in] enable:      enable/disable given parameter
 * @param[in] timer_sel:   [optional]Adaptive charging algorithm voltage decrement timer setting
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_set_inov_cfg(uint32 pmic_device, pm_scpq_usb_inov_cfg_type inov_cfg, boolean enable,
                                          pm_scpq_usb_inov_vadp_decr_timer_type timer_sel);

/**
 * @brief This function return usbin option1 configuration
 *
 * @param[in]  pmic_index:  The pmic_index of charger module.
 * @param[in]  usbin_cfg:   usbin cfg
 * @param[out] enable:      TRUE: configuration Enable, FALSE: Configuration Disable
 * @param[out] timer_sel:   pm_scpq_usb_inov_vadp_decr_timer_type selection
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_get_inov_cfg(uint32 pmic_device, pm_scpq_usb_inov_cfg_type inov_cfg, boolean *enable,
                                          pm_scpq_usb_inov_vadp_decr_timer_type *timer_sel);

/**
 * @brief This function writes to USB_SUSPEND
 *
 * @param[in] pmic_index:       The pmic_index of charger module.
 * @param[in] usb_suspend_cfg:  Refer #pm_scpq_usb_usb_suspend_type for details.
 * @param[in] set_value:        Values to be set
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_set_usbin_suspend(uint32 pmic_index, pm_scpq_usb_usb_suspend_type usb_suspend_cfg, boolean set_value);

/* @brief This function sets AICL options configuration
 *
 * @param[in]  pmic_index:        The pmic_index of charger module.
 * @param[in]  aicl_cfg_type:     AICL option config type. Refer #pm_scpq_usb_aicl_cfg_type for details.
 * @param[in]  enable:            TRUE: Enable, FALSE: Disable
 * @param[in]  collapse_gf_sel:   pm_scpq_usb_aicl_collapse_gf_sel_type selection
 * @param[in]  step_timming_sel:  pm_scpq_usb_aicl_step_timming_sel_type selection
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_aicl_options_cfg(uint32 pmic_index, pm_scpq_usb_aicl_cfg_type aicl_cfg_type, boolean enable,
                                              pm_scpq_usb_aicl_collapse_gf_sel_type collapse_gf_sel,
                                              pm_scpq_usb_aicl_step_timming_sel_type step_timming_sel);

/**
 * @brief This function enabled ICL Override after APSD.
 *
 * @param[in]  pmic_index:  The pmic_index of charger module.
 * @param[in]  enable:      TRUE  = Use SW to control Input Current Limit after APSD is completed
 *                          FALSE = Use APSD results to control Input Current Limit after APSD is completed
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_usb_enable_icl_override_after_apsd(uint32 pmic_index, boolean enable);


/**
 * @brief This function choose the input priority between USB and wireless.
 *
 * @param[in]  pmic_index:  The pmic_index of charger module.
 * @param[in]  priority:    PM_SCPQ_USB_INPUT_PRIORITY_USB -- USB input has the priority
 *                          PM_SCPQ_USB_INPUT_PRIORITY_WLS -- Wireless input has the priority
 *                          other -- invalid input
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type 
pm_scpq_usb_set_input_priority(uint32 pmic_index, pm_scpq_usb_input_priority_type priority);


#endif /* __PM_SCPQ_USB_H__ */

