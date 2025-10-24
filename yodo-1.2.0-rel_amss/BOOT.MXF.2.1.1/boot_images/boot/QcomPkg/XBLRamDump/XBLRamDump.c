/** @file XBLRamDump.c
  Top-Level Logic for XBLRamDump.c

  Copyright (c) 2014-2017, 2019-2022 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/06/22   rama    Clear minidump cookie if SDI pass 1 fails
 08/24/22   yps     Invalidate DATA ZI region before re-enter ramdump 
 08/01/22   nitesh  Moved Uncached heap before media_hw_init()
 07/18/22   yps     Return false if display init failed
 07/18/22   ck      Added MHI to config context
 07/08/22   batta   Added chipinfo init and bootslvcom init in system initialization.
 07/02/22   ck      Added missing return value checks in XBLRamdumpInit
 05/24/22   rama    Error handling in XBLRamdumpMain
 05/18/22   rama    Move dal_if to mem_if
 03/31/22   yps     Fixed USB PIPO issue
 02/09/22   ck      Updated heap function names
 01/19/22   rama    Call fdt_set_blob_handle before platforminfo_init. dt required for smem init
 10/25/21   rama    Add blacklist_if to config_context_global_values
 07/02/21   rama    initialize partition ID to NULL
 06/18/21   yps     Change post rd action for usb flashless dump
 06/16/21   ds      clear dload cookie before reset
 06/02/21   ds      minidump changes
 04/15/21   ds      DTB init
 04/03/21   ds      Initialize platforminfo with platforminfo core implementation
 02/24/21   yps     Enabled Raw ramdump
 02/16/21   ds      External Heap changes
 12/23/20   rama    Removed CONFIG_CONTEXT_BUILD_TYPE from config_context_global_values
 12/01/20   yps     enable uart log for ramdump
 05/29/20   rama    boot_dload_transition_pbl_forced_dload call with config context
 05/10/20   ds      move to edk2 arm mmu/cache lib
 04/05/20   rama    Added qusb interface table.
 03/18/20   rama    Removed boothw_target.h
 01/22/19   yps     Add ramdump function parameter
 09/06/17   yps     Remove efs_boot_initialize
 08/10/17   yps     Initialize ramdump data zi region
 05/02/17   yps     Added Dal init and init display only once
 05/09/17   sj      Added the logic to enable display if battery threshold match
 04/27/17   kpa     Update dalsys free api argument.
 05/19/16   kpa     Added support for Display
 09/10/15   kpa     Use dcache_flush_region instead of mmu_flush_cache.
 08/24/15   ck      Added logic to enter PBL EDL if ramdump is not allowed
 09/30/14   ck      efs_boot_initialize must be called before any storage functions
 08/08/14   ck      Added boot_shared_functions_consumer.h
 07/28/14   ck      Initial revision

=============================================================================*/
#include <string.h>
#include <HALhwio.h>
#include <HALbootHWIO.h>
#include "boot_target.h"
#include "boot_sahara.h"
#include "DALSys.h"
#include "boot_crashdump.h"
#include "boot_reset_if.h"
#include "BootDisplay.h"
#include "ipa_boot.h"
#include "boot_logger_uart.h"
#include <boot_qusb_al_bulk_if.h>
#include <boot_framework.h>
#include <boot_edk2_cache_if.h>
#include <boot_pmic_if.h>
#include <boot_logger_if.h>
#include <boot_config_context.h>
#include <boot_dal_if.h>
#include <boot_memory_mgr_dal.h>
#include <boot_crypto_if.h>
#include <boot_timer_hw_if.h>
#include <boot_timer_if.h>
#include <boot_memory_mgr_if.h>
#include <boot_busywait_if.h>
#include <boot_clk_if.h>
#include <boot_coldplug_if.h>
#include <boot_ddr_info_if.h>
#include <boot_efs_if.h>
#include <boot_qusb_ldr_if.h>
#include <boot_statistics_if.h>
#include <boot_smem_if.h>
#include <boot_uart_if.h>
#include <boot_visual_indication_if.h>
#include <boot_edk2_mmu_if.h>
#include <boot_edk2_armlib_if.h>
#include <pbl_sbl_shared.h>
#include <boot_heap.h>
#include <boot_seclib_if.h>
#include <boot_media_interface_if.h>
#include <boot_ramdump_if.h>
#include <ramdump_format_if.h>
#include <boot_dload_debug.h>
#include <boot_block_dev.h>
#include <boot_hfat_dev.h>
#include <boot_ramdump_table_if.h>
#include <boot_sahara_dispatch_tbl.h>
#include <boot_flashless_sahara.h>
#include <boot_shared_imem_cookie.h>
#include <boot_sahara_status_map_if.h>
#include <boot_platforminfo_if.h>
#include <DTBExtnLib.h>
#include <boot_dbginfo_if.h>
#include <boot_blacklist_if.h>
#include <boot_whitelist_if.h>
#include <boot_nvme_if.h>
#include <boot_slvcom_if.h>
#include <boot_chipinfo_if.h>
#include <boot_xrc_if.h>
#include <error_handler.h>
#include <boot_mhi_if.h>
#include <boot_minidump.h>

/* SONY_BEGIN(Ramdumper support) */
#if (defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP))
#include "boot_ramdump.h"
#include "../../SomcPkg/Platform/SomcQcomCmnPkg/Include/Library/XResetReasonLibVendor.h"
#endif /* (FEATURE_XBOOT && FEATURE_SONY_RAMDUMP) */
/* SONY_END(Ramdumper support) */

typedef enum
{
  RD_ACTION_REBOOT                  = 0x0,
  RD_ACTION_REBOOT_ON_PASS          = 0x1,
  RD_ACTION_REBOOT_ON_FAIL          = 0x2,
  RD_ACTION_CONTINUE                = 0x3,
  RD_ACTION_REBOOT_ON_FORMAT_STATUS = 0x4,
  RD_ACTION_MAX,
  RD_ACTION_FORCE_ALIGN             = 0x7FFFFFFF
} post_ramdump_action_type;

typedef enum
{
  RD_FORMAT_RAW         = 0x0,
  RD_FORMAT_HFAT        = 0x1,
  RD_FORMAT_SAHARA      = 0x2,
  RD_FORMAT_MAX,
  RD_FORMAT_FORCE_ALIGN = 0x7FFFFFFF
} ramdump_format_type;

typedef struct
{
  boot_media_type          boot_media;           /* Boot Media */
  boot_media_type          ramdump_media;        /* Media used for dump */
  ramdump_format_type      ramdump_format;       /* Ramdump Format */
  post_ramdump_action_type post_ramdump_action;  /* Perform action after RAM dump */
  bl_error_boot_type       status;               /* Status */
} ramdump_config_table_entry;

extern uintnt Image$$RAMDUMP_DATA_ZI$$Base[];
extern uintnt Image$$RAMDUMP_DATA_ZI$$Length[];
extern uintnt  Image$$STACK$$Base[];
extern uintnt  Image$$STACK$$Length[];
extern uintnt  Image$$RAMDUMP_DATA_RW$$Base[];
extern uintnt  Image$$RAMDUMP_DATA_RW$$Length[];

