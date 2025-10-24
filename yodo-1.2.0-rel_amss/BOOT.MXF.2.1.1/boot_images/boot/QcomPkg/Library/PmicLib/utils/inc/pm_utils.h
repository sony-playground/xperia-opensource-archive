#ifndef __PM_UTILS_H__
#define __PM_UTILS_H__

/*! \file
 *  
 *  \brief  pm_utils.h ----This file contain PMIC wrapper function of DALSYS_Malloc()
 *  \details his file contain PMIC wrapper function of DALSYS_Malloc()
 *  
 *    &copy; Copyright 2012-2022 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module over time.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/utils/inc/pm_utils.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/18/17   aab     Depricated pm_convert_time_to_timetick() and  pm_convert_timetick_to_time(), Since it assumes a fixed Clock speed 
12/05/17   aab     Added support to log total number of mem allocated
07/21/17   czq     Use Spare reg PON_PERPH_RB_SPARE instead of PON_DVDD_RB_SPARE
03/20/14   aab     Added pm_boot_adc_get_mv()
06/11/13   hs      Adding settling time for regulators.
06/20/12   hs      Created

===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/

#include "com_dtypes.h"
#include "pm_err_flags.h"
#include "DDIAdc.h"
#include "pm_version.h"
#include "DALSys.h"
#include "SpmiCfg.h"
#include "SpmiBus.h"


#define PON_PERPH_RB_SPARE_DEVICE_INIT_MASK      0x10   //PERPH SPARE 4 for device init 
#define PON_PERPH_RB_SPARE_DRIVER_INIT_MASK      0x20   //PERPH SPARE 5 for driver init 

 
#define PM_STATUS_MSG_LEN 300
#define PM_STATUS_MSG_HEAD_LEN 4


typedef struct
{
  uint8 pmic_index;
  uint8 pmic_model;
  uint8 reserve;
  uint8 revision;
} pm_pmic_info_type;

typedef struct
{
  uint32 pbus_log_version;
  uint32 pbus_log_sign;
  uint32 image_name;
} pm_pbus_logger_header_data_type;

typedef struct
{
  uint8 data0;
  uint16 data1;
  uint8 data2;
} pm_pbus_log_data_type;

typedef enum
{
  PM_ADC_PU_30K,
  PM_ADC_PU_100K,
  PM_ADC_PU_400K,
  PM_BATT_ID_PU_INVALID
} pm_adc_pull_up_type;

/*===========================================================================

                        FUNCTION PROTOTYPES

===========================================================================*/
/*extern */
void 
pm_malloc(uint32 dwSize, void **ppMem);

void
pm_free(void **pMem);

// Wrapper API to pet the watch dog
void 
pm_watch_dog_pet(void);

pm_err_flag_type 
pm_get_batt_therm_ohms(uint32 *ohms);


pm_err_flag_type
pm_busy_wait ( uint32 uS );

uint8
pm_utils_get_upper_idx(uint32 data_value, uint32 *data_list, uint8 list_count);

uint32 
pm_get_mem_allocated(void);


/*
 * @description: This function calculate ADC code for battery ID a given ID resistor value in the unit of ohm.
 *
 * @param type [in]: the pull up resistor type
 *        ohms [in]: the battery ID resistor which need to calculate ADC code
 *        code [out]: the adc code calculated for battery ID
 */
pm_err_flag_type
pm_get_adc_code_of_battery_id(pm_adc_pull_up_type type, uint32 ohms, uint32* code);

/* This API convert expected battery temperature to adc value which can be configured in afp thresholds */
pm_err_flag_type
pm_get_adc_code_of_battery_temp(pm_adc_pull_up_type type, int32 celsius, uint32* code);

/* This API convert expected adc code to batt temp */
pm_err_flag_type
pm_get_batt_temp_of_adc_code(pm_adc_pull_up_type type, uint32 code, int32* celsius);

/*This API configures the PMIC PS_HOLD register for normal shutdown and then drops the PS_HOLD low*/
pm_err_flag_type 
pm_device_shutdown(void);

//Check if the pm_driver_init is done
boolean 
pm_driver_init_status(void);

//check if pm_device_init is done
boolean 
pm_device_init_status(void);

uint32 
pm_get_img_type(void);

/*disable SPMI and PMIC interrupt*/
pm_err_flag_type 
pm_utils_irq_disable_clr_all(void);

/* slave ID is supported on the device or not */
boolean 
pm_is_slave_id_supported(uint8 slave_id);

boolean
pm_is_slave_id_supported_ex(uint32 bus_id, uint8 slave_id);

/** 
 * @name pm_get_pmic_info_ex 
 *  
 * @brief This function returns information about PMIC device 
 *        for a specific device index in the pmic_device_info
 *        argument. This API returns PMIC's model type value,
 *        All layer revision number and Metal revision number in
 *        pmic_device_info structure. Please refer to
 *        pm_device_info_type structure above for more info. For
 *        example, for PM8019 v2.1 the PMIC model type value is
 *        3 (since PM8019 model type value is 3 as per
 *        pm_model_type enum), All layer revision number is '2'
 *        and Metal revision number is '1'.
 * 
 * @param[in]  bus_id 
 * @param[in]  pmic_device_index.Primary PMIC:0 Secondary PMIC:1
 * @param[out] pmic_device_info:  
 *                Variable to return to the caller with PMIC
 *                device info. Please refer to
 *                pm_device_info_type structure above for more
 *                info on this structure.
 *
 * @return  pm_err_flag_type 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Error in
 *          collecting and placing PMIC info.
 *          PM_ERR_FLAG_SUCCESS = SUCCESS.
 *
 */

pm_err_flag_type 
pm_get_pmic_info_ex(uint32 bus_id, uint8 pmic_index, pm_device_info_type * pmic_device_info_ptr);

/** 
 * @name pm_get_pmic_model_ex 
 *  
 * @brief This function returns the PMIC's model type value with multiple bus support.
 *        For example, the API returns '1' for PM8941, '2'
 *        for PM8841 and so on. Please refer to pm_model_type
 *        enum above to get more info on which PMIC model type
 *        value represents which PMIC.
 * 
 * @param[in] bus_id 
 * @param[in] pmic_device_index.Primary PMIC:0 Secondary PMIC:1 
 *
 * @return  pm_model_type 
 *          Returns valid PMIC model/tier type if successful
 *          Returns PMIC_IS_INVALID under error conditions (like
 *          invalid device index param).
 *
 */
pm_model_type 
pm_get_pmic_model_ex(uint32 bus_id, uint8 pmic_device_index);

/*
 * Revoke SMMU access for UEFI accessible peripherals
 */
pm_err_flag_type
pm_revoke_channel_access(void);

pm_err_flag_type pm_utils_get_spmi_channels(SpmiCfg_ChannelCfg **spmi_cfg_ptr, uint32 *spmi_cfg_size);

void pm_utils_free_spmi_buffer();

void 
pm_utils_start_timer();

uint64 
pm_utils_get_time(char* func_name);

pm_err_flag_type
pm_utils_settings_validation_flag(uint8 *flag, boolean reset);

pm_err_flag_type
pm_utils_avg_spmi_tx_time();

#endif // __PM_UTILS_H__
