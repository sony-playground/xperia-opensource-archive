/**********************************************************************
 *
 *    UFS UTP layer - 
 *    Communicate with the UFS HCI register and generate the
 *    command/data packet structures 
 *    This layer is for interfacing with the hardware registers 
 *    exposed by the UFS host controller
 *
 * Copyright (c) 2012-2022 Qualcomm Technologies, Inc.  All Rights Reserved.
 * Qualcomm Technologies Proprietary and Confidential.
 *
 **********************************************************************/

/*======================================================================

                        EDIT HISTORY FOR MODULE

  $Header: //components/rel/core.boot/6.0/QcomPkg/Library/UfsCommonLib/ufs_utp_core.c#14 $
  $DateTime: 2022/03/15 13:02:23 $ $Author: pwbldsvc $

when         who     what, where, why
----------   ---     --------------------------------------------------- 
2022-02-10   cm      Add max freq support
2021-11-25   vm      Override DT Gear Configuration with max supported gear 
2021-11-25   vm      Run HSG3 with HSG4 Phy Settings
2021-10-27   jt      Updates for partial init 
2021-10-19   jt      Invalidate UTRD transfer buffer on completion
2021-08-13   jt      Add ufs_utp_partial_init 
2021-06-26   sa      Added Init for Gear5.
2021-04-28   jt      Add field for crypto engine enable
2021-04-28   jt      Add ICE support 
2021-01-28   jt      Ensure there is a vote for clocks
2020-10-05   jt      Add function to tune Unipro parameters 
2020-06-29   jt      Update logging function 
2020-04-13   jt      Rate B can be used for HSG4 now  
2020-03-31   jt      Add power management functions
2019-11-26   jt      Use Rate A for HSG4
2019-10-22   jt      Remove voltage switching 
2019-09-12   jt      Add additional configuration of PA_PWRModeUserData 
2019-05-15   jt      Remove controller specific PHY init 
2019-03-27   jt      Fix Resp UPIU, PRDT offset alignment  
2019-02-13   jt      Add UFS 3.0 support  
2018-09-24   jt      PHY initialization restructure v2 
2018-09-12   jt      Fix caching for UTP command descriptor
2018-09-12   jt      Don't error if link is already in intended state  
2018-09-05   jt      Restructure PHY initialization sequence  
2018-08-16   jt      Add hibernate function  
2018-07-30   jt      Add controller specific PHY init capability
2018-04-11   jt      PHY adjustment to allow HSG4, if supported  
2017-07-31   jt      Add ability to dump UFS debug registers 
2017-06-06   jt      Add PHY sequence for non-HSG4 mode  
2017-05-22   jt      Return error when submitting UTRD if transfer pending  
2017-03-20   jt      Add configuration of PA_PWRModeUserData 
2017-03-14   jt      Correct UFS HW version check  
2017-02-21   jt      Turn on clocks before device reset  
2017-01-25   jt      Add UFS device reset  
2017-01-17   jt      Check available lanes to determine proper PHY sequence  
2016-11-30   jt      Extend UTRD timeout to 30s for unmap  
2016-11-01   jt      Add reset function  
2016-08-22   jt      Update for 8998v2 
2016-08-02   jt      Allow for UFS lane/gear config 
2016-02-08   jt      Correct UTRD timeout 
2016-01-13   rh      Use PA_ConnectedRxDataLanes to detect number of RX lanes
2015-12-16   rh      Increase the PA_SaveConfigTime using vendor spec function
2015-07-08   rh      Use IS.UTRCS to detect completion of UTRD
2015-06-15   rh      Disable the PHY from decoding the LCC sequence
2014-10-30   rh      Adding multiple re-init on PHY for link startup failure
2014-09-17   rh      Merge with UEFI driver changes
2014-07-16   rh      Adding cache operation
2014-01-20   rh      Inject a DIF-P to reset the chip prior to link startup
2013-12-10   rh      Cleanup of RUMI related bring-up code
2013-10-22   rh      Overcome memcpy's limitation on 32bit alignment
2013-10-22   rh      Better ability to capture failure information
2013-09-30   rh      Adding the UIC debug dump
2013-09-04   rh      Integrate the gear switch code
2013-08-27   rh      PRDT base address is not incrementing correctly
2013-08-12   rh      DWARD length conversion for UTRD is not correct
2012-12-18   rh      Initial creation
=======================================================================*/

#include "HALhwio.h"

#include "ufs_osal.h"
#include "ufs_core.h"
#include "ufs_utp_core.h"
#include "ufs_errno.h"
#include "ufs_bsp.h"
#include "ufs_memory.h"

#define HCI_ENABLE_TIMEOUT             100000
#define HCI_UIC_TIMEOUT                100000
#define HCI_UTMRD_POLL_TIMEOUT         100000
#define HCI_LINK_STARTUP_TIMEOUT       100000
#define UFS_TX_FSM_STATE_TIMEOUT       100000
#define UFS_HCI_UPMS_POLL_TIMEOUT      100000
#define UFS_HCI_UHES_POLL_TIMEOUT      100000

// Size of the buffer determine the setting for UFS_MAX_BLOCK_TRANSFERS
#define REQUEST_LIST_BUFFER_SIZE       (4096 + 1024)  // Alignment requirement for 1k padding
#define UTRD_ARRAY_SIZE                1024
#define PRDT_DBC_MAX                   0x40000
#define MAX_PRDT_ENTRIES               256            // Buffer is 4096, 16 bytes per PRDT entries 
#define PRDT_SIZE                      16

#define UFS_UTRD_DOORBELL_CH           (0x01 << 0)
#define UFS_IS_MASK_ALL_ERROR          (BMSK_UE | BMSK_DFES | BMSK_UTPES | BMSK_HCFES | BMSK_SBFES | BMSK_CEFES)
#define UFS_UECDL_FATAL_MSK            ((1 << 5) | (1 << 6) | (1 << 13))
#define UFS_UE_ERROR_FLAG              (1 << 31)
#define UFS_MAX_ERR_CNT                5

#define GET_PHY_ADDR_L(x)  ((uint32_t)((uint64_t)x))
#define GET_PHY_ADDR_H(x)  ((uint32_t)(((uint64_t)x) >> 32))
#define GET_PHY_ADDR(x)    ((uint64_t)x)

#ifdef UFS_USES_64_BIT
#define CONV_TO_PTR(x)     (x)
#else
#define CONV_TO_PTR(x)     ((uint32_t)x)
#endif

//Select the endian adjustment macro if needed
//#define ENDIAN_ADJ_32(x)   (((x & 0xff) << 24) | ((x & 0xff000000) >> 24) | ((x & 0xff00) << 8) | ((x & 0xff0000) >> 8))
#define ENDIAN_ADJ_32(x)   (x)


//#define UFS_DEFAULT_HS_SERIES    0x01        // SERIES-A
#define UFS_DEFAULT_HS_SERIES    0x02        // SERIES-B
#define UFS_DEFAULT_LANE         0x02        // Number of Lanes used 

#define UFS_USES_HS_GEAR         1

#ifdef UFS_USES_HS_GEAR

#define UFS_DEFAULT_GEAR         0x04        // GEAR-4
#define UFS_DEFAULT_PWR_MODE     0x11        // FAST mode
#define UFS_PHY_TERMINATION      0x01

#else

#define UFS_DEFAULT_GEAR         0x04        // GEAR-4
#define UFS_DEFAULT_PWR_MODE     0x22        // SLOW mode
#define UFS_PHY_TERMINATION      0x00

#endif

#define UFS_PA_REFRESH           0x0
#define UFS_PA_INITIAL           0x1
#define UFS_PA_NO_ADAPT          0x3

#ifdef UFS_USES_UIC_DEBUG_DUMP
#define UFS_UIC_DEBUG_DUMP_SIZE     2048
struct ufs_uic_dump_item {
   uint16_t    idx;           // Attribute ID
   uint16_t    gen;           // GenSelectorIndex ID
   uint32_t    val;           // Attribute Value
};

struct ufs_uic_dump_item ufs_uic_dump_buf[UFS_UIC_DEBUG_DUMP_SIZE];
static uint32_t ufs_uic_debug_idx;
#endif
static uint8_t hsg4_turbo_clk_freq_seq = 0;
#define UFS_REG_DUMP_STR_LEN   128