extern bl_error_boot_type xbl_uncached_memmap_init(boot_handle, uintnt base, uintnt size);
extern bl_error_boot_type rd_raw_format_get_interface    (void *format_interface_if);
extern bl_error_boot_type rd_hfat_format_get_interface   (void *format_interface_if);
extern bl_error_boot_type rd_sahara_format_get_interface (void *format_interface_if);
static bl_error_boot_type uncached_heap_init(boot_handle);

/* Storing ramdump table handle */
static boot_handle ramdump_table_handle = NULL;

/* Ramdump configuration table */
ramdump_config_table_entry xbl_ramdump_config_table[] =
{
  /*boot_media  rd_media       rd_fs             post_rd_action                status */
  { SPI_FLASH,      NVME_FLASH,     RD_FORMAT_RAW,    RD_ACTION_REBOOT_ON_PASS,          BL_ERR_RAMDUMP_NOT_COLLECTED},
  { SPI_FLASH,      NVME_FLASH,     RD_FORMAT_HFAT,   RD_ACTION_REBOOT_ON_FORMAT_STATUS, BL_ERR_RAMDUMP_NOT_COLLECTED},
  { UFS_FLASH,      UFS_FLASH,      RD_FORMAT_RAW,    RD_ACTION_REBOOT_ON_PASS,          BL_ERR_RAMDUMP_NOT_COLLECTED},
  { MMC_FLASH,      MMC_FLASH,      RD_FORMAT_RAW,    RD_ACTION_REBOOT_ON_PASS,          BL_ERR_RAMDUMP_NOT_COLLECTED},
  { PCIE_FLASHLESS, PCIE_FLASHLESS, RD_FORMAT_SAHARA, RD_ACTION_REBOOT,                  BL_ERR_RAMDUMP_NOT_COLLECTED},
#ifdef FEATURE_BOOT_RAMDUMPS_TO_SD_CARD
  { PBL_MEDIA,      SDC_FLASH,      RD_FORMAT_HFAT,   RD_ACTION_REBOOT_ON_FORMAT_STATUS, BL_ERR_RAMDUMP_NOT_COLLECTED},
#endif
  { PBL_MEDIA,  USB_FLASHLESS, RD_FORMAT_SAHARA, RD_ACTION_REBOOT_ON_FAIL,             BL_ERR_RAMDUMP_NOT_COLLECTED}
};

#define NUM_DUMP_ENTRIES ((sizeof(xbl_ramdump_config_table))/(sizeof(xbl_ramdump_config_table[0])))

static whitelst_tbl_entry_type rd_placeholder_whitelist[] = {{0x0, 0x0}};

static uint32 ramdump_start_time = 0;
struct boot_log_meta_info boot_ddr_log_meta_info SECTION(".bss.BOOT_DDR_ZI_ZONE");
char sbl1_ddr_log_buf[SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE] SECTION(".bss.BOOT_DDR_ZI_ZONE");
char sbl1_ddr_time_maker_buf[SCL_SBL1_DDR_BOOT_TIME_MARKER_BUF_SIZE] SECTION(".bss.BOOT_DDR_ZI_ZONE");

boot_log_init_data boot_log_data =
{
  (void *)&sbl1_ddr_log_buf,
  SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE,
  (void *)&sbl1_ddr_time_maker_buf,
  SCL_SBL1_DDR_BOOT_TIME_MARKER_BUF_SIZE,
  (void *)&boot_ddr_log_meta_info,
  SCL_SBL1_BOOT_LOG_META_INFO_SIZE,
  NULL
};


boot_config_context_populate_table config_context_global_values[] =
{
  {CONFIG_CONTEXT_HOST_IMAGE_ID,               PARAMETER_TYPE_VALUE, {SBL1_IMG, NULL},       {}                                                                                                         },
  {CONFIG_CONTEXT_LOGGER_INTERFACE,            PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_logger_if_type),           boot_logger_get_interface},           },
  {CONFIG_CONTEXT_TIMER_INTERFACE,             PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_timer_if_type),            boot_timer_get_interface},            },
  {CONFIG_CONTEXT_RAMDUMP_INTERFACE,           PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_ramdump_if_type),          boot_ramdump_get_interface},          },
  {CONFIG_CONTEXT_BLACKLIST_INTERFACE,         PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_blacklist_if_type),        boot_blacklist_get_interface},        },
  {CONFIG_CONTEXT_MEMORY_MGR_INTERFACE,        PARAMETER_TYPE_PTR,   {},                     {&memory_mgr_dal,             0,                                     NULL},                                },
  {CONFIG_CONTEXT_RESET_INTERFACE,             PARAMETER_TYPE_PTR,   {},                     {&reset_if,                   0,                                     NULL},                                },
  {CONFIG_CONTEXT_BUSYWAIT_INTERFACE,          PARAMETER_TYPE_PTR,   {},                     {&busywait_if,                0,                                     NULL},                                },
  {CONFIG_CONTEXT_CLK_INTERFACE,               PARAMETER_TYPE_PTR,   {},                     {&clk_if,                     0,                                     NULL},                                },
  {CONFIG_CONTEXT_COLDPLUG_INTERFACE,          PARAMETER_TYPE_PTR,   {},                     {&coldplug_if,                0,                                     NULL},                                },
  {CONFIG_CONTEXT_CRYPTO_INTERFACE,            PARAMETER_TYPE_PTR,   {},                     {&crypto_if,                  0,                                     NULL},                                },
  {CONFIG_CONTEXT_DAL_INTERFACE,               PARAMETER_TYPE_PTR,   {},                     {&dal_if,                     0,                                     NULL},                                },
  {CONFIG_CONTEXT_DDR_INFO_INTERFACE,          PARAMETER_TYPE_PTR,   {},                     {&ddr_info_if,                0,                                     NULL},                                },
  {CONFIG_CONTEXT_DBGINFO_INTERFACE,           PARAMETER_TYPE_PTR,   {},                     {&dbginfo_if,                 0,                                     NULL},                                },
  {CONFIG_CONTEXT_EFS_INTERFACE,               PARAMETER_TYPE_PTR,   {},                     {&efs_if,                     0,                                     NULL},                                },
  {CONFIG_CONTEXT_PLATFORMINFO_INTERFACE,      PARAMETER_TYPE_PTR,   {},                     {&platforminfo_if,            0,                                     NULL},                                },
  {CONFIG_CONTEXT_PMIC_INTERFACE,              PARAMETER_TYPE_PTR,   {},                     {&pmic_if,                    0,                                     NULL},                                },
  //{CONFIG_CONTEXT_POWER_INTERFACE,           PARAMETER_TYPE_PTR,   {},                     {&power_if,                   0,                                     NULL},                                },
  {CONFIG_CONTEXT_QUSB_LDR_INTERFACE,          PARAMETER_TYPE_PTR,   {},                     {&qusb_ldr_if,                0,                                     NULL},                                },
  {CONFIG_CONTEXT_BOOT_STATS_INTERFACE,        PARAMETER_TYPE_PTR,   {},                     {&boot_statistics_if,         0,                                     NULL},                                },
  {CONFIG_CONTEXT_SMEM_INTERFACE,              PARAMETER_TYPE_PTR,   {},                     {&smem_if,                    0,                                     NULL},                                },
  {CONFIG_CONTEXT_UART_INTERFACE,              PARAMETER_TYPE_PTR,   {},                     {&uart_if,                    0,                                     NULL},                                },
  {CONFIG_CONTEXT_TIMER_HW_INTERFACE,          PARAMETER_TYPE_PTR,   {},                     {&timer_hw_if,                0,                                     NULL},                                },
  {CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE,  PARAMETER_TYPE_PTR,   {},                     {&visual_indicator_if,        0,                                     NULL},                                },
  {CONFIG_CONTEXT_QUSB_AL_BULK_INTERFACE,      PARAMETER_TYPE_PTR,   {},                     {&qusb_al_bulk_if,            0,                                     NULL},                                },
  {CONFIG_CONTEXT_EDK2_CACHE_INTERFACE,        PARAMETER_TYPE_PTR,   {},                     {&edk2_cache_if,              0,                                     NULL},                                },
  {CONFIG_CONTEXT_EDK2_MMU_INTERFACE,          PARAMETER_TYPE_PTR,   {},                     {&edk2_mmu_if,                0,                                     NULL},                                },
  {CONFIG_CONTEXT_EDK2_ARMLIB_INTERFACE,       PARAMETER_TYPE_PTR,   {},                     {&edk2_armlib_if,             0,                                     NULL},                                },
  {CONFIG_CONTEXT_SECLIB_INTERFACE,            PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_seclib_if_type),           boot_seclib_get_interface},           },
  {CONFIG_CONTEXT_PBL_SHARED_DATA_INTERFACE,   PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_pbl_shared_data_if_type),  boot_pbl_shared_data_get_interface},  },
  {CONFIG_CONTEXT_WHITELIST_INTERFACE,         PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_whitelist_if_type),        boot_whitelist_get_interface},        },
  {CONFIG_CONTEXT_PARTITION_ID,                PARAMETER_TYPE_PTR,   {},                     {NULL,                        0,                                     NULL},                                },
  {CONFIG_CONTEXT_SAHARA_DISPATCH_TBL,         PARAMETER_TYPE_PTR,   {},                     {&qusb_al_bulk_if,            0,                                     NULL},                                },
  {CONFIG_CONTEXT_SAHARA_STATUS_MAP_INTERFACE, PARAMETER_TYPE_PTR,   {},                     {&sahara_status_map_if,       0,                                     NULL},                                },
  {CONFIG_CONTEXT_NVME_INTERFACE,              PARAMETER_TYPE_PTR,   {},                     {&nvme_if,                    0,                                     NULL},                                },
  {CONFIG_CONTEXT_BOOT_SLVCOM_INTERFACE,       PARAMETER_TYPE_PTR,   {},                     {&boot_slvcom_if,             0,                                     NULL},                                },
  {CONFIG_CONTEXT_CHIPINFO_INTERFACE,          PARAMETER_TYPE_PTR,   {},                     {&chipinfo_if,                0,                                     NULL},                                },
  {CONFIG_CONTEXT_BOOT_XRC_INTERFACE,          PARAMETER_TYPE_PTR,   {},                     {&boot_xrc_if,                0,                                     NULL},                                },
  {CONFIG_CONTEXT_MHI_INTERFACE,               PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_mhi_if_type),              boot_mhi_get_interface},              },
};

