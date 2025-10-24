#ifndef __UFS_MEMORY_H
#define __UFS_MEMORY_H
/******************************************************************************
 * ufs_memory.h
 *
 * This file provides UFS storage device description data structure and
 * SCSI related data structure
 *
 * Copyright (c) 2012-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *
 *****************************************************************************/
/*=============================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/UfsCommonLib/ufs_memory.h#1 $
  $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     --------------------------------------------------- 
2022-05-14   sa      Added support for BlockIo2 with multiple doorbells.
2022-05-10   sa      Added SharedIce information.
2021-10-25   jt      Add write booster and sync cache support 
2021-08-13   jt      Add ufs_do_finish_config 
2021-04-28   jt      Add ICE support 
2020-03-31   jt      Add power management functions
2019-04-22   jt      Correct UFS_IDN_bCurrentPowerMode value
2018-09-24   jt      Remove 1 core id restriction 
2018-08-16   jt      Add clock gate/ungate functions 
2016-09-02   jt      Add secure write protect definitions 
2015-03-26   rh      Add ufs_get_descriptor_rpmb
2015-02-18   rh      Split set/poll for fDeviceInit
2014-09-30   rh      Adding RPMB APIs
2014-09-17   rh      Merge with UEFI driver changes
2014-04-22   rh      Adding the pre-prog config option
2013-11-05   rh      Adding the format API
2013-10-03   rh      Adding SCSI command REQUEST SENSE
2013-09-18   rh      Adding write for bConfigDescrLock attribute
2013-09-10   rh      Adding define for WRITE/READ buffer SCSI command
2012-12-18   rh      Initial creation

=============================================================================*/

#include "ufs_osal.h"
#include "ufs_core.h"


// Define SCSI commands
#define SCSI_CMD_TEST_UNIT_RDY      0x00
#define SCSI_CMD_REQUEST_SENSE      0x03
#define SCSI_CMD_FORMAT             0x04
#define SCSI_CMD_INQUIRY            0x12
#define SCSI_CMD_START_STOP_UNIT    0x1B
#define SCSI_CMD_READ10             0x28
#define SCSI_CMD_READ_CAP10         0x25     // Read Capacity
#define SCSI_CMD_SYNC_CACHE10       0x35
#define SCSI_CMD_UNMAP              0x42
#define SCSI_CMD_WRITE10            0x2A
#define SCSI_CMD_SECPROT_IN         0xA2     // Security Protocal in
#define SCSI_CMD_SECPROT_OUT        0xB5     // Security Protocal out
#define SCSI_CMD_REPORT_LUNS        0xA0
#define SCSI_CMD_WRITE_BUFFER       0x3B
#define SCSI_CMD_READ_BUFFER        0x3C

#define SCSI_STATUS_GOOD            0x00
#define SCSI_STATUS_CHK_COND        0x02
#define SCSI_STATUS_BUSY            0x08
#define SCSI_STATUS_TASK_SET_FULL   0x08

#define SCSI_FLAG_FUA               0x08

// UFS descriptor type ident value
#define UFS_DESC_IDN_DEVICE         0x00
#define UFS_DESC_IDN_CONFIGURATION  0x01
#define UFS_DESC_IDN_UNIT           0x02
#define UFS_DESC_IDN_INTERCONNECT   0x04
#define UFS_DESC_IDN_STRING         0x05
#define UFS_DESC_IDN_GEOMETRY       0x07
#define UFS_DESC_IDN_POWER          0x08

// Attributes definitions
#define UFS_IDN_bBootLunEn          0x00
#define UFS_IDN_bCurrentPowerMode   0x02
#define UFS_IDN_bActiveICCLevel     0x03
#define UFS_IDN_bPurgeStatus        0x06
#define UFS_IDN_bRefClkFreq         0x0a
#define UFS_IDN_bConfigDescrLock    0x0b

// Flags definitions
#define UFS_IDN_fDeviceInit                              0x01
#define UFS_IDN_fPermanentWPEn                           0x02
#define UFS_IDN_fPowerOnWPEn                             0x03
#define UFS_IDN_fPurgeEnable                             0x06
#define UFS_IDN_fWriteBoosterEn                          0x0E
#define UFS_IDN_fWriteBoosterBufferFlushEn               0x0F
#define UFS_IDN_fWriteBoosterBufferFlushDuringHibernate  0x10

