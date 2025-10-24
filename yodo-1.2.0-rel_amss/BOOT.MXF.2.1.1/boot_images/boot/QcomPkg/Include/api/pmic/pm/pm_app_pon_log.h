#ifndef __PM_APP_PON_LOG_H__
#define __PM_APP_PON_LOG_H__

/*! \file  pm_app_pon.h 
*  \n
*  \brief   PMIC-PON MODULE RELATED DECLARATION
*  \details  This file contains functions prototypes and variable/type/constant
*  declarations for supporting PON motor driver for the Qualcomm PMIC 
*  chip set.
*
*
*  \n &copy; Copyright 2022 QUALCOMM Technologies Inc, All Rights Reserved
*/

/* =======================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------

========================================================================== */

/*===========================================================================
                INCLUDE FILES FOR MODULE
===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"

/*=============================================================================
                    LOCAL VARIABLE DEFINITIONS
=============================================================================*/


/*===========================================================================

                 PON DRIVER FUNCTION DEFINITIONS

===========================================================================*/

#define PON_EVENT_DUMP_FILE_SIZE 64

typedef struct
{
  uint32 signature;
  uint16 version;                   /* Starts from 1 and increments if we add more data */
  uint16 size;
  uint32 pon_rsn_hist_data[PON_EVENT_DUMP_FILE_SIZE];       /* PON Reasons data   */
} pm_pon_reason_events_data_type;

pm_err_flag_type 
pm_app_pon_get_all_pon_events(pm_pon_reason_events_data_type *pon_reason_events_ptr );

#endif  //__PM_APP_PON_H__

