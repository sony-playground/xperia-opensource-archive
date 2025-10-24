/**
  @file EnterpriseMgtLib.h
  @brief EnterpriseMgt library functions.
*/
/*=============================================================================
  Copyright (c) 2020-2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies Inc., Confidential and Proprietary.
=============================================================================*/
/*=============================================================================
 $Header:
                              EDIT HISTORY


 when          who     what, where, why
 ----------    ---    --------------------------------------------------------
 02/21/2020     hh    Initial version.
=============================================================================*/
#ifndef __ENTERPRISEMGTLIB_H__
#define __ENTERPRISEMGTLIB_H__

/*===========================================================================

                          Enumerations

===========================================================================*/
/**
*  Enum to represent features to disable from EnterpriseMgt HW registers.
**/
typedef enum _ENT_MGT_FEATURE_TYPE
{
    ENT_MGT_FRONT_CAMERA_1 = 0,
    ENT_MGT_FRONT_CAMERA_2 = 1,
    ENT_MGT_FRONT_CAMERA_3 = 2,
    ENT_MGT_REAR_CAMERA_1 = 3,
    ENT_MGT_REAR_CAMERA_2 = 4,
    ENT_MGT_REAR_CAMERA_3 = 5,
    ENT_MGT_USB_PORT_0_ALL = 6,
    ENT_MGT_USB_PORT_0_DATA = 7,
    ENT_MGT_USB_PORT_0_DISP = 8,
    ENT_MGT_USB_PORT_0_PCIE = 9,
    ENT_MGT_USB_PORT_1_ALL = 10,
    ENT_MGT_USB_PORT_1_DATA = 11,
    ENT_MGT_USB_PORT_1_DISP = 12,
    ENT_MGT_USB_PORT_1_PCIE = 13,
    ENT_MGT_KEYBOARD_1 = 14,
    ENT_MGT_SD_CARD_1 = 15,
    ENT_MGT_SD_CARD_2 = 16,
    ENT_MGT_WWAN_1 = 17,
    ENT_MGT_WIFI_1 = 18,
    ENT_MGT_BLUETOOTH_1 = 19,
    ENT_MGT_BLUETOOTH_2 = 20,
    ENT_MGT_AUDIO_1 = 21,
    ENT_MGT_NFC_1 = 22,
    ENT_MGT_DISPLAY_1 = 23,
    ENT_MGT_DISPLAY_2 = 24,
    ENT_MGT_SURFACE_CONNECT_DATA_1 = 25,
    ENT_MGT_SURFACE_CONNECT_DISP_1 = 26,
    ENT_MGT_USB_PORT_0_PD = 27,
    ENT_MGT_USB_PORT_1_PD = 28,
    ENT_MGT_DIGITAL_MICS_ALL = 29,
    ENT_MGT_DIGITAL_MIC_1 = 30,
    ENT_MGT_DIGITAL_MIC_2 = 31,
    ENT_MGT_DIGITAL_MIC_3 = 32,
    ENT_MGT_DIGITAL_MIC_4 = 33,
    ENT_MGT_TRACKPAD = 34,
    ENT_MGT_FINGERPRINT = 35,
    ENT_MGT_AUDIO_INT_MICS_ALL = 36,
    ENT_MGT_HUMAN_PRESENCE_SENSOR_0 = 37,
    ENT_MGT_USB_PORT_0_USB4 = 38,
    ENT_MGT_USB_PORT_1_USB4 = 39,
    ENT_MGT_BIOMETRIC_CAMERA_0 = 40,
    ENT_MGT_BIOMETRIC_CAMERA_1 = 41,
    ENT_MGT_USB_PORT_2_ALL = 42,
    ENT_MGT_USB_PORT_2_DATA = 43,
    ENT_MGT_USB_PORT_2_DISP = 44,
    ENT_MGT_USB_PORT_2_PCIE = 45,
    ENT_MGT_USB_PORT_2_PD = 46,
    ENT_MGT_USB_PORT_2_USB4 = 47,
    ENT_MGT_USB_PORT_0_CHG = 48,
    ENT_MGT_USB_PORT_1_CHG = 49,
    ENT_MGT_USB_PORT_2_CHG = 50,
    ENT_MGT_USB_PORT_0_TC = 51,
    ENT_MGT_USB_PORT_1_TC = 52,
    ENT_MGT_USB_PORT_2_TC = 53,
    ENT_MGT_MAX_FEATURES
}ENT_MGT_FEATURE_TYPE;

/*===========================================================================

                        Public Functions

===========================================================================*/

/**
  Enterprise Management function to store client policies into UEFI NV variable. These policies 
  are used to disable hardware features in enterprise management registers by EnterpriseMgt dxe.

  @param[in] NumFeatures  Number of features to disable.
  @param[in] pFeatureList Array pointing to the features to disable.

  @retval EFI_SUCCESS            Successfully processed requested client policies.
  @retval EFI_INVALID_PARAMETER  Invalid arguments.
  @retval EFI_OUT_OF_RESOURCES   Memory allocation failed for internal usage.
  @retval EFI_DEVICE_ERROR       Internal error while processing requested client policies.
  @retval SetVariable() or FlushVariableServices() returned error code.

**/
EFI_STATUS 
EFIAPI 
EnterpriseMgtSetFeaturesToDisable (
    IN UINT16 NumFeatures, 
    IN ENT_MGT_FEATURE_TYPE *pFeatureList
    );

#endif /*__ENTERPRISEMGTLIB_H__*/