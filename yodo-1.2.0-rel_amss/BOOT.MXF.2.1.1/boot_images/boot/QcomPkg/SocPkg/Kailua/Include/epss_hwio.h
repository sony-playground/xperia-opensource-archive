#ifndef __EPSS_HWIO_H__
#define __EPSS_HWIO_H__
/*
===========================================================================
*/
/**
    @file epss_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [kailua_v1.0_p2q0r5.6_rtl_partition]
 
*/
/*
    ===========================================================================

    Copyright (c) 2021 Qualcomm Technologies, Inc.
    All Rights Reserved.
    Confidential and Proprietary - Qualcomm Technologies, Inc.

    Export of this technology or software is regulated by the U.S. Government.
    Diversion contrary to U.S. law prohibited.

    All ideas, data and information contained in or disclosed by
    this document are confidential and proprietary information of
    Qualcomm Technologies, Inc. and all rights therein are expressly reserved.
    By accepting this material the recipient agrees that this material
    and the information contained therein are held in confidence and in
    trust and will not be used, copied, reproduced in whole or in part,
    nor its contents revealed in any manner to others without the express
    written permission of Qualcomm Technologies, Inc.

    ===========================================================================

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Include/epss_hwio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: CPUCP 
 *--------------------------------------------------------------------------*/

#define CPUCP_GLOBAL_ENABLE 0x17d98008
#define GLOBAL_ENABLE_SHIFT 0x00
#define GLOBAL_ENABLE_MASK 0x01

#define CPUCP_MUC_CLK_CTRL 0x17d98004
#define CORE_SS_CLK_EN_SHIFT 0x00
#define CORE_SS_CLK_EN_MASK 0x01
#define CORE_CLK_EN_SHIFT 0x01
#define CORE_CLK_EN_MASK 0x01

#define CPUCP_SECURE_ACCESS_OVERRIDE 0x17d98000
#define SECURE_ACCESS_OVERRIDE_SHIFT 0x00
#define SECURE_ACCESS_OVERRIDE_MASK 0x01

#endif /* __EPSS_HWIO_H__ */
