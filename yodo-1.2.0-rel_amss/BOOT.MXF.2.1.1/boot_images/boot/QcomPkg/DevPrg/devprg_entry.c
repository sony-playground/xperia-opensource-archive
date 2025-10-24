/** @file devprg_entry.c
  Bootup logic for DeviceProgrammer

  Copyright (c) 2020-2022 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY

when        who  what, where, why
----------  ---  -----------------------------------------------------------
2022-04-06  sc   Fix missing devprg config global value for platform info
2022-02-09  ck   Updated heap function names
2021-03-17  wek  Change cache attributes for DDR.
2020-12-17  wek  First Revision. Derived from XBLRamdump/XBLRamdump.c

=============================================================================*/
#include <string.h>
#include <HALhwio.h>
#include <HALbootHWIO.h>
#include "boot_target.h"
#include "MIheader.h"
#include "boot_sbl_shared.h"
#include "boot_reset_if.h"
#include "boot_platforminfo_if.h"
#include "boot_logger_uart.h"
#include <boot_logger_if.h>
#include <boot_config_context.h>
#include <boot_dal_if.h>
#include <boot_memory_mgr_if.h>
#include <boot_crypto_if.h>
#include <boot_timer_if.h>
#include <boot_memory_mgr_dal.h>
#include <boot_uart_if.h>
#include <boot_edk2_mmu_if.h>
#include <boot_heap.h>
#include <boot_media_types.h>
#include <error_handler.h>
#include <pm.h>

extern uintnt Image$$DEVPRG_CODE$$Base[];
extern uintnt Image$$DEVPRG_CODE$$Length[];
extern uintnt Image$$DEVPRG_DATA_RO$$Base[];
extern uintnt Image$$DEVPRG_DATA_RO$$Length[];
extern uintnt Image$$STACK$$Base[];
extern uintnt Image$$STACK$$Length[];
extern uintnt Image$$DEVPRG_DATA_RW$$Base[];
extern uintnt Image$$DEVPRG_DATA_RW$$Length[];
extern uintnt Image$$DEVPRG_DATA_ZI$$Base[];
extern uintnt Image$$DEVPRG_DATA_ZI$$Length[];


/* Boot Logger specific variables */
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

boot_config_context_populate_table devprg_config_context_global_values[] =
{
  {CONFIG_CONTEXT_HOST_IMAGE_ID,              PARAMETER_TYPE_VALUE, {SBL1_IMG, NULL},       {}                                                                                                         },
  {CONFIG_CONTEXT_BOOT_DEVICE,                PARAMETER_TYPE_VALUE, {NO_FLASH, NULL},       {}                                                                                                         },
  {CONFIG_CONTEXT_LOGGER_INTERFACE,           PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_logger_if_type),           boot_logger_get_interface},           },
  {CONFIG_CONTEXT_TIMER_INTERFACE,            PARAMETER_TYPE_PTR,   {},                     {NULL,                        sizeof(boot_timer_if_type),            boot_timer_get_interface},            },
  {CONFIG_CONTEXT_MEMORY_MGR_INTERFACE,       PARAMETER_TYPE_PTR,   {},                     {&memory_mgr_dal,             0,                                     NULL},                                },
  {CONFIG_CONTEXT_RESET_INTERFACE,            PARAMETER_TYPE_PTR,   {},                     {&reset_if,                   0,                                     NULL},                                },
  {CONFIG_CONTEXT_CRYPTO_INTERFACE,           PARAMETER_TYPE_PTR,   {},                     {&crypto_if,                  0,                                     NULL},                                },
  {CONFIG_CONTEXT_PLATFORMINFO_INTERFACE,     PARAMETER_TYPE_PTR,   {},                     {&platforminfo_if,            0,                                     NULL},                                },  
  {CONFIG_CONTEXT_UART_INTERFACE,             PARAMETER_TYPE_PTR,   {},                     {&uart_if,                    0,                                     NULL},                                },
  {CONFIG_CONTEXT_EDK2_MMU_INTERFACE,         PARAMETER_TYPE_PTR,   {},                     {&edk2_mmu_if,                0,                                     NULL},                                },
};

