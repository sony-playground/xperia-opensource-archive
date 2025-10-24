/*
 * Copyright 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

/* @file boot_ramdump_target.c
 *
 * This module passes the target specific memory debug information
 * to ramdumper.
 */

#ifdef FEATURE_SONY_RAMDUMP

#include "boot_target.h"
#include "boot_ramdump.h"
#include "boot_dload_debug.h"
#include "boot_shared_imem_cookie.h"
#include "sbl1_hw.h"
#include "boot_util.h"
#include "pm_pbs.h"
#include <boot_ramdump_wrapper_apis.h>
#include <Library/DBIDump.h>
#include <string.h>
#include <Base.h>

static boolean boot_ramdump_get_region_name(uint64 paddr,
                                            uint64 size, uint8 *name)
{
  uint32 i = 0;
  uint32 num_regions = dload_mem_debug_num_ent();

  while(num_regions)
  {
    uint64 start, end;
    start = dload_mem_debug_mem_base(i);
    end = dload_mem_debug_mem_base(i) + dload_mem_debug_mem_length(i);
    if((paddr >= start) && ((paddr + size) <= end))
    {
      strlcpy((char *)name, dload_mem_debug_filename(i), MAX_NAME_LEN);
      return TRUE;
    }
    num_regions--;
    i++;
  }

  return FALSE;
}

static void boot_ramdump_backup_ddr_regions(void)
{
  struct ramdump_memdesc_region region;

  /* Backup SMEM area */
  region.flags = CORE_DUMP_REGION_FLAG;
  region.phys_addr = SCL_SHARED_RAM_BASE;
  region.size = SCL_SHARED_RAM_SIZE;
  strlcpy((char *)&region.name, "smemcore", MAX_NAME_LEN);
  boot_ramdump_add_region(&region);

  /* Backup QSEE area and Mark as tzcore in memdesc */
  region.flags = CORE_DUMP_REGION_FLAG;
  region.phys_addr =  SCL_QSEE_CODE_BASE;
  region.size = SCL_QSEE_TOTAL_SIZE;
  strlcpy((char *)&region.name, "tzcore", MAX_NAME_LEN);
  boot_ramdump_add_region(&region);

  /* Backup QHEE area and Mark as hypcore in memdesc */
  region.flags = CORE_DUMP_REGION_FLAG;
  region.phys_addr =  SCL_QHEE_CODE_BASE;
  region.size = SCL_QHEE_TOTAL_SIZE;
  strlcpy((char *)&region.name, "hypcore", MAX_NAME_LEN);
  boot_ramdump_add_region(&region);
}

#define LAST_LOGS_BASE 0xFFCC0000
#define LAST_LOGS_SIZE SIZE_256KB
#define LAST_LOGS_VERSION 0x00010000
#define LAST_LOGS_MAGIC 0x442474D4
#define MAX_LAST_LOGS_REGIONS 32
#define MAX_NAME_LENGTH 16

typedef struct PACK(last_logs_region)
{
  char name[MAX_NAME_LENGTH];
  uint32 offset;
  uint32 size;
  uint32 reserved;
} last_logs_region;

typedef struct PACK(last_logs_header)
{
  uint32 version;
  uint32 magic;
  uint32 num_regions;
  uint32 reserved[3];
  last_logs_region regions[MAX_LAST_LOGS_REGIONS];
} last_logs_header;

