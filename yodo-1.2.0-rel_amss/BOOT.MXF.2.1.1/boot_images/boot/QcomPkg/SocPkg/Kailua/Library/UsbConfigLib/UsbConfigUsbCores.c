/** @file \UsbConfigUsbCores.c

  Function and structure definitions for each USB core supported by this
  platform.

**/
//============================================================================
/**
  Copyright (c) 2015-2020 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================

/*=============================================================================
                              EDIT HISTORY


 when       who      what, where, why
 --------   ---      ----------------------------------------------------------
 04/15/20   ps       Added force primary and secondary to enumerate in HS
 04/18/19   gk       Fix the UsbConfigDxe Taking More Boot time
 03/26/19   ak       Support for advancing TX SuperSpeed compliance test pattern
 02/20/19   kameya   Fix GCC reset secondary USB controller and disable USB20 internal retry feature.
 01/16/19   gk       Added Support to Turnoff NPA for all cores.
 12/26/18   gk       Added Register for Non-Driving Mode
 10/11/18   kameya   Support USB SLT loopback feature.
 04/19/18   amitg    Poipu Multi-Port Support
 04/10/18   amitg    Poipu BU Fixes
 04/03/18   psapin   Remove extra ICBArb bandwidth requests for Poipu BU, set Port 2 naming as 3_2
 02/13/18   gk	     Port changes from boot.xf.2.0 and boot.xf.2.2
 01/30/18   pm       Fixed issue to StartUsbController, if no USB cable connected during bootup
 01/22/18   gk       Added USB Variable to Enable High Speed Mode For Display port
 01/05/17   jaychoi  Porting MP Core Changes for Hana from Poipu
 10/20/17   gk       Updated new Pmic API for UsbPwrCtrlDxe for UEFI
 08/10/17   amitg    Init Changes for Poipu
 06/14/17   amitg    Bus Bandwidth Vote for primary and secondary core and cleanup
 04/26/17   jc       Added missing PMI8998 check to switch primary to SS3 LDO
 03/22/17   pm       Added configuration for sec Clock and core
 03/21/17   amitg    SDM845 UEFI USB Updates
 03/16/17   pm       Enabled the initialization of clk
 03/06/17   amitg    EUD Support
 02/03/17   pm       Vbus Enablement in USB Config Protocol
 02/03/17   pm       Port from Boot.xf.1.4
 01/24/17   pm       Fix the USB clock reference count
 01/19/17   pm       Do not set PIPE3 freq to XO
 12/20/16   sm       Edited input parameter list for EnableOtg PmicUsbProtocol API
 09/22/16   amitg    Napali Pre-Si Updates
 05/06/16   ck       Temp workaround by enable VBUS asap
 04/29/16   ck       Update HS PHY init for host mode
 03/31/16   ck       Disable SS PHY init for BU and correct HS PHY init
 02/23/16   ck       Isolate UsbCore data within the module
 01/22/16   ck       Fix the USB debug message usages
 01/14/16   ck       Enable host mode support in Virtio
 11/24/15   ck       Virtio FBC support
 10/26/15   ck       Init Sdm845 Pre-Si support
=============================================================================*/

#include "UsbConfigUsbCoresPrivate.h"
#include "UsbSharedLib.h"
#include "api/systemdrivers/icbarb.h"
#include "DALSys.h"

#define FREQ_MHZ(f)     (f * 1000 * 1000)
#define FREQ_KHZ(f)     (f * 1000)
#define QUSB_DCI_PMI_INDEX                    (7)   /*For PMIC_D*/

/*
 * USB 3.0 Clock definitions
 */
#define USB3_MASTER_CLK_MIN_FREQ_HZ           FREQ_MHZ(200)
#define USB3_AXI_CLK_MIN_FREQ_HZ              FREQ_MHZ(200)
#define USB3_PHY_AUX_CLK_MIN_FREQ_HZ          FREQ_KHZ(19200)
// Mock CLK needs to be set at 19.2 Mhz
#define USB3_MOCK_CLK_MIN_FREQ_HZ             FREQ_KHZ(19200)
// Vote for no frequency
#define USB3_NOC_CLK_MIN_FREQ_HZ              FREQ_MHZ(0)

#define MICRO_STALL_UNITS(x)  ((x) * 10)
#define MILLI_STALL_UNITS(x)  ((x) * 10000)

#define QUSB_PHY_MAX_STATUS_VERIFY_ATTEMPTS   50

#define USB3_INC_CMPL_PATTERN(x)  x=((x+1)%16)


/* Power Domain list */
const CHAR8 SSUsb1PowerDomain[] = "gcc_usb30_prim_gdsc";

#ifdef USB_SEC_FLAG	
const CHAR8 SSUsb2PowerDomain[] = "gcc_usb30_sec_gdsc";
#endif
#ifdef USB_MP_FLAG
const CHAR8 SSUsb3PowerDomain[] = "usb30_mp_gdsc";
#endif

/*******************************************************************************
 * USB core structures
 ******************************************************************************/

/*
 * USB core enable clock configuration arrays
 */
// gcc_ahb2phy_south_clk would be turned ON by BOOT (PBL/XBL), so can be removed

QCOM_USB_CLOCK SSUsb1EnCoreClocks[] =
{
  //{ "clock name",                     frequency,                    divider }
  {"gcc_cfg_noc_usb3_prim_axi_clk",     USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_aggre_usb3_prim_axi_clk",       USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb30_prim_master_clk",         USB3_MASTER_CLK_MIN_FREQ_HZ,   1 },
  {"gcc_usb30_prim_sleep_clk",          0,                             1 },
  {"gcc_usb30_prim_mock_utmi_clk",      USB3_MOCK_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb3_prim_phy_aux_clk",         USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_prim_phy_com_aux_clk",     USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },  
  {"gcc_usb3_prim_phy_pipe_clk",        0,                             1 }

};
#ifdef USB_SEC_FLAG	

QCOM_USB_CLOCK SSUsb2EnCoreClocks[] =
{
  //{ "clock name",                    frequency,                    divider }
  {"gcc_cfg_noc_usb3_sec_axi_clk",     USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_aggre_usb3_sec_axi_clk",       USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb30_sec_master_clk",         USB3_MASTER_CLK_MIN_FREQ_HZ,   1 },
  {"gcc_usb30_sec_sleep_clk",          0,                             1 },
  {"gcc_usb30_sec_mock_utmi_clk",      USB3_MOCK_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb3_sec_phy_aux_clk",         USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_sec_phy_com_aux_clk",     USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },    
  {"gcc_usb3_sec_phy_pipe_clk",        0,                             1 },
  {"gcc_aggre_usb_noc_axi_clk",        USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_aggre_usb_noc_north_axi_clk",  USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_aggre_usb_noc_south_axi_clk",  USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_sys_noc_usb_axi_clk",          USB3_NOC_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb4_clkref_en",               0,                             1 },
};
#endif
#ifdef USB_MP_FLAG
QCOM_USB_CLOCK SSUsb3EnCoreClocks[] =
{
  //{ "clock name",                    frequency,                    divider }
  {"gcc_cfg_noc_usb3_mp_axi_clk",     USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_aggre_usb3_mp_axi_clk",       USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb30_mp_master_clk",         USB3_MASTER_CLK_MIN_FREQ_HZ,   1 },
  {"gcc_usb30_mp_sleep_clk",          0,                             1 },
  {"gcc_usb30_mp_mock_utmi_clk",      USB3_MOCK_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb3_mp_phy_aux_clk",         USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_mp_phy_com_aux_clk",     USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_mp_phy_pipe_0_clk",      0,                             1 },
  {"gcc_usb3_mp_phy_pipe_1_clk",      0,                             1 },
  {"gcc_aggre_usb_noc_axi_clk",       USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_aggre_usb_noc_north_axi_clk", USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_aggre_usb_noc_south_axi_clk", USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_sys_noc_usb_axi_clk",         USB3_NOC_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb3_mp0_clkref_en",          0,                             1 },
  {"gcc_usb3_mp1_clkref_en",          0,                             1 },
  {"gcc_usb2_hs0_clkref_en",          0,                             1 },
  {"gcc_usb2_hs1_clkref_en",          0,                             1 },
  {"gcc_usb2_hs2_clkref_en",          0,                             1 },
  {"gcc_usb2_hs3_clkref_en",          0,                             1 },
};
#endif 

/*
 * USB core disable clock configuration arrays
 */

QCOM_USB_CLOCK SSUsb1DisCoreClocks[] =
{
  {"gcc_cfg_noc_usb3_prim_axi_clk",     USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_aggre_usb3_prim_axi_clk",       USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb30_prim_master_clk",         USB3_MASTER_CLK_MIN_FREQ_HZ,   1 },
  {"gcc_usb30_prim_sleep_clk",          0,                             1 },
  {"gcc_usb30_prim_mock_utmi_clk",      USB3_MOCK_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb3_prim_phy_aux_clk",         USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 }, 
  {"gcc_usb3_prim_phy_com_aux_clk",     USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },    
  {"gcc_usb3_prim_phy_pipe_clk",        0,                             1 }
};

#ifdef USB_SEC_FLAG	

QCOM_USB_CLOCK SSUsb2DisCoreClocks[] =
{
  {"gcc_cfg_noc_usb3_sec_axi_clk",     USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_aggre_usb3_sec_axi_clk",       USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb30_sec_master_clk",         USB3_MASTER_CLK_MIN_FREQ_HZ,   1 },
  {"gcc_usb30_sec_sleep_clk",          0,                             1 },
  {"gcc_usb30_sec_mock_utmi_clk",      USB3_MOCK_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb3_sec_phy_aux_clk",         USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 }, 
  {"gcc_usb3_sec_phy_com_aux_clk",     USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_sec_phy_pipe_clk",        0,                             1 },
  {"gcc_aggre_usb_noc_axi_clk",         USB3_NOC_CLK_MIN_FREQ_HZ,     1 }, 
  {"gcc_aggre_usb_noc_north_axi_clk",   USB3_NOC_CLK_MIN_FREQ_HZ,     1 }, 
  {"gcc_aggre_usb_noc_south_axi_clk",   USB3_NOC_CLK_MIN_FREQ_HZ,     1 }, 
  {"gcc_sys_noc_usb_axi_clk",           USB3_NOC_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb4_clkref_en",               0,                             1 },
};
#endif
#ifdef USB_MP_FLAG
QCOM_USB_CLOCK SSUsb3DisCoreClocks[] =
{
  {"gcc_cfg_noc_usb3_mp_axi_clk",     USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_aggre_usb3_mp_axi_clk",       USB3_AXI_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb30_mp_master_clk",         USB3_MASTER_CLK_MIN_FREQ_HZ,   1 },
  {"gcc_usb30_mp_sleep_clk",          0,                             1 },
  {"gcc_usb30_mp_mock_utmi_clk",      USB3_MOCK_CLK_MIN_FREQ_HZ,     1 },
  {"gcc_usb3_mp_phy_aux_clk",         USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_mp_phy_com_aux_clk",     USB3_PHY_AUX_CLK_MIN_FREQ_HZ,  1 },
  {"gcc_usb3_mp_phy_pipe_0_clk",      0,                             1 },
  {"gcc_usb3_mp_phy_pipe_1_clk",      0,                             1 },
  {"gcc_aggre_usb_noc_axi_clk",       USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_aggre_usb_noc_north_axi_clk", USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_aggre_usb_noc_south_axi_clk", USB3_NOC_CLK_MIN_FREQ_HZ,      1 }, 
  {"gcc_sys_noc_usb_axi_clk",         USB3_NOC_CLK_MIN_FREQ_HZ,      1 },
  {"gcc_usb3_mp0_clkref_en",          0,                             1 },
  {"gcc_usb3_mp1_clkref_en",          0,                             1 },
  {"gcc_usb2_hs0_clkref_en",          0,                             1 },
  {"gcc_usb2_hs1_clkref_en",          0,                             1 },
  {"gcc_usb2_hs2_clkref_en",          0,                             1 },
  {"gcc_usb2_hs3_clkref_en",          0,                             1 },
};
#endif

/*
 * Static Variables
 */
// TLMMProtocol to enable USB HUB
EFI_TLMM_PROTOCOL                             *TLMMProtocol = NULL;

// PMIC GPIO protocol
EFI_QCOM_PMIC_GPIO_PROTOCOL                   *PmicGpioProtocol = NULL;

// NPA Client Handle for SS1 and SS2 Cores
STATIC npa_client_handle                      gPmicNpaClientSS1 = NULL;

// HS0 vote is special that it powers EUD USB2PHY, so do not vote off
STATIC npa_client_handle                      gPmicNpaClientHS1 = NULL;

#ifdef USB_SEC_FLAG	
STATIC npa_client_handle                      gPmicNpaClientSS1 = NULL;
STATIC npa_client_handle                      gPmicNpaClientHS1 = NULL;
#endif

#ifdef USB_MP_FLAG
STATIC npa_client_handle                      gPmicNpaClientSS2 = NULL;
STATIC npa_client_handle                      gPmicNpaClientHS2 = NULL;
STATIC npa_client_handle                      gPmicNpaClientSS3 = NULL;
STATIC npa_client_handle                      gPmicNpaClientHS3 = NULL;
STATIC npa_client_handle                      gPmicNpaClientHS4 = NULL;
STATIC npa_client_handle                      gPmicNpaClientHS5 = NULL;
#endif

//NPA client handles for ICB - required for all cores
STATIC npa_client_handle                      gNpaClientSS1Bus = NULL;
#ifdef USB_SEC_FLAG	
STATIC npa_client_handle                      gNpaClientSS2Bus = NULL;
#endif
#ifdef USB_MP_FLAG
STATIC npa_client_handle                      gNpaClientSS3Bus = NULL;
#endif

EFI_CLOCK_PROTOCOL                            *ClockProtocol = NULL;
EFI_USB_PWR_CTRL_PROTOCOL                     *gPwrCtrlProtocol = NULL;

extern EFI_GUID                               gQcomTokenSpaceGuid;
extern EFI_PLATFORMINFO_PLATFORM_INFO_TYPE    PlatformInfo;
extern BOOLEAN                                gHighSpeedOnlyPrimary;
extern BOOLEAN                                gUSBPriDPBonded; 
static UINT8                                  Usb1HstCmplPattNum = 0;
#ifdef USB_SEC_FLAG
extern BOOLEAN                                gHighSpeedOnlySecondary;
static UINT8                                  Usb2HstCmplPattNum = 0;
extern BOOLEAN                                gUSBSecDPBonded; 
#endif
#ifdef USB_MP_FLAG
static UINT8                                  Usb3HstCmplPattNum = 0;
extern BOOLEAN                                gHighSpeedOnlyMP;
#endif

/*******************************************************************************
 * ICB bandwidth request for USB Port 0, 1 and 2
 ******************************************************************************/
STATIC CONST ICBArb_RequestType usb_icb_request[] = 
{
  {
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 = 
    {
      .uIb = 400000000,        /**< Instantaneous bandwidth in Bytes/second */
      .uAb = 0,                /**< Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0          /**< Latency requirement in nanoseconds */
    }
  }
  #ifdef USB_SEC_FLAG	
  ,{
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 = 
    {
      .uIb = 670000000,        /**< Instantaneous bandwidth in Bytes/second */
      .uAb = 670000000,        /**< Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0          /**< Latency requirement in nanoseconds */
    }
  }
  #endif
};

STATIC CONST ICBArb_RequestType usb_icb_clrrequest[] = 
{
  {
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 = 
    {
      .uIb = 0,                /**< Instantaneous bandwidth in Bytes/second */
      .uAb = 0,                /**< Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0          /**< Latency requirement in nanoseconds */
    }
  }
#ifdef USB_SEC_FLAG	
,
  {
    .arbType = ICBARB_REQUEST_TYPE_3,
    .arbData.type3 = 
    {
      .uIb = 0,                /**< Instantaneous bandwidth in Bytes/second */
      .uAb = 0,                /**< Arbitrated bandwidth in Bytes/second */
      .uLatencyNs = 0          /**< Latency requirement in nanoseconds */
    }
  }
#endif
};


/*******************************************************************************
 * ICB Master and Slave list for USB Port 0, USB Port 1, and USB Port 2
 ******************************************************************************/
STATIC CONST ICBArb_MasterSlaveType usbport0_str_slv_lst[] = 
{
  {
    .eMaster = ICBID_MASTER_APPSS_PROC,
    .eSlave = ICBID_SLAVE_USB3_0
  },
  {
    .eMaster = ICBID_MASTER_USB3_0,
    .eSlave = ICBID_SLAVE_EBI1
  }
};
#ifdef USB_SEC_FLAG	

STATIC CONST ICBArb_MasterSlaveType usbport1_str_slv_lst[] = 
{
  {
    .eMaster = ICBID_MASTER_APPSS_PROC,
    .eSlave = ICBID_SLAVE_USB3_1
  },
  {
    .eMaster = ICBID_MASTER_USB3_1,
    .eSlave = ICBID_SLAVE_EBI1
  }
};
#endif
#if USB_MP_FLAG
STATIC CONST ICBArb_MasterSlaveType usbport2_str_slv_lst[] = 
{
  {
    .eMaster = ICBID_MASTER_APPSS_PROC,
    .eSlave = ICBID_SLAVE_USB3_MP
  },
  {
    .eMaster = ICBID_MASTER_USB3_MP,
    .eSlave = ICBID_SLAVE_EBI1
  }
};
#endif

static 
EFI_STATUS 
UsbConfigLib_pmic_npa_create_sync_client(
  OUT npa_client_handle *handle_ptr,
  IN CONST CHAR8        *group_name,
  IN CONST CHAR8        *client_name
  )
{
  if (NULL == (*handle_ptr))
  {
    *handle_ptr = npa_create_sync_client(group_name, client_name, NPA_CLIENT_REQUIRED);
    if (NULL == (*handle_ptr))
    {
      DBG(EFI_D_ERROR, "USB (%s) cannot be created", group_name);
      return EFI_INVALID_PARAMETER;
    }
  }
  return EFI_SUCCESS;
}


static 
EFI_STATUS 
UsbConfigLib_pmic_npa_issue_required_request(
  IN npa_client_handle handle,
  IN UINT32            mode
  )
{
  if (handle)
  {
    npa_issue_required_request(handle, mode);   //Sends the request to RPM, no return
    DBG(EFI_D_INFO, "UsbConfigLib_pmic_npa_issue_required_request: handle (0x%x), mode (%u)", mode);
  }
  else
  {
    DBG(EFI_D_INFO, "UsbConfigLib_pmic_npa_issue_required_request: NULL handle"); 
    return EFI_INVALID_PARAMETER;
  }
  return EFI_SUCCESS;
}


/*******************************************************************************
 * Core initialization function implementations
 ******************************************************************************/

/*
 * See UsbConfigLibPrivate.h
 */
STATIC
EFI_STATUS
UsbConfigLibOpenProtocols (
  VOID
  )
{
  EFI_STATUS                        Status              = EFI_SUCCESS;
  EFI_PM_DEVICE_INFO_TYPE           PmiDeviceInfo       = {0};
  EFI_QCOM_PMIC_VERSION_PROTOCOL   *PmicVersionProtocol = NULL;

  FNC_ENTER_MSG();

  //TODO:CK:Temp. use WRN_CHK to avoid issues
  if (!ClockProtocol) {
    Status = gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID**)&ClockProtocol);
    if (EFI_ERROR(Status)) {
      ClockProtocol = NULL;
      WRN_CHK("failed to locate CLOCK protocol");
    }
  }

   if (NULL == gPwrCtrlProtocol) {
    // Find the Power control USB charger protocol
    Status = gBS->LocateProtocol(&gQcomUsbPwrCtrlProtocolGuid, NULL, (void**)&gPwrCtrlProtocol);
    if (EFI_ERROR(Status))
    {
      gPwrCtrlProtocol = NULL;
      WRN_CHK("Failed to open Power control USB protocol Status =  (0x%x)", Status);
    }
  }
 
  //Creating NPA sync client for USB Super speed Primary core
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientSS1, PMIC_NPA_GROUP_ID_USB_SS1, "usb_ss1");
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientHS1, PMIC_NPA_GROUP_ID_USB_HS1, "usb_hs1");

  if (usb_shared_is_eud_active())
  {
    DBG(EFI_D_ERROR, "EUD is active. PRIM USB2PHY LDO ON");
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS1, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
  }

  // Detect PMI charger presence for charger API availability
  Status = gBS->LocateProtocol(&gQcomPmicVersionProtocolGuid, NULL, (VOID **)&PmicVersionProtocol);
  if (EFI_ERROR(Status))
  {
    DBG(EFI_D_ERROR, "failed to locate PMIC version protocol");
  }
  else
  {
    Status = PmicVersionProtocol->GetPmicInfo(QUSB_DCI_PMI_INDEX, &PmiDeviceInfo);
    WRN_CHK("failed to read PMI version");
  }
  
  DBG(EFI_D_ERROR, "PMI version (0x%X)", PmiDeviceInfo.PmicModel);
  
  // If there is error reading PMIC version or PMI report invalid version
  // 
  if ( (EFI_ERROR(Status))
    || (PmiDeviceInfo.PmicModel == EFI_PMIC_IS_UNKNOWN)
    || (PmiDeviceInfo.PmicModel == EFI_PMIC_IS_INVALID) )
  {
    if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_CDP)
    {
      
      DBG(EFI_D_ERROR, "Missing PMI (0x%X) on CDP (possibly no CDT), switching platform to UNKNOWN", 
        PmiDeviceInfo.PmicModel);
      PlatformInfo.platform = EFI_PLATFORMINFO_TYPE_UNKNOWN;
    }
  }

  //Create NPA nodes for USB Primary Controller required buses requests
  if (!gNpaClientSS1Bus) {
    gNpaClientSS1Bus = npa_create_sync_client_ex( "/icb/arbiter",
                           "usb_ss1_bus",
                           NPA_CLIENT_VECTOR,
                           sizeof(usbport0_str_slv_lst),
                           (void *)&usbport0_str_slv_lst);

    if (!gNpaClientSS1Bus){
      WRN_CHK("gNpaClientSS1Bus cannot be created");
    }
  }
#ifdef USB_SEC_FLAG	

  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientSS1, PMIC_NPA_GROUP_ID_USB_SS1, "usb_ss1");
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientHS1, PMIC_NPA_GROUP_ID_USB_HS1, "usb_hs1");

  //Create NPA nodes for USB secondary controller required buses requests
  if (!gNpaClientSS2Bus) {
    gNpaClientSS2Bus = npa_create_sync_client_ex( "/icb/arbiter",
                           "usb_ss1_bus",
                           NPA_CLIENT_VECTOR,
                           sizeof(usbport1_str_slv_lst),
                           (void *)&usbport1_str_slv_lst);

    if (!gNpaClientSS2Bus)
    {
      WRN_CHK("gNpaClientSS2Bus cannot be created");
    }
  }
