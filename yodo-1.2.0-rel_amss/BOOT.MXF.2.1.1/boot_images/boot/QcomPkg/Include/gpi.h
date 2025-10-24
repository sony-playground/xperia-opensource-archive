#ifndef __GPI_H__
#define __GPI_H__

/**
  @file  gpi.h
  @brief GPI public data structures and APIs.

*/
/*
===============================================================================

Edit History

$Header:

when       who     what, where, why
--------   ---     ------------------------------------------------------------
01/24/18   ah      File modified for Hana.

===============================================================================
              Copyright (c) 2016-2020 QUALCOMM Technologies, Inc.
                         All Rights Reserved.
            Qualcomm Technologies Proprietary and Confidential.
===============================================================================
*/

#include "comdef.h"
#include <gpi_common.h>

#ifdef GPI_ST
#include "rex.h"
#include "cortex-m3.h"
#endif

#ifdef GPI_DALSYS
#include "DALStdDef.h"
#endif

/* *********************************************************************************************** */
/*                                         DEFINITIONS                                             */
/* *********************************************************************************************** */

#define MAX_NUM_GPI_RING_ELEM                         16

#define GPI_PROTOCOL_TYPE                             0x2

#ifndef PACKED
#define PACKED __packed
#endif

#define GPI_CHAIN__MASK                               0x1
#define GPI_CHAIN__SHIFT                              0x0

#define GPI_IEOB__MASK                                0x100
#define GPI_IEOB__SHIFT                               0x8

#define GPI_IEOT__MASK                                0x200
#define GPI_IEOT__SHIFT                               0x9

#define GPI_BEI__MASK                                 0x400
#define GPI_BEI__SHIFT                                0xA

#define GPI_MAJOR__MASK                               0xF00000
#define GPI_MAJOR__SHIFT                              0x14
#define TRE_INVALID_MAJOR                             0x0
#define TRE_NOOP_MAJOR                                0x0
#define TRE_DMA_W_BUFFER_MAJOR                        0x1
#define TRE_DMA_W_SGL_MAJOR                           0x1
#define TRE_DMA_IMM_MAJOR                             0x1
#define TRE_GO_MAJOR                                  0x2
#define TRE_CONFIG_0_MAJOR                            0x2
#define TRE_CONFIG_1_MAJOR                            0x2
#define TRE_CONFIG_2_MAJOR                            0x2
#define TRE_CONFIG_3_MAJOR                            0x2
#define TRE_LOCK_MAJOR                                0x3
#define TRE_UNLOCK_MAJOR                              0x3

#define GPI_MINOR__MASK                               0xF0000
#define GPI_MINOR__SHIFT                              0x10
#define TRE_INVALID_MINOR                             0x0
#define TRE_NOOP_MINOR                                0x1
#define TRE_DMA_W_BUFFER_MINOR                        0x0
#define TRE_DMA_IMM_MINOR                             0x1
#define TRE_DMA_W_SGL_MINOR                           0x2
#define TRE_GO_MINOR                                  0x0
#define TRE_CONFIG_0_MINOR                            0x2
#define TRE_CONFIG_1_MINOR                            0x3
#define TRE_CONFIG_2_MINOR                            0x4
#define TRE_CONFIG_3_MINOR                            0x5
#define TRE_LOCK_MINOR                                0x0
#define TRE_UNLOCK_MINOR                              0x1

/* DMA TREs */
#define GPI_TRE_DMA_W_BUFFER_PTR__MASK                0xFFFFFFFF
#define GPI_TRE_DMA_W_BUFFER_PTR__SHIFT               0x0
#define GPI_TRE_DMA_W_BUFFER_LENGTH__MASK             0xFFFFFF
#define GPI_TRE_DMA_W_BUFFER_LENGTH__SHIFT            0x0

#define GPI_TRE_DMA_W_SGL_PTR__MASK                   0xFFFFFFFF
#define GPI_TRE_DMA_W_SGL_PTR__SHIFT                  0x0
#define GPI_TRE_DMA_W_SGL_LENGTH__MASK                0xFFFF
#define GPI_TRE_DMA_W_SGL_LENGTH__SHIFT               0x0

#define GPI_TRE_DMA_IMM_DATA__MASK                    0xFFFFFFFF
#define GPI_TRE_DMA_IMM_DATA__SHIFT                   0x0
#define GPI_TRE_DMA_IMM_LENGTH__MASK                  0xF
#define GPI_TRE_DMA_IMM_LENGTH__SHIFT                 0x0

