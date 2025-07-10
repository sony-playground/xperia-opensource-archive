/** 
  @file  ULog.h
  @brief Main interface for ULog.
*/
/*=============================================================================
  Copyright (c) 2009-2014, 2020 Qualcomm Technologies, Incorporated.
  All rights reserved.
  Qualcomm Technologies, Confidential and Proprietary.
=============================================================================*/

/*============================================================================
                             EDIT HISTORY


 when       who     what, where, why
 --------   ---     ----------------------------------------------------------
 02/27/20   da      Separated typedef definitions to Ulog_common.h
 10/02/14	vpopuri	Merged ULOGv5
 05/30/13   llg     (Tech Pubs) Edited/added Doxygen comments and markup.

============================================================================*/
#ifndef ULOG_H
#define ULOG_H

#include <ULog_common.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/**
 * <!-- ULogCore_Init -->
 *
 * @brief Initialize the ULog System.
 *
 * It is not strictly necessary to call this function since it
 * will be executed any time an attempt is made to connect to, or
 * create a log.
 *
 * @return DAL_SUCCESS if the initialization is successful.
 */
ULogResult ULogCore_Init(void);


/**
 * <!-- ULogCore_LogCreate -->
 *
 * @brief  - Create a new log.
 * 
 * Create a new log, and add it to the logs managed by the ULog
 * subsystem.
 * 
 * @param h : A ULog handle is returned at this pointer. 
 * @param logName : The log name (24 chars max, including NULL).
 * @param bufferSize : The size in bytes of the log buffer. A request of size 0 
 *                     will leave the buffer unallocated. 
 * @param memoryType : The memory configuration.
 * @param lockType : The type of locking required.
 * @param interfaceType : This field is a legacy option. There is only a single
 *                   ULOG type. Any value is ok for this param and will be
 *                   ignored. The RAW and REALTIME types are only used
 *                   internally to indicate if a write has a timestamp
 *                   included.
 *
 * @return DAL_SUCCESS if the create completed successfully.  The log will have been
 *        enabled and will be ready to use. 
 *        ULOG_ERR_INITINCOMPLETE if ULOG_MEMORY_LOCAL_MANUAL is used.  
 *        ULOG_ERR_INITINCOMPLETE if a buffersize of 0 is used.  
 *        The log can be enabled later after ULogCore_MemoryAssign sets up all the parts.
 *        Errors are defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_LogCreate(ULogHandle * h,
                              const char *  logName,
                              uint32  bufferSize,
                              uint32  memoryType,
                              ULOG_LOCK_TYPE  lockType,
                              ULOG_INTERFACE_TYPE  interfaceType);


/**
 * <!-- ULogCore_SetLockType -->
 *
 * @brief Switches the lock type for a log.
 *
 *
 * @param h : A ULog handle.
 * @param lockType : The desired lock type for the log
 * 
  */
void ULogCore_SetLockType( ULogHandle h, ULOG_LOCK_TYPE lockType );


/**
 * <!-- ULogCore_HeaderSet -->
 *
 * @brief Set the header for the log.
 *
 * Apply the supplied string to a given log header.  The header
 * is stored with a log, and will not be overwritten unless this
 * function is called again.
 *
 * There are no real limitations to this string.  The system
 * determines the length of the supplied string, allocates that
 * amount of memory, and copies the string to it.
 *
 * @param h: A ULog handle.
 * @param headerText: The string to store in the log.
 *
 * @return DAL_SUCCESS if the header was successfully stored.
 */
ULogResult ULogCore_HeaderSet(ULogHandle h, char * headerText);


/**
 * <!-- ULogCore_AttributeSet -->
 *
 * @brief Set the log attributes
 * 
 * OR in the provided attribute bits into the logs attribute mask.
 *
 * @param h : The log to set attributes for
 * @param attribute : The attributes to set
 *
 * @return A handle to the named log
 */
void ULogCore_AttributeSet(ULogHandle h, uint32 attribute);