// Placement of the message byte is determined by if 
// this is a request or a response
// For request, the message is in bit [7:0] while bit [15:8] is zero
// For response, the message is in bit [15:8] while bit [7:0] is zero
#define RPMB_REQ_KEY_PROG           0x01
#define RPMB_REQ_READ_WR_CNT        0x02
#define RPMB_REQ_DATA_WRITE         0x03
#define RPMB_REQ_DATA_READ          0x04
#define RPMB_REQ_RESULT_READ        0x05
#define RPMB_REQ_SECURE_WP_WRITE    0x06
#define RPMB_REQ_SECURE_WP_READ     0x07

#define RPMB_RESULT_OK              0x00
#define RPMB_RESULT_FAILURE         0x01
#define RPMB_RESULT_AUTH_FAILURE    0x02
#define RPMB_RESULT_CNT_FAILURE     0x03
#define RPMB_RESULT_ADDR_FAILURE    0x04
#define RPMB_RESULT_WR_FAILURE      0x05
#define RPMB_RESULT_RD_FAILURE      0x06
#define RPMB_RESULT_NO_KEY          0x07

// SCSI Sense Keys
#define SENSE_KEY_NO_SENSE          0x0
#define SENSE_KEY_RECOVERED_ERROR   0x1
#define SENSE_KEY_NOT_READY         0x2
#define SENSE_KEY_MEDIUM_ERROR      0x3
#define SENSE_KEY_HARDWARE_ERROR    0x4
#define SENSE_KEY_ILLEGAL_REQUEST   0x5
#define SENSE_KEY_UNIT_ATTENTION    0x6
#define SENSE_KEY_DATA_PROTECT      0x7
#define SENSE_KEY_BLANK_CHECK       0x8
#define SENSE_KEY_VENDOR_SPECIFIC   0x9
#define SENSE_KEY_COPY_ABORTED      0xB
#define SENSE_KEY_VOLUME_OVERFLOW   0xD
#define SENSE_KEY_MISCOMPARE        0xE


// A data stucture used by the caller of the UFS driver as 
// a handle to access the APIs
typedef struct ufs_handle {
   struct ufs_host_info *phc;
   uint8_t        is_inuse;               // Inuse flag must be fist
   uint8_t        ufs_core_id;            
   uint8_t        lun;
   uint32_t       id_magic;               // Magic # must be last

} ufs_handle_t;

// Function definitions

/* 
 * Initialize UFS memory device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success ENODEV when detection failed
 * */
int32_t ufs_mem_init (struct ufs_handle *hufs);

/* 
 * Read multiple blocks of data from UFS memory device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Output: buf  - Pointer to memory buffer for read operation
 * Input:  lba  - Logical block address for the first block
 * Input:  blocks - Number of blocks to read
 * Input/Output: xfr_context - Details of the read operation
 * Input/Output: crypto_context - Crypto details of the read operation
 * Return: EOK for success EIO when read failed
 * */
int32_t ufs_scsi_read (struct ufs_handle *hufs, uint8_t *buf, 
                       uint32_t lba, uint32_t blocks, 
                       struct ufs_xfr_context *xfr_context, 
                       struct ufs_crypto_context *crypto_context);

/* 
 * Write mutiple blocks of data from UFS memory device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Input:  buf  - Pointer to memory buffer for write operation
 * Input:  lba  - Logical block address for the first block
 * Input:  blocks - Number of blocks to write
 * Input/Output: xfr_context - Details of the write operation
 * Input/Output: crypto_context - Crypto details of the write operation
 * Return: EOK for success EIO when write failed
 * */
int32_t ufs_scsi_write (struct ufs_handle *hufs, uint8_t *buf, 
                        uint32_t lba, uint32_t blocks, 
                        struct ufs_xfr_context *xfr_context, 
                        struct ufs_crypto_context *crypto_context);

/* 
 * Unmap memory blocks from UFS memory device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Input:  lba  - Logical block address for the first block
 * Input:  blocks - Number of blocks to erase
 * Return: EOK for success EIO when erase failed
 * */
int32_t ufs_scsi_unmap (struct ufs_handle *hufs, 
                        uint32_t lba, uint32_t blocks);

/* 
 * Send sync cache command to UFS memory device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Input:  lba  - Logical block address for the first block
 * Input:  blocks - Number of blocks to sync
 * Return: EOK for success EIO when sync cache failed
 * */
int32_t ufs_scsi_sync_cache (struct ufs_handle *hufs, 
                             uint32_t lba, uint32_t blocks);

/* 
 * Erase the entire UFS LU
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success EIO when erase failed
 * */
