/** 
@file  EFIPmicScpq.h
@brief PMIC SCPQ for UEFI.
*/
/*=============================================================================
Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
All rights reserved.
Qualcomm Technologies Inc Confidential and Proprietary.
    
=============================================================================*/

/*=============================================================================
EDIT HISTORY


when       who     what, where, why
--------   ---     -----------------------------------------------------------
01/18/22   sch     Add API to get charger pmic index
02/21/20   xp      Initial draft

=============================================================================*/

#ifndef __EFIPMICSCPQ_H__
#define __EFIPMICSCPQ_H__


/*===========================================================================

                        MACRO DECLARATIONS

===========================================================================*/
/** @addtogroup efi_pmicScqp_constants 
@{ */
/**
Protocol version.
*/

#define PMIC_SCPQ_REVISION 0x0000000000010003
/** @} */ /* end_addtogroup efi_pmicScpq_constants */

/*  Protocol GUID definition */
/** @ingroup efi_pmicScpq_protocol */
#define EFI_PMIC_SCPQ_PROTOCOL_GUID \
    { 0x7fafe83b, 0xb5cf, 0x4e48, { 0xb0, 0xb0, 0xe6, 0xc1, 0xba, 0x61, 0x38, 0xbb } }


/** @cond */
/*===========================================================================

                        EXTERNAL VARIABLES

===========================================================================*/
/**
External reference to the PMIC SCPQ Protocol GUID.
*/
extern EFI_GUID gQcomPmicScpqProtocolGuid;

/*===========================================================================

                        FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

                        TYPE DEFINITIONS

===========================================================================*/

typedef enum 
{
   PM_SCPQ_POWER_PATH__NONE,    /**< No charger. */
   PM_SCPQ_POWER_PATH__BATTERY,    /**< Battery.    */
   PM_SCPQ_POWER_PATH__USBIN,    /**< USB path.   */
   PM_SCPQ_POWER_PATH__DCIN,    /**< DCIN path.  */
   PM_SCPQ_POWER_PATH__INVALID,    /**< DCIN path.  */
} PM_SCPQ_POWER_PATH_TYPE;

typedef enum
{
  EFI_PM_SCPQ_TYPEC_CONNECT_MODE_NONE,
  EFI_PM_SCPQ_TYPEC_CONNECT_MODE_DFP,
  EFI_PM_SCPQ_TYPEC_CONNECT_MODE_UFP,
  EFI_PM_SCPQ_TYPEC_CONNECT_MODE_INVALID
} EFI_PM_SCPQ_TYPEC_CONNECT_MODE_STATUS;

typedef enum
{
  EFI_PM_SCPQ_TYPEC_CC_OUT_RESERVED,
  EFI_PM_SCPQ_TYPEC_CC_OUT_CC1,
  EFI_PM_SCPQ_TYPEC_CC_OUT_CC2,
  EFI_PM_SCPQ_TYPEC_CC_OUT_OPEN,
  EFI_PM_SCPQ_TYPEC_CC_OUT_INVALID
} EFI_PM_SCPQ_TYPEC_CC_OUT_STATUS;

/**  TYPEC DFP Current Advertisement - from UFP perspective **/
typedef enum
{
  EFI_PM_SCPQ_TYPEC_DFP_CURR_ADV_RESERVED,
  EFI_PM_SCPQ_TYPEC_DFP_CURR_ADV_3A,             // 3.0A @ 5V
  EFI_PM_SCPQ_TYPEC_DFP_CURR_ADV_1P5A,           // 1.5A @ 5V
  EFI_PM_SCPQ_TYPEC_DFP_CURR_ADV_STD,            // 900mA @ 5V - STD TypeC USB Power
  EFI_PM_SCPQ_TYPEC_DFP_CURR_ADV_INVALID
} EFI_PM_SCPQ_TYPEC_DFP_CURR_ADV;