// Create two buffers -
// Task management request list buffer
// The Transfer request is 8 x 32 = 256 bytes total, follow
// by undetermined number of command descriptors
// Memory will be allocated this way
//  -----------------------
//  | UTRD * n            |      (UTP Transfer Reqeust Descriptor)
//  -----------------------
//  | UCD (3 parts)       |      (UTP Command Descriptor )
//  | - Transfer Request  |
//  | - Transfer Response |
//  | - PRD table         |
//  -----------------------
//  For this implementation, n = 1, max is 32
// NOTE: These buffer need to be 1k aligned
//

static int32_t ufs_preinit_mphy_configure (ufs_host_t *hba);

// Internal memcpy support function, perforam non-aligned copy is needed
void ufs_utp_memcpy (void *out, void *in, uint32_t size)
{
   uint32_t i;
   uint8_t *out_b = out;
   uint8_t *in_b = in;
   for (i = 0; i < size; i++) {
      *out_b++ = *in_b++;
   }
}

// Parse PA/Dl/DME errors. -EIO returned for fatal errors
static int32_t ufs_utp_parse_errors (ufs_host_t *hba)
{
   uint32_t i = 0; 
   hba->dbg_is_val = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS);

   // Read and store all error status registers
   hba->dbg_uecpa_val = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UECPA);
   hba->dbg_uecdl_val = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UECDL);
   hba->dbg_uecn_val = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UECN);
   hba->dbg_uect_val = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UECT);
   hba->dbg_uecdme_val = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UECDME);
   hba->dbg_pa_err_val = HWIO_REG_IN (hba->ufs_hci_addr, VENSPEC_REG_PA_ERR_CODE);

   // Clear the error bits
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_IS, UFS_IS_MASK_ALL_ERROR);

   // Capture PA error by type and count 
   if (hba->dbg_uecpa_val & UFS_UE_ERROR_FLAG) {
      for (i = 0; i < 5; i++) {
         if (hba->dbg_uecpa_val & (1 << i)) {
            hba->pa_ind_err_cnt[i]++;
            hba->pa_total_err_cnt++; 
         }
      }
   }

   // Capture DL error by type and count
   if (hba->dbg_uecdl_val & UFS_UE_ERROR_FLAG) {
      for (i = 0; i < 16; i++) {
         if (hba->dbg_uecdl_val & (1 << i)) {
            hba->dl_ind_err_cnt[i]++;
            hba->dl_total_err_cnt++; 
         }
      }
   }

   // Capture DME error count
   if (hba->dbg_uecdme_val & UFS_UE_ERROR_FLAG) {
      hba->dme_total_err_cnt++;
   }

   // Return on error that should be process at higher layer
   if (((hba->dbg_uecdl_val & UFS_UE_ERROR_FLAG) && (hba->dbg_uecdl_val & UFS_UECDL_FATAL_MSK)) ||
       (hba->dbg_uecn_val & UFS_UE_ERROR_FLAG) || 
       (hba->dbg_uect_val & UFS_UE_ERROR_FLAG) ||
       (hba->dbg_uecdme_val & UFS_UE_ERROR_FLAG)) {
      ufs_dump_regs(hba);
      return -EIO;
   }

   return EOK; 
}

// Use for UIC get/set command, 
// MIBattrIndex[31:16] = AttributeID
// MIBattrIndex[15:0] = GenSelectorIndex
// MIBval = Set the attribute value to
// Sent a UIC command and wait for completition flag 
int32_t ufs_utp_uic_getset (ufs_host_t *hba, uint32_t uic, uint32_t MIBattrIndex, 
                            uint32_t MIBvalSet, uint32_t *MIBvalGet)
{
   uint32_t tout;
   uint32_t re;
   volatile uint32_t pendingTasks = 0;
   int errcnt = UFS_MAX_ERR_CNT;
   
   hba->last_uic_cmd = uic;

   // Check to make sure hardware to ready to accept a UIC command
   tout = HCI_UIC_TIMEOUT;
   while (--tout) {
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_HCS) & BMSK_UCRDY) {
         break;
      }
      ufs_bsp_busy_wait (1);
   }
   if (tout == 0) {
      ufs_error_log(hba, 0x0013);
      return -EIO;
   }

   /* HPG - General SW requirement #4
       * Software should wait for completion of all outstanding TRs and TRMs with additional wait of 1 ms 
       * before issuing DME_PEER_GET and DME_PEER_SET UIC commands. */
   if ((uic == UICCMDR_DME_PEER_GET) || (uic == UICCMDR_DME_PEER_SET)) {
      do { 
         pendingTasks = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UTRLDBR) || 
            HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UTMRLDBR);
      } while (pendingTasks);
      ufs_bsp_busy_wait (1000);
   }
   
   // Clear the UCCS bit in IS register
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_IS, BMSK_UCCS);

   // Set UIC COMMAND Argument field
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UCMDARG1, MIBattrIndex);
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UCMDARG2, 0x0);
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UCMDARG3, MIBvalSet);

   // Send the UICC command 
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UICCMDR, uic);

   // Poll the IS register for UCCS bit
   tout = HCI_UIC_TIMEOUT;

   while (--tout) {
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS) & BMSK_UCCS) {
         break;
      }
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS) & UFS_IS_MASK_ALL_ERROR) {
         if (ufs_utp_parse_errors(hba) != EOK) {
            return -EIO; 
         }

         if (errcnt-- <= 0) {
            return -EIO;
         }
         ufs_bsp_busy_wait (1);
         continue;
      }
      ufs_bsp_busy_wait (1);
   }
   if (tout == 0) {
      ufs_error_log(hba, 0x0010);
      return -EIO;
   }

   // Check the result code
   re = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UCMDARG2);
   if ((re & 0xff) != 0x00) {
      ufs_error_log(hba, 0x0011);
      return -EIO;
   }

   if (MIBvalGet != NULL) {
      *MIBvalGet = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UCMDARG3);
   }

   return EOK;
}

int32_t ufs_utp_get_host_caps (ufs_host_t *hba)
{
   int32_t rc = EOK;
   uint32_t val;

   /* PWM Gear */
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_MaxRxPWMGear, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0070);
      return rc;
   }
   hba->ufs_mphy_caps.max_pwm_gear = (uint8_t)val;

   /* HS Gear */
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_MaxRxHSGear, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0075);
      return rc;
   }
   hba->ufs_mphy_caps.max_hs_gear = (uint8_t)val;

   /* HS Rate */
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_HSSeries, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0077);
      return rc;
   }
   hba->ufs_mphy_caps.last_hs_rate = (uint8_t)val;  

   /* Availalbe Data Lanes */
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_AvailTxDataLanes, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0078);
      return rc;
   }
   hba->ufs_mphy_caps.tx_avail_lanes = (uint8_t)val;

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_AvailRxDataLanes, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x007a);
      return rc;
   }
   hba->ufs_mphy_caps.rx_avail_lanes = (uint8_t)val;

   /* Version */
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_LocalVerInfo, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0068);
      return rc;
   }
   hba->ufs_mphy_caps.unipro_ver_local = (uint16_t)val;

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_RemoteVerInfo, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0069);
      return rc;
   }
   hba->ufs_mphy_caps.unipro_ver_remote = (uint16_t)val;

   return EOK; 
}

