#ifndef __TMESS_HWIO_H__
#define __TMESS_HWIO_H__
/*
===========================================================================
*/
/**
    @file tmess_hwio.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        SM8550 (Kailua) [kailua_v1.0_p3q1r7.9_rtl_partition_F01]
 
    This file contains HWIO register definitions for the following modules:
        TME_CPULAYER_MBOX


    Generation parameters: 
    { 'explicit-addressing': True,
      'filename': 'tmess_hwio.h',
      'header': '#include "msmhwiobase.h"',
      'modules': ['TME_CPULAYER_MBOX'],
      'output-attrs': True,
      'output-fvals': True,
      'output-offsets': True,
      'output-phys': True}

    Attribute definitions for the HWIO_*_ATTR macros are as follows:
        0x0: Command register
        0x1: Read-Only
        0x2: Write-Only
        0x3: Read/Write
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

    $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Include/tmess_hwio.h#1 $
    $DateTime: 2022/08/18 10:15:46 $
    $Author: pwbldsvc $

    ===========================================================================
*/

#include "msmhwiobase.h"

/*----------------------------------------------------------------------------
 * MODULE: TME_CPULAYER_MBOX
 *--------------------------------------------------------------------------*/

#define TME_CPULAYER_MBOX_REG_BASE (TMESS_BASE            + 0x02000000)
#define TME_CPULAYER_MBOX_REG_BASE_SIZE 0x4000
#define TME_CPULAYER_MBOX_REG_BASE_USED 0x0
#define TME_CPULAYER_MBOX_REG_BASE_PHYS (TMESS_BASE_PHYS + 0x02000000)
#define TME_CPULAYER_MBOX_REG_BASE_OFFS 0x02000000


#endif /* __TMESS_HWIO_H__ */
