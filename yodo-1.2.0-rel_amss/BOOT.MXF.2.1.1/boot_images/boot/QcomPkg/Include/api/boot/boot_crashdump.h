#ifndef BOOT_CRASHDUMP_H
#define BOOT_CRASHDUMP_H

/*===========================================================================

                        Boot Downloader
                          Header File 

DESCRIPTION
 Contains common defintion used by boot downloader.

INITIALIZATION AND SEQUENCING REQUIREMENTS
  None
  
Copyright 2019-2021 by Qualcomm Technologies, Inc.  All Rights Reserved.
============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.


when       who     what, where, why
--------   ---     ----------------------------------------------------------
07/08/21   ck      Updated boot_dload_transition_pbl_forced_dload signature
06/24/21   rama    Added boot_minidump_set_cookie
============================================================================*/

/*===========================================================================
 
                           INCLUDE FILES

===========================================================================*/
#include "boot_comdef.h"
#include "boot_config_context.h"
/*===========================================================================

                     PUBLIC TYPE DEFINITIONS

===========================================================================*/

/*===========================================================================

                      PUBLIC DATA DECLARATIONS

===========================================================================*/

/* In Bear family SBL owns four bits in the BOOT_MISC_DETECT register.
   In this register one bit tells SBL to enter download mode.  The following
   mask and bit field definition dictate what bits SBL owns and which one
   enables download mode. */
#define SBL_BOOT_MISC_DETECT_MASK        0x000000F0
#define SBL_DLOAD_MODE_BIT_MASK          0x00000010
#define SBL_MINIDUMP_MODE_BIT_MASK       0x00000020

#define SBL_BOOT_MISC_DETECT_MASK_V1     0x00F00000
#define SBL_DLOAD_MODE_BIT_MASK_V1       0x00100000
#define SBL_DLOAD_MODE_BIT_MASK_V1_SHFT  20

/* MASK for setting force download timeout reset warm boot cookie */
#define FORCE_DLOAD_TIMEOUT_RESET_WARM_BOOT_COOKIE 0x1000   /* bit 12 of TCSR_BOOT_MISC_DETECT reg */

/*!
 *  This function pointer is defined in each SBL* Bootloader to handle SBL-specific
 *  requirements to enter a download routine. It serves as an entry point of dload mode
 */
extern void (*sbl_dload_entry)( boot_handle );

/*===========================================================================

                      PUBLIC FUNCTION DECLARATIONS

===========================================================================*/

/*===========================================================================

FUNCTION  BOOT_DLOAD_ENTRY

DESCRIPTION
  Determines if identifier is present in IRAM to tell OEMSBL to enter
  the boot downloader, instead on continuing the normal boot process.
  
DEPENDENCIES
  Data in IRAM is retained across a reset.
  
RETURN VALUE
  TRUE indicates downloader should be entered.

SIDE EFFECTS
  None

===========================================================================*/
boolean boot_dload_entry( void );

/*===========================================================================

FUNCTION  BOOT_DLOAD_IS_DLOAD_MODE_SET

DESCRIPTION
This function shall return if the dload cookie is set or not for the
phone to go in download mode.

DEPENDENCIES
  Data in IRAM is retained across a reset.
  
RETURN VALUE
  TRUE indicates cookies are set
  FALSE cookies are not set
  
SIDE EFFECTS
  None

===========================================================================*/
boolean boot_dload_is_dload_mode_set( void );

/*=============================================================================

**  Function :  boot_dload_transition_pbl_forced_dload

** ==========================================================================
*/
/*!
* 
* @brief
*   This function sets the magic numbers for PBL to detect and enter forced
*   download mode.  It then calls the target specific function to trigger a
*   system reset.
* 
* @par Dependencies
*   None
*   
* @retval
*   bl_error_boot_type
* 
* @par Side Effects
*   Set's PBL magic numbers to enter forced download, resets target, never to
*   return.
* 
*/
bl_error_boot_type boot_dload_transition_pbl_forced_dload(boot_handle);


/*===========================================================================

**  Function :  boot_init_for_dload

** ==========================================================================
*/
/*!
* 
* @brief
*   Wrapper function that calls smem_boot_debug_init().
*  
* @param[in] bl_shared_data Pointer to shared data structure
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
bl_error_boot_type boot_init_for_dload(boot_handle config_context_handle);

/*===========================================================================

**  Function :  boot_dload_transition_enter_sahara

** ==========================================================================
*/
/*!
* 
* @brief
*   This function is implemented in each SBL to enter sahara dload mode
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
void boot_dload_transition_enter_sahara(void);


/*===========================================================================
**  Function :  boot_dload_set_cookie
** ==========================================================================
*/
/*!
* 
* @brief
*   Set the SBL dload mode cookie
**        
* @par Dependencies
*  None
*   
*/
void boot_dload_set_cookie(void);

/*===========================================================================
**  Function :  boot_minidump_set_cookie
** ==========================================================================
*/
/*!
* 
* @brief
*   Set the SBL minidump mode cookie
**        
* @par Dependencies
*  None
*   
*/
void boot_minidump_set_cookie( void );

/*===========================================================================
**  Function :  boot_smem_alloc_for_minidump
** ==========================================================================
*/
/*!
* 
* @brief
*   Allocate SMEM memory for minidump usage
**        
* @param[in] bl_shared_data Pointer to the shared data 
*
* @par Dependencies
*  None
*   
*/
bl_error_boot_type boot_smem_alloc_for_minidump(boot_handle config_context_handle);

/*===========================================================================
**  Function :  boot_dload_read_saved_cookie
** ==========================================================================
*/
/*!
* 
* @brief
*   Return the saved cookie value
**        
* @param[out] saved cookie value
*
* @par Dependencies
*  None
*   
*/
uint32 boot_dload_read_saved_cookie(void);

/*===========================================================================

FUNCTION  boot_dload_is_forced_dload_timeout_set

DESCRIPTION
  This function shall return if the forced dload timeout reset cookie  is set or not

DEPENDENCIES
  Data in BOOT_MISC_DETECT.
  
RETURN VALUE
  TRUE indicates cookies are set
  FALSE cookies are not set
  
SIDE EFFECTS
  None

===========================================================================*/
boolean boot_dload_is_forced_dload_timeout_set(void);

/*=============================================================================

**  Function :  boot_dload_handle_forced_dload_timeout

** ==========================================================================
*/
/*!
* 
* @brief
*   This function checks if PBL set FORCE_DLOAD_TIMEOUT_RESET_WARM_BOOT_COOKIE
*   If set then calls the target specific function to trigger a
*   system reset.
* 
* @par Dependencies
*   None
*   
* @retval
*   None
* 
* @par Side Effects
*   resets target, if cookie is set
* 
*/
bl_error_boot_type boot_dload_handle_forced_dload_timeout(boot_handle config_context_handle);
#endif /* BOOT_DLOAD_H */