#define LAST_LOGS_HEADER_SIZE sizeof(last_logs_header)
static uint64 boot_ramdump_add_last_logs_region(
                  char *region_name, uint32 size)
{
  static uint32 offset = LAST_LOGS_HEADER_SIZE;
  static last_logs_header *last_logs_hdr = NULL;
  last_logs_region *region;
  uint64 ret_addr;

  if(!last_logs_hdr)
  {
    memset((void *)LAST_LOGS_BASE, 0, LAST_LOGS_SIZE);
    last_logs_hdr = (last_logs_header *)LAST_LOGS_BASE;
    last_logs_hdr->version = LAST_LOGS_VERSION;
    last_logs_hdr->magic = LAST_LOGS_MAGIC;
  }

  if(((offset + size) > (LAST_LOGS_SIZE - 1)) ||
     (last_logs_hdr->num_regions > MAX_LAST_LOGS_REGIONS))
    return 0;

  region = &(last_logs_hdr->regions[last_logs_hdr->num_regions]);
  strlcpy(region->name, region_name, MAX_NAME_LENGTH);
  region->offset = offset;
  region->size = size;
  last_logs_hdr->num_regions++;

  ret_addr = (uint64)(LAST_LOGS_BASE + offset);
  offset += size;
  return ret_addr;
}

/* Check the addr is within DDR Range */
static boolean boot_is_valid_ddr_addr(uint64 addr)
{
  if(addr && (addr >= DDR_MEM_BASE) &&
     (addr < (DDR_MEM_BASE + DDR_MEM_SIZE)))
    return TRUE;

  if(addr && (addr >= DDR_MEM_BASE2) &&
     (addr < (DDR_MEM_BASE2 + DDR_MEM_SIZE2)))
    return TRUE;

  return FALSE;
}

static void boot_ramdump_backup_debug_regions(void)
{
  struct ramdump_memdesc_region region;

  region.flags = PLATFORM_DUMP_REGION_FLAG | RAW_PARTITION_DUMP_FLAG;
  region.phys_addr = DEBUG_MEM_BASE;
  region.size = DEBUG_MEM_SIZE + PSTORE_MEM_SIZE;
  strlcpy((char *)&region.name, "debug_memory", MAX_NAME_LEN);
  boot_ramdump_add_region(&region);
}

/*TZ DIAG Area size*/
#define TZ_DIAG_SIZE (12 * SIZE_1KB)
#define BOOT_VALID_IMEM_ADDR( addr ) \
           ( ((uintnt) (addr) <= RANGE_END_ADDR) && \
             ((uintnt) (addr) < IMEM_RANGE_END_ADDR) && \
             ((uintnt) (addr) >= IMEM_RANGE_START_ADDR) )
static void boot_ramdump_backup_tzbsp_diag_region(void)
{
  uint32 *imem_tz_diag_addr, *tz_diag_base;
  uint64 debug_diag_mem_base = 0;

  imem_tz_diag_addr = (uint32 *)((uintnt)boot_shared_imem_cookie_ptr + 0x720);
  tz_diag_base = (uint32 *)((uintnt)*imem_tz_diag_addr);

  if(BOOT_VALID_IMEM_ADDR(tz_diag_base) &&
                        BOOT_VALID_IMEM_ADDR(tz_diag_base + TZ_DIAG_SIZE))
  {
    debug_diag_mem_base =
        boot_ramdump_add_last_logs_region("tzbsp_log", TZ_DIAG_SIZE);
    if(boot_is_valid_ddr_addr(debug_diag_mem_base))
       memscpy((void *)debug_diag_mem_base, TZ_DIAG_SIZE,
                (void *)tz_diag_base, TZ_DIAG_SIZE);
  }
}

#define PMIC_PON_SIZE sizeof(uint64)
static void boot_ramdump_backup_pmic_pon_region(void)
{
  uint64 debug_pmic_pon_mem_base = 0;
  uint64 pmic_pon_reason;

  boot_pm_dev_get_power_on_reason(0, &pmic_pon_reason);

  debug_pmic_pon_mem_base =
      boot_ramdump_add_last_logs_region("PMIC_PON", PMIC_PON_SIZE);

  if(boot_is_valid_ddr_addr(debug_pmic_pon_mem_base))
     memscpy((void *)debug_pmic_pon_mem_base, PMIC_PON_SIZE,
               (void *)&pmic_pon_reason, PMIC_PON_SIZE);
}

