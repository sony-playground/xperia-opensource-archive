/**
 * @file QSocketQMI_Dxe.c
 *
 * DXE driver for QSocket and QMI device in UEFI
 */

/*==============================================================================
     Copyright (c) 2021 Qualcomm Technologies, Inc. 
     All rights reserved.
     Qualcomm Confidential and Proprietary
==============================================================================*/

/*===========================================================================

                           EDIT HISTORY FOR FILE


when       who     what, where, why
--------   ---     ----------------------------------------------------------
02/02/21   ar      Created UEFI support code for QSocket and QMI
===========================================================================*/

/*===========================================================================
                        INCLUDE FILES
===========================================================================*/

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIQSocketQMI.h>
#include "com_dtypes.h"
#include <Library/qsocket.h>
#include <Library/qsocket_ipcr.h>

extern void ipc_router_init(void);
extern void qmi_fw_init(void);
/*===========================================================================
                        INTERNAL FUNCTION DEFINITIONS
===========================================================================*/

static EFI_STATUS EFI_qsocket
(
  int domain,
  int type,
  int protocol,
  int ret
)
{
  ret = qsocket(domain, type, protocol);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qconnect
(
  int fd,
  struct qsockaddr *addr,
  qsocklen_t addrlen,
  int ret
)
{
  ret = qconnect(fd, addr, addrlen);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qbind
(
  int fd,
  struct qsockaddr *addr,
  qsocklen_t addrlen,
  int ret
)
{
  ret = qbind(fd, addr, addrlen);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qsendto
(
  int fd,
  void *buf,
  size_t len,
  int flags,
  struct qsockaddr *addr,
  qsocklen_t addrlen,
  int ret
)
{
  ret = qsendto(fd,buf,len,flags,addr,addrlen);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qsend
(
  int fd,
  void *buf,
  size_t len,
  int flags,
  int ret
)
{
  ret = qsend(fd,buf,len,flags);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qrecvfrom
(
  int fd,
  void *buf,
  size_t len,
  int flags,
  struct qsockaddr *addr,
  qsocklen_t *addrlen,
  int ret
)
{
  ret = qrecvfrom(fd,buf,len,flags,addr,addrlen);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qrecv
(
  int fd,
  void *buf,
  size_t len,
  int flags,
  int ret
)
{
  ret = qrecv(fd,buf,len,flags);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qgetsockopt
(
  int fd,
  int level,
  int optname,
  void *optval,
  qsocklen_t *optlen,
  int ret
)
{
  ret = qgetsockopt(fd,level,optname,optval,optlen);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qsetsockopt
(
  int fd,
  int level,
  int optname,
  void *optval,
  qsocklen_t optlen,
  int ret
)
{
  ret = qsetsockopt(fd,level,optname,optval,optlen);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qpoll
(
  struct qpollfd *pfd,
  qnfds_t num,
  int timeout_ms,
  int ret
)
{
  ret = qpoll(pfd,num,timeout_ms);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qclose
(
  int fd,
  int ret
)
{
  ret = qclose(fd);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qshutdown
(
  int fd,
  int how,
  int ret
)
{
  ret = qshutdown(fd,how);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_ipcr_find_name
(
  int fd,
  ipcr_name_t *name,
  struct qsockaddr_ipcr *addrs,
  unsigned int *instances,
  unsigned int *num_entries, 
  unsigned int flags,
  int ret
)
{
  ret = ipcr_find_name(fd,name,addrs,instances,num_entries,flags);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_ipcr_find_sname
(
  int fd,
  char *name,
  struct qsockaddr_ipcr *addrs,
  unsigned int *num_entries, 
  unsigned int flags,
  int ret
)
{
  ret = ipcr_find_sname(fd,name,addrs,num_entries,flags);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

extern void qmi_fw_init(void);


static EFI_STATUS EFI_qmi_csi_register
(
  qmi_idl_service_object_type               service_obj,
  qmi_csi_connect                           service_connect,
  qmi_csi_disconnect                        service_disconnect,
  qmi_csi_process_req                       service_process_req,
  void                                      *service_cookie,
  qmi_csi_os_params                         *os_params,
  qmi_csi_service_handle                    *service_provider,
  qmi_csi_error ret
)
{
  ret = qmi_csi_register( service_obj, service_connect, service_disconnect, service_process_req, service_cookie, os_params, service_provider);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_csi_register_with_options
(
  qmi_idl_service_object_type               service_obj,
  qmi_csi_connect                           service_connect,
  qmi_csi_disconnect                        service_disconnect,
  qmi_csi_process_req                       service_process_req,
  void                                      *service_cookie,
  qmi_csi_os_params                         *os_params,
  qmi_csi_options                           *options,
  qmi_csi_service_handle                    *service_provider,
  qmi_csi_error ret
)
{
  ret = qmi_csi_register_with_options( service_obj, service_connect, service_disconnect, service_process_req, service_cookie, os_params, options, service_provider);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_csi_handle_event
(

  qmi_csi_service_handle                    service_provider,
  qmi_csi_os_params                         *os_params,
  qmi_csi_error ret
)
{
  ret = qmi_csi_handle_event( service_provider, os_params);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}


static EFI_STATUS EFI_qmi_csi_send_resp
(
  qmi_req_handle     req_handle,
  unsigned int       msg_id,
  void               *resp_c_struct,
  unsigned int       resp_c_struct_len,
  qmi_csi_error ret
)
{
  ret = qmi_csi_send_resp( req_handle, msg_id, resp_c_struct, resp_c_struct_len);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_csi_send_resp_raw
(
  qmi_req_handle     req_handle,
  unsigned int       msg_id,
  void               *resp_buf,
  unsigned int       resp_buf_len,
  qmi_csi_error ret
)
{
  ret = qmi_csi_send_resp_raw( req_handle, msg_id, resp_buf, resp_buf_len);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_csi_send_ind
(
  qmi_client_handle  client_handle,
  unsigned int       msg_id,
  void               *ind_c_struct,
  unsigned int       ind_c_struct_len,
  qmi_csi_error ret
)
{
  ret = qmi_csi_send_ind( client_handle, msg_id, ind_c_struct, ind_c_struct_len);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_csi_send_ind_raw
(
  qmi_client_handle  client_handle,
  unsigned int       msg_id,
  void               *ind_buf,
  unsigned int       ind_buf_len,
  qmi_csi_error ret
)
{
  ret = qmi_csi_send_ind_raw( client_handle, msg_id, ind_buf, ind_buf_len);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_csi_send_broadcast_ind
(
  qmi_csi_service_handle   service_provider,
  unsigned int             msg_id,
  void                     *ind_c_struct,
  unsigned int             ind_c_struct_len,
  qmi_csi_error ret
)
{
  ret = qmi_csi_send_broadcast_ind( service_provider, msg_id, ind_c_struct, ind_c_struct_len);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_csi_send_broadcast_ind_raw
(
  qmi_csi_service_handle   service_provider,
  unsigned int             msg_id,
  void                     *ind_buf,
  unsigned int             ind_buf_len,
  qmi_csi_error ret
)
{
  ret = qmi_csi_send_broadcast_ind_raw( service_provider, msg_id, ind_buf, ind_buf_len);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_csi_unregister
(
  qmi_csi_service_handle service_provider,
  qmi_csi_error ret
)
{
  ret = qmi_csi_unregister( service_provider);
  if (ret == 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_notifier_init
(
  qmi_idl_service_object_type               service_obj,
  qmi_client_os_params                      *os_params,
  qmi_client_type                           *user_handle,
  qmi_client_error_type ret
)
{
  ret = qmi_client_notifier_init( service_obj, os_params, user_handle);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_init
(
  qmi_service_info                          *service_info,
  qmi_idl_service_object_type               service_obj,
  qmi_client_ind_cb                         ind_cb,
  void                                      *ind_cb_data,
  qmi_client_os_params                      *os_params,
  qmi_client_type                           *user_handle,
  qmi_client_error_type ret
)
{
  ret = qmi_client_init( service_info, service_obj, ind_cb, ind_cb_data, os_params, user_handle);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_send_raw_msg_async
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
)
{
  ret = qmi_client_send_raw_msg_async( user_handle, msg_id, req_buf, req_buf_len, resp_buf, resp_buf_len, resp_cb, resp_cb_data, txn_handle);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_send_msg_async
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
)
{
  ret = qmi_client_send_msg_async( user_handle, msg_id, req_c_struct, req_c_struct_len, resp_c_struct, resp_c_struct_len, resp_cb, resp_cb_data, txn_handle);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_delete_async_txn
(
  qmi_client_type  user_handle,
  qmi_txn_handle   async_txn_handle,
  qmi_client_error_type ret
)
{
  ret = qmi_client_delete_async_txn( user_handle, async_txn_handle);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_send_raw_msg_sync
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
)
{
  ret = qmi_client_send_raw_msg_sync( user_handle, msg_id, req_buf, req_buf_len, resp_buf, resp_buf_len, resp_buf_recv_len, timeout_msecs);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_send_msg_sync
(
  qmi_client_type    user_handle,
  unsigned int       msg_id,
  void               *req_c_struct,
  unsigned int       req_c_struct_len,
  void               *resp_c_struct,
  unsigned int       resp_c_struct_len,
  unsigned int       timeout_msecs,
  qmi_client_error_type ret
)
{
  ret = qmi_client_send_msg_sync( user_handle, msg_id, req_c_struct, req_c_struct_len, resp_c_struct, resp_c_struct_len, timeout_msecs);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_release_async
(
  qmi_client_type       user_handle,
  qmi_client_release_cb release_cb,
  void                  *release_cb_data,
  qmi_client_error_type ret
)
{
  ret = qmi_client_release_async( user_handle, release_cb, release_cb_data);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_release
(
  qmi_client_type       user_handle,
  qmi_client_error_type ret
)
{
  ret = qmi_client_release( user_handle);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_message_encode
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
)
{
  ret = qmi_client_message_encode( user_handle, req_resp_ind, message_id, p_src, src_len, p_dst, dst_len, dst_encoded_len);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_message_decode
(
  qmi_client_type                      user_handle,
  qmi_idl_type_of_message_type         req_resp_ind,
  unsigned int                         message_id,
  const void                           *p_src,
  unsigned int                         src_len,
  void                                 *p_dst,
  unsigned int                         dst_len,
  qmi_client_error_type ret
)
{
  ret = qmi_client_message_decode( user_handle, req_resp_ind, message_id, p_src, src_len, p_dst, dst_len);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_get_service_list
(
  qmi_idl_service_object_type service_obj,
  qmi_service_info *service_info_array,
  unsigned int *num_entries,
  unsigned int *num_services,
  qmi_client_error_type ret
)
{
  ret = qmi_client_get_service_list( service_obj, service_info_array, num_entries, num_services);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_get_service_instance
(
 qmi_idl_service_object_type service_obj,
 qmi_service_instance instance_id,
 qmi_service_info *service_info,
  qmi_client_error_type ret
)
{
  ret = qmi_client_get_service_instance( service_obj, instance_id, service_info);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_get_instance_id
(
  qmi_service_info *service_info,
  qmi_service_instance *instance_id,
  qmi_client_error_type ret
)
{
  ret = qmi_client_get_instance_id( service_info, instance_id);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_register_error_cb
(
  qmi_client_type user_handle,
  qmi_client_error_cb err_cb,
  void *err_cb_data,
  qmi_client_error_type ret
)
{
  ret = qmi_client_register_error_cb( user_handle, err_cb, err_cb_data);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_register_notify_cb
(
  qmi_client_type user_handle,
  qmi_client_notify_cb notify_cb,
  void *notify_cb_data,
  qmi_client_error_type ret
)
{
  ret = qmi_client_register_notify_cb( user_handle, notify_cb, notify_cb_data);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_register_log_cb
(
  qmi_client_type user_handle,
  qmi_client_log_cb notify_cb,
  void *log_cb_data,
  qmi_client_error_type ret
)
{
  ret = qmi_client_register_log_cb( user_handle, notify_cb, log_cb_data);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}

static EFI_STATUS EFI_qmi_client_init_instance
(
 qmi_idl_service_object_type service_obj,
 qmi_service_instance        instance_id,
 qmi_client_ind_cb           ind_cb,
 void                        *ind_cb_data,
 qmi_client_os_params        *os_params,
 uint32_t                    timeout,
 qmi_client_type             *user_handle,
  qmi_client_error_type ret
)
{
  ret = qmi_client_init_instance( service_obj, instance_id, ind_cb, ind_cb_data, os_params, timeout, user_handle);
  if (ret >= 0) {
    return EFI_SUCCESS;
  } else {
    return EFI_COMPROMISED_DATA;
  }
}


/*===========================================================================
                           INTERNAL DATA STRUCTURES
===========================================================================*/

static EFI_QSOCKETQMI_PROTOCOL QSocketQMIProtocol =
{
  EFI_QSOCKETQMI_PROTOCOL_REVISION,
  EFI_qsocket,
  EFI_qconnect,
  EFI_qbind,
  EFI_qsendto,
  EFI_qsend,
  EFI_qrecvfrom,
  EFI_qrecv,
  EFI_qgetsockopt,
  EFI_qsetsockopt,
  EFI_qpoll,
  EFI_qclose,
  EFI_qshutdown,
  EFI_ipcr_find_name,
  EFI_ipcr_find_sname,
  EFI_qmi_csi_register,
  EFI_qmi_csi_register_with_options,
  EFI_qmi_csi_handle_event,
  EFI_qmi_csi_send_resp,
  EFI_qmi_csi_send_resp_raw,
  EFI_qmi_csi_send_ind,
  EFI_qmi_csi_send_ind_raw,
  EFI_qmi_csi_send_broadcast_ind,
  EFI_qmi_csi_send_broadcast_ind_raw,
  EFI_qmi_csi_unregister,
  EFI_qmi_client_notifier_init,
  EFI_qmi_client_init,
  EFI_qmi_client_send_raw_msg_async,
  EFI_qmi_client_send_msg_async,
  EFI_qmi_client_delete_async_txn,
  EFI_qmi_client_send_raw_msg_sync,
  EFI_qmi_client_send_msg_sync,
  EFI_qmi_client_release_async,
  EFI_qmi_client_release,
  EFI_qmi_client_message_encode,
  EFI_qmi_client_message_decode,
  EFI_qmi_client_get_service_list,
  EFI_qmi_client_get_service_instance,
  EFI_qmi_client_get_instance_id,
  EFI_qmi_client_register_error_cb,
  EFI_qmi_client_register_notify_cb,
  EFI_qmi_client_register_log_cb,
  EFI_qmi_client_init_instance
};

/*===========================================================================
                        EXTERNAL FUNCTION DEFINITIONS
===========================================================================*/
/**
 * Entry point for the Qsocket and QMI DXE driver.
 */
EFI_STATUS EFIAPI QSocketQMIEntryPoint
(
  EFI_HANDLE            ImageHandle,
  EFI_SYSTEM_TABLE     *SystemTable
)
{
  EFI_HANDLE handle = NULL;
  EFI_STATUS status;
  
  /* Init Ipcrtr  */
  ipc_router_init();
  /*Init QMI */
  qmi_fw_init();


  status = gBS->InstallMultipleProtocolInterfaces(&handle,
      &gEfiQSocketQMIProtocolGuid, (void **)&QSocketQMIProtocol, NULL, NULL, NULL );

  return status;
}
