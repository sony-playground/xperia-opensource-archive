#ifndef DMA_HW_ERR_H
#define DMA_HW_ERR_H
/*===========================================================================

                DMA_HW_ERR. H

DESCRIPTION
The DMA_HW Err header file. Contains #defines for the various errors we can see in
the DMA_HW driver system.

Copyright 2013 Qualcomm Technologies Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary
===========================================================================*/

/*===========================================================================

  $Header: //components/dev/core.boot/5.1.1/lpugatch.core.boot.5.1.1.olympic_ut/QcomPkg/Include/api/data/ipa/ipa_err.h#1 $ $DateTime: 2021/12/01 12:58:23 $ $Author: lpugatch $

  when        who    what, where, why
  --------    ---    -------------------------------------------------------------
  06/25/13    hs     created file.

===========================================================================*/


#define DMA_HW_SUCCESS                     0          /* success */
#define DMA_HW_EFATAL                   -100          /* fatal error */
#define DMA_HW_EUNKNOWN                 -101          /* general error */
#define DMA_HW_EINVAL                   -102          /* invalid argument */
#define DMA_HW_EPERM                    -103          /* operation not permitted */
#define DMA_HW_ENOTSUP                  -104          /* operation not supported */
#define DMA_HW_CMD_TIMEOUT              -105          /* Command timed-out: no response from DMA_HW HW */
#define DMA_HW_ENOMATCH                 -106          /* No match on lookup      */
#define DMA_HW_ENOSERVICE               -107          /* Cannot reach QMI server */
#define DMA_HW_ENOMEM                   -108          /* Memory Allocation Failed */
#define DMA_HW_EUNEXP_QMI_RESP          -109          /* Unexpected QMI Response */
#define DMA_HW_EINPROGRESS              -110          /* Operation in progress */
#define DMA_HW_EDATA_ACTIVE             -111          /* Data activity detected during suspend operation */
#define DMA_HW_EDESC_FULL               -112          /* Descriptor is full */


#endif /* DMA_HW_ERR_H */
