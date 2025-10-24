/**
  @file EFIStorageEyemon.h
  @brief Storage Eye Monitor protocol definitions.
*/
/*=============================================================================
  Copyright (c) 2022 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when        who     what, where, why
 --------    ---     -----------------------------------------------------------
 07/15/22    jt      Initial version
 
=============================================================================*/
#ifndef __EFI_STORAGE_EYEMON_H__
#define __EFI_STORAGE_EYEMON_H__

/** @defgroup EFI_STORAGE_EYEMON_PROTOCOL  EFI_STORAGE_EYEMON_PROTOCOL 
 *  @ingroup PERIPHERALS 
 */
 /** @defgroup  EFI_STORAGE_EYEMON_PROTOCOL_prot PROTOCOL
 *  @ingroup EFI_STORAGE_EYEMON_PROTOCOL 
 */ 
 /** @defgroup  EFI_STORAGE_EYEMON_PROTOCOL_apis APIs
 *  @ingroup EFI_STORAGE_EYEMON_PROTOCOL 
 */ 

/** @defgroup  EFI_STORAGE_EYEMON_PROTOCOL_data DATA_STRUCTURES
 *  @ingroup EFI_STORAGE_EYEMON_PROTOCOL 
 */

/** @cond */
typedef struct _EFI_STORAGE_EYEMON_PROTOCOL   EFI_STORAGE_EYEMON_PROTOCOL;
/** @endcond */
  
/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_data
    Protocol version.
*/
#define EFI_STORAGE_EYEMON_PROTOCOL_REVISION      0x0000000000010000

/* Protocol GUID definition */
/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_data */
#define EFI_STORAGE_EYEMON_PROTOCOL_GUID \
	{0x3b367db4, 0xb223, 0x4ddd, { 0xa3, 0xfe, 0x30, 0xf1, 0xf7, 0xde, 0x00, 0x91 } }

/** @cond */
/* External reference to the Eye Monitor GUID */
extern EFI_GUID gEfiStorageEyemonProtocolGuid;
/** @endcond */

/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_data
  Eye Monitor modes
*/
typedef enum {
   DEVICE_EYEMON = 0, 
   HOST_EYEMON
} EFI_STORAGE_EYEMON_MODE;

/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_data
  Eye Monitor lane number
*/
typedef enum {
   LANE_0 = 0, 
   LANE_1 = 1, 
   LANE_ALL = 0xFF
} EFI_STORAGE_LANE_NUM;

/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_data
  Eye Monitor test parameters
*/
typedef struct {
   EFI_STORAGE_EYEMON_MODE    Mode; 
   EFI_STORAGE_LANE_NUM       LaneNum; 
} EFI_STORAGE_EYEMON_PARAMS; 

/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_data
  Eye Monitor capabilities
*/
typedef struct {
   UINT8      Supported; 
   UINT8      TimingMaxSteps; 
   UINT8      TimingMaxOffset; 
   UINT8      VoltageMaxSteps;
   UINT8      VoltageMaxOffset;
} EFI_STORAGE_EYEMON_CAPS;

/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_data
  Eye Monitor configuration paramters
*/
typedef struct {
   UINT8      TimingDirection;
   UINT8      TimingSteps; 
   UINT8      VoltageDirection; 
   UINT8      VoltageSteps; 
   UINT8      TargetTestCount; 
} EFI_STORAGE_EYEMON_CONFIG; 

/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_data
  Eye Monitor result values
*/
typedef struct 
{
   UINT8       ErrorCount; 
   UINT8       TestedCount; 
} EFI_STORAGE_EYEMON_RESULT; 

/** @} */ /* end_addtogroup efi_eyemon_data_types */

/*===========================================================================
   FUNCTION DEFINITIONS
===========================================================================*/

/* EFI_EYEMON_GET_CAPS */
/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_apis 
  @par Summary
  Gets the Eye Monitor capabilities 

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Pointer to the test params
  @param[out] Capabilities        Pointer to the Eye Monitor capabilities
 
  @par Description
  This function gets the capabilities for Eye Monitor based on the Params 
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par 
  EFI_DEVICE_ERROR        --   Device encountered an error.
*/ 
typedef 
EFI_STATUS
(EFIAPI *EFI_EYEMON_GET_CAPS) (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   OUT EFI_STORAGE_EYEMON_CAPS    *Capabilities
);