#endif
#ifdef USB_MP_FLAG
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientSS2, PMIC_NPA_GROUP_ID_USB_SS2, "usb_ss2");
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientHS2, PMIC_NPA_GROUP_ID_USB_HS2, "usb_hs2");
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientSS3, PMIC_NPA_GROUP_ID_USB_SS3, "usb_ss3");
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientHS3, PMIC_NPA_GROUP_ID_USB_HS3, "usb_hs3");
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientHS4, PMIC_NPA_GROUP_ID_USB_HS4, "usb_hs4");
  UsbConfigLib_pmic_npa_create_sync_client(&gPmicNpaClientHS5, PMIC_NPA_GROUP_ID_USB_HS5, "usb_hs5");

  //Create NPA nodes for USB MP controller required buses requests
  if (!gNpaClientSS3Bus) {
    gNpaClientSS3Bus = npa_create_sync_client_ex( "/icb/arbiter",
                           "usb_ss1_bus",
                           NPA_CLIENT_VECTOR,
                           sizeof(usbport2_str_slv_lst),
                           (void *)&usbport2_str_slv_lst);

    if (!gNpaClientSS3Bus)
    {
      WRN_CHK("gNpaClientSS3Bus cannot be created");
    }
  }
#endif
  if (!PmicGpioProtocol) {
    Status = gBS->LocateProtocol(&gQcomPmicGpioProtocolGuid, NULL, (void **)&PmicGpioProtocol);
    if (EFI_ERROR(Status))
    {
      PmicGpioProtocol = NULL;
      WRN_CHK("Failed to open PMIC GPIO protocol Status =  (0x%x)", Status);
    }
  }

//TODO:CK:Temp. use ON_EXIT, remove Status = EFI_SUCCESS later
//ON_EXIT:
  FNC_LEAVE_MSG();
  Status = EFI_SUCCESS;
  return Status;
}

/**
  Initializes power domains for USB.

  @retval EFI_SUCCESS            USB clocks initialized successfully.
  @retval EFI_NOT_FOUND          Unable to locate clock protocol.

**/
STATIC
EFI_STATUS
EFIAPI
ConfigPowerDomain(
  IN BOOLEAN       bEnable,
  IN CONST CHAR8   *szDomain
  )
{
  EFI_STATUS   Status = EFI_SUCCESS;
  UINTN        uClockPowerDomainId;

  FNC_ENTER_MSG ();

  if (ClockProtocol)
  {
      Status = ClockProtocol->GetClockPowerDomainID(ClockProtocol, szDomain, &uClockPowerDomainId);
      WRN_CHK ("USBConfigLib:GetClockPowerDomainID failed!");

      if (TRUE == bEnable)
      {
        Status =  ClockProtocol->EnableClockPowerDomain(ClockProtocol, uClockPowerDomainId);
        WRN_CHK ("USBConfigLib:EnableClockPowerDomain failed!");
      }
      else if (FALSE == bEnable)
      {
        Status =  ClockProtocol->DisableClockPowerDomain(ClockProtocol, uClockPowerDomainId);
        WRN_CHK ("USBConfigLib:DisableClockPowerDomain failed!");
      }
  }
  else
  {
      WRN_CHK ("failed to locate Clock Protocol ");
      WRN_CHK ("failed to initialize PowerDomain");
  }

  FNC_LEAVE_MSG ();
  return Status;
}



/**
  Initializes all clocks for a USB core.

  @param [in]  Clocks       Clock array
  @param [in]  ClockCount   Number of clocks in array

  @retval EFI_SUCCESS       USB clocks enabled successfully
  @retval Others            Error enabling at least 1 clock
**/
STATIC
EFI_STATUS
InitUsbClocks (
  IN  UINTN                 ClockCount,
  IN  QCOM_USB_CLOCK        *Clocks
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINTN       ClkIdx;

  FNC_ENTER_MSG ();

  // validate parameters
  if ((NULL == Clocks) || (0 == ClockCount)) {
    Status = EFI_INVALID_PARAMETER;
    DBG(EFI_D_ERROR, "invalid parameter");
    goto ON_EXIT;
  }

  if (NULL == ClockProtocol) {
    DBG(EFI_D_INFO, "ClockProtocol unavailable");
    // Trying to open Protocol may be done in case, 
    // USB Protocol Open was skipped if dynamic initialization of XHCI by client.
    Status = UsbConfigLibOpenProtocols();
    ERR_CHK("UsbConfigLibOpenProtocols failed %r",Status);
    goto ON_EXIT;
  }

  // enable each clock
  for (ClkIdx = 0; ClkIdx < ClockCount; ClkIdx++) {
    Status = EnableClock (
                Clocks[ClkIdx].Name,
                Clocks[ClkIdx].Frequency,
                Clocks[ClkIdx].Divider
                );
    if (EFI_ERROR (Status)) {
      DBG(EFI_D_ERROR, "failed to enable clock '%a'", Clocks[ClkIdx].Name);
    }
  }

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end InitUsbClocks


/**
  Disables all clocks for a USB core.

  @param [in]  Clocks       Clock array
  @param [in]  ClockCount   Number of clocks in array

  @retval EFI_SUCCESS       USB clocks disabled successfully
  @retval Others            Error disabling at least 1 clock
**/
STATIC
EFI_STATUS
DisableUsbClocks (
  IN  UINTN                 ClockCount,
  IN  QCOM_USB_CLOCK        *Clocks
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINTN       ClkIdx;

  FNC_ENTER_MSG ();
  DBG(EFI_D_INFO, "DisableUsbClocks");

  // validate parameters
  if ((NULL == Clocks) || (0 == ClockCount)) {
    Status = EFI_INVALID_PARAMETER;
    DBG(EFI_D_ERROR, "invalid parameter");
    goto ON_EXIT;
  }

  if (NULL == ClockProtocol) {
    DBG(EFI_D_ERROR, "ClockProtocol unavailable");
    Status = EFI_NOT_FOUND;
    goto ON_EXIT;
  }
  // disable each clock
  for (ClkIdx = 0; ClkIdx < ClockCount; ClkIdx++) {
    Status = DisableClock (Clocks[ClkIdx].Name);
    if (EFI_ERROR (Status)) {
      DBG(EFI_D_ERROR, "failed to disable clock '%a'", Clocks[ClkIdx].Name);
    }
  }

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
}

/*
 * See UsbConfigUsbCoresPublic.h
 */
EFI_STATUS
UsbConfigLibCloseNPA (
  VOID
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  FNC_ENTER_MSG();

  //Disable the clocks for primary port, since it ll be only enabled by default.
  
  UINTN           PrimaryEnClockCount   = sizeof(SSUsb1EnCoreClocks) / sizeof(QCOM_USB_CLOCK);
  QCOM_USB_CLOCK  *PrimaryEnClocks      = SSUsb1EnCoreClocks;
  UINTN           PrimaryDisClockCount  = sizeof(SSUsb1DisCoreClocks) / sizeof(QCOM_USB_CLOCK);
  QCOM_USB_CLOCK  *PrimaryDisClocks     = SSUsb1DisCoreClocks;
  
  // Enable clocks first, without that disable clocks does not work
  Status = InitUsbClocks (PrimaryEnClockCount, PrimaryEnClocks);
  usb_shared_refclk_enable(TRUE);
  WRN_CHK ("failed to initialize USB clocks");

  // Disable clocks for Primary Core controller
  Status = DisableUsbClocks (PrimaryDisClockCount, PrimaryDisClocks);
  WRN_CHK ("failed to disable USB clocks");
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS1, PMIC_NPA_MODE_ID_GENERIC_OFF);

  if (FALSE == usb_shared_is_eud_active())
  {
    usb_shared_refclk_enable(FALSE);
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS1, PMIC_NPA_MODE_ID_GENERIC_OFF);
  }

  
#ifdef USB_SEC_FLAG	  
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS1, PMIC_NPA_MODE_ID_GENERIC_OFF);
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS1, PMIC_NPA_MODE_ID_GENERIC_OFF);

#endif  
#ifdef USB_MP_FLAG  
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS2, PMIC_NPA_MODE_ID_GENERIC_OFF);
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS2, PMIC_NPA_MODE_ID_GENERIC_OFF);
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS3, PMIC_NPA_MODE_ID_GENERIC_OFF);
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS3, PMIC_NPA_MODE_ID_GENERIC_OFF);
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS4, PMIC_NPA_MODE_ID_GENERIC_OFF);
  UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS5, PMIC_NPA_MODE_ID_GENERIC_OFF);
