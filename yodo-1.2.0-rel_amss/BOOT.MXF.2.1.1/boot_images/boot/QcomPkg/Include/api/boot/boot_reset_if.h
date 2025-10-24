#ifndef BOOT_RESET_IF_H
#define BOOT_RESET_IF_H

/*=============================================================================

                         SBL1 Hardware Initialization

GENERAL DESCRIPTION
  This file does basic hardware initialization at power up.

Copyright 2020-2021 by Qualcomm Technologies Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/boot/boot_reset_if.h#1 $

when       who       what, where, why
--------   ---       ----------------------------------------------------------
07/23/21   rama      Added custom error code for reset_if
07/08/21   ck        Updated all function return types
01/19/21   rama      Removed jtag_term_putc
03/18/20   rama      Removed boot_msm.h
02/14/20   rama      Initial revision
=============================================================================*/

/*=============================================================================

                            INCLUDE FILES FOR MODULE

=============================================================================*/
#include "boot_comdef.h"
#include "boot_error_if.h"


/**
 * Max number of retries before giving up to output to jtag terminal
 */
#define JTAG_TERM_MAX_NUM_RETRY  5

/**
 * Time out value for outputing a single char to jtag terminal
 */
#define JTAG_TERM_TIME_OUT       0x10000


typedef enum
{
  BOOT_HARD_RESET_TYPE = 0,
  BOOT_WARM_RESET_TYPE = 1,
  BOOT_DVDD_HARD_RESET_TYPE = 2,
  BOOT_APQ_COLD_DEBUG_RESET = 3
} boot_hw_reset_type;

typedef enum
{
  BL_ERR_HW_RESET_FAILURE = BL_ERR_CUSTOM_ERRORS_START,
  BL_ERR_HW_POWERDOWN_FAILURE,
  BL_ERR_PWRKEY_RESET_FAILURE,
  BL_ERR_PSHOLD_RESET_FAILURE
}bl_error_boot_reset_type;

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

typedef struct boot_reset_if_type
{
  bl_error_boot_type (*hw_reset)(boot_hw_reset_type reset_type);
  bl_error_boot_type (*hw_powerdown)(void);
  bl_error_boot_type (*set_pwrkey_reset_type)(boot_hw_reset_type reset_type);
  bl_error_boot_type (*set_pshold_reset_type)(boot_hw_reset_type reset_type);
} boot_reset_if_type;


extern boot_reset_if_type reset_if;

bl_error_boot_type boot_hw_powerdown( void );
bl_error_boot_type boot_hw_reset(boot_hw_reset_type reset_type);
bl_error_boot_type boot_set_pshold_reset_type(boot_hw_reset_type reset_type);
bl_error_boot_type boot_set_pwrkey_reset_type(boot_hw_reset_type reset_type);


#endif /* BOOT_RESET_IF_H */
