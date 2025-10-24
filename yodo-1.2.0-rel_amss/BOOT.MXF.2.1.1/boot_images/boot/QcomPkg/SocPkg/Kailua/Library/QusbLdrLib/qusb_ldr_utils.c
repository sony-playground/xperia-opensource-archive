/*=======================================================================*//**
 * @file        qusb_ldr_utils.c
 * @author:     kameya
 * @date        13-Feb-2015
 *
 * @brief       QUSB implementation to check forced emergency download mode 
 *              when D+ is grounded.
 *
 * @details     This file contains the implementation of the APIs to be used by
 *              the boot code to detect PBL forced EDL entry when D+ is grounded.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2015-2022 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2020 Intel Corporation. All rights reserved.<BR>
  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php
  
  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
 */
//============================================================================
// ===========================================================================
// 
//                            EDIT HISTORY FOR FILE
//   This section contains comments describing changes made to the module.
//   Notice that changes are listed in reverse chronological order.
// 
// 
// when          who     what, where, why
// ----------   -----    ----------------------------------------------------------
// 02/13/18	gk	     Port changes from boot.xf.2.0 and boot.xf.2.2
// 2013-06-19    shreyasr Added changes for MDM9x35
// 2012-04-14    tnk     Added flat file changes 
// 2010-04-14    yli     MSM8960 branch
// 2008-09-03   amirs    First Draft
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include "qusb_ldr_utils.h"
#include "busywait.h"  // busywait APIs
#include "ClockBoot.h"
#include TARGET_DEF_H             // For SHARED_IMEM_BASE
#include "com_dtypes.h"           // common defines - basic types as uint32 etc
#include "HALhwio.h"              // For OUTF and INF definitions
#include "pmic.h"
#include "pm_chg.h"
#include "qusb_common.h"
#include "qusb_dci_common.h"
#include "qusb_cookie.h"
#include "coldplug_api.h"
#include "CoreString.h"
#include "boot_logger.h"
#include "qusb_log.h"
#include "qusb_dci_api.h"
#include "Clock.h"
//----------------------------------------------------------------------------
// Preprocessor Definitions and Constants
//----------------------------------------------------------------------------

#define QUSB_DCI_PMI_INDEX                    (7)
#define QUSB_CHARGER_DETECT_RETRY_CNT             (150)

// Hotplug API status for success
#define QUSB_FS_HOTPLUG_SUCCESS                   (0)

// Definition for UFS array
// [0] - Length (including header), [1] - Type, [2] - unicode string
#define QUSB_UFS_SER_STR_LEN_INDEX                (0)
#define QUSB_UFS_SER_STR_TYPE_INDEX               (1)
#define QUSB_UFS_SER_STR_UNICODE_INDEX            (2)

// Toggle interval D+ after detecting CDP to not lose VBUS
#define QUSB_LDR_UTILS_CDP_DP_TOGGLE_MS           (200)
#define USB_EUSB_FLAG                             (1)

//----------------------------------------------------------------------------
// Type Declarations
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
// Static Variable Definitions
//----------------------------------------------------------------------------
// If Charger detection is not available in XBL Loader, then PMIC charger API
// will always return INVALID until timeout.
boolean qusb_charger_detection_available       = TRUE;

USB_EUD_PERMISSION_TYPE qusb_ldr_eud_permission = USB_EUD_PERMISSION_ALLOW;

#ifdef SBL_PRESILICON
boolean qusb_forced_download_feature_supported = FALSE;
#else
boolean qusb_forced_download_feature_supported = TRUE;
#endif

