/**********************************************************************
 *
 * UFS memory layer - 
 * Main UFS memory interface layer, contain the code to initialize
 * a UFS memory device, formation of SCSI command to read/write to 
 * memory device and decoding device descriptor strings
 * This layer work on the data structures to read/write data or to 
 * get the device descriptor
 *
 * Copyright (c) 2012-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *
 **********************************************************************/

/*======================================================================

                        EDIT HISTORY FOR MODULE


when         who     	what, where, why
----------   ---     ----------------------------------------------------- 
2022-09-16   jt      Do re-initialization for Eye Monitor 
2022-07-11   jt      Enable adapt for gear config during boot 
2022-06-10   jt      Use FUA value from configuration settings for XBL core
2022-06-07   jt      Add function to pass info to HLOS
2022-05-14   sa      Added support for BlockIo2 with multiple doorbells.
2022-05-10   sa      Added SharedIce information.
2022-05-02   jt      Correct RPMB partition size
2022-04-06   pz      Report RPMB partition region 0 size
2022-02-04   jt      Restore clock to existing voltage corner after ungate
2021-11-02   jt      Print out sense data for errors 
2021-10-25   jt      Add write booster and sync cache support 
2021-09-08   jt      Lower gear if battery voltage is insufficient 
2021-08-13   jt      Do partial init for WLUN_BOOT 
2021-04-28   jt      Add field for crypto engine enable
2021-04-28   jt      Add ICE support 
2021-02-16   jt      Don't print serial number
2020-12-08   jt      Add HPB provisioning changes 
2020-10-05   jt      Tune Unipro parameters for clock scaling errors
2020-06-29   jt      Add additional logging 
2020-06-02   jt      Include bBootLunEn for device info 
2020-03-31   jt      Add power management functions
2020-02-21   jt      Read 0xE6 bytes for configuration descriptor
2019-10-10   jt      Change Turbo Write to Write Booster
2019-08-14   jt      Add JEDEC-compliant Turbo Write changes
2019-06-28   jt      Get config descriptor when checking LUNs if needed  
2019-06-26   jt      Correct calculation of TW Alloc Units  
2019-05-16   jt      Correct offset to TW Alloc Units in Unit Descriptor 
2019-04-29   jt      Print out active boot LUN
2019-03-27   vk      Align buffer to cache line length 
2019-03-25   jt      Add Turbo Write changes
2019-02-01   jt      Add UFS 3.0 support  
2018-12-20   jt      Increase poll time for fDeviceInit completion 
2018-11-29   jt      Only skip fDeviceInit for primary UFS
2018-09-24   jt      Remove 1 controller restriction
2018-08-16   jt      Add clock gate/ungate functions 
2018-06-22   bb      Added printing UFS part info
2018-06-11   jt      Remove the logging of a RPMB error  
2017-05-22   jt      Skip getting descriptors if we already have them
2016-10-01   jt      Update bBootLunEn locally after successful update 
2016-09-21   jt      Secure write protect changes  
2016-08-18   jt      Skip fDeviceInit for XBL core  
2016-08-01   jt      Deinit hba after UFS provisioning  
2016-07-28   jt      Add new geometry descriptor fields   
2016-05-18   jt      Set selector = 0 for ufs_read_attributes  
2016-01-25   rh      BlockIO2 debug update
2015-05-14   jt      Use ReliableWriteCount for UFS RPMB write  
2015-04-14   rh      Use no timeout for format command
2015-03-26   jt/rm   Fix ufs rpmb read write
2015-03-26   rh      Add ufs_get_descriptor_rpmb
2015-02-18   rh      Split set/poll for fDeviceInit
2014-09-17   rh      Merge with UEFI driver changes
2014-04-22   rh      Adding the pre-prog config option
2014-01-08   rh      Adding report for ENH memory type 3/4 scale factor
2013-11-05   rh      Adding the format API
2013-10-22   rh      Ensure command req structure is 0 before request
2013-10-22   rh      Provide a way for ufs_api.c to change current gear
2013-10-03   rh      Adding SCSI command REQUEST SENSE
2013-09-25   rh      Adding Toshiba specific bRefClkFreq override
2013-09-18   rh      Adding write for bConfigDescrLock attribute
2013-09-09   rh      Adding a bitfield to indicate which LUN is enabled
2013-09-05   rh      Fix a translation mistake on WLUN BOOT ID 
2013-09-04   rh      Adding enhanced area capacity adjustment factor
2013-09-03   rh      Add more debug message
2013-08-20   rh      64k limitation should be block, not byte
2013-08-12   rh      Unit descriptor is one byte short
2013-01-10   rh      Initial creation
=======================================================================*/

#include "ufs_osal.h"
#include "ufs_api.h"
#include "ufs_memory.h"
#include "ufs_core.h"
#include "ufs_errno.h"
#include "ufs_utp_core.h"
#include "ufs_bsp.h"
#include "HALhwio.h"

// Define the number of HCI controller
#define MAX_UFS_NOP_PING_RETRY      2       // How many time to retry the NOP UPIU
#define MAX_UFS_WAIT_PURGE_ENABLE   100000

// SCSI Transfer Sizes
#define MAX_SCSI_READ10_LENGTH      16383
#define MAX_SCSI_WRITE10_LENGTH     16383

// RPMB message specific defines
#define RPMB_MSG_SIZE               512
#define RPMB_SECTOR_SIZE            256

// Use a static buffer for storage of RPMB messages
static uint8_t rpmb_msg_buf[RPMB_MSG_SIZE];

// General static buffer used to hold PRDT transaction
uint8_t ufs_static_buf[128] __attribute__ ((aligned (CACHE_LINE_LENGTH_BYTES)));

ufs_host_t ufs_host_info_array[MAX_UFS_HCI_ID] __attribute__ ((aligned (CACHE_LINE_LENGTH_BYTES)));

// Reliable write count currently used for RPMB operations  
extern UINT32 ReliableWriteCount;

#define UFS_DESCRIPTOR_BUF_SIZE        256

#define GET_PHYADDR(x)    ((uint64_t)x)


void ufs_print_inquiry_str(ufs_host_t *hba)
{
  uint32_t j = 0;
  uint8 vid_buf[32];
  char log_buf[64];

  for (j=0;j<28;j++)
  {
    vid_buf[j] = hba->inquiry_vid[j] != 0 ? hba->inquiry_vid[j] : ' ';
  }

  vid_buf[j] = '\0';

  snprintf(log_buf, 64, "UFS INQUIRY ID: %s", vid_buf);
  ufs_bsp_log(log_buf, UFS_LOG_INFO);
}

void ufs_print_serial_num_str (struct ufs_handle *hufs)
{
   char log_buf[128] = {0}, serial_num[128] = {0};
   char str_descriptor[256] = {0}; 
   ufs_host_t *hba = hufs->phc;
   uint32_t i = 0, length = 0; 

   /* Get Serial Number string descriptor and convert from Unicode to ASCII. There are at most 126 Unicode characters */
   if (ufs_get_descriptor_str (hufs, hba->desc_dev.iSerialNumber, str_descriptor, sizeof(str_descriptor)) != EOK) 
   {
      return; 
   }

   if (str_descriptor[1] != 0x05)
   {
      return; 
   }

   length = str_descriptor[0]; 

   for (i = 0; i < (length - 2) / 2; i++) 
   {
      serial_num[i] = str_descriptor[(2 * i) + 3]; 
   }
   serial_num[i] = '\0'; 

   snprintf (log_buf, sizeof(log_buf), "UFS Serial Number: %s", serial_num);
   ufs_bsp_log (log_buf, UFS_LOG_INFO); 
}

int32_t ufs_mem_init (struct ufs_handle *hufs)
{
   ufs_host_t *hba;
   int32_t rc = EOK;

   // Check the validation of the core
   if (hufs == NULL) {
      return -ENODEV;
   }

   if (hufs->ufs_core_id >= MAX_UFS_HCI_ID) {
      return -ENODEV;
   }

   hba = &ufs_host_info_array[hufs->ufs_core_id];

   if (hba->init_stage != 2) {
      if (hba->init_stage == 0) {
         // Clear the device info array
         osal_memset (ufs_host_info_array, 0, sizeof(ufs_host_t) * MAX_UFS_HCI_ID);
   
         // Get the platform configuration 
         ufs_bsp_get_platform_config (&hba->plat_cfg);

         // As there are PHY updates for Eye Monitor, we will need to do the complete initialization
         #ifdef FEATURE_UFS_EYEMON
         hba->plat_cfg.core_skip = 0; 
         #endif

         // Get the default config entries 
         ufs_bsp_get_default_config (hufs->ufs_core_id, &hba->cfg_entries);
      
         hba->ufs_core_id = hufs->ufs_core_id;
      }

      if ((hufs->lun == UFS_WLUN_BOOT) && hba->plat_cfg.partial_init) {
         rc = ufs_utp_partial_init (hba); 
         if (rc == EOK) {
            hba->init_stage = 1; 
         }  
      }
      else {
         // Read the device tree
         if (hba->has_dt_cfg == 0) {
            if (ufs_bsp_get_dt_config (hufs->ufs_core_id, &hba->cfg_entries) == UFS_BSP_NO_ERROR) {
               hba->has_dt_cfg = 1; 
            }
         }

         // Call init for UTP layer
         rc = ufs_utp_init (hba);
         if (rc == EOK) {
            hba->init_stage = 2;
         }
      }
   }

   hufs->phc = hba;

   return rc;
}

int32_t ufs_scsi_process_sense (ufs_host_t *hba, ufs_cmd_req_t *req)
{
   int32_t rc = EOK;
   uint16_t sense_len;
   uint16_t i;
   char log_buf[16] = {0}; 

   sense_len = (req->req_sense[0] << 8) | req->req_sense[1];
   // Check there is a valid sense data
   if ((sense_len < 12) || (sense_len > 18)) {
      ufs_error_log(hba, 0x02a0);
      return -EPROTO;
   }
   // Keep a copy of the sense data
   for (i = 0; i < sense_len; i++) {
      hba->last_req_sense[i] = req->req_sense[i + 2];
   }
   // Verify response code
   if ((req->req_sense[2] & 0x7f) != 0x70) {
      ufs_error_log(hba, 0x02a1);
      return -EPROTO;
   }
   if ((req->req_sense[4] & 0x0f) == SENSE_KEY_UNIT_ATTENTION) {
      // Power on condition, not an error
      rc = EOK;
   }
   else {
      // All other error are flagged and reported
      rc = -EIO;

      snprintf(log_buf, 16, "UFS Sense Data");
      ufs_bsp_log(log_buf, UFS_LOG_ERROR);

      // Print bytes 2-17 in sense data
      for (i = 0; i < 16; i = i + 4) {
         osal_memset (log_buf, 0, sizeof(log_buf));
         snprintf(log_buf, 16, "%02x %02x %02x %02x", 
                  req->req_sense[i + 2], req->req_sense[i + 3], 
                  req->req_sense[i + 4], req->req_sense[i + 5]); 
         ufs_bsp_log(log_buf, UFS_LOG_ERROR); 
      }
   }
   // Update the request status to make sense data has been processed
   req->status = 0;
   return rc;
}

int32_t ufs_finish_pending_xfer (struct ufs_handle *hufs, struct ufs_xfr_context *xfr_context)
{
   return ufs_poll_pending_xfer (hufs->phc, UPIU_TYPE_RESPONSE, xfr_context);
}

int32_t ufs_scsi_read (struct ufs_handle *hufs, uint8_t *buf, 
                       uint32_t lba, uint32_t blocks, struct ufs_xfr_context *xfr_context, 
                       struct ufs_crypto_context *crypto_context)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba;

   // Maximum size of transfer supported by CMD_READ 10 is 16k blocks
   if (blocks > 65535) {
      return -EINVAL;
   }

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_READ10;        // Command
   cdb[1] = 0;    
   cdb[2] = (lba >> 24) & 0xff;     // LBA
   cdb[3] = (lba >> 16) & 0xff;
   cdb[4] = (lba >> 8) & 0xff;
   cdb[5] = (lba) & 0xff;
   cdb[6] = 0;    // Group Number
   cdb[7] = (blocks >> 8) & 0xff;   // Transfer Len
   cdb[8] = (blocks) & 0xff;  
   cdb[9] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = UFS_XFER_FLAGS_READ;
   req.expected_len = blocks * DEFAULT_SECTOR_SIZE;
   req.data_buf_phy = (uint64_t)buf;      // Address of the destination buffer

   if (hba->plat_cfg.slow_xfer) {
      hba->db_infinite_poll = 1;    // If system is slow, don't time out
   }

   // If the transfer context structure is not NULL, the request is asynchronous
   if (xfr_context != NULL) {
      req.async = 1; 
   }

   // If the crypto context structure is not NULL, crypto operations will be enabled for the request
   if (crypto_context != NULL) {
      rc = ufs_utp_enable_crypto_engine (hba); 
      if (rc != EOK) {
         ufs_error_log(hba, 0x0205);
         return rc;
      }

      req.crypto = 1; 
      req.crypto_cfg_index = crypto_context->cfg_index; 
      req.data_unit_number = crypto_context->dun; 
   }

   rc = ufs_do_scsi_command (&req, cdb);
   hba->db_infinite_poll = 0;

   if((req.async) && (xfr_context != NULL)) {
      // Asynchronous transfer, save context. 
      xfr_context->utp_doorbell_bit = req.utp_doorbell_bit;
      xfr_context->resp_upiu_offset = req.resp_upiu_offset; 
      xfr_context->prdt_offset = req.prdt_offset;  
      xfr_context->utp_cmd_desc_phy = req.utp_cmd_desc_phy;
   }

   // Return the status.
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   else if (rc == -EBUSY) {
      // Asynchronous transfer, return status 
      return rc;
   }
   
   if (rc != EOK) {
      ufs_error_log(hba, 0x0280);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0281);
      return -EIO;
   }

   return rc;
}

