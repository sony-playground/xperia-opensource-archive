/*! \file  pm_pbs_info.c
 *  
 *  \brief  This file contains the pmic PBS info driver implementation.
 *  \details  This file contains the pm_pbs_info_init & pm_pbs_info_store_glb_ctxt
 *  API implementations.
 *  
 *  &copy; Copyright 2014 - 2022 QUALCOMM Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/PmicLib/drivers/pbs/src/pm_pbs_info.c#1 $
$Author: pwbldsvc $
$DateTime: 2022/08/18 10:15:46 $
when         who     what, where, why
----------   ---     ----------------------------------------------------------
05/17/17   czq     Read 9 byte lot_id in one call and optimize parse method.
02/10/17     al      Extend read PBS info from SMEM 
01/20/2017   akm     Updated PON reasons hist API
10/12/2016   akm     Added pm_get_pon_reasons, pm_get_pon_reasons_to_dump API
08/12/2016   akm     Added pm_pbs_header_info API
12/04/2015   aab     Updated  pm_pbs_info_otp_read() and  pm_pbs_info_ram_read() 
04/29/2015   aab     Added support for PMK8001 
07/16/2014   akm     Comm change Updates
11/20/2013   mr      Removed KW errors for Banned Functions API (CR-512648)
11/18/2013   kt      Added test pgm rev to pbs_info struct (increment struct format)
11/01/2013   plc     Update for Arm6 syntax ("attribute")
03/19/2013   kt      Added pm_pbs_info_add_ram_sequence API.
10/19/2012   umr     PBS Core Driver.
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES 

===========================================================================*/
#include "pm_pbs.h"
#include "pm_pbs_driver.h"
#include "pm_pbs_info.h"
#include "pm_version.h"
#include "DALGlbCtxt.h"
#include "CoreVerify.h"
#include "pm_config_sbl.h"
#include "pm_device.h"
#include "pm_log_utils.h"

/*===========================================================================

                        TYPE DEFINITIONS 

===========================================================================*/
#define DALGLBCTXT_LOCK_TYPE_SPINLOCK        0x010000

/* Format of the pm_pbs_info_smem_type structure */ 
#define PM_PBS_INFO_SMEM_FORMAT                4
#define PM_PBS_PON_RSN_SDAM_ADRESS_MASK        0xFFFF0000
#define PM_PBS_NUM_LOT_ID_RES                  9

#define PM_REV_ID_SLAVE_COUNT_ADDR             0x106
#define PM_REV_ID_OTP_ID_ADDR                  0x154
#define PM_REV_ID_TP_REV_ADDR                  0x1F1

#define MEM_INTF_RD_DATA0_OFFS         0x4C
#define PERIPH_TYPE_OFFSET_ADDR        0x04
#define MEM_INTF_WR_DATA0_OFFS         0x48
#define PERIPH_OFFSET                  0x100

#define PON_RSN_HIST_SIGNATURE                 0x5052534E //PRSN
#define PON_RSN_HIST_VERSION                   0X02
#define PON_RSN_HIST_START_SDAM_ADDR           0xB268

/** 
  @struct pm_pbs_info_smem_type
  @brief Structure for the shared memory location which is used
         to store PMIC PBS related information such as PBS Lot
         ID, ROM Version, RAM Version, Fab Id, Wafer Id, X
         coord, Y coord and Test PGM Rev. PBS ROM/RAM Revision
         id and Variant (or Branch) id are stored in last 16
         bits(upper and lower 8 bits) of rom_version and
         ram_version.
 */
typedef struct
{
  uint32         format;                           /* Starts from 1 and increments if we add more data */
  uint8          lot_id[PM_PBS_INFO_NUM_LOT_IDS];  /* PBS Lot Id */
  uint32         rom_version;                      /* PBS ROM Version number */
  uint32         ram_version;                      /* PBS RAM Version number */
  uint32         fab_id;                           /* PBS Fab Id */
  uint32         wafer_id;                         /* PBS Wafer Id */
  uint32         x_coord;                          /* PBS X Coord */
  uint32         y_coord;                          /* PBS Y Coord */
  uint32         test_pgm_rev;                     /* PBS Test PGM Rev */
  uint32         mfg_id;                  /* PBS MGF ID */
} pm_pbs_info_smem_type;

/** 
  @struct pm_pbs_info_glb_ctxt_type
  @brief Global context data structure for sharing the pbs info 
         across processors.
 */
typedef struct
{
  DALGLB_HEADER             dal_glb_header;
  pm_pbs_info_smem_type     pbs_info_glb_arr[PM_MAX_NUM_PMICS];
} pm_pbs_info_glb_ctxt_type;

//Global variable to Store PON reason History before PM device init 
static pm_pbs_pon_reason_history_data_type pon_reason_history;

/* Static global variables to store the pbs info */
static pm_pbs_info_smem_type pm_pbs_info_arr[PM_MAX_NUM_PMICS];