static const uint32  qusb_crc32_table[256] = {
  0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F,
  0xE963A535, 0x9E6495A3, 0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
  0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2,
  0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
  0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9,
  0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
  0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C,
  0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
  0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423,
  0xCFBA9599, 0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
  0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 0x76DC4190, 0x01DB7106,
  0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
  0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D,
  0x91646C97, 0xE6635C01, 0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
  0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950,
  0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
  0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7,
  0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
  0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA,
  0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
  0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81,
  0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
  0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84,
  0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
  0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB,
  0x196C3671, 0x6E6B06E7, 0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
  0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8, 0xA1D1937E,
  0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
  0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55,
  0x316E8EEF, 0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
  0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28,
  0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
  0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F,
  0x72076785, 0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
  0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242,
  0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
  0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69,
  0x616BFFD3, 0x166CCF45, 0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
  0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC,
  0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
  0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693,
  0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
  0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

//----------------------------------------------------------------------------
// Static Function Declarations and Definitions
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Externalized Function Definitions
//----------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------------
// Core Initialization APIs
// ------------------------------------------------------------------------------------------------

// ===========================================================================
/**
 * @function    qusb_ldr_utils_get_chgr_str
 * 
 * @brief   This function converts charger type to string.
 * 
 * @param  PMIC charger type
 * 
 * @return  Charger type string 
 * 
 */
// ===========================================================================
char* qusb_ldr_utils_get_chgr_str(pm_chg_charger_port_type usb_charger_type)
{
  switch (usb_charger_type)
  {
    case PM_CHARGER_PORT_SDP_CHARGER:         return " SDP_CHARGER";
    case PM_CHARGER_PORT_OCP_CHARGER:         return " OCP_CHARGER";
    case PM_CHARGER_PORT_CDP_CHARGER:         return " CDP_CHARGER";
    case PM_CHARGER_PORT_DCP_CHARGER:         return " DCP_CHARGER";
    case PM_CHARGER_PORT_FLOAT_CHARGER:       return " FLOAT_CHARGER";
    case PM_CHARGER_PORT_QC_2P0_CHARGER:      return " QC_2P0";
    case PM_CHARGER_PORT_QC_3P0_CHARGER:      return " QC_3P0";
    case PM_CHARGER_PORT_TYPE_INVALID:        return " INVALID";
    default:                                  return " UNKNOWN";
  }
}

// ===========================================================================
/**
 * @function    qusb_ldr_utils_get_chgr_type
 * 
 * @brief   This function check if vbus is present and will read charger type with timeout.
 * 
 * @param   None
 * 
 * @return  TRUE: if charger type is SDP.
 *              FALSE: if charger type is not SDP or PMIC charger detection fails or 500ms timeout occurs.
 * 
 */
// ===========================================================================
static pm_chg_charger_port_type qusb_ldr_utils_get_chgr_type(void)
{
  uint32 charger_det_retry_cnt = QUSB_CHARGER_DETECT_RETRY_CNT;
  pm_chg_charger_port_type usb_charger_type = PM_CHARGER_PORT_TYPE_INVALID;
  pm_err_flag_type pm_err;
  pm_chg_typec_status_type typec_status  = {0};
  pm_model_type pmic_model = pm_get_pmic_model(QUSB_DCI_PMI_INDEX);

  if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
  {
    qusb_uart_error_log(QUSB_LOG_LDR, LDR_PMI_NOT_DETECT_LOG);
    usb_charger_type = PM_CHARGER_PORT_SDP_CHARGER;
    return usb_charger_type;
  }

  // Check charger type with timeout 
  while (--charger_det_retry_cnt)
  {
    // Read vbus state using PMI typec status.
    pm_err = pm_chg_get_typec_status(&typec_status);
    
    if (PM_ERR_FLAG_SUCCESS != pm_err)
    {
      qusb_uart_error_log(QUSB_LOG_LDR, LDR_VBUS_DET_ERROR_LOG);
      qusb_error_log(LDR_VBUS_DET_ERROR_LOG, 0, pm_err);
      return usb_charger_type;
    }
    
    if (0 == typec_status.vbus_sts)
    {
      qusb_uart_error_log(QUSB_LOG_LDR, LDR_VBUS_LOW_LOG);
      qusb_error_log(LDR_VBUS_LOW_LOG, 0, !typec_status.vbus_sts);
      return usb_charger_type;
    }

    pm_err = pm_chg_get_charger_port_type(&usb_charger_type);
    if (PM_ERR_FLAG_SUCCESS != pm_err)
    {
      qusb_uart_error_log(QUSB_LOG_LDR, LDR_CHGR_PORT_DET_ERROR_LOG);
      qusb_error_log(LDR_CHGR_PORT_DET_ERROR_LOG, 0, pm_err);
      return usb_charger_type;
    }

    if (PM_CHARGER_PORT_TYPE_INVALID != usb_charger_type)
    {
      break;
    }
    qusb_dci_delay_ms(5);
  }

  qusb_uart_w_str_log("usb: chgr", qusb_ldr_utils_get_chgr_str(usb_charger_type));

  if (PM_CHARGER_PORT_TYPE_INVALID == usb_charger_type)
  {
    //qusb_uart_error_log(QUSB_LOG_LDR, LDR_CHGR_TIMEOUT_LOG);
    qusb_error_log(LDR_CHGR_TIMEOUT_LOG, 0, 0);
    return usb_charger_type;
  }

  return usb_charger_type;
}


// ===========================================================================
/* @function  qusb_calc_crc32
 *
 * @ brief    Calculates CRC32 (Cyclic redundancy check) over the number 
 *            of bytes specified.
 *
 * @param data   Buffer to use to calculate crc32
 * @param nbytes Calculate CRC32 over this number of bytes.
 * @param seed   CRC32 seed. Used to chain CRC32 calculations.
 *
 * @return CRC32 over the buffer
 */
// ===========================================================================
static uint32 qusb_calc_crc32 (const uint8 *data, uint32 nbytes, uint32 seed)
{
  uint32  crc = 0;
  uint32  pos;
  const uint8   *pbyte;

  if ((data != NULL) && (nbytes != 0))
  {
    crc = seed;
    for (pos = 0, pbyte = data; pos < nbytes; pos++, pbyte++)
    {
      crc = (crc >> 8) ^ qusb_crc32_table[(uint8) crc ^ *pbyte];
    }
  }
  return  (crc ^ seed);
}


// ===========================================================================
/**
 * @function    qusb_ldr_utils_update_serial
 * 
 * @brief   This function will update ram dump cookie to UFS/EMMC serial number 
 *          if ram dump cookie is not set.
 * 
 * @param   None
 * 
 * @return  None 
 * 
 */
// ===========================================================================
void qusb_ldr_utils_update_serial(void)
{
  int     char_written_length;
  uint32  serial_num            = 0;
  uint16  length                = 0;
  boolean is_ufs_available      = FALSE;

  // Read the serial string from UFS or EMMC
  struct coldplug_handle *chdl;
  struct coldplug_device_info dev_info;
  struct coldplug_guid sbl1_partition_id = 
        /*{DEA0BA2C-CBDD-4805-B4F9-F428251C3E98}*/
        { 0xDEA0BA2C, 0xCBDD, 0x4805, { 0xB4, 0xF9, 0xF4, 0x28, 0x25, 0x1C, 0x3E, 0x98 } };

  qusb_dload_info_type *dload_info_ptr = 
    (qusb_dload_info_type*)QUSB_DLOAD_INFO_ADDR_IN_IMEM;
  
  /* We verify that the data is valid according to the product_id validity */
  if (SERIAL_NUMBER_MAGIC_NUMBER == dload_info_ptr->pid_serial_num_cookie.magic_2)
  {
    // Since serial string is updated correctly already, we can skip the logic
    // Suppress UART logging for normal boot
    qusb_uart_w_str_log("usb: ser_str_cookie_pid", dload_info_ptr->serial_number);
    return;
  }

  //======================== 
  // Try UFS first 
  //========================

  chdl = coldplug_open_gpt_partition(COLDPLUG_DEVICE_UFS, 1 /* is_embedded */, &sbl1_partition_id);
  if (NULL != chdl)
  {
    if (QUSB_FS_HOTPLUG_SUCCESS != coldplug_get_device_info(chdl, &dev_info))
    {
      qusb_uart_log("ufs_info_fail", 0);
    }
    else if (2 >= dev_info.product_serial_number_string[QUSB_UFS_SER_STR_LEN_INDEX])
    {
      qusb_uart_log("ufs_ser_strlen <= 2", dev_info.product_serial_number_string[QUSB_UFS_SER_STR_LEN_INDEX]);
    }
    else
    {
      // Execute proprietary algorithm to convert UFS Product Serial (UNICODE) 
      // to uint32 hex using customer crc32
      length = (dev_info.product_serial_number_string[QUSB_UFS_SER_STR_LEN_INDEX] - 2);

      serial_num = qusb_calc_crc32(
        &dev_info.product_serial_number_string[QUSB_UFS_SER_STR_UNICODE_INDEX], 
        length, 
        0xFFFFFFFF);

      if (serial_num) 
      {
        is_ufs_available = TRUE;
      }
    }
  }

  if (serial_num == 0)
  {
    //========================
    // Try EMMC next 
    //========================

    chdl = coldplug_open_gpt_partition(COLDPLUG_DEVICE_SD, 1 /* is_embedded */, &sbl1_partition_id);
    if (NULL == chdl)
  
  {
      qusb_uart_log("emmc_parti_unavail", 0);

      //========================
      // Try SD Card next 
      //========================

      chdl = coldplug_open_gpt_partition(COLDPLUG_DEVICE_SD, 0 /* is_embedded */, &sbl1_partition_id);
    }

    if (NULL == chdl)
    {
      qusb_uart_log("sdc_parti_unavail", 0);
    }
    else if(QUSB_FS_HOTPLUG_SUCCESS != coldplug_get_device_info(chdl, &dev_info))
    {
      qusb_uart_log("emmc/sdc_info_fail", 0);
    }
    else
    {
      serial_num = dev_info.product_serial_number;
    }
  }

  if (serial_num == 0)
  {
    //========================
    // Use Chip serial number
    //========================

    serial_num = usb_shared_get_chip_serial_number();
  }
  
  char_written_length = core_snprintf(dload_info_ptr->serial_number, QUSB_SERIAL_NUMBER_LEN, "%x", serial_num);
  
  if ((char_written_length < 0) || (char_written_length >= QUSB_SERIAL_NUMBER_LEN))
  {
    qusb_uart_log("ser_str_conv_fail", 0);
    return;
  }

  if (is_ufs_available)
  {
    qusb_uart_w_str_log("usb: UFS Serial", dload_info_ptr->serial_number);
  }
  else
  {
    qusb_uart_w_str_log("usb: Serial", dload_info_ptr->serial_number);
  }
  
  // Updated the USB Serial cookie
  dload_info_ptr->pid_serial_num_cookie.magic_2 = SERIAL_NUMBER_MAGIC_NUMBER;
}

// ===========================================================================
/**
 * @function    qusb_ldr_config_usb_clock
 * 
 * @brief   This function will be turn ON/off the USB clocks
 * 
 * @param   None
 * 
 * @return  TRUE or FALSE depending on success or failure.
 * 
 */
// ===========================================================================
boolean qusb_ldr_config_usb_clock(boolean enable)
{
  static ClockHandle clock_handle = 0;
  static ClockIdType clock_id = 0;
  static boolean is_attached = FALSE;
  
  ClockResult eResult = CLOCK_SUCCESS;
  //qusb_uart_log("qusb_ldr_config_usb_clock", enable);

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
 * @function     qusb_ldr_utils_fedl_check
 * 
 * @brief   This function will check if usb_opt to enter FEDL is met. 
 *          And if condition met then we go into EDL.
 * 
 * @param check_usb_opt - [IN] Check usb type for Force EDL
 *
 * @param check_dp_timeout_ms - [IN] timeout for Checking DP high
 *
 * @return  TRUE: if it is connected to GND
 *          FALSE: if it is not connected to GND. 
 * 
 */
// ===========================================================================
boolean qusb_ldr_utils_fedl_check(uint32 check_usb_opt, uint32 check_dp_timeout_ms)
{
  boolean is_eud_active = FALSE;
  boolean check_dp_high = TRUE;
  pm_model_type pmic_model = PMIC_IS_UNKNOWN;


  if (FALSE == qusb_forced_download_feature_supported)
  {
    // if feature is disabled, then return FALSE
    return FALSE;
  }

  if (FALSE == qusb_charger_detection_available)
  {
    return FALSE;
  }

  if (PM_CHARGER_PORT_SDP_CHARGER != qusb_ldr_utils_get_chgr_type())
  {
    return FALSE;
  }

  switch (check_usb_opt)
  {
    case CHECK_USB_D_PLUS_GROUND:
      check_dp_high = FALSE;
      break;

    case CHECK_USB_D_PLUS_HIGH_WITH_TIMEOUT:
      check_dp_high = TRUE;
      break;

    case CHECK_USB_REGULAR_CABLE:
      pmic_model = pm_get_pmic_model(QUSB_DCI_PMI_INDEX);
      if((pmic_model == PMIC_IS_UNKNOWN) || (pmic_model == PMIC_IS_INVALID))
      {
        //If Pmic is invalid, skip FEDL
        return FALSE;
      }
      qusb_uart_log("enter forced EDL", check_usb_opt);
      return TRUE;
      break;

    default:
      return FALSE;
  }

  /** Bring the controller out of Power Collapse**/
  qusb_ldr_config_usb_clock(TRUE);

  // Skip EUD PHY tune if the EUD is already ACTIVE
  is_eud_active = usb_shared_is_eud_active();

  if (is_eud_active)
  {
    qusb_ldr_config_usb_clock(FALSE);

    return FALSE;    
  }

  qusb_dci_enable_usb2_ldo(TRUE);

  qusb_dci_usb30_gcc_reset(is_eud_active);

  qusb_ldr_config_usb_clock(TRUE);

  qusb_dci_ahb2phy_cfg();

  qusb_dci_delay_us(10);

  if (FALSE == qusb_hs_phy_init())
  {
    // USB PHY initialization failed. Skip Force EDL check
    return FALSE;
  }

  if (qusb_dci_dp_gnd_check(check_dp_high, check_dp_timeout_ms))
  {
    qusb_uart_log("enter forced EDL", check_usb_opt);
    usb_shared_delay_us(5000);
    return TRUE;
  }

  qusb_ldr_config_usb_clock(FALSE);
  return FALSE;
}

// ===========================================================================
/**
 * @function     qusb_ldr_utils_handle_charger
 * 
 * @brief   This function will check connection charger type and EUD status
 *          and proper enable EUD or toggle dp line for charger
 * 
 * @return  None
 * 
 */
// ===========================================================================
volatile uint32 qusb_handle_charger_cnt = 0;

void qusb_ldr_utils_handle_charger(void)
{
  boolean is_eud_active = FALSE;
  boolean is_runstop = FALSE;
  pm_chg_charger_port_type usb_charger_type = PM_CHARGER_PORT_TYPE_INVALID;

  // API can be called in 2 different path - SBL code or PMI Weak Battery charging path,
  // and we only need to execute on one that comes first to avoid boot-up delay due to redundant logic.
  if (qusb_handle_charger_cnt > 0)
  {
    //qusb_uart_log("qusb_handle_charger_cnt ", qusb_handle_charger_cnt);
    return;
  }
  qusb_handle_charger_cnt++;

  if (FALSE == qusb_charger_detection_available)
  {
    // Allow EUD by voting from SW - requires USB AHB2PHY clock 
    // which is always enabled for this target

    // Optimize boot time by not turning on USB clocks
    //Clock_Usb30EnableSWCollapse(FALSE);    
    //Clock_InitUSB();

    // Below API will vote for EUD to be enabled in TZ if APDP setting has allowed EUD.
    // The purpose of this API is for USB SW to detect charger and prevent EUD from getting
    // enabled for DCP or Quick Charger.
    qusb_ldr_eud_permission = USB_EUD_PERMISSION_ALLOW;
    qusb_dci_eud_init();

    //Clock_DisableUSB();
    //Clock_Usb30EnableSWCollapse(TRUE);
    return;
  }
  
  /** Bring the controller out of Power Collapse**/
  qusb_ldr_config_usb_clock(TRUE);

  is_runstop = usb_shared_is_run_stop_active();

  // Skip EUD PHY tune if the EUD is already ACTIVE
  is_eud_active = usb_shared_is_eud_active();

  if (is_eud_active)
  {
    if (FALSE == is_runstop)
    {
      qusb_ldr_config_usb_clock(FALSE);
    }
    return;    
  }

  usb_charger_type = qusb_ldr_utils_get_chgr_type();

  // Reach here if SDP, CDP, or INVALID (error on charger). Either way, 
  // allow EUD to be enabled.
  // Note: This is only a dummy flag read by secure side to decide
  // if EUD can be enabled based on Host PC connection 
  switch (usb_charger_type)
  {
    case PM_CHARGER_PORT_TYPE_INVALID:
    case PM_CHARGER_PORT_CDP_CHARGER: 
    case PM_CHARGER_PORT_SDP_CHARGER:
    {
      // Below API will vote for EUD to be enabled in TZ if APDP setting has allowed EUD.
      // The purpose of this API is for USB SW to detect charger and prevent EUD from getting
      // enabled for DCP or Quick Charger.
      qusb_ldr_eud_permission = USB_EUD_PERMISSION_ALLOW;
      qusb_dci_eud_init();
    }
    break;
    default: break; // no handling for other enums
  }

  //Skip DP toggle if device is in device programmer or flashless (runstop = 1);
  if ((PM_CHARGER_PORT_CDP_CHARGER == usb_charger_type) && (FALSE == is_runstop))
  {
       
  qusb_dci_enable_usb2_ldo(TRUE);
       
  qusb_dci_usb30_gcc_reset(is_eud_active);
    
  qusb_ldr_config_usb_clock(TRUE);
    
  qusb_dci_ahb2phy_cfg();
    
  qusb_dci_delay_us(10);
    
  if (FALSE == qusb_hs_phy_init())
  {
    // USB PHY initialization failed. Skip Force EDL check
      return;
  }

    // Toggle D+ for N interval to comply with CDP
    usb_shared_dp_toggle(QUSB_LDR_UTILS_CDP_DP_TOGGLE_MS);
    
    qusb_uart_log("usb_dp_toggled_for_cdp", QUSB_LDR_UTILS_CDP_DP_TOGGLE_MS);

    qusb_ldr_config_usb_clock(FALSE);
  }
}

// ===========================================================================
/**
 * @function    qusb_ldr_utils_hs_phy_nondrive_mode_set
 * 
 * @brief   This function puts the HS PHY into non-drive mode with
 *          pull-up and pull-down on data lines disabled.
 *
 * 
 * @param   None.
 * 
 *
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_ldr_utils_hs_phy_nondrive_mode_set(void)
{ 
#ifndef USB_EUSB_FLAG
  // Comment out the log print has each UART log costs 3ms.
  //qusb_uart_log("hs_phy_nondrive_start", 0);
  qusb_ldr_config_usb_clock(TRUE);
  boolean is_eud = usb_shared_is_eud_active();
  boolean is_runstop = usb_shared_is_run_stop_active();
  if (is_eud || is_runstop)
  {
    //qusb_uart_log("Skip_nondrive_mode ", is_eud<< 8 | is_runstop);
    return;
  }
  //qusb_ldr_disable_usb30_clocks();

  qusb_hs_phy_gcc_reset();

  qusb_ldr_config_usb_clock(TRUE);

  qusb_dci_delay_us(10);

  qusb_hs_phy_init();

  qusb_hs_phy_nondrive_cfg();

  // Do not turn off the clock as it can shut off shared NOC clocks.
  //Clock_DisableUSB();
  //Clock_Usb30EnableSWCollapse(TRUE);

  //qusb_uart_log("hs_phy_nondrive_finish", 0);
#endif
}

// ===========================================================================
/**
 * @function    qusb_ldr_eud_init
 * 
 * @brief   This function update serial number and Setup permission flag EUD
 *
 * 
 * @param   None.
 * 
 *
 * @return  None.
 * 
 */
// ===========================================================================
void qusb_ldr_eud_init(void)
{
  boolean is_eud_active = FALSE;
  boolean is_runstop = FALSE;
  qusb_device_connect_speed_t usb_speed_hw = QUSB_UNKNOWN_SPEED; 
  uint32 eud_serial = 0;

  //qusb_uart_log("qusb_ldr_eud_init", 0);
  eud_serial = usb_shared_get_chip_serial_number();
  usb_shared_eud_update_serial_number(eud_serial);

  is_eud_active = usb_shared_is_eud_active();  
  // Skip EUD PHY tune if the EUD is already ACTIVE

  if (is_eud_active)
  {
    return;
  }

  // Move the USB clock enable above EUD PHY TUNE to ensure it is compatible with SDX target
  // where AHB2PHY clock is NOT always ON, and USB clock enable would turn it on.
  qusb_ldr_config_usb_clock(TRUE);

  // Tune EUD register
  qusb_dci_eud_phy_tune();

  // Check if there is enumeration already done from PBL
  // If RUN_STOP bit is not set, then we can turn off clock and power 
  // collapse the controller
  // This is required for power saving as well as you cannot keep 
  // the USB clocks ON while GDSC is OFF.

  is_runstop = usb_shared_is_run_stop_active();
  if (is_runstop)
  {
    usb_speed_hw = qusb_dci_get_speed();

    qusb_uart_log("ldr_spd", usb_speed_hw); 
    // Only allow EUD for non-high and non-full speed 
    // during flashless boot or device programmer
    switch(usb_speed_hw)
    {
      case QUSB_HIGH_SPEED:
      {
        //qusb_uart_log("HS", eud_serial); 
        qusb_ldr_eud_permission = USB_EUD_PERMISSION_NOT_ALLOW;
      }
      break;

      case QUSB_FULL_SPEED:
      {
        //qusb_uart_log("FS", eud_serial);
        qusb_ldr_eud_permission = USB_EUD_PERMISSION_NOT_ALLOW;
      }
      break;

      case QUSB_SUPER_SPEED:
      {
        qusb_ldr_eud_permission = USB_EUD_PERMISSION_ALLOW_WITH_MIN_DELAY;
        //qusb_uart_log("SS", eud_serial);
      }
      break;

      case QUSB_SUPER_SPEED_PLUS:
      {
        qusb_ldr_eud_permission = USB_EUD_PERMISSION_ALLOW_WITH_MIN_DELAY;
        //qusb_uart_log("SSP", eud_serial);
      }
      break;

      case QUSB_FULL_SPEED_48:
      case QUSB_LOW_SPEED:
      default:        
      {
        qusb_ldr_eud_permission = USB_EUD_PERMISSION_ALLOW;
        //qusb_uart_log("Unknown Speed", usb_speed_hw);
      }
      break;
    }
  }
  else
  {
    // Vote for EUD enablement
    qusb_ldr_eud_permission = USB_EUD_PERMISSION_ALLOW;
    // If EUD is active, do not vote off QREF for USB2PHY
    //qusb_uart_log("gdsc_clk_off", eud_serial);
    qusb_ldr_config_usb_clock(FALSE);
  }
  return;
}

// ===========================================================================
/**
 * @function    qusb_ldr_get_eud_permission
 * 
 * @brief   This function return if EUD is allow to enumeration
 *
 * 
 * @param   None.
 * 
 *
 * @return  USB_EUD_PERMISSION_TYPE.
 * 
 */
// ===========================================================================
USB_EUD_PERMISSION_TYPE qusb_ldr_get_eud_permission(void)
{
  return qusb_ldr_eud_permission;
}

