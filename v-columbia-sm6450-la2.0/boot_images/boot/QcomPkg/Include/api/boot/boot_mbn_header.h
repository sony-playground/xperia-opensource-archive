#ifndef __BOOT_MBN_HEADER_H__
#define __BOOT_MBN_HEADER_H__
/*===========================================================================

                MBN Header Definitions

DESCRIPTION
  This header file gives the definition of the structures in MBN header.
  
  Copyright 2020 Qualcomm Technologies Incorporated. 
  All Rights Reserved.
  Qualcomm Confidential and Proprietary
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

    This section contains comments describing changes made to this file.
    Notice that changes are listed in reverse chronological order.


   
when       who     what, where, why
--------   ---     ---------------------------------------------------------- 
02/18/20   rhy     Initial rev
===========================================================================*/

#include "boot_comdef.h"
#include "MIbib.h"

/*===========================================================================

                          MULTI-IMAGE HEADER FILE

DESCRIPTION
  This header file contains declarations and type definitions for the
  Image Header Information. Took the definition from miheader.h.
  Pointers have been changed to unsigned integer variables.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None

Copyright 2020 by Qualcomm Technologies, Incorporated.  All Rights Reserved.
============================================================================*/

typedef struct
{
  image_type image_id;       /* Identifies the type of image this header
                                 represents (OEM SBL, AMSS, Apps boot loader,
                                 etc.). */
  uint32 header_vsn_num;     /* Header version number. */
  uint32 image_src;          /* Location of image in flash: Address of
                                 image in NOR or page/sector offset to image
                                 from page/sector 0 in NAND/SUPERAND. */
  uint32 image_dest_ptr;    /* Pointer to location to store image in RAM.
                                 Also, entry point at which image execution
                                 begins. */
  uint32 image_size;         /* Size of complete image in bytes */
  uint32 code_size;          /* Size of code region of image in bytes */
  uint32 signature_ptr;      /* Pointer to images attestation signature */
  uint32 signature_size;     /* Size of the attestation signature in
                                 bytes */
  uint32 cert_chain_ptr;    /* Pointer to the chain of attestation
                                 certificates associated with the image. */
  uint32 cert_chain_size;   /* Size of the attestation chain in bytes */

} mi_boot_image_header_type;

#endif /* __BOOT_MBN_HEADER_H__ */

