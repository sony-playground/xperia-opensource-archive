/*! \file
*
*  \brief  pm_qbg.c driver implementation.
*  \details qguage driver implementation.
*  &copy;
*  Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
*  Qualcomm Technologies Proprietary and Confidential.
*/

/*===========================================================================

                        EDIT HISTORY FOR MODULE


$Header: //components/rel/core.boot/6.0/QcomPkg/Library/PmicLib/drivers/qbg/src/pm_qbg_null.c#1 $
$Author: pwbldsvc $
$DateTime: 2021/12/20 11:02:36 $
when        who    what, where, why
--------    ---    ----------------------------------------------------------
02/21/18    sv     Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "pm_qbg.h"
#include "pm_qbg_driver.h"

/*===========================================================================
                        MACRO DECLARATIONS
===========================================================================*/

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/



pm_err_flag_type pm_qbg_irq_enable(uint32 device_index, pm_qbg_irq_type irq, boolean enable)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_irq_clear(uint32  device_index, pm_qbg_irq_type irq)
{
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_qbg_irq_set_trigger(uint32 device_index, pm_qbg_irq_type irq, pm_irq_trigger_type trigger)
{
  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type pm_qbg_irq_status(uint32 device_index, pm_qbg_irq_type irq, pm_irq_status_type type, boolean *status)
{
  return PM_ERR_FLAG_SUCCESS;
}



pm_err_flag_type pm_qbg_get_status(uint32 device_index, pm_qbg_status_type* qbg_status, pm_qbg_fsm_staus_type* qbg_fsm_state)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_get_pon_ocv_acc_data(uint32 device_index, pm_qbg_acc_index_type acc_index, uint16* data)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_get_last_burst_avg_acc_data(uint32 device_index, pm_qbg_acc_index_type acc_index, uint16* data)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_set_vbat_empty_threshold(uint32 device_index, uint32 vbatEmptyThreshold)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_set_qbg_mode_ctl1_batt_opt(uint32 device_index, BOOLEAN is_1s_battery, pm_chg_2s_battery_option_type option_2s)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_set_qbg_mode_ctl2_ichg_fs_opt(uint32 device_index, BOOLEAN support_20A)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_get_qbg_mode_ctl1_batt_opt(uint32 device_index, BOOLEAN* p_is_1s_battery, pm_chg_2s_battery_option_type* p_2s_option)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_get_qbg_mode_ctl2_ichg_fs_opt(uint32 device_index, BOOLEAN* p_support_20A)
{
  return PM_ERR_FLAG_SUCCESS;
}

pm_err_flag_type pm_qbg_set_tbat_thermal_calibration_method(uint32 device_index, pm_qbg_cal_method fast_chg_sel, pm_qbg_cal_method xpm_sel)
{
  return PM_ERR_FLAG_SUCCESS;
}

