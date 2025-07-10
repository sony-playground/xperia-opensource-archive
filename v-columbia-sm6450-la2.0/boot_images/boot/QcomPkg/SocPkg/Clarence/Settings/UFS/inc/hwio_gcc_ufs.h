#ifndef __HWIO_GCC_UFS_H__
#define __HWIO_GCC_UFS_H__
/*
===========================================================================
*/
/**
    @file hwio_gcc_ufs.h
    @brief Auto-generated HWIO interface include file.

    Reference chip release:
        Clarence [clarence_v1.0_p3q1r29]
 
    This file contains HWIO register definitions for the following modules:
        GCC_CLK_CTL_REG

    'Include' filters applied: UFS_PHY_BCR[GCC_CLK_CTL_REG] 

    Generation parameters: 
    { 'filename': 'hwio_gcc_ufs.h',
      'module-filter-include': {'GCC_CLK_CTL_REG': ['UFS_PHY_BCR']},
      'modules': ['GCC_CLK_CTL_REG'],
      'output-offsets': True}
*/
/*
    ===========================================================================

    Copyright (c) 2022 Qualcomm Technologies, Inc.
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

    $Header: //components/dev/core.boot/6.0/rajinegi.core.boot.6.0.25_5_v2/QcomPkg/SocPkg/Clarence/Settings/UFS/inc/hwio_gcc_ufs.h#2 $
    $DateTime: 2022/05/27 15:00:00 $
    $Author: rajinegi $

    ===========================================================================
*/

/*----------------------------------------------------------------------------
 * MODULE: GCC_CLK_CTL_REG
 *--------------------------------------------------------------------------*/

#define GCC_CLK_CTL_REG_REG_BASE                                                                      (CLK_CTL_BASE      + 0x00010000)
#define GCC_CLK_CTL_REG_REG_BASE_SIZE                                                                 0x1e0000
#define GCC_CLK_CTL_REG_REG_BASE_USED                                                                 0xa605c
#define GCC_CLK_CTL_REG_REG_BASE_OFFS                                                                 0x00010000

#define HWIO_GCC_UFS_PHY_BCR_ADDR                                                                     (GCC_CLK_CTL_REG_REG_BASE      + 0x77000)
#define HWIO_GCC_UFS_PHY_BCR_OFFS                                                                     (GCC_CLK_CTL_REG_REG_BASE_OFFS + 0x77000)
#define HWIO_GCC_UFS_PHY_BCR_RMSK                                                                            0x1
#define HWIO_GCC_UFS_PHY_BCR_IN                    \
                in_dword(HWIO_GCC_UFS_PHY_BCR_ADDR)
#define HWIO_GCC_UFS_PHY_BCR_INM(m)            \
                in_dword_masked(HWIO_GCC_UFS_PHY_BCR_ADDR, m)
#define HWIO_GCC_UFS_PHY_BCR_OUT(v)            \
                out_dword(HWIO_GCC_UFS_PHY_BCR_ADDR,v)
#define HWIO_GCC_UFS_PHY_BCR_OUTM(m,v) \
                out_dword_masked_ns(HWIO_GCC_UFS_PHY_BCR_ADDR,m,v,HWIO_GCC_UFS_PHY_BCR_IN)
#define HWIO_GCC_UFS_PHY_BCR_BLK_ARES_BMSK                                                                   0x1
#define HWIO_GCC_UFS_PHY_BCR_BLK_ARES_SHFT                                                                     0


#endif /* __HWIO_GCC_UFS_H__ */
