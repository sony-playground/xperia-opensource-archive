/**
  @file EFIStorageDeviceManagement.h
  @brief Storage Device Management protocol definitions.
*/
/*=============================================================================
  Copyright (c) 2020, 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---     -----------------------------------------------------------
 03/02/22    sa      Added SharedIce Protocol.
 03/21/22    cm      Get information if turbo mode is supported
 02/25/22    jt      Add Level Shifter changes
 03/31/20    sa      Initial version.
 
=============================================================================*/
#ifndef __EFI_STORAGE_DEVICEMANAGEMENT_H__
#define __EFI_STORAGE_DEVICEMANAGEMENT_H__

/** @defgroup EFI_STORAGE_DEV_MGMT_PROTOCOL  EFI_STORAGE_DEV_MGMT_PROTOCOL 
 *  @ingroup PERIPHERALS 
 */
 /** @defgroup  EFI_STORAGE_DEV_MGMT_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL 
 */ 
 /** @defgroup  EFI_STORAGE_DEV_MGMT_PROTOCOL_apis APIs
 *  @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL 
 */ 

/** @defgroup  EFI_STORAGE_DEV_MGMT_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL 
 */

/** @cond */
typedef struct _EFI_STORAGE_DEV_MGMT_PROTOCOL   EFI_STORAGE_DEV_MGMT_PROTOCOL;
/** @endcond */
  
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
    Protocol version.
*/
#define EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION4     0x0000000000040000
#define EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION3     0x0000000000030000
#define EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION2     0x0000000000020000
#define EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION      EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION4


/* Protocol GUID definition */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data */
#define EFI_STORAGE_DEV_MGMT_PROTOCOL_GUID \
	{0x5bf0e02f, 0xb362, 0x4ea9, { 0x8b, 0x2f, 0xe6, 0x8d, 0xf2, 0x50, 0x0f, 0x40 } }

/** @cond */
/* External reference to the Device Management GUID */
extern EFI_GUID gEfiStorageDevMgmtProtocolGuid;
/** @endcond */

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Storage voltage corners
*/
typedef enum {
   VOLT_CORNER_MINSVS = 1, 
   VOLT_CORNER_LOWSVS = 2, 
   VOLT_CORNER_SVS = 3, 
   VOLT_CORNER_NOM = 4, 
   VOLT_CORNER_TURBO = 5,
   VOLT_CORNER_MAX = 5
} EFI_STORAGE_VOLT_CORNER;

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Information about speed levels and voltage corner capabilities
*/
typedef struct {
   UINT8 NumSpeedLevels; 
   /**< Number of different speed levels supported (higher number indicates better performance) */
   UINT8 VoltCornerSupported[VOLT_CORNER_MAX]; 
   /**< For each voltage corner listed above, 1 = supported, 0 = unsupported */
} EFI_STORAGE_OP_MODE_CAPABILITIES;

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Information about current operational mode
*/
typedef struct {
   UINT8 CurrentSpeedLevel; 
   /**< Current operating speed */
   UINT8 CurrentVoltCorner; 
   /**< Current operating voltage corner */
   UINT8 LinkState; 
   /**< 1 = Link active, 0 = Link in sleep */
} EFI_STORAGE_OP_MODE_INFO;

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Information about configurable parameters of the link
*/
typedef union { 
   UINT16 IdleTimeMs; 
   /**< Link will automatically go to sleep after this much idle time (ms)  */
} EFI_STORAGE_LINK_PARAMS;

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Storage link states
*/
typedef enum {
   LINK_SLEEP = 0, 
   LINK_ACTIVE = 1
} EFI_STORAGE_LINK_STATE;

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  UFS specific error statistics
*/
typedef struct {
   UINT32 TotalFailureCnt; 
   /**< Total number of failures since init */
   UINT32 PAIndErrCnt[5];           
   /**< Individual PA error counts for bits [4:0] in UECPA */
   UINT32 PATotalErrCnt; 
   /**< Total number of PA errors */
   UINT32 DLIndErrCnt[16]; 
   /**< Individual DL error counts for bits [15:0] in UECDL */
   UINT32 DLTotalErrCnt; 
   /**< Total number of DL errors */
   UINT32 DMETotalErrCnt; 
   /**< Total number of DME errors */
} EFI_UFS_ERR_STATS;

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Statistics about storage errors
*/
typedef union {
   EFI_UFS_ERR_STATS    UFSErrorStats; 
} EFI_STORAGE_ERR_STATS;

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Storage Device Information
*/
typedef struct {
   UINT32 SpecVersion; 
   /**< Specification version of the storage device */
   CHAR8  *VendorId; 
   /**< Name of the device vendor */
   CHAR8  *ProductId; 
   /**< Product Name of the device */
   CHAR8  *FirmwareRevision;
   /**< Firmware Revision of the device */
   CHAR8  *SerialNumber;  
   /**< Serial Number of the device */
} EFI_STORAGE_DEV_INFO; 

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Storage Level Shifter Information
*/
typedef struct {
   BOOLEAN LevelShifterPresent; 
   /**< SD card only; indicates whether Level Shifter is being used */
} EFI_STORAGE_LS_INFO; /* Added in EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION2 */

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Storage Turbo Mode enablement Information, added for Revision 3
*/
typedef struct {
   BOOLEAN DiffTurboFreq; 
   /**< UFS only ; indicates whether Turbo mode support is present. Will be use when 
   			NOM & TURBO mode are supporting different frequencies */
} EFI_STORAGE_TURBOMODE_INFO; /* Added in EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION3 */

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
  Storage device modes
