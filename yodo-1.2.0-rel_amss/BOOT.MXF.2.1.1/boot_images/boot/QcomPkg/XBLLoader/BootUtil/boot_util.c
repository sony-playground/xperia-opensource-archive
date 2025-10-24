/*=============================================================================
                        Boot Utility File 

GENERAL DESCRIPTION     
  This module defines miscellaneous utility function for boot software.
  
Copyright 2005, 2010, 2012, 2014-2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who         what, where, why
--------   ---         --------------------------------------------------
10/05/15   ck          Corrected copyright
05/22/15   as          Updates for AArch64 addresses.
07/16/14   ck          Added string include for memscpy usage
06/09/14   kedara      Add support for 64 bit compilation using llvm.
                       add uintnt cast to support 64-bit armv8
10/25/12   dh          Add boot_count_set_bits
09/27/10   dh          add boot_strlen
08/30/05   ja          Initial version  

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include "boot_util.h"

/*=========================================================================
                            
                            FUNCTION DEFINITIONS

=========================================================================*/
void qmemset (
  void* dst_ptr,
  uint32 val,
  uint32 len
)
{
  //
  // Declare the local variables that actually move the data elements as
  // volatile to prevent the optimizer from replacing this function with
  // the intrinsic memset()
  //
  volatile UINT8                    *Pointer8;
  volatile UINT32                   *Pointer32;
  volatile UINT64                   *Pointer64;
  UINT32                            Value32;
  UINT64                            Value64;

  if ((((UINTN)dst_ptr & 0x7) == 0) && (len >= 8)) {
    // Generate the 64bit value
    Value32 = (val << 24) | (val << 16) | (val << 8) | val;
    Value64 = (((UINT64)Value32) << 32) | Value32;

    Pointer64 = (UINT64*)dst_ptr;
    while (len >= 8) {
      *(Pointer64++) = Value64;
      len -= 8;
    }

    // Finish with bytes if needed
    Pointer8 = (UINT8*)Pointer64;
    while (len-- > 0) {
      *(Pointer8++) = val;
    }
  } else if ((((UINTN)dst_ptr & 0x3) == 0) && (len >= 4)) {
    // Generate the 32bit value
    Value32 = (val << 24) | (val << 16) | (val << 8) | val;

    Pointer32 = (UINT32*)dst_ptr;
    while (len >= 4) {
      *(Pointer32++) = Value32;
      len -= 4;
    }

    // Finish with bytes if needed
    Pointer8 = (UINT8*)Pointer32;
    while (len-- > 0) {
      *(Pointer8++) = val;
    }
  } else {
    Pointer8 = (UINT8*)dst_ptr;
    while (len-- > 0) {
      *(Pointer8++) = val;
    }
  }
}


