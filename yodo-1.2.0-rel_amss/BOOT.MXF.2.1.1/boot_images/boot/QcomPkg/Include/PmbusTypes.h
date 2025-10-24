/*==============================================================================
#      Copyright (c) 2016-2020, 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
#               Confidential and Proprietary - Qualcomm Technologies, Inc.
#
#
#=============================================================================*/
/** @file  PmbusTypes.h
 *  @brief  Interface declaration for PMBUS device driver.
 */

#ifndef PMBUSTYPES_H
#define PMBUSTYPES_H

#include "comdef.h"

/*-------------------------------------DATA TYPES-------------------------------------------*/

#define PMBUS_BYTE_TYPE     uint8_t
#define PMBUS_WORD_TYPE     uint16_t
#define PMBUS_BLOCK_TYPE    uint32_t

#define PPMBUS_BYTE_TYPE    uint8_t *
#define PPMBUS_WORD_TYPE    uint16_t *
#define PPMBUS_BLOCK_TYPE   uint32_t *

#define PPMBUS_HANDLE_TYPE  void **
#define PMBUS_HANDLE_TYPE   void *

/** @struct PMBUS_DEVICE_ID_ENUM
    @brief PMBUS device id enum
*/
typedef enum _PMBUS_DEVICE_ID_ENUM
{
    PMBUS_DEVICE_ID_INVALID = 0,
    PMBUS_DEVICE_ID_1,
    PMBUS_DEVICE_ID_2,
    PMBUS_DEVICE_ID_3,
    PMBUS_DEVICE_ID_4,
    PMBUS_DEVICE_ID_5,
    PMBUS_DEVICE_ID_6,
    PMBUS_DEVICE_ID_7,
    PMBUS_DEVICE_ID_8,
    PMBUS_DEVICE_ID_9,
    PMBUS_DEVICE_ID_10,
    PMBUS_DEVICE_ID_11,
    PMBUS_DEVICE_ID_12,
    PMBUS_DEVICE_ID_13,
    PMBUS_DEVICE_ID_14,
    PMBUS_DEVICE_ID_15,
    PMBUS_DEVICE_ID_16,
    PMBUS_DEVICE_ID_17,
    PMBUS_DEVICE_ID_18,
    PMBUS_DEVICE_ID_19,
    PMBUS_DEVICE_ID_20,
    PMBUS_DEVICE_ID_21,
    PMBUS_DEVICE_ID_22,
    PMBUS_DEVICE_ID_23,
    PMBUS_DEVICE_ID_24,
    PMBUS_DEVICE_ID_25,
    PMBUS_DEVICE_ID_26,
    PMBUS_DEVICE_ID_MAXIMUM
} PMBUS_DEVICE_ID_ENUM;

#define PMBUS_IS_VALID_DEVICE_ID(DEVICE_ID) (PMBUS_DEVICE_ID_INVALID < DEVICE_ID && DEVICE_ID < PMBUS_DEVICE_ID_MAXIMUM)

#define SET_PMBUS_COMMAND_INFO(COMMAND)         \
            PMBUS_##COMMAND##_COMMAND,          \
            PMBUS_##COMMAND##_COMMAND_LENGTH,   \
            PMBUS_##COMMAND##_BUS_ACCESS,       \
            PMBUS_##COMMAND##_DATA_FORMAT,      \
            PMBUS_##COMMAND##_CHANNEL_SELECT    \

#define SET_PMBUS_SBL_PDM_DELAY_COMMAND(DELAY_IN_USEC)                              \
            { PMBUS_SBL_PDM_COMMAND_DELAY, 0, { 0, 0, 0, 0, 0 }, DELAY_IN_USEC, 0 } \


#define PMBUS_GET_REGISTER_MASK(SIZE)                                               \
                         ((SIZE == 1) ? 0xFF : (SIZE == 2) ? 0xFFFF : 0xFFFFFFFF)   \

#define DEFINE_PMBUS_COMMAND_INFO_TYPE(COMMAND, FUNC_PTR)                                           \
/** @struct PMBUS_##COMMAND##_COMMAND_INFO_TYPE                                                     \
    @brief PMBUS _##COMMAND## command info type                                                     \
*/                                                                                                  \
typedef struct _PMBUS_##COMMAND##_COMMAND_INFO_TYPE                                                 \
{                                                                                                   \
    PMBUS_COMMAND_INFO_TYPE Base;                   /***< Command base fields. */                   \
    FUNC_PTR                pCommandFuncPtr;        /***< Command callback function pointer. */     \
} PMBUS_##COMMAND##_COMMAND_INFO_TYPE, *PPMBUS_##COMMAND##_COMMAND_INFO_TYPE;                       \


#define DECLARE_PMBUS_COMMAND_INFO(COMMAND)         struct _PMBUS_##COMMAND##_COMMAND_INFO_TYPE
#define DECLARE_PMBUS_COMMAND_INFO_PTR(COMMAND)     struct _PMBUS_##COMMAND##_COMMAND_INFO_TYPE *


/** @struct PMBUS_DATA_FORMAT_ENUM
    @brief PMBUS data format enum
*/
typedef enum _PMBUS_DATA_FORMAT_ENUM
{
    PMBUS_DATA_FORMAT_INVALID = 0,                      /***< Invalid data format. */
    PMBUS_DATA_FORMAT_BIT_FIELDS,                       /***< Bit fields format. */
    PMBUS_DATA_FORMAT_DIRECT,                           /***< Direct format. */
    PMBUS_DATA_FORMAT_ASCII,                            /***< ASCII format. */
    PMBUS_DATA_FORMAT_MAXIMUM,
} PMBUS_DATA_FORMAT_ENUM;


/** @struct PMBUS_CHANNEL_SELECT_ENUM
    @brief PMBUS channel select enum
*/
typedef enum _PMBUS_CHANNEL_SELECT_ENUM
{
    PMBUS_CHANNEL_SELECT_INVALID = 0,                   /***< Invalid channel select. */
    PMBUS_CHANNEL_SELECT_PAGED,                         /***< Paged channel select. */
    PMBUS_CHANNEL_SELECT_GLOBAL,                        /***< Global channel.  No page is selected prior to sending a command. */
    PMBUS_CHANNEL_SELECT_MAXIMUM,
} PMBUS_CHANNEL_SELECT_ENUM;

/** @enum PMBUS_ACCESS_TYPE_ENUM
@brief Bus access type
*/
typedef enum _PMBUS_ACCESS_TYPE_ENUM
{
    PMBUS_ACCESS_TYPE_NONE          = 0x0,              /***< Read transaction type */
    PMBUS_ACCESS_TYPE_READ          = 0x1,              /***< Read transaction type */
    PMBUS_ACCESS_TYPE_WRITE         = 0x2,              /***< Write transaction type */
    PMBUS_ACCESS_TYPE_READ_WRITE    = 0x3,              /***< Read/write transaction type */
} PMBUS_ACCESS_TYPE_ENUM;


typedef struct _PMBUS_COMMAND_INFO_TYPE
{
    uint32_t                      Command;                /***< Command. */
    uint32_t                      IoBufferSize;           /***< IO buffer size. */
    PMBUS_ACCESS_TYPE_ENUM        BusAccessType;          /***< Transaction type. */
    PMBUS_DATA_FORMAT_ENUM        DataFormat;             /***< Data format. */
    PMBUS_CHANNEL_SELECT_ENUM     ChannelSelect;          /***< Paged or global channel select. */
} PMBUS_COMMAND_INFO_TYPE, *PPMBUS_COMMAND_INFO_TYPE;



/** @struct PMBUS_DATA_SIZE_ENUM
    @brief PMBUS data type SIZE
*/
typedef enum _PMBUS_DATA_SIZE_ENUM
{
    PMBUS_INVALID_DATA_SIZE              = 0,
    PMBUS_BYTE_DATA_SIZE                 = sizeof(PMBUS_BYTE_TYPE),
    PMBUS_WORD_DATA_SIZE                 = sizeof(PMBUS_WORD_TYPE),
    PMBUS_BLOCK_DATA_SIZE                = sizeof(PMBUS_BLOCK_TYPE),
    PMBUS_COEFFICIENTS_BLOCK_DATA_SIZE   = 5,
    PMBUS_MAXIMUM_DATA_SIZE,
} PMBUS_DATA_SIZE_ENUM;

