/*===========================================================================

                   IPC ROUTER DEVICE CONFIGURATION

        This file provides the device configuration for IPC Router

  ---------------------------------------------------------------------------
  Copyright (c) 2016-2017, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header:

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/26/17   jlg     moved settings to core/settings directory
===========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
#include "ipc_router_settings.h"
#include <Library/KernelLib.h>

/*===========================================================================
                    CONSTANT / MACRO DECLARATIONS
===========================================================================*/
#define IPC_ROUTER_XAL_GLINK_PRIO HIGHEST_PRIORITY
#define IPC_ROUTER_XAL_GLINK_STACK_SIZE (1024 * 4)

/*===========================================================================
                      LOCAL DATA DEFINATION
===========================================================================*/
/* GLINK Transports */
static ipc_router_xal_glink_param_type ipc_router_devcfg_glink_xals[] =
{
 /* Link to MPSS */
  {
    "SMEM", "mpss", "IPCRTR", 0, 
    IPC_ROUTER_XAL_GLINK_PRIO,
    IPC_ROUTER_XAL_GLINK_STACK_SIZE,
    {{128,16}, {512, 8}, {1024+128, 5}, {8192+128, 1}}
  },
  /* Link to ADSP */
  {
    "SMEM", "lpass", "IPCRTR", 0, 
    IPC_ROUTER_XAL_GLINK_PRIO,
    IPC_ROUTER_XAL_GLINK_STACK_SIZE,
    {{128,16}, {512, 8}, {1024+128, 5}, {0, 0}}
  },
  /* Link to dsps */
  {
    "SMEM", "dsps", "IPCRTR", 0,
    IPC_ROUTER_XAL_GLINK_PRIO,
    IPC_ROUTER_XAL_GLINK_STACK_SIZE,
    {{128,16}, {512, 8}, {1024+128, 5}, {0, 0}},
  },
  /* Link to dsps */
  {
    "SMEM", "cdsp", "IPCRTR", 0,
    IPC_ROUTER_XAL_GLINK_PRIO,
    IPC_ROUTER_XAL_GLINK_STACK_SIZE,
    {{128,16}, {512, 8}, {1024+128, 5}, {0, 0}},
  },
  /* Link to wpss */
  {
    "SMEM", "wpss", "IPCRTR", 0,
    IPC_ROUTER_XAL_GLINK_PRIO,
    IPC_ROUTER_XAL_GLINK_STACK_SIZE,
    {{128,16}, {512, 8}, {1024+128, 5}, {0, 0}},
  },
  {
    NULL, NULL, NULL, 0, 0, 0, {{0, 0}}
  }
};

/*===========================================================================
                      GLOBAL DATA DEFINATION
===========================================================================*/
/* Processor information */
const ipc_router_proc_info_type ipc_router_devcfg_proc =
{
  "apps",
  1
};

/* Transports supported */
const ipc_router_xal_info_type ipc_router_devcfg_xals[] =
{
  {"GLINK", (const void*)ipc_router_devcfg_glink_xals},
  {NULL, NULL}
};

