/** @file SerialPortShLibInstall.h
   
  Interface to install Shared serial lib.

  Copyright (c) 2012 - 2020 Qualcomm Technologies, Inc.  All Rights Reserved. 
   
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 03/31/20   md      Added "ReplayLogs" and "SerialPortDrainToDest" API
 12/18/18   md      Added API to reinit serial buffer with configurable size.
                    Added API to prevent reinit of serial buffer. 
 11/01/16   bh      Add API to initialize log buffer parameters
 12/12/12   yg      Initial Version

=============================================================================*/
#ifndef __SIO_SH_LIB_INSTALL__H__
#define __SIO_SH_LIB_INSTALL__H__

#include <Uefi.h>

/* This function installs the Serial Port Shared Library into system.
 * Only SEC should be calling this function only once during system Init. */
EFI_STATUS SerialPortShLibInit (VOID);

EFI_STATUS
SerialBufferInit( IN  UINT8*   SerialBuffer  OPTIONAL, 
                  IN  UINT32   BufferSize    OPTIONAL);

EFI_STATUS
SerialBufferReInit( IN  UINT8*   SerialBuffer  OPTIONAL,
                    IN  UINT32   BufferSize    OPTIONAL);

VOID SerialBufferReInitLock (VOID); 


/* Retrieve logs to Replay
* Copy the max available logs from the log buffer to a new buffer. Potentially
* useful to replay the logs to some other interface (file) by retrieving to buffer.
*
* Its guaranteed to provide the logs in a right chronological order (ie from
* oldest logs to newest logs as it shows on the UART port) regardless of the
* wrap around situation in the log buffer.
*
* First invocation with just MaxLogSize valid argument, it returns the max amount
* of buffer required to retrieve full logs. If the client has smaller buffer,
* second invocation can provide Start Offset to continue to retrieve the logs
* past previous retrieval */
EFI_STATUS ReplayLogs (UINTN StartOffset OPTIONAL, 
                       UINTN* MaxLogSize OPTIONAL, 
                       UINT8* DestBuffer OPTIONAL, 
                       UINTN DestBuffSize OPTIONAL);


/* Drain the remaining active data in buffer to the specified destination .
*
* If the destination is a valid buffer of valid size, then drain the data
* to the buffer of max BuffSize or as much is outstanding.
*
* If the detination is NULL pointer, then drain the outstanding log data
* to NULL device (ie the data is marked as completely drained).
*
* Returns the number of bytes drained to destination.
*
**/ 
UINTN SerialPortDrainToDest (UINT8* DestBuffer,
                             UINTN BufferSize);

#endif /* __SIO_SH_LIB_INSTALL__H__ */

