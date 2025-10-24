/*
===========================================================================

FILE:         ddr_external_api.c

DESCRIPTION:  
  This is external APIs to support usage of SCALe sequences

  Copyright (c) 2014, 2017, 2020-2022 QUALCOMM Technologies Incorporated.  All Rights Reserved.  
  QUALCOMM Proprietary and Confidential. 
===========================================================================
                                EDIT HISTORY

================================================================================
when       who     what, where, why
--------   ---     -------------------------------------------------------------
02/16/21   mkma    Added boot mode support
08/04/17   naa     Added DDI interface support
03/29/17   kpa     Update xblconfig_read function parameters.
02/22/17   kpa     Update XBLCONFIG_ERR_NONE to XBLCONFIG_SUCCESS.
04/05/14   sr      Initial version.
================================================================================
*/

/*==============================================================================
                                  INCLUDES
==============================================================================*/
#include <string.h>
#include "ddr_common.h"
#include "ddr_drivers.h"
#include "ddi_drivers.h"
#include "seq_hwio.h"
#include "ddr_external.h"
#include "ddr_params.h"
#include "ClockBoot.h"
#include "ddr_target.h"
#include "busywait.h"
#include "ddr_hwio.h"
#include "XBLConfig.h"
#include "CoreVerify.h"
#include "DALSys.h"
#include "Target_cust.h"
#include "ddr_internal.h"
//#include "dcb.h"  //Missing
#include  "boot_error_if.h"
#include "boot_logger_if.h"
#include "crc.h"
#include "pm_smps.h"
#include "pm_ldo.h"
#include "boot_modes.h"
#include "ddr_sdi_log.h"

/*==============================================================================
                                  MACROS
==============================================================================*/
#define MAX_AVAILABLE_TEMP_TRAINING_BUFFER ( 64 * 1024 ) /* 100kb */
#define DCB_NAME_BUF_LEN_MAX 22

/*==============================================================================
                                  DATA
==============================================================================*/
/* reserve 20kb for training data */
static uint32 training_data_offset = 20 * 1024;

/* starting from offset of 0 for extended training log */
static uint32 training_log_offset_size = 0; 
extern boot_mode_type g_boot_mode;
/*==============================================================================
                                  ASSEMBLY
==============================================================================*/
boolean DDR_SetBIMCSpeed(uint32 nFreqKHz );
uint32 DDR_GetFreqInKhz();

/*==============================================================================
                                  FUNCTIONS
==============================================================================*/
void sbl1_save_ddr_training_data_to_partition
(
  uint8* ddr_training_data_ptr,
  uint32 ddr_training_data_size,
  uint32 ddr_training_data_offset
);

void sbl1_save_data_to_ddr_partition
(
  uint8* ddr_partition_data_ptr,
  uint32 ddr_partition_data_size,
  uint32 ddr_partition_data_offset
);

/* ============================================================================
**  Function : ddr_external_set_clk_speed
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to set the clock speed
*   
*   @details
*   This api will set the clock speed accordingly as specified in the parameter to this function
*   
*   @param 
*   @param clk_in_khz       -  [IN] clock speed in khz 
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_external_set_clk_speed(uint8 clk_inx)
{
  DDR_SetBIMCSpeed(ddr_driver_struct->aop_params->mc_states[clk_inx].freq_khz);
  return;
}

/* ============================================================================
**  Function : ddr_external_get_clk_speed
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to get current clock speed
*   
*   @details
*   This api will read the clock speed accordingly as specified in the parameter to this function
*   
*   @param 
*   @None
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  DDR clock value
*   
*   @sa None
*/


uint32 ddr_external_get_clk_speed(void)
{
  return DDR_GetFreqInKhz();
}


/* ============================================================================
**  Function : ddr_external_get_time
** ============================================================================
*/
/*!
* 
* @brief
*  Returns a timestamp which is the current absolute time since bootup
*  subtracts the reference time.
*   
* @retval
*    Current time in microseconds. 
*    LOG_TIMESTAMP_OVERFLOW if timestamp overflows
* 
* @par Side Effects
*   None
* 
*/

