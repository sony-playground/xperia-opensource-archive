#ifndef BOOT_ERROR_IF_H
#define BOOT_ERROR_IF_H

/*===========================================================================

                 Boot Loader Error Handler Header File

GENERAL DESCRIPTION
  This header file contains declarations and definitions for the boot
  error handler interface.
    
Copyright 2007-2012, 2014-2022 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/02/22   rama    Saving context at the point of error
06/10/22   batta   Added BL_ERROR_GROUP_SLVCOMINFO_IF and BL_ERROR_GROUP_XRC_IF
06/21/22   sairaj  Added DDR Initialization error variable in enum
05/10/22   tmt     Add DTB Loader Library codes
01/18/22   rama    Added BL_ERROR_GROUP_MINIDUMP
01/05/22   rama    Added BL_ERROR_GROUP_CHIPINFO_if
07/09/21   rhy     Added BL_ERR_SAHARA_RAMDUMP_PIPO_RESTART and BL_ERR_RAMDUMP_RESTART
07/01/21   ds      MediaInitialization lib related changes
07/08/21   ck      Added BL_ERROR_GROUP_RESET
04/15/21   ds      changes for debuglib addition
03/16/21   ck      Added BL_ERROR_GROUP_CDT
01/22/21   rama    Added error group for buttons library
01/22/21   rhy     Added GET_ERROR_INFO
01/21/21   rhy     Added error group BL_ERROR_GROUP_SAHARA_CMD_HANDLER
01/20/21   rhy     Added BL_ERROR_GROUP_SAHARA_STATUS_MAP and BL_ERR_BOOT_SAHARA_PROTOCOL_FAIL
01/20/21   rhy     Added BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED
01/19/21   rhy     Added BL_ERROR_GROUP_RAMDUMP_TABLE
01/14/21   rama    Added error group for seclib and eud
01/05/21   ds      Added error group for wdog
12/02/20   ds      Added error group for xbl test mode library
11/13/20   rama    Added error group for mode and exit interfaces
11/01/20   ds      Blacklist feature support
08/28/20   tmt     Added error group for DTB/XBLConfig
08/06/20   ck      Added BL_ERR_IMAGE_SECURITY_BUSY and BL_ERR_UNSUPPORTED_SYNC_TYPE
07/27/20   rama    Added error group for PBL shared data
07/22/20   da      Added error codes in group BL_ERROR_GROUP_DDR
07/20/20   ck      Added BL_ERROR_GROUP_EEPROM_DEV
07/15/20   ck      Added error group BL_ERROR_GROUP_NAND 
05/13/20   ck      Added error group BL_ERROR_GROUP_PAGEDEV
04/20/20   rhy     Added IPA config context
03/30/20   aus     Added error codes for minidump
03/24/20   ck      Added error group BL_ERROR_GROUP_PAGEDEV            
02/24/20   ds      GET_ERROR_CODE changes to use line number and filename
03/28/19   yps     Add error code for MMU setting
07/06/18   vk      Add error code for heap
08/09/17   yps     Replaced Macro __FILE__ with __FILE_BASENAME__
06/01/17   daison  Added error code BL_ERR_DDI_SIZE_INVALID
06/24/16   kpa     Added error code BL_ERR_INVALID_DISPLAY_SIZE
06/23/16   digant  Added exception data,instruction,sp aborts code for aarch64
06/22/15   ck      Added error code BL_ERR_SHR_VAR_SIZE
06/22/15   ck      Added error codes BL_ERR_IMAGE_ARCH_UNKNOWN and BL_ERR_IMAGE_NOT_FOUND
06/22/15   as      Added error code BL_ERR_ECC_CONFIG
06/10/15   as      Added error code BL_ERR_DDR_SPD
03/25/15   ck      Added error code BL_ERR_ACCESS_CONTROL
10/29/14   ck      Added error code BL_ERR_INVALID_ENTRY_POINT
10/28/14   ck      Added HOB error codes
06/16/14   ck      Added error code BL_ERR_INT_OVERFLOW
05/09/14   kedara  Added error code BL_ERR_AARCH64_NOT_ENABLED, BL_ERR_MISALIGNMENT
                   BL_ERR_VALUE_TOO_LARGE, BL_ERR_ELF_CLASS_INVALID
04/01/14   wg      Added two new Authentication codes for 
                   SAFE 1.0 API migration
12/06/12   jz      Added error code BL_ERR_GET_CDT_FAIL
09/06/12   kpa     Added error code for Subsystem Self Authentication (ssa)
10/30/11   kpa     Added error code for Qfprom test framework  
09/20/11   kpa     Added error code for tpm hash population. 
09/13/11   kpa     Added error code for Rollback prevention feature 
04/07/11   dh      Added error code for DLOAD
08/04/10   aus     Added error code for invalid header
07/22/10   aus     Added error code for SBL error
07/15/10   dh      Modify BL_VERIFY to fix Klockwork error
06/23/10   plc     Add error code for fail to init PBL interface
05/26/10   plc     Added codes for secboot 3.0 merge, and include 
                   boot_comdef.h only if ! _ARM_ASM_
01/05/09   vtw     Added efs error codes.
09/22/09   vw      Added error codes for sd-boot support.
04/15/08   PS      Added enum type BL_ERR_IMG_SIZE_INVALID in bl_err_type
12/04/07   MJS     Initial revision.

============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/
typedef void (*boot_error_handler_ptr_type)
(
  const char* filename_ptr,     /* File this function was called from -
                                   defined by __FILE__ */
  uint32      line,             /* Line number this function was called
                                   from - defined by  __LINE__ */
  uint32      error             /* Enum that describes error type */
);