int32_t ufs_utp_tune_unipro_params (ufs_host_t *hba)
{
   int32_t rc = EOK;
   uint32_t granularity, peer_granularity;
   uint32_t pa_tactivate, peer_pa_tactivate;
   uint32_t pa_tactivate_us, peer_pa_tactivate_us;
   uint32_t new_peer_pa_tactivate;
   uint8_t gran_to_us_table[] = {1, 4, 8, 16, 32, 100}; // From Unipro spec table 28
   uint32_t tuned_pa_hibern8time = 0;

   // PA_TACTIVATE = Time to wait before activating a burst in order to wake-up peer M-RX 
   // host PA_TACTIVATE = device PA_TACTIVATE + 1
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_Granularity, 0), 
                            0, &granularity); 
   if (rc != EOK) {
      ufs_error_log (hba, 0x004d); 
      return rc; 
   }
   
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_PEER_GET, UIC_ARG0_MIBattr(PA_Granularity, 0), 
                            0, &peer_granularity);

   if (rc != EOK) {
      ufs_error_log (hba, 0x004e); 
      return rc; 
   }

   if ((granularity < PA_Granularity_MinVal) || (granularity > PA_Granularity_MaxVal)) {
      ufs_error_log (hba, 0x004f); 
      return -EINVAL;
   }

   if ((peer_granularity < PA_Granularity_MinVal) || (peer_granularity > PA_Granularity_MaxVal)) {
      ufs_error_log (hba, 0x0050); 
      return -EINVAL;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_TActivate, 0), 
                            0, &pa_tactivate); 
   if (rc != EOK) {
      ufs_error_log (hba, 0x0051); 
      return rc; 
   }
   
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_PEER_GET, UIC_ARG0_MIBattr(PA_TActivate, 0), 
                            0, &peer_pa_tactivate);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0052); 
      return rc; 
   }

   pa_tactivate_us = pa_tactivate * gran_to_us_table[granularity - 1];
   peer_pa_tactivate_us = peer_pa_tactivate * gran_to_us_table[peer_granularity - 1];

   if (pa_tactivate_us > peer_pa_tactivate_us) {
      new_peer_pa_tactivate = pa_tactivate_us / gran_to_us_table[peer_granularity - 1];
      new_peer_pa_tactivate++;

      rc = ufs_utp_uic_getset (hba, UICCMDR_DME_PEER_SET, UIC_ARG0_MIBattr(PA_TActivate, 0), 
                               new_peer_pa_tactivate, NULL);
      if (rc != EOK) {
         ufs_error_log (hba, 0x0053); 
         return rc; 
      }
   }

   // PA_Hibern8Time = Minimum time to wait in H8before allowing a M-TX to exit H8
   // SS requires host to force PA_Hibern8Time = 300us (units in terms of granularity) 
   tuned_pa_hibern8time = 300 / gran_to_us_table[granularity - 1];
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_Hibern8Time, 0), 
                            tuned_pa_hibern8time, NULL);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0054); 
      return rc; 
   }

   return rc;
}

int32_t ufs_utp_gear_sw (ufs_host_t *hba, ufs_bsp_speed_config *config)
{
   int32_t rc = EOK;
   uint32_t hs_adapt_capability;
   uint32_t val;
   uint32_t tout;
   uint32_t lanes; 
   uint32_t phy_termination = UFS_PHY_TERMINATION, pwr_mode = UFS_DEFAULT_PWR_MODE;

   // If the gear we want to switch matches the current gear, we are done
   if (config->gear == hba->curr_speed_config.gear) {
      return EOK; 
   }

   // Clear the UPMS bit in IS register
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_IS, BMSK_UPMS);

   // If PWM mode enabled, adjust phy termination/pwr_mode values. 
   if (config->enable_hs == 0) {
      phy_termination = 0; 
      pwr_mode = 0x22;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_ConnectedRxDataLanes, 0), 
                            0, &lanes);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0042);
      return rc;
   }

   lanes = config->num_lanes < lanes ? config->num_lanes : lanes;


   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_ActiveTxDataLanes, 0), 
                            lanes, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0043);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_ActiveRxDataLanes, 0), 
                            lanes, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0044);
      return rc;
   }

   // Set the TX and RX gear in L1.5, Set the HOST PWM RX GEAR
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_RxGear, 0), config->gear, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0030);
      return rc;
   }

   // Set the HOST PWM TX GEAR 
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_TxGear, 0), config->gear, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0031);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_TxTermination, 0), phy_termination, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0045);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_RxTermination, 0), phy_termination, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0046);
      return rc;
   }

   // Set the HS Series
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_HSSeries, 0), config->rate, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0032);
      return rc;
   }

   // PA_PeerRxHsAdaptInitial should be set to the RX_HS_ADAPT_INITIAL_Capability value of the peer UFS device
   if (config->gear >= 4) {
      rc = ufs_utp_uic_getset(hba, UICCMDR_DME_PEER_GET, UIC_ARG0_MIBattr(RX_HS_ADAPT_INITIAL_Capability, GenSelectRx(0)), 0, &hs_adapt_capability); 
      if (rc != EOK) {
         ufs_error_log(hba, 0x0049); 
         return rc; 
      }

      rc = ufs_utp_uic_getset(hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_PeerRxHsAdaptInitial, 0), hs_adapt_capability, NULL); 
      if (rc != EOK) {
         ufs_error_log(hba, 0x004a); 
         return rc; 
      }

      rc = ufs_utp_uic_getset(hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_TxHsAdaptType, 0), UFS_PA_INITIAL, NULL); 
      if (rc != EOK) {
         ufs_error_log(hba, 0x004b); 
         return rc; 
      }
   }
   else
   {
      rc = ufs_utp_uic_getset(hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_TxHsAdaptType, 0), UFS_PA_NO_ADAPT, NULL);
      if (rc != EOK) {
         ufs_error_log(hba, 0x004c); 
         return rc; 
      }
   }

   // Set Device L2 Recovery disable
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_PWRModeUserData(0), 0), 0x1FFF, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0036);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_PWRModeUserData(1), 0), 0xFFFF, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0037);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_PWRModeUserData(2), 0), 0x7FFF, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0038);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_PWRModeUserData(3), 0), 0x1FFF, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x003c);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_PWRModeUserData(4), 0), 0xFFFF, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x003d);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_PWRModeUserData(5), 0), 0x7FFF, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x003e);
      return rc;
   }

   // Set the HOST PowerState
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_PWRMode, 0), pwr_mode, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0033);
      return rc;
   }

   // Wait until IS.UPMS is set to 1
   tout = UFS_HCI_UPMS_POLL_TIMEOUT;
   while (!(HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS) & BMSK_UPMS)) {
      // Check the value of the IS register for any failure
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS) & UFS_IS_MASK_ALL_ERROR) {
         rc = ufs_utp_parse_errors(hba); 
         if (rc != EOK) {
            return rc; 
         }
      }
      ufs_bsp_busy_wait (10);
      if (--tout == 0) {
         ufs_error_log(hba, 0x0034);
         return -EIO;
      }
   }

   // Set the IS.UPMS to clear it
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_IS, BMSK_UPMS);

   // Check the result of the power mode change request
   val = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_HCS);
   val = (val & 0x0700) >> 8;
   if (val != 0 && val != 1 && val != 2) {
      ufs_error_log(hba, 0x0035);
      return -EIO;
   }
   // Wait for 0.5ms
   ufs_bsp_busy_wait (500);

   // Update the current speed config
   memcpy (&hba->curr_speed_config, config, sizeof(ufs_bsp_speed_config));
           
   hba->link_state = 1;             
   return rc;
}

static int32_t ufs_utp_wait_no_pending_transfers (ufs_host_t *hba) 
{
   uint32 tout; 

   // Wait until HCS.UCRDY = 1
   tout = HCI_UIC_TIMEOUT;
   while (--tout) {
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_HCS) & BMSK_UCRDY) {
        break;
      }
      ufs_bsp_busy_wait (1);
   }
   if (tout == 0) {
      ufs_error_log (hba, 0x0012);
      return -ETIME; 
   }

   // Wait until UTMRLDBR = 0
   tout = HCI_UTMRD_POLL_TIMEOUT;
   while (--tout) {
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UTMRLDBR) == 0) {
         break; 
      }
      ufs_bsp_busy_wait (1);
   }
   if (tout == 0) {
      ufs_error_log (hba, 0x0014);
      return -ETIME; 
   }

   // Wait until UTRLDBR = 0
   tout = hba->cfg_entries.timeout_values.utrd_poll_timeout_us;
   while (tout != 0) {
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UTRLDBR) == 0) {
         break; 
      }
      ufs_bsp_busy_wait (1);
   }
   if (tout == 0) {
      ufs_error_log (hba, 0x0015);
      return -ETIME; 
   }

   return EOK; 
}

