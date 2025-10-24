#ifndef __PM_PBS_INFO_H__
#define __PM_PBS_INFO_H__

/*! \file  pm_pbs_info.h
 *  
 *  \brief  This file contains the pmic PBS info driver definitions.
 *  \details  This file contains the pm_pbs_info_init & pm_pbs_info_store_glb_ctxt
 *  API definitions.
 *  
 *  &copy; Copyright 2018, 2021 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pbs/src/pm_pbs_info.h#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when         who     what, where, why
----------   ---     ---------------------------------------------------------- 
02/13/2017   al      Extending struct pm_pbs_info_data_type to store more PBS info
01/20/2017   akm     Added pm_pbs_ram_read_data(),  pm_pbs_ram_write_data() and refactored some functions
08/12/2016   akm     Added pm_pbs_header_info API
12/04/2015   aab     Updated pm_pbs_info_data_type 
04/29/2015   aab     Added support for PMK8001 
04/05/2013   kt      Created.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_target_information.h"
#include "pm_device.h"
#include "pm_pbs.h"

/*===========================================================================

                    MACRO AND GLOBAL VARIABLES

===========================================================================*/
/* PBS ROM/RAM Size can be 128 or 256 words. */
/* PBS OTP/ROM Start Address */
#define PM_PBS_ROM_BASE_ADDR            0x000
/* PBS RAM Start Address */
#define PM_PBS_RAM_BASE_ADDR            0x400

/* PBS Memory Version stored at the last line */
#define PM_PBS_MEMORY_VER_LINE_FROM_END   1
/* MFG Info stored at the 7th from last line (if present in PBS ROM) */
#define PM_PBS_ROM_INFO_LINE_FROM_END     7

#define PM_PBS_HEADER_SIZE                5
#define PBS_DATASET_INVALID_INDEX         0xFF

#define PM_PBS_HEADER_CHECKSUM          0x50425352

typedef enum
{
    PM_PBS_INFO_IN_OTP,
    PM_PBS_INFO_IN_PERIPH,
    PM_PBS_INFO_INVALID
} pm_pbs_info_place_holder_type;


typedef struct
{
    uint16 pbs_otp_start_addr;
    uint16 pbs_otp_mem_size;
    uint16 pbs_ram_start_addr;
    uint16 pbs_ram_mem_size;
    boolean skip_verify_supported;
    uint16 skip_verify_start;
    uint16 skip_verify_end;
    pm_pbs_info_place_holder_type pbs_info_place_holder;
    uint16 perph_base_addr;
    uint16 trim_num;
    uint16 tp_rev;
    uint16 fab_id;
    uint16 wafer_id;
    uint16 x_co_ordi;
    uint16 y_co_ordi;
    uint16 lot_id;
    uint16 mfg_id;
} pm_pbs_info_data_type;


/*===========================================================================

      Function Definitions

============================================================================*/
/** 
 * @name pm_pbs_info_rom_init 
 *  
 * @brief This function is called to initialize the PBS Info driver.
 *        This function internally validates the PBS Core peripheral
 *        info to determine the valid PMIC Chips and calls an internal
 *        helper function to read PBS Manufacturing IDs and foundry
 *        information such as PBS Lot ID, ROM Version,
 *        Fab Id, Wafer Id, X coord and Y coord and stores it in static
 *        global variable. This function is called during pm_device_init
 *        after the PBS RAM data is loaded.
 *  
 * @param None. 
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_SUCCESS = SUCCESS.           
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors 
 */
pm_err_flag_type pm_pbs_info_rom_init (void);


/** 
 * @name pm_pbs_info_ram_init 
 *  
 * @brief This function is called to initialize the PBS Info driver.
 *        This function internally validates the PBS Core peripheral
 *        info to determine the valid PMIC Chips and calls an internal
 *        helper function to read PBS Manufacturing IDs and foundry
 *        information such as  RAM Version and stores it in static
 *        global variable. This function is called during pm_device_init
 *        after the PBS RAM data is loaded.
 *  
 * @param None. 
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_SUCCESS = SUCCESS.           
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = PBS peripheral is not
 *          supported.
 *          else SPMI errors 
 */
pm_err_flag_type pm_pbs_info_ram_init (void);


/** 
 * @name pm_pbs_info_store_glb_ctxt 
 *  
 * @brief This function is called to copy the PBS info to Global
 *        Context (SMEM) from static global variables where the
 *        PBS info is stored during PBS Info initilization.
 *  
 * @param None. 
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_SUCCESS = SUCCESS. 
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = Error in
 *          copying to shared memory. 
 */
pm_err_flag_type pm_pbs_info_store_glb_ctxt (void);


/**
 * @name pm_pbs_mem_read_data
 *
 * @brief 
 *        This function is used to read data from PBS RAM 
 *
 * @param slave_id          - slave id of the PMIC 
 * @param start_address  - pointer to the start address of PBS RAM to read from
 * @param data_ptr         - pointer to the data to hold the read data
 * @param data_size        - size to the data to be read
 
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_SUCCESS = SUCCESS.
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = PBS peripheral is not  supported.
 *          else SPMI errors
 */
pm_err_flag_type pm_pbs_mem_read(uint8 slave_id, uint32 start_address, uint32* data_ptr, uint32 data_size);


/**
 * @name pm_pbs_mem_write_data
 *
 * @brief 
 *        This function is used to write data to PBS RAM 
 *
 * @param slave_id          - slave id of the PMIC 
 * @param start_address  - pointer to the start address of PBS RAM to write data
 * @param data_ptr         - pointer to the data to to be written to PBS RAM
 * @param data_size        - size to the data to be written
 
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_SUCCESS = SUCCESS.
 *          PM_ERR_FLAG_FEATURE_NOT_SUPPORTED = PBS peripheral is not  supported.
 *          else SPMI errors
 */
pm_err_flag_type pm_pbs_mem_write(uint8 slave_id, uint32 start_address, uint32* data_ptr, uint32 data_size);

#endif /* __PM_PBS_INFO_H__ */
