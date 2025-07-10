#ifndef __PM_DUMP_H__
#define __PM_DUMP_H__

/*! \file
 *  
 *  \brief  pm_dump.h ----This file contain PMIC dump related API 
 *  
 *    &copy; Copyright 2020-2021 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/07/20   xp      Created

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "com_dtypes.h"
#include "pm_err_flags.h"


/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
#define REG_NUM_PER_PERIPHERAL            (0x100)
#define PMIC_DUMP_HEADER_INFO_LEN         (60) // need to be multiple of 4
#define PMIC_DUMP_VERSION                 (2)  // v2 for new framework
#define PMIC_PBUS_LOG_VERSION             (2)  // v2 for new framework

#define REG_DUMP_START_SIGNATURE          (0x4452) //Ascii of 'D' and 'R', stands for Register dump
#define REG_DUMP_COMPLETE_SIGNATURE       (0x44434752) // Ascii for 'D''C''G''R', ReGister Complete Dumped
#define IMAGE_SBL                         (0x4C4253) // Ascii of 'L', 'B' and 'S'

#define PERIPH_OFFSET (0x100)
#define PERIPH_BUF_SIZE (REG_NUM_PER_PERIPHERAL + 4)         // 4: bus id/slave id/periph id/reserved


typedef struct
{
  uint32 version;
  uint32 dump_sign;
  uint32 image_name;
  uint32 pm_dump_size;
  uint32 max_pmic_number;
} pm_dump_header_type;


/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

pm_err_flag_type pm_pmic_dump_entry(uint8* buf, uint64 offset, uint64 size);

pm_err_flag_type pm_dump_pmic_register(uint8* buf, uint64 offset, uint64 size, uint64* end_offset, boolean* complete);


#endif // __PM_DUMP_H__