/* Flag to check if PBS Info driver is initialized */
static boolean pm_pbs_info_initialized = FALSE;

/* Pointer to the PBS_INFO_DATA Structure */
static pm_pbs_info_data_type *pm_pbs_data = NULL;

/* Pointer to the PBS RAM/ROM size and start address Structure */
static pm_pbs_info_data_type **pm_pbs_config_data = NULL;
   

/*==========================================================================

                FUNCTION DEFINITIONS

==========================================================================*/
/** 
 * @name pm_pbs_info_otp_read
 *  
 * @brief This is an internal helper function for reading
 *        PBS info for PBS Peripheral with 128/256 word ROM
 *        and RAM support. This function reads the PBS
 *        ROM/RAM addresses for PMIC PBS Manufacturing IDs
 *        and foundry information such as PBS Lot ID, ROM
 *        Version, RAM Version, Fab Id, Wafer Id, X coord
 *        and Y coord. This function internally calls
 *        pm_pbs_enable/disable_access to enable/disable
 *        PBS ROM/RAM access and pm_pbs_config_access to
 *        configure READ BURST mode access to PBS ROM/RAM.
 *  
 * @param[in]  slave_id. PMIC chip's slave id value.
 * @param[out] pbs_info_ptr: Variable to return to the caller with
 *             PBS info. Please refer to pm_pbs_info_smem_type structure
 *             above for more info on this structure.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_SUCCESS = SUCCESS.
 *          else SPMI ERROR.
 *  
 * @dependencies None.
 */
static pm_err_flag_type pm_pbs_info_otp_read (uint32 slave_id, pm_pbs_info_smem_type *pbs_info_ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 read_info_temp = 0;
  uint16 pbs_element_info_temp_addr = 0;  /* Address from where PBS Info to be read */
  uint8 lot_info_cnt = PM_PBS_INFO_NUM_LOT_IDS;
  uint8 lot_info_reg_reads_cnt = (PM_PBS_INFO_NUM_LOT_IDS/3);
  uint8 periph_id = (pm_pbs_data->perph_base_addr)/ PERIPH_OFFSET;
 
  pbs_info_ptr->format = PM_PBS_INFO_SMEM_FORMAT;

  /* Configuring the base address for reading PBS ROM info.
   * PM_PBS_INFO_ADDR = pm_pbs_data->pbs_otp_start_addr + 4 * [pm_pbs_data->pbs_otp_mem_size - 7];
   */
  
  pbs_element_info_temp_addr = pm_pbs_data->pbs_otp_start_addr + 4 * (pm_pbs_data->pbs_otp_mem_size - PM_PBS_ROM_INFO_LINE_FROM_END);

  err_flag = pm_pbs_config_access(slave_id, pbs_element_info_temp_addr, PM_PBS_ACCESS_READ_BURST, PM_PBS_TYPE_ROM, periph_id);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Reading the Fab id and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8*)&read_info_temp);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Masking the opcode and reserved bits from temp variable 
     storing the Fab id and TEST_PGM_REV in the pbs info struct */
  pbs_info_ptr->test_pgm_rev = (uint32)(read_info_temp & 0x000000FF);
  pbs_info_ptr->fab_id = (uint32)((read_info_temp>>8) & 0x000000FF);
  read_info_temp = 0;

  /* Reading the Wafer ID, X and Y coords and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8*)&read_info_temp);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Masking the opcode bits from temp variable storing the Wafer ID, X and
     Y coords along with the existing Fab ID in the pbs info struct */
  pbs_info_ptr->wafer_id = (uint32)(read_info_temp & 0x000000FF);
  pbs_info_ptr->x_coord = (uint32)((read_info_temp>>8) & 0x000000FF);
  pbs_info_ptr->y_coord = (uint32)((read_info_temp>>16) & 0x000000FF);
  read_info_temp = 0;

  /* Reading the LOT info and storing it in the pbs info struct */
  while((lot_info_reg_reads_cnt != 0) && (lot_info_cnt > 2))
  {
    /* Reading the LOT info and storing it in temp variable */
    err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8*)&read_info_temp);

    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }

    pbs_info_ptr->lot_id[--lot_info_cnt] = (uint8)(read_info_temp & 0x000000FF);
    pbs_info_ptr->lot_id[--lot_info_cnt] = (uint8)((read_info_temp >> 8) & 0x000000FF);
    pbs_info_ptr->lot_id[--lot_info_cnt] = (uint8)((read_info_temp >> 16) & 0x000000FF);

    read_info_temp = 0;

    lot_info_reg_reads_cnt--;
  }

  /* Reading the ROM version info and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8*)&read_info_temp);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Store the ROM version info in the PBS Info struct */
  pbs_info_ptr->rom_version = (uint32)(read_info_temp & 0x0000FFFF);
  read_info_temp = 0;


  /* Configuring to disable PBS core read access */
  err_flag = pm_pbs_disable_access(slave_id, PM_PBS_TYPE_ROM, periph_id);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  return err_flag;
}


