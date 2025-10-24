#include "boot_target.h"


/* External heap memory, inside DDR */
static byte boot_external_cached_heap[RAMDUMP_EXTERNAL_HEAP_SIZE];
uintnt * boot_external_cached_heap_base = (uintnt *)&boot_external_cached_heap;
uintnt boot_external_cached_heap_size = sizeof(boot_external_cached_heap);

static byte boot_external_uncached_heap[RAMDUMP_UNCACHED_DDR_HEAP_SIZE]  __attribute__((__aligned__(SIZE_4KB)));


/*===========================================================================
**  Function :  xbl_get_external_cached_heap_addr
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the external cached_heap address
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
byte * xbl_get_external_cached_heap_addr(void)
{
  return (byte*)boot_external_cached_heap;
}


/*===========================================================================
**  Function :  xbl_get_external_cached_heap_size
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the external cached_heap size
*
* @par Dependencies
*   None
*
* @retval
*   uintnt
*
* @par Side Effects
*   None
*
*/
uintnt xbl_get_external_cached_heap_size(void)
{
  return boot_external_cached_heap_size;
}


/*===========================================================================
**  Function :  xbl_get_external_uncached_heap_addr
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the external uncached heap addr
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
byte* xbl_get_external_uncached_heap_addr(void)
{
  return (byte *)(&boot_external_uncached_heap);
}


/*===========================================================================
**  Function :  xbl_get_external_uncached_heap_size
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the external uncached heap size
*
* @par Dependencies
*   None
*
* @retval
*   uintnt
*
* @par Side Effects
*   None
*
*/
uintnt xbl_get_external_uncached_heap_size(void)
{
  return RAMDUMP_UNCACHED_DDR_HEAP_SIZE;
}
