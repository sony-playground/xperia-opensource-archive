#ifndef __EEPROM_OSAL__H
#define __EEPROM_OSAL__H
/**********************************************************************
 *eeprom_osal.h
 *
 * This file provides definitions for the eeprom platform specific functions
 *
 * Copyright (c) 2020 Qualcomm Technologies Inc.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 *
 **********************************************************************/
/*===================================================================
 *
 * 					  EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 *
 * when          who     what, where, why
 * ----------	 ---	 ------------------------------------------------
 * 09-10-2020	 eo 	 Initial version
 *=======================================================================*/
#include <stdlib.h>
#include "com_dtypes.h"
#include <string.h>
#include "stringl/stringl.h"

#ifndef PACKED
  #define PACKED
#endif

#ifndef PACKED_POST
  #define PACKED_POST __attribute__((__packed__))
#endif

#define FLUSH                 1
#define INVAL                 2
#define CLEAN                 4

/* Cache management wrapper */

void eeprom_cache_op (void *addr, uint32_t len, uint32_t op);

#endif /* __EEPROM_OSAL__H */