// Scale up to higher SVS modes
int32_t ufs_utp_clock_scale_up (ufs_host_t *hba, uint8_t volt_corner, uint8_t gear)
{
   int32_t rc = EOK;
   uint32_t val = 0; 
   ufs_bsp_speed_config cfg; 
   ufs_bsp_time_values reg_val = {0}; 

   rc = ufs_utp_wait_no_pending_transfers (hba); 
   if (rc != EOK) {
      ufs_error_log (hba, 0x0039); 
      return rc; 
   }

   // Enter hibernate 
   rc = ufs_utp_link_h8 (hba, 1);
   if (rc != EOK) {
      ufs_error_log (hba, 0x002b);
      return rc; 
   }
 // Below is applicable only for getting  >300MHz in HSG4
   if((hba->plat_cfg.core_turbo_switch) && (volt_corner == UFS_CLOCK_MODE_TURBO)) {
	   ufs_bsp_update_maxclk_seq(hba->ufs_core_id, 1);
	   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_VS_CLK_CFG_REG, 0), 0, &val);
	   if (rc != EOK) {
		   ufs_error_log(hba, 0x0055);
		   return rc;
	   }
	   val |= (1<<8);
	   //Write PA_VS_CLK_CFG_REG.ATTR_HW_CGC_EN=1 
	   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_VS_CLK_CFG_REG, 0), val,NULL);
	   if (rc != EOK) {
		  ufs_error_log(hba, 0x0056);
		  return rc;
	   }
	  hsg4_turbo_clk_freq_seq = 1;
   }

    // Get relevant time-related register values 
    ufs_bsp_get_time_reg_values (volt_corner, &reg_val);   

	// Write SYS1CLK_1US_REG.UFS_SYS1CLK_1US
   HWIO_REG_OUT (hba->ufs_hci_addr, VENSPEC_UFS_SYS1CLK_1US, reg_val.SYSCLK_1US);

   // Write DME_VS_CORE_CLK_CTRL.MAX_CORE_CLK_1US_CYCLES  
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(DME_VS_CORE_CLK_CTRL, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log (hba, 0x002c); 
      return rc;
   }
  
   val = (val & ~0x0FFF0000) | (reg_val.DME_MAX_1US << 16);
	
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(DME_VS_CORE_CLK_CTRL, 0), val, NULL);
   if (rc != EOK) {
      ufs_error_log (hba, 0x002d); 
      return rc;
   }

   // Write PA_VS_CORE_CLK_40NS_CYCLES via the DME_SET UIC command
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_VS_CORE_CLK_40NS_CYCLES, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log (hba, 0x002e); 
      return rc;
   }

   val = (val & ~0xF) | reg_val.PA_VS_40NS;
  
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_VS_CORE_CLK_40NS_CYCLES, 0), val, NULL);
   if (rc != EOK) {
      ufs_error_log (hba, 0x002f); 
      return rc;
   }

   // If AH8 enabled, disable HW clock control for UFS clocks 
   if (hba->auto_h8_enabled) {
      ufs_bsp_clk_hw_control (hba->ufs_core_id, 0);
   }
  
	// Re-configure UFS Host Controller clocks based on the volt_corner provided
   ufs_bsp_clk_set (hba->ufs_core_id, volt_corner); 
   hba->curr_volt_corner = volt_corner;
   
   // If AH8 enabled, re-enable HW clock control for UFS clocks 
   if (hba->auto_h8_enabled) {
      ufs_bsp_clk_hw_control (hba->ufs_core_id, 1);
   }

   // Exit hibernate 
   rc = ufs_utp_link_h8 (hba, 0);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0047);
      return rc; 
   }

   // Issue a power mode change to the gear specified 
   memcpy (&cfg, &hba->curr_speed_config, sizeof(ufs_bsp_speed_config));
   cfg.gear = gear; 
   rc = ufs_utp_gear_sw (hba, &cfg);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0048);
      return rc; 
   }
  
   return EOK; 
}

// Scale down to lower SVS modes
int32_t ufs_utp_clock_scale_down (ufs_host_t *hba, uint8_t volt_corner, uint8_t gear)
{
   int32_t rc = EOK;
   uint32_t val = 0;
   ufs_bsp_speed_config cfg;  
   ufs_bsp_time_values reg_val = {0};

   rc = ufs_utp_wait_no_pending_transfers (hba); 
   if (rc != EOK) {
      ufs_error_log (hba, 0x003f);
      return rc; 
   }

   // Write DME_VS_CORE_CLK_CTRL.CORE_CLK_DIV_EN = 0 
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(DME_VS_CORE_CLK_CTRL, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0020); 
      return rc;
   }
  
   val = val & ~(0x100);
  	
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(DME_VS_CORE_CLK_CTRL, 0), val, NULL);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0021); 
      return rc;
   }

   // Issue a power-mode change switch to selected gear 
   memcpy (&cfg, &hba->curr_speed_config, sizeof(ufs_bsp_speed_config)); 
   cfg.gear = gear; 
   rc = ufs_utp_gear_sw (hba, &cfg);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0022);
      return rc; 
   }

   // Enter hibernate
   rc = ufs_utp_link_h8 (hba, 1);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0024);
      return rc; 
   }

   // Get relevant time-related register values 
   ufs_bsp_get_time_reg_values (volt_corner, &reg_val);   

   // Disable HW clock control, if AH8 is enabled
   if (hba->auto_h8_enabled) {
      ufs_bsp_clk_hw_control (hba->ufs_core_id, 0);
   }
  
   // Re-configure UFS clocks to frequencies matching selected voltage corner
   ufs_bsp_clk_set (hba->ufs_core_id, volt_corner); 
   hba->curr_volt_corner = volt_corner;
  
   // If AH8 enabled, re-enable HW clock control for UFS clocks  
   if (hba->auto_h8_enabled) {
      ufs_bsp_clk_hw_control (hba->ufs_core_id, 1);
   }
	 // Below is applicable only for getting  <300MHz 
   if((hsg4_turbo_clk_freq_seq) && (hba->plat_cfg.core_turbo_switch) && 
							(volt_corner != UFS_CLOCK_MODE_TURBO)) {
	   
	   ufs_bsp_update_maxclk_seq(hba->ufs_core_id, 0);	   
	   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_VS_CLK_CFG_REG, 0), 0, &val);
	   if (rc != EOK) {
			ufs_error_log(hba, 0x0057);
			return rc;
		}
	    val &= ~(1<<8);
	    //Write PA_VS_CLK_CFG_REG.ATTR_HW_CGC_EN=0
	    rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_VS_CLK_CFG_REG, 0), val,NULL);
		if (rc != EOK) {
			ufs_error_log(hba, 0x0058);
			return rc;
	    }
	    hsg4_turbo_clk_freq_seq = 0;
   }
   // Write SYS1CLK_1US_REG.UFS_SYS1CLK_1US  
   HWIO_REG_OUT (hba->ufs_hci_addr, VENSPEC_UFS_SYS1CLK_1US, reg_val.SYSCLK_1US);
  
   // Write DME_VS_CORE_CLK_CTRL.MAX_CORE_CLK_1US_CYCLES: bits 27:16
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(DME_VS_CORE_CLK_CTRL, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0026); 
      return rc;
   }

   val = (val & ~0x0FFF0000) | (reg_val.DME_MAX_1US << 16);
  
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(DME_VS_CORE_CLK_CTRL, 0), val, NULL);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0025); 
      return rc;
   }

   // Write PA_VS_CORE_CLK_40NS_CYCLES: bits 3:0 
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_VS_CORE_CLK_40NS_CYCLES, 0), 0, &val);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0027); 
      return rc;
   }

   val = (val & ~0xF) | reg_val.PA_VS_40NS;
  
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_VS_CORE_CLK_40NS_CYCLES, 0), val, NULL);
   if (rc != EOK) {
      ufs_error_log (hba, 0x0028); 
      return rc;
   }

   // Exit hibernate
   rc = ufs_utp_link_h8 (hba, 0);
   if (rc != EOK) {
      ufs_error_log (hba, 0x002a);
      return rc; 
   }

   return EOK; 
}

// Entering/exiting hibernate  
int32_t ufs_utp_link_h8 (ufs_host_t *hba, uint8_t enter)
{
   int32_t rc = EOK;
   uint32_t tout, val; 
   uint32 bmsk; 

   if (hba->xfer_pend) {
      return -EBUSY;
   }

   // If link is active, then we will put the link in hibernate. Otherwise, 
   // we will exit hibernate. If link already is in the state we want to achieve, 
   // just return 
   if (hba->link_state == 1 && enter) {
      rc = ufs_utp_uic_getset (hba, UICCMDR_DME_HIBERNATE_ENTER, 0, 0, NULL);
      if (rc != EOK) {
         ufs_error_log(hba, 0x0095); 
         return rc;
      }
      bmsk = BMSK_UHES;
      hba->link_state = 0; 
   }
   else if (hba->link_state == 0 && !enter) {
      rc = ufs_utp_uic_getset (hba, UICCMDR_DME_HIBERNATE_EXIT, 0, 0, NULL);
      if (rc != EOK) {
         ufs_error_log(hba, 0x0096);  
         return rc;
      }
      bmsk = BMSK_UHXS; 
      hba->link_state = 1; 
   }
   else
   {
      return EOK;  
   }

   // Wait until IS.UHES is set to 1
   tout = UFS_HCI_UHES_POLL_TIMEOUT;
   while (!(HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS) & bmsk)) {
      // Check the value of the IS register for any failure
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS) & UFS_IS_MASK_ALL_ERROR) {
         rc = ufs_utp_parse_errors(hba); 
         if (rc != EOK) {
            return rc; 
         }
      }
      ufs_bsp_busy_wait (10);
      if (--tout == 0) {
         ufs_error_log(hba, 0x0098);
         return -EIO;
      }
   }

   // Set the IS.UHES to clear it
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_IS, bmsk);

   // Check the result of the power mode change request
   val = HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_HCS);
   val = (val & 0x0700) >> 8;
   if (val != 0 && val != 1 && val != 2) {
      ufs_error_log(hba, 0x0099);
      return -EIO;
   }

   return EOK; 
}

