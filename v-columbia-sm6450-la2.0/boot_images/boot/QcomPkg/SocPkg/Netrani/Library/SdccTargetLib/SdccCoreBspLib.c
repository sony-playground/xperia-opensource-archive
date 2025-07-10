/** @file SdccCoreBspLib.c

  SDCC driver BSP
  This file implements the SDCC driver BSP for the board in use

  Copyright (c) 2016-2022 Qualcomm Technologies, Inc. 
  All Rights Reserved. 
  Qualcomm Technologies Proprietary and Confidential 

**/

/*=============================================================================
                              EDIT HISTORY

when         who     what, where, why
----------   ---     -----------------------------------------------------------
2022-09-11   ssb     SD card rails ON/OFF support.
2022-07-27   ssb     Reverted back speed mode to default.
2022-06-29   ssb     Reorganised Sd card speed mode to SDR104
2022-04-26   ssb     Reverted back to original version mode
2022-04-22   ssb     Updated Speed mode values as per DT
2022-04-20   ssb     Updated DT storage node under soc
2022-01-14   ssb     Add support for sdcc bootup using Device Tree Config
2022-02-07	 cm		 Add sdcc_bsp_get_default_hsr_settings()
2021-10-07   ss      Added the sdcc_bsp_get_config function 
2021-07-22   vm      Add voltage ON/OFF support for SD Card
2021-07-16   jt      Allow logging of device tree entries
2021-05-24   jt      Add device tree support
2020-06-04   jt      Add power management support  
2020-04-28   jt      Netrani updates
2020-03-03   jt      Add UHS-1 support
2020-01-30   jt      Update HS200 frequency to 202 MHz
2019-07-22   jt      Add SMMU configuration API 
2019-06-10   jt      Change to 202 MHz clock 
2018-11-09   jt      Update TLMM addr for Kona 
2018-07-13   jt      Add voltage switch functions 
2017-10-30   jt      Add sdcc_bsp_busy_wait() 
2017-08-22   jt      Update TLMM addr for Hana 
2017-06-16   sb      Get platform specific speed config 
2017-06-12   jt      Update drive strength  
2017-01-17   jt      Update sdcc_bsp_get_max_supported_clk() 
2016-12-08   jt      Update for Napali. Rename file.  
2016-01-18   jt      Initial version. Branched from 8996 XBL

=============================================================================*/

#include "SdccBspConfig.h"
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/EFIPlatformInfo.h> 
#include <Protocol/EFIHALIOMMUProtocol.h>
#include <Protocol/EFIStorageDeviceMgmt.h>
#include <Protocol/EFIDtbExtn.h>

#include "iort.h"

#include "npa.h"
#include "pmapp_npa.h"




/*  Information used for power management */
typedef struct
{
   EFI_STORAGE_VOLT_CORNER volt_corner;
   sdcc_bsp_speed_mode     max_speed_mode;
} sdcc_bsp_pm_info;

/* This list should be modified based on the voltage corners specified in the Storage Device Management protocol.
   For each voltage corner, max speed mode supported is listed. */
static sdcc_bsp_pm_info sd_pm_params[] =
{
  	{ VOLT_CORNER_MINSVS,   SDCC_INVALID_SPEED},
  	{ VOLT_CORNER_LOWSVS,   SDCC_DDR50_MODE},
	{ VOLT_CORNER_SVS,      SDCC_DDR50_MODE},
	{ VOLT_CORNER_NOM,      SDCC_SDR104_MODE},
	{ VOLT_CORNER_TURBO,    SDCC_SDR104_MODE}
};

/* 
 * In case of UHS SD Card running SDR104 Mode volatge set 
 * should happen once, any re-init after voltage switch or 
 * sdcc_bsp_lower_volt_level call should be skipped
 */
static boolean volt_set_done = FALSE;
static npa_client_handle sd_mmc_vdd_handle = NULL;
static npa_client_handle sd_mmc_vdd_px2_handle = NULL;
static EFI_DTB_EXTN_PROTOCOL *DtbProtocol = NULL;

/*=============================================================================
 * FUNCTION      sdcc_bsp_target_cap_overrides
 *
 * DESCRIPTION   This function provides target specific cap overrides
 *
 * PARAMETERS    [IN]: slot number
 *               [IN/OUT]: Capability 0 (HC_REG_40_42)
 *               [IN/OUT]: Capability 1 (HC_REG_44_46)
 *
 * RETURN VALUE  None
 *
 *===========================================================================*/