#endif  

  // Remove Bus NPA votes for all Cores. Since we have turned On the votes using vector, so we need to disbale it with the same.
  if(gNpaClientSS1Bus){
    npa_issue_vector_request( gNpaClientSS1Bus,
                               (sizeof(usb_icb_clrrequest)/(sizeof(npa_resource_state))), 
                               ((npa_resource_state *)usb_icb_clrrequest) );
  }
#ifdef USB_SEC_FLAG		
  if(gNpaClientSS2Bus){
    npa_issue_vector_request( gNpaClientSS2Bus,
                               (sizeof(usb_icb_clrrequest)/(sizeof(npa_resource_state))), 
                               ((npa_resource_state *)usb_icb_clrrequest) );
  }
#endif  
#ifdef USB_MP_FLAG  
  if(gNpaClientSS3Bus){
    npa_issue_vector_request( gNpaClientSS3Bus,
                               (sizeof(usb_icb_clrrequest)/(sizeof(npa_resource_state))), 
                               ((npa_resource_state *)usb_icb_clrrequest) );
  }
#endif

  FNC_LEAVE_MSG ();
  return Status;
}


/**
  Enable vbus for primary port (SuperSpeed Port)
  @param  [in]  CoreNum          The CoreNum associated with the core number/port index.
  @retval EFI_SUCCESS            Success

**/
EFI_STATUS
EFIAPI
EnableVbusSS (
  UINT8 CoreNum
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;

  FNC_ENTER_MSG ();

  // For Clamshell Platform Host Mode Enablement is automatically taken care by EC
  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_CLS) {
     Status = EFI_SUCCESS;
     goto ON_EXIT;
  }
  else {
   if (NULL == gPwrCtrlProtocol) {
        // Find the Power Control USB charger protocol
        Status = gBS->LocateProtocol(&gQcomUsbPwrCtrlProtocolGuid, NULL, (void**)&gPwrCtrlProtocol);
      if (EFI_ERROR(Status)) {
          gPwrCtrlProtocol = NULL;
          WRN_CHK("Failed to open Power Control USB protocol Status =  (0x%x)", Status);
        goto ON_EXIT;
      }
    }

    Status = gPwrCtrlProtocol->SetVbusSourceEn(CoreNum, TRUE);
    WRN_CHK ("failed to enable Vbus, Status = 0x%x", Status);
  }

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
}


