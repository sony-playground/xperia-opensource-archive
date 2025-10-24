/*=============================================================================

                            XRC RAMDUMP

 RAM dump collection methods.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

#ifndef XRC_RAMDUMP_H
#define XRC_RAMDUMP_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "slvcom.h"

/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/

/*===========================================================================
  FUNCTION  xrc_ramdump_init
===========================================================================*/
/**
  Function to enable access to collect Helios Ram dump   
  @param[in] slvcom_handle_type: handle to the slvcom
   
  @return
  Returns true if enabling of helios ram dump is success
*/
/*==========================================================================*/
boolean xrc_ramdump_init(slvcom_handle_type *phandle);

/*===========================================================================
  FUNCTION  xrc_ramdump_done
===========================================================================*/
/**
  Function to send ramdump done status to Helios and cleanup interfaces.
  @param[in] slvcom_handle_type: handle to the slvcom
   
  @return
  Returns true if cleanup done successfully.
*/
/*==========================================================================*/
boolean xrc_ramdump_done(slvcom_handle_type *phandle);

#ifdef __cplusplus
}
#endif

#endif