uint32 ddr_external_get_time()
{
  return boot_log_get_time();
}


/* ============================================================================
**  Function : ddr_external_get_dsf_config_buffer
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to get an intermediate buffer
*   
*   @details
*   This function is called by external library to get an intermediate buffer
*   for reading DDR config blob values into
*   
*   @param 
*   @param buffer             -  [IN/OUT] uint32 ** buffer where we will populate 
*                                                   with pointer to buffer
*   @param size               -  [IN] uint32  Passed by DSF
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_external_get_dsf_config_buffer(void **buffer, uint32 size)
{
  *buffer = (void *)(SCL_SBL1_DDR_DSF_CFG_BUF_BASE);
  if (size > SCL_SBL1_DDR_DSF_CFG_BUF_SIZE)
    return;
  memset(*buffer, 0, size);
  return;
}

/* ============================================================================
**  Function : ddr_external_get_dcb
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to read a config item from XBL Config
*   
*   @details
*   This api will read data of given size, starting at given offset into a given buffer
*   
*   @param 
*   @param handle       -  [IN]      Config item handle
*   @param offset       -  [IN]      Offset from data is to be read
*   @param size         -  [IN]      Size of data to be read
*   @param buffer       -  [IN/OUT]  Buffer in which data is read
*   
*   @par Dependencies
*   Should have called ddr_external_dsf_config_open first to receive the config item handle
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/
boolean ddr_external_get_dcb (void *buffer, size_t size, char *dcb_name)
{
  uintnt dcb_handle = 0;
  uint32 dcb_size = 0;
  CORE_VERIFY(xblconfig_open(dcb_name, (uint32 *)&dcb_handle, &dcb_size) == XBLCONFIG_SUCCESS);
  CORE_VERIFY(xblconfig_read(dcb_handle, 0, dcb_size, buffer) == XBLCONFIG_SUCCESS);
  CORE_VERIFY(xblconfig_close(dcb_handle) == XBLCONFIG_SUCCESS);
  return TRUE; 
}
/* ============================================================================
**  Function : ddr_external_get_buffer
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to get a buffer for training
*   intermediate data
*   
*   @details
*   This function is called by external library to get a buffer for training
*   intermediate data
*   
*   @param 
*   @param buffer             -  [IN/OUT] uint32 ** buffer where we will populate 
*                                                   with pointer to buffer
*   @param size               -  [IN] uint32 *  we will populate with size of 
*                                                   buffer
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  boolean
*   reutrn operation success\failure
*   
*   @sa None
*/
boolean ddr_external_get_buffer( void ** buffer, uint32 *size )
{
  *buffer = (void *)(INTERMEDIATE_TRAINING_BUF); 
  if ( *size > MAX_AVAILABLE_TEMP_TRAINING_BUFFER )
	  return FALSE ;
  memset(*buffer, 0, *size);
  return TRUE;
}

