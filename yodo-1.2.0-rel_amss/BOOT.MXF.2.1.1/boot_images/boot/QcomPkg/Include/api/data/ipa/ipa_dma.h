#ifndef IPA_DMA_H
#define IPA_DMA_H
/*==============================================================================

                IPA_DMA.H

DESCRIPTION
  This file contains the declarations of IPA DMA channels

Copyright 2020-2022 Qualcomm Technologies Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary
==============================================================================*/



/*==============================================================================

                          INCLUDE FILES FOR MODULE

==============================================================================*/

#include "comdef.h"
#include "ipa_err.h"
#include "ipa_dma_osal.h"

/*==============================================================================

                           EXTERNAL TYPE DEFINITIONS

==============================================================================*/

/*!
* @brief User callback function to be called for ASYNC operations
* On success, status is always IPA_SUCCESS.
* Note: Client implementation for callback should be slim and
*       without any sleep functionality such as mutex.
*/
typedef void(*ipa_dma_cb_func_t)(void *user_data, int32 status);

/* This featurization IPA_DMA_LEGACY_MODE is temporary until MHI driver is upgraded to use the 
   Unified IPA DMA API. All the code under IPA_DMA_LEGACY_MODE shall be deleted once MHI driver
   has been upgraded. 
*/
 
#ifndef IPA_DMA_LEGACY_MODE

/*! @brief IPA DMA mechanism state */
typedef enum {
  IPA_DMA_STATE_UNINITIALIZED = 0x0,

  /* IPA driver DMA state where clients may start calling open channel API.
  to open a new channel */
  IPA_DMA_STATE_OPEN_READY = 0x1,
  
  /* IPA driver DMA state, where clients may start to queue up transfers */
  IPA_DMA_STATE_XFR_READY = 0x2,
  
  IPA_DMA_STATE_MAX
} ipa_dma_state_e;

/*! @brief DMA channel IRQ mode type
Int mode (ipa_dma_int_mode_type_e) may be dynamically changed, unlike IRQ mode (ipa_dma_ch_irq_mode_type_e) that may only be decided on channel open.
This dynamic changing is only applicable for channel opened with IPA_DMA_CH_IRQ_MODE_TYPE_POLLING_IRQ mode.
*/
typedef enum {
  IPA_DMA_CH_IRQ_MODE_TYPE_IRQ = 0x0,
  IPA_DMA_CH_IRQ_MODE_TYPE_POLLING = 0x1,
  IPA_DMA_CH_IRQ_MODE_TYPE_POLLING_IRQ = 0x2,
  IPA_DMA_CH_IRQ_MODE_TYPE_MAX
} ipa_dma_ch_irq_mode_type_e;

/*!
* @brief User callback function to be called for IPA DMA state change.
* status: On success, status is always IPA_SUCCESS.
*         No other status is expected to be returned.
* Note: Client implementation is from Interrupt service routine context.
*       Callback implementation must be slim and
*       without any sleep functionality such as mutex.
*/
typedef void(*ipa_dma_state_cb_func_t)(ipa_dma_state_e state, int32 status);
/*! @brief DMA register parameters */
typedef struct {
  ipa_dma_client_type_e client_type; /* */
  boolean is_async; /* TRUE for ASYNC channel, FALSE for sync channel */
  ipa_dma_ch_irq_mode_type_e ch_irq_mode_type; /* Set as IRQ, As only IRQ is supported for now. */
  uint32 size; /* Not in use. Must be 0 */
  ipa_dma_cb_func_t cb; /* For AYNC channel. Callback used to notify on transfer completion */
  ipa_dma_state_cb_func_t cb_state;  /* if non a NULL, this callback will be called to notify on state changes */
  uint32 options; /* 0 - no flags (for future growth) */
  uint32 ch_handle; /* out param */
} ipa_dma_ch_param_t;

