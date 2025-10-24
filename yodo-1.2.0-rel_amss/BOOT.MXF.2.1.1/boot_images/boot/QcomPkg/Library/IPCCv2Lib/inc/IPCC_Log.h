#ifndef __IPCCLOG_H__
#define __IPCCLOG_H__
/*===========================================================================

  IPCC_Log.h

DESCRIPTION
  This modules contains the logging mechanism for IPCC Logs.

REFERENCES

       Copyright (c) 2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
            Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/dev/core.boot/6.1/shantonu.core.boot.6.1.ipccHwMemOpt_uefi/QcomPkg/Library/IPCCLib/inc/IPCC_Log.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/29/18   cpaulo  First draft created. 
===========================================================================*/
#include <stdint.h>


/*===========================================================================
FUNCTION IPCCLog_Init
===========================================================================*/
void IPCCLog_Init( void );


/*===========================================================================
FUNCTION IPCCLog_Out
===========================================================================*/
#ifdef IPCC_NO_LOG
#define IPCCLog_Out(x, ...)
#else
void IPCCLog_Out( uint32_t nArgs, const char* sztStr, ... );
#endif

#endif /*__IPCCLOG_H__*/
