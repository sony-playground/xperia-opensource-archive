/*=======================================================================*//**
 * @file        UsbSharedLibCharger.c
 * @author:     niharika
 * @date        
 *
 * @brief       USB charger detection implementation.
 *
 * @details     This file contains API's and Data Connect Detect sequence 
 *				for Charger detection.
 *
 * @note        
 *              Copyright 2021,2022 QUALCOMM Technologies Incorporated.
 *              All Rights Reserved.
 *              Qualcomm Confidential and Proprietary
 * 
*//*========================================================================*/

// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 
// 02/07/22     ndhaker  BC1.2 charger detection support from USB phy
// 12/16/21     ndhaker  Initial revision
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "qusb_log.h"  
#include "DALSys.h" 
#include "UsbSharedLib.h" 
#include "ClockBoot.h"
#include "Clock.h"
#include <Library/DTBExtnLib.h>
#include <Library/DTBExtnUEFILib.h>
#include "HalusbHWIO.h"
#include "HalGccUsb.h"



//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------

#define USB_CHG_DET_RETRY_CNT (10)
#define USB_DCD_DETECT_VAL   (0x00)
#define USB_SDP_DETECT_VAL   (0x00)
#define USB_SEC_DETECT_VAL   (0x01)
#define USB_CDP_DETECT_VAL   (0x00)
#define USB_DCP_DETECT_VAL   (0x01)

// === MINIMUM LOGGING =======================================================
#define usb_shared_error_log(a,b,c)
#define usb_shared_uart_log_warn(a,b)

static boolean usb_phy_based_chrg = FALSE;

void usb_shared_charger_uart_log_dts_warn(USB_DTB_STATUS_TYPE error_code)
{
  usb_shared_error_log(DTB_ERROR_LOG, 0, error_code);
  usb_shared_uart_log_warn("usb_shared_xbl_dtb_node_init_phy: ", error_code);
  return;
}

// ===========================================================================
/**
 * @function    usb_shared_config_usb_clock
 * 
 * @brief   This function will be turn ON/off the USB clocks
 * 
 * @param   None
 * 
 * @return  TRUE or FALSE depending on success or failure.
 * 
 */
