/**---------------------------------------------------------------------------
 *
 *  @file  :  usb4_platform_target_gpio.c
 *
 *
 *  @brief :  usb4 platform implementation with relation to GPIO
 *
 *   Copyright (c) 2018-2020 Qualcomm Technologies Incorporated.
 *   All Rights Reserved.
 *   Qualcomm Confidential and Proprietary
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Includes
 *--------------------------------------------------------------------------*/
#include <Uefi.h>
#include "usb4_platform_target.h"
// #include "VVHAL_usb4_logger.h"   // Logging utilities
// #include "VVHAL_usb4_utils.h"
// #include <new>
// #include <cstring>
// #include "VVHAL_usb4_platform_defs.h"
// 
// #include "VVHAL_usb4_hwio.h"
// #include "VVHAL_usb4_hwioreg_core.h"

#if !defined(USB4_PLATFORM_GPIO_TLMM)
    #if defined(ASIC)
        #define USB4_PLATFORM_GPIO_TLMM
    #endif /* ASIC */
#endif /* !USB4_PLATFORM_GPIO_TLMM */


#if defined(USB4_PLATFORM_GPIO_TLMM)
//    #include "msmhwio_tlmm.h"
#include <Protocol/EFITlmm.h>
    
// ++++++++++++ HWIO implementation
#ifdef USB4_ASIC_HWIO
    #define USB4_GPIO_CFG_REG(core, signal)  CFG##core##_##signal
    #define USB4_GPIO_IN_OUT_REG(core, signal)  IN_OUT##core##_##signal
    
    #define CFG1_SBRX         TLMM_GPIO_CFG53
    #define CFG1_SBTX         TLMM_GPIO_CFG52
    #define CFG1_SBTX_DIR_OUT TLMM_GPIO_CFG51
    #define CFG1_SBU_MODE     TLMM_GPIO_CFG50
    #define CFG1_CC_DIR       TLMM_GPIO_CFG49
    #define CFG1_SBU_SW_OE_N  TLMM_GPIO_CFG48
    #define CFG1_SBU_SW_SEL   TLMM_GPIO_CFG47
    
    #define CFG0_SBRX         TLMM_GPIO_CFG170
    #define CFG0_SBTX         TLMM_GPIO_CFG169
    #define CFG0_SBTX_DIR_OUT TLMM_GPIO_CFG168
    #define CFG0_SBU_MODE     TLMM_GPIO_CFG167
    #define CFG0_CC_DIR       TLMM_GPIO_CFG166
    #define CFG0_SBU_SW_OE_N  TLMM_GPIO_CFG165
    #define CFG0_SBU_SW_SEL   TLMM_GPIO_CFG164
    
    #define IN_OUT1_SBRX         TLMM_GPIO_IN_OUT53
    #define IN_OUT1_SBTX         TLMM_GPIO_IN_OUT52
    #define IN_OUT1_SBTX_DIR_OUT TLMM_GPIO_IN_OUT51
    #define IN_OUT1_SBU_MODE     TLMM_GPIO_IN_OUT50
    #define IN_OUT1_CC_DIR       TLMM_GPIO_IN_OUT49
    #define IN_OUT1_SBU_SW_OE_N  TLMM_GPIO_IN_OUT48
    #define IN_OUT1_SBU_SW_SEL   TLMM_GPIO_IN_OUT47
    
    #define IN_OUT0_SBRX         TLMM_GPIO_IN_OUT170
    #define IN_OUT0_SBTX         TLMM_GPIO_IN_OUT169
    #define IN_OUT0_SBTX_DIR_OUT TLMM_GPIO_IN_OUT168
    #define IN_OUT0_SBU_MODE     TLMM_GPIO_IN_OUT167
    #define IN_OUT0_CC_DIR       TLMM_GPIO_IN_OUT166
    #define IN_OUT0_SBU_SW_OE_N  TLMM_GPIO_IN_OUT165
    #define IN_OUT0_SBU_SW_SEL   TLMM_GPIO_IN_OUT164