/* SPI Configuration TREs */
#define GPI_TRE_SPI_GO_CMD__MASK                      0x1F
#define GPI_TRE_SPI_GO_CMD__SHIFT                     0x0
#define GPI_TRE_SPI_GO_CS__MASK                       0x700
#define GPI_TRE_SPI_GO_CS__SHIFT                      0x8
#define GPI_TRE_SPI_GO_FLAGS__MASK                    0xFF000000
#define GPI_TRE_SPI_GO_FLAGS__SHIFT                   0x18
#define GPI_TRE_SPI_GO_FLAGS_PRE_CMD_DELAY__SHIFT     0x0
#define GPI_TRE_SPI_GO_FLAGS_TSTAMP_BEFORE__SHIFT     0x1
#define GPI_TRE_SPI_GO_FLAGS_FRAG__SHIFT              0x2
#define GPI_TRE_SPI_GO_FLAGS_TSTAMP_AFTER__MASK       0x3
#define GPI_TRE_SPI_GO_FLAGS_POST_CMD_DELAY__MASK     0x4
#define GPI_TRE_SPI_GO_RX_LENGTH__MASK                0xFFFFFF
#define GPI_TRE_SPI_GO_RX_LENGTH__SHIFT               0x0

#define GPI_TRE_SPI_CONFIG_0_WORD_SZ__MASK            0x1F
#define GPI_TRE_SPI_CONFIG_0_WORD_SZ__SHIFT           0x0
#define GPI_TRE_SPI_CONFIG_0_FLAGS__MASK              0x3F00
#define GPI_TRE_SPI_CONFIG_0_FLAGS__SHIFT             0x8
#define GPI_TRE_SPI_CONFIG_0_FLAGS_LOOPBACK__SHIFT    0x0
#define GPI_TRE_SPI_CONFIG_0_FLAGS_HS__SHIFT          0x1
#define GPI_TRE_SPI_CONFIG_0_FLAGS_CS_POLARITY__SHIFT 0x2
#define GPI_TRE_SPI_CONFIG_0_FLAGS_CS_TOGGLE__SHIFT   0x3
#define GPI_TRE_SPI_CONFIG_0_FLAGS_CPHA__SHIFT        0x4
#define GPI_TRE_SPI_CONFIG_0_FLAGS_CPOL__SHIFT        0x5
#define GPI_TRE_SPI_CONFIG_0_PACKING__MASK            0xFF000000
#define GPI_TRE_SPI_CONFIG_0_PACKING__SHIFT           0x18

#define GPI_TRE_SPI_CONFIG_0_INTER_WORD_DELAY__MASK   0xFF
#define GPI_TRE_SPI_CONFIG_0_INTER_WORD_DELAY__SHIFT  0x0
#define GPI_TRE_SPI_CONFIG_0_CS_CLK_DELAY__MASK       0x1F00
#define GPI_TRE_SPI_CONFIG_0_CS_CLK_DELAY__SHIFT      0x8
#define GPI_TRE_SPI_CONFIG_0_INTER_TRANSF_DELAY__MASK 0xFFFF0000
#define GPI_TRE_SPI_CONFIG_0_INTER_TRANSF_DELAY__SHIFT 0x10

#define GPI_TRE_SPI_CONFIG_0_CLCK_DIV__MASK            0xFFF
#define GPI_TRE_SPI_CONFIG_0_CLCK_DIV__SHIFT           0x0
#define GPI_TRE_SPI_CONFIG_0_CLCK_SRC__MASK            0xF0000
#define GPI_TRE_SPI_CONFIG_0_CLCK_SRC__SHIFT           0x10

/* UART Configuration TREs */
#define GPI_TRE_UART_GO_CMD__MASK                      0x1F
#define GPI_TRE_UART_GO_CMD__SHIFT                     0x0

#define GPI_TRE_UART_CONFIG_0_CH_SIZE__MASK            0x7
#define GPI_TRE_UART_CONFIG_0_CH_SIZE__SHIFT           0x0
#define GPI_TRE_UART_CONFIG_0_STOP__MASK               0x18
#define GPI_TRE_UART_CONFIG_0_STOP__SHIFT              0x3
#define GPI_TRE_UART_CONFIG_0_PARITY__MASK             0xE0
#define GPI_TRE_UART_CONFIG_0_PARITY__SHIFT            0x5
#define GPI_TRE_UART_CONFIG_0_FLAGS__MASK              0x300
#define GPI_TRE_UART_CONFIG_0_FLAGS__SHIFT             0x8
#define GPI_TRE_UART_CONFIG_0_PACKING__MASK            0xFF000000
#define GPI_TRE_UART_CONFIG_0_PACKING__SHIFT           0x18
#define GPI_TRE_UART_CONFIG_0_RX_STALE_TO__MASK        0xFFFFF
#define GPI_TRE_UART_CONFIG_0_RX_STALE_TO__SHIFT       0x0
#define GPI_TRE_UART_CONFIG_0_CLK_DIV__MASK            0xFFF
#define GPI_TRE_UART_CONFIG_0_CLK_DIV__SHIFT           0x0

