#ifndef BOOT_PARTITION_RW_H
#define BOOT_PARTITION_RW_H
/*=============================================================================

                     Boot Partition Read

GENERAL DESCRIPTION
  This file contains the implementation for boot layer that provides the APIs
  for reading and writing to block based flash devices.

Copyright 2019-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/


/*=============================================================================

                            EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.


when       who          what, where, why
--------   ---          -------------------------------------------------------
06/03/22   rama         Remove whitelist dependency for clients
07/23/21   rrwt      Initial revision.
=============================================================================*/

/*=============================================================================

LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/*=============================================================================

FUNCTION DEFINITIONS

=============================================================================*/

boolean boot_read_from_partition( 
									uint8* partition_id_main,
									uint8* partition_id_secondary,
									uint64 partition_offset,
									uint8* buffer_ptr,
									uint32 buffer_size
								);
								
boolean boot_write_to_partition( 
									uint8* partition_id_main,
									uint8* partition_id_secondary,
									uint64 partition_offset,
									uint8* buffer_ptr,
									uint32 buffer_size
								);

boolean boot_get_partition_size(uint8* partition_id, uint32* partition_size);

#endif