// ------------ HWIO implementation
#else // ~USB4_ASIC_HWIO
// ++++++++++++ UEFI TLMM implementation
    #define CFG1_SBRX         53
    #define CFG1_SBTX         52
    #define CFG1_SBTX_DIR_OUT 51
    #define CFG1_SBU_MODE     50
    #define CFG1_CC_DIR       49
    #define CFG1_SBU_SW_OE_N  48
    #define CFG1_SBU_SW_SEL   47
    
    #define CFG0_SBRX         170
    #define CFG0_SBTX         169
    #define CFG0_SBTX_DIR_OUT 168
    #define CFG0_SBU_MODE     167
    #define CFG0_CC_DIR       166
    #define CFG0_SBU_SW_OE_N  165
    #define CFG0_SBU_SW_SEL   164
    
    #define IN_OUT1_SBRX         53
    #define IN_OUT1_SBTX         52
    #define IN_OUT1_SBTX_DIR_OUT 51
    #define IN_OUT1_SBU_MODE     50
    #define IN_OUT1_CC_DIR       49
    #define IN_OUT1_SBU_SW_OE_N  48
    #define IN_OUT1_SBU_SW_SEL   47
    
    #define IN_OUT0_SBRX         170
    #define IN_OUT0_SBTX         169
    #define IN_OUT0_SBTX_DIR_OUT 168
    #define IN_OUT0_SBU_MODE     167
    #define IN_OUT0_CC_DIR       166
    #define IN_OUT0_SBU_SW_OE_N  165
    #define IN_OUT0_SBU_SW_SEL   164
#endif // ~USB4_ASIC_HWIO
// ------------ UEFI TLMM implementation


#else /* USB4_PLATFORM_GPIO_TLMM */
    #include "VVHAL_usb4_platform_copss.h"
#endif /* USB4_PLATFORM_GPIO_TLMM */


/*----------------------------------------------------------------------------
 * Macros and definitions
 *--------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
* Global variables
*--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Static local functions
 *--------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Functions implementation for USB4_COMPILING_GEN_EMU
 *--------------------------------------------------------------------------*/

#if !defined(USB4_PLATFORM_GPIO_TLMM)
int Usb4PlatformSideBandConfigure(usb4_platform_ctx_t* usb4_platform_ctx, boolean bSwap)
{
    return 0;
}

int Usb4PlatformSideBandRxControl(usb4_platform_ctx_t* usb4_platform_ctx, USB4_platform_sb_ctrl gpioCtrl)
{
    uint32 oe = 0x0;
    uint32 out = 0x0;
    uint32 gpio_func = 0x0;
    uint8* pUserRegsBase;
    
    switch (gpioCtrl)
    {
        case USB4_platform_sb_ctrl_sw_pulldown:
            oe = 0x1;
            out = 0x0; //pulldown
            gpio_func = 0x0; // sw
            break;
        case USB4_platform_sb_ctrl_sw_pullup:
            oe = 0x1;
            out = 0x1; //pullup
            gpio_func = 0x0; // sw
            break;
        case USB4_platform_sb_ctrl_sw_nopull:
            oe = 0x1;
            out = 0x0; //pulldown
            gpio_func = 0x0;  // sw
            break;
        case USB4_platform_sb_ctrl_hw_ctrl:
            oe = 0x0;
            out = 0x0;
            gpio_func = 0x1;  // hw/fw
            break;
        default:
            USB4_ERROR_STACK_MSG(-1, "Unsupported sb ctrl");
            return -1;
    }

    pUserRegsBase = usb4_platform_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS;
    HWIO_OUTXF3(pUserRegsBase, GE_DUT_USB4_CTRL_REG,
                SBRX_GPIO_OUT, SBRX_GPIO_FUNC_SEL, SBRX_GPIO_OE,
                out, gpio_func, oe);
    return 0;
}