int32_t ufs_scsi_format (struct ufs_handle *hufs);

/* 
 * Test and see if the memory device is ready for operation
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EBUSY if the device is busy and
 *         EIO if IO error is encountered
 * */
int32_t ufs_scsi_unit_rdy (struct ufs_handle *hufs);
 
/* 
 * Set the new power condition for the UFS device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         power_cond: 1 - Active, 2 - UFS_sleep, 3 - PowerDown
 * Return: EOK for success, EBUSY if the device is busy and
 *         EIO if IO error is encountered
 * */
int32_t ufs_scsi_start_stop_unit (struct ufs_handle *hufs, 
                                  uint32_t power_cond);

/* 
 * Send the request sense command and decode the sense data
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * lun  :  lun number.
 * Return: EOK for success, EBUSY if the device is busy and
 *         EIO if IO error is encountered
 * */
int32_t ufs_scsi_req_sense (struct ufs_handle *hufs, uint32_t lun);

/* 
 * Get a list of all the active LUNs 
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_scsi_report_lun (struct ufs_handle *hufs);

/* 
 * Check the LUN supplied to see if it is one of the active LUN
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, ENOENT if LUN is not valid 
 * */
int32_t ufs_check_valid_lun (struct ufs_handle *hufs, uint8_t lun);

/* 
 * Get one of the string dscriptors from the UFS device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Input:  id - ID of the descriptor to get
 * Output: buf - Pointer to memory buffer to hold the descriptor info
 * Input:  size - Size of the memory buffer
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_descriptor_str (struct ufs_handle *hufs, uint32_t id,
                                char *buf, uint32_t size);

/* 
 * Get one of the unit dscriptors from the UFS device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Input:  id - ID of the descriptor to get
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_descriptor_unit (struct ufs_handle *hufs, uint32_t id);


/* 
 * Get the RPMB unit dscriptors from the UFS device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_descriptor_rpmb (struct ufs_handle *hufs);


/* 
 * Get the device descriptor
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_descriptor_device (struct ufs_handle *hufs);


/* 
 * Get the device configuration descriptor
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_descriptor_config (struct ufs_handle *handle);


/* 
 * Get the geometry descriptor
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_descriptor_geometry (struct ufs_handle *hufs);

/* 
 * Get the flags  
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         info - UFS device information 
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_flags(struct ufs_handle *hufs, struct ufs_info_type *info);

/* 
 * Wait until device is responding to NOP UPIU requests
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_wait_device_awake (struct ufs_handle *handle);

/* 
 * Get the BOOT LUN configuration from the UFS device attribute
 * structure and store the value in the ufs_host_t data structure
 * The bBootLunEn flag identify which BOOT LUN (A or B) is mapped
 * to BOOT WLUN 
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_bBootLunEn (struct ufs_handle *hufs);

/* 
 * Set the boot LUN configuration for UFS device.  
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         id - which boot LUN to use: 
 *             0 : Disable BOOT WLUN
 *             1 : Set BOOT for A
 *             2 : Set BOOT for B
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_bBootLunEn (struct ufs_handle *hufs, uint8_t id);

/* 
 * Get the bConfigDescrLock from the UFS device attribute
 * structure and store the value in the ufs_host_t data structure
 * When bConfigDescrLock bit is set to 1, the device configuration
 * descriptor is locked
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_bConfigDescrLock (struct ufs_handle *hufs);

/* 
 * Set the bConfigDescrLock attribute for UFS device.  
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         val - 1 : Lock the congiguration descriptor 
 *             - This is a write once operation
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_bConfigDescrLock (struct ufs_handle *hufs, uint8_t val);

/* 
 * Set the fDeviceInit flag.  Setting this flag exits
 * the partial init mode for UFS device
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         async - Indicates asynchronous operation or not
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_fDeviceInit (struct ufs_handle *hufs, boolean async);

/* 
 * Poll the fDeviceInit flag.  Blocking until the fDeviceInit
 * flag is back to 0.
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_poll_fDeviceInit (struct ufs_handle *hufs);

/* 
 * Write val to fWriteBoosterEn flag. If val = 1, then 
 * set fWriteBoosterBufferFlushEn and 
 * fWriteBoosterBufferFlushDuringHibernate as well. 
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         val  - 0 : WriteBooster is not enabled
 *                1 : WriteBooster is enabled
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_fWriteBooster (struct ufs_handle *hufs, uint8_t val);

/* 
 * Set the fPowerOnWPEn flag.  Setting this flag enable
 * the Power On Write Protect fucntion.  The flag can not be
 * cleared without a power cycle
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_fPowerOnWPEn (struct ufs_handle *hufs);

/* 
 * Set the bLUWriteProtect field in the unit descriptor. 
 * Setting this field following by setting the fPowerOnWPEn 
 * flag enable the write protect feature
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         wp_setting - 0 : Not writeprotected
 *                      1 : Power on write protect
 *                      2 : Permanently write protected
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_bLUWriteProtect (struct ufs_handle *hufs, uint8_t wp_setting);

/* 
 * Set the fPurgeEnable flag.  Setting this flag starts
 * the purge fucntion.  The function will wait till the 
 * flag is resetted by the hardware to indicate completition
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         async - Indicates asynchronous operation or not
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_n_wait_fPurgeEnable (struct ufs_handle *hufs, boolean async);

/* 
 * Send the scsi inquiry command and decode the returned value.
 * Result stored in the ufs_host_t data structure
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_scsi_inquiry (struct ufs_handle *hufs);

/* 
 * Function used to get the UFS device information, fill
 * in the ufs_info_type data structure
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         info - UFS device information
 * Return: EOK for success, EIO if IO error is encountered
 * */