int32_t ufs_scsi_write (struct ufs_handle *hufs, uint8_t *buf, 
                        uint32_t lba, uint32_t blocks, struct ufs_xfr_context *xfr_context, 
                        struct ufs_crypto_context *crypto_context)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba = hufs->phc; 

   // Maximum size of transfer supported by CMD_READ 10 is 16k blocks
   if (blocks > 65535) {
      return -EINVAL;
   }

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_WRITE10;       // Command
#ifdef FEATURE_CORE_ONLY
   cdb[1] = (hba->cfg_entries.fua_value << 3); 
#else
   cdb[1] = SCSI_FLAG_FUA; 
#endif 
   cdb[2] = (lba >> 24) & 0xff;     // LBA
   cdb[3] = (lba >> 16) & 0xff;
   cdb[4] = (lba >> 8) & 0xff;
   cdb[5] = (lba) & 0xff;
   cdb[6] = 0;                      // Group Number
   cdb[7] = (blocks >> 8) & 0xff;   // Transfer Len
   cdb[8] = (blocks) & 0xff;  
   cdb[9] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = UFS_XFER_FLAGS_WRITE;
   req.expected_len = blocks * DEFAULT_SECTOR_SIZE;
   req.data_buf_phy = (uint64_t)buf;      // Address of the source buffer

   if (hba->plat_cfg.slow_xfer) {
      hba->db_infinite_poll = 1;    // If system is slow, don't time out
   }

   // If the transfer context structure is not NULL, the request is asynchronous
   if (xfr_context != NULL) {
      req.async = 1; 
   }

   // If the crypto context structure is not NULL, crypto operations will be enabled for the request
   if (crypto_context != NULL) {
      rc = ufs_utp_enable_crypto_engine (hba); 
      if (rc != EOK) {
         ufs_error_log(hba, 0x0206);
         return rc;
      }

      req.crypto = 1; 
      req.crypto_cfg_index = crypto_context->cfg_index; 
      req.data_unit_number = crypto_context->dun; 
   }

   rc = ufs_do_scsi_command (&req, cdb);
   hba->db_infinite_poll = 0;

   if ((req.async) && (xfr_context != NULL)) {
      // Asynchronous transfer, save context.
      xfr_context->utp_doorbell_bit = req.utp_doorbell_bit;
      xfr_context->resp_upiu_offset = req.resp_upiu_offset; 
      xfr_context->prdt_offset = req.prdt_offset; 
      xfr_context->utp_cmd_desc_phy = req.utp_cmd_desc_phy;	  
   }

   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   else if (rc == -EBUSY) {
      // Asynchronous transfer, return status 
      return rc;
   }
   
   if (rc != EOK) {
      ufs_error_log(hba, 0x0284);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0285);
      return -EIO;
   }

   return rc;
}


int32_t ufs_scsi_unmap (struct ufs_handle *hufs, 
                        uint32_t lba, uint32_t blocks)
{
   uint8_t cdb[16];
   uint8_t *param = ufs_static_buf;  // Unmap parameter list, 1 item used only, 24 bytes in size
   const uint8_t param_size = 24;
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba;

   // Create the parameter list with a single entry
   osal_memset (param, 0, param_size);
   param[0] = 0;                       // n = 23
   param[1] = 22;                      // n - 1
   param[2] = 0;                       // 
   param[3] = 16;                      // n - 7

   param[8]  = 0x0;                    // Upper 32 bits of LBA
   param[9]  = 0x0;
   param[10] = 0x0;
   param[11] = 0x0;
   param[12] = (lba >> 24) & 0xff;     // Lower 32 bits of LBA
   param[13] = (lba >> 16) & 0xff;
   param[14] = (lba >> 8) & 0xff;
   param[15] = (lba) & 0xff;
   param[16] = (blocks >> 24) & 0xff;  // Blocks
   param[17] = (blocks >> 16) & 0xff;
   param[18] = (blocks >> 8) & 0xff;
   param[19] = (blocks) & 0xff;
   // Reserve 4 bytes

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_UNMAP;         // Command
   cdb[1] = 0;                      // Anchor
   cdb[6] = 0;                      // Group Number
   cdb[7] = 0;                      // Transfer Len = n
   cdb[8] = param_size;      
   cdb[9] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = UFS_XFER_FLAGS_WRITE;
   req.expected_len = param_size;
   req.data_buf_phy = GET_PHYADDR(param);    // Address of the param buffer

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x0288);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0289);
      return -EIO;
   }

   return rc;
}

int32_t ufs_scsi_sync_cache (struct ufs_handle *hufs, uint32_t lba, uint32_t blocks)
{
   uint8_t cdb[16]; 
   ufs_cmd_req_t req; 
   int32_t rc = EOK; 
   ufs_host_t *hba; 

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_SYNC_CACHE10;   // Command
   cdb[2] = (lba >> 24) & 0xff;      // LBA
   cdb[3] = (lba >> 16) & 0xff;
   cdb[4] = (lba >> 8) & 0xff;
   cdb[5] = (lba) & 0xff;
   cdb[7] = (blocks >> 8) & 0xff;  // Blocks
   cdb[8] = (blocks) & 0xff;

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = 0;
   req.expected_len = 0;
   req.data_buf_phy = 0;

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x0203);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0204); 
      return -EIO;
   }

   return rc; 
}

int32_t ufs_scsi_format (struct ufs_handle *hufs)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba;

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_FORMAT;        // Command
   cdb[1] = 0;                      // Parameter
   cdb[2] = 0;                      // Vendor Specific
   cdb[5] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = 0;
   req.expected_len = 0;
   req.data_buf_phy = 0;
   hba->db_infinite_poll = 1;             // Use infinite poll for format

   rc = ufs_do_scsi_command (&req, cdb);

   hba->db_infinite_poll = 0;             
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x02a8);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x02a9);
      return -EIO;
   }

   return rc;
}

int32_t ufs_scsi_write_buf (struct ufs_handle *hufs, uint8_t *buf, 
                            uint8_t mode, uint8_t buf_id, 
                            uint32_t offset, uint32_t len)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba;

   // SCSI write buffer command has a limit on block size of up to 2^24 bytes
   if (len > 0xffffff) {
      return -EINVAL;
   }

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_WRITE_BUFFER;  // Command
   cdb[1] = mode;
   cdb[2] = buf_id;
   cdb[3] = (offset >> 16) & 0xff;
   cdb[4] = (offset >> 8) & 0xff;
   cdb[5] = (offset) & 0xff;        // Transfer Offset
   cdb[6] = (len >> 16) & 0xff;  
   cdb[7] = (len >> 8) & 0xff;   
   cdb[8] = (len) & 0xff;        // Transfer Len
   cdb[9] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = UFS_XFER_FLAGS_WRITE;
   req.expected_len = len;
   req.data_buf_phy = (uint64_t)buf;      // Address of the source buffer
   hba->db_infinite_poll = 1;             // Use infinite poll for write buf

   rc = ufs_do_scsi_command (&req, cdb);

   hba->db_infinite_poll = 0;             
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x0294);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0295);
      return -EIO;
   }

   return rc;
}

int32_t ufs_scsi_read_buf (struct ufs_handle *hufs, uint8_t *buf, 
                           uint8_t mode, uint8_t buf_id, 
                           uint32_t offset, uint32_t len)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba;

   // SCSI write buffer command has a limit on block size of up to 2^24 bytes
   if (len > 0xffffff) {
      return -EINVAL;
   }

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_READ_BUFFER;  // Command
   cdb[1] = mode;
   cdb[2] = buf_id;
   cdb[3] = (offset >> 16) & 0xff;
   cdb[4] = (offset >> 8) & 0xff;
   cdb[5] = (offset) & 0xff;        // Transfer Offset
   cdb[6] = (len >> 16) & 0xff;  
   cdb[7] = (len >> 8) & 0xff;   
   cdb[8] = (len) & 0xff;        // Transfer Len
   cdb[9] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = UFS_XFER_FLAGS_READ;
   req.expected_len = len;
   req.data_buf_phy = (uint64_t)buf;      // Address of the source buffer

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x0298);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0299);
      return -EIO;
   }

   return rc;
}


// Test Unit Ready command
int32_t ufs_scsi_unit_rdy (struct ufs_handle *hufs)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba;

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_TEST_UNIT_RDY; // Command
   cdb[9] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = 0;                // No data transfer expected
   req.expected_len = 0;
   req.data_buf_phy = 0;      // Address of the param buffer

   do {
      rc = ufs_do_scsi_command (&req, cdb);
      if (rc == EOK) {
         break; 
      }
      else {
         if (rc == -ECHKCND) {
            rc = ufs_scsi_process_sense (hba, &req);
            if (rc != EOK) {
               ufs_error_log(hba, 0x028b);
               return rc; 
            }
            else {
               if ((req.req_sense[4] & 0x0f) == SENSE_KEY_UNIT_ATTENTION) {
                  continue; 
               }
               else {
                  break; 
               }
            }
         }
         else {
            ufs_error_log(hba, 0x028c);
            return rc;
         }
      }
   }
   while (1); 

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status == SCSI_STATUS_BUSY) {
      ufs_error_log(hba, 0x028d);
      return -EBUSY;
   }
   else if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x028e);
      return -EIO;
   }

   return rc;
}

// Start stop unit
int32_t ufs_scsi_start_stop_unit (struct ufs_handle *hufs, uint32_t power_cond)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba;

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_START_STOP_UNIT; // Command
   cdb[4] = (power_cond << 4) & 0xf0; // New power condition
   cdb[5] = 0;                        // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = UFS_WLUN_DEVICE;  // LUN is always for the device
   req.flags = 0;             // No data transfer expected
   req.expected_len = 0;
   req.data_buf_phy = 0;      // Address of the param buffer

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x027c);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status == SCSI_STATUS_BUSY) {
      ufs_error_log(hba, 0x027d);
      return -EBUSY;
   }
   else if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x027e);
      return -EIO;
   }

   return rc;
}

// Request Sense command
int32_t ufs_scsi_req_sense (struct ufs_handle *hufs, uint32_t lun )
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   uint8_t *sense_buf = ufs_static_buf;
   const uint8_t sense_buf_size = 18;
   int32_t rc = EOK;
   ufs_host_t *hba;

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_REQUEST_SENSE; // Command
   cdb[4] = 18;                     // 18 bytes for sense data
   cdb[5] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.lun = lun;
   req.flags = UFS_XFER_FLAGS_READ;
   // Transfer up to 20 bytes of sense data, expect 18
   req.expected_len = sense_buf_size;  
   req.data_buf_phy = GET_PHYADDR(sense_buf);

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      // Decode and record the sense data
      rc = ufs_scsi_process_sense (hba, &req);
   }

   if (rc != EOK) {
      ufs_error_log(hba, 0x029c);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status == SCSI_STATUS_BUSY) {
      ufs_error_log(hba, 0x029d);
      return -EBUSY;
   }
   else if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x029e);
      return -EIO;            
   }

   return rc;
}