/*===========================================================================
**  Function :  minidump_is_toc_valid
** ==========================================================================
*/
/*!
*
* @brief
*   This function checks conditions for collecting minidumps.
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/
bl_error_boot_type minidump_is_toc_valid(void)
{
  bl_error_boot_type status = BL_ERR_NONE;
  uint32 dload_flag = 0x0;

  /* Check condition for collecting minidumps */
  dload_flag = boot_dload_read_saved_cookie();
  if(dload_flag & SBL_MINIDUMP_MODE_BIT_MASK)
  {
  /* if global minidump table is invalid */
    if(boot_md_is_valid_global_mdtoc() == FALSE)
    {
    /* clear MD cookie if MD & DLOAD cookies are set */
      if(dload_flag & SBL_DLOAD_MODE_BIT_MASK)
      {
        DL_LOG ("MD tbl not found, Clear MD cookie");
        HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUTM(SBL_MINIDUMP_MODE_BIT_MASK, 0);
      }
  /* raise error if only MD cookie is set */
      else
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_MINIDUMP, BL_ERR_INVALID_MINIDUMP_TABLE_ENTRY_PASSED);
      }
    }
  }

  return status;
}

boolean boot_check_display_allowed(void)
{
#define BATT_DISPLAY_THRESHOLD 3700

  bl_error_boot_type status = BL_ERR_NONE;
  boolean return_status = FALSE;
  boot_pmic_if_type *pmic_if = NULL;
  uint32 pmic_ret = 0;
  uint32 vBatt= 0;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_PMIC_INTERFACE, (void **)&pmic_if);
  if (status != BL_ERR_NONE)
  {
    boot_log_message("Display check error");
    return FALSE;
  }

  if (pmic_if == NULL)
  {
    boot_log_message("Display check pmic error");
    return FALSE;
  }

  pmic_ret = pmic_if->pm_chg_get_vbatt (&vBatt);
  if ((vBatt >= BATT_DISPLAY_THRESHOLD) && (pmic_ret == 0))
  {
    return_status = TRUE;
  }

  return return_status;
}

/*===========================================================================
**  Function :  XBLRamDumpDisplayInfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function displays messages onto screen
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/

boolean display_initialization_needed = TRUE;

static bl_error_boot_type XBLRamDumpDisplayInfo(boot_handle config_context_handle)
{
  uint8 *boot_log_base_ptr = NULL;
  uintnt boot_log_init_info_size = 0 ;
  uint8* scaled_buffer = NULL;
  boot_logger_if_type *logger;
  boot_memory_mgr_if_type *mem_if = NULL;
  bl_error_boot_type status = BL_ERR_NONE;

  do
  {

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_LOGGER_INTERFACE, (void **)&logger);
    if (status != BL_ERR_NONE || logger == NULL)
    {
      boot_log_message("get_logger_if error");
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE || mem_if == NULL)
    {
      boot_log_message("get_mem_if error");
      break;
    }

    /* re-enter sahara-download mode case, skip re-initializing display */
    if (display_initialization_needed == TRUE)
    {
      if (boot_display_init() != TRUE)
      {
        boot_log_message("Display Init Failed");
        display_initialization_needed = FALSE;
        status = BL_ERR_DISPLAY_INIT_FAIL;
        break;
      }

      /* Example use of display scaling api*/

      /*Allocate buffer for image scaling */
      status = mem_if->malloc(GLYPH_BUFF_3X_SIZE_BYTES, (void *)&scaled_buffer);
      if (status != BL_ERR_NONE)
      {
        break;
      }
      boot_display_set_font_color(COLOR_BLUE);
      boot_display_scaled_message((uint8 *)"\n\n\rQUALCOMM ", SCALE_3X, scaled_buffer, GLYPH_BUFF_3X_SIZE_BYTES);

      boot_display_set_scale_factor(SCALE_3X);
      boot_display_set_font_color(COLOR_RED);
      boot_display_message((uint8 *)"CrashDump Mode\n\r");

      boot_display_set_font_color(COLOR_YELLOW);
      boot_display_message((uint8 *)"__________________________\n\n\r");

      boot_display_set_font_color(COLOR_WHITE);
      if (NULL != logger->get_log_data)
      {
        status = logger->get_log_data(&boot_log_base_ptr, &boot_log_init_info_size);
        if (status != BL_ERR_NONE)
        {
          break;
        }
        boot_display_buffer(boot_log_base_ptr, boot_log_init_info_size, SCALE_2X, scaled_buffer, GLYPH_BUFF_2X_SIZE_BYTES);
      }

      /* Free Allocated buffers */
      status = mem_if->free((void *)scaled_buffer);

      display_initialization_needed = FALSE;
    }
  } while (FALSE);

  return status;
}