/*! @brief DMA transfer request parameters */
typedef struct {
  uint64 host_addr; /* host physical address */
  uint64 device_addr; /* device physical address */
  uint32 size; /* number of bytes to copy. ASSERT(size != 0 && size <= IPA_DMA_MAX_PER_XFR_SIZE) */
  uint32 options; /* 0 - no flags (for future growth) */
  
  /*! @brief 32b transfer descriptor (cookie) to uniquely identify a transfer.
  IPA driver uses this as an IN parameter calling client CB, which was set by client when calling ipa_dma_open.
  ASSERT(user_data != NULL) */
  void *user_data;
} ipa_dma_req_t;
#else

typedef enum {
  IPA_PER_TYPE_INVALID    = 0,
  IPA_PER_TYPE_MHI        = 1,
  IPA_PER_TYPE_HSIC       = 2,
  IPA_PER_TYPE_USB        = 3,
  IPA_PER_MAX_CLIENT_TYPE = 4
}ipa_peripheral_type;

typedef struct {
  ipa_peripheral_type type;
  boolean is_async;
  uint32 size; /* length of the FIFO, number of descriptors */
  ipa_dma_cb_func_t cb;
  uint32 ch_handle; /* out param */
} ipa_dma_ch_param_t;

typedef struct
{
  uint64 host_addr;
  uint64 device_addr;
  uint32 size; /* non-zero */
  uint32 options;
  void *user_data;
} ipa_dma_req_t;
#endif

/* ipa_dma_req_t.size */
#define IPA_DMA_REQ_MAX_SIZE     0x10000  // 64K

/* ipa_dma_req_t.options */
/* IPA_DMA_NO_SUBMIT - is only allowed on async channel
When this flag is TRUE the transfer request is queued in the FIFO, but it isn’t submitted to the DMA
The transfer request is submitted when a new request is issued whose flag is FALSE.
The transfer request is submitted when ipa_dma_flush() function is called
*/
#define IPA_DMA_NO_SUBMIT 0x1

/* IPA_DMA_NO_POLL - only allowed on sync channel
If the flag is set ipa_dma_write() function does not poll driver status for
this particular transfer.
No acknowledge on success or failure can be supplied.
This flag is not allowed in call to ipa_dma_read() */
#define IPA_DMA_NO_POLL (0x1<<1)

#define IPA_DMA_ALL_OPTIONS (IPA_DMA_NO_SUBMIT | IPA_DMA_NO_POLL)

#define IPA_DMA_TRANSFER_RING_NUM_ELEMENTS        0x80

/*==============================================================================

EXTERNAL FUNCTION DEFINITIONS

==============================================================================*/

/*============================================================================== 
  FUNCTION : ipa_dma_open()
  ==============================================================================*/
/*! 
  @brief
 
FUNCTION ipa_dma_open()

DESCRIPTION
  This function is used to open DMA channel

PARAMETERS
  type - ipa_dma_client_type_e
  is_async - whether the channel is asynchronous, otherwise - synchronous
  size - 0 (deprecated)
  cb -  In a case the channel is asynchronous the callback function is
    triggered when the transfer on the channel was finished
  ch_handle - OUT parameter.
    handle associated with DMA channel. To be used when calling IPA DMA
    read/write routines

RETURN VALUE
  0 IPA_SUCCESS - on success
  IPA_EINVAL - invalid parameters
  IPA_EUNKNOWN - DMA API cannot be used yet
  IPA_EFATAL - DMA was unable to process request.

DEPENDENCIES
  This is called only after IPA is clocked. Caller should ensure that this
  precondition is met.

SIDE EFFECTS
  None
*/

int32 ipa_dma_open(ipa_dma_ch_param_t *param);

/*=============================================================================

  FUNCTION:  ipa_dma_close

=============================================================================*/
/*!
    @brief
    This function is used to close DMA channel.

    @param handle - DMA channel handle received from ipa_dma_close function.

    @return
    @retval IPA_SUCCESS        On success
    @retval IPA_ERR_FAIL       On unrecoverable error

    @dependencies
    This may be called only after IPA SW init is completed.
*/
int32 ipa_dma_close(uint64 ch_handle);

