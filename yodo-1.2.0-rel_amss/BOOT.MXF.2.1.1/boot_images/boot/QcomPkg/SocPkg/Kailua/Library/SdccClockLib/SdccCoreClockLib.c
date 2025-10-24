/** @file SdccCoreClockLib.c

  SDCC Core clock driver BSP
  This file implements the SDCC driver BSP for XBL Core clocks

  Copyright (c) 2016, 2020, 2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ---     ----------------------------------------------------------- 
2022-08-08   jt      Kailua v2 updates
2022-01-05   jt      Update clock frequencies for Kailua 
2020-06-04   jt      Add clock frequencies for other voltage corners 
2016-05-13   jt      Use busywait instead of MicroSecondDelay 
2016-01-18   jt      Initial version. Branch from 8996 XBL 

=============================================================================*/

#include "SdccBsp.h"
#include "HALcomdef.h"
#include "ChipInfo.h"

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIClock.h>
#include <Protocol/EFIChipInfo.h>
#include <api/systemdrivers/busywait.h>

typedef struct _SDCC_CLOCK_INFO
{
   CHAR8* const clock_name;
   UINTN        clock_id;
   // Clock frequency values are in the following order: OFF, MINSVS, LOWSVS, SVS, NOM, TURBO
   UINT32       clock_freq[SDCC_CLOCK_MODE_MAX_COUNT];
}SDCC_CLOCK_INFO;

typedef struct _SDCC_CLOCKS
{
   SDCC_CLOCK_INFO sdcc_apps_clock;
   SDCC_CLOCK_INFO sdcc_ahb_clock;
}SDCC_CLOCKS;

static SDCC_CLOCKS sdcc_clocks_array[] =
{
  {{NULL, 0, 0, 0, 0, 0, 0, 0}, {NULL, 0, 0, 0, 0, 0, 0, 0}},
  {{"gcc_sdcc2_apps_clk", 0, 0, 0, SDCC_BSP_CLK_37_MHZ, SDCC_BSP_CLK_37_MHZ, SDCC_BSP_CLK_148_MHZ, SDCC_BSP_CLK_148_MHZ}, 
   {"gcc_sdcc2_ahb_clk", 0, 0, 0, 0, 0, 0, 0}},
  {{NULL, 0, 0, 0, 0, 0, 0, 0}, {NULL, 0, 0, 0, 0, 0, 0, 0}},
  {{"gcc_sdcc4_apps_clk", 0, 0, 0, SDCC_BSP_CLK_75_MHZ, SDCC_BSP_CLK_75_MHZ, SDCC_BSP_CLK_75_MHZ, SDCC_BSP_CLK_75_MHZ }, 
   {"gcc_sdcc4_ahb_clk", 0, 0, 0, 0, 0, 0, 0}}
};

static SDCC_CLOCKS sdcc_clocks_array_v2[] =
{
  {{NULL, 0, 0, 0, 0, 0, 0, 0}, {NULL, 0, 0, 0, 0, 0, 0, 0}},
  {{"gcc_sdcc2_apps_clk", 0, 0, 0, SDCC_BSP_CLK_50_MHZ, SDCC_BSP_CLK_50_MHZ, SDCC_BSP_CLK_202_MHZ, SDCC_BSP_CLK_202_MHZ}, 
   {"gcc_sdcc2_ahb_clk", 0, 0, 0, 0, 0, 0, 0}},
  {{NULL, 0, 0, 0, 0, 0, 0, 0}, {NULL, 0, 0, 0, 0, 0, 0, 0}},
  {{"gcc_sdcc4_apps_clk", 0, 0, 0, SDCC_BSP_CLK_75_MHZ, SDCC_BSP_CLK_75_MHZ, SDCC_BSP_CLK_75_MHZ, SDCC_BSP_CLK_75_MHZ }, 
   {"gcc_sdcc4_ahb_clk", 0, 0, 0, 0, 0, 0, 0}}
};


static BOOLEAN sdcc_clock_initialized = FALSE;
static EFI_CLOCK_PROTOCOL *hSdcc_Clock = NULL;

static EFI_CHIPINFO_PROTOCOL *ChipInfo = NULL;
static UINT32 ChipVersion = 0;

/******************************************************************************
                           S D C C    B S P
******************************************************************************/

