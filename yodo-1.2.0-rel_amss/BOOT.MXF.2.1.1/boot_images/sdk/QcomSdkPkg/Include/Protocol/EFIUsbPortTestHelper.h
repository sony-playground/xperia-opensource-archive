/** @file UsbPortTestHelper.h
   
  QCOM_USB_PORT_TEST_HELPER_PROTOCOL definition. 
  This protocol helps HS USB host mode electrical testing at transfer level. 

  Copyright (c) 2010 - 2022, Qualcomm Technologies,, Inc. All rights reserved.

**/


/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 08/24/22   pw       Migrated from Qcompkg to QcomSdkPkg
 02/09/22   jj       Migrated from QcomTestPkg to QcomSdkPkg
 04/20/21   sriramd  Updatd to support the info from connected devices
 12/08/11   wufan    Initial draft.
 
=============================================================================*/

#ifndef _USB_PORT_TEST_HELPER_PRO_H_
#define _USB_PORT_TEST_HELPER_PRO_H_
#include <Protocol/EFIUsbIo.h>     /* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */ 

/** @defgroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL  QCOM_USB_PORT_TEST_HELPER_PROTOCOL 
 *  @ingroup INTERFACES 
 */
 /** @defgroup  QCOM_USB_PORT_TEST_HELPER_PROTOCOL_prot PROTOCOL
 *  @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL 
 */ 
 /** @defgroup  QCOM_USB_PORT_TEST_HELPER_PROTOCOL_apis APIs
 *  @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL 
 */ 

/** @defgroup  QCOM_USB_PORT_TEST_HELPER_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL 
 */


///
/// Forward reference for pure ANSI compatibility.
///
typedef struct _QCOM_USB_PORT_TEST_HELPER_PROTOCOL QCOM_USB_PORT_TEST_HELPER_PROTOCOL;

#define EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION    EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2
#define EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_1  0x0000000000010002
#define EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2  0x0000000000020000


/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
#define MAX_CHILD_DEVICES							20
#define	STRING_DESC_DATA_MAX							100
#define	MAX_STRING_DESC_DATA							2000

/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
///
/// QCOM_USB_PORT_TEST_GET_CHILD_DATA
///
/** @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL_data
**/
typedef struct _QCOM_USB_PORT_TEST_GET_CHILD_DATA {
  UINT32                                               TotalChildCount;
  UINT32                                               VidPid[MAX_CHILD_DEVICES];
  UINT32                                               DataSize[MAX_CHILD_DEVICES];
  CHAR8                                                Data[MAX_STRING_DESC_DATA];
}QCOM_USB_PORT_TEST_GET_CHILD_DATA;

/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
#define USB_STR_DESC_SIZE (4)

/** @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL_data
**/
typedef struct {
  UINT32 Addr;
  UINT32 Speed;
  UINT32 Pid;
  UINT32 Vid;
  UINT32 Parent;
  EFI_USB_STRING_DESCRIPTOR* StrDesc[USB_STR_DESC_SIZE];
}QUSB_USB_PORT_TEST_HELPER_LIST_DEVICE_TYPE;


/** @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL_apis
  Get the device number that of the first device connected to the root hub, 
  and the parent port number for the device. 
  There should be only one device connected to the root hub for USB 
  host mode electrical testing. 
   
  @param DeviceNumber     Device number
  @param PortNumber       Port number in root hub. 

  @retval EFI_SUCCESS        Success
  @retval EFI_DEVICE_ERROR   Unsupported TestMode. 
  @retval EFI_NOT_FOUND      no USB Bus protocol instance is found

**/
typedef
EFI_STATUS
(EFIAPI *QCOM_USB_PORT_TEST_HELPER_PROTOCOL_GET_DEV_INFO) (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL  *This,
  OUT UINT8                               *DeviceNumber, 
  OUT UINT8                               *PortNumber
  );


/** @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL_apis
  Trigger a control transfer to get device descriptor. 
  Used in Host Control Packet Parameters testing. 

  @retval EFI_SUCCESS             Success
  @retval EFI_DEVICE_ERROR        Failed to trigger the transfer. 
  @retval EFI_INVALID_PARAMETER   Can't convert This to USB_BUS.  
  @retval EFI_NOT_FOUND           no USB Bus protocol instance is found

**/
typedef
EFI_STATUS
(EFIAPI *QCOM_USB_PORT_TEST_HELPER_PROTOCOL_GET_DEV_DESC) (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL        *This 
  );

/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
/** @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL_apis
  Iterate through the USBBus and list all devices connected to the bus.
  @GetChildData                   Store the connected devices data
  @retval EFI_SUCCESS             Success
  @retval EFI_INVALID_PARAMETER   Can't convert This to USB_BUS.
  @retval EFI_DEVICE_ERROR        Unsupported TestMode.
**/
typedef
EFI_STATUS
(EFIAPI *QCOM_USB_PORT_TEST_HELPER_PROTOCOL_FIND_DEVICE) (
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL  *This,
  OUT QCOM_USB_PORT_TEST_GET_CHILD_DATA   *GetChildData
  );

/* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
/** @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL_apis
**/
typedef
EFI_STATUS
(EFIAPI *QCOM_USB_PORT_TEST_HELPER_PROTOCL_GET_DEV_LIST)(
  IN  QCOM_USB_PORT_TEST_HELPER_PROTOCOL  *This,
  OUT QUSB_USB_PORT_TEST_HELPER_LIST_DEVICE_TYPE **UsbDeviceList,
  OUT UINT32                               *NumDevice
  );

#define QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION  0x00010002

///
/// QCOM_USB_PORT_TEST_HELPER_PROTOCOL
///
/** @ingroup QCOM_USB_PORT_TEST_HELPER_PROTOCOL_prot
**/
struct _QCOM_USB_PORT_TEST_HELPER_PROTOCOL {
  UINT64                                               Revision;
  QCOM_USB_PORT_TEST_HELPER_PROTOCOL_GET_DEV_INFO      GetDeviceInfo;  
  QCOM_USB_PORT_TEST_HELPER_PROTOCOL_GET_DEV_DESC      GetDeviceDescriptor;
  QCOM_USB_PORT_TEST_HELPER_PROTOCOL_FIND_DEVICE       FindDevice;          /* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
  QCOM_USB_PORT_TEST_HELPER_PROTOCL_GET_DEV_LIST       GetDeviceList;       /* Added in EFI_QCOM_USB_PORT_TEST_HELPER_PROTOCOL_REVISION_2 */
};

extern EFI_GUID gQcomUsbPortTestHelperProtocolGuid;

#endif