/** @enum PMBUS_STATUS_ENUM
    @brief PMBUS status
*/
typedef enum _PMBUS_STATUS_ENUM
{
    PMBUS_STATUS_INVALID = 0,
    PMBUS_STATUS_SUCCESS,
    PMBUS_STATUS_FAILURE,
    PMBUS_STATUS_BUS_BUSY,
    PMBUS_STATUS_BUS_READ_FAILURE,
    PMBUS_STATUS_BUS_WRITE_FAILURE,
    PMBUS_STATUS_DEVICE_NOT_FOUND,
    PMBUS_STATUS_BUS_INITIALIZATION_FAILURE,
    PMBUS_STATUS_INVALID_BUS_ACCESS_TYPE,
    PMBUS_STATUS_INVALID_BUFFER,
    PMBUS_STATUS_INVALID_HANDLE,
    PMBUS_STATUS_INVALID_DEVICE_ID,
    PMBUS_STATUS_INVALID_DEVICE_MAPPING,
    PMBUS_STATUS_INVALID_PARAMETERS,
    PMBUS_STATUS_INVALID_PARAMETER_1,
    PMBUS_STATUS_INVALID_PARAMETER_2,
    PMBUS_STATUS_INVALID_PARAMETER_3,
    PMBUS_STATUS_INVALID_PARAMETER_4,
    PMBUS_STATUS_INVALID_PARAMETER_5,
    PMBUS_STATUS_INVALID_APC_RAIL_ID,
    PMBUS_STATUS_NOT_SUPPORTED,
    PMBUS_STATUS_MAXIMUM,
} PMBUS_STATUS_ENUM;

/** @def IS_PMBUS_STATUS_SUCCESS
    @brief Macro to determine if the PMBUS STATUS is successful.
*/
#define IS_PMBUS_STATUS_SUCCESS(x) ((x) == PMBUS_STATUS_SUCCESS)
#define IS_PMBUS_STATUS_NOT_SUCCESS(x) (!IS_PMBUS_STATUS_SUCCESS(x))
#define ENCODE_PMBUS_STATUS(PmbusStatus, SmbusStatus) ((SmbusStatus) | ((PmbusStatus) << 16))
#define DECODE_PMBUS_STATUS(Status) (((Status) >> 16) & 0xFF)
#define DECODE_SMBUS_STATUS(Status) ((Status)&0xFFFF )


/** @enum PMBUS_PAGE_CHANNEL_SELECT_ENUM
    @brief Page channel select
*/
typedef enum _PMBUS_PAGE_CHANNEL_SELECT_ENUM
{
    PMBUS_PAGE_CHANNEL_SELECT_0     = 0x00,             /***< Page channel select 0 */
    PMBUS_PAGE_CHANNEL_SELECT_1     = 0x01,             /***< Page channel select 1 */
    PMBUS_PAGE_CHANNEL_SELECT_2	    = 0x2,
    PMBUS_PAGE_CHANNEL_SELECT_3	    = 0x3,
    PMBUS_PAGE_CHANNEL_SELECT_28    = 0x28,
    PMBUS_PAGE_CHANNEL_SELECT_29    = 0x29,
    PMBUS_PAGE_CHANNEL_SELECT_2A    = 0x2A,
    PMBUS_PAGE_CHANNEL_SELECT_ALL   = 0xFF,             /***< Page channel select all */
    PMBUS_PAGE_CHANNEL_SELECT_NONE  = 0xFFFF,           /***< Omit Page Selection even if Command is Paged*/
} PMBUS_PAGE_CHANNEL_SELECT_ENUM;


/** @enum PMBUS_OPERATION_ENUM
    @brief Operation modes.
*/
typedef enum _PMBUS_OPERATION_ENUM
{
    PMBUS_OPERATION_IMMEDIATE_OFF               = 0x04,             /***< Immediate off (no sequencing) */
    PMBUS_OPERATION_SOFT_OFF                    = 0x44,             /***< Soft-off (with sequencing) */
    PMBUS_OPERATION_ON_NOMINAL                  = 0x88,             /***< On - Nominal */
    PMBUS_OPERATION_ON_MARGIN_LOW               = 0x98,             /***< On - Margin low */
    PMBUS_OPERATION_ON_MARGIN_HIGH              = 0xA8,             /***< On - Margin high */
    PMBUS_OPERATION_SWITCH_TO_AVSBUS_CONTROL    = 0xB8,             /***< Switch to AVSBUS control */
} PMBUS_OPERATION_ENUM;


/** @enum PMBUS_OPERATION_OUTPUT_ENUM
    @brief Operation output configuration type to configure
           the interpretation and coordination of the OPERATION
           command and the ENABLE pin (EN).
*/
typedef enum _PMBUS_OPERATION_OUTPUT_ENUM
{
    PMBUS_OPERATION_OUTPUT_POWER_CONTROLLED                     = 0x00,     /***< Device starts any time power is present regardless of ENABLE pin or OPERATION command states. */
    PMBUS_OPERATION_OUTPUT_ENABLED_BY_PIN_WITH_SOFT_OFF         = 0x16,     /***< Device starts from ENABLE pin with soft-off. */
    PMBUS_OPERATION_OUTPUT_ENABLED_BY_PIN_WITH_IMMEDIATE_OFF    = 0x17,     /***< Device starts from ENABLE pin with immediate off. */
    PMBUS_OPERATION_OUTPUT_FROM_OPERATION_COMMAND               = 0x1A,     /***< Device starts from OPERATION command. */
} PMBUS_OPERATION_OUTPUT_ENUM;


/** @enum PMBUS_STATUS_BYTE_ENUM
    @brief Summary of the critical fault status values.
*/
typedef enum _PMBUS_STATUS_BYTE_ENUM
{
    PMBUS_STATUS_BYTE_INVALID           = 0x00,                             /***< Invalid status. */
    PMBUS_STATUS_BYTE_NONE_OF_THE_ABOVE = 0x01,                             /***< None of the above. */
    PMBUS_STATUS_BYTE_CML               = 0x02,                             /***< Communication, memory or logic fault occured. */
    PMBUS_STATUS_BYTE_TEMPERATURE       = 0x04,                             /***< Temperature fault or warning has occured. */
    PMBUS_STATUS_BYTE_VIN_UV_FAULT      = 0x08,                             /***< Input undervoltage fault has occured. */
    PMBUS_STATUS_BYTE_IOUT_OC_FAULT     = 0x10,                             /***< Output overcurrent fault has occured. */
    PMBUS_STATUS_BYTE_VOUT_OV_FAULT     = 0x20,                             /***< Output overvoltage fault has occured. */
    PMBUS_STATUS_BYTE_OFF               = 0x40,                             /***< The unit is not providing power to the ouptout, regardless of the reason, including simply not being enabled. */
    PMBUS_STATUS_BYTE_BUSY              = 0x80,                             /***< A fault was delcared because the device was busy and unable to respond. */
} PMBUS_STATUS_BYTE_ENUM;