/**
  This API is used for resetting the Link and PHYs using clock control

  @param None

**/
VOID
SynopsysGccReset(
  IN  QCOM_USB_CORE         *UsbCore
)
{
  FNC_ENTER_MSG ();

  BOOLEAN is_eud_active = usb_shared_is_eud_active();

  if (UsbCore->CoreType == USB_CONFIG_SSUSB1)
  {
    ResetClock("gcc_usb30_prim_master_clk", EFI_CLOCK_RESET_ASSERT);
    if (FALSE == is_eud_active) {
      ResetClock("gcc_qusb2phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    }
    ResetClock("gcc_usb3_dp_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3phy_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall (100);
    ResetClock("gcc_usb3phy_phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_usb3_phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_usb3_dp_phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    if (FALSE == is_eud_active) {
      ResetClock("gcc_qusb2phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    }
    ResetClock("gcc_usb30_prim_master_clk", EFI_CLOCK_RESET_DEASSERT);
    gBS->Stall (100);
  }
#ifdef USB_SEC_FLAG
  else if(UsbCore->CoreType == USB_CONFIG_SSUSB2) 
{
    // TBD - Sort out reset registers
    ResetClock("gcc_usb30_sec_master_clk", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall (100);
    ResetClock("gcc_usb30_sec_master_clk", EFI_CLOCK_RESET_DEASSERT);

    ResetClock("gcc_usb2_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb4_1_dp_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3_dp_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3phy_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);    
    gBS->Stall (100);
    ResetClock("gcc_usb3phy_phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT);    
    ResetClock("gcc_usb3_phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_usb3_dp_phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_usb4_1_dp_phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_usb2_phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT);

    gBS->Stall (100);
  }
#endif
  #ifdef USB_MP_FLAG
  else if(UsbCore->CoreType == USB_CONFIG_SSUSB3) 
  {
    ResetClock("gcc_usb30_mp_master_clk", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall (100);
    ResetClock("gcc_usb30_mp_master_clk", EFI_CLOCK_RESET_DEASSERT);

    ResetClock("gcc_qusb2phy_hs0_mp_bcr", EFI_CLOCK_RESET_ASSERT); 
    ResetClock("gcc_qusb2phy_hs1_mp_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_qusb2phy_hs2_mp_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_qusb2phy_hs3_mp_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3_uniphy_mp0_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3_uniphy_mp1_bcr", EFI_CLOCK_RESET_ASSERT);    
    ResetClock("gcc_usb3uniphy_phy_mp0_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3uniphy_phy_mp1_bcr", EFI_CLOCK_RESET_ASSERT);    


    gBS->Stall (100);
    
    ResetClock("gcc_usb3uniphy_phy_mp1_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_usb3uniphy_phy_mp0_bcr", EFI_CLOCK_RESET_DEASSERT);    
    ResetClock("gcc_usb3_uniphy_mp1_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_usb3_uniphy_mp0_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_qusb2phy_hs3_mp_bcr", EFI_CLOCK_RESET_DEASSERT); 
    ResetClock("gcc_qusb2phy_hs2_mp_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_qusb2phy_hs1_mp_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_qusb2phy_hs0_mp_bcr", EFI_CLOCK_RESET_DEASSERT);
  }
  #endif
  else
  {
    DBG(EFI_D_WARN, "Invalid Core Type");
  }

  FNC_LEAVE_MSG ();
  return;
}

/**
  Initializes High Speed QUSB2 phy for primary core when connected to SNPS Core

  @retval EFI_SUCCESS            High Speed USB phy  initialized
                                 successfully.

**/
EFI_STATUS
InitHSUSBPhy (
  IN QCOM_USB_CORE              *UsbCore
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;

  FNC_ENTER_MSG ();

  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
    // RUMI HS Phy Initialization
    if (FALSE == usb_shared_hs_phy_rumi_init(0, CORE_DEFAULT_PHY)) {
      Status = EFI_INVALID_PARAMETER;
    }
    ERR_CHK("usb_shared_hs_phy_rumi_init failed");
  }
  else if ( (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_VIRTIO) 
      && (FALSE == usb_shared_is_eud_active()) ){
    //Hard reset PHY
    ResetClock("gcc_qusb2phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall(100);
    ResetClock("gcc_qusb2phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    gBS->Stall(100);

    DBG(EFI_D_INFO, "HS Phy Init");
    usb_shared_hs_phy_init();
  }

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
}


/**
  Initializes High Speed USB QUSB2 phy for sceondary core when connected to SNPS Core

  @retval EFI_SUCCESS            High Speed USB phy  initialized
                                 successfully.

**/
#ifdef USB_SEC_FLAG

EFI_STATUS
InitHSUSBPhySec (
  IN QCOM_USB_CORE              *UsbCore
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  FNC_ENTER_MSG ();

  // Sdm845 RUMI PHY init sequence for secondary port. 
  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
    // RUMI HS Phy Initialization
    if (FALSE == usb_shared_hs_phy_rumi_init(1, CORE_DEFAULT_PHY)) {
      Status = EFI_INVALID_PARAMETER;
    }
    ERR_CHK("usb_shared_hs_phy_rumi_init failed");
  }
  if (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_VIRTIO) {

    //Hard reset PHY
    ResetClock("gcc_usb2_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall(100);
    ResetClock("gcc_usb2_phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT);
    gBS->Stall(100);

    DBG(EFI_D_INFO, "HS Phy Init Sec");
    usb_shared_hs_phy_init_sec();
  }
ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
}
#endif
#ifdef USB_MP_FLAG

/**
  Initializes High Speed QUSB2 phy for Multi Port core when connected to SNPS Core

  @retval EFI_SUCCESS            High Speed USB phy  initialized
                                 successfully.

**/
EFI_STATUS
InitHSUSBPhyMP (
  IN QCOM_USB_CORE              *UsbCore
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;

  FNC_ENTER_MSG ();

  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
    // RUMI HS Phy Initialization
    Status = usb_shared_hs_phy_rumi_init(0, CORE_DEFAULT_PHY);
    ERR_CHK("usb_shared_hs_phy_rumi_init primary port failed");

    gBS->Stall(100);

    Status = usb_shared_hs_phy_rumi_init(1, CORE_DEFAULT_PHY);
    ERR_CHK("usb_shared_hs_phy_rumi_init failed");
  }
  else if ((PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_RUMI)   &&
           (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_VIRTIO) &&
           (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    //Hard reset PHY
    ResetClock("gcc_qusb2phy_hs0_mp_bcr", EFI_CLOCK_RESET_ASSERT); 
    ResetClock("gcc_qusb2phy_hs1_mp_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_qusb2phy_hs2_mp_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_qusb2phy_hs3_mp_bcr", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall(100);
    ResetClock("gcc_qusb2phy_hs3_mp_bcr", EFI_CLOCK_RESET_DEASSERT); 
    ResetClock("gcc_qusb2phy_hs2_mp_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_qusb2phy_hs1_mp_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_qusb2phy_hs0_mp_bcr", EFI_CLOCK_RESET_DEASSERT);
    gBS->Stall(100);

    DBG(EFI_D_INFO, "HS Phy Init");

    // Add MP Core Initialization Seq in shared library
    usb_shared_hs_phy_init_MP0();
    usb_shared_hs_phy_init_MP1();
    usb_shared_hs_phy_init_MP2();
    usb_shared_hs_phy_init_MP3();
  }

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
}
#endif

/**
  Initializes super speed Primary USB phy

  @retval EFI_SUCCESS            Super Speed USB phy  initialized
                                 successfully.

**/
STATIC
EFI_STATUS
InitSSUSBPhy (
  IN QCOM_USB_CORE              *UsbCore
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  FNC_ENTER_MSG ();

  // not needed for Sdm845 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   
    ||(PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO)
    //||(PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)
  ) {
    DBG(EFI_D_WARN, "plartform %d: Bypass InitSSUSBPhy",PlatformInfo.platform);
    Status = EFI_UNSUPPORTED;
    goto ON_EXIT;
  }

  if (UsbCore->BaseAddr != USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE) {
    Status = EFI_UNSUPPORTED;
    goto ON_EXIT;
  }

  //Disable QMP PIPE3 clock branch: turn on the QMP PIPE3 clock output to the controller while the PHY is in 
  //the reset state (prior to releasing PHY_START and PHY_SW_RESET) since this clock also comes back to the 
  //PHY and needs to be sourced from the PHY pipe clock output when the PHY starts up.
  //DisableClock("gcc_usb3_prim_phy_pipe_clk"); 

  // Reset the PHY block (no GCC reset if DP Bonded Mode is enabled) 
  if (gUSBPriDPBonded) { 
    ResetClock("gcc_usb3phy_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);   
    gBS->Stall (100);
    ResetClock("gcc_usb3phy_phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    gBS->Stall (100); 
  } else { 
  // Reset the PHY block - TBD - Get correct registers
    ResetClock("gcc_usb3_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3phy_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);   
    gBS->Stall (100);
    ResetClock("gcc_usb3phy_phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    ResetClock("gcc_usb3_phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);     
    gBS->Stall (100);
  }
  //Enable QMP PIPE3 clock branch
  //EnableClock("gcc_usb3_prim_phy_pipe_clk", 0, 1); 

  if(!usb_shared_ss_phy_init(UsbCore->LaneNum)) {
    DBG(EFI_D_ERROR, "Init SSUSBPhy Enable Error");
    Status = EFI_DEVICE_ERROR; 
    goto ON_EXIT;
  }

ON_EXIT:

  FNC_LEAVE_MSG ();
  return Status;
}


 /**
  Initializes Super Speed Secondary USB phy

  @retval EFI_SUCCESS            Super Speed USB phy  initialized
                                 successfully.

**/
#ifdef USB_SEC_FLAG

STATIC
EFI_STATUS
InitSSUSBPhySec (
  IN QCOM_USB_CORE              *UsbCore
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  FNC_ENTER_MSG ();

  // not needed for Sdm845 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass InitSSUSBPhySec");
    Status = EFI_UNSUPPORTED;
    goto ON_EXIT;
  }

  if (UsbCore->BaseAddr != USB4_SS_USB3_DRD_SP_1USB31_GEN2_SUBSYSTEM_BASE) {
    Status = EFI_UNSUPPORTED;
    goto ON_EXIT;
  }

  //Disable QMP PIPE3 clock branch: turn on the QMP PIPE3 clock output to the controller while the PHY is in 
  //the reset state (prior to releasing PHY_START and PHY_SW_RESET) since this clock also comes back to the 
  //PHY and needs to be sourced from the PHY pipe clock output when the PHY starts up. 
  //DisableClock("gcc_usb3_sec_phy_pipe_clk"); 

#ifdef USB_SEC_TYPEC
  // Reset the PHY block (no GCC reset if DP Bonded Mode is enabled) 
  if (gUSBSecDPBonded) { 
    ResetClock("gcc_usb3phy_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall (100); 
    ResetClock("gcc_usb3phy_phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT); 
    gBS->Stall (100); 
  } else 
#endif
  {
  // Reset the PHY block
    ResetClock("gcc_usb4_1_dp_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
  ResetClock("gcc_usb3_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT); 
  ResetClock("gcc_usb3phy_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);  
  gBS->Stall (100); 
  ResetClock("gcc_usb3phy_phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT); 
  ResetClock("gcc_usb3_phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT); 
    ResetClock("gcc_usb4_1_dp_phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
  gBS->Stall (100);
  }

  //Enable QMP PIPE3 clock branch 
  //EnableClock("gcc_usb3_sec_phy_pipe_clk", 0, 1); 

  if(!usb_shared_ss_phy_init_sec()) {
    DBG(EFI_D_ERROR, "Init SSUSBPhySec Enable Error");
    Status = EFI_DEVICE_ERROR; 
    goto ON_EXIT;
  }

ON_EXIT:

  FNC_LEAVE_MSG ();
  return Status;
}
#endif

/**
  Polls SS PHY USB Core for training

  @retval EFI_SUCCESS            Poll did not encounter any errors

**/
STATIC
EFI_STATUS
SSUsb1PollSSPhyTraining (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  usb_shared_poll_ss_phy_training();
  return EFI_SUCCESS;
}

/**
  Polls SS PHY USB Core for training

  @retval EFI_SUCCESS            Poll did not encounter any errors

**/
#ifdef USB_SEC_FLAG
STATIC
EFI_STATUS
SSUsb2PollSSPhyTraining (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  usb_shared_poll_ss_phy_training_sec();
  return EFI_SUCCESS;
}
#endif
/**
  Prints SS compliance pattern on a core

  @retval none.

**/
VOID UsbPrintSSCmplPattern(
  IN QCOM_USB_CORE_NUM_SOC CoreNum,
  IN UINT8 CpNum
  )
{
    switch(CpNum) {
    case  0: DBG (EFI_D_WARN, "CoreNum = %d, CP0 - 5G Pseudo random data pattern", CoreNum); break;
    case  1: DBG (EFI_D_WARN, "CoreNum = %d, CP1 - Nyquist frequency 5Gbps", CoreNum); break;
    case  2: DBG (EFI_D_WARN, "CoreNum = %d, CP2 - Nyquist/2 i.e. 2.5Gbps", CoreNum); break;
    case  3: DBG (EFI_D_WARN, "CoreNum = %d, CP3 - COM pattern", CoreNum); break;
    case  4: DBG (EFI_D_WARN, "CoreNum = %d, CP4 - Low frequency periodic signaling pattern", CoreNum); break;
    case  5: DBG (EFI_D_WARN, "CoreNum = %d, CP5 - K28.7 with de-emphasis", CoreNum); break;
    case  6: DBG (EFI_D_WARN, "CoreNum = %d, CP6 - K28.7 without de-emphasis", CoreNum); break;
    case  7: DBG (EFI_D_WARN, "CoreNum = %d, CP7 - 50-250 repeating 1s and 0s with de-emphasis ", CoreNum); break;
    case  8: DBG (EFI_D_WARN, "CoreNum = %d, CP8 - 50-250 repeating 1s and 0s without de-emphasis ", CoreNum); break;
    case  9: DBG (EFI_D_WARN, "CoreNum = %d, CP9 - 10G Pseudo random data pattern", CoreNum); break;
    case 10: DBG (EFI_D_WARN, "CoreNum = %d, CP10 - Nyquist frequency 10Gbps", CoreNum); break;
    case 11: DBG (EFI_D_WARN, "CoreNum = %d, CP11 - Nyquist/2 i.e. 5Gbps", CoreNum); break;
    case 12: DBG (EFI_D_WARN, "CoreNum = %d, CP9 - 10G Pseudo random data pattern", CoreNum); break;
    case 13: DBG (EFI_D_WARN, "CoreNum = %d, CP12 - Uncoded LFSR15 for phy level testing", CoreNum); break;
    case 14: DBG (EFI_D_WARN, "CoreNum = %d, CP12 - Uncoded LFSR15 for phy level testing", CoreNum); break;
    case 15: DBG (EFI_D_WARN, "CoreNum = %d, CP12 - Uncoded LFSR15 for phy level testing", CoreNum); break;
    case 16: DBG (EFI_D_WARN, "CoreNum = %d, CP12 - Uncoded LFSR15 for phy level testing", CoreNum); break;
  }
}

/**
  Advances SS compliance pattern

  @retval EFI_SUCCESS           If write to hardware register was successful.

**/
STATIC
EFI_STATUS
Usb1AdvanceSSCmplPattern (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  USB3_INC_CMPL_PATTERN(Usb1HstCmplPattNum);

  HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(0, HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK, 
    0x1 << HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);

  // Set this bit to 0, when you run compliance tests.
  HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(0, HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK, 
    0x0 << HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);

  
  UsbPrintSSCmplPattern(USB_CORE_0_SOC, Usb1HstCmplPattNum);

  return EFI_SUCCESS;
}

/**
  Advances SS compliance pattern

  @retval EFI_SUCCESS           If write to hardware register was successful.

**/
#ifdef USB_SEC_FLAG
STATIC
EFI_STATUS
Usb2AdvanceSSCmplPattern (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  USB3_INC_CMPL_PATTERN(Usb2HstCmplPattNum);

  HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(0, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK, 
    0x1 << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);

  // Set this bit to 0, when you run compliance tests.
  HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(0, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK, 
    0x0 << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);

  UsbPrintSSCmplPattern(USB_CORE_1_SOC, Usb2HstCmplPattNum);
  return EFI_SUCCESS;
}
#endif

#ifdef USB_MP_FLAG
/**
  Advances SS compliance pattern

  @retval EFI_SUCCESS           If write to hardware register was successful.

**/
STATIC
EFI_STATUS
Usb3AdvanceSSCmplPattern (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  USB3_INC_CMPL_PATTERN(Usb3HstCmplPattNum);

  // For multi-port core, toggle compliance bit on port #0 and port #1.
  HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(0,HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK,
    0x1 << HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);
  HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(1,HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK,
    0x1 << HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);
  HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(2,HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK,
    0x1 << HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);
  HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(3,HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK,
    0x1 << HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);

  // Set this bit to 0, when you run compliance tests.
  HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(0,HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK,
    0x1 << HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);
  HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(1,HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK,
    0x1 << HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);
  HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(2,HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK,
    0x1 << HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);
  HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OUTMI(3,HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_BMSK,
    0x1 << HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_HSTPRTCMPL_SHFT);


  UsbPrintSSCmplPattern(USB_CORE_2_SOC, Usb3HstCmplPattNum);
  
  return EFI_SUCCESS;
}


/**
  Initializes Super Speed MP Core USB phy

  @retval EFI_SUCCESS            Super Speed USB phy  initialized
                                 successfully.

**/
STATIC
EFI_STATUS
InitSSUSBPhyMP (
  IN QCOM_USB_CORE              *UsbCore
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  FNC_ENTER_MSG ();

  // not needed for Sdm845 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass InitSSUSBPhySec");
    goto ON_EXIT;
  }

  if (UsbCore->BaseAddr != USB3_HOST_MPUSB31_GEN2_MULTIPORT_TOP_BASE) {
    Status = EFI_UNSUPPORTED;
    goto ON_EXIT;
  }

  //Disable QMP PIPE3 clock branch: turn on the QMP PIPE3 clock output to the controller while the PHY is in 
  //the reset state (prior to releasing PHY_START and PHY_SW_RESET) since this clock also comes back to the 
  //PHY and needs to be sourced from the PHY pipe clock output when the PHY starts up.
  //HAL_USB_AND(GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_SEC_PHY_PIPE_CBCR_OFFS, ~(UINT32)HWIO_GCC_USB3_SEC_PHY_PIPE_CBCR_CLK_ENABLE_BMSK);

  // Reset the PHY block
  //HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_SEC_BCR_OFFS, HWIO_GCC_USB3_PHY_SEC_BCR_BLK_ARES_BMSK);
  //HAL_USB_OR (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3PHY_PHY_SEC_BCR_OFFS, HWIO_GCC_USB3PHY_PHY_SEC_BCR_BLK_ARES_BMSK);
  //gBS->Stall (100);
  //HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3PHY_PHY_SEC_BCR_OFFS, ~HWIO_GCC_USB3PHY_PHY_SEC_BCR_BLK_ARES_BMSK);
  //HAL_USB_AND (GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_PHY_SEC_BCR_OFFS, ~HWIO_GCC_USB3_PHY_SEC_BCR_BLK_ARES_BMSK);
  //gBS->Stall (100);

  // TBD - Validate these are correct for Poipu
  // Dont see Phy reset for QMP phy, just see PHY_PHY reset

  //Disable QMP PIPE3 clock branch: turn on the QMP PIPE3 clock output to the controller while the PHY is in 
  //the reset state (prior to releasing PHY_START and PHY_SW_RESET) since this clock also comes back to the 
  ResetClock("gcc_usb3_mp_phy_pipe_0_clk", EFI_CLOCK_RESET_ASSERT);
  ResetClock("gcc_usb3_mp_phy_pipe_1_clk", EFI_CLOCK_RESET_ASSERT);    
  gBS->Stall (100);

  ResetClock("gcc_usb30_mp_master_clk", EFI_CLOCK_RESET_ASSERT);
  gBS->Stall (100);
  ResetClock("gcc_usb30_mp_master_clk", EFI_CLOCK_RESET_DEASSERT);
 
  // SS Phy1 Reset
  ResetClock("gcc_usb3_uniphy_mp0_bcr", EFI_CLOCK_RESET_ASSERT);
  ResetClock("gcc_usb3uniphy_phy_mp0_bcr", EFI_CLOCK_RESET_ASSERT);
  // SSPhy 2 Reset
  ResetClock("gcc_usb3_uniphy_mp1_bcr", EFI_CLOCK_RESET_ASSERT); 
  ResetClock("gcc_usb3uniphy_phy_mp1_bcr", EFI_CLOCK_RESET_ASSERT); 
  gBS->Stall (100);
  // SSPhy 2 Out of Reset
  ResetClock("gcc_usb3_uniphy_mp1_bcr", EFI_CLOCK_RESET_DEASSERT);
  ResetClock("gcc_usb3uniphy_phy_mp1_bcr", EFI_CLOCK_RESET_DEASSERT);  
  // SSPhy 1 Out of Reset 
  ResetClock("gcc_usb3_uniphy_mp0_bcr", EFI_CLOCK_RESET_DEASSERT); 
  ResetClock("gcc_usb3uniphy_phy_mp0_bcr", EFI_CLOCK_RESET_DEASSERT); 
  
  gBS->Stall (100);

  //Enable QMP PIPE3 clock branch
  ResetClock("gcc_usb3_mp_phy_pipe_0_clk", EFI_CLOCK_RESET_DEASSERT);
  ResetClock("gcc_usb3_mp_phy_pipe_1_clk", EFI_CLOCK_RESET_DEASSERT);    

  //Enable QMP PIPE3 clock branch
  //HAL_USB_OR(GCC_CLK_CTL_REG_REG_BASE, HWIO_GCC_USB3_SEC_PHY_PIPE_CBCR_OFFS, HWIO_GCC_USB3_SEC_PHY_PIPE_CBCR_CLK_ENABLE_BMSK);

  // Add MP Core Initialization Seq in shared library
  if(!usb_shared_ss_phy_init_MP0()||!usb_shared_ss_phy_init_MP1()) {
    DBG(EFI_D_ERROR, "Init SSUSBPhyMP Enable Error");
    Status = EFI_DEVICE_ERROR; 
    goto ON_EXIT;
  }

ON_EXIT:

  FNC_LEAVE_MSG ();
  return Status;
}

#endif

/**
  This API is used for petting EUD after USB LDO 3p1 goes high, 
  so EUD hub does hot show up.

  @param None

**/
VOID
USbEudSwAttachDetSet(VOID)
{
  DBG(EFI_D_INFO, "EUD_SW_ATTACH_DET: 0 -> 1");
 
  if (HWIO_EUD_SW_ATTACH_DET_INM(HWIO_EUD_SW_ATTACH_DET_SW_ATTACH_DET_0_0_BMSK))
  {
    HWIO_EUD_SW_ATTACH_DET_OUTM(HWIO_EUD_SW_ATTACH_DET_SW_ATTACH_DET_0_0_BMSK,0);
    gBS->Stall(1000);
  }
  HWIO_EUD_SW_ATTACH_DET_OUTM(HWIO_EUD_SW_ATTACH_DET_SW_ATTACH_DET_0_0_BMSK,1);;
}


/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
 **/
STATIC
EFI_STATUS
SSUsb1InitCommon (
  IN  QCOM_USB_CORE_INTERFACE         *This,
  IN  BOOLEAN                          ResetUsbOnly
  )
{
  EFI_STATUS     Status   =  EFI_SUCCESS;
  BOOLEAN        bSsPhyFailed = FALSE;
  UINTN          BaseAddr;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG ();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  if (!ClockProtocol) goto ON_EXIT;

  UsbCore = USB_CORE_FROM_IFC(This);
  if (UsbCore->CoreType != USB_CONFIG_SSUSB1)
  {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("SSUsb1InitCommon: Wrong core, core %d", UsbCore->CoreType);
  }
  BaseAddr = UsbCore->BaseAddr;

  if (!ResetUsbOnly) {
    // Init Dal Lib
    DALSYS_InitMod(NULL);

    //Turn on power rails
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS1, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS1, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
  }

  //Enable USB power domain - TBD (Check) - Clock team to debug further
  ConfigPowerDomain(TRUE, SSUsb1PowerDomain);

  //Vote for Bus
  if (gNpaClientSS1Bus) {
    npa_issue_vector_request( gNpaClientSS1Bus,
                             (sizeof(usb_icb_request)/(sizeof(npa_resource_state))), 
                             ((npa_resource_state *)usb_icb_request) );
  }
  else {
    DBG (EFI_D_ERROR, "gNpaClientSS1Bus is NULL)");
  }

  if (0 == UsbCore->ClkRefCnt) 
  {
    // Enable clocks first, without that disable clocks does not work
    Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
    usb_shared_refclk_enable(TRUE);
    
    WRN_CHK ("failed to initialize USB clocks");
  }
  
  // Disable clocks for super speed controller
  Status = DisableUsbClocks (UsbCore->DisClockCount, UsbCore->DisClocks);
  WRN_CHK ("failed to disable USB clocks");

  if (FALSE == usb_shared_is_eud_active())
  {
    usb_shared_refclk_enable(FALSE);
  }

  // Enable clocks for super speed controller
  Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
  usb_shared_refclk_enable(TRUE);

  WRN_CHK ("failed to initialize USB clocks");

  USbEudSwAttachDetSet();

  //Increment reference count
  UsbCore->ClkRefCnt++;

  /*3. 
    To avoid ambiguity in the initial state, put the core in power collapse, then bring the core out of power collapse
    Applies to primary core only
  */
  ConfigPowerDomain(TRUE, SSUsb1PowerDomain);
  gBS->Stall (100);
  ConfigPowerDomain(FALSE, SSUsb1PowerDomain);
  gBS->Stall (100);

  // Hard Reset the USB Link and PHYs using GCC control
  SynopsysGccReset (UsbCore);

  //GCC_USB_SS_PHY_LDO_EN is enabled by default

  //Write 0x11 to the AHB2PHY bridge CSR PERIPH_SS_AHB2PHY_TOP_CFG 
  //to enable one-wait-state writes and reads prior to writing or reading the QMP USB3 PHY CSRs.
  // TBD - confirm this one
  // HAL_USB_WRITE (AHB2PHY_SOUTH_AHB2PHY_SOUTH_BASE, HWIO_AHB2PHY_SOUTH_AHB2PHY_SOUTH_AHB2PHY_TOP_CFG_OFFS, 0x11);

  Status = InitHSUSBPhy(UsbCore);
  WRN_CHK("InitHSUSBPhy failed: 0x%08x", Status);

  // Dont enable the SS USB Phy for the high speed only configuration
  if(!gHighSpeedOnlyPrimary)
  {
    Status = InitSSUSBPhy(UsbCore);
    if (Status != EFI_SUCCESS)
    {
      bSsPhyFailed = TRUE;
      DBG( EFI_D_WARN, "InitSSUSBPhy failed: 0x%08x. Falling back to HS PHY only", Status);
      Status = EFI_SUCCESS;
    }
  }

  /*
     11. HS only: if operating without the SS PHY, follow this sequence to disable the pipe clock requirement.
    a. usb30_reg_general_cfg[PIPE_UTMI_CLK_DIS] = 0x1
    b. Wait 1 us.
    c. usb30_reg_general_cfg[PIPE_UTMI_CLK_SEL] = 0x1
    d. usb30_reg_general_cfg [PIPE3_PHYSTATUS_SW] = 0x1
    e. Wait 1 us.
    f. usb30_reg_general_cfg[PIPE_UTMI_CLK_DIS] = 0x0
    In this case, program the software to skip all SuperSpeed configurations in 
    the link controller and PHY, otherwise the core could get stuck.
  */
  if ((bSsPhyFailed) || gHighSpeedOnlyPrimary)
  {
    DBG( EFI_D_WARN, "Disabling USB0 SS PHY, Write UTMI_CLK");
    HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GENERAL_CFG_OFFS, HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GENERAL_CFG_OFFS, HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_SEL_BMSK);
    HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GENERAL_CFG_OFFS, HWIO_USB3_PRI_GENERAL_CFG_PIPE3_PHYSTATUS_SW_BMSK);
    //When PIPE3_PHYSTATUS is high, Setting the PIPE3_SET_PHYSTATUS_SW bit will assert the PIPE_PHYSTATUS controller input 
    //So clear PHY status here
    HAL_USB_AND (BaseAddr, HWIO_USB3_PRI_GENERAL_CFG_OFFS, ~HWIO_USB3_PRI_GENERAL_CFG_PIPE3_SET_PHYSTATUS_SW_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_AND (BaseAddr, HWIO_USB3_PRI_GENERAL_CFG_OFFS, ~HWIO_USB3_PRI_GENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK);
  }
  else
  {
    /* Set DELAYP1TRANS to 0 */
    HAL_USB_AND (BaseAddr, HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), ~HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1TRANS_BMSK);

    /* Set GUSB3PIPECTL[UX_EXIT_IN_PX] to 1 */
    HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK);
  }

  /*
    15. To save power, enable the hardware-based clock gating (not relevant for PBL):
    a. usb30_reg_cgctl[DBM_FSM_EN] = 0x1
  */
  HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_CGCTL_REG_OFFS, HWIO_USB3_PRI_CGCTL_REG_DBM_FSM_EN_BMSK);

  // Disable clock gating: DWC_USB3_GCTL.DSBLCLKGTNG = 1
  HAL_USB_OR(BaseAddr, HWIO_USB3_PRI_GCTL_OFFS, HWIO_USB3_PRI_GCTL_DSBLCLKGTNG_BMSK);

  // Allow PHY to transition to P2 from suspend (P3) state.
  HAL_USB_OR(BaseAddr, HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), 
    HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_P3EXSIGP2_BMSK);

  HAL_USB_OR(BaseAddr, HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), 
    HWIO_USB3_PRI_GUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK);

  // Reduce U3 exit handshake timer to 300ns.
  HAL_USB_OUTM(BaseAddr, HWIO_USB3_PRI_LINK_REGS_p_LU3LFPSRXTIM_OFFS(0), 
    HWIO_USB3_PRI_LINK_REGS_p_LU3LFPSRXTIM_GEN1_U3_EXIT_RSP_RX_CLK_BMSK, 
    (0x5) << HWIO_USB3_PRI_LINK_REGS_p_LU3LFPSRXTIM_GEN1_U3_EXIT_RSP_RX_CLK_SHFT);

  HAL_USB_OUTM(BaseAddr, HWIO_USB3_PRI_LINK_REGS_p_LU3LFPSRXTIM_OFFS(0), 
    HWIO_USB3_PRI_LINK_REGS_p_LU3LFPSRXTIM_GEN2_U3_EXIT_RSP_RX_CLK_BMSK, 
    (0x6) << HWIO_USB3_PRI_LINK_REGS_p_LU3LFPSRXTIM_GEN2_U3_EXIT_RSP_RX_CLK_SHFT);

  /* HW automatic L1 exit feature in device mode to 1 */
  HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GUCTL1_OFFS, HWIO_USB3_PRI_GUCTL1_DEV_L1_EXIT_BY_HW_BMSK);

  /* Decouple L1 entry and exit wakeup event from L2 event */
  HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GUCTL1_OFFS, HWIO_USB3_PRI_GUCTL1_DEV_DECOUPLE_L1L2_EVT_BMSK);

  /* Add more inter-packet delay margin between the 2 packets */
  HAL_USB_OUTM(BaseAddr, HWIO_USB3_PRI_GUCTL1_OFFS, HWIO_USB3_PRI_GUCTL1_IP_GAP_ADD_ON_BMSK,
      0x3 << HWIO_USB3_PRI_GUCTL1_IP_GAP_ADD_ON_SHFT);

  /* Disable turning off PLL during L1 Sleep to prevent PLL not bring enabled during EP Command  */
  HAL_USB_AND (BaseAddr, HWIO_USB3_PRI_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OFFS(0), 
    ~HWIO_USB3_PRI_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK);
  DBG( EFI_D_INFO, "End of SSusb1initcommon coreType %d \n", UsbCore->CoreType);

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end SynopsysInitCommon

#ifdef USB_SEC_FLAG

/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
 **/
STATIC
EFI_STATUS
SSUsb2InitCommon (
  IN  QCOM_USB_CORE_INTERFACE         *This,
  IN  BOOLEAN                          ResetUsbOnly
  )
{
  EFI_STATUS     Status   =  EFI_SUCCESS;
  BOOLEAN        bSsPhyFailed = FALSE;
  UINTN          BaseAddr;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG ();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  if (!ClockProtocol) goto ON_EXIT;

  UsbCore = USB_CORE_FROM_IFC(This);
  if (UsbCore->CoreType != USB_CONFIG_SSUSB2)
  {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("SSUsb2InitCommon: Wrong core, core %d", UsbCore->CoreType);
  }
  
  BaseAddr = UsbCore->BaseAddr;

  if (!ResetUsbOnly) {
    // Init Dal Lib
    DALSYS_InitMod(NULL);

    //Turn on power rails                                             
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS1, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);   //Sends the request to RPM, no return
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS1, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);   //Sends the request to RPM, no return
    
    //Enable USB power domain
    ConfigPowerDomain(TRUE, SSUsb2PowerDomain);

    //Vote for Bus
    if (gNpaClientSS2Bus) {
      npa_issue_vector_request( gNpaClientSS2Bus,
                               (sizeof(usb_icb_request)/(sizeof(npa_resource_state))), 
                               ((npa_resource_state *)usb_icb_request) );
    }
    else {
      DBG (EFI_D_ERROR, "gNpaClientSS2Bus is NULL)");
    }

    if (0 == UsbCore->ClkRefCnt) {
      // Enable clocks first, without that disable clocks does not work
      Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
      usb_shared_refclk_enable(TRUE);
      WRN_CHK ("failed to initialize USB clocks");
    }

    // Disable clocks for super speed controller
    Status = DisableUsbClocks (UsbCore->DisClockCount, UsbCore->DisClocks);
    WRN_CHK ("failed to disable USB clocks");
    usb_shared_refclk_enable(FALSE);

    // Enable clocks for super speed controller
    Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
    ERR_CHK ("failed to initialize USB clocks");
    usb_shared_refclk_enable(TRUE);


    USbEudSwAttachDetSet();
    
    //Increment reference count
    UsbCore->ClkRefCnt++;
  }

  /*3. 
    To avoid ambiguity in the initial state, put the core in power collapse, then bring the core out of power collapse
    Applies to primary core only
  */
  ConfigPowerDomain(TRUE, SSUsb2PowerDomain);
  gBS->Stall (100);
  ConfigPowerDomain(FALSE, SSUsb2PowerDomain);
  gBS->Stall (100);

  // Hard Reset the USB Link and PHYs using GCC control
  SynopsysGccReset (UsbCore);

  //GCC_USB_SS_PHY_LDO_EN is enabled by default

  //Write 0x11 to the AHB2PHY bridge CSR PERIPH_SS_AHB2PHY_TOP_CFG 
  //to enable one-wait-state writes and reads prior to writing or reading the QMP USB3 PHY CSRs.
  // HAL_USB_WRITE (AHB2PHY_SOUTH_AHB2PHY_SOUTH_BASE, HWIO_AHB2PHY_SOUTH_AHB2PHY_SOUTH_AHB2PHY_TOP_CFG_OFFS, 0x11);

  Status = InitHSUSBPhySec(UsbCore);
  ERR_CHK("InitHSUSBPhySec failed: 0x%08x", Status);

  // Dont enable the SS USB Phy for the high speed only configuration
  if(!gHighSpeedOnlySecondary)
  {
    Status = InitSSUSBPhySec(UsbCore);
    if (Status != EFI_SUCCESS)
    {
      bSsPhyFailed = TRUE;
      DBG( EFI_D_WARN, "InitSSUSBPhySec failed: 0x%08x. Falling back to HS PHY only", Status);
      Status = EFI_SUCCESS;
    }
  }

  /*
   11. HS only: if operating without the SS PHY, follow this sequence to disable the pipe clock requirement.
    a. usb30_reg_general_cfg[PIPE_UTMI_CLK_DIS] = 0x1
    b. Wait 1 us.
    c. usb30_reg_general_cfg[PIPE_UTMI_CLK_SEL] = 0x1
    d. usb30_reg_general_cfg [PIPE3_PHYSTATUS_SW] = 0x1
    e. Wait 1 us.
    f. usb30_reg_general_cfg[PIPE_UTMI_CLK_DIS] = 0x0
    In this case, program the software to skip all SuperSpeed configurations in 
    the link controller and PHY, otherwise the core could get stuck.
  */
  if ((bSsPhyFailed) || gHighSpeedOnlySecondary)
  {
    DBG( EFI_D_WARN, "Disabling USB1 SS PHY, Write UTMI_CLK");

    HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_PIPE_UTMI_CLK_SEL_BMSK);
    HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_PIPE3_PHYSTATUS_SW_BMSK);
    //When PIPE3_PHYSTATUS is high, Setting the PIPE3_SET_PHYSTATUS_SW bit will assert the PIPE_PHYSTATUS controller input 
    //So clear PHY status here
    HAL_USB_AND (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_OFFS, ~HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_PIPE3_SET_PHYSTATUS_SW_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_AND (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_OFFS, ~HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGENERAL_CFG_PIPE_UTMI_CLK_DIS_BMSK);
  }
  else
  {
    /* Set DELAYP1TRANS to 0 */
    HAL_USB_AND (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), ~HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1TRANS_BMSK);

    /* Set GUSB3PIPECTL[UX_EXIT_IN_PX] to 1 */
    HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK);
  }
  
  /*
    15. To save power, enable the hardware-based clock gating (not relevant for PBL):
    a. usb30_reg_cgctl[DBM_FSM_EN] = 0x1
  */
  HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMCGCTL_REG_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMCGCTL_REG_DBM_FSM_EN_BMSK);
  
  // Disable clock gating: DWC_USB3_GCTL.DSBLCLKGTNG = 1
  HAL_USB_OR(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGCTL_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGCTL_DSBLCLKGTNG_BMSK);

  // Allow PHY to transition to P2 from suspend (P3) state.
  HAL_USB_OR(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), 
    HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_P3EXSIGP2_BMSK);

  HAL_USB_OR(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), 
    HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK);

  // Reduce U3 exit handshake timer to 300ns.
  HAL_USB_OUTM(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMLINK_REGS_p_LU3LFPSRXTIM_OFFS(0), 
    HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMLINK_REGS_p_LU3LFPSRXTIM_GEN1_U3_EXIT_RSP_RX_CLK_BMSK, 
    (0x5) << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMLINK_REGS_p_LU3LFPSRXTIM_GEN1_U3_EXIT_RSP_RX_CLK_SHFT);

  HAL_USB_OUTM(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMLINK_REGS_p_LU3LFPSRXTIM_OFFS(0), 
    HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMLINK_REGS_p_LU3LFPSRXTIM_GEN2_U3_EXIT_RSP_RX_CLK_BMSK, 
    (0x6) << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMLINK_REGS_p_LU3LFPSRXTIM_GEN2_U3_EXIT_RSP_RX_CLK_SHFT);

  /* HW automatic L1 exit feature in device mode to 1 */
  HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_DEV_L1_EXIT_BY_HW_BMSK);

  /* Decouple L1 entry and exit wakeup event from L2 event */
  HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_DEV_DECOUPLE_L1L2_EVT_BMSK);

  /* Add more inter-packet delay margin between the 2 packets */
  HAL_USB_OUTM(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_IP_GAP_ADD_ON_BMSK,
      0x3 << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_IP_GAP_ADD_ON_SHFT);

  /* Disable turning off PLL during L1 Sleep to prevent PLL not bring enabled during EP Command  */
  HAL_USB_AND (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OFFS(0), 
    ~HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK);
  
ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end SynopsysInitCommon
#endif	

#ifdef USB_MP_FLAG
/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
 **/
STATIC
EFI_STATUS
SSUsb3InitCommon (
  IN  QCOM_USB_CORE_INTERFACE         *This,
  IN  BOOLEAN                          ResetUsbOnly
  )
{
  EFI_STATUS     Status   =  EFI_SUCCESS;
  BOOLEAN        bSsPhyFailed = FALSE;
  UINTN          BaseAddr;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG ();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  if (!ClockProtocol) goto ON_EXIT;

  UsbCore = USB_CORE_FROM_IFC(This);
  
  BaseAddr = UsbCore->BaseAddr;

   //TBD - Update for MP Core
   
  if (!ResetUsbOnly) {
    // Init Dal Lib
    DALSYS_InitMod(NULL);

    //Turn on power rails
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS2, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS2, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS3, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS3, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS4, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS5, PMIC_NPA_MODE_ID_GENERIC_ACTIVE);
    

    //Enable USB power domain
    ConfigPowerDomain(TRUE, SSUsb3PowerDomain);

    //Vote for Bus
    if (gNpaClientSS3Bus) {
      npa_issue_vector_request( gNpaClientSS3Bus,
                              (sizeof(usb_icb_request)/(sizeof(npa_resource_state))), 
                              ((npa_resource_state *)usb_icb_request) );
    }
    else {
      DBG (EFI_D_ERROR, "gNpaClientSS3Bus is NULL)");
    }
  
    if ( 0 == UsbCore->ClkRefCnt)
    {
      // Enable clocks for super speed controller
      Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
      ERR_CHK ("failed to initialize USB clocks");
    }

    // Enable clocks for super speed controller
    Status = DisableUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
    ERR_CHK ("failed to disable USB clocks");
  
    // Enable clocks for super speed controller
    Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
    ERR_CHK ("failed to initialize USB clocks");
    
    //Increment reference count
    UsbCore->ClkRefCnt++;
  }

  /*3. 
    To avoid ambiguity in the initial state, put the core in power collapse, then bring the core out of power collapse
  */
  ConfigPowerDomain(TRUE, SSUsb3PowerDomain);
    gBS->Stall (100);
  ConfigPowerDomain(FALSE, SSUsb3PowerDomain);
    gBS->Stall (100);

  // Hard Reset the USB Link and PHYs using GCC control
  SynopsysGccReset (UsbCore);

  //GCC_USB_SS_PHY_LDO_EN is enabled by default

  //Write 0x11 to the AHB2PHY bridge CSR PERIPH_SS_AHB2PHY_TOP_CFG 
  //to enable one-wait-state writes and reads prior to writing or reading the QMP USB3 PHY CSRs.
  //HAL_USB_WRITE (AHB2PHY_SOUTH_AHB2PHY_SOUTH_BASE, HWIO_AHB2PHY_SOUTH_AHB2PHY_SOUTH_AHB2PHY_TOP_CFG_OFFS, 0x11);

  Status = InitHSUSBPhyMP(UsbCore);
  WRN_CHK("InitHSUSBPhy MP Core Primary/Sec phy failed: 0x%08x", Status);


  // Dont enable the SS USB Phy for the high speed only configuration
  if (!gHighSpeedOnlyMP)
  {
    // TBD - implement later
    Status = InitSSUSBPhyMP(UsbCore);
    if (Status != EFI_SUCCESS)
    {
      bSsPhyFailed = TRUE;
      DBG( EFI_D_WARN, "InitSSUSBPhyMP failed: 0x%08x. Falling back to HS PHY only", Status);
      Status = EFI_SUCCESS;
    }
  }

  /*
   11. HS only: if operating without the SS PHY, follow this sequence to disable the pipe clock requirement.
    a. usb30_reg_general_cfg[PIPE_UTMI_CLK_DIS] = 0x1
    b. Wait 1 s.
    c. usb30_reg_general_cfg[PIPE_UTMI_CLK_SEL] = 0x1
    d. usb30_reg_general_cfg [PIPE3_PHYSTATUS_SW] = 0x1
    e. Wait 1 s.
    f. usb30_reg_general_cfg[PIPE_UTMI_CLK_DIS] = 0x0
    In this case, program the software to skip all SuperSpeed configurations in 
    the link controller and PHY, otherwise the core could get stuck.
  */
  if ((bSsPhyFailed) || gHighSpeedOnlyMP)
  {
    DBG( EFI_D_WARN, "Disabling SS PHY 0");
    HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, HWIO_USB3_HOST_MPGENERAL_CFG_PIPE_UTMI_CLK_DIS_0_BMSK);

    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, HWIO_USB3_HOST_MPGENERAL_CFG_PIPE_UTMI_CLK_SEL_0_BMSK);
    HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, HWIO_USB3_HOST_MPGENERAL_CFG_PIPE3_PHYSTATUS_SW_0_BMSK);
    //When PIPE3_PHYSTATUS is high, Setting the PIPE3_SET_PHYSTATUS_SW bit will assert the PIPE_PHYSTATUS controller input 
    //So clear PHY status here
    HAL_USB_AND (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, ~HWIO_USB3_HOST_MPGENERAL_CFG_PIPE3_SET_PHYSTATUS_SW_0_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_AND (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, ~HWIO_USB3_HOST_MPGENERAL_CFG_PIPE_UTMI_CLK_DIS_0_BMSK);

    DBG( EFI_D_WARN, "Disabling SS PHY 1");
    HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, HWIO_USB3_HOST_MPGENERAL_CFG_PIPE_UTMI_CLK_DIS_1_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, HWIO_USB3_HOST_MPGENERAL_CFG_PIPE_UTMI_CLK_SEL_1_BMSK);
    HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, HWIO_USB3_HOST_MPGENERAL_CFG_PIPE3_PHYSTATUS_SW_1_BMSK);
    //When PIPE3_PHYSTATUS is high, Setting the PIPE3_SET_PHYSTATUS_SW bit will assert the PIPE_PHYSTATUS controller input 
    //So clear PHY status here
    HAL_USB_AND (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, ~HWIO_USB3_HOST_MPGENERAL_CFG_PIPE3_SET_PHYSTATUS_SW_1_BMSK);
    gBS->Stall (MICRO_STALL_UNITS(10));
    HAL_USB_AND (BaseAddr, HWIO_USB3_HOST_MPGENERAL_CFG_OFFS, ~HWIO_USB3_HOST_MPGENERAL_CFG_PIPE_UTMI_CLK_DIS_1_BMSK);
  }
  else
  {
    DBG( EFI_D_INFO, "enable MP SS PHY 0 and 1");

    /* Set DELAYP1TRANS to 0 */
    HAL_USB_AND (BaseAddr, HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), ~HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1TRANS_BMSK);
    HAL_USB_AND (BaseAddr, HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(1), ~HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_DELAYP1TRANS_BMSK);

    /* Set GUSB3PIPECTL[UX_EXIT_IN_PX] to 1 */
    HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK);
    HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(1), HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK);
  }

  /*
    15. To save power, enable the hardware-based clock gating (not relevant for PBL):
    a. usb30_reg_cgctl[DBM_FSM_EN] = 0x1
  */
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPCGCTL_REG_OFFS, HWIO_USB3_HOST_MPCGCTL_REG_DBM_FSM_EN_BMSK);

  // Disable clock gating: DWC_USB3_GCTL.DSBLCLKGTNG = 1
  HAL_USB_OR(BaseAddr, HWIO_USB3_HOST_MPGCTL_OFFS, HWIO_USB3_HOST_MPGCTL_DSBLCLKGTNG_BMSK);
  
  // Allow PHY to transition to P2 from suspend (P3) state.
  HAL_USB_OR(BaseAddr, HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_P3EXSIGP2_BMSK);
  HAL_USB_OR(BaseAddr, HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(0), HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK);
  HAL_USB_OR(BaseAddr, HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(1), HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_P3EXSIGP2_BMSK);
  HAL_USB_OR(BaseAddr, HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_OFFS(1), HWIO_USB3_HOST_MPGUSB3PIPECTL_REGS_p_GUSB3PIPECTL_UX_EXIT_IN_PX_BMSK);
  
  // Reduce U3 exit handshake timer to 300ns.
  HAL_USB_OUTM(BaseAddr, HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_OFFS(0),
    HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_GEN1_U3_EXIT_RSP_RX_CLK_BMSK,
    (0x5) << HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_GEN1_U3_EXIT_RSP_RX_CLK_SHFT);
  HAL_USB_OUTM(BaseAddr, HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_OFFS(1),
    HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_GEN1_U3_EXIT_RSP_RX_CLK_BMSK,
    (0x5) << HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_GEN1_U3_EXIT_RSP_RX_CLK_SHFT);

  HAL_USB_OUTM(BaseAddr, HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_OFFS(0),
    HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_GEN2_U3_EXIT_RSP_RX_CLK_BMSK,
    (0x6) << HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_GEN2_U3_EXIT_RSP_RX_CLK_SHFT);
  HAL_USB_OUTM(BaseAddr, HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_OFFS(1),
    HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_GEN2_U3_EXIT_RSP_RX_CLK_BMSK,
    (0x6) << HWIO_USB3_HOST_MPLINK_REGS_p_LU3LFPSRXTIM_GEN2_U3_EXIT_RSP_RX_CLK_SHFT);
  
  /* HW automatic L1 exit feature in device mode to 1 */
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGUCTL1_OFFS, HWIO_USB3_HOST_MPGUCTL1_DEV_L1_EXIT_BY_HW_BMSK);
  
  /* Decouple L1 entry and exit wakeup event from L2 event */
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGUCTL1_OFFS, HWIO_USB3_HOST_MPGUCTL1_DEV_DECOUPLE_L1L2_EVT_BMSK);

  /* Add more inter-packet delay margin between the 2 packets */
  HAL_USB_OUTM(BaseAddr, HWIO_USB3_HOST_MPGUCTL1_OFFS, HWIO_USB3_HOST_MPGUCTL1_IP_GAP_ADD_ON_BMSK,
      0x3 << HWIO_USB3_HOST_MPGUCTL1_IP_GAP_ADD_ON_SHFT);

  /* Disable turning off PLL during L1 Sleep to prevent PLL not bring enabled during EP Command  */
  HAL_USB_AND (BaseAddr, HWIO_USB3_HOST_MPGUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OFFS(0), 
    ~HWIO_USB3_HOST_MPGUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK);
  /* Disable turning off PLL during L1 Sleep to prevent PLL not bring enabled during EP Command  */
  HAL_USB_AND (BaseAddr, HWIO_USB3_HOST_MPGUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OFFS(1), 
    ~HWIO_USB3_HOST_MPGUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK);

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end SynopsysInitCommon

