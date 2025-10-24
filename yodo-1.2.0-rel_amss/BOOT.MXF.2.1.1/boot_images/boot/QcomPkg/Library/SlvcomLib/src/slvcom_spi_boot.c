/*=============================================================================

                            SLVCOM SPI BOOT

 Slave Communication logging.

 Copyright  2021-2022 Qualcomm Technologies, Inc. All Rights Reserved.
 Qualcomm Technologies, Inc. Confidential and Proprietary.

=============================================================================*/

/*=============================================================================

                         EDIT HISTORY FOR FILE

$Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SlvcomLib/src/slvcom_spi_boot.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
===========================================================================*/


/*=============================================================================

                           INCLUDE FILES

=============================================================================*/
#include "com_dtypes.h"
#include "stdio.h"
#include "SpiApi.h"
#include "SpiDevice.h"
#include "slvcom.h"
#include "slvcom_log.h"
#include "slvcom_os.h"
#include "slvcom_spi.h"
#include <stdlib.h>
#include "DALSys.h"

/*=============================================================================

                         MACRO DECLARATIONS

=============================================================================*/
#undef  SLVCOM_LOG_TAG
#define SLVCOM_LOG_TAG "SPI"

/*=============================================================================

                         TYPE DEFINITIONS

=============================================================================*/
/**
 * SPI state
 */
typedef enum {
  SLVCOM_SPI_STATE_CLOSED = 0,
  SLVCOM_SPI_STATE_OPENED = 1,
} slvcom_spi_state_type;

/*=============================================================================

                       LOCAL DATA DECLARATIONS

=============================================================================*/
/* SPI state */
static slvcom_spi_state_type slvcom_spi_state;

static void *slvcom_spi_handle;

static void *slvcom_spi_uncached_mem_region;

/* SPI config: BLSP4 – mDSP SPI to BG2.0 */
static const spi_instance slvcom_spi_device_id = SPI_INSTANCE_004;

static SpiDeviceInfoType slvcom_spi_config =
{
  {
    /* SpiClockModeType eClockMode */
    SPI_CLK_NORMAL,
    
    /* SpiClockPolarityType eClockPolarity */
    SPI_CLK_IDLE_LOW,

    /* SpiShiftModeType eShiftMode */
    SPI_INPUT_FIRST_MODE,

	/* uint32 u32DeassertionTime */
    0,

	/* uint32 u32MinSlaveFrequencyHz */
    0,

    /* uint32 u32MaxSlaveFrequencyHz */
    4000000,

    /* SpiCSPolarityType eCSPolarity */
    SPI_CS_ACTIVE_LOW,

    /* SpiCSModeType eCSMode */
    SPI_CS_KEEP_ASSERTED,

    /* boolean bHSMode. Flag to specify whether
       to enable high speed mode */
	0
  },

  {
    /* uint32 nSlaveNumber */
    0,

	/* SpiCoreModeType eCoreMode */
	SPI_CORE_MODE_MASTER
  },

  {
    /* uint32  nNumBits */
    8,    

	/* SpiLoopbackModeType  eLoopbackMode */
	SPI_LOOPBACK_DISABLED
  }
  	
};

/*=============================================================================

                     PUBLIC VARIABLE DECLARATIONS

=============================================================================*/


/*=============================================================================

                     LOCAL FUNCTION DEFINITION

=============================================================================*/

/*=============================================================================
  FUNCTION  slvcom_spi_uncached_mem_alloc
=============================================================================*/
/**
 * Allocates un-cached memory for transfer.
 *
 * @param[in]  size      Memory size to allocate
 * @param[out] paddr     Allocated un-cached physical address.
 *
 * @return
 * Allocated un-cached virtual address.
 */
/*===========================================================================*/
static uint8 *slvcom_spi_uncached_mem_alloc(uint32 size, uint8 **paddr)
{
  DALSYS_Malloc(size,(void**)&slvcom_spi_uncached_mem_region);
  
  *paddr = (uint8 *)slvcom_spi_uncached_mem_region;

  return *paddr;
}

/*=============================================================================
  FUNCTION  slvcom_spi_uncached_mem_free
=============================================================================*/
/**
 * Frees un-cached memory.
 *
 * @param
 * None
 *
 * @return
 */
/*===========================================================================*/
static void slvcom_spi_uncached_mem_free(void)
{
  DALSYS_Free(slvcom_spi_uncached_mem_region);
}

