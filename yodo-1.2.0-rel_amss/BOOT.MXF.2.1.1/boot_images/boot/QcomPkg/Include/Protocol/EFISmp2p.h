/** 
  @file  EFISmp2p.h
  @brief Smp2p Protocol for UEFI.
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     ----------------------------------------------------------
 02/10/20   ar      Initial version for Smp2p lib.

=============================================================================*/
#ifndef __EFISMP2P_H__
#define __EFISMP2P_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/
#include "smp2p_common.h"
#include <Library/KernelLib.h>

/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/

/** @ingroup efi_smp2p_constants
  Protocol version.
*/
#define EFI_SMP2P_PROTOCOL_REVISION 0x0000000000010001

/*  Protocol GUID definition */
/** @ingroup efi_smp2p_protocol */
#define EFI_SMP2P_PROTOCOL_GUID \
  { 0xfe8e7e5f, 0x5bc9, 0x45a2, { 0x86, 0x86, 0xf2, 0x2c, 0x12, 0xaf, 0xf2, 0xa3 } }

/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/*
  External reference to the SMP2P Protocol GUID.
 */
extern EFI_GUID gEfiSMP2PProtocolGuid;
/** @endcond */
/*===========================================================================
  FUNCTION  smp2p_create
===========================================================================*/
/**
  Creates one SMP2P 32 bit entry on behalf of the client to the specified
  destination.

  Clients may call this routine multiple times to create multiple entries.

  If the SMP2P connection has not been opened, that process will be initiated
  and this function will return a status code indicating that initialization
  is in progress.

  The client may call smp2p_write when either of the following two has occurred:
    - This function returns success.
    - The client has called the wait API.

  @param [out]  ctx       Pointer to pointer of SMP2P context.
                          Context will be created and this pointer will be made
                          to point to it.
  @param [in]   dest      Destination processor ID.
  @param [in]   name      16 byte name string.
                          Must be unique for outbound entries to the specified
                          endpoint.

  @param [out]  ret
  SMP2P_STATUS_SUCCESS       - Entry is created and ready to accept write data.
  SMP2P_STATUS_NOT_INIT      - Connection is opening. Client must call wait API
                               before writing data.
  SMP2P_STATUS_DUPLICATE     - Duplicate name found.
  SMP2P_STATUS_INVALID_PARAM - Invalid parameter.
  Other non-success status   - Error occurred.
  
  @return       Standard EFI error codes

  @dependencies
  None.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_CREATE)
(
  smp2p_context_type ** ctx,
  smem_host_type        dest,
  char *                name,
  uint32				*ret
);

/*===========================================================================
  FUNCTION  smp2p_write
===========================================================================*/
/**
  Writes data to the SMP2P entry and notifies remote endpoint. Entry location is
  determined by contents of context parameter.

  @param [in]   ctx       Pointer to SMP2P context.
  @param [in]   data      Data to be written.

  @param [out]  ret
  SMP2P_STATUS_SUCCESS       - Operation successful.
  SMP2P_STATUS_NOT_INIT      - Connection is opening and is not ready for data.
  SMP2P_STATUS_INVALID_PARAM - Invalid parameter.
  
  @return       Standard EFI error codes

  @dependencies
  Context must be initialized.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_WRITE)
(
  smp2p_context_type * ctx,
  uint32               data,
  uint32				*ret
);

/*===========================================================================
  FUNCTION  smp2p_modify
===========================================================================*/
/**
  Performs read-modify-write bits in the entry specified, then notifies remote
  endpoint.  Clear mask is applied before set mask.

  @param[in]  context   Pointer to SMP2P context.
  @param[in]  clr_mask  Bit mask to use when clearing bits.
  @param[in]  set_mask  Bit mask to use when setting bits.

  @param [out]  ret
  SMP2P_STATUS_SUCCESS       - Operation successful.
  SMP2P_STATUS_NOT_INIT      - Connection is opening and is not ready for data.
  SMP2P_STATUS_INVALID_PARAM - Invalid parameter.
  
  @return       Standard EFI error codes

  @dependencies
  Context must be initialized.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_MODIFY)
(
  smp2p_context_type * ctx,
  uint32               clr_mask,
  uint32               set_mask,
  uint32				*ret
);

/*===========================================================================
  FUNCTION  smp2p_modify_ex
===========================================================================*/
/**
  Performs read-modify-write bits in the entry specified, then notifies remote
  endpoint.  Clear mask is applied before set mask.

  @param[in]  context   Pointer to SMP2P context.
  @param[in]  clr_mask  Bit mask to use when clearing bits.
  @param[in]  set_mask  Bit mask to use when setting bits.
  @param[in]  flags     Flags parameter.
                        SMP2P_FLAGS_NO_INTR disables sending an interrupt 
                          following the SMP2P entry update.
                        SMP2P_FLAGS_NONE is normal behavior.

  @param [out]  ret
  SMP2P_STATUS_SUCCESS       - Operation successful.
  SMP2P_STATUS_NOT_INIT      - Connection is opening and is not ready for data.
  SMP2P_STATUS_INVALID_PARAM - Invalid parameter.
  
  @return       Standard EFI error codes

  @dependencies
  Context must be initialized.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_MODIFY_EX)
(
  smp2p_context_type * ctx,
  uint32               clr_mask,
  uint32               set_mask,
  uint32               flags,
  uint32				*ret
);

/*===========================================================================
  FUNCTION  smp2p_register
===========================================================================*/
/**
  Registers an OS event to be triggered when data arrives on the specified
  entry.

  If the specified entry is not yet created by the remote endpoint,
  SMP2P will save the params and trigger the specified OS event upon
  creation of the entry.

  If the specified entry is already created by the remote endpoint,
  SMP2P will trigger the event immediately to inform the client to call
  smp2p_read() to read the data there.

  Clients should call the wait API to wait for an event.

  @param [out]  ctx       Pointer to pointer of SMP2P context.
                          Context will be created and this pointer will be made
                          to point to it.
  @param [in]   source    Source processor ID.
  @param [in]   name      16 byte name string of the entry.

  @param [out]  ret
  SMP2P_STATUS_SUCCESS          - Operation successful.
  SMP2P_STATUS_NOT_FOUND        - Entry not found in Rx data.
                                  Client may call wait API to be notified when
                                  the Tx side to creates the entry.
  SMP2P_STATUS_INVALID_PARAM    - Invalid parameter.
  SMP2P_STATUS_DUPLICATE        - Duplicate name already present.
  SMP2P_STATUS_OUT_OF_RESOURCES - Out of room in pending list.
  
  @return       Standard EFI error codes

  @dependencies
  none.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_REGISTER)
(
  smp2p_context_type ** ctx,
  smem_host_type        source,
  char *                name,
  uint32				*ret
);

/*===========================================================================
  FUNCTION  smp2p_deregister
===========================================================================*/
/**
  Remove the RX context from smp2p_rx_active_list/ smp2p_rx_pending_list.

  @param [in]   ctx       Pointer to SMP2P context.

  @return
  SMP2P_STATUS_SUCCESS       - Operation successful.
  SMP2P_STATUS_INVALID_PARAM - Invalid parameter.

  @dependencies
  Context must be initialized.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_DEREGISTER)
(
  smp2p_context_type *ctx,
  uint32             *ret
);

/*===========================================================================
  FUNCTION  smp2p_read
===========================================================================*/
/**
  Reads data from an entry. Entry location is determined by contents of context
  parameter.

  Client should call this routine after SMP2P has triggered a receive event
  as registered by smp2p_register().

  Clients may call this routine at any time to read the current data value
  of the entry.

  @param [in]   ctx       Pointer to SMP2P context.
  @param [out]  data      Data read by SMP2P.

  @param [out]  ret
  SMP2P_STATUS_SUCCESS       - Operation successful.
  SMP2P_STATUS_NOT_INIT      - Connection is opening and is not ready for data.
  SMP2P_STATUS_INVALID_PARAM - Invalid parameter.
  
  @return       Standard EFI error codes

  @dependencies
  Context must be initialized.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_READ)
(
  smp2p_context_type * ctx,
  uint32 *             data,
  uint32				*ret
);

/*===========================================================================
  FUNCTION  smp2p_wait
===========================================================================*/
/**
  Calls OS specific wait function to wait for an event specified in the context.

  For a transmit/outbound context, the following scenarios may trigger an event:
    - A call to smp2p_create() returned status indicating that the
      connection must be negotiated.  SMP2P will trigger the event when
      the connection is open and ready to use.

  For a receive/inbound context, the following scenarios may trigger an event:
    - An entry has new data available to read.
    - A call to smp2p_register() has found the requested entry.
      Client should read the data value after this event since data may be
      updated.
    - A call to smp2p_register() returned status indicating that the entry
      is not found.  SMP2P will trigger the event when the Tx side notifies
      the local side that the entry is created.
      Client should read the data value after this event since data may be
      updated.

  This function will sleep (ie. not return) until the event triggers.

  @param [in]   ctx       Pointer to SMP2P context.

  @param [out]  ret
  SMP2P_STATUS_SUCCESS  - Entry is created and ready to accept write data.
  SMP2P_STATUS_FAILURE  - Error occurred.
  
  @return       Standard EFI error codes

  @dependencies
  Context must initialized by a call to SMP2P.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_WAIT)
(
  smp2p_context_type * ctx,
  uint32				*ret
);

/*===========================================================================
  FUNCTION  smp2p_wait_multiple
===========================================================================*/
/**
  Calls OS specific wait function to wait for an event specified in the context.
  This function waits for multiple events and returns when any one of them
  has been triggered.

  This function will sleep (ie. not return) until the event triggers.

  @param [in]   ctx_arr     Array of one or more pointers to SMP2P contexts
                            to wait on.
  @param [in]   ctx_count   Number of valid contexts in ctx array
  @param [out]  trigger_idx Index of context which was triggered

  @param [out]  ret
  SMP2P_STATUS_SUCCESS  - Entry is created and ready to accept write data.
  SMP2P_STATUS_FAILURE  - Error occurred.
  
  @return       Standard EFI error codes

  @dependencies
  Context must initialized by a call to SMP2P.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_SMP2P_WAIT_MULTIPLE)
(
  smp2p_context_type ** ctx_arr,
  uint32                ctx_count,
  uint32              * trigger_idx,
  uint32				*ret
);

typedef EFI_STATUS (EFIAPI* EFI_SMP2P_GET_EVT)
(
  smp2p_context_type*   ctx,
  Event**               Evt
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_smp2p_protocol
  @par Summary
  Smp2p Protocol interface.

  @par Parameters
  @inputprotoparams{smp2p_proto_params.tex}
*/
typedef struct _EFI_SMP2P_PROTOCOL {
  UINT64                              Revision;
  EFI_SMP2P_CREATE					  Smp2pCreate;
  EFI_SMP2P_WRITE					  Smp2pWrite;
  EFI_SMP2P_MODIFY					  Smp2pModify;
  EFI_SMP2P_MODIFY_EX				  Smp2pModifyEx;
  EFI_SMP2P_REGISTER				  Smp2pRegister;
  EFI_SMP2P_DEREGISTER				  Smp2pDeregister;
  EFI_SMP2P_READ					  Smp2pRead;
  EFI_SMP2P_WAIT					  Smp2pWait;
  EFI_SMP2P_WAIT_MULTIPLE			  Smp2pWaitMultiple;
  EFI_SMP2P_GET_EVT					  Smp2pGetEvt;
}EFI_SMP2P_PROTOCOL;

#endif /* __EFISMP2P_H__ */
