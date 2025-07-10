/** 
  @file  Spi.h
  @brief SPI header file
*/
/*=============================================================================
  Copyright (c) 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*=============================================================================z
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/24/20   daisond Created

=============================================================================*/

#ifndef __SPI_COMMON_H__
#define __SPI_COMMON_H__

/**
  SPI core passed to the spi_open() function. 
*/
typedef enum {
  SPI_INSTANCE_001,          /**< Instance 01. */
  SPI_INSTANCE_002,          /**< Instance 02. */
  SPI_INSTANCE_003,          /**< Instance 03. */
  SPI_INSTANCE_004,          /**< Instance 04. */
  SPI_INSTANCE_005,          /**< Instance 05. */
  SPI_INSTANCE_006,          /**< Instance 06. */
  SPI_INSTANCE_007,          /**< Instance 07. */
  SPI_INSTANCE_008,          /**< Instance 08. */
  SPI_INSTANCE_009,          /**< Instance 09. */
  SPI_INSTANCE_010,          /**< Instance 10. */
  SPI_INSTANCE_011,          /**< Instance 11. */
  SPI_INSTANCE_012,          /**< Instance 12. */
  SPI_INSTANCE_013,          /**< Instance 13. */
  SPI_INSTANCE_014,          /**< Instance 14. */
  SPI_INSTANCE_015,			 /**< Instance 15. */
  SPI_INSTANCE_016,			 /**< Instance 16. */
  SPI_INSTANCE_017,			 /**< Instance 17. */
  SPI_INSTANCE_018,			 /**< Instance 18. */
  SPI_INSTANCE_019,			 /**< Instance 19. */
  SPI_INSTANCE_020,			 /**< Instance 20. */
  SPI_INSTANCE_021,			 /**< Instance 21. */
  SPI_INSTANCE_022,			 /**< Instance 22. */
  SPI_INSTANCE_023,			 /**< Instance 23. */
  SPI_INSTANCE_024,			 /**< Instance 24. */
  SPI_INSTANCE_MAX,			 /**< Instance Max.*/
} spi_instance;

/**
  Function status codes.
*/
typedef enum {
	 /*parameter and system errors*/
	SPI_SUCCESS  = 0x0000,
    SPI_ERROR,
    SPI_ERROR_INVALID_PARAM,
    SPI_ERROR_HW_INFO_ALLOCATION,
    SPI_ERROR_MEM_ALLOC,
    SPI_ERROR_MUTEX,
    SPI_ERROR_HANDLE_ALLOCATION,
    SPI_ERROR_INVALID_EXECUTION_LEVEL,
	SPI_ERROR_UNSUPPORTED_IN_ISLAND_MODE,
	SPI_ERROR_UNCLOCKED_ACCESS,
	SPI_ERROR_INVALID_FW_VERSION,
	SPI_ERROR_FW_LOAD_FALIURE,
	
	/*FIFO related error */
	SPI_ERROR_INPUT_FIFO_UNDER_RUN,
	SPI_ERROR_INPUT_FIFO_OVER_RUN,
	SPI_ERROR_OUTPUT_FIFO_UNDER_RUN,
	SPI_ERROR_OUTPUT_FIFO_OVER_RUN,
	SPI_ERROR_COMMAND_OVER_RUN,
	SPI_TRANSFER_FORCE_TERMINATED,
	SPI_ERROR_COMMAND_ILLEGAL,
	SPI_ERROR_COMMAND_FAIL,
	SPI_ERROR_INVALID_CMD_OPCODE,

    /*transfer and dma related errors*/
    SPI_ERROR_TRANSFER_TIMEOUT,
    SPI_ERROR_PENDING_TRANSFER,
    SPI_ERROR_DMA_PROCESS_TRE_FAIL,
    SPI_ERROR_DMA_INSUFFICIENT_RESOURCES,
    SPI_ERROR_DMA_EVT_OTHER,
    SPI_ERROR_DMA_QUP_NOTIF,
    SPI_ERROR_DMA_REG_FAIL,
    SPI_ERROR_DMA_DEREG_FAIL,
    SPI_ERROR_DMA_TX_CHAN_ALLOC_FAIL,
    SPI_ERROR_DMA_RX_CHAN_ALLOC_FAIL,
    SPI_ERROR_DMA_EV_CHAN_ALLOC_FAIL,
    SPI_ERROR_DMA_TX_CHAN_START_FAIL,
    SPI_ERROR_DMA_RX_CHAN_START_FAIL,
    SPI_ERROR_DMA_TX_CHAN_STOP_FAIL,
    SPI_ERROR_DMA_RX_CHAN_STOP_FAIL,
    SPI_ERROR_DMA_TX_CHAN_RESET_FAIL,
    SPI_ERROR_DMA_RX_CHAN_RESET_FAIL,
    SPI_ERROR_DMA_TX_CHAN_DEALLOC_FAIL,
    SPI_ERROR_DMA_RX_CHAN_DEALLOC_FAIL,
    SPI_ERROR_DMA_EV_CHAN_DEALLOC_FAIL,

    /*platform errors*/
    SPI_ERROR_PLAT_GET_CONFIG_FAIL,
    SPI_ERROR_PLAT_REG_INT_FAIL,
    SPI_ERROR_PLAT_CLK_ENABLE_FAIL,
    SPI_ERROR_PLAT_GPIO_ENABLE_FAIL,
    SPI_ERROR_PLAT_CLK_DISABLE_FAIL,
    SPI_ERROR_PLAT_GPIO_DISABLE_FAIL,
    SPI_ERROR_PLAT_CLK_SET_FREQ_FAIL,
    SPI_ERROR_PLAT_INTERRUPT_REGISTER,
    SPI_ERROR_PLAT_INTERRUPT_DEREGISTER,
	SPI_ERROR_PLAT_SET_RESOURCE_FAIL,
	SPI_ERROR_PLAT_RESET_RESOURCE_FAIL,

    SPI_ERROR_QDI_ALLOC_FAIL,
    SPI_ERROR_QDI_COPY_FAIL,
    SPI_ERROR_QDI_MMAP_FAIL,
	
	SPI_ERROR_CORE_NOT_OPEN,

    SPI_ERROR_INIT,         				
   
    SPI_ERROR_DEINIT, 						
   
    SPI_ERROR_POWER_ON,						
   
    SPI_ERROR_POWER_OFF,					
   
    SPI_ERROR_BUS_ACQUISITION_TIMEOUT,		
   
    SPI_ERROR_BUSY,							
   
    SPI_ERROR_OPERATION_DENIED,				
   
    SPI_ERROR_OPERATION_FAILED,   			
         
    SPI_ERROR_TRANSFER,						
   
    SPI_ERROR_DRV_FWK_INIT,					
   
    SPI_ERROR_DRV_FWK_NULL_HANDLE			
   
 

} spi_status;

