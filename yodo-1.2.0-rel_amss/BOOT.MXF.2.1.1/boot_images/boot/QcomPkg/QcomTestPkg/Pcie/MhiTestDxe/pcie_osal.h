#ifndef PCIE_OSAL_H
#define PCIE_OSAL_H
/**
 *  @file pcie_osal.h
 *
 *  @brief This file contains the OS abstraction interface.
 */
/*============================================================================
               Copyright (c) 2021 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "comdef.h"
#include "DALSys.h"
#include "err.h"
#include <stdint.h>
#include <stdarg.h>
//#include <stdlib.h>
#include <Library/KernelLib.h>

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/
/** Error codes */
#define PCIE_OSAL_ERROR -1

/** Macro for printing a 64-bit integer value */
#define PCIE_OSAL_LOG_64(x) (uint32)(x), (uint32)((uint64)(x) >> 32)

/** Macro used when the physical address is unspecified */
#define PCIE_OSAL_PA_UNSPECIFIED 0

/** Sync option flags that can be ORed together */
#define PCIE_OSAL_SYNC_FLAG_NONE        0x0
#define PCIE_OSAL_SYNC_FLAG_PREEMPTION  0x1

/** Macro to count the number of variadic arguments */
#define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(0, ## __VA_ARGS__, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define VA_NUM_ARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, N, ...) N

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#endif /* ifndef ARRAY_SIZE */

#define PCIE_OSAL_DEFAULT_STACK_SIZE 0x1000

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/
/** Client IDs for logging */
typedef enum
{
   PCIE_OSAL_LOG_PCIE = 0,
   PCIE_OSAL_LOG_PCIE_PROFILING,
   PCIE_OSAL_LOG_MHI,
   PCIE_OSAL_LOG_MHI_PROFILING,
   PCIE_OSAL_LOG_SAT_IPC,
   PCIE_OSAL_LOG_SAT_IPC_PROFILING,
   PCIE_OSAL_LOG_PCIEDRV0,
   PCIE_OSAL_LOG_PCIEDRV1,
   PCIE_OSAL_LOG_PCIEDRV2,
   PCIE_OSAL_LOG_MHI_DIAG,
   PCIE_OSAL_LOG_PCIEDRV,
   PCIE_OSAL_LOG_HOST_RC,
   _PCIE_OSAL_LOG_NUM_CLIENTS
} pcie_osal_log_client_t;

/** Log levels */
typedef enum
{
   PCIE_OSAL_LOG_LEVEL_LOW = 0,
   PCIE_OSAL_LOG_LEVEL_MED,
   PCIE_OSAL_LOG_LEVEL_HIGH,
   PCIE_OSAL_LOG_LEVEL_ERROR,
   PCIE_OSAL_LOG_LEVEL_FATAL
} pcie_osal_log_level_t;

/** Time units */
typedef enum
{
   PCIE_OSAL_TIME_UNIT_TICKS = 0,  /**< Ticks */
   PCIE_OSAL_TIME_UNIT_US,         /**< Microseconds */
   PCIE_OSAL_TIME_UNIT_MS          /**< Milliseconds */
} pcie_osal_time_unit_t;

/** Memory properties type */
typedef enum
{
   PCIE_OSAL_MEM_UNCACHED = 0,  /**< Uncached memory */
   PCIE_OSAL_MEM_DEVICE         /**< Device memory */
} pcie_osal_mem_props_t;

/** Cache operations */
typedef enum
{
   PCIE_OSAL_CACHE_OP_FLUSH_INVALIDATE,  /**< Flush then invalidate */
   PCIE_OSAL_CACHE_OP_FLUSH,             /**< Flush */
   PCIE_OSAL_CACHE_OP_INVALIDATE         /**< Invalidate */
} pcie_osal_cache_op_t;

/** Virtual address type */
typedef uintptr_t pcie_osal_va_t;

/** Physical address type */
typedef uint64 pcie_osal_pa_t;

/**
 *  This is type for a callback function.
 *
 *  @param[in]  ctxt  User-supplied callback context
 *
 *  @return None.
 */
typedef int (*pcie_osal_cb_t)(void *ctxt);

/** Memory info type */
typedef struct
{
   pcie_osal_va_t va;   /**< Virtual address */
   pcie_osal_pa_t pa;   /**< Physical address */
   size_t size;         /**< Size of the memory */
   DALSYSMemHandle _h;  /**< Handle */
   DALSYSMemObj _obj;   /**< Object (avoids dynamic allocation) */
} pcie_osal_mem_info_t;

