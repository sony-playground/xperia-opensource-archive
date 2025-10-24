/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_gcc_platform.c
 *
 *  @brief :  usb4 GCC class platform specific implementation
 *
 *   Copyright (c) 2019-2021 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Defintions
 *-------------------------------------------------------------------------*/
#if defined(USB4_COMPILING_GEN_EMU) || defined(RUMI) 
    #define USB4_GCC_GENEMU
#endif /* USB4_COMPILING_GEN_EMU || RUMI */

/*----------------------------------------------------------------------------
 * Include Files
 *-------------------------------------------------------------------------*/
#include "msmhwiobase.h"
#include <HALhwio.h>
#include "usb4_gcc_hwio.h"
#include "pd_hwioreg_dut.h" // GE registers

#include <Usb4Utils.h>
#include "usb4_gcc.h"
// #include "VVHAL_usb4_hwio.h"            // HWIO macros
// #include "VVHAL_usb4_logger.h"          // logging utilities
// #include "VVHAL_usb4_timer.h"           // timer
// #include "VVHAL_usb4_hwioreg_core.h"    // HWIO symbols


#ifdef USB4_PLATFORM_SOC_TLMM
#include "msmhwio_tlmm.h"
#endif /* USB4_PLATFORM_SOC_TLMM */

// #if !defined(USB4_GCC_GENEMU)
// extern "C" {
//     #include "VVDRV_clk_drv.h"
// }
// #endif // USB4_GCC_GENEMU


/*----------------------------------------------------------------------------
 * Defintions
 *-------------------------------------------------------------------------*/
#if defined(USB4_GCC_GENEMU)
#define USB4_GCC_PLATFORM_CLK_ALL \
(\
        USB4_GCC_HIA_MASTER | \
        USB4_GCC_SB         | \
        USB4_GCC_SYS        | \
        USB4_GCC_TMU        | \
        USB4_GCC_AHB        | \
        USB4_GCC_PHY_RX0    | \
        USB4_GCC_PHY_RX1    | \
        USB4_GCC_DP_PCLK    | \
        USB4_GCC_DP_PRLL    | \
        USB4_GCC_PCIE_PIPE  | \
        USB4_GCC_USB_PIPE   | \
        USB4_GCC_PHY_FLL      \
)

#else /* !USB4_GCC_GENEMU */
#define USB4_GCC_PLATFORM_CLK_ALL \
(\
        USB4_GCC_HIA_MASTER                 |\
        USB4_GCC_SB                         |\
        USB4_GCC_SYS                        |\
        USB4_GCC_TMU                        |\
        USB4_GCC_AHB                        |\
        USB4_GCC_PHY_RX0                    |\
        USB4_GCC_PHY_RX1                    |\
        USB4_GCC_AGGRE_USB4_AXI             |\
        USB4_GCC_DP_PCLK                    |\
        USB4_GCC_PCIE_PIPE                  |\
        USB4_GCC_USB_PIPE                   |\
        USB4_GCC_PHY_FLL                    |\
        USB4_GCC_TPDM_APB                   |\
        USB4_GCC_TPDM_ATB                   |\
        USB4_GCC_PHY_P2RR2P_PIPE            |\
        USB4_GCC_AGGRE_USB_NOC_AXI          \
)

  // USB4_GCC_DP_PRLL (from MDSS, not in our control) | \
  //  USB4_GCC_MMNOC_TSCTR (Cannot modify in UEFI)               | \
  //  USB4_GCC_AGGRE_NOC_AXI (Cannot modify in UEFI)              |\
  // USB4_GCC_AGGRE_NOC_QOSGEN_EXTREF  (Cannot modify in UEFI)    |\
  // USB4_GCC_AGGRE_NOC_PCIE_TUNNEL_AXI  (Cannot modify in UEFI)
#endif /* !USB4_GCC_GENEMU */

#define USB4_FREQ_MHZ(f)                   (f * 1000 * 1000)
#define USB4_FREQ_KHZ(f)                   (f * 1000)

/*----------------------------------------------------------------------------
 * Tyepedefs
 *-------------------------------------------------------------------------*/

#if defined(USB4_GCC_GENEMU)
typedef struct
{
    UINT32 api_mask; 
    UINT32 field_mask;
} USB4_gcc_map;
#else /* USB4_GCC_GENEMU */
typedef struct
{
    UINT32 api_mask; 
    const char* clk;
    const char* clk_ares;
    CONST UINT32  Freq; // HLOS
    CONST UINT32  Div; // HLOS
    // ClockIdType handle; // This has to be the very last entry as it's not initialized until code runs
} USB4_gcc_map;
#endif /* USB4_GCC_GENEMU */

/*----------------------------------------------------------------------------
 * Local variables
 *-------------------------------------------------------------------------*/
#if defined(USB4_GCC_GENEMU)
    static const USB4_gcc_map s_usb4_gcc_map[] =
    {
        { USB4_GCC_HIA_MASTER, HWIO_FMSK(GE_DUT_RESET_REG, USB4_HIA_MSTR_RESET) },
        { USB4_GCC_SB,         HWIO_FMSK(GE_DUT_RESET_REG, USB4_SB_RESET)       },
        { USB4_GCC_SYS,        HWIO_FMSK(GE_DUT_RESET_REG, USB4_SYS_RESET)      },
        { USB4_GCC_TMU,        HWIO_FMSK(GE_DUT_RESET_REG, USB4_TMU_ARES)       },
        { USB4_GCC_AHB,        HWIO_FMSK(GE_DUT_RESET_REG, USB4_AHB_RESET)      },
        { USB4_GCC_PHY_RX0,    HWIO_FMSK(GE_DUT_RESET_REG, USB4_RX0_RESET)      },
        { USB4_GCC_PHY_RX1,    HWIO_FMSK(GE_DUT_RESET_REG, USB4_RX1_RESET)      },
        { USB4_GCC_DP_PCLK,    HWIO_FMSK(GE_DUT_RESET_REG, USB4_DP_PCLK_ARES)   },
        { USB4_GCC_DP_PRLL,    HWIO_FMSK(GE_DUT_RESET_REG, DP_PRLL_ARES)        },
        { USB4_GCC_PCIE_PIPE,  HWIO_FMSK(GE_DUT_RESET_REG, USB4_PCIE_PIPE_ARES) },
        { USB4_GCC_USB_PIPE,   USB4_HWIO_2FMSK(GE_DUT_RESET_REG, USB4_USB_PIPE_ARES, USB4_CTRL_PIPE_ARES) },// single clock domain on asic, split in ge
        { USB4_GCC_PHY_FLL,    HWIO_FMSK(GE_DUT_RESET_REG, USB4_PHY_FLL_ARES)   },
        //{ USB4_GCC_PDPHY_AHB,
    };

