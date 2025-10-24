#ifndef XBL_CONFIG_H
#define XBL_CONFIG_H

/*=============================================================================

                            XBLConfig Module Sources

GENERAL DESCRIPTION
  This file defines XBL config api's to support initializing XBLconfig module
  and access a config item.

Copyright 2016, 2017, 2020-2022 by Qualcomm Technologies, Inc.  All Rights Reserved.
=============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.


when         who     what, where, why
----------   ---     ----------------------------------------------------------
05/11/22     tmt      Add pOemVariant parameter to platforminfo
04/19/22     yps      Add apis to support dtbo
12/20/21     yps      Add chipinfo and platforminfo hierarchy structures
11/11/21     tmt      Fix xblconfig_status_type xblconfig_create_platforminfo() encoding
06/25/21     tmt      Add DTB support: xblconfig_open_by_hwinfo, xblconfig_chipinfo, xblconfig_platforminfo
10/16/20     rama     Added initialization mode to xblconfig_init
05/10/17     kpa      rename XBLCONFIG_SIZE_OVERFLOW_ERR to XBLCONFIG_OVERFLOW_ERR
03/10/17     kpa      Added error codes, update xblconfig_read parameters
03/03/17     kpa      Added error type and XCFG_LOADER_MAGIC_COOKIE_SIZE
02/14/17     kpa      Rename XBLCONFIG_ERR_NONE to XBLCONFIG_SUCCESS
01/20/17     kpa      Update magic cookie
10/14/16     kpa      Initial version
===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/
#include "boot_framework.h"
#include "boot_comdef.h"



/*===========================================================================
                      DATA DECLARATIONS
===========================================================================*/

#define XCFG_LOADER_MAGIC_COOKIE_SIZE  4

/*  Define XBL config loader magic number "CFGL" */
#define XCFG_LOADER_MAG0_INDEX    0      /* Header identification byte 0 index */
#define XCFG_LOADER_MAG0         'C'     /* Magic number byte 0              */

#define XCFG_LOADER_MAG1_INDEX    1      /* Header identification byte 1 index */
#define XCFG_LOADER_MAG1         'F'     /* Magic number byte 1              */

#define XCFG_LOADER_MAG2_INDEX    2     /* Header identification byte 2 index */
#define XCFG_LOADER_MAG2         'G'    /* Magic number byte 2              */

#define XCFG_LOADER_MAG3_INDEX    3     /* Header identification byte 3 index */
#define XCFG_LOADER_MAG3         'L'    /* Magic number byte 3              */


/*  Define XBL config Core magic number "CFGU" */
#define XCFG_CORE_MAG0_INDEX    0      /* Header identification byte 0 index */
#define XCFG_CORE_MAG0         'C'     /* Magic number byte 0              */

#define XCFG_CORE_MAG1_INDEX    1      /* Header identification byte 1 index */
#define XCFG_CORE_MAG1         'F'     /* Magic number byte 1              */

#define XCFG_CORE_MAG2_INDEX    2     /* Header identification byte 2 index */
#define XCFG_CORE_MAG2         'G'    /* Magic number byte 2              */

#define XCFG_CORE_MAG3_INDEX    3     /* Header identification byte 3 index */
#define XCFG_CORE_MAG3         'U'    /* Magic number byte 3              */



#define XBL_CONFIG_MAJOR_VERSION          0X2
#define XBL_CONFIG_MINOR_VERSION          0X0

#define XBL_CONFIG_MAX_NUM_ENTRIES        0X9
#define XBL_CONFIG_MAX_HANDLES            0X5


typedef struct xcfg_metadata_header_type
{
  uint32 xcfg_type;
  uint8 major_version; 
  uint8 minor_version; 
  uint16 number_of_entries; 
  uint32 XBLconfig_meta_size;
} xcfg_metadata_header_type;


typedef struct xcfg_metadata_table_entries_type
{
  uint32 attributes;
  uint32 offset_from_meta_start; 
  uint32 size;
  uint64 chipinfo;
  uint64 platforminfo;
  uint32 config_name_len; 
  char   config_name_start;
} __attribute__ ((packed)) xcfg_metadata_table_entries_type;


typedef struct xcfg_parsed_metadata_table_entry_type
{
  /* pointer to start of entry in blob */
  xcfg_metadata_table_entries_type *entry_ptr;

}xcfg_parsed_metadata_table_entry_type;

typedef struct xcfg_config_handle_type
{
  uintnt config_entry_index;
  boolean is_valid;
}xcfg_config_handle_type;

typedef struct chipinfo_hierarchy
{
  uint16 reserved; 
  uint8  Minor_version;
  uint8  Major_version;
  uint16 ChipId;
  uint16 ChipFamily;
} __attribute__ ((packed)) chipinfo_hierarchy_type;

typedef struct platfrominfo_hierarchy
{
  uint16 reserved2;
  uint8  reserved1;
  uint8  Oem_flavor_id;
  uint8  Minor_version;
  uint8  Major_version;
  uint8  PlatformSubtype; 
  uint8  Platformtype;
} __attribute__ ((packed)) platfrominfo_hierarchy_type;