int Usb4PlatformSideBandTxControl(usb4_platform_ctx_t* usb4_platform_ctx, USB4_platform_sb_ctrl gpioCtrl)
{
    uint32 oe = 0x0;
    uint32 sbtx_value = 0x0;
    uint32 gpio_func = 0x0;
    uint8* pUserRegsBase;

    switch (gpioCtrl)
    {
        case USB4_platform_sb_ctrl_sw_pulldown:
            oe = 0x1;
            sbtx_value = 0x0; //pulldown
            gpio_func = 0x0; // sw
            break;
        case USB4_platform_sb_ctrl_sw_pullup:
            oe = 0x1;
            sbtx_value = 0x1; //pullup
            gpio_func = 0x0; // sw
            break;
        case USB4_platform_sb_ctrl_sw_nopull:
            oe = 0x1;
            sbtx_value = 0x0; //pulldown
            gpio_func = 0x0;  // sw
            break;
        case USB4_platform_sb_ctrl_hw_ctrl:
            oe = 0x0;
            sbtx_value = 0x0; //pulldown
            gpio_func = 0x1;  // hw/fw
            break;
        default:
            USB4_ERROR_STACK_MSG(-1, "Unsupported sb ctrl");
            return -1;
    }

    pUserRegsBase = usb4_platform_ctx->m_coreBaseAddress + GE_DUT_USER_REGS_REG_BASE_OFFS;
    HWIO_OUTXF3(pUserRegsBase, GE_DUT_USB4_CTRL_REG,
                SBTX_GPIO_OUT, SBTX_GPIO_FUNC_SEL, SBTX_GPIO_OE,
                sbtx_value, gpio_func, oe);
    return 0;
}
#else /* USB4_PLATFORM_GPIO_TLMM */

#if defined(RUMI) /* && USB4_PLATFORM_GPIO_TLMM */
int Usb4PlatformSideBandConfigure(usb4_platform_ctx_t* usb4_platform_ctx, boolean bSwap)
{
    return 0;
}

int Usb4PlatformSideBandRxControl(usb4_platform_ctx_t* usb4_platform_ctx, USB4_platform_sb_ctrl gpioCtrl)
{
    uint32 oe = 0x0;
    uint32 pull = 0x0;
    uint32 gpio_func = 0x0;

    /* O - no pull,
     * 1 - pull down
     * 3 - pull up
     */
    switch (gpioCtrl)
    {
        case USB4_platform_sb_ctrl_sw_pulldown:
            pull = 0x1; //pulldown = 0x1
            break;
        case USB4_platform_sb_ctrl_sw_pullup:
            pull = 0x3;
            break;
        case USB4_platform_sb_ctrl_sw_nopull:
            pull = 0x1; //pulldown = 0x1 - No other option on RUMI
            break;
        case USB4_platform_sb_ctrl_hw_ctrl:
            pull = 0x0; // dontcare
            gpio_func = 0x1; // hw/fw = 0x1
        default:
            USB4_ERROR_STACK_MSG(-1, "Unsupported sb ctrl");
            return -1;
    }

    if (0x0 == usb4_platform_ctx->m_coreIndex)
    {
        // DUT0 SBRX
        HWIO_OUTF4(USB4_GPIO_CFG_REG(0,SBRX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                   pull, gpio_func, 0x4,         oe);
    }
    else
    {
        // DUT1 SBRX
        HWIO_OUTF4(USB4_GPIO_CFG_REG(1,SBRX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                   pull, gpio_func, 0x4,        oe);
    }
    return 0;
}

int Usb4PlatformSideBandTxControl(usb4_platform_ctx_t* usb4_platform_ctx, USB4_platform_sb_ctrl gpioCtrl)
{
    uint32 oe = 0x1; /* If pulling down is not sufficient, driving down may be used */
    uint32 sbtx_value = 0x0;
    uint32 gpio_func = 0x0;

    switch (gpioCtrl)
    {
        case USB4_platform_sb_ctrl_sw_pulldown:
            sbtx_value = 0x0;
            break;
        case USB4_platform_sb_ctrl_sw_pullup:
            sbtx_value = 0x1;
            break;
        case USB4_platform_sb_ctrl_sw_nopull:
            sbtx_value = 0x0; //No other option on RUMI
            break;
        case USB4_platform_sb_ctrl_hw_ctrl:
            oe = 0;
            sbtx_value = 0x0; // dontcare
            gpio_func = 0x1; // hw/fw = 0x1
        default:
            USB4_ERROR_STACK_MSG(-1, "Unsupported sb ctrl");
            return -1;
    }
    
    if (0x0 == usb4_platform_ctx->m_coreIndex)
    {
        // DUT0 SBTX DIR_OUT=0x300 => sw control pullup =>
        //              USB0_SBTX_DIR=0x1 => TX dir is out of MSM
        HWIO_OUT(USB4_GPIO_CFG_REG(0,SBTX_DIR_OUT), 0x300);

        // DUT0 SBTX
        if (1 == oe)
        {
            HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBTX), GPIO_OUT, sbtx_value);
        }
        HWIO_OUTF4(USB4_GPIO_CFG_REG(0, SBTX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                       0, gpio_func, 0x4, oe);
    }
    else
    {
        // DUT0 SBTX DIR_OUT=0x300 => Drive OUT, value from IN_OUT register, POR 0.
        HWIO_OUT(USB4_GPIO_CFG_REG(1,SBTX_DIR_OUT), 0x300);

        // DUT0 SBTX
        if (1 == oe)
        {
            HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBTX), GPIO_OUT, sbtx_value);
        }
        HWIO_OUTF4(USB4_GPIO_CFG_REG(1, SBTX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                       0, gpio_func, 0x4, oe);
    }
    return 0;
}


