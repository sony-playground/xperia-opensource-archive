#ifndef BOOT_CONFIG_DATA_IF_H
#define BOOT_CONFIG_DATA_IF_H

/*===========================================================================

                    BOOT CONFIG DATA TABLE DEFINITIONS

DESCRIPTION
  Contains definition of the config data table which is stored in eeprom

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2010-2015 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/27/15   kpa     Added prototypes for boot_cdt_contains_ddr_cdb and
                   boot_config_data_table_default_init
06/09/14   kpa     Update to support 64-bit MSM8996, different PACK syntax
12/20/13   kpa     Added boot_get_eepromII_info
12/05/12   jz      Added boot_update_config_data_table
10/25/11   dh      Add boot_copy_config_data_block
10/18/10   dh      Add cdt_info structure
09/08/10   dh      Add logic to read EEPROM
08/19/10   dh      Initial Creation.

===========================================================================*/
/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "boot_framework.h"
#include "boot_error_if.h"

/*  CDT FORMAT  */ 
/*===========================================================================
magic number: uint32
version     : uint16
reserved 1  : 32 bits
reserved 2  : 32 bits

block0 meta data: 32 bits (see BLOCK META DATA FORMAT for detail)
block1 meta data: 32 bits
....
blockN meta data: 32 bits

block0 data : user defined length 
block1 data : user defined length 
....
blockN data : user defined length 
=============================================================================*/

/* BLOCK META DATA FORMAT*/
/*=============================================================================
data offset      : uint16
block size       : uint16
=============================================================================*/

/*=============================================================================

            LOCAL DEFINITIONS AND DECLARATIONS FOR MODULE

This section contains local definitions for constants, macros, types,
variables and other items needed by this module.

=============================================================================*/
/**
 * 4 bytes.
 * Used in identifying valid cdt table.
 * It's the null ended ascii string "CDT"
 */
#define CONFIG_DATA_MAGIC 0x00544443


/** 
 * max size of the cdt in memory in bytes
 */
#define CONFIG_DATA_TABLE_MAX_SIZE 1024


/**
 * structure that holds an pointer to cdt and its actual size in bytes
 */
struct cdt_info
{
  /*size of the whole table*/
  uint32 size;
  /*pointer to array that contains the whole table's data*/
  uint8 *cdt_ptr;
};


/**
 * Structure that defines the header of configuration data table.
 */
struct PACK(cdt_header)
{
  uint32 magic;         /**< Magic number to identify valid cdt table */
  uint16 version;       /**< Version number to track structure definition 
                             changes and maintain backward compatibilities */
  uint32 reserved1;     /**< Reserved */
  uint32 reserved2;     /**< Reserved */
  /*pack the struct because the compiler defults at 4 bytes alignement*/
}; 


/**
 * Structure that defines the meta data of each block
 */
struct PACK(cdb_meta)
{
  uint16 offset;   /**< offset to the first byte of data of this block, 
                        it's relative to the starting location of cdt */
  uint16 size;     /**< size of this block's data in bytes*/
  /*pack the struct because the compiler defults at 4 bytes alignement*/
}; 


/**
 * Index of configuration data block
 */
typedef enum
{
  CONFIG_DATA_BLOCK_INDEX_V1_PLATFORM_ID = 0,
  CONFIG_DATA_BLOCK_INDEX_V1_DDR = 1,  
  /*force 4 bytes enum size*/
  CONFIG_DATA_BLOCK_INDEX_TYPE_MAX_SIZE = 0x7FFFFFFF
}config_data_block_index_type;

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

void boot_update_config_data_table(struct cdt_info *cdt_info_ptr); //!!!
boolean boot_cdt_contains_ddr_cdb(void);  //!!!



typedef struct boot_config_data_if_type
{
  bl_error_boot_type (*init)(boot_handle config_context_handle);
  bl_error_boot_type (*deinit)(void);
  uint8* (*get_config_data_block)(
                  const uint8 *raw_cdt, 
                  uint32 index, 
                  uint32 *length);
  boot_boolean (*copy_config_data_block)(
                  uint8 *dst_cdt, 
                  uint32 cdb_index, 
                  const uint8 *src_cdb_data, 
                  uint32 src_cdb_size);
  bl_error_boot_type (*config_data_table_init)(void);
  bl_error_boot_type (*config_data_table_default_init)(void);
//  void (*update_config_data_table)(struct cdt_info *cdt_info_ptr);
} boot_config_data_if_type;


/*===========================================================================
**  Function :  boot_config_data_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_config_data_get_interface object 
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_config_data_get_interface(void *ptr);

#endif /* BOOT_CONFIG_DATA_IF_H */
