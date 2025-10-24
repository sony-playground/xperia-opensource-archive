/**********************************************************************
* UfsLoaderBspLib.c
*
* Board support file for XBL Loader
*
* Copyright (c) 2013-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
* Qualcomm Technologies Proprietary and Confidential.
* 
*
**********************************************************************/

/*=======================================================================
                        Edit History

YYYY-MM-DD   who     what, where, why
---------------------------------------------------------------------- 
2022-08-24   rn      Remove /storage/ from path in DTB tree
2022-04-15   sa      Added BlockIo2 for multiple doorbells.
2022-03-21   cm      Add API to return turbo mode support info
2022-02-23   sa      Move from Setting to Library Folder.
2022-02-05   sa      Init busywait timer.
2021-11-05   jt      Add refclk_freq to platform_config 
2021-10-27   jt      Disable partial init for device programmer 
2021-10-07   jt      Change error code when battery status API fails 
2021-09-08   jt      Add ability to check battery status 
2021-08-13   jt      Add device tree support
2020-06-29   jt      Update logging function 
2020-03-31   jt      Add power management functions  
2019-10-22   jt      Remove voltage switching
2019-09-10   jt      Add dcache_clean for ufs_bsp_cache_op 
2019-07-22   jt      Add SMMU configuration API 
2019-02-01   jt      Add UFS 3.0 support 
2018-11-29   jt      Add ufs_bsp_volt_set  
2019-01-14   yps     Added dcache inval for ufs_bsp_cache_op
2018-11-01   jt      Mask off lowest 2 bits for SOC emulation type  
2018-09-24   jt      Move PHY settings to its own file 
2018-09-05   jt      Restructure PHY initialization 
2018-07-24   jt      HPG updates for Hana v2 
2018-05-30   jt      HPG v7.0 PHY updates for Hana/Poipu 
2018-04-26   jt      More PHY init updates for Hana/Poipu 
2018-04-11   jt      Additional PHY init updates for Hana/Poipu  
2018-02-13   jt      PHY init updates for Hana/Poipu 
2018-01-25   vk      Remove UEFI libs
2017-07-31   jt      Add log function 
2017-06-20   jt      Enable clocks for RUMI  
2017-06-06   jt      Adapt for Hana
2017-04-08   jt      Add GCC reset for silicon 
2017-02-10   jt      Update PHY init sequence for Hynix part  
2017-01-25   jt      Add UFS device reset
2016-11-01   jt      Add reset function 
2016-10-21   jt      Enable HS for RUMI 
2016-09-14   jt      AANG RUMI PHY init updates  
2016-08-22   jt      PHY init updates from 8998v2 
2016-07-22   jt      Adapt for Napali 
2015-06-15   rh      Disable the PHY from decoding the LCC sequence
2015-02-12   rh      8996 V1 PHY workaround
2014-09-17   rh      Adapted for 8996 
2014-07-16   rh      Adding cache operation
2014-06-02   rh      PHY init adjustment
2014-03-24   rh      Adapt the BSP file for 8994
2013-10-30   rh      Clock regime function cleanup
2013-10-30   rh      More accurate delay added
2013-06-19   rh      Initial creation
===========================================================================*/

#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/ArmLib.h>
#include "HALbootHWIO.h"
#include <HALhwio.h>
#include "UfsHwioAll.h"
#include "aang_phy_hwio.h"
#include "UfsPhySequence.h"
#include "Clock.h"
#include "voltage_level.h"
#include "DDIPlatformInfo.h"

#include "DALSys.h"
#include "boot_logger.h"
#include "busywait.h"
#include <stdio.h>
#include <DTBExtnLib.h>

#include "pm_chg.h"

#define UFS_PHY_PCS_READY_TIMEOUT           1000
#define REQUEST_LIST_BUFFER_SIZE            4096  
#define TOTAL_UTRD_LENGTH                   (32 * 32)
//__attribute__((section(".bss.BOOT_OCIMEM_PAGE_TABLE_ZONE"))) char ALIGN(4*1024) transfer_request_list_buf[REQUEST_LIST_BUFFER_SIZE];      
char transfer_request_list_buf[REQUEST_LIST_BUFFER_SIZE];      

DalPlatformInfoPlatformType g_platform;
ClockHandle clock_handle;
UFS_CLOCK_INFO ufs_clk_info = {"ufs_phy", 0, {0}};
bool bClockInit = FALSE;
boolean busywait_timer_inited = FALSE;