/** 
 * @name pm_pbs_info_ram_read
 *  
 * @brief This is an internal helper function for reading
 *        PBS info for PBS Peripheral with 128/256 word 
 *        RAM support. This function reads the PBS
 *        RAM addresses for PMIC PBS Manufacturing IDs
 *        and foundry information such as PBS Lot ID, ROM
 *        Version, RAM Version, Fab Id, Wafer Id, X coord
 *        and Y coord. This function internally calls
 *        pm_pbs_enable/disable_access to enable/disable
 *        PBS RAM access and pm_pbs_config_access to
 *        configure READ BURST mode access to PBS ROM/RAM.
 *  
 * @param[in]  slave_id. PMIC chip's slave id value.
 * @param[out] pbs_info_ptr: Variable to return to the caller with
 *             PBS info. Please refer to pm_pbs_info_smem_type structure
 *             above for more info on this structure.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_SUCCESS = SUCCESS.
 *          else SPMI ERROR.
 *  
 * @dependencies None.
 */
static pm_err_flag_type pm_pbs_info_ram_read (uint32 slave_id, pm_pbs_info_smem_type *pbs_info_ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 read_info_temp = 0;
  uint16 pbs_element_info_temp_addr = 0;  /* Address from where PBS Info to be read */
  uint8 periph_id = (pm_pbs_data->perph_base_addr)/ PERIPH_OFFSET;

  pbs_info_ptr->format = PM_PBS_INFO_SMEM_FORMAT;

  /* Configuring the base address for reading PBS RAM version info */
  pbs_element_info_temp_addr = pm_pbs_data->pbs_ram_start_addr + 4 * (pm_pbs_data->pbs_ram_mem_size - PM_PBS_MEMORY_VER_LINE_FROM_END);

  err_flag = pm_pbs_config_access(slave_id, pbs_element_info_temp_addr, PM_PBS_ACCESS_READ_BURST, PM_PBS_TYPE_RAM, periph_id);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Reading the RAM version info and storing it in temp variable */
  err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8*)&read_info_temp);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  /* Store the RAM version info in the PBS Info struct */
  pbs_info_ptr->ram_version = (uint32)(read_info_temp & 0x0000FFFF);
  read_info_temp = 0;

  /* Configuring to disable PBS core read access */
  err_flag = pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);

  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }

  return err_flag;
}


/**
 * @name pm_pbs_info_read_from_periph
 *
 * @brief This is an internal helper function for reading
 *        PBS info for PBS Peripheral with 128/256 word OTP
 *        and RAM support. This function reads PMIC PBS
 *        Manufacturing IDs and foundry information such as
 *        PBS Lot ID, OTP Version, RAM Version, Fab Id,
 *        Wafer Id, X/Y coord from MISC or REV_ID Peripheral.
 *        This function internally calls
 *        pm_pbs_enable/disable_access to enable/disable PBS
 *        OTP/RAM access and pm_pbs_config_access to configure
 *        READ BURST mode access to PBS OTP/RAM.
 *
 * @param[in]  slave_id. PMIC chip's slave id value.
 * @param[out] pbs_info_ptr: Variable to return to the caller with
 *             PBS info. Please refer to pm_pbs_info_smem_type structure
 *             above for more info on this structure.
 *
 * @return  pm_err_flag_type
 *          PM_ERR_FLAG_SUCCESS = SUCCESS.
 *          else SPMI ERROR.
 *
 * @dependencies None.
 */


