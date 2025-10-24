#ifndef _IPC_ROUTER_XAL_GLINK_H_
#define _IPC_ROUTER_XAL_GLINK_H_
/*===========================================================================

                      I P C    R O U T E R    X A L
                                G L I N K

  ---------------------------------------------------------------------------
  Copyright (c) 2014, 2017 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------
===========================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IpcrtrLib/src/ipc_router_xal_glink.h#1 $ 
$DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
01/26/17   jlg     Moved settings-related definitions to ipc_router_settings.h
11/06/14   aep     Initial creation
===========================================================================*/

/*===========================================================================
                          INCLUDE FILES
===========================================================================*/
#include "ipc_router_os.h"
#include "ipc_router_xal.h"
#include "glink.h"

/** The operation table of the XAL */
extern ipc_router_xal_ops_type ipc_router_xal_glink;

#endif
