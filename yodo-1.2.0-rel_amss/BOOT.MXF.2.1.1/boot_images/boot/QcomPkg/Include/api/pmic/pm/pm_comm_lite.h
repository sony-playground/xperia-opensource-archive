#ifndef __PM_COMM_H__
#define __PM_COMM_H__

/*! \file pm_comm.h
 *  \n
 *  \brief
 *  \n
 *  &copy; Copyright 2014-2019,2021 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/pmic/pm/pm_comm_lite.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
30/08/21   aab     File added

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "pm_err_flags.h"

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/

pm_err_flag_type
pm_comm_read_byte(uint32 slave_id ,
                  uint16 addr,
                  uint8* data);


#endif /* __PM_COMM_H__ */

