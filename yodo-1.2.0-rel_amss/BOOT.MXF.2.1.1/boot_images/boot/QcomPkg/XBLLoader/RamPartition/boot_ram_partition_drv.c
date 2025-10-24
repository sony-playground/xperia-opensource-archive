/*===========================================================================

                RAM Partition Table Function Implementations

DESCRIPTION
  This source file gives the implementation of the RAM Partition Table
  population functions.

Copyright 2019-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

    This section contains comments describing changes made to this file.
    Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/17/21   rama    APIs to support updating used regions in ram partition table
03/25/21   rhy     Defined and exposed boot_add_single_ram_partition_table_entry
12/09/20   rama    Ported error handling changes in add_system_ram_partitions
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include <string.h>
#include "boot_config_context.h"
#include "boot_ram_partition_drv.h"
#include "boot_ddr_info_if.h"
#include "boot_ddr_if.h"
#include "boot_smem_if.h"
#include "boot_target.h"

#define CONVERT_TO_BYTE_SHIFT  20

/*=========================================================================

                      FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

**  Function :  load_ram_partition_table

** ==========================================================================
*/
/*!
*
* @brief
*    Function initializes usable_ram_partition_table in shared memory.
*
* @param[out]  result Function return status. If it equals RAM_PART_SUCCESS
*                     then the table is successfully allocated.
*
* @par Dependencies
*   None
*
* @retval
*   usable_ram_part_table_t usable_ram_part_tbl_ptr
*     - returns pointer to usable ram partition table in shared memory.
*
* @par Side Effects
*   None
*/
static bl_error_boot_type load_ram_partition_table(boot_handle config_context_handle, usable_ram_part_table_t *usable_ram_part_tbl_ptr, uint32 *result)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  boot_smem_if_type *smem_if = NULL;

  do
  {
    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SMEM_INTERFACE, (void **)&smem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    /* allocate memory in shared memory region for usable_ram_part_table */
    *usable_ram_part_tbl_ptr = (usable_ram_part_table_t)(smem_if->alloc(SMEM_USABLE_RAM_PARTITION_TABLE, sizeof(usable_ram_part_table)));
    *result = RAM_PART_OTHER_ERR;

    /* verify shared memory allocation for usable_ram_part_table didn't fail */
    if (*usable_ram_part_tbl_ptr == NULL)
    {
      *result = RAM_PART_NULL_PTR_ERR;
      break;
    }

    /* verify if usable_ram_partition_table is in shared memory region */
    if ((((uintnt)(*usable_ram_part_tbl_ptr)) > SCL_SHARED_RAM_BASE) &&
        (((uintnt)(*usable_ram_part_tbl_ptr) + sizeof(usable_ram_part_table))
         <=(SCL_SHARED_RAM_BASE + SCL_SHARED_RAM_SIZE)))
    {
      (*usable_ram_part_tbl_ptr)->num_partitions = 0;
      *result = RAM_PART_SUCCESS;
    }
    else
    {
      *result = RAM_PART_OUT_OF_BOUND_PTR_ERR;
      break;
    }

  } while (0);

  /* return pointer to usable ram part table in shared memory */
  return return_status;
}


/*===========================================================================

**  Function :  add_single_ram_partition

** ==========================================================================
*/
/*!
*
* @brief
*    Function adds a single partition entry into the ram partition table.
*
* @param[in] usable_ram_part_tbl_ptr Pointer to ram partition table that
*                                    should be updated.
*
* @param[in] uintnt start_address start address of this partition
*
*
* @param[in] uint32 length length of this partition in bytes
*
*
* @param[in] uint32 partition_attribute attribute of this partition
*
*
* @param[in] uint32 partition_domain domain of this partition
*
*
* @param[in] uint32 partition_type type of this partition
*
* @par Dependencies
*   None
*
* @retval
*   ram_partition_return_type
*   RAM_PART_SUCCESS     - if function is successful.
*   RAM_PART_TABLE_FULL_ERR - if table is full or not enough space in
*                             the table
*
* @par Side Effects
*   None
*/
static ram_partition_return_type add_single_ram_partition
(
  usable_ram_part_table_t usable_ram_part_tbl_ptr,
  uintnt start_address,
  uintnt length,
  uint32 partition_attribute,
  uint32 partition_category,
  uint32 partition_domain,
  uint32 partition_type
)
{
  ram_part_entry_t ram_part_entry_ptr = NULL;
  ram_partition_return_type result = RAM_PART_TABLE_FULL_ERR;

  if (usable_ram_part_tbl_ptr->num_partitions < RAM_NUM_PART_ENTRIES)
  {
    ram_part_entry_ptr = &usable_ram_part_tbl_ptr->
                         ram_part_entry[usable_ram_part_tbl_ptr->num_partitions];

    ram_part_entry_ptr->start_address = start_address;
    ram_part_entry_ptr->length = length;
    ram_part_entry_ptr->available_length = length;
    ram_part_entry_ptr->partition_attribute = partition_attribute;
    ram_part_entry_ptr->partition_category = partition_category;
    ram_part_entry_ptr->partition_domain = partition_domain;
    ram_part_entry_ptr->partition_type = partition_type;
    usable_ram_part_tbl_ptr->num_partitions++;
    result = RAM_PART_SUCCESS;
  }

  return result;
}


