/** @file XhciPortTest.h

  QCOM_USB_PORT_TEST_PROTOCOL driver.

  Copyright (c) 2011 - 2022, QUALCOMM Technologies Inc. All rights reserved.

**/
/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/09/22   jj      Migrated from QcomTestPkg to QcomSdkPkg

=============================================================================*/
#ifndef _EFI_XHCI_PORT_TEST_H_
#define _EFI_XHCI_PORT_TEST_H_


#include <Protocol/EFIUsbPortTest.h>


#define USB_PORT_TEST_VAR_UNDEFINED     -1


/**
  The global UsbPortTest protocol instance for Xhci driver.
**/
extern QCOM_USB_PORT_TEST_PROTOCOL gXhciUsbPortTestTemplate;


#endif
