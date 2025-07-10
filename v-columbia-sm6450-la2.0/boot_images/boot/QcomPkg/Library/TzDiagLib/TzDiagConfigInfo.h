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
08/10/21   var     Created. 

===============================================================================
              Copyright (c) 2021 QUALCOMM Technologies, Inc.
                         All Rights Reserved.
            Qualcomm Technologies Proprietary and Confidential.
===============================================================================
*/

#include <Uefi.h>
#include <TzDiagConfig.h>


/*
*  NOTE:: Keeping the size constraints in mind, always maintain the information of required targets only. 
*/

/* WAIPIO */
tzbsp_diag_config_info_t target_config_info_waipio = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* FILLMORE */
tzbsp_diag_config_info_t target_config_info_fillmore = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* PALIMA */
tzbsp_diag_config_info_t target_config_info_palima = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* KAILUA */
tzbsp_diag_config_info_t target_config_info_Kailua = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* AURORA */
tzbsp_diag_config_info_t target_config_info_aurora = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* NETRANI */
tzbsp_diag_config_info_t target_config_info_netrani = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* LASSEN */
tzbsp_diag_config_info_t target_config_info_lassen = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

/* CLARENCE */
tzbsp_diag_config_info_t target_config_info_clarence = 
{
    .pDiagAddr               = (void *)(0x14680000 + 0x0002A000 + 0x00000720),    // SYSTEM_IMEM_BASE + IMEM_BASE_OFFSET + IMEM_TZ_DIAG_OFFSET
    .bIsDiagEncFeatSupported = TRUE,
};

#endif