/*===========================================================================

**  Function :  add_system_ram_partitions

** ==========================================================================
*/
/*!
*
* @brief
*    Function adds all the DDR interfaces to ram partition table.
*    Each DDR interface will be added as a single entry in the table.
*    Partition category  will be RAM_PARTITION_SDRAM for all DDR entries.
*
* @param[in] usable_ram_part_tbl_ptr Pointer to the ram partition table that
*                                    should be populated
*
* @par Dependencies
*   None
*
* @retval
*   ram_partition_return_type
*   RAM_PART_SUCCESS        - if function is successful.
*   RAM_PART_TABLE_FULL_ERR - if table is full or not enough space in
*                             the table
*   RAM_PART_CATEGORY_NOT_EXIST_ERR - if unable to populate certain DDR information
*
* @par Side Effects
*   None
*/
static bl_error_boot_type add_system_ram_partitions(boot_handle config_context_handle, usable_ram_part_table_t usable_ram_part_tbl_ptr, uint32* result_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  ram_part_entry_t ram_part_entry_ptr = NULL;
  boot_ddr_info_type *ddr_info = NULL;
  boot_extended_ddr_info_type *ddr_extended_info = NULL;
  uint32 partition_index = 0;
  *result_ptr = RAM_PART_SUCCESS;
  boot_ddr_info_if_type *ddr_info_if = NULL;
  boot_ddr_if_type *ddr_if = NULL;
  boot_ddr_device_info_type *ddr_shared_info = NULL;
  uint32 param_size=0;

  return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DDR_INFO_INTERFACE, (void **)&ddr_info_if);
  if (return_status != BL_ERR_NONE)
  {
    return return_status;
  }

  return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_DDR_INTERFACE, (void **)&ddr_if);
  if (return_status != BL_ERR_NONE)
  {
    return return_status;
  }

  ddr_shared_info = ddr_info_if->get_ddr_info();

  /*ram_part_entry_ptr points to first empty slot in the table*/
  ram_part_entry_ptr =
    &usable_ram_part_tbl_ptr->
    ram_part_entry[usable_ram_part_tbl_ptr->num_partitions];

  /*Loop through ddr_info and add all DDR interfaces into the table*/
  for (; partition_index < ddr_shared_info->noofddr  &&
       usable_ram_part_tbl_ptr->num_partitions < RAM_NUM_PART_ENTRIES;
       partition_index++)
  {
    ddr_info = &ddr_shared_info->ddr_info[partition_index];

    ram_part_entry_ptr->partition_category = RAM_PARTITION_SDRAM;
    ram_part_entry_ptr->start_address = ddr_info->cs_addr;
    ram_part_entry_ptr->length = ddr_info->ramsize << CONVERT_TO_BYTE_SHIFT;
    ram_part_entry_ptr->available_length = ram_part_entry_ptr->length;
    ram_part_entry_ptr->partition_attribute = RAM_PARTITION_READWRITE;
    ram_part_entry_ptr->partition_domain = RAM_PARTITION_DEFAULT_DOMAIN;
    ram_part_entry_ptr->partition_type = RAM_PARTITION_SYS_MEMORY;
    /*Get the granule size from DDR driver, granule size is in MB */
    param_size = 0;
    return_status = ddr_if->get_ddr_region_param(partition_index, MIN_PASR_SIZE, NULL, &param_size);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    ddr_if->get_ddr_region_param(partition_index, MIN_PASR_SIZE, &(ram_part_entry_ptr->min_pasr_size), &param_size);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    /*Add the extended ddr information to current ram partition entry*/
    if (ddr_shared_info->ddr_partition_info != NULL)
    {
      ddr_extended_info = &ddr_shared_info->ddr_partition_info[partition_index];

      /*Make sure the base address of ddr extended info matches the current ddr base address*/
      if (ddr_extended_info->sdram_addr != ram_part_entry_ptr->start_address)
      {
        *result_ptr = RAM_PART_CATEGORY_NOT_EXIST_ERR;
        break;
      }
      ram_part_entry_ptr->num_partitions = ddr_extended_info->num_partitions;
      ram_part_entry_ptr->highest_bank_bit = ddr_extended_info->highest_bank_bit;
    }

    ram_part_entry_ptr++;
    usable_ram_part_tbl_ptr->num_partitions++;
  }


  return return_status;
}


