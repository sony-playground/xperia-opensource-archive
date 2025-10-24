#ifndef __KAILUA_PCIE_HWIO_BASES_H___
#define __KAILUA_PCIE_HWIO_BASES_H___
/*
 *  ==============================================================================
 *      Copyright (c) 2022 QUALCOMM Technologies Incorporated
 *      All Rights Reserved.  Qualcomm Confidential and Proprietary.
 *  ==============================================================================
 */


/*----------------------------------------------------------------------------
 * BASE: PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_EDMA
 *--------------------------------------------------------------------------*/
#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_EDMA_BASE                 0x01c00000
#define PCIE0_PCIE_WRAPPER_AHB_W_PHY_G3X2_EDMA_SIZE                 0x00008000

/*----------------------------------------------------------------------------
 * BASE: PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA
 *--------------------------------------------------------------------------*/
#define PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA_BASE                 0x01c08000
#define PCIE1_PCIE_WRAPPER_AHB_W_PHY_G4X2_EDMA_SIZE                 0x00008000


/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN4X2_SPACE
 *--------------------------------------------------------------------------*/
#define PCIE_GEN4X2_SPACE_BASE                                      0x40000000
#define PCIE_GEN4X2_SPACE_SIZE                                      0x20000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_GEN3X2_SPACE
 *--------------------------------------------------------------------------*/
#define PCIE_GEN3X2_SPACE_BASE                                      0x60000000
#define PCIE_GEN3X2_SPACE_SIZE                                      0x04000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_1_SPACE
 *--------------------------------------------------------------------------*/
#define PCIE_1_SPACE_BASE                                           0x400000000uLL
#define PCIE_1_SPACE_BASE_SIZE                                      0x300000000

#endif  /* __PCIE_HWIO_BASES_H___ */