/******************************************************************************
* Name: sdcc_bsp_get_clock_handle
*
* Description:
*    This function gets the clock protocol handle.
*
* Arguments:
*    None
*
* Returns:
*    None
*
******************************************************************************/
static VOID sdcc_bsp_get_clock_handle (VOID)
{
   EFI_STATUS    eResult = EFI_SUCCESS;
   
   if (NULL == hSdcc_Clock)
   {
      eResult = gBS->LocateProtocol(&gEfiClockProtocolGuid,
                                    NULL,
                                    (VOID **)&hSdcc_Clock);
   
      if (EFI_SUCCESS != eResult || NULL == hSdcc_Clock)
      {
          hSdcc_Clock = NULL;      
          ASSERT_EFI_ERROR(eResult);
      }
   }
}

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
   EFI_STATUS  eResult = EFI_SUCCESS;
   UINT8  driveno = 0;
   UINT32 sdcc_bsp_num_slots = 0;
   
   if (NULL == hSdcc_Clock)
   {
       sdcc_bsp_get_clock_handle();
       if (NULL == hSdcc_Clock)
       {      
          return SDCC_BSP_ERR_UNKNOWN;
       }  
   }
   
   sdcc_bsp_num_slots = sdcc_bsp_get_slot_count();
   
   for (driveno = 0; driveno < sdcc_bsp_num_slots; driveno++) 
   {
      if (sdcc_bsp_get_slot_access_type(driveno) != SDCC_BSP_SLOT_INVALID)
      {
         eResult = hSdcc_Clock->GetClockID(hSdcc_Clock, 
                                           sdcc_clocks_array[driveno].sdcc_apps_clock.clock_name, 
                                           &sdcc_clocks_array[driveno].sdcc_apps_clock.clock_id);
         
         if (EFI_SUCCESS != eResult)
         {
            ASSERT_EFI_ERROR(eResult);
            return SDCC_BSP_ERR_UNKNOWN;
         }
         
         eResult = hSdcc_Clock->GetClockID(hSdcc_Clock, 
                                           sdcc_clocks_array[driveno].sdcc_ahb_clock.clock_name, 
                                           &sdcc_clocks_array[driveno].sdcc_ahb_clock.clock_id);   
                   
         if (EFI_SUCCESS != eResult)
         {
            ASSERT_EFI_ERROR(eResult);
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
*    This function is to enable the SDCC controller gcc_sdcc_apps clock.
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
   EFI_STATUS    eResult = EFI_SUCCESS;
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
   
   nClockID = sdcc_clocks_array[driveno].sdcc_apps_clock.clock_id;
   eResult = hSdcc_Clock->EnableClock(hSdcc_Clock, nClockID);
   if (EFI_SUCCESS != eResult)
   {  
      ASSERT_EFI_ERROR(eResult);      
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
   EFI_STATUS    eResult = EFI_SUCCESS;
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

   nClockID = sdcc_clocks_array[driveno].sdcc_apps_clock.clock_id;
   eResult = hSdcc_Clock->DisableClock(hSdcc_Clock, nClockID);
   if (EFI_SUCCESS != eResult)
   {  
      ASSERT_EFI_ERROR(eResult);      
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
   EFI_STATUS    eResult = EFI_SUCCESS;
   UINTN         nClockID = 0;
   UINT32        nFreqHz = 0;

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
   
   nClockID = sdcc_clocks_array[driveno].sdcc_apps_clock.clock_id;
   eResult = hSdcc_Clock->SetClockFreqHz(hSdcc_Clock, nClockID, (UINT32)sdcc_mclk,
                                        EFI_CLOCK_FREQUENCY_HZ_AT_MOST, &nFreqHz);
   if (EFI_SUCCESS != eResult)
   {  
      ASSERT_EFI_ERROR(eResult);      
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
   EFI_STATUS Status = EFI_SUCCESS; 

   if (NULL == ChipInfo) 
   {
      Status = gBS->LocateProtocol(&gEfiChipInfoProtocolGuid, NULL, (VOID**) &ChipInfo);
      if (Status != EFI_SUCCESS) 
      {
         return SDCC_BSP_ERR_UNKNOWN;
      }
   }

   if (0 == ChipVersion) 
   {
      Status = ChipInfo->GetChipVersion (ChipInfo, &ChipVersion); 
      if (Status != EFI_SUCCESS) 
      {
         return SDCC_BSP_ERR_UNKNOWN;
      }
   }

   if (ChipVersion >= CHIPINFO_VERSION(2, 0)) 
   {
      return sdcc_set_mclk_frequency (driveno, sdcc_clocks_array_v2[driveno].sdcc_apps_clock.clock_freq[volt_corner]);
   }
   else 
   {
      return sdcc_set_mclk_frequency (driveno, sdcc_clocks_array[driveno].sdcc_apps_clock.clock_freq[volt_corner]); 
   }
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
   EFI_STATUS    eResult = EFI_SUCCESS;
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
   
   nClockID = sdcc_clocks_array[driveno].sdcc_apps_clock.clock_id;
   eResult = hSdcc_Clock->DisableClock(hSdcc_Clock, nClockID);
   if (EFI_SUCCESS != eResult)
   {  
      ASSERT_EFI_ERROR(eResult);      
      return SDCC_BSP_ERR_UNKNOWN;
   }
   
   busywait(100);

   eResult = hSdcc_Clock->EnableClock(hSdcc_Clock, nClockID);
   if (EFI_SUCCESS != eResult)
   {  
      ASSERT_EFI_ERROR(eResult);      
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
   EFI_STATUS    eResult = EFI_SUCCESS;
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
   
   nClockID = sdcc_clocks_array[driveno].sdcc_ahb_clock.clock_id;
   eResult = hSdcc_Clock->EnableClock(hSdcc_Clock, nClockID);
   if (EFI_SUCCESS != eResult)
   {  
      ASSERT_EFI_ERROR(eResult);      
      return SDCC_BSP_ERR_UNKNOWN;
   }

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
   EFI_STATUS    eResult = EFI_SUCCESS;
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
   
   nClockID = sdcc_clocks_array[driveno].sdcc_ahb_clock.clock_id;
   eResult = hSdcc_Clock->DisableClock(hSdcc_Clock, nClockID);
   if (EFI_SUCCESS != eResult)
   {  
      ASSERT_EFI_ERROR(eResult);      
      return SDCC_BSP_ERR_UNKNOWN;
   }
  
   return SDCC_BSP_NO_ERROR;
}