/**  TYPEC UFP Connection Type (Cable Connector) - from DFP perspective  **/
typedef enum
{
  EFI_PM_SCPQ_TYPEC_CABLE_CONNECTOR_RESERVED,
  EFI_PM_SCPQ_TYPEC_STATE_UNATTACHED,            // DFP_OPEN_OPEN
  EFI_PM_SCPQ_TYPEC_UFP_ATTACHED,                // DFP_RD_OPEN
  EFI_PM_SCPQ_TYPEC_PWR_CABLE_NO_UFP_ATTCHED,    // DFP_RA_OPEN
  EFI_PM_SCPQ_TYPEC_PWR_CABLE_UFP,               // DFP_RD_RA_VCONN
  EFI_PM_SCPQ_TYPEC_AUDIO_ADAP_MODE,             // DFP_RA_RA
  EFI_PM_SCPQ_TYPEC_DEBUG_ACCESSORY_MODE,        // DFP_RD_RD
  // DFP-to-DFP and UFP-to-UFP are undetectable states
  EFI_PM_SCPQ_TYPEC_CABLE_CONNECTOR_INVALID
} EFI_PM_SCPQ_TYPEC_UFP_CONNECTOR_TYPE;

/**  OTG status type **/
typedef enum
{
  EFI_PM_SCPQ_DCDC_OTG_ENABLED,
  EFI_PM_SCPQ_DCDC_OTG_DISABLED,
  EFI_PM_SCPQ_DCDC_OTG_ERROR,
  EFI_PM_SCPQ_DCDC_OTG_EXECUTING_ENABLE_SEQ,
  EFI_PM_SCPQ_DCDC_OTG_EXECUTING_DISABLE_SEQ,
  EFI_PM_SCPQ_DCDC_OTG_STATUS_INVALID
} EFI_PM_SCPQ_DCDC_OTG_STATUS_TYPE;

/**  Charging port types. **/
typedef enum EFI_PM_SCPQ_CHGR_PORT_TYPE
{
  EFI_PM_SCPQ_CHG_PORT_SDP_CHARGER,         /**< Standard Downstream Port         */
  EFI_PM_SCPQ_CHG_PORT_OCP_CHARGER,         /**< Other Charging Port              */
  EFI_PM_SCPQ_CHG_PORT_CDP_CHARGER,         /**< Charging Downstream Port         */
  EFI_PM_SCPQ_CHG_PORT_DCP_CHARGER,         /**< Dedicated Charging Port          */
  EFI_PM_SCPQ_CHG_PORT_FLOAT_CHARGER,       /**< Floating Charging Port           */
  EFI_PM_SCPQ_CHG_PORT_QC_2P0,              /**< Quick Charger 2.0 Charging Port  */
  EFI_PM_SCPQ_CHG_PORT_QC_3P0,              /**< Quick Charger 3.0 Charging Port  */
  EFI_PM_SCPQ_CHG_PORT_INVALID = 0xFF,             /**< INVALID PORT                     */
}EFI_PM_SCPQ_CHGR_PORT_TYPE;

typedef enum
{
  EFI_PM_SCPQ_WDOG_STS_BARK,                          /**< Indicates BARK WDOG Timer expired   >*/
  EFI_PM_SCPQ_WDOG_STS_BITE_CHARGING_DISABLED,        /**< Indicates BITE WDOG Timer expired and Charging is Disabled  >*/
  EFI_PM_SCPQ_WDOG_STS_BITE_CHARGING_NOT_DISABLED,    /**< Indicates BITE WDOG Timer expired but Charging is not Disabled  >*/
  EFI_PM_SCPQ_WDOG_STS_INVALID,
}EFI_PM_SCPQ_WDOG_STS_TYPE;

