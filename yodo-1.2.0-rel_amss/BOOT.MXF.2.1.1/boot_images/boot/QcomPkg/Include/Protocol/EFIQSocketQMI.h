/** 
  @file  EFIQSocketQMI.h
  @brief QSocket and QMI Protocol for UEFI.
*/
/*=============================================================================
  Copyright (c) 2021 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     ----------------------------------------------------------
 02/02/21   ar      Initial version for QSocket and QMI Protocol.

=============================================================================*/
#ifndef __EFIQSOCKETQMI_H__
#define __EFIQSOCKETQMI_H__

/*===========================================================================
  INCLUDE FILES
===========================================================================*/
#include "prot_dtypes.h"
#include "qsocket_common.h"
#include "qsocket_ipcr_common.h"
#include "qmi_idl_lib.h"
#include "qmi_csi.h"
#include "qmi_client.h"
/*===========================================================================
  MACRO DECLARATIONS
===========================================================================*/

/** @ingroup efi_glink_constants
  Protocol version.
*/
#define EFI_QSOCKETQMI_PROTOCOL_REVISION 0x0000000000010001

/*  Protocol GUID definition */
/** @ingroup efi_qsocketqmi_protocol {26ce12a9-b1a6-4fe1-9062-79242a65ca1e}*/
#define EFI_QSOCKETQMI_PROTOCOL_GUID \
  { 0x26ce12a9, 0xb1a6, 0x4fe1, { 0x90, 0x62, 0x79, 0x24, 0x2a, 0x65, 0xca, 0x1e } }

/** @cond */
/*===========================================================================
  EXTERNAL VARIABLES
===========================================================================*/
/*
  External reference to the QSocketQMI Protocol GUID.
 */
extern EFI_GUID gEfiQSocketQMIProtocolGuid;
/** @endcond */

