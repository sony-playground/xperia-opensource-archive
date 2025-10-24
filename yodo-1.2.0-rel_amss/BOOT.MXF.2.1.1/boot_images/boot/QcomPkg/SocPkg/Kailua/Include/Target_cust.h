#ifndef _TARGET_CUST_H
#define _TARGET_CUST_H

/*===========================================================================

                                Target_cust
                                Header File

GENERAL DESCRIPTION
  This header file contains target specific declarations and definitions

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2018-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   --------     ----------------------------------------------------------
07/08/22   rama         Added AOP CMD DB base and size
08/16/21   cm           Added SCL_RAMDUMP_DDR_BASE
07/23/21   rama         Added ddr_dt_log_region related macros
12/01/20   yps          Added RAMDUMP_EXTERNAL_HEAP_SIZE 
11/06/20   ds           Blacklist and flex whitelist feature support
11/03/20   yps          update DDR region base on memory map V3
10/19/20   rama         Added XBL_CFG_BOOT_IMEM_REGION_BASE
09/22/20   ck           Added heap sizes
07/31/20   ds           add tme mbox region
07/28/20   ds           waipio updates for whitelist and mem regions
07/17/20   ds           waipio updates for memmap and rumi validation
06/24/20   ds           waipio update for memmap and hwio
03/27/19   c_vkuppa     Align buffer to cache line length
01/22/19   yps          Clean unused definitions
08/29/18   msantos      Added SBL crash dump region
07/30/18   ds           Initial version for SM8250 with memory map update
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/

#include "../Include/Soc_cust.h"
/*===========================================================================
              DEFINES FOR TARGET (equivalent to <target>.builds src)
===========================================================================*/
#define REGISTER_REGION1_BASE             0x00100000
#define REGISTER_REGION1_SIZE             0x0AFE0000

#define REGISTER_REGION2_BASE             0x0B0E8000
#define REGISTER_REGION2_SIZE             0x04F18000

#define SCL_IMEM_BASE                    0x14680000
#define SCL_IMEM_SIZE                    SIZE_176KB
#define SCL_IMEM_UNUSED_REGION_SIZE      SIZE_4KB

#define SCL_BOOTROM_MEMORY_REGION         (SIZE_100KB)
#define SCL_BOOT_IMEM_START_XBL_UNUSED    SCL_BOOTROM_MEMORY_REGION

/* SBL's DDR section is shared by Loader DDR Data and minidump table*/
#define SCL_SBL1_DDR_BASE                0xD8100000
/* 256KB region in DDR reserved for XBL_SC DDR ZI and RW regions */
#define SCL_SBL1_DDR_SIZE                SIZE_256KB

#define SCL_SBL1_DDR_DATA_BASE           SCL_SBL1_DDR_BASE
#define SCL_SBL1_DDR_DATA_SIZE           SIZE_64KB
#define SCL_SBL1_DDR_ZI_BASE             (SCL_SBL1_DDR_DATA_BASE + SCL_SBL1_DDR_DATA_SIZE)  
#define SCL_SBL1_DDR_ZI_SIZE             SIZE_172KB

#define SCL_BOOT_MEMORY_RESTRICT_REGION_BASE (DDR_MEM_BASE_2 + DDR_MEM_SIZE_2)

#undef SCL_AOP_BASE
#undef SCL_AOP_SIZE
#undef AOP_CFG_BASE
#undef AOP_CFG_SIZE

#define SCL_AOP_BASE                     0x81C00000
#define SCL_AOP_SIZE                     SIZE_384KB
#define SCL_AOP_CMD_DB_BASE              SCL_AOP_BASE + SCL_AOP_SIZE
#define SCL_AOP_CMD_DB_SIZE              SIZE_128KB
#define AOP_CFG_BASE                     SCL_AOP_CMD_DB_BASE + SCL_AOP_CMD_DB_SIZE
#define AOP_CFG_SIZE                     SIZE_128KB

#undef SCL_pIMEM_BASE
#undef SCL_pIMEM_SIZE

#undef SCL_SHRM_MEM_SHRM_BASE
#undef SCL_SHRM_MEM_SHRM_SIZE

// SHRM memory that needs to be dumped
#define SHRM_DMEM_SHRM_DRAM_BASE        0x24050000
#define SHRM_DMEM_SHRM_DRAM_SIZE        SIZE_64KB

#define SHRM_IMEM_SHRM_IRAM_BASE        0x24040000
#define SHRM_IMEM_SHRM_IRAM_SIZE        SIZE_64KB

#define SHRM_TOTAL_DUMP_MEM_SIZE (SHRM_DMEM_SHRM_DRAM_SIZE + SHRM_IMEM_SHRM_IRAM_SIZE)

#undef  SCL_SHARED_RAM_BASE
#define SCL_SHARED_RAM_BASE              0x81D00000

#define XBL_DDR_LOG_DT_REGION_BASE       0x81A00000
#define XBL_DDR_LOG_DT_REGION_SIZE       SIZE_256KB

/* RAMDUMP's DDR section */
#undef  SCL_RAMDUMP_DDR_BASE
#define SCL_RAMDUMP_DDR_BASE             0x81A40000

#define XBL_DDR_LOG_REGION_BASE          XBL_DDR_LOG_DT_REGION_BASE
#define XBL_DDR_LOG_REGION_SIZE          SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE

#define XBL_DDR_DT_REGION_BASE           (XBL_DDR_LOG_REGION_BASE+XBL_DDR_LOG_REGION_SIZE)
#define XBL_DDR_DT_REGION_SIZE           (XBL_DDR_LOG_DT_REGION_SIZE-XBL_DDR_LOG_REGION_SIZE)

//#undef BOOT_TEMP_CHECK_THRESHOLD_DEGC

/* IPA Ramdump memory regions */
//#define SCL_IPA_IU_BASE    0x03FA0000
#undef  SCL_IPA_IU_SIZE
#define SCL_IPA_IU_SIZE     0xDF00

//#define SCL_IPA_SRAM_BASE  0x03F50000
#undef  SCL_IPA_SRAM_SIZE
#define SCL_IPA_SRAM_SIZE  20480

//#define SCL_IPA_MBOX_BASE  0x03FC2000
#undef  SCL_IPA_MBOX_SIZE
#define SCL_IPA_MBOX_SIZE  256

//#define SCL_IPA_GSI_BASE   0x03E06000
#undef  SCL_IPA_GSI_SIZE
#define SCL_IPA_GSI_SIZE   8152

//#define SCL_IPA_HRAM_BASE  0x03F60000
#undef  SCL_IPA_HRAM_SIZE
#define SCL_IPA_HRAM_SIZE  102400

//#define SCL_IPA_SEQ_BASE   0x03F81000
#undef  SCL_IPA_SEQ_SIZE
#define SCL_IPA_SEQ_SIZE   1128

//IPA Memory Region
#define IPA_MEMORY_REGION_TABLE MEMORY_REGION20,MEMORY_REGION21,MEMORY_REGION22,MEMORY_REGION23,MEMORY_REGION24,MEMORY_REGION25,MEMORY_REGION_LAST

#define SLAVE_MEMORY_REGION_TABLE MEMORY_REGION_LAST
#define SCL_SLAVE_MEMORY_RESTRICT_REGION_BASE  0x2000000000

#define TSENS_DEVCFG_DISABLE

#endif  /* _TARGET_CUST_H */