#define PMON_HIS_SIZE sizeof(pm_pbs_pon_reason_history_data_type)
static void boot_ramdump_backup_pmon_his_region(void)
{
  uint64 debug_pmon_his_mem_base = 0;
  pm_pbs_pon_reason_history_data_type pmic_pon_history;

  pm_pbs_get_pon_reason_history(&pmic_pon_history);

  debug_pmon_his_mem_base =
      boot_ramdump_add_last_logs_region("PMON_HIS", PMON_HIS_SIZE);

  if(boot_is_valid_ddr_addr(debug_pmon_his_mem_base))
     memscpy((void *)debug_pmon_his_mem_base, PMON_HIS_SIZE,
               (void *)&pmic_pon_history, PMON_HIS_SIZE);
}


#define RST_STAT_SIZE sizeof(uint32)
#define SNDSDI_MAGIC_NUMBER             0xDEADD00D
static void boot_ramdump_backup_reset_status_region(void)
{
  uint64 debug_reset_status_mem_base = 0;
  uint32 reset_status;
  uint32 *sdi_magic_addr, *sdi_gcc_reset_status_addr;

  sdi_magic_addr = (uint32 *)((uintnt)boot_shared_imem_cookie_ptr + 0xB14);
  sdi_gcc_reset_status_addr = (uint32 *)((uintnt)boot_shared_imem_cookie_ptr + 0x764);

  if(BOOT_VALID_IMEM_ADDR(sdi_magic_addr) &&
      (*(uint32 *)sdi_magic_addr == SNDSDI_MAGIC_NUMBER) &&
      BOOT_VALID_IMEM_ADDR(sdi_gcc_reset_status_addr)) {
    reset_status = *sdi_gcc_reset_status_addr;
  } else {
    reset_status = boot_shared_imem_cookie_ptr->reset_status_register;
  }

  debug_reset_status_mem_base =
      boot_ramdump_add_last_logs_region("RST_STAT", RST_STAT_SIZE);

  if(boot_is_valid_ddr_addr(debug_reset_status_mem_base))
     memscpy((void *)debug_reset_status_mem_base, RST_STAT_SIZE,
               (void *)&reset_status, RST_STAT_SIZE);
}

#define MSM_DUMP_DATA_MAGIC 0x42445953
#define CPU_REG_CXT_SIZE 0x800
#define CPU_REG_BIN_HDR_SIZE \
        (sizeof(CPU_REG_BIN_HEADER_INFO))
#define CPU_REG_BIN_HDR_VERSION 0x01
#define CPU_REG_BIN_HDR_MAGIC 0x53594442
#define DUMP_DATA_TYPE_SIZE \
        (sizeof(DUMP_DATA_TYPE) + sizeof(uint64))
#define MAX_DUMP_DATA_TYPE_SIZE \
        (NUMBER_OF_CORES * DUMP_DATA_TYPE_SIZE)
#define MAX_CPU_REG_CXT_SIZE \
        ((NUMBER_OF_CORES * CPU_REG_CXT_SIZE) + MAX_DUMP_DATA_TYPE_SIZE + \
        CPU_REG_BIN_HDR_SIZE)
/* Max no of entries as per memory_dump.h in kernel */
#define MAX_NUM_ENTRIES 0x150

typedef struct
{
  UINT32 version;
  UINT32 magic;
  UINT32 no_of_cores;
  UINT32 cpu_header_sect_len;
} CPU_REG_BIN_HEADER_INFO;

static boolean boot_is_valid_dump_table_ptr(DUMP_TABLE_TYPE *tbl)
{
  if(((uint64)tbl == MSM_DUMP_DATA_MAGIC) ||
     !boot_is_valid_ddr_addr((uint64)tbl))
    return FALSE;

  if(((tbl->Version != DBI_DUMP_TABLE_VERSION) && (tbl->Version != DBI_DUMP_TABLE_VERSION_1_4)) ||
     (tbl->NumEntries <= 0) ||
     (tbl->NumEntries > MAX_NUM_ENTRIES))
    return FALSE;

  return TRUE;
}

