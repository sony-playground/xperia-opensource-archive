/**
 * @file:  cprf.h
 * @brief:
 *
 * Copyright (c) 2016, 2019 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 */

#ifndef CPRF_H
#define CPRF_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#include "comdef.h"

typedef enum
{
    CPR_RETURN_SUCCESS = 0,
    CPR_RETURN_ERROR,
} cpr_return_status;

typedef enum cprf_enum_t
{
  CPRF_CX       =  0,               // SOC Logic
  CPRF_MX       =  1,               // SOC Memory
  CPRF_EBI      =  2,               // DDR Phy Analog
  CPRF_LCX      =  3,               // Sensors Island Logic
  CPRF_LMX      =  4,               // Sensors Island Memory
  CPRF_GFX      =  5,               // Graphics
  CPRF_MSS      =  6,               // Modem
  CPRF_MMCX     =  7,               // Multimedia CX
  CPRF_MXC      =  8,               // MxC
  CPRF_NSP      =  9,               // NSP
} cprf_enum_t;

/**
 * <!-- cpr_enable_controller -->
 *
 * @brief API to enable/disable CPR Controller.
 *
 * API to enable/disable the RBCPR controller associated with a rail.
 *
 * @param id     : CPRF id used to identify the controller
 *                 to be enabled/disabled.
 * @param enable : TRUE to enable, FALSE to disable the controller.
 *
 * @return CPR_SUCCESS or CPR_ERROR if the 'id' does not match
 *         a controller.
 */
cpr_return_status cpr_enable_controller(uint8 id, boolean enable);

/**
 * <!-- cpr_enable_controller_force -->
 *
 * @brief API to enable/disable CPR Controller.
 *
 * API to enable/disable the RBCPR controller associated with a rail.
 * Will toggle the controller irrespective of what mode the controller
 * was configured to at init.
 *
 * @param id     : CPRF id used to identify the controller
 *                 to be enabled/disabled.
 * @param enable : TRUE to enable, FALSE to disable the controller.
 *
 * @return CPR_SUCCESS or CPR_ERROR if the 'id' does not match
 *         a controller.
 */
cpr_return_status cpr_enable_controller_force(uint8 id, boolean enable);

/**
 * <!-- cpr_toggle_cprf_interface_en -->
 *
 * @brief API to toggle CPR Controller CPRF_INTERFACE_ENABLE bit.
 *
 * @param id     : CPRF id used to identify the controller
 *                 to be enabled/disabled.
 * @param enable : TRUE to assert, FALSE to de-assert cprf_interface_en
 * bit at the specified controller.
 *
 * @return CPR_SUCCESS or CPR_ERROR if the 'id' does not match
 * any of the rpmh managed (Closed-loop capable) rail's controller.
 */
cpr_return_status cpr_toggle_cprf_interface_en(uint8 id, boolean enable);

/**
 * <!-- cpr_toggle_ctrl_interaction_en -->
 *
 * @brief API to toggle CPRF's Controller Interaction Enable bit.
 *
 * @param id     : CPRF id used to identify the controller
 *                 to be enabled/disabled.
 * @param enable : TRUE to assert, FALSE to de-assert ctrl_interaction_en
 * bit at the specified CPRF.
 *
 * @return CPR_SUCCESS or CPR_ERROR if the 'id' does not match
 * any of the CPRF instances.
 */
cpr_return_status cpr_toggle_ctrl_interaction_en(uint8 id, boolean enable);

/**
 * <!-- cpr_get_ret_voltage -->
 *
 * @brief API to get the retention voltage of a given rail.
 *
 * @param id     : CPRF id used to identify the rail using the
 *                 rail whos retention voltage needs to be retrieved.
 * @return       : Retention Voltage of the rail. Returns SAFE_VOLTAGE which
 *                 is the same as VMAX and VMIN for Retention.
 */
uint32 cpr_get_ret_voltage (uint8 id);

