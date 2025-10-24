/*==============================================================================

FILE:      icbcfgnull.c

DESCRIPTION: This file implements the ICB Null Configuration driver.


When        Who    What, where, why
----------  ---    -----------------------------------------------------------
2021/10/15  ck     Created
 
        Copyright (c) 2021 QUALCOMM Technologies, Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
==============================================================================*/

#include "icbcfg_common.h"
#include "icbcfg.h"
#include "ddr_common.h"


icbcfg_error_type ICB_Config_Init(const char * dev)
{
   return ICBCFG_SUCCESS;
}


icbcfg_error_type ICB_Config_PostInit(const char * dev)
{
   return ICBCFG_SUCCESS;
}


icbcfg_error_type ICB_Segments_Init(const char * dev,
                                    ddr_info * info)
{
   return ICBCFG_SUCCESS;
}


icbcfg_error_type ICB_RemapEx(const char * dev,
                              ddr_info * info,
                              uint32 index,
                              icbcfg_remap_info_type * remap)
{
   return ICBCFG_SUCCESS;
}


icbcfg_error_type ICB_Remap(const char * dev,
                            ddr_info * info,
                            icbcfg_remap_info_type * remap)
{
   return ICBCFG_SUCCESS;
}


icbcfg_error_type ICB_UnmapTCM(const char * dev)
{
   return ICBCFG_ERROR_UNSUPPORTED;
}
