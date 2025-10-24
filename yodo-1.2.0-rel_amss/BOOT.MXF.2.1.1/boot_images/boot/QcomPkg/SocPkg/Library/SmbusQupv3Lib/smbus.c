/**
    @file  smbus.c
    @brief SMBus Implementation on I2C
 */
/*=============================================================================
            Copyright (c) 2022 Qualcomm Technologies, Incorporated.
                              All rights reserved.
              Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/


/*==================================================================================================
                                           INCLUDE FILES
==================================================================================================*/
#include "i2c_api.h"
#include "smbus.h"

#ifndef UNUSED
#define UNUSED(x) (void)x
#endif

/*==================================================================================================
                                             CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                              TYPEDEFS
==================================================================================================*/

/*==================================================================================================
                                              VARIABLES
==================================================================================================*/

/*==================================================================================================
                                          GLOBAL FUNCTIONS
==================================================================================================*/
static smbus_result smbus_convert_i2c_status(i2c_status status)
{
    switch ((uint32_t)status)
    {
        case I2C_SUCCESS:
            return SMBUS_SUCCESS;
        case I2C_ERROR_ADDR_NACK:
            return SMBUS_ERROR_ADDR_NACKED;
        case I2C_ERROR_DATA_NACK:
            return SMBUS_ERROR_DATA_NACKED;
        case I2C_ERROR_START_STOP_UNEXPECTED:
        case I2C_ERROR_ARBITRATION_LOST:
            return SMBUS_ERROR_DEVICE_ERROR;
        case I2C_ERROR_TRANSFER_TIMEOUT:
            return SMBUS_ERROR_TIMEOUT;
        case I2C_ERROR_INVALID_PARAMETER:
        case I2C_ERROR_UNSUPPORTED_CORE_INSTANCE:
        case I2C_ERROR_API_INVALID_EXECUTION_LEVEL:
        case I2C_ERROR_API_NOT_SUPPORTED:
        case I2C_ERROR_API_ASYNC_MODE_NOT_SUPPORTED:
        case I2C_ERROR_API_PROTOCOL_MODE_NOT_SUPPORTED:
            return SMBUS_ERROR_INVALID_PARAMETER;
        default:
            return SMBUS_ERROR_UNKNOWN_I2C_ERROR;
    }
    return SMBUS_ERROR_UNKNOWN_I2C_ERROR;
}

static smbus_result smbus_i2c_transfer(void *smbus_handle, smbus_slave_config *config, i2c_descriptor *desc, uint32_t num_desc)
{
    i2c_slave_config cfg;
    i2c_status       status;
    
    cfg.bus_frequency_khz             = config->bus_frequency_khz;
    cfg.slave_address                 = config->slave_address;
    cfg.mode                          = I2C;
    cfg.slave_max_clock_stretch_us    = 0;
    cfg.core_configuration1           = 0;
    cfg.core_configuration2           = 0;
    
    status = i2c_transfer(smbus_handle, &cfg, desc, num_desc, NULL, NULL, 0, NULL);
    
    return smbus_convert_i2c_status(status);
}

smbus_result smbus_open(smbus_instance instance, void **smbus_handle)
{
    i2c_status status;
    
    status = i2c_open((i2c_instance)instance,smbus_handle);
    
    return smbus_convert_i2c_status(status);
}

smbus_result smbus_close(void *smbus_handle)
{
    i2c_status status;
    
    status = i2c_close(smbus_handle);
    
    return smbus_convert_i2c_status(status);
}

smbus_result smbus_quick_command(void *smbus_handle, smbus_slave_config *config, bool rw_bit)
{
    i2c_descriptor desc = {0};
    
    desc.buffer      = NULL;
    desc.length      = 0;
    desc.flags       = I2C_FLAG_START;
    
    /*HW does not support changing R/W bit for Address only command */
    UNUSED(rw_bit);
    
    return smbus_i2c_transfer(smbus_handle,config,&desc,1);
}


smbus_result smbus_send_byte(void *smbus_handle, smbus_slave_config *config, uint8_t *buffer)
{
    i2c_descriptor desc = {0};
    
    desc.buffer      = buffer;
    desc.length      = 1;
    desc.flags       = I2C_WRITE_TRANSFER;
    
    return smbus_i2c_transfer(smbus_handle,config,&desc,1);
}

smbus_result smbus_receive_byte(void *smbus_handle, smbus_slave_config *config, uint8_t *buffer)
{
    i2c_descriptor desc = {0};
    
    desc.buffer      = buffer;
    desc.length      = 1;
    desc.flags       = I2C_READ_TRANSFER;
    
    return smbus_i2c_transfer(smbus_handle,config,&desc,1);
}