/*---------------------------------------------------------------------------
  Define XBL_SC ERROR types. This classifies different types of errors in XBL. 
 ---------------------------------------------------------------------------*/
typedef enum
{
  BL_ERROR_GROUP_GENERIC                     = 0x00000000,
  BL_ERROR_GROUP_BOOT                        = 0x01000000,
  BL_ERROR_GROUP_BOOT_RECOVERY               = 0x01110000,
  BL_ERROR_GROUP_BUSES                       = 0x02000000,
  BL_ERROR_GROUP_BAM                         = 0x03000000,
  BL_ERROR_GROUP_BUSYWAIT                    = 0x04000000,
  BL_ERROR_GROUP_CLK                         = 0x05000000,
  BL_ERROR_GROUP_CRYPTO                      = 0x06000000,
  BL_ERROR_GROUP_DAL                         = 0x07000000,
  BL_ERROR_GROUP_DEVPROG                     = 0x08000000,
  BL_ERROR_GROUP_DEVPROG_DDR                 = 0x10000000,
  BL_ERROR_GROUP_EFS                         = 0x11000000,
  BL_ERROR_GROUP_EFS_LITE                    = 0x12000000,
  BL_ERROR_GROUP_FLASH                       = 0x13000000,
  BL_ERROR_GROUP_HOTPLUG                     = 0x14000000,
  BL_ERROR_GROUP_HSUSB                       = 0x15000000,
  BL_ERROR_GROUP_ICB                         = 0x16000000,
  BL_ERROR_GROUP_LIMITS                      = 0x17000000,
  BL_ERROR_GROUP_MHI                         = 0x18000000,
  BL_ERROR_GROUP_PCIE                        = 0x20000000,
  BL_ERROR_GROUP_PLATFORM                    = 0x21000000,
  BL_ERROR_GROUP_PMIC                        = 0x22000000,
  BL_ERROR_GROUP_POWER                       = 0x23000000,
  BL_ERROR_GROUP_PRNG                        = 0x24000000,
  BL_ERROR_GROUP_QUSB                        = 0x25000000,
  BL_ERROR_GROUP_SECIMG                      = 0x26000000,
  BL_ERROR_GROUP_SECBOOT                     = 0x27000000,
  BL_ERROR_GROUP_SECCFG                      = 0x28000000,
  BL_ERROR_GROUP_SMEM                        = 0x30000000,
  BL_ERROR_GROUP_SPMI                        = 0x31000000,
  BL_ERROR_GROUP_SUBSYS                      = 0x32000000,
  BL_ERROR_GROUP_TLMM                        = 0x33000000,
  BL_ERROR_GROUP_TSENS                       = 0x34000000,
  BL_ERROR_GROUP_HWENGINES                   = 0x35000000,
  BL_ERROR_GROUP_IMAGE_VERSION               = 0x36000000,
  BL_ERROR_GROUP_SECURITY                    = 0x37000000,
  BL_ERROR_GROUP_STORAGE                     = 0x38000000,
  BL_ERROR_GROUP_SYSTEMDRIVERS               = 0x40000000,
  BL_ERROR_GROUP_DDR                         = 0x41000000,
  BL_ERROR_GROUP_EXCEPTIONS                  = 0x42000000,
  BL_ERROR_GROUP_MPROC                       = 0x43000000,
  BL_ERROR_GROUP_BOOT_SAHARA                 = 0x44000000,
  BL_ERROR_GROUP_DISPLAY                     = 0x45000000,
  BL_ERROR_GROUP_HEAP                        = 0x46000000,
  BL_ERROR_GROUP_IPA                         = 0x47000000,
  BL_ERROR_GROUP_SAHARA_DISPATCH_TBL         = 0x48000000,
  BL_ERROR_GROUP_SAHARA_CMD_HANDLER          = 0x49000000,
  BL_ERROR_GROUP_NAND                        = 0x4A000000,
  BL_ERROR_GROUP_EEPROM_DEV                  = 0x4B000000,
  BL_ERROR_GROUP_RAMDUMP_TABLE               = 0x4C000000,
  BL_ERROR_GROUP_SAHARA_STATUS_MAP           = 0x4D000000,
  
  BL_ERROR_GROUP_CONFIG_CONTEXT              = 0x80000000,
  BL_ERROR_GROUP_LOADER                      = 0x81000000,
  BL_ERROR_GROUP_ELF_LOADER                  = 0x82000000,

  BL_ERROR_GROUP_PLATFORMINFO                = 0x83000000,
  BL_ERROR_GROUP_COLDPLUG                    = 0x84000000,
  BL_ERROR_GROUP_BUS                         = 0x85000000,
  BL_ERROR_GROUP_TSENSOR                     = 0x86000000,
  BL_ERROR_GROUP_SEC_IMG                     = 0x87000000,
  BL_ERROR_GROUP_QUSB_LDR                    = 0x88000000,
  BL_ERROR_GROUP_PIMEM                       = 0x89000000,
  BL_ERROR_GROUP_VSENSE                      = 0x8A000000,
  BL_ERROR_GROUP_RAMDUMP                     = 0x8B000000,
  BL_ERROR_GROUP_MEMORY_MGR                  = 0x8C000000,
  BL_ERROR_GROUP_DDI                         = 0x8D000000,
  BL_ERROR_GROUP_UART                        = 0x8E000000,
  BL_ERROR_GROUP_QSEE                        = 0x8F000000,
  BL_ERROR_GROUP_VISUAL_INDICATOR            = 0x90000000,
  BL_ERROR_GROUP_CONFIG_DATA                 = 0x91000000,
  BL_ERROR_GROUP_DDR_INFO                    = 0x92000000,
  BL_ERROR_GROUP_LOGGER                      = 0x93000000,
  BL_ERROR_GROUP_TIMER                       = 0x94000000,
  BL_ERROR_GROUP_REGISTERED_LOGGER           = 0x95000000,
  BL_ERROR_GROUP_DLOAD_DEBUG                 = 0x96000000,
  BL_ERROR_GROUP_DLOAD_DUMP                  = 0x97000000,
  BL_ERROR_GROUP_RAM                         = 0x98000000,
  BL_ERROR_GROUP_SBL                         = 0x99000000,
  BL_ERROR_GROUP_MMU                         = 0x9A000000,
  BL_ERROR_GROUP_EFS_COOKIE                  = 0x9B000000,
  BL_ERROR_GROUP_XBL_CONFIG                  = 0x9C000000,
  BL_ERROR_GROUP_STI                         = 0x9D000000,
  BL_ERROR_GROUP_WHITELIST                   = 0x9E000000,
  BL_ERROR_GROUP_BLOCKDEV                    = 0x9F000000,
  BL_ERROR_GROUP_BOOT_MEDIA_IF               = 0xA0000000,
  BL_ERROR_GROUP_MBN_LOADER                  = 0xA1000000,
  BL_ERROR_GROUP_LOADER_IF                   = 0xA2000000,
  BL_ERROR_GROUP_BOOTSTATS                   = 0xA3000000,
  BL_ERROR_GROUP_PAGEDEV                     = 0xA4000000,
  BL_ERROR_GROUP_EEPROMDEV                   = 0xA5000000,
  BL_ERROR_GROUP_HFATDEV                     = 0xA5100000,
  BL_ERROR_GROUP_PBL_SHARED_DATA             = 0xA6000000,
  BL_ERROR_GROUP_BLACKLIST                   = 0xA7000000,
  BL_ERROR_GROUP_EXIT_IF                     = 0xA8000000,
  BL_ERROR_GROUP_MODE_IF                     = 0xA9000000,
  BL_ERROR_GROUP_TEST_MODE                   = 0xAA000000,
  BL_ERROR_GROUP_CPUCP_IF                    = 0xAB000000,
  BL_ERROR_GROUP_WDOGTMR                     = 0xAC000000,
  BL_ERROR_GROUP_EUD                         = 0xAD000000,
  BL_ERROR_GROUP_SECLIB                      = 0xAE000000,
  BL_ERROR_GROUP_BUTTONS                     = 0xAF000000,
  BL_ERROR_GROUP_CDT                         = 0xB0000000,
  BL_ERROR_GROUP_DBGINFOLIB                  = 0xB1000000,
  BL_ERROR_GROUP_RESET                       = 0xB2000000,
  BL_ERROR_GROUP_MEDIA_INITIALIZATION        = 0xB3000000,
  BL_ERROR_GROUP_STORE_LOGS                  = 0xB4000000,
  BL_ERROR_GROUP_CHIPINFO_IF                 = 0xB5000000,
  BL_ERROR_GROUP_MINIDUMP                    = 0xB6000000,
  BL_ERROR_GROUP_SLVCOMINFO_IF               = 0xB7000000,
  BL_ERROR_GROUP_XRC_IF                      = 0xB8000000,
  BL_ERROR_GROUP_MAX                         = 0x7FFFFFFF
} bl_error_group_type;

