/*! \file pm_pbus_log.c
*  \n
*  \brief This file contains the implementation of the API for PBS logger support.
*  \n
*  \n &copy; Copyright 2015-2019, 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pbs/src/pm_pbus_log.c#1 $

$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/17/16   akm     Created.
========================================================================== */

/*===========================================================================
INCLUDE FILES FOR MODULE
===========================================================================*/
#include <string.h>
#include "busywait.h"
#include "pmio_bus.h"
#include "pm_comm.h"
#include "pm_pbus.h"
#include "device_info.h"
#include "pm_utils.h"
#include "pm_log_utils.h"
#include "pm_config_target.h"
#include "hw_module_type.h"

/*===========================================================================
Type Definitions
===========================================================================*/

/**
  * 64 bit number.
  */
typedef struct int64_t
{
  uint8 dummy_c; // keep compiler happy
  union {
    uint8  c_array[8];
    uint64 int64_n;
    struct {
      uint32 lsb;
      uint32 msb;
    } int32_n;
  }int64_val;

} int64_type;


/*===========================================================================
Data Declarations
===========================================================================*/

#define PMIO_RTC_RW_SEC_ACCESS_ADDR              0x000060d0
#define PMIO_RTC_RW_TEST2_ADDR                   0x000060e3
#define PMIO_RTC_RW_TEST2_TS_ENABLE_BMSK         0x1
#define PMIO_RTC_RW_SEC_ACCESS_SEC_UNLOCK_BMSK   0xa5
#define REVID_PERPH_TYPE 0x104
#define PM_SIGNATURE 0x4D50
#define PM_BUS_PERPH_TYPE 0x404
#define PM_BUS_PERPH_SUBTYPE 0x405
#define PM_BUS_SUBTYPE_INTBUS_ARB_WITH_LOGGER 0x3
/*===========================================================================
Functions
===========================================================================*/

/**
 * @brief This function configures and captures the PBUS logger.
 *
 * @details
 *
 * @param[in/out] a pointer to a buffer that contains data from
 *        the PBUS logger in 64 bits format as below:
 *
 * @return
 * PM_ERR_FLAG_SUCCESS -- on success otherwise PMIC error code.
 */
pm_err_flag_type pm_pbus_logger
(
  uint8 device_index,
  pm_pbus_data_type* pbus_data_ptr
)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  uint8 buffer_size = 0;
  uint32 slave_id = 0;
  uint32 bus_id = 0;
  uint8 data = 0;
  uint32 i;
  uint8 reg_val = 0, log_count   = 0;

  err_flag = pm_version_detect();
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  /* Init pmic comm interface. */
  pm_comm_info_init();

  /* Get PMIC device Primary slave id */
  err_flag = pm_get_slave_id(device_index, 0, &slave_id);

  if (pm_is_slave_id_supported_ex(bus_id, slave_id) == FALSE)
  {
	 return PM_ERR_FLAG_INVALID_PARAMETER; 
  }

  err_flag = pm_comm_read_byte(slave_id, PM_BUS_PERPH_TYPE, &data);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
     return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  /* Check if the Bus peripheral Exists*/
  if(data != PM_HW_MODULE_INTERFACE )
  {
    return err_flag;
  }
  
  err_flag = pm_comm_read_byte(slave_id, PM_BUS_PERPH_SUBTYPE, &data);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
     return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  /* Check if the peripheral subtype has logger */
  if(data != PM_BUS_SUBTYPE_INTBUS_ARB_WITH_LOGGER )
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  /* Initialize PBUS logger */
  /*Read the buffer size*/
  err_flag = pm_comm_read_byte(slave_id, PMIO_BUS_FIFO_SIZE_ADDR, &buffer_size);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /*Configure logger control:  PERPH_FILTER=no,TIMESTAMP=Yes,log R&W,No Wrap */
  err_flag = pm_comm_write_byte(slave_id, PMIO_BUS_LOGGER_CTL_ADDR, 0x0);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  /* Wait for the logger */
  busywait(20);

   /* Disable  the logger */
  err_flag = pm_comm_write_byte(slave_id, PMIO_BUS_LOGGER_EN_ADDR, 0x0);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

   /* Set MEM logger address to 0. */
  err_flag = pm_comm_write_byte(slave_id, PMIO_BUS_MEM_INTF_ADDR_ADDR, 0x0);
   if (err_flag != PM_ERR_FLAG_SUCCESS)
   {
     return err_flag;
   }

  /* Enable the logger */
  err_flag = pm_comm_write_byte(slave_id, PMIO_BUS_LOGGER_EN_ADDR, 0x80);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }


  /* Start the logging. */


  /* Read status. */
  err_flag = pm_comm_read_byte(slave_id,PMIO_BUS_STATUS1_ADDR,&reg_val);
  if (err_flag)
  {
    return err_flag;
  }

  /* Read MEMPTR value. */
  err_flag = pm_comm_read_byte(slave_id,PMIO_BUS_MEM_INTF_ADDR_ADDR,&log_count);

  /* Check logger full.
  if (!(reg_val& PMIO_BUS_STATUS1_LOGGER_FULL_BMSK))
  {
    return PM_ERR_FLAG_BUS_ERR;
  }*/

  /* Disable the logger to read MEMPTR */
  err_flag = pm_comm_write_byte(slave_id, PMIO_BUS_LOGGER_EN_ADDR, 0x0);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Read MEMPTR value. */
  err_flag = pm_comm_read_byte(slave_id,PMIO_BUS_MEM_INTF_ADDR_ADDR,&log_count);

  /* Set MEM logger address to 0. */
  err_flag = pm_comm_write_byte(slave_id, PMIO_BUS_MEM_INTF_ADDR_ADDR, 0x0);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Trigger data to read and increment MEMPTR. */
  err_flag |= pm_comm_write_byte( slave_id, PMIO_BUS_CAPTURE_INC_ADDR, 0x1);

  for (i=0; i < buffer_size; i++)
  {

    /* Read from MEM_INTF_DATA0-7,. */
    err_flag |= pm_comm_read_byte_array( slave_id,
                                         PMIO_BUS_MEM_INTF_DATA0_ADDR, 
                                         8,
                                         &(pbus_data_ptr->data[8*i]));

    /* Trigger data to read and increment MEMPTR. */
    err_flag |= pm_comm_write_byte( slave_id, PMIO_BUS_CAPTURE_INC_ADDR, 0x1);

  }
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  return err_flag;

} /* pm_pbus_logger */


