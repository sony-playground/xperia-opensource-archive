#ifndef __PM_QBG_H__
#define __PM_QBG_H__

/*! \file
*  \n
*  \brief  pm_qbg.h PMIC MODULE RELATED DECLARATION 
*  \details  This header file contains functions and variable declarations 
*  to support Qualcomm qgauge module.
*  \n &copy; Copyright 2020-2021 QUALCOMM Technologies Incorporated, All Rights Reserved.
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who    what, where, why
--------    ---    ---------------------------------------------------------- 
01/22/2020  cs     Initial version. 
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_chg.h"
#include "pm_sdam.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

/*! \enum pm_qbg_irq_bit_field_type
   \brief different types of irq bit fields of by smbb irq module
 */
typedef enum {
   PM_QBG_BATTERY_MISSING_INT_RT_STS,
   PM_QBG_VBAT_EMPTY_INT_RT_STS,
   PM_QBG_DATA_READY_INT_RT_STS,
   PM_QBG_FSM_STAT_CHG_INT_RT_STS,
   PM_QBG_EVENT_INT_RT_STS,
   PM_QBG_IRQ_INVALID
}pm_qbg_irq_type;


typedef struct
{
  boolean                     qg_ok;
  boolean                     battery_present;  
  boolean                     adc_conv_fault_occured;
  boolean                     data_reset;  
}pm_qbg_status_type;

typedef enum
{
  PM_QBG_FSM_DISABLED,
  PM_QBG_FSM_PON_OCV,
  PM_QBG_FSM_QBG_OK,
  PM_QBG_FSM_LPM,
  PM_QBG_FSM_MPM,
  PM_QBG_FSM_HPM,
  PM_QBG_FSM_FAST_CHAR,
  PM_QBG_FSM_INVALID
}pm_qbg_fsm_staus_type;

typedef enum
{
  PM_QBG_ACC0,
  PM_QBG_ACC1,
  PM_QBG_ACC2,
  PM_QBG_ACC3,
  PM_QBG_ACC_INVALID,
} pm_qbg_acc_index_type;

typedef enum
{
  PM_QBG_CAL_METHOD_NO_CAL,
  PM_QBG_CAL_METHOD_RATIO_CAL,
  PM_QBG_CAL_METHOD_ABS_CAL,
  PM_QBG_CAL_METHOD_INVALID,
} pm_qbg_cal_method;

typedef struct
{
  uint32 pmic_index;
  pm_sdam_type sdam_index;
  uint8 mem_index;
} pm_qbg_ext_rsns_scale_loc_type;

/*===========================================================================

                        SCHG DRIVER FUNCTION PROTOTYPES

===========================================================================*/


