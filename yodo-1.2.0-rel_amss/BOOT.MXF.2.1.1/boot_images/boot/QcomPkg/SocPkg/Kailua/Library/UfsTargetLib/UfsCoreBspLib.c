/**********************************************************************
* UfsCoreBspLib.c
*
* Board support file for XBL core
*
* Copyright (c) 2013-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
* 
*
**********************************************************************/

/*=======================================================================
                        Edit History

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/UfsTargetLib/UfsCoreBspLib.c#3 $
$DateTime: 2022/09/23 17:25:31 $

YYYY-MM-DD   who     what, where, why
---------------------------------------------------------------------- 
2022-09-16   jt      Add PHY init functions for Eye Monitor  
2022-08-24   rn      Remove /storage/ from path in DTB tree
2022-07-11   jt      Set FORCE_MEM_CORE_ON=1 for ICE clock 
2022-06-10   jt      Add FUA value to configuration settings 
2022-06-07   jt      Add function to pass info to HLOS
2022-04-14   sa      Added support for BlockIo2 with multiple doorbells.
2022-03-21   cm      Add API to return turbo mode support info
2022-02-23   sa      Move from Setting to Library Folder.
2022-02-17   jt      ICE clock frequency update for Kailua
2021-11-05   jt      Add refclk_freq to platform_config
2021-09-08   jt      Add ability to check battery status 
2021-08-13   jt      Add device tree support
2021-08-10   sa      Remove ref clock as it is not supported.
2021-07-20   sa      Remove reference to smmu header.
2021-01-28   jt      Add reference clock
2020-09-10   jt      Remove UFS Card SMMU configuration
2020-06-29   jt      Update logging function 
2020-05-04   jt      Re-enable clock if previously disabled   
2020-03-31   jt      Add power management functions
2019-10-22   jt      Remove voltage switching
2019-07-22   jt      Add SMMU configuration API 
2019-02-27   jt      Add UFS 3.0 support  
2018-11-01   jt      Mask off lowest 2 bits for SOC emulation type 
2018-09-24   jt      Move PHY settings to its own file 
2018-09-05   jt      Restructure PHY initialization 
2018-07-24   jt      HPG updates for Hana v2 
2018-06-21   jt      Only do cache management if CCA disabled
2018-06-04   jt      Add ability to turn clocks off/on
2018-05-30   jt      HPG v7.0 PHY updates for Hana/Poipu   
2018-02-13   jt      PHY init updates for Hana/Poipu 
2017-07-31   jt      Add log function 
2017-06-06   jt      Adapt for Hana
2017-04-08   jt      Turn on flags to skip actions in core  
2017-01-25   jt      Add UFS device reset 
2016-11-01   jt      Add reset function 
2016-10-21   jt      Enable HS for RUMI
2016-09-14   jt      AANG RUMI PHY init updates  
2016-08-22   jt      PHY init updates from 8998v2 
2016-07-22   jt      Adapted for Napali 
2015-06-15   rh      Disable the PHY from decoding the LCC sequence
2014-09-17   rh      Adapted for 8996 
2013-10-30   rh      Clock regime function cleanup
2013-10-30   rh      More accurate delay added
2013-06-19   rh      Initial creation
===========================================================================*/

#include <Uefi.h>
#include <HALhwio.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/SynchronizationLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiCfgLib.h>
#include <Protocol/EFIHWIO.h>
#include <Protocol/EFIClock.h>
#include <Protocol/LoadedImage.h> 
#include <Protocol/EFIPlatformInfo.h> 
#include <Protocol/EFIHALIOMMUProtocol.h>
#include <Protocol/EFIStorageDeviceMgmt.h>
#include <Protocol/EFIDtbExtn.h>

#include <Library/PcdLib.h>
#include <Library/ArmLib.h>
#include <stdio.h>

#include "DDIPlatformInfo.h"
#include "UfsPhySequence.h"
#include "aang_phy_hwio.h"
#include "HALbootHWIO.h"
#include "UfsHwioAll.h"
#include "npa.h"
#include "pmapp_npa.h"

#define UFS_PHY_PCS_READY_TIMEOUT      0xffffff

BOOLEAN UFSClocksInited = FALSE; 
EFI_CLOCK_PROTOCOL *hUFS_Clock = NULL;
EFI_DTB_EXTN_PROTOCOL *DtbProtocol = NULL;
DalPlatformInfoPlatformType g_platform;
enum hal_iommu_bypass_domain_type cca_flag = HAL_IOMMU_DOMAIN_TYPE_INVALID;
 
// Information used for power management 
typedef struct 
{
   EFI_STORAGE_VOLT_CORNER volt_corner;
   ufs_bsp_hs_gears        max_hs_gear_allowed;
   ufs_bsp_time_values     time_vals;
} ufs_bsp_pm_info;

