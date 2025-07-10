#ifndef __PM_EXT_I2C_CHARGER_H__
#define __PM_EXT_I2C_CHARGER_H__
 /*! @file pm_ext_i2c_charger.h
 *
 * Provide limit support for 3rd party external charger via I2C interface
 *
 * Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved. 
 * Qualcomm Technologies Proprietary and Confidential.
 */

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------------------------------------------------------------------------------------
 01/07/22   pxm     Creation
=============================================================================*/

#include "pm_err_flags.h"

pm_err_flag_type
pm_ext_i2c_charger_rerun_apsd(void);

#endif // __PM_EXT_I2C_CHARGER_H__
