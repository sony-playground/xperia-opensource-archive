/** @file  
                    EFIMeasureBoot.h

 
  Copyright (c) 2012-2017, 2020, 2022 Copyright Qualcomm Technologies, Inc.
  All Rights Reserved.

**/

/*=============================================================================
                              EDIT HISTORY
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.



 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 06/22/20   shl      Reorg, removed unnecessary API expose.
 06/13/17   pr       Changes to fix PCR4 measurment issue
 12/03/14   sk       Added to change library to driver
 08/22/13   shl      Added offline crash dump interface
 12/10/12   shl      Warning fix 
 07/17/12   shl      Add back two interfaces
 05/15/12   shl      Added support for OEM FW update authentication 
 03/23/12   shl      Added functions for store acpi before and after fixup
 11/28/11   shl      Moved SetExitBootServicesRegSignal() to SecurityDxe
 08/18/11   shl      Initial version

=============================================================================*/

/** @cond */
typedef struct _EFI_QCOM_MEASUREBOOT_PROTOCOL EFI_QCOM_MEASUREBOOT_PROTOCOL;
/** @endcond */

/* External reference to the gQcomMeasureBootProtocolGuid GUID */
/** @cond */
extern EFI_GUID gQcomMeasureBootProtocolGuid;
/** @endcond */

/** @ingroup efi_scm_constants
  Protocol version.
*/
#define QCOM_MEASURE_BOOT_PROTOCOL_REVISION 0x0000000000020001

/*===========================================================================
  FUNCTION DECLARATIONS
===========================================================================*/

/* EFI_MEASUREBOOT_INIT_CERTBUFFER_FORMEASURE */ 
/** @ingroup efi_measureboot_init_certbuffer_formeasure
  @par Summary
    
  @param[in]  This   Pointer to EFI_QCOM_MEASUREBOOT_PROTOCOL instance.

  @return
  EFI_SUCCESS        Function completed successfully. \n
  Others             Other error. \n
*/
typedef VOID (EFIAPI *EFI_MEASUREBOOT_INIT_CERTBUFFER_FORMEASURE)( IN EFI_QCOM_MEASUREBOOT_PROTOCOL *This);


/* EFI_MEASUREBOOT_STORE_CERTBUFFER_FORMEASURE */ 
/** @ingroup efi_measureboot_store_certbuffer_formeasure
  @par Summary
    
  @param[in]  This   Pointer to EFI_QCOM_MEASUREBOOT_PROTOCOL instance.

  @return
  EFI_SUCCESS        Function completed successfully. \n
  Others             Other error. \n
*/
typedef VOID (EFIAPI *EFI_MEASUREBOOT_STORE_CERTBUFFER_FORMEASURE)( IN EFI_QCOM_MEASUREBOOT_PROTOCOL *This, 
                                                                    UINT8                            *Cert, 
                                                                    UINT32                            CertSize,
                                                                    EFI_GUID                         *OwnerGuid );


/* EFI_MEASUREBOOT_MEASURE_CERTINBUFFER */ 
/** @ingroup efi_measureboot_measure_certbuffer
  @par Summary
    
  @param[in]  This   Pointer to EFI_QCOM_MEASUREBOOT_PROTOCOL instance.

  @return
  EFI_SUCCESS        Function completed successfully. \n
  Others             Other error. \n
*/
typedef EFI_STATUS (EFIAPI *EFI_MEASUREBOOT_MEASURE_CERTINBUFFER)( IN EFI_QCOM_MEASUREBOOT_PROTOCOL *This );


/** @ingroup efi_measureboot_measure_peimageall
  @par Summary
    
  @param[in]     This                   Pointer to EFI_QCOM_MEASUREBOOT_PROTOCOL instance.
  @param[in]     AuthenticationStatus   Authenticate status
  @param[in]     DevicePath             File path
  @param[in]     FileBuffer             File buffer size
  @param[in]     FileSize               File size
  
  @return
  EFI_SUCCESS        Function completed successfully. \n
  Others             Other error. \n
*/
typedef EFI_STATUS (EFIAPI *EFI_MEASUREBOOT_MEASURE_PEIMAGEALL)( EFI_QCOM_MEASUREBOOT_PROTOCOL  *This, 
                                                                 UINT32                          AuthenticationStatus, 
                                                                 CONST EFI_DEVICE_PATH_PROTOCOL *DevicePath, 
                                                                 VOID                           *FileBuffer, 
                                                                 UINTN                           FileSize );


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_measureboot_protocol
  @par Summary
  Contains modules to measure various data and code. 

  @par Parameters
  @inputprotoparams{measureboot_proto_params.tex} 
*/
struct _EFI_QCOM_MEASUREBOOT_PROTOCOL
{
  EFI_MEASUREBOOT_INIT_CERTBUFFER_FORMEASURE    InitCertBufferForMeasure;
  EFI_MEASUREBOOT_STORE_CERTBUFFER_FORMEASURE   StoreCertBufferForMeasure;
  EFI_MEASUREBOOT_MEASURE_CERTINBUFFER          MeasureCertInBuffer;
  EFI_MEASUREBOOT_MEASURE_PEIMAGEALL            MeasurePeImgAll;
}; 