/* ============================================================================
**  Function : ddr_external_page_to_storage
** ============================================================================
*/
/*!
*   @brief
*   This function is called by external library to save ddr training logs to 
* 	external non-volatile storage
*   
*   @details
*   This function is called by external library to save ddr training logs to 
* 	external non-volatile storage. This api has to take care of offsets for 
* 	saving to external storage so we do not run out of space.
*   api will perform a memset 0 on input buffer of input size before returning
*   
*   @param 
*   @param buffer             -  [IN] uint32 * buffer where traiing logs are located
*   @param size               -  [IN] uint32  size of data in buffer
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  void
*
*   
*   @sa None
*/
void ddr_external_page_to_storage( void * buffer, uint32 size )
{
	if(g_boot_mode !=  BOOT_MODE_RAMDUMP) //if(PcdGet32 (PcdBuildType) != 5)
	{
		if(buffer != NULL)
		{
			if( size != 0 && 
			(size+training_log_offset_size+training_data_offset) < DDR_MAX_LOG_SIZE)
			{
				/* call sbl1 function to save into flash storage */
				sbl1_save_ddr_training_data_to_partition(buffer, 
													   size, 
													   training_log_offset_size + training_data_offset);	

				/* increment offset for next page*/
				training_log_offset_size += size;

				/* check to see if offset is 1k aligned, if not we need to pad it */
				if(training_log_offset_size%1024 != 0)
				{
					/* divide by 1024 (round down divide), add 1 to the result and multiply by
					 * 1024 again to get the rounded up to 1k align size
					 * this is equivalent operation of doing a round up divide by 1024 then 
					 * multiply by 1024 again
					 */
					training_log_offset_size =  ((training_log_offset_size/1024)+1) * 1024;
				}
			}

			/* zero initialize buffer regardless  */
			memset(buffer, 0, size);
		}
	
	
	}
	else
	{
	 /* zero initialize buffer   */
		memset(buffer, 0, size);
	
	}

 
}

/* ============================================================================
**  Function : ddr_external_get_training_log_size
** ============================================================================
*/
/*!
*   @brief
*   This function is used to return the current stored training log size
*   
*   @details
*   This function is used to return the current stored training log size
*   
*   @param 
*   None
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  uint32
*   size of current trainig log saved to emmc
*   
*   @sa None
*/
uint32 ddr_external_get_training_log_size(void)
{
  return training_log_offset_size;
}

boolean ddr_external_set_ddrss_cfg_clk(boolean on_off)
{
/* Clock_EnableClock & Clock_DisableClock APIs are not 
   supported in SBL1 and only supported on RPM */ 
   return TRUE;
}

void seq_wait(uint32 time_value, SEQ_TimeUnit time_unit)
  {

    if(time_unit == SEC)
    {
       busywait(time_value * 1000 * 1000);
    }
    else if(time_unit == MS)
    {
       busywait(time_value * 1000);
    }
    else if(time_unit == US)
    {
       busywait(time_value);
    }
    else
    {
       /* time_unit == NS */
       busywait(time_value / 1000);
    }

}

/* ============================================================================
**  Function : ddr_send_data_to_ddi
** ============================================================================
*/
/*!
*   @brief
*   This function is called during training to pass training results to ddi
*   
*   @details
*   This function is called during training to pass training results to ddi
*   
*   @param 
*   @param flag             -  [IN] boolean flag to enable/disable IO clamps
*   
*   @par Dependencies
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void ddr_send_data_to_ddi(void * buffer, uint32 size, ddr_training_args* tArgs)
{ 
  // sendDatatoDDI(buffer, size, (ddr_training_args *)tArgs, training_params_ptr); 
} 
void copy_ddrinfo_to_ocimem(void)
{
  memscpy((void*)SDI_DDR_IMEM_START_ADDR, sizeof(ddr_shared_data->ddr_abort_info), &ddr_shared_data->ddr_abort_info, sizeof(ddr_shared_data->ddr_abort_info));
  memscpy((void*)SDI_DDR_IMEM_START_ADDR+sizeof(ddr_shared_data->ddr_abort_info), sizeof(ddr_shared_data->device_params), &ddr_shared_data->device_params, sizeof(ddr_shared_data->device_params));
  memscpy((void*)SDI_DDR_IMEM_START_ADDR+sizeof(ddr_shared_data->ddr_abort_info)+sizeof(ddr_shared_data->device_params), sizeof(ddr_driver_struct->ddr_regions_info), &ddr_driver_struct->ddr_regions_info, sizeof(ddr_driver_struct->ddr_regions_info));
  memscpy((void*)SDI_DDR_IMEM_START_ADDR+sizeof(ddr_shared_data->ddr_abort_info)+sizeof(ddr_shared_data->device_params)+sizeof(ddr_driver_struct->ddr_regions_info), sizeof(ddr_shared_data->dsf_code_version), &ddr_shared_data->dsf_code_version, sizeof(ddr_shared_data->dsf_code_version));
}

void copy_ddr_abortinfo_to_ocimem(void)
{
  memscpy((void*)SDI_DDR_IMEM_START_ADDR, sizeof(ddr_shared_data->ddr_abort_info), &ddr_shared_data->ddr_abort_info, sizeof(ddr_shared_data->ddr_abort_info));
}

void ddr_abort(void)
{
  /* force assert boot error */
  BL_VERIFY(0,BL_ERR_CORE_VERIFY);
}

