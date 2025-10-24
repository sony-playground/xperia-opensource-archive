#ifndef __HAMOA_PCIE_HWIO_BASES_H___
#define __HAMOA_PCIE_HWIO_BASES_H___
/*
 *  ==============================================================================
 *      Copyright (c) 2022 QUALCOMM Technologies Incorporated
 *      All Rights Reserved.  Qualcomm Confidential and Proprietary.
 *  ==============================================================================
 */

/*----------------------------------------------------------------------------
 * BASE: CORE_TOP_CSR
 *--------------------------------------------------------------------------*/

#define CORE_TOP_CSR_BASE                                           0x01f00000
#define CORE_TOP_CSR_BASE_SIZE                                      0x00100000
#define CORE_TOP_CSR_BASE_PHYS                                      0x01f00000

/*----------------------------------------------------------------------------
 * BASE: PCIE_4PCIE_WRAPPER_AXI_G3X1_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE_4PCIE_WRAPPER_AXI_G3X1_AUTO_BASE                       0x30000000
#define PCIE_4PCIE_WRAPPER_AXI_G3X1_AUTO_BASE_SIZE                  0x02000000
#define PCIE_4PCIE_WRAPPER_AXI_G3X1_AUTO_BASE_PHYS                  0x30000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_3BPCIE_WRAPPER_AXI_G3X2_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE_3BPCIE_WRAPPER_AXI_G3X2_AUTO_BASE                      0x32000000
#define PCIE_3BPCIE_WRAPPER_AXI_G3X2_AUTO_BASE_SIZE                 0x02000000
#define PCIE_3BPCIE_WRAPPER_AXI_G3X2_AUTO_BASE_PHYS                 0x32000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_3APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE_3APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO_BASE                 0x34000000
#define PCIE_3APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO_BASE_SIZE            0x02000000
#define PCIE_3APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO_BASE_PHYS            0x34000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_2BPCIE_WRAPPER_AXI_G3X2_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE_2BPCIE_WRAPPER_AXI_G3X2_AUTO_BASE                      0x38000000
#define PCIE_2BPCIE_WRAPPER_AXI_G3X2_AUTO_BASE_SIZE                 0x02000000
#define PCIE_2BPCIE_WRAPPER_AXI_G3X2_AUTO_BASE_PHYS                 0x38000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_2APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE_2APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO_BASE                 0x3c000000
#define PCIE_2APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO_BASE_SIZE            0x02000000
#define PCIE_2APCIE_WRAPPER_AXI_G3X4_EDMA_AUTO_BASE_PHYS            0x3c000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_2B_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_2B_SPACE_SIZE_BASE                                     0x40000000
#define PCIE_2B_SPACE_SIZE_BASE_SIZE                                0x00000000
#define PCIE_2B_SPACE_SIZE_BASE_PHYS                                0x40000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_3A_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_3A_SPACE_SIZE_BASE                                     0x40000000
#define PCIE_3A_SPACE_SIZE_BASE_SIZE                                0x00000000
#define PCIE_3A_SPACE_SIZE_BASE_PHYS                                0x40000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_3B_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_3B_SPACE_SIZE_BASE                                     0x40000000
#define PCIE_3B_SPACE_SIZE_BASE_SIZE                                0x00000000
#define PCIE_3B_SPACE_SIZE_BASE_PHYS                                0x40000000

/*----------------------------------------------------------------------------
 * BASE: PCIE_4_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_4_SPACE_SIZE_BASE                                      0x40000000
#define PCIE_4_SPACE_SIZE_BASE_SIZE                                 0x00000000
#define PCIE_4_SPACE_SIZE_BASE_PHYS                                 0x40000000

/*----------------------------------------------------------------------------
 * BASE: PCIE4_CFGPCIE_WRAPPER_AHB_W_PHY_G3X1_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE4_CFGPCIE_WRAPPER_AHB_W_PHY_G3X1_AUTO_BASE              0x01c00000
#define PCIE4_CFGPCIE_WRAPPER_AHB_W_PHY_G3X1_AUTO_BASE_SIZE         0x00008000
#define PCIE4_CFGPCIE_WRAPPER_AHB_W_PHY_G3X1_AUTO_BASE_PHYS         0x01c00000

/*----------------------------------------------------------------------------
 * BASE: PCIE3B_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE3B_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE     0x01c08000
#define PCIE3B_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_SIZE 0x00008000
#define PCIE3B_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_PHYS 0x01c08000

/*----------------------------------------------------------------------------
 * BASE: PCIE3A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE3A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE     0x01c10000
#define PCIE3A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_SIZE 0x00008000
#define PCIE3A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_PHYS 0x01c10000

/*----------------------------------------------------------------------------
 * BASE: PCIE2B_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE2B_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE     0x01c18000
#define PCIE2B_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_SIZE 0x00008000
#define PCIE2B_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_PHYS 0x01c18000

/*----------------------------------------------------------------------------
 * BASE: PCIE2A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO
 *--------------------------------------------------------------------------*/

