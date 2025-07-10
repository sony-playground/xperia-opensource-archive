/** 
@file  EFIPmicQbg.h
@brief PMIC QBG for UEFI.
*/
/*=============================================================================
Copyright (c) 2020 Qualcomm Technologies, Inc.
All rights reserved.
Qualcomm Technologies Inc Confidential and Proprietary.
    
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------

02/21/20   xp      Initial draft

=============================================================================*/

#ifndef __EFIPMICQBG_H__
#define __EFIPMICQBG_H__


/*===========================================================================

                        MACRO DECLARATIONS

===========================================================================*/
/** @addtogroup efi_pmicQbg_constants 
@{ */
/**
Protocol version.
*/

#define PMIC_QBG_REVISION 0x0000000000010001
/** @} */ /* end_addtogroup efi_pmicQbg_constants */

/*  Protocol GUID definition */
/** @ingroup efi_pmicQbg_protocol */
#define EFI_PMIC_QBG_PROTOCOL_GUID \
    { 0xd0d11d84, 0xa0ee, 0x43fa, { 0xa9, 0x26, 0xe3, 0xc7, 0x6c, 0xfe, 0xf6, 0x1d } }


/** @cond */
/*===========================================================================

                        EXTERNAL VARIABLES

===========================================================================*/
/**
External reference to the PMIC QBG Protocol GUID.
*/
extern EFI_GUID gQcomPmicQbgProtocolGuid;


typedef struct _EFI_PM_QBG_BATT_STATUS_INFO
{
  UINT32 StateOfCharge;
  INT32  ChargeCurrent;
  INT32  BatteryVoltage;
  INT32  BatteryTemperature;
}EFI_PM_QBG_BATT_STATUS_INFO;

typedef struct
{
  UINT64 BattId;
}EFI_PM_QBG_BATTERY_ID;

typedef struct
{
  UINT32 PmicIndex;
  UINT32 SlaveIndex;
} EFI_PM_QBG_PMIC_INFO;


/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/
/* EFI_PMIC_QBG_INIT */
/** @ingroup efi_pmicQbgInit
  @par Summary
  Initializes QBG Module

  @param[in] PmicDeviceIndex: Pmic Device Index (0 for primary)

 @return 
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
  EFI_NOT_READY         -- Physical device is busy or not ready to
                           process this request.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_QBG_INIT)(
  IN UINT32                      PmicDeviceIndex
);

/* EFI_PMIC_QBG_EXIT */
/** @ingroup efi_pmicQbgExit
  @par Summary
  Exit QBG Module

  @param[in] PmicDeviceIndex: Pmic Device Index (0 for primary)

 @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
  EFI_NOT_READY         -- Physical device is busy or not ready to
                           process this request.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_QBG_EXIT)( 
  IN UINT32 PmicDeviceIndex
);


/* EFI_PMIC_QBG_DUMP_PERIPHERAL */
/** @ingroup efi_pmicQbgDumpPeripheral
  @par Summary
    Dumps QBG Pheripherals

  @param: Void

 @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
  EFI_NOT_READY         -- Physical device is busy or not ready to
                           process this request.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_QBG_DUMP_PERIPHERAL )(
  VOID
);


/* EFI_PMIC_QBG_GET_BATTERY_STATUS */
/** @ingroup efi_pmicQbgGetBatteryStsInfo
  @par Summary
  Get Battery Status Information

  @param[in]  PmicDeviceIndex    : Pmic Device Index (0 for primary)
  @param[out] pBattStsInfo      :  Battery status info

 @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
  EFI_NOT_READY         -- Physical device is busy or not ready to
                           process this request.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_QBG_GET_BATTERY_STATUS)(
  IN  UINT32          PmicDeviceIndex,
  OUT EFI_PM_QBG_BATT_STATUS_INFO *pBattStsInfo
);



/* EFI_PMIC_QBG_GET_BATT_ID */
/** @ingroup efi_pmicQbgGetBatteryId
  @par Summary
  Get battery id

  @param[out] BattId           : Battery id

 @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
  EFI_NOT_READY         -- Physical device is busy or not ready to
                           process this request.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_QBG_GET_BATTERY_ID)(
  OUT EFI_PM_QBG_BATTERY_ID *BatteryId
);


/* EFI_PMIC_QBG_GET_PMIC_INFO */
/** @ingroup efi_pmicQbgInit
  @par Summary
  Provides PMIC Index for QBG Module

  @param[out] QbgPmicInfo   Pmic Device Index (0 for primary)

 @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_QBG_GET_PMIC_INFO)(
  OUT EFI_PM_QBG_PMIC_INFO *QbgPmicInfo
);

/* EFI_PMIC_QBG_IS_BATTERY_PRESENT */
/** @ingroup efi_pmicQbgInit
  @par Summary
  Provides PMIC Index for QBG Module

  @param[out] BOOLEAN IF BATTERY IS MISSING

 @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- Parameter is invalid. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_QBG_IS_BATTERY_PRESENT)(
  IN UINT32 PmicDeviceIndex,
  OUT BOOLEAN *battery_present
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_pmicQbg_protocol
  @par Summary
  Qualcomm PMIC Battery Monitoring System (QBG) Protocol interface.

  @par Parameters
  @inputprotoparams{pmic_qbg_proto_params.tex} 
*/
struct _EFI_QCOM_PMIC_QBG_PROTOCOL
{
  UINT64                            Revision;
  EFI_PMIC_QBG_GET_PMIC_INFO        GetPmicInfo;
  EFI_PMIC_QBG_INIT                 Init;
  EFI_PMIC_QBG_EXIT                 Exit;
  EFI_PMIC_QBG_DUMP_PERIPHERAL      DumpPeripheral;
  EFI_PMIC_QBG_GET_BATTERY_STATUS   GetBatteryStatus;
  EFI_PMIC_QBG_GET_BATTERY_ID       GetBatteryId;
  EFI_PMIC_QBG_IS_BATTERY_PRESENT   IsBatteryPresent;
};

typedef struct _EFI_QCOM_PMIC_QBG_PROTOCOL EFI_QCOM_PMIC_QBG_PROTOCOL;

#endif /* __EFIPMICQBG_H__ */

