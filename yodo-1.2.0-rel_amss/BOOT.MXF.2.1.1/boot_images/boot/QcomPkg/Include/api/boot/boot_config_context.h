#ifndef BOOT_CONFIG_CONTEXT_H
#define BOOT_CONFIG_CONTEXT_H

/*===========================================================================

                      Boot Config Context Header File

GENERAL DESCRIPTION
  This file contains the interfaces for Config Context module.

Copyright 2019-2022 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/boot/boot_config_context.h#1 $
$DateTime: 2022/08/18 10:15:46 $
$Author: pwbldsvc $

when        who      what, where, why
----------  ---      ----------------------------------------------------------
06/10/22    batta    Added CONFIG_CONTEXT_BOOT_SLVCOM_INTERFACE and CONFIG_CONTEXT_BOOT_XRC_INTERFACE
01/14/22    ck       Added CONFIG_CONTEXT_PCIE_INTERFACE
01/05/22    rama     Added CONFIG_CONTEXT_CHIPINFO_INTERFACE
04/15/21    ds       changes for debuglib addition
05/02/21    ds       added CONFIG_CONTEXT_AOP_LOADED
03/25/21    rhy      Added CONFIG_CONTEXT_ENTRY_PT_MEMORY_REGION_BASE_ADDR and CONFIG_CONTEXT_ENTRY_PT_MEMORY_REGION_SIZE
02/03/21    rama     Added CONFIG_CONTEXT_BUTTONS_INTERFACE
01/26/21    rhy      Added Sahara command handler to params
01/25/21    rhy      Added CONFIG_CONTEXT_SAHARA_STATUS_MAP_INTERFACE
01/24/21    rhy      Added CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE and CONFIG_CONTEXT_RAMDUMP_OR_MINIDUMP_COOKIE
01/21/21    rama     Added CONFIG_CONTEXT_EUD_INTERFACE
12/23/20    rama     Removed CONFIG_CONTEXT_BUILD_TYPE
11/12/20    rama     Renamed CONFIG_CONTEXT_BOOT_EXIT_TO_NS_INTERFACE->CONFIG_CONTEXT_BOOT_EXIT_INTERFACE
11/01/20    ds       Blacklist feature support
09/30/20    rama     Added CONFIG_CONTEXT_BOOT_EXIT_TO_NS_INTERFACE and CONFIG_CONTEXT_BOOT_MODE_INTERFACE
08/24/20    rama     Removed CONFIG_CONTEXT_BL_SHARED_DATA, added CONFIG_CONTEXT_DDR_INITIALIZATON_STATE
07/23/20    rama     Added CONFIG_CONTEXT_PBL_SHARED_DATA_INTERFACE
07/10/20    ck       Added CONFIG_CONTEXT_LOAD_CANCEL_FUNC
07/07/20    ck       Added CONFIG_CONTEXT_BAM_INTERFACE
06/25/20    rama     removed params for sec_img,pimem,seccfg and added param for seclib
06/22/20    ck       Added CONFIG_CONTEXT_ELF_SYNC_TYPE
05/10/20    ds       move to edk2 arm mmu/cache lib
05/13/20    ck       Added EEPROM_INTERFACE to boot_config_context_param_type
04/20/20    rhy      Entry for backed up AOSS_CC_RESET_STATUS for ramdump
04/07/20    rhy      Added MHI and IPA config context
04/06/20    ck       Added NAND_INTERFACE to boot_config_context_param_type
04/05/20   rama      Added qusb to params
02/24/20   rama      Added config context for reset lib
02/23/20    ds       boot_statistics interface
04/03/19    ep       Created the file

===========================================================================*/


/*===========================================================================
                           INCLUDE FILES
===========================================================================*/
#include "boot_framework.h"
#include "boot_comdef.h"
#include "boot_error_if.h"
#include "boot_memory_mgr_if.h"


/*==========================================================================
                          PUBLIC DATA DECLARATIONS
===========================================================================*/

/*
This is the default ConfigContext handle.
There are instances where we would need to access a ConfigCOntext API, but a handle is not available.
This is used as teh default handle (it is assume that a ConfigCOntext was already opened)
*/
#define CONFIG_CONTEXT_CRT_HANDLE    (boot_handle)-1

