/** @file ClockTestInterface.c

  This file contains test for common clock interface APIs.

  Copyright (c) 2020 Qualcomm Technologies, Inc. All rights reserved.

**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/28/20   gbedi     Created.

=============================================================================*/



/*=========================================================================
      Include Files
==========================================================================*/

#include <Library/Clock.h>
#include <Library/DebugLib.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Protocol/EFIDALSYSProtocol.h>

/*=========================================================================
      Type Definitions
==========================================================================*/
#define Sample_frequency_KHZ 19200
#define Ext_Source_frequency_HZ 179000000
#define debug_mux_gcc_cnoc_center_gc_qx_clk 0x12

/*=========================================================================
      Dependency Array 
==========================================================================*/
typedef struct
{
  const char  *szName;
} ClockNameListType;

ClockNameListType ClockDependencyArr[] =
{
  { "gcc_disp_xo_clk"            },
  { "gcc_disp_ahb_clk"           }, 
  { "disp_cc_mdss_ahb_clk"       }, 
  { NULL },
};

ClockNameListType GDSCDependencyArr[] =
{
  { "disp_cc_mdss_core_gdsc"     },  
  { NULL },
};

/*=========================================================================
      Functions
==========================================================================*/


/**
  Test clock driver application entry point.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/

EFI_STATUS
EFIAPI
ClockTestInterfaceEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  static ClockHandle  GlobalClockHandle = (ClockHandle)NULL;
  uintnt              ClockId = 0;
  ClockIdType         GDSCId = 0;
  ClockIdType         nGccDebugMuxId = 0;
  bool                bIsEnabled =0;
  bool                bIsOn =0;
  uint32_t            nFrequencyHz=0;

  // Initializing Clock Attach
   DEBUG((EFI_D_WARN, "ClockTestInterface_Driver Entered\r\n")); 
   
   if(!GlobalClockHandle)
   {
    if(CLOCK_SUCCESS == Clock_Attach(&GlobalClockHandle, "ClockTestInterface_Driver"))
    {
       DEBUG((EFI_D_WARN, "ClockTestInterface_Driver Clock Attach Success\r\n")); 
    }
    else
    {
        DEBUG((EFI_D_WARN, "ClockTestInterface_Driver Clock Attach Failed\r\n")); 
    }
   }
   
   if(GlobalClockHandle)
   {
     // Enabling clock dependency for disp_cc_mdss_byte0_intf_clk 
     DEBUG((EFI_D_WARN, "Enabling dependencies for disp_cc_mdss_byte0_intf_clk\r\n")); 
     for ( uint32_t i = 0; ClockDependencyArr[i].szName != NULL; i++)
     {
       if (CLOCK_SUCCESS != Clock_GetId(GlobalClockHandle, ClockDependencyArr[i].szName, &ClockId))
       {
          DEBUG((EFI_D_WARN, "Test Driver Failed to Get clock ID for %a \r\n",ClockDependencyArr[i].szName));
          return EFI_INVALID_PARAMETER;
       }
       else
       {
          DEBUG((EFI_D_WARN,"Test Driver Clock_GetId Success for %a: %x \r\n",ClockDependencyArr[i].szName,ClockId));
       }  
       //enable clock
       if(CLOCK_SUCCESS == Clock_Enable(GlobalClockHandle, ClockId))
       {
          DEBUG((EFI_D_WARN,"Test Driver %a enabled\r\n",ClockDependencyArr[i].szName));
       }
       else
       {
         DEBUG((EFI_D_WARN,"Test Driver %a not getting enabled\r\n",ClockDependencyArr[i].szName));
         return EFI_INVALID_PARAMETER;
       }
     }
     DEBUG((EFI_D_WARN, "Clock Dependencies for disp_cc_mdss_byte0_intf_clk Enabled\r\n"));
     
     // Enabling GDSC dependency for disp_cc_mdss_byte0_intf_clk 
     DEBUG((EFI_D_WARN, "Enabling dependencies for disp_cc_mdss_byte0_intf_clk\r\n")); 
     for ( uint32_t i = 0; GDSCDependencyArr[i].szName != NULL; i++)
     {
       if (CLOCK_SUCCESS != Clock_GetId(GlobalClockHandle, GDSCDependencyArr[i].szName, &GDSCId))
       {
          DEBUG((EFI_D_WARN, "Test Driver Failed to Get GDSC ID for %a \r\n",GDSCDependencyArr[i].szName));
          return EFI_INVALID_PARAMETER;
       }
       else
       {
          DEBUG((EFI_D_WARN,"Test Driver Clock_GetId Success for %a: %x \r\n",GDSCDependencyArr[i].szName,GDSCId));
       }  
       //enable GDSC
       if(CLOCK_SUCCESS == Clock_Enable(GlobalClockHandle, GDSCId))
       {
          DEBUG((EFI_D_WARN,"Test Driver %a enabled\r\n",GDSCDependencyArr[i].szName));
       }
       else
       {
         DEBUG((EFI_D_WARN,"Test Driver %a not getting enabled\r\n",GDSCDependencyArr[i].szName));
         return EFI_INVALID_PARAMETER;
       }
     }
     DEBUG((EFI_D_WARN, "GDSC Dependencies for disp_cc_mdss_byte0_intf_clk Enabled\r\n"));
     
     //Clock_GetId for disp_cc_mdss_byte0_intf_clk
     if (CLOCK_SUCCESS != Clock_GetId(GlobalClockHandle, "disp_cc_mdss_byte0_intf_clk", &ClockId))
     {
        DEBUG((EFI_D_WARN, "Test Driver Failed to Get clock ID for disp_cc_mdss_byte0_intf_clk \r\n"));
        return EFI_INVALID_PARAMETER;
     }
     else
     {
        DEBUG((EFI_D_WARN,"Test Driver Clock_GetId Success for disp_cc_mdss_byte0_intf_clk: %x \r\n",ClockId));
     }       
       
     //Clock_IsEnabled
     if (CLOCK_SUCCESS == Clock_IsEnabled(GlobalClockHandle, ClockId, &bIsEnabled)&& bIsEnabled ==0)
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk is not enabled \r\n"));
      //enable clock
        if(CLOCK_SUCCESS == Clock_Enable(GlobalClockHandle, ClockId))
        {
           DEBUG((EFI_D_WARN,"Test Driver disp_cc_mdss_byte0_intf_clk enabled\r\n"));
          if(CLOCK_SUCCESS == Clock_IsOn(GlobalClockHandle, ClockId, &bIsOn) && bIsOn==1)
          {
              DEBUG((EFI_D_WARN,"Test Driver disp_cc_mdss_byte0_intf_clk clock is on\r\n"));
          }
          else
          {
             DEBUG((EFI_D_WARN,"Test Driver disp_cc_mdss_byte0_intf_clk clock is not turning on due to missing dependencies\r\n"));
             return EFI_INVALID_PARAMETER;
          }
        }
      
     }
     else if (CLOCK_SUCCESS == Clock_IsEnabled(GlobalClockHandle,ClockId, &bIsEnabled) && bIsEnabled ==1)
     {
       DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk is already enabled\r\n"));
     }

     // Sample frequency is 19200 KHZ
     if(CLOCK_SUCCESS == Clock_SetFrequency(GlobalClockHandle, ClockId, Sample_frequency_KHZ,CLOCK_FREQUENCY_KHZ_AT_LEAST, &nFrequencyHz))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  set frequency :%d \r\n",nFrequencyHz));
     }
     
     //GetFrequency does not get frequency measurement from HW, it is based on SW. 
     if(CLOCK_SUCCESS == Clock_GetFrequency(GlobalClockHandle, ClockId, &nFrequencyHz))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  current get frequency :%ld \r\n",nFrequencyHz));
     }
     
     //MeasureFrequency uses the HW debug mux which takes time, hence this API should be used only for test purposes and not production. 
     if(CLOCK_SUCCESS == Clock_MeasureFrequency(GlobalClockHandle, ClockId, &nFrequencyHz))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  current measure frequency :%ld \r\n",nFrequencyHz));
     }
     
     // Disable clock
     if(CLOCK_SUCCESS == Clock_Disable(GlobalClockHandle, ClockId))
     {
       DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk disable successful \r\n"));
     } 
     
     // Sample frequency to be set to 56MHZ, Source we are selecting here is dsi0_phy_pll_out_byteclk, which is an external PLL and rest all parameters dividers flags are passed 0 over here
     // Clock might not be enabled as the source (PLL) is externally controlled
     if (CLOCK_SUCCESS == Clock_SelectExternalSourceEx(GlobalClockHandle, ClockId, Ext_Source_frequency_HZ, 1,0x1,0,0,0,0))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  external source changed\r\n"));
     }
     else
     {
       DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  external source not able to change\r\n"));
     }
     
     if(CLOCK_SUCCESS == Clock_Enable(GlobalClockHandle, ClockId))
     {
        DEBUG((EFI_D_WARN,"Test Driver disp_cc_mdss_byte0_intf_clk enabled\r\n"));
     }
     
     if(CLOCK_SUCCESS == Clock_GetFrequency(GlobalClockHandle, ClockId, &nFrequencyHz))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  current get frequency :%ld \r\n",nFrequencyHz));
     }
      if(CLOCK_SUCCESS == Clock_MeasureFrequency(GlobalClockHandle, ClockId, &nFrequencyHz))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  current measure frequency :%ld \r\n",nFrequencyHz));
     }

     // Divider is by default 1 we are setting it to 0 to verify
     if (CLOCK_SUCCESS == Clock_SetDivider(GlobalClockHandle, ClockId, 0))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  divider set\r\n"));
     }
     if(CLOCK_SUCCESS == Clock_GetFrequency(GlobalClockHandle, ClockId, &nFrequencyHz))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  current get frequency :%ld \r\n",nFrequencyHz));
     }
      if(CLOCK_SUCCESS == Clock_MeasureFrequency(GlobalClockHandle, ClockId, &nFrequencyHz))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  current measure frequency :%ld \r\n",nFrequencyHz));
     }
     
     // Clock ID for a clock that is not owned by APPS. Debug Mux clock.  
     // Should be used only for testing, not production SW
     if(CLOCK_SUCCESS == Clock_GetId (GlobalClockHandle, "gcc", &nGccDebugMuxId))
     {
        DEBUG((EFI_D_WARN, "Test Driver Clock_GetId Success for GCC Debug MUX %x \r\n",nGccDebugMuxId));
     }
     else
     {
        DEBUG((EFI_D_WARN, "Test Driver Clock_GetId Failed for GCC Debug MUX \r\n"));
        return EFI_INVALID_PARAMETER;
     }
     if(CLOCK_SUCCESS == Clock_MeasureFrequencyEx(GlobalClockHandle, nGccDebugMuxId, debug_mux_gcc_cnoc_center_gc_qx_clk, &nFrequencyHz))
     {
        DEBUG((EFI_D_WARN, "Test Driver for debug_mux_gcc_cnoc_center_gc_qx_clk: gcc_sleep_clk current measure frequency :%ld \r\n",nFrequencyHz));
     }
          
     // Reset clocks: Reset Asserting being executed here
     // Should be sparingly used as it will reset the entire block and may cause other clocks to get reset as well. 
     if(CLOCK_SUCCESS == Clock_Reset(GlobalClockHandle, ClockId, 1))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  reset done \r\n"));
     }
 
     if(CLOCK_SUCCESS == Clock_ResetBlock(GlobalClockHandle, ClockId, 1))
     {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  reset branch done \r\n"));
     } 
   
     // DeAsserting the block
     if(CLOCK_SUCCESS == Clock_Reset(GlobalClockHandle, ClockId, 0))
      {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  reset done \r\n"));
      }
 
     if(CLOCK_SUCCESS == Clock_ResetBlock(GlobalClockHandle, ClockId, 0))
      {
        DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_byte0_intf_clk  reset branch done \r\n"));
      }
        
      
      // Running API's for Disabling gdsc disp_cc_mdss_core_gdsc
      if(CLOCK_SUCCESS == Clock_Disable(GlobalClockHandle, GDSCId))
      {
         DEBUG((EFI_D_WARN, "Test Driver disp_cc_mdss_core_gdsc disable successful \r\n"));
      }
        
      // Initializing Clock_Detach
      
      if(CLOCK_ERROR == Clock_Detach(GlobalClockHandle))
      {
         DEBUG((EFI_D_WARN, "Test Driver Clock_Detach Failed\r\n"));
      }
      else
      {
          DEBUG((EFI_D_WARN, "Test Driver Clock_Detach Success\r\n"));
      }
  
   }
     
   else
   {
      return EFI_INVALID_PARAMETER;   
   }

  return EFI_SUCCESS;
}

