/****************************************************************************

                 Embedded USB Debugger Library Routines
                 --------------------------------------

DESCRIPTION
This file contains Public APIs for making use of the EUD HW block.

Copyright (c) 2020 QUALCOMM Technologies Incorporated.
All Rights Reserved. Qualcomm Proprietary

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/api/systemdebug/eud/EUD.h#1 $

when       who      what, where, why
--------   ---      ----------------------------------------------------------
03/17/21   amcheriy Added enablement options
07/21/20   amcheriy Created.
******************************************************************************/


#ifndef _EUD_H
#define _EUD_H


#include "com_dtypes.h"

/*
* @typedef        eud_config_type
* @constant       EUD_ENABLE_GPIO         GPIO based enablement
* @constant       EUD_ENABLE_OTHER        Any other form of EUD enablement
* @constant       EUD_ENABLE_MAX          
*/
typedef enum
{
 EUD_ENA_GPIO   = 0x0,
 EUD_ENA_OTHER  = 0x1,
 EUD_ENA_MAX    = 0x2
}eud_ena_type;

/*
* @typedef        eud_err_type
* @constant       EUD_ERR_NONE            Error not detected
* @constant       EUD_ERR_NOT_SUPPORTED   Feature not supported. Not fatal error
* @constant       EUD_ERR_GPIO_CONFIG     Error during GPIO config / detection
* @constant       EUD_ERR_MAX             Max.possible error codes
*/
typedef enum
{
 EUD_ERR_NONE           = 0x0000,
 EUD_ERR_NOT_SUPPORTED  = 0x0001,
 EUD_ERR_GPIO_CONFIG    = 0x0002,
 EUD_ERR_TGT_CONFIG     = 0x0003,
 EUD_ERR_ALREADY_ENUMERATED = 0x0004,
 EUD_ERR_USB_NOT_ALLOW      = 0x0005,
 EUD_ERR_MAX            = 0x7FFF
}eud_err_type;

/*
* @function    EUDEarlyEnable
* @abstract    Enable Embedded USB Debugger early on in boot stages
* @param       None
* @result      Enum of type eud_err_type
* @discussion  Enabled EUD early on after checking state of a physical GPIO pin
*/
eud_err_type EUDEarlyEnable(void);
 
/*
* @function    EUDEnable
* @abstract    Enable Embedded USB Debugger early on in boot stages
* @param       None
* @result      Enum of type eud_err_type
* @discussion  Enable EUD unconditionally
*/
eud_err_type EUDEnable(void);
 
#endif /* _EUD_H */