/*---------------------------------------------------------------------------
 ERRORS FROM BOOT
 ---------------------------------------------------------------------------*/
typedef enum
{
  BL_ERR_NONE,
  BL_ERR_NULL_PTR_PASSED                     = 0x0001,
  BL_ERR_MISALIGNMENT                        = 0x0002,
  BL_ERR_BUFFER_SIZE_TOO_SMALL               = 0x0003,
  BL_ERR_SUBSYS_BOOT_FAIL                    = 0x0004,
  
  BL_ERR_CODE_ROLLBACK_VERSION_VERIFY_FAIL   = 0x0005,
  BL_ERR_CODE_ROLLBACK_VERSION_BLOW_FAIL     = 0x0006,
  
  BL_ERR_AUTH_DISABLED                       = 0x0007,  
  BL_ERR_HASH_TBL_AUTH_FAIL                  = 0x0008,
  BL_ERR_IMG_SIZE_INVALID                    = 0x0010,
           
  BL_ERR_CDB_COPY_ERROR                      = 0x0011,
  BL_ERR_CDT_SIZE_INVALID                    = 0x0012,
  BL_ERR_CDT_PARAMS_SIZE_INVALID             = 0x0013,
  
  BL_ERR_CLOBBER_PROTECTION_VIOLATION        = 0x0014,
  BL_ERR_FLASH_READ_FAIL                     = 0x0015,
  BL_ERR_IMG_SIZE_TOO_BIG                    = 0x0016,
  BL_ERR_SDC_INVALID_SIZE                    = 0x0017,
  BL_ERR_SDCC_WRITE_FAIL                     = 0x0018,
  BL_ERR_SDC_INVALID_PARTI                   = 0x0020,
  
  BL_ERR_IMG_HASH_FAIL                       = 0x0021,
  BL_ERR_ELF_HASH_MISMATCH                   = 0x0022,
  BL_ERR_INVALID_HASH_PTR                    = 0x0023,
  BL_ERR_TPM_HASH_BLK_STR_FAIL               = 0x0024,
  BL_ERR_INVALID_SECDAT_BUFFER               = 0x0025,
  
  BL_ERR_FLASH_DRIVER                        = 0x0026,
  BL_ERR_BUFFER_SIZE_MISMATCH                = 0x0027,
  BL_ERR_BOOT_FLASH_ACCESS                   = 0x0028,
  BL_ERR_PARTI_TABLE_NOT_FOUND               = 0x0030,
  BL_ERR_PARTI_NAME_NOT_FOUND                = 0x0031,
  BL_ERR_PARTI_ENTRY_NOT_FOUND               = 0x0032,
  BL_ERR_WRG_PARTI_ENTRY_NAME_FMT            = 0x0033,

  BL_ERR_FAILED_TO_COPY_IMG_HDR              = 0x0034,
  BL_ERR_IMAGE_HDR_INVALID                   = 0x0035,
  BL_ERR_ELF_CLASS_INVALID                   = 0x0036,
  BL_ERR_ELF_INVAL_PARAM                     = 0x0037,

  BL_ERR_IMGID_NOT_FOUND                     = 0x0038,
  BL_ERR_IMG_HDR_INVALID                     = 0x0040,
  BL_ERR_IMG_NOT_FOUND                       = 0x0041,
  BL_ERR_IMG_SIZE_ZERO                       = 0x0042,
  BL_ERR_RESOURCE_NOT_AVAILABLE              = 0x0043,

  BL_ERR_MMU_PGTBL_MAPPING_FAIL              = 0x0044,
  BL_ERR_MMU_PGTBL_CPY_FAIL                  = 0x0045,
       
  BL_ERR_QFPROM_TEST_FRAMEWORK_FAIL          = 0x0046,
  BL_ERR_FAIL_ALLOCATE_SMEM                  = 0x0047,
  BL_ERR_INVALID_COOKIE_FILE_NAME            = 0x0048,
  BL_ERR_INVALID_ENTRY_POINT                 = 0x0050,
       
  BL_ERR_BUSY_WAIT_INIT_FAIL                 = 0x0051,
  BL_ERR_CPU_CLK_INIT_FAIL                   = 0x0052,
  BL_ERR_DISABLE_CLOCK_FAIL                  = 0x0053,
  BL_ERR_INIT_GPIO_FOR_TLMM_CONFIG_FAIL      = 0x0054,
     
  BL_ERR_SECBOOT_FTBL_INIT_FAIL              = 0x0055,
       
  BL_ERR_EFS_CLOSE_FAIL                      = 0x0056,
  BL_ERR_EFS_INVALID_HANDLE                  = 0x0057,
       
  BL_ERR_HOTPLUG                             = 0x0058,
  BL_ERR_RAM_DUMP_FAIL                       = 0x0060,
  BL_ERR_INVALID_FILE_NAME                   = 0x0061,
  BL_ERR_COOKIE_TOO_BIG                      = 0x0062,
  BL_ERR_UNSUPPORTED_IMG                     = 0x0063,
  BL_ERR_FEATURE_NOT_SUPPORTED               = 0x0064,
  BL_ERR_IMG_SECURITY_FAIL                   = 0x0065,
  BL_ERR_UNSUPPORTED_HASH_ALGO               = 0x0066,
  BL_ERR_NAND_TRANS_INTERFACE_NOT_FOUND      = 0x0067,
  BL_ERR_SDCC_TRANS_INTERFACE_NOT_FOUND      = 0x0068,
  BL_ERR_INVALID_SECTOR_SIZE                 = 0x0070,
  BL_ERR_GET_CDT_FAIL                        = 0x0071,
  BL_ERR_OTHERS                              = 0x0072,
  BOOT_PRE_DDR_CLK_INIT_FAIL                 = 0x0073,
  BL_ERR_INTEGER_OVERFLOW                    = 0x0074,
  BL_ERR_VSENS_INIT_FAIL                     = 0x0075,
  BL_ERR_VSENSE_COPY_TO_SMEM_FAIL            = 0x0076,
  BL_ERR_IMAGE_ARCH_UNKNOWN                  = 0x0077,
          
  BL_ERR_HOB_CREATE_FAIL                     = 0x0078,
  BL_ERR_HOB_STORE_FAIL                      = 0x0080,
  BL_ERR_HOB_BOOT_MODE_FAIL                  = 0x0081,
  BL_ERR_HOB_GUID_FAIL                       = 0x0082,
          
  BL_ERR_BOOT_SAHARA_INIT_FAIL               = 0x0083,
  BL_ERR_CORE_VERIFY                         = 0x0084,
  BL_ERR_INVALID_ELF_FORMAT                  = 0x0085,
  BL_ERR_INVALID_DISPLAY_SIZE                = 0x0086,

  BL_ERR_INT_HEAP_INIT_FAIL                  = 0x0087,
  BL_ERR_INT_HEAP_DEINIT_FAIL                = 0x0088,
  BL_ERR_EXT_HEAP_INIT_FAIL                  = 0x0089,
  BL_ERR_EXT_HEAP_DEINIT_FAIL                = 0x008A,

  BL_ERR_MMU_INVALID_ADDRESS                 = 0x008B,
  BL_ERR_MMU_INVALID_SIZE                    = 0x008C,

  /* Ram dump, Mini dump */
  BL_ERR_RAMDUMP_IMAGE_EXIT                  = 0x0090,
  BL_ERR_RAMDUMP_NOT_COLLECTED               = 0x0091,
  BL_ERR_MD_REGISTER_FAIL                    = 0x0092,
  BL_ERR_MD_ADD_REGION_FAIL                  = 0x0093,
  BL_ERR_RD_UNSUPPORTED_MODE                 = 0x0094,
  BL_ERR_INVALID_TABLE_ENTRY_PASSED          = 0x0095,
  BL_ERR_INVALID_MINIDUMP_TABLE_ENTRY_PASSED = 0x0096,

  BL_ERR_XCFG_OPEN_FAIL                      = 0x0800,
  BL_ERR_XCFG_READ_FAIL                      = 0x0801,
  BL_ERR_MEMORY_FREE_FAIL                    = 0x0802,
  BL_ERR_NO_FDT_HANDLE                       = 0x0803,
  BL_ERR_FDT_SET_BLOB_FAIL                   = 0x0804,
  BL_ERR_FDT_GET_BLOB_FAIL                   = 0x0805,
  BL_ERR_CHIPINFO_FAIL                       = 0x0806,
  BL_ERR_PLATFORMINFO_FAIL                   = 0x0807,
  BL_ERR_DTB_CARVEOUT_2_SMALL                = 0x0808,
  BL_ERR_NO_DTB_4_UEFI                       = 0x0809,

  BL_ERR_INVALID_PARAMETER                   = 0x1000,
  BL_ERR_MEMORY_ALLOC_FAIL                   = 0x1001,
  BL_ERR_INTERFACE_FAILURE                   = 0x1002,
  BL_ERR_ATTRIBUTE_FAILURE                   = 0x1003,
  BL_ERR_UNINITIALIZED_VARIABLE              = 0x1004,
  BL_ERR_TOO_MANY_ENTRIES                    = 0x1005,
  BL_ERR_TOO_MEMORY_FAILURE                  = 0x1006,
  BL_ERR_TBD_ERROR                           = 0x1007,
  BL_ERR_INITIALIZATION_ERROR                = 0x1008,
  BL_ERR_INVALID_HANDLE                      = 0x1009,
  BL_ERR_BUFFER_OVERFLOW                     = 0x1010,
  BL_ERR_NO_FLASH                            = 0x1011,
  BL_ERROR_OPEN_GPT_PARTITION_FAIL           = 0x1012,
  BL_ERROR_GET_DDR_TRAINING_DATA_FAIL        = 0x1013,
  BL_ERR_IMAGE_SECURITY_BUSY                 = 0x1014,
  BL_ERR_UNSUPPORTED_SYNC_TYPE               = 0x1015,
  BL_ERR_MEMORY_DEALLOC_FAIL                 = 0x1016,
  BL_ERR_RAMDUMP_COLLECTION_NOT_SUPPORTED    = 0x1017,
  BL_ERR_GET_LOG_DATA_FAIL                   = 0x1018,
  BL_ERR_DISPLAY_INIT_FAIL                   = 0x1019,
  BL_ERR_BOOT_SAHARA_PROTOCOL_FAIL           = 0x101A,
  BL_ERR_COOKIE_FILE_NOT_FOUND               = 0x101B,
  BL_ERR_RAMDUMP_COLLECTED_REBOOT            = 0x101C,
  BL_ERR_RAMDUMP_COLLECTED_WARM_REBOOT       = 0x101D,
  BL_ERR_COMMAND_NOT_RECOGNIZED              = 0x101E,
  BL_ERR_SAHARA_RAMDUMP_PIPO_RESTART         = 0x101F,
  BL_ERR_RAMDUMP_RESTART                     = 0x1020,
  BL_ERR_NOT_INITIALIZED                     = 0x1021,
  BL_ERROR_RESTORE_PARTITION_GUID_FAIL       = 0x1022,
  BL_ERR_INVALID_LUN                         = 0x1023,

  BL_ERR_CUSTOM_ERRORS_START                 = 0x2000,

  BL_ERR_MAX                                 = 0x7FFF
}bl_error_boot_type;

