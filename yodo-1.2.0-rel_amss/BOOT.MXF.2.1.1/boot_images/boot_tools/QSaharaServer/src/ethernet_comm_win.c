/*
 * Copyright (C) 2022 Qualcomm Technologies, Inc. All rights reserved.
 *
 * All data and information contained in or disclosed by this document is
 * confidential and proprietary information of Qualcomm Technologies, Inc. and all
 * rights therein are expressly reserved.  By accepting this material the
 * recipient agrees that this material and the information contained therein
 * is held in confidence and in trust and will not be used, copied, reproduced
 * in whole or in part, nor its contents revealed in any manner to others
 * without the express written permission of Qualcomm Technologies, Inc.
 *
 *
 * ==========================================================================================
 *  Edit History:
 *  YYYY-MM-DD		who		why
 *  -----------------------------------------------------------------------------
 *  2022-07-28          ck              Corrected compilation errors
 *  2022-03-23          ck              Initial release
 *
 *==========================================================================================
 */

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include "common_protocol_defs.h"
#include "comm.h"
#include "kickstart_log.h"
#include "kickstart_utils.h"
#include "transport_protocol.h"
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")

SOCKET client_socket = INVALID_SOCKET;


void ethernet_comm_populate_medium_interface(function_table* Medium)
{
  Medium->initialize_medium = ethernet_transport_init;
  Medium->port_connect      = ethernet_port_connect;
  Medium->port_disconnect   = ethernet_port_disconnect;
  Medium->boot_transport_tx = boot_ethernet_tx_data;
  Medium->boot_transport_rx = boot_ethernet_rx_data;
}


void ethernet_port_disconnect()
{
  int result = 0;

  result = shutdown(client_socket,
                    SD_BOTH);
  if (result == SOCKET_ERROR)
  {
    dbg(LOG_ERROR, "Failure while shutting down socket");
	perror("ethernet_port_disconnect::shutdown");
  }

  closesocket(client_socket);
  WSACleanup();
}


bool ethernet_port_connect(char* port_name)
{
  bool return_value = TRUE;
  int result = 0;
  struct addrinfo * addr_info_result = NULL,  hints;
  WSADATA wsa_data;
  SOCKET listen_socket = INVALID_SOCKET;


  /* Clear and populate hints structure */
  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;


  /* Initialize Winsock */
  result = WSAStartup(MAKEWORD(2, 2),
                      &wsa_data);

  if (result != 0)
  {
    dbg(LOG_ERROR, "Winsock startup FAILURE");
	perror("ethernet_port_connect::WSAStartup");
    return_value = FALSE;
    goto exit;
  }


  /* Create socket */
  result = getaddrinfo(NULL,
                       (PCSTR)com_port.ethernet_port,
                       &hints,
                       &addr_info_result);
  if (result != 0)
  {
    dbg(LOG_ERROR, "Failure getting address info");
	perror("ethernet_port_connect::getaddrinfo");
    WSACleanup();
    return_value = FALSE;
    goto exit;
  }

  listen_socket = socket(addr_info_result->ai_family,
                         addr_info_result->ai_socktype,
                         addr_info_result->ai_protocol);
  if (listen_socket == INVALID_SOCKET)
  {
    dbg(LOG_ERROR, "Failure to create socket");
	perror("ethernet_port_connect::socket");
    freeaddrinfo(addr_info_result);
    WSACleanup();
    return_value = FALSE;
    goto exit;
  }


  /* Bind to socket */
  result = bind(listen_socket,
                addr_info_result->ai_addr,
                (int)addr_info_result->ai_addrlen);
  if (result == SOCKET_ERROR)
  {
    dbg(LOG_ERROR, "Failure to bind socket");
	perror("ethernet_port_connect::bind");
    freeaddrinfo(addr_info_result);
    closesocket(listen_socket);
    WSACleanup();
    return_value = FALSE;
    goto exit;
  }


  /* Listen on socket for connection */
  if (listen(listen_socket,
             SOMAXCONN) == SOCKET_ERROR)
  {
    dbg(LOG_ERROR, "Failure listening to socket");
	perror("ethernet_port_connect::listen");
    closesocket(listen_socket);
    WSACleanup();
    return_value = FALSE;
    goto exit;
  }


  /* Accept connection */  
  client_socket = accept(listen_socket,
                         NULL,
                         NULL);
  if (client_socket == INVALID_SOCKET)
  {
    dbg(LOG_ERROR, "Failure accepting connection");
	perror("ethernet_port_connect::accept");
    closesocket(listen_socket);
    WSACleanup();
    return_value = FALSE;
    goto exit;
  }

  
 exit:
  return return_value;
}


bool boot_ethernet_tx_data(byte * buffer,
                           size_t bytes_to_send)
{
  bool return_value = TRUE;
  int result = 0;
  size_t bytes_sent = 0;
  size_t temp_bytes_to_send = 0;


  /* Validate arguments */
  if (buffer == NULL)
  {
    dbg(LOG_INFO, "boot_ethernet_tx_data called with null buffer pointer");
    return_value = FALSE;
    goto exit;
  }

  if (bytes_to_send == 0)
  {
    dbg(LOG_INFO, "boot_ethernet_tx_data called with 0 bytes to send");
    return_value = FALSE;
    goto exit;
  }

  
  dbg(LOG_INFO, "Transmitting %d bytes", bytes_to_send);

  if (kickstart_options.verbose > 1)
  {
    print_buffer(buffer,
                 bytes_to_send,
                 com_port.BYTES_TO_PRINT);
  }


  while (bytes_sent < bytes_to_send)
  {
    result = send(client_socket,
                  buffer,
                  MIN(bytes_to_send - bytes_sent, com_port.MAX_TO_WRITE),
                  0);
    if (result == SOCKET_ERROR)
    {
      dbg(LOG_ERROR, "Error occurred while writing to socket");
	  perror("boot_ethernet_tx_data::send");
      return_value = FALSE;
      goto exit;
    }

    bytes_sent += result;
    com_port.total_bytes_sent += result;
  }

  dbg(LOG_INFO, "Total bytes sent so far: %d", com_port.total_bytes_sent);

  
 exit:
  return return_value;
}


bool boot_ethernet_rx_data(byte * buffer,
                           size_t bytes_to_read,
                           size_t * bytes_read)
{
  bool return_value = TRUE;
  int result = 0;


  /* Validate required parameters */
  if (buffer == NULL)
  {
    dbg(LOG_INFO, "boot_ethernet_rx_data called with null buffer pointer");
    return_value = FALSE;
    goto exit;
  }

  if (bytes_to_read == 0)
  {
    dbg(LOG_INFO, "boot_ethernet_rx_data called with 0 bytes to read");
    return_value = FALSE;
    goto exit;
  }


  /* Read data from socket */
  result = recv(client_socket,
                buffer,
                MIN(bytes_to_read, com_port.MAX_TO_READ),
                MSG_WAITALL);
  if (result > 0)
  {
    printf("Bytes received: %d\n", result);
  }
  else
  {
    dbg(LOG_ERROR, "Error occurred while reading from socket");
	perror("boot_ethernet_rx_data::recv");
    return_value = FALSE;
    goto exit;
  }


  /* Report bytes read if applicable */
  if (bytes_read != NULL)
  {
    *bytes_read = result;
  }

  
  dbg(LOG_INFO, "Received %d bytes", result);
  com_port.total_bytes_recd += result;

  
  if (kickstart_options.verbose > 1)
  {
    print_buffer(buffer,
                 (size_t)result,
                 com_port.BYTES_TO_PRINT);
  }

 exit:
  return return_value;
}


void ethernet_transport_init()
{
}