// Get list of active LUNs
int32_t ufs_scsi_inquiry (struct ufs_handle *hufs)
{
   uint8_t cdb[16];
   uint8_t *param = ufs_static_buf;       // Inquiry string is 96 bytes
   uint8_t param_size = 96;
   ufs_host_t *hba;
   ufs_cmd_req_t req;
   int32_t rc = EOK;

   hba = hufs->phc;

   if (hba->has_scsi_inquiry) {
      return EOK;
   }

   // Create the parameter list with a single entry
   osal_memset (param, 0, param_size);

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_INQUIRY; // Command
   cdb[1] = 0;                      // EVPD
   cdb[3] = 0;                      // Pagecode
   cdb[4] = param_size;          // Transfer Len = param array size
   cdb[5] = 0;                      // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   req.phc = hufs->phc;
   req.lun = hufs->lun;
   req.flags = UFS_XFER_FLAGS_READ;
   req.expected_len = param_size;
   req.data_buf_phy = GET_PHYADDR(param);    // Address of the param buffer

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x0201);
      return rc;
   }

   // Verify SCSI transfer status
   hba->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0202);
      return -EIO;
   }

   ufs_bsp_cache_op (param, param_size, INVAL); 
   // Copy the Vendor ID and store it
   osal_memcpy (hba->inquiry_vid, param + 8, 28);
   hba->has_scsi_inquiry = 1;

   // Print the inquiry string to console
   ufs_print_inquiry_str(hba);

   return rc;
}

/* General function to reset the host controller.*/
int32_t ufs_reset_host_controller(struct ufs_handle *hufs)
{
  int32_t rc = EOK;
  ufs_bsp_speed_config config;
  ufs_host_t *hba;
  int i=0;

  hba = hufs->phc;

  //Resetting this flag to force reinit in some functions.
  hba->plat_cfg.core_skip = 0;

  // Reset the host controller and cause link startup
  rc = ufs_utp_reinit_host_controller(hba);
  if (rc != EOK) {
     ufs_error_log(hba, 0x02c0);
	 return rc; 
  }

  //wait for device awake
  hba->device_awake=0;
  rc = ufs_wait_device_awake(hufs);
  if (rc != EOK) {
     ufs_error_log(hba, 0x02c1);
	 return rc; 
  }

  // fdevice init
  hba->fDeviceInit_sent = 0;
  hba->fDeviceInit_done = 0;
  rc = ufs_set_fDeviceInit(hufs, FALSE);
  if (rc != EOK) {
     ufs_error_log(hba, 0x02c2);
	 return rc; 
  }

  rc = ufs_poll_fDeviceInit (hufs);
  if (rc != EOK) {
    ufs_error_log(hba, 0x02c3);
	return rc;
  }

  // SCSI sense for all the LUN'S
  rc = ufs_scsi_req_sense(hufs, UFS_WLUN_DEVICE);
  if (rc != EOK) {
     ufs_error_log(hba, 0x02c4);
	 return rc;
  }

  for(i=0; i<hba->desc_dev.bNumberLU; i++)
  {
    rc = ufs_scsi_req_sense(hufs, i);
	if (rc != EOK) {
      ufs_error_log(hba, 0x02c5);
	  return rc;
    }
  }
  
  rc = ufs_scsi_req_sense(hufs, UFS_WLUN_RPMB);
  if (rc != EOK) {
     ufs_error_log(hba, 0x02c6);
	 return rc;
  }
	
  // Get the current gear config.
  osal_memcpy (&config, &hba->curr_speed_config, sizeof(ufs_bsp_speed_config));

  // Set current gear to 0 in hba, to reinitialise gear 
  osal_memset (&hba->curr_speed_config, 0, sizeof(hba->curr_speed_config));
  rc = ufs_utp_gear_sw(hba,&config);
  if (rc != EOK) {
     ufs_error_log(hba, 0x02c7);
	 return rc;
  }

  // Enable Write Booster 
  rc = ufs_set_fWriteBooster (hufs, 1); 
  if ((rc != EOK) && (rc != -EPERM)) {
       ufs_error_log(hba, 0x02cd); 
       return rc; 
      }

  //Restore the flag to skip core init functions.
  hba->plat_cfg.core_skip = 1;

  return rc;
}

// Set the gear speed to operational speed
int32_t ufs_set_gear (struct ufs_handle *hufs)
{
   ufs_host_t *hba;
   int32_t rc = EOK;
   ufs_bsp_err_type err = UFS_BSP_NO_ERROR;
   uint32_t curr_gear = 0, curr_rate = 0, num_lanes = 0, volt_mv = 0; 
   char rate = 'B', log_buf[32] = {0}; 
   ufs_bsp_speed_config *config; 

   hba = hufs->phc;
   
   if (hba->has_gear_switched) {
      return rc;
   }

   // Allow adapt during gear switch in boot 
   hba->cfg_entries.init_speed_params.adapt = 1; 
   hba->cfg_entries.perf_speed_params.adapt = 1; 

   config = &hba->cfg_entries.init_speed_params; 

   // Skip gear switch for primary UFS if required, but take note 
   // of the current gear, number of lanes
   if (hba->plat_cfg.core_skip && (hba->ufs_core_id == 0)) {
      // Query the current device gear 
      rc = ufs_utp_uic_getset (hba, UICCMDR_DME_PEER_GET, UIC_ARG0_MIBattr(TX_HSGEAR, GenSelectTx(0)), 
                               0, &curr_gear);
      if (rc == EOK) {
         hba->curr_speed_config.gear = curr_gear & 0xff; 
         hba->curr_speed_config.enable_hs = 1;  
      }
      else {
         ufs_error_log (hba, 0x02b5);
         return rc; 
      }

      // Query the current rate 
      rc = ufs_utp_uic_getset (hba, UICCMDR_DME_PEER_GET, UIC_ARG0_MIBattr(TX_HSRATE_Series, GenSelectTx(0)),
                               0, &curr_rate);
      if (rc == EOK) {
          hba->curr_speed_config.rate = curr_rate & 0xff; 
      }
      else {
         ufs_error_log (hba, 0x002b6);
         return rc; 
      }

      // Query the number of active lanes 
      rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_ActiveTxDataLanes, 0), 
                               0, &num_lanes); 
      if (rc == EOK) {
         hba->curr_speed_config.num_lanes = num_lanes & 0xff; 
      }
      else {
         ufs_error_log (hba, 0x02b7); 
         return rc; 
      }

      if (hba->cfg_entries.perf_speed_params.gear == hba->curr_speed_config.gear) {
         hba->has_gear_switched = 1; 
         return EOK; 
      }
      else {
         // If gear was lowered in XBL_SC due to low battery, don't change the gear in Ramdump 
         #if defined(BOOT_RAMDUMP_ENABLE) && !defined(FEATURE_DEVICEPROGRAMMER_IMAGE)
            hba->has_gear_switched = 1; 
            return EOK;  
         #else 
            config = &hba->cfg_entries.perf_speed_params; 
         #endif
      }
   }

   rc = ufs_utp_tune_unipro_params (hba);
   if (rc != EOK) {
      return rc; 
   }

   // Check battery status and adjust to gear 1 if battery threshold is not met 
   err = ufs_bsp_get_vbatt (&volt_mv); 
   if (err == 0) {
      if (volt_mv <= hba->cfg_entries.battery_threshold_mv) {
         config->gear = 1; 

         snprintf(log_buf, sizeof(log_buf), "UFS Gear 1 due to low battery");
         ufs_bsp_log(log_buf, UFS_LOG_INFO); 
      }
   }
   else {
      if (err != UFS_BSP_ERR_FEATURE_UNSUPPORTED) {
         ufs_error_log (hba, 0x02ba); 
         return -EPROTO;
      }
   }

   rc = ufs_utp_gear_sw (hba, config);
   if (rc != EOK) {
      ufs_error_log (hba, 0x02b0);
   }
   else {
      hba->has_gear_switched = 1;
      if (hba->curr_speed_config.rate == RATE_A) {
         rate = 'A';
      }
      snprintf(log_buf, 32, "UFS Speed: Gear %d Lane %d Rate %c", hba->curr_speed_config.gear, 
               hba->curr_speed_config.num_lanes, rate);
      ufs_bsp_log(log_buf, UFS_LOG_ERROR);
   }

   return rc;
}

int32_t ufs_check_valid_lun (struct ufs_handle *hufs, uint8_t lun)
{
   int32_t rc = EOK;
   ufs_host_t *hba = hufs->phc;

   // Check the default always enabled LUs
   if (lun == UFS_WLUN_REPORT ||
       lun == UFS_WLUN_DEVICE  ||
       lun == UFS_WLUN_RPMB) {
      return EOK;
   }
   
   // If it is boot LU, check to see if the BootLU is enabled
   if (lun == UFS_WLUN_BOOT && hba->attr.bBootLunEn != 0) {
      return EOK;
   }

   if (hba->has.has_desc_config == 0) {
      rc = ufs_get_descriptor_config (hufs); 
      if (rc != EOK) {
         return rc; 
      }
   }
 
   // Check the list of enabled LUs
   if (hba->desc_cfg.unit_cfg[lun].bLUEnable) {
      return EOK;
   }

   return -ENOENT;
}


// Get the device descriptor string
int32_t ufs_get_descriptor_str (struct ufs_handle *hufs, uint32_t id,
                                char *buf, uint32_t size)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint32_t xsize;

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   // Limit the read size to 512 bytes
   xsize = size;
   if (xsize > 512) {
      xsize = 512;
   }

   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   req.resp_data_len = xsize;
   req.resp_data_buf = (uint8_t *)buf;
   req.idn = UFS_DESC_IDN_STRING;
   req.idx = id;

   rc = ufs_read_dev_descriptor (&req);
   return rc;
}

// Get device size, LUN size, Number of LUN activated, store in dev_t 
int32_t ufs_get_descriptor_unit (struct ufs_handle *hufs, uint32_t id)
{
   ufs_host_t *hba;
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint8_t buf[0x22];
   uint8_t *pt;
   uint64_t qLogicalBlockCount;
   uint32_t dEraseBlockSize;

   // LUN ID can be from 0 to 7 for UFS device
   if (id > 7) {
      return -EINVAL;
   }

   hba = hufs->phc;
   if (hba->has.has_desc_unit[id] == 1) {
      return EOK; 
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   req.resp_data_len = sizeof(buf);
   req.resp_data_buf = buf;
   req.idn = UFS_DESC_IDN_UNIT;
   req.idx = id;

   rc = ufs_read_dev_descriptor (&req);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0210);
      return rc;
   }

   // Check if the content of unit descriptor is reasonable
   if (buf[1] != 0x02) {
      ufs_error_log(hba, 0x0211);
      return -EIO;
   }

   // Record the LUN in use flag and size
   pt = &buf[0xb];
   qLogicalBlockCount =  (uint64_t)*pt++ << 56;
   qLogicalBlockCount |= (uint64_t)*pt++ << 48;
   qLogicalBlockCount |= (uint64_t)*pt++ << 40;
   qLogicalBlockCount |= (uint64_t)*pt++ << 32;
   qLogicalBlockCount |= (uint64_t)*pt++ << 24;
   qLogicalBlockCount |= (uint64_t)*pt++ << 16;
   qLogicalBlockCount |= (uint64_t)*pt++ << 8;
   qLogicalBlockCount |= (uint64_t)*pt++;

   hba->desc_unit[id].qLogicalBlockCount = qLogicalBlockCount;

   pt = &buf[0x13];
   dEraseBlockSize = *pt++ << 24;
   dEraseBlockSize |= *pt++ << 16;
   dEraseBlockSize |= *pt++ << 8;
   dEraseBlockSize |= *pt++;
   
   hba->desc_unit[id].dEraseBlockSize = dEraseBlockSize;

   hba->has.has_desc_unit[id] = 1;
   return rc;
}

// Get the RPMB unit descriptor 
int32_t ufs_get_descriptor_rpmb (struct ufs_handle *hufs)
{
   ufs_host_t *hba;
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint8_t buf[0x22];
   uint8_t *pt;
   uint64_t qLogicalBlockCount;

   hba = hufs->phc;
   if (hba->has.has_desc_rpmb_unit) {
      return EOK; 
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   req.resp_data_len = sizeof(buf);
   req.resp_data_buf = buf;
   req.idn = UFS_DESC_IDN_UNIT;
   req.idx = UFS_WLUN_RPMB;

   rc = ufs_read_dev_descriptor (&req);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0218);
      return rc;
   }

   // Check if the content of unit descriptor is reasonable
   if (buf[1] != 0x02) {
      ufs_error_log(hba, 0x0219);
      return -EIO;
   }

   // Record the LUN in use flag and size
   pt = &buf[0xb];
   qLogicalBlockCount =  (uint64_t)*pt++ << 56;
   qLogicalBlockCount |= (uint64_t)*pt++ << 48;
   qLogicalBlockCount |= (uint64_t)*pt++ << 40;
   qLogicalBlockCount |= (uint64_t)*pt++ << 32;
   qLogicalBlockCount |= (uint64_t)*pt++ << 24;
   qLogicalBlockCount |= (uint64_t)*pt++ << 16;
   qLogicalBlockCount |= (uint64_t)*pt++ << 8;
   qLogicalBlockCount |= (uint64_t)*pt++;

   hba->desc_rpmb.qLogicalBlockCount = qLogicalBlockCount;
   if (hba->desc_dev.wSpecVersion >= 0x300)
   {
      hba->desc_rpmb.bRPMBRegion0Size = buf[0x13];
      hba->desc_rpmb.bRPMBRegion1Size = buf[0x14];
      hba->desc_rpmb.bRPMBRegion2Size = buf[0x15]; 
      hba->desc_rpmb.bRPMBRegion3Size = buf[0x16]; 
   } 
   
   hba->desc_rpmb.bLogicalBlockSize = buf[0x0a];

   hba->has.has_desc_rpmb_unit = 1;
   return rc;
}