#elif defined(ASIC) /* && USB4_PLATFORM_GPIO_TLMM */
/* Need to configure external muxes */

int Usb4PlatformInitTlmm(usb4_platform_ctx_t* usb4_platform_ctx)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = gBS->LocateProtocol(&gEfiTLMMProtocolGuid,
                                 NULL, (VOID **)&usb4_platform_ctx->TLMMProtocol);
  if (Status != EFI_SUCCESS)
  {
    // DEBUG(( EFI_D_WARN, "%a: TLMM Locate Protocol failed\r\n", __func__));
    USB4_ERROR_STACK(-1);
    return -1;
  }
  return Status;
}


int Usb4PlatformSideBandSetOrientation(usb4_platform_ctx_t* usb4_platform_ctx, boolean bFlipped) /* USB4_PLATFORM_GPIO_TLMM && ASIC */
{
    EFI_STATUS Status = EFI_SUCCESS;
    if (0x0 == usb4_platform_ctx->m_coreIndex)
    {
        if (bFlipped)
        {
            // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_SEL), GPIO_OUT, 1);
            Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                EFI_GPIO_CFG(
                  IN_OUT0_SBU_SW_SEL, // GpioNum
                  0, // Func
                  GPIO_OUTPUT, // Direction
                  GPIO_NO_PULL, // Pull
                  4 // DriveStrength
                  ),
                GPIO_HIGH_VALUE);
            if (Status != EFI_SUCCESS)
            {
              // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
              return -1;
            }
        }
        else
        {
            // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_SEL), GPIO_OUT, 0);
            Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                EFI_GPIO_CFG(
                  IN_OUT0_SBU_SW_SEL, // GpioNum
                  0, // Func
                  GPIO_OUTPUT, // Direction
                  GPIO_NO_PULL, // Pull
                  4 // DriveStrength
                  ),
                GPIO_LOW_VALUE);
            if (Status != EFI_SUCCESS)
            {
              // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
              return -1;
            }
        }
