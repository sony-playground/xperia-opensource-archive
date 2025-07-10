/*=======================================================================*//**
  @file         qusb_al_fast_enum.c

  @brief        Adaptation layer for fast enumeration

  @details      
                In case of data card on PC, BIOS may want to enumerate all
                attached devices in order to check every device against its
                whitelist.
                Application starts stack, polls it until enumeration done,
                then shuts down stack.

                There are 3 flavors:
                - separate descriptor set
                - HDLC descriptor set


                Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
*//*========================================================================*/

/*============================================================================
  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.  Please
  use ISO format for dates.


  when        who       what, where, why
  ----------  ---      -------------------------------------------------------
  08/16/21    ck       Added edit history and copyright  
  
============================================================================*/
#include "qusb_al_bulk.h"

// ===========================================================================
/**
* @function    qusb_al_fast_enum_init
* 
* @brief       Initialize the Function Driver for performing fast enumeration
*
* @param       [IN] speed_required- Maximum Speed Required
*
*          
* @return      None
* 
* @Note        For fast enum, currently we support only HS.   
*/
// ===========================================================================
void qusb_al_fast_enum_init(qusb_max_speed_required_t speed_required)
{
}
// ===========================================================================
/**
* @function    qusb_al_fast_enum_shutdown
* 
* @brief       API to perform the shutdown of the function driver 
*
* @param       None
*
*          
* @return      None
* 
* @Note          
*/
// ===========================================================================
void qusb_al_fast_enum_shutdown(void)
{
}
// ===========================================================================
/**
* @function    qusb_al_fast_enum_poll
* 
* @brief       API to poll for USB events to perform enumeration 
*
* @param       None
*
*          
* @return      TRUE : If SET_CONFIGURED is received
*              FALSE: If SET_CONFIGURED is not received
* 
* @Note          
*/
// ===========================================================================
boolean qusb_al_fast_enum_poll(void)
{
  return FALSE;
}
// ===========================================================================
/**
* @function    qusb_al_do_fast_enum
* 
* @brief       API to perform Fast Enumeration- Extern API 
*
* @param       [IN]- speed_required - Maximum Speed at which the device should 
*                                     be configured
*
*          
* @return      None
* 
* @Note        Sahara Layer should call this function to perform the
*              the enumeration. 
*/
// ===========================================================================
void qusb_al_do_fast_enum(qusb_max_speed_required_t speed_required)
{
}