// Get device descriptor (1st configuration)
int32_t ufs_get_descriptor_device (struct ufs_handle *hufs)
{
   ufs_host_t *hba;
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint8_t buf[0x57] = {0}; 
   char log_buf[32] = {0}; 

   hba = hufs->phc;
   if (hba->has.has_desc_device) {
      return EOK;
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   req.resp_data_len = 0x1C;
   req.resp_data_buf = buf;
   req.idn = UFS_DESC_IDN_DEVICE;

   rc = ufs_read_dev_descriptor (&req);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0212);
      return rc;
   }

   // Decode the buffer content
   // If bLength > 0x40, increase the length to 0x57 for early UFS 3.1 samples
   if (buf[0] > 0x40) {
      req.resp_data_len = sizeof(buf); 
      rc = ufs_read_dev_descriptor (&req);
      if (rc != EOK) {
         ufs_error_log(hba, 0x0213);
         return rc;
      }
   }

   if (buf[1] != 0x00) {
      // Device descriptor has bDescriptorType of 0x00
      ufs_error_log(hba, 0x0214);
      return -EIO;
   }

   // Record the LUN in use flag and size
   hba->desc_dev.bLength = buf[0]; 
   hba->desc_dev.bNumberLU = buf[0x06];
   hba->desc_dev.bNumberWLU = buf[0x07];
   hba->desc_dev.bBootEnable = buf[0x08];
   hba->desc_dev.bDescrAccessEn = buf[0x09];

   // Print UFS spec version
   hba->desc_dev.wSpecVersion = (buf[0x10] << 8) | buf[0x11];
   snprintf(log_buf, sizeof(log_buf), "UFS Spec Version: %d.%x", buf[0x10], buf[0x11]); 
   ufs_bsp_log (log_buf, UFS_LOG_INFO);

#ifdef FEATURE_CORE_ONLY
   ufs_bsp_hlos_shared_info info; 
   info.ufs_version = ((buf[0x10] & 0xf) << 4) | ((buf[0x11] >> 4) & 0xf);
   ufs_bsp_set_shared_info (hba->ufs_core_id, &info);
#endif 

   hba->desc_dev.iManufacturerName = buf[0x14];
   hba->desc_dev.iProductName = buf[0x15];
   hba->desc_dev.iSerialNumber = buf[0x16];
   hba->desc_dev.iOemID = buf[0x17];
   hba->desc_dev.wManufacturerID = (buf[0x18] << 8) | buf[0x19];
   hba->desc_dev.bUD0BaseOffset = buf[0x1A]; 
   hba->desc_dev.bUDConfigPLength = buf[0x1B]; 
   hba->desc_dev.dExtendedUFSFeaturesSupport = (buf[0x4f] << 24) | (buf[0x50] << 16) | (buf[0x51] << 8) | buf[0x52];
   hba->has.has_desc_device = 1;

   return rc;
}

// Get configuration descriptor
int32_t ufs_get_descriptor_config (struct ufs_handle *hufs)
{
   ufs_host_t *hba;
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint8_t buf[0xE6] = {0};
   uint8_t *pt;
   int i;

   hba = hufs->phc;
   if (hba->has.has_desc_config) {
      return EOK;
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   if ((hba->desc_dev.wSpecVersion >= 0x310) || 
       ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8)) {
      req.resp_data_len = sizeof(buf);
   }
   else
   {
      req.resp_data_len = 0x90;
   }
   req.resp_data_buf = buf;
   req.idn = UFS_DESC_IDN_CONFIGURATION;

   rc = ufs_read_dev_descriptor (&req);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0220);
      return rc;
   }

   // Verify the content of the buffer is configuration descriptor
   if (buf[1] != 0x01) {
      // Configuration descriptor have identifier of 1
      ufs_error_log(hba, 0x0221);
      return -EIO;
   }
   hba->desc_cfg.dev_cfg.bDescriptorType = buf[1];

   // Decode the device configuration
   pt = &buf[3];
   hba->desc_cfg.dev_cfg.bBootEnable = *pt++;
   hba->desc_cfg.dev_cfg.bDescrAccessEn = *pt++;
   hba->desc_cfg.dev_cfg.bInitPowerMode = *pt++;
   hba->desc_cfg.dev_cfg.bHighPriorityLUN = *pt++;
   hba->desc_cfg.dev_cfg.bSecureRemovalType = *pt++;
   hba->desc_cfg.dev_cfg.bInitActiveICCLevel = *pt++;
   hba->desc_cfg.dev_cfg.wPeriodicRTCUpdate = *pt++ << 8;
   hba->desc_cfg.dev_cfg.wPeriodicRTCUpdate |= *pt++;
   if ((hba->desc_dev.wSpecVersion >= 0x310) || 
       ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x80) >> 7)) {
      hba->desc_cfg.dev_cfg.bHPBControl = *pt++;
   }
   if ((hba->desc_dev.wSpecVersion >= 0x310) || 
       ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8)) {
      pt = &buf[0x10];
      hba->desc_cfg.dev_cfg.bWriteBoosterBufferPreserveUserSpaceEn = *pt++;
      hba->desc_cfg.dev_cfg.bWriteBoosterBufferType = *pt++;
   }

   for (i = 0; i < 8; i++) {
      pt = &buf[(hba->desc_dev.bUDConfigPLength * i) + hba->desc_dev.bUD0BaseOffset];

      hba->desc_cfg.unit_cfg[i].bLUEnable = *pt++;
      hba->desc_cfg.unit_cfg[i].bBootLunID = *pt++;
      hba->desc_cfg.unit_cfg[i].bLUWriteProtect = *pt++;
      hba->desc_cfg.unit_cfg[i].bMemoryType = *pt++;
      hba->desc_cfg.unit_cfg[i].dNumAllocUnits = *pt++ << 24;
      hba->desc_cfg.unit_cfg[i].dNumAllocUnits |= *pt++ << 16;
      hba->desc_cfg.unit_cfg[i].dNumAllocUnits |= *pt++ << 8;
      hba->desc_cfg.unit_cfg[i].dNumAllocUnits |= *pt++;
      hba->desc_cfg.unit_cfg[i].bDataReliability = *pt++;
      hba->desc_cfg.unit_cfg[i].bLogicalBlockSize = *pt++;
      hba->desc_cfg.unit_cfg[i].bProvisioningType = *pt++;
      hba->desc_cfg.unit_cfg[i].wContextCapabilities = *pt++ << 8;
      hba->desc_cfg.unit_cfg[i].wContextCapabilities |= *pt++;
      if ((hba->desc_dev.wSpecVersion >= 0x310) || 
          ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8)) {
         pt += 3; 
         if ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x80) >> 7) {
            hba->desc_cfg.unit_cfg[i].wLUMaxActiveHPBRegions = *pt++ << 8;
            hba->desc_cfg.unit_cfg[i].wLUMaxActiveHPBRegions |= *pt++;
            hba->desc_cfg.unit_cfg[i].wHPBPinnedRegionStartIdx = *pt++ << 8;
            hba->desc_cfg.unit_cfg[i].wHPBPinnedRegionStartIdx |= *pt++;
            hba->desc_cfg.unit_cfg[i].wNumHPBPinnedRegions = *pt++ << 8;
            hba->desc_cfg.unit_cfg[i].wNumHPBPinnedRegions |= *pt++;
         }
         else {
            pt += 6; 
         }
         hba->desc_cfg.unit_cfg[i].dLUNumWriteBoosterBufferAllocUnits = *pt++ << 24;
         hba->desc_cfg.unit_cfg[i].dLUNumWriteBoosterBufferAllocUnits |= *pt++ << 16;
         hba->desc_cfg.unit_cfg[i].dLUNumWriteBoosterBufferAllocUnits |= *pt++ << 8;
         hba->desc_cfg.unit_cfg[i].dLUNumWriteBoosterBufferAllocUnits |= *pt++;
      }
   }

   hba->has.has_desc_config = 1;

   return rc;
}


int32_t ufs_get_descriptor_geometry (struct ufs_handle *hufs)
{
   ufs_host_t *hba;
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint8_t buf[0x58] = {0}; 
   char log_buf[32] = {0}; 
   uint64_t ufs_size_gb = 0; 

   hba = hufs->phc;
   if (hba->has.has_desc_geometry) {
      return EOK;
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   if (((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8) && 
       (hba->desc_dev.bLength == 0x57)) 
   {
      req.resp_data_len = sizeof(buf);
   }
   else if ((hba->desc_dev.wSpecVersion >= 0x310) || 
            ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8)) 
   {
      req.resp_data_len = 0x57;
   }
   else if (hba->desc_dev.wSpecVersion >= 0x210) 
   {
      req.resp_data_len = 0x48;
   }
   else
   {
      req.resp_data_len = 0x44;
   }
   req.resp_data_buf = buf;
   req.idn = UFS_DESC_IDN_GEOMETRY;

   rc = ufs_read_dev_descriptor (&req);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0222);
      return rc;
   }

   // Geometry descriptor have identifier of 7
   if (buf[1] != 0x07) {
      ufs_error_log(hba, 0x0223);
      return -EIO;
   }

   // Record the LUN in use flag and size
   if (buf[0xc] == 0) 
   {
      hba->desc_geo.bMaxNumberLU = 8;
   }
   else if (buf[0xc] == 1) 
   {
      hba->desc_geo.bMaxNumberLU = 32;
   }

   hba->desc_geo.dSegmentSize =  (uint32_t)buf[0x10] | 
                                ((uint32_t)buf[0x0f] << 8) | 
                                ((uint32_t)buf[0x0e] << 16) | 
                                ((uint32_t)buf[0x0d] << 24);
   hba->desc_geo.qTotalRawDeviceCapacity =  
           (uint64_t)buf[0x0b] | ((uint64_t)buf[0x0a] << 8) | 
           ((uint64_t)buf[0x09] << 16) | ((uint64_t)buf[0x08] << 24) |
           ((uint64_t)buf[0x07] << 32) | ((uint64_t)buf[0x06] << 40) |
           ((uint64_t)buf[0x05] << 48) | ((uint64_t)buf[0x04] << 56);
   hba->desc_geo.bAllocationUnitSize = buf[0x11];
   hba->desc_geo.bMinAddrBlockSize = buf[0x12];
   hba->desc_geo.bRPMB_ReadWriteSize = buf[0x17];

   hba->desc_geo.wSupportedMemoryTypes = (uint16_t)buf[0x1f] | 
                                        ((uint16_t)buf[0x1e] << 8) ;
   hba->desc_geo.dEnhanced1MaxNAllocU =  (uint32_t)buf[0x2f] | 
                                        ((uint32_t)buf[0x2e] << 8) | 
                                        ((uint32_t)buf[0x2d] << 16) | 
                                        ((uint32_t)buf[0x2c] << 24);
   hba->desc_geo.wEnhanced1CapAdjFac =   (uint16_t)buf[0x31] | 
                                        ((uint16_t)buf[0x30] << 8) ;
   hba->desc_geo.dEnhanced2MaxNAllocU =  (uint32_t)buf[0x35] | 
                                        ((uint32_t)buf[0x34] << 8) | 
                                        ((uint32_t)buf[0x33] << 16) | 
                                        ((uint32_t)buf[0x32] << 24);
   hba->desc_geo.wEnhanced2CapAdjFac =   (uint16_t)buf[0x37] | 
                                        ((uint16_t)buf[0x36] << 8) ;

   hba->desc_geo.dEnhanced3MaxNAllocU =  (uint32_t)buf[0x3b] | 
                                        ((uint32_t)buf[0x3a] << 8) | 
                                        ((uint32_t)buf[0x39] << 16) | 
                                        ((uint32_t)buf[0x38] << 24);
   hba->desc_geo.wEnhanced3CapAdjFac =   (uint16_t)buf[0x3d] | 
                                        ((uint16_t)buf[0x3c] << 8) ;
   hba->desc_geo.dEnhanced3MaxNAllocU =  (uint32_t)buf[0x41] | 
                                        ((uint32_t)buf[0x40] << 8) | 
                                        ((uint32_t)buf[0x3f] << 16) | 
                                        ((uint32_t)buf[0x3e] << 24);
   hba->desc_geo.wEnhanced3CapAdjFac =   (uint16_t)buf[0x43] | 
                                        ((uint16_t)buf[0x42] << 8) ;

   hba->desc_geo.dOptimalLogicalBlockSize = (uint32_t)buf[0x47] | 
                                        ((uint32_t)buf[0x46] << 8) | 
                                        ((uint32_t)buf[0x45] << 16) | 
                                        ((uint32_t)buf[0x44] << 24);

   hba->desc_geo.bHPBNumberLU = buf[0x49];

   hba->desc_geo.wDeviceMaxActiveHPBRegions = (uint16_t)buf[0x4c] | 
                                        ((uint16_t)buf[0x4b] << 8);

   hba->desc_geo.dWriteBoosterBufferMaxNAllocUnits = (uint32_t)buf[0x52] | 
                                        ((uint32_t)buf[0x51] << 8) | 
                                        ((uint32_t)buf[0x50] << 16) | 
                                        ((uint32_t)buf[0x4f] << 24);

   hba->desc_geo.bDeviceMaxWriteBoosterLUs = buf[0x53];
   hba->desc_geo.bWriteBoosterBufferCapAdjFac = buf[0x54];
   hba->desc_geo.bSupportedWriteBoosterBufferUserSpaceReductionTypes = buf[0x55];
   hba->desc_geo.bSupportedWriteBoosterBufferTypes = buf[0x56];

   ufs_size_gb = (hba->desc_geo.qTotalRawDeviceCapacity * 512) / (1000 * 1000 * 1000); 
   if (ufs_size_gb % 2) 
   {
      ufs_size_gb++; 
   }

   snprintf(log_buf, sizeof(log_buf), "UFS Total Size: %d GB", ufs_size_gb);
   ufs_bsp_log(log_buf, UFS_LOG_INFO);

   hba->has.has_desc_geometry = 1;

   return rc;
}

