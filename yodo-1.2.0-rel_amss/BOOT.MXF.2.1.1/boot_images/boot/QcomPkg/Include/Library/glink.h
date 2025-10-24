#ifndef GLINK_H
#define GLINK_H

/**
 * @file glink.h
 *
 * Public API for the GLink
 */

/** \defgroup glink GLink
 * \ingroup SMD
 *
 * GLink reliable, in-order, datagram-based interprocessor communication
 * over a set of supported transport (Shared Memory, UART, BAM, HSIC)
 *
 * All ports preserve message boundaries across the interprocessor channel; one
 * write into the port exactly matches one read from the port.
 */
/*@{*/

/*==============================================================================
     Copyright (c) 2014-2016 QUALCOMM Technologies Incorporated.
     All rights reserved.
     Qualcomm Confidential and Proprietary
==============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/Library/glink.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
06/20/16   ap      Added intent allocation/deallocation callbacks
04/25/16   sm      Added timeout for wait on remote intent
04/14/16   na      Changed header definition of 'glink_notify_rx_abort_cb'
06/19/15   pp      Expanded list for err_type & changed to -ve error codes
04/15/15   sm      Added timeout error type.
04/02/15   an      Use com_dtypes instead of comdef due to wider availability
02/23/15   bc      Add rx tracer packet notification callback
12/19/14   bm      Add rx/tx abort notifiaction callbacks
11/20/14   bm      Added glink open config flag
07/04/14   bm      Updated API to v0.6.5 GLink spec
03/22/14   bm      Initial release of GLink API
===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/
#include "com_dtypes.h"
#include "stddef.h"
#include <string.h>
#include "glink_common.h"

/*===========================================================================
                      MACRO DECLARATIONS
===========================================================================*/

/** List of possible subsystems */
/**
  "apss"   Application Processor Subsystem
  "mpss"   Modem subsystem
  "lpass"  Low Power Audio Subsystem
  "dsps"   Sensors Processor
  "wcnss"  Wireless Connectivity Subsystem
  "rpm"    Resource Power Manager processor
*/

/* Bit position of DTR/CTS/CD/RI bits in control sigs 32 bit signal map */
#define SMD_DTR_SIG_SHFT 31
#define SMD_CTS_SIG_SHFT 30
#define SMD_CD_SIG_SHFT  29
#define SMD_RI_SIG_SHFT  28

/** Version number for the glink_link_id_type structure */
#define GLINK_LINK_ID_VER  0x00000001

/** Macro to initialize the link identifier structure with default values.
 * It memsets the header to 0 and initializes the header field */
#define GLINK_LINK_ID_STRUCT_INIT(link_id) \
                          (link_id).xport = 0; \
                          (link_id).remote_ss = 0; \
                          (link_id).link_notifier = 0; \
                          (link_id).handle = 0; \
                          (link_id).version = GLINK_LINK_ID_VER;

/* GLink tx options */
/* Flag for no options */
#define GLINK_TX_NO_OPTIONS      ( 0 )

/* Whether to block and request for remote rx intent in
 * case it is not available for this pkt tx */
#define GLINK_TX_REQ_INTENT      0x00000001

/* If the tx call is being made from single threaded context. GLink tries to
 * flush data into the transport in glink_tx() context, or returns error if
 * it is not able to do so */
#define GLINK_TX_SINGLE_THREADED 0x00000002

/* This option is to turn on tracer packet */
#define GLINK_TX_TRACER_PKT      0x00000004

/* ======================= glink open cfg options ==================*/

/* Specified transport is just the initial transport and migration is possible
 * to higher-priority transports.  Without this flag, the open will fail if
 * the transport does not exist. */
#define GLINK_OPT_INITIAL_XPORT            0x00000001

/* Specified if the client wishes to provide their own allocation/deallocation
 * methods. See glink_notify_allocate_cb and glink_notify_deallocate_cb for 
 * more info. */
#define GLINK_OPT_CLIENT_BUFFER_ALLOCATION 0x00000002

/* Clients must call this macro to initialize the open config structure
 * before setting its individual members. This will ensure that the 
 * default optional values in the structure are appropriately initialized. */
#define GLINK_OPEN_CONFIG_INIT(cfg) \
  memset(&(cfg), 0, sizeof(cfg))

/*===========================================================================
                      GLINK PUBLIC API
===========================================================================*/
/** 
 * Regsiters a client specified callback to be invoked when the specified
 * transport (link) is up/down.
 *
 * @param[in]    link_id  Pointer to the configuration structure for the
 *                        xport(link) to be monitored. See glink.h
 * @param[in]    priv     Callback data returned to client when callback
 *                        is invoked.
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Puts the callback in a queue which gets scanned when a 
 *               transport(link) comes up OR an SSR happnes.
 */
glink_err_type glink_register_link_state_cb
(
  glink_link_id_type *link_id,
  void* priv
);