// Setup autoH8
void ufs_utp_link_autoh8 (ufs_host_t *hba, uint16_t idle_time_ms) 
{
   ufs_bsp_autoH8 (hba->ufs_core_id, idle_time_ms); 
}

// Check if link is in H8 by reading the TX_FSM_State
boolean ufs_utp_check_link_h8 (ufs_host_t *hba)
{
   uint32_t val; 
   int32_t rc; 

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(TX_FSM_State, 0), 0, &val);
   if (rc < 0) {
      ufs_error_log(hba, 0x0018);
      return FALSE; 
   }

   if (val == TX_FSM_State_HIBERN8) {
      return TRUE; 
   }
   else {
      return FALSE;
   }
}

// Build the UPIU data structure in memory
void ufs_utp_build_upiu (uint32_t *dest_in, upiu_item_t *pupiu)
{
   uint8_t *dest = (uint8_t *)dest_in;
   *dest++ = pupiu->type;
   *dest++ = pupiu->flags;
   *dest++ = pupiu->lun;
   *dest++ = pupiu->task_tag;
   *dest++ = pupiu->cmd_set_type & 0x03;
   *dest++ = pupiu->query_fnc;            // Query Function
   *dest++ = 0;                           // Response
   *dest++ = 0;                           // Status
   *dest++ = 0;                           // Total EHS Length, must be 0
   *dest++ = 0;                           // Device information
   *dest++ = pupiu->data_segment_len >> 8;
   *dest++ = pupiu->data_segment_len & 0xff;

   if (pupiu->type == UPIU_TYPE_COMMAND) {       // Expected Data Length
      *dest++ = pupiu->data_expected_len >> 24;
      *dest++ = pupiu->data_expected_len >> 16;
      *dest++ = pupiu->data_expected_len >> 8;
      *dest++ = pupiu->data_expected_len & 0xff;
   } 

   // Op Specific field - // CDB for command, 
   //                     // Parameter for management
   ufs_utp_memcpy (dest, pupiu->param, 16); 
   dest += 16;
                                          
   // Need to pad a reserved DWORD
   if (pupiu->type != UPIU_TYPE_COMMAND) {
      *((uint32_t *)dest) = 0;
      dest += 4;
   }  

   // If there are more data atached to UPIU header, copy it in
   if ((pupiu->aux_data_len > 0) && (pupiu->aux_data_buf != NULL)) {
      ufs_utp_memcpy (dest, pupiu->aux_data_buf, pupiu->aux_data_len);
   }
}


// Decode the response UPIU
void ufs_utp_decode_upiu (uint32_t *dest_in, upiu_item_t *pupiu)
{
   uint8_t *dest = (uint8_t *)dest_in;
   pupiu->type = *dest++;
   pupiu->flags = *dest++;
   pupiu->lun = *dest++;
   pupiu->task_tag = *dest++;
   pupiu->cmd_set_type = *dest++ & 0x03;
   pupiu->query_fnc = *dest++;
   pupiu->response = *dest++;
   pupiu->status = *dest++;
   dest += 2;
   pupiu->data_segment_len = *dest++ << 8;
   pupiu->data_segment_len |= *dest++;

   if (pupiu->type == UPIU_TYPE_RESPONSE) {
      pupiu->data_residual_len = *dest++ << 24;
      pupiu->data_residual_len |= *dest++ << 16;
      pupiu->data_residual_len |= *dest++ << 8;
      pupiu->data_residual_len |= *dest++;
   }

   // Op Specific field - // CDB for command, 
   //                     // Parameter for management
   ufs_utp_memcpy (pupiu->param, dest, 16);

   if (pupiu->type != UPIU_TYPE_RESPONSE) {
      dest += 4;        // Reserved address is after Transaction specific field
   }
   // If there are more data atached to UPIU header, copy it 
   if ((pupiu->aux_data_len > 0) && (pupiu->aux_data_buf != NULL)) {
      ufs_utp_memcpy (pupiu->aux_data_buf, dest + 16, pupiu->aux_data_len);
   }
}


// Assembly of the transfer request
int32_t ufs_utp_submit_utrd (ufs_host_t *hba, utrd_item_t *pinfo)
{
   // Build UTRD into the memory first
   uint32_t *pt;
   uint32_t prdt_len;
   uint32_t prdt_doffset;
   uint32_t prdt_ents;
   uint32_t i;

   if (hba->xfer_pend) {
      return -EBUSY; 
   }

   // Calculate number of entries required
   prdt_ents = pinfo->data_xfer_len / PRDT_DBC_MAX;
   if (pinfo->data_xfer_len % PRDT_DBC_MAX) {
      prdt_ents++;
   }

   hba->prdtCount = prdt_ents;
   
   // Transfer size check
   if (prdt_ents > MAX_PRDT_ENTRIES) {
      ufs_error_log(hba, 0x0007);
      return -EINVAL;
   }

   pt = pinfo->utp_xfr_desc_ptr;

   *pt++ = ENDIAN_ADJ_32(((pinfo->cmd_type & 0xf) << 28) | 
                         ((pinfo->data_dir & 0x3) << 25) |
                         ((pinfo->interrupt & 0x1) << 24) | 
                         ((pinfo->crypto & 0x1) << 23) | 
                         (pinfo->crypto_index & 0xff));
   *pt++ = ENDIAN_ADJ_32(pinfo->dun & 0xffffffff);  // Lower 32 bits
   *pt++ = 0xf;      // Overall command status, set to 0 at the start
   *pt++ = ENDIAN_ADJ_32((pinfo->dun >> 32) & 0xffffffff); // Upper 32 bits
   *pt++ = ENDIAN_ADJ_32(pinfo->utp_cmd_desc_phy & 0xffffffff);            
                     // Lower 32 bits
   *pt++ = ENDIAN_ADJ_32((pinfo->utp_cmd_desc_phy >> 32) & 0xffffffff);    
                     // Upper 32 bits
   *pt++ = ENDIAN_ADJ_32((((pinfo->resp_upiu_offset / 4) << 16) & 0xffff0000) |
                          ((pinfo->resp_upiu_len / 4 + 
                                (pinfo->resp_upiu_len & 0x03 ? 1 : 0)) & 0x0000ffff));
   *pt++ = ENDIAN_ADJ_32((((pinfo->prdt_offset / 4) << 16) & 0xffff0000) | 
                          (prdt_ents & 0x0000ffff));

   // Build a command descriptor
   pt = pinfo->utp_cmd_desc_ptr;
   ufs_utp_build_upiu (pt, &pinfo->req_upiu);

   // Build the Physical Region Description Table 
   prdt_len = pinfo->data_xfer_len;
   pt = pinfo->utp_cmd_desc_ptr + pinfo->prdt_offset / 4;
   i = 0;
   prdt_doffset = 0;

   if (pinfo->data_dir != UTRD_DIR_NODATA)
   {
      while(1) {
         *pt++ = (pinfo->data_buf_phy + prdt_doffset) & 0xffffffff;
         *pt++ = ((pinfo->data_buf_phy + prdt_doffset) >> 32) & 0xffffffff;
         *pt++ = 0;        // Reserved field
         *pt++ = prdt_len > PRDT_DBC_MAX ? PRDT_DBC_MAX - 1 : (prdt_len - 1);
         if (prdt_len <= PRDT_DBC_MAX) {
            break;
         }
         prdt_len -= PRDT_DBC_MAX;
         prdt_doffset += PRDT_DBC_MAX;
         if (i++ > MAX_PRDT_ENTRIES) {
            ufs_error_log(hba, 0x0006);
            return -EINVAL;
         }
      } 
   }

   // Clear any interupt pending
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_IS, BMSK_UE | BMSK_UTRCS);

   // Check if UTRLRSR is set
   if ( !(HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UTRLRSR))) {
      ufs_error_log(hba, 0x000b);
      return -EIO;
   } 

   // Flush UTRD
   ufs_bsp_cache_op ((void *)(uintptr_t)pinfo->utp_xfr_desc_phy, 256, FLUSH);
   
   // Flush Command Descriptor
   ufs_bsp_cache_op ((void *)(uintptr_t)pinfo->utp_cmd_desc_phy, 
                     pinfo->prdt_offset + (hba->prdtCount * PRDT_SIZE), FLUSH);

   // Ensure data buffer cache is cleaned for writes or invalidated for reads
   if (UTRD_DIR_WRITE == pinfo->data_dir)
      ufs_bsp_cache_op ((void *)(size_t)pinfo->data_buf_phy, pinfo->data_xfer_len, CLEAN);     
   else if (UTRD_DIR_READ == pinfo->data_dir)
      ufs_bsp_cache_op ((void *)(size_t)pinfo->data_buf_phy, pinfo->data_xfer_len, FLUSH);     
   
   ufs_bsp_memory_barrier();

   // Trigger the transfer by write to doorbell register
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTRLDBR, pinfo->utp_doorbell_bit);
   ufs_bsp_memory_barrier();
   
   return EOK;
}


