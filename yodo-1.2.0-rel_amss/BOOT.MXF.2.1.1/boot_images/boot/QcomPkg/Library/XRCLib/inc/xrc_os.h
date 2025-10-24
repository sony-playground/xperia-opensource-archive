/*=============================================================================

                            XRC OS

 XRC Communication OS interface

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef XRC_OS_H
#define XRC_OS_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"
#include <stdlib.h>
#include <string.h>
#include "xrc_log.h"
#include "DALSys.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/
#ifndef XRC_LOG_TAG
#define XRC_LOG_TAG "OS"
#endif

#ifndef inline
#define inline __inline
#endif

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/

/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/

/*=============================================================================

                    PUBLIC FUNCTION DECLARATIONS

=============================================================================*/

/*=============================================================================
  FUNCTION  xrc_os_malloc
=============================================================================*/
/**
 * Allocates the requested memory and returns a pointer to it
 * @param[in] size: Size of memory to be allocated
 *
 * @return
 * Pointer to the memory allocated. It is the caller resposibility to check 
 * memory is allocated or not
 *
 */
/*===========================================================================*/
static inline void *xrc_os_malloc(uint32 size)
{
  void *ptr;
  DALSYS_Malloc(size,(void**)&ptr);
  
  return ptr;
}

/*=============================================================================
  FUNCTION  xrc_os_calloc
=============================================================================*/
/**
 * Allocates the requested memory and returns a pointer to it
 * @param[in]:Size of memory to be allocated
 *
 * @return
 * Allocates the requested memory and returns a pointer to it
 * Difference in xrc_os_malloc and xrc_os_calloc is that xrc_os_malloc does not 
 * set the memory to zero where as xrc_os_calloc sets allocated memory to zero.
 */
/*===========================================================================*/
static inline void *xrc_os_calloc(uint32 count, uint32 size)
{
  void *ptr;

  DALSYS_Malloc(count * size,(void**)&ptr);
  if(ptr)
  {
    memset(ptr, 0, count * size);
  }
  return ptr;
}

/*=============================================================================
  FUNCTION  xrc_os_free
=============================================================================*/
/**
 * Frees the allocated memory
 * @param[in]: Ponter to the memory
 *
 * @return
 *
 */
/*===========================================================================*/
static inline void xrc_os_free(void *ptr)
{
  DALSYS_Free(ptr);
}

/*===========================================================================
  FUNCTION  xrc_os_memcopy
===========================================================================*/
/**
  Copies bytes from the source buffer to the destination buffer.

  This function ensures that there will not be a copy beyond the size of 
  the destination buffer.

  The result of calling this on overlapping source and destination
  buffers is undefined.
  
  @param[out] dst       Destination buffer.
  @param[in]  dst_size  Size of the destination buffer in bytes.
  @param[in]  src       Source buffer.
  @param[in]  copy_size Number of bytes to copy from source buffer.

  @return
  The number of bytes copied to the destination buffer.  It is the
  caller's responsibility to check for trunction if it cares about it -
  truncation has occurred if the return value is less than src_size.
*/
/*==========================================================================*/
static inline uint32 xrc_os_memcopy
(
  void       *dst, 
  uint32     dst_size, 
  const void *src, 
  uint32     copy_size
)
{
  uint32 ret_size;

  ret_size = memscpy(dst, dst_size, src, copy_size);
  return ret_size;
}

/*===========================================================================
  FUNCTION  xrc_os_memmove
===========================================================================*/
/**
  Moves bytes from the source buffer to the destination buffer.

  This function ensures that there will not be a copy beyond 
  the size of the destination buffer. 

  This function should be used in preference to memscpy() if there
  is the possiblity of source and destination buffers overlapping.
  The result of the operation is defined to be as if the copy were from
  the source to a temporary buffer that overlaps neither source nor
  destination, followed by a copy from that temporary buffer to the
  destination.
   
  @param[out] dst       Destination buffer.
  @param[in]  dst_size  Size of the destination buffer in bytes.
  @param[in]  src       Source buffer.
  @param[in]  copy_size Number of bytes to copy from source buffer.
   
  @return 
  The number of bytes copied to the destination buffer.  It is the
  caller's responsibility to check for trunction if it cares about it -
  truncation has occurred if the return value is less than src_size.
*/
/*==========================================================================*/
static inline uint32 xrc_os_memmove
(
  void       *dst, 
  uint32     dst_size, 
  const void *src, 
  uint32     copy_size
)
{
  uint32 ret_size;

  ret_size = memsmove(dst, dst_size, src, copy_size);
  return ret_size;
}

#ifdef __cplusplus
}
#endif

#endif /* SLVCOM_OS_H */
