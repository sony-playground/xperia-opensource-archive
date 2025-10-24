#ifndef BOOT_RAM_PARTITION_DRV_H
#define BOOT_RAM_PARTITION_DRV_H

/*===========================================================================

              RAM Partition Table Function Definitions Header File

GENERAL DESCRIPTION
  This header file gives boot specific external definition for RAM 
  Partition Table feature implementation.
  
Copyright 2019-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
===========================================================================*/


/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/17/21   rama    Added boot_update_syndrome_regions
03/25/21   rhy     Added custom error wrt to ram_partition_return_type

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "com_dtypes.h"
#include "ram_partition.h"
#include "boot_sbl_if.h"
#include "boot_sbl_shared.h"
#include "boot_error_if.h"

#define BL_ERR_RAM_PART_CUSTOM_ERROR_START  0x100


/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

typedef enum
{
  BL_ERR_RAM_PART_SUCCESS           =       BL_ERR_CUSTOM_ERRORS_START,
  BL_ERR_RAM_PART_NULL_PTR_ERR,             /**< Partition table/entry null pointer */
  BL_ERR_RAM_PART_OUT_OF_BOUND_PTR_ERR,     /**< Partition table pointer is not in SMEM */
  BL_ERR_RAM_PART_TABLE_EMPTY_ERR,          /**< Trying to delete entry from empty table */
  BL_ERR_RAM_PART_TABLE_FULL_ERR,           /**< Trying to add entry to full table */
  BL_ERR_RAM_PART_CATEGORY_NOT_EXIST_ERR,   /**< Partition doesn't belong to any memory category */
  BL_ERR_RAM_PART_OTHER_ERR,                /**< Unknown error */
  
  BL_ERR_RAM_PART_DRV_TABLE_POINTER_UNINITIALIZE    =   BL_ERR_RAM_PART_CUSTOM_ERROR_START
  
} bl_error_ram_partition_drv_type;

/*===========================================================================

**  Function :  boot_populate_ram_partition_table

** ==========================================================================
*/
/*!
* 
* @brief
*    Function initializes usable_ram_partition_table in shared memory.
*    Then for each type of memory (system memories,boot memory and appsbl memory),
*    this function adds a partition entry in the ram partition table
*    Once complete, function writes magic numbers and version number into table. 
* 
* @param[in] bl_shared_data Pointer to the shared data structure
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
bl_error_boot_type boot_populate_ram_partition_table(boot_handle config_context_handle);

  
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
*                                     category.
* 
* @par Side Effects
*   None
*/
ram_partition_return_type get_partition_category(usable_ram_part_table_t ,
                                                 uintnt,
                                                 uint32 *);

/*===========================================================================

**  Function :  boot_add_single_ram_partition_table_entry

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
*  None
* 
* @retval
*  None
*
* @par Side Effects
*  None
*/
bl_error_boot_type boot_add_single_ram_partition_table_entry(boot_handle config_context_handle,
                                                                uintnt start_address,
                                                                uintnt length,
                                                                uint32 partition_attribute,
                                                                uint32 partition_category,
                                                                uint32 partition_domain,
                                                                uint32 partition_type );


/*===========================================================================

**  Function :  remove_regions_update_ram_partition_table

** ==========================================================================
*/
/*!
*
* @brief
*    A wrapper function to exclude a set of regions from ram partition table
*
* @param[in]  boot_handle
* @param[in]  used_ram_info_ptr_type
* @param[in]  uint32
* 
* @par Dependencies
*  boot_populate_ram_partition_table must be called before calling this API
* 
* @retval
*  None
*
* @par Side Effects
*  None
*/
bl_error_boot_type remove_regions_update_ram_partition_table(boot_handle config_context_handle, used_ram_info_ptr_type used_ram_info_tbl, uint32 num_entries);

#endif /* BOOT_RAM_PARTITION_H */
