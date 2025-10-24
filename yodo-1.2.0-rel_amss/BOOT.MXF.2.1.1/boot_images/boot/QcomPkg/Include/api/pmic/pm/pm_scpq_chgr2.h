#ifndef __PM_SCPQ_CHGR2_H__
#define __PM_SCPQ_CHGR2_H__

/*! \file
 *  \n
 *  \brief  pm_scpq_chgr2.h PMIC-SCPQ MODULE RELATED DECLARATION
 *  \details  This header file contains functions and variable declarations
 *  to support Qualcomm PMIC SCPQ (Switch-Mode Battery Charger) module. The
 *  Switched-Mode Battery Charger (SCPQ) module includes a buck regulated
 *  battery charger with integrated switches. The SCPQ module, along with the
 *  Over Voltage Proection (OVP) module will majorly be used by charger
 *  appliation for charging Li-Ion batteries with high current.
 *  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE


when        who    what, where, why
--------    ---    ----------------------------------------------------------
14/01/22    xp     Initial revision
========================================================================== */

/*===========================================================================

                        INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/






/*===========================================================================

                        SCPQ DRIVER FUNCTION PROTOTYPES

===========================================================================*/



/**
* @brief This function gets the battery type of 1S or 2S
*        In PBS OTP, we read MFG_ID_SPARE (0x1FF), AND it with 0xC0 to determine if the PMIC is 2S or 1S PMIC.
*        Then the OTP writes to one time write register BAT_2S_CHARGE_CFG (0x26A0).
*
* @param[in] pmic_device:  The pmic_index of charger module.
* @param[in] is_2s_bat:    0 : it's 1S Battery Charging config
*                          1 : it's 2S Battery Charging config
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*          version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*/
pm_err_flag_type
pm_scpq_chgr2_get_bat_2s_chg_cfg(uint32 pmic_index, boolean* is_2s_bat);

#endif /*__PM_SCPQ_CHGR2_H__ */