//        HWIO_OUTF4(  USB4_GPIO_CFG_REG(0,SBU_SW_SEL), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
//                                                              0,        0,           0x4,       1);
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG0_SBU_SW_SEL, // GpioNum
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_ENABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }
    }
    else
    {
        if (bFlipped)
        {
            // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_SEL), GPIO_OUT, 1);
            Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                EFI_GPIO_CFG(
                  IN_OUT1_SBU_SW_SEL, // GpioNum
                  0, // Func
                  GPIO_OUTPUT, // Direction
                  GPIO_NO_PULL, // Pull
                  4 // DriveStrength
                  ),
                GPIO_HIGH_VALUE);
            if (Status != EFI_SUCCESS)
            {
              // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
              return -1;
            }
        }
        else
        {
            // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_SEL), GPIO_OUT, 0);
            Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                EFI_GPIO_CFG(
                  IN_OUT1_SBU_SW_SEL, // GpioNum
                  0, // Func
                  GPIO_OUTPUT, // Direction
                  GPIO_NO_PULL, // Pull
                  4 // DriveStrength
                  ),
                GPIO_LOW_VALUE);
            if (Status != EFI_SUCCESS)
            {
              // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
              return -1;
            }
        }
//        HWIO_OUTF4(  USB4_GPIO_CFG_REG(1,SBU_SW_SEL), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
//                                                              0,        0,           0x4,       1);
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG1_SBU_SW_SEL, // GpioNum
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_ENABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }
    }

    return 0;   
}


