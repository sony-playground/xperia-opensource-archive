/**
 * @file ddi_test_list.c
 * @brief
 * DDI test list.
 */
/*=============================================================================

                                DDI Test cases
                                Source File
GENERAL DESCRIPTION
This file defines the DDI test cases available

  Copyright (c) 2016-2017,2020-2021 QUALCOMM Technologies Incorporated.
  All rights reserved.
  Qualcomm Confidential and Proprietary.
===============================================================================

===============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

===============================================================================
when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/19/17   na      Initial version
==============================================================================*/

/*==============================================================================
                                  INCLUDES
==============================================================================*/

#include "ddi_testing.h"
#include "ddi_test_cases.h"

/*==============================================================================
                                  DATA
==============================================================================*/

ddi_test_case_func test_case_list[] = {
    {DDI_FACTORY_GROUP | DDI_MEMTEST_GROUP, ddi_run_command_rd},
    {DDI_FACTORY_GROUP | DDI_MEMTEST_GROUP, ddi_run_command_wr},
    {DDI_FACTORY_GROUP | DDI_MEMTEST_GROUP, ddi_run_command_rdwr},
    {DDI_FACTORY_GROUP | DDI_MEMTEST_GROUP | DDI_POST_DDR_GROUP, ddi_run_command_delay},
    {DDI_FACTORY_GROUP | DDI_MEMTEST_GROUP | DDI_POST_DDR_GROUP, ddi_run_command_freq},
    {0, ddi_run_command_empty},
    {DDI_POST_DDR_GROUP, ddi_run_command_plot},
    {0, ddi_run_command_empty},
    {DDI_PRE_DDR_GROUP, ddi_get_device_info},
    {DDI_PRE_DDR_GROUP, ddi_read_ecdt_parameters},
    {DDI_PRE_DDR_GROUP, ddi_get_ac_timing},
    {DDI_PRE_DDR_GROUP, ddi_get_safe_mode_info},
    {DDI_POST_DDR_GROUP, ddi_read_mr},
    {0, ddi_run_command_empty},
};

uint8 ddi_number_of_cmds = sizeof(test_case_list)/sizeof(test_case_list[0]);