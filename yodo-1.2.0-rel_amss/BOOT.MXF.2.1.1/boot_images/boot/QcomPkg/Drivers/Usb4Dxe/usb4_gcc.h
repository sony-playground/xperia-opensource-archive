
/**
 * @file usb4_gcc.h
 *
 * @brief USB4_COMDEF types
 *
 * Copyright (c) 2019-2020 Qualcomm Technologies Incorporated.
 * All Rights Reserved.
 * Qualcomm Confidential and Proprietary
 */
#ifndef __USB4_GCC_H__
#define __USB4_GCC_H__

/*----------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------*/
#include "Usb4Log.h"
#include "usb4_platform.h"
// #include "VVHAL_usb4_comdef.h"

/*----------------------------------------------------------------------------
 * Defines
 *-------------------------------------------------------------------------*/

#define USB4_GCC_HIA_MASTER                 (1 << 0)
#define USB4_GCC_SB                         (1 << 1)
#define USB4_GCC_SYS                        (1 << 2)
#define USB4_GCC_TMU                        (1 << 3)
#define USB4_GCC_AHB                        (1 << 4)
#define USB4_GCC_PHY_RX0                    (1 << 5)
#define USB4_GCC_PHY_RX1                    (1 << 6)
#define USB4_GCC_AGGRE_USB4_AXI             (1 << 7)
#define USB4_GCC_DP_PCLK                    (1 << 8)
#define USB4_GCC_DP_PRLL                    (1 << 9)
#define USB4_GCC_PCIE_PIPE                  (1 << 10)
#define USB4_GCC_USB_PIPE                   (1 << 11)
#define USB4_GCC_PHY_FLL                    (1 << 12)
#define USB4_GCC_TPDM_APB                   (1 << 13)   /* tpdm registers */
#define USB4_GCC_TPDM_ATB                   (1 << 14)   /* interface to dragonlink */
#define USB4_GCC_MMNOC_TSCTR                (1 << 15)
#define USB4_GCC_PHY_P2RR2P_PIPE            (1 << 16)
#define USB4_GCC_AGGRE_NOC_AXI              (1 << 17)
#define USB4_GCC_AGGRE_USB_NOC_AXI          (1 << 18)
#define USB4_GCC_AGGRE_NOC_QOSGEN_EXTREF    (1 << 19)
#define USB4_GCC_AGGRE_NOC_PCIE_TUNNEL_AXI  (1 << 20)

#define USB4_GCC_RESET_ALL           0xFFFFFFFF

#define USB4_GCC_WAKE_SPECIFIC_RESET    (\
                                            USB4_GCC_HIA_MASTER |\
                                            USB4_GCC_SB         |\
                                            USB4_GCC_SYS        |\
                                            USB4_GCC_TMU        |\
                                            USB4_GCC_AHB        |\
                                            USB4_GCC_PHY_RX0    |\
                                            USB4_GCC_PHY_RX1    |\
                                            USB4_GCC_AGGRE_USB4_AXI   |\
                                            USB4_GCC_DP_PCLK          |\
                                            USB4_GCC_DP_PRLL          |\
                                            USB4_GCC_PCIE_PIPE        |\
                                            USB4_GCC_USB_PIPE         |\
                                            USB4_GCC_MMNOC_TSCTR      |\
                                            USB4_GCC_PHY_P2RR2P_PIPE  |\
                                            USB4_GCC_AGGRE_NOC_AXI     \
                                        )

#define USB4_GCC_USB3_INIT_SPECIFIC_RESET    (\
                                                USB4_GCC_USB_PIPE         \
                                             )

// TODO: AC Note: usb4_gcc_platform specific APIs are absorbed into this file


#if 0 // Change into usb4_platform_ctx_t
typedef struct
{
    UINT32 m_coreIdx;    /**< @brief core index */
    void* m_pHandler;   /**< @brief may be used by the implementation */
} usb4_gcc_ctx_t;
#endif

/**
 * @brief Initialzie GCC module 
 * @param [in] coreIdx core index
 * @param [in] coreBaseAddr core base address
 * @return 0 on success, other on failure
 */
int Usb4GccInit(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 coreIdx, UINT8* coreBaseAddr);

/**
 * @brief Core collapse control
 * @param [in] bCollapse - Collapse if TRUE, Un-collapse if FALSE
 * @return 0 on success, other on failure
 */
int Usb4GccCoreCollapse(usb4_platform_ctx_t* usb4_platform_ctx, boolean bCollapse);

 /**
 * @brief GateUSB3SleepClk for Sleep/Wake scenario
 * @param [in] bEnable TRUE to enable, FALSE to disable
 * @return 0 on success, other on failure
 */
int Usb4GccEnableUSBSleepClk(usb4_platform_ctx_t* usb4_platform_ctx, boolean bEnable);

/**
 * @brief Configure USB3 controller to USB4 tunneled mode
 * @return 0 on success, other on failure
 */
int Usb4GccConfigureUSB3toUSB4mode(usb4_platform_ctx_t* usb4_platform_ctx);


/**
 * @brief Enable all the clocks
 * @param [in] api_mask see #USB4_GCC* for details
 * @param [in] bEnable TRUE to enable, FALSE to disable
 * @return 0 on success, other on failure
 */
int Usb4GccEnableClocks(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 api_mask, BOOLEAN bEnable);

/**
 * @brief Assert the reset signal
 * @param [in] mask see #USB4_GCC* for details
 * @return 0 on success, other on failure
 */
int Usb4GccAssertReset(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 mask);

/**
 * @brief Assert the reset signal
 * @param [in] mask see #USB4_GCC* for details
 * @return 0 on success, other on failure
 */
int Usb4GccDeAssertReset(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 mask);


/**
 * @brief Configure MUXs in GCC (for ASIC only)
 * @param [in] Value to configure muxs with
 * @return 0 on success, other on failure
 */
int Usb4GccConfigureGccMUXs(usb4_platform_ctx_t* usb4_platform_ctx, uint32 muxVal);


EFI_STATUS
Usb4PlatformConfigPowerDomain(
  IN usb4_platform_ctx_t* usb4_platform_ctx,
  IN BOOLEAN Enable,
  IN CONST CHAR8 *DomainStr
  );
#endif /* __USB4_GCC_H__ */