static pm_err_flag_type pm_pbs_info_read_from_periph (uint32 slave_id, pm_pbs_info_smem_type *pbs_info_ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 read_info_temp8 = 0; // i = 0;
  uint32 read_info_temp32 = 0;
  uint16 pbs_element_info_temp_addr = 0;  /* Address from where PBS Info to be read */
  uint16 lot_info_addr = 0;
  uint8 lot_arry[PM_PBS_NUM_LOT_ID_RES + 1] = {0}; //PM_PBS_NUM_LOT_ID_RES + 1 to avoid lot_ptr out of bounds
  uint8*  lot_ptr = lot_arry;
  int lot_info_cnt = 11;
  uint8 pmic_sid_count = 0;
  uint32 rev_id_data =0;
  uint8 periph_id = (pm_pbs_data->perph_base_addr)/ PERIPH_OFFSET;
  
  pbs_info_ptr->format = PM_PBS_INFO_SMEM_FORMAT;

  /* Retrieve place where MFG info stored */
  err_flag = pm_comm_read_byte(slave_id, PM_REV_ID_SLAVE_COUNT_ADDR, &pmic_sid_count);
  
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return err_flag;
  }
  
  if (pmic_sid_count != 1)
  {
    /* Reading the Test_PGM_Rev and storing it in temp variable */
    err_flag = pm_comm_read_byte(slave_id, pm_pbs_data->perph_base_addr + pm_pbs_data->tp_rev, &read_info_temp8);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
    
    pbs_info_ptr->test_pgm_rev = (uint32) read_info_temp8;
    read_info_temp8 = 0;
    
    /* Reading the Fab id, Wafer id, X/Y Co-ords and storing it in temp variable */
    err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr + pm_pbs_data->fab_id, 4, (uint8*)&read_info_temp32);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
    return err_flag;
    }
    
    /* Storing the Fab ID, Wafer ID, X and Y coords in the pbs info struct */
    pbs_info_ptr->fab_id = (uint32)(read_info_temp32 & 0x000000FF);
    pbs_info_ptr->wafer_id = (uint32)((read_info_temp32>>8) & 0x000000FF);
    pbs_info_ptr->x_coord = (uint32)((read_info_temp32>>16) & 0x000000FF);
    pbs_info_ptr->y_coord = (uint32)((read_info_temp32>>24) & 0x000000FF);
    read_info_temp32 = 0;
    
    /* Reading the Lot info stored in MISC/REV_ID peripheral registers. 12 Lot Ids are
     stored in 9 registers with 6 bits assigned for each lot id. Since the bit
     mask for the lot ids would be the same for every 3 register reads, below
     logic is implemented in while loop. The logic is to read and store 4 lot ids
     spread across 3 registers and repeat the same logic thrice in the loop for
     9 registers */
    
    /* Starting to read from LOT_ID_01_00 register and decrement to the next register
     addr after every read */
    
    lot_info_addr = pm_pbs_data->perph_base_addr + pm_pbs_data->lot_id; // LOT_ID_01_00;
    
    /* The third and final loop will start the register read from LOT_ID_09_08 register
     and the lot info count should be < 9 since we increment the count 4 times per
     loop and the number of lot ids are 12 */
    
    err_flag = pm_comm_read_byte_array(slave_id, lot_info_addr, PM_PBS_NUM_LOT_ID_RES, lot_arry);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
     
    while (lot_info_cnt > 2)
    {
      pbs_info_ptr->lot_id[lot_info_cnt--] = *lot_ptr >> 2 & 0x3F;
      pbs_info_ptr->lot_id[lot_info_cnt--] = *(uint16*)lot_ptr++ >> 4 & 0x3F;
      pbs_info_ptr->lot_id[lot_info_cnt--] = *(uint16*)lot_ptr++ >> 6 & 0x3F;
      pbs_info_ptr->lot_id[lot_info_cnt--] = *lot_ptr++ & 0x3F;
    }
    
    /* Reading the MFG_ID and storing it in temp variable */
    err_flag = pm_comm_read_byte(slave_id, pm_pbs_data->perph_base_addr + pm_pbs_data->mfg_id, &read_info_temp8);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
    pbs_info_ptr->mfg_id =  read_info_temp8 ;
    
    /* Configuring the base address for reading PBS OTP info */
    pbs_element_info_temp_addr = PM_PBS_ROM_BASE_ADDR + 4 * (pm_pbs_data->pbs_otp_mem_size - PM_PBS_MEMORY_VER_LINE_FROM_END);
    err_flag = pm_pbs_config_access(slave_id, pbs_element_info_temp_addr, PM_PBS_ACCESS_READ_BURST, PM_PBS_TYPE_ROM, periph_id);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
    
    /* Reading the OTP version info and storing it in temp variable */
    err_flag = pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8*)&read_info_temp32);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
    
    /* Store the OTP Version info in the PBS Info struct */
    pbs_info_ptr->rom_version = (uint32)(read_info_temp32 & 0x0000FFFF);
    
    /* Configuring to disable PBS core read access */
    err_flag = pm_pbs_disable_access(slave_id, PM_PBS_TYPE_ROM, periph_id);
  }
  
  if (pmic_sid_count == 1)
  {
    err_flag = pm_comm_read_byte_array(slave_id, PM_REV_ID_TP_REV_ADDR, 4, (uint8*)&rev_id_data);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
   
    pbs_info_ptr->test_pgm_rev = (uint32)(rev_id_data & 0x000000FF);
    pbs_info_ptr->fab_id = (uint32)((rev_id_data>>8) & 0x000000FF);
    pbs_info_ptr->wafer_id = (uint32)(rev_id_data>>16 & 0x000000FF);
    pbs_info_ptr->x_coord = (uint32)((rev_id_data>>24) & 0x000000FF);
   
    err_flag = pm_comm_read_byte_array(slave_id, PM_REV_ID_TP_REV_ADDR + 0x04, 4, (uint8*)&rev_id_data);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
   
    pbs_info_ptr->y_coord = (uint32)((rev_id_data>>0) & 0x000000FF);
    pbs_info_ptr->lot_id[10] = (uint8)((rev_id_data >>8) & 0x000000FF);
    pbs_info_ptr->lot_id[9] = (uint8)((rev_id_data >> 16) & 0x000000FF);
    pbs_info_ptr->lot_id[8] = (uint8)((rev_id_data >> 24) & 0x000000FF);
   
    err_flag = pm_comm_read_byte_array(slave_id, PM_REV_ID_TP_REV_ADDR + 0x08, 4, (uint8*)&rev_id_data);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
   
    pbs_info_ptr->lot_id[6] = (uint32)((rev_id_data>>0) & 0x000000FF);
    pbs_info_ptr->lot_id[5] = (uint8)((rev_id_data >>8) & 0x000000FF);
    pbs_info_ptr->lot_id[4] = (uint8)((rev_id_data >> 16) & 0x000000FF);
    pbs_info_ptr->lot_id[2] = (uint8)((rev_id_data >> 24) & 0x000000FF);
   
    err_flag = pm_comm_read_byte_array(slave_id, PM_REV_ID_TP_REV_ADDR + 0x0B, 4, (uint8*)&rev_id_data);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }
   
    pbs_info_ptr->lot_id[1] = (uint32)((rev_id_data>>0) & 0x000000FF);
    pbs_info_ptr->lot_id[0] = (uint8)((rev_id_data >>8) & 0x000000FF);
    pbs_info_ptr->mfg_id = (uint8)((rev_id_data >> 16) & 0x000000FF);
   
    err_flag = pm_comm_read_byte_array(slave_id, PM_REV_ID_OTP_ID_ADDR, 1,(uint8*)&rev_id_data);        
    pbs_info_ptr->rom_version = (uint8)rev_id_data; 
  }
  
  return err_flag;
}


