/*=======================================================================*//**
 * @file        UsbRepeater.c
 * @author:     pohanw
 * @date        09-Sep-2021
 *
 * @brief       USB common & shared USB core implementation for repeater Library.
 *
 * @details     This file contains sequence to enable repeater.
 *
 * @note        
 *
 * 
*//*========================================================================*/
//============================================================================
/**
  Copyright (c) 2021-2022 Qualcomm Technologies, Inc. All rights reserved.
  Portions Copyright (c) 2007 - 2013 Intel Corporation. All rights reserved.<BR>
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
// 09/09/21      srmi    Initial revision
// 
// ===========================================================================

//----------------------------------------------------------------------------
// Include Files
//----------------------------------------------------------------------------
#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Library/UefiBootServicesTableLib.h>
#include "UsbSharedLib.h"
#include "UsbRepeater.h"
#include "SpmiTypes.h"
#include <Protocol/EFISPMI.h>

EFI_QCOM_SPMI_PROTOCOL *pSpmiProtocol = NULL;
const usb_repeater_cfg_type*  g_repeater_tuning_cfg_handle;
uint32 g_repeater_tuning_size;

static const usb_repeater_cfg_type PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_MTP [] = 
{ 
  {PMIO_EUSB2_TUNE_IUSB2_ADDR, 0x08},
  {PMIO_EUSB2_TUNE_SQUELCH_U_ADDR, 0x03},
  {PMIO_EUSB2_TUNE_USB2_PREEM_ADDR, 0x05},
};
static const usb_repeater_cfg_type PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_ATP [] = 
{ 
  {PMIO_EUSB2_TUNE_IUSB2_ADDR, 0x00},
  {PMIO_EUSB2_TUNE_SQUELCH_U_ADDR, 0x04},
  {PMIO_EUSB2_TUNE_USB2_PREEM_ADDR, 0x00},
};
static const usb_repeater_cfg_type PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_QRD [] = 
{ 
  {PMIO_EUSB2_TUNE_IUSB2_ADDR, 0x0D},
  {PMIO_EUSB2_TUNE_HSDISC_ADDR, 0x06},
  {PMIO_EUSB2_TUNE_SQUELCH_U_ADDR, 0x03},
  {PMIO_EUSB2_TUNE_USB2_PREEM_ADDR, 0x07},
};



// ===========================================================================
/**
 * @function    usb_shared_read_cfg_reg_array
 * 
 * @brief   This function reads from array and prints the current register 
 *          values
 * 
 * @param   cfg_array   - array holding address and value of HW register
 *          start_index     - starting index for array processing
 *          array_entry_cnt - number of entries in the array
 *          core_num  -  core number to which repeater is connected
 * 
 * @return  boolean  - if reads are successful
 * 
 */
// ===========================================================================
static boolean usb_repeater_spmi_read_cfg_reg_array
(
  const usb_repeater_cfg_type*  cfg_table,
  UINT32                    start_index, 
  UINT32                    array_entry_cnt,
  UINT32                    core_num
)
{
  UINT8 index = start_index;
  UINT8 data =0;
  Spmi_Result spmi_ret = SPMI_SUCCESS;
  UINT32 len = 1;
  UINT16 address;
  UINT32 bytesRead =0;

  if ( (NULL == cfg_table)
      || (0 == array_entry_cnt) || (NULL == pSpmiProtocol) )
  {
    DEBUG(( EFI_D_ERROR, "Process_Array: Null Parameter Passed++\r\n"));
    return FALSE;
  }

  for (index = 0; index < array_entry_cnt; index++)
  {
    address = cfg_table[index].reg;
    spmi_ret |= pSpmiProtocol->ReadLong(pSpmiProtocol, PMIC_EUSB_RPTR_SPMI_BUSID, PMIC_EUSB_RPTR_INDEX,
                                        SPMI_BUS_ACCESS_PRIORITY_LOW, address, &data, len, &bytesRead);

    // DEBUG(( EFI_D_ERROR, "READING: reg: 0x%x, data: %d, res = %d\r\n",address, data, spmi_ret));
  }

  if(SPMI_SUCCESS != spmi_ret)
  {
    DEBUG(( EFI_D_ERROR, "read spmi reg failed: %d\r\n", spmi_ret));
    return FALSE;
  }

  return TRUE;
}

// ===========================================================================
/**
 * @function    usb_shared_process_cfg_reg_array
 * 
 * @brief   This function reads from array which define list of hwio writes for
 *          USB PHY
 * 
 * @param   cfg_array   - array holding address and value of HW register
 *          start_index     - starting index for array processing
 *          array_entry_cnt - number of entries in the array
 *          core_num  -  core number to which repeater is connected
 * 
 * @return  boolean  - if writes are successful
 * 
 */
