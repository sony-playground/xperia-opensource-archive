/*===========================================================================

                  BOOT SAHARA COMMAND HANDLER TABLE DEFINITIONS

DESCRIPTION
  Contains wrapper definition for populating sahara command handler table

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2020-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who      what, where, why
--------    ---      ----------------------------------------------------------
08/12/21    ck       Initial revision

===========================================================================*/

#include "boot_error_if.h"


bl_error_boot_type boot_read_serial_number(uint32* serial_num)
{
  return BL_ERR_NONE;
}


bl_error_boot_type boot_get_ddr_training(uint32 * tr_data_size,
                                         uint8 ** ddr_training_data_ptr)
{
  return BL_ERR_NONE;
}


bl_error_boot_type boot_force_reset(void)
{
  return BL_ERR_NONE;
}


bl_error_boot_type boot_sahara_command_handler_table_get_interface(void * sahara_cmd_handler_if)
{
  return BL_ERR_NONE;
}