/*Partition id size in bytes*/
#define PARTITION_ID_MAX_SIZE 16

/*
This is to check the truncation of 64 bit address in 32 bit architecture
*/
#define TRUNC_CHECK_64BIT_TO_32BIT(address) ((uint64)(address) <= (uint64)UINT_MAX)

/*
These are the types of values supported by ConfigContext parameteres.
  PARAMETER_TYPE_PTR = "void *"
  PARAMETER_TYPE_VALUE = "int32"
*/
typedef enum
{
  PARAMETER_TYPE_PTR,
  PARAMETER_TYPE_VALUE,
} config_context_parameter_type;


/*
These are the parameters supported by ConfigContext.
If the upper layer wants to set/get a parameter which is not in this list explicitely, he can use
CONFIG_CONTEXT_CUSTOM_PARAM_* defined at the end
*/
typedef enum
{
  CONFIG_CONTEXT_PRE_PROCS = 0,                                 //_populate_config_context_per_image
  CONFIG_CONTEXT_LOAD_CANCEL_FUNC,                              //_populate_config_context_per_image
  CONFIG_CONTEXT_LOAD_METADATA_FUNC,                            //_populate_config_context_per_image
  CONFIG_CONTEXT_EXEC_PROC,                                     //_populate_config_context_per_image
  CONFIG_CONTEXT_POST_PROCS,                                    //_populate_config_context_per_image
  CONFIG_CONTEXT_JUMP_LOAD_PROC,                                //_populate_config_context_per_image
  CONFIG_CONTEXT_IMAGE_WHITELIST,                               //_populate_config_context_per_image
  CONFIG_CONTEXT_WHITELIST_NUM_ENTRIES,                         //_populate_config_context_per_image
  CONFIG_CONTEXT_TARGET_IMAGE_STR,                              //_populate_config_context_per_image
  CONFIG_CONTEXT_AUTH_INTERFACE,                                //config_context_global_values
  CONFIG_CONTEXT_BOOT_MEDIA_INTERFACE,                          //config_context_global_values
  CONFIG_CONTEXT_MMU_INTERFACE,                                 //
  CONFIG_CONTEXT_WHITELIST_INTERFACE,                           //config_context_global_values
  CONFIG_CONTEXT_BLACKLIST_INTERFACE,                           //config_context_global_values
  CONFIG_CONTEXT_LOADER_INTERFACE,                              //config_context_global_values
  CONFIG_CONTEXT_LOGGER_INTERFACE,                              //config_context_global_values
  CONFIG_CONTEXT_TIMER_INTERFACE,                               //config_context_global_values
  CONFIG_CONTEXT_MEMORY_MGR_INTERFACE,                          //config_context_global_values
  CONFIG_CONTEXT_BAM_INTERFACE,                                 //config_context_global_values
  CONFIG_CONTEXT_BUS_INTERFACE,                                 //config_context_global_values
  CONFIG_CONTEXT_RESET_INTERFACE,                               //config_context_global_values
  CONFIG_CONTEXT_BUSYWAIT_INTERFACE,                            //config_context_global_values
  CONFIG_CONTEXT_CLK_INTERFACE,                                 //config_context_global_values
  CONFIG_CONTEXT_COLDPLUG_INTERFACE,                            //config_context_global_values
  CONFIG_CONTEXT_CRYPTO_INTERFACE,                              //config_context_global_values
  CONFIG_CONTEXT_DAL_INTERFACE,                                 //config_context_global_values
  CONFIG_CONTEXT_DDI_INTERFACE,                                 //config_context_global_values
  CONFIG_CONTEXT_DDR_INTERFACE,                                 //config_context_global_values
  CONFIG_CONTEXT_DDR_INFO_INTERFACE,                            //config_context_global_values
  CONFIG_CONTEXT_EEPROM_INTERFACE,                              //config_context_global_values
  CONFIG_CONTEXT_EFS_INTERFACE,                                 //config_context_global_values
  CONFIG_CONTEXT_NAND_INTERFACE,                                //config_context_global_values
  CONFIG_CONTEXT_PLATFORMINFO_INTERFACE,                        //config_context_global_values
  CONFIG_CONTEXT_PMIC_INTERFACE,                                //config_context_global_values
  CONFIG_CONTEXT_POWER_INTERFACE,                               //config_context_global_values
  CONFIG_CONTEXT_QSEE_INTERFACE,                                //config_context_global_values
  CONFIG_CONTEXT_QUSB_LDR_INTERFACE,                            //config_context_global_values
  CONFIG_CONTEXT_SECLIB_INTERFACE,                              //config_context_global_values
  CONFIG_CONTEXT_BOOT_STATS_INTERFACE,                          //config_context_global_values
  CONFIG_CONTEXT_SECBOOT_INTERFACE,                             //config_context_global_values
  CONFIG_CONTEXT_SMEM_INTERFACE,                                //config_context_global_values
  CONFIG_CONTEXT_TLMM_INTERFACE,                                //config_context_global_values
  CONFIG_CONTEXT_TSENSOR_INTERFACE,                             //config_context_global_values
  CONFIG_CONTEXT_UART_INTERFACE,                                //config_context_global_values
  CONFIG_CONTEXT_VSENSE_INTERFACE,                              //config_context_global_values
  CONFIG_CONTEXT_RAMDUMP_INTERFACE,                             //
  CONFIG_CONTEXT_VISUAL_INDICATOR_INTERFACE,                    //config_context_global_values
  CONFIG_CONTEXT_CONFIG_DATA_INTERFACE,                         //config_context_global_values
  CONFIG_CONTEXT_PBL_MEDIA_BOOT_DEVICE,                         //config_context_global_values
  CONFIG_CONTEXT_BOOT_DEVICE,                                   //config_context_global_values
  CONFIG_CONTEXT_SAHARA_COMMAND_HANDLER_TBL,                    //config_context_global_values
  CONFIG_CONTEXT_RAMDUMP_TABLE_INTERFACE,                       //config_context_global_values
  CONFIG_CONTEXT_RAMDUMP_TABLE_HANDLE,                          //config_context_global_values
  CONFIG_CONTEXT_SAHARA_DISPATCH_TBL,                           //config_context_global_values
  CONFIG_CONTEXT_QUSB_AL_BULK_INTERFACE,                        //config_context_global_values
  CONFIG_CONTEXT_PARTITION_ID,                                  //_populate_config_context_per_image
  CONFIG_CONTEXT_SKIP_AUTH,                                     //_populate_config_context_per_image
  CONFIG_CONTEXT_TIMER_HW_INTERFACE,                            //config_context_global_values
  CONFIG_CONTEXT_MBN_LOADER_INTERFACE,                          //config_context_global_values
  CONFIG_CONTEXT_MHI_INTERFACE,                                 //config_context_global__values
  CONFIG_CONTEXT_IPA_INTERFACE,                                 //config_context_global_values
  CONFIG_CONTEXT_EDK2_CACHE_INTERFACE,                          //config_context_global_values
  CONFIG_CONTEXT_EDK2_MMU_INTERFACE,                            //config_context_global_values
  CONFIG_CONTEXT_EDK2_ARMLIB_INTERFACE,                         //config_context_global_values
  CONFIG_CONTEXT_DDR_INITIALIZATON_STATE,                       //config_context_global_values
  CONFIG_CONTEXT_TARGET_IMAGE_SEC_TYPE,                         //_populate_config_context_per_image
  CONFIG_CONTEXT_HOST_IMAGE_ID,                                 //config_context_global_values
  CONFIG_CONTEXT_ELF_SYNC_TYPE,                                 //config_context_global_values
  CONFIG_CONTEXT_LOAD_FLAG,                                     //_populate_config_context_per_image
  CONFIG_CONTEXT_EXEC_FLAG,                                     //_populate_config_context_per_image
  CONFIG_CONTEXT_JUMP_FLAG,                                     //_populate_config_context_per_image
  CONFIG_CONTEXT_OPTIONAL_IMAGE,                                //_populate_config_context_per_image
  CONFIG_CONTEXT_IMG_ENTRY_POINT,                               //_populate_config_context_per_image
  CONFIG_CONTEXT_IMAGE_TYPE,                                    //_populate_config_context_per_image
  CONFIG_CONTEXT_RAM_PARTITION_TYPE,                            //_populate_config_context_per_image
  CONFIG_CONTEXT_ENTRY_PT_MEMORY_REGION_BASE_ADDR,              //_populate_config_context_per_image
  CONFIG_CONTEXT_ENTRY_PT_MEMORY_REGION_SIZE,                   //_populate_config_context_per_image
  CONFIG_CONTEXT_AOSS_RESET_STATUS_REGISTER,                    //config_context_global_values
  CONFIG_CONTEXT_RAMDUMP_OR_MINIDUMP_COOKIE,                    //config_context_global_values
  CONFIG_CONTEXT_MEDIA_IF_PARTIAL_INIT,                         //config_context_global_values
  CONFIG_CONTEXT_SAHARA_STATUS_MAP_INTERFACE,                   //config_context_global_values
  CONFIG_CONTEXT_PCIE_INTERFACE,                                //config_context_global_values
  CONFIG_CONTEXT_PBL_SHARED_DATA_INTERFACE,
  CONFIG_CONTEXT_BOOT_MODE_INTERFACE,
  CONFIG_CONTEXT_BOOT_EXIT_INTERFACE,
  CONFIG_CONTEXT_CPUCP_INTERFACE,
  CONFIG_CONTEXT_EUD_INTERFACE,
  CONFIG_CONTEXT_BUTTONS_INTERFACE,
  CONFIG_CONTEXT_DBGINFO_INTERFACE,
  CONFIG_CONTEXT_CHIPINFO_INTERFACE,
  CONFIG_CONTEXT_AOP_LOADED,
  CONFIG_CONTEXT_NVME_INTERFACE,
  CONFIG_CONTEXT_RECOVERY_PARTITION_ID,
  CONFIG_CONTEXT_BOOT_SLVCOM_INTERFACE,
  CONFIG_CONTEXT_BOOT_XRC_INTERFACE,
  CONFIG_CONTEXT_CUSTOM_PARAM_START,
  CONFIG_CONTEXT_CUSTOM_PARAM_1 = CONFIG_CONTEXT_CUSTOM_PARAM_START,
  CONFIG_CONTEXT_CUSTOM_PARAM_2,
  CONFIG_CONTEXT_CUSTOM_PARAM_3,
  CONFIG_CONTEXT_CUSTOM_PARAM_4,
  CONFIG_CONTEXT_CUSTOM_PARAM_5,

  CONFIG_CONTEXT_NO_PARAMS
} boot_config_context_param_type;