/*=============================================================================

  FUNCTION:  ipa_dma_host_to_device

=============================================================================*/
/*!
    @brief
    This function is used to copy data from host space buffer to
    device space buffer. Transfer size limitations: IPA_DMA_MAX_PER_XFR_SIZE

    @param handle - DMA channel handle received from ipa_dma_open function.
    @param req - request to transfer. See ipa_dma_req_t for details.

    @return
    @retval IPA_SUCCESS            On successful queuing request
    @retval IPA_ERR_FAIL           On unrecoverable error
    @retval IPA_ERR_EDESC_FULL     On channel full

    @dependencies
    This may be called only after IPA is clocked, calling ipa_vote().
    Caller should ensure that this precondition is met.
*/
int32 ipa_dma_host_to_device(uint64 ch_handle, ipa_dma_req_t *req);

/*=============================================================================

  FUNCTION:  ipa_dma_device_to_host

=============================================================================*/
/*!
    @brief
    This function is used to copy data from device space buffer
    to host space buffer. Transfer size limitations: IPA_DMA_MAX_PER_XFR_SIZE

    @param handle - DMA channel handle received from ipa_dma_open function.
    @param req - request to transfer. See ipa_dma_req_t for details.

    @return
    @retval IPA_SUCCESS            On successful queuing request
    @retval IPA_ERR_FAIL           On unrecoverable error
    @retval IPA_ERR_EDESC_FULL     On channel full

    @dependencies
    This may be called only after IPA is clocked, calling ipa_vote().
    Caller should ensure that this precondition is met.
*/
int32 ipa_dma_device_to_host(uint64 ch_handle, ipa_dma_req_t *req);

/*============================================================================== 
 
  FUNCTION:  ipa_dma_flush

=============================================================================*/
/*!
    @brief
FUNCTION ipa_dma_flush() -- deprecated API

DESCRIPTION
  This function is used to flush data 
  For async channel:
    Submits to DMA the transfer requests pending in FIFO (See flag IPA_DMA_NO_SUBMIT)
  Sync channel:
    Polls all requests that were inserted using IPA_DMA_NO_POLL flag
  When ipa_dma_flush() is called on empty FIFO an error is returned (IPA_EUNKNOWN)

PARAMETERS
  ch_handle - handle associated with DMA channel.

RETURN VALUE
  0 IPA_SUCCESS - on success
  IPA_EINVAL - invalid parameters
  IPA_EUNKNOWN - is called on empty FIFO an error is returned
  IPA_EFATAL - the operation failed

DEPENDENCIES
  This is called only after IPA is clocked. Caller should ensure that this
  precondition is met.

SIDE EFFECTS
  None
==============================================================================*/
int32 ipa_dma_flush(uint64 ch_handle);

/*============================================================================== 
   
  FUNCTION:  ipa_dma_poll

=============================================================================*/
/*!
    @brief
 
FUNCTION ipa_dma_poll()

DESCRIPTION
This function is allowed to be called only when the channel works in polling mode
This function is used to poll for transfer completions

For each completed request with non-NULL user_data callback CB will be called with
user_data as parameter
For each completed request with NULL user_data callback CB will not be invoked

PARAMETERS
ch_handle - handle associated with DMA channel.

RETURN VALUE
IPA_DMA_SUCCESS - on success
IPA_DMA_ERROR - the operation failed
IPA_DMA_EINVAL - the channel is synchronous or asynchronous but not working in
IPA_DMA_ASYNC_INT_MODE_POLL

DEPENDENCIES
This is called only after IPA is clocked. Caller should ensure that this
precondition is met.

SIDE EFFECTS
None
==============================================================================*/
int32 ipa_dma_poll(uint64 ch_handle);

#ifdef IPA_DMA_LEGACY_MODE

/* Legacy APIs have been retained as wrappers around the new APIs 
   ipa_hw_init -> renamed to ipa_dma_hw_init()
   ipa_dma_deinit --> renamed to ipa_dma_hw_deinit()
   ipa_dma_read --> ipa_dma_host_to_device ()
   ipa_dma_write --> ipa_dma_device_to_host()
*/

void ipa_hw_init(void);
int32 ipa_dma_deinit(void);
int32 ipa_dma_write(uint64 ch_handle, ipa_dma_req_t *req);
int32 ipa_dma_read(uint64 ch_handle, ipa_dma_req_t *req);

#endif // IPA_DMA_LEGACY

#endif

