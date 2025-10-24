/*==============================================================================

GsiDmaLibNull.C

DESCRIPTION
This file contains the null GSI DMA boot related implementation

Copyright (c) 2022, Qualcomm Technologies, Inc. All rights reserved.
==============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 01/21/22   ck      Initial revision

=============================================================================*/

#include "dma_hw.h"


int32 dma_hw_open(dma_hw_ch_param_t *ch_params)
{
  return 0;
}

int32 dma_hw_poll(dma_hw_ch_hdl_t ch_handle)
{
  return 0;
}

int32 dma_hw_init(void)
{
  return 0;
}


int32 dma_hw_deinit(void)
{
  return 0;
}


int32 dma_hw_write(dma_hw_ch_hdl_t ch_handle, dma_hw_req_t *req)
{
  return 0;
}


int32 dma_hw_read(dma_hw_ch_hdl_t ch_handle, dma_hw_req_t *req)
{
  return 0;
}

