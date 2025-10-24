#ifndef BOOT_UTIL_H
#define BOOT_UTIL_H

/*=============================================================================
                        Boot Utility Header File 

GENERAL DESCRIPTION     
  This module defines miscellaneous utility function for boot software.
  
Copyright 2005-2014 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/

/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------- 
06/09/14   kedara       Update for 64 bit compilation using LLVM (remove inline "asm")
05/07/14   kedara       Make inlined api boot_get_bit_set_position static
10/25/12   dh           Add boot_count_set_bits
                        Remove pragma to surpass inline assemly since armct5.01 allows it
10/13/11   kedara       Suppress inline assembly warning for rvct4.1
09/01/11   kedara       Added arm pragma.
06/28/10   plc          Fix bug for C-implemented solution for Arm7 CLZ 
04/29/10   dxiang       Add interface for fast_memcpy() and fast_memzi()
03/03/10   plc          Add support for compiling for Arm7 Processor
12/02/09   tnk          Compilation of boot_get_bit_set_position in arm mode 
                        and rest of the file in thumb mode for 512B Nand
                        Support feature. 
11/13/09   tnk          Disableing the boot_get_bit_set_position compilation 
                        if DBL is compiled for Thumbmode. 
8/30/05   John Alayari  Initial version  

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"

#undef  WORDSIZE
#define WORDSIZE   sizeof(int)
#undef  WORDMASK
#define WORDMASK   (WORDSIZE - 1)

typedef uint32 BLONG;

/*=========================================================================
                            
                          FUNCTION DEFINITIONS

=========================================================================*/

/*===========================================================================

**  Function : qmemset

** ==========================================================================
*/
/*!
* 
* @brief
*   
*   This function set a block of memory to agiven value.
*  
*   This routine implements memset and ensures that read 
*   and write operations from/to memory are 32 bit aligned 
*   This function sets Len bytes of destination to input value.
* 
*  
* @par Dependencies
*   None.
* 
* @param
*   dst_ptr         - Pointer to destination buffer.
*   val             - Value  to be set
*   len             - Length to set
*
* @retval
*   None.
* 
* @par Side Effects
*   None.
*/
void qmemset (
  void* dst_ptr,
  uint32 val,
  uint32 len
);

#endif /* BOOT_UTIL_H */