/** Sync object type */
typedef struct
{
   Mutex *lock;
} pcie_osal_sync_t;

/** Event object type */
typedef struct
{
   Event *evt;
} pcie_osal_event_t;

/** Thread object type */
typedef struct
{
   void *_thread;             /**< Thread handle */
   pcie_osal_cb_t _fcn;       /**< Thread entry */
   void *_ctxt;               /**< User-supplied context */
} pcie_osal_thread_t;

/** Interrupt context type */
typedef struct
{
   pcie_osal_cb_t _isr;  /**< ISR */
   void *_ctxt;          /**< User-supplied context */
   uint32 irq_id;        /**< IRQ ID */
} pcie_osal_irq_t;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/
/**
 * This function initializes the OSAL. On images with RCINIT, this function
 * will be called by RCINIT automatically, and clients should place a
 * dependency on 'pcie_osal'.
 *
 * @return None
 */
void pcie_osal_init(void);

/**
 * This function deinitializes the OSAL.
 *
 * @return None
 */
void pcie_osal_deinit(void);

/*----------------------------------------------------------------------------
 * Logging
 * -------------------------------------------------------------------------*/
/**
 * This function initializes logging for a given client.
 *
 * @param[in]  client        Which client
 * @param[in]  name          Log name
 * @param[in]  size          Size of log in bytes
 * @param[in]  filter_level  Log calls below this level will be filtered
 *                           out at run time (compile-time stripping is
 *                           preferred)
 *
 * @return None
 */
void pcie_osal_log_init(pcie_osal_log_client_t client, const char *name, size_t size,
                        pcie_osal_log_level_t filter_level);

unsigned long long AsciiPrint (const char* fmt, ...);

/** The following macros wrap _pcie_osal_log to avoid having to specify the
 *  number of arguments. Additionally, _fatal calls fatal error and does
 *  not return. These macros should be used instead of directly calling
 *  _pcie_osal_log. Clients may wish to further wrap these macros to avoid
 *  always having to specify their log ID.
 */
