#ifndef _QSOCKET_COMMON_H_
#define _QSOCKET_COMMON_H_
/******************************************************************************
  @file    qsocket_common.h
  @brief   Generic Socket-like interface

  DESCRIPTION

  Provides a generic socket like interface currently used for IPC Router.
  If this becomes a generic interface the documentation must change 
  appropriately

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

/*============================================================================
                             TYPES
============================================================================*/

struct qsockaddr {
  unsigned short sa_family;
  char sa_data[14];
};

typedef size_t qsocklen_t;


typedef size_t qnfds_t;

/* Input to pollfd */
struct qpollfd {
  int fd;      /* File descriptor */
  int events;  /* Interested events */
  int revents; /* Returned events */
};


#ifdef __cplusplus
}
#endif

#endif