/** @enum PMBUS_STATUS_WORD_ENUM
    @brief Extended critical fault status values.
*/
typedef enum _PMBUS_STATUS_WORD_ENUM
{
    PMBUS_STATUS_WORD_INVALID           = PMBUS_STATUS_BYTE_INVALID,            /***< Invalid status. */
    PMBUS_STATUS_WORD_NONE_OF_THE_ABOVE = PMBUS_STATUS_BYTE_NONE_OF_THE_ABOVE,  /***< None of the above. */
    PMBUS_STATUS_WORD_CML               = PMBUS_STATUS_BYTE_CML,                /***< Communication, memory or logic fault occured. */
    PMBUS_STATUS_WORD_TEMPERATURE       = PMBUS_STATUS_BYTE_TEMPERATURE,        /***< Temperature fault or warning has occured. */
    PMBUS_STATUS_WORD_VIN_UV_FAULT      = PMBUS_STATUS_BYTE_VIN_UV_FAULT,       /***< Input undervoltage fault has occured. */
    PMBUS_STATUS_WORD_IOUT_OC_FAULT     = PMBUS_STATUS_BYTE_IOUT_OC_FAULT,      /***< Output overcurrent fault has occured. */
    PMBUS_STATUS_WORD_VOUT_OV_FAULT     = PMBUS_STATUS_BYTE_VOUT_OV_FAULT,      /***< Output overvoltage fault has occured. */
    PMBUS_STATUS_WORD_OFF               = PMBUS_STATUS_BYTE_OFF,                /***< The unit is not providing power to the ouptout, regardless of the reason, including simply not being enabled. */
    PMBUS_STATUS_WORD_BUSY              = PMBUS_STATUS_BYTE_BUSY,               /***< A fault was delcared because the device was busy and unable to respond. */
    PMBUS_STATUS_WORD_UNKNOWN           = 0x0100,                               /***< A fault type not given in bits 15:1 of the STATUS_WORD has been detected. */
    PMBUS_STATUS_WORD_OTHER             = 0x0200,                               /***< A bit in STATUS_OTHER is set. */
    PMBUS_STATUS_WORD_FANS              = 0x0400,                               /***< A fan or airflow fault or warning has occurred. */
    PMBUS_STATUS_WORD_POWER_GOOD        = 0x0800,                               /***< The POWER_GOOD signal, if present, is negated. */
    PMBUS_STATUS_WORD_MFG_SPECIFIC      = 0x1000,                               /***< A manufacturer specific fault or warning has occurred. */
    PMBUS_STATUS_WORD_INPUT             = 0x2000,                               /***< An input voltage, input current, or input power fault or warning has occurred. */
    PMBUS_STATUS_WORD_IOUT_POUT         = 0x4000,                               /***< An output current or output power fault or warning has occurred. */
    PMBUS_STATUS_WORD_VOUT              = 0x8000,                               /***< An output voltage fault or warning has occurred. */
} PMBUS_STATUS_WORD_ENUM, *PPMBUS_STATUS_WORD_ENUM;


/** @enum PMBUS_OUTPUT_VOLTAGE_STATUS_ENUM
    @brief Summary of the output voltage status values.
*/
typedef enum _PMBUS_OUTPUT_VOLTAGE_STATUS_ENUM
{
    PMBUS_OUTPUT_VOLTAGE_STATUS_INVALID         = 0x00,                         /***< Invalid status. */
    PMBUS_OUTPUT_VOLTAGE_STATUS_RESERVED1       = 0x0F,                         /***< Not used. */
    PMBUS_OUTPUT_VOLTAGE_STATUS_VOUT_UV_FAULT   = 0x10,                         /***< Indicates an output undervoltage fault. */
    PMBUS_OUTPUT_VOLTAGE_STATUS_VOUT_UV_WARNING = 0x20,                         /***< Indicates an output undervoltage warning. */
    PMBUS_OUTPUT_VOLTAGE_STATUS_VOUT_OV_WARNING = 0x40,                         /***< Indicates an output overvoltage warning. */
    PMBUS_OUTPUT_VOLTAGE_STATUS_VOUT_OV_FAULT   = 0x80,                         /***< Indicates an output overvoltage fault. */
} PMBUS_OUTPUT_VOLTAGE_STATUS_ENUM, *PPMBUS_OUTPUT_VOLTAGE_STATUS_ENUM;


/** @enum PMBUS_OUTPUT_CURRENT_STATUS_ENUM
    @brief Summary of the output current status values.
*/
typedef enum _PMBUS_OUTPUT_CURRENT_STATUS_ENUM
{
    PMBUS_OUTPUT_CURRENT_STATUS_INVALID             = 0x00,                     /***< Invalid status. */
    PMBUS_OUTPUT_CURRENT_STATUS_RESERVED1           = 0x0F,                     /***< Not used. */
    PMBUS_OUTPUT_CURRENT_STATUS_IOUT_UC_FAULT       = 0x10,                     /***< Indicates an output undercurrent fault has occurred. */
    PMBUS_OUTPUT_CURRENT_STATUS_IOUT_OC_WARNING     = 0x20,                     /***< Indicates an output overcurrent warning has occurred. */
    PMBUS_OUTPUT_CURRENT_STATUS_IOUT_OC_LV_FAULT    = 0x40,                     /***< Indicates an output overcurrent and low voltage fault has occurred. */
    PMBUS_OUTPUT_CURRENT_STATUS_IOUT_OC_FAULT       = 0x80,                     /***< Indicates an output overcurrent fault has occurred. */
} PMBUS_OUTPUT_CURRENT_STATUS_ENUM, *PPMBUS_OUTPUT_CURRENT_STATUS_ENUM;


/** @enum PMBUS_STATUS_INPUT_ENUM
    @brief Input voltage and input current status values.
*/
typedef enum _PMBUS_STATUS_INPUT_ENUM
{
    PMBUS_STATUS_INPUT_INVALID          = 0x0,                                  /***< Invalid status. */
    PMBUS_STATUS_INPUT_RESERVED1        = 0x0F,                                 /***< Not used. */
    PMBUS_STATUS_INPUT_VIN_UV_FAULT     = 0x10,                                 /***< Indicates an input undervoltage fault has occurred. */
    PMBUS_STATUS_INPUT_VIN_UV_WARNING   = 0x20,                                 /***< Indicates an input undervoltage warning has occurred. */
    PMBUS_STATUS_INPUT_VIN_OV_WARNING   = 0x40,                                 /***< Indicates an input overvoltage warning has occurred. */
    PMBUS_STATUS_INPUT_VIN_OV_FAULT     = 0x80,                                 /***< Indicates an input overvoltage fault has occurred. */
} PMBUS_STATUS_INPUT_ENUM, *PPMBUS_STATUS_INPUT_ENUM;


/** @enum PMBUS_STATUS_TEMPERATURE_ENUM
    @brief Temperature specific status values.
*/
typedef enum _PMBUS_STATUS_TEMPERATURE_ENUM
{
    PMBUS_STATUS_TEMPERATURE_INVALID        = 0x00,                             /***< Invalid status. */
    PMBUS_STATUS_TEMPERATURE_RESERVED1      = 0x0F,                             /***< Not used. */
    PMBUS_STATUS_TEMPERATURE_VIN_UT_FAULT   = 0x10,                             /***< Indicates an under-temperature fault has occured. */
    PMBUS_STATUS_TEMPERATURE_VIN_UT_WARNING = 0x20,                             /***< Indicates an under-temperature warning has occured. */
    PMBUS_STATUS_TEMPERATURE_VIN_OT_WARNING = 0x40,                             /***< Indicates an over-temperature warning has occured. */
    PMBUS_STATUS_TEMPERATURE_VIN_OT_FAULT   = 0x80,                             /***< Indicates an over-temperature fault has occured. */

} PMBUS_STATUS_TEMPERATURE_ENUM, *PPMBUS_STATUS_TEMPERATURE_ENUM;


/** @enum PMBUS_STATUS_CML_ENUM
    @brief Communication, logic, and memory specific status values.
*/
typedef enum _PMBUS_STATUS_CML_ENUM
{
    PMBUS_STATUS_CML_INVALID                                = 0x00,             /***< Invalid status. */
    PMBUS_STATUS_CML_RESERVED1                              = 0x01,             /***< Not used. */
    PMBUS_STATUS_CML_PMBUS_COMMAND_INVALID_ACCESS           = 0x02,             /***< Indicates a PMBus command tried to write to a read-only or protected command, or a communication fault other than the ones listed in this table has occurred. */
    PMBUS_STATUS_CML_RESERVED2                              = 0x1C,             /***< Not used. */
    PMBUS_STATUS_CML_PMBUS_COMMAND_PACKET_ERROR_DETECTED    = 0x20,             /***< Indicates a packet error was detected in the PMBus command. */
    PMBUS_STATUS_CML_PMBUS_COMMAND_INVALID_DATA             = 0x40,             /***< Indicates a PMBus command was sent with invalid or unsupported data. */
    PMBUS_STATUS_CML_RECEIVED_INVALID_PMBUS_COMMAND         = 0x80,             /***< Indicates an invalid or unsupported PMBus command was received. */
} PMBUS_STATUS_CML_ENUM, *PPMBUS_STATUS_CML_ENUM;


/** @struct PMBUS_PAGE_CHANNEL_SELECT_TYPE
    @brief Page channel select type to configure the page channel.
*/
typedef struct _PMBUS_PAGE_CHANNEL_SELECT_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_ENUM  PageChannelSelect;  /***< Selects page channel 0, 1 or both. */
    PMBUS_ACCESS_TYPE_ENUM          BusAccessType;      /***< Transaction type. */
} PMBUS_PAGE_CHANNEL_SELECT_TYPE, *PPMBUS_PAGE_CHANNEL_SELECT_TYPE;