// This list should be modified based on the voltage corners specified in the Storage Device Management protocol. 
// For each voltage corner, max gear supported is listed. The register vales are also based on the voltage corner. 
static ufs_bsp_pm_info ufs_pm_params[] = 
{ 
  	{ VOLT_CORNER_MINSVS,   UFS_GEAR_INVALID, {   0, 0,     0}},
  	{ VOLT_CORNER_LOWSVS,   UFS_GEAR_2,       {  75, 3,    75}},  
	{ VOLT_CORNER_SVS,      UFS_GEAR_3,       { 150, 6,   150}},
	{ VOLT_CORNER_NOM,      UFS_GEAR_5,       { 300, 12,  300}},
	{ VOLT_CORNER_TURBO,    UFS_GEAR_5,       { 300, 12,  300}}
};

// Below values are in the following order:   
// {clock name, clock_id, OFF, MINSVS, LOWSVS, SVS, NOM, TURBO}
static UFS_CLOCK_LIST ufs_clocks_array[] = 
{
   {
      {"gcc_ufs_phy_axi_clk", 0, 0, 0, 75000000, 150000000, 300000000, 300000000}, 
      {"gcc_ufs_phy_ice_core_clk", 0, 0, 0, 100000000, 201500000, 403000000, 403000000}, 
      {"gcc_ufs_phy_unipro_core_clk", 0, 0, 0, 75000000, 150000000, 300000000, 300000000},
      {"gcc_aggre_ufs_phy_axi_clk", 0, 0, 0, 0, 0, 0, 0}, 
      {"gcc_ufs_phy_ahb_clk", 0, 0, 0, 0, 0, 0, 0}, 
      {"gcc_ufs_phy_phy_aux_clk", 0, 0, 0, 0, 0, 0, 0}, 
      {"gcc_ufs_phy_tx_symbol_0_clk", 0, 0, 0, 0, 0, 0, 0},
      {"gcc_ufs_phy_rx_symbol_0_clk", 0, 0, 0, 0, 0, 0, 0},
      {"gcc_ufs_phy_rx_symbol_1_clk", 0, 0, 0, 0, 0, 0, 0},
      { NULL, 0, 0, 0, 0, 0, 0, 0}
   } 
};

void ufs_bsp_clk_set (uint8_t hostid, uint32_t mode)
{
   BOOLEAN cur_clock_enabled = FALSE;
   EFI_STATUS eResult = EFI_SUCCESS;
   UINT8 i = 0; 
   UINT8 num_clocks = sizeof(UFS_CLOCK_LIST) / sizeof(UFS_CLOCK_INFO);
   UFS_CLOCK_INFO *cur_clock = NULL; 
   UFS_CLOCK_INFO *clock_list = NULL; 

   if (NULL == hUFS_Clock)
   {
      eResult = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID **)&hUFS_Clock);
      if ((EFI_SUCCESS != eResult) || (NULL == hUFS_Clock))
      {
          hUFS_Clock = NULL;
          ASSERT_EFI_ERROR(eResult);
      }

      // Set FORCE_MEM_CORE_ON=1 so that the ICE configuration is retained when the clock is gated
      HWIO_GCC_UFS_PHY_ICE_CORE_CBCR_OUTM(HWIO_GCC_UFS_PHY_ICE_CORE_CBCR_FORCE_MEM_CORE_ON_BMSK,
                                          (1 << HWIO_GCC_UFS_PHY_ICE_CORE_CBCR_FORCE_MEM_CORE_ON_SHFT));
   }

   if (NULL != hUFS_Clock) 
   {
      clock_list = (UFS_CLOCK_INFO *)&ufs_clocks_array[hostid]; 
      for (i = 0; i < num_clocks; i++) 
      {
         cur_clock = clock_list + i; 
         if(cur_clock->clock_name == NULL)
           continue;
		 
         if (cur_clock->clock_id == 0) 
         {
            eResult = hUFS_Clock->GetClockID(hUFS_Clock, cur_clock->clock_name,
                                             &cur_clock->clock_id);
            if (EFI_SUCCESS != eResult)
            {
               ASSERT_EFI_ERROR(eResult);
            }

            eResult = hUFS_Clock->EnableClock(hUFS_Clock, cur_clock->clock_id);          
            if (EFI_SUCCESS != eResult)
            {
               ASSERT_EFI_ERROR(eResult);
            }
         }

         switch (mode)
         {
            case UFS_CLOCK_MODE_OFF: 
               eResult = hUFS_Clock->DisableClock(hUFS_Clock, cur_clock->clock_id);
               if (EFI_SUCCESS != eResult)
               {
                  ASSERT_EFI_ERROR(eResult);
               }
               break; 

            case UFS_CLOCK_MODE_LOWSVS: 
            case UFS_CLOCK_MODE_SVS: 
            case UFS_CLOCK_MODE_NOM: 
            case UFS_CLOCK_MODE_TURBO: 
               eResult = hUFS_Clock->IsClockEnabled(hUFS_Clock, cur_clock->clock_id, &cur_clock_enabled);
               if (EFI_SUCCESS != eResult) 
               {
                  ASSERT_EFI_ERROR(eResult);
               }

               if (FALSE == cur_clock_enabled) 
               {
                  eResult = hUFS_Clock->EnableClock(hUFS_Clock, cur_clock->clock_id);          
                  if (EFI_SUCCESS != eResult)
                  {
                     ASSERT_EFI_ERROR(eResult);
                  }
               }
 
               if (cur_clock->freq[mode] != 0) 
               {
                  eResult = hUFS_Clock->SetClockFreqHz(hUFS_Clock, cur_clock->clock_id, cur_clock->freq[mode], 
                                                       EFI_CLOCK_FREQUENCY_HZ_AT_MOST, &cur_clock->freq[mode]);          
                  if (EFI_SUCCESS != eResult)
                  {
                     ASSERT_EFI_ERROR(eResult);
                  }
               }
               break; 

            default: 
               DEBUG((EFI_D_ERROR, "UFS Unsupported Clock mode\n"));
               break; 
         }  
      }
   }
}