/*---------------------------------------------------------------------------
 ENUMS FOR INITIALIZING XBL CONFIG FROM LOADER,RAM ELF AND RAM ADDRESS
 ---------------------------------------------------------------------------*/
typedef enum
{
  XBLCONFIG_INIT_FROM_FLASH = 0,
  XBLCONFIG_INIT_FROM_RAM_ADDRESS
}xblconfig_init_mode_type;
/*---------------------------------------------------------------------------
 ERRORS FROM XBL CONFIG
 ---------------------------------------------------------------------------*/
typedef enum
{
  XBLCONFIG_SUCCESS                            = 0X0000,
  XBLCONFIG_ITEM_NOT_FOUND                     = 0X0001,
  XBLCONFIG_INVALID_SIZE                       = 0X0002,
  XBLCONFIG_META_DATA_LOAD_ERR                 = 0X0003,  
  XBLCONFIG_CONFIG_DATA_LOAD_ERR               = 0X0004,  
  XBLCONFIG_INIT_ERR                           = 0X0005,
  XBLCONFIG_OPEN_ERR                           = 0X0006,
  XBLCONFIG_READ_ERR                           = 0X0007,
  XBLCONFIG_CLOSE_ERR                          = 0X0008,
  XBLCONFIG_MEMORY_ALLOCATION_ERR              = 0X0009,
  XBLCONFIG_HASH_SEG_ERR                       = 0X000A,
  XBLCONFIG_NULL_PTR_ERR                       = 0X000B,  
  XBLCONFIG_HANDLE_ERR                         = 0X000C,  
  XBLCONFIG_VERIFY_ERR                         = 0X000D,  
  XBLCONFIG_UNINITIALIZED                      = 0X000E,  
  XBLCONFIG_BUFFER_VALIDATION_ERR              = 0X000F,  
  XBLCONFIG_RAM_ELF_INFO_INIT_ERR              = 0X0010,
  XBLCONFIG_MEMORY_FREE_ERR                    = 0X0011,
  XBLCONFIG_DEINIT_ERR                         = 0X0012,  
  XBLCONFIG_OVERFLOW_ERR                       = 0X0013,  
  XBLCONFIG_INVALID_NAME                       = 0X0014,
  XBLCONFIG_CHIPFAMILY_DTB_NOTFOUND            = 0X0015,
  XBLCONFIG_DTBO_NOTFOUND                      = 0X0016,
  XBLCONFIG_DTBO_MERGE_FAILED                  = 0X0017,
  XBLCONFIG_ADD_SORT_LIST_FAILED               = 0X0018,
  XBLCONFIG_INVALID_DTBO_STATE                 = 0X0019,
  XBLCONFIG_ERR_MAX                            = 0x7FFF
} xblconfig_status_type, cfg_status_type;



typedef enum
{
  CFG_GET_INITIALIZED                        = 0X0000,
  CFG_GET_SOC_DTBO                           = CFG_GET_INITIALIZED,
  CFG_GET_PLAT_DTBO                          ,
  CFG_GET_MAX_DTBO                                                             
} cfg_dtbo_state_type;
/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/


/*===========================================================================
**  Function :  xblconfig_init
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes xblconfig module
* 
* @param[in] 
*   boot_handle     handle passed by caller
*   xbconfig_init_mode_type    mode of initialization(from elf, start addr or flash)
*        
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xblconfig_init(boot_handle, xblconfig_init_mode_type);

/*===========================================================================
**  Function :  xblconfig_open
** ==========================================================================
*/
/*!
* 
* @brief
*   This function parses xbl config meta data to locate config item and
*   returns a config handle if found, along with its size
*
* @param[in]    config_name       Null terminated config item name string
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*        
* @par Dependencies
*   XBLConfig module should have been initialized via xblconfig_init
*   before calling xblconfig_open
*   
* @retval
*   xblconfig_status_type   Status of operation
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xblconfig_open
(
  const char *config_name,
  uint32 *config_handle,
  uint32 *config_item_size
);

/*===========================================================================
**  Function :  xblconfig_create_chipinfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the chipinfo value as used by xblconfig_open_by_hwinfo
*   Per XBLConfig v2.0 spec, chipinfo parameter (uint64) is created thusly...
*     [63..48] Chip_Family
*     [47..32] Chip_ID
*     [31..24] Major_Version
*     [23..16] Minor_Version
*     [15..0]  Reserved
*
* @param[in]         cFamily                  16-bit Chip_Family
*                    cId                      16-bit Chip_ID
*                    cVersion                 16-bit Major_Minor_Version
*
* @param[out]        chipinfo                 64-bit chip code
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_create_chipinfo
(
  uint16   cFamily,
  uint16   cID,
  uint16   cVersion,
  uint64  *chipinfo
);


/*===========================================================================
**  Function :  xblconfig_create_platforminfo
** ==========================================================================
*/
/*!
*
* @brief
*   This function returns the platforminfo value as used by xblconfig_open_by_hwinfo
*   Per XBLConfig v2.0 spec, platforminfo parameter (uint64) is created thusly...
*     [63..56] Platform_Type    
*     [55..48] Platform_SubType
*     [47..40] Major_Version
*     [39..32] Minor_Version
*     [31..0]  Reserved
*
* @param[in]         pType                        8-bit platform Type
*                    pVersion                     16-bit Platform Version
*                    pSubtype                     8-bit Platform SubType
*                    pOemVariant                  8-bit OEM Variant Id
*
* @param[out]        platforminfo                 64-bit platform code
*
* @par Dependencies
*   None
*
* @retval
*   xblconfig_status_type   Status of operation
*
* @par Side Effects
*   None
*
*/
xblconfig_status_type xblconfig_create_platforminfo
(
  uint8     pType,
  uint16   pVersion,
  uint8    pSubtype,
  uint8    pOemVariant,
  uint64  *platforminfo
);