/*===========================================================================

**  Function :  add_imem_ram_partition

** ==========================================================================
*/
/*!
*
* @brief
*    Function adds a partition entry for imem memory into the
*    ram partition table.
*
* @param[in] usable_ram_part_tbl_ptr Pointer to ram partition table that
*                                    should be updated.
*
* @par Dependencies
*   None
*
* @retval
*   ram_partition_return_type
*   RAM_PART_SUCCESS     - if function is successful.
*   RAM_PART_TABLE_FULL_ERR - if table is full or not enough space in
*                             the table
*
* @par Side Effects
*   None
*/
static bl_error_boot_type add_imem_ram_partition(usable_ram_part_table_t usable_ram_part_tbl_ptr, uint32* result_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  *result_ptr = RAM_PART_SUCCESS;

  /* Using IMEM_RANGE values as targets can have multiple IMEM regions
     and a single SCL_IMEM_* value might not exist. */

  if (IMEM_RANGE_START_ADDR != 0) /* there's imem partition to add*/
  {
    *result_ptr = add_single_ram_partition(usable_ram_part_tbl_ptr,
                                           IMEM_RANGE_START_ADDR,
                                           (IMEM_RANGE_END_ADDR - IMEM_RANGE_START_ADDR),
                                           RAM_PARTITION_READWRITE,
                                           RAM_PARTITION_IMEM,
                                           RAM_PARTITION_DEFAULT_DOMAIN,
                                           RAM_PARTITION_SYS_MEMORY);
  }

  return return_status;
}


/*===========================================================================

**  Function :  add_iram_ram_partition

** ==========================================================================
*/
/*!
*
* @brief
*    Function adds a partition entry for iram memory into the
*    ram partition table.
*
* @param[in] usable_ram_part_tbl_ptr Pointer to ram partition table that
*                                    should be updated.
*
* @par Dependencies
*   None
*
* @retval
*   ram_partition_return_type
*   RAM_PART_SUCCESS     - if function is successful.
*   RAM_PART_TABLE_FULL_ERR - if table is full or not enough space in
*                             the table
*
* @par Side Effects
*   None
*/
static bl_error_boot_type add_iram_ram_partition(usable_ram_part_table_t usable_ram_part_tbl_ptr, uint32* result_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  *result_ptr = RAM_PART_SUCCESS;

  if (SCL_IRAM_SIZE != 0) /* there's iram to add*/
  {
    *result_ptr = add_single_ram_partition(usable_ram_part_tbl_ptr,
                                           SCL_IRAM_BASE,
                                           SCL_IRAM_SIZE,
                                           RAM_PARTITION_READWRITE,
                                           RAM_PARTITION_IRAM,
                                           RAM_PARTITION_DEFAULT_DOMAIN,
                                           RAM_PARTITION_SYS_MEMORY);
  }

  return return_status;
}