ufs_bsp_err_type ufs_bsp_check_valid_operational_mode (uint8_t volt_corner, uint8_t gear)
{
   uint8_t i = 0; 
   uint8_t pm_entries = sizeof(ufs_pm_params) / sizeof (ufs_bsp_pm_info);

   for (i = 0; i < pm_entries; i++) {
      if (ufs_pm_params[i].volt_corner == volt_corner) {
         break; 
      }
   }

   if (i == pm_entries) {
      return UFS_BSP_ERR_INVALID_PARAM;  
   }

   if (ufs_pm_params[i].max_hs_gear_allowed >= gear) { 
      return UFS_BSP_NO_ERROR; 
   }

  return UFS_BSP_ERR_INVALID_PARAM;
}

ufs_bsp_err_type ufs_bsp_operational_mode_info (uint8_t curr_gear, void *caps)
{
   EFI_STORAGE_OP_MODE_CAPABILITIES *UfsCaps; 
   UINT8 i = 0; 

   if (caps == NULL) {
      return UFS_BSP_ERR_INVALID_PARAM;
   }

   UfsCaps = (EFI_STORAGE_OP_MODE_CAPABILITIES *)caps; 

   if (curr_gear < UFS_MAX_GEAR) {
      UfsCaps->NumSpeedLevels = curr_gear; 
   }
   else {
      UfsCaps->NumSpeedLevels = UFS_MAX_GEAR; 
   } 

   for (i = 0; i < VOLT_CORNER_MAX; i++) {
      if (ufs_pm_params[i].max_hs_gear_allowed == UFS_GEAR_INVALID) {
         UfsCaps->VoltCornerSupported[i] = 0; 
      }
      else {
         UfsCaps->VoltCornerSupported[i] = 1; 
      }
   }

   return UFS_BSP_NO_ERROR; 
}

ufs_bsp_err_type ufs_bsp_default_volt_corner (uint8_t hostid, uint8_t *volt_corner)
{
   (void)hostid; 

   if (volt_corner != NULL) {
      *volt_corner = VOLT_CORNER_NOM;
      return UFS_BSP_NO_ERROR; 
   }
   else {
      return UFS_BSP_ERR_INVALID_PARAM;
   }
}
    
void ufs_bsp_clk_hw_control (uint8_t hostid, uint8_t enable)
{
   if (hostid == 0) {
      HWIO_GCC_AGGRE_UFS_PHY_AXI_CBCR_OUTM(HWIO_GCC_AGGRE_UFS_PHY_AXI_CBCR_HW_CTL_BMSK,
                                           (enable << HWIO_GCC_AGGRE_UFS_PHY_AXI_CBCR_HW_CTL_SHFT));
      HWIO_GCC_UFS_PHY_AXI_CBCR_OUTM(HWIO_GCC_UFS_PHY_AXI_CBCR_HW_CTL_BMSK,
                                     (enable << HWIO_GCC_UFS_PHY_AXI_CBCR_HW_CTL_SHFT));
      HWIO_GCC_UFS_PHY_UNIPRO_CORE_CBCR_OUTM(HWIO_GCC_UFS_PHY_UNIPRO_CORE_CBCR_HW_CTL_BMSK,
                                             (enable << HWIO_GCC_UFS_PHY_UNIPRO_CORE_CBCR_HW_CTL_SHFT));
      HWIO_GCC_UFS_PHY_ICE_CORE_CBCR_OUTM(HWIO_GCC_UFS_PHY_ICE_CORE_CBCR_HW_CTL_BMSK,
                                          (enable << HWIO_GCC_UFS_PHY_ICE_CORE_CBCR_HW_CTL_SHFT));
      HWIO_GCC_UFS_PHY_PHY_AUX_CBCR_OUTM(HWIO_GCC_UFS_PHY_PHY_AUX_CBCR_HW_CTL_BMSK,
                                         (enable << HWIO_GCC_UFS_PHY_PHY_AUX_CBCR_HW_CTL_SHFT));
   }
}

