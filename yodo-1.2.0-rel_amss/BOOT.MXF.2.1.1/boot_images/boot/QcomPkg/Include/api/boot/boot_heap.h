#ifndef BOOT_HEAP_INIT
#define BOOT_HEAP_INIT


/*===========================================================================
**  Function :  xbl_get_external_cached_heap_addr
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the external cached heap address
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
byte* xbl_get_external_cached_heap_addr(void);


/*===========================================================================
**  Function :  xbl_get_external_cached_heap_size
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns external cached heap size
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
uintnt xbl_get_external_cached_heap_size(void);


/*===========================================================================
**  Function :  xbl_get_internal_cached_heap_addr
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the internal cached heap address
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
byte* xbl_get_internal_cached_heap_addr(void);


/*===========================================================================
**  Function :  xbl_get_internal_cached_heap_size
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the internal cached heap size
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
uintnt xbl_get_internal_cached_heap_size(void);


/*===========================================================================
**  Function :  xbl_get_internal_cached_heap_addr
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the internal uncached heap address
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
byte* xbl_get_internal_uncached_heap_addr(void);


/*===========================================================================
**  Function :  xbl_get_internal_uncached_heap_size
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the internal uncached heap size
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
uintnt xbl_get_internal_uncached_heap_size(void);


/*===========================================================================
**  Function :  xbl_get_external_cached_heap_addr
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the external uncached heap address
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
byte* xbl_get_external_uncached_heap_addr(void);


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
uintnt xbl_get_external_uncached_heap_size(void);

#endif