static void boot_ramdump_backup_cpu_reg_context(void)
{
  uint8 i, cpu = 0;
  uint32 offset;
  uint64 *imem_diag_base, debug_mem_base_cpu_reg = 0;
  DUMP_TABLE_TYPE *dump_table, *cpu_dump_table = NULL;
  DUMP_ENTRY_TYPE *entry;
  DUMP_DATA_TYPE *cpu_data;
  CPU_REG_BIN_HEADER_INFO cpu_regs_hdr_info;

  imem_diag_base =
        ((uint64 *)((uintnt)boot_shared_imem_cookie_ptr +
        DBI_SHARED_IMEM_COOKIE_OFFSET));

  if(!BOOT_VALID_IMEM_ADDR(imem_diag_base))
    return;

  dump_table = (DUMP_TABLE_TYPE *)(*imem_diag_base);
  if(!boot_is_valid_dump_table_ptr(dump_table))
    return;

  for(i = 0; i < dump_table->NumEntries; i++)
  {
    entry = &dump_table->Entries[i];
    if(entry->type == MSM_DUMP_TYPE_TABLE)
    {
      cpu_dump_table = (DUMP_TABLE_TYPE *)(entry->start_addr);
      if(boot_is_valid_ddr_addr((uint64)cpu_dump_table))
        break;
    }
  }

  if(!boot_is_valid_dump_table_ptr(cpu_dump_table))
    return;

  debug_mem_base_cpu_reg =
      boot_ramdump_add_last_logs_region("cpu_regs", MAX_CPU_REG_CXT_SIZE);
  if(!boot_is_valid_ddr_addr(debug_mem_base_cpu_reg))
    return;

  cpu_regs_hdr_info.version = CPU_REG_BIN_HDR_VERSION;
  cpu_regs_hdr_info.magic = CPU_REG_BIN_HDR_MAGIC;
  cpu_regs_hdr_info.no_of_cores = NUMBER_OF_CORES;
  cpu_regs_hdr_info.cpu_header_sect_len = DUMP_DATA_TYPE_SIZE;
  memscpy((void *)debug_mem_base_cpu_reg, CPU_REG_BIN_HDR_SIZE,
           (void *)&cpu_regs_hdr_info, CPU_REG_BIN_HDR_SIZE);

  for(i = 0; (i < cpu_dump_table->NumEntries) && (cpu < NUMBER_OF_CORES); i++)
  {
    entry = &cpu_dump_table->Entries[i];
    if(entry->id == (MSM_CPU_REGS_DUMP + cpu))
    {
      cpu_data = (DUMP_DATA_TYPE *)(entry->start_addr);
      if((boot_is_valid_ddr_addr((uint64)cpu_data)) &&
         (cpu_data->header.magic == MSM_DUMP_DATA_MAGIC))
      {
        offset = cpu * DUMP_DATA_TYPE_SIZE + CPU_REG_BIN_HDR_SIZE;
        memscpy((void *)(debug_mem_base_cpu_reg + offset), DUMP_DATA_TYPE_SIZE,
                 (void *)cpu_data, DUMP_DATA_TYPE_SIZE);
        offset = MAX_DUMP_DATA_TYPE_SIZE + cpu * CPU_REG_CXT_SIZE + CPU_REG_BIN_HDR_SIZE;
        memscpy((void *)(debug_mem_base_cpu_reg + offset), CPU_REG_CXT_SIZE,
                 (void *)(cpu_data->start_addr), CPU_REG_CXT_SIZE);
      } else {
        offset = cpu * DUMP_DATA_TYPE_SIZE + CPU_REG_BIN_HDR_SIZE;
        memscpy((void *)(debug_mem_base_cpu_reg + offset), DUMP_DATA_TYPE_SIZE,
                 (void *)cpu_data, DUMP_DATA_TYPE_SIZE);
        memset((void *)(debug_mem_base_cpu_reg + offset +
                 OFFSET_OF(DUMP_HEADER_TYPE, magic)), 0, sizeof(UINT32));
        offset = MAX_DUMP_DATA_TYPE_SIZE + cpu * CPU_REG_CXT_SIZE + CPU_REG_BIN_HDR_SIZE;
        memset((void *)(debug_mem_base_cpu_reg + offset), 0, CPU_REG_CXT_SIZE);
      }
      cpu++;
    }
  }
}

