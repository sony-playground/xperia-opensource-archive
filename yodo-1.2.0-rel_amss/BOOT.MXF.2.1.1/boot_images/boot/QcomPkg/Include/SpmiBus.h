/**
 * @file:  SpmiBus.h
 * @brief: This module provides the interface to the SPMI bus driver software.
 *         It provides APIs to do I/O and interrupt handling on SPMI bus.
 * 
 * Copyright (c) 2013-2022 by Qualcomm Technologies Incorporated. All Rights Reserved.
 * 
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/Include/SpmiBus.h#1 $
 * $Change: 39147961 $ 
 * 
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 8/06/15  More than 256 chan support.
 * 1/20/15  Multiple bus support
 * 10/1/13  Initial Version
 */
#ifndef SPMIBUS_H
#define	SPMIBUS_H

#include "SpmiTypes.h"
#include "com_dtypes.h"

/**
 * @brief Token needed for registering and unregistering ISRs.
 * 
 *        The fields are for internal use in the SPMI driver.
 *        Users should treat the object as a blackbox.
 */
typedef struct 
{
    uint8 bid;
    uint16 chan;
    uint32 id;
} SpmiToken;

/**
 * @brief Initialize the driver 
 * 
 * This function initializes the Spmi driver. It is mandatory 
 * to call this function before using any other APIs of this driver
 * 
 * @return  SPMI_SUCCESS on success, error code on error
 * 
 * @see SpmiBus_DeInit
 */
Spmi_Result SpmiBus_Init(void);

/**
 * @brief De-initialize the driver 
 * 
 * This function de-initializes the Spmi driver.  After this call any
 * outstanding transaction will finish and SPMI bus will be disabled.
 * 
 * @return  SPMI_SUCCESS on success, error code on error
 * 
 * @see SpmiBus_Init
 */
Spmi_Result SpmiBus_DeInit(void);

/**
 * @brief Registers an ISR
 * 
 * This function registers an ISR with SPMI driver.
 * 
 * @param[in] busId    Bus Id of the device
 * @param[in] slaveId  Slave Id of the device
 * @param[in] periph   Peripheral address
 * @param[in] mask     Mask of extended interrupt bits. Every bit represents 
 *                     an interrupt bit within a peripheral.
 *    Example:
 *     0x01 means register for intrpt 0
 *     0x03 means register for intrpt 0 and 1
 *     0x05 means register for intrpt 0 and 2
 *     ...
 *     0xFF means you are registering for all interrupts within
 *          the peripheral
 * 
 * @param[in] isr  ISR routine associated with the interrupt
 * @param[in] ctx  ISR context which will be copied as a parameter 
 *                 on isr invocation
 * 
 * @param[out] token A pointer to a token object that will be used by this function. 
 * 
 * @return SPMI_SUCCESS on success, error code on error
 * 
 * @see SpmiBus_Unregister()
 */
Spmi_Result SpmiBus_RegisterIsr(uint8 busId,
                                uint8 slaveId,
                                uint8 periph,
                                uint8 mask,
                                const SpmiIsr isr,
                                const void* ctx,
                                SpmiToken* token);

/**
 * @brief Unregisters an ISR
 * 
 * This function unregisters an ISR with SPMI driver.
 * 
 * @param[in] token  A pointer to the token that was used to register the ISR.
 * @param[in] mask   Mask of extended interrupt bits. Every bit represents 
 *                   an interrupt bit within a peripheral.  This mask can be
 *                   different than the one used to register the ISR to allow for
 *                   unregistering only a subset of the extended interrupts.  Bits 
 *                   set in this mask that weren't set when registering have no effect
 *                   and won't produce an error.
 *    Example:
 *     0x01 means unregister intrpt 0
 *     0x03 means unregister intrpt 0 and 1
 *     0x05 means unregister intrpt 0 and 2
 *     ...
 *     0xFF means you are unregistering for all interrupts within
 *          the peripheral
 * 
 * @return SPMI_SUCCESS on success, error code on error
 * 
 * @see SpmiBus_RegisterIsr()
 */
Spmi_Result SpmiBus_UnregisterIsr(SpmiToken* token, uint8 mask);

/**
 * @brief Reads from a SPMI slave device 
 *
 * This function reads data from a SPMI Slave device.
 *
 * @param[in] busId      Bus Id of the device
 * @param[in] slaveId    Slave Id of the device
 * @param[in] priority   Requested priority with which the command needs 
 *                       to be sent on the SPMI bus
 * @param[in] address    16-bit register address on the SPMI slave device
 *                       Consists of upper 8-bit peripheral id and lower 8-bit
 *                       register offset.
 * @param[in] data       Buffer to fill with data
 * @param[in] len        Number of bytes to read
 * @param[out] bytesRead  Number of bytes read on the bus.  Can be NULL if
 *                        this information is not needed.
 * 
 * @return  SPMI_SUCCESS on success, error code on error
 */