/*
This type is used to populate the values for parameters of "ptr" type
See boot_config_context_init_ptr_params()
*/
typedef struct boot_config_context_ptr_data
{
  boot_config_context_param_type type;
  void *ptr;
} boot_config_context_ptr_data;


/*
This type is used to populate the values for parameters of "int32" type
See boot_config_context_init_ptr_params()
*/
typedef struct boot_config_context_value_data
{
  boot_config_context_param_type type;
  uint32 value;
} boot_config_context_value_data;


/*
This is a function pointer type used to get a value of a parameter.
This is used to populate the "value" parameters during intialization
*/
typedef bl_error_boot_type (*config_context_get_value_type)(uint32 *);


/*
This is a function pointer type used to populate the fields of a structure (passed by void *)
It's used for initalizations the "pptr" parameters for those parameters which represent pointer to a structure
*/
typedef bl_error_boot_type (*config_context_get_ptr_type)(void *);


/*
This is used for initializing a "value" parameter.
If get_value != NULL, we call the function to intializa the value.
If get_value == NULL, "value" filed is used to initialize the parameter
*/
typedef struct boot_config_context_populate_value
{
  uint32 value;
  config_context_get_value_type get_value;
} boot_config_context_populate_value;


/*
This is used for initializing a "ptr" parameter.
If get_ptr != NULL, ConfigContext allocates "size" memory and call get_ptr() to populate it.
If get_ptr == NULL, the parameter is set to "ptr" value.
*/
typedef struct boot_config_context_populate_ptr
{
  void *ptr;
  uint32 size;
  config_context_get_ptr_type get_ptr;
} boot_config_context_populate_ptr;