#define SECURE_RESET_REASON_OFFSET 0x7A4
#define SECURE_RESET_REASON_SIZE sizeof(uint32)
static void boot_ramdump_secure_reset_reason_region(void)
{
  uint32 *secure_reset_reason_addr;
  uint64 debug_secure_reset_reason_mem_base = 0;

  secure_reset_reason_addr =
      (uint32 *)((uintnt)boot_shared_imem_cookie_ptr + SECURE_RESET_REASON_OFFSET);
  if(!BOOT_VALID_IMEM_ADDR(secure_reset_reason_addr))
    return;

  debug_secure_reset_reason_mem_base =
      boot_ramdump_add_last_logs_region("reset_reason", SECURE_RESET_REASON_SIZE);
  if(boot_is_valid_ddr_addr(debug_secure_reset_reason_mem_base))
    memscpy((void *)debug_secure_reset_reason_mem_base, SECURE_RESET_REASON_SIZE,
             (void *)secure_reset_reason_addr, SECURE_RESET_REASON_SIZE);
}

#define RESTART_REASON_SIZE sizeof(uint32)
static void boot_ramdump_restart_reason_region(void)
{
  uint8 restart_reason = 0;
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint64 debug_restart_reason_mem_base = 0;

  err_flag = pm_pon_get_spare_reg(0, PM_PON_SOFT_SPARE, &restart_reason);
  if (err_flag == PM_ERR_FLAG_SUCCESS && restart_reason) {
     restart_reason = 0x7F & (restart_reason >> 1);
     debug_restart_reason_mem_base =
         boot_ramdump_add_last_logs_region("restart_reason", RESTART_REASON_SIZE);
     if(boot_is_valid_ddr_addr(debug_restart_reason_mem_base))
         memscpy((void *)debug_restart_reason_mem_base, RESTART_REASON_SIZE,
                 (void *)&restart_reason, sizeof(restart_reason));
  }
}

#define AOP_MEMORY_REGION_TABLE  MEMORY_REGION2,MEMORY_REGION3,MEMORY_REGION4,\
                                 MEMORY_REGION5,MEMORY_REGION6,MEMORY_REGION7,\
                                 MEMORY_REGION8,MEMORY_REGION9,MEMORY_REGION10,\
                                 MEMORY_REGION11,MEMORY_REGION12,MEMORY_REGION13,\
                                 MEMORY_REGION14,MEMORY_REGION15,MEMORY_REGION16,\
                                 MEMORY_REGION17,MEMORY_REGION18,MEMORY_REGION19,\
                                 MEMORY_REGION_LAST

static void boot_ramdump_backup_aop_regions(void)
{
  uint64 debug_aop_region_mem_base = 0;

  struct memory_region
  {
    uint32 region_base;
    uint32 region_size;
    char* desc;
    char* filename;
  } aop_regions[] = {AOP_MEMORY_REGION_TABLE};

  uint32 index = 0;

  while (aop_regions[index].region_base != 0x0 )
  {
    debug_aop_region_mem_base =
        boot_ramdump_add_last_logs_region(aop_regions[index].filename, aop_regions[index].region_size);

    if(boot_is_valid_ddr_addr(debug_aop_region_mem_base))
      memscpy((void *)debug_aop_region_mem_base, aop_regions[index].region_size,
               (void *)(uintnt)aop_regions[index].region_base, aop_regions[index].region_size);
    index++;
  }
}