void ufs_bsp_get_time_reg_values (uint8_t volt_corner, ufs_bsp_time_values *reg)
{
   uint32_t i = 0; 
   uint32_t pm_entries = sizeof(ufs_pm_params) / sizeof (ufs_bsp_pm_info);

   for (i = 0; i < pm_entries; i++) {
      if (ufs_pm_params[i].volt_corner == volt_corner) {
         break; 
      }
   }

   if (i == pm_entries) {
      return;  
   }

   reg->DME_MAX_1US = ufs_pm_params[i].time_vals.DME_MAX_1US;
   reg->PA_VS_40NS = ufs_pm_params[i].time_vals.PA_VS_40NS;
   reg->SYSCLK_1US = ufs_pm_params[i].time_vals.SYSCLK_1US; 
}

void ufs_bsp_autoH8 (uint8_t hostid, uint16_t idle_time_ms)
{
   if (hostid == 0) {
      // Enable HW clock control for UFS clocks
      ufs_bsp_clk_hw_control (hostid, 1);

      // Set AH8_CFG to enable the clock request feature 
      HWIO_REG_OUT(ufs_bsp_get_reg_baseaddress(hostid), UFS_MEM_AH8_CFG, 0x3c);

      // Set AH8 after time indicated
      HWIO_REG_OUT(ufs_bsp_get_reg_baseaddress(hostid), UFS_MEM_AHIT, (0xc00 | (idle_time_ms & 0x3ff)));
   }
}
    

void ufs_bsp_cache_op (void *addr, uint32_t len, uint32_t op) 
{
   if (cca_flag == HAL_IOMMU_DOMAIN_TYPE_INVALID) {
      if (GetConfigValue ("EnableUfsIOC", &cca_flag) != EFI_SUCCESS)
      {
         cca_flag = HAL_IOMMU_AARCH64_NON_CCA_DOMAIN_TYPE;
      }
   }

   if (cca_flag != HAL_IOMMU_AARCH64_CCA_DOMAIN_TYPE) {
      if (op & FLUSH) {
         WriteBackInvalidateDataCacheRange (addr, len);
      }

      if (op & INVAL) {
         InvalidateDataCacheRange (addr, len);
      }

      if (op & CLEAN) {
         WriteBackDataCacheRange (addr, len);
      }
   }
}

void ufs_bsp_busy_wait(uint32_t us)
{
   gBS->Stall(us);
}

void ufs_bsp_memory_barrier ()
{
   ArmDataMemoryBarrier();
}

uint32_t ufs_bsp_get_mphy_init_item_table (struct ufs_mphy_init_item **itm)
{
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      *itm = ufs_bsp_mphy_init_table_rumi;
      return sizeof(ufs_bsp_mphy_init_table_rumi)/sizeof(struct ufs_mphy_init_item);
   }
   else {
      *itm = ufs_bsp_mphy_init_table;
      return sizeof(ufs_bsp_mphy_init_table)/sizeof(struct ufs_mphy_init_item);
   }
}

uint32_t ufs_bsp_get_mphy_init_2_lane_item_table (struct ufs_mphy_init_item **itm)
{
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      *itm = ufs_bsp_mphy_2_lane_init_table_rumi;
      return sizeof(ufs_bsp_mphy_2_lane_init_table_rumi)/sizeof(struct ufs_mphy_init_item);
   }
   else {
      *itm = ufs_bsp_mphy_2_lane_init_table;
      return sizeof(ufs_bsp_mphy_2_lane_init_table)/sizeof(struct ufs_mphy_init_item);
   }
}

uint32_t ufs_bsp_get_mphy_eom_item_table (struct ufs_mphy_init_item **itm)
{
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return 0; 
   }
   else {
      *itm = ufs_bsp_mphy_eom_table;
      return sizeof(ufs_bsp_mphy_eom_table)/sizeof(struct ufs_mphy_init_item);
   }
}