void ufs_fill_in_device_info (struct ufs_handle *hufs, 
                              struct ufs_info_type *info);

/* 
 * Function used to get the UFS error statistics
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Output: err_info - Information about UFS errors 
 * Return: None
 * */
void ufs_fill_in_error_stats (struct ufs_handle *hufs, struct ufs_error_stats *err_info);

/* 
 * Function used to get the UFS operational mode capabilities
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Output: caps - Information about the operational mode capabilities
 * Return: None
 * */
void ufs_fill_in_operation_mode_caps (struct ufs_handle *hufs, void *caps);

/* 
 * Function used to get the current UFS operational mode information
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Output: curr_op_mode - Information about the current operational mode 
 * Return: None
 * */
void ufs_fill_in_current_operating_mode (struct ufs_handle *hufs, 
                                         struct ufs_current_operational_mode_info *curr_op_mode);

/* 
 * Main function used for the initial provisioning of the UFS device
 * and configuration of the LU layout
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         cfg - LU configuration information
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_do_config_device( struct ufs_handle *hufs, 
                              struct ufs_config_descr *cfg );

/* 
 * Set the value of the bRefClkFreq
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         freq - RefClk frequency in Hz
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_bRefClkFreq (struct ufs_handle *hufs, uint32_t freq);

/* 
 * Send the scsi write buffer command 
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         buf - Pointer to data to write
 *         mode - Mode field in the SCSI CDB
 *         buf_id - Bufer ID field in the SCSI CDB
 *         offset - Buffer Offset field in the SCSI CDB
 *         len - Data transfer length in bytes
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_scsi_write_buf (struct ufs_handle *hufs, uint8_t *buf, 
                            uint8_t mode, uint8_t buf_id, 
                            uint32_t offset, uint32_t len);

/* 
 * Send the scsi read buffer command 
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         buf - Pointer to data to write
 *         mode - Mode field in the SCSI CDB
 *         buf_id - Bufer ID field in the SCSI CDB
 *         offset - Buffer Offset field in the SCSI CDB
 *         len - Data transfer length in bytes
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_scsi_read_buf (struct ufs_handle *hufs, uint8_t *buf, 
                           uint8_t mode, uint8_t buf_id, 
                           uint32_t offset, uint32_t len);

/* 
 * Set the UFS gear speed to operational speed
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_set_gear (struct ufs_handle *hufs);

/* 
 * Control the operation of the pre-programming mode
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         code - Vendor specific operation code
 * Return: EOK for success, EIO if operation failed
 * */
int32_t ufs_vend_pprog_ctrl (struct ufs_handle *hufs, uint32_t code);

/* 
 * Get UNIPRO/MPHY Capabilities
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_phy_capabilities (struct ufs_handle *hufs);

/* 
 * Write the RPMB command message buffer out using 
 * security protocal out operation
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         msg_buf - Message buffer containing the message
 * Return: EOK for success, EIO if operation failed
 * */
int32_t ufs_mem_rpmb_msg_out (struct ufs_handle *hufs, uint8_t *msg_buf);

/* 
 * Read the RPMB commang message buffer in using 
 * security protocal in operation
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         msg_buf - Message buffer containing the message
 * Return: EOK for success, EIO if operation failed
 * */