typedef enum {
  EFI_PM_SCPQ_DC_IRQ_DCIN_0,  /*TBD*/
  EFI_PM_SCPQ_DC_IRQ_DCIN_VASHDN, /*The DCIN voltage has crossed the auto-shutdown threshold*/
  EFI_PM_SCPQ_DC_IRQ_DCIN_UV, /*The DCIN voltage has crossed the under-voltage threshold*/
  EFI_PM_SCPQ_DC_IRQ_DCIN_OV, /*The DCIN voltage has crossed the over-voltage threshold*/
  EFI_PM_SCPQ_DC_IRQ_DCIN_PLUGIN, /*DCIN plugged in, goes low on un-plug*/
  EFI_PM_SCPQ_DC_IRQ_REVI,  /*The DCIN voltage is below the revi threshold*/
  EFI_PM_SCPQ_DC_IRQ_PON, /*The DCIN_PON Pin is Enabled*/
  EFI_PM_SCPQ_DC_IRQ_EN,  /*The DCIN_EN Pin is Enabled*/
  EFI_PM_SCPQ_DC_IRQ_INVALID, /*Invalid*/
}EFI_PM_SCPQ_DC_IRQ_TYPE; 

typedef enum {
  EFI_PM_SCPQ_THERM_CMP,
  EFI_PM_SCPQ_BATT_ID_BMISS,
  EFI_PM_SCPQ_FAKE_BAT_DET,
}EFI_PM_SCPQ_BATTERY_MISSING_STATUS_TYPE;

typedef enum
{
  EFI_PM_SCHG_OS_BOOTLOADER,
  EFI_PM_SCHG_OS_HLOS,
  EFI_PM_SCHG_OS_INVALID,
}EFI_PM_SCHG_OS_TYPE;

typedef struct
{
  UINT32 PmicIndex;
  UINT32 SlaveIndex;
} EFI_PM_SCPQ_PMIC_INFO;

/**  TYPEC Port status on attach of USB cable **/
typedef struct
{
  EFI_PM_SCPQ_TYPEC_CC_OUT_STATUS         cc_out_sts;
  EFI_PM_SCPQ_TYPEC_DFP_CURR_ADV          dfp_curr_adv;
  EFI_PM_SCPQ_TYPEC_UFP_CONNECTOR_TYPE    ufp_conn_type;
  BOOLEAN                                 vbus_sts;
  BOOLEAN                                 vbus_err_sts;
  BOOLEAN                                 debounce_done_sts;
  BOOLEAN                                 vconn_oc_sts;
  BOOLEAN                                 ccout_out_hiz_sts;
} EFI_PM_SCPQ_TYPEC_PORT_STATUS;


typedef struct
{
  UINT32 max_icl_status;                         /* Max ICL value */
  UINT32 aicl_icl_status;                        /* ICL value post AICL */
  UINT32 thermal_icl_status;                     /* ICL value post HW therm adjustment */
  UINT32 final_icl_status;                       /* ICL value post AICL, HW and SW therm adjustment */ 
  UINT32 aicl_done;
}EFI_PM_SCPQ_ICL_STATUS;

typedef struct
{
  BOOLEAN jeitaHardHot;
  BOOLEAN jeitaSoftHot;
  BOOLEAN jeitaHardCold;
  BOOLEAN jeitaSoftCold;
}EFI_PM_SCPQ_BATT_TEMP_STATUS;


typedef struct
{
  BOOLEAN bChargingEnabled;
}EFI_PM_SCPQ_CHARGING_STATUS;


/* EFI_PMIC_SCPQ_GET_PMIC_INFO */
/** @ingroup EFI_PmicScpqGetPmicInfo
  @par Summary
  Provides SCPQ charger PMIC Index.

  @param[out]  ScpqPmicInfo     PMIC Info, on what SCPQ charger resides

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_INVALID_PARAMETER -- If input param is invalid. \n
  EFI_DEVICE_ERROR      -- Error occurred during the operation.
*/
typedef
EFI_STATUS (EFIAPI *EFI_PMIC_SCPQ_GET_PMIC_INFO)(
    OUT EFI_PM_SCPQ_PMIC_INFO *ScpqPmicInfo
);