uint32_t ufs_bsp_get_mphy_eom_2_lane_item_table (struct ufs_mphy_init_item **itm)
{
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return 0; 
   }
   else {
      *itm = ufs_bsp_mphy_2_lane_eom_table;
      return sizeof(ufs_bsp_mphy_2_lane_eom_table)/sizeof(struct ufs_mphy_init_item);
   }
}

uint32_t ufs_bsp_get_mphy_init_end_item_table (struct ufs_mphy_init_item **itm)
{
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return 0; 
   }
   else {
      *itm = ufs_bsp_mphy_init_end_table;
      return sizeof(ufs_bsp_mphy_init_end_table)/sizeof(struct ufs_mphy_init_item);
   }
}

// Start the PHY and wait for the PHY to be ready 
ufs_bsp_err_type ufs_bsp_mphy_start (uint8_t hostid)
{
   int32_t tout = UFS_PHY_PCS_READY_TIMEOUT;
   uintptr_t base_addr = ufs_bsp_get_reg_baseaddress(hostid); 

   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      HWIO_REG_OUT(base_addr, UFS_PHY_PHY_START, 1);
      ufs_bsp_busy_wait (10);

      while (HWIO_REG_IN(base_addr, QSERDES_COM_RESET_SM) != 0x3d) {
         if (tout-- == 0) {
            return UFS_BSP_DEVICE_ERROR;
         }
         ufs_bsp_busy_wait (1);
      }
   }
   else
   {
      HWIO_REG_OUTM (base_addr, UFS_MEM_UFS_PHY_PHY_START, 1, 1);
      ufs_bsp_busy_wait (10);

      while (!(HWIO_REG_IN(base_addr, UFS_MEM_UFS_PHY_PCS_READY_STATUS) & 0x01)) {
         if (tout-- == 0) {
            return UFS_BSP_DEVICE_ERROR;
         }
         ufs_bsp_busy_wait (1);
      }
   }

   return UFS_BSP_NO_ERROR;
}

void ufs_bsp_reset (uint8_t hostid)
{
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {

      // Reset and sleep 50 ms
      out_dword(HWIO_GE_DUT_RESET_REG_ADDR, 0x5f); 
      ufs_bsp_busy_wait (50000);

      // Release reset and sleep 50 ms
      out_dword(HWIO_GE_DUT_RESET_REG_ADDR, 0x0);
      ufs_bsp_busy_wait (50000);

      // Clock frequencies used
      out_dword(HWIO_GE_DUT_CLK_STATUS_SEL_REG_ADDR, 0x1);

      // Reset ICE fuses
      out_dword(HWIO_GE_DUT_UFS_ICE_CTRL_REG_ADDR, 0x0);
   }
   else
   {
      if (hostid == 0) {
         out_dword(HWIO_GCC_UFS_PHY_BCR_ADDR, 1);
         ufs_bsp_busy_wait(500);
         out_dword(HWIO_GCC_UFS_PHY_BCR_ADDR, 0); 
      }
   }
}

void ufs_bsp_post_link_init (uint8_t hostid)
{
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return;
   }

   HWIO_REG_OUT(ufs_bsp_get_reg_baseaddress(hostid), UFS_MEM_UFS_PHY_LINECFG_DISABLE, 0x02);   
}

void ufs_bsp_device_reset (uint8_t hostid)
{
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return;
   }

   if (hostid == 0) {
      out_dword(HWIO_TLMM_UFS_RESET_ADDR, 0); 
      ufs_bsp_busy_wait(10); 
      out_dword(HWIO_TLMM_UFS_RESET_ADDR, 1); 
      ufs_bsp_busy_wait(10); 
   }
}

// Allocate command descriptor, must be 128-byte aligned 
void *ufs_bsp_allocate_command_buf (size_t size)
{
   return UncachedAllocateAlignedPool(size, 128);
}

void  ufs_bsp_free_command_buf (void *pmem)
{
   if ( pmem == NULL )
      return;

   UncachedFreePool(pmem);
}

void *ufs_bsp_allocate_norm_buf (size_t size)
{
    VOID *mem;
    EFI_STATUS            status;
    status=gBS->AllocatePool(EfiBootServicesData,size,(VOID**)&mem);

    if (EFI_SUCCESS != status)
    {
        DEBUG((EFI_D_ERROR, "UFS: Allocate memory of size 0x%x     [FAILED]\n",size));
        return NULL;
    }
    return mem;
}

void  ufs_bsp_free_norm_buf (void *pmem)
{
    if ( pmem == NULL )
        return;

    gBS->FreePool(pmem);
}