/*===========================================================================
  TYPE DEFINITIONS
===========================================================================*/
/*===========================================================================
  FUNCTION  qsocket
===========================================================================*/
/*!
@brief

  This function returns a socket descriptor

@param[in]   domain    The address family of the socket (Currently only
                       AF_IPC_ROUTER is supported)
@param[in]   type      Type of socket. See SOCKET TYPES for more info
@param[in]   protocol  Family specific protocol (Currently unused)

@return
  Positive socket descriptor upon success, negative error code on failure.

@note

  - Dependencies
    - None

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QSOCKET)
(
  int domain,
  int type,
  int protocol,
  int ret
);

/*===========================================================================
  FUNCTION  qconnect
===========================================================================*/
/*!
@brief

  Connect the socket to the specified destination endpoint. Considering 
  IPC Router is a connection-less protocol, this does not result in
  an actual connection, but just associates the socket to the remote
  endpoint. Thus, if the remote endpoint terminates, the sender will
  detect a failure.

@param[in]   fd        Socket descriptor
@param[in]   addr      Address of the destination endpoint
@param[in]   addrlen   Length of the address

@return
  0 on success, negative error code on failure.

@note

  - Dependencies
    - None

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QCONNECT)
(
  int fd,
  struct qsockaddr *addr,
  qsocklen_t addrlen,
  int ret
);

/*===========================================================================
  FUNCTION  qbind
===========================================================================*/
/*!
@brief

  Binds a socket to a specific name.
  Since all ports in IPC Router are ephemeral ports, it is not allowed
  to bind to a specified physical port ID (Like UDP/IP).

@param[in]   fd        Socket descriptor
@param[in]   addr      Name to bind with the socket
@param[in]   addrlen   Length of the address

@return
  0 on success, negative error code on failure.

@note

  - Dependencies
    - Note that the 'type' field of the NAME _must_ be allocated and reserved
      by the Qualcomm Interface Control board else it is highly likely that
      the users might be in conflict with names allocated to other users.

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QBIND)
(
  int fd,
  struct qsockaddr *addr,
  qsocklen_t addrlen,
  int ret
);

/*===========================================================================
  FUNCTION  qsendto
===========================================================================*/
/*!
@brief

  Sends a message to a specific remote address

@param[in]   fd        Socket descriptor
@param[in]   buf       Pointer to the buffer
@param[in]   len       Length of the buffer
@param[in]   flags     Flags - See SOCKET SEND/RECV FLAGS for more info
@param[in]   addr      Address of the destination
@param[in]   addrlen   Length of the address

@return
  Transmitted length on success, negative error code on failure.
  If the destination is flow controlled, and QMSG_DONTWAIT is
  set in flags, then the function can return QEAGAIN

  If the address is of type IPCR_ADDR_NAME, the message is multicast
  to all ports which has bound to the specified name.

@note
  - Dependencies
    - None

  - Retry logic (After receiving an error of QEAGAIN)
    - If QMSG_DONTWAIT is set in the flags, the user must retry
      after blocking and receiving the:
      * QPOLLOUT event (In the case of a connected socket)'
      * QPOLLIN event in the case of a unconnected socket and
        qrecvfrom() returns a zero length message with the unblocked
        destination in the output address.

  - Side Effects
    - Function can block.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QSENDTO)
(
  int fd,
  void *buf,
  size_t len,
  int flags,
  struct qsockaddr *addr,
  qsocklen_t addrlen,
  int ret
);

/*===========================================================================
  FUNCTION  qsend
===========================================================================*/
/*!
@brief

  Sends a message to the connected address

@param[in]   fd        Socket descriptor
@param[in]   buf       Pointer to the buffer
@param[in]   len       Length of the buffer
@param[in]   flags     Flags - See SOCKET SEND/RECV FLAGS for more info

@return
  Transmitted length on success, negative error code on failure.
  If the destination is flow controlled, and QMSG_DONTWAIT is
  set in flags, then the function can return QEAGAIN

  If the address is of type IPCR_ADDR_NAME, the message is multicast
  to all ports which has bound to the specified name.

@note
  - Dependencies
    - None

  - Retry logic (After receiving an error of QEAGAIN)
    - If QMSG_DONTWAIT is set in the flags, the user must retry
      after blocking and receiving the:
      * QPOLLOUT event (In the case of a connected socket)'
      * QPOLLIN event in the case of a unconnected socket and
        qrecvfrom() returns a zero length message with the unblocked
        destination in the output address.

  - Dependencies
    - qconnect() must have been called to associate this socket
      with a destination address

  - When the connected endpoint terminates (normally or abnormally), the
    function would unblock and return QENOTCONN/QEDESTADDRREQ.

  - Side Effects
    - Function can block.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QSEND)
(
  int fd,
  void *buf,
  size_t len,
  int flags,
  int ret
);

/*===========================================================================
  FUNCTION  qrecvfrom
===========================================================================*/
/*!
@brief

  Receives a message from a remote address

@param[in]   fd        Socket descriptor
@param[in]   buf       Pointer to the buffer
@param[in]   len       Length of the buffer
@param[in]   flags     Flags - See SOCKET SEND/RECV FLAGS for more info
@param[out]  addr      Address of the sender
@param[inout]addrlen   Input: Size of the passed in buffer for address
                       Output: Size of the address filled by the framework.
                       (Can be NULL if addr is also NULL).

@return
  Received packet size in bytes, negative error code in failure.

@note

  - Dependencies
    - None

  - Retry logic
    - If QMSG_DONTWAIT is set in the flags, the user must retry
      after blocking and receiving the QPOLLIN event using qpoll()

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QRECVFROM)
(
  int fd,
  void *buf,
  size_t len,
  int flags,
  struct qsockaddr *addr,
  qsocklen_t *addrlen,
  int ret
);

/*===========================================================================
  FUNCTION  qrecv
===========================================================================*/
/*!
@brief

  Receives a message from the connected address address

@param[in]   fd        Socket descriptor
@param[in]   buf       Pointer to the buffer
@param[in]   len       Length of the buffer
@param[in]   flags     Flags - See SOCKET SEND/RECV FLAGS for more info

@return
  Received packet size in bytes, negative error code in failure.

@note

  - Dependencies
    - qconnect() must have been called to associate this socket
      with a destination address

  - Retry logic
    - If QMSG_DONTWAIT is set in the flags, the user must retry
      after blocking and receiving the QPOLLIN event using qpoll()

  - When the connected endpoint terminates (normally or abnormally), the
    function would unblock and return QENOTCONN/QEDESTADDRREQ.

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QRECV)
(
  int fd,
  void *buf,
  size_t len,
  int flags,
  int ret
);

/*===========================================================================
  FUNCTION  qgetsockopt
===========================================================================*/
/*!
@brief

  Gets an option value

@param[in]   fd        Socket descriptor
@param[in]   level     Level of the option. Currently the only supported
                       level is QSOL_IPC_ROUTER
@param[in]   optname   Option name to get
@param[in]   optval    Buffer to place the option
@param[inout]optlen    In: Length of the buffer passed into qgetsockopt
                       Out: Length of the filled in options

@return
  0 on success, negative error code on failure.

@note
  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QGETSOCKOPT)
(
  int fd,
  int level,
  int optname,
  void *optval,
  qsocklen_t *optlen,
  int ret
);

/*===========================================================================
  FUNCTION  qsetsockopt
===========================================================================*/
/*!
@brief

  Sets an option on a socket

@param[in]   fd        Socket descriptor
@param[in]   level     Level of the option. Currently the only supported
                       level is QSOL_IPC_ROUTER
@param[in]   optname   Option name to get
@param[in]   optval    Buffer to place the option
@param[in]   optlen    Length of the buffer passed into qsetsockopt

@return
  0 on success, negative error code on failure.

@note
  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QSETSOCKOPT)
(
  int fd,
  int level,
  int optname,
  void *optval,
  qsocklen_t optlen,
  int ret
);

/*===========================================================================
  FUNCTION  qpoll
===========================================================================*/
/*!
@brief

  Blocks on requested events on the provided socket descriptors

@param[in]   pfd       Array of poll info (See qpollfd for more info)
@param[in]   num       Number of sockets to wait on (Len of pfd array)
@param[in]   timeout_ms Timeout in milli-seconds:
                        -1 = Infinite
                        0  = poll, return immediately if there are no events
                        val > 0, timeout

@return
  Total number of socket descriptors which have events on them on success
  0 if there were no events, and the function unblocked after the timeout.
  Negative error code on failure.

@note

  - Dependencies
    - None

  - Side Effects
    - Blocks waiting for events
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QPOLL)
(
  struct qpollfd *pfd,
  qnfds_t num,
  int timeout_ms,
  int ret
);

/*===========================================================================
  FUNCTION  qclose
===========================================================================*/
/*!
@brief

  Closes the socket

@param[in]   fd        Socket descriptor

@return
  0 on success, negative error code on failure

@note

  - Dependencies
    - None

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QCLOSE)
(
  int fd,
  int ret
);

/*===========================================================================
  FUNCTION  qshutdown
===========================================================================*/
/*!
@brief

  Shuts down a socket

@param[in]   fd        Socket descriptor
@param[in]   how       QSHUTRD (or 0) - Stop receiving packets
                       QSHUTWR (or 1) - Stop transmitting packets
                       QSHUTRDWR (or 2) - Stop both receiving and transmitting

@return
  0 on success  negative error code on failure.

@note

  - Dependencies
    - None

  - Side Effects
    - shutting down both RD and WR will have the same effect as qclose()
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QSHUTDOWN)
(
  int fd,
  int how,
  int ret
);

/*===========================================================================
  FUNCTION  ipcr_find_name
===========================================================================*/
/*!
@brief

 Finds all ports with the associated name

@param[in]   fd        Caller's file descriptor
@param[in]   name      Name of the port
@param[out]  addrs     (Optional, can be NULL, num_entries is assumed
                       to be 0) Pointer to array of addresses to store 
                       the address of found ports with matching name.
@param[out]  instances (Optional, can be NULL) Pointer to array of 
                       instance IDs of the names found (Useful if
                       IPCR_FLAGS_ANY_INSTANCE is used to get the
                       instance ID of the found address). Note, the
                       array must allow the same number of entries 
                       as 'addrs'
@param[inout]num_entires (Optional, can be NULL, input assumed to be 0)
                         Input the size of the array 'addrs' and
                         if provided, 'instances'.
                         Output, the number of entries filled.
@param[in]   flags     0 for an exact match on the provided
                       TYPE and INSTANCE pair.
                       IPCR_FLAGS_ANY_INSTANCE to match just
                       the TYPE.

@return
  Number of services found upon success, negative error code on failure.

@note

  - Dependencies
    - The user must hold a valid file descriptor toward IPC Router.
      (return of qsocket(AF_IPC_ROUTER, *, *)

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_IPCR_FIND_NAME)
(
  int fd,
  ipcr_name_t *name,
  struct qsockaddr_ipcr *addrs,
  unsigned int *instances,
  unsigned int *num_entries, 
  unsigned int flags,
  int ret
);

/*===========================================================================
  FUNCTION  ipcr_find_sname
===========================================================================*/
/*!
@brief

 Finds all ports with the associated name

@param[in]   fd        Caller's file descriptor
@param[in]   name      Name of the port
@param[out]  addrs     (Optional, can be NULL, num_entries is assumed
                       to be 0) Pointer to array of addresses to store 
                       the address of found ports with matching name.
@param[inout]num_entires (Optional, can be NULL, input assumed to be 0)
                         Input the size of the array 'addrs' and
                         if provided, 'instances'.
                         Output, the number of entries filled.
@param[in]   flags     0 (Currently unused)

@return
  Number of services found upon success, negative error code on failure.

@note

  - Dependencies
    - The user must hold a valid file descriptor toward IPC Router.
      (return of qsocket(AF_IPC_ROUTER, *, *)

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_IPCR_FIND_SNAME)
(
  int fd,
  char *name,
  struct qsockaddr_ipcr *addrs,
  unsigned int *num_entries, 
  unsigned int flags,
  int ret
);

/*=============================================================================
  FUNCTION  qmi_csi_register
=============================================================================*/
/*!
@brief
  Register a service with the QCSI infrastructure.

@param[in]  service_obj         Object containing meta information to
                                encode/decode the messages.
@param[in]  service_connect     Callback to register each client with the
                                service.
@param[in]  service_disconnect  Callback to unregister each client from
                                service.
@param[in]  service_process_req Callback that handles the incoming requests.
@param[in]  service_cookie      User data.
@param[out] service_provider    Handle that infra provides to represent this
                                service connection.
@retval    QMI_CSI_NO_ERR       Success
@retval    QMI_CSI_.....        Look into the enumeration qmi_csi_error for
                                the error values.
*/
/*=========================================================================*/

typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_REGISTER)
(
 qmi_idl_service_object_type               service_obj,
 qmi_csi_connect                           service_connect,
 qmi_csi_disconnect                        service_disconnect,
 qmi_csi_process_req                       service_process_req,
 void                                      *service_cookie,
 qmi_csi_os_params                         *os_params,
 qmi_csi_service_handle                    *service_provider,
 qmi_csi_error                              ret
 );


/*=============================================================================
  FUNCTION  qmi_csi_register_with_options
=============================================================================*/
/*!
@brief
  Register a service with the QCSI infrastructure.

@param[in]  service_obj         Object containing meta information to
                                encode/decode the messages.
@param[in]  service_connect     Callback to register each client with the
                                service.
@param[in]  service_disconnect  Callback to unregister each client from
                                service.
@param[in]  service_process_req Callback that handles the incoming requests.
@param[in]  service_cookie      User data.
@param[in]  options             Options as defined by qmi_csi_options
@param[out] service_provider    Handle that infra provides to represent this
                                service connection.
@retval    QMI_CSI_NO_ERR       Success
@retval    QMI_CSI_.....        Look into the enumeration qmi_csi_error for
                                the error values.
*/
/*=========================================================================*/

typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_REGISTER_WITH_OPTIONS)
(
 qmi_idl_service_object_type               service_obj,
 qmi_csi_connect                           service_connect,
 qmi_csi_disconnect                        service_disconnect,
 qmi_csi_process_req                       service_process_req,
 void                                      *service_cookie,
 qmi_csi_os_params                         *os_params,
 qmi_csi_options                           *options,
 qmi_csi_service_handle                    *service_provider,
 qmi_csi_error                              ret
 );

/*=============================================================================
  FUNCTION  qmi_csi_handle_event
=============================================================================*/
/*!
@brief
  Handle event after the server thread receives an event notification.
  Callbacks from qmi_csi_register may be invoked in the server's context.

@param[in] service_provider    Opaque handle that defines the service.
@param[in] os_params           OS-defined parameters such as file handle.

@retval    QMI_CSI_NO_ERR       Success
@retval    Other error codes    Failure
*/
/*=========================================================================*/

typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_HANDLE_EVENT)
(
 qmi_csi_service_handle                    service_provider,
 qmi_csi_os_params                         *os_params,
 qmi_csi_error                              ret
 );

/*=============================================================================
  FUNCTION  qmi_csi_send_resp
=============================================================================*/
/*!
@brief
  Sends a response to the client.

@param[in]  req_handle            Handle used by QCSI infrastructure to
                                  identify the transaction and the destination
                                  client.
@param[in]  msg_id                Message ID for this particular message.
@param[in]  resp_c_struct         C data structure for this response.
@param[in]  resp_c_struct_len     Size of the response c struct.

@retval  QMI_CSI_NO_ERR           Success.
@retval  QMI_CSI_.....            Look into the enumeration qmi_csi_error for
                                  the error values.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_SEND_RESP)
(
 qmi_req_handle     req_handle,
 unsigned int       msg_id,
 void               *resp_c_struct,
 unsigned int       resp_c_struct_len,
 qmi_csi_error      ret
 );

/*=============================================================================
  FUNCTION  qmi_csi_send_resp_raw
=============================================================================*/
/*!
@brief
  Sends a response to the client without encoding.

@param[in]  req_handle            Handle used by QCSI infrastructure to
                                  identify the transaction and the destination
                                  client.
@param[in]  msg_id                Message ID for this particular message.
@param[in]  resp_buf              Response buffer
@param[in]  resp_buf_len          Size of the response buffer

@retval  QMI_CSI_NO_ERR           Success.
@retval  QMI_CSI_.....            Look into the enumeration qmi_csi_error for
                                  the error values.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_SEND_RESP_RAW)
(
 qmi_req_handle     req_handle,
 unsigned int       msg_id,
 void               *resp_buf,
 unsigned int       resp_buf_len,
 qmi_csi_error      ret
 );

/*=============================================================================
  FUNCTION  qmi_csi_send_ind
=============================================================================*/
/*!
@brief
  Sends an indication to the client.

@param[in]  client_handle            Handle used by QCSI infrastructure
                                     to identify the destination client.
@param[in]  msg_id                   Message ID for this particular message.
@param[in]  ind_c_struct             C data strcuture for this indication.
@param[in]  ind_c_struct_len         Size of the indication c struct

@retval    QMI_CSI_NO_ERR            Success.
@retval    QMI_CSI_.....             Look into the enumeration qmi_csi_error for
                                     the error values.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_SEND_IND)
(
 qmi_client_handle  client_handle,
 unsigned int       msg_id,
 void               *ind_c_struct,
 unsigned int       ind_c_struct_len,
 qmi_csi_error      ret
 );

/*=============================================================================
  FUNCTION  qmi_csi_send_ind_raw
=============================================================================*/
/*!
@brief
  Sends an indication to the client without encoding

@param[in]  client_handle            Handle used by QCSI infrastructure
                                     to identify the destination client.
@param[in]  msg_id                   Message ID for this particular message.
@param[in]  ind_buf                  Indication buffer.
@param[in]  ind_buf_len              Size of the indication buffer.

@retval    QMI_CSI_NO_ERR            Success.
@retval    QMI_CSI_.....             Look into the enumeration qmi_csi_error for
                                     the error values.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_SEND_IND_RAW)
(
 qmi_client_handle  client_handle,
 unsigned int       msg_id,
 void               *ind_buf,
 unsigned int       ind_buf_len,
 qmi_csi_error      ret
 );

/*=============================================================================
  FUNCTION  qmi_csi_send_broadcast_ind
=============================================================================*/
/*!
@brief
  Sends a broadcast indication to all registered clients.

@param[in]  service_provider         Handle used by QCSI infrastructure
                                     to identify the service that intends to
                                     send a broadcast message.
@param[in]  msg_id                   Message ID for this particular message.
@param[in]  ind_c_struct             C data structure for this broadcast
                                     indication.
@param[in]  ind_c_struct_len         Size of the broadcast indication

@retval    QMI_CSI_NO_ERR            Success
@retval    QMI_CSI_.....             Look into the enumeration qmi_csi_error for
                                     the error values.
*/
/*=========================================================================*/

typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_SEND_BROADCAST_IND)
(
 qmi_csi_service_handle   service_provider,
 unsigned int             msg_id,
 void                     *ind_c_struct,
 unsigned int             ind_c_struct_len,
 qmi_csi_error            ret
 );

/*=============================================================================
  FUNCTION  qmi_csi_send_broadcast_ind_raw
=============================================================================*/
/*!
@brief
  Sends a raw broadcast indication to all registered clients

@param[in]  service_provider         Handle used by QCSI infrastructure
                                     to identify the service that intends to
                                     send a broadcast message.
@param[in]  msg_id                   Message ID for this particular message.
@param[in]  ind_buf                  broadcast indication buffer
@param[in]  ind_buf_len              Size of the broadcast indication

@retval    QMI_CSI_NO_ERR            Success
@retval    QMI_CSI_.....             Look into the enumeration qmi_csi_error for
                                     the error values.
*/
/*=========================================================================*/

typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_SEND_BROADCAST_IND_RAW)
(
 qmi_csi_service_handle   service_provider,
 unsigned int             msg_id,
 void                     *ind_buf,
 unsigned int             ind_buf_len,
 qmi_csi_error            ret
 );