static void boot_ramdump_backup_sbl1_ddr_log_buf(void)
{
  uint32 *sbl1_ddr_log_buf_addr;
  uint64 sbl1_ddr_log_buf_mem_base = 0;

  sbl1_ddr_log_buf_addr =
      (uint32 *)((uintnt)boot_shared_imem_cookie_ptr->boot_log_addr);

  sbl1_ddr_log_buf_mem_base =
      boot_ramdump_add_last_logs_region("sbl1_ddr_logs", SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE);
  if(boot_is_valid_ddr_addr(sbl1_ddr_log_buf_mem_base))
    memscpy((void *)sbl1_ddr_log_buf_mem_base, SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE,
             (void *)sbl1_ddr_log_buf_addr, SCL_SBL1_DDR_BOOT_LOG_BUF_SIZE);
}

void boot_ramdump_target_init(boot_handle config_context_handle)
{
  uint32 i = 0;
  uint32 num_regions;
  struct ramdump_memdesc_region region;

  /* Initialize the QC debug memory regions array */
  dload_mem_debug_init(config_context_handle);

  num_regions = dload_mem_debug_num_ent();

  /* Backup PMIC_PON & RST_STAT region */
  boot_ramdump_backup_pmic_pon_region();
  boot_ramdump_backup_pmon_his_region();
  boot_ramdump_backup_reset_status_region();

 /* Backup debug memory region */
  boot_ramdump_backup_debug_regions();

 /* Add QC debug memory regions */
  while(num_regions && (i < MAX_NUM_REGIONS))
  {
    memset(&region, 0, sizeof(struct ramdump_memdesc_region));
    region.flags = PLATFORM_DUMP_REGION_FLAG | RAW_PARTITION_DUMP_FLAG;
    if(!boot_is_ramdump_to_rddata_allowed(config_context_handle))
      region.flags |= RAW_SDCARD_DUMP_FLAG;
    region.phys_addr = dload_mem_debug_mem_base(i);
    region.size = dload_mem_debug_mem_length(i);
    strlcpy((char *)&region.name, dload_mem_debug_filename(i),
             MAX_NAME_LEN);
    boot_ramdump_add_region(&region);
    num_regions--;
    i++;
  }

 /* Add DDR backup regions */
  boot_ramdump_backup_ddr_regions();

 /*Backup tzdiag region*/
  boot_ramdump_backup_tzbsp_diag_region();

 /* Backup cpu registers */
  boot_ramdump_backup_cpu_reg_context();

 /* Backup restart reason from imem */
  boot_ramdump_restart_reason_region();

 /* Backup sbl1 ddr log from boot logger buffer*/
  boot_ramdump_backup_sbl1_ddr_log_buf();
}

void boot_ramdump_target_secure_init(void)
{
 /*Backup tzdiag region*/
  boot_ramdump_backup_tzbsp_diag_region();

 /* Backup PMIC_PON & RST_STAT region */
  boot_ramdump_backup_pmic_pon_region();
  boot_ramdump_backup_pmon_his_region();
  boot_ramdump_backup_reset_status_region();

 /* Backup restart reason from imem */
  boot_ramdump_restart_reason_region();

 /* Backup AOP regions*/
  boot_ramdump_backup_aop_regions();

 /* Make sure that all the regions backed up to
  * debug memory and atlast backup the complete
  * debug memory to rddata partition
  */
  boot_ramdump_backup_debug_regions();

 /* Back up secure reset reason from imem */
  boot_ramdump_secure_reset_reason_region();

 /* Backup sbl1 ddr log from boot logger buffer*/
  boot_ramdump_backup_sbl1_ddr_log_buf();
}

void boot_ramdump_failed_target_init(void)
{
  boot_ramdump_backup_debug_regions();
}

#endif /* FEATURE_SONY_RAMDUMP */