typedef
EFI_STATUS (EFIAPI *EFI_PMIC_SCPQ_GET_CHARGER_PMIC_INDEX)(
        OUT UINT8 *ChargerPmicIndex
);

/* EFI_PMIC_SCPQ_USBIN_VALID */
/** @ingroup efi_pmicScpq_usbin_valid
  @par Summary
  Indicates whether the VBUS on PMIC is high or low.

  @param[in]  PmicDeviceIndex    0:Primary, 1:Secondary
  @param[out] Valid              TRUE if VBUS high else FALSE.

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
*/
typedef
EFI_STATUS (EFIAPI *EFI_PMIC_SCPQ_USBIN_VALID)(
  IN  UINT32  PmicDeviceIndex,
  OUT BOOLEAN *Valid
);

/* EFI_PMIC_SCPQ_GET_POWER_PATH */
/** @ingroup
  @par Summary
  Returns information about the charger attached to the device.

  @param[in]  PmicDeviceIndex    0:Primary, 1:Secondary
  @param[out] ChargerPath        Charger path; see #PM_SCPQ_POWER_PATH_TYPE
                                 for details.

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
*/
typedef
EFI_STATUS (EFIAPI *EFI_PMIC_SCPQ_GET_POWER_PATH)(
  IN  UINT32                   PmicDeviceIndex,
  OUT PM_SCPQ_POWER_PATH_TYPE  *ChargerPath
);

/* EFI_PMIC_SCPQ_IS_BATTERY_PRESENT */
/** @ingroup efi_pmicScpq_is_battery_present
  @par Summary
  Indicates whether the battery is present.

  @param[in]  PmicDeviceIndex    0:Primary, 1:Secondary
  @param[out] BatteryPresent     Whether or not the battery is present.

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
*/
typedef
EFI_STATUS (EFIAPI *EFI_PMIC_SCPQ_IS_BATTERY_PRESENT)(
  IN  UINT32  PmicDeviceIndex,
  OUT BOOLEAN *BatteryPresent
);

/* EFI_PMIC_SCPQ_GET_CHARGER_PORT_TYPE */
/** @ingroup efi_pmic_scpq_get_charger_port_type
  @par Summary
  reads charger port type.

  @param[in]  PmicDeviceIndex    Primary: 0, Secondary:1
  @param[out] PortType           Charging port type.
                                 For more info refer enum EFI_PM_SCPQ_CHGR_PORT_TYPE

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
*/
typedef
EFI_STATUS (EFIAPI *EFI_PMIC_SCPQ_GET_CHARGER_PORT_TYPE)(
  IN  UINT32                       PmicDeviceIndex,
  OUT EFI_PM_SCPQ_CHGR_PORT_TYPE *PortType
);

/**@ingroup efi_pmic_scpq_get_otg_ocp_sts
  @par Summary
  Returns OTG Over-current protection (OCP) status

  @param[in]   PmicDeviceIndex   0:Primary, 1:Secondary
  @param[out]  Ok                OTG OCP is in good standing, FLASE: OTG OCP needs to be re-enabled

  @return
  EFI_SUCCESS            -- Function completed successfully. \n
  EFI_DEVICE_ERROR       -- Physical device reported an error. \n
*/
typedef
EFI_STATUS (EFIAPI *EFI_PMIC_SCPQ_GET_OTG_STATUS)(
  IN  UINT32                       PmicDeviceIndex,
  OUT EFI_PM_SCPQ_DCDC_OTG_STATUS_TYPE  *pOtgStatus
);

/* EFI_PMIC_SCPQ_DUMP_PERIPHERAL */
/** @ingroup efi_pmic_scpq_dump_pheripheral
  @par Summary
  Dump Charger Pheripheral

  @param[in]  PmicDeviceIndex    Primary: 0, Secondary:1

  @return
  EFI_SUCCESS           -- Function completed successfully. \n
  EFI_DEVICE_ERROR      -- Physical device reported an error. \n
*/
typedef
EFI_STATUS (EFIAPI *EFI_PMIC_SCPQ_DUMP_PERIPHERAL)(
  VOID
);