/*===========================================================================

**  Function :  add_boot_region_ram_partition

** ==========================================================================
*/
/*!
*
* @brief
*    Function adds sbl1 DDR memory region into the ram partition table.
*
* @param[in] usable_ram_part_tbl_ptr Pointer to ram partition table that
*                                    should be updated.
*
* @par Dependencies
*   None
*
* @retval
*   ram_partition_return_type
*   RAM_PART_SUCCESS        - if function is successful.
*   RAM_PART_TABLE_FULL_ERR - if table is full
*
* @par Side Effects
*   None
*/
static bl_error_boot_type add_boot_region_ram_partition(usable_ram_part_table_t usable_ram_part_tbl_ptr, uint32* result_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  uint32 category = RAM_PARTITION_DEFAULT_CATEGORY;
  *result_ptr = RAM_PART_SUCCESS;

  get_partition_category(usable_ram_part_tbl_ptr,
                         SCL_SBL1_DDR_DATA_BASE,
                         &category);

  if (SCL_SBL1_DDR_SIZE != 0) /* there's boot region partition to add*/
  {
    *result_ptr = add_single_ram_partition(usable_ram_part_tbl_ptr,
                                           SCL_SBL1_DDR_BASE,
                                           SCL_SBL1_DDR_SIZE,
                                           RAM_PARTITION_READWRITE,
                                           category,
                                           RAM_PARTITION_DEFAULT_DOMAIN,
                                           RAM_PARTITION_BOOT_REGION_MEMORY1);
  }

  return return_status;
}


/*===========================================================================

**  Function :  add_ram_partitions

** ==========================================================================
*/
/*!
*
* @brief
*    For each type of memory (system memories and boot memory),
*    this function adds a partition entry in the ram partition table
*
* @param[in] usable_ram_part_tbl_ptr Pointer to ram partition table that
*                                    should be updated.
*
* @par Dependencies
*   None
*
* @retval
*   ram_partition_return_type
*   RAM_PART_SUCCESS     - if function is successful.
*   RAM_PART_TABLE_FULL_ERR - if table is full or not enough space in
*                             the table
*
* @par Side Effects
*   None
*/
static bl_error_boot_type add_ram_partitions(boot_handle config_context_handle, usable_ram_part_table_t usable_ram_part_tbl_ptr, uint32 *result_ptr)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  *result_ptr = RAM_PART_OTHER_ERR;

  do
  {
    return_status = add_system_ram_partitions(config_context_handle, usable_ram_part_tbl_ptr, result_ptr);
    if (*result_ptr != RAM_PART_SUCCESS || return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = add_iram_ram_partition(usable_ram_part_tbl_ptr, result_ptr);
    if (*result_ptr != RAM_PART_SUCCESS || return_status != BL_ERR_NONE)
    {
      break;
    }

    return_status = add_imem_ram_partition(usable_ram_part_tbl_ptr, result_ptr);
    if (*result_ptr != RAM_PART_SUCCESS || return_status != BL_ERR_NONE)
    {
      break;
    }

    /* only after system ram partitions are added should we call add appsbl
    and add boot region, because add_boot_region_ram_partition and
    add_appsbl_ram_partition will use the system ram partitions
    entries in the table to figure out which ram categories appsbl/boot
    region memory belong to*/
    return_status = add_boot_region_ram_partition(usable_ram_part_tbl_ptr, result_ptr);
    if (*result_ptr != RAM_PART_SUCCESS || return_status != BL_ERR_NONE)
    {
      break;
    }

  } while (0);

  return return_status;
}


/*===========================================================================

**  Function :  boot_populate_ram_partition_table

** ==========================================================================
*/
/*!
*
* @brief
*    Function initializes usable_ram_partition_table in shared memory.
*    Then for each type of memory (system memories,boot memory and appsbl memory)
*    this function adds a partition entry in the ram partition table
*    Once complete, function writes magic numbers and version number into table.
*
* @param[in] bl_shared_data Pointer to the shared data passed between functions
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_populate_ram_partition_table(boot_handle config_context_handle)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  usable_ram_part_table_t usable_ram_part_tbl_ptr = NULL;
  ram_partition_return_type result = RAM_PART_OTHER_ERR;

  do
  {
    /* allocate memory for ram partition table in shared memory region */
    return_status = load_ram_partition_table(config_context_handle, &usable_ram_part_tbl_ptr, (uint32*)&result);

    if (return_status!=BL_ERR_NONE)
    {
      break;
    }

    if (result != RAM_PART_SUCCESS || usable_ram_part_tbl_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MPROC, (BL_ERR_RAM_PART_SUCCESS + result));
      break;
    }


    /* add all partitions to the table*/
    return_status = add_ram_partitions(config_context_handle, usable_ram_part_tbl_ptr, (uint32*)&result);
    if (return_status!=BL_ERR_NONE)
    {
      break;
    }

    if (result != RAM_PART_SUCCESS)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MPROC, (BL_ERR_RAM_PART_SUCCESS + result));
      break;
    }

    usable_ram_part_tbl_ptr->magic1  = RAM_PART_MAGIC1;
    usable_ram_part_tbl_ptr->magic2  = RAM_PART_MAGIC2;
    usable_ram_part_tbl_ptr->version = RAM_PARTITION_VERSION;
  } while (FALSE);

  return return_status;
}