void *ufs_bsp_allocate_xfer_buf (size_t size)
{
    return UncachedAllocatePool(size);
}

void  ufs_bsp_free_xfer_buf (void *pmem)
{
    if ( pmem == NULL )
        return;

    UncachedFreePool(pmem);
}

void ufs_bsp_get_platform_config (ufs_bsp_platform_config *cfg)
{
   EFI_STATUS                          eResult = EFI_SUCCESS;
   EFI_PLATFORMINFO_PROTOCOL           *hPlatformInfoProtocol;
   EFI_PLATFORMINFO_PLATFORM_INFO_TYPE PlatformInfo;
   uint32_t soc_emulation_type = 0;
   
   eResult = gBS->LocateProtocol(&gEfiPlatformInfoProtocolGuid, NULL,
     (VOID **) &hPlatformInfoProtocol);
   if (eResult != EFI_SUCCESS)
   {
     DEBUG((EFI_D_WARN, "Error: Failed to locate PlatformInfo protocol.\n"));
     goto ConfigEnd;
   }
   
   eResult = hPlatformInfoProtocol->GetPlatformInfo(hPlatformInfoProtocol,
     &PlatformInfo);
   if (eResult != EFI_SUCCESS)
   {
     DEBUG((EFI_D_WARN, "Error: GetPlatformInfo failed.\n"));
     goto ConfigEnd;
   }
   
   if (PlatformInfo.platform >= EFI_PLATFORMINFO_NUM_TYPES)
   {
     DEBUG((EFI_D_WARN, "Error: Unknown platform type (%d)\n", PlatformInfo.platform));
     eResult = EFI_PROTOCOL_ERROR;
     goto ConfigEnd; 
   }

   if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
   	g_platform = DALPLATFORMINFO_TYPE_RUMI;
   }

ConfigEnd:
   if (eResult != EFI_SUCCESS) {
      soc_emulation_type = in_dword(0x01fc8004) & 0x3; 

      /* 0 = Silicon, 1 = RUMI, 2 = Veloce, 3 = Virtio */
      if (soc_emulation_type == 1) 
      {
         g_platform = DALPLATFORMINFO_TYPE_RUMI; 
      }
   }

   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      cfg->slow_xfer = 1;
      cfg->core_skip = 0; 
      cfg->partial_init = 0; 
      cfg->core_turbo_switch=0;
   }
   else {
      /* VIRTIO or Silicon */
      cfg->slow_xfer = 0;
      cfg->core_skip = 1; 
      cfg->partial_init = 1; 
      cfg->core_turbo_switch=0;
   }

   cfg->refclk_freq = 38400000;
}

void ufs_bsp_get_default_config (uint8_t hostid, ufs_bsp_config *cfg)
{
   (void)hostid; 

   memset(cfg, 0x00, sizeof(ufs_bsp_config)); 

   cfg->init_speed_params.enable_hs = 1; 
   cfg->init_speed_params.num_lanes = 2; 
   cfg->init_speed_params.rate = RATE_B;

   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      cfg->init_speed_params.gear = 1;
   }
   else {
      cfg->init_speed_params.gear = 4;  
   }

   memscpy (&cfg->perf_speed_params, sizeof(cfg->perf_speed_params),
           &cfg->init_speed_params, sizeof(ufs_bsp_speed_config)); 

   cfg->timeout_values.fdevice_init_timeout_us = DEV_INIT_TIMEOUT;
   cfg->timeout_values.utrd_poll_timeout_us = UTRD_POLL_TIMEOUT;

   cfg->fua_value = 0;

   cfg->num_linkstartup_retries = NUM_LINK_STARTUP_RETRIES; 
}