// ===========================================================================
static boolean usb_repeater_spmi_process_cfg_reg_array
(
  const usb_repeater_cfg_type*  cfg_table,
  UINT32                    start_index, 
  UINT32                    array_entry_cnt,
  UINT32                    core_num
)
{
  UINT32 index = start_index;
  UINT8 data = 0;
  UINT32 len = 1;
  UINT16 address;
  Spmi_Result spmi_ret = SPMI_SUCCESS;

  if ( (NULL == cfg_table)
      || (0 == array_entry_cnt) || (NULL == pSpmiProtocol) )
  {
    DEBUG(( EFI_D_ERROR, "Process_Array: Null Parameter Passed++\r\n"));
    return FALSE;
  }

  for (; index < array_entry_cnt; index++)
  {
    address = cfg_table[index].reg;
    data = cfg_table[index].data;
    spmi_ret |= pSpmiProtocol->WriteLong(pSpmiProtocol, PMIC_EUSB_RPTR_SPMI_BUSID, PMIC_EUSB_RPTR_INDEX,
                                         SPMI_BUS_ACCESS_PRIORITY_LOW, address, &data, len);

     DEBUG(( EFI_D_ERROR, "WRITING: reg: 0x%x, data: %d, res = %d\r\n",address, data, spmi_ret));
  }

  if(SPMI_SUCCESS != spmi_ret)
  {
    DEBUG(( EFI_D_ERROR, "write spmi reg failed: %d\r\n", spmi_ret));
    return FALSE;
  }

  return TRUE;
}

boolean usb_repeater_spmi_init(uint32 core_num)
{
  EFI_STATUS    Status;

  /* Get SPMI Protocol */
  Status = gBS->LocateProtocol(&gQcomSPMIProtocolGuid, NULL, (VOID **) &pSpmiProtocol);
  if ( EFI_ERROR (Status) )
  {
    DEBUG(( EFI_D_ERROR, "failed to locate SPMIProtocol, Status = (0x%x)\r\n", Status));
    return FALSE;
  }
  
  if (TRUE == usb_repeater_spmi_process_cfg_reg_array(g_repeater_tuning_cfg_handle, 0 , g_repeater_tuning_size, 0))
  {
    return usb_repeater_spmi_read_cfg_reg_array(g_repeater_tuning_cfg_handle, 0 , g_repeater_tuning_size, 0);
  }
  return FALSE;
}

volatile boolean usb_shared_enable_repeater_support = FALSE;

boolean usb_repeater_is_tuning_allowed (usb_platform_ctx plat_type)
{
  boolean repeater_tune_allow = FALSE;
  usb_shared_uart_log_error("Platform :", plat_type.platform); 
  switch (plat_type.platform)
  {
    case DALPLATFORMINFO_TYPE_QRD:
      repeater_tune_allow = TRUE;
      g_repeater_tuning_cfg_handle = PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_QRD;
      g_repeater_tuning_size = (sizeof(PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_QRD) / sizeof(usb_repeater_cfg_type));
	  break;
    case DALPLATFORMINFO_TYPE_MTP:
      /* fall through */
    case DALPLATFORMINFO_TYPE_IDP:
      repeater_tune_allow = TRUE;
      g_repeater_tuning_cfg_handle = PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_MTP;
      g_repeater_tuning_size = (sizeof(PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_MTP) / sizeof(usb_repeater_cfg_type));
	  
      break;
    case DALPLATFORMINFO_TYPE_ATP:
      repeater_tune_allow = TRUE;
      g_repeater_tuning_cfg_handle = PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_ATP;
      g_repeater_tuning_size = (sizeof(PMIC_EUSB_RPTR_OVRD_SEQ_PLAT_ATP) / sizeof(usb_repeater_cfg_type));
      break;
    default:
      repeater_tune_allow = FALSE;
  }
  return repeater_tune_allow;
}

boolean usb_repeater_init(uint32 core_num)
{
  usb_platform_ctx plat_type = usb_shared_get_platform();
  usb_shared_enable_repeater_support = usb_repeater_is_tuning_allowed(plat_type);
  
  if (usb_shared_enable_repeater_support)
  {
	usb_shared_uart_log_error("usb_repeater_init, tuning_allowed", usb_shared_enable_repeater_support);
    return usb_repeater_spmi_init(core_num);
  }
  return TRUE;
}
