#ifndef _QSOCKET_IPCR_COMMON_H_
#define _QSOCKET_IPCR_COMMON_H_
/******************************************************************************
  @file    qsocket_ipcr_common.h
  @brief   IPC Router protocol specific definitions

  DESCRIPTION

  IPC Router: 
  IPC Router is a connection-less datagram protocol covering the Network
  and Transport layers of the OSI model. It provides a packet delimited
  end-to-end flow control. Any streaming functionalities provided by
  IPC Router are implemented on top of the datagram methods. IPC Router
  also provides a reliable transport to users as it expects reliability
  from it's link layer.

  IPC Router provides a control endpoint to allow services/clients to
  listen on events from the distributed name service.

  IPC Router also provides a distributed name service in order to provide
  location transparency to it's clients

  This header provides a set of socket-like API to to communicate
  over IPC Router.

  Certain Operating systems might need special setup. Please refer
  to qsocket_<os>.h if it exists
  
  ---------------------------------------------------------------------------
  Copyright (c) 2020 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
  ---------------------------------------------------------------------------

 *******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/* NAME bound by an IPC Router socket */
typedef struct {
  uint32_t service;
  uint32_t instance;
} ipcr_name_t;

/* PORT ADDRESS of an IPC Router socket */
typedef struct {
  uint32_t node_id; /* Processor ID */
  uint32_t port_id; /* Port ID */
} ipcr_port_t;

/* IPC Router protocol address type */
struct qsockaddr_ipcr {
  unsigned short sa_family; /* IPCR_FAMILY */
  struct ipcr_addr {
    unsigned char addrtype; /* IPCR_ADDR_PORT or IPCR_ADDR_NAME */
    union {
      ipcr_port_t port_addr; /* Phy address */
      ipcr_name_t port_name; /* Name */
      char        port_sname[32]; /* String name */
    } addr;
  } address; /* IPCR Address type */
  unsigned char reserved;
};

#ifdef __cplusplus
}
#endif

#endif