/*===========================================================================
**  Function : system_init
** ==========================================================================
*/
/*!
*
* @brief
*   This function is entry point for XBL Ramdump image
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/
extern pm_err_flag_type boot_pm_pon_wdog_cfg(uint8 pmic_device_index, uint32 s1_timer, uint32 s2_timer, pm_pon_reset_cfg_type reset_cfg_type);
extern pm_err_flag_type boot_pm_pon_wdog_enable(uint8 pmic_device_index, pm_on_off_type enable);
extern bl_error_boot_type ramdump_populate_mem_map(boot_handle config_context_handle);

bl_error_boot_type system_init(boot_handle *config_context_handle)
{
  DALResult bsy_wait_init;
  boot_clk_if_type *clk_if = NULL;
  boot_media_interface_if_type *media_if = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_busywait_if_type *busywait_if = NULL;
  boot_logger_if_type *logger_if = NULL;
  boot_pmic_if_type *pmic_if = NULL;
  boot_registered_logger_if_type *logger_uart_if = NULL;
  boot_edk2_mmu_if_type *edk2_mmu_if = NULL;
  bl_error_boot_type status = BL_ERR_NONE;
  boot_platforminfo_if_type *platforminfo_if = NULL;
  pm_err_flag_type pm_return;
  void * boot_device_tree_blob_address = NULL;
  DALResult dal_result = DAL_SUCCESS;
  boot_slvcom_if_type *boot_slvcom_if = NULL;
  boot_chipinfo_if_type *chipinfo_if = NULL;

  do
  {
    /* Calculate the SBL start time for use during boot logger initialization. */
    ramdump_start_time = CALCULATE_TIMESTAMP(HWIO_IN(TIMETICK_CLK));

    /* Initialize dal heap using external memory */
    dal_result = dal_if.HeapInit((void *)xbl_get_external_cached_heap_addr(),
                                 xbl_get_external_cached_heap_size(),
                                 DALHEAP_DDR);
    if (dal_result != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_DAL, BL_ERR_EXT_HEAP_INIT_FAIL);
      break;
    }

    /* Initialize DAL, needs to be called before modules that uses DAL */
    dal_if.InitMod(NULL);

    status = boot_config_context_open(config_context_handle, &memory_mgr_dal);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_set_parameters(*config_context_handle, config_context_global_values, sizeof(config_context_global_values)/sizeof(boot_config_context_populate_table));
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Initialize the stack protection canary */
    boot_init_stack_chk_canary();
    /* Initialize ramdump memory map */
    status = ramdump_populate_mem_map(*config_context_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }    
    /* Uncached heap is required by some media to initialize internal structures*/
    /* Called after configuring MMU */
    status = uncached_heap_init(*config_context_handle);
    if (status != BL_ERR_NONE)
    {
        boot_log_message("Uncached heap init failed");
        break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_CLK_INTERFACE, (void **)&clk_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Clock Driver Initialization */
    status = clk_if->init();
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_EDK2_MMU_INTERFACE, (void **)&edk2_mmu_if);
    if (status != BL_ERR_NONE || edk2_mmu_if == NULL)
    {
        break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* initialize DTdriver with DTB in DDR */
    boot_device_tree_blob_address = (void *)boot_shared_imem_cookie_ptr->boot_devtree_addr;

    if (fdt_set_blob_handle(boot_device_tree_blob_address, DEFAULT_BLOB_ID) != 0)
    {
      status = BL_ERR_NO_FDT_HANDLE;
      break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_PLATFORMINFO_INTERFACE, (void *)&platforminfo_if);
    if (status != BL_ERR_NONE || platforminfo_if == NULL)
    {
      break;
    }

    dal_result = platforminfo_if->Init();
    if (dal_result != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_DAL, BL_ERR_INITIALIZATION_ERROR);
      break;
    }

    status = boot_config_context_set_value(*config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, (uint32)boot_shared_imem_cookie_ptr->boot_device_type);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_set_value(*config_context_handle, CONFIG_CONTEXT_PBL_MEDIA_BOOT_DEVICE, (uint32)boot_shared_imem_cookie_ptr->boot_device_type);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_set_ptr(*config_context_handle, CONFIG_CONTEXT_IMAGE_WHITELIST, (void **)&rd_placeholder_whitelist);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_set_value(*config_context_handle, CONFIG_CONTEXT_WHITELIST_NUM_ENTRIES, (sizeof(rd_placeholder_whitelist)/sizeof(whitelst_tbl_entry_type)));
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_BUSYWAIT_INTERFACE, (void **)&busywait_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Initialize busywait module Note: required before logger init due to uart driver dependency on busywait */
    bsy_wait_init = busywait_if->init();
    if (bsy_wait_init != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_BUSYWAIT, BL_ERR_INITIALIZATION_ERROR);
      break;
    }

    /* uart log init*/
    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_LOGGER_INTERFACE, (void *)&logger_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /*initialize boot logger*/
    logger_if->init(*config_context_handle, &boot_log_data);

    status = boot_logger_uart_get_interface(&logger_uart_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = logger_if->register_logger(logger_uart_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = mem_if->malloc(sizeof(boot_media_interface_if_type), (void *)&media_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_media_get_interface(*config_context_handle, media_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* It is possible to have a media type with no interface.
       Call media's hw init if pointer is not null. */
    if (media_if->media_hw_init != NULL)
    {
      status = media_if->media_hw_init(*config_context_handle);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }

    status = boot_config_context_set_ptr(*config_context_handle, CONFIG_CONTEXT_BOOT_MEDIA_INTERFACE, (void *)(media_if));
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_PMIC_INTERFACE, (void **)&pmic_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }


    pm_return = pmic_if->pm_infra_init();
    if (pm_return != PM_ERR_FLAG_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PMIC, BL_ERR_INITIALIZATION_ERROR);
      break;
    }

    pm_return = pmic_if->pm_driver_init();
    if (pm_return != PM_ERR_FLAG_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_PMIC, BL_ERR_INITIALIZATION_ERROR);
      break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_CHIPINFO_INTERFACE, (void **)&chipinfo_if);
    if(status != BL_ERR_NONE)
    {
       break;
    }

    /* ChipInfo init */
    status = chipinfo_if->init();
    if(status != BL_ERR_NONE)
    {
       break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_BOOT_SLVCOM_INTERFACE, (void **)&boot_slvcom_if);
    if(status != BL_ERR_NONE)
    {
       break;
    }
    status = boot_slvcom_if->init();
    if(status != BL_ERR_NONE) {
       return status;
    }

  }while(FALSE);

  return status;
}

