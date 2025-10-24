#ifndef __PM_SCHG_TYPEC_H__
#define __PM_SCHG_TYPEC_H__

/*! \file
*  \n
*  \brief  pm_schg_typec.h PMIC-SCHG MODULE RELATED DECLARATION 
*  \details  This header file contains functions and variable declarations 
*  to support Qualcomm PMIC SCHG (Switch-Mode Battery Charger) module. The 
*  Switched-Mode Battery Charger (SCHG) module includes a buck regulated 
*  battery charger with integrated switches. The SCHG module, along with the 
*  Over Voltage Proection (OVP) module will majorly be used by charger 
*  appliation for charging Li-Ion batteries with high current (up to 2A).
*  \n &copy; Copyright 2017-2021 QUALCOMM Technologies Inc, All Rights Reserved
*/

/* =======================================================================
                                Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when        who    what, where, why
--------    ---    ---------------------------------------------------------- 
05/14/18    ra     Support for Debug Accessory Mode
02/20/18    richaa Remove obsolete code.
10/19/17    richaa Initial version. 
========================================================================== */
#include "pm_chg.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/

typedef enum
{
  PM_SCHG_USB_TYPEC_VCONN_CONTROL_BY_HW,
  PM_SCHG_USB_TYPEC_VCONN_DISABLE_BY_SW,
  PM_SCHG_USB_TYPEC_VCONN_ENABLE_BY_SW = 0x03,
  PM_SCHG_USB_TYPEC_VCONN_INVALID
} pm_schg_usb_typec_vconn_enable_type;

/**  TYPEC VConn Current Limit **/
typedef enum
{
  PM_SCHG_USB_TYPEC_VCONN_ILIMIT_300MA,
  PM_SCHG_USB_TYPEC_VCONN_ILIMIT_500MA,
  PM_SCHG_USB_TYPEC_VCONN_ILIMIT_INVALID
} pm_schg_usb_typec_vconn_ilimit_type;

/** TYPEC VConn Soft Start Pull Down Current mA - SS_PD_IMA **/
typedef enum
{
  PM_SCHG_USB_TYPEC_VCONN_SS_PD_35MA,
  PM_SCHG_USB_TYPEC_VCONN_SS_PD_88MA,
  PM_SCHG_USB_TYPEC_VCONN_SS_PD_160MA,
  PM_SCHG_USB_TYPEC_VCONN_SS_PD_248MA,
  PM_SCHG_USB_TYPEC_VCONN_SS_PD_INVALID
} pm_schg_usb_typec_vconn_ss_pd_ima_type;

typedef enum
{
  PM_SCHG_USB_TYPEC_DAM_ICL_3A,
  PM_SCHG_USB_TYPEC_DAM_ICL_FMB
} pm_schg_usb_typec_dam_icl_sel;

/*===========================================================================

                 SCHG DRIVER FUNCTION PROTOTYPES

===========================================================================*/

/**
* @brief This function returns the USB type-C status
* 
* @param[in]   pmic_index:    The pmic_index of charger module.
* @param[out]  typec_status:  USB type c status type. Refer #pm_chg_typec_status_type for more info
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_usb_get_typec_status(uint32 pmic_index, pm_chg_typec_status_type *typec_status);

/**
 * @brief This function returns the USB type-C status
 *
 * @param[in] pmic_index:    The pmic_index of charger module.
 * @param[out] vbus_status:  True = VBUS is present.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *                                               version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_schg_usb_get_typec_vbus_status(uint32 pmic_index, boolean *vbus_status);

/**
* @brief This function enables vconn based on the input vconn source type
* 
* @param[in]  pmic_index:   The pmic_index of charger module.
* @param[in]  status_type:  VCONN source type. Refer #pm_schg_usb_typec_vconn_enable_type for more info
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_usb_typec_vconn_enable(uint32 pmic_index, pm_schg_usb_typec_vconn_enable_type enable_type);

/**
* @brief This function gets the TypeC port role as DRP/DFP/UFP
* 
* @param[in]   pmic_index: The pmic_index of charger module.
* @param[out]  port_role:  USB type c port role type. Refer #pm_chg_typec_port_role_type for more info
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_usb_typec_get_port_role(uint32 pmic_index, pm_chg_typec_port_role_type *port_role);

/**
* @brief This function sets the TypeC port role as DRP/DFP/UFP
* 
* @param[in]  pmic_index: The pmic_index of charger module.
* @param[in]  port_role:  USB type c port role type. Refer #pm_chg_typec_port_role_type for more info
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_usb_typec_set_port_role(uint32 pmic_index, pm_chg_typec_port_role_type port_role);

/**
* @brief This function disables the TYPE-C block
* 
* @param[in]  pmic_index: The pmic_index of charger module.
* @param[in]  disable:    FALSE = Do not disable TYPEC block,
*                         TRUE = Put TYPEC block in disable state 
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_usb_typec_disable(uint32 pmic_index, boolean disable);

/**
* @brief This function configures try sink mode
* 
* @param[in]  pmic_index: The pmic_index of charger module.
* @param[in]  enable:     enable/disable try sink mode
*
* @return  pm_err_flag_type 
*          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
*                                               version of the PMIC.
*          PM_ERR_FLAG_SUCCESS               = SUCCESS.
*
*/
pm_err_flag_type pm_schg_usb_typec_enable_try_sink_mode(uint32 pmic_index, boolean enable);

/**
 * @brief This function configures debug access sink mode
 *
 * @param[in] pmic_index:     The pmic_index of charger module.
 * @param[in] EnDbgAccessSnk: enable/disable debug access sink mode
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *                                               version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_schg_typec_en_dbg_access_snk(uint32 pmic_index, boolean EnDbgAccessSnk);

/**
 * @brief This function configures Factory Mode Boot(FMB) mode
 *
 * @param[in] pmic_index:  The pmic_index of charger module.
 * @param[in] EnFmb:       enable/disable Factory Mode Boot(FMB) mode.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *                                               version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_schg_typec_en_fmb(uint32 pmic_index, boolean EnFmb);

/**
 * @brief This function gets Debug Access Mode(dam) status.
 *
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[out] ConnectSts:  DAM status.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *                                               version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_schg_typec_get_dam_connect_sts(uint32 pmic_index, boolean *ConnectSts);

/**
 * @brief This function configures Debug Access Mode(dam) icl.
 *
 * @param[in] pmic_index:   The pmic_index of charger module.
 * @param[in] icl_sel:      Refer #pm_scpq_usb_typec_dam_icl_sel for details.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Feature not available on this
 *                                               version of the PMIC.
 *          PM_ERR_FLAG_SUCCESS               = SUCCESS.
 *
 */
pm_err_flag_type pm_schg_typec_set_dam_icl(uint32 pmic_index, pm_schg_usb_typec_dam_icl_sel icl_sel);

#endif /* __PM_SCHG_USB_H__ */