/* EFI_PMIC_SCPQ_GET_CHARGING_STATUS */
/** @ingroup EFI_PmicScpqGetChargingStatus
@par Summary
Returns if charging is enabled/disabled

@param[in]   PmicDeviceIndex    Primary: 0, Secondary:1
@param[out]  pChargingEnabled    TRUE: Charging Enabled
                                 FALSE: Charging Disabled

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_DEVICE_ERROR      -- Physical device reported an error. \n
*/
typedef
EFI_STATUS (EFIAPI * EFI_PMIC_SCPQ_GET_CHARGING_STATUS)(
  UINT32 PmicDeviceIndex,
  OUT EFI_PM_SCPQ_CHARGING_STATUS *pChargingStatus
);

/* EFI_PMIC_SCPQ_DCIN_VALID */
/** @ingroup efi_pmicScpq_dcin_valid
@par Summary
Indicates whether the DC IN is plugged in or not

@param[in]  PmicDeviceIndex    0:Primary, 1:Secondary
@param[out] Valid              TRUE if VBUS high else FALSE.

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_DEVICE_ERROR      -- Physical device reported an error. \n
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_SCPQ_DCIN_VALID)(
  IN  UINT32  PmicDeviceIndex,
  OUT BOOLEAN *Valid
);

/* EFI_PMIC_SCPQ_GET_ICL_STATUS */
/** @ingroup EFI_PmicGetIclStatus
@par Summary
Gets the ICL values post AICL, thermal and other HW adjustments

@param[in]  PmicDeviceIndex    Primary: 0, Secondary:1
@param[out]  pIclStatus See struct def

@return
EFI_SUCCESS           -- Function completed successfully. \n
EFI_DEVICE_ERROR      -- Physical device reported an error. \n
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_SCPQ_GET_ICL_STATUS)
(
IN UINT32                      PmicDeviceIndex,
OUT EFI_PM_SCPQ_ICL_STATUS *pIclStatus
);

/* EFI_PMIC_SCPQ_TYPEC_GET_PORT_STATE */
/*@par Summary
This API returns Type-C port status.

@param[in]   PmicDeviceIndex   0:Primary, 1:Secondary
@param[out]  TypeCStatus        Type-C port status

@return
EFI_SUCCESS            -- Function completed successfully.
EFI_DEVICE_ERROR       -- Physical device reported an error.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_SCPQ_TYPEC_GET_PORT_STATE)(
IN UINT32                      PmicDeviceIndex,
OUT  EFI_PM_SCPQ_TYPEC_PORT_STATUS  *TypeCStatus
);


/* EFI_PMIC_SCPQ_TYPEC_GET_CONNECT_STATE*/
/*@par Summary
This API returns Type-C port Connection status - in terms of Port Role.

@param[in]   PmicDeviceIndex   0:Primary, 1:Secondary
@param[out]  TypeCConnStatus   Type-C port connection status

@return
EFI_SUCCESS            -- Function completed successfully.
EFI_DEVICE_ERROR       -- Physical device reported an error.
*/
typedef
EFI_STATUS(EFIAPI *EFI_PMIC_SCPQ_TYPEC_GET_CONNECT_STATE)(
IN UINT32                      PmicDeviceIndex,
OUT  EFI_PM_SCPQ_TYPEC_CONNECT_MODE_STATUS  *TypeCConnStatus
);

/* EFI_PMIC_SCPQ_GET_DC_IRQ_STATUS */
/*@par Summary
This API gets DC irq status

@param[in]  PmicDeviceIndex  : Pmic Device Index (0 for primary)
@param[in]  irq : irq 
@param[out] status: Not triggered 0, triggered 1

@return
EFI_SUCCESS           -- Function completed successfully
EFI_INVALID_PARAMETER -- Parameter is invalid
EFI_DEVICE_ERROR      -- Physical device reported an error
*/