/** @struct PMBUS_OPERATION_CONFIGURATION_TYPE
    @brief Operation configuration type to configure the operation margins.

    Sets enable, disable and VOUT margin settings.  Data values of OPERATION
    that force margin high or low only take effect when the MGN pin is left
    open (i.e., in the nominal margin state)
*/
typedef struct _PMBUS_OPERATION_CONFIGURATION_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_OPERATION_ENUM            OperationMode;      /***< Operation mode to enable, disable and VOUT margin modes. */
} PMBUS_OPERATION_CONFIGURATION_TYPE, *PPMBUS_OPERATION_CONFIGURATION_TYPE;


/** @struct PMBUS_OPERATION_OUTPUT_CONFIGURATION_TYPE
    @brief Operation output configuration type to configure the operation enable.

    Configures the interpretation and coordination of the OPERATION command and the ENABLE pin (EN).
*/
typedef struct _PMBUS_OPERATION_OUTPUT_CONFIGURATION_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_OPERATION_OUTPUT_ENUM     OperationOutput;    /***< Operation output to interpret and coordinate  the OPERATION command and the ENABLE pin (EN). */
} PMBUS_OPERATION_OUTPUT_CONFIGURATION_TYPE, *PPMBUS_OPERATION_OUTPUT_CONFIGURATION_TYPE;


/** @struct PMBUS_PHASE_TYPE
    @brief PHASE command to control multiple phase on one PMBus unit.

    Configure, control, and monitor multiple phases on one PMBus unit..
*/
typedef struct _PMBUS_PHASE_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_BYTE_TYPE                 Phase;              /***< Phase. */
} PMBUS_PHASE_TYPE, *PPMBUS_PHASE_TYPE;


/** @struct PMBUS_VOLTAGE_LEVEL_TYPE
    @brief VOUT Command type to set the nominal value of the output voltage.

    Sets or reports the target output voltage. This voltage level cannot be set a value higher
    than either VOUT_MAX or 110% of the pin-strap VOUT setting.
*/
typedef struct _PMBUS_VOLTAGE_LEVEL_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 VoltageLevel;       /***< Voltage level. */
} PMBUS_VOLTAGE_LEVEL_TYPE, *PPMBUS_VOLTAGE_LEVEL_TYPE;


/** @struct PMBUS_CURRENT_LEVEL_TYPE
    @brief IOUT Command type to set the nominal value of the output voltage.

    Sets or reports the target output current.
*/
typedef struct _PMBUS_CURRENT_LEVEL_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 CurrentLevel;       /***< Current level. */
} PMBUS_CURRENT_LEVEL_TYPE, *PPMBUS_CURRENT_LEVEL_TYPE;


/** @struct PMBUS_VOUT_CAL_OFFSET_TYPE
    @brief VOUT calibration offset type to set a fixed voltage offset.

    The VOUT_CAL_OFFSET command is used to apply a fixed offset voltage to the output voltage command
    value. This command is typically used by the user to calibrate a device in the application circuit.

*/
typedef struct _PMBUS_VOUT_CAL_OFFSET_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 VoltageOffset;      /***< Voltage offset calibration. */
} PMBUS_VOUT_CAL_OFFSET_TYPE, *PPMBUS_VOUT_CAL_OFFSET_TYPE;


/** @struct PMBUS_VOUT_MARGIN_TYPE
    @brief VOUT margin type to set voltage output high/low margins.

    Sets the value of the VOUT during a margin low/high. This VOUT_MARGIN_LOW/VOUT_MARGIN_HIGH
    command loads the unit with the voltage to which the output is to be changed when the OPERATION
    command is set to "Margin Low"/"Margin High".
*/
typedef struct _PMBUS_VOUT_MARGIN_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 VoltageMargin;      /***< Voltage margin. */
} PMBUS_VOUT_MARGIN_TYPE, *PPMBUS_VOUT_MARGIN_TYPE;


/** @struct PMBUS_VOLTAGE_TRANSITION_RATE_TYPE
    @brief Voltage transition rate type to set the transition rate during margin or other change of Vout.

    Sets the rate at which the output should change voltage when the device receives an
    OPERATION command (marging high, marging low) which causes the output voltage to change.
    The maximum poissible positive value of the two data bytes indicates that the device
    should make the transition as quickly as possible.
*/
typedef struct _PMBUS_VOLTAGE_TRANSITION_RATE_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 TransitionRate;     /***< Output voltage transition rate. */
} PMBUS_VOLTAGE_TRANSITION_RATE_TYPE, *PPMBUS_VOLTAGE_TRANSITION_RATE_TYPE;


/** @struct PMBUS_VOLTAGE_DROOP_TYPE
    @brief Voltage droop rate type to read the loadline (V/I Slope) resistance for the rail.

    The VOUT_DROOP sets the effective load line (V/I slope) for the rail in which the device is used.
    It is the rate, in mV/A at which the output voltage decreases (or increases) with increasing
    (or decreasing) output current for use with adaptive voltage positioning schemes.
*/
typedef struct _PMBUS_VOLTAGE_DROOP_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 VoltageDroop;       /***< Output voltage droop. */
} PMBUS_VOLTAGE_DROOP_TYPE, *PPMBUS_VOLTAGE_DROOP_TYPE;


/** @struct PMBUS_VOLTAGE_THRESHOLD_TYPE
    @brief Voltage threshold type to set/read the Vout overvoltage threshold.

    Sets the Vout overvoltage fault threshold.
*/
typedef struct _PMBUS_VOLTAGE_THRESHOLD_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 Threshold;          /***< Output voltage overvoltage/undervoltage threshold limit. */
} PMBUS_VOLTAGE_THRESHOLD_TYPE, *PPMBUS_VOLTAGE_THRESHOLD_TYPE;


/** @struct PMBUS_TEMPERATURE_FAULT_THRESHOLD_TYPE
    @brief Temperature fault threshold type to set/read the over temperature fault threshold.

    Gets/Sets the over temperature fault threshold.
*/
typedef struct _PMBUS_TEMPERATURE_THRESHOLD_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 Threshold;          /***< Temperature threshold limit. */
} PMBUS_TEMPERATURE_THRESHOLD_TYPE, *PPMBUS_TEMPERATURE_THRESHOLD_TYPE;


/** @struct PMBUS_TIME_TYPE
    @brief Time type used to set/read the power ON/OFF time delay/rise.
*/
typedef struct _PMBUS_TIME_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 Time;               /***< Time. */
} PMBUS_TIME_TYPE, *PPMBUS_TIME_TYPE;


/** @struct PMBUS_TEMPERATURE_FAULT_THRESHOLD_TYPE
    @brief Temperature fault threshold type to set/read the over temperature fault threshold.

    Gets/Sets the over temperature fault threshold.
*/
typedef struct _PMBUS_TEMPERATURE_FAULT_THRESHOLD_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 FaultThreshold;     /***< Over temperature fault limit. */
} PMBUS_TEMPERATURE_FAULT_THRESHOLD_TYPE, *PPMBUS_TEMPERATURE_FAULT_THRESHOLD_TYPE;


/** @struct PMBUS_STATUS_BYTE_TYPE
    @brief Returns an abbreviated status for fast reads.
*/
typedef struct _PMBUS_STATUS_BYTE_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_STATUS_BYTE_ENUM          Status;             /***< Status. */
} PMBUS_STATUS_BYTE_TYPE, *PPMBUS_STATUS_BYTE_TYPE;


/** @struct PMBUS_STATUS_WORD_TYPE
    @brief Returns a summary of the unit's fault conditions.
*/
typedef struct _PMBUS_STATUS_WORD_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_STATUS_WORD_ENUM          Status;             /***< Status. */
} PMBUS_STATUS_WORD_TYPE, *PPMBUS_STATUS_WORD_TYPE;


/** @struct PMBUS_OUTPUT_VOLTAGE_STATUS_TYPE
    @brief Output voltage status
*/
typedef struct _PMBUS_OUTPUT_VOLTAGE_STATUS_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE      Device;         /***< Device page channel select and bus access type. */
    PMBUS_OUTPUT_VOLTAGE_STATUS_ENUM    Status;         /***< Status. */
} PMBUS_OUTPUT_VOLTAGE_STATUS_TYPE, *PPMBUS_OUTPUT_VOLTAGE_STATUS_TYPE;