int Usb4PlatformSideBandConfigure(usb4_platform_ctx_t* usb4_platform_ctx, boolean bSwap) /* USB4_PLATFORM_GPIO_TLMM && ASIC */
{
#ifndef USB4_ASIC_HWIO
  EFI_STATUS Status = EFI_SUCCESS;
    /* O - no pull,
     * 1 - pull down
     * 3 - pull up
     */
  if (0x0 == usb4_platform_ctx->m_coreIndex)
  {
        /* Configure DIR pin to be under HW control */
        // HWIO_OUTF4(USB4_GPIO_CFG_REG(0, SBTX_DIR_OUT), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
        //                                                        0,        1,          0x4,       0);
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG0_SBTX_DIR_OUT, // GpioNum 168
              1, // Func
              GPIO_INPUT, // Direction  (OE = 0)
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_DISABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        // HWIO_OUTF4(USB4_GPIO_CFG_REG(0,SBRX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
        //                                               0,        1,          0x4,       0); /* Normal SBRX configuration - function 1 */
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG0_SBRX, // GpioNum 170
              1, // Func
              GPIO_INPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_DISABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        // HWIO_OUTF4(USB4_GPIO_CFG_REG(0,SBTX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
        //                                               0,        1,          0x4,       0); /* Normal SBTX configuration - function 1 */
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG0_SBTX, // GpioNum 169
              1, // Func
              GPIO_INPUT, // Direction  (OE = 0)
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_DISABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        //HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_MODE), GPIO_OUT, 0);
        //HWIO_OUTF4(  USB4_GPIO_CFG_REG(0,SBU_MODE), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
        //                                                    0,        0,           0x4,          1);
        Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
            EFI_GPIO_CFG(
              IN_OUT0_SBU_MODE, // GpioNum 167
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL, // Pull
              4 // DriveStrength
              ),
            GPIO_LOW_VALUE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
          return -1;
        }
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG0_SBU_MODE, // GpioNum 167
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_ENABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }
        

        /* Blocks HW controled TX and RX from going through level shifter and muxes */
        // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_OE_N), GPIO_OUT, 1);
        // HWIO_OUTF4(  USB4_GPIO_CFG_REG(0,SBU_SW_OE_N), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
        //                                                     0,           0,           0x4,       1);
        Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
            EFI_GPIO_CFG(
              IN_OUT0_SBU_SW_OE_N, // GpioNum 165
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL, // Pull
              4 // DriveStrength
              ),
            GPIO_HIGH_VALUE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
          return -1;
        }
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG0_SBU_SW_OE_N, // GpioNum 165
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_ENABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        if (bSwap)
        {
            // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_SEL), GPIO_OUT, 1);
            Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                EFI_GPIO_CFG(
                  IN_OUT0_SBU_SW_SEL, // GpioNum 164
                  0, // Func
                  GPIO_OUTPUT, // Direction
                  GPIO_NO_PULL, // Pull
                  4 // DriveStrength
                  ),
                GPIO_HIGH_VALUE);
            if (Status != EFI_SUCCESS)
            {
              // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
              return -1;
            }
        }
        else
        {
            // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_SEL), GPIO_OUT, 0);
            Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                EFI_GPIO_CFG(
                  IN_OUT0_SBU_SW_SEL, // GpioNum 164
                  0, // Func
                  GPIO_OUTPUT, // Direction
                  GPIO_NO_PULL, // Pull
                  4 // DriveStrength
                  ),
                GPIO_LOW_VALUE);
            if (Status != EFI_SUCCESS)
            {
              // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
              return -1;
            }
        }
        // HWIO_OUTF4(  USB4_GPIO_CFG_REG(0,SBU_SW_SEL), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
        //                                                       0,        0,           0x4,       1);
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG0_SBU_SW_SEL, // GpioNum 164
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_ENABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }
    }
    else // Secondary core
    {
        /* Configure DIR pin to be under HW control */
        // HWIO_OUTF4(USB4_GPIO_CFG_REG(1, SBTX_DIR_OUT), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
        //                                                        0,        1,          0x4,       0);
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG1_SBTX_DIR_OUT, // GpioNum
              1, // Func
              GPIO_INPUT, // Direction  (OE = 0)
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_DISABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        // HWIO_OUTF4(USB4_GPIO_CFG_REG(1,SBRX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
        //                                               0,        1,          0x4,       0); /* Normal SBRX configuration - function 1 */
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG1_SBRX, // GpioNum
              1, // Func
              GPIO_INPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_DISABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        // HWIO_OUTF4(USB4_GPIO_CFG_REG(1,SBTX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
        //                                               0,        1,          0x4,       0); /* Normal SBTX configuration - function 1 */
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG1_SBTX, // GpioNum
              1, // Func
              GPIO_INPUT, // Direction  (OE = 0)
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_DISABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_MODE), GPIO_OUT, 0);
        // HWIO_OUTF4(  USB4_GPIO_CFG_REG(1,SBU_MODE), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH,    GPIO_OE,
        //                                                     0,        0,           0x4,          1);
        Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
            EFI_GPIO_CFG(
              IN_OUT1_SBU_MODE, // GpioNum
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL, // Pull
              4 // DriveStrength
              ),
            GPIO_LOW_VALUE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
          return -1;
        }
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG1_SBU_MODE, // GpioNum
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_ENABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        /* Blocks HW controled TX and RX from going through level shifter and muxes */
        // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_OE_N), GPIO_OUT, 1);
        // HWIO_OUTF4(  USB4_GPIO_CFG_REG(1,SBU_SW_OE_N), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
        //                                                        0,        0,           0x4,       1);
        Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
            EFI_GPIO_CFG(
              IN_OUT1_SBU_SW_OE_N, // GpioNum
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL, // Pull
              4 // DriveStrength
              ),
            GPIO_HIGH_VALUE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
          return -1;
        }
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG1_SBU_SW_OE_N, // GpioNum
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_ENABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }

        if (bSwap)
        {
            // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_SEL), GPIO_OUT, 1);
            Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                EFI_GPIO_CFG(
                  IN_OUT1_SBU_SW_SEL, // GpioNum
                  0, // Func
                  GPIO_OUTPUT, // Direction
                  GPIO_NO_PULL, // Pull
                  4 // DriveStrength
                  ),
                GPIO_HIGH_VALUE);
            if (Status != EFI_SUCCESS)
            {
              // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
              return -1;
            }
        }
        else
        {
            // HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_SEL), GPIO_OUT, 0);
            Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                EFI_GPIO_CFG(
                  IN_OUT1_SBU_SW_SEL, // GpioNum
                  0, // Func
                  GPIO_OUTPUT, // Direction
                  GPIO_NO_PULL, // Pull
                  4 // DriveStrength
                  ),
                GPIO_LOW_VALUE);
            if (Status != EFI_SUCCESS)
            {
              // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
              return -1;
            }
        }
        // HWIO_OUTF4(  USB4_GPIO_CFG_REG(1,SBU_SW_SEL), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
        //                                                       0,        0,           0x4,       1);
        Status = usb4_platform_ctx->TLMMProtocol->ConfigGpio(
            EFI_GPIO_CFG(
              CFG1_SBU_SW_SEL, // GpioNum
              0, // Func
              GPIO_OUTPUT, // Direction
              GPIO_NO_PULL,
              4 // DriveStrength
              ),
            TLMM_GPIO_ENABLE);
        if (Status != EFI_SUCCESS)
        {
          // DEBUG(( EFI_D_WARN, "%a: ConfigGpio failed\r\n", __func__));
          return -1;
        }
    }