int32_t ufs_get_flags(struct ufs_handle *hufs, struct ufs_info_type *info)
{
   ufs_attr_req_t req;
   ufs_host_t *hba;
   int32_t rc = EOK;

   hba = hufs->phc;

   if (hba->need_flags.need_fPowerOnWPEn) 
   {
      /* Get fPowerOnWPEn flag  */
      osal_memset (&req, 0, sizeof (ufs_attr_req_t));
      req.phc = hufs->phc;
      req.idn = UFS_IDN_fPowerOnWPEn;
      req.idx = 0;
      req.val = 0;

      rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_READ);
      if (rc != EOK) {
         ufs_error_log(hba, 0x02bd);
         return rc; 
      }

      hba->flag.fPowerOnWPEn = req.val; 
      hba->need_flags.need_fPowerOnWPEn = 0; 
      info->fPowerOnWPEn = hba->flag.fPowerOnWPEn; 
   }

   if (hba->need_flags.need_fPermanentWPEn) 
   {
      /* Get fPermanentWPEn flag */
      osal_memset (&req, 0, sizeof (ufs_attr_req_t));
      req.phc = hufs->phc;
      req.idn = UFS_IDN_fPermanentWPEn;
      req.idx = 0;
      req.val = 0;

      rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_READ);
      if (rc != EOK) {
         ufs_error_log(hba, 0x02be); 
         return rc; 
      }

      hba->flag.fPermanentWPEn = req.val; 
      hba->need_flags.need_fPermanentWPEn = 0; 
      info->fPermanentWPEn = hba->flag.fPermanentWPEn; 
   }

   return rc;
}


int32_t ufs_get_phy_capabilities (struct ufs_handle *hufs)
{
   ufs_host_t *hba;
   int32_t rc = EOK;

   hba = hufs->phc;

   if (hufs->phc->has_caps) {
      return EOK;
   }

   rc = ufs_utp_get_host_caps (hba);
   if (rc != EOK) {
      ufs_error_log(hba, 0x02bc);
   }

   hufs->phc->has_caps = 1;

   return rc;
}

// Wait until device is responding to NOP UPIU pings
int32_t ufs_wait_device_awake (struct ufs_handle *hufs)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;
   int32_t i;

   if (hufs->phc->device_awake) {
      return EOK; 
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;

   for (i = 0; i < MAX_UFS_NOP_PING_RETRY; i++) {
      // Ping using NOP_OUT UPIU each try
      rc = ufs_send_nop_ping (&req);
      if (rc == EOK) {
         hufs->phc->device_awake = 1; 
         return rc;
      }
   }
   
   ufs_error_log(req.phc, 0x0228);
   return rc;
}

// Get the bBootLunEn field in the attributes
int32_t ufs_get_bBootLunEn (struct ufs_handle *hufs)
{
   char log_buf[32] = {0}; 
   ufs_attr_req_t req;
   int32_t rc = EOK;

   if (hufs->phc->has_attr.has_bBootLunEn) {
      return EOK;
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;
   req.idn = UFS_IDN_bBootLunEn;
   req.idx = 0;
   req.val = 0;
   req.sel = 0; 

   rc = ufs_read_attributes (&req);

   hufs->phc->attr.bBootLunEn = req.val;
   hufs->phc->has_attr.has_bBootLunEn = 1;

   if (rc == EOK) {
      snprintf(log_buf, 32, "UFS Boot LUN: %d", req.val);
      ufs_bsp_log(log_buf, UFS_LOG_INFO);
   }
   return rc;
}

// Set the bBootLunEn field in the attributes
int32_t ufs_set_bBootLunEn (struct ufs_handle *hufs, uint8_t id)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;
   req.idn = UFS_IDN_bBootLunEn;
   req.idx = 0;
   req.val = id;

   rc = ufs_write_attributes (&req);

   // If attribute written successfully, update bBootLunEn locally
   if (rc == EOK) {
      hufs->phc->attr.bBootLunEn = id; 
   }

   return rc;
}

// Get the bConfigDescrLock field in the attributes
int32_t ufs_get_bConfigDescrLock (struct ufs_handle *hufs)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;

   if (hufs->phc->has_attr.has_bConfigDescrLock) {
      return EOK;
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;
   req.idn = UFS_IDN_bConfigDescrLock;
   req.idx = 0;
   req.val = 0;
   req.sel = 0; 

   rc = ufs_read_attributes (&req);

   hufs->phc->attr.bConfigDescrLock = req.val;
   hufs->phc->has_attr.has_bConfigDescrLock = 1;
   return rc;
}

// Set the bConfigDescrLock field in the attributes
int32_t ufs_set_bConfigDescrLock (struct ufs_handle *hufs, uint8_t val)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;
   req.idn = UFS_IDN_bConfigDescrLock;
   req.idx = 0;
   req.val = val;

   rc = ufs_write_attributes (&req);
   return rc;
}

// Set the bRefClkFreq field in the attributes 
int32_t ufs_set_bRefClkFreq (struct ufs_handle *hufs, uint32_t freq)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;
   req.idn = UFS_IDN_bRefClkFreq;
   req.idx = 0;
   req.sel = 0; 

   rc = ufs_read_attributes (&req);

   switch (freq) {
      case 19200000:
         if (req.val == 0) {
            return EOK;          // If value is set correctly, exit immidiately
         }
         req.val = 0;
         break;
      case 26000000:
         if (req.val == 1) {
            return EOK;
         }
         req.val = 1;
         break;
      case 38400000:
         if (req.val == 2) {
            return EOK;
         }
         req.val = 2;
         break;
      case 52000000:
         if (req.val == 3) {
            return EOK;
         }
         req.val = 3;
         break;
      default:
         return -EINVAL;
   }

   rc = ufs_write_attributes (&req);
   return rc;
}

// Set the fDeviceInit field in the flags and wait for the bit to set
int32_t ufs_set_fDeviceInit (struct ufs_handle *hufs, boolean async)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba;

   hba = hufs->phc;

   // If we are in XBL core, we can skip this for primary UFS
   if (hba->plat_cfg.core_skip && (hba->ufs_core_id == 0)) {
      //Set non_blocking_en = 0 in case we had tried to start the background init
     // hba->non_blocking_en = 0; 
      return EOK; 
   }

   // Check if the internal fDevicInit flag is set, skip the entire function
   if (hba->fDeviceInit_sent) {
      return EOK;
   }

   // If asynchronous fDeviceInit is in progress, poll for the response. 
   // Otherwise, send the fDeviceInit request
   if (hba->fDeviceInit_async) { 
      rc = ufs_poll_pending_xfer (hba, UPIU_TYPE_QUERY_RESP, NULL);
      if (rc != EOK) {
         ufs_error_log(hba, 0x0230);
         return rc; 
      }
      else
      {
         hba->fDeviceInit_async = 0; 
      }
   }
   else
   {
      memset (&req, 0, sizeof (ufs_attr_req_t));
      req.phc = hufs->phc;
      req.idn = UFS_IDN_fDeviceInit;
      req.idx = 0;
      req.val = 0;

      if (async) {
         req.async = 1; 
      }

      // fDeviceInit is not set, sent set flag UPIU
      rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_SET);
      if (rc == -EBUSY && async) {
         // Asynchronous transfer, return status
         hba->fDeviceInit_async = 1; 
         return rc;
      }
      if (rc != EOK) {
         ufs_error_log(hba, 0x0255);
         return rc;
      }
   }

   hba->fDeviceInit_sent = 1;
   return rc;
}

// Poll the fDeviceInit field and wait for the bit to set
int32_t ufs_poll_fDeviceInit (struct ufs_handle *hufs)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;
   int32_t i;
   ufs_host_t *hba;

   hba = hufs->phc;

   // If we are in XBL core, we can skip this for primary UFS 
   if (hba->plat_cfg.core_skip && (hba->ufs_core_id == 0)) {
      return EOK; 
   }

   // Check if the internal fDevicInit flag is set, skip the entire function
   if (hba->fDeviceInit_done) {
      return EOK;
   }

   memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;
   req.idn = UFS_IDN_fDeviceInit;
   req.idx = 0;
   req.val = 0;

   // Loop until flag is cleared
   i = hba->cfg_entries.timeout_values.fdevice_init_timeout_us / 10;
   do {
      rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_READ);
      if (rc != EOK) {
         return rc;
      }
      if (req.val == 0) {
         hba->fDeviceInit_done = 1;
         return EOK;
      }
      ufs_bsp_busy_wait (10);
   } while (i--);

   ufs_error_log(hba, 0x0231);
   // TIMEOUT
   return -ETIME;
}
 
// Enable/disable Write Booster  
int32_t ufs_set_fWriteBooster (struct ufs_handle *hufs, uint8_t val)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;
   ufs_host_t *hba = hufs->phc;
   boolean wb_31_compliant = FALSE; 

   if (hba->plat_cfg.core_skip || (hba->wb_enabled == val)) {
      return EOK; 
   }

   wb_31_compliant = ((((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8) && (hba->desc_dev.bLength == 0x59)) ||
                      (hba->desc_dev.wSpecVersion >= 0x310) || (hba->desc_dev.wSpecVersion == 0x220));

   if (wb_31_compliant == FALSE) {
      return -EPERM;
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;
   req.idn = UFS_IDN_fWriteBoosterEn;
   req.idx = 0;
   req.val = val;

   rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_SET);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0207); 
      return rc; 
   }

   // If enabling write booster, then set flags to flush the Write Booster buffer 
   // during idle and hibernate
   if (val == 1) {
       osal_memset (&req, 0, sizeof (ufs_attr_req_t));
       req.phc = hufs->phc;
       req.idn = UFS_IDN_fWriteBoosterBufferFlushEn; 
       req.idx = 0;
       req.val = 1;

       rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_SET);
       if (rc != EOK) {
          ufs_error_log (hba, 0x0208);
          return rc; 
       }

       osal_memset (&req, 0, sizeof (ufs_attr_req_t));
       req.phc = hufs->phc;
       req.idn = UFS_IDN_fWriteBoosterBufferFlushDuringHibernate;
       req.idx = 0;
       req.val = 1;

       rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_SET);
       if (rc != EOK) {
          ufs_error_log (hba, 0x0209); 
          return rc; 
       }
   }

   hba->wb_enabled = val; 

   return rc;
}

// Set the fPowerOnWPEn field in the flags 
int32_t ufs_set_fPowerOnWPEn (struct ufs_handle *hufs)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   req.phc = hufs->phc;
   req.idn = UFS_IDN_fPowerOnWPEn;
   req.idx = 0;
   req.val = 0;

   rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_SET);

   // If successful, we want to get the new value of the flag 
   if (rc == EOK) {
      hufs->phc->need_flags.need_fPowerOnWPEn = 1; 
   }

   return rc;
}

