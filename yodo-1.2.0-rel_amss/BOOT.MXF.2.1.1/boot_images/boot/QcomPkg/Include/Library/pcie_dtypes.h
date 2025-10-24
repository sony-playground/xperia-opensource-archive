#ifndef __PCIE_DTYPES_H__
#define __PCIE_DTYPES_H__
/*
 *  Defines the PCIe sw specific data types
 */
/*
===============================================================================

                    Edit History


   when       who     what, where, why
   --------   ---     ---------------------------------------------------------
   10/20/20   Yg      Created new
*/
/*============================================================================
         Copyright (c) 2020 - 2022 QUALCOMM Technologies Incorporated
                          All Rights Reserved.
                 Qualcomm Confidential and Proprietary.
============================================================================*/

#include "com_dtypes.h"

typedef enum
{
   PCIE_SUCCESS       = 0,
   PCIE_ERROR         = 1,
   PCIE_INVALID_PARAM = 2,
   PCIE_UNSUPPORTED   = 3,
   PCIE_DISABLED      = 4,
   PCIE_NOT_READY     = 5,
   PCIE_NOT_FOUND     = 6,
   PCIE_OUT_OF_RANGE  = 7,
} pcie_status_t;

typedef enum
{
   PCIE_PRIMARY_BOOT_DEVICE = 0,
   PCIE_ALTERNATE_BOOT_DEVICE = 1,

   PCIE_DEVICE_PORT_MAX = 2,
}pcie_device_port_type;

typedef enum {
   PCIE_LOOPBACK_NONE            = 0,
   PCIE_LOCAL_DIGITAL_LOOPBACK   = 1,
   PCIE_LOCAL_ANALOG_LOOPBACK    = 2,
   PCIE_REMOTE_DIGITAL_LOOPBACK  = 3,
   PCIE_REMOTE_ANALOG_LOOPBACK   = 4,

   PCIE_LOOPBACK_MAX
}pcie_loopback_type;

#define DISABLE  0
#define ENABLE   1

#define HOST_BDF_VAL    0x000

/* Note that EP BDF value will change based on any switch/bridges present
 * in the PCIe bus topology, need a proper solution for such cases which
 * are not supported today */
#define EP_BDF_VAL      0x100

#define ALL_BDF_VAL    0xFFFF

#define SET_MASK_VAL(x,regfld,v)   ((x) = (x) & (~regfld##_BMSK)); \
                                     (x) = (x) | (regfld##_BMSK & ((v) << regfld##_SHFT));

#define GET_MASK_VAL(x,regfld)   ((x) = (((x) & regfld##_BMSK) >> regfld##_SHFT));

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))
#endif /* ifndef ARRAY_SIZE */


#endif   /* __PCIE_DTYPES_H__ */