#endif

/**
  Performs Host mode specific initialization on a Synopsys super speed USB Primary core.

  @param [in]  UsbCore      The USB core instance

  @retval EFI_SUCCESS       USB core successfully initialized
  @retval EFI_UNSUPPORTED   USB core not supported
  @retval Others            Error encountered initializing USB core
**/
STATIC
EFI_STATUS
SynopsysInitHostConfig (
  IN  QCOM_USB_CORE         *UsbCore
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       BaseAddr;

  FNC_ENTER_MSG ();

  if (NULL == UsbCore) {
    DBG(EFI_D_ERROR, "invalid parameter");
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }
  
  BaseAddr = UsbCore->BaseAddr;
  
  //2. Set usb30_reg_gctl:[PRTCAPDIR] = 0x1 (host), [U2EXIT_LFPS] = 0x1
  HAL_USB_AND(BaseAddr,HWIO_USB3_PRI_GCTL_OFFS,~HWIO_USB3_PRI_GCTL_PRTCAPDIR_BMSK);
  HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GCTL_OFFS, HWIO_USB3_PRI_GCTL_U2EXIT_LFPS_BMSK | ( (1 << HWIO_USB3_PRI_GCTL_PRTCAPDIR_SHFT)) );

  //3. Enable the wake on connect event for the port:
  HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_PORTSC_20_REGS_p_PORTSC_20_OFFS(0), HWIO_USB3_PRI_PORTSC_20_REGS_p_PORTSC_20_WCE_BMSK );
  HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_PORTSC_30_REGS_p_PORTSC_30_OFFS(0), HWIO_USB3_PRI_PORTSC_30_REGS_p_PORTSC_30_WCE_BMSK );

  //4. Set GRXTHRCFG based on the case 8000615753 values
  HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GRXTHRCFG_OFFS,  (3 << HWIO_USB3_PRI_GRXTHRCFG_USBMAXRXBURSTSIZE_SHFT) |
  (3 << HWIO_USB3_PRI_GRXTHRCFG_USBRXPKTCNT_SHFT) | HWIO_USB3_PRI_GRXTHRCFG_USBRXPKTCNTSEL_BMSK);

  //5. Set the bus configuration 1K page pipe limit:
  //TODO:CK:HWIO_GSBUSCFG1_DESADRSPC_BMSK & HWIO_GSBUSCFG1_DATADRSPC_BMSK is not defined.
  //HAL_USB_AND(BaseAddr, HWIO_GSBUSCFG1_ADDR(0), ~HWIO_GSBUSCFG1_DESADRSPC_BMSK | ~HWIO_GSBUSCFG1_DATADRSPC_BMSK );
  HAL_USB_OR(BaseAddr, HWIO_USB3_PRI_GSBUSCFG1_OFFS, (0xE << HWIO_USB3_PRI_GSBUSCFG1_PIPETRANSLIMIT_SHFT) | HWIO_USB3_PRI_GSBUSCFG1_EN1KPAGE_BMSK );

  /* Disable USB2.0 internal retry feature */
  HAL_USB_OR (BaseAddr, HWIO_USB3_PRI_GUCTL3_OFFS, HWIO_USB3_PRI_GUCTL3_USB20_RETRY_DISABLE_BMSK);

  //set USB GUCTL1[21] = 3 (IP_GAP_ADD_ON)
  //to fix 1.	EL_22 Inter-Packet gap between host and device packet test
  //       2. EL_23 Inter-Packet gap between first two packets test
  HAL_USB_OR(BaseAddr, HWIO_USB3_PRI_GUCTL1_OFFS, (0x3 << HWIO_USB3_PRI_GUCTL1_IP_GAP_ADD_ON_SHFT)& HWIO_USB3_PRI_GUCTL1_IP_GAP_ADD_ON_BMSK);
  

  Usb1HstCmplPattNum = 0;
ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end SynopsysInitHost