#define pcie_osal_log_low(client, fmt, ...) \
   AsciiPrint((fmt), ## __VA_ARGS__)

#define pcie_osal_log_med(client, fmt, ...) \
   AsciiPrint((fmt), ## __VA_ARGS__)

#define pcie_osal_log_high(client, fmt, ...) \
   AsciiPrint((fmt), ## __VA_ARGS__)

#define pcie_osal_log_error(client, fmt, ...) \
   AsciiPrint((fmt), ## __VA_ARGS__)

#define pcie_osal_log_fatal(client, fmt, ...) \
   do { \
      AsciiPrint((fmt), ## __VA_ARGS__); \
      ASSERT(fmt); \
   } while (0)


/**
 * This function writes a message to the client's log. Clients should use the
 * macro wrappers instead of calling this API directly to avoid having to pass
 * the number of variadic arguments.
 *
 * @attention For %s string format specifiers, only a pointer to the string
 * is stored. If the string changes then what is read from the log might
 * be different than expected.
 *
 * @param[in]  client    Which client
 * @param[in]  level     Log level
 * @param[in]  num_args  Number of arguments for the format string
 * @param[in]  fmt       Format string
 *
 * @return None
 */
void _pcie_osal_log(pcie_osal_log_client_t client, pcie_osal_log_level_t level,
                    uint32 num_args, const char *fmt, ...);

/**
 * This function copies a string to the client's log.
 *
 * @attention Since this function copies the whole string into the log,
 * only use it when absolutely neccessary, i.e. when not using const strings.
 *
 * @param[in]  client    Which client
 * @param[in]  level     Log level
 * @param[in]  fmt       Format string
 *
 * @return None
 */
void pcie_osal_log_string(pcie_osal_log_client_t client,
                          pcie_osal_log_level_t level,
                          const char *fmt, ...);

/**
 * This function gets the current system time in ticks.
 *
 * @return Current system time in ticks
 */
uint64 pcie_osal_get_systime_ticks(void);

/**
 * This function returns the time elapsed between two timestamps.
 *
 * @param[in]  t1    Start timestamp in ticks
 * @param[in]  t2    Stop timestamp in ticks
 * @param[in]  unit  Desired time unit
 *
 * @return Elapsed time in the desired units
 */
uint64 pcie_osal_get_elapsed_time(uint64 t1, uint64 t2, pcie_osal_time_unit_t unit);

/**
 * This function returns the start timestamp for profiling.
 *
 * @return Start timestamp
 */
static __inline uint64 pcie_osal_profile_start(void)
{
   return pcie_osal_get_systime_ticks();
}

/**
 * This function stops profiling and returns the time elapsed between start
 * and stop in the units desired.
 *
 * @param[in]  start  Start timestamp
 * @param[in]  unit   Desired time unit
 *
 * @return Elapsed time in the desired units
 */
static __inline uint64 pcie_osal_profile_stop(uint64 start, pcie_osal_time_unit_t unit)
{
   return pcie_osal_get_elapsed_time(start,
                                     pcie_osal_get_systime_ticks(),
                                     unit);
}

/*----------------------------------------------------------------------------
 * Memory
 * -------------------------------------------------------------------------*/
/**
 * This function dynamically allocates memory. Memory should be freed only with
 * \ref pcie_osal_free.
 *
 * @param[in]  size  Size (in bytes) of memory to allocate
 *
 * @return Pointer to the memory allocated; NULL if failed
 */
void* pcie_osal_malloc(size_t size);

/**
 * This function frees memory previously allocated by \ref pcie_osal_malloc.
 *
 * @param[in]  ptr  Memory to be freed
 *
 * @return None
 */
void pcie_osal_free(void *ptr);

/**
 * This function dynamically allocates memory with a specified alignment.
 * Memory should be freed only with \ref pcie_osal_free_aligned.
 *
 * @param[in]  size   Size (in bytes) of memory to allocate
 * @param[in]  align  Alignment - must be a power of 2
 *
 * @return Pointer to the memory allocated; NULL if failed
 */
void* pcie_osal_malloc_aligned(size_t size, uint8 align);

/**
 * This function frees memory previously allocated by
 * \ref pcie_osal_malloc_aligned.
 *
 * @param[in]  ptr  Memory to be freed
 *
 * @return None
 */
void pcie_osal_free_aligned(void *ptr);

/**
 * This function maps a physically continguous memory region. If the base
 * physical address is known then it must be provided. Otherwise, a memory
 * region will be allocated from the default pool. Memory should be unmapped
 * only with \ref pcie_osal_mem_region_unmap.
 *
 * @param[in]  pa         Desired base physical address or PCIE_OSAL_PA_UNSPECIFIED
 * @param[in]  size       Size (in bytes) of memory to allocate
 * @param[in]  mem_props  Memory type
 * @param[out] mem_info   Mapped memory region info
 *
 * @return 0 for success else an error
 */
int pcie_osal_mem_region_map(pcie_osal_pa_t pa, size_t size, pcie_osal_mem_props_t mem_props,
                             pcie_osal_mem_info_t *mem_info);

/**
 * This function unmaps memory previously allocated by
 * \ref pcie_osal_mem_region_map.
 *
 * @param[in]  mem_info  Mapped memory region info
 *
 * @return 0 for success else an error
 */
int pcie_osal_mem_region_unmap(pcie_osal_mem_info_t *mem_info);

/**
 * This function looks up the physical address for a virtual address.
 *
 * @param[in]  va  Virtual address
 *
 * @return Corresponding physical address
 */
pcie_osal_pa_t pcie_osal_va_to_pa(pcie_osal_va_t va);

/**
 * This function performs a cache operation on a given buffer.
 *
 * @attention It is the responsibility of the caller to ensure that the
 * cache lines that will be operated on fall within the buffer.
 *
 * @param[in]  op    Cache operation
 * @param[in]  va    Virtual address
 * @param[in]  size  Buffer size
 *
 * @return None
 */
void pcie_osal_cache_ctrl(pcie_osal_cache_op_t op, pcie_osal_va_t va, size_t size);

/**
 * This function issues a memory barrier.
 *
 * @return None
 */
void pcie_osal_memory_barrier(void);

/*----------------------------------------------------------------------------
 * Synchronization
 * -------------------------------------------------------------------------*/
/**
 * This function initializes a sync object.
 *
 * @param[out] sync   Sync object
 * @param[in]  flags  Bitmask of option flags
 *
 * @return 0 for success else an error
 */
int pcie_osal_sync_init(pcie_osal_sync_t *sync, uint32 flags);

/**
 * This function deinitializes a sync object.
 *
 * @param[in]  sync  Sync object
 *
 * @return 0 for success else an error
 */
int pcie_osal_sync_deinit(pcie_osal_sync_t *sync);

/**
 * This function enters into a synchronized context.
 *
 * @param[in]  sync  Sync object
 *
 * @return None
 */
void pcie_osal_sync_enter(pcie_osal_sync_t *sync);

/**
 * This function leaves a synchronized context.
 *
 * @param[in]  sync  Sync object
 *
 * @return None
 */
void pcie_osal_sync_leave(pcie_osal_sync_t *sync);

/*----------------------------------------------------------------------------
 * Events
 * -------------------------------------------------------------------------*/
/**
 * This function initializes an event object.
 *
 * @param[out] event  Event object
 *
 * @return 0 for success else an error
 */
int pcie_osal_event_init(pcie_osal_event_t *event);

/**
 * This function deinitializes an event object.
 *
 * @param[in]  event  Event object
 *
 * @return 0 for success else an error
 */
int pcie_osal_event_deinit(pcie_osal_event_t *event);

/**
 * This function resets an event to its unsignaled state.
 *
 * @param[in]  event  Event object
 *
 * @return None
 */
void pcie_osal_event_reset(pcie_osal_event_t *event);

/**
 * This function waits for an event to be signaled.
 *
 * @param[in]  event  Event object
 *
 * @return None
 */
void pcie_osal_event_wait(pcie_osal_event_t *event);

/**
 * This function signals an event.
 *
 * @param[in]  event  Event object
 *
 * @return None
 */
void pcie_osal_event_signal(pcie_osal_event_t *event);

/**
 * This function busywaits for the specified time.
 *
 * @param[in]  time_us  Busywait time in microseconds
 *
 * @return None
 */
void pcie_osal_busywait(uint32 time_us);

/**
 * This function sleeps for the specified time.
 *
 * @param[in]  time_ms         Sleep time in milliseconds
 * @param[in]  non_deferrable  Whether or not the sleep is deferrable
 *
 * @return None
 */
void pcie_osal_sleep(uint32 time_ms, boolean non_deferrable);

/*----------------------------------------------------------------------------
 * Threads
 * -------------------------------------------------------------------------*/
/**
 * This function spawns a thread.
 *
 * @param[out] thread    Thread object
 * @param[in]  name      Thread name
 * @param[in]  fcn       Function to invoke when thread starts
 * @param[in]  ctxt      Context passed to the thread
 * @param[in]  priority  Thread priority
 *
 * @return 0 for success else an error
 */
int pcie_osal_thread_spawn(pcie_osal_thread_t *thread, const char *name,
                           pcie_osal_cb_t fcn, void *ctxt, uint32 priority);

/*----------------------------------------------------------------------------
 * Buffers
 * -------------------------------------------------------------------------*/
/**
 * This function initializes memory to a desired value.
 *
 * @param[in]  ptr   Pointer to the buffer
 * @param[in]  val   Value to set
 * @param[in]  size  Number of bytes to initialize
 *
 * @return ptr
 */
void* pcie_osal_memset(void *ptr, uint8 val, size_t size);

/**
 * This function copies memory of a specified size to the destination of
 * a specified size. The number of bytes copied will not exceed the size
 * of the destination buffer.
 *
 * @param[out] dst       Pointer to the destination buffer
 * @param[in]  dst_size  Destination buffer size
 * @param[in]  src       Pointer to the source buffer
 * @param[in]  src_size  Number of bytes to copy from source
 *
 * @return Number of bytes copied (can be checked for truncation)
 */
size_t pcie_osal_memscpy(void *dst, size_t dst_size, const void *src, size_t src_size);

/**
 * This function is a safer version of strcpy that takes into consideration the
 * destination size and always NUL-terminates.
 *
 * @param[out] dst       Pointer to the destination buffer
 * @param[in]  src       Pointer to the source buffer
 * @param[in]  dst_size  Destination buffer size
 *
 * @return Length of the source string (can be checked for truncation)
 */
size_t pcie_osal_strlcpy(char *dst, const char *src, size_t dst_size);

/*----------------------------------------------------------------------------
 * Atomic Operations
 * -------------------------------------------------------------------------*/
/**
 * This function should be used to set the value of the variable being used
 * with atomic operations.
 *
 * @param[in]  ptr    Pointer to atomic variable
 * @param[in]  value  Value to set
 *
 * @return Value after the variable is set
 */
uint32 pcie_osal_atomic_set(uint32 *ptr, uint32 value);

/**
 * This function should be used to read the value of the variable being used
 * with atomic operations.
 *
 * @param[in]  ptr  Pointer to atomic variable
 *
 * @return Value read
 */
uint32 pcie_osal_atomic_read(uint32 *ptr);

/**
 * This function atomically sets a bit.
 *
 * @param[in]  ptr  Pointer to atomic variable
 * @param[in]  bit  Which bit
 *
 * @return None
 */
void pcie_osal_atomic_set_bit(uint32 *ptr, uint32 bit);

/**
 * This function atomically clears a bit.
 *
 * @param[in]  ptr  Pointer to atomic variable
 * @param[in]  bit  Which bit
 *
 * @return None
 */
void pcie_osal_atomic_clear_bit(uint32 *ptr, uint32 bit);

/**
 * This function atomically increments.
 *
 * @param[in]  ptr  Pointer to atomic variable
 *
 * @return Value after incrementing
 */
uint32 pcie_osal_atomic_inc(uint32 *ptr);

/**
 * This function atomically decrements.
 *
 * @param[in]  ptr  Pointer to atomic variable
 *
 * @return Value after decrementing
 */
uint32 pcie_osal_atomic_dec(uint32 *ptr);

/*----------------------------------------------------------------------------
 * Interrupts
 * -------------------------------------------------------------------------*/
/**
 * This function registers an ISR.
 *
 * @param[out] irq     IRQ object
 * @param[in]  irq_id  IRQ ID
 * @param[in]  isr     ISR to be called
 * @param[in]  ctxt    Context passed to the ISR
 *
 * @return 0 for success else an error
 */
int pcie_osal_isr_register(pcie_osal_irq_t *irq, uint32 irq_id, pcie_osal_cb_t isr, void *ctxt);

/**
 * This function unregisters an ISR.
 *
 * @param[in]  irq  IRQ object
 *
 * @return 0 for success else an error
 */
int pcie_osal_isr_unregister(pcie_osal_irq_t *irq);

/**
 * This function enables an IRQ.
 *
 * @param[in]  irq  IRQ object
 *
 * @return 0 for success else an error
 */
int pcie_osal_irq_enable(pcie_osal_irq_t *irq);

/**
 * This function disables an IRQ.
 *
 * @param[in]  irq  IRQ object
 *
 * @return 0 for success else an error
 */
int pcie_osal_irq_disable(pcie_osal_irq_t *irq);

/**
 * This function returns TRUE if an IRQ is set or FALSE if an
 * IRQ is not set.
 *
 * @param[in]  irq  IRQ object
 *
 * @return TRUE / FALSE
 */
boolean pcie_osal_irq_is_set(pcie_osal_irq_t *irq);

/**
 * This function masks an IRQ.
 *
 * @param[in]  irq  IRQ object
 *
 * @return 0 for success else an error
 */
int pcie_osal_isq_mask(pcie_osal_irq_t *irq);

/**
 * This function unmasks an IRQ.
 *
 * @param[in]  irq  IRQ object
 *
 * @return 0 for success else an error
 */
int pcie_osal_isq_unmask(pcie_osal_irq_t *irq);

/**
 * This function acknowledges an IRQ. Some OS implementations require the ISR
 * to ACK the IRQ to reactive the IRQ.
 *
 * @param[in]  irq  IRQ object
 *
 * @return 0 for success else an error
 */
int pcie_osal_irq_ack(pcie_osal_irq_t *irq);

/*----------------------------------------------------------------------------
 * Miscellaneous
 * -------------------------------------------------------------------------*/

/**
 * Get chip/platform information.
 *
 * @param[in]  chip_id_ptr          Location where to return Chip ID
 * @param[in]  chip_ver_ptr         Location where to return Chip ver
 * @param[in]  plat_info_ptr        Location where to return Platform Info
 *
 * @return 0 for success else an error
 */
int pcie_get_target_platform_info (uint32* chip_id_ptr, uint32* chip_ver_ptr, uint32* chip_family_ptr, uint32* plat_info_ptr);


/**
 * Generate a random integer.
 *
 * @return Randomly generated integer
 */
uint32 pcie_osal_rand();

#endif