/** 
 * @name pm_pbs_info_rom_init 
 *  
 * @brief Please refer to pm_pbs_info.h file for info regarding 
 *        this function.
 */
pm_err_flag_type pm_pbs_info_rom_init (void) 
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_pbs_info_data_type** pm_pbs_temp_data = NULL;
  uint32 slave_id = 0;
  uint8 pmic_index = 0;
  uint8 data = 0;
  uint8 periph_id = 0;

  DALSYS_memset(pm_pbs_info_arr, 0, sizeof(pm_pbs_info_arr));

  /* Retrieve place where PBS info stored */
  pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);

  if(NULL == pm_pbs_temp_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    /* Get PMIC device primary slave id */
    err_flag = pm_get_slave_id(pmic_index, 0, &slave_id);

    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      err_flag = PM_ERR_FLAG_SUCCESS;
      continue;
    }

    pm_pbs_data = pm_pbs_temp_data[pmic_index];
    
    if(pm_pbs_data == NULL)
    {
      continue;
    }
  
    periph_id = (pm_pbs_data->perph_base_addr)/ PERIPH_OFFSET;
    /* Read PBS Peripheral info and check if PBS peripheral exists */
    
    err_flag = pm_comm_read_byte(slave_id, pm_pbs_data->perph_base_addr+PERIPH_TYPE_OFFSET_ADDR, &data);

    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }

    if (data != PM_HW_MODULE_PBS)
    {
      err_flag = PM_ERR_FLAG_SUCCESS;
      continue;
    }

    if (PM_PBS_INFO_IN_PERIPH == pm_pbs_data->pbs_info_place_holder)
    {
      err_flag = pm_pbs_info_read_from_periph (slave_id, &(pm_pbs_info_arr[pmic_index]));
    }
    else if (PM_PBS_INFO_IN_OTP == pm_pbs_data->pbs_info_place_holder) 
    {
      /* Read all the PMIC's PBS Manufacturing IDs from PBS ROM */
      err_flag = pm_pbs_info_otp_read(slave_id, &(pm_pbs_info_arr[pmic_index]));
    }
    else
    {
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }

    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      /* Configuring to disable PBS core read access */
      pm_pbs_disable_access(slave_id, PM_PBS_TYPE_ROM, periph_id);

      return err_flag;
    }
  }

  pm_pbs_info_initialized = TRUE;
  return err_flag;
}

/** 
 * @name pm_pbs_info_ram_init 
 *  
 * @brief Please refer to pm_pbs_info.h file for info regarding 
 *        this function.
 */
