/**
    @file  smbus.h
    @brief System Management Bus APIs
 */
/*=============================================================================
         Copyright (c) 2022 Qualcomm Technologies, Incorporated.
                        All rights reserved.
           Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

#ifndef SMBUS_H
#define SMBUS_H

#include "comdef.h"
#include <stdbool.h>

#define SMBUS_QUEUE_TIMEOUT        2
#define I2C_DEFAULT_TIMEOUT_MS     5
#define I2C_DEFAULT_CLOCK_FREQ_KHZ 400

typedef enum
{
    SMBUS_SUCCESS                      = 0,
    SMBUS_ERROR_INVALID_PARAMETER,
    SMBUS_ERROR_NOT_INITIALIZED,
    SMBUS_ERROR_NOT_SUPPORTED,
    SMBUS_ERROR_OUT_OF_RANGE_PARAMETER,
    SMBUS_ERROR_BUSY_RESOURCE,

    // SMBus-specific errors
    SMBUS_ERROR_SPEC_BASE              = (int32_t) 0x4000,
    SMBUS_ERROR_ADDR_NACKED,
    SMBUS_ERROR_DATA_NACKED,
    SMBUS_ERROR_TIMEOUT,
    SMBUS_ERROR_DEVICE_ERROR,
    SMBUS_ERROR_DRIVER_ERROR,
    SMBUS_ERROR_I2C_PLATFORM_ERROR,
    SMBUS_ERROR_OS_ERROR,
    SMBUS_ERROR_UNKNOWN_I2C_ERROR
} smbus_result;

typedef enum
{
    SMBUS_INSTANCES_1 = 1,
    SMBUS_INSTANCES_2,
    SMBUS_INSTANCES_3,
    SMBUS_INSTANCES_4,
    SMBUS_INSTANCES_5,
    SMBUS_INSTANCES_6,
    SMBUS_INSTANCES_7,
    SMBUS_INSTANCES_8,
    SMBUS_INSTANCES_9,
    SMBUS_INSTANCES_10,
    SMBUS_INSTANCES_11,
    SMBUS_INSTANCES_12,
    SMBUS_INSTANCES_13,
    SMBUS_INSTANCES_14,
    SMBUS_INSTANCES_15,
    SMBUS_INSTANCES_16,
    SMBUS_INSTANCES_17,
    SMBUS_INSTANCES_18,
    SMBUS_INSTANCES_19,
    SMBUS_INSTANCES_20,
    SMBUS_INSTANCES_21,
    SMBUS_INSTANCES_22,
    SMBUS_INSTANCES_23,
    SMBUS_INSTANCES_24,
    SMBUS_INSTANCES_25,
    SMBUS_INSTANCES_26,
    SMBUS_NUM_INSTANCES
} smbus_instance;

/**
 * These parameters are shared amongst many or all of the commands.  Any generic
 * parameter will be described up here, parameters with command-specific
 * functionality will be described below
 *
 * For full descriptions on what each of the commands do, refer to the SMBUS
 *  specification (V2.0), in the Bus Protocols section.
 *
 * @param[in]   SmbusDevice    The index of the SMBus Device to do the transfer
 * @param[in]   SmbusTransfer  A structure containing transfer specific info
 * @return      SmbusResult    Return status for executed command
 **/

typedef struct
{
    uint32_t      bus_frequency_khz;          /**< Bus speed in kHz. */
    uint32_t      slave_address;              /**< 7-bit smbus slave address*/
    uint32_t      flags;                      /**< Place Holder for future use*/
} smbus_slave_config;

typedef struct
{
    uint8_t   *buffer;                  /**< Buffer for the data transfer. */
    uint32_t  length;                   /**< Length of the data to be transferred in bytes. 
                                             Should be as per API description of transfer size*/
    uint8_t   command;                  /**< Command to be sent as per API description. */
    bool      buffer_contains_length;   /**< Determines if byte 0 of packet contains length as per Spec.
                                             If false, driver will prepend Length to transfer buffer
                                             Applicable only to Block transfer API's*/
} smbus_descriptor;

/* Function Headers */

smbus_result smbus_open(smbus_instance instance, void **smbus_handle);

smbus_result smbus_close(void *smbus_handle);

smbus_result smbus_quick_command(void *smbus_handle, smbus_slave_config *config, bool rw_bit);

smbus_result smbus_send_byte(void *smbus_handle, smbus_slave_config *config, uint8_t *buffer);

smbus_result smbus_receive_byte(void *smbus_handle, smbus_slave_config *config, uint8_t *buffer);

smbus_result smbus_write_byte_or_word(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc);

smbus_result smbus_read_byte_or_word(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc);

smbus_result smbus_process_call(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc);

smbus_result smbus_block_write(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc);

smbus_result smbus_block_read(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc);

smbus_result smbus_block_process_call(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc);

smbus_result smbus_read_alert_response(void *smbus_handle, smbus_slave_config *config, uint8 *slave_address);

#endif /* SMBUS_H */