ufs_bsp_err_type ufs_bsp_get_dt_config (uint8_t hostid, ufs_bsp_config *cfg)
{
   char fdt_node_str[DT_PATH_LEN] = {0};
   EFI_STATUS status = EFI_SUCCESS; 
   fdt_node_handle node; 
   int result = 0;  
   uint32 address_info[2];

   status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL, (VOID **)&DtbProtocol);
   if ((EFI_SUCCESS != status) || (NULL == DtbProtocol)) {
      DEBUG((EFI_D_ERROR, "Failed to Locate DTBExtnProtocol 0x%x\n", status));
      return UFS_BSP_ERR_DT; 
   }
   else {
      snprintf (fdt_node_str, DT_PATH_LEN, "/soc/ufs%d", hostid);

      result = DtbProtocol->FdtGetNodeHandle (&node, fdt_node_str); 
      if (result == 0) {
         result = DtbProtocol->FdtGetUint32PropList(&node, "reg", address_info, sizeof(address_info)); 
         if (result == 0) {
            // Use the UFS base address in device tree to determine whether it is valid
            if (address_info[0] != ufs_bsp_get_reg_baseaddress (hostid)) {
               return UFS_BSP_ERR_INVALID_PARAM;
            }
         }
         else {
            goto DTConfigExit;  
         }

         result = DtbProtocol->FdtGetUint8Prop (&node, "FUA_Value", &cfg->fua_value);
         if (result) {
            goto DTConfigExit;  
         }

         result = DtbProtocol->FdtGetUint8Prop (&node, "LinkStartupRetryCount", &cfg->num_linkstartup_retries);
         if (result) {
            goto DTConfigExit; 
         }
      }
      else {
         goto DTConfigExit;  
      }

      snprintf (fdt_node_str, DT_PATH_LEN, "/soc/ufs%d/timeout_values", hostid); 
      result = DtbProtocol->FdtGetNodeHandle (&node, fdt_node_str);   
      if (result == 0) {
         result = DtbProtocol->FdtGetPropValuesOfNode (&node, "ww", &cfg->timeout_values, sizeof(ufs_bsp_timeout_config));
         if (result) {
            goto DTConfigExit;
         }
      }
      else {
         goto DTConfigExit; 
      }

      snprintf (fdt_node_str, DT_PATH_LEN, "/soc/ufs%d/init_speed_params", hostid); 
      result = DtbProtocol->FdtGetNodeHandle (&node, fdt_node_str); 
      if (result == 0) {
         result = DtbProtocol->FdtGetPropValuesOfNode (&node, "bbbb", &cfg->init_speed_params, sizeof(ufs_bsp_speed_config));
         if (result) {
            goto DTConfigExit; 
         }
      }
      else {
         goto DTConfigExit; 
      }

      snprintf (fdt_node_str, DT_PATH_LEN, "/soc/ufs%d/perf_speed_params", hostid); 
      result = DtbProtocol->FdtGetNodeHandle (&node, fdt_node_str); 
      if (result == 0) {
         result = DtbProtocol->FdtGetPropValuesOfNode (&node, "bbbb", &cfg->perf_speed_params, sizeof(ufs_bsp_speed_config)); 
         if (result) {
            goto DTConfigExit; 
         }
      }
      else {
         goto DTConfigExit; 
      }
   }

DTConfigExit:
   if (result) {
      DtbProtocol = NULL; 
      return UFS_BSP_ERR_DT; 
   }
   else {
      // RUMI is limited to gear 1
      if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
         cfg->init_speed_params.gear = 1;
         cfg->perf_speed_params.gear = 1; 
      }

      return UFS_BSP_NO_ERROR;
   }
}

uintptr_t ufs_bsp_get_reg_baseaddress (uint8_t hostid)
{
   if (0 == hostid) 
   {
      return (uintptr_t) 0x1d80000;
   }
   else
   {
      return 0x0; 
   }
}

void ufs_bsp_log (char *str, ufs_bsp_log_level level)
{
   if (level == UFS_LOG_ERROR)
   {
      DEBUG((EFI_D_ERROR, "%a\n", str));
   }
   else if (level == UFS_LOG_INFO)
   {
      DEBUG((EFI_D_INFO, "%a\n", str));
   }
}

