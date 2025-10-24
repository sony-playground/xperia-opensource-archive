/**
 * @file boot_mhi_null.c
 *
 * @brief Null wrapper for mhi_boot.c.
 */
/*============================================================================
               Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
               All Rights Reserved.
               Confidential and Proprietary - Qualcomm Technologies, Inc.
============================================================================*/

/*----------------------------------------------------------------------------
 * Include Files
 * -------------------------------------------------------------------------*/
#include "mhi_boot.h"

/*----------------------------------------------------------------------------
 * Preprocessor Definitions and Constants
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Global Data Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Variable Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static Function Declarations and Definitions
 * -------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Externalized Function Definitions
 * -------------------------------------------------------------------------*/
/**
 * This function initializes the MHI boot interface, including the Sahara
 * and bootlogger channels.
 *
 * @return Possible return values include:
 *         * BULK_SUCCESS: success
 *         * BULK_ERR_ENUMERATION: a channel could not be opened
 *         * BULK_ERR_UNKNOWN: all other errors
 */
uint32 mhi_boot_init(void)
{
   return BULK_SUCCESS;
}

/**
 * This function shuts down MHI boot. This involves any clean up such as
 * saving rings to host memory to allow hand over to AMSS.
 *
 * @return None
 */
void mhi_boot_shutdown(void)
{
   return;
}

/**
 * This function polls MHI for any new data.
 *
 * @return None
 */
void mhi_boot_poll(void)
{
   return;
}

/**
 * This function reads bulk data over the MHI Sahara RX channel.
 *
 * @param[in]  rx_buf    RX buffer
 * @param[in]  len       Length of buffer in bytes
 * @param[in]  rx_cb     CB to be called when operation is completed
 * @param[out] err_code  Set if any error occurred
 * @param[in]  type      Specifies the packet type
 *
 * @return The number of bytes read if CB is not specified
 */
uint32 mhi_boot_rx_bulk(uint8 *rx_buf, uint32 len, sahara_rx_cb_type rx_cb,
                        uint32 *err_code, enum boot_sahara_packet_type type)
{
   return 0;
}

/**
 * This function transmits bulk data over the MHI Sahara TX channel.
 *
 * @param[in]  tx_buf    TX buffer
 * @param[in]  len       Length of data in bytes
 * @param[in]  tx_cb     CB to be called when operation is completed
 * @param[out] err_code  Set if any error occurred
 *
 * @return The number of bytes written if CB is not specified
 */
uint32 mhi_boot_tx_bulk(uint8 *tx_buf, uint32 len, sahara_tx_cb_type tx_cb, uint32 *err_code)
{
   return 0;
}

/**
 * This function returns the maximum raw data size, in bytes, for the MHI
 * Sahara channels. This is used to determine the maximum raw binary data
 * size that can be read at one time.
 *
 * @return The maximum raw data size
 */
uint32 mhi_boot_get_max_raw_data_size(void)
{
   return 0;
}

/**
 * This function logs a message over the MHI bootlogger channel.
 *
 * @param[in]  msg   Message to log
 * @param[in]  size  Message size
 *
 * @return 0 for success else an error
 */
uint32 mhi_boot_log_message(const char *msg, uint32 size)
{
   return 0;
}

/**
 * This function checks whether MHI inband EDL mode was enabled by the host.
 *
 * @return Whether MHI inband EDL mode was enabled (TRUE or FALSE)
 */
boot_boolean mhi_boot_edl_check(void)
{
   return FALSE;
}


void mhi_boot_set_dma_enable(boolean enable)
{
}