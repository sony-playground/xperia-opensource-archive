/****************************************************************************

                 Embedded USB Debugger Library Routines
                 --------------------------------------

DESCRIPTION
-----------
This file contains private APIs and data structures for use within EUD Library.

Copyright (c) 2020 QUALCOMM Technologies Incorporated.
All Rights Reserved. Qualcomm Proprietary

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NullLibs/EudTargetLibNull/eud_config.c#1 $

when       who      what, where, why
--------   ---      ----------------------------------------------------------
07/21/20   amcheriy Created.
******************************************************************************/

#include "com_dtypes.h"
#include "hwio_eud.h"
#include "eud_config.h"

static const eud_config_type eud_config_data = {
  .bGPIO           = 1,
  .nGPIOIdx        = 55,
  .bBootConfig     = 0,
  .nBootConfigMask = (1 << 11),
  .eud_en_val      = HWIO_EUD_EN2_EUD_EN2_BMSK,
  .eud_en_csr      = (uint32_t *)HWIO_EUD_EN2_ADDR,
  .bStallOnEnable  = 1,
  /* Duration for which boot needs to be stalled (seconds) */
  .nStallDelay     = 12,
};


const eud_config_type *get_target_config(void)
{
  return &eud_config_data;
}
