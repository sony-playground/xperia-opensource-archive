/*=============================================================================

                            SLVCOM BOOT TARGET File

 Slave Communication Target File.

 Copyright  2021 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/src/slvcom_target_boot.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/


/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "DDIPlatformInfo.h"
#include "DDIChipInfo.h"
#include "slvcom_log.h"


/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/


/*=============================================================================

                     PUBLIC FUNCTION DEFINITION

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_is_target_supported
=============================================================================*/
/**
 * Checks Platform, Chip Info and confirms whether current target is SLV or not
 *
 * @return
 * TRUE - If SLV Target
 * FALSE - If Non-SLV Target
 *
 */
/*===========================================================================*/
boolean slvcom_is_target_supported()
{
	
/* As Boot driver is checking platform sub-type, SLVCOM is by-passing platform 
check and always assumes it to be SLV based platform */
  return TRUE;
}