/*
This is the maximum number of dependencies for each parameter during initialization.
*/
#define CONFIG_CONTEXT_MAX_DEPENDENCIES    10

/*
This is used for initializing a list of parameteres (both value and ptr) using the same array.
parameter_id = should be some value from boot_config_context_param_type
parameter_type = value of ptr
populate_value = used only for value parameters
populate_ptr = used only for ptr parameters
dependencies = an array of parameters IDs which are dependencies for a particular one.
This means that the dependencies parameteres should be filled before this one, regarless of the oreder
of parameters in the initialization array.
This feature is not implemented yet.
*/
typedef struct boot_config_context_populate_table
{
  uint32 parameter_id;
  config_context_parameter_type parameter_type;
  boot_config_context_populate_value  populate_value;
  boot_config_context_populate_ptr  populate_ptr;
} boot_config_context_populate_table;


/*===========================================================================
                      PUBLIC FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
**  Function :  config_context_open
** ==========================================================================
*/
/*!
*
* @brief
* Open a ConfigContext
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_open(boot_handle *handle, boot_memory_mgr_if_type *mem_if);



/*===========================================================================
**  Function :  config_context_set_crt_handle
** ==========================================================================
*/
/*!
*
* @brief
* Set CRT handle for instance of ConfigContext
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_set_crt_handle(boot_handle handle);

/*===========================================================================
**  Function :  config_context_get_crt_handle
** ==========================================================================
*/
/*!
*
* @brief
* Set CRT handle for instance of ConfigContext
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_get_crt_handle(boot_handle *handle);

/*===========================================================================
**  Function :  config_context_close
** ==========================================================================
*/
/*!
*
* @brief
* Close a ConfigContext
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_close(const boot_handle);

/*===========================================================================
**  Function :  config_context_reset_parameter
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type config_context_reset_parameter(const boot_handle handle, boot_config_context_param_type);



/*===========================================================================
**  Function :  config_context_reset
** ==========================================================================
*/
/*!
*
* @brief
* Remove all the parameters values of a ConfigContext
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_reset_parameters(const boot_handle handle);



/*===========================================================================
**  Function :  config_context_init
** ==========================================================================
*/
/*!
*
* @brief
* Initialize a list of "ptr" parameters
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_init_ptr_params(const boot_handle handle, boot_config_context_ptr_data *init_params, int no_params);



/*===========================================================================
**  Function :  boot_config_context_init_value_params
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   Initialize a list of "value" parameters
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_init_value_params(const boot_handle handle, boot_config_context_value_data *init_params, int no_params);



/*===========================================================================
**  Function :  boot_config_context_get_ptr
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   Return a "ptr" parameter value
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_get_ptr(const boot_handle handle, boot_config_context_param_type, void **);



/*===========================================================================
**  Function :  boot_config_context_get_value
** ==========================================================================
*/
/*!
*
* @brief
* Return a "value" parameter value
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_get_value(const boot_handle handle, boot_config_context_param_type, uint32 *);



/*===========================================================================
**  Function :  boot_config_context_set_ptr
** ==========================================================================
*/
/*!
*
* @brief
* Set a "ptr" parameter value
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_set_ptr(const boot_handle handle, boot_config_context_param_type, void *);



/*===========================================================================
**  Function :  boot_config_context_set_value
** ==========================================================================
*/
/*!
*
* @brief
* Set a "value" parameter value
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_set_value(const boot_handle handle, boot_config_context_param_type, uint32);


/*===========================================================================
**  Function :  boot_config_context_set_parameters
** ==========================================================================
*/
/*!
*
* @brief
* Initialize a list of parameters (both values and ptr)
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_set_parameters(const boot_handle handle, boot_config_context_populate_table *, uint32);


/*===========================================================================
**  Function :  boot_config_context_duplicate
** ==========================================================================
*/
/*!
*
* @brief
*
*
* @par Dependencies
*   None
*
* @retval
*   Success/Error
*
* @par Side Effects
*   None
*/
bl_error_boot_type boot_config_context_duplicate(const boot_handle handle, boot_handle *new_handle);


#endif  /* BOOT_CONFIG_CONTEXT_H */