// ===========================================================================
boolean usb_shared_config_usb_clock(boolean enable)
{
  static ClockHandle clock_handle = 0;
  static ClockIdType clock_id = 0;
  static boolean is_attached = FALSE;
  
  ClockResult eResult = CLOCK_SUCCESS;
  //qusb_uart_log("usb_shared_config_usb_clock", enable);

  if (FALSE == is_attached)
  {
    eResult = Clock_Attach(&clock_handle, NULL);
    if (eResult != CLOCK_SUCCESS)   
    {      
      return FALSE;
    }
    eResult = Clock_GetId(clock_handle,
                          "usb30_prim",
                          &clock_id);
    if (eResult != CLOCK_SUCCESS)
    {
      return FALSE;
    }
    is_attached = TRUE;
  }    

  if (enable)
  {    
    eResult =  Clock_SetFrequency(clock_handle, clock_id, RAIL_VOLTAGE_LEVEL_NOM, CLOCK_FREQUENCY_FMAX, NULL);
    if (eResult != CLOCK_SUCCESS)
    {
       return FALSE;
    }

    eResult =  Clock_Enable(clock_handle, clock_id);
    if (eResult != CLOCK_SUCCESS)
    {
       return FALSE;
    }
  }
  else
  {
    eResult =  Clock_Disable(clock_handle, clock_id);
    if (eResult != CLOCK_SUCCESS)
    {
       return FALSE;
    }
  }
  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_shared_is_usbchg_enabled
 *
 * @brief   This function return True if usb phy charging is enabled
 *
 *
 * @param   None.
 *
 *
 * @return  boolean.
 *
 */
// ===========================================================================
boolean usb_shared_is_usbchg_enabled(void)
{
  return usb_phy_based_chrg;
}

//============================================================================
/**
* @function  usb_shared_xbl_dtb_node_init_phy
*
* @brief  Get USB phy charging value from device tree binary node
          and program whether to enable pmic charging or usb phy charging
*
* @Note : None
*
* @param : Get USB phy charging value from device tree binary node
 	 	   and program whether to enable pmic charging or usb phy charging
  
*
* @return : USB_DTB_STATUS_TYPE 0 succssful else error
*
*/
//============================================================================
USB_DTB_STATUS_TYPE usb_shared_xbl_dtb_node_init_phy(char *pdtb_node_name)
{
  void *fdtblob_h;
  int32 rt_val= -1;
  FdtNodeHandle fdtnode_h;
  uint32 *usb_phy_chg_dt_prop = NULL;
  uint32 usb_phy_chg_dt_size=0;
  static boolean CallDtbOnce = FALSE;
  
    if (CallDtbOnce == FALSE)
   {	
	  if(NULL == pdtb_node_name )
	  {
		usb_shared_charger_uart_log_dts_warn(USB_DTB_STATUS_WRONG_NAME);
		return USB_DTB_STATUS_WRONG_NAME;
	  }
	  
	  rt_val = fdt_get_blob_handle(&fdtblob_h, DEFAULT_BLOB_ID);
	  if(rt_val || NULL == fdtblob_h)
	  {
		usb_shared_charger_uart_log_dts_warn(USB_DTB_STATUS_FAILED_GET_BLOB);
		return USB_DTB_STATUS_FAILED_GET_BLOB;

	  }
	  
	  rt_val = fdt_get_node_handle(&fdtnode_h, fdtblob_h, pdtb_node_name);
	  if(rt_val)
	  {
		usb_shared_charger_uart_log_dts_warn(USB_DTB_STATUS_FAILED_GET_NODE);
		return USB_DTB_STATUS_FAILED_GET_NODE;

	  }

	  rt_val = fdt_get_prop_size(&fdtnode_h, "usb-phy-charging", &usb_phy_chg_dt_size);
	  if(rt_val)
	  {
		usb_shared_charger_uart_log_dts_warn(USB_DTB_STATUS_FAILED_GET_PROP_SIZE);
		return USB_DTB_STATUS_FAILED_GET_PROP_SIZE;
	  }
	  else 
	  {
		usb_shared_error_log(DCI_DAL_ERROR_LOG, 0, __LINE__);
		usb_shared_uart_log_warn("usb_shared_xbl_dtb_node_init: fdt_get_prop_size SUCCESS", usb_phy_chg_dt_size);
	  }

	  if(DAL_SUCCESS != DALSYS_Malloc(usb_phy_chg_dt_size, (void**)&usb_phy_chg_dt_prop) )
	  {
		usb_shared_charger_uart_log_dts_warn(USB_DTB_STATUS_FAILED_ALLOC);
		return USB_DTB_STATUS_FAILED_ALLOC;
	  }

	  rt_val = fdt_get_uint32_prop_list(&fdtnode_h, "usb-phy-charging", (uint32*)usb_phy_chg_dt_prop, usb_phy_chg_dt_size);
	  if(rt_val)
	  {
		usb_shared_charger_uart_log_dts_warn(USB_DTB_STATUS_FAILED_GET_PROP_LIST);
		return USB_DTB_STATUS_FAILED_GET_PROP_LIST;
	  }
	  
	  usb_phy_based_chrg = (*usb_phy_chg_dt_prop == 1) ? TRUE  : FALSE; 
	  CallDtbOnce = TRUE; 
	  usb_shared_uart_log_error("usb-phy: chgr value", usb_phy_based_chrg);
	  
	  if(DAL_SUCCESS != DALSYS_Free((void*)usb_phy_chg_dt_prop))
	  {
		usb_shared_charger_uart_log_dts_warn(USB_DTB_STATUS_FAILED_FREE);
		return USB_DTB_STATUS_FAILED_FREE;
	  }
    }   
  return USB_DTB_STATUS_SUCCESS;
}

// ===========================================================================
/**
 * @function    usb_shared_chgr_detect_nondrive_cfg
 * 
 * @brief   API used for UTMI SW Override and Setting D+/D- in Non-drive mode
 * 
 * @param   None
 * 
 * @return  None.
 * 
 */
// ===========================================================================
void usb_shared_chgr_detect_nondrive_cfg(void)
{
	usb_shared_uart_log_error("Set non-drive", 0);
	
	//1. USB_PHY_HS_PHY_CTRL2[1]  1’b1  enabling the utmi clock
	HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL2_OUT(0x6);
	 
	//2. USB_PHY_HS_PHY_CTRL_COMMON0[7] 1’b1 forces xo, bias and pll to stay on during suspend
	HWIO_USB2PHY_USB_PHY_HS_PHY_CTRL_COMMON0_OUT(0x88);
	
	//3. USB_PHY_UTMI_CTRL0[4:3]	2’b01	This sets the OPMODE into nondriving mode
	//   USB_PHY_UTMI_CTRL0[5]	    1’b1	This termination is required for FS Mode which is a requirement
	HWIO_USB2PHY_USB_PHY_UTMI_CTRL0_OUT(0x29);
	
	//4. USB_PHY_UTMI_CTRL1[1:0]	2’b01	This is the other requirement for FS
	HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_OUT(0x1);
	
	//5. USB_PHY_CFG0[1]	1’b1	UTMI_PHY_CMN_CTRL_OVERRIDE_EN=1
	//   USB_PHY_CFG0[0]	1’b1	UTMI_PHY_DATAPATH_CTRL_OVERRIDE_EN=1
	HWIO_USB2PHY_USB_PHY_CFG0_OUT(0x3);
}

// ===========================================================================
/**
 * @function    usb_shared_detect_charger_type
 * 
 * @brief    This API contains the register update sequence for dcd and charger
 *           type detection.
 * 
 * @param   Charger type
 * 
 * @return  return error flag
 * 
 */
// ===========================================================================
pm_err_flag_type usb_shared_detect_charger_type(pm_chg_charger_port_type *chg_type)
{
	uint32 dcd_detected, detect_status;
	uint32 chg_det_dcd_timeout = USB_CHG_DET_RETRY_CNT;
	pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
	static boolean ClockEnable = TRUE;
	
	// To enable USB clocks
	ClockEnable = usb_shared_config_usb_clock(TRUE);
	if(!ClockEnable)
	{
	  usb_shared_uart_log_error("clock enable fail", ClockEnable);
	}
	
	// Check status of RUN_STOP bit
	//The software writes 1 to RUN_STOP bit to start the device controller operation.
	boolean is_runstop = usb_shared_is_run_stop_active();
	if(is_runstop)
	{
	  usb_shared_uart_log_error("RUN_STOP bit set", is_runstop);
	  *chg_type = PM_CHARGER_PORT_SDP_CHARGER; 
	  return err_flag;
	}
	// Api for UTMI SW Overrride and Non-Drive mode
	usb_shared_chgr_detect_nondrive_cfg();
	
	// Start Data Contact Detect (DCD)  Sequence
	
	//1. USB_PHY_UTMI_CTRL1[3]	1’b1	required for DCD test
	HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_OUT(0x8);
	
	//2. USB_PHY_CHARGING_DET_CTRL[0]	1’b1	Enables DCD Current source
	HWIO_USB2PHY_USB_PHY_CHARGING_DET_CTRL_OUT(0x11);
	
	//3. delay 10 ms
	usb_shared_delay_ms(10);
	
	
	while(0 != (dcd_detected = HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_INM(HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_FSVPLUS0_BMSK) >> HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_FSVPLUS0_SHFT))
   {
		usb_shared_delay_ms(90);
		if (--chg_det_dcd_timeout > 0)
		{
			usb_shared_uart_log_error("DCD Tout:goto prim_det", 0);
			dcd_detected = USB_DCD_DETECT_VAL;
			break;
		}
    }
	
	if(dcd_detected == USB_DCD_DETECT_VAL)
	{
		usb_shared_uart_log_error("DCD_detected", dcd_detected);
		
		// diasble DCD 
			
		//1. USB_PHY_CHARGING_DET_CTRL[0]	1’b0	Deasserting DCDBEN0
		HWIO_USB2PHY_USB_PHY_CHARGING_DET_CTRL_OUT(0X10);
		//2. USB_PHY_UTMI_CTRL1[3]	1’b0	Deasserting DMPULLDOWN
		HWIO_USB2PHY_USB_PHY_UTMI_CTRL1_OUT(0x00);
		//3. delay 10 ms for DCD circuit to turn off
		usb_shared_delay_ms(10);
		
		
		// DO PRIMARY DETECTION
		
		/*1. USB_PHY_CHARGING_DET_CTRL[1]	1’b0	VDAT_SRC driven on D+
			 USB_PHY_CHARGING_DET_CTRL[2]	1’b1	enabling vdat_src
			 USB_PHY_CHARGING_DET_CTRL[3]	1’b1	enabling chrgdet comparator*/
		HWIO_USB2PHY_USB_PHY_CHARGING_DET_CTRL_OUT(0X1C);
		
		//2. Wait 40ms
		usb_shared_delay_ms(40);
		
		//3. USB_PHY_CHARGING_DET_OUTPUT[5]		Read CHGDET0 Battery charger detection output
		detect_status =  HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_INM(HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_CHGDET0_BMSK) >> HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_CHGDET0_SHFT; 
		
		if(detect_status == USB_SDP_DETECT_VAL)
		{
			*chg_type = PM_CHARGER_PORT_SDP_CHARGER;
			usb_shared_uart_log_error("usb: SDP",detect_status);
			
			//disable Primary Detection
			HWIO_USB2PHY_USB_PHY_CHARGING_DET_CTRL_OUT(0X10);	
		}
		else if(detect_status == USB_SEC_DETECT_VAL)
		{
			
			//Disable primary detection before moving to secondary charger detection
			HWIO_USB2PHY_USB_PHY_CHARGING_DET_CTRL_OUT(0X10);
			usb_shared_delay_ms(20);
			
			
			// DO SECONDARY DETECTION
			
			/*1. USB_PHY_CHARGING_DET_CTRL[1]	1’b1	VDAT_SRC driven on D-
				 USB_PHY_CHARGING_DET_CTRL[2]	1’b1	enabling vdat_src
				 USB_PHY_CHARGING_DET_CTRL[3]	1’b1	enabling chrgdet comparator*/
			HWIO_USB2PHY_USB_PHY_CHARGING_DET_CTRL_OUT(0X1E);
			
			//2. wait 40 ms
			usb_shared_delay_ms(40);
			
			//3. USB_PHY_CHARGING_DET_OUTPUT[5]		Read CHGDET0 Battery charger detection output
			detect_status =  HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_INM(HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_CHGDET0_BMSK) >> HWIO_USB2PHY_USB_PHY_CHARGING_DET_OUTPUT_CHGDET0_SHFT;
			
			if(detect_status == USB_CDP_DETECT_VAL)
			{
				*chg_type = PM_CHARGER_PORT_CDP_CHARGER;
				usb_shared_uart_log_error("usb: CDP",detect_status);
				usb_shared_dp_toggle(50); 
			}
			else if(detect_status == USB_DCP_DETECT_VAL)
			{
				*chg_type = PM_CHARGER_PORT_DCP_CHARGER;
				usb_shared_uart_log_error("usb: DCP",detect_status);
			}
			
			//Disable secondary detection
			HWIO_USB2PHY_USB_PHY_CHARGING_DET_CTRL_OUT(0X10);	
		}
		// resetting High Speed PHY using GCC control and initialise Phy again
        HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,(0x1 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));
		
        usb_shared_delay_us(100);
		
        HWIO_GCC_QUSB2PHY_PRIM_BCR_OUTM(HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_BMSK,(0x0 << HWIO_GCC_QUSB2PHY_PRIM_BCR_BLK_ARES_SHFT));
		
		usb_shared_hs_phy_init();
        		
	}
	
  return err_flag;	
}