static bl_error_boot_type uncached_heap_init (boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_dal_if_type *dal_if = NULL;
  DALResult dal_result;
  uintnt external_uncached_heap_addr = 0;
  uintnt external_uncached_heap_size = 0;

  external_uncached_heap_addr = (uintnt)(xbl_get_external_uncached_heap_addr());
  external_uncached_heap_size = xbl_get_external_uncached_heap_size();

  do
  {
    if (config_context_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_HANDLE);
      break;
    }

    /* Set as uncached */
    status = xbl_uncached_memmap_init(config_context_handle,
                                      external_uncached_heap_addr,
                                      external_uncached_heap_size);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("uncached heap map error");
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DAL_INTERFACE, (void **)&dal_if);
    if (status != BL_ERR_NONE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_HANDLE);
      boot_log_message("get_cc_if error");
      break;
    }

    if (dal_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_HANDLE);
      boot_log_message("get_dal_if error");
      break;
    }

    /* Initialize dal heap using internal uncache memory */
    dal_result = dal_if->HeapInit ((void*)external_uncached_heap_addr,
                                   external_uncached_heap_size,
                                   DALHEAP_UNCACHED);
    if (dal_result != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_DAL, BL_ERR_EXT_HEAP_INIT_FAIL);
      break;
    }
  } while (FALSE);

  return status;
}


/*===========================================================================
**  Function :  xbl_ramdump_print_table
** ==========================================================================
*/
/*!
*
* @brief
*   This function prints current table entries
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/

bl_error_boot_type  xbl_ramdump_print_table (ramdump_table_if *rd_table_if, boot_handle ramdump_table_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_type *rd_table_ptr = NULL;
  uintnt rd_table_len = 0;
  uintnt i = 0;

  do
  {
    if (rd_table_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_PARAMETER);
      break;
    }

    status = rd_table_if->get_table_len(ramdump_table_handle, &rd_table_len);
    if (status != BL_ERR_NONE)
    {
      break;
    }


    status = rd_table_if->get_table_addr(ramdump_table_handle, (uintnt*)&rd_table_ptr);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (rd_table_ptr == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_INVALID_PARAMETER);
      break;
    }

    rd_table_len/=sizeof(ramdump_table_type);

    for (i=0; i < rd_table_len; i++)
    {
      if (rd_table_ptr[i].filename != NULL)
      {
        boot_log_message(rd_table_ptr[i].filename);
      }
      else
      {
        boot_log_message("NULL");
      }
    }
  } while (FALSE);

  return status;
}


/*===========================================================================
**  Function :  XBLRamDumpTableInit
** ==========================================================================
*/
/*!
*
* @brief
*   This function sets up the RAM dump table
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/

bl_error_boot_type XBLRamDumpTableInit (boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_memory_mgr_if_type *mem_if = NULL;
  ramdump_table_if *rd_table_if = NULL;
  boot_boolean memdump_allowed = FALSE;
  boot_sahara_dispatch_tbl *sahara_dispatch_tbl_if = NULL;

  do
  {
    if (config_context_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = mem_if->malloc(sizeof(ramdump_table_if), (void *)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (rd_table_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_ramdump_table_get_interface (rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("rd_if_get error");
      break;
    }

    if (rd_table_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void *)(rd_table_if));
    if (status != BL_ERR_NONE)
    {
      boot_log_message("set_ptr error");
      break;
    }

    /* Prepare for ramdump table with entries */
    status = rd_table_if->open(config_context_handle, &ramdump_table_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Check for ramdump table handle */
    if (ramdump_table_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE, (void *)ramdump_table_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    xbl_ramdump_print_table (rd_table_if, ramdump_table_handle);

    /* Check for dump collection supported from qsee */
    status = rd_table_if->is_ramdump_allowed(config_context_handle, &memdump_allowed);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    /* Dump collection is not supported */
    if (memdump_allowed == FALSE)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_LOADER, BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED);
      break;
    }

    /* Set the cookie if dump collection is supported returns true */
    status = boot_config_context_set_value(config_context_handle, CONFIG_CONTEXT_RAMDUMP_OR_MINIDUMP_COOKIE, TRUE);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = mem_if->malloc(sizeof(boot_sahara_dispatch_tbl), (void *)&sahara_dispatch_tbl_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    memset((void* )(sahara_dispatch_tbl_if), 0x0, sizeof(boot_sahara_dispatch_tbl));

    status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_SAHARA_DISPATCH_TBL, (void *)(sahara_dispatch_tbl_if));
    if (status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_sahara_dispatch_table_init(config_context_handle);
    if (status != BL_ERR_NONE)
    {
      break;
    }


  } while (FALSE);

  dload_mem_debug_init(config_context_handle);

  return status;
}

/*===========================================================================
**  Function :  XBLRamDumpTableDeinit
** ==========================================================================
*/
/*!
*
* @brief
*   This function closes and free Ramdump Table interface and
*   frees Sahara Dispatch Table
*
* @param[in]
*   Config_context_handle
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/
bl_error_boot_type XBLRamDumpTableDeinit (boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  ramdump_table_if *rd_table_if = NULL;
  boot_memory_mgr_if_type *mem_if = NULL;
  boot_sahara_dispatch_tbl *sahara_dispatch_tbl_if = NULL;

  do
  {
    /* Handle closing of Ramdump table */
    if (config_context_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_MEMORY_MGR_INTERFACE, (void **)&mem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (mem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void **)&rd_table_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("GetRamdump table interface ptr error");
      break;
    }

    if (rd_table_if)
    {


      status = rd_table_if->close(config_context_handle, ramdump_table_handle);
      if (status != BL_ERR_NONE)
      {
        boot_log_message("Ramdump Table close error");
        break;
      }

      /* Reset ramdump table handle */
      ramdump_table_handle = NULL;

      status = mem_if->free((void *)rd_table_if);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      rd_table_if = NULL;

      /* Reset Ramdump Table Interface in config context table */
      status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE, (void *)NULL);
      if (status != BL_ERR_NONE)
      {
        boot_log_message("Set Ramdump table interface ptr error");
        break;
      }
    }

    /* Handle Free of Sahara Dispatch table */
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SAHARA_DISPATCH_TBL, (void **)&sahara_dispatch_tbl_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    if (sahara_dispatch_tbl_if)
    {
      status = mem_if->free((void *)sahara_dispatch_tbl_if);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_SAHARA_DISPATCH_TBL, (void *)NULL);
      if (status != BL_ERR_NONE)
      {
        break;
      }
    }

  } while (FALSE);

  return status;
}