/* I2C Configuration TREs */
#define GPI_TRE_I2C_GO_CMD__MASK                       0x1F
#define GPI_TRE_I2C_GO_CMD__SHIFT                      0x0
#define GPI_TRE_I2C_GO_SLAVE_ID__MASK                  0x7F00
#define GPI_TRE_I2C_GO_SLAVE_ID__SHIFT                 0x8
#define GPI_TRE_I2C_GO_FLAGS__MASK                     0xFF000000
#define GPI_TRE_I2C_GO_FLAGS__SHIFT                    0x18
#define GPI_TRE_I2C_GO_FLAGS_PRE_CMD_DELAY__SHIFT      0x0
#define GPI_TRE_I2C_GO_FLAGS_TIMESTAMP_BEFORE__SHIFT   0x1
#define GPI_TRE_I2C_GO_FLAGS_STOP_STRETCH__SHIFT       0x2
#define GPI_TRE_I2C_GO_FLAGS_TIMESTAMP_AFTER__SHIFT    0x3
#define GPI_TRE_I2C_GO_FLAGS_POST_CMD_DELAY__SHIFT     0x4
#define GPI_TRE_I2C_GO_FLAGS_IGNORE_ADDR_NACK__SHIFT   0x5
#define GPI_TRE_I2C_GO_FLAGS_RX_ACK__SHIFT             0x6
#define GPI_TRE_I2C_GO_FLAGS_BYPASS_ADDR_PHASE__SHIFT  0x7
#define GPI_TRE_I2C_GO_RX_LENGTH__MASK                 0xFFFFFF
#define GPI_TRE_I2C_GO_RX_LENGTH__SHIFT                0x0

#define GPI_TRE_I2C_CONFIG_0_T_LOW__MASK               0xFF
#define GPI_TRE_I2C_CONFIG_0_T_LOW__SHIFT              0x0
#define GPI_TRE_I2C_CONFIG_0_T_HIGH__MASK              0xFF00
#define GPI_TRE_I2C_CONFIG_0_T_HIGH__SHIFT             0x8
#define GPI_TRE_I2C_CONFIG_0_T_CYCLE__MASK             0xFF0000
#define GPI_TRE_I2C_CONFIG_0_T_CYCLE__SHIFT            0x10
#define GPI_TRE_I2C_CONFIG_0_PACKING__MASK             0xFF000000
#define GPI_TRE_I2C_CONFIG_0_PACKING__SHIFT            0x18
#define GPI_TRE_I2C_CONFIG_0_NOISE_REJ_LEVEL__MASK     0xFF
#define GPI_TRE_I2C_CONFIG_0_NOISE_REJ_LEVEL__SHIFT    0x0
#define GPI_TRE_I2C_CONFIG_0_INTER_TRANSF_DELAY__MASK  0xFFFF0000
#define GPI_TRE_I2C_CONFIG_0_INTER_TRANSF_DELAY__SHIFT 0x10
#define GPI_TRE_I2C_CONFIG_0_CLCK_DIV__MASK            0xFFF
#define GPI_TRE_I2C_CONFIG_0_CLCK_DIV__SHIFT           0x0
#define GPI_TRE_I2C_CONFIG_0_CLCK_SRC__MASK            0xF0000
#define GPI_TRE_I2C_CONFIG_0_CLCK_SRC__SHIFT           0x10

/* I3C Configuration TREs */
#define GPI_TRE_I3C_GO_CMD__MASK                       0x1F
#define GPI_TRE_I3C_GO_CMD__SHIFT                      0x0
#define GPI_TRE_I3C_GO_SLAVE_ID__MASK                  0x7F00
#define GPI_TRE_I3C_GO_SLAVE_ID__SHIFT                 0x8
#define GPI_TRE_I3C_GO_CCC__MASK                       0xFF0000
#define GPI_TRE_I3C_GO_CCC__SHIFT                      0x10
#define GPI_TRE_I3C_GO_FLAGS__MASK                     0xFF000000
#define GPI_TRE_I3C_GO_FLAGS__SHIFT                    0x18
#define GPI_TRE_I3C_GO_FLAGS_PRE_CMD_DELAY__SHIFT      0x0
#define GPI_TRE_I3C_GO_FLAGS_TIMESTAMP_BEFORE__SHIFT   0x1
#define GPI_TRE_I3C_GO_FLAGS_STOP_STRETCH__SHIFT       0x2
#define GPI_TRE_I3C_GO_FLAGS_TIMESTAMP_AFTER__SHIFT    0x3
#define GPI_TRE_I3C_GO_FLAGS_POST_CMD_DELAY__SHIFT     0x4
#define GPI_TRE_I3C_GO_FLAGS_IGNORE_ADDR_NACK__SHIFT   0x5
#define GPI_TRE_I3C_GO_FLAGS_RX_ACK__SHIFT             0x6
#define GPI_TRE_I3C_GO_FLAGS_BYPASS_ADDR_PHASE__SHIFT  0x7

#define GPI_TRE_I3C_GO_I3C_FLAGS__MASK                 0xF
#define GPI_TRE_I3C_GO_I3C_FLAGS__SHIFT                0x0
#define GPI_TRE_I3C_GO_I3C_FLAGS_USE_7E__SHIFT         0x0
#define GPI_TRE_I3C_GO_I3C_FLAGS_IBI_CONTROL__SHIFT    0x1
#define GPI_TRE_I3C_GO_I3C_FLAGS_CONT_MODE__SHIFT      0x2
#define GPI_TRE_I3C_GO_RX_LENGTH__MASK                 0xFFFFFF
#define GPI_TRE_I3C_GO_RX_LENGTH__SHIFT                0x0