/** @struct PMBUS_OUTPUT_CURRENT_STATUS_TYPE
    @brief Output current status
*/
typedef struct _PMBUS_OUTPUT_CURRENT_STATUS_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE      Device;         /***< Device page channel select and bus access type. */
    PMBUS_OUTPUT_CURRENT_STATUS_ENUM    Status;         /***< Status. */
} PMBUS_OUTPUT_CURRENT_STATUS_TYPE, *PPMBUS_OUTPUT_CURRENT_STATUS_TYPE;


/** @struct PMBUS_STATUS_TEMPERATURE_TYPE
    @brief Temperature status type to return the temperature specific status.

    The STATUS_TEMPERATURE command returns one byte of information with a summary of any
    temperature related faults or warnings.
*/
typedef struct _PMBUS_STATUS_TEMPERATURE_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_STATUS_TEMPERATURE_ENUM   Status;             /***< Status. */
} PMBUS_STATUS_TEMPERATURE_TYPE, *PPMBUS_STATUS_TEMPERATURE_TYPE;


/** @struct PMBUS_TEMPERATURE_TYPE
    @brief Temperature monitor type to return the temperature reading.
*/
typedef struct _PMBUS_TEMPERATURE_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 Temperature;        /***< Temperature. */
} PMBUS_TEMPERATURE_TYPE, *PPMBUS_TEMPERATURE_TYPE;


/** @struct PMBUS_POWER_TYPE
    @brief Power type to report the output power.
*/
typedef struct _PMBUS_POWER_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_WORD_TYPE                 Power;              /***< Power. */
} PMBUS_POWER_TYPE, *PPMBUS_POWER_TYPE;


/** @struct PMBUS_MANUFACTURER_INFO_TYPE
    @brief Manufacturer info
*/
typedef struct _PMBUS_MANUFACTURER_INFO_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_BLOCK_TYPE                ManufacturerInfo;   /***< Manufacturer data. */
} PMBUS_MANUFACTURER_INFO_TYPE, *PPMBUS_MANUFACTURER_INFO_TYPE;


/** @struct PMBUS_PMBUS_REVISION_TYPE
    @brief PMBUS revision
*/
typedef struct _PMBUS_PMBUS_REVISION_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;             /***< Device page channel select and bus access type. */
    PMBUS_BLOCK_TYPE                Revision;           /***< PMBUS revision. */
} PMBUS_PMBUS_REVISION_TYPE, *PPMBUS_PMBUS_REVISION_TYPE;


/** @struct PMBUS_COEFFICIENTS_TYPE
    @brief Operation output configuration type to configure the operation enable.

    Configures the interpretation and coordination of the OPERATION command and the ENABLE pin (EN).
*/
typedef struct _PMBUS_COEFFICIENTS_TYPE
{
    PMBUS_PAGE_CHANNEL_SELECT_TYPE  Device;                                             /***< Device page channel select and bus access type. */
    uint8_t                   Coefficients[PMBUS_COEFFICIENTS_BLOCK_DATA_SIZE];   /***< Coefficient array. */
} PMBUS_COEFFICIENTS_TYPE, *PPMBUS_COEFFICIENTS_TYPE;

/*----------------------------- PMBUS COMMANDS AND CONFIGURATION-------------------------------------------*/

// COMMANDS
#define PMBUS_PAGE_COMMAND                                      0x00
#define PMBUS_OPERATION_COMMAND                                 0x01
#define PMBUS_ON_OFF_CONFIG_COMMAND                             0x02
#define PMBUS_CLEAR_FAULTS_COMMAND                              0x03
#define PMBUS_PHASE_COMMAND                                     0x04
#define PMBUS_05_COMMAND					0x05
#define PMBUS_WRITE_PROTECT_COMMAND                             0x10
#define PMBUS_VOUT_MODE_COMMAND                                 0x20
#define PMBUS_VOUT_COMMAND_COMMAND                              0x21
#define PMBUS_VOUT_TRIM_COMMAND                                 0x22
#define PMBUS_VOUT_CAL_OFFSET_COMMAND                           0x1E
#define PMBUS_VOUT_MAX_COMMAND                                  0x24
#define PMBUS_VOUT_MARGIN_HIGH_COMMAND                          0x25
#define PMBUS_VOUT_MARGIN_LOW_COMMAND                           0x26
#define PMBUS_VOUT_TRANSITION_RATE_COMMAND                      0x27
#define PMBUS_VOUT_DROOP_COMMAND                                0x28
#define PMBUS_VOUT_MIN_COMMAND                                  0x2B
#define PMBUS_VOUT_OV_FAULT_LIMIT_COMMAND                       0x40
#define PMBUS_VOUT_UV_FAULT_LIMIT_COMMAND                       0x44
#define PMBUS_OT_FAULT_LIMIT_COMMAND                            0x4F
#define PMBUS_OT_WARN_LIMIT_COMMAND                             0x51
#define PMBUS_VIN_OV_FAULT_LIMIT_COMMAND                        0x55
#define PMBUS_VIN_UV_FAULT_LIMIT_COMMAND                        0x59
#define PMBUS_IIN_OC_FAULT_LIMIT_COMMAND                        0x5B
#define PMBUS_TON_DELAY_COMMAND                                 0x60
#define PMBUS_TON_RISE_COMMAND                                  0x61
#define PMBUS_TOFF_DELAY_COMMAND                                0x64
#define PMBUS_TOFF_FALL_COMMAND                                 0x65
#define PMBUS_STATUS_BYTE_COMMAND                               0x78
#define PMBUS_STATUS_WORD_COMMAND                               0x79
#define PMBUS_STATUS_VOUT_COMMAND                               0x7A
#define PMBUS_STATUS_IOUT_COMMAND                               0x7B
#define PMBUS_STATUS_INPUT_COMMAND                              0x7C
#define PMBUS_STATUS_TEMPERATURE_COMMAND                        0x7D
#define PMBUS_STATUS_CML_COMMAND                                0x7E
#define PMBUS_STATUS_MFR_SPECIFIC_COMMAND                       0x80
#define PMBUS_READ_VIN_COMMAND                                  0x88
#define PMBUS_READ_IIN_COMMAND                                  0x89
#define PMBUS_READ_VOUT_COMMAND                                 0x8B
#define PMBUS_READ_IOUT_COMMAND                                 0x8C
#define PMBUS_READ_TEMPERATURE_1_COMMAND                        0x8D
#define PMBUS_READ_TEMPERATURE_2_COMMAND                        0x8E
#define PMBUS_READ_TEMPERATURE_3_COMMAND                        0x8F
#define PMBUS_READ_POUT_COMMAND                                 0x96
#define PMBUS_READ_PIN_COMMAND                                  0x97
#define PMBUS_PMBUS_REVISION_COMMAND                            0x98
#define PMBUS_MFR_ID_COMMAND                                    0x99
#define PMBUS_MFR_MODEL_COMMAND                                 0x9A
#define PMBUS_MFR_DATE_COMMAND                                  0x9D
#define PMBUS_LOOP_CONFIG_COMMAND                               0xF0
#define PMBUS_RESTORE_CONFIG_COMMAND                            0xF2
#define PMBUS_IC_DEVICE_ID_COMMAND                              0xAD
#define PMBUS_IC_DEVICE_REV_COMMAND                             0xAE
#define PMBUS_APPLY_SETTINGS_COMMAND                            0xE7
#define PMBUS_RESTORE_CONFIG_COMMAND                            0xF2

/* More PMBUS commands */
#define PMBUS_0D_COMMAND					0x0D
#define PMBUS_1D_COMMAND					0x1D
#define PMBUS_5E_COMMAND					0x5E

#define PMBUS_0D_COMMAND_LENGTH                               PMBUS_WORD_DATA_SIZE
#define PMBUS_0D_CHANNEL_SELECT                               PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_0D_DATA_FORMAT                                  PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_0D_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_0D_DEFAULT                                      PMBUS_PAGE_CHANNEL_SELECT_2
#define PMBUS_0D_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE

#define PMBUS_1D_COMMAND_LENGTH                               PMBUS_WORD_DATA_SIZE
#define PMBUS_1D_CHANNEL_SELECT                               PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_1D_DATA_FORMAT                                  PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_1D_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_1D_DEFAULT                                      PMBUS_PAGE_CHANNEL_SELECT_2
#define PMBUS_1D_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE

#define PMBUS_5E_COMMAND_LENGTH                               PMBUS_WORD_DATA_SIZE
#define PMBUS_5E_CHANNEL_SELECT                               PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_5E_DATA_FORMAT                                  PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_5E_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_5E_DEFAULT                                      PMBUS_PAGE_CHANNEL_SELECT_0
#define PMBUS_5E_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE

#define PMBUS_05_COMMAND_LENGTH                               PMBUS_WORD_DATA_SIZE
#define PMBUS_05_CHANNEL_SELECT                               PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_05_DATA_FORMAT                                  PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_05_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_05_DEFAULT                                      PMBUS_PAGE_CHANNEL_SELECT_0
#define PMBUS_05_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE

// Command configurations

// PMBUS_COMMAND_PAGE
#define PMBUS_PAGE_COMMAND_LENGTH                               PMBUS_BYTE_DATA_SIZE
#define PMBUS_PAGE_CHANNEL_SELECT                               PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_PAGE_DATA_FORMAT                                  PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_PAGE_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_PAGE_DEFAULT                                      PMBUS_PAGE_CHANNEL_SELECT_0
#define PMBUS_PAGE_BUS_ACCESS                                   PMBUS_ACCESS_TYPE_READ_WRITE

// PMBUS_COMMAND_OPERATION
#define PMBUS_OPERATION_COMMAND_LENGTH                          PMBUS_BYTE_DATA_SIZE
#define PMBUS_OPERATION_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_OPERATION_DATA_FORMAT                             PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_OPERATION_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_OPERATION_DEFAULT                                 0x08


// PMBUS_COMMAND_ON_OFF_CONFIG
#define PMBUS_ON_OFF_CONFIG_COMMAND_LENGTH                      PMBUS_BYTE_DATA_SIZE
#define PMBUS_ON_OFF_CONFIG_CHANNEL_SELECT                      PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_ON_OFF_CONFIG_DATA_FORMAT                         PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_ON_OFF_CONFIG_BUS_ACCESS                          PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_ON_OFF_CONFIG_DEFAULT                             0x16


// PMBUS_COMMAND_CLEAR_FAULTS
#define PMBUS_CLEAR_FAULTS_COMMAND_LENGTH                       PMBUS_INVALID_DATA_SIZE
#define PMBUS_CLEAR_FAULTS_CHANNEL_SELECT                       PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_CLEAR_FAULTS_DATA_FORMAT                          PMBUS_DATA_FORMAT_INVALID
#define PMBUS_CLEAR_FAULTS_BUS_ACCESS                           PMBUS_ACCESS_TYPE_WRITE


// PMBUS_PHASE_COMMAND
#define PMBUS_PHASE_COMMAND_LENGTH                              PMBUS_BYTE_DATA_SIZE
#define PMBUS_PHASE_CHANNEL_SELECT                              PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_PHASE_DATA_FORMAT                                 PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_PHASE_BUS_ACCESS                                  PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_PHASE_DEFAULT                                     0xFF


// PMBUS_WRITE_PROTECT
#define PMBUS_WRITE_PROTECT_COMMAND_LENGTH                      PMBUS_BYTE_DATA_SIZE
#define PMBUS_WRITE_PROTECT_CHANNEL_SELECT                      PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_WRITE_PROTECT_DATA_FORMAT                         PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_WRITE_PROTECT_BUS_ACCESS                          PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_WRITE_PROTECT_DEFAULT                             0x00


// PMBUS_VOUT_MODE
#define PMBUS_VOUT_MODE_COMMAND_LENGTH                          PMBUS_BYTE_DATA_SIZE
#define PMBUS_VOUT_MODE_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_VOUT_MODE_DATA_FORMAT                             PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_VOUT_MODE_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ
#define PMBUS_VOUT_MODE_DEFAULT                                 0x40


// PMBUS_COEFFICIENTS_COMMAND
#define PMBUS_COEFFICIENTS_COMMAND_LENGTH                       PMBUS_COEFFICIENTS_BLOCK_DATA_SIZE
#define PMBUS_COEFFICIENTS_CHANNEL_SELECT                       PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_COEFFICIENTS_DATA_FORMAT                          PMBUS_DATA_FORMAT_INVALID
#define PMBUS_COEFFICIENTS_BUS_ACCESS                           PMBUS_ACCESS_TYPE_READ_WRITE


// PMBUS_COMMAND_VOUT_COMMAND
#define PMBUS_VOUT_COMMAND_COMMAND_LENGTH                       PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_COMMAND_CHANNEL_SELECT                       PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_COMMAND_DATA_FORMAT                          PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_COMMAND_BUS_ACCESS                           PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_COMMAND_DEFAULT                              0x0384


// PMBUS_VOUT_TRIM_COMMAND
#define PMBUS_VOUT_TRIM_COMMAND_LENGTH                          PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_TRIM_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_TRIM_DATA_FORMAT                             PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_TRIM_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_TRIM_DEFAULT                                 0x0000


// PMBUS_VOUT_CAL_OFFSET_COMMAND
#define PMBUS_VOUT_CAL_OFFSET_COMMAND_LENGTH                    PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_CAL_OFFSET_CHANNEL_SELECT                    PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_CAL_OFFSET_DATA_FORMAT                       PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_CAL_OFFSET_BUS_ACCESS                        PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_CAL_OFFSET_DEFAULT                           0x0000

// PMBUS_VOUT_MAX_COMMAND
#define PMBUS_VOUT_MAX_COMMAND_LENGTH                           PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_MAX_CHANNEL_SELECT                           PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_MAX_DATA_FORMAT                              PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_MAX_BUS_ACCESS                               PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_MAX_DEFAULT                                  0x08FC


// PMBUS_VOUT_MARGIN_HIGH_COMMAND
#define PMBUS_VOUT_MARGIN_HIGH_COMMAND_LENGTH                   PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_MARGIN_HIGH_CHANNEL_SELECT                   PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_MARGIN_HIGH_DATA_FORMAT                      PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_MARGIN_HIGH_BUS_ACCESS                       PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_MARGIN_HIGH_DEFAULT                          0x0640


// PMBUS_VOUT_MARGIN_LOW_COMMAND
#define PMBUS_VOUT_MARGIN_LOW_COMMAND_LENGTH                    PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_MARGIN_LOW_CHANNEL_SELECT                    PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_MARGIN_LOW_DATA_FORMAT                       PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_MARGIN_LOW_BUS_ACCESS                        PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_MARGIN_LOW_DEFAULT                           0x00FA


// PMBUS_VOUT_TRANSITION_RATE_COMMAND
#define PMBUS_VOUT_TRANSITION_RATE_COMMAND_LENGTH               PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_TRANSITION_RATE_CHANNEL_SELECT               PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_TRANSITION_RATE_DATA_FORMAT                  PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_TRANSITION_RATE_BUS_ACCESS                   PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_TRANSITION_RATE_DEFAULT                      0x0064


//PMBUS_VOUT_DROOP_COMMAND
#define PMBUS_VOUT_DROOP_COMMAND_LENGTH                         PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_DROOP_CHANNEL_SELECT                         PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_DROOP_DATA_FORMAT                            PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_DROOP_BUS_ACCESS                             PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_DROOP_DEFAULT                                0x0000


//PMBUS_VOUT_MIN_COMMAND
#define PMBUS_VOUT_MIN_COMMAND_LENGTH                           PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_MIN_CHANNEL_SELECT                           PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_MIN_DATA_FORMAT                              PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_MIN_BUS_ACCESS                               PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_MIN_DEFAULT                                  0x0000


// PMBUS_VOUT_OV_FAULT_LIMIT_COMMAND
#define PMBUS_VOUT_OV_FAULT_LIMIT_COMMAND_LENGTH                PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_OV_FAULT_LIMIT_CHANNEL_SELECT                PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_OV_FAULT_LIMIT_DATA_FORMAT                   PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_OV_FAULT_LIMIT_BUS_ACCESS                    PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_OV_FAULT_LIMIT_DEFAULT                       0x076C