typedef enum
{
  BL_ERR_DDR_SET_PARAMS_FAIL                         = 0x0001,
  BL_ERR_DDR_INFO_NOT_SET                            = 0x0003,
  BL_ERR_PASS_DDR_TRAINING_DATA_TO_DDR_DRIVER_FAIL   = 0x0004,
  BL_ERR_DDR_TRAINING_DATA_SIZE_INVALID              = 0x0005,
  BL_ERR_INVALID_CLOCK_PLAN                          = 0x0006,
  BL_ERR_DDR_NULL_TRAINED_PARAMS                     = 0x0007,
  BL_ERR_DDR_SPD                                     = 0x0008,
  BL_ERR_DDI_SIZE_INVALID                            = 0x0009,
  BL_ERR_DDR_GET_PARAM_BUFFER_SMALL                  = 0x0010,
  BL_ERR_DDR_INVALID_REGION_IDX                      = 0x0011,
  BL_ERR_DDR_PARAM_BUFFER_NULL                       = 0x0012,
  BL_ERR_DDR_INVALID_PARAM_ID                        = 0x0013,
  BL_ERR_DDR_INITIALIZATION_ERROR                    = 0x0014,
  BL_ERR_DDR_MAX                                     = 0x7FFF
}bl_error_ddr_type;