/*=============================================================================
  FUNCTION  qmi_csi_unregister
=============================================================================*/
/*!
@brief
  Unregisters a server.

@param[in]  service_provider         Handle given in the qmi_csi_register by
                                     the service.
@retval     QMI_CSI_NO_ERR           Success
@retval     QMI_CSI_.....            Look into the enumeration qmi_csi_error for
                                     the error values.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CSI_UNREGISTER)
(
 qmi_csi_service_handle service_provider,
 qmi_csi_error      ret
 );

/*===========================================================================
  FUNCTION  qmi_client_notifier_init
===========================================================================*/
/*!
@brief

  This function is used for initializing a notifier with a service object.
  When a service supporting the service_obj, is registered or de-registered,
  the signal or event object specified in os_params will be set.

@param[in]   service_obj        Service object
@param[in]   os_params          OS-specific parameters. It can be a pointer
                                to event object, or signal mask and TCB
@param[out]  user_handle        Handle used by the infrastructure to
                                identify different clients.                                
@return

  Sets the user_handle and returns QMI_NO_ERR if successful,
  error code if not successful

@note

  - Dependencies
    - None

  - Side Effects
    - A client is created and the signal will be set when a remote server is
      registered. 
    - The caller must make sure that the structure pointed by os_params is
      valid throughout the lifetime of the returned user_handle.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_NOTIFIER_INIT)
(
 qmi_idl_service_object_type               service_obj,
 qmi_client_os_params                      *os_params,
 qmi_client_type                           *user_handle,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_init
===========================================================================*/
/*!
@brief

  This function is used for initializing a connection to a service.

@param[in]   service_info       Pointer to an entry in the service_info array
                                returned by qmi_client_get_service_list()
@param[in]   service_obj        Service object
@param[in]   qmi_client_ind_cb  Indication callback function
@param[in]   ind_cb_data        Indication callback user-data
@param[in]   os_params          OS-specific parameters. It can be a pointer
                                to event object, or signal mask and TCB
@param[out]  user_handle        Handle used by the infrastructure to
                                identify different clients.                                
@return
  Sets the user_handle and returns QMI_NO_ERR if successful,
  error code if not successful
  QMI_SERVICE_ERR if server cannot be reached

@note

  - Dependencies
    - None

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_INIT)
(
 qmi_service_info                          *service_info,
 qmi_idl_service_object_type               service_obj,
 qmi_client_ind_cb                         ind_cb,
 void                                      *ind_cb_data,
 qmi_client_os_params                      *os_params,
 qmi_client_type                           *user_handle,
 qmi_client_error_type ret
);



/*===========================================================================
  FUNCTION  qmi_client_send_raw_msg_async
===========================================================================*/
/*!
@brief
  Sends an asynchronous QMI service message on the specified connection.
  The caller is expected to encode the message before sending it through
  this function.

@param[in]   user_handle        Handle used by the infrastructure to
@param[in]   msg_id             Message ID
@param[in]   req_buf            Pointer to the request
@param[in]   req_buf_len        Length of the request
@param[in]   resp_buf           Pointer to where the response will be stored
@param[in]   resp_buf_len       Length of the response buffer
@param[in]   resp_cb            Callback function to handle the response
@param[in]   resp_cb_data       Callback user-data
@param[out]  txn_handle         Handle used to identify the transaction

@return
  QMI_NO_ERR and sets the transaction handle if function is successful,
  error code otherwise.
  QMI_SERVICE_ERR if server cannot be reached
@note

  - Dependencies
    - User must maintain the validity of the resp_buf throughout the lifetime
      of the txn_handle (Till the response is received or the transaction
      is cancelled).

  - Side Effects
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_SEND_RAW_MSG_ASYNC)
(
 qmi_client_type                   user_handle,
 unsigned int                      msg_id,
 void                              *req_buf,
 unsigned int                      req_buf_len,
 void                              *resp_buf,
 unsigned int                      resp_buf_len,
 qmi_client_recv_raw_msg_async_cb  resp_cb,
 void                              *resp_cb_data,
 qmi_txn_handle                    *txn_handle,
 qmi_client_error_type ret
);


/*===========================================================================
  FUNCTION  qmi_client_send_msg_async
===========================================================================*/
/*!
@brief
  Sends an asynchronous QMI service message on the specified connection.
  The callback functi is expected to encode the message before sending it 
  through this function.

@param[in]   user_handle        Handle used by the infrastructure to
@param[in]   msg_id             Message ID
@param[in]   req_c_struct       Pointer to the request
@param[in]   req_c_struct_len   Length of the request
@param[in]   resp_c_struct      Pointer to where the response will be stored
@param[in]   resp_c_struct_len  Length of the response buffer
@param[in]   resp_cb            Callback function to handle the response
@param[in]   resp_cb_data       Cablback user-data
@param[out]  txn_handle         Handle used to identify the transaction


@return
  QMI_NO_ERR and sets the transaction handle if function is successful,
  error code otherwise.
  QMI_SERVICE_ERR if server cannot be reached

@note

  - Dependencies
    - User must maintain the validity of the resp_c_struct throughout the 
      lifetime of the txn_handle (Till the response is received or the 
      transaction is cancelled).

  - Side Effects
*/
/*=========================================================================*/

typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_SEND_MSG_ASYNC)
(
 qmi_client_type                 user_handle,
 unsigned int                    msg_id,
 void                            *req_c_struct,
 unsigned int                    req_c_struct_len,
 void                            *resp_c_struct,
 unsigned int                    resp_c_struct_len,
 qmi_client_recv_msg_async_cb    resp_cb,
 void                            *resp_cb_data,
 qmi_txn_handle                  *txn_handle,
 qmi_client_error_type ret
);


