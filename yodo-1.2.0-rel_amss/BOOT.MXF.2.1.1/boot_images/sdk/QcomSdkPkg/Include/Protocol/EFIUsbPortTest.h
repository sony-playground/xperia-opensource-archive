/** @file EFIUsbPortTest.h
   
  QCOM_USB_PORT_TEST_PROTOCOL definition. 
  This protocol allows user interface to set up USB HW for host mode 
  electrical testing. 

**/
//============================================================================
/**
  Copyright (c) 2011-2012, 2017-2022 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================

/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 08/24/22   pw       Migrated from QcomPkg to QcomSdkPkg
 02/09/22   jj       Migrated from QcomTestPkg to QcomSdkPkg
 03/26/19   ak       Support for advancing TX SuperSpeed compliance test pattern
 02/13/17   gk       Port changes from boot.xf.2.0 and boot.xf.2.2
 09/04/17   gk	     UEFI USB compliance test changes
 01/04/12   wufan    Initial draft.
 04/30/12   wufan    Adding parameter get/set interface for port test.
 08/08/12   wufan    Add support of device mode signal quality testing.
 06/17/13   mliss    Added Identify function to support multiple instances
 
=============================================================================*/

#ifndef _EFI_USB_PORT_TEST_PRO_H_
#define _EFI_USB_PORT_TEST_PRO_H_

/** @defgroup QCOM_USB_PORT_TEST_PROTOCOL  QCOM_USB_PORT_TEST_PROTOCOL 
 *  @ingroup INTERFACES 
 */
 /** @defgroup  QCOM_USB_PORT_TEST_PROTOCOL_prot PROTOCOL
 *  @ingroup QCOM_USB_PORT_TEST_PROTOCOL 
 */ 
 /** @defgroup  QCOM_USB_PORT_TEST_PROTOCOL_apis APIs
 *  @ingroup QCOM_USB_PORT_TEST_PROTOCOL 
 */ 

/** @defgroup  QCOM_USB_PORT_TEST_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup QCOM_USB_PORT_TEST_PROTOCOL 
 */

///
/// Forward reference for pure ANSI compatibility.
///
typedef struct _QCOM_USB_PORT_TEST_PROTOCOL  QCOM_USB_PORT_TEST_PROTOCOL;

#define EFI_QCOM_USB_PORT_TEST_PROTOCOL_REVISION    EFI_QCOM_USB_PORT_TEST_PROTOCOL_REVISION_1
#define EFI_QCOM_USB_PORT_TEST_PROTOCOL_REVISION_1  0x0000000000010002

/** @ingroup QCOM_USB_PORT_TEST_PROTOCOL_data
  Enumeration for Port Test Mode.
**/
typedef enum {
  USB_PORT_TEST_DISABLE,
  USB_PORT_TEST_J_STATE,
  USB_PORT_TEST_K_STATE,
  USB_PORT_TEST_SE0_NAK,
  USB_PORT_TEST_PACKET,
  USB_PORT_TEST_FORCE_ENABLE,
  USB_PORT_TEST_ENABLE_SS_COMPLIANCE,
  USB_PORT_TEST_ADVANCE_COMP_PATTERN,
  USB_PORT_TEST_GET_DISCONNECT_STATUS,
  USB_PORT_TEST_DISABLE_PERIODIC,
  USB_PORT_TEST_ENABLE_PERIODIC,
  USB_PORT_TEST_MODE_MAX
} QCOM_USB_PORT_TEST_MODE;


/** @ingroup QCOM_USB_PORT_TEST_PROTOCOL_data
   Enumeration for Port Test Parameters.
 **/
typedef enum {

  USB_PORT_TEST_PARAM_QTD_INDEX,
  USB_PORT_TEST_PARAM_MAX

} QCOM_USB_PORT_TEST_PARAM;


/**@ingroup QCOM_USB_PORT_TEST_PROTOCOL_apis
  Run usb port test. Host mode procedures defined in EHCI spec 4.14.
   
  @param  TestMode   Test mode 
  @param  Data       [IN] *Data =1 means device mode. [OUT] Test results for some tests.

  @retval EFI_SUCCESS             Success.
  @retval EFI_INVALID_PARAMETER   Unsupported test mode or data is null 
                                  when output data is expected.
  @retval EFI_NOT_FOUND           Failed to locate USB config protocol

**/
typedef
EFI_STATUS
(EFIAPI *QCOM_USB_PORT_TEST_PROTOCOL_RUN_TEST) (
  IN  QCOM_USB_PORT_TEST_PROTOCOL     *This,
  IN  QCOM_USB_PORT_TEST_MODE         TestMode,
  IN  OUT UINTN                       *Data 
  );




/**@ingroup QCOM_USB_PORT_TEST_PROTOCOL_apis
  Set parameter used in Port Test.
   
  @param  ParamType   Parameter type 
  @param  ParamValue  Parameter value

  @retval EFI_SUCCESS             Success.
  @retval EFI_INVALID_PARAMETER   Parameter type not valid.

**/
typedef
EFI_STATUS
(EFIAPI *QCOM_USB_PORT_TEST_PROTOCOL_SET_PARAM) (
    IN  QCOM_USB_PORT_TEST_PROTOCOL     *This,            
    IN  QCOM_USB_PORT_TEST_PARAM         ParamType,
    IN  INTN                             ParamValue
  );



/**@ingroup QCOM_USB_PORT_TEST_PROTOCOL_apis
  Get parameter used in Port Test.
   
  @param  ParamType   Parameter type 
  @param  ParamValue  Parameter value

  @retval EFI_SUCCESS             Success.
  @retval EFI_INVALID_PARAMETER   Parameter type or pointer to value not valid.

**/
typedef
EFI_STATUS
(EFIAPI *QCOM_USB_PORT_TEST_PROTOCOL_GET_PARAM) (
    IN  QCOM_USB_PORT_TEST_PROTOCOL     *This,            
    IN  QCOM_USB_PORT_TEST_PARAM         ParamType,
    OUT INTN                            *ParamValue
  );



/** @ingroup QCOM_USB_PORT_TEST_PROTOCOL_apis
  Uniquely identify an instance of this protocol.

  @param This       Protocol instance pointer

  @return Identification string
**/
typedef
CHAR16 *
(EFIAPI *QCOM_USB_PORT_TEST_PROTOCOL_IDENTIFY) (
    IN  QCOM_USB_PORT_TEST_PROTOCOL     *This
  );


///
/// QCOM_USB_PORT_TEST_PROTOCOL
///
/**@ingroup QCOM_USB_PORT_TEST_PROTOCOL_prot
**/
struct _QCOM_USB_PORT_TEST_PROTOCOL {
  UINT64                                    Revision;
  QCOM_USB_PORT_TEST_PROTOCOL_RUN_TEST      RunPortTest;  
  QCOM_USB_PORT_TEST_PROTOCOL_GET_PARAM     GetParam;
  QCOM_USB_PORT_TEST_PROTOCOL_SET_PARAM     SetParam;
  QCOM_USB_PORT_TEST_PROTOCOL_IDENTIFY      Identify;
  INTN                                      QtdIndex;
};


extern EFI_GUID gQcomUsbPortTestProtocolGuid;

#endif




