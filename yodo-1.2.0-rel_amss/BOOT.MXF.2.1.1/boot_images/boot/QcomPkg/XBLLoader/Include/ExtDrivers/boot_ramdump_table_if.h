#ifndef BOOT_RAMDUMP_TABLE_IF_H
#define BOOT_RAMDUMP_TABLE_IF_H

/*===========================================================================
                    BOOT SAHARA TABLE HANDLER IF DEFINITIONS

DESCRIPTION
  Contains function pointers for Sahara table handlers

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2021 by Qualcomm Technologies Incorporated.  All Rights Reserved.
============================================================================*/
/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.
    
    
when       who      what, where, why
--------   ---      ----------------------------------------------------------
11/11/20   rhy      Renamed is_dump_support to is_ramdump_allowed
07/10/20   rhy      Inital revision

===========================================================================*/

/*==========================================================================

                               INCLUDE FILES

===========================================================================*/

#include "boot_error_if.h"
#include "boot_framework.h"
#include "boot_comdef.h"
#include "boot_ramdump_table.h"

/*===========================================================================

                     EXTERNAL DEFINITIONS FOR MODULE

===========================================================================*/
#define SCRIPT_BUF_SIZE             32768 

#define POS(x) (x > 0 ? x : 0)

#define DL_LOG(f, ...)  dload_log(f, ##__VA_ARGS__) 

/*debug structure for 32 bits ram dump */
typedef struct 
{
    byte save_pref;
    uintnt mem_base;
    uintnt length;
    char desc[DLOAD_DEBUG_STRLEN_BYTES];
    char filename[DLOAD_DEBUG_STRLEN_BYTES];
}ramdump_table_type;


typedef struct ramdump_table_if
{
    
    /* Initializes the memory debug region table and enables access to each
        accessible region. Calls and allocate target specific memory regions.
    */
    bl_error_boot_type (*open)(const boot_handle, boot_handle *);
    
    /*  Returns TRUE if memory debug is supported in current mode of operation
        i.e. if secure boot is enabled, memory debug not enabled
    */
    bl_error_boot_type (*is_ramdump_allowed) (boot_handle, boot_boolean*);

    /* Returns the address of the memory debug region table. */
    bl_error_boot_type  (*get_table_addr)         (boot_handle, uintnt*);
    
    /* Returns the length in bytes of the memory debug region table. */
    bl_error_boot_type  (*get_table_len)          (boot_handle, uintnt*);
    
    /* Verifies if the input base to base+len is a valid address range
        for memory debug.
        Inputs:
        base - Base address to check for validity
        len  - Length in bytes to check starting from base
    
        Return: TRUE if valid address range; FALSE otherwise
    */
    bl_error_boot_type (*verify_addr)        (boot_handle, 
                                                uint64, 
                                                uint64, 
                                                boot_boolean *);
    /* Verifies if the input base to base+len is a restricted address range
        i.e. the memory range cannot be directly accessed by the hardware
        interface; thus needs to be first copied to a temporary buffer.
        Inputs:
        base - Base address to check for restriction
        len  - Length in bytes to check starting from base
    
        Return: TRUE if restricted address range; FALSE otherwise
    */
    bl_error_boot_type (*verify_restricted_addr) (boot_handle,
                                        uint64 addr, 
                                        uint64 length,
                                        boot_boolean *is_verified);
    
    /* Copies restricted address range to a temporary buffer supplied
        by the Sahara client.
        Inputs:
        base - Address to start copying data from
        len  - Length in bytes to copy from base
    
        Return: Address of temporary buffer if copy was successful
                Set to 0 if copy failed or input address range is invalid
    */
    bl_error_boot_type  (*copy_restricted)    (uint8 *temp_buff,
                                               uint64 addr,
                                               uint64 len);
    
    /*  when sbl sahara encounters an unrecoverable error such as cable unplugged,
        shutdown usb hw and reboot into dload mode*/
    bl_error_boot_type  (*unrecoverable_error_handler) (void);
    
    /* Free the memory debug region table and target specific memory regions too.
    */
    bl_error_boot_type (*close)(const boot_handle, boot_handle);
                                           
}ramdump_table_if;



/*===========================================================================
                      FUNCTION DECLARATIONS
===========================================================================*/

/*===========================================================================
**  Function :  boot_ramdump_table_get_interface
** ==========================================================================
*/
/*!
* 
* @brief
*   This function initializes a boot_sahara_mem_debug_handler_get_interface
*
* @par Dependencies
*   None 
* 
*/

bl_error_boot_type boot_ramdump_table_get_interface(void *);

#endif /* BOOT_RAMDUMP_TABLE_IF_H */
