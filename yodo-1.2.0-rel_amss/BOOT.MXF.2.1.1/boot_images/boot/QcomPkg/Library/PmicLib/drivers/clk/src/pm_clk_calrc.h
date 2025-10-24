#ifndef __PM_CLK_CALRC_H__
#define __PM_CLK_CALRC_H__

/*! \file pm_clk_calrc.h
*  \n
*  \brief This header file contains functions and variable declarations
*         to support PMIC Clock peripheral.
*  \n
*  \n &copy; Copyright 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.


when        who         what, where, why
--------    ---         ----------------------------------------------------------
05/04/2021  dvaddem     CALRC is supported as a driver
========================================================================== */
/*===========================================================================

                        HEADER FILES

===========================================================================*/

#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "pm_resources_and_types.h"


/*===========================================================================

                        TYPE DEFINE AND ENUMS

===========================================================================*/

typedef enum 
{
  PM_COINCAP_TYPE_WEAK,
  PM_COINCAP_TYPE_STRONG,
  PM_COINCAP_TYPE_INVALID,
}pm_clk_calrc_coincap_type;


/*===========================================================================

                        API

===========================================================================*/

/**
* 
* @brief This API can be used to enable or disable the smpl
* @param pmic_index selects the pmic chip. Device index starts with zero
* @param enable_smpl takes PM_ON value to enable or PM_OFF to disable the smpl.
* 
* @return pm_err_flag_type PM_ERR_FLAG_SUCCESS if successful
*/
pm_err_flag_type 
pm_clk_calrc_smpl_enable(uint32 pmic_index, pm_on_off_type enable_smpl);

/**
* 
* @brief This API can be used to set the SMPL delay setting
* @param pmic_index Selects the pmic chip in which the buffers being controlled are located.
* @param delay_setting The delay value to set. 
* Available delays include 100ms, 200ms, 400ms, 800ms, 1600ms.
* 
* @return pm_err_flag_type PM_ERR_FLAG_SUCCESS if successful
*/
pm_err_flag_type 
pm_clk_calrc_set_smpl_delay(uint32 pmic_index, uint32 delay_setting);

/**
* 
* @brief This API can be used to enable or disable the sleep clock.
* @param pmic_index Selects the pmic chip. Device index starts with zero
* @param enable_calrc Takes PM_ON value to enable or PM_OFF to disable the CALRC.
* 
* @return pm_err_flag_type PM_ERR_FLAG_SUCCESS if successful
*/
pm_err_flag_type 
pm_clk_calrc_enable(uint32 pmic_index, pm_on_off_type enable_calrc);

/**
* 
* @brief This API can be used to enable or disable the coincell.
* @param pmic_index Selects the pmic chip. Device index starts with zero
* @param coincell_cap takes the config value from the enum.
* 
* @return pm_err_flag_type PM_ERR_FLAG_SUCCESS if successful
*/
pm_err_flag_type 
pm_clk_calrc_coincell_config(uint32 pmic_index, pm_clk_calrc_coincap_type coincell_cap);

#endif /* __PM_CLK_CALRC_H__ */