/*=============================================================================

                     PUBLIC FUNCTION DEFINITION

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
)
{
  uint8 *virt_addr;
  uint8 *phys_addr;
  int32 err;

  /* Update the state */
  slvcom_spi_state = SLVCOM_SPI_STATE_CLOSED;
  
  /* Allocate the read and write buffers togather */
  virt_addr = slvcom_spi_uncached_mem_alloc(write_buf_len + read_buf_len, &phys_addr);
  *write_buf_phys_addr = phys_addr;
  *write_buf_virt_addr = virt_addr;
  *read_buf_phys_addr  = phys_addr + write_buf_len;
  *read_buf_virt_addr  = virt_addr + write_buf_len;
 
  /* Initialization SPI driver */
  err = spi_open(slvcom_spi_device_id,&slvcom_spi_handle);
  if (err != SPI_SUCCESS)
  {
    SLVCOM_LOG_FATAL(2, "spi_open failed! device_id=%d, err=%d.", slvcom_spi_device_id, err);
  }
}

/*=============================================================================
  FUNCTION  slvcom_spi_deinit
=============================================================================*/
/**
 * Calls spi_close to close the SPI connection. Frees the read and write buffers.
 *
 * @param
 * None
 *
 * @return
 * None
 *
 */
/*===========================================================================*/
void slvcom_spi_deinit(void)
{
  int32 err;

  /* Closing the SPI connection */
  err = spi_close(slvcom_spi_handle);
  if (err != SPI_SUCCESS)
  {
    SLVCOM_LOG_FATAL(1, "spi_close failed! err=%d.", err);
  }

  slvcom_spi_state = SLVCOM_SPI_STATE_CLOSED;
  
  /* Free the read and write buffers */
  slvcom_spi_uncached_mem_free();
}

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
void slvcom_spi_sleep(void)
{
  int32 err;

  if (slvcom_spi_state == SLVCOM_SPI_STATE_OPENED)
  {
    err = spi_close(slvcom_spi_handle);
    if (err != SPI_SUCCESS)
    {
      SLVCOM_LOG_FATAL(1, "spi_close failed! err=%d.", err);
    }
    /* Update the state */
    slvcom_spi_state = SLVCOM_SPI_STATE_CLOSED;
  }
}

/*=============================================================================
  FUNCTION  slvcom_spi_transfer
=============================================================================*/
/**
 * Opens the SPI driver in case it closed, makes SPI transfer.
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
)
{
  //spi_transaction_t wr_info;
  //spi_transaction_t rd_info;

  int32 err;

  SLVCOM_LOG_DBG(4, "spi_xfter write_addr=0x%08X, write_len=%d, read_addr=0x%08X, read_len=%d.", 
        write_buf_virt_addr, write_buf_len, read_buf_virt_addr, read_buf_len);
  
  if (slvcom_spi_state == SLVCOM_SPI_STATE_CLOSED)
  {
    err = spi_open(slvcom_spi_device_id,&slvcom_spi_handle);
    if (err != SPI_SUCCESS)
    {
      SLVCOM_LOG_FATAL(2, "spi_open failed! device_id=%d, err=%d.", slvcom_spi_device_id, err);
      return SLVCOM_ERR_SPI_ERR;
    }
    /* Update the state */
    slvcom_spi_state = SLVCOM_SPI_STATE_OPENED;
  }

  /*wr_info.buf_phys_addr = write_buf_phys_addr;
  wr_info.buf_virt_addr = write_buf_virt_addr;
  wr_info.buf_len       = write_buf_len;
  wr_info.total_bytes   = 0;*/

  /*rd_info.buf_phys_addr = read_buf_phys_addr;
  rd_info.buf_virt_addr = read_buf_virt_addr;
  rd_info.buf_len       = read_buf_len;
  rd_info.total_bytes   = 0;*/

  err = spi_transfer(slvcom_spi_handle,
                        &slvcom_spi_config,
                        write_buf_virt_addr,
                        write_buf_len,
                        read_buf_virt_addr,
                        read_buf_len);
  if (err != SPI_SUCCESS)
  {
    SLVCOM_LOG_FATAL(2, "spi_full_duplex failed! device_id=%d, err=%d.",
          slvcom_spi_device_id, err);
    return SLVCOM_ERR_SPI_ERR;
  }

  return SLVCOM_ERR_NONE;
}

