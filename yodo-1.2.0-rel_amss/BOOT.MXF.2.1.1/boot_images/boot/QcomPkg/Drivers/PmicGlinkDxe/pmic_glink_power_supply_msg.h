#ifndef PMIC_GLINK__POWER_SUPPLY_MSG_H
#define PMIC_GLINK__POWER_SUPPLY_MSG_H

/*===========================================================================
* Copyright (c) 2019 Qualcomm Technologies Incorporated. All Rights Reserved.
* QUALCOMM Confidential and Proprietary
*
*$Header: //components/rel/core.boot/6.1.1/QcomPkg/Drivers/PmicGlinkDxe/pmic_glink_power_supply_msg.h#1 $
*$DateTime: 2022/08/18 10:15:46 $
*$Author: pwbldsvc $
=============================================================================
EDIT HISTORY

when           who     what, where, why
--------       ---     -----------------------------------------------------------
10/04/2019     cs      initial implementation
=============================================================================*/



#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup power_supply_properties_type_e
@{
*/
  typedef enum {
    POWER_SUPPLY_CHARGING_STATUS, /**< 0-unknown (default), 1-charging (any charging, pre,trickle, taper fullon), 2-discharging (no input), 3-not charging (paused, disable charging), 4-full (terminated, inhibited)>*/
    POWER_SUPPLY_HEALTH, /**< Jeita + overvoltage,  0-unknown, 1-good, 2-overheat, 3-hot, 4-overvoltage, 5-cool, 6 - cold >*/
    POWER_SUPPLY_PRESENT, /**<  battery presence >*/
    POWER_SUPPLY_CHARGE_TYPE, /**<  charging state, 0 - unknown, 1- none, 2 - trickle, 3 - fast, 4 - taper >*/
    POWER_SUPPLY_CAPACITY, /**<  battery percentage 0 - 10000 as 0% to 100% >*/
    POWER_SUPPLY_SOH, /**<  0 - 100 based on battery health  >*/
    POWER_SUPPLY_OCV, /**<  OCV in uV > */
    POWER_SUPPLY_VOLTAGE_NOW, /**< vbatt in uV >*/
    POWER_SUPPLY_VOLTAGE_MAX, /**< Vfloat in uV >*/
    POWER_SUPPLY_CURRENT_NOW, /**< ibatt in uA, negative is discharging >*/
    POWER_SUPPLY_CHARGE_CONTROL_LIMIT,   /**<same as chargeRate 0, 1, 2, 3 levels, each level will be 25% of the full FCC as of now.>*/
    POWER_SUPPLY_CHARGE_CONTROL_LIMIT_MAX, /**<THIS IS THE MAX CHARGE CONTROL LIMIT WHEN IT REGISTERS WITH THERMAL FRAMEWORK, default max is 4>*/
    POWER_SUPPLY_BATTERY_TEMP, /**< batt temp in degree C>*/
    POWER_SUPPLY_BATTERY_TECHNOLOGY, /**< battery technology: 0 - unknown, 1 - NiMh, 2 - Li-ion, 3- LiPO, 4 - Li-Fe, 5 - Ni-Cd, 6 - LiMn>*/
    POWER_SUPPLY_CHARGER_COUNTER, /**< remaining capacity in uAh>*/
    POWER_SUPPLY_CYCLE_COUNTER, /**< charge cycle count>*/
    POWER_SUPPLY_NOMINAL_CAPACITY, /**< designed capacity in uAh>*/
    POWER_SUPPLY_LEARNED_CAPACITY, /**< dlearned capacity in uAh>*/
    POWER_SUPPLY_BATTERY_MODEL, /**< battery model name, will need to be a string>*/
    POWER_SUPPLY_TTF, /**< integer in seconds, can be 0 or negative during discharging>*/
    POWER_SUPPLY_TTE, /**< integer in seconds, can be 0 or negative during charging>*/
    POWER_SUPPLY_PROP_RESISTANCE, /*battery resistance, ESR*/
    POWER_SUPPLY_PROP_POWER_NOW, /*instantaneous power in micro watts*/
    POWER_SUPPLY_PROP_POWER_AVG,  /*average power in micro watts*/
    POWER_SUPPLY_PROPERTIES_MAX,
    POWER_SUPPLY_RESERVED_1 = POWER_SUPPLY_PROPERTIES_MAX,
    POWER_SUPPLY_RESERVED_2,
    POWER_SUPPLY_PROPERTIES_TOTAL_MAX,
  }battery_power_supply_properties_type_e;

  typedef enum
  {
    USB_POWER_SUPPLY_ONLINE, 
    USB_POWER_SUPPLY_VOLTAGE_NOW, /**< USB INPUT VOLTAGE uV >*/
    USB_POWER_SUPPLY_VOLTAGE_MAX, /**< max output voltage of attached usb, uV>*/
    USB_POWER_SUPPLY_CURRENT_NOW, /**< INPUT CURRENT READ FROM adc>*/
    USB_POWER_SUPPLY_CURRENT_MAX, /**< AICL settled current uA >*/
    USB_POWER_SUPPLY_INPUT_CURRENT_LIMIT, /**< max current for input current in uA, 0 to suspend, 0xFFFFFFFF to unspsend>*/
    USB_POWER_SUPPLY_CHARGER_TYPE,  /**< CHARGER TYPE 0 - unkonw, 1 - usb >*/
    USB_POWER_SUPPLY_USB_TYPE,  /**< usb type, 0 - unkonw, 1 - usb_sdp, 2 - dcp, 3 cdp, 4- ACA, 5- typeC, 6-PD, 7, PD-DRP, 8, PD-PPS, 9 - Apple >*/
    USB_POWER_SUPPLY_MOISTURE_DETECTION_ENABLE, /**< set, enable/disable moisture detection >*/
    USB_POWER_SUPPLY_MOISTURE_DETECTION_STATUS, /**< get moisture detection result 0 - not detected, 1 - detected >*/
    USB_POWER_SUPPLY_PROPERTIES_MAX
  }usb_power_supply_properties_type_e;
/**
@}
*/

  typedef enum
  {
    DC_POWER_SUPPLY_ONLINE,     /**< 0 - offline; 1- online >*/
    DC_POWER_SUPPLY_VOLTAGE_NOW, /**< DC INPUT VOLTAGE uV >*/
    DC_POWER_SUPPLY_VOLTAGE_MAX, /**< max output voltage of DC input, uV>*/
    DC_POWER_SUPPLY_CURRENT_NOW, /**< wireless output current in uA>*/
    DC_POWER_SUPPLY_CURRENT_MAX, /**< Requested wireless output current uA >*/
    DC_POWER_SUPPLY_CHARGER_TYPE,  /**< CHARGER TYPE 0 - unkonw, 2 - DC, 3 - wireless >*/
    DC_POWER_SUPPLY_BOOST_EN,     /**< enable/disable boost for wireless tx 0 - disable, 1 - enable >*/
    DC_POWER_SUPPLY_HBST_VMAX,   /**< charger FW to notify HBST Vmax . */
    DC_POWER_SUPPLY_PROPERTIES_MAX
  }dc_power_supply_properties_type_e;
  /**
  @}
  */
 
/** @addtogroup power_supply_charging_status_type_e
@{
*/
/**< 0-unknown (default), 1-charging (any charging, pre,trickle, taper fullon), 2-discharging (no input), 3-not charging (paused, disable charging), 4-full (terminated, inhibited)>*/
typedef enum {
  POWER_SUPPLY_CHARGING_STATUS_UNKNOWN, 
  POWER_SUPPLY_CHARGING_STATUS_CHARGING,
  POWER_SUPPLY_CHARGING_STATUS_DISCHARGING,
  POWER_SUPPLY_CHARGING_STATUS_NOT_CHARGING,
  POWER_SUPPLY_CHARGING_STATUS_FULL
}power_supply_charging_status_type_e;
/**
@}
*/

/** @addtogroup power_supply_health_type_e
@{
*/
/**< Jeita + overvoltage,  0-unknown, 1-good, 2-overheat, 3-hot, 4-overvoltage, 5-cool, 6 - cold >*/
typedef enum {
  POWER_SUPPLY_HEALTH_UNKNOWN,
  POWER_SUPPLY_HEALTH_GOOD,
  POWER_SUPPLY_HEALTH_TOO_HOT,
  POWER_SUPPLY_HEALTH_HOT,
  POWER_SUPPLY_HEALTH_BATT_OV,
  POWER_SUPPLY_HEALTH_COLD,
  POWER_SUPPLY_HEALTH_TOO_COLD
}power_supply_health_type_e;
/**
@}
*/


/** @addtogroup power_supply_charging_state_type_e
@{
*/
/**<  charging state, 0 - unknown, 1- none, 2 - trickle, 3 - fast, 4 - taper >*/
typedef enum {
  POWER_SUPPLY_CHARGING_STATE_UNKNOWN,
  POWER_SUPPLY_CHARGING_STATE_NONE,
  POWER_SUPPLY_CHARGING_STATE_TRICKLE,
  POWER_SUPPLY_CHARGING_STATE_FAST,
  POWER_SUPPLY_CHARGING_STATE_TAPER
}power_supply_charging_state_type_e;
/**
@}
*/


/** @addtogroup power_supply_batt_tech_type_e
@{
*/
/**< battery technology: 0 - unknown, 1 - NiMh, 2 - Li-ion, 3- LiPO, 4 - Li-Fe, 5 - Ni-Cd, 6 - LiMn>*/
typedef enum {
  POWER_SUPPLY_BATT_TECH_UNKNOWN,
  POWER_SUPPLY_BATT_TECH_NIMH,
  POWER_SUPPLY_BATT_TECH_LIION,
  POWER_SUPPLY_BATT_TECH_LIPO,
  POWER_SUPPLY_BATT_TECH_LIFE,
  POWER_SUPPLY_BATT_TECH_NICD,
  POWER_SUPPLY_BATT_TECH_LIMN
}power_supply_batt_tech_type_e;
/**
@}
*/

/** @addtogroup power_supply_charger_type_e
@{
*/
/**< CHARGER TYPE 0 - unkonw, 1 - usb, 2 - DC, 3 - wireless >*/
typedef enum {
  POWER_SUPPLY_CHARGER_TYPE_UNKNOWN,
  POWER_SUPPLY_CHARGER_TYPE_USB,
  POWER_SUPPLY_CHARGER_TYPE_DC,
  POWER_SUPPLY_CHARGER_TYPE_WIRELESS
}power_supply_charger_type_e;
/**
@}
*/

/** @addtogroup power_supply_usb_type_e
@{
*/
/**< usb type, 0 - unkonw, 1 - usb_sdp, 2 - dcp, 3 cdp, 4- ACA, 5- typeC, 6-PD, 7, PD-DRP, 8, PD-PPS, 9 - Apple >*/
typedef enum {
  POWER_SUPPLY_USB_TYPE_UNKNOWN,
  POWER_SUPPLY_USB_TYPE_SDP,
  POWER_SUPPLY_USB_TYPE_DCP,
  POWER_SUPPLY_USB_TYPE_CDP,
  POWER_SUPPLY_USB_TYPE_ACA,
  POWER_SUPPLY_USB_TYPE_TYPEC,
  POWER_SUPPLY_USB_TYPE_PD,
  POWER_SUPPLY_USB_TYPE_PD_DRP,
  POWER_SUPPLY_USB_TYPE_PD_PPS,
  POWER_SUPPLY_USB_TYPE_APPLE
}power_supply_usb_type_e;
/**
@}
*/

#ifdef __cplusplus
}
#endif
#endif

