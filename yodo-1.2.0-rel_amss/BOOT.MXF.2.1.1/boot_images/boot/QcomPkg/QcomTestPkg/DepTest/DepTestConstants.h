/** @file DepTestConstants.h
   
  Constants for Data Execution Prevention (AARCH64)
  
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc.  All
  Rights Reserved. Qualcomm Technologies Proprietary and
  Confidential.

**/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/05/21   cm      Initital revision

=============================================================================*/


#define MAX_IMAGE_SIZE 0x80000
#define MAX_IMG_PATH_LEN 256

#define NOP_OPCODE 0xAA0003E0 //mov r0,#0
#define RET_OPCODE 0xD65F03C0 // ret 