/*===========================================================================

**  Function :  boot_add_single_ram_partition_table_entry

** ==========================================================================
*/
/*!
*
* @brief
*    A wrapper function to add an entry in RAM Partition table
*
* @param[in]  start_address
* @param[in]  length
* @param[in]  partition_attribute
* @param[in]  partition_category
* @param[in]  partition_domain
* @param[in]  partition_type
*
* @par Dependencies
*   None
*
* @retval
*   None
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_add_single_ram_partition_table_entry
(   boot_handle config_context_handle,
    uintnt  start_address,
    uintnt  length,
    uint32  partition_attribute,
    uint32  partition_category,
    uint32  partition_domain,
    uint32  partition_type
)
{
  bl_error_boot_type return_status = BL_ERR_NONE;
  usable_ram_part_table_t usable_ram_part_tbl_ptr = NULL;
  ram_partition_return_type result = RAM_PART_TABLE_FULL_ERR;
  boot_smem_if_type *smem_if = NULL;
  uint32 table_size = 0;

  do
  {
    if (config_context_handle == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    return_status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SMEM_INTERFACE, (void **)&smem_if);
    if (return_status != BL_ERR_NONE)
    {
      break;
    }
    if (smem_if == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    /* Get the RAM Partition table base address */
    usable_ram_part_tbl_ptr = (usable_ram_part_table_t) smem_if->get_addr(SMEM_USABLE_RAM_PARTITION_TABLE, &table_size);
    if (usable_ram_part_tbl_ptr == NULL)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MPROC, BL_ERR_RAM_PART_DRV_TABLE_POINTER_UNINITIALIZE);
      break;
    }

    result = add_single_ram_partition(usable_ram_part_tbl_ptr,
                                      start_address,
                                      length,
                                      partition_attribute,
                                      partition_category,
                                      partition_domain,
                                      partition_type);

    if (result != RAM_PART_SUCCESS)
    {
      return_status = GET_ERROR_CODE(BL_ERROR_GROUP_MPROC, (BL_ERR_RAM_PART_SUCCESS + result));
      break;
    }

  } while (FALSE);

  return return_status;
}


/*===========================================================================

**  Function :  get_partition_category

** ==========================================================================
*/
/*!
*
* @brief
*    Given a memory address mem_base function returns the
*    partition_category this address belongs to. This function can only be
*    used after all system memory partitions are added into the table.
*
* @param[in]  usable_ram_part_tbl_ptr Pointer to table containing usable memory
*                                     partitions.
* @param[in]  mem_base                Base of the memory address
* @param[out] partition_category      Returned value of partition category
*
* @par Dependencies
*   None
*
* @retval
*   ram_partition_return_type
*   RAM_PART_SUCCESS                - if function is successful.
*   RAM_PART_CATEGORY_NOT_EXIST_ERR - if function can't retrieve partition
*                                      category.
*
* @par Side Effects
*   None
*/
ram_partition_return_type get_partition_category
(
  usable_ram_part_table_t usable_ram_part_tbl_ptr,
  uintnt mem_base,
  uint32 *partition_category
)
{
  uint32 counter = 0;
  ram_part_entry_t ram_part_entry_ptr = 0;
  ram_partition_return_type result = RAM_PART_CATEGORY_NOT_EXIST_ERR;
  *partition_category = RAM_PARTITION_DEFAULT_CATEGORY;

  for ( ; counter < usable_ram_part_tbl_ptr->num_partitions; counter++)
  {
    /* retrieve ram part entry info at current counter index */
    ram_part_entry_ptr = &usable_ram_part_tbl_ptr->ram_part_entry[counter];
    /* if mem_base is within partition range of ram_part_entry_ptr then
    * return partition_category of ram_part_entry_ptr
    */
    if (mem_base >= ram_part_entry_ptr->start_address &&
        mem_base <=
        (ram_part_entry_ptr->start_address + ram_part_entry_ptr->length))
    {
      *partition_category = ram_part_entry_ptr->partition_category;
      result = RAM_PART_SUCCESS;
      break;
    }
  }
  return result;
}