#else // USB4_ASIC_HWIO
    /* O - no pull,
     * 1 - pull down
     * 3 - pull up
     */
    if (0x0 == usb4_platform_ctx->m_coreIndex)
    {
        /* Configure DIR pin to be under HW control */
        HWIO_OUTF4(USB4_GPIO_CFG_REG(0, SBTX_DIR_OUT), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                               0,        1,          0x4,       0);

        HWIO_OUTF4(USB4_GPIO_CFG_REG(0,SBRX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                      0,        1,          0x4,       0); /* Normal SBRX configuration - function 1 */
        HWIO_OUTF4(USB4_GPIO_CFG_REG(0,SBTX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                      0,        1,          0x4,       0); /* Normal SBTX configuration - function 1 */

        HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_MODE), GPIO_OUT, 0);
        HWIO_OUTF4(  USB4_GPIO_CFG_REG(0,SBU_MODE), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
                                                            0,        0,           0x4,          1);

        /* Blocks HW controled TX and RX from going through level shifter and muxes */
        HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_OE_N), GPIO_OUT, 1);
        HWIO_OUTF4(  USB4_GPIO_CFG_REG(0,SBU_SW_OE_N), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
                                                            0,           0,           0x4,       1);

        if (bSwap)
        {
            HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_SEL), GPIO_OUT, 1);
        }
        else
        {
            HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_SEL), GPIO_OUT, 0);
        }
        HWIO_OUTF4(  USB4_GPIO_CFG_REG(0,SBU_SW_SEL), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
                                                              0,        0,           0x4,       1);
    }
    else
    {
        /* Configure DIR pin to be under HW control */
        HWIO_OUTF4(USB4_GPIO_CFG_REG(1, SBTX_DIR_OUT), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                               0,        1,          0x4,       0);

        HWIO_OUTF4(USB4_GPIO_CFG_REG(1,SBRX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                      0,        1,          0x4,       0); /* Normal SBRX configuration - function 1 */
        HWIO_OUTF4(USB4_GPIO_CFG_REG(1,SBTX), GPIO_PULL, FUNC_SEL, DRV_STRENGTH, GPIO_OE,
                                                      0,        1,          0x4,       0); /* Normal SBTX configuration - function 1 */

        HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_MODE), GPIO_OUT, 0);
        HWIO_OUTF4(  USB4_GPIO_CFG_REG(1,SBU_MODE), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH,    GPIO_OE,
                                                            0,        0,           0x4,          1);

        /* Blocks HW controled TX and RX from going through level shifter and muxes */
        HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_OE_N), GPIO_OUT, 1);
        HWIO_OUTF4(  USB4_GPIO_CFG_REG(1,SBU_SW_OE_N), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
                                                               0,        0,           0x4,       1);

        if (bSwap)
        {
            HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_SEL), GPIO_OUT, 1);
        }
        else
        {
            HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_SEL), GPIO_OUT, 0);
        }
        HWIO_OUTF4(  USB4_GPIO_CFG_REG(1,SBU_SW_SEL), GPIO_PULL, FUNC_SEL,  DRV_STRENGTH, GPIO_OE,
                                                              0,        0,           0x4,       1);
    }
#endif // USB4_ASIC_HWIO
    return 0;
}

int Usb4PlatformSideBandRxControl(usb4_platform_ctx_t* usb4_platform_ctx, USB4_platform_sb_ctrl gpioCtrl) /* USB4_PLATFORM_GPIO_TLMM && ASIC */
{
    return 0; 
}

