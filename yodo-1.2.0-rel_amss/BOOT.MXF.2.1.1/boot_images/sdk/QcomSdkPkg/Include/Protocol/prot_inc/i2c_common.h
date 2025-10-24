/**
    @file  i2c_common.h
 */
/*=============================================================================
         Copyright (c) 2020 Qualcomm Technologies, Incorporated.
                              All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

#ifndef __I2C_COMMON_H__
#define __I2C_COMMON_H__



/** @defgroup efi_i2c_protocol EFI_I2C_PROTOCOL
 *  @ingroup INTERFACES 
 */
 /** @defgroup  efi_i2c_protocol_prot PROTOCOL
 *  @ingroup efi_i2c_protocol 
 */ 
 /** @defgroup  efi_i2c_protocol_apis APIs
 *  @ingroup efi_i2c_protocol 
 */ 

/** @defgroup  efi_i2c_protocol_data DATA_STRUCTURES
 *  @ingroup efi_i2c_protocol 
 */

/** @ingroup efi_i2c_protocol_data
  Instance of the I2C core that the client wants to use. This instance is
  passed in i2c_open().
*/
typedef enum
{
    I2C_INSTANCE_001 = 1,      /**< Instance 01. */
    I2C_INSTANCE_002,          /**< Instance 02. */
    I2C_INSTANCE_003,          /**< Instance 03. */
    I2C_INSTANCE_004,          /**< Instance 04. */
    I2C_INSTANCE_005,          /**< Instance 05. */
    I2C_INSTANCE_006,          /**< Instance 06. */
    I2C_INSTANCE_007,          /**< Instance 07. */
    I2C_INSTANCE_008,          /**< Instance 08. */
    I2C_INSTANCE_009,          /**< Instance 09. */
    I2C_INSTANCE_010,          /**< Instance 10. */
    I2C_INSTANCE_011,          /**< Instance 11. */
    I2C_INSTANCE_012,          /**< Instance 12. */
    I2C_INSTANCE_013,          /**< Instance 13. */
    I2C_INSTANCE_014,          /**< Instance 14. */
    I2C_INSTANCE_015,          /**< Instance 15. */
    I2C_INSTANCE_016,          /**< Instance 16. */
    I2C_INSTANCE_017,          /**< Instance 17. */
    I2C_INSTANCE_018,          /**< Instance 18. */
    I2C_INSTANCE_019,          /**< Instance 19. */
    I2C_INSTANCE_020,          /**< Instance 20. */
    I2C_INSTANCE_021,          /**< Instance 21. */
    I2C_INSTANCE_022,          /**< Instance 22. */
    I2C_INSTANCE_023,          /**< Instance 23. */
    I2C_INSTANCE_024,          /**< Instance 24. */

    I2C_INSTANCE_MAX,          /**< Instance Max. */

} i2c_instance;

/** @ingroup efi_i2c_protocol_data
  Function status codes returned by the APIs or the transfer_status field of
  the callback.
*/
typedef enum
{
    I2C_SUCCESS = 0,
    I2C_ERROR_INVALID_PARAMETER,
    I2C_ERROR_UNSUPPORTED_CORE_INSTANCE,
    I2C_ERROR_API_INVALID_EXECUTION_LEVEL,
    I2C_ERROR_API_NOT_SUPPORTED,
    I2C_ERROR_API_ASYNC_MODE_NOT_SUPPORTED,
    I2C_ERROR_API_PROTOCOL_MODE_NOT_SUPPORTED,

    I2C_ERROR_HANDLE_ALLOCATION,
    I2C_ERROR_HW_INFO_ALLOCATION,
    I2C_ERROR_BUS_NOT_IDLE,
    I2C_ERROR_TRANSFER_TIMEOUT,
	I2C_ERROR_MEM_ALLOC_FAIL,

    I2C_ERROR_INPUT_FIFO_OVER_RUN,
    I2C_ERROR_OUTPUT_FIFO_UNDER_RUN,
    I2C_ERROR_INPUT_FIFO_UNDER_RUN,
    I2C_ERROR_OUTPUT_FIFO_OVER_RUN,

    I2C_ERROR_COMMAND_OVER_RUN,
    I2C_ERROR_COMMAND_ILLEGAL,
    I2C_ERROR_COMMAND_FAIL,
    I2C_ERROR_INVALID_CMD_OPCODE,

    I2C_ERROR_START_STOP_UNEXPECTED,
    I2C_ERROR_DATA_NACK,
    I2C_ERROR_ADDR_NACK,
    I2C_ERROR_ARBITRATION_LOST,

    I2C_ERROR_PLATFORM_INIT_FAIL,
    I2C_ERROR_PLATFORM_DEINIT_FAIL,
    I2C_ERROR_PLATFORM_CRIT_SEC_FAIL,
    I2C_ERROR_PLATFORM_SIGNAL_FAIL,
    I2C_ERROR_PLATFORM_GET_CONFIG_FAIL,
    I2C_ERROR_PLATFORM_GET_CLOCK_CONFIG_FAIL,
    I2C_ERROR_PLATFORM_REG_INT_FAIL,
    I2C_ERROR_PLATFORM_DE_REG_INT_FAIL,
    I2C_ERROR_PLATFORM_CLOCK_ENABLE_FAIL,
    I2C_ERROR_PLATFORM_GPIO_ENABLE_FAIL,
    I2C_ERROR_PLATFORM_CLOCK_DISABLE_FAIL,
    I2C_ERROR_PLATFORM_GPIO_DISABLE_FAIL,
	I2C_ERROR_PLATFORM_HWIO_MAP_FAIL,
	I2C_ERROR_PLATFORM_HWIO_UNMAP_FAIL,

    I2C_TRANSFER_CANCELED,
    I2C_TRANSFER_FORCE_TERMINATED,
    I2C_TRANSFER_COMPLETED,
    I2C_TRANSFER_INVALID,

    I2C_ERROR_HANDLE_ALREADY_IN_QUEUE,
    I2C_ERROR_DMA_REG_FAIL,
    I2C_ERROR_DMA_EV_CHAN_ALLOC_FAIL,
    I2C_ERROR_DMA_TX_CHAN_ALLOC_FAIL,
    I2C_ERROR_DMA_RX_CHAN_ALLOC_FAIL,
    I2C_ERROR_DMA_TX_CHAN_START_FAIL,
    I2C_ERROR_DMA_RX_CHAN_START_FAIL,
    I2C_ERROR_DMA_TX_CHAN_STOP_FAIL,
    I2C_ERROR_DMA_RX_CHAN_STOP_FAIL,
    I2C_ERROR_DMA_TX_CHAN_RESET_FAIL,
    I2C_ERROR_DMA_RX_CHAN_RESET_FAIL,
    I2C_ERROR_DMA_EV_CHAN_DE_ALLOC_FAIL,
    I2C_ERROR_DMA_TX_CHAN_DE_ALLOC_FAIL,
    I2C_ERROR_DMA_RX_CHAN_DE_ALLOC_FAIL,
    I2C_ERROR_DMA_INSUFFICIENT_RESOURCES,
    I2C_ERROR_DMA_PROCESS_TRANSFER_FAIL,
    I2C_ERROR_DMA_EVT_OTHER,
    I2C_ERROR_FW_LOAD_FALIURE,
    I2C_ERROR_INVALID_FW_VERSION,
} i2c_status;

