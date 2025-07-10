/*
=====================================================================================
*/
/**
  @file qmp_glink.h

*/
/*
  ===================================================================================

  Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ====================================================================
*/

#ifndef QMP_GLINK_H
#define QMP_GLINK_H

#include "glink.h"
#include <Protocol/EFIGLink.h>

/*=============================================================================
  INTERNAL DEFINES
=============================================================================*/

#define QMP_GLINK_PKT_SIZE             0x60
#define QMP_GLINK_RX_FIFO_DEPTH        6
#define QMP_GLINK_XPORT_NAME           "qmp"
#define QMP_GLINK_REMOTE_SS_NAME       "rpm"
#define QMP_GLINK_APSS_PORT_NAME       "aop_uefi" /* Port name used to communicate with APSS */
#define QMP_GLINK_MAX_TYPEC_PORT       4
#define QMP_COMMAND_BUF_SIZE           64

/*=============================================================================
  INTERNAL TYPEDEF
=============================================================================*/
typedef struct
{
  BOOLEAN is_link_up;
  BOOLEAN is_channel_open;
  BOOLEAN tx_done;
  BOOLEAN rx_notified;
}QMP_GLINK_CONTEXT;


typedef glink_handle_type glink_handle_t;

typedef void (*glink_api_t)(glink_handle_type handle,
                                const void *priv, 
                                const void *pkt_priv,
								const void *ptr, 
								size_t     size);


/*=============================================================================
                        INTERNAL FUNCTIONS
=============================================================================*/

/*=============================================================================
  FUNCTION  Clock_QmpInit
=============================================================================*/

EFI_STATUS Clock_QmpInit();

/*=============================================================================
  FUNCTION  Clock_QmpDeInit
=============================================================================*/

void Clock_QmpDeInit();


/*=============================================================================
  FUNCTION  Clock_QmpTx
=============================================================================*/

EFI_STATUS Clock_QmpTx(const void *priv, const void *data, const size_t size);
EFI_STATUS Clock_QmpSendMsg(const void *data, const size_t size);

/*=============================================================================
  FUNCTION  Clock_QmpRxDone
=============================================================================*/

EFI_STATUS Clock_QmpRxDone(const void *data, BOOLEAN refill);

#endif // QMP_GLINK_H
