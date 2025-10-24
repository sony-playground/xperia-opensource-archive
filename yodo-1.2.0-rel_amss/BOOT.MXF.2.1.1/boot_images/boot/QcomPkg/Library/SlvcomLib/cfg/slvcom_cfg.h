/*=============================================================================

                            SLVCOM CFG

 Slave Communication Configuration.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/cfg/slvcom_cfg.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef SLVCOM_CFG_H
#define SLVCOM_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "comdef.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/
/** Read buffer size */
#define SLVCOM_CFG_RD_BUF_SIZE             (0x1000+0x10)

/** Write buffer size */
#define SLVCOM_CFG_WR_BUF_SIZE             (0x1000+0x10)

/** Inactivity timeout in msec */
#define SLVCOM_CFG_MAX_IDEAL_TIMEOUT       (1000)

/** Slave wake try configuration */
#define SLVCOM_CFG_SLAVE_WAKEUP_DELAY_USEC (10)
#define SLVCOM_CFG_SLAVE_WAKEUP_TRY_CNT    (1000)

/** Read ideal bytes */
#define SLVCOM_CFG_READ_IDEAL_BYTES        (3)

/** TZ NS GPIO line */
#define SLVCOM_CFG_GPIO_TZ_NS              41

/** GPIO assertion for slave - refer slvcom_gpio_value_type */
#define SLVCOM_GPIO_ENSECMODE_ASSERTION   SLVCOM_GPIO_VALUE_HIGH
#define SLVCOM_GPIO_DISSECMODE_ASSERTION  SLVCOM_GPIO_VALUE_LOW

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/


/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/


/*=============================================================================

                    PUBLIC FUNCTION DECLARATIONS

=============================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* SLVCOM_CFG_H */