/**
 * <!-- ULogCore_MemoryAssign -->
 *
 * @brief Assign memory to specific log buffers.
 * 
 * When a log is created with the allocation type
 * ULOG_ALLOC_MANUAL, the buffers are and must be manually
 * assigned with this function.  All supplied buffers must be word
 * aligned.  If a buffer is not word aligned, this function will
 * fail.
 * 
 * @param h : A ULog handle.
 * @param id : Which buffer to assign.
 * @param bufferPtr : A pointer to the buffer memory to assign.
 *                   Note that ALL buffers must be word aligned.
 * @param bufferSize : The size in bytes of the buffer.
 *
 * @return DAL_SUCCESS if the memory was assigned successfully.
 *        Errors are defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_MemoryAssign(ULogHandle h,
                                 ULOG_VALUE_ID id,
                                 void * bufferPtr,
                                 uint32  bufferSize);


/**
 * <!-- ULogCore_Enable -->
 *
 * @brief Enable a log that is already defined.
 *
 * Enable a log.  A log can need manual enabling if it has manual
 * allocation, has been disabled, or buffer memory was not assigned.
 *
 * @param h : A ULog handle.
 *
 * @return DAL_SUCCESS if the log was enabled successfully.
 *        Errors are defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_Enable(ULogHandle h);


/**
 * <!-- ULogCore_IsEnabled -->
 *
 * @brief Check if a log is enabled.
 *
 * @param h : A ULog handle.
 * @param core : A vtable to fill in with the appropriate
 *              interface functions for the current log
 *
 * @return TRUE if the log is enabled.
 */
DALBOOL ULogCore_IsEnabled(ULogHandle h, ULOG_CORE_VTABLE ** core);


/**
 * <!-- ULogCore_Query -->
 * 
 * @brief Query information about a specific log or the logging system.
 * 
 * This function will return the expected sizes of internal log
 * buffers, in order to manually allocate the buffers.  Use a NULL
 * handle for these values.
 *
 * @param h : A ULog handle.
 * @param id : A log buffer ID.
 * @param value : The returned number of bytes needed by the
 *               selected buffer.
 *
 * @return DAL_SUCCESS if the buffer id was known, and supported.
 *         Errors are defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_Query(ULogHandle h, ULOG_VALUE_ID id, uint32 * value);


/**
 * <!-- ULogCore_ValueQuery -->
 *
 * @brief Query the expected sizes of internal buffers.
 *
 * This function will return the expected sizes of internal log
 * buffers, in order to manually allocate the buffers.
 *
 * @param id : A log buffer ID.
 * @param value : The returned number of bytes needed by the selected buffer.
 *
 * @return DAL_SUCCESS if the buffer id was known, and supported.
 *        Errors are defined in the ULOG_ERRORS enum.
 */
#define ULogCore_ValueQuery(id, value)     ULogCore_Query(NULL, id, value)


/**
 * <!-- ULogCore_Read -->
 *
 * @brief Read data from the log buffer.
 * 
 * Read data from the log buffer.  This data is unformatted. Call
 * ULogCore_MsgFormat to format each message.  Only full messages
 * are placed in the output buffer, thus it is incorrect to use
 * outputCount != outputSize as an indicator that the log buffer
 * is empty.
 *
 * An empty log buffer will yield a read of only status, and an
 * outputCount = 4.
 * 
 * @param h : A ULog handle of the log to read.
 * @param outputSize : Size of the output buffer.
 * @param outputMem : A pointer to the output buffer.
 * @param outputCount : The amount of data placed in the output buffer.
 *
 * @return DAL_SUCCESS if the read completed.
 */
ULogResult ULogCore_Read(ULogHandle h,
                         uint32  outputSize,
                         char *  outputMem,
                         uint32 *  outputCount);


/**
 * <!-- ULogCore_ReadEx -->
 *
 * @brief Read data from the log buffer.
 *
 * Read data from the log buffer.  See ULogCore_Read for
 * description.  Allows additional control of limited number of
 * messages read.
 *
 * @param h : A ULog handle of the log to read.
 * @param outputSize : Size of the output buffer.
 * @param outputMem : A pointer to the output buffer.
 * @param outputCount : The amount of data placed in the output buffer.
 * @param outputMessageLimit : The maximum number of messages to read from
 *                             the buffer.
 *
 * @return DAL_SUCCESS if the read completed.
 */
ULogResult ULogCore_ReadEx(ULogHandle h,
                           uint32  outputSize,
                           char *  outputMem,
                           uint32 *  outputCount,
                           uint32 outputMessageLimit);