/* EFI_EYEMON_PM_CHANGE */
/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_apis 
  @par Summary
  Changes the power mode for Eye Monitor measurement 

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Pointer to the test params
  @param[in]  Gear                HS Gear to switch to
  @param[in]  Adapt               Enable adapt or not
 
  @par Description
  This function changes the power mode to the gear and adapt value specified
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par 
  EFI_DEVICE_ERROR        --   Device encountered an error.
*/  
typedef 
EFI_STATUS
(EFIAPI *EFI_EYEMON_PM_CHANGE) (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This,
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN UINT8                       Gear, 
   IN UINT8                       Adapt
);

/* EFI_EYEMON_SET_COARSE_CODE */
/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_apis 
  @par Summary
  Sets the coarse code for Host Side Eye Monitor measurement 

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Pointer to the test params
  @param[in]  CoarseCode          Coarse Code value
 
  @par Description
  This function sets the coarse code (valid only for Host Side Eye Monitor)
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par 
  EFI_DEVICE_ERROR        --   Device encountered an error.
*/  
typedef 
EFI_STATUS
(EFIAPI *EFI_EYEMON_SET_COARSE_CODE) (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This,
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN UINT8                       CoarseCode
);

/* EFI_EYEMON_CONFIG */
/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_apis 
  @par Summary
  Configure the Eye Monitor params 

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Pointer to the test params
  @param[in]  Config              Pointer to the Eye Monitor configuration parameters
 
  @par Description
  This function will configure the Eye Monitor parameters, such as timing/voltage offset and test count 
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par 
  EFI_DEVICE_ERROR        --   Device encountered an error.
*/ 
typedef 
EFI_STATUS 
(EFIAPI *EFI_EYEMON_CONFIG) (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN EFI_STORAGE_EYEMON_CONFIG   *Config
);

/* EFI_EYEMON_ENABLE */
/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_apis 
  @par Summary
  Starts/ends Eye Monitor measurement 

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Pointer to the test params
  @param[in]  Enable              Enable or disable Eye Monitor
 
  @par Description
  This function will enable/disable the Eye Monitor measurement
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par 
  EFI_DEVICE_ERROR        --   Device encountered an error.
*/
typedef
EFI_STATUS 
(EFIAPI *EFI_EYEMON_ENABLE) (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This, 
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   IN BOOLEAN                     Enable
);

/* EFI_EYEMON_GET_RESULT */
/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_apis 
  @par Summary
  Retrieves the Eye Monitor result

  @param[in]  This                Pointer to the EFI_STORAGE_EYEMON_PROTOCOL instance
  @param[in]  Params              Pointer to the test params
  @param[out] Result              Pointer to the Eye Monitor result values
 
  @par Description
  This function gets the Eye Monitor result for the current configuration 
 
  @return
  EFI_SUCCESS             --   Function completed successfully.
  @par
  EFI_INVALID_PARAMETER   --   Parameter is invalid. 
  @par 
  EFI_NOT_READY           --   Measurement still in progress. 
  @par 
  EFI_DEVICE_ERROR        --   Device encountered an error.
*/  
typedef 
EFI_STATUS 
(EFIAPI *EFI_EYEMON_GET_RESULT) (
   IN EFI_STORAGE_EYEMON_PROTOCOL *This,
   IN EFI_STORAGE_EYEMON_PARAMS   *Params, 
   OUT EFI_STORAGE_EYEMON_RESULT  *Result
);

/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/

/** @ingroup EFI_STORAGE_EYEMON_PROTOCOL_prot
  @par Summary
  Eye Monitor Protocol interface. 

  @par Parameters
  @inputprotoparams{eyemon_proto_params.tex}
**/
struct _EFI_STORAGE_EYEMON_PROTOCOL 
{  
   UINT64                       Revision;
   EFI_EYEMON_GET_CAPS          GetCapabilities;
   EFI_EYEMON_PM_CHANGE         PowerModeChange; 
   EFI_EYEMON_SET_COARSE_CODE   SetCoarseCode; 
   EFI_EYEMON_CONFIG            Config; 
   EFI_EYEMON_ENABLE            Enable;    
   EFI_EYEMON_GET_RESULT        GetResult; 
};

#endif	/* __EFI_STORAGE_EYEMON_H__ */