/**
* @brief This function enables irq
*
* @details
*  This function enables irq
*
* @param[in] pmic_device_index.  Primary: 0 Secondary: 1
* @param[in] irq                 pm_qbg_irq_type
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*          version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_qbb_irq_enable(uint32 device_index, pm_qbg_irq_type irq, boolean enable);


/**
* @brief This function clears the qbg irq
*
* @details
*  This function clears the qbg irq
*
* @param[in] pmic_device_index.  Primary: 0 Secondary: 1
* @param[in] irq                 pm_qgauge_irq_type
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*          version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_qbg_irq_clear(uint32  device_index, pm_qbg_irq_type irq);


/**
* @brief This function configures the qbg irq trigger
*
* @details
*  This function configures the qbg irq trigger
*
* @param[in] pmic_device_index.  Primary: 0 Secondary: 1
* @param[in] irq                 pm_qgauge_irq_type
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*          version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/

pm_err_flag_type pm_qbg_irq_set_trigger(uint32 device_index, pm_qbg_irq_type irq, pm_irq_trigger_type trigger);


/**
* @brief This function configures the QBG for irq
*
* @details
*  This function configures the qbg for irq
*
* @param[in] pmic_device_index.  Primary: 0 Secondary: 1
* @param[in] irq                 pm_qbg_irq_type
*
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*          version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_qbg_irq_status(uint32 device_index, pm_qbg_irq_type irq, pm_irq_status_type type, boolean *status);


/**
* @brief This function provides QBG status info.
*
* @details
*  This function provides QBG PMIC info.
*
* @param[in] pmic_index         On what PMIC Index, QBG resides.
* @param[out] qbg_status      Qgauge info in pm_qbg_status_type.
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_get_status(uint32 device_index, pm_qbg_status_type* qbg_status, pm_qbg_fsm_staus_type* qbg_fsm_state);

/**
* @brief This function sets battery empty threshold.
*
* @details
*  This function provides QBG PMIC info.
*
* @param[in] pmic_index         On what PMIC Index, QBG resides.
* @param[in] vbatEmptyThreshold Battery empty threshold in mV.
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_set_vbat_empty_threshold(uint32 device_index, uint32 vbatEmptyThreshold);


/**
* @brief This function sets qbg MODE_CTL1 for battery options
*
* @details
*  This function sets QBG mode_ctl1 config
*
* @param[in] pmic_index         On what PMIC Index, QBG resides.
* @param[in] battery_type.
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_set_qbg_mode_ctl1_batt_opt(uint32 device_index, pm_chg_battery_type battery_type);

/**
* @brief This function sets qbg MODE_CTL3 for battery options
*
* @details
*  This function sets QBG mode_ctl3 config
*
* @param[in] pmic_index         On what PMIC Index, QBG resides.
* @param[in] option_2s to set if it is 1s or 2s, and vbatt_2s option.
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_set_qbg_mode_ctl3_batt_opt(uint32 device_index, pm_chg_2s_battery_option_type option_2s);


/**
* @brief This function sets qbg MODE_CTL2 for ichg full scale option
*
* @details
*  This function sets QBG mode_ctl2 config
*
* @param[in] pmic_index         On what PMIC Index, QBG resides.
* @param[in] support_20A to set if it support 24A or 12A ibatt.
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_set_qbg_mode_ctl2_ichg_fs_opt(uint32 device_index, BOOLEAN support_24A);


/**
* @brief This function gets qbg MODE_CTL1 for battery options
*
* @details
*  This function gets QBG mode_ctl1 config
*
* @param[in] pmic_index         On what PMIC Index, QBG resides.
* @param[out] battery_type
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_get_qbg_mode_ctl1_batt_opt(uint32 device_index, pm_chg_battery_type* battery_type);

/**
* @brief This function gets qbg MODE_CTL3 for battery options
*
* @details
*  This function gets QBG mode_ctl3 config
*
* @param[in] pmic_index         On what PMIC Index, QBG resides.
* @param[out] p_2s_option
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_get_qbg_mode_ctl3_batt_opt(uint32 device_index, pm_chg_2s_battery_option_type* option_2s);

/**
* @brief This function gets qbg MODE_CTL2 for ichg full scale option
*
* @details
*  This function gets QBG mode_ctl2 config
*
* @param[in] pmic_index         On what PMIC Index, QBG resides.
* @param[out] p_support_24A
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_get_qbg_mode_ctl2_ichg_fs_opt(uint32 device_index, BOOLEAN* p_support_24A);

/**
* @brief This function gets PON OCV acc data0 and data1 according to accumulator index
*
* @param[in] pmic_index: On what PMIC Index, QBG resides.
* @param[in] acc_index: the index of acc.
* @param[out] data: the data0 and data1 of the required accumulator
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_get_pon_ocv_acc_data(uint32 device_index, pm_qbg_acc_index_type acc_index, uint16* data);


/**
* @brief This function gets last burst average acc data0 and data1 according to accumulator index
*
* @param[in] pmic_index: On what PMIC Index, QBG resides.
* @param[in] acc_index: the index of acc.
* @param[out] data: the data0 and data1 of the required accumulator
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_get_last_burst_avg_acc_data(uint32 device_index, pm_qbg_acc_index_type acc_index, uint16* data);


/**
* @brief This function provides QBG PMIC info.
*
* @details
*  This function provides QBG PMIC info.
*
* @param[out] pmic_index         On what PMIC Index, QBG resides.
* @param[out] slave_id           On what SlaveID for given PMIC, Qgauge resides.
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_get_qbg_pmic_info(uint32 *pmic_index, uint8 *slave_id);

/**
* @brief This function configures battery therm calibration method in fast chaging mode and LPM/MPM/HPM state.
*
* @param[in] device_index         On what PMIC Index, QBG resides.
* @param[in] fast_chg_sel        the selection in fast charging state
* @param[in] xpm_sel             the selection in LPM/MPM/HPM state
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available.
*          PM_ERR_FLAG_INVALID_PARAMETER     = Invalid parameters.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type pm_qbg_set_tbat_thermal_calibration_method(uint32 device_index, pm_qbg_cal_method fast_chg_sel, pm_qbg_cal_method xpm_sel);


#endif /* __PM_QBG_H__ */

