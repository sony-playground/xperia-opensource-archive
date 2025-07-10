#ifndef _IMAGE_OFFSETS_H
#define _IMAGE_OFFSETS_H

/*===========================================================================

                               Image Offsets
                                Header File

GENERAL DESCRIPTION
  This header file contains target specific declarations and definitions

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2020 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   --------     ----------------------------------------------------------
10/29/20   ka           Initial version
============================================================================*/

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/


/*===========================================================================
                         IMAGE OFFSET DEFINES FOR TARGET
===========================================================================*/

#define UEFI_FD_SIZE              0x1000000
#define UEFI_INFO_BLK_OFFSET      0x601000
#define UEFI_INFO_BLK_SIZE        0x001000
#define SEC_HEAP_MEM_OFFSET       0x64D000
#define SEC_HEAP_MEM_SIZE         0x08C000
#define SERIAL_BUFFER_OFFSET      0x605000
#define SERIAL_BUFFER_SIZE        0x008000
#define BYTES_TO_MB               0x100000

#endif  /* _IMAGE_OFFSETS_H */
