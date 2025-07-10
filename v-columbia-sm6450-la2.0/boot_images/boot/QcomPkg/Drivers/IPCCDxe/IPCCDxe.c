/** @file IPCCkDxe.c

 *This file implements IPCC EFI protocol interface. Copyright  
 *(c) 2020 Qualcomm Technologies, Inc. All rights  
 *reserved.  

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 04/15/20   cpaulo  Initial release.

=============================================================================*/


/*=========================================================================
      Include Files
==========================================================================*/

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIIPCC.h>
#include <Library/QcomTargetLib.h>
#include <Library/QcomLib.h>
#include "IPCC.h"

/*=========================================================================
      Type Definitions
==========================================================================*/


/*=========================================================================
      Function Prototypes
==========================================================================*/

extern void IPCC_Init(void);

EFIIPCCErr IPCCDxe_Attach(EFIIPCC_Handle   *pH, EFIIPCC_Protocol eProtocol);

EFIIPCCErr IPCCDxe_Detach(EFIIPCC_Handle *pH);

EFIIPCCErr IPCCDxe_RegisterInterrupt( EFIIPCC_Handle       h, 
                                      EFIIPCC_Client       eSenderCID, 
                                      EFIIPCC_Signal       nSignalLow, 
                                      EFIIPCC_Signal       nSignalHigh,
                                      EFIIPCC_CB           pfnCB, 
                                      EFIIPCC_CBData       nData );


EFIIPCCErr IPCCDxe_DeregisterInterrupt( EFIIPCC_Handle       h, 
                                        EFIIPCC_Client       eSenderCID, 
                                        EFIIPCC_Signal       nSignalLow, 
                                        EFIIPCC_Signal       nSignalHigh );

EFIIPCCErr IPCCDxe_Trigger( EFIIPCC_Handle       h, 
                            EFIIPCC_Client       eTargetCID, 
                            EFIIPCC_Signal       nSignalLow, 
                            EFIIPCC_Signal       nSignalHigh );


/*=========================================================================
      Data Declarations
==========================================================================*/

// IPCC Public Protocol
static EFI_IPCC_PROTOCOL IPCCProtocol =
{
  EFI_IPCC_PROTOCOL_VERSION,
  IPCCDxe_Attach,
  IPCCDxe_Detach,
  IPCCDxe_RegisterInterrupt,
  IPCCDxe_DeregisterInterrupt,
  IPCCDxe_Trigger
};


/*=========================================================================
      Functions
==========================================================================*/


/**
  Attaches given handle to IPCC driver and protocol.

  This function takes a reference to a user handle and protocol enumeration.
  This function must be called before calling any other IPCC API in order to
  notify the IPCC driver of the requirement to use the protocol requested.  

  @param pH        [out] Reference to a client handle.
  @param eProtocol [in]  IPCC protocol requested to use.

  @return
  IPCC_EOK -- Successfully attached to protocol eProtocol. \n
  IPCC_EGENERR -- IPCC not yet initialized. \n
  IPCC_EMEM -- Insufficient memory available for client handle reference. \n
  IPCC_ENOTSUPPORTED -- Protocol requested is not supported. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Driver must be initialized.
*/

EFIIPCCErr 
IPCCDxe_Attach
(
  EFIIPCC_Handle   *pH, 
  EFIIPCC_Protocol eProtocol
)
{
  return (EFIIPCCErr)IPCC_Attach((IPCC_Handle)pH, (IPCC_Protocol)eProtocol);
}

