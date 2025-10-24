/** @file UsbRepeater.h

  The public header file for UsbRepeater.c
  Copyright (c) 2016-2019 QUALCOMM Technologies Inc. All rights reserved.

**/
//============================================================================
/**
  Copyright (c) 2021 Qualcomm Technologies, Inc. All rights reserved.
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
 09/09/21   srmi     Initial Check-in
=============================================================================*/

#ifndef _USB_REPEATER_H_
#define _USB_REPEATER_H_

#include "UsbSharedLib.h"

typedef struct 
{
  uint32  reg;
  uint32  data;
} usb_repeater_cfg_type;

#define PMIC_EUSB_RPTR_INDEX                        (7)   // PMIC_H, Kohala PM8550B
#define PMIC_EUSB_RPTR_SPMI_BUSID                   (0)

#define EUSB2_BASE                                  0x0000fd00
#define PMIO_EUSB2_TUNE_USB2_CROSSOVER_ADDR         (EUSB2_BASE            + 0x00000050)
#define PMIO_EUSB2_TUNE_IUSB2_ADDR                  (EUSB2_BASE            + 0x00000051)
#define PMIO_EUSB2_TUNE_RES_FSDIF_ADDR              (EUSB2_BASE            + 0x00000052)
#define PMIO_EUSB2_TUNE_HSDISC_ADDR                 (EUSB2_BASE            + 0x00000053)
#define PMIO_EUSB2_TUNE_SQUELCH_U_ADDR              (EUSB2_BASE            + 0x00000054)
#define PMIO_EUSB2_TUNE_USB2_SLEW_ADDR              (EUSB2_BASE            + 0x00000055)
#define PMIO_EUSB2_TUNE_USB2_EQU_ADDR               (EUSB2_BASE            + 0x00000056)
#define PMIO_EUSB2_TUNE_USB2_PREEM_ADDR             (EUSB2_BASE            + 0x00000057)
#define PMIO_EUSB2_TUNE_USB2_HS_COMP_CURRENT_ADDR   (EUSB2_BASE            + 0x00000058)
#define PMIO_EUSB2_TUNE_EUSB_SLEW_ADDR              (EUSB2_BASE            + 0x00000059)
#define PMIO_EUSB2_TUNE_EUSB_EQU_ADDR               (EUSB2_BASE            + 0x0000005a)
#define PMIO_EUSB2_TUNE_EUSB_HS_COMP_CURRENT_ADDR   (EUSB2_BASE            + 0x0000005b)

// ===========================================================================
/**
 * @function    usb_repeater_init
 * 
 * @brief   This function start repeater driver
 * 
 * @param   core_num   -  which core repeater locate
 * 
 * @return  boolean - TRUE successs, FALSE error
 * 
 */
// ===========================================================================
boolean usb_repeater_init(uint32 core_num);

#endif /* _USB_REPEATER_H_ */