bool ufs_bsp_clk_init()
{
   ClockResult eResult = CLOCK_SUCCESS;

   eResult = Clock_Attach(&clock_handle, NULL);
   if (eResult != CLOCK_SUCCESS)
   {
      return FALSE;
   }

   eResult = Clock_GetId(clock_handle,
                         ufs_clk_info.clock_name,
                         (ClockIdType*)&ufs_clk_info.clock_id);
   if (eResult != CLOCK_SUCCESS)
   {
      return FALSE;
   }

   bClockInit = TRUE;

   return TRUE;
}

void ufs_bsp_clk_set (uint8_t hostid, uint32_t mode)
{
   (void) hostid;

   if (!bClockInit)
   {
      if (!ufs_bsp_clk_init())
      {
         return;
      }
   }

   if (mode == UFS_CLOCK_MODE_OFF) {
      (void) Clock_Disable(clock_handle, ufs_clk_info.clock_id);
   }
   else if (mode == UFS_CLOCK_MODE_ON) {
      (void) Clock_SetFrequency(clock_handle,
                                ufs_clk_info.clock_id,
                                RAIL_VOLTAGE_LEVEL_NOM,
                                CLOCK_FREQUENCY_FMAX,
                                NULL);
      (void) Clock_Enable(clock_handle, ufs_clk_info.clock_id);
   }
}

ufs_bsp_err_type ufs_bsp_check_valid_operational_mode (uint8_t volt_corner, uint8_t gear)
{
   (void)volt_corner; 
   (void)gear; 

   return UFS_BSP_ERR_FEATURE_UNSUPPORTED; 
}

ufs_bsp_err_type ufs_bsp_operational_mode_info (uint8_t curr_gear, void *caps)
{
   (void)curr_gear;
   (void)caps; 

   return UFS_BSP_ERR_FEATURE_UNSUPPORTED; 
}

ufs_bsp_err_type ufs_bsp_default_volt_corner (uint8_t hostid, uint8_t *volt_corner)
{
   (void)hostid; 
   (void)volt_corner; 

   return UFS_BSP_ERR_FEATURE_UNSUPPORTED; 
}

void ufs_bsp_clk_hw_control (uint8_t hostid, uint8_t enable)
{
   (void)hostid; 
   (void)enable; 
}

void ufs_bsp_get_time_reg_values (uint8_t volt_corner, ufs_bsp_time_values *reg)
{
   (void)volt_corner; 
   (void)reg;
}

void ufs_bsp_autoH8 (uint8_t hostid, uint16_t idle_time_ms)
{
   (void)hostid; 
   (void)idle_time_ms; 
}

void ufs_bsp_enable_symbol_clk (void)
{
}

/* A utility function to get the sleep timetick */
static uint32 Clock_GetSclkTimetick()
{
   volatile uint32_t curr_count;
   uint32_t last_count;  
   
   /*Grab current time count*/
   curr_count = HWIO_IN(MPM_SLEEP_TIMETICK_COUNT_VAL);
   
   if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
      return curr_count;
   }
   
   
   /*Keep grabbing the time until a stable count is given*/
   do 
   {
     last_count = curr_count;
     curr_count = HWIO_IN(MPM_SLEEP_TIMETICK_COUNT_VAL);
   } while (curr_count != last_count &&
            g_platform != DALPLATFORMINFO_TYPE_RUMI &&
            g_platform != DALPLATFORMINFO_TYPE_VIRTIO );
   
   return curr_count;
}

// Maximum delay is 134s
void ufs_bsp_busy_wait(uint32_t us)
{
#if 0  
   uint32_t pause_cycle = us * 32 / 1000 + us * 768 / 1000000;
   uint32_t now;

   // Need to check if there is a case of wrapping around
   now = Clock_GetSclkTimetick();
   while( Clock_GetSclkTimetick() - now <= pause_cycle);
#endif
   if(FALSE == busywait_timer_inited)
   {
     busywait_init();
     busywait_timer_inited = TRUE;
   }
   busywait(us);   
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
         if (!bClockInit)
         {
            if (!ufs_bsp_clk_init())
            {
               return;
            }
         }

         (void) Clock_Reset(clock_handle,
                            ufs_clk_info.clock_id,
                            CLOCK_RESET_ASSERT);
         ufs_bsp_busy_wait(500);
         (void) Clock_Reset(clock_handle,
                            ufs_clk_info.clock_id,
                            CLOCK_RESET_DEASSERT); 
      }

   }
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

