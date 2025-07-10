/*===========================================================================
Copyright (c) 2018,2019, 2021 Qualcomm Technologies Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Fillmore/Library/SmemImageLib/smem_xbl_cfg_fillmore.c#3 $
$DateTime: 2021/11/09 13:27:33 $
$Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
10/09/18   mad     Removed Access control for MPSS for Kona
08/27/15   an      Initial version.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include <comdef.h>
#include "smem_type.h"
#include <seclib_ac.h>

/*===========================================================================
                      TYPE DEFINITIONS
===========================================================================*/


/*===========================================================================
                      GLOBAL DATA DEFINITIONS
===========================================================================*/

/*----------------------------------------------------------------------------
 * smem_ac_host_to_vm_get()
 *--------------------------------------------------------------------------*/
ACSecDomainId smem_ac_host_to_vm_get(smem_host_type host)
{
  ACSecDomainId ret = AC_SD_END_MARKER;
  
  switch(host)
  {
    case SMEM_APPS:
      ret = AC_SD_AP_NSEC;
      break;

    case SMEM_MODEM:
      ret = AC_SD_MODEM;
      break;

    case SMEM_RPM:
      ret = AC_SD_AOP;
      break;

    case SMEM_TZ:
      ret = AC_SD_AP_SEC;
      break;

    case SMEM_TME:
      ret = AC_SD_TME_FW;
      break;

    default:
      ret = AC_SD_END_MARKER;
      break;
  }
  
  return ret;
}