/*===========================================================================
FUNCTION  REMOVE_USED_RAM_REARRANGE_USABLE_RAM_TABLE

DESCRIPTION
   Function parse through the table containing usable ram partition entries
   and rearranges table if used ram is within any entry and returs TRUE.
   Function handles different scenarios
   - It removes usable ram partition entry from table if used ram exactly
     overlaps usable ram partition entry. This action decreases number of
     usable ram partitions by 1.
   - If used ram start_address and usable ram partition entry start_address
     matches but used ram length is less than usable ram partition, function
     changes usable ram partition start_addess and length. This action
     doesn't change number of usable ram paritions.
   - If used ram region is part of usable ram partition entry (used ram
     start_address is > table entry start_address and smaller length),
     function changes usable ram partition start_addess and length to reflect
     beginning usable portion of entry. Function also creates new usable
     ram partition entry to reflect rest of the usable portion of original
     entry. This action increments number of usable ram paritions by 1.
   - If used ram end_address and usable ram partition entry end address
     matches but used ram start_address doesn't match usable ram partition
     start_address then function changes usable ram partition start_address
     and length. This action doesn't change number of usable ram partitions.

ARGUMENTS
    usable_ram_part_table_t usable_ram_part_tbl_ptr - pointer to table
                containing usable ram partition entries
    used_ram_info_ptr_type  used_ram_info_ptr - pointer to structure
                containing used ram info like start_address & length

DEPENDENCIES
  None

RETURN VALUE
  ram_partition_return_type
  RAM_PART_SUCCESS          - if function is successful for rearranging table.
  RAM_PART_NULL_PTR_ERR     - if input pointer parameter is NULL
  RAM_PART_TABLE_EMPTY_ERR  - if partition table is empty
  RAM_PART_TABLE_FULL_ERR   - if partition table is full and it requires to
                              add entry as part of rearrangment

SIDE EFFECTS
  None
===========================================================================*/
static ram_partition_return_type remove_used_ram_rearrange_usable_ram_table
(
  usable_ram_part_table_t usable_ram_part_tbl_ptr,
  used_ram_info_ptr_type  used_ram_info_ptr
)
{
  uint32 counter = 0;
  uint32 loop_ctr = 0;
  ram_partition_return_type result = RAM_PART_OTHER_ERR;
  ram_part_entry_t ram_part_entry_ptr = 0;
  uint64 ram_part_start_addr;
  uint64 ram_part_end_addr;
  uint64 used_ram_start_addr = 0;
  uint64 used_ram_end_addr = 0;

  if ( (usable_ram_part_tbl_ptr == NULL) || (used_ram_info_ptr == NULL) )
  {
    result = RAM_PART_NULL_PTR_ERR;
    return result;
  }

  used_ram_start_addr = used_ram_info_ptr->start_address;
  used_ram_end_addr = used_ram_start_addr + used_ram_info_ptr->length - 1;

  counter = usable_ram_part_tbl_ptr->num_partitions - 1;
  loop_ctr = counter;

  /* dummy for loop which loops only once, used for minimizing nested loop
     and breaking on failure out of loop */
  do
  {

    if (usable_ram_part_tbl_ptr->num_partitions==0)
    {
      result = RAM_PART_TABLE_EMPTY_ERR;
      break;
    }

    if (usable_ram_part_tbl_ptr->num_partitions == RAM_NUM_PART_ENTRIES)
    {
      result = RAM_PART_TABLE_FULL_ERR;
      break;
    }

    /* iterate through usable ram partition table and rearrange table
       based on used ram info */
    for ( ; ; counter--)
    {
      /* retrieve ram part entry info at current counter index */
      ram_part_entry_ptr = (ram_part_entry_t)(&usable_ram_part_tbl_ptr->ram_part_entry[counter]);
      ram_part_start_addr = ram_part_entry_ptr->start_address;
      ram_part_end_addr   = ram_part_start_addr + ram_part_entry_ptr->length - 1;

      /* if used ram area is within current usable ram part entry in
         usable part entry table, then rearrange table and remove used ram region */
      if ( (used_ram_start_addr >= ram_part_start_addr) && (used_ram_end_addr <= ram_part_end_addr) )
      {
        /* check if part of or whole usable ram_part_entry of table is in use */
        if (used_ram_start_addr > ram_part_start_addr)
        {
          /* Part of or whole original usable ram_part_entry is in use,
             so original entry is rearranged */
          ram_part_entry_ptr->length = used_ram_info_ptr->start_address - ram_part_entry_ptr->start_address;
          ram_part_entry_ptr->available_length = ram_part_entry_ptr->length;
          /* if only part of original usable ram entry is in use then
             add new entry for rest of unused ram of original usable ram entry */
          if (used_ram_end_addr < ram_part_end_addr)
          {
            for (++loop_ctr; ; loop_ctr--)
            {
              if (loop_ctr == (counter+1))
              {
                if (usable_ram_part_tbl_ptr->num_partitions < RAM_NUM_PART_ENTRIES)
                {
                  /* populate remained part entry info and increment num_partitions */
                  ram_part_entry_ptr = (ram_part_entry_t)(&usable_ram_part_tbl_ptr->ram_part_entry[loop_ctr]);
                  ram_part_entry_ptr->start_address = (used_ram_end_addr + 1);
                  ram_part_entry_ptr->length = (ram_part_end_addr - used_ram_end_addr);
                  /* partition category would be same as the previous partition,
                     as this new entry created as part of previous entry used ram */
                  ram_part_entry_ptr->partition_attribute = usable_ram_part_tbl_ptr->ram_part_entry[counter].partition_attribute;
                  ram_part_entry_ptr->partition_category = usable_ram_part_tbl_ptr->ram_part_entry[counter].partition_category;
                  ram_part_entry_ptr->partition_domain = usable_ram_part_tbl_ptr->ram_part_entry[counter].partition_domain;
                  ram_part_entry_ptr->partition_type = usable_ram_part_tbl_ptr->ram_part_entry[counter].partition_type;
                  ram_part_entry_ptr->num_partitions = usable_ram_part_tbl_ptr->ram_part_entry[counter].num_partitions;
                  ram_part_entry_ptr->hw_info = usable_ram_part_tbl_ptr->ram_part_entry[counter].hw_info;
                  ram_part_entry_ptr->highest_bank_bit = usable_ram_part_tbl_ptr->ram_part_entry[counter].highest_bank_bit;
                  ram_part_entry_ptr->min_pasr_size = usable_ram_part_tbl_ptr->ram_part_entry[counter].min_pasr_size;
                  ram_part_entry_ptr->available_length = ram_part_entry_ptr->length;
                  usable_ram_part_tbl_ptr->num_partitions++;
                  result = RAM_PART_SUCCESS;
                }
                break;
              }
              else
              {
                /* backing up previous part entry to maintain sorted table */
                memscpy((void *)&usable_ram_part_tbl_ptr->ram_part_entry[loop_ctr], sizeof(struct ram_partition_entry), (void *)&usable_ram_part_tbl_ptr->ram_part_entry[(loop_ctr-1)], sizeof(struct ram_partition_entry));
              }
            }
          }
          else
          {
            result = RAM_PART_SUCCESS;
          }
        }
        else
        {
          /* if used ram area is exactly overlapping with usable ram part entry
             then remove usable ram part entry from table */
          if (used_ram_end_addr == ram_part_end_addr)
          {
            for (loop_ctr=counter; ; loop_ctr++)
            {
              if (loop_ctr == (usable_ram_part_tbl_ptr->num_partitions - 1))
              {
                /* remove this entry from table */
                ram_part_entry_ptr = (ram_part_entry_t)(&usable_ram_part_tbl_ptr->ram_part_entry[loop_ctr]);

                memset((void *)ram_part_entry_ptr, 0, sizeof(ram_part_entry_t));

                usable_ram_part_tbl_ptr->num_partitions--;
                result = RAM_PART_SUCCESS;
                break;
              }
              else
              {
                /* pushing table entries up by 1 entry as last entry will be removed */
                memscpy((void *)&usable_ram_part_tbl_ptr->ram_part_entry[loop_ctr], sizeof(struct ram_partition_entry), (void *)&usable_ram_part_tbl_ptr->ram_part_entry[(loop_ctr+1)], sizeof(struct ram_partition_entry));
              }
            }
          }
          else
          {
            /* used ram start_address aligns with usable_ram_part_entry but
               length of used ram is less than length of usable ram.
               Easy!!! just rearrange the start_address and length of
               usable_ram_part_entry */
            ram_part_entry_ptr->start_address = used_ram_end_addr + 1;
            ram_part_entry_ptr->length = ram_part_end_addr - used_ram_end_addr;
            ram_part_entry_ptr->available_length = ram_part_entry_ptr->length;
            result = RAM_PART_SUCCESS;
          }
        }
        break;
      }
      if (counter == 0)
      {
        break;
      }
    }
    break; /* dummy loop to minimize indentation and break on failure */
  } while (FALSE);

  return result;
}