typedef enum
{
   SPI_CLK_NORMAL,     // SPI CLK turned off during idle state
   SPI_CLK_ALWAYS_ON,  // SPI CLK left running during idle state
} SpiClockModeType;

typedef enum
{
   SPI_CLK_IDLE_LOW,   // clock signal is driven low when idle
   SPI_CLK_IDLE_HIGH,  // clock signal is driven high when idle
} SpiClockPolarityType;

typedef enum
{
   SPI_INPUT_FIRST_MODE,   // leading edge of clock is used for sampling input data
   SPI_OUTPUT_FIRST_MODE,  // leading edge of clock is used for driving output data
} SpiShiftModeType;

typedef enum
{
   SPI_CS_ACTIVE_LOW,   // chip select is driven low when asserted
   SPI_CS_ACTIVE_HIGH,  // chip select is driven high when asserted
} SpiCSPolarityType;

typedef enum
{
   SPI_CS_DEASSERT,       // chip select is deasserted between N-bit transfers
   SPI_CS_KEEP_ASSERTED,  // chip select is asserted as long as the core is in the run state
} SpiCSModeType;

typedef enum
{
   SPI_CORE_MODE_SLAVE,   // SPI core is set in slave mode
   SPI_CORE_MODE_MASTER,  // SPI core is set in master mode
} SpiCoreModeType;


typedef enum
{
   SPI_LOOPBACK_DISABLED,  // loopback mode is disabled
   SPI_LOOPBACK_ENABLED,   // loopback mode is enabled
} SpiLoopbackModeType;


typedef struct
{
   SpiClockModeType eClockMode;          // Clock mode type to be used for the SPI core.
                                         // This parameter determines if the Clock could
                                         // be running even if there is no ongoing transfer.
   SpiClockPolarityType eClockPolarity;  // Clock polarity type to be used for the SPI core.
   SpiShiftModeType eShiftMode;          // Shift mode type to be used for SPI core.  This
                                         // parameter specifies whether the SPI core operates
                                         // in OUTPUT or INPUT FIRST Mode. This specifies whether
                                         // the shift register latches the DATA at the input pin
                                         // on the rising or falling edge.
   UINT32 u32DeassertionTime;            // The minimum time delay in nano second, between two
                                         // word(N-bits) transfers.  This sets the minimum time
                                         // in nanoseconds that the chip select is deasserted
                                         // between SPI transfers (in master mode).  The
                                         // deassertion clock ticks will be configured so that
                                         // the deassertion time will be as close as possible to,
                                         // but not less than, the time specified by this
                                         // parameter.
   UINT32 u32MinSlaveFrequencyHz;        // The Minimum frequency above which the spi core
                                         // should be run.  Normally this is set to zero.
   UINT32 u32MaxSlaveFrequencyHz;        // This is desired frequency of operation.  If the core
                                         // cannot run at this frequency, a value below this but
                                         // greater than u32MinSlaveFrequencyHz will be chosen
                                         // depending on the frequencies available in the
                                         // clkregim SPI clock steps configuration.
   SpiCSPolarityType eCSPolarity;        // CS polarity type to be used for the SPI core.  This
                                         // field tells whethere the Chip select is active high
                                         // or active low.
   SpiCSModeType eCSMode;                // CS Mode to be used for the SPI core.  This specifies
                                         // whether the Chip select is asserted through the
                                         // entire Transaction or whether it is deasserted in
                                         // between SPI transfers of each transaction.
   BOOLEAN bHSMode;                      // Flag to specify whether to enable high speed mode.
} SpiDeviceParametersType;


typedef struct
{
   UINT32          nSlaveNumber;  // slave number (which chip select the slave uses)
   SpiCoreModeType eCoreMode;     // specifies wether the core acts as master or slave
} SpiDeviceBoardInfoType;

typedef struct
{
   UINT32              nNumBits;       // number of bits (N) in one logical SPI transfer
   SpiLoopbackModeType eLoopbackMode;  // specifies whether loopback mode is enabled
} SpiTransferParametersType;

typedef struct
{
   SpiDeviceParametersType   deviceParameters;
   SpiDeviceBoardInfoType    deviceBoardInfo;
   SpiTransferParametersType transferParameters;
} SpiDeviceInfoType;

#endif	/* __SPI_COMMON_H__ */
