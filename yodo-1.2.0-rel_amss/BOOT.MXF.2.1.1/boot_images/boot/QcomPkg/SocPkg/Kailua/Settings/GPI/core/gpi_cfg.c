/*
===========================================================================

FILE:         gpi_cfg.c

DESCRIPTION:  This file implements the GPI Config Data.

===========================================================================

                             Edit History


when       who     what, where, why
--------   ---     -------------------------------------------------------- 
09/29/21   BNG     Initial revision for Kailua.

===========================================================================
             Copyright (c) 2021 QUALCOMM Technologies, Incorporated.
                    All Rights Reserved
                   QUALCOMM Proprietary
===========================================================================
*/

#include "gpitgtcfgdata.h"
#include "msmhwiobase.h"

#define GSI_0_BASE       (QUPV3_1_QUPV3_ID_1_BASE + 0x00004000)
#ifdef QUPV3_2_QUPV3_ID_1_BASE 
#define GSI_1_BASE       (QUPV3_2_QUPV3_ID_1_BASE + 0x00004000)
#elif QUPV3_2_QUPV3_ID_2_BASE
#define GSI_1_BASE       (QUPV3_2_QUPV3_ID_2_BASE + 0x00004000)
#endif

#define GSI_SSC_BASE     (LPASS_BASE + 0x01904000)

const tgt_gpi_config_type  tgt_gpi_config[] =
{
   { TRUE, 0, GSI_0_BASE,   0, { 311, 312, 313, 314, 315, 316, 325, 326, 327, 328, 329, 330 } },  /* QUP_0 */
   { TRUE, 1, GSI_1_BASE,   0, { 620, 621, 622, 623, 624, 625, 626, 627, 628, 629, 630, 631 } },  /* QUP_1 */
   { TRUE, 2, GSI_SSC_BASE, 0, { 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 421, 422, 423 , 424, 425, 426 } }   /* QUP_SSC */
};

