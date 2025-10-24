#ifndef PCIE_OSAL_H
#define PCIE_OSAL_H
/*
 *  pcie_osal.h
 *
 *  This file contains the OS abstraction interface.
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Derived from ADSP driver implementation

*/
/*============================================================================
               Copyright (c) 2013-2022 Qualcomm Technologies, Inc.
                  All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "comdef.h"
#include "pcie_dtypes.h"
#include "pcie_cfg_types.h"
#include "err.h"
#include <stdint.h>
#include <stdarg.h>

// circular dependency results into some macros will have wrong values based on sequence of inclusion
//#include "pcie_host_log.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/* Error codes */
#define PCIE_OSAL_ERROR -1

/* Macro for printing a 64-bit integer value */
#define PCIE_OSAL_LOG_64(x) (uint32)(x), (uint32)((uint64)(x) >> 32)

/* Macro used when the physical address is unspecified */
#define PCIE_OSAL_PA_UNSPECIFIED 0

/* Sync option flags that can be ORed together */
#define PCIE_OSAL_SYNC_FLAG_NONE        0x0
#define PCIE_OSAL_SYNC_FLAG_PREEMPTION  0x1

/* Macro to count the number of variadic arguments */
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(0, ## __VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define VA_NUM_ARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

/*----------------------------------------------------------------------------
 *   TARGET/IMAGE configuration
 * -------------------------------------------------------------------------*/

/* Max number of root port configurations that the image can support holding
 * in memory. Can be less than max, but should be enough to hold all listed
 * port entries */
#define PCIE_MAX_ENABLED_ROOT_PORTS                  8

/* Max number of active open root ports need to be supported for the image */
#define PCIE_MAX_ACTIVE_ROOT_PORTS                   4

/* Maximum number for drivers the host driver can support for storing probe
 * callback registrations */
#define MAX_PCIE_CLIENTS                             4

/* Need 2 contexts each for allocating to root port and endpoint. Set to
 * max depth of the tree that need to be supported. For now set to 4 */
#define MAX_MEM_CONTEXTS                            4


/** Default log levels, pick from PcieRpLib\pcie_host_log.h */
#undef PCIE_HOST_LOG_LEVEL
#define PCIE_HOST_LOG_LEVEL                 LOG_LEVEL_HIGH

#define PCIE_ENABLE_PERF_LOGS

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
typedef enum
{
   PCIE_OSAL_TIME_UNIT_TICKS = 0,
   PCIE_OSAL_TIME_UNIT_US,
   PCIE_OSAL_TIME_UNIT_MS,
} pcie_osal_time_unit_t;

typedef enum
{
   PCIE_OSAL_MEM_CACHED   = 0,
   PCIE_OSAL_MEM_UNCACHED = 1,
   PCIE_OSAL_MEM_DEVICE   = 2,
} pcie_osal_mem_props_t;

typedef enum
{
   PCIE_OSAL_CACHE_OP_FLUSH_INVALIDATE,
   PCIE_OSAL_CACHE_OP_FLUSH,
   PCIE_OSAL_CACHE_OP_INVALIDATE,
} pcie_osal_cache_op_t;

typedef uintptr_t pcie_osal_va_t;

typedef uint64 pcie_osal_pa_t;

typedef void (*pcie_osal_cb_t)(void *ctxt);

typedef struct
{
   pcie_osal_va_t va;
   pcie_osal_pa_t pa;
   size_t size;
} pcie_osal_mem_info_t;

/*----------------------------------------------------------------------------
 *                    Init
 * -------------------------------------------------------------------------*/
void pcie_osal_init(void);

void pcie_osal_deinit(void);

/*----------------------------------------------------------------------------
 *                   Logging
 * -------------------------------------------------------------------------*/
void pcie_osal_log_msg(const char *fmt, ...);

/*----------------------------------------------------------------------------
 * Memory
 * -------------------------------------------------------------------------*/

#define OSAL_CONVERT_PA_TO_VA(x)    (x)

/* This function dynamically allocates memory. Memory should be freed only
 * with pcie_osal_free */
void* pcie_osal_malloc(size_t size);

/* This function frees memory previously allocated by pcie_osal_malloc. */
void pcie_osal_free(void *ptr);

/* This function dynamically allocates memory with a specified alignment.
 * Memory should be freed only with pcie_osal_free_aligned.
 *
 * size  :  Size (in bytes) of memory to allocate
 * align :  Alignment - must be a power of 2
 *
 * Returns Pointer to the memory allocated; NULL if failed */
void* pcie_osal_malloc_aligned(size_t size, uint8 align);

/* This function frees memory previously allocated by pcie_osal_malloc_aligned. */
void pcie_osal_free_aligned(void *ptr);

/*
 * This function maps a physically continguous memory region. If the base
 * physical address is known then it must be provided. Otherwise, a memory
 * region will be allocated from the default pool. Memory should be unmapped
 * only with pcie_osal_mem_region_unmap.
 *
 *  pa         Desired base physical address or PCIE_OSAL_PA_UNSPECIFIED
 *  size       Size (in bytes) of memory to allocate
 *  mem_props  Memory type
 *  mem_info   Mapped memory region info
 *
 * Return 0 for success else an error
 */
pcie_status_t pcie_osal_mem_region_map(pcie_osal_pa_t pa, size_t size, pcie_osal_mem_props_t mem_props,
                             pcie_osal_mem_info_t *mem_info);

/* This function unmaps memory previously allocated by pcie_osal_mem_region_map.
 * Return 0 for success else an error */
pcie_status_t pcie_osal_mem_region_unmap(pcie_osal_mem_info_t *mem_info);

/* This function performs a cache operation on a given buffer.  */
void pcie_osal_cache_ctrl(pcie_osal_cache_op_t op, pcie_osal_va_t va, size_t size);

/* This function issues a memory barrier. */
void pcie_osal_memory_barrier(void);

/* This function spins in tight loop until the given duration lapsed */
void pcie_osal_busywait_us(uint32 time_us);

void pcie_osal_sleep(uint32 time_ms, boolean non_deferrable);

/*----------------------------------------------------------------------------
 * Buffers
 * -------------------------------------------------------------------------*/
/* This function initializes memory to a desired value.  */
void* pcie_osal_memset(void *ptr, uint8 val, size_t size);

/*
 * This function copies memory of a specified size to the destination of
 * a specified size. The number of bytes copied will not exceed the size
 * of the destination buffer.
 *
 * Returns : Number of bytes copied (can be checked for truncation)
 */
size_t pcie_osal_memscpy(void *dst, size_t dst_size, const void *src, size_t src_size);

/*
 * This function is a safer version of strcpy that takes into consideration the
 * destination size and always NUL-terminates.
 *
 * Returns : Length of the source string (can be checked for truncation)
 *
 */
size_t pcie_osal_strlcpy(char *dst, const char *src, size_t dst_size);

/* Return various platform/target information based on the argument provided */
pcie_status_t pcie_get_target_platform_info (uint32* chip_id_ptr,
                                             uint32* chip_ver_ptr,
                                             uint32* chip_family_ptr,
                                             uint32* plat_type_ptr);

/* Environment dependent register val set call for secure memory and fuses */
pcie_status_t pcie_initialize_gpios (pcie_resources_ctxt_t* rsrc_ctxt,
                                     const pcie_gpio_cfg_t *gpio_cfg);

/* Get time lapsed in ms since the device powered up */
uint64 pcie_osal_get_time_ms (void);

/* Set a GPIO pin to a level */
pcie_status_t pcie_osal_gpio_set (uint32 pin, boolean level);

pcie_status_t enable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt,
                                     const pcie_port_config_t  *port_cfg);
pcie_status_t disable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt,
                                     const pcie_port_config_t  *port_cfg);

pcie_status_t pcie_drive_ext_clocks (pcie_resources_ctxt_t* rsrc_ctxt,
                                     const pcie_clocks_cfg_t *clock_config,
                                     uint32 enable);
pcie_status_t enable_rsc_module(void);
pcie_status_t write_secure_tcsr_reg_val (uint32* addr, uint32 val);

pcie_status_t map_mem_smmu_sid (uint32 smmu_config, uint32 rbdf, void* base_addr, uint64 size_bytes, void** map_handle_ptr);
pcie_status_t unmap_smmu_sid (void* map_handle);

pcie_status_t enable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt, const pcie_port_config_t  *port_cfg);
pcie_status_t disable_pcie_resources (pcie_resources_ctxt_t *resources_ctxt, const pcie_port_config_t  *port_cfg);

pcie_status_t pcie_initialize_gpios (pcie_resources_ctxt_t* rsrc_ctxt, const pcie_gpio_cfg_t *gpio_cfg);


#endif