// Wait for a UTRD to complete using polling method
int32_t ufs_utp_poll_utrd_complete (ufs_host_t *hba, utrd_item_t *pinfo)
{
   // Poll the doorbell register until the corresponding bit is 0
   uint32_t tout = hba->cfg_entries.timeout_values.utrd_poll_timeout_us; 
   int errcnt = UFS_MAX_ERR_CNT;

      while (tout != 0) {
      if ( HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS) & BMSK_UTRCS) {
         if (! (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UTRLDBR) & 
                pinfo->utp_doorbell_bit)) {
            // Clear completion interrupt after each transfer to give HW time
            HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_IS, BMSK_UTRCS); 
            // Invalidate the UTRD transfer buffer - somehow response type is wrong
            // in some rare cases
            ufs_bsp_cache_op ((void *)(uintptr_t)pinfo->utp_cmd_desc_phy, 
                              pinfo->prdt_offset + (hba->prdtCount * PRDT_SIZE), INVAL);
            if (pinfo->data_dir == UTRD_DIR_READ) {
               ufs_bsp_cache_op((void *)(size_t)pinfo->data_buf_phy, pinfo->data_xfer_len, INVAL); 
            } 
            return EOK;
         }
      }
      // Check for any UIC error bit
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_IS) & UFS_IS_MASK_ALL_ERROR) {
         if (ufs_utp_parse_errors(hba) != EOK) {
            return -EIO; 
         }

         if (errcnt-- <= 0) {
            return -EIO;
         }
         continue;      // Check for error again
      }
      // If in infinite poll mode, don't decrement counter
      if (!hba->db_infinite_poll) {
         ufs_bsp_busy_wait (1);
         tout--;
      }
      // If non-blocking is enabled, return with busy code if not done
      if (hba->non_blocking_en) {
         return -EBUSY;
      }
   }

   // Timeout has occurred
   ufs_error_log(hba, 0x0004);
   return -ETIME;
}


// Decode of the transfer request response
void ufs_utp_decode_utrd_resp (ufs_host_t *hba, utrd_item_t *pinfo)
{
   // Build UTRD into the memory first
   uint32_t *pt;
   uint8_t cmd_status;

   pt = pinfo->utp_cmd_desc_ptr;

   // Read out the overall command status field
   cmd_status = pt[2] & 0xff;

   if (cmd_status == OCS_SUCCESS) 
   {
      // Decode the Response UPIU
      pt += pinfo->resp_upiu_offset;
   }
}


// Abort a transfer by clearing a UTRD doorbell register
void ufs_utp_abort_utrd (ufs_host_t *hba, utrd_item_t *pinfo)
{
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTRLCLR, ~pinfo->utp_doorbell_bit);
}


// Wait for a UTMRD to complete using polling method
int32_t ufs_utp_poll_utmrd_complete (ufs_host_t *hba, utmrd_item_t *pinfo)
{
   // Poll the doorbell register until the corresponding bit is 0
   uint32_t tout = HCI_UTMRD_POLL_TIMEOUT;

   while (--tout) {
      if (! (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_UTMRLDBR) & 
             pinfo->utp_doorbell_bit)) {
         return EOK;
      }
      ufs_bsp_busy_wait (1);
   }

   // Timeout has occurred
   ufs_error_log(hba, 0x0005);
   return -ETIME;
}


// Abort a transfer by clearing a UTMRD doorbell register
void ufs_utp_abort_utmrd (ufs_host_t *hba, utmrd_item_t *pinfo)
{
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTMRLCLR, ~pinfo->utp_doorbell_bit);
}

// Enable the crypto engine in the host controller
int32_t ufs_utp_enable_crypto_engine (ufs_host_t *hba)
{
   int32_t rc = EOK; 
   uint32_t hce_bmsk = BMSK_CGE | BMSK_HCE, tout = HCI_ENABLE_TIMEOUT;

   if (hba->ce_enabled == 1) {
      return EOK; 
   }

   rc = ufs_utp_wait_no_pending_transfers(hba); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x0008);
      return rc; 
   }

   if (HWIO_REG_IN(hba->ufs_hci_addr, UFSHCI_CAP) & BMSK_CS) {
      HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_HCE, hce_bmsk);

      while (--tout) {
         if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_HCE) & hce_bmsk) {
            break;
         }
         ufs_bsp_busy_wait (1);
      }
      if (tout == 0) {
         ufs_error_log(hba, 0x0009);
         return -EIO;
      }

      hba->ce_enabled = 1; 
   }

   return EOK; 
}

// Partial initialization (No PHY init, link startup)
int32_t ufs_utp_partial_init (ufs_host_t *hba)
{
   // If we have finished the partial init stage or further, return immediately
   if (hba->init_stage >= 1) {
      return EOK; 
   }

   // Look up the base address for the controller and program it
   hba->ufs_hci_addr = ufs_bsp_get_reg_baseaddress(hba->ufs_core_id);
   if (hba->ufs_hci_addr == 0) return -EIO;

   // Clear the debug variables
   hba->next_failure = 0;
   hba->failure_cnt = 0;

   // Start the task counter at 0
   hba->ufs_task_cnt = 0;

   // By default, do not do infinite poll on doorbell
   hba->db_infinite_poll = 0;

   ufs_bsp_default_volt_corner (hba->ufs_core_id, &hba->curr_volt_corner); 
   ufs_bsp_volt_set (hba->ufs_core_id, UFS_BSP_REGULATORS_ON); 

   // NOTE: These buffer need to be 1k aligned
   hba->ufs_req_list_phy = GET_PHY_ADDR(ufs_bsp_allocate_xfer_buf(REQUEST_LIST_BUFFER_SIZE));   
   if (!hba->ufs_req_list_phy)
   {
      ufs_error_log(hba, 0x0079);
      return -ENOMEM;
   }

   // The array is allocated for double amount of space, find the 
   // 1k aligned location 
   hba->ufs_req_list_phy = (hba->ufs_req_list_phy + 1023) & ~((uint64_t)1023);
   // Do the same for logical address
   hba->ufs_req_list_ptr = (uint8_t *)((uintptr_t)hba->ufs_req_list_phy);

   // The management request buffer is the last 1k after the 
   // transfer request buffer, not really used.
   hba->ufs_mgr_list_phy = hba->ufs_req_list_phy + REQUEST_LIST_BUFFER_SIZE - 1024;
   hba->ufs_mgr_list_ptr = hba->ufs_req_list_ptr + REQUEST_LIST_BUFFER_SIZE - 1024;   

   if (hba->plat_cfg.partial_init) {
      // Program the physical address into the register, in this case
      // both the physical address and logical address is identical
      HWIO_REG_OUT(hba->ufs_hci_addr, UFSHCI_UTRLBA, GET_PHY_ADDR_L(hba->ufs_req_list_phy));
      HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTRLBAU, GET_PHY_ADDR_H(hba->ufs_req_list_phy));

      // Managment list 
      HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTMRLBA, GET_PHY_ADDR_L(hba->ufs_mgr_list_phy));
      HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTMRLBAU, GET_PHY_ADDR_H(hba->ufs_mgr_list_phy));
   }

   hba->prdtCount = 0;

   return EOK; 
}