smbus_result smbus_write_byte_or_word(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc)
{
    i2c_descriptor i2c_desc = {0};

    i2c_desc.buffer  = desc->buffer;
    i2c_desc.length  = desc->length;
    i2c_desc.cmd     = desc->command;
    i2c_desc.flags   = (I2C_FLAG_START | SMBUS_FLAG_CMD |I2C_FLAG_WRITE | I2C_FLAG_STOP);
    
    return smbus_i2c_transfer(smbus_handle,config,&i2c_desc,1);
}

smbus_result smbus_read_byte_or_word(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc)
{
    i2c_descriptor i2c_desc[2] = {0};
    uint8_t        cmd_buf = desc->command;
    
    i2c_desc[0].buffer      = &cmd_buf;
    i2c_desc[0].length      = 1;
    i2c_desc[0].flags       = (I2C_FLAG_START | I2C_FLAG_WRITE);
    
    i2c_desc[1].buffer      = desc->buffer;
    i2c_desc[1].length      = desc->length;
    i2c_desc[1].flags       = (I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP);
    
    return smbus_i2c_transfer(smbus_handle,config,i2c_desc,2);
}

smbus_result smbus_process_call(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc)
{
    i2c_descriptor i2c_desc[2] = {0};
    
    i2c_desc[0].buffer      = desc[0].buffer;
    i2c_desc[0].length      = desc[0].length;
    i2c_desc[0].cmd         = desc[0].command;
    i2c_desc[0].flags       = (I2C_FLAG_START | SMBUS_FLAG_CMD | I2C_FLAG_WRITE);
    
    i2c_desc[1].buffer      = desc[1].buffer;
    i2c_desc[1].length      = desc[1].length;
    i2c_desc[1].flags       = (I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP);
    
    return smbus_i2c_transfer(smbus_handle,config,i2c_desc,2);
}

smbus_result smbus_block_write(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc)
{
    i2c_descriptor i2c_desc = {0};
   
    i2c_desc.buffer      = desc[0].buffer;
    i2c_desc.length      = desc[0].length;
    i2c_desc.cmd         = desc[0].command;
    i2c_desc.flags       = (I2C_FLAG_START | SMBUS_FLAG_CMD | I2C_FLAG_WRITE | I2C_FLAG_STOP);
     
    if(!desc[0].buffer_contains_length)
    {
        i2c_desc.flags |= SMBUS_FLAG_LEN;
    }
    
    return smbus_i2c_transfer(smbus_handle,config,&i2c_desc,1);
}

smbus_result smbus_block_read(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc)
{
    i2c_descriptor i2c_desc[2] = {0};
    uint8_t        cmd_buf;
    
    cmd_buf = desc[0].command;
    
    i2c_desc[0].buffer      = &cmd_buf;
    i2c_desc[0].length      = 1;
    i2c_desc[0].flags       = (I2C_FLAG_START | I2C_FLAG_WRITE);
    
    i2c_desc[1].buffer      = desc[0].buffer;
    i2c_desc[1].length      = desc[0].length;
    i2c_desc[1].flags       = (I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP);
    
    if(!desc[0].buffer_contains_length)
    {
        i2c_desc[1].flags |= SMBUS_FLAG_LEN;
    }
    
    return smbus_i2c_transfer(smbus_handle,config,i2c_desc,2);
}

smbus_result smbus_block_process_call(void *smbus_handle, smbus_slave_config *config, smbus_descriptor *desc)
{
    i2c_descriptor i2c_desc[2] = {0};
    
    i2c_desc[0].buffer      = desc[0].buffer;
    i2c_desc[0].length      = desc[0].length;
    i2c_desc[0].cmd         = desc[0].command;
    i2c_desc[0].flags       = (I2C_FLAG_START | SMBUS_FLAG_CMD | I2C_FLAG_WRITE);
    
    if(!desc[0].buffer_contains_length)
    {
        i2c_desc[0].flags |= SMBUS_FLAG_LEN;
    }
       
    i2c_desc[1].buffer      = desc[1].buffer;
    i2c_desc[1].length      = desc[1].length;
    i2c_desc[1].flags       = (I2C_FLAG_START | I2C_FLAG_READ | I2C_FLAG_STOP);
    
    if(!desc[1].buffer_contains_length)
    {
        i2c_desc[1].flags |= SMBUS_FLAG_LEN;
    }
    
    return smbus_i2c_transfer(smbus_handle,config,i2c_desc,2);
}

smbus_result smbus_read_alert_response(void *smbus_handle, smbus_slave_config *config, uint8 *slave_address)
{
    /* To Be implemented*/
    return SMBUS_ERROR_INVALID_PARAMETER;
}
