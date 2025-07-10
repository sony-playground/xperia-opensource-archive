/*===========================================================================

                  Unified Crypto Environment API - XBLCORE

GENERAL DESCRIPTION


EXTERNALIZED FUNCTIONS


INITIALIZATION AND SEQUENCING REQUIREMENTS

Copyright (c) 2020 Qualcomm Technologies, Inc.
All rights reserved.
Qualcomm Technologies, Inc. Confidential and Proprietary.
===========================================================================*/

/*===========================================================================
                     INCLUDE FILES FOR MODULE
===========================================================================*/
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>

#include "uclib_env.h"
#include "uclib_err.h"
#include "msmhwiobase.h"
#include <Uefi.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/CacheMaintenanceLib.h>
#include "Library/ArmLib.h"
#include <Library/DebugLib.h>
#include "Library/KernelLib.h"

#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include "com_dtypes.h"

#include "bam_drv.h"
#include "ucenv_xbl_core.h"

/* For ICB API's */
#include "icbarb.h"
#include "icbid.h"
#include "ucenv_clk_table.h"

#define UEFI_PRNG_CFG_PRNG_TOP_BASE    RNG_SOC_TOP_BASE
#define UEFI_UCLIB_BOOT_PRNG_EE_NUM    3

#define UCLIB_ENV_UEFI_DEFAULT_PIPE_SET   2                  /** For Waipio UEFI tx_pipe_num = 4  rx_pipe_num = 5 */
#define UCENV_STATIC_ASSERT(cond) typedef char assertion[(!!(cond))*2-1]

/* BAM_TXRX_DESC_SIZE must be multiple of 8 bytes */
UCENV_STATIC_ASSERT(BAM_TXRX_DESC_SIZE %8 == 0);

static size_t              clk_ref[CLK_RESOURCE_COUNT] = {0};
static npa_client_handle   ce_icb_handle = NULL;

/*===========================================================================
                 DEFINITIONS AND TYPE DECLARATIONS
 ===========================================================================*/
static int ucenv_set_bandwidth(env_resource ce, env_clklev lvl, uint32_t flags)
{
  if ( CE1 != ce ) return 0;  /* skip voting other than CE clock */

  ICBArb_RequestType req = {0};
  ICBArb_MasterSlaveType masterSlaveAry[] = {
    { ICBID_MASTER_CRYPTO, ICBID_SLAVE_EBI1 }
  };
  
  req.arbType = ICBARB_REQUEST_TYPE_3_LAT;
  req.arbData.type3.uLatencyNs = 0;
  
  /* Get Clock ICB handle and in case of the first time, create a client */
  if( !ce_icb_handle ) {
    /*create a client*/
    ce_icb_handle = icbarb_create_client("/clk/ce1", masterSlaveAry, 1);
    if( !ce_icb_handle ) return -1;
  }

  if (INACTIVE == lvl) {
    /* Disable Clock */
    req.arbData.type3.uIb = CE_BW_IB_INACTIVE;
    req.arbData.type3.uAb = CE_BW_AB_INACTIVE;
  } else if (LOW == lvl) {
    req.arbData.type3.uIb = (uint64)CE_BW_IB_LOW;
    req.arbData.type3.uAb = (uint64)CE_BW_AB_LOW;
  } else if (HIGH == lvl) {
    req.arbData.type3.uIb = (uint64)CE_BW_IB_HIGH;
    req.arbData.type3.uAb = (uint64)CE_BW_AB_HIGH;
  } else {
    /* Default level is MEDIUM */
    req.arbData.type3.uIb = (uint64)CE_BW_IB_MEDIUM;
    req.arbData.type3.uAb = (uint64)CE_BW_AB_MEDIUM;
  }
  
  if (ICBARB_ERROR_SUCCESS != icbarb_issue_request( ce_icb_handle, &req, 1 )) return -1;
  return 0;
}

static size_t ucenv_get_set_clk_ref(env_var_op operation, env_resource ce)
{
  if (ce >= sizeof(clk_ref)/sizeof(clk_ref[0])) {
    return 0;
  }
  switch(operation) {
    case INCR:    return ++clk_ref[ce];
    case DECR:    return --clk_ref[ce];
    case GET:
    default:      return clk_ref[ce];
  }
}

static size_t ucenv_dcache_line_size(void)
{
  return ArmDataCacheLineLength() ;
}

static int ucenv_xbl_vtop(uintptr_t va, uintptr_t *p_pa)
{
  if ( !p_pa)
    return -1;

  *p_pa = va;
  return 0;
}

static void ucenv_xbl_dcache_flush_region(void *addr, size_t length)
{
  WriteBackInvalidateDataCacheRange(addr,length);
}

static void ucenv_xbl_dsb(void)
{
  __asm__("DSB SY");
}

static void ucenv_xbl_isb(void)
{
  __asm__("ISB SY");
}

static void * uclib_xbl_malloc(uint32_t size)
{
  return AllocatePool((size_t)size);
}

/* Mutex operations */
static int uefi_LockInit(void* lock)
{
  return 0;
}

static int uefi_Lock(void* lock)
{
  if (lock)
    AcquireLock((LockHandle*)lock);

  return 0;
}