/*===========================================================================
**  Function :  XBLRamDumpInit
** ==========================================================================
*/
/*!
*
* @brief
*   This function is init function for RAM dump module
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/

bl_error_boot_type XBLRamDumpInit (boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_edk2_cache_if_type *edk2_cache_if = NULL;
  extern boot_qusb_al_bulk_if_type qusb_al_bulk_if;
  extern boot_nvme_if_type nvme_if;
  uint32 dload_flag =0x0;

  do
  {
    if (config_context_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_HANDLE);
      break;
    }

    /* Set crt_handle for config context instance in RAM dump */
    status = boot_config_context_set_crt_handle(config_context_handle);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("set_crt error");
      break;
    }

    status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_QUSB_AL_BULK_INTERFACE, (void *)(&qusb_al_bulk_if));
    if (status != BL_ERR_NONE)
    {
      boot_log_message("set_ptr error");
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void**)&edk2_cache_if);
    if ((status != BL_ERR_NONE) || (edk2_cache_if == NULL))
    {
      boot_log_message("get_cache_if error");
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MMU, BL_ERR_INVALID_HANDLE);
      break;
    }
    /* Flush cache for ZI region */
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)Image$$RAMDUMP_DATA_ZI$$Base, (uintnt)Image$$RAMDUMP_DATA_ZI$$Length);

    status = boot_config_context_set_ptr(config_context_handle, CONFIG_CONTEXT_NVME_INTERFACE, (void *)&nvme_if);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("set_ptr error");
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_HANDLE);
      break;
    }

    dload_flag = boot_dload_read_saved_cookie() & (SBL_MINIDUMP_MODE_BIT_MASK | SBL_DLOAD_MODE_BIT_MASK);
    if (dload_flag == SBL_MINIDUMP_MODE_BIT_MASK)
    {
#if 0
      extern pm_err_flag_type boot_pm_pon_wdog_cfg(uint8 pmic_device_index, uint32 s1_timer, uint32 s2_timer, pm_pon_reset_cfg_type reset_cfg_type);
      extern pm_err_flag_type boot_pm_pon_wdog_enable(uint8 pmic_device_index, pm_on_off_type enable);
      /* Enable PMIC WDG timer only for Minidump case, since full-dumps to eMMC/SDCard/QPST will not complete within PMIC WDG expiry */
      boot_pm_pon_wdog_cfg(PMIC_DEVICE_INDEX, DLOAD_PMIC_WDG_S1_VALUE, DLOAD_PMIC_WDG_S1_VALUE, PM_PON_RESET_CFG_HARD_RESET);
      boot_pm_pon_wdog_enable(PMIC_DEVICE_INDEX, PM_ON);
#endif
    }

    ipa_boot_init();

/* SONY_BEGIN(Ramdumper support) */
#if !(defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP))
    /* Configure power key to do a hardreset */
    status = boot_set_pwrkey_reset_type(BOOT_HARD_RESET_TYPE);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("Power key configuration failed");
      break;
    }


    /* Configure pshold to hardreset */
    status = boot_set_pshold_reset_type(BOOT_HARD_RESET_TYPE);
    if (status != BL_ERR_NONE)
    {
      boot_log_message("PSHold Configuration failed");
      break;
    }


    if (boot_check_display_allowed())
    {
      status = XBLRamDumpDisplayInfo(config_context_handle);
      if (status != BL_ERR_NONE)
      {
        DL_LOG("RamDump DisplayInfo fail, Errcode:0x%x", status);

        /* Display init is not fatal error for RAM dump */
        status = BL_ERR_NONE;
      }
    }

#endif /* FEATURE_XBOOT && FEATURE_SONY_RAMDUMP */
/* SONY_END(Ramdumper support) */
  } while (FALSE);

  return status;
}


/*===========================================================================
**  Function :  get_ramdump_media_if
** ==========================================================================
*/
/*!
*
* @brief
*   This function gets media interface for RAM dump entry in config table
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   RAM dump media interface
*
*/

bl_error_boot_type get_ramdump_media_if (boot_media_type media_type, ramdump_format_type rd_format, boot_media_interface_if_type *rd_media_if)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if (rd_media_if == NULL)
  {
    status = GET_ERROR_CODE( BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_PARAMETER);
    return status;
  }

  switch (media_type)
  {
  case MMC_FLASH:
  case UFS_FLASH:
  case NVME_FLASH:
    if ( rd_format == RD_FORMAT_HFAT )
      status = boot_hfat_dev_get_interface (rd_media_if);
    else
      status = boot_block_dev_get_interface (rd_media_if);
    break;

  case SDC_FLASH:
    status = boot_hfat_dev_get_interface (rd_media_if);
    break;

  case PCIE_FLASHLESS:
  case USB_FLASHLESS:
    status = boot_flashless_dev_get_interface (rd_media_if);
    break;

  default:
    status = GET_ERROR_CODE( BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_PARAMETER);
    break;
  }

  return status;
}


/*===========================================================================
**  Function :  get_ramdump_format_if
** ==========================================================================
*/
/*!
*
* @brief
*   *   This function gets format interface for RAM dump entry in config table
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   RAM dump format interface
*
*/
bl_error_boot_type get_ramdump_format_if (ramdump_format_type rd_format, ramdump_format_if_type *rd_format_if)
{
  bl_error_boot_type status = BL_ERR_NONE;

  if (rd_format_if == NULL)
  {
    status = GET_ERROR_CODE( BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_PARAMETER);
    return status;
  }

  switch (rd_format)
  {
  case RD_FORMAT_RAW:
    rd_raw_format_get_interface (rd_format_if);
    status = BL_ERR_NONE;
    break;

  case RD_FORMAT_HFAT:
    rd_hfat_format_get_interface (rd_format_if);
    status = BL_ERR_NONE;
    break;

  case RD_FORMAT_SAHARA:
    status = rd_sahara_format_get_interface (rd_format_if);
    break;

  default:
    status = GET_ERROR_CODE (BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_PARAMETER);
    break;
  }

  return status;
}

/*===========================================================================
**  Function :  xbl_ramdump_process_post_dump
** ==========================================================================
*/
/*!
*
* @brief
*   This function handles post dump action
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/

bl_error_boot_type xbl_ramdump_process_post_dump (bl_error_boot_type closed_status, post_ramdump_action_type rd_action)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_edk2_cache_if_type *edk2_cache_if = NULL;
  boot_hw_reset_type rd_reset_type = BOOT_HARD_RESET_TYPE;

  status = boot_config_context_get_ptr(CONFIG_CONTEXT_CRT_HANDLE, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void**)&edk2_cache_if);
  if (status != BL_ERR_NONE)
  {
    return status;
  }
  if (edk2_cache_if == NULL)
  {
    status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP, BL_ERR_NULL_PTR_PASSED);
    return status;
  }

#if 0
  /* NOTE: On fusion we don't do hard reset */
  if (boot_PlatformInfo_IsFusion())
  {
    rd_reset_type = BOOT_APQ_COLD_DEBUG_RESET;
  }
  else
  {
    rd_reset_type = BOOT_HARD_RESET_TYPE;
  }
