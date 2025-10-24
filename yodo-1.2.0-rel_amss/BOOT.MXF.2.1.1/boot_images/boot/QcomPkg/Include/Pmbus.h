/*==============================================================================
#      Copyright (c) 2016-2020, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#
#
#
#=============================================================================*/
/** @file   Pmbus.h
 *  @brief  Public API and related functions for PMBUS driver
 */
 
#ifndef PMBUS_H
#define PMBUS_H

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

#include "PmbusTypes.h"

/** @brief Opens a connection to a PMBUS device.

    @param PmbusDeviceId            PMBUS device ID.
    @param hPmbusDeviceHandle       Pointer to a PMBUS device handle
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusOpen
(
    PMBUS_DEVICE_ID_ENUM    PmbusDeviceId,
    PPMBUS_HANDLE_TYPE      hPmbusDeviceHandle
);


/** @brief Close a connection with a PMBUS device.

    @param PmbusDeviceHandle    PMBUS device handle
    @return                     PMBUS_STATUS_INVALID_HANDLE if the device handle is invalid.
    @return                     PMBUS_STATUS_SUCCESS if successful.
 */
PMBUS_STATUS_ENUM PmbusClose
(
    PMBUS_HANDLE_TYPE  PmbusDeviceHandle
);


/** @brief Performs a generic read command

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         PMBUS device Slave Address
    @param Command              PMBUS command.
    @param pIoBuffer            Pointer to the input/output buffer.
    @param BufferSize           I/O buffer size.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusGenericRead
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    uint32_t            Command,
    void                *pIoBuffer,
    size_t              BufferSize
);


/** @brief Performs a generic read command

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         PMBUS device Slave Address
    @param Command              PMBUS command.
    @param pIoBuffer            Pointer to the input/output buffer.
    @param BufferSize           I/O buffer size.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusGenericWrite
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    uint32_t            Command,
    void                *pIoBuffer,
    size_t              BufferSize
);


/** @brief Generic execute PMBUS command.

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pCommandInfo             Pointer to the command info
    @param pIoBuffer                Pointer to the input/output buffer
    @param pDevice                  Device page channel select and bus access type
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusGenericExecuteCommand
(
    PMBUS_HANDLE_TYPE               PmbusDeviceHandle,
    uint32_t                        SlaveAddress,
    const PPMBUS_COMMAND_INFO_TYPE  pCommandInfo,
    void                            *pIoBuffer,
    PPMBUS_PAGE_CHANNEL_SELECT_TYPE pDevice
);


/** @brief Selects the page channel

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         PMBUS device Slave Address
    @param PageChannel          The selected page channel.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PmbusSelectPageChannel
(
    PMBUS_HANDLE_TYPE               PmbusDeviceHandle,
    uint32_t                        SlaveAddress,
    PMBUS_PAGE_CHANNEL_SELECT_ENUM  PageChannel
);


/** @brief Command: PAGE - Selects page channel 0, 1 or both.

    Selects Controller 0, Controller 1 or both Controllers 0 and 1 to receive commands.
    All commands following this command will be received and acted on by the selected
    controller or controllers.

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pPageChannelSelect       Pointer to the page channel.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PageChannelSelect
(
    PMBUS_HANDLE_TYPE               PmbusDeviceHandle,
    uint32_t                        SlaveAddress,
    PPMBUS_PAGE_CHANNEL_SELECT_TYPE pPageChannelSelect
);


/** @brief Command: OPERATION - Sets enable, disable and VOUT margin modes.

    Sets enable, disable and VOUT margin settings.  Data values of OPERATION that force
    margin high or low only take effect when the MGN pin is left open
    (i.e., in the nominal margin state).

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             PMBUS device Slave Address
    @param pOperationConfiguration  Pointer to the operation margin configuration
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM Operation
(
    PMBUS_HANDLE_TYPE                   PmbusDeviceHandle,
    uint32_t                            SlaveAddress,
    PPMBUS_OPERATION_CONFIGURATION_TYPE pOperationConfiguration
);


/** @brief Command: ON_OFF_CONFIG - Configures the EN pin and PMBus commands to turn the unit ON/OFF.

    Configures the interpretation and coordination of the OPERATION command and the ENABLE pin (EN).

    @param  PmbusDeviceHandle                PMBUS device handle
    @param  SlaveAddress                     PMBUS device Slave Address
    @param  pOperationOutputConfiguration    Pointer to the operation output configuration
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OperationOutput
(
    PMBUS_HANDLE_TYPE                           PmbusDeviceHandle,
    uint32_t                                    SlaveAddress,
    PPMBUS_OPERATION_OUTPUT_CONFIGURATION_TYPE  pOperationOutputConfiguration
);


/** @brief Command: CLEAR_FAULTS - Clears fault indications.

    Clears all fault bits in all registers and releases the SALRT pin(if asserted) simultaneously.
    If a fault condition still exists, the bit will reassert immediately.This command will not restart
    a device if it has shut down, it will only clear the faults.

    @param PmbusDeviceHandle     PMBUS device handle
    @param SlaveAddress          PMBUS device Slave Address
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM ClearFaults
(
    PMBUS_HANDLE_TYPE  PmbusDeviceHandle,
    uint32_t           SlaveAddress
);


/** @brief Command: PHASE - The PHASE command provides the ability to control multiple phase on one PMBus unit.

    The PHASE command provides the ability to configure, control, and monitor multiple
    phases on one PMBus unit.

    @param PmbusDeviceHandle      PMBUS device handle
    @param SlaveAddress           PMBUS device Slave Address
    @param pPhase                 Pointer to the phase.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM Phase
(
    PMBUS_HANDLE_TYPE  PmbusDeviceHandle,
    uint32_t           SlaveAddress,
    PPMBUS_PHASE_TYPE  pPhase
);


/** @brief Command: WRITE_PROTECT - The WRITE_PROTECT command provides the ability to control write protection to the configuration command.

    The WRITE_PROTECT command provides the ability to set the write protection of certain configuration commands.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pWriteProtect        Pointer to the write protect settings
    @param BusAccessType        Bus access type
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM WriteProtect
(
    PMBUS_HANDLE_TYPE       PmbusDeviceHandle,
    uint32_t                SlaveAddress,
    PPMBUS_BYTE_TYPE        pWriteProtect,
    PMBUS_ACCESS_TYPE_ENUM  BusAccessType
);


/** @brief Command: VOUT_MODE - The VOUT_MODE command returns the supported VOUT mode.

    The VOUT_MODE command returns the supported VOUT mode.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         PMBUS device Slave Address
    @param pVoltageOutputMode   Pointer to the voltage output mode.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetVoltageOutputMode
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_BYTE_TYPE    pVoltageOutputMode
);


/** @brief Command: VOUT_COMMAND - Sets the nominal value of the output voltage.

    This command sets or reports the target output voltage. This command cannot set a value higher
    than either VOUT_MAX or 110% of the pin-strap VOUT setting.

    @param PmbusDeviceHandle            PMBUS device handle
    @param SlaveAddress                 PMBUS device Slave Address
    @param pVoltageOutputConfiguration  Poiner to the voltage output level configuration
    @return PMBUS_STATUS_ENUM.
    */
