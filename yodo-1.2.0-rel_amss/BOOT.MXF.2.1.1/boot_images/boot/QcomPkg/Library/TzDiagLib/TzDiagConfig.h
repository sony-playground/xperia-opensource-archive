#ifndef __TZDIAGCONFIG_H__
#define __TZDIAGCONFIG_H__

/**
 * @file  TzDiagConfig.h
 * @brief Contains target specific information. 
 */
/*
===============================================================================

                               Edit History

$Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------ 
09/09/20   dpk     Created. 

===============================================================================
              Copyright (c) 2020 QUALCOMM Technologies, Inc.
                         All Rights Reserved.
            Qualcomm Technologies Proprietary and Confidential.
===============================================================================
*/

#include <Protocol/EFIChipInfoTypes.h>


typedef struct tzbsp_diag_config_info_s
{
  void *pDiagAddr;                    /* TZ Diag address in PIMEM */
  BOOLEAN bIsDiagEncFeatSupported;    /* TZ Diag encryption feature supported for this target or not */

} tzbsp_diag_config_info_t;


tzbsp_diag_config_info_t *tz_diag_get_config_info(EFIChipInfoFamilyType chip_family);



#endif