// Set and wait the fPurgeEnable field in the flags 
int32_t ufs_set_n_wait_fPurgeEnable (struct ufs_handle *hufs, boolean async)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;
   int32_t i;
   ufs_host_t *hba = hufs->phc;

   // If asynchronous and purge flag not set, set it now
   if (async && (hba->purge_set == 0)) {
      osal_memset (&req, 0, sizeof (ufs_attr_req_t));
      req.phc = hufs->phc;
      req.idn = UFS_IDN_fPurgeEnable;
      req.idx = 0;
      req.val = 0;

      rc = ufs_dev_flag_op (&req, UPIU_FLAG_OP_SET);
      if (rc != EOK) {
         return rc;
      }

      hba->purge_set = 1; 
   }

   i = MAX_UFS_WAIT_PURGE_ENABLE;
   do {
      req.phc = hufs->phc;
      req.idn = UFS_IDN_bPurgeStatus;
      req.idx = 0;
      req.val = 0;
      req.sel = 0; 

      rc = ufs_read_attributes (&req);
      if (rc != EOK) {
         ufs_error_log(hba, 0x0237); 
         return rc;
      }

      hufs->phc->attr.bPurgeStatus = req.val;
      // If purge is still in progress, return immediately if asynchronous
      if (req.val == 1) {
         if (async) {
            return -EBUSY;      
         }
         // Wait for some more time
         ufs_bsp_busy_wait (1000);
         continue;
      }
      else if (req.val == 0 || req.val == 3) {
         // Operation completed
         hba->purge_set = 0; 
         return rc;
      }
      else {
         // Operation failed 
         ufs_error_log(hba, 0x0239); 
         return -EIO;
      }
   } while (i--);

   ufs_error_log(hba, 0x0238);   // Timeout
   return -ETIME;
}

// Set the LUN write protect by updating the unit device configuration
int32_t ufs_set_bLUWriteProtect (struct ufs_handle *hufs, uint8_t wp_setting)
{
   ufs_host_t *hba;
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint8_t buf[16 * 8 + 16];     
   // 8 LUN (Each 16 bytes) + Configuration descriptor (16 bytes)

   // LUN ID can be from 0 to 7 for UFS device
   if (hufs->lun > 7) {
      return -EINVAL;
   }

   // WP setting can be either 0, 1, or 2
   if (wp_setting > 2) {
      return -EINVAL;
   }

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));
   hba = hufs->phc;
   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   req.resp_data_len = sizeof (buf);
   req.resp_data_buf = buf;
   req.idn = UFS_DESC_IDN_CONFIGURATION;
   req.idx = hufs->lun;

   rc = ufs_read_dev_descriptor (&req);
   if (rc != EOK) {
      return rc;
   }

   // Decode the buffer content
   if (buf[0] != 0x22) {
      // Unit descriptor is always 0x22 bytes long
      ufs_error_log(hba, 0x0232);
      return -EIO;
   }

   // Update the bLUWriteProtect field
   buf[16 + hufs->lun * 16 + 2] = wp_setting;

   // Write the updated data back
   req.phc = hba;
   req.req_data_len = sizeof (buf);
   req.req_data_buf = buf;
   req.resp_data_len = 0;
   req.resp_data_buf = NULL;
   req.idn = UFS_DESC_IDN_CONFIGURATION;
   req.idx = hufs->lun;
   rc = ufs_write_dev_descriptor (&req);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0233);
   }
   return rc;
}

// Write the RPMB message buffer out using security protocal out operation
int32_t ufs_mem_rpmb_msg_out (struct ufs_handle *hufs, uint8_t *msg_buf)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   const uint32_t len = RPMB_MSG_SIZE;
   ufs_host_t *hba;

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_SECPROT_OUT;   // Command
   cdb[1] = 0xEC;                   // Security Protocal
   cdb[2] = 0x00;                   // 
   cdb[3] = 0x01;                   // Security Protocal Specific
   cdb[4] = 0x00;                   // Reserved
   cdb[5] = 0x00;                   // Reserved
   cdb[6] = (len >> 24) & 0xff;     // 
   cdb[7] = (len >> 16) & 0xff;     // 
   cdb[8] = (len >> 8) & 0xff;      // 
   cdb[9] = (len) & 0xff;           // Transfer Length
   cdb[10] = 0;                     // Reserve
   cdb[11] = 0;                     // Control

   osal_memset (&req, 0, sizeof (ufs_cmd_req_t));
   req.phc = hufs->phc;
   hba = hufs->phc;
   req.lun = UFS_WLUN_RPMB;
   req.flags = UFS_XFER_FLAGS_WRITE;
   req.expected_len = RPMB_MSG_SIZE;
   req.data_buf_phy = GET_PHYADDR (msg_buf);   

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x0240);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0241);
      return -EIO;
   }

   return rc;
}

// Read the RPMB message buffer in using security protocal in operation
int32_t ufs_mem_rpmb_msg_in (struct ufs_handle *hufs, uint8_t *msg_buf)
{
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   int32_t rc = EOK;
   const uint32_t len = RPMB_MSG_SIZE;
   ufs_host_t *hba;

   // Fill in the CDB with SCSI command structure
   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_SECPROT_IN;    // Command
   cdb[1] = 0xEC;                   // Security Protocal
   cdb[2] = 0x00;                   // 
   cdb[3] = 0x01;                   // Security Protocal Specific
   cdb[4] = 0x00;                   // Reserved
   cdb[5] = 0x00;                   // Reserved
   cdb[6] = (len >> 24) & 0xff;     // 
   cdb[7] = (len >> 16) & 0xff;     // 
   cdb[8] = (len >> 8) & 0xff;      // 
   cdb[9] = (len) & 0xff;           // Transfer Length
   cdb[10] = 0;                     // Reserve
   cdb[11] = 0;                     // Control

   req.phc = hufs->phc;
   hba = hufs->phc;
   req.lun = UFS_WLUN_RPMB;
   req.flags = UFS_XFER_FLAGS_READ;
   req.expected_len = RPMB_MSG_SIZE;
   req.data_buf_phy = GET_PHYADDR(msg_buf);   

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x0248);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0249);
      return -EIO;
   }

   return rc;
}

int32_t ufs_mem_rpmb_read_write_cnt (struct ufs_handle *hufs, uint8_t *pkt_buf)
{
   int32_t rc = EOK;
   uint16_t rst;
   ufs_host_t *hba;

   hba = hufs->phc;

   // Fill in the RPMB message buffer
   osal_memset (rpmb_msg_buf, 0, RPMB_MSG_SIZE);
   rpmb_msg_buf[510] = 0x00;
   rpmb_msg_buf[511] = RPMB_REQ_READ_WR_CNT;

   rc = ufs_mem_rpmb_msg_out (hufs, rpmb_msg_buf);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0250);
      return rc;
   }

   // Get the STATUS by issue a security protocal in message
   osal_memset (pkt_buf, 0, RPMB_MSG_SIZE);

   rc = ufs_mem_rpmb_msg_in (hufs, pkt_buf);

   // Check the mesage type to make sure it is good
   if (pkt_buf[510] != RPMB_REQ_READ_WR_CNT ||
       pkt_buf[511] != 0x00) {
      ufs_error_log(hba, 0x0251);
      return -EIO;
   }

   // Check the return status to make sure it is good
   rst = (pkt_buf[508] << 8) | pkt_buf[509];
   hufs->phc->last_rpmb_status = rst;
   if (rst != RPMB_RESULT_OK) {
      ufs_error_log(hba, 0x0252);
      return -EIO;
   }

   // Return the count value
   //*write_cnt = (rpmb_msg_buf[500] << 24) | (rpmb_msg_buf[501] << 16) | 
   //             (rpmb_msg_buf[502] << 8)  | (rpmb_msg_buf[503]);

   return rc;
}

int32_t ufs_mem_rpmb_write_key (struct ufs_handle *hufs, uint8_t *key)
{
   int32_t rc = EOK;
   uint16_t rst;
   ufs_host_t *hba;

   hba = hufs->phc;

   // Fill in the RPMB message buffer
   osal_memset (rpmb_msg_buf, 0, RPMB_MSG_SIZE);
   rpmb_msg_buf[510] = 0x00;
   rpmb_msg_buf[511] = RPMB_REQ_READ_WR_CNT;

   rc = ufs_mem_rpmb_msg_out (hufs, rpmb_msg_buf);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0258);
      return rc;
   }

   // Get the STATUS by issue a security protocal in message
   osal_memset (rpmb_msg_buf, 0, RPMB_MSG_SIZE);

   rc = ufs_mem_rpmb_msg_in (hufs, rpmb_msg_buf);

   // Check the mesage type to make sure it is good
   if (rpmb_msg_buf[510] != RPMB_REQ_READ_WR_CNT ||
       rpmb_msg_buf[511] != 0x00) {
      ufs_error_log(hba, 0x0259);
      return -EIO;
   }

   // Check the return status to make sure it is good
   rst = (rpmb_msg_buf[508] << 8) | rpmb_msg_buf[509];
   hufs->phc->last_rpmb_status = rst;
   if (rst != RPMB_RESULT_OK) {
      ufs_error_log(hba, 0x025a);
      return -EIO;
   }

   return rc;
}

int32_t ufs_mem_rpmb_write_data (struct ufs_handle *hufs, 
                                 uint32_t blocks, 
                                 uint8_t *cmd_buf, 
                                 uint8_t *rsp_buf)
{
   int32_t rc = EOK;
   ufs_host_t *hba = hufs->phc;
   uint16_t rst;
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   uint32_t len;
   uint32_t current_bl;
   uint32_t total_bl;
   uint32_t offset = 0;
   uint8_t result_request[RPMB_MSG_SIZE];
   
   total_bl = blocks;
   while (total_bl) {
      #if 0 
      current_bl = total_bl > hba->desc_geo.bRPMB_ReadWriteSize ? 
                   hba->desc_geo.bRPMB_ReadWriteSize : total_bl;
      #endif 
      current_bl = ReliableWriteCount; 
      total_bl -= current_bl;
      len = current_bl * 512;          // Length is 512 bytes per block to transfer

      // Fill in the CDB with SCSI command structure
      osal_memset (cdb, 0, sizeof(cdb));
      cdb[0] = SCSI_CMD_SECPROT_OUT;   // Command
      cdb[1] = 0xEC;                   // Security Protocal
      cdb[2] = 0x00;                   // 
      cdb[3] = 0x01;                   // Security Protocal Specific
      cdb[4] = 0x00;                   // Reserved
      cdb[5] = 0x00;                   // Reserved
      cdb[6] = (len >> 24) & 0xff;     // 
      cdb[7] = (len >> 16) & 0xff;     // 
      cdb[8] = (len >> 8) & 0xff;      // 
      cdb[9] = (len) & 0xff;           // Transfer Length
      cdb[10] = 0;                     // Reserve
      cdb[11] = 0;                     // Control

      osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
      req.phc = hufs->phc;
      req.lun = UFS_WLUN_RPMB;
      req.flags = UFS_XFER_FLAGS_WRITE;
      req.expected_len = RPMB_MSG_SIZE * current_bl;
      req.data_buf_phy = GET_PHYADDR(cmd_buf + RPMB_MSG_SIZE * offset);   

      rc = ufs_do_scsi_command (&req, cdb);
      if (rc == -ECHKCND) {
         rc = ufs_scsi_process_sense (hba, &req);
      }
      if (rc != EOK) {
         ufs_error_log(hba, 0x0261);
         return rc;
      }

      // Verify SCSI transfer status
      hufs->phc->last_scsi_status = req.status;
      if (req.status != SCSI_STATUS_GOOD) {
         ufs_error_log(hba, 0x0262);
         return -EIO;
      }
      
      // Send result register read request
      osal_memset (result_request, 0, RPMB_MSG_SIZE);
      result_request[511] = 0x05;
      
      rc = ufs_mem_rpmb_msg_out(hufs, result_request);
      
      // Get the STATUS by issue a security protocal in message
      osal_memset (rsp_buf, 0, RPMB_MSG_SIZE);

      rc = ufs_mem_rpmb_msg_in (hufs, rsp_buf);

      // Check the message type to make sure it is good
      if (rsp_buf[510] == RPMB_REQ_DATA_WRITE)
      {
         if(rsp_buf[511] != 0x00)
         {
            ufs_error_log(hba, 0x0265);
         }            
      }
      else if (rsp_buf[510] == RPMB_REQ_KEY_PROG)
      {
         if(rsp_buf[511] != 0x00)
         {
            ufs_error_log(hba, 0x0266);
         }      
      }
      else if (rsp_buf[510] == RPMB_REQ_SECURE_WP_WRITE)
      {
         if(rsp_buf[511] != 0x00)
         {
            ufs_error_log(hba, 0x0267);
         }      
      }
      else
      {
         ufs_error_log(hba, 0x0263);
      }   

      // Check the return status to make sure it is good
      rst = (rsp_buf[508] << 8) | rsp_buf[509];
      hufs->phc->last_rpmb_status = rst;
 
      offset += current_bl;
   }

   return rc;
}

