#ifndef BOOT_HEAP_INIT
#define BOOT_HEAP_INIT
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
byte* sbl1_get_external_heap_addr(void);

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
uint32 sbl1_get_external_heap_size(void);
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
byte* sbl1_get_internal_heap_addr(void);

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
uint32 sbl1_get_internal_heap_size(void);
/*===========================================================================

**  Function :  xbl_get_uncached_heap_addr

** ==========================================================================
*/
/*!
*
* @brief
*   This function returns uncached heap address
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
byte* xbl_get_uncached_heap_addr(void);

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
uint32 xbl_get_uncached_heap_size(void);
#endif