typedef enum
{
  BL_ERR_UNDEF_INSTR            = 0x0001,
  BL_ERR_SWI                    = 0x0002,
  BL_ERR_PREFETCH_ABORT         = 0x0003,
  BL_ERR_DATA_ABORT             = 0x0004,
  BL_ERR_RESERVED_HANDLER       = 0x0005,
  BL_ERR_IRQ                    = 0x0006,
  BL_ERR_FIQ                    = 0x0007,
  BL_ERR_C_LIB_RT               = 0x0008,
  BL_ERR_SYS                    = 0x0009,
  BL_EXCEPTION_I_ABORT          = 0x0021,      /* Exception from an instruction abort without a change in level */
  BL_EXCEPTION_D_ABORT          = 0x0025,      /* Exception from a data abort without a change in level */
  BL_ERR_EXCEPTION_MAX          = 0x7FFF
}bl_error_exceptions_type;

/* The BL error callback function */
typedef void (*bl_error_callback_func_type)
(
  void *data_ptr
);

/* Structure for storing error handler callback data */
typedef struct bl_error_callback_node_type
{
  struct
  {
    bl_error_callback_func_type cb_func;
    void *data_ptr;
  } data;

  struct bl_error_callback_node_type *next_ptr;
} bl_error_callback_node_type;