int32_t ufs_mem_rpmb_read_data (struct ufs_handle *hufs, 
                                uint32_t blocks, 
                                uint8_t *cmd_buf, 
                                uint8_t *data_buf)
{
   int32_t rc = EOK;
   uint8_t cdb[16];
   ufs_cmd_req_t req;
   ufs_host_t *hba = hufs->phc;
   uint32_t len;
   uint32_t current_bl;
   uint32_t total_bl;
   uint32_t cmd_offset = 0, data_offset = 0;

   total_bl = blocks;
   while (total_bl) {
       current_bl = total_bl > hba->desc_geo.bRPMB_ReadWriteSize ? 
                    hba->desc_geo.bRPMB_ReadWriteSize : total_bl;
       total_bl -= current_bl;
   
   // Send the command for read data block
       rc = ufs_mem_rpmb_msg_out (hufs, cmd_buf + cmd_offset * RPMB_MSG_SIZE);
   if (rc != EOK) {
      return rc;
   }

   // Write the actual data in a SECPROTO out packet
       len = current_bl * 512;          // Length is 512 bytes per block to transfer

   // Fill in the CDB with SCSI command structure
   osal_memset (cdb, 0, sizeof(cdb));
   cdb[0] = SCSI_CMD_SECPROT_IN;    // Command
   cdb[1] = 0xEC;                   // Security Protocal
   cdb[2] = 0x00;                   // 
   cdb[3] = 0x01;                   // Security Protocal Specific
   cdb[4] = 0x00;                   // Reserved
   cdb[5] = 0x00;                   // Reserved
   cdb[6] = (len >> 24) & 0xff;     // 
   cdb[7] = (len >> 16) & 0xff;     // 
   cdb[8] = (len >> 8) & 0xff;      // 
   cdb[9] = (len) & 0xff;           // Transfer Length
   cdb[10] = 0;                     // Reserve
   cdb[11] = 0;                     // Control

   osal_memset (&req, 0, sizeof(ufs_cmd_req_t));
   req.phc = hufs->phc;
   req.lun = UFS_WLUN_RPMB;
   req.flags = UFS_XFER_FLAGS_READ;
   req.expected_len = len;
       req.data_buf_phy = GET_PHYADDR(data_buf + data_offset * RPMB_MSG_SIZE);   

   rc = ufs_do_scsi_command (&req, cdb);
   if (rc == -ECHKCND) {
      rc = ufs_scsi_process_sense (hba, &req);
   }
   if (rc != EOK) {
      ufs_error_log(hba, 0x0268);
      return rc;
   }

   // Verify SCSI transfer status
   hufs->phc->last_scsi_status = req.status;
   if (req.status != SCSI_STATUS_GOOD) {
      ufs_error_log(hba, 0x0269);
      return -EIO;
   }   
       cmd_offset += 1; 
       data_offset += current_bl; 
   }

   return rc;
}

int32_t ufs_do_config_device( struct ufs_handle *hufs, 
                              struct ufs_config_descr *cfg )
{
   ufs_host_t *hba;
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint8_t buf[0xE6] = {0};
   uint8_t *pt;
   int i;
   boolean wb_31_compliant = FALSE; 

   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   hba = hufs->phc;
   req.phc = hba;

   // Check to see if the device is compliant with UFS 3.1 Write Booster 
   wb_31_compliant = ((((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8) && (hba->desc_dev.bLength == 0x59)) ||
                      (hba->desc_dev.wSpecVersion >= 0x310) || (hba->desc_dev.wSpecVersion == 0x220));

   req.req_data_len = 0x90; 
   if (wb_31_compliant) {
      req.req_data_len = sizeof(buf);
   }
   req.req_data_buf = buf;
   req.resp_data_len = 0;
   req.resp_data_buf = NULL;
   req.idn = UFS_DESC_IDN_CONFIGURATION;
   req.idx = 0;

   // Fill in the buffer with configuration data
   pt = buf;
   *pt++ = req.req_data_len; // bLength
   *pt++ = 0x01;        // bDescriptorType
   *pt++ = 0;           // Reserved in UFS2.0 and onward
   *pt++ = cfg->bBootEnable;
   *pt++ = cfg->bDescrAccessEn;
   *pt++ = cfg->bInitPowerMode;
   *pt++ = cfg->bHighPriorityLUN;
   *pt++ = cfg->bSecureRemovalType;
   *pt++ = cfg->bInitActiveICCLevel;
   *pt++ = (cfg->wPeriodicRTCUpdate >> 8) & 0xff;
   *pt++ = cfg->wPeriodicRTCUpdate & 0xff;
   if ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x80) >> 7) {
      *pt++ = cfg->bHPBControl; 
   }
   else {
      *pt++ = 0; 
   }
   *pt++ = 0;           // Reserved fields
   *pt++ = 0;
   *pt++ = 0;
   *pt++ = 0;
   if ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8) {
      *pt++ = cfg->bWriteBoosterBufferPreserveUserSpaceEn; 
      *pt++ = cfg->bWriteBoosterBufferType; 
   }
   if (wb_31_compliant)
   {
      *pt++ = (cfg->dNumSharedWriteBoosterBufferAllocUnits >> 24) & 0xff; 
      *pt++ = (cfg->dNumSharedWriteBoosterBufferAllocUnits >> 16) & 0xff; 
      *pt++ = (cfg->dNumSharedWriteBoosterBufferAllocUnits >> 8) & 0xff; 
      *pt++ = (cfg->dNumSharedWriteBoosterBufferAllocUnits) & 0xff; 
   }

   for (i = 0; i < 8; i++) {
      *pt++ = cfg->unit[i].bLUEnable;
      *pt++ = cfg->unit[i].bBootLunID;
      *pt++ = cfg->unit[i].bLUWriteProtect;
      *pt++ = cfg->unit[i].bMemoryType;
      *pt++ = (cfg->unit[i].dNumAllocUnits >> 24) & 0xff;
      *pt++ = (cfg->unit[i].dNumAllocUnits >> 16) & 0xff;
      *pt++ = (cfg->unit[i].dNumAllocUnits >> 8) & 0xff;
      *pt++ = (cfg->unit[i].dNumAllocUnits) & 0xff;
      *pt++ = cfg->unit[i].bDataReliability;
      *pt++ = cfg->unit[i].bLogicalBlockSize;
      *pt++ = cfg->unit[i].bProvisioningType;
      *pt++ = (cfg->unit[i].wContextCapabilities >> 8) & 0xff;
      *pt++ = cfg->unit[i].wContextCapabilities;
      *pt++ = 0;        // Reserved fields
      *pt++ = 0;
      *pt++ = 0;

      if ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x80) >> 7) {
         *pt++ = (cfg->unit[i].wLUMaxActiveHPBRegions >> 8) & 0xff; 
         *pt++ = cfg->unit[i].wLUMaxActiveHPBRegions & 0xff;
         *pt++ = (cfg->unit[i].wHPBPinnedRegionStartIdx >> 8) & 0xff; 
         *pt++ = cfg->unit[i].wHPBPinnedRegionStartIdx & 0xff;
         *pt++ = (cfg->unit[i].wNumHPBPinnedRegions >> 8) & 0xff; 
         *pt++ = cfg->unit[i].wNumHPBPinnedRegions & 0xff; 
      }

      if ((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x100) >> 8) {
         if (((hba->desc_dev.dExtendedUFSFeaturesSupport & 0x80) >> 7) == 0) {
            *pt++ = 0; 
            *pt++ = 0; 
            *pt++ = 0; 
            *pt++ = 0; 
            *pt++ = 0; 
            *pt++ = 0;
         }

         *pt++ = (cfg->unit[i].dLUNumWriteBoosterBufferAllocUnits >> 24) & 0xff; 
         *pt++ = (cfg->unit[i].dLUNumWriteBoosterBufferAllocUnits >> 16) & 0xff;
         *pt++ = (cfg->unit[i].dLUNumWriteBoosterBufferAllocUnits >> 8) & 0xff;
         *pt++ = (cfg->unit[i].dLUNumWriteBoosterBufferAllocUnits) & 0xff;
      }
   }

   rc = ufs_write_dev_descriptor (&req);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0270);
      return rc;
   }

   if (cfg->bConfigDescrLock) {
      rc = ufs_set_bConfigDescrLock (hufs, cfg->bConfigDescrLock);
      if (rc != EOK) {
         ufs_error_log(hba, 0x0271);
         return rc;
      }
   }

   /* Set init_stage to 0, so that any reinit
      happens with the new config information */
   hba->init_stage = 0; 

   return rc;
}

void ufs_fill_in_device_info (struct ufs_handle *hufs, 
                              struct ufs_info_type *info)
{
   ufs_host_t *hba = hufs->phc;
   uint8_t lun;
   int i;

   lun = hufs->lun;

   info->bBootLunEn = hba->attr.bBootLunEn;
   if (lun > 7 && lun == UFS_WLUN_BOOT && hba->desc_dev.bBootEnable) {
      if (info->bBootLunEn == 1 || info->bBootLunEn == 2) {
         for (i = 0; i < 8; i++) {
            if (hba->desc_cfg.unit_cfg[i].bBootLunID == info->bBootLunEn) {
               lun = i;
            }
         }
      }
   }

   if (hba->init_stage == 2) {
      info->fInitialized = 1; 
   } else {
      info->fInitialized = 0; 
   }

   info->bLUN = lun;
   info->bDeviceEmbedded                   = (hba->desc_dev.bDeviceSubClass >> 1) & 0x1; 
   info->bDeviceBootable                   = hba->desc_dev.bDeviceSubClass & 0x1;
   info->bNumberLu                         = hba->desc_dev.bNumberLU;
   info->wManufacturerID                   = hba->desc_dev.wManufacturerID;
   info->bBootEnable                       = hba->desc_dev.bBootEnable;
   info->qTotalRawDeviceCapacity           = hba->desc_geo.qTotalRawDeviceCapacity;
   info->bMinAddrBlockSize                 = hba->desc_geo.bMinAddrBlockSize;
   info->dSegmentSize                      = hba->desc_geo.dSegmentSize; 
   info->bAllocationUnitSize               = hba->desc_geo.bAllocationUnitSize;
   info->bRPMB_ReadWriteSize               = hba->desc_geo.bRPMB_ReadWriteSize;
   info->wSupportedMemoryTypes             = hba->desc_geo.wSupportedMemoryTypes;
   info->dEnhanced1MaxNAllocU              = hba->desc_geo.dEnhanced1MaxNAllocU;
   info->wEnhanced1CapAdjFac               = hba->desc_geo.wEnhanced1CapAdjFac;
   info->dEnhanced2MaxNAllocU              = hba->desc_geo.dEnhanced2MaxNAllocU;
   info->wEnhanced2CapAdjFac               = hba->desc_geo.wEnhanced2CapAdjFac;
   info->dEnhanced3MaxNAllocU              = hba->desc_geo.dEnhanced3MaxNAllocU;
   info->wEnhanced3CapAdjFac               = hba->desc_geo.wEnhanced3CapAdjFac;
   info->dEnhanced4MaxNAllocU              = hba->desc_geo.dEnhanced4MaxNAllocU;
   info->wEnhanced4CapAdjFac               = hba->desc_geo.wEnhanced4CapAdjFac;
   info->dWriteBoosterBufferMaxNAllocUnits = hba->desc_geo.dWriteBoosterBufferMaxNAllocUnits; 
   info->bDeviceMaxWriteBoosterLUs         = hba->desc_geo.bDeviceMaxWriteBoosterLUs; 
   info->bWriteBoosterBufferCapAdjFac      = hba->desc_geo.bWriteBoosterBufferCapAdjFac; 
   info->bSupportedWriteBoosterBufferTypes = hba->desc_geo.bSupportedWriteBoosterBufferTypes; 
   info->iManufacturerName                 = hba->desc_dev.iManufacturerName;
   info->iProductName                      = hba->desc_dev.iProductName;
   info->iSerialNumber                     = hba->desc_dev.iSerialNumber;
   info->iOemID                            = hba->desc_dev.iOemID;
   info->dExtendedUFSFeaturesSupport       = hba->desc_dev.dExtendedUFSFeaturesSupport; 
   info->bConfigDescrLock                  = hba->attr.bConfigDescrLock;
   info->qHostBaseAddr                     = (uint64_t)hba->ufs_hci_addr;
   info->wSpecVersion                      = hba->desc_dev.wSpecVersion; 
   info->bSupportedWriteBoosterBufferUserSpaceReductionTypes = hba->desc_geo.bSupportedWriteBoosterBufferUserSpaceReductionTypes;
   info->bHPBNumberLU                      = hba->desc_geo.bHPBNumberLU;
   info->wDeviceMaxActiveHPBRegions        = hba->desc_geo.wDeviceMaxActiveHPBRegions; 

   // Populate the LUN enabled bit field
   info->dLunEnabled = 0;
   for (i = 0; i < 8; i++) {
      info->dLunEnabled |= (hba->desc_cfg.unit_cfg[i].bLUEnable ? 1 : 0) << i;
   }

