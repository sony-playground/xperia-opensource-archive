/**
 * @file usb4_mem.h
 *
 * @brief USB4 Memory DMA pools.
 *
 * Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 */
#ifndef __USB4_MEM_H__
#define __USB4_MEM_H__

/*----------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------*/
// #include "VVHAL_usb4_comdef.h"      /* base types definitions */

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 *-------------------------------------------------------------------------*/
/** Memory management flags */
#define USB4_MEM_ZERO          0x0001  /**< Zero the allocation */
#define USB4_MEM_PAGE_ALIGN    0x0004  /**< Block must not cross page boundaries */


/*----------------------------------------------------------------------------
 * Type Declarations
 *-------------------------------------------------------------------------*/
/** @brief enum defines the memory region to be used */
typedef enum USB4_mem_region_t
{
   USB4_MEM_REGION_DEFAULT = 0, /**< The default USB4 pool */
   USB4_MEM_REGION_HIGH    = 1, /**< USB4 HIGH DMA (depends on platform) */
   USB4_MEM_REGION_MAX,
} USB4_mem_region;

/** @brief definition of a memory region */
typedef struct USB4_mem_region_cfg_s
{
   USB4_mem_region region; /**< region type */
   void* vaddr;            /**< start virtual address */
   UINT64 paddr;           /**< start physical address */
   UINT32 size_bytes;      /**< region size in bytes */
} USB4_mem_region_cfg;

/** @brief definition of a memory regions array */
typedef struct USB4_mem_regions_arr_s
{
   const USB4_mem_region_cfg *regions;
   UINT32 size;
} USB4_mem_regions_arr;

/** @brief definition of a buffer */
typedef struct usb4_buff_s
{
   USB4_mem_region region;    /**< memory region which is used */
   UINT32 size_bytes;         /**< buffer size in bytes */
   UINT32 align_bytes;        /**< buffer alignment in bytes */
   UINT8* vaddr;              /**< virtual pointer */
   UINT64 paddr;              /**< physical pointer */
   void*  handle;             /**< handler to be used by this manager */
} usb4_buff;

/** @brief DMA and MEM allocations statistics */
typedef struct usb4_memStats_s
{
   /** Counter for allocated and not freed from MEM POOL */
   UINT32 nMemAllocCnt;

   /** Max requested size for a single MEM allocation (may be a failed req) */
   UINT32 nMemMaxAlloc;

   /** Counter for allocated and not freed from DMA POOL */
   UINT32 pDmaAllocCnt[USB4_MEM_REGION_MAX];

   /** Max requested size for a single DMA allocation (may be a failed req) */
   UINT32 pDmaMaxAlloc[USB4_MEM_REGION_MAX];
} usb4_memStats;


/*----------------------------------------------------------------------------
 * Global variables
 *-------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static functions
 *-------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 * API functions decleration
 *-------------------------------------------------------------------------*/

/**
 * @brief Init all available memory regions
 * @return 0 or error reason on failure
 *
 */
int usb4_mem_init(void);

/**
 * @brief Un-initializes the memory-allocator service
 */
void usb4_mem_uninit(void);

/**
 * @brief De-fragments the freed memory blocks of all pools
 * @note Under normal operation there should be no need to call this
 *       API. De-fragmentation will automatically be attempted when
 *       an allocation attempt fails
 * @return  0 or error reason on failure
 */
int usb4_mem_defrag(void);

/**
 * @brief Allocate memory from default region
 * @param [in] size - Size of the required buffer, in bytes
 * @param [in] flags - Size of the required buffer, in bytes
 * @return NULL if failed, else pointer to the allocated buffer
 *
 */
void* usb4_mem_alloc(UINT32 size, UINT16 flags);

/**
 * @brief Free previously allocated memory
 * @param [in] buff - Pointer to a memory block previously allocated
 *                    by usb4_mem_allocate(), that needs to be freed
 *
 */
void usb4_mem_free(void* buff);

/**
 * @brief Free previously allocated memory
 * @param[in/out] pStats - output the memory statistics
 * @return 0 on success, other on failure
 *
 */
int usb4_mem_getstats(usb4_memStats* pStats);

/**
 * @brief Allocate dma memory from specific region
 * @param [in,out] buff - Defines request and results of allocation
 * @return 0 or error reason on failure
 *
 */
int usb4_mem_dma_alloc(usb4_buff* buff);

/**
 * @brief Free previously allocated dma memory
 * @param [in] buff - Defines memory for release
 *
 */
void usb4_mem_dma_free(usb4_buff* buff);

/**
  * @brief compare two buffers for number of bytes 
  * @param [in] buffA - buffer to compare
  * @param [in] buffB - buffer to compare to
  * @param [in] max_bytes - number of bytes to compare 
  * @return 0 if equal, otherwise the 1st byte which is different
  */
int usb4_mem_strncmp(const UINT8* buffA, const UINT8* buffB, UINT32 max_bytes);

/**
  * @brief copies n characters from memory area src to memory area dst. 
  * @param [in] src - destination array where the content is to be copied
  * @param [in] dest - source of data to be copied
  * @param [in] n - number of bytes to be copy 
  * @return 0 on success, other on failure
  */
int usb4_mem_memcpy(void* dest, const void* src, UINT32 n);

/**
  * @brief copies n characters from memory area src to memory area dst.  For firmware copying only
  * @param [in] src - destination array where the content is to be copied
  * @param [in] dest - source of data to be copied
  * @param [in] n - number of bytes to be copy 
  * @return 0 on success, other on failure
  */
int usb4_mem_memcpy_custom(void* dest, const void* src, UINT32 n);


/**
  @brief sets the first num bytes of the block of memory pointed by ptr 
         to the specified value (interpreted as an unsigned char).
  * @param [in] dest - pointer to the block of memory to fill
  * @param [in] ch - value to be set. 
  * @param [in] n Number of bytes to be set to the value.
  * @return 0 on success, other on failure
  */
int usb4_mem_memset(void* buff, int ch, UINT32 n);

#endif /* __USB4_MEM_H__ */