PMBUS_STATUS_ENUM VoltageOutput
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pVoltageOutputConfiguration
);


/** @brief Command: VOUT_TRIM - Applies trim voltage to VOUT set-point.

    This command Sets a fixed trim voltage to the output voltage command value
    This command is typically used to calibrate a device in the application circuit.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         PMBUS device Slave Address
    @param pVoltageTrim         Poiner to the voltage trim.
    @return PMBUS_STATUS_ENUM.
    */
PMBUS_STATUS_ENUM VoltageTrim
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pVoltageTrim
);


/** @brief Command: VOUT_CALL_OFFSET - Applies a fixed offset voltage to the VOUT_COMMAND.

    The VOUT_CAL_OFFSET command is used to apply a fixed offset voltage to the output voltage command
    value. This command is typically used by the user to calibrate a device in the application circuit.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         PMBUS device Slave Address
    @param pFixedVoltageOffset  Pointer to the voltage offset calibration
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageCalibrateOffset
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_VOUT_CAL_OFFSET_TYPE pFixedVoltageOffset
);


/** @brief Command: VOUT_MAX - Sets the maximum possible value of Vout.

    The VOUT_ MAX command sets an upper limit on the output voltage the unit can command regardless of any other
    commands or combinations. The intent of this command is to provide a safeguard against a user accidentally
    setting the output voltage to a possibly destructive level rather than to be the primary output overprotection.
    Default value can be changed via PMBus.

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pMaximumOutputVoltage    Pointer to the maximum output voltage.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM MaximumOutputVoltage
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pMaximumOutputVoltage
);


/** @brief Command: VOUT_MARGIN_HIGH - Sets the value of the Vout during a marging high.

    Sets the value of the VOUT during a margin high. This VOUT_MARGIN_HIGH command loads the unit with the voltage
    to which the output is to be changed when the OPERATION command is set to "Margin High".

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pHighOutputVoltageMargin Pointer to the high output voltage margin.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageHighMargin
(
    PMBUS_HANDLE_TYPE       PmbusDeviceHandle,
    uint32_t                SlaveAddress,
    PPMBUS_VOUT_MARGIN_TYPE pHighOutputVoltageMargin
);


/** @brief Command: VOUT_MARGIN_LOW - Sets the value of the Vout during a marging low.

    Sets the value of the VOUT during a margin low. This VOUT_MARGIN_LOW command loads
    the unit with the voltage to which the output is to be changed when the OPERATION
    command is set to "Margin Low".

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pLowOutputVoltageMargin  Pointer to the low output voltage margin.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageLowMargin
(
    PMBUS_HANDLE_TYPE       PmbusDeviceHandle,
    uint32_t                SlaveAddress,
    PPMBUS_VOUT_MARGIN_TYPE pLowOutputVoltageMargin
);


/** @brief Command: VOUT_TRANSITION_RATE - Sets the transition rate during margin or other change of Vout.

    Sets the rate at which the output should change voltage when the device receives an
    OPERATION command (marging high, marging low) which causes the output voltage to change.
    The maximum poissible positive value of the two data bytes indicates that the device
    should make the transition as quickly as possible.

    @param PmbusDeviceHandle            PMBUS device handle
    @param SlaveAddress                 Slave Address of PMBus Device
    @param pOutputVoltageTransitionRate Pointer to the output voltage transition rate.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageTransitionRate
(
    PMBUS_HANDLE_TYPE                   PmbusDeviceHandle,
    uint32_t                            SlaveAddress,
    PPMBUS_VOLTAGE_TRANSITION_RATE_TYPE pOutputVoltageTransitionRate
);


/** @brief Command: VOUT_DROOP - Reads the loadline (V/I Slope) resistance for the rail.

    The VOUT_DROOP sets the effective load line (V/I slope) for the rail in which the device is used.
    It is the rate, in mV/A at which the output voltage decreases (or increases) with increasing
    (or decreasing) output current for use with adaptive voltage positioning schemes.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         PMBUS device Slave Address
    @param pOutputVoltageDroop  Pointer to the output voltage droop.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OutputVoltageDroop
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_VOLTAGE_DROOP_TYPE   pOutputVoltageDroop
);


/** @brief Command: VOUT_MIN - Sets the minimum possible value of Vout.

    The VOUT_MIN command sets an lower limit on the output voltage the unit can command regardless of any other
    commands or combinations.

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pMinimumOutputVoltage    Pointer to the minimum output voltage.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM MinimumOutputVoltage
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pMinimumOutputVoltage
);


/** @brief Command: VOUT_OV_FAULT_LIMIT - Reads the Vout overvoltage fault threshold.

    Sets the Vout overvoltage fault threshold.

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pOvervoltageFaultLimit   Pointer to the over voltage fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OverVoltageFaultLimit
(
    PMBUS_HANDLE_TYPE               PmbusDeviceHandle,
    uint32_t                        SlaveAddress,
    PPMBUS_VOLTAGE_THRESHOLD_TYPE   pOvervoltageFaultLimit
);


/** @brief Command: VOUT_UV_FAULT_LIMIT - Reads the Vout undervoltage fault threshold.

    Sets the VOUT undervoltage fault threshold. This fault is masked during ramp or when disabled.

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pUnderVoltageFaultLimit  Pointer to the under voltage fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM UnderVoltageFaultLimit
(
    PMBUS_HANDLE_TYPE             PmbusDeviceHandle,
    uint32_t                      SlaveAddress,
    PPMBUS_VOLTAGE_THRESHOLD_TYPE pUnderVoltageFaultLimit
);


/** @brief Command: OT_FAULT_LIMIT - Reads/Writes the over temperature fault threshold.

    Gets/Sets the over temperature fault threshold.

    @param PmbusDeviceHandle           PMBUS device handle
    @param SlaveAddress                Slave Address of PMBus Device
    @param pOverTemperatureFaultLimit  Pointer to the over temperature fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OverTemperatureFaultLimit
(
    PMBUS_HANDLE_TYPE                   PmbusDeviceHandle,
    uint32_t                            SlaveAddress,
    PPMBUS_TEMPERATURE_THRESHOLD_TYPE   pOverTemperatureFaultLimit
);


/** @brief Command: OT_WARN_LIMIT - Reads/Writes the over temperature warning threshold.

    Gets/Sets the over temperature warning threshold.

    @param PmbusDeviceHandle            PMBUS device handle
    @param SlaveAddress                Slave Address of PMBus Device
    @param pOverTemperatureWarningLimit Pointer to the over temperature fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM OverTemperatureWarningLimit
(
    PMBUS_HANDLE_TYPE                   PmbusDeviceHandle,
    uint32_t                            SlaveAddress,
    PPMBUS_TEMPERATURE_THRESHOLD_TYPE   pOverTemperatureWarningLimit
);


/** @brief Command: VIN_OV_FAULT_LIMIT - Reads/Writes the intput overvoltage fault threshold.

    Gets/Sets the intput over voltage fault threshold. Changes to this setting require a write
    to the APPLY_SETTINGS command before the change will take effect.

    @param  PmbusDeviceHandle     PMBUS device handle
    @param  SlaveAddress          Slave Address of PMBus Device
    @param  pThreshold            Pointer to the threshold fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM InputOvervoltageFaultLimit
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pThreshold
);


/** @brief Command: VIN_UV_FAULT_LIMIT - Reads/Writes the intput undervoltage fault threshold.

    Gets/Sets the intput under voltage fault threshold. Changes to this setting require a write
    to the APPLY_SETTINGS command before the change will take effect.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pThreshold           Pointer to the threshold fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM InputUndervoltageFaultLimit
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pThreshold
);


/** @brief Command: IIN_OC_FAULT_LIMIT - Reads/Writes the intput overcurrent fault threshold.

    Gets/Sets the intput overcurrent fault threshold. Changes to this setting require a write
    to the APPLY_SETTINGS command before the change will take effect.

    @param  PmbusDeviceHandle    PMBUS device handle
    @param  SlaveAddress         Slave Address of PMBus Device
    @param  pThreshold           Pointer to the threshold fault limit.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM InputOvercurrentFaultLimit
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pThreshold
);


/** @brief Command: TON_DELAY - Reads/Writes the delay time of output voltage during enable.

    Gets/Sets the delay time of the output voltage during enable.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pTime                Pointer to the time delay.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PowerOnTimeDelay
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_TIME_TYPE    pTime
);


/** @brief Command: TON_RISE - Reads/Writes the rise time of output voltage during enable.

    Gets/Sets the rise time of output voltage during enable.
    Changes to this setting require a write to the APPLY_SETTINGS command before
    the change will take effect.
    This function uses the value of VOUT to calculate rise time, so APPLY_SETTINGS
    must be sent after any change to the VOUT target for accurate rise time.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pTime                Pointer to the rise time.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PowerOnRiseTime
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_TIME_TYPE    pTime
);


/** @brief Command: TOFF_DELAY - Reads/Writes the delay time of output voltage during disable.

    Gets/Sets the delay time of the output voltage during disable.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pTime                Pointer to the time delay.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PowerOffTimeDelay
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_TIME_TYPE    pTime
);


/** @brief Command: TOFF_FALL - Reads/Writes the fall time of output voltage during diable.

    Gets/Sets the fall time of output voltage during diable.
    Changes to this setting require a write to the APPLY_SETTINGS command before
    the change will take effect.
    This function uses the value of VOUT to calculate rise time, so APPLY_SETTINGS
    must be sent after any change to the VOUT target for accurate rise time.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pTime                Pointer to the fall time.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM PowerOffFallTime
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_TIME_TYPE    pTime
);


/** @brief Command: STATUS_BYTE - Returns an abbreviated status for fast reads.

    The STATUS_BYTE command returns one byte of information with a summary of the most critical faults.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pUnitStatus          Pointer to the status of the unit's condition.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetUnitsShortStatus
(
    PMBUS_HANDLE_TYPE       PmbusDeviceHandle,
    uint32_t                SlaveAddress,
    PPMBUS_STATUS_BYTE_TYPE pUnitStatus
);


/** @brief Command: STATUS_WORD - Returns information with a summary of the unit's fault condition.

    The STATUS_WORD command returns two bytes of information with a summary of the unit's fault condition.
    Based on the information in these bytes, the host can get more information by reading the appropriate
    status registers. The low byte of the STATUS_WORD is the same register as the STATUS_BYTE (78h) command.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pUnitStatus          Pointer to the status of the unit's condition.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetUnitsFullStatus
(
    PMBUS_HANDLE_TYPE       PmbusDeviceHandle,
    uint32_t                SlaveAddress,
    PPMBUS_STATUS_WORD_TYPE pUnitStatus
);


/** @brief Command: STATUS_VOUT - Returns the Vout specific status.

    The STATUS_VOUT command returns one data byte with the status of the output voltage.

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pOutputVoltageStatus     Pointer to the output voltage status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputVoltageStatus
(
    PMBUS_HANDLE_TYPE                   PmbusDeviceHandle,
    uint32_t                            SlaveAddress,
    PPMBUS_OUTPUT_VOLTAGE_STATUS_TYPE   pOutputVoltageStatus
);


/** @brief Command: STATUS_IOUT - Returns the Iout specific status.

    The STATUS_IOUT command returns one data byte with the status of the output current.

    @param PmbusDeviceHandle        PMBUS device handle
    @param SlaveAddress             Slave Address of PMBus Device
    @param pOutputCurrentStatus     Pointer to the output current status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputCurrentStatus
(
    PMBUS_HANDLE_TYPE                   PmbusDeviceHandle,
    uint32_t                            SlaveAddress,
    PPMBUS_OUTPUT_CURRENT_STATUS_TYPE   pOutputCurrentStatus
);


/** @brief Command: STATUS_INPUT - Returns specific status specific to the input.

    The STATUS_INPUT command returns input voltage and input current status information.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pInputStatus         Pointer to the specific input status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetInputStatus
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_STATUS_INPUT_ENUM    pInputStatus
);


/** @brief Command: STATUS_TEMPERATURE - Returns the temperature specific status.

    The STATUS_TEMPERATURE command returns one byte of information with a summary of any
    temperature related faults or warnings.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pTemperatureStatus   Pointer to the specific temperature status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetTemperatureStatus
(
    PMBUS_HANDLE_TYPE               PmbusDeviceHandle,
    uint32_t                        SlaveAddress,
    PPMBUS_STATUS_TEMPERATURE_TYPE  pTemperatureStatus
);


/** @brief Command: STATUS_CML - Returns the communication, memory, and logic specific status.

    The STATUS_CML command returns one byte of information with a summary of any communications, logic
    and / or memory errors.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pCmlStatus           Pointer to the communication, memory, and logic specific status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetCmlStatus
(
    PMBUS_HANDLE_TYPE       PmbusDeviceHandle,
    uint32_t                SlaveAddress,
    PPMBUS_STATUS_CML_ENUM  pCmlStatus
);


/** @brief Command: STATUS_MFR_SPECIFIC - Returns the manufacturer specific status.

    The STATUS_MFR_SPECIFIC command returns one byte of information that is manufacturer specific.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pStatus              Pointer to the manufacturer specific status.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetManufacturerSpecificStatus
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_BYTE_TYPE    pStatus
);


/** @brief Command: READ_VIN - Returns the input voltage reading.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pInputVoltage        Pointer to the read input voltage level in Volts.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetInputVoltageLevel
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pInputVoltage
);


/** @brief Command: READ_IIN - Returns the input current reading.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pInputCurrent        Pointer to the read input current level in Amps.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetInputCurrentLevel
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pInputCurrent
);


/** @brief Command: READ_VOUT - Returns the output voltage reading.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pOutputVoltage       Pointer to the read output voltage level in Volts.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputVoltageLevel
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_VOLTAGE_LEVEL_TYPE   pOutputVoltage
);


/** @brief Command: READ_IOUT - Returns the output current reading.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pOutputCurrent       Pointer to the read output current level in Amps.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputCurrentLevel
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_CURRENT_LEVEL_TYPE   pOutputCurrent
);


/** @brief Command: READ_TEMPERATURE_1 - Returns the controller junction temperature
                                         reading from internal temperature sensor.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pTemperature         Pointer to the read temperature from internal sensors
                                in degrees celcius.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetTemperatureMonitor1
(
    PMBUS_HANDLE_TYPE       PmbusDeviceHandle,
    uint32_t                SlaveAddress,
    PPMBUS_TEMPERATURE_TYPE pTemperature
);


/** @brief Command: READ_TEMPERATURE_2 - Returns the temperature reading from
                                         external source at CH-0.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pTemperature         Pointer to the read temperature in degrees celcius.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetTemperatureMonitor2
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pTemperature
);


/** @brief Command: READ_TEMPERATURE_3 - Returns the temperature reading from
                                         external source at CH-1.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pTemperature         Pointer to the read temperature in degrees celcius.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetTemperatureMonitor3
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pTemperature
);


/** @brief Command: READ_POUT - Returns the output power.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pOutputPower         Pointer to the read output power in Watts.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetOutputPower
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_POWER_TYPE   pOutputPower
);


/** @brief Command: READ_PIN - Returns the input power.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pInputPower          Pointer to the read input power in Watts.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetInputPower
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pInputPower
);


/** @brief Command: MFR_ID - Return's the device's manufacturer.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pManufacturerId      Pointer to the read manufacturer Id.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetManufacturerId
(
    PMBUS_HANDLE_TYPE               PmbusDeviceHandle,
    uint32_t                        SlaveAddress,
    PPMBUS_MANUFACTURER_INFO_TYPE   pManufacturerId
);


/** @brief Command: MFR_MODEL - Return's the device's model.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pDeviceModel         Pointer to the read device's model.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetDeviceModel
(
    PMBUS_HANDLE_TYPE               PmbusDeviceHandle,
    uint32_t                        SlaveAddress,
    PPMBUS_MANUFACTURER_INFO_TYPE   pDeviceModel
);


/** @brief Command: PMBUS_REVISION - Return's the device's PMBUS revision.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pDeviceRevision      Pointer to the read device's PMBUS revision.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetPmbusRevision
(
    PMBUS_HANDLE_TYPE           PmbusDeviceHandle,
    uint32_t                    SlaveAddress,
    PPMBUS_PMBUS_REVISION_TYPE  pPmbusRevision
);


/** @brief Command: MFR_DATE - Return's the device's manufacturing date in YYMMDD format.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pManufacturingDate   Pointer to the read device's manufacturing date.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetManufacturingDate
(
    PMBUS_HANDLE_TYPE               PmbusDeviceHandle,
    uint32_t                        SlaveAddress,
    PPMBUS_MANUFACTURER_INFO_TYPE   pManufacturingDate
);


/** @brief Command: IC_DEVICE_ID - Return's the device Id.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pDeviceId            Pointer to the read device id.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetDeviceId
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_BLOCK_TYPE   pDeviceId
);


/** @brief Command: IC_DEVICE_REV - Return's the device's revision.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pDeviceRevision      Pointer to the read device's revision.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM GetDeviceRevision
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_BLOCK_TYPE   pDeviceRevision
);


/** @brief Command: APPLY_SETTINGS - Applies the updated settings.

    The APPLY_SETTINGS command instruct the controller to one byte of information that is manufacturer specific.

    The commands that require this are VOUT_TRANSITION_RATE, VOUT_DROOP, VOUT_OV_FAULT_LIMIT, VIN_OV_FAULT_LIMIT,
    VIN_UV_FAULT_LIMIT, IIN_OC_FAULT_LIMIT, TON_RISE, and TOFF_FALL.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pSettings            Pointer to the settings to be applied.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM ApplySettings
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_WORD_TYPE    pSettings
);


/** @brief Command: RESTORE_CONFIG - Restore configuration from NVM.

    The RESTORE_CONFIG command identifies the configuration to be restored from NVM
    and loads the store's settings into the device's active memory.

    @param PmbusDeviceHandle    PMBUS device handle
    @param SlaveAddress         Slave Address of PMBus Device
    @param pConfig              Pointer to the config to restore.
    @return PMBUS_STATUS_ENUM.
 */
PMBUS_STATUS_ENUM RestoreConfig
(
    PMBUS_HANDLE_TYPE   PmbusDeviceHandle,
    uint32_t            SlaveAddress,
    PPMBUS_BYTE_TYPE    pConfig
);

#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* PMBUS_H */