void ufs_bsp_cache_op (void *addr, uint32_t len, uint32_t op) 
{
   if (op & FLUSH) {
      WriteBackInvalidateDataCacheRange(addr, len);
   }
   if (op & INVAL) {
      InvalidateDataCacheRange(addr, len);
   }
   if (op & CLEAN) {
      WriteBackDataCacheRange(addr, len); 
   }
}

void ufs_bsp_memory_barrier ()
{
   ArmDataMemoryBarrier();
}

void *ufs_bsp_allocate_command_buf (size_t size)
{
   /* As we only expect 1 queued request at a time in loader,
      the command buffer should be immediately after all the UTRD.
      The UTRD is at a 1KB aligned address from the Transfer request list buffer */
   (void)size;
   void *mem = (void *)((((uint64_t)transfer_request_list_buf + 1023) & ~((uint64_t)1023)) + TOTAL_UTRD_LENGTH); 
   return mem; 
}

void ufs_bsp_free_command_buf (void *pmem)
{
  (void) pmem;
}

void *ufs_bsp_allocate_norm_buf (size_t size)
{
   (void) size;
   void *mem = transfer_request_list_buf;
   return mem;
}

void  ufs_bsp_free_norm_buf (void *pmem)
{
   (void) pmem;
}

void *ufs_bsp_allocate_xfer_buf (size_t size)
{
   (void) size;
   void *mem = transfer_request_list_buf;
   return mem;
}

void  ufs_bsp_free_xfer_buf (void *pmem)
{
   (void) pmem;
}