#endif

  switch (rd_action)
  {
  case RD_ACTION_REBOOT_ON_PASS:
    if (closed_status == BL_ERR_NONE)
    {
      /* Clear ID so the downloader is not entered again on the next boot. */
      HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUTM(SBL_DLOAD_MODE_BIT_MASK | SBL_MINIDUMP_MODE_BIT_MASK, 0);
      goto reset_exit;
    }
    status = BL_ERR_NONE;
    break;

  case RD_ACTION_REBOOT_ON_FAIL:
    if (closed_status != BL_ERR_NONE)
    {
      /* Clear ID so the downloader is not entered again on the next boot. */
      HWIO_TCSR_TCSR_BOOT_MISC_DETECT_OUTM(SBL_DLOAD_MODE_BIT_MASK | SBL_MINIDUMP_MODE_BIT_MASK, 0);
      goto reset_exit;
    }
    status = BL_ERR_NONE;
    break;

  case RD_ACTION_CONTINUE:
    status = BL_ERR_NONE;
    break;

  case RD_ACTION_REBOOT_ON_FORMAT_STATUS:
    if (closed_status == BL_ERR_RAMDUMP_COLLECTED_REBOOT)
    {
      goto reset_exit;
    }
    else if (closed_status == BL_ERR_RAMDUMP_COLLECTED_WARM_REBOOT)
    {
      rd_reset_type = BOOT_WARM_RESET_TYPE;
      goto reset_exit;
    }
    status = BL_ERR_NONE;
    break;

  default:
    status = GET_ERROR_CODE( BL_ERROR_GROUP_RAMDUMP, BL_ERR_INVALID_PARAMETER);
    break;
  }

  goto exit;

reset_exit:
  edk2_cache_if->WriteBackDataCache();
  boot_hw_reset(rd_reset_type);