static int uefi_UnLock(void* lock)
{
  if (lock)
    ReleaseLock((LockHandle*)lock);
 
  return 0;
}

static void uclib_xblcore_log(const char* fmt, va_list ap)
{
  DebugPrint( EFI_D_ERROR, fmt, ap);
}

/* timesafe_memcmp() should perform a memcmp() in constant time (proportional to len) */
/* Function returns 1 if the strings are different and 0 if the strings are the same  */
/* This prevents any information about difference between two buffers being leaked.   */
static int timesafe_memcmp(const void *ptr1, const void *ptr2, size_t len)
{
  uint8_t rc = 0;
  uint8_t *p1 = ( uint8_t *)ptr1;
  uint8_t *p2 = ( uint8_t *)ptr2;

  while (len > 0)
  {
    /* *p1 XOR * p2 will be zero if and only if *p1 == *p2                  */
    /* The OR means that once rc becomes non-zero, it will remain that way. */
    rc = rc | (*p1 ^ *p2);

    /* Setup for next iteration                                             */
    len--;
    p1++;
    p2++;
  }

  /* Reduce rc to 1 if rc is non-zero and 0 if rc is zero.                    */
  rc = (rc >> 4) | (rc & 0x0F);
  rc = (rc >> 2) | (rc & 0x03);
  rc = (rc >> 1) | (rc & 0x01);

  return (int)rc;
}

static bool uclib_xbl_is_crypto_operation_allowed( crypto_operation_enum operation)
{
  return true;
}

static bool uclib_xbl_is_fips_enabled(void)
{
  return false;
}

static env_cfg_t ucenv_xbl_core_env_cfg = {
  /** CE HW Base Address */
  .ce = {
    .prng_base = UEFI_PRNG_CFG_PRNG_TOP_BASE,            /** Mandatory Env. member if HW PRNG is supported - Top Base Addr*/ 
  },

  /** PRNG Access API's */
  .prng =
  {
    .init_done   = true,                                 /** Mandatory flag */
    .ee = UEFI_UCLIB_BOOT_PRNG_EE_NUM,                   /** Mandatory for PRNG */
    .lock = NULL,
  },

  /** Clock API's */
  .clk = {
    .ce_clk = CE1,                                                        /** Clock Resource Name */
    .lvl = MEDIUM,                                                        /** Bandwidth level     */
  },

  /** BAM Driver Static Allocations */
  .bam = {
    .cmd_desc_buf_sz = BAM_DRV_CTX_SIZE,                                  /** Mandatory if BAM Engine is used.                                                     */
    .desc_sz = BAM_TXRX_DESC_SIZE,                                        /** Mandatory if BAM Engine is used. Tx-Rx BAM Descriptor Size. Must be multiple of 8    */
    .uses_550_features = true,                                            /** Mandatory if CE 5.5.0 features are enabled                                           */
    .cmds_over_hwio = false,                                              /** Indicates if need use HWIO for sending command while use BAM for data                */
    .default_pipeset_num = UCLIB_ENV_UEFI_DEFAULT_PIPE_SET,               /** Indicates the default pipe set num. 0 - for TZ; 2 - for uefi                         */
     /* This count indicates the maximum number of iterations to poll for
      * the BAM poll API. To arrive at a value, we ran a SHA384 hash test
      * for 64KB (one descriptor max data), and a AES-128 ECB cipher test
      * for 64KB, on a Lahaina v1 device, using UEFI-TZT. The maximum number
      * of times we repeated the call to the polling API for Tx/Rx pipes,
      * was 0x22e (decimal 558). As a result (0x4000) 16384 seems like a
      * conservative value, also considering that some algorithms like
      * AES-CCM (which uses both the Auth and Cipher engines) might take
      * longer than just plain SHA384 or AES-ECB.
      */
    .max_poll_count = 0x4000,
  },
};

