/** @file SdccLoaderClockLib.c

  SDCC Loader clock driver BSP
  This file implements the SDCC driver BSP for XBL Loader clocks

  Copyright (c) 2016-2017, 2020 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
2020-06-04   jt      Add clock frequencies for other voltage corners  
2020-04-28   jt      Waipio updates 
2017-08-09   jt      Don't restrict SDC2 clocks to 100 MHz
2016-05-13   jt      Use busywait instead of MicroSecondDelay  
2016-01-18   jt      Initial version. Branch from 8996 XBL 

=============================================================================*/

#include "SdccBsp.h"
#include "msmhwiobase.h"
#include "HALhwio.h"
#include <api/systemdrivers/busywait.h>
#include "Clock.h"

typedef struct _SDCC_CLOCK_INFO
{
   char* const clock_name;
   ClockIdType clock_id;
}SDCC_CLOCK_INFO;

static SDCC_CLOCK_INFO sdcc_clocks_array[] =
{
  {0},
  {"sdcc2", 0}, 
  {0},
  {"sdcc4", 0}, 
};

static BOOLEAN sdcc_clock_initialized = FALSE;
static ClockHandle clock_handle;

/******************************************************************************
                           S D C C    B S P
******************************************************************************/

/******************************************************************************
* Name: sdcc_bsp_initialize_clock
*
* Description:
*    This function initializes clocks for all SDCs
*
* Arguments:
*    None
* Returns:
*    sdcc_bsp_err_type: SDCC_BSP_NO_ERROR means success. Error otherwise.
*
******************************************************************************/
static sdcc_bsp_err_type
sdcc_bsp_initialize_clock (VOID)
{
   ClockResult  eResult = CLOCK_SUCCESS;
   UINT8  driveno = 0;
   UINT32 sdcc_bsp_num_slots = 0;
   
   if (!clock_handle)
   {
       eResult = Clock_Attach(&clock_handle, NULL);
       if (CLOCK_SUCCESS != eResult || !clock_handle)
       {      
          return SDCC_BSP_ERR_UNKNOWN;
       }
   }
   
   sdcc_bsp_num_slots = sdcc_bsp_get_slot_count();
   
   for (driveno = 0; driveno < sdcc_bsp_num_slots; driveno++) 
   {
      if (sdcc_bsp_get_slot_access_type(driveno) != SDCC_BSP_SLOT_INVALID)
      {
         eResult = Clock_GetId(clock_handle, 
                               sdcc_clocks_array[driveno].clock_name, 
                               &sdcc_clocks_array[driveno].clock_id);
         
         if (CLOCK_SUCCESS != eResult)
         {
            return SDCC_BSP_ERR_UNKNOWN;
         }
      }
   }
   
   sdcc_clock_initialized = TRUE;
   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* Name: sdcc_enable_mclk
*
* Description:
*    This function is to enable the SDCC controller gcc1_sdcc_apps clock.
*
* Arguments:
*    driveno          [IN] : drive number
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type
sdcc_enable_mclk (UINT32 driveno)
{
   ClockResult eResult = CLOCK_SUCCESS;
   UINTN nClockID = 0;

   if (sdcc_clock_initialized == FALSE)
   {
      if (SDCC_BSP_NO_ERROR != sdcc_bsp_initialize_clock())
      {
         return SDCC_BSP_ERR_UNKNOWN;
      }
   }
   
   if (sdcc_bsp_get_slot_access_type(driveno) == SDCC_BSP_SLOT_INVALID)
   {
      return SDCC_BSP_ERR_UNKNOWN;
   }      
   
   nClockID = sdcc_clocks_array[driveno].clock_id;
   eResult = Clock_Enable(clock_handle, nClockID);
   if (CLOCK_SUCCESS != eResult)
   {     
      return SDCC_BSP_ERR_UNKNOWN;
   }

   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* Name: sdcc_disable_mclk
*
* Description:
*    This function is to disable the SDCC controller gcc1_sdcc_apps_clk.
*
* Arguments:
*    driveno          [IN] : drive number
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type
sdcc_disable_mclk (UINT32 driveno)
{
   ClockResult eResult = CLOCK_SUCCESS;
   UINTN nClockID = 0;

   if (sdcc_clock_initialized == FALSE)
   {
      if (SDCC_BSP_NO_ERROR != sdcc_bsp_initialize_clock())
      {
         return SDCC_BSP_ERR_UNKNOWN;
      }
   }
   
   if (sdcc_bsp_get_slot_access_type(driveno) == SDCC_BSP_SLOT_INVALID)
   {
      return SDCC_BSP_ERR_UNKNOWN;
   }

   nClockID = sdcc_clocks_array[driveno].clock_id;
   eResult = Clock_Disable(clock_handle, nClockID);
   if (CLOCK_SUCCESS != eResult)
   {        
      return SDCC_BSP_ERR_UNKNOWN;
   }
 
   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* Name: sdcc_set_mclk_frequency
*
* Description:
*    This function is to select the SDCC mclock rate.
*
* Arguments:
*    driveno          [IN] : drive number
*    sdcc_mclk        [IN] : clock speed
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type
sdcc_set_mclk_frequency (UINT32 driveno, sdcc_bsp_clk_type sdcc_mclk)
{
   ClockResult eResult = CLOCK_SUCCESS;
   UINTN       nClockID = 0;
   UINT32      nFreqHz = 0;

   if (sdcc_clock_initialized == FALSE)
   {
      if (SDCC_BSP_NO_ERROR != sdcc_bsp_initialize_clock())
      {
         return SDCC_BSP_ERR_UNKNOWN;
      }
   }
   
   if (sdcc_bsp_get_slot_access_type(driveno) == SDCC_BSP_SLOT_INVALID)
   {
      return SDCC_BSP_ERR_UNKNOWN;
   } 
   
   nClockID = sdcc_clocks_array[driveno].clock_id;
   eResult = Clock_SetFrequency(clock_handle, nClockID, (UINT32)sdcc_mclk / 1000,
                                        CLOCK_FREQUENCY_KHZ_AT_MOST, &nFreqHz);
   if (CLOCK_SUCCESS != eResult)
   {      
      return SDCC_BSP_ERR_UNKNOWN;
   }

   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* Name: sdcc_set_volt_corner_frequency
*
* Description:
*    This function is to set the SDCC mclock rate based on the voltage corner.
*
* Arguments:
*    driveno          [IN] : drive number
*    volt_corner      [IN] : voltage corner
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type
sdcc_set_volt_corner_frequency (UINT32 driveno, UINT8 volt_corner)
{
   (void)driveno;
   (void)volt_corner;

   return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
}

/******************************************************************************
* Name: sdcc_reset_mclk
*
* Description:
*    This function resets the mclk
*
* Arguments:
*    driveno          [IN] : drive number
*
* Returns:
*     sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type
sdcc_reset_mclk( UINT32 driveno )
{
   ClockResult eResult = CLOCK_SUCCESS;
   UINTN nClockID = 0;

   if (sdcc_clock_initialized == FALSE)
   {
      if (SDCC_BSP_NO_ERROR != sdcc_bsp_initialize_clock())
      {
         return SDCC_BSP_ERR_UNKNOWN;
      }
   }
   
   if (sdcc_bsp_get_slot_access_type(driveno) == SDCC_BSP_SLOT_INVALID)
   {
      return SDCC_BSP_ERR_UNKNOWN;
   } 
   
   nClockID = sdcc_clocks_array[driveno].clock_id;
   eResult = Clock_Reset(clock_handle, nClockID, CLOCK_RESET_ASSERT);
   if (CLOCK_SUCCESS != eResult)
   {      
      return SDCC_BSP_ERR_UNKNOWN;
   }

   busywait(500);

   eResult = Clock_Reset(clock_handle, nClockID, CLOCK_RESET_DEASSERT);
   if (CLOCK_SUCCESS != eResult)
   {      
      return SDCC_BSP_ERR_UNKNOWN;
   }

   return SDCC_BSP_NO_ERROR;
} /* sdcc_reset */

/******************************************************************************
* Name: sdcc_ahb_clk_init
*
* Description:
*    This function is to initialize the SDCC AHB clock.
*
* Arguments:
*    driveno          [IN] : drive number
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type
sdcc_ahb_clk_init ( UINT32 driveno )
{
   /*
    * AHB clock will be controlled along with the apps clock.
    * No need to do anything here
    *
    * Does SDCC need to do anything in between turning on ahb clock and
    * apps clock?
    */
   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* Name: sdcc_ahb_clk_disable
*
* Description:
*    This function is to disable the SDCC AHB clock
*
* Arguments:
*    driveno          [IN] : drive number
*
* Returns:
*    sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type
sdcc_ahb_clk_disable ( UINT32 driveno )
{
   /*
    * AHB clock will be controlled along with the apps clock.
    * No need to do anything here
    */
   return SDCC_BSP_NO_ERROR;
}