*/
typedef enum {
   DEVICE_ON = 1, 
   DEVICE_SLEEP = 2, 
   DEVICE_OFF = 3
} EFI_STORAGE_DEV_MODE;

/* @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
Shared ICE Algorithm */

#define NUM_OF_FLOOR_ALGO_SETS  10
#define NUM_OF_SHARED_ICE_ALGO	3

/* @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
 Disable/Enable SharedIce */
typedef enum
{
  SHARED_ICE_DISABLE = 0,
  SHARED_ICE_ENABLE = 1,
  SHARED_ICE_MAX = 2,
}EFI_STORAGE_SHARED_ICE;

/*@ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
SharedIce Algorithms */
typedef enum
{
  SHARED_ICE_ALGO_STATIC = 0,
  SHARED_ICE_ALGO_FLOOR = 1,
  SHARED_ICE_ALGO_INSTANT = 2,
  SHARED_ICE_ALGO_MAX = 3,
}EFI_STORAGE_SHARED_ICE_ALGO;

/*@ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
Buffer to share Shared ICE information between driver and tools. */
typedef struct
{
    UINT8 SharedIceEnable;
    EFI_STORAGE_SHARED_ICE_ALGO SharedIceAlgo;
    UINT8 *AlgoValues;
}EFI_STORAGE_SHARED_ICE_INFO;

/*@ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
Parameters for FLOOR based SharedIce Algo */
typedef struct 
{
  UINT8 AlgoValid;
  UINT8 NoOfTxCore;
  UINT8 NoOfRxCore;
  UINT8 NoOfWriteTaskMax;
  UINT8 NoOfWriteTaskMin;
  UINT8 NoOfReadTaskMax;
  UINT8 NoOfReadTaskMin;
}EFI_STORAGE_ICE_FLOOR_PARAMS;

/* @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data
 Parameters for STATIC SharedIce Algo */
typedef struct
{
  UINT8 NoOfTxCore;
  UINT8 NoOfRxCore;
}EFI_STORAGE_ICE_STATIC_PARAMS;

