/** @file DepTestConstants.h
   
  Constants for Data Execution Prevention (ARM)
  
  Copyright (c) 2021 Qualcomm Technologies, Inc.  All
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

#define NOP_OPCODE 0xE3A03000 //mov r3,#0
#define RET_OPCODE 0xE12FFF1E // ret LR