pm_err_flag_type pm_pbs_info_ram_init (void) 
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  pm_pbs_info_data_type** pm_pbs_temp_data = NULL;
  uint32 slave_id = 0;
  uint8 pmic_index = 0;
  uint8 data = 0;
  uint8 periph_id = 0;

  /* Return error if PBS ROM driver is not already initialized */
  if (!pm_pbs_info_initialized)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /* Retrieve place where PBS info stored */
  pm_pbs_temp_data = (pm_pbs_info_data_type**)pm_target_information_get_specific_info(PM_PROP_PBS_INFO);

  if(NULL == pm_pbs_temp_data)
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }

  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    /* Get PMIC device primary slave id */
    err_flag = pm_get_slave_id(pmic_index, 0, &slave_id);

    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      err_flag = PM_ERR_FLAG_SUCCESS;
      continue;
    }

    pm_pbs_data = pm_pbs_temp_data[pmic_index];
    if(pm_pbs_data == NULL)
    {
      continue;
    }
  
    periph_id = (pm_pbs_data->perph_base_addr)/ PERIPH_OFFSET;
  
    /* Read PBS Peripheral info and check if PBS peripheral exists */
    err_flag = pm_comm_read_byte(slave_id, pm_pbs_data->perph_base_addr+PERIPH_TYPE_OFFSET_ADDR, &data);

    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }

    if (data != PM_HW_MODULE_PBS)
    {
      err_flag = PM_ERR_FLAG_SUCCESS;
      continue;
    }

    /* Read all the PMIC's PBS Manufacturing IDs from PBS ROM */
    if ( pm_pbs_data->pbs_info_place_holder < PM_PBS_INFO_INVALID )
    {
        err_flag = pm_pbs_info_ram_read(slave_id, &(pm_pbs_info_arr[pmic_index]));
    }

    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      /* Configuring to disable PBS core read access */
      pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);

      return err_flag;
    }
  }

  pm_pbs_info_initialized = TRUE;
  return err_flag;
}

/** 
 * @name pm_pbs_info_store_glb_ctxt 
 *  
 * @brief Please refer to pm_pbs_info.h file for info regarding 
 *        this function.
 */
pm_err_flag_type pm_pbs_info_store_glb_ctxt (void) 
{
  pm_pbs_info_glb_ctxt_type* pbs_glb_ctxt_ptr = NULL;
  uint8 pmic_index = 0;

  /* Return error if PBS driver is not already initialized */
  if (!pm_pbs_info_initialized)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /* Ensure global context has been initialized */
  if(DAL_SUCCESS != DALGLBCTXT_Init())
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /* Allocate the context */
  if(DAL_SUCCESS != DALGLBCTXT_AllocCtxt("PM_PBS_INFO", sizeof(pm_pbs_info_glb_ctxt_type),
                                         DALGLBCTXT_LOCK_TYPE_SPINLOCK, (void **)&pbs_glb_ctxt_ptr))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (pbs_glb_ctxt_ptr == NULL)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  for (pmic_index = 0; pmic_index < PM_MAX_NUM_PMICS; pmic_index++)
  {
    /* Fill in the global context with PMIC's PBS info */
    DALSYS_memscpy(&(pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index]), sizeof(pm_pbs_info_smem_type), &(pm_pbs_info_arr[pmic_index]), sizeof(pm_pbs_info_smem_type));
  }

  return PM_ERR_FLAG_SUCCESS;
}

static pm_err_flag_type pm_get_pbs_info_from_smem(uint8 pmic_index, pm_pbs_info_type *pbs_info_ptr)
{
  static pm_pbs_info_glb_ctxt_type *pbs_glb_ctxt_ptr = NULL;

  /* Ensure global context has been initialized */
  if (DAL_SUCCESS != DALGLBCTXT_Init())
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (NULL == pbs_glb_ctxt_ptr)
  {
    /* Look-up the global context */
    if (DAL_SUCCESS != DALGLBCTXT_FindCtxt("PM_PBS_INFO", (void **)&pbs_glb_ctxt_ptr))
    {
      return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
    }
  }

  /* Format 0 indicates pbs info read failed in sbl */
  if (pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].format == 0)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /* Major format increments breaks the backward compatibility */
  if (((uint32)((pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].format) >> 16)) != 0)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /* Get the PBS info from global context and return it */
  DALSYS_memcpy(pbs_info_ptr->lot_id, pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].lot_id, sizeof(pbs_info_ptr->lot_id));

  pbs_info_ptr->rom_version = pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].rom_version;
  pbs_info_ptr->ram_version = pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].ram_version;
  pbs_info_ptr->fab_id = pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].fab_id;
  pbs_info_ptr->wafer_id = pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].wafer_id;
  pbs_info_ptr->x_coord = pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].x_coord;
  pbs_info_ptr->y_coord = pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].y_coord;
  pbs_info_ptr->test_pgm_rev = pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].test_pgm_rev;
  pbs_info_ptr->mfg_id = pbs_glb_ctxt_ptr->pbs_info_glb_arr[pmic_index].mfg_id;

  return PM_ERR_FLAG_SUCCESS;
}