// PMBUS_VOUT_UV_FAULT_LIMIT_COMMAND
#define PMBUS_VOUT_UV_FAULT_LIMIT_COMMAND_LENGTH                PMBUS_WORD_DATA_SIZE
#define PMBUS_VOUT_UV_FAULT_LIMIT_CHANNEL_SELECT                PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_VOUT_UV_FAULT_LIMIT_DATA_FORMAT                   PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VOUT_UV_FAULT_LIMIT_BUS_ACCESS                    PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VOUT_UV_FAULT_LIMIT_DEFAULT                       0x0000


// PMBUS_OT_FAULT_LIMIT_COMMAND
#define PMBUS_OT_FAULT_LIMIT_COMMAND_LENGTH                     PMBUS_WORD_DATA_SIZE
#define PMBUS_OT_FAULT_LIMIT_CHANNEL_SELECT                     PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_OT_FAULT_LIMIT_DATA_FORMAT                        PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_OT_FAULT_LIMIT_BUS_ACCESS                         PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_OT_FAULT_LIMIT_DEFAULT                            0x007D


// PMBUS_OT_WARN_LIMIT_COMMAND
#define PMBUS_OT_WARN_LIMIT_COMMAND_LENGTH                      PMBUS_WORD_DATA_SIZE
#define PMBUS_OT_WARN_LIMIT_CHANNEL_SELECT                      PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_OT_WARN_LIMIT_DATA_FORMAT                         PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_OT_WARN_LIMIT_BUS_ACCESS                          PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_OT_WARN_LIMIT_DEFAULT                             0x07D0


// PMBUS_VIN_OV_FAULT_LIMIT_COMMAND
#define PMBUS_VIN_OV_FAULT_LIMIT_COMMAND_LENGTH                 PMBUS_WORD_DATA_SIZE
#define PMBUS_VIN_OV_FAULT_LIMIT_CHANNEL_SELECT                 PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_VIN_OV_FAULT_LIMIT_DATA_FORMAT                    PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VIN_OV_FAULT_LIMIT_BUS_ACCESS                     PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VIN_OV_FAULT_LIMIT_DEFAULT                        0x36B0


// PMBUS_VIN_UV_FAULT_LIMIT_COMMAND
#define PMBUS_VIN_UV_FAULT_LIMIT_COMMAND_LENGTH                 PMBUS_WORD_DATA_SIZE
#define PMBUS_VIN_UV_FAULT_LIMIT_CHANNEL_SELECT                 PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_VIN_UV_FAULT_LIMIT_DATA_FORMAT                    PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_VIN_UV_FAULT_LIMIT_BUS_ACCESS                     PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_VIN_UV_FAULT_LIMIT_DEFAULT                        0x1F40


// PMBUS_IIN_OC_FAULT_LIMIT_COMMAND
#define PMBUS_IIN_OC_FAULT_LIMIT_COMMAND_LENGTH                 PMBUS_WORD_DATA_SIZE
#define PMBUS_IIN_OC_FAULT_LIMIT_CHANNEL_SELECT                 PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_IIN_OC_FAULT_LIMIT_DATA_FORMAT                    PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_IIN_OC_FAULT_LIMIT_BUS_ACCESS                     PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_IIN_OC_FAULT_LIMIT_DEFAULT                        0x0032


// PMBUS_TON_DELAY_COMMAND
#define PMBUS_TON_DELAY_COMMAND_LENGTH                          PMBUS_WORD_DATA_SIZE
#define PMBUS_TON_DELAY_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_TON_DELAY_DATA_FORMAT                             PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_TON_DELAY_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_TON_DELAY_DEFAULT                                 0x0014


// PMBUS_TON_DELAY_COMMAND
#define PMBUS_TON_RISE_COMMAND_LENGTH                           PMBUS_WORD_DATA_SIZE
#define PMBUS_TON_RISE_CHANNEL_SELECT                           PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_TON_RISE_DATA_FORMAT                              PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_TON_RISE_BUS_ACCESS                               PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_TON_RISE_DEFAULT                                  0x01F4


// PMBUS_TOFF_DELAY_COMMAND
#define PMBUS_TOFF_DELAY_COMMAND_LENGTH                         PMBUS_WORD_DATA_SIZE
#define PMBUS_TOFF_DELAY_CHANNEL_SELECT                         PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_TOFF_DELAY_DATA_FORMAT                            PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_TOFF_DELAY_BUS_ACCESS                             PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_TOFF_DELAY_DEFAULT                                0x0000


// PMBUS_TOFF_FALL_COMMAND
#define PMBUS_TOFF_FALL_COMMAND_LENGTH                          PMBUS_WORD_DATA_SIZE
#define PMBUS_TOFF_FALL_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_TOFF_FALL_DATA_FORMAT                             PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_TOFF_FALL_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ_WRITE
#define PMBUS_TOFF_FALL_DEFAULT                                 0x01F4


// PMBUS_STATUS_BYTE_COMMAND
#define PMBUS_STATUS_BYTE_COMMAND_LENGTH                        PMBUS_WORD_DATA_SIZE
#define PMBUS_STATUS_BYTE_CHANNEL_SELECT                        PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_STATUS_BYTE_DATA_FORMAT                           PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_STATUS_BYTE_BUS_ACCESS                            PMBUS_ACCESS_TYPE_READ
#define PMBUS_STATUS_BYTE_DEFAULT                               0x0000


// PMBUS_STATUS_WORD_COMMAND
#define PMBUS_STATUS_WORD_COMMAND_LENGTH                        PMBUS_WORD_DATA_SIZE
#define PMBUS_STATUS_WORD_CHANNEL_SELECT                        PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_STATUS_WORD_DATA_FORMAT                           PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_STATUS_WORD_BUS_ACCESS                            PMBUS_ACCESS_TYPE_READ
#define PMBUS_STATUS_WORD_DEFAULT                               0x0000


// PMBUS_STATUS_VOUT_COMMAND
#define PMBUS_STATUS_VOUT_COMMAND_LENGTH                        PMBUS_BYTE_DATA_SIZE
#define PMBUS_STATUS_VOUT_CHANNEL_SELECT                        PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_STATUS_VOUT_DATA_FORMAT                           PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_STATUS_VOUT_BUS_ACCESS                            PMBUS_ACCESS_TYPE_READ
#define PMBUS_STATUS_VOUT_DEFAULT                               0x00


// PMBUS_STATUS_IOUT_COMMAND
#define PMBUS_STATUS_IOUT_COMMAND_LENGTH                        PMBUS_BYTE_DATA_SIZE
#define PMBUS_STATUS_IOUT_CHANNEL_SELECT                        PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_STATUS_IOUT_DATA_FORMAT                           PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_STATUS_IOUT_BUS_ACCESS                            PMBUS_ACCESS_TYPE_READ
#define PMBUS_STATUS_IOUT_DEFAULT                               0x00


// PMBUS_STATUS_INPUT_COMMAND
#define PMBUS_STATUS_INPUT_COMMAND_LENGTH                       PMBUS_BYTE_DATA_SIZE
#define PMBUS_STATUS_INPUT_CHANNEL_SELECT                       PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_STATUS_INPUT_DATA_FORMAT                          PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_STATUS_INPUT_BUS_ACCESS                           PMBUS_ACCESS_TYPE_READ
#define PMBUS_STATUS_INPUT_DEFAULT                              0x00


// PMBUS_STATUS_TEMPERATURE_COMMAND
#define PMBUS_STATUS_TEMPERATURE_COMMAND_LENGTH                 PMBUS_BYTE_DATA_SIZE
#define PMBUS_STATUS_TEMPERATURE_CHANNEL_SELECT                 PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_STATUS_TEMPERATURE_DATA_FORMAT                    PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_STATUS_TEMPERATURE_BUS_ACCESS                     PMBUS_ACCESS_TYPE_READ
#define PMBUS_STATUS_TEMPERATURE_DEFAULT                        0x00


// PMBUS_STATUS_CML_COMMAND
#define PMBUS_STATUS_CML_COMMAND_LENGTH                         PMBUS_BYTE_DATA_SIZE
#define PMBUS_STATUS_CML_CHANNEL_SELECT                         PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_STATUS_CML_DATA_FORMAT                            PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_STATUS_CML_BUS_ACCESS                             PMBUS_ACCESS_TYPE_READ
#define PMBUS_STATUS_CML_DEFAULT                                0x00


