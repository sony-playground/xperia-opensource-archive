#ifndef UFS_EYEMON_H
#define UFS_EYEMON_H
 /**********************************************************************
 * ufs_eyemon.h
 *
 * UFS EYEMON Header file
 *
 * Copyright (c) 2022
 * Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************

                             Edit History

when         who     what, where, why
----------   ---     --------------------------------------------------------------  
2022-04-18   jt      Initial version  
-----------------------------------------------------------------------------*/

/* UFS EYEMON Modes */
typedef enum
{
   UFS_EYEMON_DEVICE = 0, 
   UFS_EYEMON_HOST
} ufs_eyemon_mode;

/* UFS EYEMON Result Values */
typedef struct 
{
   uint8_t     error_count; 
   uint8_t     tested_count; 
} ufs_eyemon_result;

/* UFS EYEMON Capabilities */
typedef struct 
{
   uint8_t     eyemon_supported; 
   uint8_t     timing_max_steps; 
   uint8_t     timing_max_offset; 
   uint8_t     voltage_max_steps; 
   uint8_t     voltage_max_offset; 
} ufs_eyemon_caps;

/* UFS Device EYEMON Step Setting */
typedef struct 
{
   uint8_t    direction; 
   uint8_t    val; 
} ufs_eyemon_step_setting;  

/* UFS Device EYEMON Config Parameters*/
typedef struct 
{
   ufs_eyemon_step_setting   timing_steps; 
   ufs_eyemon_step_setting   voltage_steps; 
   uint8_t                   target_test_count; 
} ufs_eyemon_config; 

/** \details
 * This function gets the Eye Monitor capabilities. 
 *
 * @param[in] handle
 *    a pointer to the UFS handle that was returned from \ref ufs_open
 *
 * @param[in] mode
 *    Host or Device 
 *
 * @param[in] lane_num
 *    Lane 0 or 1
 *  
 * @param[out] caps
 *    Pointer to the Eye Monitor capabilities 
 *
 * @return 0 if successful.  Error code otherwise.
 */
int32_t ufs_eyemon_get_capabilities (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_caps *caps);

/** \details
 * This function enables the Eye Monitor.
 *
 * @param[in] handle
 *    a pointer to the UFS handle that was returned from \ref ufs_open
 *
 * @param[in] mode
 *    Host or Device 
 *
 * @param[in] lane_num
 *    Lane 0 or 1
 *  
 * @param[in] enable
 *    Enable or disable the Eye Monitor 
 *
 * @return 0 if successful.  Error code otherwise.
 */
int32_t ufs_eyemon_enable (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, boolean enable);

/** \details
 * This function sets the Eye Monitor configuration values.
 *
 * @param[in] handle
 *    a pointer to the UFS handle that was returned from \ref ufs_open
 *
 * @param[in] mode
 *    Host or Device 
 *
 * @param[in] lane_num
 *    Lane 0 or 1
 *  
 * @param[in] config
 *    a pointer to the configuration parameters 
 *
 * @return 0 if successful.  Error code otherwise.
 */
int32_t ufs_eyemon_set_config (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_config *config);

/** \details
 * This function gets the Eye Monitor result.
 *
 * @param[in] handle
 *    a pointer to the UFS handle that was returned from \ref ufs_open
 *
 * @param[in] mode
 *    Host or Device 
 *
 * @param[in] lane_num
 *    Lane 0 or 1
 *  
 * @param[out] result
 *    a pointer to the result (error/test count) 
 *
 * @return 0 if successful.  Error code otherwise.
 */
int32_t ufs_eyemon_get_result (struct ufs_handle *handle, ufs_eyemon_mode mode, uint8_t lane_num, ufs_eyemon_result *result);

/** \details
 * This function changes the power mode for Eye Monitor measurement. 
 *
 * @param[in] handle
 *    a pointer to the UFS handle that was returned from \ref ufs_open
 *
 * @param[in] gear
 *    High speed gear to switch to 
 *
 * @param[in] lanes
 *    Number of lanes 
 *
 * @param[in] adapt
 *    Enable adapt or not 
 *
 * @return 0 if successful.  Error code otherwise.
 */
int32_t ufs_eyemon_pm_change (struct ufs_handle *handle, uint8_t gear, uint8_t lanes, uint8_t adapt); 

/** \details
 * This function sets the coarse code for Host Side Eye Monitor measurement. 
 *
 * @param[in] handle
 *    a pointer to the UFS handle that was returned from \ref ufs_open
 *
 * @param[in] lane_num
 *    Lane 0 or 1
 *
 * @param[in] coarse_code
 *    Coarse Code value 
 *
 * @return 0 if successful.  Error code otherwise.
 */
int32_t ufs_eyemon_set_coarse_code (struct ufs_handle *handle, uint8_t lane_num, uint8_t coarse_code); 

#endif /* #ifndef UFS_EYEMON_H */