#define PCIE2A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE     0x01c20000
#define PCIE2A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_SIZE 0x00008000
#define PCIE2A_CFGPCIE_WRAPPER_AHB_W_PHY_G3X2_X4_EDMA_AUTO_BASE_PHYS 0x01c20000

/*----------------------------------------------------------------------------
 * BASE: PCIE_4_SPACE
 *--------------------------------------------------------------------------*/

#define PCIE_4_SPACE_BASE                                           0x400000000uLL
#define PCIE_4_SPACE_BASE_SIZE                                      0x00000000
#define PCIE_4_SPACE_BASE_PHYS                                      0x400000000uLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_4_SPACE_END
 *--------------------------------------------------------------------------*/

#define PCIE_4_SPACE_END_BASE                                       0x43fffffffuLL
#define PCIE_4_SPACE_END_BASE_SIZE                                  0x00000000
#define PCIE_4_SPACE_END_BASE_PHYS                                  0x43fffffffuLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_3B_SPACE
 *--------------------------------------------------------------------------*/

#define PCIE_3B_SPACE_BASE                                          0x440000000uLL
#define PCIE_3B_SPACE_BASE_SIZE                                     0x00000000
#define PCIE_3B_SPACE_BASE_PHYS                                     0x440000000uLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_3B_SPACE_END
 *--------------------------------------------------------------------------*/

#define PCIE_3B_SPACE_END_BASE                                      0x47fffffffuLL
#define PCIE_3B_SPACE_END_BASE_SIZE                                 0x00000000
#define PCIE_3B_SPACE_END_BASE_PHYS                                 0x47fffffffuLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_3A_SPACE
 *--------------------------------------------------------------------------*/

#define PCIE_3A_SPACE_BASE                                          0x480000000uLL
#define PCIE_3A_SPACE_BASE_SIZE                                     0x00000000
#define PCIE_3A_SPACE_BASE_PHYS                                     0x480000000uLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_3A_SPACE_END
 *--------------------------------------------------------------------------*/

#define PCIE_3A_SPACE_END_BASE                                      0x4bfffffffuLL
#define PCIE_3A_SPACE_END_BASE_SIZE                                 0x00000000
#define PCIE_3A_SPACE_END_BASE_PHYS                                 0x4bfffffffuLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_2B_SPACE
 *--------------------------------------------------------------------------*/

#define PCIE_2B_SPACE_BASE                                          0x4c0000000uLL
#define PCIE_2B_SPACE_BASE_SIZE                                     0x00000000
#define PCIE_2B_SPACE_BASE_PHYS                                     0x4c0000000uLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_2B_SPACE_END
 *--------------------------------------------------------------------------*/

#define PCIE_2B_SPACE_END_BASE                                      0x4ffffffffuLL
#define PCIE_2B_SPACE_END_BASE_SIZE                                 0x00000000
#define PCIE_2B_SPACE_END_BASE_PHYS                                 0x4ffffffffuLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_2A_SPACE
 *--------------------------------------------------------------------------*/

#define PCIE_2A_SPACE_BASE                                          0x500000000uLL
#define PCIE_2A_SPACE_BASE_SIZE                                     0x00000000
#define PCIE_2A_SPACE_BASE_PHYS                                     0x500000000uLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_2A_SPACE_END
 *--------------------------------------------------------------------------*/

#define PCIE_2A_SPACE_END_BASE                                      0x5ffffffffuLL
#define PCIE_2A_SPACE_END_BASE_SIZE                                 0x00000000
#define PCIE_2A_SPACE_END_BASE_PHYS                                 0x5ffffffffuLL

/*----------------------------------------------------------------------------
 * BASE: PCIE_2A_SPACE_SIZE
 *--------------------------------------------------------------------------*/

#define PCIE_2A_SPACE_SIZE_BASE                                     0x100000000uLL
#define PCIE_2A_SPACE_SIZE_BASE_SIZE                                0x00000000
#define PCIE_2A_SPACE_SIZE_BASE_PHYS                                0x100000000uLL


#endif  /* __PCIE_HWIO_BASES_H___ */