exit:
  return status;
}
/*===========================================================================
**  Function :  ReenterRamdump
** ==========================================================================
*/
/*!
*
* @brief
*   This function is re entry RAM dump image
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/
extern void el1_entry(void*);
bl_error_boot_type ReenterRamdump(boot_handle config_context_handle)
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_edk2_cache_if_type *edk2_cache_if = NULL;
  boot_edk2_mmu_if_type * edk2_mmu_if = NULL;
  boot_dal_if_type *dal_if = NULL;
  uintnt external_uncached_heap_addr = 0;
  uintnt external_uncached_heap_size = 0;

  external_uncached_heap_addr = (uintnt)(xbl_get_external_uncached_heap_addr());
  external_uncached_heap_size = xbl_get_external_uncached_heap_size();
  do
  {
    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_EDK2_CACHE_INTERFACE, (void**)&edk2_cache_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (edk2_cache_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DAL_INTERFACE, (void **)&dal_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (dal_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_RAMDUMP_TABLE, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Obtain EDK2 MMU interface */
    status = boot_config_context_get_ptr(config_context_handle,
                                        CONFIG_CONTEXT_EDK2_MMU_INTERFACE,
                                        (void **)&edk2_mmu_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    /* Invalidate data cache, re-enter download mode without reset */
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)SCL_RAMDUMP_DLOAD_BUFFERS_BASE, (uintnt)SCL_RAMDUMP_DLOAD_BUFFERS_SIZE);
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)xbl_get_external_cached_heap_addr(), (uintnt)xbl_get_external_cached_heap_size());
    dal_if->DeInitMod();
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)Image$$RAMDUMP_DATA_RW$$Base, (uintnt)Image$$RAMDUMP_DATA_RW$$Length);
    edk2_cache_if->WriteBackInvalidateDataCacheRange((void *)Image$$STACK$$Base, (uintnt)Image$$STACK$$Length);
     /* Set uncached heap region as cacheable */
    if (edk2_mmu_if->ArmSetMemoryAttributes((uintnt)external_uncached_heap_addr,
                                            (uintnt)external_uncached_heap_size,
                                            EFI_ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN) != EFI_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MMU, BL_ERR_MMU_PGTBL_MAPPING_FAIL);
      break;
    }

    edk2_cache_if->InvalidateDataCacheRange((void *)Image$$RAMDUMP_DATA_ZI$$Base, (uintnt)Image$$RAMDUMP_DATA_ZI$$Length);
    el1_entry((void*)NULL);
  } while (FALSE);
  return status;
}
/*===========================================================================
**  Function :  XBLRamDumpMain
** ==========================================================================
*/
/*!
*
* @brief
*   This function is entry point of RAM dump image
*
* @param[in]
*   None
*
* @par Dependencies
*   None
*
* @retval
*   None
*
*/
bl_error_boot_type XBLRamDumpMain( void *sbl_shared )
{
  bl_error_boot_type status = BL_ERR_NONE;
  boot_media_type inital_boot_device = NO_FLASH;
  static boot_handle config_context_handle __attribute__((__aligned__(SIZE_4KB)));
  static boot_media_interface_if_type rd_media_if;
  static ramdump_format_if_type rd_format_if;
  int current_dump_entry = 0, range_num = 0;
/* SONY_BEGIN(Ramdumper support) */
#if (defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP))
  ramdump_type rd_type;
  boot_dbginfo_if_type *dbginfo_if = NULL;
#endif /* (FEATURE_XBOOT && FEATURE_SONY_RAMDUMP) */
/* SONY_END(Ramdumper support) */

  do
  {

    /* Zero initialize ZI section in DDR for RAM dump */
    memset (Image$$RAMDUMP_DATA_ZI$$Base, 0, (size_t)Image$$RAMDUMP_DATA_ZI$$Length);

    /* Setup config context */
    status = system_init(&config_context_handle);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = minidump_is_toc_valid();
    if(status != BL_ERR_NONE)
    {
      break;
    }

    /* Ram Dump Image Init */
    status = XBLRamDumpInit (config_context_handle);
    if (status != BL_ERR_NONE)
    {
      DL_LOG ("ERROR: Ramdump Init 0x%x", status);
      break;
    }

    /* Ram Dump table - region setup */
    status = XBLRamDumpTableInit(config_context_handle);
    if (status != BL_ERR_NONE)
    {
      DL_LOG ("ERROR: Ramdump TableInit 0x%x", status);
      break;
    }

/* SONY_BEGIN(Ramdumper support) */
#if (defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP))
  boot_ramdump_init(config_context_handle);

  if (boot_is_ramdump_to_rddata_allowed(config_context_handle))
    boot_hw_reset(BOOT_HARD_RESET_TYPE);

#endif /* (FEATURE_XBOOT && FEATURE_SONY_RAMDUMP) */
/* SONY_END(Ramdumper support) */

    status = boot_config_context_get_value (config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, (void *)&inital_boot_device);
    if (status != BL_ERR_NONE)
    {
      break;
    }

    for (current_dump_entry = 0; current_dump_entry < NUM_DUMP_ENTRIES; current_dump_entry++)
    {
      /* If current boot device is not one from supported list skip processing */
      if ( (inital_boot_device != xbl_ramdump_config_table[current_dump_entry].boot_media) &&
          (xbl_ramdump_config_table[current_dump_entry].boot_media != PBL_MEDIA) )
      {
        DL_LOG ("Boot device check, skipping [%d]", current_dump_entry);
        continue;
      }

/* SONY_BEGIN(Ramdumper support) */
#if (defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP))
    if ((xbl_ramdump_config_table[current_dump_entry].ramdump_media != SDC_FLASH) )
    {
      DL_LOG ("Sony Ramdump device check, skipping [%d]", current_dump_entry);
      continue;
    }
    else /* Avoid collecting minidump into sdcard for commercial device */
    {
      status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DBGINFO_INTERFACE, (void *)&dbginfo_if);
      if (status != BL_ERR_NONE || dbginfo_if == NULL)
      {
        DL_LOG ("Dbginfo_if Get Fail, Errcode:0x%x", status);
        break;
      }

      status = dbginfo_if->which_ramdump_allowed(&rd_type);
      if (status != BL_ERR_NONE)
      {
        DL_LOG ("Which ramdump allowed status check failed, Errcode:0x%x", status);
        break;
      }

      DL_LOG ("Allowed ramdump type:%d", rd_type);
      if (rd_type != FULL_DUMP_ALLOWED)
      {
        boot_log_message("Skip collecting minidump/Nonsecure dumps into sdcard");
        break;
      }
    }
#endif /* (FEATURE_XBOOT && FEATURE_SONY_RAMDUMP) */
/* SONY_END(Ramdumper support) */

      /* Case 1: Set CONFIG_CONTEXT_BOOT_DEVICE to get media_interface and call hw init on it */
      if ( (xbl_ramdump_config_table[current_dump_entry].boot_media != xbl_ramdump_config_table[current_dump_entry].ramdump_media) )
      {
        status = boot_config_context_set_value (config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE, xbl_ramdump_config_table[current_dump_entry].ramdump_media);
        if (status != BL_ERR_NONE)
        {
          xbl_ramdump_config_table[current_dump_entry].status = BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED;
          boot_log_message("set boot device failed");
          goto skip_to_next;
        }

        status = get_ramdump_media_if (xbl_ramdump_config_table[current_dump_entry].ramdump_media, xbl_ramdump_config_table[current_dump_entry].ramdump_format, &rd_media_if);
        if (status != BL_ERR_NONE)
        {
          xbl_ramdump_config_table[current_dump_entry].status = BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED;
          boot_log_message("get rd_media_if failed");
          goto skip_to_next;
        }

        if (rd_media_if.media_hw_init != NULL)
        {
          boot_log_message("rd_media_if.media_hw_init");
          status = rd_media_if.media_hw_init (config_context_handle);
          if (status != BL_ERR_NONE)
          {
            xbl_ramdump_config_table[current_dump_entry].status = BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED;
            boot_log_message("get media_hw_init failed");
            goto skip_to_next;
          }
        }
      }

      /* Case2: We don't have to call media hw init in this case */
      status = get_ramdump_media_if (xbl_ramdump_config_table[current_dump_entry].ramdump_media, xbl_ramdump_config_table[current_dump_entry].ramdump_format, &rd_media_if);
      if (status != BL_ERR_NONE)
      {
        xbl_ramdump_config_table[current_dump_entry].status = BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED;
        boot_log_message("get rd_media_if failed");
        goto skip_to_next;
      }

      status = get_ramdump_format_if(xbl_ramdump_config_table[current_dump_entry].ramdump_format, &rd_format_if);
      xbl_ramdump_config_table[current_dump_entry].status = status;
      if (status != BL_ERR_NONE)
      {
        xbl_ramdump_config_table[current_dump_entry].status = BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED;
        boot_log_message("get rd_format_if failed");
        goto skip_to_next;
      }

      /* Init checks preconditions to proceed with dump */
      status = rd_format_if.init (&rd_media_if);
      xbl_ramdump_config_table[current_dump_entry].status = status;
      if (status != BL_ERR_NONE)
      {
        xbl_ramdump_config_table[current_dump_entry].status = BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED;
        boot_log_message("get rd_format_if.init failed");
        goto skip_to_next;
      }

      /* Open performs all operations prior to dumping of regions */
      status = rd_format_if.open (&rd_media_if);
      xbl_ramdump_config_table[current_dump_entry].status = status;
      if (status != BL_ERR_NONE)
      {
        xbl_ramdump_config_table[current_dump_entry].status = BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED;
        boot_log_message("get rd_format_if.open failed");
        goto skip_to_next;
      }

      /* Iterate over each range and perform write */
      for (range_num = 0; range_num < dload_mem_debug_num_ent(); range_num++)
      {
        status = rd_format_if.write (&rd_media_if, dload_mem_debug_filename (range_num), (void*)dload_mem_debug_mem_base (range_num), dload_mem_debug_mem_length (range_num));
        if (status != BL_ERR_NONE)
        {
          boot_log_message("write error");
          break;
        }
      }
      boot_log_message("start rd_format_if.close");
      /* Perform post write steps */
      status = rd_format_if.close (&rd_media_if);
      xbl_ramdump_config_table[current_dump_entry].status = status;
      if (status != BL_ERR_NONE)
      {
        xbl_ramdump_config_table[current_dump_entry].status = status;
        boot_log_message("close error");
        goto skip_to_next;
      }


skip_to_next:

      /* Check if Ramdump restart is required */
      if (status == (BL_ERROR_GROUP_RAMDUMP | BL_ERR_RAMDUMP_RESTART))
      {
        /* HW Deinit the transport layer. It will be reinitialized after RD restart */
        if (rd_media_if.media_hw_deinit != NULL)
        {
          boot_log_message("rd_media_if.media_hw_deinit");
          /* Do not collect return value since status is already bad */
          rd_media_if.media_hw_deinit(config_context_handle);

        }

        goto restart_ramdump;
      }

      /* Reset original boot device */
      status = boot_config_context_set_value (config_context_handle, CONFIG_CONTEXT_BOOT_DEVICE,  inital_boot_device);
      if (status != BL_ERR_NONE)
      {
        break;
      }

      /* Post dump processing step */
      status = xbl_ramdump_process_post_dump (xbl_ramdump_config_table[current_dump_entry].status, xbl_ramdump_config_table[current_dump_entry].post_ramdump_action);
      if (status != BL_ERR_NONE)
      {
        boot_log_message("post process error");
      }
    }

/* SONY_BEGIN(Ramdumper support) */
#if (defined(FEATURE_XBOOT) && defined(FEATURE_SONY_RAMDUMP))

    boot_hw_reset(BOOT_HARD_RESET_TYPE);

#endif /* (FEATURE_XBOOT && FEATURE_SONY_RAMDUMP) */
/* SONY_END(Ramdumper support) */

    /* Should not get here, target should reset after all dumps are processed */
    status = (BL_ERROR_GROUP_RAMDUMP | BL_ERR_RAMDUMP_IMAGE_EXIT);
    break;

  restart_ramdump:
    boot_log_message("re-enter ramdump");
    XBLRamDumpTableDeinit(config_context_handle);
    ReenterRamdump(config_context_handle);

  }while(FALSE);

  if(status != BL_ERR_NONE)
  {
    bl_err_if.error_handler(__FILE_BASENAME__, __LINE__, status);
  }
  return status;

}

bl_error_boot_type (*Main_entry)(void*) = XBLRamDumpMain;
