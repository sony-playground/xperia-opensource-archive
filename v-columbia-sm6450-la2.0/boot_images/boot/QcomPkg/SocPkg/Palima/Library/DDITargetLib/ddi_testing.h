/** 
  @file  ddi_testing.h
  @brief defines command DDI test parameters
*/
/*=============================================================================

                                DDI Internal Test cases APIs
                                Header File
GENERAL DESCRIPTION
This file defines common DDI test parameters

  Copyright (c) 2016-2017,2020-2021 QUALCOMM Technologies Incorporated.
  All rights reserved.
  Qualcomm Confidential and Proprietary.
===============================================================================

===============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

when       who     what, where, why
--------   ---     ------------------------------------------------------------
07/19/17   na      Initial version.
==============================================================================*/
#ifndef __DDI_TESTING_H__
#define __DDI_TESTING_H__

/*==========================================================================
                               INCLUDES
===========================================================================*/

#include "HALcomdef.h"
#include "ddi_drivers.h"
#include "ddi_flash_params.h"

/*==============================================================================
                                  TYPES & DEFINES
==============================================================================*/

#define DDI_PRINT_ENABLE 1
#define DDI_OUTPUT_SECTION_START_IN_DDR		SIZE_320KB
#define DDI_OUTPUT_SECTION_END_IN_DDR       SIZE_1MB

#define TEST_REPORT_STRING(v) \
  ((v&DDI_CMD_INVALID_INPUT)?"INVALID": \
  ((v&DDI_CMD_FAIL)?"FAIL": \
  ((v&DDI_CMD_COMPLETE)?"PASS": \
  ((v==DDI_CMD_NOT_COMPLETE)?"NOTRUN":"UNKNOWN"))))

/*==========================================================================
                               FUNCTION DEFINITIONS
===========================================================================*/

typedef ddi_error (*test_case_func)(uint64 cmd_id, void* params, uint64* output_iter);
typedef int (*peg_frequency)(void);

typedef enum
{
  DDR_DDI_SUCCESS,
  DDR_DDI_FAIL,
  DDR_DDI_CONTINUE,
  DDR_DDI_INVALID,
}ddr_ddi_result_code;

  
typedef struct
{
  ddi_step_param ddi_step;
  test_case_func func_ptr;
}ddi_test_case_func;

#endif /* __DDI_TESTING_H__ */