/** @ingroup efi_i2c_protocol_data
  Protocol modes. Underlying implementation may not support some modes. Refer
  i2c_transfer() for more details.
*/
typedef enum
{
    I2C = 0,
    SMBUS,
    I3C_SDR,
    I3C_HDR_DDR,
    I3C_BROADCAST_CCC,
    I3C_DIRECT_CCC,
    I3C_IBI_READ,

} i2c_mode;



/** @name Structure Definitions
@{ */

/** @ingroup efi_i2c_protocol_data
  Slave configuration parameters that the client uses to communicate to a slave.
*/
typedef struct
{
    UINT32      bus_frequency_khz;          /**< Bus speed in kHz. */
    UINT32      slave_address;              /**< 7-bit I2C slave address. 7-bit I3C dynamic address */
    i2c_mode    mode;                       /**< Protocol mode. Refer #i2c_mode */
    UINT32      slave_max_clock_stretch_us; /**< Maximum time in microseconds that an I2C slave may hold the SCL line low. Not applicable for I3C*/
    UINT32      core_configuration1;        /**< Core Specific Configuration. Recommended 0. */
    UINT32      core_configuration2;        /**< Core Specific Configuration. Recommended 0. */

} i2c_slave_config;

/** @ingroup efi_i2c_protocol_data
  Transfer descriptor that the client uses to perform a read or a write.
  Clients pass this descriptor or an array of these descriptors to the
  i2c_transfer() API.
*/
typedef struct
{
    UINT8   *buffer;        /**< Buffer for the data transfer. */
    UINT32  length;         /**< Length of the data to be transferred in bytes. */
    UINT32  flags;          /**< Flags used for the transfer descriptor. */

} i2c_descriptor;



/** @ingroup efi_i2c_protocol_apis
  Transfer callback. Applicable only to asynchronous transfer mode. Refer to
  i2c_transfer().

  Declares the type of callback function that needs to be defined by the client.
  The callback is called when the data is completely transferred on the bus or
  the transfer ends due to an error or cancellation.

  Clients pass the callback function pointer and the callback context to the
  driver in the i2c_transfer () API.

  @note
  The callback is called in a thread that processes multiple clients. Calling
  any of the APIs defined here in this callback is not recommended. Processing
  in the callback function must be kept to a minimum to avoid system latencies.
  In some implementations the callback occurs from interrupt context and calling
  any of the APIs defined here will result in an
  I2C_ERROR_API_INVALID_EXECUTION_LEVEL error.

  @param[out] transfer_status   The completion status of the transfer; see
                                #i2c_status for actual values.
  @param[out] transferred       Total number of bytes transferred. If
                                transfer_status is I2C_SUCCESS, then this value
                                is equal to the sum of lengths of all the
                                descriptors passed in a call to i2c_transfer().
                                If transfer_status is not I2C_SUCCESS, this
                                value is less than the sum of lengths of all the
                                descriptors passed in a call to i2c_transfer().
  @param[out] ctxt              The callback context parameter that was passed
                                in the call to i2c_transfer().
*/
typedef void (*callback_func) (UINT32 transfer_status, UINT32 transferred, void *ctxt);

#endif /* __I2C_COMMON_H__ */