#define GPI_TRE_I3C_CONFIG_0_T_LOW__MASK               0xFF
#define GPI_TRE_I3C_CONFIG_0_T_LOW__SHIFT              0x0
#define GPI_TRE_I3C_CONFIG_0_T_HIGH__MASK              0xFF00
#define GPI_TRE_I3C_CONFIG_0_T_HIGH__SHIFT             0x8
#define GPI_TRE_I3C_CONFIG_0_T_CYCLE__MASK             0xFF0000
#define GPI_TRE_I3C_CONFIG_0_T_CYCLE__SHIFT            0x10
#define GPI_TRE_I3C_CONFIG_0_PACKING__MASK             0x3000000
#define GPI_TRE_I3C_CONFIG_0_PACKING__SHIFT            0x18
#define GPI_TRE_I3C_CONFIG_0_SCALE__MASK               0x18000000
#define GPI_TRE_I3C_CONFIG_0_SCALE__SHIFT              0x1B

#define GPI_TRE_I3C_CONFIG_0_I3C_T_HIGH__MASK          0xFF
#define GPI_TRE_I3C_CONFIG_0_I3C_T_HIGH__SHIFT         0x0
#define GPI_TRE_I3C_CONFIG_0_I3C_T_CYCLE__MASK         0xFF00
#define GPI_TRE_I3C_CONFIG_0_I3C_T_CYCLE__SHIFT        0x8
#define GPI_TRE_I3C_CONFIG_0_CMD_DELAY__MASK           0xFFFF0000
#define GPI_TRE_I3C_CONFIG_0_CMD_DELAY__SHIFT          0x10

#define GPI_TRE_I3C_CONFIG_0_CLCK_DIV__MASK            0xFF
#define GPI_TRE_I3C_CONFIG_0_CLCK_DIV__SHIFT           0x0
#define GPI_TRE_I3C_CONFIG_0_CLCK_SRC__MASK            0xF0000
#define GPI_TRE_I3C_CONFIG_0_CLCK_SRC__SHIFT           0x10

/* Lock TREs */
#define GPI_TRE_LOCK_PROTOCOL__MASK                    0x1
#define GPI_TRE_LOCK_PROTOCOL__SHIFT                   0x0

/* Scatter/Gather List Entry */
#define GPI_SGL_ENTRY_BUF_PTR_1__MASK                  0xFFFFFFFF
#define GPI_SGL_ENTRY_BUF_PTR_1__SHIFT                 0x0
#define GPI_SGL_ENTRY_BUF_PTR_2__MASK                  0xFFFFFFFF
#define GPI_SGL_ENTRY_BUF_PTR_2__SHIFT                 0x0
#define GPI_SGL_ENTRY_BUF_LEN__MASK                    0xFFFFF
#define GPI_SGL_ENTRY_BUF_LEN__SHIFT                   0x0



/* *********************************************************************************************** */
/*                                               MACROS                                            */
/* *********************************************************************************************** */

#define GPI_GET_TRE_TYPE(_major, _minor)   (((_major) << 4) | (_minor))

#define GPI_FIELD_MASK(_FIELD)                (GPI_##_FIELD##__MASK)
#define GPI_FIELD_SHIFT(_FIELD)               (GPI_##_FIELD##__SHIFT)
#define GPI_SUBFIELD_SHIFT(_FIELD,_SUBFIELD)  (SHIFT(_FIELD##_##_SUBFIELD))

/* DMA w. buffer */
#define GPI_BUILD_DMA_W_BUFFER_TRE_0(_PTR)                            \
   (((_PTR) << GPI_FIELD_SHIFT(TRE_DMA_W_BUFFER_PTR)) & GPI_FIELD_MASK(TRE_DMA_W_BUFFER_PTR))
#define GPI_BUILD_DMA_W_BUFFER_TRE_1(_PTR)                            \
   (((_PTR) << GPI_FIELD_SHIFT(TRE_DMA_W_BUFFER_PTR)) & GPI_FIELD_MASK(TRE_DMA_W_BUFFER_PTR))
#define GPI_BUILD_DMA_W_BUFFER_TRE_2(_LENGTH)                         \
   (((_LENGTH) << GPI_FIELD_SHIFT(TRE_DMA_W_BUFFER_LENGTH)) & GPI_FIELD_MASK(TRE_DMA_W_BUFFER_LENGTH))

/* DMA w. S/G list */
#define GPI_BUILD_DMA_W_SGL_TRE_0(_PTR)                            \
   (((_PTR) << GPI_FIELD_SHIFT(TRE_DMA_W_SGL_PTR)) & GPI_FIELD_MASK(TRE_DMA_W_SGL_PTR))
#define GPI_BUILD_DMA_W_SGL_TRE_1(_PTR)                            \
   (((_PTR) << GPI_FIELD_SHIFT(TRE_DMA_W_SGL_PTR)) & GPI_FIELD_MASK(TRE_DMA_W_SGL_PTR))
