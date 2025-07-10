#ifndef _TARGET_CUST_H
#define _TARGET_CUST_H

/*===========================================================================

                                Target_cust
                                Header File

GENERAL DESCRIPTION
  This header file contains target specific declarations and definitions

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2018-2021,2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   --------     ----------------------------------------------------------
07/23/21   rama         Added ddr_dt_log_region related macros
03/03/21   ds           V6 memmap change
12/01/20   yps          Added RAMDUMP_EXTERNAL_HEAP_SIZE 
11/06/20   ds           Blacklist and flex whitelist feature support
11/03/20   yps          update DDR region base on memory map V3
10/19/20   rama         Added XBL_CFG_BOOT_IMEM_REGION_BASE
09/22/20   ck           Added heap sizes
07/31/20   ds           add tme mbox region
07/28/20   ds           clarence updates for whitelist and mem regions
07/17/20   ds           clarence updates for memmap and rumi validation
06/24/20   ds           clarence update for memmap and hwio
03/27/19   c_vkuppa     Align buffer to cache line length
01/22/19   yps          Clean unused definitions
08/29/18   msantos      Added SBL crash dump region
07/30/18   ds           Initial version for SM8250 with memory map update
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/

#include "Soc_cust.h"
/*===========================================================================
              DEFINES FOR TARGET (equivalent to <target>.builds src)
===========================================================================*/
#define REGISTER_REGION1_BASE             0x00100000
#define REGISTER_REGION1_SIZE             0x0AFE0000

#define REGISTER_REGION2_BASE             0x0B0E8000
#define REGISTER_REGION2_SIZE             0x04F18000

#define SCL_IMEM_BASE                    0x14680000
#define SCL_IMEM_SIZE                    SIZE_172KB
#define SCL_IMEM_UNUSED_REGION_SIZE      0x0

#define SCL_BOOTROM_MEMORY_REGION         (SIZE_100KB)
#define SCL_BOOT_IMEM_START_XBL_UNUSED    SCL_BOOTROM_MEMORY_REGION

#define AOSS_ISLAND_RAM_BASE             0x0EE10000
#define AOSS_ISLAND_RAM_SIZE             0x0

/* SBL's DDR section is shared by Loader DDR Data and minidump table*/
#define SCL_SBL1_DDR_BASE                0xA6E00000
/* 256KB region in DDR reserved for XBL_SC DDR ZI and RW regions */
#define SCL_SBL1_DDR_SIZE                SIZE_256KB

#define SCL_SBL1_DDR_DATA_BASE           SCL_SBL1_DDR_BASE
#define SCL_SBL1_DDR_DATA_SIZE           SIZE_64KB
#define SCL_SBL1_DDR_ZI_BASE             (SCL_SBL1_DDR_DATA_BASE + SCL_SBL1_DDR_DATA_SIZE)  
#define SCL_SBL1_DDR_ZI_SIZE             SIZE_172KB

#define SCL_BOOT_MEMORY_RESTRICT_REGION_BASE (DDR_MEM_BASE_2 + DDR_MEM_SIZE_2)

// Clock Group Name
#define CLK_FREQ_GRP_NAME  "apss"

// SHRM memory that needs to be dumped

#define SHRM_DMEM_SHRM_DRAM_BASE  0x19050000
#define SHRM_DMEM_SHRM_DRAM_SIZE  SIZE_48KB

#define SHRM_IMEM_SHRM_IRAM_BASE  0x19040000
#define SHRM_IMEM_SHRM_IRAM_SIZE  SIZE_48KB

#define SHRM_TOTAL_DUMP_MEM_SIZE  SIZE_48KB

#define XBL_DDR_LOG_DT_REGION_BASE       0x80600000
#define XBL_DDR_LOG_DT_REGION_SIZE       SIZE_256KB

#define XBL_DDR_LOG_REGION_BASE          XBL_DDR_LOG_DT_REGION_BASE
#define XBL_DDR_LOG_REGION_SIZE          SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE

#define XBL_DDR_DT_REGION_BASE           (XBL_DDR_LOG_REGION_BASE+XBL_DDR_LOG_REGION_SIZE)
#define XBL_DDR_DT_REGION_SIZE           (XBL_DDR_LOG_DT_REGION_SIZE-XBL_DDR_LOG_REGION_SIZE)

#endif  /* _TARGET_CUST_H */