/* @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
Parameters for INSTANTANEOUS SharedIce Algo */
typedef struct
{
  UINT8 NoOfTxR1W1Core;
  UINT8 NoOfRxR1W1Core;
  UINT8 NoOfTxR0W1Core;
  UINT8 NoOfRxR1W0Core;
}EFI_STORAGE_ICE_INSTANT_PARAMS;

/** @} */ /* end_addtogroup efi_deviceManagement_data_types */

/*===========================================================================
   FUNCTION DEFINITIONS
===========================================================================*/

/* EFI_GET_DEV_INFO */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_apis
  @par Summary
  Provides information about the storage device 

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] DevInfo             Storage device information
 
  @par Description
  This function provides information about the storage device (spec version, firmware version, 
  serial number).
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par
  EFI_OUT_OF_RESOURCES    --   Buffer could not be allocated.
  @par 
  EFI_DEVICE_ERROR        --   Device encountered an error getting the device information.
*/ 
typedef 
EFI_STATUS
(EFIAPI * EFI_GET_DEV_INFO) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
   OUT EFI_STORAGE_DEV_INFO *DevInfo
);

/* EFI_GET_ERROR_STATS */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_apis 
  @par Summary
  Provides the storage error statistics

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] ErrStats            Statistics about the storage errors
 
  @par Description
  This function provides statistics about the errors encountered by the storage device (details 
  may vary depending on the storage type).
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
*/
typedef
EFI_STATUS
(EFIAPI * EFI_GET_ERROR_STATS) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   OUT EFI_STORAGE_ERR_STATS *ErrStats
); 

/* EFI_GET_OP_MODE_CAPS */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Provides information about the capabilities of storage operational modes

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] OpModeCaps          Information about the operational modes
 
  @par Description
  This function provides the capabilities about the storage operational modes (the number of speed
  levels and voltage corners, as well as which voltage corner corresponds to nominal).
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
*/ 
typedef
EFI_STATUS
(EFIAPI * EFI_GET_OP_MODE_CAPS) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   OUT EFI_STORAGE_OP_MODE_CAPABILITIES *OpModeCaps
);

/* EFI_GET_CURRENT_OP_MODE */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Gets the current operational mode information of the storage

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] OpModeInfo          Information about the current operational mode
 
  @par Description
  This function provides the current speed level, voltage corner, and link state of the
  storage device. 
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
*/
typedef
EFI_STATUS
(EFIAPI * EFI_GET_CURRENT_OP_MODE) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
   OUT EFI_STORAGE_OP_MODE_INFO *OpModeInfo
);
 
/* EFI_SET_SPEED */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Sets the storage device speed

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  SpeedLevel          Speed level to be set 
 
  @par Description
  This function sets the storage device speed to the value indicated
 
  @return
  EFI_SUCCESS             --   Speed level was set successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par 
  EFI_UNSUPPORTED         --   The speed passed is unsupported with the current voltage corner. 
  @par
  EFI_DEVICE_ERROR        --   The speed level was not set successfully.
*/
typedef
EFI_STATUS
(EFIAPI * EFI_SET_SPEED) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   IN UINT8 SpeedLevel
);
  
/* EFI_SET_VOLTAGE_CORNER */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Sets the voltage corner that storage should enter

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  VoltCorner          Voltage corner to enter
 
  @par Description
  This function configures the storage to operate in the indicated voltage corner
 
  @return
  EFI_SUCCESS             --   No issues changing storage to the voltage corner.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par
  EFI_UNSUPPORTED         --   The voltage corner is unsupported with the current speed level. 
  @par
  EFI_DEVICE_ERROR        --   Issues were encountered while changing storage to the voltage corner. 
*/ 
typedef
EFI_STATUS
(EFIAPI * EFI_SET_VOLTAGE_CORNER) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   IN EFI_STORAGE_VOLT_CORNER VoltCorner
);