#define GPI_BUILD_DMA_W_SGL_TRE_2(_LENGTH)                         \
   (((_LENGTH) & GPI_FIELD_MASK(TRE_DMA_W_SGL_LENGTH)) << GPI_FIELD_SHIFT(TRE_DMA_W_SGL_LENGTH))

/* DMA Immediate TRE */
#define GPI_BUILD_DMA_IMM_TRE_0(_DATA)                              \
   (((_DATA) << GPI_FIELD_SHIFT(TRE_DMA_IMM_DATA)) & GPI_FIELD_MASK(TRE_DMA_IMM_DATA))
#define GPI_BUILD_DMA_IMM_TRE_1(_DATA)                              \
   (((_DATA) << GPI_FIELD_SHIFT(TRE_DMA_IMM_DATA)) & GPI_FIELD_MASK(TRE_DMA_IMM_DATA))
#define GPI_BUILD_DMA_IMM_TRE_2(_LENGTH)                            \
   (((_LENGTH) << GPI_FIELD_SHIFT(TRE_DMA_IMM_LENGTH)) & GPI_FIELD_MASK(TRE_DMA_IMM_LENGTH))

/* SPI GO */
#define GPI_BUILD_TRE_SPI_GO_0(_CMD,_CS,_FLAGS)      \
   ((((_CMD) << GPI_FIELD_SHIFT(TRE_SPI_GO_CMD)) & GPI_FIELD_MASK(TRE_SPI_GO_CMD))                | \
    (((_CS) << GPI_FIELD_SHIFT(TRE_SPI_GO_CS)) & GPI_FIELD_MASK(TRE_SPI_GO_CS))                   | \
    (((_FLAGS) << GPI_FIELD_SHIFT(TRE_SPI_GO_FLAGS)) & GPI_FIELD_MASK(TRE_SPI_GO_FLAGS)))
#define GPI_BUILD_TRE_SPI_GO_2(_RX_LENGTH)                             \
   (((_RX_LENGTH) << GPI_FIELD_SHIFT(TRE_SPI_GO_RX_LENGTH)) & GPI_FIELD_MASK(TRE_SPI_GO_RX_LENGTH))

/* SPI CONFIG-0 */
#define GPI_BUILD_TRE_SPI_CONFIG_0_0(_WORD_SZ,_FLAGS,_PACKING)                \
   ((((_WORD_SZ) << GPI_FIELD_SHIFT(TRE_SPI_CONFIG_0_WORD_SZ)) & GPI_FIELD_MASK(TRE_SPI_CONFIG_0_WORD_SZ)) | \
    (((_FLAGS) << GPI_FIELD_SHIFT(TRE_SPI_CONFIG_0_FLAGS)) & GPI_FIELD_MASK(TRE_SPI_CONFIG_0_FLAGS))             | \
    (((_PACKING) << GPI_FIELD_SHIFT(TRE_SPI_CONFIG_0_PACKING)) & GPI_FIELD_MASK(TRE_SPI_CONFIG_0_PACKING)))
#define GPI_BUILD_TRE_SPI_CONFIG_0_1(_INTER_WORD_DELAY,_CS_CLK_DELAY,_INTER_TRANSF_DELAY)                \
   ((((_INTER_WORD_DELAY) << GPI_FIELD_SHIFT(TRE_SPI_CONFIG_0_INTER_WORD_DELAY)) & GPI_FIELD_MASK(TRE_SPI_CONFIG_0_INTER_WORD_DELAY)) | \
    (((_CS_CLK_DELAY) << GPI_FIELD_SHIFT(TRE_SPI_CONFIG_0_CS_CLK_DELAY)) & GPI_FIELD_MASK(TRE_SPI_CONFIG_0_CS_CLK_DELAY))             | \
    (((_INTER_TRANSF_DELAY) << GPI_FIELD_SHIFT(TRE_SPI_CONFIG_0_INTER_TRANSF_DELAY)) & GPI_FIELD_MASK(TRE_SPI_CONFIG_0_INTER_TRANSF_DELAY)))
#define GPI_BUILD_TRE_SPI_CONFIG_0_2(_CLCK_DIV,_CLCK_SRC)                      \
   ((((_CLCK_DIV) << GPI_FIELD_SHIFT(TRE_SPI_CONFIG_0_CLCK_DIV)) & GPI_FIELD_MASK(TRE_SPI_CONFIG_0_CLCK_DIV)) |\
    (((_CLCK_SRC) << GPI_FIELD_SHIFT(TRE_SPI_CONFIG_0_CLCK_SRC)) & GPI_FIELD_MASK(TRE_SPI_CONFIG_0_CLCK_SRC)))

/* UART GO */
#define GPI_BUILD_TRE_UART_GO_0(_CMD)  \
   (((_CMD) << GPI_FIELD_SHIFT(TRE_UART_GO_CMD)) & GPI_FIELD_MASK(TRE_UART_GO_CMD))
#define GPI_BUILD_TRE_UART_GO_1(_TRANS_LENGTH)  \
   (((_TRANS_LENGTH) << GPI_FIELD_SHIFT(TRE_UART_GO_TRANS_LENGTH)) & GPI_FIELD_MASK(TRE_UART_GO_TRANS_LENGTH))
