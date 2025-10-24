#ifndef __IPCCLOG_H__
#define __IPCCLOG_H__
/*===========================================================================

  IPCC_Log.h

DESCRIPTION
  This modules contains the logging mechanism for IPCC Logs.

REFERENCES

       Copyright (c) 2018-2020 QUALCOMM Technologies Incorporated.
               All Rights Reserved.
            QUALCOMM Proprietary/GTDR
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/IPCCLib/inc/IPCC_Log.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
05/29/18   cpaulo  First draft created. 
===========================================================================*/
#include <stdint.h>

/*===========================================================================
Definitions
===========================================================================*/

typedef enum 
{
  IPCCLOG_LEGACY_TRIGGER_SUCCESS,
  IPCCLOG_LEGACY_TRIGGER_FAIL,
  IPCCLOG_TX_SUCCESS,
  IPCCLOG_TX_FAIL,
  IPCCLOG_MAX,
}
IPCCLogStr;

/*===========================================================================
FUNCTION IPCCLog_Init
===========================================================================*/
void IPCCLog_Init( void );


/*===========================================================================
FUNCTION IPCCLog_Out
===========================================================================*/
void IPCCLog_Out( uint32_t nArgs, const char* sztStr, ... );

#endif /*__IPCCLOG_H__*/