/**
  Detaches the given handle from IPCC driver.

  This function takes a reference to a user handle and detaches it from the
  driver.  It should only be used if there is no requirement for this handle
  at the point it's called.  

  @param pH        [out] Reference to a client handle.

  @return
  IPCC_EOK -- Successfully detached client handle. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

EFIIPCCErr 
IPCCDxe_Detach
(
  EFIIPCC_Handle *pH
)
{
  return (EFIIPCCErr)IPCC_Detach((IPCC_Handle)pH);
}

/**
  Registers a callback function for when signals are received from a given
  sender.

  This function is used to register a notification with the IPCC driver.
  The callback function pfnCB is called whenever the sender eSenderCID
  signals the processor running this SW with any of the signals in the
  range nSignalLow to nSignalHigh.  If only one signal is being registered,
  then nSignalLow should be the same as nSignalHigh.  If any of the signals
  are in use, then the API will fail and none of the requested signals will
  be registered.

  @param h           [in] Client handle.
  @param eSenderCID  [in] Client ID of the sender.
  @param nSignalLow  [in] Lowest signal number to listen on.
  @param nSignalHigh [in] Highest signal number to listen on.
  @param pfnCB       [in] Callback function for when signal is received.
  @param nData       [in] Data to pass into callback function when signal
                          is received.

  @return
  IPCC_EOK -- Successfully registered the signals for eSenderCID. \n
  IPCC_EARG -- Unsupported argument passed in by client. \n
  IPCC_EINUSE -- One or more of the requested signals are in use.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

EFIIPCCErr 
IPCCDxe_RegisterInterrupt
( 
  EFIIPCC_Handle       h, 
  EFIIPCC_Client       eSenderCID, 
  EFIIPCC_Signal       nSignalLow, 
  EFIIPCC_Signal       nSignalHigh,
  EFIIPCC_CB           pfnCB, 
  EFIIPCC_CBData       nData 
)
{
  return (EFIIPCCErr)IPCC_RegisterInterrupt((IPCC_Handle)h, 
                                            (IPCC_Client)eSenderCID, 
                                            (IPCC_Signal)nSignalLow, 
                                            (IPCC_Signal)nSignalHigh, 
                                            (IPCC_CB)pfnCB, 
                                            (IPCC_CBData)nData);
}

/**
  Deregisters a previously registered callback function for signals
  received from a given sender.

  This function is used to deregister a notification from the IPCC driver.
  This will remove all future notificatoins of the previously registered
  callback function from happening.  If only one signal is being deregistered,
  then nSignalLow should be the same as nSignalHigh.  If any of the signals
  are not in use, then the API will fail and none of the requested signals will
  be deregistered.

  @param h           [in] Client handle.
  @param eSenderCID  [in] Client ID of the sender.
  @param nSignalLow  [in] Lowest signal number to deregister.
  @param nSignalHigh [in] Highest signal number to deregister.

  @return
  IPCC_EOK -- Successfully deregistered the signals for eSenderCID. \n
  IPCC_EARG -- Unsupported argument passed in by client. \n
  IPCC_EUNUSED -- One or more of the requested signals are not in use.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

EFIIPCCErr 
IPCCDxe_DeregisterInterrupt
( 
  EFIIPCC_Handle       h, 
  EFIIPCC_Client       eSenderCID, 
  EFIIPCC_Signal       nSignalLow, 
  EFIIPCC_Signal       nSignalHigh 
)
{
  return (EFIIPCCErr)IPCC_DeregisterInterrupt((IPCC_Handle)h, 
                                              (IPCC_Client)eSenderCID, 
                                              (IPCC_Signal)nSignalLow, 
                                              (IPCC_Signal)nSignalHigh);
}

/**
  Triggers interrupts on remote clients.

  This function is used to assert the signals in the range nSignalLow to
  nSignalHigh on target eTargetCID.  

  @param h           [in] Client handle.
  @param eTargetCID  [in] Client ID of the target.
  @param nSignalLow  [in] Lowest signal number to assert.
  @param nSignalHigh [in] Highest signal number to assert.

  @return
  IPCC_EOK -- Successfully trigger the signals to eTargetCID. \n
  IPCC_EARG -- Unsupported argument passed in by client.

  @dependencies
  Handle must be valid, and driver must be initialized.
*/

EFIIPCCErr 
IPCCDxe_Trigger
( 
  EFIIPCC_Handle       h, 
  EFIIPCC_Client       eTargetCID, 
  EFIIPCC_Signal       nSignalLow, 
  EFIIPCC_Signal       nSignalHigh 
)
{
  return (EFIIPCCErr)IPCC_Trigger((IPCC_Handle)h, 
                                  (IPCC_Client)eTargetCID, 
                                  (IPCC_Signal)nSignalLow, 
                                  (IPCC_Signal)nSignalHigh);
}

/**
  IPCC DXE driver entry point.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
IPCCDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_HANDLE  handle = NULL;
  EFI_STATUS  status;

  IPCC_Init();

  // Publish the DALSYS Protocol
  status = gBS->InstallMultipleProtocolInterfaces(
             &handle,
             &gEfiIpccProtocolGuid,
             (void **)&IPCCProtocol,
             NULL );

  return status;
}