/*===========================================================================
  FUNCTION  qmi_client_delete_async_txn
===========================================================================*/
/*!
@brief
  Deletes an asynchronous transaction so that it will free resources
  associated with transaction

@param[in]   user_handle        Handle used by the infrastructure to
@param[in]   txn_handle         Handle used to identify the transaction as
                                returned by the send async functions
@return
   QMI_NO_ERR if successful, error code otherwise
@note

  - Dependencies
    - None

  - Side Effects
    - Async response will not be delivered

  Users should be aware of the potential race condition where an
  asynchronous response may be in the process of being handled
  by the "users_rsp_cb" callback up until this routine returns.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_DELETE_ASYNC_TXN)
(
 qmi_client_type  user_handle,
 qmi_txn_handle   async_txn_handle,
 qmi_client_error_type ret
);


/*===========================================================================
  FUNCTION  qmi_client_send_raw_msg_sync
===========================================================================*/
/*!
@brief
  Sends a synchronous QMI service message on the specified connection.
  This function expects the user to encode the message before sending
  and decode the message after receiving.

@param[in]   user_handle        Handle used by the infrastructure to
@param[in]   msg_id             Message ID
@param[in]   req_buf            Pointer to the request
@param[in]   req_buf_len        Length of the request
@param[in]   resp_buf           Pointer to where the response will be stored
@param[in]   resp_buf_len       Length of the response buffer
@param[in]   resp_buf_recv_len  Length of the response received
@param[in]   timeout_msecs      Time-out in milliseconds. 0 = no timeout

@return
  QMI_NO_ERR and sets resp_buf_recv_len if function is successful,
  error code otherwise.
  QMI_SERVICE_ERR if server cannot be reached

@note
  - Dependencies
    - None

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_SEND_RAW_MSG_SYNC)
(
 qmi_client_type           user_handle,
 unsigned int              msg_id,
 void                      *req_buf,
 unsigned int              req_buf_len,
 void                      *resp_buf,
 unsigned int              resp_buf_len,
 unsigned int              *resp_buf_recv_len,
 unsigned int              timeout_msecs,
 qmi_client_error_type ret
);


/*===========================================================================
  FUNCTION  qmi_client_send_msg_sync
===========================================================================*/
/*!
@brief
  Sends a synchronous QMI service message on the specified connection.
  This function provides the encoding/decoding functionality and
  user gets the decoded data in the response structure provided.

@param[in]   user_handle        Handle used by the infrastructure to
@param[in]   msg_id             Message ID
@param[in]   req_c_struct       Pointer to the request
@param[in]   req_c_struct_len   Length of the request
@param[in]   resp_c_struct      Pointer to where the response will be stored
@param[in]   resp_c_struct_len  Length of the response buffer
@param[in]   timeout_msecs      Time-out in milliseconds. 0 = no timeout

@return
  QMI_NO_ERR if function is successful,
  error code otherwise.
  QMI_SERVICE_ERR if server cannot be reached

@note
  - Dependencies
    - None

  - Side Effects
    - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_SEND_MSG_SYNC)
(
 qmi_client_type    user_handle,
 unsigned int       msg_id,
 void               *req_c_struct,
 unsigned int       req_c_struct_len,
 void               *resp_c_struct,
 unsigned int       resp_c_struct_len,
 unsigned int       timeout_msecs,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_release_async
===========================================================================*/
/*!
@brief
  Releases the connection to a service and return immediately without blocking. 
  the provided callback is called when the connection is fully released and 
  it is safe for the caller to release any associated resources.

@param[in]   user_handle        Handle used by the infrastructure to
@param[in]   release_cb         Callback to call when the connection is
                                fully released.
@param[in]   release_cb_data    Cookie to be provided with the callback.

@return
  QMI_NO_ERR if function is successful, error code otherwise.

@note

  - Dependencies
    - None

  - Side Effects
   - None
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_RELEASE_ASYNC)
(
 qmi_client_type       user_handle,
 qmi_client_release_cb release_cb,
 void                  *release_cb_data,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_release
===========================================================================*/
/*!
@brief
  Releases the connection to a service.

@param[in]   user_handle        Handle used by the infrastructure to

@return
  QMI_NO_ERR if function is successful, error code otherwise.

@note

  - Dependencies
    - None

  - Side Effects
   - This call will block till the handle is fully released.
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_RELEASE)
(
 qmi_client_type     user_handle,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_message_encode
===========================================================================*/
/*!
@brief
  Encodes the body (TLV's) of a QMI message from the C data structure to the
  wire format.
@param[in]  user_handle   opaque handle
                          object accessor function from service header file.
@param[in]  message_type  The type of message: request, response, or indication.
@param[in]  message_id    Message ID from IDL.
@param[in]  p_src         Pointer to C structure containing message data.
@param[in]  src_len       Length (size) of p_src C structure in bytes.
@param[out] p_dst         Pointer to beginning of first TLV in message.
@param[in]  dst_len       Length of p_dst buffer in bytes.
@param[out] dst_decoded_len Pointer to the return value, the length of
                          encoded message (to be filled in as the length
                          field in the QMI header).

@retval    QMI_NO_ERR     Success
@retval    QMI_IDL_...    Error, see error codes defined in qmi.h*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_MESSAGE_ENCODE)
(
 qmi_client_type                      user_handle,
 qmi_idl_type_of_message_type         req_resp_ind,
 unsigned int                         message_id,
 const void                           *p_src,
 unsigned int                         src_len,
 void                                 *p_dst,
 unsigned int                         dst_len,
 unsigned int                         *dst_encoded_len,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_message_decode
===========================================================================*/
/*!
@brief
  Decodes the body (TLV's) of a QMI message body from the wire format to the
  C structure.

@param[in]  user_handle   opaque  handle
                          object accessor function from service header file.
@param[in]  message_type  The type of message: request, response, or indication.
@param[in]  message_id    Message ID from IDL.
@param[in]  p_src         Pointer to beginning of first TLV in message.
@param[in]  src_len       Length of p_src buffer in bytes.
@param[out] p_dst         Pointer to C structure for decoded data
@param[in]  dst_len       Length (size) of p_dst C structure in bytes.

@retval    QMI_NO_ERR     Success
@retval    QMI_IDL_...    Error, see error codes defined in qmi.h
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_MESSAGE_DECODE)
(
 qmi_client_type                         user_handle,
 qmi_idl_type_of_message_type            req_resp_ind,
 unsigned int                            message_id,
 const void                              *p_src,
 unsigned int                            src_len,
 void                                    *p_dst,
 unsigned int                            dst_len,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_get_service_list
===========================================================================*/
/*!
@brief 
   Retrieves a list of services capable of handling the service object
   @return
   QMI_NO_ERR if function is successful, error code otherwise.

@param[in]      service_obj         Service object
@param[out]     service_info_array  Array to fill
@param[in/out]  num_entries         Number of entries in the array as input
                                    Number of entires filled as output
@param[out]     num_services        Number of known services. If num_services
                                    > num_entries, a larger array may be needed

@note
  
  - Dependencies
    - None

  - Side Effects
   - service_info_array may be filled
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_GET_SERVICE_LIST)
(
 qmi_idl_service_object_type service_obj,
 qmi_service_info *service_info_array,
 unsigned int *num_entries,
 unsigned int *num_services,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_get_service_instance
===========================================================================*/
/*!
@brief 
   Retrieves a service with a specific instance ID capable of handling the 
   service object

@return
   QMI_NO_ERR if function is successful, error code otherwise.

@param[in]      service_obj         Service object
@param[in]      instance_id         Instance ID of the service
                                    Use QMI_CLIENT_INSTANCE_ANY to mention
                                    no preference.
@param[out]     service_info        Service information 

@note
  
  - Dependencies
    - None

  - Side Effects
   - service_info may be written
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_GET_SERVICE_INSTANCE)
(
 qmi_idl_service_object_type service_obj,
 qmi_service_instance instance_id,
 qmi_service_info *service_info,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_get_instance_id
===========================================================================*/
/*!
@brief
  Accessor function for obtaining the instance ID for a specific service_info
  entry

@param[in]   service_info       Pointer to an entry in the service_info array
@param[out]  instance_id        Instance ID of the service_info entry

@return
  Sets the user_handle and returns QMI_NO_ERR if successful,
  error code if not successful
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_GET_INSTANCE_ID)
(
 qmi_service_info *service_info,
 qmi_service_instance *instance_id,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_register_error_cb
===========================================================================*/
/*!
@brief
  Register an service error callback with the user handle (Valid operation
  for connected client handles returned by qmi_client_init only).

@param[in]  user_handle   opaque handle returned by qmi_client_init
@param[in]  err_cb        Pointer to callback function
@param[in]  err_cb_data   User-data

@retval  QMI_NO_ERR       Success
         QMI_SERVICE_ERR  Server has gone down and the callback is invoked
         QMI_CLIENT_TRANSPORT_ERR Non-recoverable error in the transport
         QMI_INTERNAL_ERR Invalid input parameters
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_REGISTER_ERROR_CB)
(
 qmi_client_type user_handle,
 qmi_client_error_cb err_cb,
 void *err_cb_data,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_register_notify_cb
===========================================================================*/
/*!
@brief
  Register a callback to be called upon service events. 
  If there already exists at least one service when this function is
  called, then the framework may call the passed in notify_cb as part 
  of the register operation.

@param[in]  user_handle    opaque handle returned by qmi_client_notifer_init
@param[in]  notify_cb      Pointer to callback function
@param[in]  notify_cb_data User-data

@retval  QMI_NO_ERR       Success
         QMI_INTERNAL_ERR Invalid input parameters
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_REGISTER_NOTIFY_CB)
(
 qmi_client_type user_handle,
 qmi_client_notify_cb notify_cb,
 void *notify_cb_data,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_register_log_cb
===========================================================================*/
/*!
@brief
  Register a callback to be called upon reception and transmission of a
  message. The user may use this functionality to log transactions to
  an area which the user chooses.

@param[in]  user_handle    opaque handle returned by qmi_client_init or
                           qmi_client_init_instance
@param[in]  log_cb         Pointer to callback function
@param[in]  log_cb_data    User-data

@retval  QMI_NO_ERR       Success
         QMI_INTERNAL_ERR Invalid input parameters
*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_REGISTER_LOG_CB)
(
 qmi_client_type user_handle,
 qmi_client_log_cb notify_cb,
 void *log_cb_data,
 qmi_client_error_type ret
);

/*===========================================================================
  FUNCTION  qmi_client_init_instance
===========================================================================*/
/*!
@brief
  Helper blocking function to lookup and initialize a connection with a 
  service with a specific instance ID.

@param[in]   service_obj        Service object
@param[in]   instance_id        Instance ID of the service.
                                Use QMI_CLIENT_INSTANCE_ANY if there is
                                no preference on the instance ID.
@param[in]   ind_cb             Indication callback function
@param[in]   ind_cb_data        Indication callback user-data
@param[in]   os_params          OS-specific parameters. It can be a pointer
                                to event object, or signal mask and TCB
@param[in]   timeout            Time-out in milliseconds. 0 = no timeout
@param[out]  user_handle        Handle used by the infrastructure to
                                identify different clients.                                

@retval  QMI_NO_ERR       Success
         QMI_INTERNAL_ERR Invalid input parameters
         QMI_TIMEOUT_ERR  No service of the required instance_id was found
                          in the time provided by timeout.

@notes
 1. This function internally calls qmi_client_get_service_list() and 
    qmi_client_init() and may also create a notifier client in case
    the service is not already up. 

 2. If a service of the required instance ID is not found, the function may 
    block for a time longer than 'timeout' before returning QMI_TIMEOUT_ERR.
 
 3. If the client does not know the instance ID but still does not want
    to connect with the first instance of the service (QMI_CLIENT_INSTANCE_ANY)
    then it should use qmi_client_get_service_list() and qmi_client_init()
    with the notifier client instead of this helper.

*/
/*=========================================================================*/
typedef EFI_STATUS (EFIAPI* EFI_QMI_CLIENT_INIT_INSTANCE)
(
 qmi_idl_service_object_type service_obj,
 qmi_service_instance        instance_id,
 qmi_client_ind_cb           ind_cb,
 void                        *ind_cb_data,
 qmi_client_os_params        *os_params,
 uint32_t                    timeout,
 qmi_client_type             *user_handle,
 qmi_client_error_type ret
);