void sdcc_bsp_target_cap_overrides (UINT32 slot_num, UINT32 *caps0, UINT32 *caps1) {
  return;
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_base_addr
 *
 * DESCRIPTION   This function queries the SDCC register base addresses
 *
 * PARAMETERS    [OUT]: sdcc_base_addr_type pointer to retrieve the SDCC base addresses
 *
 * RETURN VALUE  sdcc_bsp_err_type
 *
 *===========================================================================*/
sdcc_bsp_err_type
sdcc_bsp_get_base_addr (sdcc_base_addr_type *sdcc_base_addr)
{
  sdcc_base_addr->sdc1_base_hc = HWIO_SDC1_SDCC5_HC_ADDR;
  sdcc_base_addr->sdc2_base_hc = HWIO_SDC2_SDCC5_HC_ADDR;
  
  return SDCC_BSP_NO_ERROR;
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_slot_type
 *
 * DESCRIPTION   This function queries the slot to find out if the slot is designated
 *               for eMMC, SD or no device.
 *
 * PARAMETERS    [IN]: slot number
 *
 * RETURN VALUE  sdcc_bsp_slot_type
 *
 *===========================================================================*/
sdcc_bsp_slot_type
sdcc_bsp_get_slot_type (UINT32 slot_num)
{
   sdcc_bsp_slot_type slot_type = SDCC_BSP_NO_SLOT;

   if (slot_num >= SDCC_BSP_NUM_SLOTS)
   {
      /* Return No slot available*/
      slot_type = SDCC_BSP_NO_SLOT;
   }
   else
   {
      slot_type = sdcc_bsp_slot_config [slot_num];
   }

   return slot_type;
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_get_slot_access_type
 *
 * DESCRIPTION   This function queries the slot to find out if the slot is designated
 *               as internal or external memory device. Hotplug needs this info
 *               to determine which memory device to boot from.
 *
 * PARAMETERS    [IN]: slot number
 *
 * RETURN VALUE  sdcc_bsp_slot_access_type
 *
 *===========================================================================*/
sdcc_bsp_slot_access_type
sdcc_bsp_get_slot_access_type (UINT32 slot_num)
{
   sdcc_bsp_slot_access_type slot_access_type = SDCC_BSP_SLOT_INVALID;

   if (slot_num >= SDCC_BSP_NUM_SLOTS)
   {
      /* Return No slot available*/
      slot_access_type = SDCC_BSP_SLOT_INVALID;
   }
   else
   {
      slot_access_type = sdcc_bsp_slot_access_config [slot_num];
   }

   return slot_access_type;
}
/*=============================================================================
 * FUNCTION      sdcc_bsp_get_default_hsr_settings
 *
 * DESCRIPTION   This function gets the default HSR settings for DLL configuration
 *
 * PARAMETERS    [IN]: slot number
 *               [IN]: speed mode 
 *               [OUT]: hsr_settings
 *
 * RETURN VALUE  none
 *
 *===========================================================================*/
void sdcc_bsp_get_default_hsr_settings (UINT32 slot_num, sdcc_bsp_speed_mode speed_mode,
                                             sdcc_bsp_hsr_settings_type *hsr_settings)
{
if(slot_num==SDCC_BSP_SLOT_0)
	{
	hsr_settings->ddr_config = 	SDC1_BSP_DDR_CONFIG_DEFAULT_VAL;
	hsr_settings->dll_user_ctrl = SDC1_BSP_DLL_USER_CTRL_DEFAULT_VAL;	 
	
	if(speed_mode==SDCC_HS400_MODE)
	{
	hsr_settings->dll_config = SDC1_BSP_DLL_CONFIG_DEFAULT_VAL;
	hsr_settings->dll_config_2  = SDC1_BSP_DLL_CONFIG_2_DEFAULT_VAL;	
	hsr_settings->dll_config_3  = SDC1_BSP_DLL_CONFIG_3_DEFAULT_VAL;
	hsr_settings->dll_test_ctrl = SDC1_BSP_DLL_TEST_CTRL_DEFAULT_VAL;
	}
	
	else if(speed_mode==SDCC_HS200_MODE)
	{
	hsr_settings->dll_config =    SDC1_BSP_DLL_CONFIG_DEFAULT_VAL_HS200_VAL;
	hsr_settings->dll_config_2  = SDC1_BSP_DLL_CONFIG_2_DEFAULT_VAL_HS200_VAL;	
	hsr_settings->dll_config_3  = SDC1_BSP_DLL_CONFIG_3_DEFAULT_VAL_HS200_VAL;
	hsr_settings->dll_test_ctrl = SDC1_BSP_DLL_TEST_CTRL_DEFAULT_VAL_HS200_VAL;
	}
	
	}
	
    else if(slot_num==SDCC_BSP_SLOT_1)
    {
	hsr_settings->dll_config = SDC2_BSP_DLL_CONFIG_DEFAULT_VAL;
	hsr_settings->dll_config_2  = SDC2_BSP_DLL_CONFIG_2_DEFAULT_VAL;	
	hsr_settings->dll_config_3  = SDC2_BSP_DLL_CONFIG_3_DEFAULT_VAL;
	hsr_settings->dll_test_ctrl = SDC2_BSP_DLL_TEST_CTRL_DEFAULT_VAL;
	hsr_settings->ddr_config = 	SDC2_BSP_DDR_CONFIG_DEFAULT_VAL;
	hsr_settings->dll_user_ctrl = SDC2_BSP_DLL_USER_CTRL_DEFAULT_VAL;	 
	}
}											 
/*=============================================================================
 * FUNCTION      sdcc_bsp_get_hsr_settings
 *
 * DESCRIPTION   This function gets the HSR settings for DLL configuration
 *
 * PARAMETERS    [IN]: slot number
 *               [IN]: speed mode 
 *               [OUT]: hsr_settings
 *
 * RETURN VALUE  sdcc_bsp_err_type
 *
 *===========================================================================*/
sdcc_bsp_err_type sdcc_bsp_get_hsr_settings (UINT32 slot_num, sdcc_bsp_speed_mode speed_mode, 
                                             sdcc_bsp_hsr_settings_type *hsr_settings)
{
   CHAR8 FdtNodeStr[SDCC_BSP_DT_PATH_LEN] = {0};
   FdtNodeHandle Node; 

   switch(slot_num)
   {
	  case SDCC_BSP_SLOT_0: 
	  
	    if (NULL != DtbProtocol) 
        {
            snprintf (FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d/HsrSettings", slot_num); 

            if (0 == DtbProtocol->FdtGetNodeHandle (&Node, FdtNodeStr))
            {
                if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DDRConfig", &hsr_settings->ddr_config))
                {
                    return SDCC_BSP_ERR_DT;
                }

                if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLUserCtrl", &hsr_settings->dll_user_ctrl))
                {
                    return SDCC_BSP_ERR_DT;
                }
            }
            else
            {
                return SDCC_BSP_ERR_DT;
            }
                if (SDCC_HS400_MODE == speed_mode)
            {
               snprintf(FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d/HsrSettings/HS400", slot_num);
            }
                else if (SDCC_HS200_MODE == speed_mode)
            {
               snprintf(FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d/HsrSettings/HS200", slot_num);
            }
            else 
            {
               return SDCC_BSP_ERR_INVALID_PARAM; 
            }

            if (0 == DtbProtocol->FdtGetNodeHandle (&Node, FdtNodeStr))
            {
               if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLConfig",&hsr_settings->dll_config))
               {
                  return SDCC_BSP_ERR_DT;
               }
			   if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLConfig2", &hsr_settings->dll_config_2))
               {
                    return SDCC_BSP_ERR_DT;
               }

               if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLConfig3", &hsr_settings->dll_config_3))
               {
                    return SDCC_BSP_ERR_DT;
               }

               if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLTestCtrl", &hsr_settings->dll_test_ctrl))
               {
                    return SDCC_BSP_ERR_DT;
               }
            }
            else
            {
                return SDCC_BSP_ERR_DT;
            }
			
			
        }
        else
        {
            return SDCC_BSP_ERR_DT;
        }

        if (enable_dt_logging) 
        {
            DEBUG((EFI_D_ERROR, "SDCC HSR Settings from Device Tree:\n" \
                                "DLLConfig = 0x%x, DLLConfig2 = 0x%x, DLLConfig3 = 0x%x\n" \
                                "DLLTestCtrl = 0x%x, DDRConfig = 0x%x, DLLUserCtrl = 0x%x\n", 
                   hsr_settings->dll_config, hsr_settings->dll_config_2, hsr_settings->dll_config_3, 
                   hsr_settings->dll_test_ctrl, hsr_settings->ddr_config, hsr_settings->dll_user_ctrl));
        }
		break;
	 case SDCC_BSP_SLOT_1:

        if (NULL != DtbProtocol) 
        {
            snprintf (FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d/HsrSettings", slot_num); 

            if (0 == DtbProtocol->FdtGetNodeHandle (&Node, FdtNodeStr))
            {
                if (0 != DtbProtocol->FdtGetUint32Prop (&Node, "DLLConfig", &hsr_settings->dll_config))
                {
                    return SDCC_BSP_ERR_DT;
                }

                if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLConfig2", &hsr_settings->dll_config_2))
                {
                    return SDCC_BSP_ERR_DT;
                }

                if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLConfig3", &hsr_settings->dll_config_3))
                {
                    return SDCC_BSP_ERR_DT;
                }

                if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLTestCtrl", &hsr_settings->dll_test_ctrl))
                {
                    return SDCC_BSP_ERR_DT;
                }

                if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DDRConfig", &hsr_settings->ddr_config))
                {
                    return SDCC_BSP_ERR_DT;
                }

                if (0 != DtbProtocol->FdtGetUint32Prop(&Node, "DLLUserCtrl", &hsr_settings->dll_user_ctrl))
                {
                    return SDCC_BSP_ERR_DT;
                }
            }
            else
            {
                return SDCC_BSP_ERR_DT;
            }
        }
        else
        {
            return SDCC_BSP_ERR_DT;
        }

        if (enable_dt_logging) 
        {
            DEBUG((EFI_D_ERROR, "SDCC HSR Settings from Device Tree:\n" \
                                "DLLConfig = 0x%x, DLLConfig2 = 0x%x, DLLConfig3 = 0x%x\n" \
                                "DLLTestCtrl = 0x%x, DDRConfig = 0x%x, DLLUserCtrl = 0x%x\n", 
                   hsr_settings->dll_config, hsr_settings->dll_config_2, hsr_settings->dll_config_3, 
                   hsr_settings->dll_test_ctrl, hsr_settings->ddr_config, hsr_settings->dll_user_ctrl));
        }
        break;
      default:
        return SDCC_BSP_ERR_INVALID_PARAM;
   }

   return SDCC_BSP_NO_ERROR; 
}

/*=============================================================================
 * FUNCTION      sdcc_bsp_gpio_control
 *
 * DESCRIPTION   This function enables/disables the GPIO interface to the
 *               card slot.
 *
 * PARAMETERS    [IN]: slot number
 *               [IN]: GPIO ON/OFF
 *
 * RETURN VALUE  sdcc_bsp_err_type.
 *
 *===========================================================================*/
sdcc_bsp_err_type
sdcc_bsp_gpio_control (UINT32 slot_num, UINT32 state)
{
   CHAR8 FdtNodeStr[SDCC_BSP_DT_PATH_LEN] = {0};
   EFI_STATUS Status = EFI_SUCCESS; 
   FdtNodeHandle Node; 
   UINT32 AddressInfo[2];
   UINT32 DriveStrength[2] = {0};
   UINT32 BaseAddr = 0;

   if(slot_num >= SDCC_BSP_NUM_SLOTS)
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   if(SDCC_BSP_NO_SLOT == sdcc_bsp_slot_config [slot_num])
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   if (NULL == DtbProtocol) 
   {
       Status = gBS->LocateProtocol(&gEfiDtbExtnProtocolGuid, NULL, (VOID **)&DtbProtocol);
       if ((EFI_SUCCESS != Status) || (NULL == DtbProtocol))
       {
           DEBUG((EFI_D_ERROR, "Failed to Locate DTBExtnProtocol 0x%x\n", Status));
       }
       else
       {
           snprintf (FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d", slot_num);
           if (0 == DtbProtocol->FdtGetNodeHandle(&Node, FdtNodeStr)) 
           {
               if (0 == DtbProtocol->FdtGetUint32PropList(&Node, "reg", AddressInfo, sizeof(AddressInfo)))
               {
                   if (slot_num == SDCC_BSP_SLOT_0) 
                   {
                      BaseAddr = HWIO_SDC1_SDCC5_HC_ADDR;
                   }
                   else if (slot_num == SDCC_BSP_SLOT_1)
                   {
                      BaseAddr = HWIO_SDC2_SDCC5_HC_ADDR;
                   }

                   // Use the base address in device tree to determine whether it is valid
                   if (AddressInfo[0] != BaseAddr) 
                   {
                       DtbProtocol = NULL; 
                   }
               }
               else
               {
                   DtbProtocol = NULL; 
               }
           }
           else
           {
               DtbProtocol = NULL; 
           }
       }
   }

   switch(slot_num)
   {
       case SDCC_BSP_SLOT_0:
	     DriveStrength[0] = SDC1_BSP_DEFAULT_DRIVE_STRENGTH_CTL0;
		 DriveStrength[1] = SDC1_BSP_DEFAULT_DRIVE_STRENGTH_CTL1;
         if (NULL != DtbProtocol) 
         {
            snprintf (FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d", slot_num);

            if (0 == DtbProtocol->FdtGetNodeHandle(&Node, FdtNodeStr))
            {
               DtbProtocol->FdtGetUint8Prop(&Node, "EnableLogging", &enable_dt_logging);

               if (0 == DtbProtocol->FdtGetUint32PropList(&Node, "DriveStrength", DriveStrength,sizeof(DriveStrength)))
               {
                  if (enable_dt_logging) 
                  {
                     DEBUG((EFI_D_ERROR, "SDCC Drive Strength CTL-0 Setting from Device Tree: 0x%x\n", DriveStrength[0]));
                     DEBUG((EFI_D_ERROR, "SDCC Drive Strength CTL-1 Setting from Device Tree: 0x%x\n", DriveStrength[1]));
                  }
               }
            }
         }

         out_dword (HWIO_TLMM_SDC1_HDRV_PULL_CTL_0_ADDR, DriveStrength[0]);
         out_dword (HWIO_TLMM_SDC1_HDRV_PULL_CTL_1_ADDR, DriveStrength[1]);
      case SDCC_BSP_SLOT_1:
	     DriveStrength[0] = SDC2_BSP_DEFAULT_DRIVE_STRENGTH_CTL;
         if (NULL != DtbProtocol) 
         {
            snprintf (FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d", slot_num);

            if (0 == DtbProtocol->FdtGetNodeHandle(&Node, FdtNodeStr))
            {
               DtbProtocol->FdtGetUint8Prop(&Node, "EnableLogging", &enable_dt_logging);
               if (0 == DtbProtocol->FdtGetUint32Prop(&Node, "DriveStrength", &DriveStrength[0]))
               {
                  if (enable_dt_logging) 
                  {
                     DEBUG((EFI_D_ERROR, "SDCC Drive Strength Setting from Device Tree: 0x%x\n", DriveStrength[0]));
                  }
               }
            }
         }

         out_dword (HWIO_TLMM_SDC2_HDRV_PULL_CTL_ADDR, DriveStrength[0]);
         break;
      default:
         return SDCC_BSP_ERR_INVALID_PARAM;
   }

   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_max_supported_mclk_freq
*
* DESCRIPTION   Get the maximum mclock frequency supported
*
* PARAMETERS    [IN]: drive number
*
* RETURN VALUE  Clock frequency supported
*
******************************************************************************/
sdcc_bsp_clk_type
sdcc_bsp_get_max_supported_clk (UINT32 driveno)
{   
   switch(driveno)
   {
       case SDCC_BSP_SLOT_0:
          return SDCC_BSP_CLK_384_MHZ;
       case SDCC_BSP_SLOT_1:
          return SDCC_BSP_CLK_202_MHZ;
       default:
          return SDCC_BSP_CLK_INVALID;
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_supported_freq
*
* DESCRIPTION   Get the supported frequency for various speed modes
*
* PARAMETERS    [IN]: drive number
*               [OUT]: Frequency for corresponding speed modes
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_get_supported_freq (UINT32 driveno, sdcc_bsp_supported_frequencies *freq)
{
      freq->ds_mode = SDCC_BSP_CLK_25_MHZ;
      freq->hs_mode = SDCC_BSP_CLK_50_MHZ;
      freq->sdr12_mode = SDCC_BSP_CLK_25_MHZ;
      freq->sdr25_mode = SDCC_BSP_CLK_50_MHZ;
      freq->sdr50_mode = SDCC_BSP_CLK_100_MHZ;
      freq->ddr50_mode = SDCC_BSP_CLK_100_MHZ; 

	  if (driveno == SDCC_BSP_SLOT_0) 
      {  
      freq->hs200_mode = SDCC_BSP_CLK_192_MHZ;
      freq->hs400_mode = SDCC_BSP_CLK_384_MHZ; 
      }
      else if (driveno == SDCC_BSP_SLOT_1) 
      {	  
      freq->hs200_mode = SDCC_BSP_CLK_202_MHZ;
      freq->hs400_mode = SDCC_BSP_CLK_INVALID; 
      }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_busy_wait
*
* DESCRIPTION   Waits for the specified amount of us
*
* PARAMETERS    [IN]: us to wait 
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_busy_wait(UINT32 us)
{
   gBS->Stall(us); 
}

/******************************************************************************
* FUNCTION      sdcc_bsp_cache_operation
*
* DESCRIPTION   Performs cache operations on the provided memory region.
*               Used for DMA related operations only.
*
* PARAMETERS    [IN]: cache operation type
*               [IN]: start address of the memory region
*               [IN]: length of the memory region
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_cache_operation
(
   sdcc_bsp_cache_op_type op,
   void *addr,
   UINT32 length
)
{
   switch(op)
   {
      case SDCC_BSP_CACHE_FLUSH:
        WriteBackInvalidateDataCacheRange(addr, length);
        break;

      case SDCC_BSP_CACHE_INVAL:
        InvalidateDataCacheRange(addr, length);
        break;

      default:
        break;
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_vreg_switch_status
*
* DESCRIPTION   Check whether PMIC APIs work (for UHS-1) by enabling the VDD
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_get_vreg_switch_status (UINT32 driveno)
{
   if (driveno == SDCC_BSP_SLOT_1) {
      /* For RUMI (SOC_EMULATION_TYPE = 1), disable UHS-1 support. */
      if (1 == (in_dword(HWIO_TCSR_SOC_EMULATION_TYPE) & 0x3))
      {
         return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
      }

      if (sd_mmc_vdd_px2_handle == NULL) {
         sd_mmc_vdd_px2_handle = npa_create_sync_client(PMIC_NPA_GROUP_ID_SD_MMC_VDD_PX2, "sd_mmc_vdd_px2", NPA_CLIENT_REQUIRED);
      }
   }
   else {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   if (sd_mmc_vdd_px2_handle == NULL) {
      return SDCC_BSP_ERR_PMIC;
   }

   npa_issue_required_request(sd_mmc_vdd_px2_handle, PMIC_NPA_MODE_ID_GENERIC_HV);

   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_lower_volt_level
*
* DESCRIPTION   Lower the VDD to 1.8V for UHS1
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_lower_volt_level (UINT32 driveno)
{ 
   if (driveno == SDCC_BSP_SLOT_1) {
      /* For RUMI (SOC_EMULATION_TYPE = 1), disable UHS-1 support. */
      if (1 == (in_dword(HWIO_TCSR_SOC_EMULATION_TYPE) & 0x3))
      {
         return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
      }

      if (sd_mmc_vdd_px2_handle == NULL) {
         sd_mmc_vdd_px2_handle = npa_create_sync_client(PMIC_NPA_GROUP_ID_SD_MMC_VDD_PX2, "sd_mmc_vdd_px2", NPA_CLIENT_REQUIRED);
      }
   }
   else {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   if (sd_mmc_vdd_px2_handle == NULL) {
      return SDCC_BSP_ERR_PMIC;
   }

   npa_issue_required_request(sd_mmc_vdd_px2_handle, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);

   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_memory_barrier
*
* DESCRIPTION   Performs data memory barrier operation.
*
* PARAMETERS    None
*
* RETURN VALUE  None
*
******************************************************************************/
void sdcc_bsp_memory_barrier(void)
{
   ArmDataMemoryBarrier();
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_slot_count
*
* DESCRIPTION   Get the maximum SDCC number of slots support
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  Maximum number of slots on the target
*
******************************************************************************/
UINT32 sdcc_bsp_get_slot_count (VOID)
{
   return SDCC_BSP_NUM_SLOTS;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_platform_speed_config
*
* DESCRIPTION   Get the speed config based on the platform
*
* PARAMETERS    [IN]: speed_mode
*
* RETURN VALUE  Speed config based on the platform
*
******************************************************************************/
UINT8
sdcc_bsp_get_platform_speed_config (UINT32 driveno)
{
   CHAR8 FdtNodeStr[SDCC_BSP_DT_PATH_LEN] = {0};
   FdtNodeHandle Node; 
   UINT8 SpeedMode;

   switch(driveno)
   {
      case SDCC_BSP_SLOT_0:

         if (1 == in_dword(HWIO_TCSR_SOC_EMULATION_TYPE)) 
         {
            return SDCC_SDR50_MODE;
         }
         else
         {
		  SpeedMode = SDCC_SDR50_MODE;
            if (NULL != DtbProtocol)
            {
               snprintf (FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d", driveno); 
            
               if (0 == DtbProtocol->FdtGetNodeHandle (&Node, FdtNodeStr))
               {
                  if (0 == DtbProtocol->FdtGetUint8Prop (&Node, "MaxSpeedMode", &SpeedMode))
                  {
                     if (enable_dt_logging) 
                     {
                        DEBUG((EFI_D_ERROR, "SDCC Speed Mode Setting from Device Tree: %d\n", SpeedMode)); 
                     }
                  }
               }
            }

            return SpeedMode; 
         }
      case SDCC_BSP_SLOT_1:

         if (1 == in_dword(HWIO_TCSR_SOC_EMULATION_TYPE)) 
         {
            return SDCC_HS_MODE; 
         }
         else
         {
		 SpeedMode = SDCC_SDR104_MODE;
            if (NULL != DtbProtocol)
            {
                 snprintf (FdtNodeStr, SDCC_BSP_DT_PATH_LEN, "/soc/storage/sdc%d", driveno); 
            
               if (0 == DtbProtocol->FdtGetNodeHandle (&Node, FdtNodeStr))
               {
                  if (0 == DtbProtocol->FdtGetUint8Prop (&Node, "MaxSpeedMode", &SpeedMode))
                  {
                     if (enable_dt_logging) 
                     {
                        DEBUG((EFI_D_ERROR, "SDCC Speed Mode Setting from Device Tree: %d\n", SpeedMode)); 
                     }
                  }
               }
            }

            return SpeedMode; 
         }
      default:
         return SDCC_INVALID_SPEED; 
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_configure_smmu
*
* DESCRIPTION   Configure the SMMU for SDCC
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_configure_smmu() 
{
   EFI_STATUS Status = EFI_SUCCESS;
   static boolean configure_completed = FALSE; 
   static HAL_IOMMU_fptable_t *fp_table = NULL;
   VOID *sdc1_domain_hdl, *sdc2_domain_hdl;
   EFI_HAL_IOMMU_PROTOCOL *Iommu = NULL;

   if (configure_completed) {
      return SDCC_BSP_NO_ERROR; 
   }

   /* Locate UEFI IOMMU protocol */
   if (fp_table == NULL) {
      Status = gBS->LocateProtocol(&gEfiHalIommuProtocolGuid,
                                   NULL,
                                   (VOID **)&Iommu);
      if (Status != EFI_SUCCESS) {
         DEBUG((EFI_D_ERROR, "SDCC IOMMU LocateProtocol failed 0x%x\n", Status));
         return SDCC_BSP_ERR_UNKNOWN;
      }

      Iommu->_HAL_IOMMU_protocol_init(&fp_table);
   }

   /* Create Domain for SDC1 */
   if (HAL_IOMMU_ERR_OK != fp_table->domain_create_func(&sdc1_domain_hdl)) {
      DEBUG((EFI_D_ERROR, "SDC1 IOMMU domain create failed\n"));
      return SDCC_BSP_ERR_UNKNOWN;
   }

   /* Attach SDC1 to the domain */
   if (HAL_IOMMU_ERR_OK != fp_table->config_bypass_domain_func(sdc1_domain_hdl, 
                                                               HAL_IOMMU_AARCH64_NON_CCA_DOMAIN_TYPE))
   {
      DEBUG((EFI_D_ERROR, "SDC1 IOMMU domain configure failed\n"));
      return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
   }

   if (HAL_IOMMU_ERR_OK != fp_table->domain_attach_func(sdc1_domain_hdl, (void *)"SDC1_EMMC", 
                                                        ((IORT_WORLD_ID_NON_SECURE << IORT_WORLD_ID_SHIFT) \
                                                         | (IORT_DYNAMIC_MAPPING_NO << IORT_DYNAMIC_MAPPING_SHIFT) \
                                                         | (IORT_TRANSLATION_TYPE_NESTED << IORT_TRANSLATION_TYPE_SHIFT)), 0x0))
   {
      DEBUG((EFI_D_ERROR, "SDC1 IOMMU domain attach failed\n"));
      return SDCC_BSP_ERR_UNKNOWN;
   }

   /* Create Domain for SDC2 */
   if (HAL_IOMMU_ERR_OK != fp_table->domain_create_func(&sdc2_domain_hdl)) {
      DEBUG((EFI_D_ERROR, "SDC2 IOMMU domain create failed\n"));
      return SDCC_BSP_ERR_UNKNOWN;
   }

   /* Attach SDC2 to the domain */
   if (HAL_IOMMU_ERR_OK != fp_table->config_bypass_domain_func(sdc2_domain_hdl, 
                                                               HAL_IOMMU_AARCH64_NON_CCA_DOMAIN_TYPE))
   {
      DEBUG((EFI_D_ERROR, "SDC2 IOMMU domain configure failed\n"));
      return SDCC_BSP_ERR_FEATURE_UNSUPPORTED;
   }

   if (HAL_IOMMU_ERR_OK != fp_table->domain_attach_func(sdc2_domain_hdl, (void *)"SDC2", 
                                                        ((IORT_WORLD_ID_NON_SECURE << IORT_WORLD_ID_SHIFT) \
                                                         | (IORT_DYNAMIC_MAPPING_NO << IORT_DYNAMIC_MAPPING_SHIFT) \
                                                         | (IORT_TRANSLATION_TYPE_NESTED << IORT_TRANSLATION_TYPE_SHIFT)), 0x0))
   {
      DEBUG((EFI_D_ERROR, "SDC2 IOMMU domain attach failed\n"));
      return SDCC_BSP_ERR_UNKNOWN;
   }

   configure_completed = TRUE; 

   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_default_volt_corner
*
* DESCRIPTION   Provides the default voltage corner 
*
* PARAMETERS    [OUT]: volt_corner
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_default_volt_corner (UINT8 *volt_corner)
{
   if (volt_corner != NULL) {
      *volt_corner = VOLT_CORNER_NOM;
      return SDCC_BSP_NO_ERROR;
   }
   else {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }
}

/******************************************************************************
* FUNCTION      sdcc_bsp_check_valid_operational_mode
*
* DESCRIPTION   Checks whether the voltage corner and speed mode are compatible
*
* PARAMETERS    [IN]: driveno
*               [IN]: volt_corner
*               [IN]: speed_mode
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_check_valid_operational_mode (UINT32 driveno, 
                                                         UINT8 volt_corner, 
                                                         UINT8 speed_mode)
{
   uint32_t i = 0;
   uint32_t pm_entries = 0; 
   sdcc_bsp_pm_info *pm_info = NULL; 

   if (driveno == SDCC_BSP_SLOT_1) 
   {
      pm_entries = sizeof(sd_pm_params) / sizeof(sdcc_bsp_pm_info);
      pm_info = sd_pm_params;
   }
   else
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   for (i = 0; i < pm_entries; i++) 
   {
      if (pm_info[i].volt_corner == volt_corner) 
      {
         break;
      }
   }

   if (i == pm_entries) 
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   if (pm_info[i].max_speed_mode >= speed_mode) 
   {
      return SDCC_BSP_NO_ERROR;
   }

  return SDCC_BSP_ERR_INVALID_PARAM;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_operational_mode_info
*
* DESCRIPTION   Provides information about speed modes and voltage corners
*               supported
*
* PARAMETERS    [IN]: driveno
*               [IN]: curr_speed_mode
*               [OUT]: caps
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_operational_mode_info (UINT32 driveno,
                                                  sdcc_bsp_speed_mode curr_speed_mode, 
                                                  void *caps)
{
   (void)driveno; 
   EFI_STORAGE_OP_MODE_CAPABILITIES *SdccCaps;
   UINT8 i = 0;

   if (caps == NULL) 
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }

   SdccCaps = (EFI_STORAGE_OP_MODE_CAPABILITIES *)caps;

   if (curr_speed_mode < SDCC_MAX_SPEED_MODE) {
      SdccCaps->NumSpeedLevels = curr_speed_mode;
   }
   else {
      SdccCaps->NumSpeedLevels = SDCC_MAX_SPEED_MODE;
   }

   for (i = 0; i < VOLT_CORNER_MAX; i++) {
      if (sd_pm_params[i].max_speed_mode == SDCC_INVALID_SPEED) {
         SdccCaps->VoltCornerSupported[i] = 0;
      }
      else {
         SdccCaps->VoltCornerSupported[i] = 1;
      }
   }

   return SDCC_BSP_NO_ERROR;
}

/******************************************************************************
* FUNCTION      sdcc_bsp_volt_set
*
* DESCRIPTION   Turns on voltage regulators for SD Card(SDC2)
*
* PARAMETERS    [IN]: driveno
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_volt_set (UINT32 driveno, sdcc_bsp_regulator_mode mode)
{
   /* For RUMI (SOC_EMULATION_TYPE = 1) */
   if (1 == (in_dword(HWIO_TCSR_SOC_EMULATION_TYPE) & 0x3))
   {
      return SDCC_BSP_NO_ERROR;
   }

   if (driveno == SDCC_BSP_SLOT_1)
   {
      if (sd_mmc_vdd_handle == NULL) 
      {
         sd_mmc_vdd_handle = npa_create_sync_client(PMIC_NPA_GROUP_ID_SD_MMC_VDD, "sd_mmc_vdd", NPA_CLIENT_REQUIRED);
         if (sd_mmc_vdd_handle == NULL) 
         {
             return SDCC_BSP_ERR_PMIC;
         }
      }

      if (sd_mmc_vdd_px2_handle == NULL) 
      {
         sd_mmc_vdd_px2_handle = npa_create_sync_client(PMIC_NPA_GROUP_ID_SD_MMC_VDD_PX2, "sd_mmc_vdd_px2", NPA_CLIENT_REQUIRED);
         if (sd_mmc_vdd_px2_handle == NULL) 
         {
             return SDCC_BSP_ERR_PMIC;
         }
      }

      if (mode == SDCC_BSP_REGULATORS_ON && volt_set_done != TRUE) 
      {
         npa_issue_required_request(sd_mmc_vdd_handle, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
         npa_issue_required_request(sd_mmc_vdd_px2_handle, PMIC_NPA_MODE_ID_GENERIC_HV);
		 volt_set_done = TRUE;    
      }
      else if (mode == SDCC_BSP_REGULATORS_OFF) 
      {
         npa_issue_required_request(sd_mmc_vdd_handle, PMIC_NPA_MODE_ID_GENERIC_OFF);
         npa_issue_required_request(sd_mmc_vdd_px2_handle, PMIC_NPA_MODE_ID_GENERIC_OFF);
		 volt_set_done = FALSE;   
      }
      else
      {
         return SDCC_BSP_ERR_INVALID_PARAM;
      }
   }
   else
   {
      return SDCC_BSP_ERR_INVALID_PARAM;
   }
   	
   return SDCC_BSP_NO_ERROR;   
}

/******************************************************************************
* FUNCTION      sdcc_bsp_get_config
*
* DESCRIPTION   Get the SDCC configuration for differnt parameters from the target specific files
*
* PARAMETERS    [IN]: Drive Number , sdcc_bsp_config structure
*
* RETURN VALUE  sdcc_bsp_err_type
*
******************************************************************************/
sdcc_bsp_err_type sdcc_bsp_get_config (UINT32 driveno, sdcc_bsp_config *sdcc_config_data)
{
	sdcc_config_data->ExtSlotNumber   =  1;
	sdcc_config_data->MAXSlotNumber   =  2;
	sdcc_config_data->DmaEnabled      =  TRUE;
	sdcc_config_data->EmmcSlotNumber  =  0;
    sdcc_config_data->SpeedMode   =  sdcc_bsp_get_platform_speed_config (driveno);
	
	return SDCC_BSP_NO_ERROR;
	
}	
/******************************************************************************
* FUNCTION      sdcc_bsp_get_rca
*
* DESCRIPTION   Get the SDCC Relative Card Address from the target specific files
*
* PARAMETERS    [IN]: Drive Number
*
* RETURN VALUE  RCA value
*
******************************************************************************/

UINT16 sdcc_bsp_get_rca (UINT32 driveno)
{
	UINT16 rca = 0;
	
	if (driveno == SDCC_BSP_SLOT_0)
	{
	    rca = 2;
	}
	return rca;
}


/******************************************************************************
* FUNCTION      sdcc_bsp_is_adma_supported
*
* DESCRIPTION   Get the SDCC ADMA availability from the target specific files
*
* PARAMETERS    [IN]: None
*
* RETURN VALUE  Boolean value
*
******************************************************************************/

BOOLEAN sdcc_bsp_is_adma_supported() 
{
	BOOLEAN ret = TRUE;
	return ret;
}