/* The BL error interface */
typedef struct boot_error_if_type
{
/*===========================================================================

**  Function :  error_handler

** ==========================================================================
*/
/*!
* 
*   @brief
*     This function handles boot errors.
* 
*   @par Dependencies
*     None
*   
*   @retval
*     None
* 
*   @par Side Effects
*     None
* 
*/
boot_error_handler_ptr_type error_handler;

/*===========================================================================

**  Function :  install_callback

** ==========================================================================
*/
/*!
* 
*   @brief
*     Installs a callback that will be executed when an error occurs.
* 
*     NOTE: The caller must allocate a node for use in the error callback
*           linked list data structure, but does not need to initialize
*           the structure, as this function does the initialization of
*           the linked list data structure.
* 
*   @par Dependencies
*     None
*   
*   @retval
*     None
* 
*   @par Side Effects
*     None
* 
*/
  void (*install_callback)
  (
    bl_error_callback_func_type cb_func,  /* The callback function */
    void *data_ptr,       /* Data to pass to the callback function */
    bl_error_callback_node_type *node_ptr /* Data structure allocated by
                                        caller to store linked list node */
  );
} boot_error_if_type;

/* The global boot error interface structure */
extern boot_error_if_type bl_err_if;


/* get_error_code function pointer */
typedef bl_error_boot_type (*get_error_code_fn_ptr)(uint32, uint32, char*, uint32);