/*===========================================================================
  PROTOCOL INTERFACE
===========================================================================*/
/** @ingroup efi_qsocketqmi_protocol
  @par Summary
  QSocket and QMI Protocol interface.

  @par Parameters
  @inputprotoparams{qsocketqmi_proto_params.tex}
*/
typedef struct _EFI_QSOCKETQMI_PROTOCOL {
  UINT64                              Revision;
  EFI_QSOCKET                         IPCRQsocket;
  EFI_QCONNECT                        IPCRQconnect;
  EFI_QBIND                           IPCRQbind;
  EFI_QSENDTO                         IPCRQsendto;
  EFI_QSEND                           IPCRQsend;
  EFI_QRECVFROM                       IPCRQrecvfrom;
  EFI_QRECV                           IPCRQrecv;
  EFI_QGETSOCKOPT                     IPCRQgetsockopt;
  EFI_QSETSOCKOPT                     IPCRQsetsockopt;
  EFI_QPOLL                           IPCRQpoll;
  EFI_QCLOSE                          IPCRQclose;
  EFI_QSHUTDOWN                       IPCRQshutdown;
  EFI_IPCR_FIND_NAME                  IPCRFindname;
  EFI_IPCR_FIND_SNAME                 IPCRFindsname;
  EFI_QMI_CSI_REGISTER                QmiCsiRegister;
  EFI_QMI_CSI_REGISTER_WITH_OPTIONS   QmiCsiRegisterWithOptions;
  EFI_QMI_CSI_HANDLE_EVENT            QmiCsiHandleEvent;
  EFI_QMI_CSI_SEND_RESP               QmiCsiSendResp;
  EFI_QMI_CSI_SEND_RESP_RAW           QmiCsiSendRespRaw;
  EFI_QMI_CSI_SEND_IND                QmiCsiSendInd;
  EFI_QMI_CSI_SEND_IND_RAW            QmiCsiSendIndRaw;
  EFI_QMI_CSI_SEND_BROADCAST_IND      QmiCsiSendBroadcastInd;
  EFI_QMI_CSI_SEND_BROADCAST_IND_RAW  QmiCsiSendBroadcastIndRaw;
  EFI_QMI_CSI_UNREGISTER              QmiCsiUnregister;
  EFI_QMI_CLIENT_NOTIFIER_INIT        QmiClientNotifierInit;
  EFI_QMI_CLIENT_INIT                 QmiClientInit;
  EFI_QMI_CLIENT_SEND_RAW_MSG_ASYNC   QmiClientSendRawMsgAsync;
  EFI_QMI_CLIENT_SEND_MSG_ASYNC       QmiClientSendMsgAsync;
  EFI_QMI_CLIENT_DELETE_ASYNC_TXN     QmiClientDeleteAsyncTxn;
  EFI_QMI_CLIENT_SEND_RAW_MSG_SYNC    QmiClientSendRawMsgSync;
  EFI_QMI_CLIENT_SEND_MSG_SYNC        QmiClientSendMsgSync;
  EFI_QMI_CLIENT_RELEASE_ASYNC        QmiClientReleaseAsync;
  EFI_QMI_CLIENT_RELEASE              QmiClientRelease;
  EFI_QMI_CLIENT_MESSAGE_ENCODE       QmiClientMessageEncode;
  EFI_QMI_CLIENT_MESSAGE_DECODE       QmiClientMessageDecode;
  EFI_QMI_CLIENT_GET_SERVICE_LIST     QmiClientGetServiceList;
  EFI_QMI_CLIENT_GET_SERVICE_INSTANCE QmiClientGetServiceInstance;
  EFI_QMI_CLIENT_GET_INSTANCE_ID      QmiClientGetInstanceId;
  EFI_QMI_CLIENT_REGISTER_ERROR_CB    QmiClientRegisterErrorCb;
  EFI_QMI_CLIENT_REGISTER_NOTIFY_CB   QmiClientRegisterNotifyCb;
  EFI_QMI_CLIENT_REGISTER_LOG_CB      QmiClientRegisterLogCb;
  EFI_QMI_CLIENT_INIT_INSTANCE        QmiClientInitInstance;
}EFI_QSOCKETQMI_PROTOCOL;

#endif /* __EFIQSOCKETQMI_H__ */
