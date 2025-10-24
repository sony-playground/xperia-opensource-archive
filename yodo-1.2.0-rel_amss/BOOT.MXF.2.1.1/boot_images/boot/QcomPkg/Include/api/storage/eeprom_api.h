#ifndef EEPROM_API_H
#define EEPROM_API_H

/**********************************************************************
 * eeprom_api.h
 *
 * Public interface declaration for the EEPROM Driver.
 *
 * This file describes the EEPROM external interface.
 *
 * Copyright (c) 2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * QUALCOMM Confidential and Proprietary
 *
 **********************************************************************/
/*===================================================================
 *
 *                       EDIT HISTORY FOR FILE
 *
 *   This section contains comments describing changes made to the
 *   module. Notice that changes are listed in reverse chronological
 *   order.
 *
 *
 *
 * when         who     what, where, why
 * ----------   ---     ------------------------------------------------
 * 05-15-2020   eo      Initial version
 *=======================================================================*/

/**  \mainpage EEPROM Functional Overview
 *
 * The EEPROM driver provides a high-level interface for clients, such
 * as bootloaders and tools to interact with EEPROM devices over a specified
 * transport layer. It handles the EEPROM device specifics by interacting with a
 * lower layer driver and abstracts the client from the device-specific algorithms,
 * interfaces and OS adaptations.
 *
 * \n
 *
 */
#ifdef EEPROM_TYPES_API_HEADER
  #include EEPROM_TYPES_API_HEADER
#endif
#include "com_dtypes.h"

#define EEPROM_API_VERSION                (0x00000001)  /** EEPROM API version */

/** EEPROM operation status */
#define EEPROM_DEVICE_DONE                 0   /**< Operation passed */
#define EEPROM_DEVICE_FAIL                (-1) /**< Operation failed */
#define EEPROM_DEVICE_NOT_SUPPORTED       (-2) /**< Device/operation not supported */
#define EEPROM_DEVICE_INVALID_PARAMETER   (-3) /**< API parameters invalid */
#define EEPROM_DEVICE_NOT_FOUND           (-4) /**< Device not found on supported device list */
#define EEPROM_DEVICE_NO_MEM              (-5) /**< Insufficient memory */

typedef int EEPROM_STATUS;                /**< Error status values used in EEPROM driver */

#define EEPROM_DEVICE_NAME_SIZE           (32)

/** EEPROM device IDs to use in eeprom_open() API. */
#define EEPROM_DEVICE_ID_CDT   (0) /**< CDT EEPROM device */
#define EEPROM_DEVICE_ID_RF    (1) /**< RF  EEPROM device */
#define EEPROM_DEVICE_ID_2     (2) /**< Reserved */
#define EEPROM_DEVICE_ID_3     (3) /**< Reserved */
#define EEPROM_DEVICE_ID_4     (4) /**< Reserved */

/** EEPROM client device data */
struct eeprom_info
{
  uint32  version;                      /**< Version info of this structure */
  uint8   device_name[EEPROM_DEVICE_NAME_SIZE];  /**< Device name string */
  uint32  device_address;               /**< Device Address */
  uint32  device_clk_freq_KHz;          /**< Device operating clock frequency in KHz */
  uint32  total_pages_in_device;        /**< Total number of pages in device */
  uint16  page_size_bytes;              /**< Page size in bytes */
};

typedef void *eeprom_handle_t;

/**
 * Opens a handle to an EEPROM device.
 *
 * @param dev_id [IN]
 *   Device ID that specifies a EEPROM device.
 *
 * @param handle [OUT]
 *   EEPROM interface handle.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EEPROM_STATUS eeprom_open(uint32 dev_id, eeprom_handle_t *handle);

/**
 * Closes a handle to an EEPROM device.
 * Clients should close the EEPROM driver instance when accesses
 * to the EEPROM are no longer needed.
 *
 * @param handle [IN]
 *   EEPROM interface handle.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EEPROM_STATUS eeprom_close(eeprom_handle_t handle);

/**
 * Intialize the Device Tree blob for I2c driver
 * \n
 *
 * @param handle [IN]
 *   None
 *
 * @param eeprom_info [OUT]
 *   None
 *
 * @return int [OUT]
 *   None
 *
 */

void eeprom_init_dtb(void);
/**
 * Gets EEPROM device information. EEPROM driver assumes that the memory
 * for returned information is allocated by the driver client.
 * \n
 *
 * @param handle [IN]
 *   EEPROM interface handle
 *
 * @param eeprom_info [OUT]
 *   Pointer to the client's EEPROM device info data.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EEPROM_STATUS eeprom_get_info(eeprom_handle_t handle, struct eeprom_info *eeprom_info);

/**
 * Allows write data to the EEPROM.
 *
 * @param handle [IN]
 *   EEPROM interface handle
 *
 * @param byte_offset [IN]
 *   Byte offset from the beginning of the EEPROM device to write to.
 *
 * @param byte_count [IN]
 *   Number of bytes to write data.
 *
 * @buffer [IN]
 *   data buffer for a EEPROM device write operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 *
 */
EEPROM_STATUS eeprom_write(eeprom_handle_t handle,
  uint32 byte_offset, uint32 byte_count, void *buffer);

/**
 * Allows read data from the EEPROM
 *
 * @param handle [IN]
 *   EEPROM interface handle
 *
 * @param byte_offset [IN]
 *   Byte offset from the beginning of the EEPROM device to read from.
 *
 * @param byte_count [IN]
 *   Number of bytes to read data.
 *
 * @buffer [OUT]
 *   data buffer for a EEPROM device read operation.
 *
 * @return int [OUT]
 *   Result of the operation.
 */
EEPROM_STATUS eeprom_read(eeprom_handle_t handle,
  uint32 byte_offset, uint32 byte_count, void *buffer);

#endif /* #ifndef EEPROM_API_H */