/**
 * <!-- cpr_set_ret_voltage -->
 *
 * @brief API to set the retention voltage of a given rail.
 *
 * @param id     : CPRF id used to identify the rail using the
 *                 rail whos retention voltage needs to be set.
 *                 Voltage to set the retention level to for the given rail.
 * @return       : CPR_RETURN_SUCCESS on success.
 */

cpr_return_status cpr_set_ret_voltage (uint8 id, uint32 vol);

/**
 * <!-- cpr_get_ceiling_voltage -->
 *
 * @brief API to get the programmed ceiling voltage of a given rails corner.
 *
 * @param id     : CPRF id used to identify the rail using the
 *                 rail whos voltage needs to be retrieved.
 * @param hlvl   : hlvl of the corner whos voltage needs to be retrieved.
 * @param ceiling: Ceiling Voltage of the rail's corner.
 * @return       : CPR_RETURN_SUCCESS or CPR_RETRUN_ERROR
 */
cpr_return_status cpr_get_ceiling_voltage (uint8 id, uint16 hlvl, uint32 *ceiling);

/**
 * <!-- cpr_get_floor_voltage -->
 *
 * @brief API to get the programmed floor voltage of a given rails corner.
 *
 * @param id     : CPRF id used to identify the rail using the
 *                 rail whos voltage needs to be retrieved.
 * @param hlvl   : hlvl of the corner whos voltage needs to be retrieved.
 * @param floor  : Floor Voltage of the rail's corner.
 * @return       : CPR_RETURN_SUCCESS or CPR_RETRUN_ERROR
 */
cpr_return_status cpr_get_floor_voltage (uint8 id, uint16 hlvl, uint32 *floor);

/**
 * <!-- cpr_get_mol_voltage -->
 *
 * @brief API to get the mol voltage of a given rail.
 *
 * @param id     : CPRF id used to identify the rail using the
 *                 rail whos mol voltage needs to be retrieved.
 * @return       : Retention Voltage of the rail. Returns SAFE_VOLTAGE which
 *                 is the same as VMAX and VMIN for Retention.
 */
uint32 cpr_get_mol_voltage (uint8 id);

/**
 * <!-- cpr_get_mol_floor_voltage -->
 *
 * @brief API to get the floor mol voltage of a given rail.
 *
 * @param id     : CPRF id used to identify the rail using the
 *                 rail whos mol voltage needs to be retrieved.
 * @return       : Floor mol Voltage of the rail.  
 *                 Returns VMIN for that level.
 */
uint32 cpr_target_get_mol_floor_voltage (uint8 id);

/**
 * <!-- cpr_set_cprf_default_timeout
 *
 * @brief API to set the cprf timeout val
 *
 * @param id     : CPRF id used to identify the rail whos cprf
 *                 timeout value needs to be set to the recommended default.
 * @return       : CPR_RETURN_SUCCESS or CPR_RETURN_ERROR in case of error.
 */
cpr_return_status cpr_set_cprf_default_timeout (uint8 id);

/**
 * <!-- cpr_set_cprf_boost_timeout
 *
 * @brief API to set the cprf timeout val to the recommended boost value
 *
 * @param id     : CPRF id used to identify the rail whos cprf
 *                 timeout value needs to be set to the recommended boost val.
 * @return       : CPR_RETURN_SUCCESS or CPR_RETURN_ERROR in case of error.
 */
cpr_return_status cpr_set_cprf_boost_timeout (uint8 id);

/**
 * <!-- cpr_extra_init
 *
 * @brief API to set up any extra cpr initialization.
 *
 */
void cpr_extra_init (void);

/**
 * <!-- cpr_get_wlan_volt
 *
 * @brief API to query Wlan voltages.
 *
 */
uint32 cpr_get_wlan_volt(uint32 mode);

/**
 * <!-- cpr_target_cprf_debug_bus_logging
 *
 * @brief API to dump cprf debug bus data. 
 *
 */
void cpr_debug_bus_logging(void);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //CPRF_H