// PMBUS_STATUS_MFR_COMMAND
#define PMBUS_STATUS_MFR_SPECIFIC_COMMAND_LENGTH                PMBUS_BYTE_DATA_SIZE
#define PMBUS_STATUS_MFR_SPECIFIC_CHANNEL_SELECT                PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_STATUS_MFR_SPECIFIC_DATA_FORMAT                   PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_STATUS_MFR_SPECIFIC_BUS_ACCESS                    PMBUS_ACCESS_TYPE_READ
#define PMBUS_STATUS_MFR_SPECIFIC_DEFAULT                       0x00


// PMBUS_READ_VIN_COMMAND
#define PMBUS_READ_VIN_COMMAND_LENGTH                           PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_VIN_CHANNEL_SELECT                           PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_READ_VIN_DATA_FORMAT                              PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_VIN_BUS_ACCESS                               PMBUS_ACCESS_TYPE_READ


// PMBUS_READ_IIN_COMMAND
#define PMBUS_READ_IIN_COMMAND_LENGTH                           PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_IIN_CHANNEL_SELECT                           PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_READ_IIN_DATA_FORMAT                              PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_IIN_BUS_ACCESS                               PMBUS_ACCESS_TYPE_READ


// PMBUS_READ_VOUT_COMMAND
#define PMBUS_READ_VOUT_COMMAND_LENGTH                          PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_VOUT_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_READ_VOUT_DATA_FORMAT                             PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_VOUT_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ


// PMBUS_READ_IOUT_COMMAND
#define PMBUS_READ_IOUT_COMMAND_LENGTH                          PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_IOUT_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_READ_IOUT_DATA_FORMAT                             PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_IOUT_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ


// PMBUS_READ_TEMPERATURE_1_COMMAND
#define PMBUS_READ_TEMPERATURE_1_COMMAND_LENGTH                 PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_TEMPERATURE_1_CHANNEL_SELECT                 PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_READ_TEMPERATURE_1_DATA_FORMAT                    PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_TEMPERATURE_1_BUS_ACCESS                     PMBUS_ACCESS_TYPE_READ


// PMBUS_READ_TEMPERATURE_2_COMMAND
#define PMBUS_READ_TEMPERATURE_2_COMMAND_LENGTH                 PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_TEMPERATURE_2_CHANNEL_SELECT                 PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_READ_TEMPERATURE_2_DATA_FORMAT                    PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_TEMPERATURE_2_BUS_ACCESS                     PMBUS_ACCESS_TYPE_READ


// PMBUS_READ_TEMPERATURE_3_COMMAND
#define PMBUS_READ_TEMPERATURE_3_COMMAND_LENGTH                 PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_TEMPERATURE_3_CHANNEL_SELECT                 PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_READ_TEMPERATURE_3_DATA_FORMAT                    PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_TEMPERATURE_3_BUS_ACCESS                     PMBUS_ACCESS_TYPE_READ


// PMBUS_READ_POUT_COMMAND
#define PMBUS_READ_POUT_COMMAND_LENGTH                          PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_POUT_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_READ_POUT_DATA_FORMAT                             PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_POUT_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ


// PMBUS_READ_PIN_COMMAND
#define PMBUS_READ_PIN_COMMAND_LENGTH                           PMBUS_WORD_DATA_SIZE
#define PMBUS_READ_PIN_CHANNEL_SELECT                           PMBUS_CHANNEL_SELECT_PAGED
#define PMBUS_READ_PIN_DATA_FORMAT                              PMBUS_DATA_FORMAT_DIRECT
#define PMBUS_READ_PIN_BUS_ACCESS                               PMBUS_ACCESS_TYPE_READ


// PMBUS_IC_DEVICE_ID_COMMAND
#define PMBUS_PMBUS_REVISION_COMMAND_LENGTH                     PMBUS_BYTE_DATA_SIZE
#define PMBUS_PMBUS_REVISION_CHANNEL_SELECT                     PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_PMBUS_REVISION_DATA_FORMAT                        PMBUS_DATA_FORMAT_ASCII
#define PMBUS_PMBUS_REVISION_BUS_ACCESS                         PMBUS_ACCESS_TYPE_READ
#define PMBUS_PMBUS_REVISION_DEFAULT                            0x33


// PMBUS_IC_DEVICE_ID_COMMAND
#define PMBUS_IC_DEVICE_ID_COMMAND_LENGTH                       PMBUS_BLOCK_DATA_SIZE
#define PMBUS_IC_DEVICE_ID_CHANNEL_SELECT                       PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_IC_DEVICE_ID_DATA_FORMAT                          PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_IC_DEVICE_ID_BUS_ACCESS                           PMBUS_ACCESS_TYPE_READ
#define PMBUS_IC_DEVICE_ID_DEFAULT                              0x49D22700


// PMBUS_IC_DEVICE_REV_COMMAND
#define PMBUS_IC_DEVICE_REV_COMMAND_LENGTH                      PMBUS_BLOCK_DATA_SIZE
#define PMBUS_IC_DEVICE_REV_CHANNEL_SELECT                      PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_IC_DEVICE_REV_DATA_FORMAT                         PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_IC_DEVICE_REV_BUS_ACCESS                          PMBUS_ACCESS_TYPE_READ


// PMBUS_MFR_ID_COMMAND
#define PMBUS_MFR_ID_COMMAND_LENGTH                             PMBUS_BLOCK_DATA_SIZE
#define PMBUS_MFR_ID_CHANNEL_SELECT                             PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_MFR_ID_DATA_FORMAT                                PMBUS_DATA_FORMAT_ASCII
#define PMBUS_MFR_ID_BUS_ACCESS                                 PMBUS_ACCESS_TYPE_READ


// PMBUS_MFR_MODE_COMMAND
#define PMBUS_MFR_MODEL_COMMAND_LENGTH                          PMBUS_BLOCK_DATA_SIZE
#define PMBUS_MFR_MODEL_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_MFR_MODEL_DATA_FORMAT                             PMBUS_DATA_FORMAT_ASCII
#define PMBUS_MFR_MODEL_BUS_ACCESS                              PMBUS_ACCESS_TYPE_READ


// PMBUS_MFR_REVISION_COMMAND
#define PMBUS_MFR_REVISION_COMMAND_LENGTH                       PMBUS_BLOCK_DATA_SIZE
#define PMBUS_MFR_REVISION_CHANNEL_SELECT                          PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_MFR_REVISION_DATA_FORMAT                          PMBUS_DATA_FORMAT_ASCII
#define PMBUS_MFR_REVISION_BUS_ACCESS                           PMBUS_ACCESS_TYPE_READ


// PMBUS_MFR_DATE_COMMAND
#define PMBUS_MFR_DATE_COMMAND_LENGTH                           PMBUS_BLOCK_DATA_SIZE
#define PMBUS_MFR_DATE_CHANNEL_SELECT                           PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_MFR_DATE_DATA_FORMAT                              PMBUS_DATA_FORMAT_ASCII // Date code in YYMMDD Format.
#define PMBUS_MFR_DATE_BUS_ACCESS                               PMBUS_ACCESS_TYPE_READ


// PMBUS_APPLY_SETTINGS_COMMAND
#define PMBUS_APPLY_SETTINGS_COMMAND_LENGTH                     PMBUS_WORD_DATA_SIZE
#define PMBUS_APPLY_SETTINGS_CHANNEL_SELECT                     PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_APPLY_SETTINGS_DATA_FORMAT                        PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_APPLY_SETTINGS_BUS_ACCESS                         PMBUS_ACCESS_TYPE_WRITE
#define PMBUS_APPLY_SETTINGS_DEFAULT                            0x0001


// PMBUS_RESTORE_CONFIG_COMMAND
#define PMBUS_RESTORE_CONFIG_COMMAND_LENGTH                     PMBUS_BYTE_DATA_SIZE
#define PMBUS_RESTORE_CONFIG_CHANNEL_SELECT                     PMBUS_CHANNEL_SELECT_GLOBAL
#define PMBUS_RESTORE_CONFIG_DATA_FORMAT                        PMBUS_DATA_FORMAT_BIT_FIELDS
#define PMBUS_RESTORE_CONFIG_BUS_ACCESS                         PMBUS_ACCESS_TYPE_WRITE


#endif /* PMBUSTYPES_H */