/* clear_error_code function pointer */
typedef void (*clear_error_code_fn_ptr)(void);

/* pointer to the get_error_code function */
extern get_error_code_fn_ptr get_error_code_ptr;

/* pointer to the clear_error_code function */
extern clear_error_code_fn_ptr clear_error_code_ptr;

/* get_error_info function pointer */
typedef bl_error_boot_type (*get_error_info_fn_ptr)(void);

/* pointer to get error code from error_info */
extern get_error_info_fn_ptr get_error_info_ptr;

/* set_error_code function pointer */
typedef bl_error_boot_type (*set_error_code_fn_ptr) (bl_error_boot_type);

/* pointer to the set_error_code function */
extern set_error_code_fn_ptr set_error_code_ptr;
/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

**  Macro :  bl_verify

** ==========================================================================
*/
/*!
* 
* @brief
*   Given a boolean expression, this macro will verify the condition is TRUE
*   and do nothing if the condition is TRUE, otherwise it will call the
*   SBL error handler.
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   This macro never returns if the condition is FALSE.
* 
*/
/*The forever loop after error_handler will never be executed, it is added to fix klockwork warning*/
#define BL_VERIFY( xx_exp, error_type ) \
            do { \
               if( !(xx_exp) ) \
               { \
                 get_error_code_ptr(0, error_type, __FILE_BASENAME__, __LINE__); \
                 bl_err_if.error_handler( __FILE_BASENAME__, __LINE__, \
                                        ( (uint32) ( error_type ) ) ); \
                 while(1) \
                 { \
                 } \
               } \
            } while(0)

