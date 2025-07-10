/*
===========================================================================

FILE:         gpi_cfg.c

DESCRIPTION:  This file implements the GPI Config Data.

===========================================================================

                             Edit History


when       who     what, where, why
--------   ---     -------------------------------------------------------- 
03/30/22   PS      Revision for Clarence
09/29/20   ANL     Initial revision for Clarence.

===========================================================================
             Copyright (c) 2022 QUALCOMM Technologies, Incorporated.
                    All Rights Reserved
                   QUALCOMM Proprietary
===========================================================================
*/

#include "gpitgtcfgdata.h"
#include "msmhwiobase.h"

#define GSI_0_BASE       (QUPV3_0_QUPV3_ID_12_BASE + 0x00004000)
#define GSI_1_BASE       (QUPV3_1_QUPV3_ID_12_BASE + 0x00004000)
#define GSI_SSC_BASE     (LPASS_BASE + 0x00B04000)

const tgt_gpi_config_type  tgt_gpi_config[] =
{
   { TRUE, 0, GSI_0_BASE,   0, { 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287 } },  /* QUP_0 */
   { TRUE, 1, GSI_1_BASE,   0, { 311, 312, 313, 314, 315, 316, 325, 326, 327, 328, 329, 330 } },  /* QUP_1 */
   { TRUE, 3, GSI_SSC_BASE, 0, { 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 459, 460, 461 , 378, 504, 505 } }   /* QUP_SSC */
};