#else /* !USB4_GCC_GENEMU */

    /* not const since clkopen will update the handle */
    static USB4_gcc_map s_usb4_0_gcc_map[] = // south bridge
    {
        { USB4_GCC_AGGRE_NOC_AXI,       "gcc_aggre_noc_south_axi_clk",  "gcc_aggre_noc_south_axi_ares",    0,                    1},
        { USB4_GCC_AGGRE_USB4_AXI,      "gcc_aggre_usb4_axi_clk",       "gcc_aggre_usb4_axi_ares",         USB4_FREQ_MHZ(350),   1},
        { USB4_GCC_HIA_MASTER,          "gcc_usb4_master_clk",          "gcc_usb4_master_ares",            USB4_FREQ_MHZ(350),   1},
        { USB4_GCC_SB,                  "gcc_usb4_sb_if_clk",           "gcc_usb4_sb_if_ares",             0,                    1},
        { USB4_GCC_SYS,                 "gcc_usb4_sys_clk",             "gcc_usb4_sys_ares",               0,                    1},
        { USB4_GCC_TMU,                 "gcc_usb4_tmu_clk",             "gcc_usb4_tmu_ares",               USB4_FREQ_MHZ(250),   1},
        { USB4_GCC_AHB,                 "gcc_usb4_cfg_ahb_clk",         "gcc_usb4_cfg_ahb_ares",           0,                    1},
        { USB4_GCC_PHY_RX0,             "gcc_usb4_phy_rx0_clk",         "gcc_usb4_phy_rx0_ares",           0,                    1},
        { USB4_GCC_PHY_RX1,             "gcc_usb4_phy_rx1_clk",         "gcc_usb4_phy_rx1_ares",           0,                    1},
        { USB4_GCC_DP_PCLK,             "gcc_usb4_dp_clk",              "gcc_usb4_dp_ares",                0,                    1},
        // { USB4_GCC_DP_PRLL,          NULL,                           }, // not from GCC, from MDSS, we don't control it..
        { USB4_GCC_PCIE_PIPE,           "gcc_usb4_phy_pcie_pipe_clk",   "gcc_usb4_phy_pcie_pipe_ares",     0,                    1},
        { USB4_GCC_USB_PIPE,            "gcc_usb4_phy_usb_pipe_clk",    "gcc_usb4_phy_usb_pipe_ares",      0,                    1},
        { USB4_GCC_PHY_FLL,             "gcc_usb4phy_phy_prim_bcr",     NULL,                              0,                    1}, // reseting the PHY + sleep login in CIO //
        { USB4_GCC_TPDM_APB,            "gcc_usb4_apb_clk",             "gcc_usb4_apb_ares" ,              0,                    1}, // tpdm registers
        { USB4_GCC_TPDM_ATB,            "gcc_usb4_at_clk",              "gcc_usb4_at_ares",                0,                    1}, // interface to dragonlink
        
        { USB4_GCC_PHY_P2RR2P_PIPE,     "gcc_usb4_phy_p2rr2p_pipe_clk", "gcc_usb4_phy_p2rr2p_pipe_ares",   0,                    1},
        { USB4_GCC_MMNOC_TSCTR,         "gcc_mmnoc_tsctr_clk",          "gcc_mmnoc_tsctr_ares",            0,                    1},
        
        { USB4_GCC_AGGRE_USB_NOC_AXI,         "gcc_aggre_usb_noc_axi_clk",     "gcc_aggre_usb_noc_axi_ares",                  0, 1},
        { USB4_GCC_AGGRE_NOC_QOSGEN_EXTREF,   "gcc_aggre_noc_qosgen_extref_clk", "gcc_aggre_noc_qosgen_extref_ares",          0, 1},
        { USB4_GCC_AGGRE_NOC_PCIE_TUNNEL_AXI, "gcc_aggre_noc_pcie0_tunnel_axi_clk", "gcc_aggre_noc_pcie0_tunnel_axi_ares",    0, 1},
    };
    /* not const since clkopen will update the handle */
    static USB4_gcc_map s_usb4_1_gcc_map[] = // north bridge
    {
        { USB4_GCC_AGGRE_NOC_AXI,   "gcc_aggre_noc_north_axi_clk",    "gcc_aggre_noc_north_axi_ares",      0,                    1},
        { USB4_GCC_AGGRE_USB4_AXI,  "gcc_aggre_usb4_1_axi_clk",       "gcc_aggre_usb4_1_axi_ares",         USB4_FREQ_MHZ(350),   1},
        { USB4_GCC_HIA_MASTER,      "gcc_usb4_1_master_clk",          "gcc_usb4_1_master_ares",            USB4_FREQ_MHZ(350),   1},
        { USB4_GCC_SB,              "gcc_usb4_1_sb_if_clk",           "gcc_usb4_1_sb_if_ares",             0,                    1},
        { USB4_GCC_SYS,             "gcc_usb4_1_sys_clk",             "gcc_usb4_1_sys_ares",               0,                    1},
        { USB4_GCC_TMU,             "gcc_usb4_1_tmu_clk",             "gcc_usb4_1_tmu_ares",               USB4_FREQ_MHZ(250),   1},
        { USB4_GCC_AHB,             "gcc_usb4_1_cfg_ahb_clk",         "gcc_usb4_1_cfg_ahb_ares",           0,                    1},
        { USB4_GCC_PHY_RX0,         "gcc_usb4_1_phy_rx0_clk",         "gcc_usb4_1_phy_rx0_ares",           0,                    1},
        { USB4_GCC_PHY_RX1,         "gcc_usb4_1_phy_rx1_clk",         "gcc_usb4_1_phy_rx1_ares",           0,                    1},
        { USB4_GCC_DP_PCLK,         "gcc_usb4_1_dp_clk",              "gcc_usb4_1_dp_ares",                0,                    1},
        // { USB4_GCC_DP_PRLL,      NULL,                             }, // not from GCC, from MDSS, we don't control it..
        { USB4_GCC_PCIE_PIPE,       "gcc_usb4_1_phy_pcie_pipe_clk",   "gcc_usb4_1_phy_pcie_pipe_ares",     0,                    1},
        { USB4_GCC_USB_PIPE,        "gcc_usb4_1_phy_usb_pipe_clk",    "gcc_usb4_1_phy_usb_pipe_ares",      0,                    1},
        { USB4_GCC_PHY_FLL,         "gcc_usb4phy_1_phy_prim_bcr",     NULL,                                0,                    1}, // reseting the PHY + sleep login in CIO
        { USB4_GCC_TPDM_APB,        "gcc_usb4_1_apb_clk",             "gcc_usb4_1_apb_ares",               0,                    1}, // tpdm registers
        { USB4_GCC_TPDM_ATB,        "gcc_usb4_1_at_clk",              "gcc_usb4_1_at_ares",                0,                    1}, // interface to dragonlink
        { USB4_GCC_PHY_P2RR2P_PIPE, "gcc_usb4_1_phy_p2rr2p_pipe_clk", "gcc_usb4_1_phy_p2rr2p_pipe_ares",   0,                    1},
        { USB4_GCC_MMNOC_TSCTR,     "gcc_mmnoc_tsctr_clk",            "gcc_mmnoc_tsctr_ares",              0,                    1},
        
        { USB4_GCC_AGGRE_USB_NOC_AXI,         "gcc_aggre_usb_noc_axi_clk",     "gcc_aggre_usb_noc_axi_ares",                  0, 1},
        { USB4_GCC_AGGRE_NOC_QOSGEN_EXTREF,   "gcc_aggre_noc_qosgen_extref_clk",  "gcc_aggre_noc_qosgen_extref_ares",         0, 1},
        { USB4_GCC_AGGRE_NOC_PCIE_TUNNEL_AXI, "gcc_aggre_noc_pcie1_tunnel_axi_clk", "gcc_aggre_noc_pcie1_tunnel_axi_clk",     0, 1},
        
        // HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE_4, USB4_1_PHY_PCIE_PIPE_CLK_ENA, enable);

    };

