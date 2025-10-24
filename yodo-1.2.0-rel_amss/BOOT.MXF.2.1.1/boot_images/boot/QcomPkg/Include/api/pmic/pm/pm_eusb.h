#ifndef __PM_EUSB_H__
#define __PM_EUSB_H__

/*! \file  pm_eusb.h
 *  \n
 *  \brief  PMIC-EUSB MODULE RELATED DECLARATION
 *  \details  This file contains functions and variable declarations to support
 *   the PMIC EUSB module.
 *
 *  \n &copy; Copyright (c) 2022 QUALCOMM Technologies Incorporated. All Rights Reserved.
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/pmic/pm/pm_eusb.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/06/22   akm     Implement EUSB driver
===========================================================================*/

/*===========================================================================
                INCLUDE FILES FOR MODULE
===========================================================================*/
#include "pm_err_flags.h"
#include "com_dtypes.h"

/*=============================================================================
                    LOCAL VARIABLE DEFINITIONS
=============================================================================*/



/*===========================================================================
                          FUNCTION DEFINITIONS
===========================================================================*/


/**
 * @brief This function enable/disable EUSB functionality
 *
 * @param[in]  pmic_index:
 *               0 for primary pmic
 *               1 for secondary pmic
 * @param[in] enable:
 *               enable or disable
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *          version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 * DEPENDENCY: pm_driver_init() must be called in advance
 */
pm_err_flag_type 
pm_eusb_enable (uint32 pmic_index, boolean enable);

#endif

