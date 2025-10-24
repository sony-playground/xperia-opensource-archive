/*===========================================================================

GENERAL DESCRIPTION
  This module contains the initial memory map for Ramdump.

  Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.

 ==============================================================================*/
/*=============================================================================
                          EDIT HISTORY

when       who     what, where, why
--------   ---     -----------------------------------------------------------
08/08/22   yps     Mapped DDR region and ZI regions to cacheable
02/08/22   ck      Moved uncached_heap_memmap_init to common file
02/02/22   ck      Added optional PCIE_0_PCIE_WRAPPER_AXI_BASE region
06/17/21   rama    Mapped TME_CPULAYER_CSR region for dbginfo
03/11/21   yps     Mapped all ramdump data regions
03/03/21   ds      Map DCC regions
01/18/21   yps     Added PIMEM region 
12/07/20   yps     Correct ramdump code region and attribute for MMU setting
11/05/20   yps     Initial revision

=============================================================================*/

#include "boot_target.h"
#include "boot_error_if.h"
#include "boot_config_context.h"
#include "Target_cust.h"
#include "MDPPlatformLib.h"
#include <boot_edk2_mmu_if.h>
#include <msmhwiobase.h>
#include <HALbootHWIO.h>

extern uintnt  Image$$RAMDUMP_CODE$$Base[];
extern uintnt  Image$$RAMDUMP_CODE$$Length[];
extern uintnt  Image$$RAMDUMP_DATA_ZI$$Base[];
extern uintnt  Image$$RAMDUMP_DATA_ZI$$Length[];
extern uintnt  Image$$RAMDUMP_DATA_RW$$Base[];
extern uintnt  Image$$RAMDUMP_DATA_RW$$Length[];
extern uintnt  Image$$RAMDUMP_DATA_RO$$Base[];
extern uintnt  Image$$RAMDUMP_DATA_RO$$Length[];
extern uintnt  Image$$STACK$$Base[];
extern uintnt  Image$$STACK$$Length[];


/*===========================================================================
**  Function :  xbl_populate_initial_mem_map
** ==========================================================================
*/
/*!
*
* @brief
*   populate the existing pbl page table with Ramdump memory mapping
*
* @param[in] bl_shared_data Pointer to shared data
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*
*/
bl_error_boot_type ramdump_populate_mem_map(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_edk2_mmu_if_type *edk2_mmu_if = NULL;

  ARM_MEMORY_REGION_DESCRIPTOR ramdump_memory_map[]=
  {
    { GCC_CLK_CTL_REG_REG_BASE,            GCC_CLK_CTL_REG_REG_BASE,           GCC_CLK_CTL_REG_REG_BASE_SIZE,                                        ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { REGISTER_REGION1_BASE,               REGISTER_REGION1_BASE,              REGISTER_REGION1_SIZE,                                                ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { SCL_AOP_DATA_RAM_BASE,               SCL_AOP_DATA_RAM_BASE,              SCL_AOP_DATA_RAM_SIZE,                                                ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { REGISTER_REGION2_BASE,               REGISTER_REGION2_BASE,              REGISTER_REGION2_SIZE,                                                ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { SCL_IMEM_BASE,                       SCL_IMEM_BASE,                      SCL_IMEM_SIZE,                                                        ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
#ifdef SCL_pIMEM_BASE
    { SCL_pIMEM_BASE,                      SCL_pIMEM_BASE,                     SCL_pIMEM_SIZE,                                                       ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
#endif    
    { (uint64)SHARED_IMEM_BASE,            (uint64)SHARED_IMEM_BASE,           (uint64)SHARED_IMEM_SIZE,                                             ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED_XN },
    { (uint64)SCL_BOOT_IMEM_BASE_ADDR,     (uint64)SCL_BOOT_IMEM_BASE_ADDR,    (uint64)SCL_BOOT_IMEM_START_XBL_UNUSED,                               ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { APSS_HM_BASE,                        APSS_HM_BASE,                       APSS_HM_BASE_SIZE,                                                    ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { DDR_SS_BASE,                         DDR_SS_BASE,                        DDR_SS_BASE_SIZE,                                                     ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { SCL_DCC_LL_SRAM_BASE,                SCL_DCC_LL_SRAM_BASE,               SCL_DCC_LL_SRAM_SIZE,                                                 ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { SCL_DCC_CFG,                         SCL_DCC_CFG,                        SCL_DCC_CFG_SIZE,                                                     ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { QFPROM_CORR_REG_BASE,                QFPROM_CORR_REG_BASE,               QFPROM_CORR_REG_BASE_SIZE,                                            ARM_MEMORY_REGION_ATTRIBUTE_DEVICE_RO },
    { FUSE_CONTROLLER_SW_RANGE4_REG_BASE,  FUSE_CONTROLLER_SW_RANGE4_REG_BASE, FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE,                              ARM_MEMORY_REGION_ATTRIBUTE_DEVICE_RO },
    { DDR_MEM_BASE_1,                      DDR_MEM_BASE_1,                     DDR_MEM_SIZE_1,                                                       ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { DDR_MEM_BASE_2,                      DDR_MEM_BASE_2,                     DDR_MEM_SIZE_2,                                                       ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { (uint64)Image$$RAMDUMP_CODE$$Base,   (uint64)Image$$RAMDUMP_CODE$$Base,  (uint64)Image$$RAMDUMP_CODE$$Length,                                  ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_RO },
    { (uint64)Image$$STACK$$Base,          (uint64)Image$$STACK$$Base,         (uint64)Image$$STACK$$Length,                                         ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { (uint64)Image$$RAMDUMP_DATA_RO$$Base,(uint64)Image$$RAMDUMP_DATA_RO$$Base, (uint64)Image$$RAMDUMP_DATA_RO$$Length,                             ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN_RO },
    { (uint64)Image$$RAMDUMP_DATA_RW$$Base,(uint64)Image$$RAMDUMP_DATA_RW$$Base, (uint64)Image$$RAMDUMP_DATA_RW$$Length,                             ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { (uint64)Image$$RAMDUMP_DATA_ZI$$Base,(uint64)Image$$RAMDUMP_DATA_ZI$$Base, (uint64)Image$$RAMDUMP_DATA_ZI$$Length,                             ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { (uint64)TME_CPULAYER_CSR_REG_BASE,   (uint64)TME_CPULAYER_CSR_REG_BASE,    (uint64)TME_CPULAYER_CSR_REG_BASE_SIZE,                             ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
#ifdef PCIE_0_PCIE_WRAPPER_AXI_BASE
    { PCIE_0_PCIE_WRAPPER_AXI_BASE,        PCIE_0_PCIE_WRAPPER_AXI_BASE,       PCIE_0_PCIE_WRAPPER_AXI_BASE_SIZE,                                    ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
#endif
    /* Table terminator */
    {0,0,0,0}
  };

  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_EDK2_MMU_INTERFACE, (void **)&edk2_mmu_if);
    if(return_status != BL_ERR_NONE || edk2_mmu_if == NULL)
    {
      break;
    }
      
    if(edk2_mmu_if->ArmConfigureMmu (ramdump_memory_map, NULL, NULL) != EFI_SUCCESS)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MMU, BL_ERR_MMU_PGTBL_MAPPING_FAIL);
    }
  }while(0);

  return return_status;
}
