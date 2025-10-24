/**
 * @file DDITargetLibNull.c
 */
/*=============================================================================

                                DDI Null
                                Source File

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.
  All rights reserved.
===============================================================================

===============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

===============================================================================
when       who     what, where, why
--------   ---     ------------------------------------------------------------
08/12/21   ck      Initial version
==============================================================================*/

#include "ddi_drivers.h"


ddi_mode_code ddi_get_mode(void)
{
  return DDI_NOOP_MODE;
}


void ddi_pre_entry(void)
{
}


ddi_exit_code ddi_entry(ddi_result_code *ddi_test_result_code )
{
  return DDI_EXIT_HLOS;
}


void ddi_set_param(void)
{
}