uint32 ddr_get_fuse_value(uint32 addr)
{
  if(addr > (QFPROM_CORR_REG_BASE_SIZE - 4))
  {
     ddr_abort();
  }
  return in_dword(QFPROM_CORR_REG_BASE + addr);
}

void ddr_external_memscpy(void *dest, size_t dst_size, const void *src, size_t copy_size)
{
  memscpy(dest, dst_size, src, copy_size);
}

void ddr_external_snprintf(char* str, size_t size, const char* format, va_list vargs)
{
    //va_list vargs;
    //va_start(vargs, format);
    vsnprintf(str, size, format, vargs);
    //va_end(vargs); 
}

void ddr_external_memset(void* dst_ptr, int val, size_t len)
{
    memset(dst_ptr,val,len);
}

int ddr_external_strncmp(const char* str1, const char *str2, size_t len)
{
    return strncmp(str1,str2,len);
}

uint32 ddr_external_get_checksum(uint8  *buf_ptr, uint16  len, uint32  seed)
{
    return crc_32_calc(buf_ptr, len, seed);
}

boolean ddr_get_tsens_temp(uint32 *temp_deg_c)
{
	uint32 temp_deg = -1;
	boolean status = FALSE;
	status = get_ddr_temperature(&temp_deg);
	*temp_deg_c = temp_deg;
	return status;
}


boolean ddr_external_get_regulator_voltage(const char *regulator, uint32 *voltage)
{
    size_t length;
    char first;
    char last;
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    uint8 peripheral_index = 0, pmic_chip = 0;
    pm_volt_level_type pm_volt_level = 0;
    
    /*Check the length of the string*/
    length = strlen(regulator);
    if((length < 3) || (length > 4))
    {
        return FALSE;
    }
    
    pmic_chip = regulator[length - 1] - 'A';

    first = regulator[1];
    if((first < '0') || (first > '9'))
    {
        return FALSE;
    }
    
    if(length == 4)
    {    
       last = regulator[length - 2];
       if((last < '0') || (last > '9'))
       {
           return FALSE;
       }
    }
    
    peripheral_index = first - '0' - 1;
    if(length == 4)
    {
        peripheral_index *= 10;
        peripheral_index += last - '0';
    }

    if(regulator[0] == 'S')
    {
        err_flag = pm_smps_volt_level_status(pmic_chip,peripheral_index, &pm_volt_level);
        *voltage = pm_volt_level/1000;
    }
    else if(regulator[0] == 'L')
    {
        err_flag = pm_ldo_volt_level_status(pmic_chip,peripheral_index,&pm_volt_level);
        *voltage = pm_volt_level/1000;
    }
    else
    {
       *voltage = 0;
       return FALSE;
    }
    
    if(err_flag != PM_ERR_FLAG_SUCCESS)
    {
        *voltage = 0;
        return FALSE;
    }
    return TRUE;
}

#if defined FEATURE_BOOT_DDI_ENABLE

/* ============================================================================
**  Function : save_ddi_data2ddr_partition
** ============================================================================
*/
/*!
*   @brief
*   This function is called to save ddi output to ddr partition
*   
*   @param 
*   @param[in] ddi_data_ptr - Pointer to ddi data to be written to ddr partition
*   @param[in] ddi_data_size - size of ddi data to be written
*   @param[in] ddi_data_offset - offset from section
*   
*   @par Side Effects
*   None
*   
*   @retval  TRUE when data saved to the partition, otherwise FALSE
*   
*   @sa None
*/