/*===========================================================================
**  Function :  xblconfig_open_by_hwinfo
** ==========================================================================
*/
/*!
* 
* @brief
*   This function parses xbl config meta data to locate config item and
*   returns a config handle if found, along with its size
*
* @param[in]    config_name       Null terminated config item name string
*
* @param[out]   config_handle     Config item handle, if found
*               config_item_size  Total size of config item
*        
* @par Dependencies
*   XBLConfig module should have been initialized via xblconfig_init
*   before calling xblconfig_open
*   
* @retval
*   xblconfig_status_type   Status of operation
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xblconfig_open_by_hwinfo
(
  uint64 chipinfo,
  uint64 platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size
);

 /*===========================================================================
 **  Function :  cfg_item_config_open_next_dtbo
 ** ==========================================================================
 */
 /*!
 *
 * @brief
 *   This function parses config items to get best match DTBO binary
 * @param[in]        chipinfo                 64-bit chip code
 *                   platforminfo             64-bit platform code
 *                   config_name_starts_with  Null terminated config item [partial] name string
 *                   state                    which DTBO to get. 
 *
 * @param[out]   config_handle     Config item handle, if found
 *               config_item_size  Total size of config item
 *               state             current match states.
 *
 * @par Dependencies
 *   XBLConfig module should have been initialized via xblconfig_init
 *   before calling xblconfig_open
 *
 * @retval
 *   xblconfig_status_type   Status of operation
 *
 * @par Side Effects
 *   None
 *
 */
xblconfig_status_type cfg_item_config_open_next_dtbo
(
  uint64  chipinfo,
  uint64  platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size,
  cfg_dtbo_state_type *state
);
 /*===========================================================================
 **  Function :  cfg_item_config_open_first_dtb
 ** ==========================================================================
 */
 /*!
 *
 * @brief
 *   This function parses xbl config meta data to locate config item and
 *   returns a config handle if found, along with its size
 *
 * @param[in]        chipinfo                 64-bit chip code
 *                   platforminfo             64-bit platform code
 *                   config_name_starts_with  Null terminated config item [partial] name string
 *
 * @param[out]   config_handle     Config item handle, if found
 *               config_item_size  Total size of config item
 *
 * @par Dependencies
 *   config module should have been initialized via xblconfig_init
 *   before calling xblconfig_open
 *
 * @retval
 *   xblconfig_status_type   Status of operation
 *
 * @par Side Effects
 *   None
 *
 */
xblconfig_status_type cfg_item_config_open_first_dtb
(
  uint64  chipinfo,
  uint64  platforminfo,
  const char *config_name_starts_with,
  uint32 *config_handle,
  uint32 *config_item_size
);
/*===========================================================================
**  Function :  xblconfig_read
** ==========================================================================
*/
/*!
* 
* @brief
*   This function copies config item data equal to input "size" from read offset
*   into provided buffer
* 
* @param[in]    config_handle   Handle to identify config item to be read
*               read_offset     Offset within config item to start read
*               size            Size of data to be read
*
* @param[out]   buffer          Data buffer provided by callee for reading data
*                    
* @par Dependencies
*   NOTE:   The user of xblconfig_read api has to allocate memory and
*           point it via buffer for loading data.
*   
* @retval
*   xblconfig_status_type   Status of operation
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xblconfig_read
( 
  const uint32 config_handle,
  uint32 read_offset,
  uint32 size,
  void *buffer
);

/*===========================================================================
**  Function :  xblconfig_close
** ==========================================================================
*/
/*!
* 
* @brief
*   This function free's config handle to be closed(sets to 0)
* 
* @param[in]  config_handle   Handle to be closed
*   None
*        
* @par Dependencies
*   NOTE:   The user of xblconfig_close api has to free memory 
*           used for reads associated with the handle to be closed.
*   
* @retval
*   xblconfig_status_type   Status of operation
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xblconfig_close (uint32 config_handle);

/*===========================================================================
**  Function :  xblconfig_deinit
** ==========================================================================
*/
/*!
* 
* @brief
*   This function deinitializes xblconfig module. Free's all internal allocated
*   buffers
* 
* @param[in] 
*   None
*        
* @par Dependencies
*   None
*   
* @retval
*   xblconfig_status_type   Status of operation
* 
* @par Side Effects
*   None
* 
*/
xblconfig_status_type xblconfig_deinit(void);

#endif /* XBL_CONFIG_H */

