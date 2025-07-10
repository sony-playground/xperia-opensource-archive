#ifndef _XBL_MINIDUMP_KEY_STRUCT_H
#define _XBL_MINIDUMP_KEY_STRUCT_H

/*===========================================================================

                                OEM public key for minidump encryption
                                

GENERAL DESCRIPTION
  This header file contains OEM public key for minidump encryption

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright (c) 2021 Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.0/QcomPkg/SocPkg/Include/xbl_minidump_key_struct.h#1 $
  $DateTime: 2021/07/22 19:05:34 $ 
  $Author: pwbldsvc $

when       who          what, where, why
--------   --------     ----------------------------------------------------------
07/12/21   rama         Initial version
============================================================================*/

/*===========================================================================*/


typedef struct
{
  uint32      bitLength;   
  char  *n;          
  const char  *p;
  const char  *q;
  char  *e;
  const char  *d;
}raw_key_t;

#endif  /* _XBL_MINIDUMP_KEY_STRUCT_H */