#define GPI_BUILD_TRE_UART_GO_2(_RX_STALE_TO)  \
   (((_RX_STALE_TO) << GPI_FIELD_SHIFT(TRE_UART_GO_RX_STALE_TO)) & GPI_FIELD_MASK(TRE_UART_GO_RX_STALE_TO))

/* UART CONFIG-0 */
#define GPI_BUILD_TRE_UART_CONFIG_0_0(_CH_SIZE,_STOP,_PARITY,_FLAGS,_PACKING)         \
   ((((_CH_SIZE) << GPI_FIELD_SHIFT(TRE_UART_CONFIG_0_CH_SIZE)) & GPI_FIELD_MASK(TRE_UART_CONFIG_0_CH_SIZE)) | \
    (((_STOP) << GPI_FIELD_SHIFT(TRE_UART_GO_STOP)) & GPI_FIELD_MASK(TRE_UART_GO_STOP))  | \
    (((_PARITY) << GPI_FIELD_SHIFT(TRE_UART_GO_PARITY)) & GPI_FIELD_MASK(TRE_UART_GO_PARITY))  | \
    (((_FLAGS) << GPI_FIELD_SHIFT(TRE_UART_GO_FLAGS)) & GPI_FIELD_MASK(TRE_UART_GO_FLAGS))  | \
    (((_PACKING) << GPI_FIELD_SHIFT(TRE_UART_CONFIG_0_PACKING)) & GPI_FIELD_MASK(TRE_UART_CONFIG_0_PACKING)))
#define GPI_BUILD_TRE_UART_CONFIG_0_1(_RX_STALE_TO)          \
   (((_RX_STALE_TO) << GPI_FIELD_SHIFT(TRE_UART_CONFIG_0_RX_STALE_TO)) & GPI_FIELD_MASK(TRE_UART_CONFIG_0_RX_STALE_TO))
#define GPI_BUILD_TRE_UART_CONFIG_0_2(_CLK_DIV)                \
   (((_CLK_DIV) << GPI_FIELD_SHIFT(TRE_UART_CONFIG_0_CLK_DIV)) & GPI_FIELD_MASK(TRE_UART_CONFIG_0_CLK_DIV))

/* I2C GO */
#define GPI_BUILD_TRE_I2C_GO_0(_CMD,_SLAVE_ID,_FLAGS)               \
   ((((_CMD) << GPI_FIELD_SHIFT(TRE_I2C_GO_CMD)) & GPI_FIELD_MASK(TRE_I2C_GO_CMD))     | \
    (((_SLAVE_ID) << GPI_FIELD_SHIFT(TRE_I2C_GO_SLAVE_ID)) & GPI_FIELD_MASK(TRE_I2C_GO_SLAVE_ID))  | \
    (((_FLAGS) << GPI_FIELD_SHIFT(TRE_I2C_GO_FLAGS)) & GPI_FIELD_MASK(TRE_I2C_GO_FLAGS)))
#define GPI_BUILD_TRE_I2C_GO_2(_RX_LENGTH)                      \
   (((_RX_LENGTH) << GPI_FIELD_SHIFT(TRE_I2C_GO_RX_LENGTH)) & GPI_FIELD_MASK(TRE_I2C_GO_RX_LENGTH))

/* I2C CONFIG-0 */
#define GPI_BUILD_TRE_I2C_CONFIG_0_0(_T_LOW,_T_HIGH,_T_CYCLE,_PACKING)         \
   ((((_T_LOW) << GPI_FIELD_SHIFT(TRE_I2C_CONFIG_0_T_LOW)) & GPI_FIELD_MASK(TRE_I2C_CONFIG_0_T_LOW)) | \
    (((_T_HIGH) << GPI_FIELD_SHIFT(TRE_I2C_CONFIG_0_T_HIGH)) & GPI_FIELD_MASK(TRE_I2C_CONFIG_0_T_HIGH)) | \
    (((_T_CYCLE) << GPI_FIELD_SHIFT(TRE_I2C_CONFIG_0_T_CYCLE)) & GPI_FIELD_MASK(TRE_I2C_CONFIG_0_T_CYCLE)) | \
    (((_PACKING) << GPI_FIELD_SHIFT(TRE_I2C_CONFIG_0_PACKING)) & GPI_FIELD_MASK(TRE_I2C_CONFIG_0_PACKING)))
#define GPI_BUILD_TRE_I2C_CONFIG_0_1(_NOISE_REJ_LEVEL,_INTER_TRANSF_DELAY)             \
   ((((_NOISE_REJ_LEVEL) << GPI_FIELD_SHIFT(TRE_I2C_CONFIG_0_NOISE_REJ_LEVEL)) & GPI_FIELD_MASK(TRE_I2C_CONFIG_0_NOISE_REJ_LEVEL)) | \
    (((_INTER_TRANSF_DELAY) << GPI_FIELD_SHIFT(TRE_I2C_CONFIG_0_INTER_TRANSF_DELAY)) & GPI_FIELD_MASK(TRE_I2C_CONFIG_0_INTER_TRANSF_DELAY)))