   // Copy the inquiry field
   for (i = 0; i < sizeof(hba->inquiry_vid); i++) {
      info->inquiry_str[i] = hba->inquiry_vid[i];
   }
   info->inquiry_str[i] = 0;

   if (lun <= 7) {
      // LUN specific area
      info->dNumAllocUnits     = hba->desc_cfg.unit_cfg[lun].dNumAllocUnits;
      info->bLogicalBlockSize  = hba->desc_cfg.unit_cfg[lun].bLogicalBlockSize;
      info->bProvisioningType  = hba->desc_cfg.unit_cfg[lun].bProvisioningType;
      info->bLUWriteProtect    = hba->desc_cfg.unit_cfg[lun].bLUWriteProtect;
      info->bBootLunID         = hba->desc_cfg.unit_cfg[lun].bBootLunID;
      info->bMemoryType        = hba->desc_cfg.unit_cfg[lun].bMemoryType;
      info->qLogicalBlockCount = hba->desc_unit[lun].qLogicalBlockCount;
   }

   if (lun == UFS_WLUN_RPMB) {
      info->bLogicalBlockSize  = hba->desc_rpmb.bLogicalBlockSize;
      info->qLogicalBlockCount = hba->desc_rpmb.qLogicalBlockCount;
      if (hba->desc_dev.wSpecVersion >= 0x300) {
         // RPMB Region 0 size calculation from 13.2.3 of the UFS specification
         info->RPMBPartitionSizeInBytes = ((hba->desc_rpmb.qLogicalBlockCount / 512) - hba->desc_rpmb.bRPMBRegion1Size - hba->desc_rpmb.bRPMBRegion2Size - hba->desc_rpmb.bRPMBRegion3Size) * 128 * 1024;
      } 
      else {
         info->RPMBPartitionSizeInBytes = hba->desc_rpmb.qLogicalBlockCount * 256;
      }
   }
}

void ufs_fill_in_error_stats (struct ufs_handle *hufs, struct ufs_error_stats *err_info)
{
   ufs_host_t *hba = hufs->phc; 

   err_info->total_error_cnt = hba->failure_cnt; 
   osal_memcpy (err_info->pa_ind_err_cnt, hba->pa_ind_err_cnt, sizeof(hba->pa_ind_err_cnt)); 
   err_info->pa_total_err_cnt = hba->pa_total_err_cnt; 
   osal_memcpy(err_info->dl_ind_err_cnt, hba->dl_ind_err_cnt, sizeof(hba->dl_ind_err_cnt)); 
   err_info->dl_total_err_cnt = hba->dl_total_err_cnt; 
   err_info->dme_total_err_cnt = hba->dme_total_err_cnt; 
}

void ufs_fill_in_operation_mode_caps (struct ufs_handle *hufs, void *caps)
{
   ufs_bsp_operational_mode_info (hufs->phc->curr_speed_config.gear, caps);  
}

void ufs_fill_in_current_operating_mode (struct ufs_handle *hufs, struct ufs_current_operational_mode_info *curr_op_mode)
{
   ufs_host_t *hba = hufs->phc;

   curr_op_mode->speed_level = hba->curr_speed_config.gear; 
   curr_op_mode->volt_corner = hba->curr_volt_corner; 

   // For autoH8, retrieve the link state
   if (hba->auto_h8_enabled == 1) {
      curr_op_mode->link_state = (ufs_utp_check_link_h8 (hba) == TRUE) ? 0 : 1; 

   }
   else {
      curr_op_mode->link_state = hba->link_state; 
   }
}

// Vendor specific command, use to control pre-programming mode
int32_t ufs_vend_pprog_ctrl (struct ufs_handle *hufs, uint32_t code)
{
   ufs_host_t *hba;
   ufs_attr_req_t req;
   int32_t rc = EOK;
   uint8_t osf[8];     
   uint8_t buffer[512];

   hba = hufs->phc;
   req.phc = hufs->phc;
   req.req_data_len = 0x200;
   req.req_data_buf = (uint8_t *)buffer;
   req.resp_data_len = 0x200;
   req.resp_data_buf = (uint8_t *)buffer;
   req.idn = 0;
   req.idx = 0;

   // Program the buffer
   osal_memset (buffer, 0x00, sizeof (buffer));
   buffer[0] = 0x0b;
   buffer[4] = (code >> 24) & 0xff;
   buffer[5] = (code >> 16) & 0xff;
   buffer[6] = (code >> 8) & 0xff;
   buffer[7] = (code) & 0xff;
   buffer[8] = 0x01;
   buffer[9] = 0x01;

   rc = ufs_generic_write_query (&req, osf, 0xc2);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0287);
      return rc;
   }

   return rc;
}

// Scale up to higher SVS modes
int32_t ufs_do_clock_scale_up (struct ufs_handle *hufs, uint8_t volt_corner, uint8_t gear)
{
   int32_t rc = EOK; 
   ufs_host_t *hba = hufs->phc;
  
   rc = ufs_utp_clock_scale_up (hba, volt_corner, gear); 
   if (rc != EOK) {
      ufs_error_log (hba, 0x02b1);
      return rc; 
   }
   
   return EOK;
}

// Scale down to lower SVS modes
int32_t ufs_do_clock_scale_down (struct ufs_handle *hufs, uint8_t volt_corner, uint8_t gear)
{
   int32_t rc = EOK; 
   ufs_host_t *hba = hufs->phc;

   rc = ufs_utp_clock_scale_down (hba, volt_corner, gear); 
   if (rc != EOK) {
      ufs_error_log (hba, 0x02b2);
      return rc; 
   }    
   
   return EOK;
}

// Configure UFS gear and SVS mode
int32 ufs_do_operational_mode (struct ufs_handle *hufs, uint8_t volt_corner, uint8_t gear)
{
   int32 rc = EOK;
   ufs_host_t *hba = hufs->phc;
   ufs_bsp_err_type err; 
   ufs_bsp_speed_config cfg; 
      
   // Check to see if the volt_corner and gear combination is valid
   err = ufs_bsp_check_valid_operational_mode (volt_corner, gear); 
   if (err == UFS_BSP_ERR_FEATURE_UNSUPPORTED) {
      ufs_error_log (hba, 0x02b9); 
      return -ENOSYS;
   }
   else if (err != UFS_BSP_NO_ERROR) {  
      ufs_error_log (hba, 0x02b6);
      return -EINVAL;  
   }
  
   // Compare volt_corner with curr_volt_corner to decide if we are clock scaling up or down, or
   // just changing the gear
   if (hba->curr_volt_corner < volt_corner)
   {
      rc = ufs_do_clock_scale_up (hufs, volt_corner, gear);
   }
   else if (hba->curr_volt_corner > volt_corner)
   {
      rc = ufs_do_clock_scale_down (hufs, volt_corner, gear); 
   }  
   else
   {
      osal_memcpy (&cfg, &hba->curr_speed_config, sizeof(ufs_bsp_speed_config)); 
      cfg.gear = gear; 
      rc = ufs_utp_gear_sw (hba, &cfg);  
   }
   
   return rc;
}

// Put link in hibernate and gate the UFS clocks 
int32_t ufs_do_clock_gate (struct ufs_handle *hufs)
{
   int32_t rc = EOK; 
   ufs_host_t *hba = hufs->phc; 

   // Enter hibernate
   rc = ufs_utp_link_h8 (hba, 1); 
   if (rc != EOK) {
      ufs_error_log (hba, 0x02b3);
      return rc; 
   }

   ufs_bsp_clk_set (hba->ufs_core_id, UFS_CLOCK_MODE_OFF);

   return EOK; 
}

// Ungate the UFS clocks and take the link out of hibernate 
int32_t ufs_do_clock_ungate (struct ufs_handle *hufs)
{
   int32_t rc = EOK; 
   ufs_host_t *hba = hufs->phc; 

   ufs_bsp_clk_set (hba->ufs_core_id, hba->curr_volt_corner); 

   // Exit hibernate
   rc = ufs_utp_link_h8 (hba, 0); 
   if (rc != EOK) {
      ufs_error_log (hba, 0x02b4);
      return rc; 
   }

   return EOK; 
}

// Entering/exiting manual hibernate 
int32_t ufs_link_h8 (struct ufs_handle *hufs, uint8_t enter)
{
   int32_t rc = EOK; 
   ufs_host_t *hba = hufs->phc; 

   rc = ufs_utp_link_h8 (hba, enter);
   if (rc != EOK) {
      ufs_error_log (hba, 0x02b8);
      return rc; 
   }

   return EOK; 
}

// Configure timer for auto hibernate 
void ufs_link_autoH8 (struct ufs_handle *hufs, uint16_t time_in_ms)
{
   ufs_host_t *hba = hufs->phc; 

   ufs_utp_link_autoh8 (hba, time_in_ms);

   // Indicate auto hibernate is enabled
   hba->auto_h8_enabled = 1;
}

int32_t ufs_do_finish_config (struct ufs_handle *hufs, ufs_config_mode mode)
{
   char log_buf[32] = {0};
   int32_t rc = EOK; 
   ufs_host_t *hba = hufs->phc; 

   if (mode == UFS_PERF_CONFIG) {
      // For performance configuration, first check if we need to change to a different gear. 
      if (hba->cfg_entries.perf_speed_params.gear != hba->curr_speed_config.gear) {
         rc = ufs_utp_gear_sw (hba, &hba->cfg_entries.perf_speed_params);
         if (rc != EOK) {
            ufs_error_log (hba, 0x02c8); 
            return rc; 
         }
         else {
            snprintf(log_buf, 32, "UFS changed to gear %d", hba->cfg_entries.perf_speed_params.gear);  
            ufs_bsp_log(log_buf, UFS_LOG_INFO); 
            hba->has_gear_switched = 1;
         }
      }
   }

   return EOK;
}

#if !defined (FEATURE_NO_SHARED_ICE)

/* Set Shared Ice algorithm */
int32_t ufs_do_set_shared_ice_algo(struct ufs_handle *hufs, void *algo_info)
{
  int32_t rc = EOK; 
  ufs_host_t *hba = hufs->phc; 

  // Go ahead only if shared ice is supported.
  if (ufs_utp_is_shared_ice_supported(hba) == FALSE)
  {
    ufs_error_log(hba, 0x02c9);
	return -EPERM;
  }

  /* Reset the controller before sharedice algorithm change.
     Reset is needed mainly when change is made from any dynamic algorithm to static.
     EG: floor -> static, Instantaneous -> static.
  */
  rc = ufs_reset_host_controller(hufs);
  if (rc != EOK)
  {
    ufs_error_log(hba, 0x02ca);
	return rc;
  }
  
  /* Crypto needs to be enabled before SharedIce ALgorith is set */
  osal_memset(&hba->ice_params, 0, sizeof(hba->ice_params));
  rc = ufs_utp_enable_crypto_engine(hba);
  if (rc != EOK)
  {
    ufs_error_log(hba, 0x2cb);
	return rc;
  }
   
  rc = ufs_utp_set_shared_ice_algo(hba, algo_info);
  if (rc != EOK)
  {
    ufs_error_log(hba, 0x02cc);
	return rc;
  }
  
  return rc;
}

/* Get Shared Ice algorithm info */
int32_t ufs_do_get_shared_ice_algo(struct ufs_handle *hufs, void *algo_info)
{
  int32_t rc = EOK; 
  ufs_host_t *hba = hufs->phc; 

  rc = ufs_utp_get_shared_ice_algo(hba, algo_info);
  
  if (rc != EOK)
  {
    ufs_error_log(hba, 0x02ce);
  }
  return rc;
}

#endif

#ifdef FEATURE_XBOOT
// Get the device descriptor　(raw value)
int32_t ufs_get_descriptor_device_raw(struct ufs_handle *hufs,
                                      char *buf,
                                      uint32_t size)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;
   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   req.resp_data_len = size;
   req.resp_data_buf = (uint8_t *)buf;
   req.idn = UFS_DESC_IDN_DEVICE;

   rc = ufs_read_dev_descriptor (&req);
   return rc;
}

// Get one of the unit dscriptors from the UFS device 　(raw value)
int32_t ufs_get_descriptor_unit_raw(struct ufs_handle *hufs,
                                    uint32_t lun,
                                    char *buf,
                                    uint32_t size)
{
   ufs_attr_req_t req;
   int32_t rc = EOK;
   osal_memset (&req, 0, sizeof (ufs_attr_req_t));

   req.phc = hufs->phc;
   req.req_data_len = 0;
   req.req_data_buf = NULL;
   req.resp_data_len = size;
   req.resp_data_buf = (uint8_t *)buf;
   req.idn = UFS_DESC_IDN_UNIT;
   req.idx = lun;

   rc = ufs_read_dev_descriptor (&req);
   return rc;
}
#endif /* FEATURE_XBOOT */
