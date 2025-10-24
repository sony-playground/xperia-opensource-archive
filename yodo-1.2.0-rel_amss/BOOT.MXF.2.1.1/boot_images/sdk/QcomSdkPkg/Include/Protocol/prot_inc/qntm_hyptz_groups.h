/** 
  @file  qntm_hyptz_groups.h
  @brief Quantum Hyp and Tz protocol shared structure interface.
*/
/*=============================================================================
  Copyright (c) 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who       what, where, why
 --------   ---       -----------------------------------------------------------
 01/05/22   avm       Initial version
=============================================================================*/

#ifndef _QNTM_HYPTZ_GROUPS_H_
#define _QNTM_HYPTZ_GROUPS_H_

#define HYP_TESTS_OWNER_ARCH    0x0    // TEST_GROUP_ID used by arch team
#define HYP_TESTS_OWNER_PLATFORM  0x1    // TEST_GROUP_ID used by arch team
#define HYP_TESTS_OWNER_QHEE    0x2   // TEST_GROUP_ID used by arch team
#define HYP_TESTS_OWNER_HYPX    0x3  // TEST_GROUP_ID used by arch team
#define HYP_TESTS_OWNER_GUNYAH    0x4    // TEST_GROUP_ID used by arch team
  
#define TZ_TESTS_OWNER_ARCH     0x0    // TEST_GROUP_ID used by arch team
#define TZ_TESTS_OWNER_PLATFORM   0x1    // TEST_GROUP_ID used by arch team

#endif // _QNTM_HYPTZ_GROUPS_H_