typedef
EFI_STATUS(EFIAPI *EFI_PMIC_SCPQ_GET_DC_IRQ_STATUS)
(
  IN UINT32 PmicDeviceIndex,
  IN EFI_PM_SCPQ_DC_IRQ_TYPE irq,
  OUT BOOLEAN* irq_status
);

/* EFI_PMIC_SCPQ_GET_BATTERY_MISSING_STATUS */
/*@par Summary
This API detects if battery is missing due to ID or therm pin floating or if it is a fake battery

@param[in]  PmicDeviceIndex  : Pmic Device Index (0 for primary)
@param[in]  status_type: id missing, therm missing or fake battery
@param[out] status_val: return status indication if it is missing or fake battery
@return
EFI_SUCCESS           -- Function completed successfully
EFI_INVALID_PARAMETER -- Parameter is invalid
EFI_DEVICE_ERROR      -- Physical device reported an error
*/

typedef
EFI_STATUS(EFIAPI *EFI_PMIC_SCPQ_GET_BATTERY_MISSING_STATUS)
(
  IN UINT32 PmicDeviceIndex,
  IN EFI_PM_SCPQ_BATTERY_MISSING_STATUS_TYPE status_type,
  OUT BOOLEAN* status_val
);

/* EFI_PMIC_SCHG_SET_OS */
/*@par Summary
This API set sdam16 MEM_030, ADDRESS 0x1 to set OS

@param[in]      OS       : to set OS type

@return
EFI_SUCCESS           -- Function completed successfully
EFI_INVALID_PARAMETER -- Parameter is invalid
EFI_DEVICE_ERROR      -- Physical device reported an error
*/

typedef
EFI_STATUS(EFIAPI *EFI_PMIC_SCHG_SET_OS)
(
IN EFI_PM_SCHG_OS_TYPE OS
);

/**
Protocol declaration.
*/
typedef struct _EFI_QCOM_PMIC_SCPQ_PROTOCOL   EFI_QCOM_PMIC_SCPQ_PROTOCOL;
/** @endcond */

struct _EFI_QCOM_PMIC_SCPQ_PROTOCOL {
  UINT64                                          Revision;
  EFI_PMIC_SCPQ_GET_PMIC_INFO                     GetPmicInfo;
  EFI_PMIC_SCPQ_DUMP_PERIPHERAL                   DumpPeripheral;
  EFI_PMIC_SCPQ_USBIN_VALID                       UsbinValid;
  EFI_PMIC_SCPQ_DCIN_VALID                        DcinValid;
  EFI_PMIC_SCPQ_GET_POWER_PATH                    GetPowerPath;
  EFI_PMIC_SCPQ_IS_BATTERY_PRESENT                IsBatteryPresent;
  EFI_PMIC_SCPQ_GET_CHARGER_PORT_TYPE             GetChargerPortType;
  EFI_PMIC_SCPQ_GET_OTG_STATUS                    GetOtgStatus;
  EFI_PMIC_SCPQ_GET_CHARGING_STATUS               GetChargingStatus;
  EFI_PMIC_SCPQ_GET_ICL_STATUS                    GetIclStatus;
  EFI_PMIC_SCPQ_TYPEC_GET_PORT_STATE              GetPortState;
  EFI_PMIC_SCPQ_TYPEC_GET_CONNECT_STATE           GetConnectState;
  EFI_PMIC_SCPQ_GET_DC_IRQ_STATUS                 GetDcIrqStatus;
  EFI_PMIC_SCPQ_GET_BATTERY_MISSING_STATUS        GetBatteryMissingStatus;
  EFI_PMIC_SCHG_SET_OS                            SetOS;
  EFI_PMIC_SCPQ_GET_CHARGER_PMIC_INDEX            GetChargerPmicIndex;
};


#endif /* __EFIPMICSCPQ_H__ */

