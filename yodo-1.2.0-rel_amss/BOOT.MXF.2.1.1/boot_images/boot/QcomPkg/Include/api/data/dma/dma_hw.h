#ifndef DMA_HW_H
#define DMA_HW_H
/*==============================================================================

                DMA_HW.H

DESCRIPTION
  This file contains the declarations of IPA DMA channels

Copyright 2020 Qualcomm Technologies Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary
==============================================================================*/



/*==============================================================================

                          INCLUDE FILES FOR MODULE

==============================================================================*/

#include "comdef.h"
#include "dma_hw_err.h"

#define DMA_HW_TRANSFER_RING_NUM_ELEMENTS (0x80)

/*@brief dma ch handle */
typedef void* dma_hw_ch_hdl_t;
/*@brief dma CB function */
typedef void(*dma_cb_func_t)(void *user_data, int32 status);

/*@brief CH type, used as part of ch open parameters */
typedef enum {
  DMA_HW_CH_TYPE_INVALID    = 0,
  DMA_HW_CH_TYPE_MHI        = 1,
  DMA_HW_CH_TYPE_HSIC       = 2,
  DMA_HW_CH_TYPE_USB        = 3,
  DMA_HW_CH_TYPE_ETH        = 4,
  DMA_HW_CH_MAX_CLIENT_TYPE
}dma_hw_ch_type;

typedef struct {
  dma_hw_ch_type ch_type;
  boolean is_async;
  uint32 n_desc; /* length of the FIFO, number of descriptors */
  dma_cb_func_t cb;
  dma_hw_ch_hdl_t ch_handle; /* out param */
} dma_hw_ch_param_t;

/* @brief struct for dma write/read API calls */
typedef struct
{
  uint64 host_addr;
  uint64 device_addr;
  uint32 size; /* non-zero */
  uint32 options;
  void *user_data;
} dma_hw_req_t;

/*============================================================================== 
   
  FUNCTION:  dma_hw_open

=============================================================================*/
/*!
    @brief

DESCRIPTION
This function is used to open a DMA HW CH.

PARAMETERS
ch_params - Channel parametrs for opening a new DMA CH.

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed
DMA_HW_EINVAL - the channel is synchronous or asynchronous but not working in
DMA_HW_ASYNC_INT_MODE_POLL

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 dma_hw_open(dma_hw_ch_param_t *ch_params);

/*============================================================================== 
   
  FUNCTION:  dma_hw_poll

=============================================================================*/
/*!
    @brief

DESCRIPTION
This function is allowed to be called only when the channel works in polling mode
This function is used to poll for transfer completions

For each completed request with non-NULL user_data callback CB will be called with
user_data as parameter
For each completed request with NULL user_data callback CB will not be invoked

PARAMETERS
ch_handle - handle associated with DMA channel.

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed
DMA_HW_EINVAL - the channel is synchronous or asynchronous but not working in
DMA_HW_ASYNC_INT_MODE_POLL

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 dma_hw_poll(dma_hw_ch_hdl_t ch_handle);


/*============================================================================== 
   
  FUNCTION:  dma_hw_init

=============================================================================*/
/*!
    @brief
 
FUNCTION dma_hw_init()

DESCRIPTION
This Function intializes the DMA HW,
Must be called before write/read/poll operations


RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 dma_hw_init(void);

/*============================================================================== 
   
  FUNCTION:  dma_hw_deinit

=============================================================================*/
/*!
    @brief
 
DESCRIPTION
This Function de-intializes the DMA HW,
 write/read/poll operations shall not be called adter this function is called


RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 dma_hw_deinit(void);


/*============================================================================== 
   
  FUNCTION:  dma_hw_write

=============================================================================*/
/*!
    @brief

DESCRIPTION
This Function sends a write request to DMA HW

PARAMETERS
ch_handle - handle associated with DMA channel.
req - Parameters of the read request

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 dma_hw_write(dma_hw_ch_hdl_t ch_handle, dma_hw_req_t *req);


/*============================================================================== 
   
  FUNCTION:  dma_hw_read

=============================================================================*/
/*!
    @brief

DESCRIPTION
This Function sends a read request to DMA HW

PARAMETERS
ch_handle - handle associated with DMA channel.
req - Parameters of the read request

RETURN VALUE
DMA_HW_SUCCESS - on success
DMA_HW_ERROR - the operation failed

DEPENDENCIES

SIDE EFFECTS
None
==============================================================================*/
int32 dma_hw_read(dma_hw_ch_hdl_t ch_handle, dma_hw_req_t *req);

#endif /* DMA_HW_H */