// Making an assumption that the controller ID
// and is programmed into the device data structure
int32_t ufs_utp_init (ufs_host_t *hba)
{
   uint32_t tout;
   int32_t rc = EOK;
   uint32_t val = 0;
   uint32_t phy_reinit_retry = 2;      // Retry phy initialization 
   uint32_t max_hsgear_device = 0; 

   rc = ufs_utp_partial_init(hba);
   if (rc != 0) {
      ufs_error_log(hba, 0x001f); 
      return rc; 
   }

   // Link startup + PHY initialization can be skipped for primary UFS, but vote for the clocks again
   if ((hba->plat_cfg.core_skip) && (hba->ufs_core_id == 0))
   {
       ufs_bsp_clk_set (hba->ufs_core_id, UFS_CLOCK_MODE_ON); 
       goto SKIP_LINK_STARTUP;
   }

   /* UFS HPG v1.1.0 - Section 3.2*/

   /* Steps 1 -3: Enable clocks
         Call the BSP to enable the clock */
PHY_REINIT_RETRY:
   ufs_bsp_reset (hba->ufs_core_id); 
   ufs_bsp_clk_set (hba->ufs_core_id, UFS_CLOCK_MODE_ON);
   ufs_bsp_busy_wait (1000);

   hba->ufs_hw_version = (HWIO_REG_IN (hba->ufs_hci_addr, VENSPEC_UFS_HW_VERSION)) >> 16; 
   if (hba->ufs_hw_version >= 0x3001) 
   {
      ufs_bsp_device_reset(hba->ufs_core_id); 
   }

   rc = ufs_utp_get_host_caps (hba);
   if (rc != EOK) {
      ufs_error_log(hba, 0x001c);
      return rc; 
   }

   hba->has_caps = 1;
   
   // Reset the controller by setting HCE register to 0
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_HCE, 0);

   /*  4. Write UFS_CFG1.UFS_PHY_SOFT_RESET=1. */ 
   HWIO_REG_OUT (hba->ufs_hci_addr, VENSPEC_UFS_CFG1, 0x1800052e); 
   ufs_bsp_busy_wait (1000);

   /* 5.2. Configure PHY */
   rc = ufs_preinit_mphy_configure (hba);
   if (rc < 0) {
      ufs_error_log(hba, 0x001d);
      return rc;
   }

   /* 6. Write UFS_CFG1.UFS_PHY_SOFT_RESET=0. */
   HWIO_REG_OUT (hba->ufs_hci_addr, VENSPEC_UFS_CFG1, 0x1800052c);   
   ufs_bsp_busy_wait (1000);

   /* 7. Set the SERDES_START */
   if (ufs_bsp_mphy_start (hba->ufs_core_id) != UFS_BSP_NO_ERROR) {
      ufs_error_log(hba, 0x001e);
      return -EIO;
   }

   // UFS_CFG1.QUNIPRO_SEL=1 to enable Qunipro controller.
   // Set UFS_DEV_REF_CLK_EN=1 to enable external reference clock
   HWIO_REG_OUT (hba->ufs_hci_addr, VENSPEC_UFS_CFG1, 0x1800052d | (1 << 26));   

   // End of vendor specific config
   // Enable the host controller
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_HCE, BMSK_HCE);

   // Wait until controller is enabled
   tout = HCI_ENABLE_TIMEOUT;
   while (--tout) {
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_HCE) & BMSK_HCE) {
         break;
      }
      ufs_bsp_busy_wait (1);
   }
   if (tout == 0) {
      ufs_error_log(hba, 0x0002);
      return -EIO;
   }

   // Wait until TX_FSM_State attribute is in HIBERN8
   tout = UFS_TX_FSM_STATE_TIMEOUT;
   while (1) {
      if (ufs_utp_check_link_h8 (hba) == TRUE) {
         break; 
      }

      if (tout-- == 0) {
         ufs_error_log(hba, 0x0019);
         return -EIO;
      }
   }

   // Disable LCC on both side during capability exchange
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_Local_TX_LCC_Enable, 0), 
                            0, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0040);
      return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_Peer_TX_LCC_Enable, 0), 
                            0, NULL);
   if (rc != EOK) {
      ufs_error_log(hba, 0x0041);
      return rc;
   }

  /* Note about updating the Appendix A Time-Related Programmable Registers:
     * These registers must be written odd number of times when RX is in DIF-Z.
     * Every 2nd write will erase the value when in DIF-Z. */

   // Not using interrupt, so not setting the IE register
   // Retry number of times for link startup
   tout = hba->cfg_entries.num_linkstartup_retries;
   do {
      // Send DME_LINKSTARTUP command
      rc = ufs_utp_uic_getset (hba, UICCMDR_DME_LINKSTARTUP, 0, 0, NULL);
      if (rc == 0) {
         // First linkstartup ok, continue
         break;
      }
      ufs_error_log(hba, 0x0003);

      if (tout-- == 0) {
         ufs_error_log(hba, 0x000a);
         if (phy_reinit_retry-- != 0) {
            goto PHY_REINIT_RETRY;
         }
         else {
            return -EIO;
         }
      }
   } while(1);

SKIP_LINK_STARTUP:
   // Since HSG4 and beyond is only supported starting from UFS 3.0 and requires a different PHY 
   // sequence, check to see if the device actually has the support. 
   
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_PEER_GET, 
                            UIC_ARG0_MIBattr(TX_HSGEAR_Capability, 0), 
                            0, &max_hsgear_device); 
   if (rc != EOK) {
      ufs_error_log(hba, 0x0097);
      return rc;
   }

   // HSG4 Phy Settings works for HSG3. No need to to reinit the Phy
   // Make a note of max supported gear and overwrite in configuration as well
   if (hba->cfg_entries.init_speed_params.enable_hs && (hba->cfg_entries.init_speed_params.gear > 3)) {
      if (max_hsgear_device < hba->cfg_entries.init_speed_params.gear) {
         hba->cfg_entries.init_speed_params.gear = max_hsgear_device;
      }
   }

   if (hba->cfg_entries.perf_speed_params.enable_hs && (hba->cfg_entries.perf_speed_params.gear > 3)) {
      if (max_hsgear_device < hba->cfg_entries.perf_speed_params.gear) {
         hba->cfg_entries.perf_speed_params.gear = max_hsgear_device;
      }
   }
   
   // At this point, link is up
   hba->link_state = 1;
   
   // If partial init was previously done, we will need to repeat the NOP and re-program 
   // the UTRL and UTMRL addresses after the reset
   if (hba->init_stage == 1) {
      hba->device_awake = 0;   
   }

   // Program the physical address into the register, in this case
   // both the physical address and logical address is identical
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTRLBA, GET_PHY_ADDR_L(hba->ufs_req_list_phy));
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTRLBAU, GET_PHY_ADDR_H(hba->ufs_req_list_phy));

   // Managment list 
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTMRLBA, GET_PHY_ADDR_L(hba->ufs_mgr_list_phy));
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTMRLBAU, GET_PHY_ADDR_H(hba->ufs_mgr_list_phy));

   // More UIC command required?
   
   // Check to make sure the device is detected, wait until it is
   tout = HCI_LINK_STARTUP_TIMEOUT;
   while (--tout) {
      if (HWIO_REG_IN (hba->ufs_hci_addr, UFSHCI_HCS) & BMSK_DP) {
         break;
      }
      ufs_bsp_busy_wait (1);
   }
   if (tout == 0) {
       ufs_error_log(hba, 0x0029);
       return -EIO;
   }

   // Check the value of PA_ConectedTxDataLanes prior to update the value 
   // of MPHY_UFS_UFS_PHY_TX_LANE_ENABLE
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_ConnectedTxDataLanes, 0), 0, &val);
   if (rc != EOK) {
       ufs_error_log(hba, 0x0023);
       return rc;
   }

   // Increase the PA_SaveConfigTime setting beyond the max set by Unipro spec,
   // using vendor specific function
   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, UIC_ARG0_MIBattr(PA_VS_CONFIG_REG1, 0), 0, &val);
   if (rc != EOK) {
       ufs_error_log(hba, 0x0093);
       return rc;
   }

   rc = ufs_utp_uic_getset (hba, UICCMDR_DME_SET, UIC_ARG0_MIBattr(PA_VS_CONFIG_REG1, 0), val | (1 << 12), NULL);
   if (rc != EOK) {
       ufs_error_log(hba, 0x0094);
       return rc;
   }

   // Enable the UTP transfer request list
   HWIO_REG_OUT (hba->ufs_hci_addr, UFSHCI_UTRLRSR, 0x01);
   return rc;
}