static pm_err_flag_type pm_get_pbs_info_from_otp(uint8 pmic_index, pm_pbs_info_type *pbs_info_ptr)
{
  if ((pm_pbs_info_initialized == FALSE) || (pm_pbs_info_arr[pmic_index].format != PM_PBS_INFO_SMEM_FORMAT))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  if (pm_pbs_info_arr[pmic_index].format != PM_PBS_INFO_SMEM_FORMAT)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  //get the PBS info from static global variable and return it
  DALSYS_memscpy(pbs_info_ptr->lot_id, sizeof(pbs_info_ptr->lot_id), pm_pbs_info_arr[pmic_index].lot_id, sizeof(pbs_info_ptr->lot_id));

  pbs_info_ptr->rom_version = pm_pbs_info_arr[pmic_index].rom_version;
  pbs_info_ptr->ram_version = pm_pbs_info_arr[pmic_index].ram_version;
  pbs_info_ptr->fab_id = pm_pbs_info_arr[pmic_index].fab_id;
  pbs_info_ptr->wafer_id = pm_pbs_info_arr[pmic_index].wafer_id;
  pbs_info_ptr->x_coord = pm_pbs_info_arr[pmic_index].x_coord;
  pbs_info_ptr->y_coord = pm_pbs_info_arr[pmic_index].y_coord;
  pbs_info_ptr->test_pgm_rev = pm_pbs_info_arr[pmic_index].test_pgm_rev;
  pbs_info_ptr->mfg_id = 0;

  return PM_ERR_FLAG_SUCCESS;
}


pm_err_flag_type
pm_pbs_pon_rsn_sdam_read(uint32 slave_id,uint32 start_address, uint32* dataset_ptr, uint32 dataset_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 read_data = 0;
  uint8 i = 0; 

  for (i =0 ; i < dataset_size ; i++)
  {
    err_flag |= pm_comm_read_byte_array(slave_id, start_address, 4, (uint8 *)&read_data);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      return err_flag;
    }

    dataset_ptr[i] = read_data;
     
    //Update start address to read next register
    start_address = start_address + 0x04;
  }
  
  return err_flag;
}


pm_err_flag_type pm_get_pbs_info(uint8 pmic_index, pm_pbs_info_type *pbs_info_ptr)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

  if ((NULL == pbs_info_ptr) || (pmic_index >= PM_MAX_NUM_PMICS))
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  /*read PBS info from SMEM where OTP can't be accessed*/
  if (PM_IMG_LOADER == pm_get_img_type())
  {
    err_flag = pm_get_pbs_info_from_otp(pmic_index, pbs_info_ptr);
  }
  else if (PM_IMG_CORE == pm_get_img_type())
  {
    err_flag = pm_get_pbs_info_from_smem(pmic_index, pbs_info_ptr);
  }
  else
  {
    err_flag = PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }

  return err_flag;
}



  
pm_err_flag_type pm_pbs_mem_read(uint8 slave_id, uint32 start_address, uint32* data_ptr, uint32 data_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint32 read_data = 0;
  uint8 i = 0; 
  pm_pbs_info_data_type *pm_pbs_data = NULL;
  uint8 pmic_index = 0;
  uint8 periph_id = 0;
  
  err_flag = pm_get_pmic_index_from_slave(slave_id, &pmic_index);
  
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED ;
  }
  
  pm_pbs_data = pm_pbs_config_data[pmic_index];
  if(NULL == pm_pbs_data)
  {
    return PM_ERR_FLAG_DATA_VERIFY_ERR;
  }
  periph_id = (pm_pbs_data->perph_base_addr)/ PERIPH_OFFSET;

  err_flag |= pm_pbs_get_mem_info(slave_id, &pm_pbs_data->pbs_ram_start_addr,
              &pm_pbs_data->pbs_otp_mem_size, &pm_pbs_data->pbs_ram_mem_size);
             
  if(data_ptr == NULL || data_size == 0 )
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
             
  //check PBS RAM read address is within range
  if((start_address + data_size) > (pm_pbs_data->pbs_ram_start_addr + (4 * (pm_pbs_data->pbs_ram_mem_size))))
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
     
  /* Configuring to enable PBS core access for ROM reads */
  err_flag |= pm_pbs_config_access(slave_id, start_address , PM_PBS_ACCESS_READ_BURST, PM_PBS_TYPE_RAM, periph_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    err_flag |= pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);
    return err_flag;
  }

  /* Perform PBS read*/
  for (i =0 ; i < data_size ; i++)
  {
    err_flag |= pm_comm_read_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_RD_DATA0_OFFS, 4, (uint8 *)&read_data);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      err_flag |= pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);
      return err_flag;
    }
    data_ptr[i] = (uint32)read_data;
  }

  /* Configuring to disable PBS core read access */
  err_flag |= pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);

  return err_flag;
}