/*===========================================================================

**  Macro :  bl_err_fatal

** ==========================================================================
*/
/*!
* 
* @brief
*   This macro calls the error handler.
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   This macro never returns.
* 
*/
/*The forever loop after error_handler will never be executed, it is added to fix klockwork warning*/
#define BL_ERR_FATAL( error_type )  \
            do{ \
                get_error_code_ptr(0, error_type, __FILE_BASENAME__, __LINE__); \
                bl_err_if.error_handler( __FILE_BASENAME__, __LINE__, \
                                       ( (uint32) error_type ) ); \
                while(1) \
                { \
                } \
              } while (0)

#endif  /* BOOT_ERROR_IF_H */

/*===========================================================================

**  Macro :  GET_ERROR_CODE

** ==========================================================================
*/
/*!
* 
* @brief
*   This macro sets the line numer and file name for tracking error 
*   and returns the OR(|) of the group with error.
* 
* @par Dependencies
*   None
*   
* @retval
*   OR of group and error
* 
* 
*/
/*The forever loop after error_handler will never be executed, it is added to fix klockwork warning*/
#define GET_ERROR_CODE(group, error) ((*get_error_code_ptr)(((uint32)group),((uint32)error),__FILE_BASENAME__, __LINE__))

/*===========================================================================

**  Macro :  GET_ERROR_INFO

** ==========================================================================
*/
/*!
* 
* @brief
*   This macro gets the error code from error_info
* 
* @par Dependencies
*   None
*   
* @retval
*   OR of group and error
* 
* 
*/
#define GET_ERROR_INFO (*get_error_info_ptr)()

/*===========================================================================

**  Macro :  CLEAR_ERROR_CODE

** ==========================================================================
*/
/*!
* 
* @brief
*   This macro clears the error info
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* 
*/
/*The forever loop after error_handler will never be executed, it is added to fix klockwork warning*/
#define CLEAR_ERROR_CODE (*clear_error_code_ptr)()

#define SET_ERROR_CODE(error_code) (*set_error_code_ptr)((bl_error_boot_type)error_code)

/*===========================================================================

**  Function :  boot_cache_flush_boot_regions

** ==========================================================================
*/
/*!
* 
* @brief
*   API that flushes boot log,ZI and RW regions.
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
boolean boot_cache_flush_boot_regions(void);
