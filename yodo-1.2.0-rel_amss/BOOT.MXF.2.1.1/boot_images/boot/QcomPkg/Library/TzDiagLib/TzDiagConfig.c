/**
 * @file  TzDiagTarget.c
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

#include <Uefi.h>
#include <TzDiagConfigInfo.h>
#include <Protocol/EFIChipInfo.h>



tzbsp_diag_config_info_t *tz_diag_get_config_info(EFIChipInfoFamilyType chip_family)
{
    tzbsp_diag_config_info_t *p_target_config_info = NULL;
    	
    switch (chip_family)
    {
        case EFICHIPINFO_FAMILY_MAKENA:
            p_target_config_info = &target_config_info_makena;
            break;

        case EFICHIPINFO_FAMILY_OLYMPIC:
            p_target_config_info = &target_config_info_olympic;
            break;

        default:
            DEBUG((EFI_D_ERROR,"tz_diag_get_config_info(): Target 0x%x not supported \n", chip_family));  
    }
  
    return p_target_config_info;
}