/*===========================================================================
FUNCTION  remove_regions_update_ram_partition_table

DESCRIPTION
  This function removes the used_ram_partitions from ram partition table.

ARGUMENTS
  boot_handle  config context handle passed by caller.
  used_ram_info_ptr_type  list of regions that need to be excluded
  uint32  number of regions in the list

DEPENDENCIES
  boot_populate_ram_partition_table must be called before calling this API

RETURN VALUE
  bl_error_boot_type
    BL_ERR_NONE      if updating used ram partition regions are updated successfully.

SIDE EFFECTS
  None
===========================================================================*/
bl_error_boot_type remove_regions_update_ram_partition_table(boot_handle config_context_handle, used_ram_info_ptr_type used_ram_info_tbl, uint32 num_entries)
{

  ram_partition_return_type result = RAM_PART_OTHER_ERR;
  bl_error_boot_type status = BL_ERR_NONE;
  uint32 used_ram_table_index = 0;
  boot_smem_if_type * smem_if = NULL;
  usable_ram_part_table_t usable_ram_part_tbl_ptr = NULL;
  uint32 table_size = 0;

  used_ram_info_type_struct used_ram_partition_info = {0, 0};

  do
  {
    if (config_context_handle == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    if (num_entries == 0)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MPROC, BL_ERR_INVALID_PARAMETER);
      break;
    }

    status = boot_config_context_get_ptr(config_context_handle, CONFIG_CONTEXT_SMEM_INTERFACE, (void **)&smem_if);
    if (status != BL_ERR_NONE)
    {
      break;
    }
    if (smem_if == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_NULL_PTR_PASSED);
      break;
    }

    usable_ram_part_tbl_ptr = (usable_ram_part_table_t) smem_if->get_addr(SMEM_USABLE_RAM_PARTITION_TABLE, &table_size);
    if (usable_ram_part_tbl_ptr == NULL)
    {
      status = GET_ERROR_CODE(BL_ERROR_GROUP_MPROC, BL_ERR_RAM_PART_DRV_TABLE_POINTER_UNINITIALIZE);
      break;
    }
    /* Loop through used ram regions and call remove each used ram region from ram_partition table */
    for (used_ram_table_index = 0; used_ram_table_index < num_entries; used_ram_table_index++)
    {
      /* raise error if used ram region address or size are 0 when index is less than region count */
      if (used_ram_info_tbl[used_ram_table_index].start_address == 0 || used_ram_info_tbl[used_ram_table_index].length == 0)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_CONFIG_CONTEXT, BL_ERR_INVALID_PARAMETER);
        break;
      }

      used_ram_partition_info.start_address = used_ram_info_tbl[used_ram_table_index].start_address;
      used_ram_partition_info.length = used_ram_info_tbl[used_ram_table_index].length;

      result = remove_used_ram_rearrange_usable_ram_table(usable_ram_part_tbl_ptr, &used_ram_partition_info);
      if (result != RAM_PART_SUCCESS)
      {
        status = GET_ERROR_CODE(BL_ERROR_GROUP_MPROC, result);
        break;
      }
    }

  } while (FALSE);

  return status;
}
