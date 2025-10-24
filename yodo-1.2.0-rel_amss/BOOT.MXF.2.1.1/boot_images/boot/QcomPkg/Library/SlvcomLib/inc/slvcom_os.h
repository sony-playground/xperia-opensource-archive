/*=============================================================================

                            SLVCOM OS

 Slave Communication OS interface

 Copyright  2021 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/inc/slvcom_os.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef SLVCOM_OS_H
#define SLVCOM_OS_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"
#include <stdlib.h>
#include <string.h>
// #include <LoaderUtils.h>
#include "slvcom_log.h"
#include "DALSys.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/
#ifndef SLVCOM_LOG_TAG
#define SLVCOM_LOG_TAG "OS"
#endif

#ifndef inline
#define inline __inline
#endif

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/
typedef uint32 slvcom_os_mutex_type;

/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/

/*=============================================================================

                    PUBLIC FUNCTION DECLARATIONS

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_os_malloc
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void *slvcom_os_malloc(uint32 size)
{
  void *ptr;
  DALSYS_Malloc(size,(void**)&ptr);
  
  return ptr;
}

/*=============================================================================
  FUNCTION  slvcom_os_calloc
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void *slvcom_os_calloc(uint32 count, uint32 size)
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
  FUNCTION  slvcom_os_free
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void slvcom_os_free(void *ptr)
{
  DALSYS_Free(ptr);
}

/*=============================================================================
  FUNCTION  slvcom_os_mutex_init
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void slvcom_os_mutex_init(slvcom_os_mutex_type *mutex)
{
  //Mutex not present/required on SBL
}

/*=============================================================================
  FUNCTION  slvcom_os_mutex_deinit
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void slvcom_os_mutex_deinit(slvcom_os_mutex_type *mutex)
{
  //Mutex not present/required on SBL
}

/*=============================================================================
  FUNCTION  slvcom_os_mutex_lock
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void slvcom_os_mutex_lock(slvcom_os_mutex_type *mutex)
{
  //Mutex not present/required on SBL
}

/*=============================================================================
  FUNCTION  slvcom_os_mutex_unlock
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void slvcom_os_mutex_unlock(slvcom_os_mutex_type *mutex)
{
  //Mutex not present/required on SBL
}

/*=============================================================================
  FUNCTION  slvcom_os_sleep
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void slvcom_os_sleep(uint32 usec)
{
  //Timers not present/required on SBL
}

/*=============================================================================
  FUNCTION  slvcom_os_get_thread_id
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline uint32 slvcom_os_get_thread_id(void)
{
  return 0;
}

/*===========================================================================
  FUNCTION  slvcom_os_memcopy
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
static inline uint32 slvcom_os_memcopy
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
  FUNCTION  slvcom_os_memmove
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
static inline uint32 slvcom_os_memmove
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

/*=============================================================================
  FUNCTION  slvcom_os_init
=============================================================================*/
/**
 * @param[in]
 *
 * @return
 *
 * @sideeffects
 */
/*===========================================================================*/
static inline void slvcom_os_init(void)
{

}

#ifdef __cplusplus
}
#endif

#endif /* SLVCOM_OS_H */
