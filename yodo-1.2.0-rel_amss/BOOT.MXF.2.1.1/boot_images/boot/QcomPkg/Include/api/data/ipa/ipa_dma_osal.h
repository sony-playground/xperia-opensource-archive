/*!
  @file
  ipa_dma_osal.h

  @brief
  This file contain the ipa dma API specific for APSS.

*/
/*===========================================================================

  Copyright 2022 QUALCOMM Technologies Incorporated. All Rights Reserved

  Qualcomm Proprietary

  Export of this technology or software is regulated by the U.S. Government.
  Diversion contrary to U.S. law prohibited.

  All ideas, data and information contained in or disclosed by
  this document are confidential and proprietary information of
  QUALCOMM Technologies Incorporated and all rights therein are expressly reserved.
  By accepting this material the recipient agrees that this material
  and the information contained therein are held in confidence and in
  trust and will not be used, copied, reproduced in whole or in part,
  nor its contents revealed in any manner to others without the express
  written permission of QUALCOMM Technologies Incorporated.

===========================================================================*/
/*===========================================================================

                        EDIT HISTORY FOR MODDLE

This section contains comments describing changes made to the module.
Notice that changes are listed in reverse chronological order.

$Header: //components/rel/core.boot/5.1.1/QcomPkg/Include/api/data/ipa/ipa_dma_osal.h#1 $ $DateTime: 2021/07/26 12:51:36 $ $Author: pwbldsvc $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
04/17/22   ms      IPA xbl driver checkin for SDx75
01/02/19   yl      IPA DMA API unification
===========================================================================*/
#ifndef IPA_DMA_OSAL_H
#define IPA_DMA_OSAL_H

/*===========================================================================

                           INCLUDE FILES

===========================================================================*/
#include "ipa_err.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define IPA_DMA_MAX_PER_XFR_SIZE 0x7FFF   /* 32K - 1 */

/*! @brief DMA client type */
typedef enum {
  IPA_DMA_CLIENT_TYPE_MHI_CTRL = 0x0,
  IPA_DMA_CLIENT_TYPE_MHI_DATA = 0x1,
  IPA_DMA_CLIENT_TYPE_MAX
} ipa_dma_client_type_e;

/*! @brief For each DMA client, pre-defined max number of outstanding transfers */
#define IPA_DMA_MAX_OUTSTANDING_XFR_MHI_DATA (128)
#define IPA_DMA_MAX_OUTSTANDING_XFR_MHI_CTRL (128)

#define IPA_DMA_API_SUPPORTED_IPA_DMA_STATE_GET (0) /* Not supported and will always return IPA_DMA_STATE_XFR_READY by default */
#define IPA_DMA_API_SUPPORTED_IPA_DMA_FLUSH (0)
#define IPA_DMA_API_SUPPORTED_IPA_DMA_SET_IRQ_MODE (0)
#define IPA_DMA_API_SUPPORTED_IPA_DMA_POLL (1)

/* is_async and IRQ mode supported on this platform */
#define IPA_DMA_API_SUPPORTED_DMA_CH_ASYNC_IRQ (0)
#define IPA_DMA_API_SUPPORTED_DMA_CH_SYNC_IRQ (0)
#define IPA_DMA_API_SUPPORTED_DMA_CH_SYNC_POLLING (1)
#define IPA_DMA_API_SUPPORTED_DMA_CH_ASYNC_POLLING_IRQ (0)

#ifdef __cplusplus
};
#endif

#endif