/**
 *  <!-- ULogCore_ReadSessionComplete -->
 *
 * @brief Indicate that any previous read sessions are complete. No overrun detection needed 
 * on the very next read of this log. Also make sure rewind logs are rewound.
 *
 * This function is needed so that reading a log multiple times doesn't consider the
 * read jump at the start of reading to be an overrun.  Use this safely at the start
 * or end of your read session.
 *
 * @param h : A ULog handle of the log about to be read or just completed being read.
 *
 * @return DAL_SUCCESS if the read completed.
 */
ULogResult ULogCore_ReadSessionComplete(ULogHandle h);


/**
 * <!-- ULogCore_Allocate -->
 *
 * @brief Allocate memory to the log buffer.
 *
 * When a log is created with no output buffer, this function can
 * be used to allocate that memory.  It is intended for use from
 * applications enabling and reading logs from the system.
 *
 * This only works for logs created with ULOG_ALLOC_LOCAL
 * allocation type.
 *
 * @param h : A ULog handle of the log to read.
 * @param bufferSize : Size of the circular buffer to allocate.
 *
 * @return DAL_SUCCESS if the memory was allocated successfully.
 *         Errors are defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_Allocate(ULogHandle h, uint32 bufferSize);


/**
 * <!-- ULogCore_Disable -->
 *
 * @brief Disable a log. Drop message writes until re-enabled.
 *
 * @param h : A ULog handle.
 *
 * @return DAL_SUCCESS if the log was disabled successfully.
 *        Errors are defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_Disable(ULogHandle h);


/**
 * <!-- ULogCore_List -->
 *
 * @brief List of all logs available in the system, output as a text string.
 *
 * @param registeredCount : The number of logs that are registered.
 * @param nameArraySize : The size of the array that receives log names.
 * @param namesReadCount : The number of log names that were actually placed
 *                         in the nameArray.
 * @param nameArray : The buffer to receive log name data.
 *
 * @return DAL_SUCCESS if the list was successfull. Errors are defined in
 *        the ULOG_ERRORS enum.
 */
ULogResult ULogCore_List(uint32 *  registeredCount,
                         uint32  nameArraySize,
                         uint32 *  namesReadCount,
                         char *  nameArray);


/**
 * <!-- ULogCore_ListEx -->
 *
 * @brief List the available logs.
 *
 * Create a list of all logs available in the system, and output
 * it as a text string.  Offset into the list by the provided
 * amount.
 * 
 * @param offsetCount : The number of log names to skip before returning log name data.
 * @param registeredCount : The number of logs that are registered.
 * @param nameArraySize : The size of the array that receives log names.
 * @param namesReadCount : The number of log names that were actually placed
 *                        in the nameArray.
 * @param nameArray : The buffer to receive log name data.
 *
 * @return DAL_SUCCESS if the list was successful. Errors are defined in
 *        the ULOG_ERRORS enum.
 */
ULogResult ULogCore_ListEx(uint32 offsetCount,
                           uint32 *  registeredCount,
                           uint32  nameArraySize,
                           uint32 *  namesReadCount,
                           char *  nameArray);


/**
 * <!-- ULogCore_MsgFormat -->
 *
 * @brief Format an individual message retrieved with the ULogCore_Read function.
 *
 * Format and output an individual message read with the
 * ULogCore_Read function.
 *
 * @param h : A ULog handle to the log we are formatting.
 * @param msg : The input message.
 * @param msgString : The output string.
 * @param msgStringSize : The size of the output string
 * @param msgConsumed : Number of bytes consumed from the original msg buffer.
 *
 * @return DAL_SUCCESS if the format was successful. Errors are
 *        defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_MsgFormat(ULogHandle h,
                              char *  msg,
                              char *  msgString,
                              uint32 msgStringSize,
                              uint32 * msgConsumed);


/**
 * <!-- ULogCore_HeaderRead -->
 * 
 * @brief Read the header from the supplied log.
 * 
 * @param h : A handle of the log to access.
 * @param statusString : The output string.
 * @param statusStringSize : The size of the output string
 * 
 * @return DAL_SUCCESS if the format was successful. Errors are
 *         defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_HeaderRead(ULogHandle h,
                               uint32 headerReadOffset,
                               char * headerString,
                               uint32 headerStringSize,
                               uint32 * headerActualLength);


/**
 * <!-- ULogCore_Connect -->
 *
 * @brief Connect a log handle to a log defined elsewhere.
 *
 * Connect a log handle to a log that has been, or will be defined
 * elsewhere.  A successful return allows logging through the
 * handle, although no data will be written to a physical log
 * until the log is defined with the ULogCore_Create function.
 *
 * @param h : A ULog handle.
 * @param logName : The name of the log to connect with.
 *
 * @return DAL_SUCCESS if the connect was successful. Errors are
 *        defined in the ULOG_ERRORS enum.
 */