// Fill in an UTRD with default values
int32_t ufs_utp_build_std_utrd (ufs_host_t *hba, utrd_item_t *pinfo,
                            uint32_t req_dlen, uint32_t resp_dlen)
{
   // Empty UTRD structure first
   osal_memset (pinfo, 0, sizeof (utrd_item_t));

   pinfo->utrd_desc_ptr = hba->ufs_req_list_ptr;

   // Minimal alignment requirement is 64 bytes
   // Request descriptor is at the base address of the request list 
   pinfo->utp_xfr_desc_phy = hba->ufs_req_list_phy;
   pinfo->utp_xfr_desc_ptr = (uint32_t *)(pinfo->utrd_desc_ptr);
   // Offset the first command descriptor 256 bytes from the request descriptor
   pinfo->utp_cmd_desc_phy = hba->ufs_req_list_phy + 256;
   pinfo->utp_cmd_desc_ptr = (uint32_t *)(pinfo->utrd_desc_ptr + 256);

   pinfo->req_upiu_len = UPIU_STD_HDR_LEN + req_dlen;
   pinfo->resp_upiu_len = UPIU_STD_HDR_LEN + resp_dlen;

   // Make sure the RESP UPIU is adjusted to 64-bit boundary
   pinfo->resp_upiu_offset = (pinfo->req_upiu_len & (~0x07)) + 
                             ((pinfo->req_upiu_len & 0x07) ? 8 : 0);
   pinfo->prdt_offset = pinfo->resp_upiu_offset + pinfo->resp_upiu_len;

   // Adjust PRDT offset to 64-bit boundary
   pinfo->prdt_offset = (pinfo->prdt_offset & ~0x07) + 
                        ((pinfo->prdt_offset & 0x07) ? 8 : 0);

   pinfo->prdt_len = 16;                  // Single entry
   pinfo->utp_doorbell_bit = UFS_UTRD_DOORBELL_CH;
   pinfo->interrupt = 1;

   return EOK;
}

void ufs_preinit_write_mphy_values (ufs_host_t *hba, 
                                    struct ufs_mphy_init_item *mphy_table, uint32_t table_size)
{
   boolean rateb = FALSE, gear4 = FALSE, gear5 = FALSE; 
   uint16_t flags = 0, offs = 0; 
   uint32_t i = 0; 
   uint8_t val;

   rateb = (hba->cfg_entries.perf_speed_params.rate == 0x02) ? TRUE : FALSE; 
   gear4 = ((hba->cfg_entries.perf_speed_params.enable_hs) && (hba->cfg_entries.perf_speed_params.gear == 4)) ? TRUE : FALSE; 
   gear5 = ((hba->cfg_entries.perf_speed_params.enable_hs) && (hba->cfg_entries.perf_speed_params.gear >= 5)) ? TRUE : FALSE; 
   
   for (i = 0; i < table_size; i++) {
      offs = mphy_table[i].offset; 
      val = mphy_table[i].val;
      flags = mphy_table[i].flags; 

      // If last item is reached, stop
      if (flags == STOP_CONDITION) break;    

      /* If conditional entry flag is set, check the conditions to decide if the next entry is
         valid or not */
      if (flags != 0) {
         if (((flags & RATE_MASK) >> RATE_SHFT) == RATE_A) {
            if (rateb == TRUE) {
               continue; 
            } 
         }
         else if (((flags & RATE_MASK) >> RATE_SHFT) == RATE_B) {
            if (rateb == FALSE) {
               continue; 
            }
         }

         if (((flags & GEAR_MASK) >> GEAR_SHFT) == HS_G4) {
            if (gear4 == FALSE) {
               continue; 
            }
         }
		 else if (((flags & GEAR_MASK) >> GEAR_SHFT) == HS_G5) {
            if (gear5 == FALSE) {
               continue; 
            }
         }
         else if (((flags & GEAR_MASK) >> GEAR_SHFT) == DEFAULT_GEAR) {
            if ((gear4 == TRUE) || (gear5 == TRUE)) { 
               continue; 
            }
         }
      }

      out_dword(offs + hba->ufs_hci_addr, val);
   }
}

// QCOM UFS MPHY spcific configurations
static int32_t ufs_preinit_mphy_configure (ufs_host_t *hba)
{
   struct ufs_mphy_init_item *mphy_init_table;
   uint32_t size; 

   size = ufs_bsp_get_mphy_init_item_table (&mphy_init_table);
   ufs_preinit_write_mphy_values(hba, mphy_init_table, size); 

   // For HW version 3.1.0 and above, apply the 2 lane PHY sequence 
   if ((hba->ufs_hw_version >= 0x3001) &&
       (hba->ufs_mphy_caps.tx_avail_lanes == 2)) {

      size = ufs_bsp_get_mphy_init_2_lane_item_table (&mphy_init_table);
      ufs_preinit_write_mphy_values(hba, mphy_init_table, size);
   }

   size = ufs_bsp_get_mphy_init_end_item_table (&mphy_init_table);
   ufs_preinit_write_mphy_values(hba, mphy_init_table, size);

   return EOK;
}

#ifdef UFS_USES_UIC_DEBUG_DUMP
void ufs_uic_debug_dump_group (ufs_host_t *hba, uint32_t *item_array, 
                               uint32_t item_cnt, uint32_t GIdx)
{
   uint32_t i;
   uint32_t val;
   int32_t rc;

   for (i = 0; i < item_cnt; i++) {
      rc = ufs_utp_uic_getset (hba, UICCMDR_DME_GET, 
                               MIBattr(item_array[i], GIdx), 0, &val);
      if (rc == EOK) {
         ufs_uic_dump_buf[ufs_uic_debug_idx].idx = item_array[i];
         ufs_uic_dump_buf[ufs_uic_debug_idx].gen = GIdx;
         ufs_uic_dump_buf[ufs_uic_debug_idx].val = val;
         if (ufs_uic_debug_idx++ >= UFS_UIC_DEBUG_DUMP_SIZE) {
            ufs_uic_debug_idx = 0;
         }
      }
   }
}
#endif

void ufs_uic_debug_dump (ufs_host_t *hba)
{
#ifdef UFS_USES_UIC_DEBUG_DUMP
   uint32_t l1_tx_itm[] = DME_L1_TX_ITEM;
   uint32_t l1_rx_itm[] = DME_L1_RX_ITEM;
   uint32_t l1x5_itm[] =  DME_L1x5_ITEM;
   uint32_t l2_itm[] = DME_L2_ITEM;
   uint32_t l3_itm[] = DME_L3_ITEM;
   uint32_t l4_itm[] =  DME_L4_ITEM;
   uint32_t dme_itm[] =  DME_DME_ITEM;

   ufs_uic_debug_dump_group (hba, l1_tx_itm, (sizeof (l1_tx_itm)/sizeof(uint32_t)), 0);
   ufs_uic_debug_dump_group (hba, l1_rx_itm, (sizeof (l1_rx_itm)/sizeof(uint32_t)), 4);
   ufs_uic_debug_dump_group (hba, l1x5_itm, (sizeof (l1x5_itm)/sizeof(uint32_t)), 0);
   ufs_uic_debug_dump_group (hba, l2_itm, (sizeof (l2_itm)/sizeof(uint32_t)), 0);
   ufs_uic_debug_dump_group (hba, l3_itm, (sizeof (l3_itm)/sizeof(uint32_t)), 0);
   ufs_uic_debug_dump_group (hba, l4_itm, (sizeof (l4_itm)/sizeof(uint32_t)), 0);
   ufs_uic_debug_dump_group (hba, dme_itm, (sizeof (dme_itm)/sizeof(uint32_t)), 0);
#endif
   (void) hba;
}

void ufs_dump_regs (ufs_host_t *hba)
{
   char log_buffer[UFS_REG_DUMP_STR_LEN] = {0}; 
   
   if (NULL == hba) 
   {
      return; 
   }

   snprintf(log_buffer, UFS_REG_DUMP_STR_LEN, 
            "IS: %x, UECPA: %x, UECDL: %x, UECN: %x, UECT: %x, UECDME: %x, REG_PA_ERR_CODE: %x",
            hba->dbg_is_val, hba->dbg_uecpa_val, hba->dbg_uecdl_val, hba->dbg_uecn_val, 
            hba->dbg_uect_val, hba->dbg_uecdme_val, hba->dbg_pa_err_val); 
   ufs_bsp_log(log_buffer, UFS_LOG_ERROR); 
}