/* EFI_SET_OP_MODE */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Sets the storage operating mode (speed level + voltage corner)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  VoltCorner          Voltage corner to enter
  @param[in]  SpeedLevel          Speed level to be set
 
  @par Description
  This function configures the storage to operate at the indicated speed level and voltage corner
 
  @return
  EFI_SUCCESS             --   Storage switched to the indicated speed level and voltage corner.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par
  EFI_UNSUPPORTED         --   The voltage corner and speed level combination is unsupported. 
  @par
  EFI_DEVICE_ERROR        --   Issues were encountered while changing storage to the speed level and/or voltage corner. 
*/
typedef
EFI_STATUS
(EFIAPI * EFI_SET_OP_MODE) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   IN EFI_STORAGE_VOLT_CORNER VoltCorner, 
   IN UINT8 SpeedLevel
); 

/* EFI_CONFIGURE_LINK */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Configures the link characteristics

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  Params              Link parameters to configure
 
  @par Description
  This function configures link characterstics that are tunable
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Invalid argument is provided.  
  @par
  EFI_DEVICE_ERROR        --   Physical device reported an error when configuring the parameters. 
*/
typedef
EFI_STATUS
(EFIAPI * EFI_CONFIGURE_LINK) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   IN EFI_STORAGE_LINK_PARAMS *Params
); 

/* EFI_SET_LINK_STATE */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Set the link state 

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  LinkState           The state to change the link to   
 
  @par Description
  This function changes the link to the indicated state
 
  @return
  EFI_SUCCESS             --   Link is changed to the indicated state. 
  @par
  EFI_INVALID_PARAMETER   --   Invalid argument is provided.  
  @par
  EFI_DEVICE_ERROR        --   Physical device encountered an error when changing the link state. 
*/
typedef 
EFI_STATUS 
(EFIAPI * EFI_SET_LINK_STATE) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   IN EFI_STORAGE_LINK_STATE LinkState
);

/* EFI_SET_DEVICE_MODE */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Sets the storage device mode (on/off/sleep)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[in]  DevMode             Device mode to enter
 
  @par Description
  This function changes the device mode of the storage device
 
  @return
  EFI_SUCCESS             --   Storage successfully entered the device mode indicated.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invaid. 
  @par
  EFI_UNSUPPORTED         --   Device mode is not supported. 
  @par
  EFI_DEVICE_ERROR        --   Issues were encountered while changing storage to the device mode.  
*/
typedef
EFI_STATUS
(EFIAPI * EFI_SET_DEVICE_MODE) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   IN EFI_STORAGE_DEV_MODE DevMode
);  

/* EFI_GET_LS_INFO */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Provides information about Level Shifter (EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION2 and above)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] LevelShifterInfo    Information about Level Shifter
 
  @par Description
  This function provides information about Level Shifter (SD card only)
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par 
  EFI_DEVICE_ERROR        --   Device encountered an error.
*/ 
typedef 
EFI_STATUS
(EFIAPI * EFI_GET_LS_INFO) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This, 
   OUT EFI_STORAGE_LS_INFO          *LevelShifterInfo
);

/* EFI_GET_SHARED_ICE_ALGO */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data  
  @par Summary
  Gets the shared ice mode (static/floor/Instanteneous)
    (EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION4 and above)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[OUT]  AlgoInfo           Buffer containing information on shared ICE.
 
  @par Description
  This function gets the information about sharedICE algorithm enabled/disabled and the register values.
 
  @return
  EFI_SUCCESS             --   Success in getting the Shared Ice Algorithm parameters.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invaid. 
  @par
  EFI_DEVICE_ERROR        --   Issues were encountered while getting shared ice algorithm.

*/
typedef
EFI_STATUS
(EFIAPI * EFI_GET_SHARED_ICE_ALGO) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   OUT EFI_STORAGE_SHARED_ICE_INFO *AlgoInfo
); 

