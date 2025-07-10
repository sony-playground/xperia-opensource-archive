#ifndef __PM_SCHG_BOB_H__
#define __PM_SCHG_BOB_H__

/*! \file
*  \n
*  \brief  pm_schg_bob.h PMIC-SCHG MODULE RELATED DECLARATION
*  \details  This header file contains functions and variable declarations
*  to support Qualcomm PMIC SCHG (Switch-Mode Battery Charger) module. The
*  Switched-Mode Battery Charger (SCHG) module includes a buck regulated
*  battery charger with integrated switches. The SCHG module, along with the
*  Over Voltage Proection (OVP) module will majorly be used by charger
*  appliation for charging Li-Ion batteries with high current (up to 2A).
*  \n &copy; Copyright 2017-2021 QUALCOMM Technologies Inc, All Rights Reserved
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who    what, where, why
--------    ---    ----------------------------------------------------------
06/20/18    cs     Initial version.
========================================================================== */
#include "com_dtypes.h"
#include "pm_err_flags.h"

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

/*===========================================================================

                 SCHG DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/**
* @brief This function returns if this charging port is active
*
* @param[in] pmic_index:  The pmic_index of charger module.
* @param[out]  isActive:  1 the port is active, 0, port not active.
*
* @return  pm_err_flag_type
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_bob_is_port_active(uint32 pmic_index, boolean *is_active);

#endif /* __PM_SCHG_BOB_H__ */

