/*=============================================================================

                            SLVCOM SPI

 Slave Communication SPI interface

 Copyright  2021 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/inc/slvcom_spi.h#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/

#ifndef SLVCOM_SPI_H
#define SLVCOM_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/


/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_spi_init
=============================================================================*/
/**
 * Makes calls to SPI driver init function. Allocates the read and write
 * buffers for SPI transfer.
 *
 * @param[in]   write_buf_len        SPI Write buffer length.
 * @param[in]   read_buf_len         SPI Read buffer length.
 * @param[out]  write_buf_phys_addr  Write buffer physical address.
 * @param[out]  write_buf_virt_addr  Write buffer virtual address.
 * @param[out]  read_buf_phys_addr   Read buffer physical address.
 * @param[out]  read_buf_virt_addr   Read buffer virtual address.
 *
 * @return
 * None
 *
 */
/*===========================================================================*/
void slvcom_spi_init
(
  uint32 write_buf_len,
  uint32 read_buf_len,
  uint8  **write_buf_phys_addr,
  uint8  **write_buf_virt_addr,
  uint8  **read_buf_phys_addr,
  uint8  **read_buf_virt_addr
);

/*=============================================================================
  FUNCTION  slvcom_spi_deinit
=============================================================================*/
/**
 * Makes calls to SPI driver deinit function. Frees the read and write buffers.
 *
 * @param[in] None
 *
 * @return
 * None
 *
 */
/*===========================================================================*/
void slvcom_spi_deinit(void);

/*=============================================================================
  FUNCTION  slvcom_spi_sleep
=============================================================================*/
/**
 * Makes calls to SPI driver close function.
 *
 * @param[in] None
 *
 * @return
 * None
 *
 */
/*===========================================================================*/
void slvcom_spi_sleep(void);

/*=============================================================================
  FUNCTION  slvcom_spi_transfer
=============================================================================*/
/**
 * Opens the SPI driver in case it closed, makes SPI full duplex transfer.
 *
 * @param[in]  write_buf_phys_addr  Write buffer physical address.
 * @param[in]  write_buf_virt_addr  Write buffer virtual address.
 * @param[in]  write_buf_len        Write buffer length.
 * @param[out] read_buf_phys_addr   Read buffer physical address.
 * @param[out] read_buf_virt_addr   Read buffer virtual address.
 * @param[in]  read_buf_len         Read buffer length.
 *
 * @return
 * SLVCOM_ERR_NONE if function is successful,
 * Otherwise returns error code (see slvcom_err_type enumeration).
 *
 */
/*===========================================================================*/
slvcom_err_type slvcom_spi_transfer
(
  uint8  *write_buf_phys_addr,
  uint8  *write_buf_virt_addr,
  uint32 write_buf_len,
  uint8  *read_buf_phys_addr,
  uint8  *read_buf_virt_addr,
  uint32 read_buf_len
);

#ifdef __cplusplus
}
#endif

#endif /* SLVCOM_SPI_H */