#define GPI_BUILD_TRE_I2C_CONFIG_0_2(_CLCK_DIV,_CLCK_SRC)                 \
   ((((_CLCK_DIV) << GPI_FIELD_SHIFT(TRE_I2C_CONFIG_0_CLCK_DIV)) & GPI_FIELD_MASK(TRE_I2C_CONFIG_0_CLCK_DIV)) | \
    (((_CLCK_SRC) << GPI_FIELD_SHIFT(TRE_I2C_CONFIG_0_CLCK_SRC)) & GPI_FIELD_MASK(TRE_I2C_CONFIG_0_CLCK_SRC)))

/* I3C GO */
#define GPI_BUILD_TRE_I3C_GO_0(_CMD,_SLAVE_ID,_CCC,_FLAGS)                                                              \
   ((((_CMD)        << GPI_FIELD_SHIFT(TRE_I3C_GO_CMD))         & GPI_FIELD_MASK(TRE_I3C_GO_CMD))                   |   \
    (((_SLAVE_ID)   << GPI_FIELD_SHIFT(TRE_I3C_GO_SLAVE_ID))    & GPI_FIELD_MASK(TRE_I3C_GO_SLAVE_ID))              |   \
    (((_CCC)        << GPI_FIELD_SHIFT(TRE_I3C_GO_CCC))         & GPI_FIELD_MASK(TRE_I3C_GO_CCC))                   |   \
    (((_FLAGS)      << GPI_FIELD_SHIFT(TRE_I3C_GO_FLAGS))       & GPI_FIELD_MASK(TRE_I3C_GO_FLAGS)))

#define GPI_BUILD_TRE_I3C_GO_1(_I3C_FLAGS)                                                                              \
   (((_I3C_FLAGS)   << GPI_FIELD_SHIFT(TRE_I3C_GO_I3C_FLAGS))   & GPI_FIELD_MASK(TRE_I3C_GO_I3C_FLAGS))

#define GPI_BUILD_TRE_I3C_GO_2(_RX_LENGTH)                                                                              \
   (((_RX_LENGTH)   << GPI_FIELD_SHIFT(TRE_I3C_GO_RX_LENGTH))   & GPI_FIELD_MASK(TRE_I3C_GO_RX_LENGTH))

/* I3C CONFIG-0 */
#define GPI_BUILD_TRE_I3C_CONFIG_0_0(_T_LOW,_T_HIGH,_T_CYCLE,_PACKING, _SCALE)                                                  \
   ((((_T_LOW)          << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_T_LOW))         & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_T_LOW))       |   \
    (((_T_HIGH)         << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_T_HIGH))        & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_T_HIGH))      |   \
    (((_T_CYCLE)        << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_T_CYCLE))       & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_T_CYCLE))     |   \
    (((_PACKING)        << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_PACKING))       & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_PACKING))     |   \
    (((_SCALE)          << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_SCALE))         & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_SCALE)))

#define GPI_BUILD_TRE_I3C_CONFIG_0_1(_I3C_T_HIGH,_I3C_T_CYCLE,_CMD_DELAY)                                                        \
   ((((_I3C_T_HIGH)     << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_I3C_T_HIGH))    & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_I3C_T_HIGH)) |   \
    (((_I3C_T_CYCLE)    << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_I3C_T_CYCLE))   & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_I3C_T_CYCLE))|   \
    (((_CMD_DELAY)      << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_CMD_DELAY))     & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_CMD_DELAY)))

#define GPI_BUILD_TRE_I3C_CONFIG_0_2(_CLCK_DIV,_CLCK_SRC)                                                                       \
   ((((_CLCK_DIV)       << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_CLCK_DIV))      & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_CLCK_DIV))    |   \
    (((_CLCK_SRC)       << GPI_FIELD_SHIFT(TRE_I3C_CONFIG_0_CLCK_SRC))      & GPI_FIELD_MASK(TRE_I3C_CONFIG_0_CLCK_SRC)))

/* Control DWORD */
#define GPI_BUILD_TRE_CTRL(_MAJOR,_MINOR,_BEI,_IEOT,_IEOB,_CHAIN)    \
   ((((_MAJOR) << GPI_FIELD_SHIFT(MAJOR)) & GPI_FIELD_MASK(MAJOR)) | \
    (((_MINOR) << GPI_FIELD_SHIFT(MINOR)) & GPI_FIELD_MASK(MINOR)) | \
    (((_BEI) << GPI_FIELD_SHIFT(BEI)) & GPI_FIELD_MASK(BEI))       | \
    (((_IEOT) << GPI_FIELD_SHIFT(IEOT)) & GPI_FIELD_MASK(IEOT))    | \
    (((_IEOB) << GPI_FIELD_SHIFT(IEOB)) & GPI_FIELD_MASK(IEOB))    | \
    (((_CHAIN) << GPI_FIELD_SHIFT(CHAIN)) & GPI_FIELD_MASK(CHAIN)))

