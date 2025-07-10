#include "boot_target.h"

/* External heap memory, inside DDR */
static byte boot_external_heap[RAMDUMP_EXTERNAL_HEAP_SIZE];
uint64 *boot_external_heap_base = (uint64 *)&boot_external_heap;
uint64 boot_external_heap_size = sizeof(boot_external_heap);
static byte ramdump_uncached_ddr_heap[RAMDUMP_UNCACHED_DDR_HEAP_SIZE]  __attribute__((__aligned__(SIZE_4KB)));
/*===========================================================================

**  Function :  sbl1_get_external_heap_addr

** ==========================================================================
*/
/*!
*
* @brief
*   This function returns external heap address
*
* @par Dependencies
*   None
*
* @retval
*   byte *
*
* @par Side Effects
*   None
*
*/

byte* sbl1_get_external_heap_addr(void)
{
  return (byte*)boot_external_heap;
}

/*===========================================================================

**  Function :  sbl1_get_external_heap_size

** ==========================================================================
*/
/*!
*
* @brief
*   This function returns external heap size
*
* @par Dependencies
*   None
*
* @retval
*   uint32
*
* @par Side Effects
*   None
*
*/
uint32 sbl1_get_external_heap_size(void)
{
  return boot_external_heap_size;
}

/*===========================================================================

**  Function :  xbl_get_uncached_heap_addr

** ==========================================================================
*/
/*!
*
* @brief
*   This function returns uncached heap addr
*
* @par Dependencies
*   None
*
* @retval
*   uint32
*
* @par Side Effects
*   None
*
*/
byte* xbl_get_uncached_heap_addr(void)
{
  return (byte *)(&ramdump_uncached_ddr_heap);
}

/*===========================================================================

**  Function :  xbl_get_uncached_heap_size

** ==========================================================================
*/
/*!
*
* @brief
*   This function returns uncached heap size
*
* @par Dependencies
*   None
*
* @retval
*   uint32
*
* @par Side Effects
*   None
*
*/
uint32 xbl_get_uncached_heap_size(void)
{
  return RAMDUMP_UNCACHED_DDR_HEAP_SIZE;
}