static const env_t ucenv_xbl_core_env = {
  .ver = UCLIB_ENV_VERSION_MAJOR,
  .magic = UCLIB_ENV_MAGIC_NUMBER,

  /** env_fp const struct API's */
  .env_fp = {
    /** Clock API's */
    .clk_fp = {
      .ref = ucenv_get_set_clk_ref,                      /** Reference count     */
      .set_bw_fp = ucenv_set_bandwidth,                  /** Mandatory Env. callback if HW crypto is supported */
    },

    /** Heap API's */
    .mm = {
      .malloc_fp = uclib_xbl_malloc,                     /** Mandatory Env. callback if heap management is supported in the image */
      .free_fp = FreePool,                               /** Mandatory Env. callback if heap management is supported in the image */
    },

    /** memory API's */
    .mem = {
      .memcpy_fp = memcpy,                               /** Mandatory Env. callback */
      .memset_fp = memset,                               /** Mandatory Env. callback */
      .memcmp_fp = memcmp,                               /** Mandatory Env. callback */
      .timesafe_memcmp_fp = timesafe_memcmp,             /** Mandatory Env. callback */
      .memmove_fp = memmove,                             /** Mandatory Env. callback */
      .vtop_fp = ucenv_xbl_vtop,                         /** Mandatory Env. callback if HW crypto BAM mode is supported */
      .dcache_civ_fp = ucenv_xbl_dcache_flush_region,    /** Mandatory Env. callback if HW crypto BAM mode is supported */
      .dcache_sz_fp = ucenv_dcache_line_size,            /** Mandatory Env. callback if HW crypto BAM mode is supported */
      .mem_barrier_fp = ucenv_xbl_dsb,                   /** Mandatory Env. callback if HW crypto BAM mode is supported */
      .inst_barrier_fp = ucenv_xbl_isb,                  /** Mandatory Env. callback if HW crypto BAM mode is supported */
    },

    /** Mutex API's */
    .mtx_fp = {
      .mutex_init_fp = uefi_LockInit,                    /** Mandatory Env. callback if HW crypto BAM mode is supported */
      .mutex_lock_fp = uefi_Lock,                        /** Mandatory Env. callback if HW crypto BAM mode is supported */
      .mutex_release_fp = uefi_UnLock,                   /** Mandatory Env. callback if HW crypto BAM mode is supported */
    },

    /** PRNG API's */
    .prng_fp = {
      .prng_lock_fp = uefi_Lock,                        /** Mandatory Env. callback for multithread support */
      .prng_release_fp = uefi_UnLock,                   /** Mandatory Env. callback for multithread support */
    },

    /** Log API's */
    .log_fp = uclib_xblcore_log,                           /** Optional Env. callback */

    /** selftest API's */
    .is_crypto_operation_allowed_fp = uclib_xbl_is_crypto_operation_allowed,
    .is_fips_enabled_fp = uclib_xbl_is_fips_enabled,
  },
  .env_cfg_ptr = &ucenv_xbl_core_env_cfg,                /** env configurable struct pointer pointed to env_cfg_t substract */	  
};

env_t * ucenv_get_env(void)
{
  return (env_t *)&ucenv_xbl_core_env;
}

/**
 * To set HW Base Address in ucenv_xbl_core env structure.
 *
 * @param env       [in]: pointer to environment structure
 * @param var       [in]: indicate which base address to be set in enum env_base_addr_var_t
 * @param baseAddr  [in]: the 32bit value of HW base addr to be set
 *
 * @return 0 if successful. negative value otherwise.
 */
int xbl_core_set_env_HW_base(env_t *env, env_base_addr_var_t var, uint32_t baseAddr)
{
  if ( !env || !env->env_cfg_ptr)
    return -1;

  switch(var) {
    case ENV_CE_BASE:       env->env_cfg_ptr->ce.ce_base = baseAddr; return 0;
    case ENV_CE_BAM_BASE:   env->env_cfg_ptr->ce.ce_bam_base = baseAddr; return 0;
    case ENV_CE_IRQ_NUM:    env->env_cfg_ptr->ce.ce_irq_num = baseAddr; return 0;
    case ENV_PRNG_BASE:     env->env_cfg_ptr->ce.prng_base = baseAddr; return 0;
    case ENV_PKA_BASE:      env->env_cfg_ptr->ce.pka_base = baseAddr; return 0;
    default: return -1;
  }
}

/**
 * To set CE BAM used buf address.
 *
 * @param env     [in]: pointer to environment structure
 * @param var     [in]: indicate which BAM buf address to be set in enum env_bam_var_t
 * @param data    [in]: data of BAM buf address to be set
 *
 * @return 0 if successful. negative value otherwise.
 */
int xbl_core_set_env_bam_buf_addr(env_t *env, env_bam_var_t var, uint8_t* data)
{
  if ( !env || !env->env_cfg_ptr)
    return -1;

  switch(var) {
    case ENV_BAM_TX_DESC:       env->env_cfg_ptr->bam.tx_desc = data; return 0;
    case ENV_BAM_RX_DESC:       env->env_cfg_ptr->bam.rx_desc = data; return 0;
    case ENV_BAM_RSLT:          env->env_cfg_ptr->bam.rslt = data; return 0;
    case ENV_BAM_CONTAINER:     env->env_cfg_ptr->bam.container = data; return 0;
    case ENV_BAM_CMD_DESC_BUF:  env->env_cfg_ptr->bam.cmd_desc_buf = data; return 0;
    default: return -1;
  }
}

/**
 * To set the CE Lock.
 *
 * @param env     [in]: pointer to environment structure
 * @param lock    [in]: CE lock to be set
 *
 * @return 0 if successful. negative value otherwise.
 */
int xbl_core_set_lock(env_t *env, void* lock)
{
  if ( !env || !env->env_cfg_ptr)
    return -1;

  env->env_cfg_ptr->mtx.lock = lock;
  return 0;
}

/**
 * To set the PRNG Lock.
 *
 * @param env     [in]: pointer to environment structure
 * @param lock    [in]: PRNG lock to be set
 *
 * @return 0 if successful. negative value otherwise.
 */
int xbl_core_set_prng_lock(env_t *env, void* lock)
{
  if ( !env || !env->env_cfg_ptr)
    return -1;

  env->env_cfg_ptr->prng.lock = lock;
  return 0;
}