/**
  Performs Host mode specific initialization on a Synopsys super speed USB Secondary core.

  @param [in]  UsbCore      The USB core instance

  @retval EFI_SUCCESS       USB core successfully initialized
  @retval EFI_UNSUPPORTED   USB core not supported
  @retval Others            Error encountered initializing USB core
**/
#ifdef USB_SEC_FLAG	
STATIC
EFI_STATUS
SynopsysInitHostConfigSec (
  IN  QCOM_USB_CORE         *UsbCore
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       BaseAddr;

  FNC_ENTER_MSG ();

  if (NULL == UsbCore) {
    DBG(EFI_D_ERROR, "invalid parameter");
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }
  
  BaseAddr = UsbCore->BaseAddr;
  
  //2. Set usb30_reg_gctl:[PRTCAPDIR] = 0x1 (host), [U2EXIT_LFPS] = 0x1
  HAL_USB_AND(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGCTL_OFFS, ~HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGCTL_PRTCAPDIR_BMSK);
  HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGCTL_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGCTL_U2EXIT_LFPS_BMSK | ( (1 << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGCTL_PRTCAPDIR_SHFT)) );

  //3. Enable the wake on connect event for the port:
  HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMPORTSC_20_REGS_p_PORTSC_20_OFFS(0), HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMPORTSC_20_REGS_p_PORTSC_20_WCE_BMSK );
  HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMPORTSC_30_REGS_p_PORTSC_30_OFFS(0), HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMPORTSC_30_REGS_p_PORTSC_30_WCE_BMSK );

  //4. Set GRXTHRCFG based on the case 8000615753 values
  HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGRXTHRCFG_OFFS,  (3 << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGRXTHRCFG_USBMAXRXBURSTSIZE_SHFT) |
  (3 << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGRXTHRCFG_USBRXPKTCNT_SHFT) | HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGRXTHRCFG_USBRXPKTCNTSEL_BMSK);

  //5. Set the bus configuration 1K page pipe limit:
  //TODO:CK:HWIO_GSBUSCFG1_DESADRSPC_BMSK & HWIO_GSBUSCFG1_DATADRSPC_BMSK is not defined.
  //HAL_USB_AND(BaseAddr, HWIO_GSBUSCFG1_ADDR(0), ~HWIO_GSBUSCFG1_DESADRSPC_BMSK | ~HWIO_GSBUSCFG1_DATADRSPC_BMSK );
  HAL_USB_OR(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGSBUSCFG1_OFFS, (0xE << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGSBUSCFG1_PIPETRANSLIMIT_SHFT) | HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGSBUSCFG1_EN1KPAGE_BMSK );

  /* Disable USB2.0 internal retry feature */
  HAL_USB_OR (BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL3_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL3_USB20_RETRY_DISABLE_BMSK);

  //set USB GUCTL1[21] = 3 (IP_GAP_ADD_ON)
  //to fix 1.	EL_22 Inter-Packet gap between host and device packet test
  //       2. EL_23 Inter-Packet gap between first two packets test
  HAL_USB_OR(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_OFFS, (0x3 << HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_IP_GAP_ADD_ON_SHFT)& HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUCTL1_IP_GAP_ADD_ON_BMSK);

  Usb2HstCmplPattNum = 0;

ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end SynopsysInitHostSec
#endif