int Usb4PlatformSideBandTxControl(usb4_platform_ctx_t* usb4_platform_ctx, USB4_platform_sb_ctrl gpioCtrl) /* USB4_PLATFORM_GPIO_TLMM && ASIC */
{ 
    EFI_STATUS Status = EFI_SUCCESS;
    switch (gpioCtrl)
    {
        case USB4_platform_sb_ctrl_sw_pulldown:
        case USB4_platform_sb_ctrl_sw_pullup:
        case USB4_platform_sb_ctrl_sw_nopull:
            /* Blocks HW controled TX and RX from going through level shifter and muxes */
            if (0x0 == usb4_platform_ctx->m_coreIndex)
            {
#ifdef USB4_ASIC_HWIO
                HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_OE_N), GPIO_OUT, 1);
#else // ~USB4_ASIC_HWIO
                Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                    EFI_GPIO_CFG(
                      IN_OUT0_SBU_SW_OE_N, // GpioNum
                      0, // Func
                      GPIO_OUTPUT, // Direction
                      GPIO_NO_PULL, // Pull
                      4 // DriveStrength
                      ),
                    GPIO_HIGH_VALUE);
                if (Status != EFI_SUCCESS)
                {
                  // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
                  return -1;
                }
#endif // ~USB4_ASIC_HWIO
            }
            else
            {
#ifdef USB4_ASIC_HWIO
                HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_OE_N), GPIO_OUT, 1);
#else // ~USB4_ASIC_HWIO
                Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                    EFI_GPIO_CFG(
                      IN_OUT1_SBU_SW_OE_N, // GpioNum
                      0, // Func
                      GPIO_OUTPUT, // Direction
                      GPIO_NO_PULL, // Pull
                      4 // DriveStrength
                      ),
                    GPIO_HIGH_VALUE);
                if (Status != EFI_SUCCESS)
                {
                  // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
                  return -1;
                }
#endif // ~USB4_ASIC_HWIO
            }
            break;
        case USB4_platform_sb_ctrl_hw_ctrl:
            /* Allows HW controlled TX and RX to go through level shifter and muxes */
            if (0x0 == usb4_platform_ctx->m_coreIndex)
            {
#ifdef USB4_ASIC_HWIO
                HWIO_OUTF(USB4_GPIO_IN_OUT_REG(0,SBU_SW_OE_N), GPIO_OUT, 0);
#else // ~USB4_ASIC_HWIO
                Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                    EFI_GPIO_CFG(
                      IN_OUT0_SBU_SW_OE_N, // GpioNum
                      0, // Func
                      GPIO_OUTPUT, // Direction
                      GPIO_NO_PULL, // Pull
                      4 // DriveStrength
                      ),
                    GPIO_LOW_VALUE);
                if (Status != EFI_SUCCESS)
                {
                  // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
                  return -1;
                }
#endif // ~USB4_ASIC_HWIO
            }
            else
            {
#ifdef USB4_ASIC_HWIO
                HWIO_OUTF(USB4_GPIO_IN_OUT_REG(1,SBU_SW_OE_N), GPIO_OUT, 0);
#else // ~USB4_ASIC_HWIO
                Status = usb4_platform_ctx->TLMMProtocol->GpioOut(
                    EFI_GPIO_CFG(
                      IN_OUT1_SBU_SW_OE_N, // GpioNum
                      0, // Func
                      GPIO_OUTPUT, // Direction
                      GPIO_NO_PULL, // Pull
                      4 // DriveStrength
                      ),
                    GPIO_LOW_VALUE);
                if (Status != EFI_SUCCESS)
                {
                  // DEBUG(( EFI_D_WARN, "%a: GpioOut failed\r\n"));
                  return -1;
                }
#endif // ~USB4_ASIC_HWIO
            }
            break;
        default:
            USB4_ERROR_STACK_MSG(-1, "Unsupported sb ctrl");
            return -1;
    }
    return 0; 
}
#endif /* ASIC */

#endif /* USB4_PLATFORM_GPIO_TLMM */


