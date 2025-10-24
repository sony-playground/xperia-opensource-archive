#ifndef __TZDIAGCONFIGINFO_H__
#define __TZDIAGCONFIGINFO_H__

/**
 * @file  TzDiagConfigInfo.h
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
#include <TzDiagConfig.h>


/*
*  NOTE:: Keeping the size constraints in mind, always maintain the information of required targets only. 
*/

/* MAKENA */
tzbsp_diag_config_info_t target_config_info_makena = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0003F000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};


/* OLYMPIC */
tzbsp_diag_config_info_t target_config_info_olympic = 
{
    .pDiagAddr               = NULL,
    .bIsDiagEncFeatSupported = FALSE,
};

#endif