bl_error_boot_type devprg_populate_mem_map(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_edk2_mmu_if_type *edk2_mmu_if = NULL;

  ARM_MEMORY_REGION_DESCRIPTOR ramdump_memory_map[]=
  {
    { GCC_CLK_CTL_REG_REG_BASE,            GCC_CLK_CTL_REG_REG_BASE,           GCC_CLK_CTL_REG_REG_BASE_SIZE,                                    ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { REGISTER_REGION1_BASE,               REGISTER_REGION1_BASE,              REGISTER_REGION1_SIZE,                                            ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { SCL_AOP_DATA_RAM_BASE,               SCL_AOP_DATA_RAM_BASE,              SCL_AOP_DATA_RAM_SIZE,                                            ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { REGISTER_REGION2_BASE,               REGISTER_REGION2_BASE,              REGISTER_REGION2_SIZE,                                            ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { SCL_IMEM_BASE,                       SCL_IMEM_BASE,                      SCL_IMEM_SIZE,                                                    ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { (uint64)SHARED_IMEM_BASE,            (uint64)SHARED_IMEM_BASE,           (uint64)SHARED_IMEM_SIZE,                                         ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED_XN },
    { (uint64)SCL_BOOT_IMEM_BASE_ADDR,     (uint64)SCL_BOOT_IMEM_BASE_ADDR,    (uint64)SCL_BOOT_IMEM_START_XBL_UNUSED,                           ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { APSS_HM_BASE,                        APSS_HM_BASE,                       APSS_HM_BASE_SIZE,                                                ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { DDR_SS_BASE,                         DDR_SS_BASE,                        DDR_SS_BASE_SIZE,                                                 ARM_MEMORY_REGION_ATTRIBUTE_DEVICE },
    { QFPROM_CORR_REG_BASE,                QFPROM_CORR_REG_BASE,               QFPROM_CORR_REG_BASE_SIZE,                                        ARM_MEMORY_REGION_ATTRIBUTE_DEVICE_RO },
    { FUSE_CONTROLLER_SW_RANGE4_REG_BASE,  FUSE_CONTROLLER_SW_RANGE4_REG_BASE, FUSE_CONTROLLER_SW_RANGE4_REG_BASE_SIZE,                          ARM_MEMORY_REGION_ATTRIBUTE_DEVICE_RO },
    { DDR_MEM_BASE_1,                      DDR_MEM_BASE_1,                     DDR_MEM_SIZE_1,                                                   ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { DDR_MEM_BASE_2,                      DDR_MEM_BASE_2,                     DDR_MEM_SIZE_2,                                                   ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { (uint64)Image$$DEVPRG_CODE$$Base,    (uint64)Image$$DEVPRG_CODE$$Base,   (uint64)Image$$DEVPRG_CODE$$Length,                               ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_RO },
    { (uint64)Image$$DEVPRG_DATA_RO$$Base, (uint64)Image$$DEVPRG_DATA_RO$$Base,(uint64)Image$$DEVPRG_DATA_RO$$Length,                            ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN_RO },
    { (uint64)Image$$STACK$$Base,          (uint64)Image$$STACK$$Base,         (uint64)Image$$STACK$$Length,                                     ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
    { (uint64)Image$$DEVPRG_DATA_RW$$Base, (uint64)Image$$DEVPRG_DATA_RW$$Base,(uint64)Image$$DEVPRG_DATA_RW$$Length,                            ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK_XN },
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


void devprg_system_init(boot_handle *config_context_handle)
{
  boot_logger_if_type *logger_if;
  boot_registered_logger_if_type *logger_uart_if;
  bl_error_boot_type status = BL_ERR_NONE;
  DALResult dal_result;

  boot_edk2_mmu_if_type *edk2_mmu_if = NULL;
  uintnt external_uncached_heap_addr = (uintnt)(xbl_get_external_uncached_heap_addr());
  uintnt external_uncached_heap_size = xbl_get_external_uncached_heap_size();

  do
  {
    /* Calculate the SBL start time for use during boot logger initialization. */
    ramdump_start_time = CALCULATE_TIMESTAMP(HWIO_IN(TIMETICK_CLK));


    /* Initialize dal heap using internal memory */
    dal_result = dal_if.HeapInit((void *)xbl_get_external_cached_heap_addr(),
                                 xbl_get_external_cached_heap_size(),
                                 1);
    if(dal_result != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_DAL, BL_ERR_TBD_ERROR);
      break;
    }

    /* Initialize DAL, needs to be called before modules that uses DAL */
    dal_if.InitMod(NULL);

    status = boot_config_context_open(config_context_handle, &memory_mgr_dal);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_set_parameters(*config_context_handle, devprg_config_context_global_values, sizeof(devprg_config_context_global_values)/sizeof(boot_config_context_populate_table));
    if(status != BL_ERR_NONE)
    {
      break;
    }

    /* Initialize the stack protection canary */
    boot_init_stack_chk_canary();
    /* Initialize ramdump memory map */
    status = devprg_populate_mem_map(*config_context_handle);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    /* uart log init*/
    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_LOGGER_INTERFACE, (void *)&logger_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }

    status = boot_config_context_get_ptr(*config_context_handle, CONFIG_CONTEXT_EDK2_MMU_INTERFACE, (void **)&edk2_mmu_if);
    if(status != BL_ERR_NONE || edk2_mmu_if == NULL)
    {
      break;
    }

    if(edk2_mmu_if->ArmSetMemoryAttributes(external_uncached_heap_addr,
                                           external_uncached_heap_size,
                                           EFI_ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED_XN) != EFI_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MMU, BL_ERR_MMU_PGTBL_MAPPING_FAIL);
      break;
    }
    dal_result = dal_if.HeapInit((void *)external_uncached_heap_addr,
                                 external_uncached_heap_size,
                                 DALHEAP_UNCACHED);
    if (dal_result != DAL_SUCCESS)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_DAL, BL_ERR_INT_HEAP_INIT_FAIL);
      break;
    }

    /*initialize boot logger*/
    logger_if->init(*config_context_handle, &boot_log_data);

    status = boot_logger_uart_get_interface(&logger_uart_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }
	
	pm_infra_init();

    status = logger_if->register_logger(logger_uart_if);
    if(status != BL_ERR_NONE)
    {
      break;
    }
  }while(0);
  if(status != BL_ERR_NONE)
  {
    bl_err_if.error_handler(__FILE_BASENAME__, __LINE__, status);
  }
}

void devprg_firehose_entry(void);
VOID devprg_img_entry (void)
{
  boot_handle config_context_handle = NULL;
  memset(Image$$DEVPRG_DATA_ZI$$Base, 0, (uint32)(uintptr_t)Image$$DEVPRG_DATA_ZI$$Length);
  devprg_system_init(&config_context_handle);
  devprg_firehose_entry();
}

VOID XBLRamDumpMain( void *sbl_shared )
{
  (void) sbl_shared;
  devprg_img_entry();
}
void (*Main_entry)(void*) = XBLRamDumpMain;
