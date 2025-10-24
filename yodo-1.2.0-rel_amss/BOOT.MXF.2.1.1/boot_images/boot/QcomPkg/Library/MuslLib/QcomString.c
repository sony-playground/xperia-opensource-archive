/********************************************************************
 * @file LoaderUtils.c
 *
 * @brief String/Utility function for XBL Loader
 *
 * Copyright (C) 2014,2020 by Qualcomm Technologies Inc. All Rights Reserved.
 *
 *********************************************************************/
/*=======================================================================
                        Edit History

when       who     what, where, why
--------   ----    ---------------------------------------------------
09/24/20   ds      add memset_32bit_alligned
01/01/15   bh      Remove stlib function definitions
10/14/14   jb      Removed duplicate memset declaration
09/10/14   ck      Fixed bug with strlcpy's return value
08/21/14   kedara  Update snprintf implementation.
07/18/14   kedara  Added strncmp, strcmp api's.
06/20/14   kedara  Initial revision
========================================================================*/
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include "assert.h"
#include "com_dtypes.h"

#define PCD_MAX_ASCII_STRING_LENGTH 1000000

#define MAX_FORMAT_STR_SIZE 1024
char format_str_buff[MAX_FORMAT_STR_SIZE];

size_t memscpy( void *dst, size_t dst_size, const void *src, size_t src_size)
{
  size_t  copy_size = (dst_size <= src_size)? dst_size : src_size;
  CopyMem(dst, src, copy_size);
  return copy_size;
}

static void *xbl_memmove(void *dst, const void *src, size_t len)
{
  return CopyMem(dst, src, len);
}

size_t memsmove(void *dst, size_t dst_size, const void *src, size_t src_size)
{
  size_t  copy_size = (dst_size <= src_size)? dst_size : src_size;
  xbl_memmove(dst, src, copy_size);
  return copy_size;
}


size_t wstrlcpy(CHAR16 * dst,
                const CHAR16 * src,
                size_t size)
{
  /* StrnCpy is natively uses 2 byte characters (I.E. wchar) */
  if (StrnCpyS(dst, size+1,
              src,
              size) != RETURN_SUCCESS)
  {
    /* An error occured if return value from strncpy does not match dst */
  }

  /* Return the characters copied and not the null padding */
  return StrLen(dst);
}

void memset_32bit_alligned(void* dest, uint8_t ch, uint32_t size)
{
    uint32_t* dest_ptr32 = (uint32_t*)dest;
    uint64_t* dest_ptr = NULL;
    uint64_t  num64b = 0;
    uint32_t  num32b = 0;
    
    /* Check for null pointer */
    if(dest_ptr32 == NULL)
    {
      return;
    }
    
    /* Check if dest address and size is aligned to 4 bytes */
    if(((((uint32_t)(uintptr_t)dest_ptr32) & 3) != 0) || ((size & 3) !=0))
    {
      return;
    }

    /* Make a 4 byte value from the passed argument for word writes */
    num32b = ((uint32_t)ch << 8) | ((uint32_t)ch);
    num32b = (num32b << 16) | num32b;
    
    /* Make a 8 byte value for double word writes */
    num64b = ((uint64_t)num32b << 32) | ((uint64_t)num32b);
    
    /* write 4 bytes to make address 8 bytes aligned if not already */
    if(((uint64_t)dest_ptr32 & 7) != 0)
    {
      *(dest_ptr32++) = num32b;
      size-=4;
    }
    
    /* get the pointer ready for 8 byte writes */
    dest_ptr = (uint64_t*)dest_ptr32;
    
    /* write 8 bytes for the remaining size */
    while((size/8) > 0)
    {
      *(dest_ptr++) = num64b;
      size-=8;
    }
    
    dest_ptr32 = (uint32_t*) dest_ptr;
    
    /* write remaining 4 bytes */
    while((size/4) > 0)
    {
      *(dest_ptr32++) = num32b;
      size-=4;
    }
    
    return; 
}