ULogResult ULogCore_Connect(ULogHandle * h, const char * logName);


/**
 * <!-- ULogCore_LogLevelSet -->
 *
 * @brief Set the log level.
 *
 * ULog does not filter messages, but this function is
 * intended to facilitate filtering without requiring it. This
 * simply sets a parameter in a log that can be used to filter log
 * messages, along with the provided macros.
 *
 * @param h : A ULog handle.
 * @param level : The new level for the log.
 */
void ULogCore_LogLevelSet(ULogHandle h, uint32 level);


/**
 * <!-- ULogCore_LogLevelGet -->
 *
 * @brief Get the log level.
 *
 * ULog does not filter messages, but this function is
 * intended to facilitate filtering without requiring it. This
 * simply returns a parameter in a log that can be used to filter
 * log messages, along with the provided macros.
 *
 * @param h : A ULog handle.
 *
 * @return The current log value.  0 if the log handle is NULL.
 */
uint32 ULogCore_LogLevelGet(ULogHandle h);


/**
 * <!-- ULOG_FILTER_CMD -->
 *
 * @brief Filter a log command based on the log level.
 *
 * ULog does not filter messages, but this macro is intended to
 * facilitate filtering without requiring it. This macro compares
 * the provided level against the level of the provided log.  If
 * the provided level is <= the log level then the provided
 * function is executed.
 * 
 * @param handle : A ULog handle.  The level is retrieved from this handle.
 * @param level : The level of this command.
 * @param function : The function to execute if the levels indicate acceptance.
 *
 * @return The current log value.  0 if the log handle is NULL.
 */
#define ULOG_FILTER_CMD(handle, level, function)     if (level <= ULogCore_LogLevelGet(handle)) { function }


/**
 * <!-- ULogCore_TeeAdd -->
 *
 * @brief Group handles together.
 *
 * Group handles together so that any logging information will be copied to
 * multiple logs.
 *
 * Note: the first handle may points to an updated object after a call to
 * this function, whereas the second one will not.
 *
 * @param h1 : A ULog handle, which may be one to a single or a group of logs
 * @param h2 : A ULog handle, which may be one to a single or a group of logs
 *             to be added to h1
 *
 * @return A handle to the grouped logs
 */
ULogHandle ULogCore_TeeAdd(ULogHandle h1, ULogHandle h2);


/**
 * <!-- ULogCore_TeeRemove -->
 *
 * @brief Remove some handle(s)
 *
 * Note: the first handle may points to an updated object after a call to
 * this function, whereas the second one will not.
 *
 * @param h1 : A ULog handle, which may be one to a single or a group of logs
 * @param h2 : A ULog handle, which may be one to a single or a group of logs
 *             to be removed from h1
 *
 * @return A handle to the resulting group of logs
 */
ULogHandle ULogCore_TeeRemove(ULogHandle h1, ULogHandle h2);


/**
 * <!-- ULogCore_HandleGet -->
 *
 * @brief Get a log handle by its name.
 *
 * @param logName: Name of a ULog to search for.
 *
 * @return A handle to the named log
 */
ULogHandle ULogCore_HandleGet(char *logName);


/**
 * <!-- ULogCore_IsLogPresent -->
 *
 * @brief Check if a named log is present in a log set
 *
 * @param h : A ULog handle, which may be a handle to a single or a group of logs
 * @param logName : name of a ULog
 *
 * @return TRUE if the named log is present in the log(s) indicated by the handle
 *        h, and FALSE otherwise
 */
DALBOOL ULogCore_IsLogPresent(ULogHandle h, char *logName);