/* Scatter/Gather List Entry */
#define GPI_BUILD_SGL_ENTRY(_BUF_PTR_1,_BUF_PTR_2,_LEN)               \
   ((((_BUF_PTR_1) << GPI_FIELD_SHIFT(SGL_ENTRY_BUF_PTR_1)) & GPI_FIELD_MASK(SGL_ENTRY_BUF_PTR_1)) | \
    (((_SLAVE_ID) << GPI_FIELD_SHIFT(SGL_ENTRY_BUF_PTR_2)) & GPI_FIELD_MASK(SGL_ENTRY_BUF_PTR_2))  | \
    (((_LEN) << GPI_FIELD_SHIFT(SGL_ENTRY_BUF_LEN)) & GPI_FIELD_MASK(SGL_ENTRY_BUF_LEN)))
/* *********************************************************************************************** */
/*                                               APIs                                              */
/* *********************************************************************************************** */

/**
 * Registers a client GPI interface.
 *
 * @param[in]    params                GPI interface registration parameters
 *
 * @return       GPI_RETURN_STATUS     Return status.
 */
GPI_RETURN_STATUS gpi_iface_reg(gpi_iface_params *params);

/**
 * De-Registers a client GPI interface.
 *
 * @param[in]    handle            Handle to GPI Interface
 *
 * @return       GPI_RETURN_STATUS     Return status.
 */
GPI_RETURN_STATUS gpi_iface_dereg(GPI_CLIENT_HANDLE handle);

/**
 * Informs GPI of the interface active status.
 *
 * @param[in]    handle            Handle to GPI Interface
 * @param[in]    active            TRUE if interface is active, FALSE otherwise
 *
 * @return       None.
 */
GPI_RETURN_STATUS gpi_iface_active(GPI_CLIENT_HANDLE handle, boolean active);

/**
 * Queries whether a GPI interface is running in interrupt or polling mode.
 *
 * @param[in]        handle            Handle to GPI Interface
 * @param[in, out]   irq_mode          1 if Interface in IRQ mode, 0 otherwise
 *
 * @return       GPI_RETURN_STATUS     Return status.
 */
GPI_RETURN_STATUS gpi_iface_in_irq_mode(GPI_CLIENT_HANDLE handle, uint8 *irq_mode);

/**
 * Enables/Disables a GPI interface IRQ mode.
 *
 * @param[in]    handle           Handle to the GPI Interface
 * @param[in]    irq_en           TRUE to enable IRQ mode, FALSE for polling
 *
 * @return       GPI_RETURN_STATUS     Return status.
 */
GPI_RETURN_STATUS gpi_iface_set_irq_mode(GPI_CLIENT_HANDLE handle, boolean irq_en);

/**
 * @brief A GPI client may call this function to save the QUP registers of a GPII that it owns.
 *        Clients must make sure to turn the specific QUP clocks on similar to what's done during transfer requests. 
 *
 * @param[in]        handle              Handle to GPI Interface
 * @param[in, out]   regs                Register values saved
 *
 * @return         GPI_RETURN_STATUS     Return status.
 *
 */
GPI_RETURN_STATUS gpi_reg_save(GPI_CLIENT_HANDLE handle, gpi_debug_regs *regs);

/**
 * Queries the channel current status.
 *
 * @param[in]         handle           Handle to the GPI Interface
 * @param[in]         chan             Virtual Channel ID
 * @param[in, out]    chan_status      Information about channel current status
 *
 * @return       GPI_RETURN_STATUS     Return status.
 */
GPI_RETURN_STATUS gpi_query_chan_status(GPI_CLIENT_HANDLE handle,
                                        GPI_CHAN_TYPE chan,
                                        chan_status_info * chan_status);

/**
 * Polls a GPI interface.
 * The corresponding callback will be invoked with any available results.
 *
 * @param[in]    handle               GPI client handle
 *
 * @return       GPI_RETURN_STATUS     Return status.
 */
GPI_RETURN_STATUS gpi_iface_poll(GPI_CLIENT_HANDLE handle);

/**
 * Issues a channel command.
 *
 * @param[in]      handle              Handle to GPI Interface
 * @param[in]      chan                Virtual Channel ID
 * @param[in]      cmd_type            Command type
 * @param[in]      user_cmd            GENERIC_CMD_IBI content
 * @param[in]      user_data           Client context data for this command
 *
 * @return       GPI_RETURN_STATUS     Return status.
 */
GPI_RETURN_STATUS gpi_issue_cmd(GPI_CLIENT_HANDLE handle,
                                GPI_CHAN_TYPE chan,
                                GPI_CHAN_CMD cmd_type,
                                uint32            user_cmd,
                                void            * user_data);

/**
 * Process TREs request.
 *
 * @param[in]    tre_request           Request details
 *
 * @return       GPI_RETURN_STATUS     Return status.
 */
GPI_RETURN_STATUS gpi_process_tre(gpi_tre_req *tre_request);

/**
 * Main function to initialize GPI EE, target, and gloabl data structure.
 * To be called from the main task before any GPI request is made.
 *
 * @param[in]    None.
 *
 * @return       None.
 */
void gpi_init(void);

#endif /* __GPI_H__ */
