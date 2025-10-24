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

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/NullLibs/EudTargetLibNull/eud_config.h#1 $

when       who      what, where, why
--------   ---      ----------------------------------------------------------
07/21/20   amcheriy Created.
******************************************************************************/

#ifndef _EUD_CONFIG_H
#define _EUD_CONFIG_H

#include "com_dtypes.h"

#define EUD_LOGSTRING_SZ  50

/* Private data structure for EUD Configuration */
typedef struct 
{
  uint32_t bGPIO;
  uint32_t nGPIOIdx;
  uint32_t bBootConfig;
  uint32_t nBootConfigMask;
  uint32_t eud_en_val;
  uint32_t *boot_config_csr;
  uint32_t *eud_en_csr;
  uint32_t bStallOnEnable;
  uint32_t nStallDelay;
}eud_config_type;

const eud_config_type *get_target_config(void);

#endif /* _EUD_CONFIG_H */