#ifdef USB_MP_FLAG
/**
  Performs Host mode specific initialization on a Synopsys super speed USB MultiPort core.

  @param [in]  UsbCore      The USB core instance

  @retval EFI_SUCCESS       USB core successfully initialized
  @retval EFI_UNSUPPORTED   USB core not supported
  @retval Others            Error encountered initializing USB core
**/
STATIC
EFI_STATUS
SynopsysInitHostConfigMPCore (
  IN  QCOM_USB_CORE         *UsbCore
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       BaseAddr;

  FNC_ENTER_MSG ();

  if (NULL == UsbCore) {
    DBG(EFI_D_ERROR, "invalid parameter");
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }
  
  BaseAddr = UsbCore->BaseAddr;
  
  //TBD - Add Stuff for MP Core
  
  //2. Set usb30_reg_gctl:[PRTCAPDIR] = 0x1 (host), [U2EXIT_LFPS] = 0x1
  HAL_USB_AND(BaseAddr, HWIO_USB3_HOST_MPGCTL_OFFS, ~HWIO_USB3_HOST_MPGCTL_PRTCAPDIR_BMSK);
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGCTL_OFFS, HWIO_USB3_HOST_MPGCTL_U2EXIT_LFPS_BMSK | ( (1 << HWIO_USB3_HOST_MPGCTL_PRTCAPDIR_SHFT)) );

  //3. Enable the wake on connect event for the port:
  //Port 0
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPPORTSC_20_REGS_p_PORTSC_20_OFFS(0), HWIO_USB3_HOST_MPPORTSC_20_REGS_p_PORTSC_20_WCE_BMSK );
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPPORTSC_30_REGS_p_PORTSC_30_OFFS(0), HWIO_USB3_HOST_MPPORTSC_30_REGS_p_PORTSC_30_WCE_BMSK );

  //Port -1
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPPORTSC_20_REGS_p_PORTSC_20_OFFS(1), HWIO_USB3_HOST_MPPORTSC_20_REGS_p_PORTSC_20_WCE_BMSK );
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPPORTSC_30_REGS_p_PORTSC_30_OFFS(1), HWIO_USB3_HOST_MPPORTSC_30_REGS_p_PORTSC_30_WCE_BMSK );


  //4. Set GRXTHRCFG based on the case 8000615753 values
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGRXTHRCFG_OFFS,  (3 << HWIO_USB3_HOST_MPGRXTHRCFG_USBMAXRXBURSTSIZE_SHFT) |
  (3 << HWIO_USB3_HOST_MPGRXTHRCFG_USBRXPKTCNT_SHFT) | HWIO_USB3_HOST_MPGRXTHRCFG_USBRXPKTCNTSEL_BMSK);

  //5. Set the bus configuration 1K page pipe limit:
  //TODO:CK:HWIO_GSBUSCFG1_DESADRSPC_BMSK & HWIO_GSBUSCFG1_DATADRSPC_BMSK is not defined.
  //HAL_USB_AND(BaseAddr, HWIO_GSBUSCFG1_ADDR(0), ~HWIO_GSBUSCFG1_DESADRSPC_BMSK | ~HWIO_GSBUSCFG1_DATADRSPC_BMSK );
  HAL_USB_OR(BaseAddr, HWIO_USB3_HOST_MPGSBUSCFG1_OFFS, (0xE << HWIO_USB3_HOST_MPGSBUSCFG1_PIPETRANSLIMIT_SHFT) | HWIO_USB3_HOST_MPGSBUSCFG1_EN1KPAGE_BMSK );

  /* Disable USB2.0 internal retry feature */
  HAL_USB_OR (BaseAddr, HWIO_USB3_HOST_MPGUCTL3_OFFS, HWIO_USB3_HOST_MPGUCTL3_USB20_RETRY_DISABLE_BMSK);

  //set USB GUCTL1[21] = 3 (IP_GAP_ADD_ON)
  //to fix 1.	EL_22 Inter-Packet gap between host and device packet test
  //       2. EL_23 Inter-Packet gap between first two packets test
  HAL_USB_OR(BaseAddr, HWIO_USB3_HOST_MPGUCTL1_OFFS, (0x3 << HWIO_USB3_HOST_MPGUCTL1_IP_GAP_ADD_ON_SHFT)& HWIO_USB3_HOST_MPGUCTL1_IP_GAP_ADD_ON_BMSK);

  Usb3HstCmplPattNum = 0;
ON_EXIT:
  FNC_LEAVE_MSG ();
  return Status;
} // end SynopsysInitHostConfigMPCore

#endif

/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
**/
STATIC
EFI_STATUS
Usb30InitHost (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameters");
  }
 
  UsbCore = USB_CORE_FROM_IFC(This);
  
  /*if (UsbCore->CoreType == USB_CONFIG_SSUSB1) {
    Status = EnableVbusSS1();
    ERR_CHK("Failed to initialize VbusSS1");
  }*/

  if(UsbCore->CoreType == USB_CONFIG_SSUSB1)
      Status = SynopsysInitHostConfig(UsbCore);
#ifdef USB_SEC_FLAG	
  else if(UsbCore->CoreType == USB_CONFIG_SSUSB2)
      Status = SynopsysInitHostConfigSec(UsbCore);
#endif
#ifdef USB_MP_FLAG
  else if(UsbCore->CoreType == USB_CONFIG_SSUSB3)
    Status = SynopsysInitHostConfigMPCore(UsbCore);
#endif

  else
  	DBG(EFI_D_WARN, "Invalid Core Type");

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
**/
STATIC
EFI_STATUS
Usb30GetVbusSt (
  IN  QCOM_USB_CORE_INTERFACE         *This,
  OUT UINT32                          *VbusSt
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This || !VbusSt) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameters");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  // For Clamshell Platform Host Mode Enablement is automatically taken care by EC
  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_CLS) {
      Status = EFI_SUCCESS;
      goto ON_EXIT;
  }
  else {
     if (NULL == gPwrCtrlProtocol) {
       // Find the Power Control USB charger protocol
       Status = gBS->LocateProtocol(&gQcomUsbPwrCtrlProtocolGuid, NULL, (void**)&gPwrCtrlProtocol);
        if (EFI_ERROR(Status)) {
          gPwrCtrlProtocol = NULL;
          WRN_CHK("Failed to open Power control USB protocol Status =  (0x%x)", Status);
          goto ON_EXIT;
        }
      }

    if(UsbCore->CoreType == USB_CONFIG_SSUSB1)
    {
      Status = gPwrCtrlProtocol->GetVbusSrcOkStatus(USB_CORE_0_SOC, (BOOLEAN *)VbusSt);
    }
#ifdef USB_SEC_FLAG			
    else if(UsbCore->CoreType == USB_CONFIG_SSUSB2)
    {
      Status = gPwrCtrlProtocol->GetVbusSrcOkStatus(USB_CORE_1_SOC, (BOOLEAN *)VbusSt);
    }
#endif
#ifdef USB_MP_FLAG
    else if(UsbCore->CoreType == USB_CONFIG_SSUSB3)
    {
      Status = gPwrCtrlProtocol->GetVbusSrcOkStatus(USB_CORE_2_SOC, (BOOLEAN *)VbusSt);
    }
#endif
    else
    {
      Status = EFI_INVALID_PARAMETER;
      DBG(EFI_D_WARN, "Invalid Core Type");
    }
    
    WRN_CHK ("failed to get Vbus Status, Status = 0x%x", Status);
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
**/
STATIC
EFI_STATUS
Usb30EnableVbus (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameters");
  }

  UsbCore = USB_CORE_FROM_IFC(This);
  
  // Enable Vbus for the Primary Core (host mode)
  if(UsbCore->CoreType == USB_CONFIG_SSUSB1) {
    Status = EnableVbusSS(USB_CORE_0_SOC);
    ERR_CHK("Failed to initialize VbusSS for core 1");
  }
#ifdef USB_SEC_FLAG		
  else if(UsbCore->CoreType == USB_CONFIG_SSUSB2) { 
    Status = EnableVbusSS(USB_CORE_1_SOC);
    ERR_CHK("Failed to initialize VbusSS for core 2");
  }
#endif
#ifdef USB_MP_FLAG
  else if(UsbCore->CoreType == USB_CONFIG_SSUSB3) { 
    //Wont ever come here since PMIC always enables the Vbus for Multi-Port
    Status = EnableVbusSS(USB_CORE_2_SOC);
    ERR_CHK("Failed to initialize VbusSS for core 3");
   Status = EFI_SUCCESS;
  }
#endif
  else
  	DBG(EFI_D_WARN, "Invalid Core Type");


ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/**
  Performs device mode specific initialization on a Synopsys super speed USB Primary core.

  @param [in]  UsbCore      The USB core instance

  @retval EFI_SUCCESS       USB core successfully initialized
  @retval EFI_UNSUPPORTED   USB core not supported
  @retval Others            Error encountered initializing USB core
**/
STATIC
EFI_STATUS
SynopsysInitDevice (
  IN  QCOM_USB_CORE         *UsbCore
  )
{

  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       BaseAddr;

  FNC_ENTER_MSG ();

  if (NULL == UsbCore) {
    DBG(EFI_D_ERROR, "invalid parameter");
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  BaseAddr = UsbCore->BaseAddr;
  USB_ASSERT_GOTO ((BaseAddr != 0), ON_EXIT);

  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
    // Reset Device Core.
    HAL_USB_OR(BaseAddr, HWIO_USB3_PRI_DCTL_OFFS, HWIO_USB3_PRI_DCTL_CSFTRST_BMSK);
    while (HAL_USB_READ(BaseAddr, HWIO_USB3_PRI_DCTL_OFFS) & HWIO_USB3_PRI_DCTL_CSFTRST_BMSK) { ; }
    //InitHSUSBPhy(UsbCore);
    goto ON_EXIT;
  }

  /*
    16. Enable the hardware LPM:
    usb30_reg_gusb2phycfg_regs_p_gusb2phycfg[ENBLSLPM] = 0x1
  */
  HAL_USB_OR( BaseAddr, HWIO_USB3_PRI_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OFFS (0), HWIO_USB3_PRI_GUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK);

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/**
  Performs device mode specific initialization on a Synopsys super speed USB Secondary core.

  @param [in]  UsbCore      The USB core instance

  @retval EFI_SUCCESS       USB core successfully initialized
  @retval EFI_UNSUPPORTED   USB core not supported
  @retval Others            Error encountered initializing USB core
**/
#ifdef USB_SEC_FLAG	

STATIC
EFI_STATUS
SynopsysInitDeviceSec (
  IN  QCOM_USB_CORE         *UsbCore
  )
{

  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       BaseAddr;

  FNC_ENTER_MSG ();

  if (NULL == UsbCore) {
    DBG(EFI_D_ERROR, "invalid parameter");
    Status = EFI_INVALID_PARAMETER;
    goto ON_EXIT;
  }

  BaseAddr = UsbCore->BaseAddr;
  USB_ASSERT_GOTO ((BaseAddr != 0), ON_EXIT);

  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
    // Reset Device Core.
    HAL_USB_OR(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMDCTL_OFFS, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMDCTL_CSFTRST_BMSK);
    while (HAL_USB_READ(BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMDCTL_OFFS) & HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMDCTL_CSFTRST_BMSK) { ; }
    InitHSUSBPhySec(UsbCore);
    goto ON_EXIT;
  }

  /*
    16. Enable the hardware LPM:
    usb30_reg_gusb2phycfg_regs_p_gusb2phycfg[ENBLSLPM] = 0x1
  */
  HAL_USB_OR( BaseAddr, HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB2PHYCFG_REGS_p_GUSB2PHYCFG_OFFS (0), HWIO_USB4_SS_USB3_DRD_SP_1USB31_PRIMGUSB2PHYCFG_REGS_p_GUSB2PHYCFG_ENBLSLPM_BMSK);
  
ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}
#endif

/**
  Refer UsbConfigUsbCoresPrivate.h for the header description
**/
STATIC
EFI_STATUS
Usb30InitDevice (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  if(UsbCore->CoreType == USB_CONFIG_SSUSB1)
    Status = SynopsysInitDevice(UsbCore);
#ifdef USB_SEC_FLAG	
  else if(UsbCore->CoreType == USB_CONFIG_SSUSB2)
    Status = SynopsysInitDeviceSec(UsbCore);
#endif
  else
    DBG(EFI_D_WARN, "Invalid Core Type");

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/* Refer UsbConfigUsbCoresPrivate.h for the header description*/
STATIC
EFI_STATUS
SSUsb1EnterLpm (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  // not needed for Sdm845 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass SynopsysPrimEnterLpm");
    goto ON_EXIT;
  }

  if (!UsbCore->IsCoreInLPM)
  {
    // Reference Count 0 implies that we have not enabled clocks
    if (UsbCore->ClkRefCnt == 0)
    {
      // Enable clocks first, without that disable clocks doesn't work
      Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
      usb_shared_refclk_enable(TRUE);
      WRN_CHK ("failed to enable USB clocks");
      // Increment reference count
      UsbCore->ClkRefCnt++;
    }
    
    //Assert controller & PHYs resets - TBD - Get correct registers
    ResetClock("gcc_usb30_prim_master_clk", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_qusb2phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3phy_phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);

    Status = DisableUsbClocks (UsbCore->DisClockCount, UsbCore->DisClocks);
    WRN_CHK ("failed to disable USB clocks");

    // Disable USB Foot Switch (Power domain)
    ConfigPowerDomain(FALSE, SSUsb1PowerDomain);

    //  Enable SW PowerCollapse for USB30 Controller
    ConfigPowerDomain(TRUE, SSUsb1PowerDomain);

    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS1, PMIC_NPA_MODE_ID_GENERIC_STANDBY);

    if (FALSE == usb_shared_is_eud_active())
    {
      UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS1, PMIC_NPA_MODE_ID_GENERIC_STANDBY);
    }
    //Remove bus votes
    if (gNpaClientSS1Bus) {
        npa_issue_vector_request( gNpaClientSS1Bus,
                                 (sizeof(usb_icb_clrrequest)/(sizeof(npa_resource_state))), 
                                 ((npa_resource_state *)usb_icb_clrrequest) );
    }

    // Decrement reference count
    UsbCore->ClkRefCnt--;
    UsbCore->IsCoreInLPM = TRUE;

    // Unknown Reference Count, Faulty scenario
    if (UsbCore->ClkRefCnt > 1)
    {
      WRN_CHK ("SSUsb1EnterLpm: Wrong clock Reference count= 0x%x", UsbCore->ClkRefCnt);
    }
  }
  else
  {
    WRN_CHK ("SSUsb1EnterLpm: Synopsys Core already in LPM");
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

#ifdef USB_SEC_FLAG	

/* Refer UsbConfigUsbCoresPrivate.h for the header description*/
STATIC
EFI_STATUS
SSUsb2EnterLpm (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  // not needed for Sdm845 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass SynopsysPrimEnterLpm");
    goto ON_EXIT;
  }

  if (!UsbCore->IsCoreInLPM)
  {
    // Reference Count 0 implies that we have not enabled clocks
    if (UsbCore->ClkRefCnt == 0)
    {
      // Enable clocks first, without that disable clocks doesn't work
      Status = InitUsbClocks (UsbCore->EnClockCount, UsbCore->EnClocks);
      usb_shared_refclk_enable(TRUE);
      WRN_CHK ("failed to enable USB clocks");
      // Increment reference count
      UsbCore->ClkRefCnt++;
    }
    
    //Assert controller & PHYs resets
    ResetClock("gcc_usb30_sec_master_clk", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_qusb2phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);
    ResetClock("gcc_usb3phy_phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);

    Status = DisableUsbClocks (UsbCore->DisClockCount, UsbCore->DisClocks);
    WRN_CHK ("failed to disable USB clocks");

    // Disable USB Foot Switch (Power domain)
    ConfigPowerDomain(FALSE, SSUsb2PowerDomain);

    //  Enable SW PowerCollapse for USB30 Controller
    ConfigPowerDomain(TRUE, SSUsb2PowerDomain);

    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientSS1, PMIC_NPA_MODE_ID_GENERIC_STANDBY);
    UsbConfigLib_pmic_npa_issue_required_request(gPmicNpaClientHS1, PMIC_NPA_MODE_ID_GENERIC_STANDBY);

    //Remove bus votes
    if (gNpaClientSS2Bus) {
        npa_issue_vector_request( gNpaClientSS2Bus,
                                 (sizeof(usb_icb_clrrequest)/(sizeof(npa_resource_state))), 
                                 ((npa_resource_state *)usb_icb_clrrequest) );
    }

    // Decrement reference count
    UsbCore->ClkRefCnt--;
    UsbCore->IsCoreInLPM = TRUE;

    // Unknown Reference Count, Faulty scenario
    if (UsbCore->ClkRefCnt > 1)
    {
      WRN_CHK ("SSUsb2EnterLpm: Wrong clock Reference count= 0x%x", UsbCore->ClkRefCnt);
    }
  }
  else
  {
    WRN_CHK ("SSUsb2EnterLpm: Synopsys Core already in LPM");
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}
#endif

/* Refer UsbConfigUsbCoresPrivate.h for the header description*/
STATIC
EFI_STATUS
Usb30ExitLpm (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  // not needed for Sdm845 PRE-SI platform
  if ((PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI)   ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_VIRTIO) ||
      (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    DBG(EFI_D_WARN, "Pre-SI: Bypass SynopsysExitLpm");
    goto ON_EXIT;
  }

  // Perform GCC reset for controller and PHYs
  SynopsysGccReset (UsbCore);

ON_EXIT:
  FNC_LEAVE_MSG();
  return EFI_SUCCESS;
}


/* Refer UsbConfigUsbCoresPrivate.h for the header description*/
EFI_STATUS
Usb30Reset (
  IN  QCOM_USB_CORE_INTERFACE         *This
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
Usb30SetPhyLane(
  IN QCOM_USB_CORE_INTERFACE           *This,
  IN UINT8                              LaneNum
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  UsbCore->LaneNum = LaneNum;

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
Usb30GetBaseAddr(
  IN   QCOM_USB_CORE_INTERFACE           *This,
  OUT  UINTN                             *BaseAddr
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This || !BaseAddr) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  *BaseAddr = UsbCore->BaseAddr;

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
Usb30ResetSSPhy(
  IN   QCOM_USB_CORE_INTERFACE           *This
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);

  if(UsbCore->CoreType == USB_CONFIG_SSUSB1)
  InitSSUSBPhy(UsbCore);
  #ifdef USB_SEC_FLAG	
  else if(UsbCore->CoreType == USB_CONFIG_SSUSB2)
    InitSSUSBPhySec(UsbCore);
  #endif
  else
    DBG(EFI_D_WARN, "Invalid Core Type");

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

/* Refer UsbConfigUsbCoresPrivate.h for the header description */ 
STATIC
EFI_STATUS
SSUsb1SetPhyNonDrivingMode(
  IN   QCOM_USB_CORE_INTERFACE           *This,
  IN   BOOLEAN                            NonDrivingMode
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);
  
  // power off the PHY for high-z
  if (NonDrivingMode)
  {
    // TBD - Get the correct register for SNPS femto Phy
    #if 0
    HAL_USB_WRITE(PERIPH_SS_AHB2PHY_NORTH_BASE, HWIO_PERIPH_SS_QUSB2PHY_QUSB2PHY_PWR_CTRL1_OFFS, 0x23);
    #endif
  }
  else
  {
    // in order to put the phy back to the NORMAL mode, we have to re-init the HS phy.
    InitHSUSBPhy(UsbCore);
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}

#ifdef USB_SEC_FLAG	
/* Refer UsbConfigUsbCoresPrivate.h for the header description */ 
STATIC
EFI_STATUS
SSUsb2SetPhyNonDrivingMode(
  IN   QCOM_USB_CORE_INTERFACE           *This,
  IN   BOOLEAN                            NonDrivingMode
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;
  UINTN BaseAddr;

  FNC_ENTER_MSG();

  if (!This) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("invalid parameter");
  }

  UsbCore = USB_CORE_FROM_IFC(This);
  
  BaseAddr = UsbCore->BaseAddr;

  // power off the PHY for high-z
  if (NonDrivingMode)
  {
    // TBD - Get the correct register for SNPS femto Phy
    #if 0
    HAL_USB_WRITE(PERIPH_SS_AHB2PHY_NORTH_BASE, HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PWR_CTRL1_OFFS, 0x23);
    #endif
  }
  else
  {
    // in order to put the phy back to the NORMAL mode, we have to re-init the HS phy.
    InitHSUSBPhySec(UsbCore);
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}
#endif

/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
SSUsb1InitHSUSBPhyKeepPwrDwn (
  IN QCOM_USB_CORE_INTERFACE           *This
  )
{
  FNC_ENTER_MSG ();

  // Sdm845 RUMI PHY init sequence.
  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
      DBG(EFI_D_INFO, "Return without any configuration for RUMI");
      goto ON_EXIT;
  }

// TBD - check the sequence later for snps femto phy
#if 0
  if ((PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_RUMI)   &&
      (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_VIRTIO) &&
      (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    //Hard reset PHY
    ResetClock("gcc_qusb2phy_prim_bcr", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall(100);
    ResetClock("gcc_qusb2phy_prim_bcr", EFI_CLOCK_RESET_DEASSERT);
    gBS->Stall(100);

    DBG(EFI_D_INFO, "HS Phy Init");

    // Keep Port Power Down
    HAL_USB_WRITE(PERIPH_SS_AHB2PHY_NORTH_BASE, HWIO_PERIPH_SS_QUSB2PHY_QUSB2PHY_PWR_CTRL1_OFFS, 0x23);
    gBS->Stall(100);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_QUSB2PHY_PLL_ANALOG_CONTROLS_TWO_OFFS,
      0x03);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_QUSB2PHY_PLL_CLOCK_INVERTERS_OFFS,
      0x7C);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_QUSB2PHY_PLL_CMODE_OFFS,
      0x80);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_QUSB2PHY_PLL_PLL_LOCK_DELAY_OFFS,
      0x0A);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_QUSB2PHY_TUNE2_OFFS,
      0x09);
  }