pm_err_flag_type pm_pbs_mem_write(uint8 slave_id, uint32 start_address, uint32* data_ptr, uint32 data_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  uint8 i = 0; 
  pm_pbs_info_data_type *pm_pbs_data = NULL;
  uint8 pmic_index = 0;
  uint8 periph_id = 0;
  
  err_flag = pm_get_pmic_index_from_slave(slave_id, &pmic_index);
  
  if(err_flag != PM_ERR_FLAG_SUCCESS)
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED ;
  }
  
  pm_pbs_data = pm_pbs_config_data[pmic_index];
  if(NULL == pm_pbs_data)
  {
    return PM_ERR_FLAG_DATA_VERIFY_ERR;
  }
  
  periph_id = (pm_pbs_data->perph_base_addr)/ PERIPH_OFFSET;
  
  err_flag |= pm_pbs_get_mem_info(slave_id, &pm_pbs_data->pbs_ram_start_addr,
              &pm_pbs_data->pbs_otp_mem_size, &pm_pbs_data->pbs_ram_mem_size);
  
  
  if(data_ptr == NULL || data_size == 0 )
  {
    return PM_ERR_FLAG_FEATURE_NOT_SUPPORTED;
  }
  
  //check PBS RAM write address is within range
  if((start_address + data_size) > (pm_pbs_data->pbs_ram_start_addr + (4 * (pm_pbs_data->pbs_ram_mem_size - PM_PBS_MEMORY_VER_LINE_FROM_END))) ||
    ((start_address) < (pm_pbs_data->pbs_ram_start_addr)) )
  {
    return PM_ERR_FLAG_INVALID_PARAMETER;
  }
  
  /* Configuring to enable PBS core access for ROM reads */   
  err_flag |= pm_pbs_config_access(slave_id, start_address , PM_PBS_ACCESS_WRITE_BURST, PM_PBS_TYPE_RAM, periph_id);
  if (err_flag != PM_ERR_FLAG_SUCCESS)
  {
    err_flag |= pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);
    return err_flag;
  }
  
  /* Perform PBS write*/
  for (i =0 ; i < data_size ; i++)
  {
    err_flag |= pm_comm_write_byte_array(slave_id, pm_pbs_data->perph_base_addr+MEM_INTF_WR_DATA0_OFFS, 4, (uint8*)&data_ptr[i]);
    if (err_flag != PM_ERR_FLAG_SUCCESS)
    {
      err_flag |= pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);
      return err_flag;
    }
  }
  
  /* Configuring to disable PBS core write access */
  err_flag |= pm_pbs_disable_access(slave_id, PM_PBS_TYPE_RAM, periph_id);
  
  return err_flag;
    
}


pm_err_flag_type 
pm_pbs_get_pon_reason_hist_dataset(void)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  boolean valid_sid = FALSE;
  uint32 slave_id = 0; 
  uint8 pmic_index = 0; 
  uint8 copy_data_count = 0;
  pm_model_type pm_model = PMIC_IS_UNKNOWN;
  uint32 rev_id_read = 0;
  uint32 pon_temp_data = 0;

  pon_reason_history.signature = PON_RSN_HIST_SIGNATURE; 
  pon_reason_history.version   = PON_RSN_HIST_VERSION;
  pon_reason_history.max_no_of_pmics = MAX_NO_OF_PMICS_FOR_PON_RSN;
  pon_reason_history.no_of_pon_reasons_per_pmics = NO_OF_PON_RSN_PER_PMIC;

  for (pmic_index =0 ; pmic_index < MAX_NO_OF_PMICS_FOR_PON_RSN; pmic_index++)
  {
    pm_get_slave_id(pmic_index, 0, &slave_id);
    pm_resolve_chip_revision(slave_id, &valid_sid, &rev_id_read);
    
    if (valid_sid == FALSE)
    {
      continue;  //PMIC does not exist
    }

    pm_model = pm_get_pmic_model(pmic_index);
    pon_reason_history.pbs_pon_rsn_hist_data[pmic_index].pmic_id = pm_model;
    
    pm_log_message("PON REASON HISTORY LOGS");
    for(copy_data_count =0; copy_data_count < NO_OF_PON_RSN_PER_PMIC; copy_data_count++  )
    {
      err_flag = pm_comm_read_byte_array(slave_id, (PON_RSN_HIST_START_SDAM_ADDR + (4 * copy_data_count)), 4, (uint8*)&pon_temp_data);
      pm_log_message("Word %d : 0x%lX",copy_data_count, pon_temp_data);
      pon_reason_history.pbs_pon_rsn_hist_data[pmic_index].pon_data[copy_data_count] = pon_temp_data;
    }
  }
   
   return err_flag;

}


pm_err_flag_type 
pm_pbs_get_pon_reason_history(pm_pbs_pon_reason_history_data_type *pon_reason_history_ptr )
{
  
    pm_err_flag_type  err_flag = PM_ERR_FLAG_SUCCESS;
  
    //Copy the data from Local variable to the memory dump location
    DALSYS_memscpy(pon_reason_history_ptr, sizeof(pm_pbs_pon_reason_history_data_type), &pon_reason_history, sizeof(pm_pbs_pon_reason_history_data_type));

  return err_flag;
    
}