/** 
 * Degsiter the link UP/DOWN notification callback associated with the
 * provided handle.
 *
 * @param[in]    handle  Callback handler returned by 
 *                       glink_register_link_state_cb
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Removes the callback in a queue which gets scanned when a 
 *               transport(link) comes up OR an SSR happnes.
 */
glink_err_type glink_deregister_link_state_cb
(
  glink_link_handle_type handle
);

/** 
 * Opens a logical GLink based on the specified config params
 *
 * @param[in]    cfg_ptr  Pointer to the configuration structure for the
 *                        GLink. See glink.h
 * @param[out]   handle   GLink handle associated with the logical channel
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Allocates channel resources and informs remote host about
 *               channel open.
 */
glink_err_type glink_open
(
  glink_open_config_type *cfg_ptr,
  glink_handle_type      *handle
);

/** 
 * Closes the GLink logical channel specified by the handle.
 *
 * @param[in]    handle   GLink handle associated with the logical channel
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Closes local end of the channel and informs remote host
 */
glink_err_type glink_close
(
  glink_handle_type handle
);

/** 
 * Transmit the provided buffer over GLink.
 *
 * @param[in]    handle    GLink handle associated with the logical channel
 *
 * @param[in]   *pkt_priv  Per packet private data
 *
 * @param[in]   *data      Pointer to the data buffer to be transmitted
 *
 * @param[in]   size       Size of buffer
 *
 * @param[in]   options    Flags specifying how transmission for this buffer 
 *                         would be handled. See GLINK_TX_* flag definitions.
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Causes remote host to wake-up and process rx pkt
 */
glink_err_type glink_tx
(
  glink_handle_type handle,
  const void        *pkt_priv,
  const void        *data,
  size_t            size,
  uint32            options
);

/** 
 * Transmit the provided vector buffer over GLink.
 *
 * @param[in]    handle    GLink handle associated with the logical channel
 *
 * @param[in]   *pkt_priv  Per packet private data
 *
 * @param[in]   *iovec     Pointer to the vector buffer to be transmitted
 *
 * @param[in]   size       Size of buffer
 *
 * @param[in]   vprovider  Buffer provider for virtual space
 *
 * @param[in]   pprovider  Buffer provider for physical space
 *
 * @param[in]   options    Flags specifying how transmission for this buffer 
 *                         would be handled. See GLINK_TX_* flag definitions.
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  Causes remote host to wake-up and process rx pkt
 */
glink_err_type glink_txv
(
  glink_handle_type        handle,
  const void               *pkt_priv,
  void                     *iovec,
  size_t                   size,
  glink_buffer_provider_fn vprovider,
  glink_buffer_provider_fn pprovider,
  uint32                   options
);

/** 
 * Queue one or more Rx intent for the logical GPIC Link channel.
 *
 * @param[in]    handle   GLink handle associated with the logical channel
 *
 * @param[in]   *pkt_priv Per packet private data
 *
 * @param[in]   size      Size of buffer
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  GLink XAL allocates rx buffers for receiving packets
 */
glink_err_type glink_queue_rx_intent
(
  glink_handle_type handle,
  const void        *pkt_priv,
  size_t            size
);

/** 
 * Client uses this to signal to GLink layer that it is done with the received 
 * data buffer. This API should be called to free up the receive buffer, which,
 * in zero-copy mode is actually remote-side's transmit buffer.
 *
 * @param[in]   handle   GLink handle associated with the logical channel
 *
 * @param[in]   *ptr     Pointer to the received buffer
 *
 * @param[in]   reuse    Reuse intent
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  GLink XAL frees the Rx buffer
 */
glink_err_type glink_rx_done
(
  glink_handle_type handle,
  const void        *ptr,
  boolean           reuse
);

/** 
 * Set the 32 bit control signal field. Depending on the transport, it may
 * take appropriate actions on the set bit-mask, or transmit the entire 
 * 32-bit value to the remote host.
 *
 * @param[in]   handle     GLink handle associated with the logical channel
 *
 * @param[in]   sig_value  32 bit signal word
 *
 * @return       Standard GLink error codes
 *
 * @sideeffects  None
 */
glink_err_type glink_sigs_set
(
  glink_handle_type handle,
  uint32            sig_value
);

/** 
 * Get the local 32 bit control signal bit-field.
 *
 * @param[in]   handle      GLink handle associated with the logical channel
 *
 * @param[out]  *sig_value  Pointer to a 32 bit signal word to get sig value
 *
 * @return      Standard GLink error codes
 *
 * @sideeffects  None
 */
glink_err_type glink_sigs_local_get
(
  glink_handle_type handle,
  uint32            *sig_value
);

/** 
 * Get the remote 32 bit control signal bit-field.
 *
 * @param[in]   handle      GLink handle associated with the logical channel
 *
 * @param[out]  *sig_value  Pointer to a 32 bit signal word to get sig value
 *
 * @return      Standard GLink error codes
 *
 * @sideeffects  None
 */
glink_err_type glink_sigs_remote_get
(
  glink_handle_type handle,
  uint32            *sig_value
);

#ifdef __cplusplus
}
#endif

#endif //GLINK_H
