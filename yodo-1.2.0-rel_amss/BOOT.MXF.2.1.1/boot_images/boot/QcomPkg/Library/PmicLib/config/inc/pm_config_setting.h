
#ifndef __PM_CONFIG_SETTING_H__
#define __PM_CONFIG_SETTING_H__

/*! \file pm_config_setting.h
*  \n
*  \brief This file contains target specific PMIC setting initialization APIs common across processors.
*  \n
*  \n &copy; Copyright 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.


$Header: //components/dev/core.boot/6.1/dvaddem.core.boot.6.1.config_part2/QcomPkg/Library/PmicLib/config/inc/pm_config_setting.h#1 $
$Author: dvaddem $
$DateTime: 2022/04/14 10:46:25 $
when            who         what, where, why
--------        ---         ---------------------------------------------------------
04/11/2022      dvaddem     Creating: Header file with APIs to initalize the settings
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "com_dtypes.h"
#include "pm_prop_ids.h"
#include "pm_err_flags.h"

/* ==========================================================================

		          Function Definitions

==============================================================================*/

/*! \brief This function gets the common config data
 *  \param[in/out] common_config_data: The common config data from the 
 *                                     target file is saved in this parameter.
 *  \param[in/out] common_config_data_size: The common config data size from 
 *                                          the target file is saved in this parameter.
 *
 *  \return Error flag.
 *
 *  <b>Dependencies</b>
 *  \li None
 */
pm_err_flag_type
pm_config_common_data( pm_config_data_kvp **common_config_data, 
                       uint32 *common_config_data_size);
					   

/*! \brief This function gets the Lock By bit setting data from pm_config_lock_bit.c
 *  \param[in/out] lock_by_bit_config_data: The Lock By Bit config data from the 
 *                                          pm_config_lock_bit.c file is saved in this parameter.
 *  \param[in/out] lock_by_bit_config_data_size: The Lock By Bit config data size from 
 *                                               the pm_config_lock_bit.c file is saved in this parameter.
 *
 *  \return Error flag.
 *
 *  <b>Dependencies</b>
 *  \li None
 */
pm_err_flag_type
pm_config_lock_by_bit_data( pm_config_data_kvp **lock_by_bit_config_data, 
                            uint32 *lock_by_bit_config_data_size);



/*! \brief This function gets the SPMI config data from pm_config_spmi.c
 *  \param[in/out] spmi_config_data: The SPMI config data from the 
 *                                   pm_config_spmi.c file is saved in this parameter.
 *  \param[in/out] spmi_config_data_size: The SPMI config data size from 
 *                                        the pm_config_spmi.c file is saved in this parameter.
 *
 *  \return Error flag.
 *
 *  <b>Dependencies</b>
 *  \li None
 */
pm_err_flag_type
pm_config_spmi_data( pm_config_data_kvp **spmi_config_data, 
                     uint32 *spmi_config_data_size);



/*! \brief This function gets the ARB(PVC/MGPI) setting data from pm_pvc_config.c
 *  \param[in/out] arb_config_data: The ARB(PVC/MGPI) config data from the 
 *                                  pm_pvc_config.c file is saved in this parameter.
 *  \param[in/out] arb_config_data_size: The ARB(PVC/MGPI) config data size from 
 *                                       the pm_pvc_config.c file is saved in this parameter.
 *
 *  \return Error flag.
 *
 *  <b>Dependencies</b>
 *  \li None
 */
pm_err_flag_type
pm_config_arb_data( pm_config_data_kvp **arb_config_data, 
                    uint32 *arb_config_data_size);



/*! \brief This function gets the pam setting data from pm_config_pam.c
 *  \param[in/out] pam_config_data: The PAM config data from the 
 *                                  pm_config_pam.c file is saved in this parameter.
 *  \param[in/out] pam_config_data_size: The PAM config data size from 
 *                                       the pm_config_pam.c file is saved in this parameter.
 *
 *  \return Error flag.
 *
 *  <b>Dependencies</b>
 *  \li None
 */
pm_err_flag_type
pm_config_pam_data(  pm_config_data_kvp **pam_config_data, 
                            uint32 *pam_config_data_size);



/*! \brief This function populates the common settings into config data array
 *  \param[in/out] pm_config_data_arr: pointer to the array that holds all settings information.
 *  \param[in] config_data_size: Size of the config array.
 *                                  
 *  \return Error flag.
 *
 *  <b>Dependencies</b>
 *  \li None
 */
pm_err_flag_type
pm_config_common_populate_settings(void **pm_config_data_arr, uint32 config_data_size);



/*! \brief This function populates the image specific settings into config data array
 *  \param[in]: None 
 * 
 *  \return Error flag.
 *
 *  <b>Dependencies</b>
 *  \li None
 */
pm_err_flag_type
pm_config_img_settings_init ( void );

#endif // __PM_CONFIG_SETTING_H__