boolean save_ddi_data2ddr_partition
(
  uint8* ddi_data_ptr,
  uint32 ddi_data_size,
  uint32 ddi_data_offset // START_IN_DDR + offset 
)
{
  uint32 startoffset=ddi_get_DDIpartition_offset();
  uint32 endoffset=startoffset+ddi_get_DDIpartition_size();
	
  if((startoffset + ddi_data_offset + ddi_data_size) <= endoffset)
  {
    sbl1_save_data_to_ddr_partition(ddi_data_ptr, ddi_data_size, startoffset + ddi_data_offset);
    return TRUE;
  }
  else
    return FALSE;
}

/* ============================================================================
**  Function : save_mr_data2ddr_partition
** ============================================================================
*/
/*!
*   @brief
*   This function is called to save mr data to ddr partition
*   
*   @param 
*   @param[in] ddi_data_ptr - Pointer to ddi data to be written to ddr partition
*   @param[in] ddi_data_size - size of ddi data to be written, should not exceed beyond 10K alloted for DDI
*   @param[in] ddi_data_offset - offset from section
*   
*   @par Side Effects
*   None
*   
*   @retval  TRUE when data saved to the partition, otherwise FALSE
*   
*   @sa None
*/

boolean save_mr_data2ddr_partition
(
  uint8* ddi_data_ptr,
  uint32 ddi_data_size,
  uint32 ddi_data_offset // START_IN_DDR + offset 
)
{
  uint32 startoffset=ddi_get_MRpartition_offset();
  uint32 endoffset=startoffset+ddi_get_MRpartition_size();
	
  if((startoffset + ddi_data_offset + ddi_data_size) <= endoffset)
  {
    sbl1_save_data_to_ddr_partition(ddi_data_ptr, ddi_data_size, startoffset + ddi_data_offset);
    return TRUE;
  }
  else
    return FALSE;
}


/* ============================================================================
**  Function : ddr_external_read_ddi_binary
** ============================================================================
*/
/*!
*   @brief
*   This function is called to read DDI binary from xbl_config partition
*   Read 1024 bytes of ddi data from offset 0x4800 (18 K) of xbl_config to dcb_buffer_ptr
*   Copy the last 8 bytes of DDI which is used for DDI test input to local variable test[2]
*   
*   @param None
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

void* ddr_external_read_ddi_binary(void)
{
  //size_t dcb_size = 0;
  void* ddi_buffer_ptr;

  /* Open dcb bin in xbl Config*/
  /*char dcb_name[DCB_NAME_BUF_LEN_MAX] = {0};

  // Generate DCB file name
  HAL_EXT_CORE_SW_snprintf(dcb_name, DCB_NAME_BUF_LEN_MAX, "/%04X_%04X_%01X_dcb.bin",
      ddr_shared_data->platform_id,
      (ddr_shared_data->chip_version & 0xFF00),
      ddr_shared_data->target_silicon);
  
  CORE_VERIFY(ddr_shared_data->dcb.ptr != NULL);
  ddr_external_get_dcb (ddr_shared_data->dcb.ptr, dcb_size, dcb_name);*/
  
  ddi_buffer_ptr = (void*)((size_t)(ddr_shared_data->dcb.ptr) + (*ddr_shared_data->dcb.ptr)[DDI_INPUT_IDX][0]);
  return ddi_buffer_ptr;
}


/* ============================================================================
**  Function : ddr_external_get_ddi_binary_size
** ============================================================================
*/
/*!
*   @brief
*   This function returns size of DDI DCB area
*   
*   @param None
*   
*   @par Side Effects
*   None
*   
*   @retval  None
*   
*   @sa None
*/

uint16 ddr_external_get_ddi_binary_size(void)
{
  return (*ddr_shared_data->dcb.ptr)[DDI_INPUT_IDX][1];
}

#endif //FEATURE_BOOT_DDI_ENABLE
