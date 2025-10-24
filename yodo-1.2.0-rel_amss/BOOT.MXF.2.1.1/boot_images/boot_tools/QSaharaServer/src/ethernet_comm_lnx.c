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
 *  2022-03-23          ck              Initial release
 *
 *==========================================================================================
 */

#include "common_protocol_defs.h"
#include "comm.h"
#include "kickstart_log.h"
#include "kickstart_utils.h"
#include "transport_protocol.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>


int client_socket = 0;


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
  if (close(client_socket))
  {
    dbg(LOG_ERROR, "Failure while shutting down socket");
    perror("ethernet_port_disconnect::close");
  }
}


bool ethernet_port_connect(char* port_name)
{
  bool return_value = true;
  struct sockaddr_in addr_info;
  int listen_socket = 0;


  /* Clear and populate addr_info */
  memset(&addr_info,
         0,
         sizeof(addr_info));

  addr_info.sin_family = AF_INET;
  addr_info.sin_addr.s_addr = htonl(INADDR_ANY);
  addr_info.sin_port = htons(com_port.ethernet_port);

  
  /* Create socket */
  listen_socket = socket(AF_INET,
                         SOCK_STREAM,
                         0);
  if (listen_socket == -1)
  {
    dbg(LOG_ERROR, "Failure to create socket");
    perror("ethernet_port_connect::socket");
    return_value = false;
    goto exit;
  }


  /* Bind to socket */
  if (bind(listen_socket,
           (struct sockaddr*)&addr_info,
           sizeof(addr_info)))
  {
    dbg(LOG_ERROR, "Failure to bind socket");
    perror("ethernet_port_connect::bind");
    close(listen_socket);
    return_value = false;
    goto exit;
  }


  /* Listen on socket for connection */
  if (listen(listen_socket,
             5))
  {
    dbg(LOG_ERROR, "Failure listening to socket");
    perror("ethernet_port_connect::listen");
    close(listen_socket);
    return_value = false;
    goto exit;
  }


  /* Accept connection */  
  client_socket = accept(listen_socket,
                         (struct sockaddr *)NULL,
                         NULL);
  if (client_socket == -1)
  {
    dbg(LOG_ERROR, "Failure accepting connection");
    perror("ethernet_port_connect::accept");
    close(listen_socket);
    return_value = false;
    goto exit;
  }

  
 exit:
  return return_value;
}


bool boot_ethernet_tx_data(byte * buffer,
                           size_t bytes_to_send)
{
  bool return_value = true;
  int result = 0;
  size_t bytes_sent = 0;
  size_t temp_bytes_to_send = 0;


  /* Validate arguments */
  if (buffer == NULL)
  {
    dbg(LOG_INFO, "boot_ethernet_tx_data called with null buffer pointer");
    return_value = false;
    goto exit;
  }

  if (bytes_to_send == 0)
  {
    dbg(LOG_INFO, "boot_ethernet_tx_data called with 0 bytes to send");
    return_value = false;
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
    result = write(client_socket,
                   buffer,
                   MIN(bytes_to_send - bytes_sent, com_port.MAX_TO_WRITE));
    if (result != MIN(bytes_to_send - bytes_sent, com_port.MAX_TO_WRITE))
    {
      dbg(LOG_ERROR, "Error occurred while writing to socket");
      perror("boot_ethernet_tx_data::write");
      return_value = false;
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
  bool return_value = true;
  int result = 0;


  /* Validate required parameters */
  if (buffer == NULL)
  {
    dbg(LOG_INFO, "boot_ethernet_rx_data called with null buffer pointer");
    return_value = false;
    goto exit;
  }

  if (bytes_to_read == 0)
  {
    dbg(LOG_INFO, "boot_ethernet_rx_data called with 0 bytes to read");
    return_value = false;
    goto exit;
  }


  /* Read data from socket */
  result = read(client_socket,
                buffer,
                MIN(bytes_to_read, com_port.MAX_TO_READ));
  if (result == MIN(bytes_to_read, com_port.MAX_TO_READ))
  {
    printf("Bytes received: %d\n", result);
  }
  else
  {
    dbg(LOG_ERROR, "Error occurred while reading from socket");
    perror("boot_ethernet_rx_data::read");
    return_value = false;
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