ufs_bsp_err_type ufs_bsp_volt_set(uint8_t hostid, ufs_bsp_regulator_mode mode)
{
   static npa_client_handle vcc_client_handle = NULL;
   static npa_client_handle vccq_client_handle = NULL;
   static npa_client_handle vdda_client_handle = NULL;
   static npa_client_handle vdda_core_client_handle = NULL;

   if (hostid == 0) {
      if (vcc_client_handle == NULL) {
         vcc_client_handle = npa_create_sync_client(PMIC_NPA_GROUP_ID_UFS0_VCC, "ufs0_vcc", NPA_CLIENT_REQUIRED); 
         if (vcc_client_handle == NULL) {
            return UFS_BSP_ERR_PMIC;
         }
      }
      if (vccq_client_handle == NULL) {
         vccq_client_handle = npa_create_sync_client(PMIC_NPA_GROUP_ID_UFS0_VCCQ, "ufs0_vccq", NPA_CLIENT_REQUIRED); 
         if (vccq_client_handle == NULL) {
            return UFS_BSP_ERR_PMIC;
         }
      }
      if (vdda_client_handle == NULL) {
         vdda_client_handle = npa_create_sync_client(PMIC_NPA_GROUP_ID_UFS0_VDDA, "ufs0_vdda", NPA_CLIENT_REQUIRED); 
         if (vdda_client_handle == NULL) {
            return UFS_BSP_ERR_PMIC;
         }
      }
      if (vdda_core_client_handle == NULL) {
         vdda_core_client_handle = npa_create_sync_client(PMIC_NPA_GROUP_ID_UFS0_VDDA_CORE, "ufs0_vdda_core", NPA_CLIENT_REQUIRED); 
         if (vdda_core_client_handle == NULL) {
            return UFS_BSP_ERR_PMIC;
         }
      }
   }
   else {
      return UFS_BSP_ERR_INVALID_PARAM;
   }

   /* Turn all UFS regulators ON */
   if (mode == UFS_BSP_REGULATORS_ON) {
      npa_issue_required_request(vcc_client_handle, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
      npa_issue_required_request(vccq_client_handle, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
      npa_issue_required_request(vdda_client_handle, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
      npa_issue_required_request(vdda_core_client_handle, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
   }
   /* Lower Vcc to 0V for UFS device sleep */
   else if (mode == UFS_BSP_REGULATORS_SLEEP) {
      npa_issue_required_request(vcc_client_handle, PMIC_NPA_MODE_ID_GENERIC_OFF);
   }
   else if (mode == UFS_BSP_REGULATORS_OFF) {
      npa_issue_required_request(vdda_core_client_handle, PMIC_NPA_MODE_ID_GENERIC_STANDBY);
      npa_issue_required_request(vdda_client_handle, PMIC_NPA_MODE_ID_GENERIC_OFF);
      npa_issue_required_request(vccq_client_handle, PMIC_NPA_MODE_ID_GENERIC_STANDBY);
      npa_issue_required_request(vcc_client_handle, PMIC_NPA_MODE_ID_GENERIC_OFF);
   } 
   else
   {
      return UFS_BSP_ERR_FEATURE_UNSUPPORTED; 
   }

   return UFS_BSP_NO_ERROR;
}

ufs_bsp_err_type ufs_bsp_configure_smmu()
{
   EFI_STATUS Status = EFI_SUCCESS;
   static boolean configure_completed = FALSE; 
   static HAL_IOMMU_fptable_t *fp_table = NULL;
   VOID *ufs_mem_domain_hdl;
   EFI_HAL_IOMMU_PROTOCOL *Iommu = NULL;

   if (configure_completed) {
      return UFS_BSP_NO_ERROR; 
   }

   /* Locate UEFI IOMMU protocol */
   if (fp_table == NULL) {
      Status = gBS->LocateProtocol(&gEfiHalIommuProtocolGuid,
                                   NULL,
                                   (VOID **)&Iommu);
      if (Status != EFI_SUCCESS) {
         DEBUG((EFI_D_ERROR, "UFS IOMMU LocateProtocol failed 0x%x\n", Status));
         return UFS_BSP_DEVICE_ERROR;
      }

      Iommu->_HAL_IOMMU_protocol_init(&fp_table);
   }

   if (cca_flag == HAL_IOMMU_DOMAIN_TYPE_INVALID) {
      if (GetConfigValue ("EnableUfsIOC", &cca_flag) != EFI_SUCCESS)
      {
         cca_flag = HAL_IOMMU_AARCH64_NON_CCA_DOMAIN_TYPE;
      }
   }

   /* Create Domain for UFS */
   if (HAL_IOMMU_ERR_OK != fp_table->domain_create_func(&ufs_mem_domain_hdl)) {
      DEBUG((EFI_D_ERROR, "UFS IOMMU domain create failed\n"));
      return UFS_BSP_DEVICE_ERROR;
   }

   /* Attach UFS device to the domain */
   if (HAL_IOMMU_ERR_OK != fp_table->config_bypass_domain_func(ufs_mem_domain_hdl, cca_flag))
   {
      DEBUG((EFI_D_ERROR, "UFS IOMMU domain configure failed\n"));
      return UFS_BSP_ERR_FEATURE_UNSUPPORTED;
   }

   if (HAL_IOMMU_ERR_OK != fp_table->domain_attach_func(ufs_mem_domain_hdl, (void *)"UFS_MEM", 0x0, 0x0))
   {
      DEBUG((EFI_D_ERROR, "UFS IOMMU domain attach failed\n"));
      return UFS_BSP_DEVICE_ERROR;
   }

   configure_completed = TRUE; 

   return UFS_BSP_NO_ERROR;
}

ufs_bsp_err_type ufs_bsp_get_vbatt (uint32 *volt_mv)
{
   return UFS_BSP_ERR_FEATURE_UNSUPPORTED;
}

void ufs_bsp_set_shared_info (uint8_t hostid, ufs_bsp_hlos_shared_info *info)
{
   HWIO_REG_OUT (ufs_bsp_get_reg_baseaddress(hostid), UFS_MEM_DEBUG_SPARE_CFG, info->ufs_version);
}

