/** 
  @file  SpiApi.h
  @brief SPI APIs
*/
/*=============================================================================
  Copyright (c) 2014, 2019 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 10/15/19   bn	   SPI driver support for UEFI
 09/23/14   sg     Created

=============================================================================*/

#ifndef __SPIAPI_H__
#define __SPIAPI_H__

#include "SpiDeviceTypes.h"
#include "SpiDevice.h"
#include "Spi_common.h"

typedef enum
{
   SPI_MODE_0,   /*CPOL = 0, CPHA = 0*/
   SPI_MODE_1,   /*CPOL = 0, CPHA = 1*/
   SPI_MODE_2,   /*CPOL = 1, CPHA = 0*/
   SPI_MODE_3,   /*CPOL = 1, CPHA = 1*/
}spi_mode_t;


typedef enum
{
   CS_ACTIVE_LOW,/**< During idle state CS  line is held low*/
   CS_ACTIVE_HIGH,/**< During idle state CS line is held high*/
   CS_ACTIVE_INVALID = 0x7FFFFFFF
}spi_cs_polarity_t;

/*Note - Endian ness - it is unclear  whether we can
 * support this in all (FIFO/GSI) modes !
 * Order in which bytes from tx/rx buffer words are put on the bus.
 */
typedef enum
{
    SPI_NATIVE = 0,
    SPI_LITTLE_ENDIAN = 0,
    SPI_BIG_ENDIAN /* network*/
}spi_byte_order_t;


/* SPI configuration passed to the spi_full_duplex() function. */
typedef struct
{
   spi_mode_t spi_mode;
   spi_cs_polarity_t spi_cs_polarity;
   spi_byte_order_t endianness;
   uint8 spi_bits_per_word;  /*4 <= N <= 32*/
   uint8 spi_slave_index;
   /**< Slave index, beginning at 0, if mulitple SPI devices are connected to the same master
   At most 7 slaves are allowed. If an invalid number (7 or higher) is set, CS
   signal will not be used*/
   uint32 clk_freq_hz;
   /**< Host will set the SPI clk frequency closest to the requested frequency */
   uint8 cs_clk_delay_cycles;
   /*Num of clk cycles to wait after asserting CS before starting txfer*/
   uint8 inter_word_delay_cycles;
   /*Num of clk cycles to wait between SPI words*/
   boolean cs_toggle;
   /*1 = CS deasserts between words
     0 = CS stays asserted between words.*/
   boolean loopback_mode;
   /**<Normally 0. If set, SPI controller will enable loopback mode, used primarily for testing */
} spi_config_t;

typedef struct
{
    uint8  *tx_buf;
    uint8  *rx_buf;
    uint32  len;
    boolean leave_cs_asserted;
}spi_descriptor_t;
/*===========================================================================
  FUNCTION DEFINITIONS
===========================================================================*/
/* spi_open */ 
/** @ingroup spi_open
  @par Summary
  This function is called by the client code to initialize the respective 
  SPI core instance used by the client. On success, spi_handle points to the handle 
  for the SPI core. 
  
  @param[in]  instance              SPI core instance that the client intends to
                                    initialize; see #spi_instance for 
                                    details.
  @param[out] spi_handle            Pointer location to be filled by the
                                    driver with a handle to the core.

  @return
  See #spi_status for details.
*/
spi_status 
spi_open( 
	spi_instance instance, 
	void **spi_handle 
);

/**
  spi_transfer ()

  @brief
  Transfer implementation of EFI_QCOM_SPI_PROTOCOL
 */
spi_status 
spi_transfer( 
		void	*spi_handle,
		SpiDeviceInfoType	*devInfo,
		CONST UINT8	*write_buffer,
		UINT32	write_len,
		UINT8	*read_buffer,
		UINT32	read_len
);


/* spi_close */ 
/** @ingroup spi_close
  @par Summary
  De-initializes the SPI core.

  @param[in] spi_handle             Handle to the SPI core.

  @return
  See #spi_status for details.
*/
spi_status
spi_close(
    void *spi_handle
);

#endif	/* __SPIAPI_H__ */