/**
 * <!-- ULogCore_SetTimestampSrcFn -->
 *
 * @brief Allows the source of the timestamp to be altered by the user
 *
 * @param h : A ULog Handle
 * @param altULogTimeStampFn : Fn pointer to the users timestamp source fn
 *
 * @return DAL_SUCCESS if the Timestamp function was correctly set
 *				 Errors are defined in the ULOG_ERRORS enum
 *
 */
ULogResult ULogCore_SetTimestampSrcFn(ULogHandle h, ULOG_ALT_TS_SRC altULogTimeStampFn);


/**
 * <!-- ULogCore_SetTransportToRAM -->
 *
 * @brief Write log messages to the circular RAM buffer.
 * 
 * Writing messages to the circular RAM buffer is the default behavior for logs. 
 *
 * @param h : A ULog handle
 *
 * @return DAL_SUCCESS if the transport is changed, DAL_ERROR if it isn't
 */
ULogResult ULogCore_SetTransportToRAM(ULogHandle h);


/**
 * <!-- ULogCore_SetTransportToStm -->
 *
 * @brief Write log messages to the QDSS/STM transport
 *
 * @param h : A ULog handle
 * @param protocol_num : A QDSS protocol number (0 to 127) is assigned to the 
 *                      ULog handle and this protocol number can be used to
 *                      match logs to the handle when reading the QDSS output.
 *
 * @return DAL_SUCCESS if the transport is changed, DAL_ERROR if it isn't
 */
ULogResult ULogCore_SetTransportToStm(ULogHandle h, unsigned char protocol_num);


/**
 * <!-- ULogCore_SetTransportToStmAscii -->
 *
 * @brief Write log messages as ASCII to the QDSS/STM transport
 *
 * @param h : A ULog handle
 * @param protocol_num : A QDSS protocol number (0 to 127) is assigned to the
 *                      ULog handle and can be used to identify log output when
 *                      reading the QDSS output.
 *
 * @return DAL_SUCCESS if the transport is changed, DAL_ERROR if it isn't
 */
ULogResult ULogCore_SetTransportToStmAscii(ULogHandle h, unsigned char protocol_num);


/**
 * <!-- ULogCore_SetTransportToAlt -->
 *
 * @brief Write log messages using the provided handlers
 *
 * @param h : A ULog handle
 * @param newTansportVTable : A Write, MultipartStart and MultipartEnd function table.
 *
 * @return DAL_SUCCESS if the transport is changed, DAL_ERROR if it isn't
 */
ULogResult ULogCore_SetTransportToAlt(ULogHandle h, ULOG_CORE_VTABLE* newTansportVTable);


/**
 * <!-- ULogDiagAddPlugin -->
 *
 * @brief Setup and enable a ULog Diag plugin.
 * 
 * When the PC based ULogDiagPluginLauncher.exe is run, the plugin with a 
 * matching plugin_id will be run with a 32 bit int passed as an argument 
 * to the plugin. These plugins can be used to create useful analysis tools.
 * For example: when the PC ULogDiagPluginLauncher is run:
 *     ULogDiagPluginLauncher.exe COM12 Modem 1 0
 * The plugin that the NPA team provides as 
 *     ULogDiagAddPlugin(npa_generate_dump_log, ULOG_DIAG_PLUGIN_ID_NPADUMP); 
 * will create a new ULog called "NPA Dump Log" that can be read out with
 * the ULogDiagReader tool.  
 *
 * Plugins should mostly return DAL_SUCCESS, or DAL_ERROR.
 * For more complicated return values, values 10000 to 20000 
 * should remain unused by normal ULog return values and 
 * can be returned. The PC application uses ULOG_ERR_NOTCONNECTED
 * to indicate an ID has no plugin attached to it. 							
 *
 * @param new_pluginfcn : A function pointer to a plugin.  The plugin accepts 
 *                        a uint32 as an input and returns an integer.
 * @param new_plugin_id : A uint32 id that the plugin will be registered with.  
 *
 * @return DAL_SUCCESS if the plugin is registered successfully, an error code if it isn't. 
 */
ULogResult ULogDiagAddPlugin(int(*new_pluginfcn)(uint32), uint32 new_plugin_id);

#ifdef __cplusplus
}
#endif

#endif // ULOG_H