#endif /* USB4_GCC_GENEMU */

/*----------------------------------------------------------------------------
 * Static functions
 *-------------------------------------------------------------------------*/
#if defined(USB4_GCC_GENEMU)
static int get_fmask(UINT32 apimask, UINT32* pMask)
{
    UINT32 i;
    UINT32 mask = 0x0;
    
    for (i = 0; i < ARR_SIZE(s_usb4_gcc_map); ++i)
    {
        if (0 != (s_usb4_gcc_map[i].api_mask & apimask))
        {
            mask |= s_usb4_gcc_map[i].field_mask;
        }
    }
    
    *pMask = mask;`
    return 0;
}
#else /* !USB4_GCC_GENEMU */
static const USB4_gcc_map* get_clk(UINT32 coreId, UINT32 apimask)
{
    UINT32 i;
//    UINT32 mask = 0x0;
    
    if (0 == coreId)
    {
        for (i = 0; i < ARR_SIZE(s_usb4_0_gcc_map); ++i)
        {
            if (0 != (s_usb4_0_gcc_map[i].api_mask & apimask))
            {
                return s_usb4_0_gcc_map + i;
            }
        }
    }
    else if (1 == coreId)
    {
        for (i = 0; i < ARR_SIZE(s_usb4_1_gcc_map); ++i)
        {
            if (0 != (s_usb4_1_gcc_map[i].api_mask & apimask))
            {
                return s_usb4_1_gcc_map + i;
            }
        }
    }
    else
    {
        USB4_ERROR_STACK_MSG(-1, "Unsupported coreId");
        return NULL;
    }
    
    Usb4Log2(USB4_LOG_CFG, getclk__Params__Core__CouldNotFindClkMask, 0, coreId, apimask);
    // USB4_LOG_ERROR("Core[%u] Couldnt find clk mask= 0x%02X\n", coreId, apimask);
    USB4_ERROR_STACK(-1);
    return NULL;
}

static UINT32 g_usb4_full_phy_reset = 1;
static UINT32 g_usb4_mux_delay = 100;
static UINT32 g_usb4_hold_delay = 1;
static UINT32 g_usb4_release_delay = 0;


static int assert_gcc_misc_resets(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 coreId, BOOLEAN bAssert)
{
    UINT32 elapsed_us;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
    if (0 == coreId)
    {
        if (TRUE == bAssert)
        {
            HWIO_OUT(GCC_USB4CIO_0_MISC_RESET, HWIO_GCC_USB4CIO_0_MISC_RESET_RMSK);
            USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, g_usb4_mux_delay))
            HWIO_OUT(GCC_USB4PHY_PHY_PRIM_BCR, 1);
            if(g_usb4_full_phy_reset)
            {
                HWIO_OUT(GCC_USB4_DP_PHY_PRIM_BCR, 1);
            }
            USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, g_usb4_hold_delay)) /* HPG Reset */
        }
        else
        {
            HWIO_OUT(GCC_USB4_DP_PHY_PRIM_BCR, 0);
            HWIO_OUT(GCC_USB4PHY_PHY_PRIM_BCR, 0);
            USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, g_usb4_release_delay))
            HWIO_OUT(GCC_USB4CIO_0_MISC_RESET, 0);
            /* Wait for system clock */
            USB4_ASSERT(0 == usb4_timer_Start(&timer))
            while (1 == HWIO_INF(GCC_USB4_SYS_CBCR, CLK_OFF))
            {

            }
            USB4_ASSERT(0 == usb4_timer_GetElapsed_us(&timer, &elapsed_us))
            //USB4_LOG_WARNING("System clock took %lu usec to start\n", elapsed_us);
            Usb4Log1(USB4_LOG_CFG, assertgccrmiscesets__Params__SystemClockCoreXTookuSecToStart, 0, elapsed_us);
        }
    }
    else
    {
        if (TRUE == bAssert)
        {
            HWIO_OUT(GCC_USB4CIO_1_MISC_RESET, HWIO_GCC_USB4CIO_1_MISC_RESET_RMSK);
            USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, g_usb4_mux_delay))
            HWIO_OUT(GCC_USB4PHY_1_PHY_PRIM_BCR, 1);
            if(g_usb4_full_phy_reset)
            {
                HWIO_OUT(GCC_USB4_1_DP_PHY_PRIM_BCR, 1);
            }
            USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, g_usb4_hold_delay)) /* HPG Reset */
        }
        else
        {
            HWIO_OUT(GCC_USB4_1_DP_PHY_PRIM_BCR, 0);
            HWIO_OUT(GCC_USB4PHY_1_PHY_PRIM_BCR, 0);
            USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, g_usb4_release_delay))
            HWIO_OUT(GCC_USB4CIO_1_MISC_RESET, 0);
            /* Wait for system clock */
            USB4_ASSERT(0 == usb4_timer_Start(&timer))
            while (1 == HWIO_INF(GCC_USB4_1_SYS_CBCR, CLK_OFF))
            {

            }
            USB4_ASSERT(0 == usb4_timer_GetElapsed_us(&timer, &elapsed_us))
            //USB4_LOG_WARNING("System clock took %lu usec to start\n", elapsed_us);
            Usb4Log1(USB4_LOG_CFG, assertgccrmiscesets__Params__SystemClockCoreXTookuSecToStart, 0, elapsed_us);
        }
    }
    return 0;
}


static int assert_gcc_resets(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 coreId, UINT32 api_mask, BOOLEAN bAssert)
{
//    const USB4_gcc_map* pClk;
//    eClkResult result;

//    UINTN  ClockId;
//    UINT32 elapsed_us;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;
//    EFI_STATUS Status = EFI_SUCCESS;

    if (usb4_platform_ctx->ClockProtocol == NULL) {
      Usb4Log(USB4_LOG_CFG, AssertGccClks__ErrInvalidParam__ClockProtocol, 0);
      return -1;
    }

//    ares = (TRUE == bAssert) ? eClockReset_ClkAres_Assert:
//                               eClockReset_ClkAres_Deassert;

   switch(api_mask)
   {
       case USB4_GCC_RESET_ALL:
       default:
           return assert_gcc_misc_resets(usb4_platform_ctx, coreId, bAssert);
       case USB4_GCC_WAKE_SPECIFIC_RESET:
           if (0 == coreId)
           {
               if (TRUE == bAssert)
               {
                   HWIO_OUT(GCC_USB4CIO_0_MISC_RESET, HWIO_GCC_USB4CIO_0_MISC_RESET_RMSK);
                   USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, g_usb4_mux_delay)) /* HPG Reset */
               }
               else
               {
                   HWIO_OUT(GCC_USB4CIO_0_MISC_RESET, HWIO_GCC_USB4CIO_0_MISC_RESET_USB4CIO_0_PCIE_PIPE_BCR_BLK_ARES_BMSK);
               }
           }
           else
           {
               if (TRUE == bAssert)
               {
                   HWIO_OUT(GCC_USB4CIO_1_MISC_RESET, HWIO_GCC_USB4CIO_1_MISC_RESET_RMSK);
                   USB4_ASSERT(0 == usb4_timer_Sleep_us(&timer, g_usb4_mux_delay))
               }
               else
               {
                   HWIO_OUT(GCC_USB4CIO_1_MISC_RESET, HWIO_GCC_USB4CIO_0_MISC_RESET_USB4CIO_0_PCIE_PIPE_BCR_BLK_ARES_BMSK);
               }
           }
           break;
        case USB4_GCC_USB3_INIT_SPECIFIC_RESET:
            if (0 == coreId)
            {
                HWIO_OUTF(GCC_USB4CIO_0_MISC_RESET,USB4CIO_0_USB_PIPE_BCR_BLK_ARES, (TRUE == bAssert) ? 1:0);
            }
            else
            {
                HWIO_OUTF(GCC_USB4CIO_1_MISC_RESET,USB4CIO_1_USB_PIPE_BCR_BLK_ARES, (TRUE == bAssert) ? 1:0);
            }
            usb4_timer_Sleep_ms(&timer, 1);
            break;
   }

   // TODO: AC Manually added extra delay for all types of GCC resets to improve reliability
   usb4_timer_Sleep_us(&timer, g_usb4_mux_delay);

#if 0
// Merge the following UEFI Port if code uses ClockReset API above again
        bitfield = (1 << i);
        if (0 != (mask & bitfield))
        {
            pClk = get_clk(coreId, bitfield);
            if (NULL == pClk)
            {
                Usb4Log2(USB4_LOG_CFG, AssertGccClks__Params__Core_CouldNotFindClockForMsk, 0, coreId, bitfield);
                // USB4_LOG_ERROR("Core[%u] could not find clock for msk=0x%02X\n", 
                //               coreId, bitfield);
                return -1;
            }

            Status = usb4_platform_ctx->ClockProtocol->GetClockID(usb4_platform_ctx->ClockProtocol, pClk->clk, &ClockId);
            if (Status != EFI_SUCCESS) {
              Usb4Log(USB4_LOG_CFG, AssertGccClks__Err_Failed_GetClockID__ClockName, 0);
              return -1;
            }
  
            if (bAssert)
            {
                // reset clock.
                Status = usb4_platform_ctx->ClockProtocol->ResetClock(usb4_platform_ctx->ClockProtocol, ClockId, EFI_CLOCK_RESET_ASSERT);
                if (Status != EFI_SUCCESS) {
                  Usb4Log(USB4_LOG_CFG, AssertGccClks__Err_Failed_GccAssert__ClockName, 0);
                  return -1;
                }
            }
            else
            {
                // reset clock.
                Status = usb4_platform_ctx->ClockProtocol->ResetClock(usb4_platform_ctx->ClockProtocol, ClockId, EFI_CLOCK_RESET_DEASSERT);
                if (Status != EFI_SUCCESS) {
                  Usb4Log(USB4_LOG_CFG, AssertGccClks__Err_Failed_GccDeAssert__ClockName, 0);
                  return -1;
                }
            }
            mask &= ~bitfield;
        }
        ++i;
#endif
    return 0;
}
#endif /* USB4_GCC_GENEMU */


/*----------------------------------------------------------------------------
 * Functions
 *-------------------------------------------------------------------------*/
int Usb4GccInit(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 coreIdx, UINT8* coreBaseAddr)
{ 
//    usb4_platform_ctx->m_coreIndex = coreIdx;  // Already initialized by caller
    usb4_platform_ctx->m_pHandler = (void*)coreBaseAddr; // New structure used by gcc_platform
#if !defined(USB4_GCC_GENEMU)
    // No special initialization required, LocateProtocol already invoked in Usb4Platform
    // gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL, (VOID**)&usb4_platform_ctx->ClockProtocol);
#if 0
    UINT32 i;
    USB4_gcc_map* pClk;

    if (0x0 == coreIdx)
    {
        for (i = 0; i < ARR_SIZE(s_usb4_0_gcc_map); ++i)
        {
            pClk = s_usb4_0_gcc_map + i;
            pClk->handle = VVDRV_clk_ClockOpen(pClk->clk);
            if (0x0 == pClk->handle)
            {
                USB4_LOG_ERROR("Failed openning core[%u] clk handle %u: %s\n", 
                               coreIdx, i, pClk->clk);
                USB4_ERROR_STACK(-1);
            }
        }
    }
    
    else if (0x1 == coreIdx)
    {
        for (i = 0; i < ARR_SIZE(s_usb4_1_gcc_map); ++i)
        {
            pClk = s_usb4_1_gcc_map + i;
            pClk->handle = VVDRV_clk_ClockOpen(pClk->clk);
            if (0x0 == pClk->handle)
            {
                USB4_LOG_ERROR("Failed openning core[%u] clk handle %u: %s\n", 
                               coreIdx, i, pClk->clk);
                USB4_ERROR_STACK(-1);
            }
        }
    }
#endif
#endif /* USB4_GCC_GENEMU */

//     m_coreIdx = coreIdx;
//     m_pHandler = static_cast<void*>(coreBaseAddr); 
    return 0;
};

int Usb4GccCoreCollapse(usb4_platform_ctx_t* usb4_platform_ctx, boolean bCollapse)
{
#if defined(ASIC)
    UINT32 elapsed_ms;
    UINT32 sw_collapse;
    UINT32 pw_on;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    sw_collapse = (TRUE == bCollapse)? 1:0;
    pw_on = (TRUE == bCollapse)? 0:1;

    usb4_timer_Start(&timer);
    if (usb4_platform_ctx->m_coreIndex == 0)
    {
         /* Power collapse through GCC GDSCR register */
        HWIO_OUTF(GCC_USB4_GDSCR,SW_COLLAPSE,sw_collapse);//Write into GDSCR
        while(HWIO_INF(GCC_USB4_GDSCR,PWR_ON) != pw_on)//Wait if POWER ON/OFF state is
        {
            if (0 != usb4_timer_GetElapsed_ms(&timer, &elapsed_ms)||(elapsed_ms > 1000))
            {
                return -1;
            }
        }
    }
    else
    {
        /* Power collapse through GCC GDSCR register */
        HWIO_OUTF(GCC_USB4_1_GDSCR,SW_COLLAPSE,sw_collapse);//Write into GDSCR
        while(HWIO_INF(GCC_USB4_1_GDSCR,PWR_ON) != pw_on)//Wait if POWER ON state is
        {
            if (0 != usb4_timer_GetElapsed_ms(&timer, &elapsed_ms)||(elapsed_ms > 1000))
            {
                return -1;
            }
        }
    }
#endif

    return 0;
}

int Usb4GccEnableUSBSleepClk(usb4_platform_ctx_t* usb4_platform_ctx, boolean bEnable)
{
#if defined(ASIC)
  switch(usb4_platform_ctx->m_coreIndex)
  {
   case 0:
       HWIO_OUTF(GCC_USB30_PRIM_SLEEP_CBCR, CLK_ENABLE, bEnable);
    break;

   case 1:
        HWIO_OUTF(GCC_USB30_SEC_SLEEP_CBCR, CLK_ENABLE, bEnable);
    break;

   default:
    break;
  }
#else
    UINT8* base = (UINT8*)(usb4_platform_ctx->m_pHandler) + GE_DUT_USER_REGS_REG_BASE_OFFS;
    HWIO_OUTX(base, GE_DUT_USB31_CTRL_REG, (bEnable<<4) | bEnable); // Gate pipe + sleep_clk
#endif /* ASIC */

  return 0;
}

int Usb4GccConfigureUSB3toUSB4mode(usb4_platform_ctx_t* usb4_platform_ctx)
{

#ifndef USB4_COMPILING_GEN_EMU
  switch(usb4_platform_ctx->m_coreIndex)
  {
   case 0:
        HWIO_OUT(TCSR_USB4_MODE_REG, 0x3); /* configure USB PRIM controller in USB4 tunneled mode */
        HWIO_OUTF(GCC_USB4_PHY_USB_PIPE_CBCR, HW_CTL, 0);
    break;

   case 1:
        HWIO_OUT(TCSR_USB4_MODE_REG, 0x3); /* configure USB SEC controller in USB4 tunneled mode */
        HWIO_OUTF(GCC_USB4_1_PHY_USB_PIPE_CBCR, HW_CTL, 0);
    break;

   default:
    break;
  }
#endif /* USB4_COMPILING_GEN_EMU */

  return 0;
}

int Usb4GccEnableClocks(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 api_mask, BOOLEAN bEnable)
{

#if defined(USB4_GCC_GENEMU)
    (void) api_mask;
    (void) bEnable;
#else /* USB4_GCC_GENEMU */
    const USB4_gcc_map* pClk;
    UINT32 bitfield;
    UINT32 i = 0;
//    eClkResult result;
    UINT32 mask;
    UINTN  ClockId;
    UINT32 Freq;
    UINT32 FreqHz; // Return value from clock API
    EFI_STATUS Status = EFI_SUCCESS;

// TODO: AC port to ClockProtocol
    /* This is a temporary code until proper driver calls can be used */
    //per.set.field ezaxi:0x10F054 %long 0x1 0x1 ; Enable GCC_USB3_PRIM_PHY_AUX_CBCR
    HWIO_OUTF(GCC_USB3_PRIM_PHY_AUX_CBCR, CLK_ENABLE, bEnable?1:0);
    //per.set.field ezaxi:0x110054 %long 0x1 0x1 ; Enable GCC_USB3_SEC_PHY_AUX_CBCR
    HWIO_OUTF(GCC_USB3_SEC_PHY_AUX_CBCR, CLK_ENABLE, bEnable?1:0);

// UEFI USB4 addition, need extra enablement of gcc_usb3_prim_phy_pipe_clk, but do not turn off to not afffect USB3 operation
    if (1 == bEnable)
    {
      HWIO_OUTF(GCC_USB3_PRIM_PHY_PIPE_CBCR, CLK_ENABLE, 1);
    }

    //per.set.field ezaxi:0x15D024 %long 0x1 0x1 ; Enable GCC_AGGRE_USB_NOC_AXI_CBCR
    HWIO_OUTF(GCC_AGGRE_USB_NOC_AXI_CBCR, CLK_ENABLE, bEnable?1:0);
    //per.set.field ezaxi:0x15D020 %long 0x1 0x1 ; Enable GCC_AGGRE_USB_NOC_NORTH_AXI_CBCR
    HWIO_OUTF(GCC_AGGRE_USB_NOC_NORTH_AXI_CBCR, CLK_ENABLE, bEnable?1:0);
    //per.set.field ezaxi:0x15D01C %long 0x1 0x1 ; Enable GCC_AGGRE_USB_NOC_SOUTH_AXI_CBCR
    HWIO_OUTF(GCC_AGGRE_USB_NOC_SOUTH_AXI_CBCR, CLK_ENABLE, bEnable?1:0);

#if 0 // TODO: AC port to ClockProtocol
    //per.set.field ezaxi:0x104138 %long 0x1 0x1 ; Enable GCC_SYS_NOC_AXI_CBCR
    HWIO_OUTF(GCC_SYS_NOC_AXI_CBCR, CLK_ENABLE, bEnable?1:0);
#endif
    //per.set.field ezaxi:0x15D000 %long 0x1 0x1 ; Enable GCC_SYS_NOC_USB_AXI_CBCR
    HWIO_OUTF(GCC_SYS_NOC_USB_AXI_CBCR, CLK_ENABLE, bEnable?1:0);

    // Manually ported, this is not automatically provided by platform
    HWIO_OUTF(GCC_USB4_CFG_AHB_CBCR, HW_CTL, 0x1);
    HWIO_OUTF(GCC_USB4_1_CFG_AHB_CBCR, HW_CTL, 0x1);
    // HWIO_OUTF(GCC_APCS_CLOCK_BRANCH_ENA_VOTE_4, USB4_PHY_PCIE_PIPE_CLK_ENA, enable); // done as part of pcie_pipe_clk, 0x152020 core 0 = bit 18, core 1 = bit 19

    
    // make sure only supported clocks are asserted
    mask = (api_mask & USB4_GCC_PLATFORM_CLK_ALL);
    
    while (0x0 != mask)
    {
      bitfield = (1 << i);
      if (0x0 != (bitfield & mask))
      {
          pClk = get_clk(usb4_platform_ctx->m_coreIndex, bitfield);
          if (NULL == pClk)
          {
              Usb4Log2(USB4_LOG_CFG, Usb4GccEnableClocks__Params__Core_CouldNotFindClockForMsk, 0, usb4_platform_ctx->m_coreIndex, bitfield);
              // USB4_LOG_ERROR("Core[%u] EnableClocks could not find clock for msk=0x%02X\n", 
              //               , bitfield);
              USB4_ERROR_STACK(-1);
              return -1;
          }
          // Get clock ID.
          Status = usb4_platform_ctx->ClockProtocol->GetClockID(usb4_platform_ctx->ClockProtocol, pClk->clk, &ClockId);
          if (Status != EFI_SUCCESS) {
            Usb4Log2(USB4_LOG_CFG, Usb4ClkEnable__Err_Failed_GetClockID__ClockName_HrIdx, 0, (UINT64) pClk->clk, usb4_platform_ctx->m_coreIndex);
            USB4_ERROR_STACK(-1);
            return -1;
          }

          Freq = pClk->Freq;
          if (Freq) {
            Status = usb4_platform_ctx->ClockProtocol->SetClockFreqHz(usb4_platform_ctx->ClockProtocol, ClockId, Freq, EFI_CLOCK_FREQUENCY_HZ_AT_LEAST, 
                &FreqHz);
            if (Status != EFI_SUCCESS) {
              Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__Err_Failed_SetClockFreqHz__ClockName_ClockId_Freq, 0, (UINT32)pClk->clk, 
                  ClockId, Freq);
            }
            else {
              Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__SetClockFreqHz__ClockName_ClockId_Freq, 0, (UINT32)pClk->clk, 
                  ClockId, FreqHz);
            }
          }

          // Enable clock.
          Status = usb4_platform_ctx->ClockProtocol->EnableClock(usb4_platform_ctx->ClockProtocol, ClockId);
          if (Status != EFI_SUCCESS) {
            Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__Err_Failed_EnableClock__ClockName_ClockId_Freq, 0, (UINT32)pClk->clk, 
                ClockId, Freq);
            USB4_ERROR_STACK(-1);
            return -1;
          }

          if (pClk->Div > 1 ) {
            Status = usb4_platform_ctx->ClockProtocol->SetClockDivider(usb4_platform_ctx->ClockProtocol, ClockId, pClk->Div);
            if (Status != EFI_SUCCESS) {
              Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__Err_Failed_SetClockDivider__ClockName_ClockId_Div, 0, (UINT32)pClk->clk, 
                  ClockId, pClk->Div);  
            }
          }
          Usb4Log2(USB4_LOG_CFG, Usb4GccEnableClocks__Params__Core_BitField, 0, usb4_platform_ctx->m_coreIndex, bitfield);

          mask &= ~bitfield;
        }
        ++i;
    }

#endif /* USB4_GCC_GENEMU */
    return 0;
}


int Usb4GccAssertReset(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 mask)
{
#if defined(USB4_GCC_GENEMU)
    UINT8* base = 
        (UINT8*)(usb4_platform_ctx->m_pHandler) + GE_DUT_USER_REGS_REG_BASE_OFFS;
    UINT32 reset_mask = 0;
    UINT32 rval = 0x0;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    if (0 != get_fmask(mask, &reset_mask))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }

    // Read reset register value
    rval = HWIO_INX(base, GE_DUT_RESET_REG);
    
    // Append reset mask
    rval |= reset_mask;
    
    // Assert the reset register
    HWIO_OUTX(base, GE_DUT_RESET_REG , rval);
    
    if (0 != usb4_timer_Sleep_ms(&timer, 10))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    return 0;

#else /* !USB4_GCC_GENEMU */
    if (0 != assert_gcc_resets(usb4_platform_ctx, usb4_platform_ctx->m_coreIndex, mask, TRUE))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    
    return 0;
    
#endif /* USB4_GCC_GENEMU */
};

int Usb4GccDeAssertReset(usb4_platform_ctx_t* usb4_platform_ctx, UINT32 mask)
{
#if defined(USB4_GCC_GENEMU)
    UINT8* base = 
        (UINT8*)(usb4_platform_ctx->m_pHandler) + GE_DUT_USER_REGS_REG_BASE_OFFS;
    UINT32 reset_mask = 0;
    UINT32 rval = 0x0;
    usb4_utils_timer timer;
    timer.m_source = USB4_TIMER_SOURCE_QTIMER;

    if (0 != get_fmask(mask, &reset_mask))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    // Read reset register value
    rval = HWIO_INX(base, GE_DUT_RESET_REG);
    
    // Clear the de-assert reset bits from register val
    rval &= ~reset_mask;
    
    // Write the new value
    HWIO_OUTX(base, GE_DUT_RESET_REG , rval);

    if (0 != usb4_timer_Sleep_ms(&timer, 10)) /* Needed reset de-assertion to propagate */
    {
      USB4_ERROR_STACK(-1);
      return -1;
    }
    
    return 0;

#else /* !USB4_GCC_GENEMU */
    if (0 != assert_gcc_resets(usb4_platform_ctx, usb4_platform_ctx->m_coreIndex, mask, FALSE))
    {
        USB4_ERROR_STACK(-1);
        return -1;
    }
    return 0;
#endif /* USB4_GCC_GENEMU */
};


int Usb4GccConfigureGccMUXs(usb4_platform_ctx_t* usb4_platform_ctx, uint32 muxVal)
{
#ifndef USB4_GCC_GENEMU
//    int rc = 0;


    switch (usb4_platform_ctx->m_coreIndex)
    {
        case 0:

            if (muxVal != HWIO_INF(GCC_USB4_PHY_RX0_MUXR, MUX_SEL))
            {
                HWIO_OUTF(GCC_USB4_PHY_RX0_CBCR, CLK_ENABLE, 0);
                HWIO_OUTF(GCC_USB4_PHY_RX1_CBCR, CLK_ENABLE, 0);

                HWIO_OUTF(GCC_USB4_PHY_RX0_MUXR, MUX_SEL, muxVal);
                HWIO_OUTF(GCC_USB4_PHY_RX1_MUXR, MUX_SEL, muxVal);

                if (0 == muxVal)
                {
                    HWIO_OUTF(GCC_USB4_PHY_RX0_CBCR, CLK_ENABLE, 1);
                    HWIO_OUTF(GCC_USB4_PHY_RX1_CBCR, CLK_ENABLE, 1);
                }
            }
            break;

        case 1:
            if (muxVal != HWIO_INF(GCC_USB4_1_PHY_RX0_MUXR, MUX_SEL))
            {
                HWIO_OUTF(GCC_USB4_1_PHY_RX0_CBCR, CLK_ENABLE, 0);
                HWIO_OUTF(GCC_USB4_1_PHY_RX1_CBCR, CLK_ENABLE, 0);

                HWIO_OUTF(GCC_USB4_1_PHY_RX0_MUXR, MUX_SEL, muxVal);
                HWIO_OUTF(GCC_USB4_1_PHY_RX1_MUXR, MUX_SEL, muxVal);

                if (0 == muxVal)
                {
                    HWIO_OUTF(GCC_USB4_1_PHY_RX0_CBCR, CLK_ENABLE, 1);
                    HWIO_OUTF(GCC_USB4_1_PHY_RX1_CBCR, CLK_ENABLE, 1);
                }
            }
            break;

        default:
            break;
    }
    return 0;
#else
    return 0;
#endif
}


// This is needed for HLOS
EFI_STATUS
Usb4PlatformConfigPowerDomain(
  IN usb4_platform_ctx_t* usb4_platform_ctx,
  IN BOOLEAN Enable,
  IN CONST CHAR8 *DomainStr
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN ClockPowerDomainId;
#if defined(USB4_GCC_GENEMU)
#else /* !USB4_GCC_GENEMU */

  if (usb4_platform_ctx && usb4_platform_ctx->ClockProtocol) {
      Status = usb4_platform_ctx->ClockProtocol->GetClockPowerDomainID(usb4_platform_ctx->ClockProtocol, DomainStr, &ClockPowerDomainId);
      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "Usb4PlatformConfigPowerDomain: Failed to GetClockPowerDomainID\n"));
        return EFI_ABORTED;
      }

      if (Enable) {
        Status =  usb4_platform_ctx->ClockProtocol->EnableClockPowerDomain(usb4_platform_ctx->ClockProtocol, ClockPowerDomainId);
      }
      else {
        Status =  usb4_platform_ctx->ClockProtocol->DisableClockPowerDomain(usb4_platform_ctx->ClockProtocol, ClockPowerDomainId);
      }

      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "Usb4PlatformConfigPowerDomain: ClockPowerDomain API Failed. Enable %d , Status %x\n", 
          Enable, Status));
        return EFI_ABORTED;
      }      
  }
  else {
    DEBUG ((EFI_D_ERROR, "Usb4PlatformConfigPowerDomain: Failed to register clock protocol\n"));
  }
#endif /* USB4_GCC_GENEMU */
  return Status;
}




// +++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++
// +++++++++++++++++++++++++++++++++

#if 0 // +++Previous UEFI

EFI_STATUS
Usb4ClkEnable (
  IN USB4_CONFIG_PROTOCOL* This,
  IN CONST CHAR8* ClockName,
  IN UINT32 Freq,
  IN UINT32 Div
  )
{
  // Initialize locals.
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       ClockId;
  UINT32      FreqHz;

  if (This == NULL)
  {
    Usb4Log1(USB4_LOG_CFG, Usb4Platform__Err_NullPtr__line, 0, __LINE__);
    return EFI_INVALID_PARAMETER;
  }
  if ((This->ClockProtocol == NULL) || (ClockName == NULL)){
    Usb4Log2(USB4_LOG_CFG, Usb4ClkEnable__Err_Invalid_Param__ClockProtocol_ClockName, 0, 
      (UINT32)This->ClockProtocol, (UINT32)ClockName);
    return EFI_INVALID_PARAMETER;
  }

  Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__Params__ClockName_Freq_Div, 0, (UINT64) ClockName, Freq, Div);
  
  // Get clock ID.
  Status = This->ClockProtocol->GetClockID (This->ClockProtocol, ClockName, &ClockId);
  if (Status != EFI_SUCCESS) {
    Usb4Log2(USB4_LOG_CFG, Usb4ClkEnable__Err_Failed_GetClockID__ClockName_HrIdx, 0, (UINT64) ClockName, This->HrIdx);
    return EFI_ABORTED;
  }

  if (Freq) {
    Status = This->ClockProtocol->SetClockFreqHz(This->ClockProtocol, ClockId, Freq, EFI_CLOCK_FREQUENCY_HZ_AT_LEAST, 
      &FreqHz);
    if (Status != EFI_SUCCESS) {
      Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__Err_Failed_SetClockFreqHz__ClockName_ClockId_Freq, 0, (UINT32)ClockName, 
        ClockId, Freq);
    }
    else {
      Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__SetClockFreqHz__ClockName_ClockId_Freq, 0, (UINT32)ClockName, 
        ClockId, FreqHz);
    }
  }

  // Enable clock.
  Status = This->ClockProtocol->EnableClock(This->ClockProtocol, ClockId);
  if (Status != EFI_SUCCESS) {
    Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__Err_Failed_EnableClock__ClockName_ClockId_Freq, 0, (UINT32)ClockName, 
      ClockId, Freq);
    return EFI_ABORTED;
  }

  if (Div > 1 ) {
    Status = This->ClockProtocol->SetClockDivider(This->ClockProtocol, ClockId, Div);
    if (Status != EFI_SUCCESS) {
      Usb4Log3(USB4_LOG_CFG, Usb4ClkEnable__Err_Failed_SetClockDivider__ClockName_ClockId_Div, 0, (UINT32)ClockName, 
        ClockId, Div);  
    }
  }

  return Status;
}


/**
  Disables specified clock.

  @param  ClockName              Clock name as specified in
                                 QcomPkg/Application/ClockApp/ClockTestData.c.

  @retval EFI_SUCCESS            Clock is enabled.
  @retval EFI_INVALID_PARAMETER  One or more arguments has an unsupported value.
  @retval EFI_DEVICE_ERROR       Clock is not on.
  @retval EFI_PROTOCOL_ERROR     Unable to get clock ID.

**/
EFI_STATUS
Usb4ClkDisable (
  IN USB4_CONFIG_PROTOCOL* This,
  IN CONST CHAR8* ClockName
  )
{
  // Initialize locals.
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN ClockId;
  if (This == NULL)
  {
    Usb4Log1(USB4_LOG_CFG, Usb4Platform__Err_NullPtr__line, 0, __LINE__);
    return EFI_INVALID_PARAMETER;
  }

  if ((This->ClockProtocol == NULL) || (ClockName == NULL)){
    Usb4Log2(USB4_LOG_CFG, Usb4ClkDisable__Err_Invalid_Param__ClockProtocol_ClockName, 0,  
      (UINT32)This->ClockProtocol, (UINT32)ClockName);
    return EFI_INVALID_PARAMETER;
  }

  // Get clock ID.
  Status = This->ClockProtocol->GetClockID(This->ClockProtocol, ClockName, &ClockId);
  if (Status != EFI_SUCCESS) {
    Usb4Log2(USB4_LOG_CFG, Usb4ClkDisable__Err_Failed_GetClockID__ClockName_HrIdx, 0, (UINT64) ClockName, This->HrIdx);
    return EFI_ABORTED;
  }

  // Disable clock.
  Status = This->ClockProtocol->DisableClock (This->ClockProtocol, ClockId);
  if (Status != EFI_SUCCESS) {
    Usb4Log2(USB4_LOG_CFG, Usb4ClkDisable__Err_Failed_EnableClock__ClockName_ClockId, 0, (UINT32)ClockName, ClockId);
    return EFI_ABORTED;
  }

  return Status;
}

EFI_STATUS
EFIAPI
Usb4ClkReset (
  IN USB4_CONFIG_PROTOCOL*  This,
  IN CONST CHAR8*           ClockName,
  IN EFI_CLOCK_RESET_TYPE   AssertFlag
  )
{
  // Initialize locals.
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       ClockId;

  if (This == NULL)
  {
    Usb4Log1(USB4_LOG_CFG, Usb4Platform__Err_NullPtr__line, 0, __LINE__);
    return EFI_INVALID_PARAMETER;
  }
  if ((This->ClockProtocol == NULL) || (ClockName == NULL)){
    Usb4Log2(USB4_LOG_CFG, Usb4ClkReset__Err_Invalid_Param__ClockProtocol_ClockName, 0, 
      (UINT32)This->ClockProtocol, (UINT32)ClockName);
    return EFI_INVALID_PARAMETER;
  }

  // Get clock ID.
  Status = This->ClockProtocol->GetClockID(This->ClockProtocol, ClockName, &ClockId);
  if (Status != EFI_SUCCESS) {
    Usb4Log2(USB4_LOG_CFG, Usb4ClkReset__Err_Failed_GetClockID__ClockName_HrIdx, 0, (UINT64) ClockName, This->HrIdx);
    return EFI_ABORTED;
  }

  // Reset clock.
  Status = This->ClockProtocol->ResetClock(This->ClockProtocol, ClockId, AssertFlag);
  if (Status != EFI_SUCCESS) {
    Usb4Log2(USB4_LOG_CFG, Usb4ClkReset__Err_Failed_ResetClock__ClockName_ClockId, 0, (UINT32)ClockName, ClockId);
    return EFI_ABORTED;
  }

  return Status;
}


EFI_STATUS
Usb4PlatformClkInit (
  IN USB4_CONFIG_PROTOCOL*  This,
  IN UINTN                  ClockCount,
  IN USB4_CLK*              Clocks
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINTN       ClkIdx;

  // Validate parameters
  if (This == NULL)
  {
    Usb4Log1(USB4_LOG_CFG, Usb4Platform__Err_NullPtr__line, 0, __LINE__);
    return EFI_INVALID_PARAMETER;
  }
  if ((This->ClockProtocol == NULL) || (ClockCount == 0) || (Clocks == NULL)){
    Usb4Log3(USB4_LOG_CFG, Usb4PlatformClkInit__Err_Invalid_Param__ClockProtocol_Clocks_Count, 0, 
      (UINT32)This->ClockProtocol, (UINT16)Clocks, ClockCount);
    return EFI_INVALID_PARAMETER;
  }

  Usb4Log4(USB4_LOG_CFG, Usb4PlatformClkInit__Params__HrIdx_ClockProtocol_Clocks_Count, 0, This->HrIdx, 
    (UINT32)This->ClockProtocol, (UINT16)Clocks, ClockCount);


  // Enable each clock
  for (ClkIdx = 0; ClkIdx < ClockCount; ClkIdx++) {
    Status = Usb4ClkEnable(This, Clocks[ClkIdx].Name, Clocks[ClkIdx].Freq, Clocks[ClkIdx].Div);
    if (Status != EFI_SUCCESS) {
      Usb4Log1(USB4_LOG_CFG, Usb4PlatformClkInit__Err_Failed_ClkEnable__ClockName, 0, (UINT64)Clocks[ClkIdx].Name);
    }    
  }

  return Status;
} // end InitUsbClocks


EFI_STATUS
Usb4PlatformClkUnInit (
  IN USB4_CONFIG_PROTOCOL*  This,
  IN UINTN                  ClockCount,
  IN USB4_CLK*              Clocks
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;
  UINTN       ClkIdx;

  // Validate Params
  if (This == NULL)
  {
    Usb4Log1(USB4_LOG_CFG, Usb4Platform__Err_NullPtr__line, 0, __LINE__);
    return EFI_INVALID_PARAMETER;
  }
  if ((This->ClockProtocol == NULL) || (ClockCount == 0) || (Clocks == NULL)){
    Usb4Log3(USB4_LOG_CFG, Usb4PlatformClkUnInit__Err_Invalid_Param__ClockProtocol_Clocks_Count, 0,
      (UINT32)This->ClockProtocol, (UINT16)Clocks, ClockCount);
    return EFI_INVALID_PARAMETER;
  }

  Usb4Log4(USB4_LOG_CFG, Usb4PlatformClkUnInit__Params__HrIdx_ClockProtocol_Clocks_Count, 0, This->HrIdx, 
    (UINT32)This->ClockProtocol, (UINT16)Clocks, ClockCount);

  // Disable clocks
  for (ClkIdx = 0; ClkIdx < ClockCount; ClkIdx++) {
    Status = Usb4ClkDisable(This, Clocks[ClkIdx].Name);
    if (Status != EFI_SUCCESS) {
      Usb4Log1(USB4_LOG_CFG, Usb4PlatformClkUnInit__Err_Failed_ClkDisable__ClockName, 0, (UINT64)Clocks[ClkIdx].Name);
      return EFI_ABORTED;
    }
  }

  return Status;
}


// This is needed for HLOS
EFI_STATUS
Usb4PlatformConfigPowerDomain(
  IN USB4_CONFIG_PROTOCOL*  This,
  IN BOOLEAN Enable,
  IN CONST CHAR8 *DomainStr
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINTN ClockPowerDomainId;

  if (This && This->ClockProtocol) {
      Status = This->ClockProtocol->GetClockPowerDomainID(This->ClockProtocol, DomainStr, &ClockPowerDomainId);
      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "Usb4PlatformConfigPowerDomain: Failed to GetClockPowerDomainID\n"));
        return EFI_ABORTED;
      }

      if (Enable) {
        Status =  This->ClockProtocol->EnableClockPowerDomain(This->ClockProtocol, ClockPowerDomainId);
      }
      else {
        Status =  This->ClockProtocol->DisableClockPowerDomain(This->ClockProtocol, ClockPowerDomainId);
      }

      if (Status != EFI_SUCCESS) {
        DEBUG ((EFI_D_ERROR, "Usb4PlatformConfigPowerDomain: ClockPowerDomain API Failed. Enable %d , Status %x\n", 
          Enable, Status));
        return EFI_ABORTED;
      }      
  }
  else {
    DEBUG ((EFI_D_ERROR, "Usb4PlatformConfigPowerDomain: Failed to register clock protocol\n"));
  }

  return Status;
}

VOID
Usb4PlatformGccAssertReset(
  IN USB4_CONFIG_PROTOCOL*  This,
  IN UINTN                  ClockCount,
  IN USB4_CLK*              Clocks  
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       ClockId;
  UINTN       ClockIdx;

  Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccAssertReset__Entry__ConfigProtocol, 0, (UINT64)This);

  if (This == NULL)
  {
    Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccAssertReset__ErrNullPtr__line, 0, __LINE__);
    return;
  }
  if (This->ClockProtocol == NULL) {
    Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccAssertReset__ErrInvalidParam__ClockProtocol, 0, 
      (UINT32)This->ClockProtocol);
    return;
  }

  for (ClockIdx = 0; ClockIdx < ClockCount; ClockIdx++) {
    Status = This->ClockProtocol->GetClockID(This->ClockProtocol, Clocks[ClockIdx].Name, &ClockId);
    if (Status != EFI_SUCCESS) {
      Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccAssertReset__Err_Failed_GetClockID__ClockName, 0, (UINT64)Clocks[ClockIdx].Name);
      return;
    }

    // reset clock.
    Status = This->ClockProtocol->ResetClock(This->ClockProtocol, ClockId, EFI_CLOCK_RESET_ASSERT);
    if (Status != EFI_SUCCESS) {
      Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccAssertReset__Err_Failed_GccAssert__ClockName, 0, (UINT64)Clocks[ClockIdx].Name);
      return;
    }
  }
}

VOID
Usb4PlatformGccDeAssertReset (
  IN USB4_CONFIG_PROTOCOL*  This,
  IN UINTN                  ClockCount,
  IN USB4_CLK*              Clocks
  )
{
  EFI_STATUS  Status  =  EFI_SUCCESS;
  UINTN       ClockId;
  UINTN       ClockIdx;

  Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccDeAssertReset__Entry__ConfigProtocol, 0, (UINT64) This);

  if (This == NULL)
  {
    Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccDeAssertReset__ErrNullPtr__line, 0, __LINE__);
    return;
  }
  if (This->ClockProtocol == NULL) {
    Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccDeAssertReset__ErrInvalidParam__ClockProtocol, 0, 
      (UINT32)This->ClockProtocol);
    return;
  }

  for (ClockIdx = 0; ClockIdx < ClockCount; ClockIdx++) {
    Status = This->ClockProtocol->GetClockID(This->ClockProtocol, Clocks[ClockIdx].Name, &ClockId);
    if (Status != EFI_SUCCESS) {
      Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccDeAssertReset__Err_Failed_GetClockID__ClockName, 0, (UINT64)Clocks[ClockIdx].Name);
      return;
    }

    // reset clock.
    Status = This->ClockProtocol->ResetClock(This->ClockProtocol, ClockId, EFI_CLOCK_RESET_DEASSERT);
    if (Status != EFI_SUCCESS) {
      Usb4Log1(USB4_LOG_CFG, Usb4PlatformGccDeAssertReset__Err_Failed_GccDeAssert__ClockName, 0, (UINT64)Clocks[ClockIdx].Name);
      return;
    }
  }
}

#endif // ---Previous UEFI