/* EFI_SET_SHARED_ICE_ALGO */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Sets the shared ice mode (static/floor/Instanteneous)
    (EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION4 and above)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[OUT]  AlgoInfo           Buffer conatining information on shared ICE.
 
  @par Description
  This function sets the sharedICE algorithm enabled/disabled and the register values.
 
  @return
  EFI_SUCCESS             --   Success in setting the Shared Ice Algorithm.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invaid. 
  @par
  EFI_DEVICE_ERROR        --   Issues were encountered while setting shared ice algorithm.  
*/
typedef
EFI_STATUS
(EFIAPI * EFI_SET_SHARED_ICE_ALGO) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   IN EFI_STORAGE_SHARED_ICE_INFO *AlgoInfo
); 

/* EFI_GET_TURBO_MODE_INFO */
/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
  @par Summary
  Provides information on Turbo mode supporting different frequency than NOM mode  
  								(EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION3 and above)

  @param[in]  This                Pointer to the EFI_STORAGE_DEV_MGMT_PROTOCOL instance
  @param[out] TurboModeInfo             indicates whether Turbo mode freq is different than NOM or not. 
 
  @par Description
  This function provides the information if TURBO freq used Is different from NOM or not.
 
  @return
  EFI_SUCCESS             --   Storage successfully entered the device mode indicated.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invaid. 
  @par
  EFI_UNSUPPORTED         --   Device mode is not supported. 
  @par
  EFI_DEVICE_ERROR        --   Issues were encountered while changing storage to the device mode.  
*/
typedef
EFI_STATUS
(EFIAPI * EFI_GET_TURBO_MODE_INFO) (
   IN EFI_STORAGE_DEV_MGMT_PROTOCOL *This,
   OUT EFI_STORAGE_TURBOMODE_INFO   *TurboModeInfo
);  
/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_apis
**/
typedef struct
{  
   EFI_GET_OP_MODE_CAPS       GetOpModeCaps;
   EFI_GET_CURRENT_OP_MODE    GetCurrentOpMode; 
   EFI_SET_SPEED              SetSpeedLevel;
   EFI_SET_VOLTAGE_CORNER     SetVoltageCorner;
   EFI_SET_OP_MODE            SetOperationalMode;
   EFI_CONFIGURE_LINK         ConfigLink;
   EFI_SET_LINK_STATE         SetLinkState; 
   EFI_SET_DEVICE_MODE        SetDeviceMode; 
} EFI_STORAGE_POWER_MGMT_OPS;

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_data 
**/
typedef struct 
{
  EFI_GET_SHARED_ICE_ALGO  GetSharedIceAlgorithm;
  EFI_SET_SHARED_ICE_ALGO  SetSharedIceAlgorithm;
}EFI_ICE_OPS;


/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_apis
**/
typedef struct 
{
   EFI_GET_LS_INFO            GetLevelShifterInfo;   /* Added in EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION2 */
   EFI_GET_TURBO_MODE_INFO    GetTurboModeinfo;    /* Added in EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION3 */
   EFI_ICE_OPS                SharedIceMgmt;         /* Added in EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION4 */
} EFI_STORAGE_HW_CONFIG; 

/** @ingroup EFI_STORAGE_DEV_MGMT_PROTOCOL_prot
  @par Summary
  Device Management Protocol interface. 

  @par Parameters
  @inputprotoparams{device_management_proto_params.tex}
**/
struct _EFI_STORAGE_DEV_MGMT_PROTOCOL 
{  
   UINT64                     Revision;
   EFI_GET_DEV_INFO           GetDeviceInfo; 
   EFI_GET_ERROR_STATS        GetErrorStats;  
   EFI_STORAGE_POWER_MGMT_OPS PowerMgmt;    
   EFI_STORAGE_HW_CONFIG      HwConfig;      /* Added in EFI_STORAGE_DEV_MGMT_PROTOCOL_REVISION2 */
};

#endif	/* __EFI_STORAGE_DEVICEMANAGEMENT_H__ */

