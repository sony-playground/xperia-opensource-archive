#ifndef IPA_ERR_H
#define IPA_ERR_H
/*===========================================================================

                IPA_ERR. H

DESCRIPTION
The IPA Err header file. Contains #defines for the various errors we can see in
the IPA driver system.

Copyright 2022 Qualcomm Technologies Incorporated. 
All Rights Reserved.
Qualcomm Confidential and Proprietary
===========================================================================*/

/*===========================================================================

  $Header: //components/rel/core.boot/5.1.1/QcomPkg/Include/api/data/ipa/ipa_err.h#1 $ $DateTime: 2021/07/26 12:51:36 $ $Author: pwbldsvc $

  when        who    what, where, why
  --------    ---    -------------------------------------------------------------
  06/25/13    hs     created file.

===========================================================================*/


#define IPA_SUCCESS                     0          /* success */
#define IPA_EFATAL                   -100          /* fatal error */
#define IPA_EUNKNOWN                 -101          /* general error */
#define IPA_EINVAL                   -102          /* invalid argument */
#define IPA_EPERM                    -103          /* operation not permitted */
#define IPA_ENOTSUP                  -104          /* operation not supported */
#define IPA_CMD_TIMEOUT              -105          /* Command timed-out: no response from IPA HW */
#define IPA_ENOMATCH                 -106          /* No match on lookup      */
#define IPA_ENOSERVICE               -107          /* Cannot reach QMI server */
#define IPA_ENOMEM                   -108          /* Memory Allocation Failed */
#define IPA_EUNEXP_QMI_RESP          -109          /* Unexpected QMI Response */
#define IPA_EINPROGRESS              -110          /* Operation in progress */
#define IPA_EDATA_ACTIVE             -111          /* Data activity detected during suspend operation */
#define IPA_EDESC_FULL               -112          /* Descriptor is full */


#endif /* IPA_ERR_H */