Spmi_Result SpmiBus_ReadLong(uint32  busId,
                             uint32 slaveId,
                             Spmi_AccessPriority priority,
                             uint32 address,
                             uint8* data,
                             uint32 len,
                             uint32* bytesRead);

/**
 * @brief Writes to a SPMI slave device 
 * 
 * This function writes data to the SPMI Slave device.
 * 
 * @param[in] busId      Bus Id of the device
 * @param[in] slaveId    Slave Id of the device
 * @param[in] priority   Requested priority with which the command needs 
 *                       to be sent on the SPMI bus
 * @param[in] address    16-bit register address on the SPMI slave device
 *                       Consists of upper 8-bit peripheral id and lower 8-bit
 *                       register offset.
 * @param[in] data       Data buffer containing data to write
 * @param[in] len        Number of bytes to write
 * 
 * @return  SPMI_SUCCESS on success, error code on error
 */
Spmi_Result SpmiBus_WriteLong(uint32  busId,
                              uint32 slaveId,
                              Spmi_AccessPriority priority,
                              uint32 address,
                              uint8* data,
                              uint32 len);
/**
 * @brief Writes to PBS memory 
 * 
 * This function writes data to PBS memory.
 * 
 * @param[in] busId      Bus Id of the device
 * @param[in] slaveId    Slave Id of the device
 * @param[in] priority   Requested priority with which the command needs 
 *                       to be sent on the SPMI bus
 * @param[in] address    16-bit register address on the SPMI slave device
 *                       Consists of upper 8-bit peripheral id and lower 8-bit
 *                       register offset.
 * @param[in] data       Data buffer containing data to write
 * @param[in] len        Number of bytes to write
 * 
 * @return  SPMI_SUCCESS on success, error code on error
 */
Spmi_Result SpmiBus_PBSWriteLong(uint32  busId,
                              uint32 slaveId,
                              Spmi_AccessPriority priority,
                              uint32 address,
                              uint8* data,
                              uint32 len);

/**
 * @brief Send a command to SPMI slave device
 * 
 * This function sends a command to SPMI slave device.
 * 
 * @param[in] vSlaveId   Virtual slave Id of the device (see SpmiEncodeVSid)
 * @param[in] priority  Priority with which the command needs to be sent on
 *                      the SPMI bus
 * @param[in] cmd       The command to send
 * 
 * @return  SPMI_SUCCESS on success, error code on error
 */
Spmi_Result SpmiBus_Command(uint32 busId,
                            uint32 slaveId,
                            Spmi_AccessPriority priority,
                            Spmi_Command cmd);

                            
/**
 * @brief Read-Modify-Write a byte from SPMI slave device
 *
 * This function reads a byte from SPMI slave device, modifies it
 * and writes it back to SPMI Slave device.
 * 
 * @param[in] busId    Bus Id of the device
 * @param[in] slaveId  Slave Id of the device
 * @param[in] priority   Priority with which the command needs to be sent on
 *                       the SPMI bus
 * @param[in] address    16-bit register address on the SPMI slave device
 *                       Consists of upper 8-bit peripheral id and lower 8-bit
 *                       register offset.
 * @param[in] data       Data to write
 * @param[in] mask       Mask of the bits which needs to be modified
 * @param[out] byteWritten  Set to the actual value written on the bus
 *
 * @return  SPMI_SUCCESS on success, error code on error
 */                       
Spmi_Result SpmiBus_ReadModifyWriteLongByte(uint32 busId,
                                            uint32 vSlaveId,
                                            Spmi_AccessPriority priority,
                                            uint32 address,
                                            uint8 data,
                                            uint8 mask,
                                            uint8 *byteWritten);

/**
@brief Clear all spmi interrupts

This function clears the all spmi interrupts

@return  SPMI_SUCCESS on success, error code on error 

@see None
*/
Spmi_Result SpmiIntrCtlr_InterruptClearAll(void);

/**
@brief Get number of SPMI busses supported

This function gets the number of spmi busses supported

@param[in] uNumDevices  Argument to fill with number of buses

@return  SPMI_SUCCESS on success, error code on error 

@see None
*/
Spmi_Result SpmiBus_GetNumDevices(uint8 *uNumDevices);

/**
 * @brief Enables auxillary SPMI BUS
 * 
 * @param[in] busId    Bus Id of the device
 *
 * @return  void
 */  
void SpmiBus_EnableAuxBus(uint32 busId);

/**
 * @brief Gets the sw channel assigned to particular peripheral
 *
 * This function gets sw channel assigned to particular peripheral
 * a channel
 *
 * @param[in] busId  The bus to query
 * @param[in] slaveId  The slaveid to query
 * @param[in] periphId  The periphId to query
 * @param[out] channel SW Channel asigned to periphId with slaveId
 *
 * @return  SPMI_SUCCESS on success, error code on error
 *
 * @see SpmiBus_GetChannel
 */
Spmi_Result SpmiBus_GetChannel(uint8 busId, uint8 slaveId, uint8 periphId, uint16 *channel);

#endif