void ufs_bsp_get_platform_config (ufs_bsp_platform_config *cfg)
{
   uint32_t soc_emulation_type = 0; 

   // __FIX__SDM845:  substitute non DAL platforminfo api
   g_platform = DalPlatformInfo_Platform();

   /* If DAL API doesn't work, query the SOC emulation type register */
   if (g_platform == DALPLATFORMINFO_TYPE_UNKNOWN) 
   {
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

      /* For ramdump, UFS is already initialized in XBL_SC, so init operations can be skipped */
      #if defined(BOOT_RAMDUMP_ENABLE) && !defined(FEATURE_DEVICEPROGRAMMER_IMAGE)
         cfg->core_skip = 1; 
      #else 
         cfg->core_skip = 0; 
      #endif

      #ifdef FEATURE_DEVICEPROGRAMMER_IMAGE
         cfg->partial_init = 0; 
      #else
         cfg->partial_init = 1; 
      #endif
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

   cfg->num_linkstartup_retries = NUM_LINK_STARTUP_RETRIES; 

   cfg->battery_threshold_mv = BATTERY_THRESHOLD_MV; 
}

ufs_bsp_err_type ufs_bsp_get_dt_config (uint8_t hostid, ufs_bsp_config *cfg)
{
   boolean enable_logging = FALSE; 
   char fdt_node_str[DT_PATH_LEN] = {0};
   fdt_node_handle node; 
   int result = 0; 
   void *fdt_handle = NULL;  
   uint32 address_info[2];

   snprintf (fdt_node_str, DT_PATH_LEN, "/soc/ufs%d", hostid);

   result = fdt_get_blob_handle (&fdt_handle, 0);

   if ((0 == result) && (NULL != fdt_handle)) {
      result = fdt_get_node_handle (&node, fdt_handle, fdt_node_str); 
      if (0 == result) {
         result = fdt_get_uint32_prop_list (&node, "reg", address_info, sizeof(address_info));
         if (result) {
            goto DTConfigExit; 
         }
         else {
            // Use the UFS base address in device tree to determine whether it is valid
            if (address_info[0] != ufs_bsp_get_reg_baseaddress (hostid)) {
               return UFS_BSP_ERR_INVALID_PARAM;
            }
         }

         fdt_get_uint8_prop (&node, "EnableLogging", &enable_logging); 

         result = fdt_get_uint8_prop (&node, "LinkStartupRetryCount", &cfg->num_linkstartup_retries);
		 
         if (result) {
            goto DTConfigExit; 
         }

         result = fdt_get_uint32_prop (&node, "BatteryThresholdMv", &cfg->battery_threshold_mv); 
         if (result) {
            goto DTConfigExit; 
         }
      }
      else {
         goto DTConfigExit;
      }

      snprintf (fdt_node_str, DT_PATH_LEN, "/soc/ufs%d/timeout_values", hostid); 
      result = fdt_get_node_handle (&node, fdt_handle, fdt_node_str);   
      if (0 == result) {
         result = fdt_get_prop_values_of_node (&node, "ww", &cfg->timeout_values, sizeof(ufs_bsp_timeout_config));
         if (result) {
            goto DTConfigExit;
         }
      }
      else {
         goto DTConfigExit; 
      }

      snprintf (fdt_node_str, DT_PATH_LEN, "/soc/ufs%d/init_speed_params", hostid); 
      result = fdt_get_node_handle (&node, fdt_handle, fdt_node_str); 

      if ((0 == result) && (NULL != fdt_handle)) {
         result = fdt_get_prop_values_of_node (&node, "bbbb", &cfg->init_speed_params, sizeof(ufs_bsp_speed_config));
         if (result) {
            goto DTConfigExit; 
         }
      }
      else {
         goto DTConfigExit; 
      }

      snprintf (fdt_node_str, DT_PATH_LEN, "/soc/ufs%d/perf_speed_params", hostid); 
      result = fdt_get_node_handle (&node, fdt_handle, fdt_node_str); 

      if ((0 == result) && (NULL != fdt_handle)) {
         result = fdt_get_prop_values_of_node (&node, "bbbb", &cfg->perf_speed_params, sizeof(ufs_bsp_speed_config)); 
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
      return UFS_BSP_ERR_DT; 
   }
   else {
      // RUMI is limited to gear 1
      if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
         cfg->init_speed_params.gear = 1;
         cfg->perf_speed_params.gear = 1; 
      }

      if (enable_logging) {
          char log_str[DT_LOG_STR_LEN] = {0};
          snprintf(log_str, DT_LOG_STR_LEN, "UFS Device Tree Settings"); 
          boot_log_message(log_str); 

          memset(log_str, 0x00, DT_LOG_STR_LEN); 
          snprintf(log_str, DT_LOG_STR_LEN, "UFS Init Speed: HS Enabled %d, Gear %d %d Lane Rate %d", 
                   cfg->init_speed_params.enable_hs, cfg->init_speed_params.gear, cfg->init_speed_params.num_lanes, 
                   cfg->init_speed_params.rate);
          boot_log_message(log_str); 
          snprintf(log_str, DT_LOG_STR_LEN, "UFS Perf Speed: HS Enabled %d, Gear %d %d Lane Rate %d", 
                   cfg->perf_speed_params.enable_hs, cfg->perf_speed_params.gear, cfg->perf_speed_params.num_lanes, 
                   cfg->perf_speed_params.rate); 
          boot_log_message(log_str); 

          memset(log_str, 0x00, DT_LOG_STR_LEN); 
          snprintf(log_str, DT_LOG_STR_LEN, "UFS Timeouts(us): fDeviceInit %d, UTRD Poll %d", 
                   cfg->timeout_values.fdevice_init_timeout_us, cfg->timeout_values.utrd_poll_timeout_us); 
          boot_log_message(log_str);

          memset(log_str, 0x00, DT_LOG_STR_LEN); 
          snprintf(log_str, DT_LOG_STR_LEN, "UFS: BatteryThreshold %d mV", cfg->battery_threshold_mv); 
          boot_log_message(log_str); 
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
   (void) level;
   boot_log_message(str); 
}

ufs_bsp_err_type ufs_bsp_volt_set(uint8_t hostid, ufs_bsp_regulator_mode mode)
{
   (void)hostid;
   (void)mode; 

   return UFS_BSP_ERR_FEATURE_UNSUPPORTED; 
}

ufs_bsp_err_type ufs_bsp_configure_smmu()
{
   return UFS_BSP_ERR_FEATURE_UNSUPPORTED; 
}

ufs_bsp_err_type ufs_bsp_get_vbatt (uint32 *volt_mv)
{
   #if defined(FEATURE_DEVICEPROGRAMMER_IMAGE) || defined(BOOT_RAMDUMP_ENABLE)
        return UFS_BSP_ERR_FEATURE_UNSUPPORTED;
   #else 
      if (g_platform == DALPLATFORMINFO_TYPE_RUMI) {
         return UFS_BSP_ERR_FEATURE_UNSUPPORTED; 
      }

      if (pm_chg_get_vbatt(volt_mv) != PM_ERR_FLAG_SUCCESS) {
         return UFS_BSP_ERR_FEATURE_UNSUPPORTED;
      }
    
      return UFS_BSP_NO_ERROR; 
   #endif
}

