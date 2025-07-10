/**
  @file Credential.c
        Implementation of IIO.h APIs  

   Copyright (c) 2020 QUALCOMM Technologies, Inc.  All Rights Reserved.

*/
/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
01/09/20   shl     Initial revision

=============================================================================*/
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <object.h>
#include "Credential.h"
#include "IIO_invoke.h"
#include <Library/MemoryAllocationLib.h>


/**
 * IIO object context, it only stores a buffer representing the all UEFI client credential.
 */
typedef struct
{
  uint8_t *buffer;
  size_t   bufferLen;
  int      refs;
}Credential;


int32_t Credential_release(Credential * me)
{
   if (--me->refs == 0)
      FreePool(me);

   return Object_OK;
}


static int32_t Credential_retain(Credential * me)
{
   ++me->refs;
   return Object_OK;
}


static int32_t Credential_getLength( const Credential *me, uint64_t *len_ptr)
{
    if( !len_ptr )
       return Object_ERROR_INVALID;

   *len_ptr = me->bufferLen;
    return Object_OK;
}


static int32_t Credential_readAtOffset( const Credential  *me,
                                              uint32_t     offset,
                                              void        *value,
                                              size_t       valueLen,
                                              size_t      *valueLenOut)
{
   if( !value || !valueLenOut )
      return IIO_ERROR_INVALID_BUFFER_AND_OFFSET;

   if( offset >= ( me->bufferLen - 1) )
      return IIO_ERROR_OFFSET_OUT_OF_BOUNDS;

   *valueLenOut = memscpy(value, valueLen, me->buffer+offset, me->bufferLen-offset);
   return Object_OK;
}


static int32_t Credential_writeAtOffset( Credential  *me,
                                         uint64_t     offset_val,
                                         void const  *data_ptr,
                                         size_t       data_len )
{
   return Object_ERROR_INVALID;
}


static IIO_DEFINE_INVOKE(Credential_invoke, Credential_, Credential *)


/**
 * Create an IIO object using the input credential content.
 */
int32_t Credential_create( const uint8_t *buffer,
                                 size_t   bufferLen,
                                 Object  *objOut )
{
   *objOut = Object_NULL;

   if( !buffer || bufferLen == 0 )
       return Object_ERROR;

   /* one time combined allocation for better performance and simple memory management */
   Credential *me = (Credential *)AllocateZeroPool( sizeof(Credential) + bufferLen );
   if (me == NULL)
      return Object_ERROR_KMEM;

   me->refs      = 1;
   me->bufferLen = bufferLen;
   me->buffer    = (uint8_t *)me + sizeof(Credential);
   memscpy( me->buffer, me->bufferLen, buffer, bufferLen );

   *objOut = (Object) { Credential_invoke, me };

   return Object_OK;
}