#endif

  ON_EXIT:
  FNC_LEAVE_MSG ();
  return EFI_SUCCESS;
}

#ifdef USB_SEC_FLAG	
/* Refer UsbConfigUsbCoresPrivate.h for the header description */
STATIC
EFI_STATUS
SSUsb2InitHSUSBPhyKeepPwrDwn (
  IN QCOM_USB_CORE_INTERFACE           *This
  )
{
  FNC_ENTER_MSG ();

  // Sdm845 RUMI PHY init sequence.
  if (PlatformInfo.platform == EFI_PLATFORMINFO_TYPE_RUMI) {
      DBG(EFI_D_INFO, "Return without any configuration for RUMI");
      goto ON_EXIT;
  }

  // TBD - check the sequence later for snps femto phy
  #if 0
  if ((PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_RUMI)   &&
      (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_VIRTIO) &&
      (PlatformInfo.platform != EFI_PLATFORMINFO_TYPE_UNKNOWN)) {
    //Hard reset PHY
    ResetClock("gcc_qusb2phy_sec_bcr", EFI_CLOCK_RESET_ASSERT);
    gBS->Stall(100);
    ResetClock("gcc_qusb2phy_sec_bcr", EFI_CLOCK_RESET_DEASSERT);
    gBS->Stall(100);

    DBG(EFI_D_INFO, "HS Phy Init");

    // Keep Port Power Down
    HAL_USB_WRITE(PERIPH_SS_AHB2PHY_NORTH_BASE, HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PWR_CTRL1_OFFS, 0x23);
    gBS->Stall(100);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PLL_ANALOG_CONTROLS_TWO_OFFS,
      0x03);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PLL_CLOCK_INVERTERS_OFFS,
      0x7C);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PLL_CMODE_OFFS,
      0x80);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_PLL_PLL_LOCK_DELAY_OFFS,
      0x0A);

    HAL_USB_WRITE(
      PERIPH_SS_AHB2PHY_NORTH_BASE,
      HWIO_PERIPH_SS_QUSB2PHY_SEC_QUSB2PHY_TUNE2_OFFS,
      0x09);
  }
  #endif

  ON_EXIT:
  FNC_LEAVE_MSG ();
  return EFI_SUCCESS;
}
#endif

/* Refer to UsbConfigUsbCoresPublic.h for header description*/
EFI_STATUS
UsbConfigCoresInit(
  IN  UINTN                      CoreNum,
  OUT QCOM_USB_CORE_INTERFACE  **UsbCoreInterface
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;
  STATIC UINTN FlagToCallAPIOnlyOnce = 0; 

  FNC_ENTER_MSG();

  if (!UsbCoreInterface) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("Invalid Parameters: CoreNum %d, UsbCore %p", CoreNum, UsbCoreInterface);
  }

  UsbCore = AllocateZeroPool(sizeof(QCOM_USB_CORE));

  if (!UsbCore) {
    Status = EFI_OUT_OF_RESOURCES;
    ERR_CHK("Out of Resources");
  }

  if (CoreNum == USB_CORE_0_SOC) {
    UsbCore->CoreInterface.InitCommon = SSUsb1InitCommon;
    UsbCore->CoreInterface.InitDevice = Usb30InitDevice;
    UsbCore->CoreInterface.InitHost = Usb30InitHost;
    UsbCore->CoreInterface.GetVbusStatus = Usb30GetVbusSt;
    UsbCore->CoreInterface.EnableVbus = Usb30EnableVbus;
    UsbCore->CoreInterface.Reset = Usb30Reset;
    UsbCore->CoreInterface.CoreEnterLPM = SSUsb1EnterLpm;
    UsbCore->CoreInterface.CoreExitLPM = Usb30ExitLpm;
    UsbCore->CoreInterface.SetPhyLane = Usb30SetPhyLane;
    UsbCore->CoreInterface.GetBaseAddress = Usb30GetBaseAddr;
    UsbCore->CoreInterface.ResetSSPhy = Usb30ResetSSPhy;
    UsbCore->CoreInterface.SetNonDrivingMode = SSUsb1SetPhyNonDrivingMode;
    UsbCore->CoreInterface.InitHsPhyPwrDwn = SSUsb1InitHSUSBPhyKeepPwrDwn;
    UsbCore->CoreInterface.PollSSPhyTraining = SSUsb1PollSSPhyTraining;
    UsbCore->CoreInterface.AdvanceSSCmplPattern = Usb1AdvanceSSCmplPattern;

    if (FALSE == usb_shared_repeater_init(USB_CORE_0_SOC))
    {
      DBG(EFI_D_ERROR, "Repeater tuning failed");
    }

    *UsbCoreInterface = &UsbCore->CoreInterface;

    UsbCore->CoreType = USB_CONFIG_SSUSB1;
    UsbCore->BaseAddr = USB3_PRI_USB31_PRIM_MVS_WRAPPER_BASE;
    UsbCore->EnClockCount = sizeof(SSUsb1EnCoreClocks) / sizeof(QCOM_USB_CLOCK);
    UsbCore->EnClocks = SSUsb1EnCoreClocks;
    UsbCore->DisClockCount = sizeof(SSUsb1DisCoreClocks) / sizeof(QCOM_USB_CLOCK);
    UsbCore->DisClocks = SSUsb1DisCoreClocks;
    UsbCore->ClkRefCnt = 0;
    UsbCore->IsCoreInLPM = FALSE;
    UsbCore->LaneNum = 0;
  }
#ifdef USB_SEC_FLAG	
  else if(CoreNum == USB_CORE_1_SOC) {
    UsbCore->CoreInterface.InitCommon = SSUsb2InitCommon;
    UsbCore->CoreInterface.InitDevice = Usb30InitDevice;
    UsbCore->CoreInterface.InitHost = Usb30InitHost;
    UsbCore->CoreInterface.GetVbusStatus = Usb30GetVbusSt;
    UsbCore->CoreInterface.EnableVbus = Usb30EnableVbus;
    UsbCore->CoreInterface.Reset = Usb30Reset;
    UsbCore->CoreInterface.CoreEnterLPM = SSUsb2EnterLpm;
    UsbCore->CoreInterface.CoreExitLPM = Usb30ExitLpm;
    UsbCore->CoreInterface.SetPhyLane = Usb30SetPhyLane;
    UsbCore->CoreInterface.GetBaseAddress = Usb30GetBaseAddr;
    UsbCore->CoreInterface.ResetSSPhy = Usb30ResetSSPhy;
    UsbCore->CoreInterface.SetNonDrivingMode = SSUsb2SetPhyNonDrivingMode;
    UsbCore->CoreInterface.InitHsPhyPwrDwn = SSUsb2InitHSUSBPhyKeepPwrDwn;
    UsbCore->CoreInterface.PollSSPhyTraining = SSUsb2PollSSPhyTraining;
    UsbCore->CoreInterface.AdvanceSSCmplPattern = Usb2AdvanceSSCmplPattern;

    *UsbCoreInterface = &UsbCore->CoreInterface;

    UsbCore->CoreType = USB_CONFIG_SSUSB2;
    UsbCore->BaseAddr = USB3_2ND_USB31_PRIM_MVS_WRAPPER_BASE;
    UsbCore->EnClockCount = sizeof(SSUsb2EnCoreClocks) / sizeof(QCOM_USB_CLOCK);
    UsbCore->EnClocks = SSUsb2EnCoreClocks;
    UsbCore->DisClockCount = sizeof(SSUsb2DisCoreClocks) / sizeof(QCOM_USB_CLOCK);
    UsbCore->DisClocks = SSUsb2DisCoreClocks;
    UsbCore->ClkRefCnt = 0;
    UsbCore->IsCoreInLPM = FALSE;
    UsbCore->LaneNum = 0;
  }
#endif
#ifdef USB_MP_FLAG
  else if(CoreNum == USB_CORE_2_SOC) {
    UsbCore->CoreInterface.InitCommon = SSUsb3InitCommon;
    UsbCore->CoreInterface.InitDevice = NULL;
    UsbCore->CoreInterface.InitHost = Usb30InitHost;
    UsbCore->CoreInterface.GetVbusStatus = Usb30GetVbusSt;
    UsbCore->CoreInterface.EnableVbus = Usb30EnableVbus;
    UsbCore->CoreInterface.Reset = Usb30Reset;
    UsbCore->CoreInterface.CoreEnterLPM = SSUsb2EnterLpm;
    UsbCore->CoreInterface.CoreExitLPM = Usb30ExitLpm;
    UsbCore->CoreInterface.SetPhyLane = Usb30SetPhyLane;
    UsbCore->CoreInterface.GetBaseAddress = Usb30GetBaseAddr;
    UsbCore->CoreInterface.ResetSSPhy = Usb30ResetSSPhy;
    UsbCore->CoreInterface.SetNonDrivingMode = SSUsb2SetPhyNonDrivingMode;
    UsbCore->CoreInterface.InitHsPhyPwrDwn = SSUsb2InitHSUSBPhyKeepPwrDwn;
    UsbCore->CoreInterface.AdvanceSSCmplPattern = Usb3AdvanceSSCmplPattern;

    *UsbCoreInterface = &UsbCore->CoreInterface;

    UsbCore->CoreType = USB_CONFIG_SSUSB3;
    UsbCore->BaseAddr = USB3_HOST_MPUSB31_GEN2_MULTIPORT_TOP_BASE;
    UsbCore->EnClockCount = sizeof(SSUsb3EnCoreClocks) / sizeof(QCOM_USB_CLOCK);
    UsbCore->EnClocks = SSUsb3EnCoreClocks;
    UsbCore->DisClockCount = sizeof(SSUsb3DisCoreClocks) / sizeof(QCOM_USB_CLOCK);
    UsbCore->DisClocks = SSUsb3DisCoreClocks;
    UsbCore->ClkRefCnt = 0;
    UsbCore->IsCoreInLPM = FALSE;
    UsbCore->LaneNum = 0;
  }
#endif
  else {
    DBG(EFI_D_WARN, "Invalid Core Type");
  }

  //Open EFI Protocols only once
  if(FlagToCallAPIOnlyOnce == 0 && CoreNum < USB_CORE_MAX_NUM_SOC) {
    Status = UsbConfigLibOpenProtocols();
    ERR_CHK("UsbConfigLibOpenProtocols failed %r",Status);
	FlagToCallAPIOnlyOnce = 1;
  }

ON_EXIT:
  FNC_LEAVE_MSG();
  return Status;
}


/* Refer to UsbConfigUsbCoresPublic.h for header description*/
EFI_STATUS
UsbConfigCoresDeinit(
  IN QCOM_USB_CORE_INTERFACE  *UsbCoreInterface
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  QCOM_USB_CORE *UsbCore;

  FNC_ENTER_MSG();

  if (!UsbCoreInterface) {
    Status = EFI_INVALID_PARAMETER;
    ERR_CHK("Invalid Parameters: CoreNum %d, UsbCore %p", UsbCoreInterface);
  }

  UsbCore = USB_CORE_FROM_IFC(UsbCoreInterface);

  if (UsbCore)
    FreePool(UsbCore);

ON_EXIT:
  return Status;
}
