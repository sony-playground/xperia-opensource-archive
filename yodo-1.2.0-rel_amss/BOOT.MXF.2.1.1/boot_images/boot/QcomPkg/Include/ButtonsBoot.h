#ifndef __BUTTONSBOOT_H__
#define __BUTTONSBOOT_H__
/*============================================================================
  @file buttonsboot.h

  Function and data structure declarations for Buttons Boot 


       Copyright (c) 2019-2020 Qualcomm Technologies, Inc.
       All Rights Reserved.
       Qualcomm Technologies Proprietary and Confidential.
============================================================================*/
/* $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/ButtonsBoot.h#1 $ */

/*-------------------------------------------------------------------------
 * Include Files
 * ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * ----------------------------------------------------------------------*/
/**
 * BUTTON_BMAP: Buttons bit map, each bit represent a signle button press */
#define POWER_BUTTON_BMAP                (1 << 0)
#define VOLUME_UP_BUTTON_BMAP            (1 << 1)
#define VOLUME_DN_BUTTON_BMAP            (1 << 2)
#define HOME_BUTTON_BMAP                 (1 << 3)

/*-------------------------------------------------------------------------
 * Type Declarations
 * ----------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Function Declarations and Documentation
 * ----------------------------------------------------------------------*/
/**
*  @brief Reads the buttons state and store the result 
*
*  @details This function reads the buttons state and store the result
*           for use by the UEFI driver.
*
*/
void CaptureBootButtonsState();

/**
*  @brief Reads the buttons state and return to the caller
*
*  @details This function reads the current buttons state and return the
*           value to the caller
*  @param[out] ButtonState State of the buttons, see definition for BUTTON_BMAP
*  @return 0 For success
*
*/
int32 BootButtonsStateRead(uint32 *ButtonState);

#endif /* #ifndef __BUTTONSBOOT_H__ */

