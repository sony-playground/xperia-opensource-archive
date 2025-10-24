#ifndef RPMH_COMMON_H
#define RPMH_COMMON_H

/*===========================================================================
                             rpmh_common.h

DESCRIPTION:
  Verbose description of what is defined by this header file. Typically
  describes the service provided by the structs, macros, etc. defined in
  this file.

Copyright (c) 2016-2017 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/

//===========================================================================
//                   Includes and Public Data Declarations
//===========================================================================

//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Constant / Define Declarations
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Type Declarations
//---------------------------------------------------------------------------

/*
 *  The "set" concept associated with making RPMh requests.  
 */
typedef enum
{
  RPMH_SET_ACTIVE = 0, // Commands for this set are applied when the subsystem is active
  RPMH_SET_SLEEP = 1,  // Commands for this set are applied when the subsystem goes to sleep
  RPMH_SET_WAKE = 2,   // Commands for this set are applied when the subsystem wakes up
  RPMH_NUM_SETS
} rpmh_set_enum;

/**
* RPMh driver<-->RSC Hal numbering scheme, RSCSW_DRV_MAPPING, is used for communication between RPMh driver and Hal
* This mapping is a software concept and not same as Drv Id used in SWI. 
* However, this mapping scheme matches the AOSS DRV Id scheme.
* This is defined by HW, and must match the HW implementation.
*
**/

typedef enum {
    RSC_DRV_TZ            = 0,
    RSC_DRV_HLOS          = 1,
    RSC_DRV_AOP           = 2,
    RSC_DRV_DEBUG         = 3,
    RSC_DRV_MODEM_SW      = 4,
    RSC_DRV_MODEM_HW      = 5,
    RSC_DRV_DDR_AUX		  = 6,
    RSC_DRV_ARC_CPRF      = 7,
    RSC_DRV_MAX,



    //virtual DRVs
    RSC_DRV_VIRTUAL_DRVS = 0x3FFFFF00,
    RSC_DRV_VIRTUAL_SENSORS, 		
    RSC_DRV_VIRTUAL_MAX = 0x3FFFFFFF,
} RSCSW_DRV_MAPPING;

//---------------------------------------------------------------------------
// Forward Declarations
//---------------------------------------------------------------------------

//===========================================================================
//                             Function Definitions
//===========================================================================

#endif /* RPMH_COMMON_H */