int32_t ufs_mem_rpmb_msg_in (struct ufs_handle *hufs, uint8_t *msg_buf);

/* 
 * Read the write counter value
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         pkt_buf - Message buffer containing the RPMB response message
 * Return: EOK for success, EIO if operation failed
 * */
int32_t ufs_mem_rpmb_read_write_cnt (struct ufs_handle *hufs, uint8_t *pkt_buf);

/* 
 * Write data blocks
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         blocks - Number of data block to be transferred
 *         cmd_buf - Message buffer containing the command message + data
 *         rsp_buf - Response buffer containing the result of the operation
 * Return: EOK for success, EIO if operation failed
 * */
int32_t ufs_mem_rpmb_write_data (struct ufs_handle *hufs, uint32_t blocks, 
                                 uint8_t *cmd_buf, uint8_t *rsp_buf);

/* 
 * Read data blocks
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         pkt_buf - Message buffer containing the RPMB response message
 * Return: EOK for success, EIO if operation failed
 * */
int32_t ufs_mem_rpmb_read_data (struct ufs_handle *hufs, uint32_t blocks, 
                                uint8_t *cmd_buf, uint8_t *data_buf);
/* 
 * Poll any pending non-blocking transfer
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         xfr_context - Details about the read/write command that was previously issued 
 * Return: EOK for success
 * */
int32_t ufs_finish_pending_xfer (struct ufs_handle *hufs, 
                                 struct ufs_xfr_context *xfr_context);

/*
 * Set UFS operational state (voltage corner and gear)
 *
 * Input:  hufs - Pointer to the UFS handle structure
           volt_corner - voltage corner to set
           gear - Gear to set.
 * Return: EOK for success, error otherwise
 * */
int32_t ufs_do_operational_mode (struct ufs_handle *hufs, uint8_t volt_corner, uint8_t gear);

/* 
 * Gate the UFS clocks after putting the link in hibernate
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, error otherwise 
 * */
int32_t ufs_do_clock_gate (struct ufs_handle *hufs);

/* 
 * Ungate the UFS clocks and take the link out of hibernate
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Return: EOK for success, error otherwise 
 * */
int32_t ufs_do_clock_ungate (struct ufs_handle *hufs);

/*
 * Enable/disable manual hibernate
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         enter - enter/exit hibernate
 * Return: EOK for success, error otherwise
 * */
int32_t ufs_link_h8 (struct ufs_handle *hufs, uint8_t enter);

/*
 * Enable auto-hibernate
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         idle_time_ms - idle timer value in ms
 * Return: None
 * */
void ufs_link_autoH8 (struct ufs_handle *hufs, uint16_t idle_time_ms);

/*
 * Finish UFS configuration (voltage switch + gear config)
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         config- configuration mode
 * Return: EOOK for success, error otherwise
 * */
int32_t ufs_do_finish_config (struct ufs_handle *hufs, ufs_config_mode mode);

#if !defined (FEATURE_NO_SHARED_ICE)

/*
 * Set SharedIce Algorithm. (Static/Floor/Instant)
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         buffer - Buffer containing sharedIce algorithm and register values.
 * Return: EOK for success, error otherwise
 * */
int32_t ufs_do_set_shared_ice_algo(struct ufs_handle *hufs, void *algo_info);

/*
 * Get SharedIce Algorithm. (Static/Floor/Instant)
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         buffer - Buffer containing sharedIce algorithm and register values.
 * Return: EOK for success, error otherwise
 * */
int32_t ufs_do_get_shared_ice_algo(struct ufs_handle *hufs, void *algo_info);

#endif

#ifdef FEATURE_XBOOT
/*
 * Get the device descriptor　(raw value)
 *
 * Input:  hufs - Pointer to the UFS handle structure
 *         buf - Pointer to data to write
 *         size - Data transfer size in bytes
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_descriptor_device_raw(struct ufs_handle *hufs,
                                      char *buf, uint32_t size);

/*
 * Get one of the unit dscriptors from the UFS device 　(raw value)
 *
 * Input:  hufs - Pointer to the UFS handle structure
 * Input:  id - ID of the descriptor to get
 *         buf - Pointer to data to write
 *         size - Data transfer size in bytes
 * Return: EOK for success, EIO if IO error is encountered
 * */
int32_t ufs_get_descriptor_unit_raw(struct ufs_handle *hufs,
                                    uint32_t lun, char *buf,
                                    uint32_t size);

#endif /* FEATURE_XBOOT */

#endif /* UFS_MEMORY_H */