/** Disable logger for given pmic **/
pm_err_flag_type pm_pbus_logger_disable(uint8 pmic_index)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 slave_id = 0;
  err_flag = pm_get_slave_id(pmic_index, 0, &slave_id); // Get PMIC chip primary slave id
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
  	return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  err_flag = pm_comm_write_byte(slave_id, PMIO_BUS_LOGGER_EN_ADDR, 0x00);
  return err_flag;
}


/** Dump Pbus logger data for all pmics into global structure **/
pm_err_flag_type pm_pbus_logger_collect_data(pm_pbus_logger_data_type *pbus_log_table, boolean uart_print)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 pbus_log_reg_val = 0;
  uint8 pmic_index =0;
  uint8 pbus_read_data[8] = {0};
  uint8 log_count = 0;
  uint32 slave_id = 0;
  uint8 pbus_read_cnt = 0;
  uint8 pbus_buffer_max_trans = 0;
  uint32 total_log_count = 0;
  uint32 timestamp;
  pm_device_info_type pmic_device_info_s;
  char *master, *reg_opr;
  pm_model_type pmic_model;

  //Add signature to specify PBUS log has started
  pbus_log_table[total_log_count].val = 0xFF;
  pbus_log_table[total_log_count].regoffs = 0x4250 ;  //PBUS_LOG_SIGN
  pbus_log_table[total_log_count].opr = 0xFF;
  total_log_count++;
  
  for(uint8 bus_id = 0; bus_id < PM_MAX_BUSES_SUPPORTED; bus_id++)
  {
    for(pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
    {
    	pbus_log_table[total_log_count].val = 0xFF;
    	pbus_log_table[total_log_count].regoffs = PM_SIGNATURE; //PMIC_SIGN;
    	pbus_log_table[total_log_count].opr = 0xFF;
    	total_log_count++;

    	pmic_model = pm_get_pmic_model_ex(bus_id, pmic_index);
    	if(pmic_model == PMIC_IS_INVALID || pmic_model == PMIC_IS_UNKNOWN)
    	{
    	  pbus_log_table[total_log_count].val = 0xFF;
    	  pbus_log_table[total_log_count].regoffs = 0x00;
    	  pbus_log_table[total_log_count].opr = 0xFF;
    	  total_log_count++;
    	  continue;
    	}

    	err_flag = pm_get_slave_id_ex(bus_id, pmic_index, 0, &slave_id);
    	if (err_flag != PM_ERR_FLAG_SUCCESS)
    	{
    	  return err_flag;
    	}

    	//Dummy Read
    	pm_comm_read_byte_ex(bus_id, slave_id, REVID_PERPH_TYPE, &pbus_log_reg_val);

    	/* Read FIFO size. */
    	err_flag = pm_comm_read_byte_ex(bus_id, slave_id, PMIO_BUS_FIFO_SIZE_ADDR, &pbus_log_reg_val);
    	if (err_flag != PM_ERR_FLAG_SUCCESS)
    	{
    	  total_log_count++;
    	  continue;
    	}

    	//Set log size to max
    	pbus_buffer_max_trans = 0x40 << pbus_log_reg_val;
    	/* Read status. */
    	err_flag = pm_comm_read_byte_ex(bus_id, slave_id, PMIO_BUS_STATUS1_ADDR, &pbus_log_reg_val);
    	if (err_flag != PM_ERR_FLAG_SUCCESS)
    	{
    	  return err_flag;
    	}
    	/* Disable the logger to read MEMPTR */
    	err_flag = pm_comm_write_byte_ex(bus_id, slave_id, PMIO_BUS_LOGGER_EN_ADDR, 0x0);
    	if (err_flag != PM_ERR_FLAG_SUCCESS)
    	{
    	  return err_flag;
    	}
    	/* Read MEMPTR value. */
    	err_flag = pm_comm_read_byte_ex(bus_id, slave_id,PMIO_BUS_MEM_INTF_ADDR_ADDR, &log_count);
    	if (err_flag != PM_ERR_FLAG_SUCCESS)
    	{
    	  return err_flag;
    	}
    	/* Check logger full. if not, set the max log read to mem_ptr */
    	if (!(pbus_log_reg_val& PMIO_BUS_STATUS1_LOGGER_FULL_BMSK))
    	{
    	  pbus_buffer_max_trans = log_count;
    	}
    	/* Set MEM logger address to 0. */
    	err_flag = pm_comm_write_byte_ex(bus_id, slave_id, PMIO_BUS_MEM_INTF_ADDR_ADDR, 0x0);
    	if (err_flag != PM_ERR_FLAG_SUCCESS)
    	{
    	  return err_flag;
    	}

    	//Add PMIC Info in beginning of pbus dump
    	pbus_log_table[total_log_count].val = pmic_model;
    	pbus_log_table[total_log_count].regoffs = pbus_buffer_max_trans;
		pm_get_pmic_info_ex( bus_id, slave_id, &pmic_device_info_s);
    	pbus_log_table[total_log_count].opr = pmic_device_info_s.nPmicAllLayerRevision; // pm_get_pmic_revision(pmic_index);

    	total_log_count++;

    	for (pbus_read_cnt = 0; pbus_read_cnt < pbus_buffer_max_trans; pbus_read_cnt++)
    	{
    	  /* Trigger data to read and increment MEMPTR. */
    	  err_flag |= pm_comm_write_byte_ex( bus_id, slave_id, PMIO_BUS_CAPTURE_INC_ADDR, 0x1);

    	  /* Read from MEM_INTF_DATA0-7,. */
    	  err_flag |= pm_comm_read_byte_array_ex( bus_id, slave_id, PMIO_BUS_MEM_INTF_DATA0_ADDR, 8, pbus_read_data);

    	  if(uart_print)
    	  {
      		err_flag |= pm_comm_read_byte_ex(bus_id, slave_id, PMIO_BUS_LOGGER_CTL_ADDR, &pbus_log_reg_val);
      		master = (((pbus_read_data[3] << 2) & 0x1F) == 0x2)? "PBS" : "SPMI";
      		reg_opr = ((pbus_read_data[3] & 0x80) == 0x80) ? "Write" : "Read";
      		if((pbus_log_reg_val & 0x04) == 0x00)
      		{
      		  timestamp = (uint32)(pbus_read_data[7] <<24) | (pbus_read_data[6] <<16) | (pbus_read_data[5] <<8) | (pbus_read_data[4]);
      		  pm_log_message("0x%x: %s %s Addr:0x%05x Data:0x%02x ", timestamp, master, reg_opr, (pbus_read_data[2] <<8 | pbus_read_data [1]), pbus_read_data[0]);
      		}
      		else
      		{
      		  pm_log_message(" %s %s Addr:0x%05x Data:0x%02x ", master, reg_opr, (pbus_read_data[2] <<8 | pbus_read_data [1]), pbus_read_data[0]);
      		  master = (((pbus_read_data[7] << 2) & 0x1F) == 0x2)? "PBS" : "SPMI";
      		  reg_opr = ((pbus_read_data[7] & 0x80) == 0x80) ? "Write" : "Read";
      		  pm_log_message(" %s %s Addr:0x%05x Data:0x%02x ", master, reg_opr, (pbus_read_data[6] <<8 | pbus_read_data [5]), pbus_read_data[4]);
      		}
    	  }
    	  else
    	  {
      		/* Extract data  */
      		pbus_log_table[total_log_count].val = pbus_read_data[0];
      		pbus_log_table[total_log_count].regoffs = pbus_read_data[1] <<8 | pbus_read_data [2] ;
      		pbus_log_table[total_log_count].opr = pbus_read_data[3];
      		total_log_count++;

      		pbus_log_table[total_log_count].val = pbus_read_data[4];
      		pbus_log_table[total_log_count].regoffs = pbus_read_data[5] <<8 | pbus_read_data [6] ;
      		pbus_log_table[total_log_count].opr = pbus_read_data[7];
      		total_log_count++;

      		if(total_log_count > (PM_LOGGER_MAX_BUFFER_SIZE - 1 ))
      		{
      		  /*Terminate Log count if exceeds max buffer size */
      		  pbus_log_table[total_log_count].val = 0x46; //F- Buffer full
      		  pbus_log_table[total_log_count].regoffs = 0x4250; //PB
      		  pbus_log_table[total_log_count].opr = 0xFF;
      		  break;	//terminate log
      		}
    	  }
    	}
    }
  }
  
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    pbus_log_table[total_log_count].val = 0x45; //E - error
    pbus_log_table[total_log_count].regoffs = 0x4250; //PB
    pbus_log_table[total_log_count].opr = 0xFF;
    total_log_count++;
  }

  return PM_ERR_FLAG_SUCCESS;
}

