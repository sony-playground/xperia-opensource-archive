#ifndef __PM_SCPQ_WLS_H__
#define __PM_SCPQ_WLS_H__

/*! \file
 *  \n
 *  \brief  pm_scpq_dc.h PMIC-SCPQ MODULE RELATED DECLARATION
 *  \details  This header file contains functions and variable declarations
 *  to support Qualcomm PMIC SCPQ (Switch-Mode Battery Charger) module. The
 *  Switched-Mode Battery Charger (SCPQ) module includes a buck regulated
 *  battery charger with integrated switches. The SCPQ module, along with the
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


/*! \enum pm_scpq_usb_chgpth_irq_bit_field_type
   \brief different types of irq bit fields of by smbb irq module
*/
typedef enum {
  PM_SCPQ_WLS_IRQ_DCIN_PLUGIN,  //High when WLS_IN plugged in, goes low on un-plug
  PM_SCPQ_WLS_COLLAPSE,         //High when WLS_IN below AICL collapse threshold, Low when it's above
  PM_SCPQ_WLS_IRQ_DCIN_UV,      //High when WLS_IN below UVLO threshold, Low when it's above
  PM_SCPQ_WLS_IRQ_DCIN_OV,      //High when WLS_IN above OVLO threshold, Low when it's below
  PM_SCPQ_WLS_GT_VT,            //High when WSL_IN above LT_VT threshold, Low when it's below
  PM_SCPQ_WLS_DRV_ON_EN = PM_SCPQ_WLS_GT_VT,
  PM_SCPQ_WLS_5,                //Reserved
  PM_SCPQ_WLS_ICL_CHANGE,       //Change in WLS_IN input current limit
  PM_SCPQ_WLS_IRQ_INVALID,      //Invalid
}pm_scpq_wls_irq_type;


typedef enum
{
  PM_SCPQ_WLS_SUSPEND_WLS_SUSPEND = 0,  //WLS_IN Suspend: 0 = not suspend 1 = suspend
  PM_SCPQ_WLS_SUSPEND_EXT_BST     = 4,  //1 = External Boost enable, 0 = Disable
  PM_SCPQ_WLS_SUSPEND_ON_COLLAPSE = 7,  //1 = WLS suspends on AICL reduces to ICL_MIN
  PM_SCPQ_WLS_SUSPEND_INVALID           //Invalid
}pm_scpq_wls_suspend_type;


/*===========================================================================

                        SCPQ DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/**
 * @brief This function configures the SCPQ for irq
 *
 * @param[in] pmic_index: The pmic_index of charger module.
 * @param[in] irq:
 *                SCPQ irq type. Refer enum pm_Smbb_irq_type.
 * @param[in] type:
 *                Type of IRQ status to read. Refer enum pm_irq_status_type
 *                from pm_uefi_irq.h for more details
 * @param[out] status:
 *                IRQ status.
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_wls_irq_status(uint32 pmic_index, pm_scpq_wls_irq_type irq, pm_irq_status_type type, boolean *status);

/**
 * @brief This function sets the DCIN current limit
 *
 * @details
 *  This function configure the WLS Input Current Limit(ICL) value
 *
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[in] current_limit  WLS current to configure. Limits are 0 to 3000mAmp
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_wls_icl_cfg(uint32 pmic_index, uint32 current_limit);

/**
 * @brief This function writes to SCPQ_P_WLS_WLS_SUSPEND
 *
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] set_type:    Refer #pm_scpq_wls_suspend_type for details.
 * @param[in] set_value:   values to be set
 *
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type
pm_scpq_wls_set_suspend(uint32 pmic_index, pm_scpq_wls_suspend_type set_type, boolean set_value);


#endif /* __PM_SCPQ_WLS_H__ */

