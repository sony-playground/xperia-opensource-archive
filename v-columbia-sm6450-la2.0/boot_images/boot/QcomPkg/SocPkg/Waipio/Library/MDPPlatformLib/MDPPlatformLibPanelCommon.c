/*=============================================================================

  File: MDPPlatformLibPanelCommon.c

  MDP default platform panel functions

  Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicClkBuff.h>
#include <Protocol/EFITlmm.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicVreg.h>
#include <Protocol/EFIPmicWled.h>
#include <Protocol/EFIPmicIbb.h>
#include <Protocol/EFIPmicLab.h>
#include <Protocol/EFIPmicAb.h>
#include <Protocol/EFIPmicLcdb.h>
#include <Protocol/EFIPmicVersion.h>
#include <Protocol/EFIPmicGpio.h>
#include <Protocol/EFIPmicPwm.h>
#include "DDIChipInfo.h"
#include "MDPSystem.h"
#include "MDPPeripherals.h"
#include "MDPPlatformLibPanelCommon.h"
#include "DisplayUtils.h"
#include "pmapp_npa.h"
#include "DDITlmm.h"
#include "HALDSILib.h"
#include "api/pmic/pm/pm_version.h"

/* MDP supported panel functions for each display id */
MDPPlatformPanelFunctionTable gMDPSupportPanelFunctions[MDP_DISPLAY_MAX];


/**********************************************************************************************
*
* FUNCTION: Panel_Default_PowerUp()
*
* DESCRIPTION:
*   Panel power up sequence for default platform, such as CDP/MTP/QRD.
*
***********************************************************************************************/
MDP_Status Panel_Default_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status                     Status                    = MDP_STATUS_OK;
  EFI_TLMM_PROTOCOL             *TLMMProtocol              = NULL;
  MDPPlatformPanelFunctionTable *pMDPSupportPanelFunctions = MDP_GET_PANELFUNC(eDisplayId);

  if (MDP_STATUS_OK != (Status = PlatformClientInit(eDisplayId, pPowerParams)))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Failed to initialize handle for display NPA node.\n"));
  }
  else if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TLMMProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate TLMM protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    /*
     * Voting for Display NPA node to be ON
     */
    npa_issue_required_request(pPowerParams->sNPAClient[eDisplayId], PMIC_NPA_MODE_ID_GENERIC_ACTIVE);

    /* Display TE pin */
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio(EFI_GPIO_CFG(pMDPSupportPanelFunctions->pMDPPlatformPanelGpio->uDispTeGpio,
                                                             pMDPSupportPanelFunctions->pMDPPlatformPanelGpio->uDispTeGpioFuncSelect,
                                                             GPIO_INPUT,
                                                             GPIO_NO_PULL,
                                                             GPIO_2MA),
                                                             TLMM_GPIO_ENABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Configure GPIO %d for TE line failed!\n", pMDPSupportPanelFunctions->pMDPPlatformPanelGpio->uDispTeGpio));
    }

    /*
    * Enable LCD_REG_EN for local on board boost regulator for the panels that do not have
    * OLEDB_EN signal to PMIC to enable IBB/LAB.
    */
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(Default_DISP_LCD_REG_EN, 0, GPIO_OUTPUT, GPIO_PULL_UP, GPIO_16MA), TLMM_GPIO_ENABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Configure GPIO %d for LCD_REG_EN failed!\n", Default_DISP_LCD_REG_EN));
    }

    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(Default_DISP_LCD_REG_EN, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_16MA), GPIO_HIGH_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: LCD_REG_EN line Low failed!\n"));
    }

  }

  return Status;
}

/**********************************************************************************************
*
* FUNCTION: Panel_Default_PowerDown()
*
* DESCRIPTION:
*   Panel power down sequence for default platform, such as CDP/MTP/QRD.
*
***********************************************************************************************/
MDP_Status Panel_Default_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status                     Status                    = MDP_STATUS_OK;
  EFI_TLMM_PROTOCOL             *TLMMProtocol              = NULL;
  MDPPlatformPanelFunctionTable *pMDPSupportPanelFunctions = MDP_GET_PANELFUNC(eDisplayId);

  if (NULL == pPowerParams->sNPAClient[eDisplayId])
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: NULL Handle for display NPA node.\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TLMMProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate TLMM protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    /* 
     * GPIOs & VRegs
     */
    /* Display RESET_N pin */
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(pPowerParams->uResetGpio, 0, GPIO_OUTPUT, GPIO_PULL_UP, GPIO_16MA), TLMM_GPIO_DISABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Failed to disable GPIO %d for Reset_N line\n", pPowerParams->uResetGpio));
    }

    /* Display TE pin */
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio(EFI_GPIO_CFG(pMDPSupportPanelFunctions->pMDPPlatformPanelGpio->uDispTeGpio,
                                                             pMDPSupportPanelFunctions->pMDPPlatformPanelGpio->uDispTeGpioFuncSelect,
                                                             GPIO_INPUT,
                                                             GPIO_PULL_DOWN,
                                                             GPIO_2MA),
                                                             TLMM_GPIO_DISABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Failed to disable GPIO %d for TE pin\n", pMDPSupportPanelFunctions->pMDPPlatformPanelGpio->uDispTeGpio));
    }

    /*
    * Disable LCD_REG_EN for local on board boost regulator for the panels that do not have
    * OLEDB_EN signal to PMIC to enable IBB/LAB.
    */

    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(Default_DISP_LCD_REG_EN, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_16MA), GPIO_LOW_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: LCD_REG_EN line Low failed!\n"));
    }

    if (MDP_DISPLAY_PRIMARY == eDisplayId)
    {
      if (TRUE == pPowerParams->bDisplayNPAStatus[MDP_DISPLAY_SECONDARY])
      {
        // If secondary display is still on, then just set primary display to disabled status.
        pPowerParams->bDisplayNPAStatus[MDP_DISPLAY_PRIMARY] = FALSE;
      }
      else
      {
        npa_complete_request(pPowerParams->sNPAClient[MDP_DISPLAY_PRIMARY]);           // Complete the request to power rails
      }
    }
    else if (MDP_DISPLAY_SECONDARY == eDisplayId)
    {
      if (TRUE == pPowerParams->bDisplayNPAStatus[MDP_DISPLAY_PRIMARY])
      {
        // If primary display is still on, then just set secondary display to disabled status.
        pPowerParams->bDisplayNPAStatus[MDP_DISPLAY_SECONDARY] = FALSE;
      }
      else
      {
        npa_complete_request(pPowerParams->sNPAClient[MDP_DISPLAY_SECONDARY]);           // Complete the request to power rails
      }
    }
    else
    {
      /*
       * Voltage Regulators
       */
      npa_complete_request(pPowerParams->sNPAClient[eDisplayId]);           // Complete the request to power rails
    }
  }

  return Status;
}

/**********************************************************************************************
*
* FUNCTION: Panel_HDK_PowerUp()
*
* DESCRIPTION:
*   Panel power up sequence for HDK platform.
*
***********************************************************************************************/
MDP_Status Panel_HDK_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status                     Status                   = MDP_STATUS_OK;
  EFI_QCOM_PMIC_GPIO_PROTOCOL    *PmicGpioProtocol        = NULL;

  if (EFI_SUCCESS != gBS->LocateProtocol( &gQcomPmicGpioProtocolGuid, NULL, (void **)&PmicGpioProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate get pmic gpio protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    /* LCD WLED Enable Pin */
    if (EFI_SUCCESS != PmicGpioProtocol->CfgMode(PMIC_B, EFI_PM_GPIO_9, EFI_PM_GPIO_DIG_OUT))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: config pmic_b gpio9 failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetVoltageSource(PMIC_B, EFI_PM_GPIO_9, EFI_PM_GPIO_VIN0))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set gpio9 voltage failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetOutputLevel(PMIC_B, EFI_PM_GPIO_9, EFI_PM_GPIO_LEVEL_HIGH))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set gpio9 out put level failed!\n"));
    }

    /* LCD BIAS Enable Pin */
    if (EFI_SUCCESS != PmicGpioProtocol->CfgMode(PMIC_B, EFI_PM_GPIO_8, EFI_PM_GPIO_DIG_OUT))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: config pmic_b gpio8 failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetVoltageSource(PMIC_B, EFI_PM_GPIO_8, EFI_PM_GPIO_VIN0))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set gpio8 voltage failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetOutputLevel(PMIC_B, EFI_PM_GPIO_8, EFI_PM_GPIO_LEVEL_HIGH))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set gpio8 out put level failed!\n"));
    }

    /* LCD PWM Control Pin */
    if (EFI_SUCCESS != PmicGpioProtocol->CfgMode(PMIC_C, EFI_PM_GPIO_8, EFI_PM_GPIO_DIG_OUT))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: config pmic_c gpio8 failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetVoltageSource(PMIC_C, EFI_PM_GPIO_8, EFI_PM_GPIO_VIN0))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set pmic_c gpio8 voltage failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetOutputLevel(PMIC_C, EFI_PM_GPIO_8, EFI_PM_GPIO_LEVEL_LOW))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set pmic_c gpio8 out put level failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetOutSrcCfg(PMIC_C, EFI_PM_GPIO_8, EFI_PM_GPIO_SRC_SPECIAL_FUNCTION1))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set pmic_c gpio8 out src cfg failed!\n"));
    }
  }

  Status = Panel_Default_PowerUp(eDisplayId, pPowerParams);

  return Status;
}

/**********************************************************************************************
*
* FUNCTION: Panel_HDK_PowerDown()
*
* DESCRIPTION:
*   Panel power down sequence for HDK platform.
*
***********************************************************************************************/
MDP_Status Panel_HDK_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status            Status      = MDP_STATUS_OK;
  EFI_QCOM_PMIC_GPIO_PROTOCOL *PmicGpioProtocol = NULL;

  if (EFI_SUCCESS != gBS->LocateProtocol( &gQcomPmicGpioProtocolGuid, NULL, (void **)&PmicGpioProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate get pmic gpio protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    if (EFI_SUCCESS != PmicGpioProtocol->CfgMode(PMIC_B, EFI_PM_GPIO_9, EFI_PM_GPIO_DIG_OUT))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: config pmic_b gpio9 failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetOutputLevel(PMIC_B, EFI_PM_GPIO_9, EFI_PM_GPIO_LEVEL_LOW))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set pmic_b gpio9 output failed!\n"));
    }

    if (EFI_SUCCESS != PmicGpioProtocol->CfgMode(PMIC_B, EFI_PM_GPIO_8, EFI_PM_GPIO_DIG_OUT))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: config pmic_b gpio8 failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetOutputLevel(PMIC_B, EFI_PM_GPIO_8, EFI_PM_GPIO_LEVEL_LOW))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: set pmic_b gpio8 output failed!\n"));
    }

    if (EFI_SUCCESS != PmicGpioProtocol->CfgMode(PMIC_C, EFI_PM_GPIO_8, EFI_PM_GPIO_DIG_OUT))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: config pmic_c gpio8 failed!\n"));
    }
    else if (EFI_SUCCESS != PmicGpioProtocol->SetOutputLevel(PMIC_C, EFI_PM_GPIO_8, EFI_PM_GPIO_LEVEL_LOW))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: config pmic_c gpio8 output failed!\n"));
    }
  }

  Status = Panel_Default_PowerDown(eDisplayId, pPowerParams);

  return Status;
}

/**********************************************************************************************
*
* FUNCTION: Panel_ResetStateExec()
*
* DESCRIPTION:
*   Toggle reset gpio base on states transition.
*
***********************************************************************************************/
static void Panel_ResetStateExec(EFI_TLMM_PROTOCOL *tlmm, MDPPlatformPanelResetInfo *pResetInfo, uint32 state0, uint32 state1, uint32 state2)
{

  if (EFI_SUCCESS != tlmm->GpioOut((UINT32)EFI_GPIO_CFG(pResetInfo->uResetGpio, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_8MA), state0))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Reset_N line FAILED at state-0!\n"));
  }

  MDP_OSAL_DELAYUS(pResetInfo->uPreResetTimeUs);

  if (EFI_SUCCESS != tlmm->GpioOut((UINT32)EFI_GPIO_CFG(pResetInfo->uResetGpio, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_8MA), state1))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Reset_N line FAILED at state-1!\n"));
  }

  MDP_OSAL_DELAYUS(pResetInfo->uResetAssertTimeUs);

  if (EFI_SUCCESS != tlmm->GpioOut((UINT32)EFI_GPIO_CFG(pResetInfo->uResetGpio, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_16MA), state2))
  {
    DEBUG((EFI_D_WARN, "DisplayDxe: Reset_N line FAILED at state-2!\n"));
  }
}


/**********************************************************************************************
*
* FUNCTION: Panel_Default_Reset()
*
* DESCRIPTION:
*   Panel reset sequence for default platform, such as CDP/MTP/QRD.
*
***********************************************************************************************/
MDP_Status Panel_Default_Reset(MDPPlatformPanelResetInfo *pResetInfo)
{
  MDP_Status                    Status           = MDP_STATUS_OK;
  EFI_TLMM_PROTOCOL            *TLMMProtocol     = NULL;

  if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void **)&TLMMProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate TLMM protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    /* Enable Display Reset pin*/
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(pResetInfo->uResetGpio, 0, GPIO_OUTPUT, GPIO_PULL_UP, GPIO_8MA), TLMM_GPIO_ENABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Configure GPIO %d for Reset_N line failed!\n", pResetInfo->uResetGpio));
    }

    switch (pResetInfo->uAssertState)
    {
      case MDP_RESET_STATE_EDGE_LOW2HIGH:
         Panel_ResetStateExec(TLMMProtocol, pResetInfo, GPIO_LOW_VALUE, GPIO_HIGH_VALUE, GPIO_HIGH_VALUE);
       break;
      case MDP_RESET_STATE_EDGE_HIGH2LOW:
         Panel_ResetStateExec(TLMMProtocol, pResetInfo, GPIO_HIGH_VALUE, GPIO_LOW_VALUE, GPIO_LOW_VALUE);
       break;
      case MDP_RESET_STATE_LEVEL_HIGH:
         Panel_ResetStateExec(TLMMProtocol, pResetInfo, GPIO_LOW_VALUE, GPIO_HIGH_VALUE, GPIO_LOW_VALUE);
       break;
      case MDP_RESET_STATE_LEVEL_LOW:
      default:
         Panel_ResetStateExec(TLMMProtocol, pResetInfo, GPIO_HIGH_VALUE, GPIO_LOW_VALUE, GPIO_HIGH_VALUE);
       break;
    }

    MDP_OSAL_DELAYUS(pResetInfo->uPostResetTimeUs);

    /*
     * post reset time: Timing space between end of reset to start sending init dcs cmds
     * NOTE:
     *   use DSIInitMasterTime to extend post reset time control if required
     */
  }
  
  return Status;
}


/**********************************************************************************************
*
* FUNCTION: Panel_Default_Brightness_Enable()
*
* DESCRIPTION:
*   Configure GPIO to enable external backlight
*
***********************************************************************************************/
MDP_Status Panel_Default_Brightness_Enable(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status           Status       = MDP_STATUS_OK;
  EFI_TLMM_PROTOCOL   *TLMMProtocol = NULL;

  if (EFI_SUCCESS != gBS->LocateProtocol(&gEfiTLMMProtocolGuid, NULL, (void**)&TLMMProtocol))
  {
    DEBUG((EFI_D_ERROR, "DisplayDxe: Locate TLMM protocol failed!\n"));
    Status = MDP_STATUS_NO_RESOURCES;
  }
  else
  {
    if (EFI_SUCCESS != TLMMProtocol->ConfigGpio((UINT32)EFI_GPIO_CFG(Default_DISP_LCD_BKLT_EN, 0, GPIO_OUTPUT, GPIO_PULL_UP, GPIO_16MA), TLMM_GPIO_ENABLE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Configure GPIO %d for Default_DISP_LCD_BKLT_EN failed!\n", Default_DISP_LCD_BKLT_EN));
    }

    if (EFI_SUCCESS != TLMMProtocol->GpioOut((UINT32)EFI_GPIO_CFG(Default_DISP_LCD_BKLT_EN, 0, GPIO_OUTPUT, GPIO_NO_PULL, GPIO_16MA), GPIO_HIGH_VALUE))
    {
      DEBUG((EFI_D_WARN, "DisplayDxe: Set Default_DISP_LCD_BKLT_EN line high failed!\n"));
    }
  }

  return Status;
}


/**********************************************************************************************
*
* FUNCTION: Panel_Default_Brightness_Level()
*
* DESCRIPTION:
*   The function can control the panel brightness level.
*
***********************************************************************************************/
MDP_Status Panel_Default_Brightness_Level(MDP_Display_IDType eDisplayId, BacklightConfigType *pBacklightConfig)
{
  MDP_Status Status = MDP_STATUS_OK;

  if (MDP_PANEL_BACKLIGHTTYPE_PMIC == pBacklightConfig->eBacklightType)
  {
    // Configure the power grid based on the module type
    switch (pBacklightConfig->uBacklightCntrl.eBacklightCtrl)
    {
    case MDP_PMIC_BACKLIGHT_CONTROLTYPE_WLED:
      {
        EFI_QCOM_PMIC_WLED_PROTOCOL  *PmicWledProtocol = NULL;

        if (EFI_SUCCESS != gBS->LocateProtocol(&gQcomPmicWledProtocolGuid, NULL, (VOID **)&PmicWledProtocol))
        {
          DEBUG((EFI_D_ERROR, "DisplayDxe: Locate WLED Protocol failed!\n"));
          Status = MDP_STATUS_NO_RESOURCES;
        }
        else
        {
          uint32 uWLEDValue = (0xFFF * pBacklightConfig->uLevel) / 100; // Calculate duty cycle based on 12 bit mode

          if (EFI_SUCCESS != PmicWledProtocol->SetLedDutyCycle(PMIC_PMI_DEV_INDEX, EFI_PM_MODULATOR_TYPE_A, uWLEDValue))
          {
            DEBUG((EFI_D_ERROR, "Wled Protocol SetLedDutyCycle for ModulatorA failed\n"));
          }

          if (EFI_SUCCESS != PmicWledProtocol->SetLedDutyCycle(PMIC_PMI_DEV_INDEX, EFI_PM_MODULATOR_TYPE_B, uWLEDValue))
          {
            DEBUG((EFI_D_ERROR, "Wled Protocol SetLedDutyCycle for ModulatorB failed\n"));
          }
        }
      }
      break;

    case MDP_PMIC_BACKLIGHT_CONTROLTYPE_PWM:
    {
      EFI_QCOM_PMIC_PWM_PROTOCOL *PmicPwmProtocol = NULL;
      uint32                     uBrightnessValue = (511 * pBacklightConfig->uLevel) / 100;

      if (EFI_SUCCESS != gBS->LocateProtocol(&gQcomPmicPwmProtocolGuid, NULL, (void**)&PmicPwmProtocol))
      {
        DEBUG((EFI_D_ERROR, "DisplayDxe: Locate Pmic PWM Protocol failed!\n"));
        Status = MDP_STATUS_NO_RESOURCES;
      }
      else if (EFI_SUCCESS != PmicPwmProtocol->PwmConfig(PMIC_PMI_DEV_INDEX, EFI_PM_PWM_RSRC_PWM_4, uBrightnessValue, 1, 2, EFI_PM_PWM_CLK_19_2_MHZ, EFI_PM_PWM_SIZE_9BIT))
      {
        DEBUG((EFI_D_ERROR, "DisplayDxe: PwmConfig failed!\n"));
      }
      else if (EFI_SUCCESS != PmicPwmProtocol->SetPwmValue(PMIC_PMI_DEV_INDEX, EFI_PM_PWM_RSRC_PWM_4, uBrightnessValue))
      {
        DEBUG((EFI_D_ERROR, "DisplayDxe: SetPwmValue failed!\n"));
      }
    }
    break;
    default:
      break;
    }
  }
  else if (MDP_PANEL_BACKLIGHTTYPE_DSI == pBacklightConfig->eBacklightType)
  {
    if (pBacklightConfig->uNumBits > 16)
    {
      DEBUG((EFI_D_ERROR, "Backlight dcs bit width is not available\n"));
      Status = MDP_STATUS_BAD_PARAM;
    }
    else
    {
      PlatformPanelBacklightControl panelBacklightControl = {
        0x00,
        {0x51, 0x00, 0x00}, // Using standard MIPI DCS commands to control brightness
      };

      if (pBacklightConfig->uNumBits > 8)
      {
        // Calculate brightness
        panelBacklightControl.uCmdType   = 0x39; // Use dcs long write type, e.g. 10bits: first byte is bits 0:7, the second byte is bits 8:9.
        panelBacklightControl.command[1] = DISP_DIV_ROUND_UP(((1 << pBacklightConfig->uNumBits) - 1) * pBacklightConfig->uLevel, 100) &  0xFF;
        panelBacklightControl.command[2] = DISP_DIV_ROUND_UP(((1 << pBacklightConfig->uNumBits) - 1) * pBacklightConfig->uLevel, 100) >> 0x08;
      }
      else
      {
        // Default to calculate brightness based on 8 bit mode
        panelBacklightControl.uCmdType   = 0x15; // Use dcs short write type as only needs one byte.
        panelBacklightControl.command[1] = DISP_DIV_ROUND_UP(0xFF * pBacklightConfig->uLevel, 100) & 0xFF;
      }

      Status = DSIDriver_Write(eDisplayId,
                               panelBacklightControl.uCmdType,
                               panelBacklightControl.command,
                               sizeof(panelBacklightControl.command),
                               0);
      if (MDP_STATUS_OK != Status)
      {
        DEBUG((EFI_D_ERROR, "Backlight brightness DCS command send failed\n"));
      }
	}
  }
  else
  {
    // Nothing to do for other configurations
  }

  return Status;
}


/**********************************************************************************************
*
* FUNCTION: Panel_Default_V2_Brightness_Level()
*
* DESCRIPTION:
*   The version2 function to control the panel brightness level.
*
*   For this version of dcs control to adjust brightness level,
*   need to save high brightness bits in first command parameter and low brightness bits in secondary command parameter.
*
***********************************************************************************************/
MDP_Status Panel_Default_V2_Brightness_Level(MDP_Display_IDType eDisplayId, BacklightConfigType *pBacklightConfig)
{
  MDP_Status Status = MDP_STATUS_OK;

  if (MDP_PANEL_BACKLIGHTTYPE_DSI == pBacklightConfig->eBacklightType)
  {
    if (pBacklightConfig->uNumBits > 16)
    {
      DEBUG((EFI_D_ERROR, "Backlight dcs bit width is not available\n"));
      Status = MDP_STATUS_BAD_PARAM;
    }
    else
    {
      PlatformPanelBacklightControl panelBacklightControl = {
        0x00,
        {0x51, 0x00, 0x00}, // Using standard MIPI DCS commands to control brightness
      };

      if (pBacklightConfig->uNumBits > 8)
      {
        // Calculate brightness based on another dcs control version, save high brightness bits in first parameter and low brightness bits in secondary parameter.
        panelBacklightControl.uCmdType   = 0x39; // Use dcs long write type, e.g. 10bits: first byte is bits 8:11, the second byte is bits 0:7.
        panelBacklightControl.command[1] = DISP_DIV_ROUND_UP(((1 << pBacklightConfig->uNumBits) - 1) * pBacklightConfig->uLevel, 100) >> 0x08;
        panelBacklightControl.command[2] = DISP_DIV_ROUND_UP(((1 << pBacklightConfig->uNumBits) - 1) * pBacklightConfig->uLevel, 100) &  0xFF;
      }
      else
      {
        // Default to calculate brightness based on 8 bit mode
        panelBacklightControl.uCmdType   = 0x15; // Use dcs short write type as only needs one byte.
        panelBacklightControl.command[1] = DISP_DIV_ROUND_UP(0xFF * pBacklightConfig->uLevel, 100) & 0xFF;
      }

      Status = DSIDriver_Write(eDisplayId,
                               panelBacklightControl.uCmdType,
                               panelBacklightControl.command,
                               sizeof(panelBacklightControl.command),
                               0);
      if (MDP_STATUS_OK != Status)
      {
        DEBUG((EFI_D_ERROR, "Backlight brightness DCS command send failed\n"));
      }
	}
  }
  else
  {
    // Nothing to do for other configurations
  }
  return Status;
}

/**********************************************************************************************
*
* FUNCTION: DP_USBPlugInvertedOrientation()
*
* DESCRIPTION:
*   Get DP plug polarity (TRUE = inverted, FALSE = normal).
*
***********************************************************************************************/
bool32 DP_USBPlugInvertedOrientation (void)
{ 
  /* USB driver support for detecting orientation is not available. 
   * Use Hardcoded cable polarity 
   */
  bool32  bPolarity = DP_PLUG_INVERTED_POLARITY;

  // For Klocwork - will never be true when this fn. is called
  if (PCD_EXTERNAL_DISPLAY_DP != PcdGet32(PcdExtDisplayType))
  {
     bPolarity = !bPolarity;
  }

  return bPolarity;
}


/**********************************************************************************************
*
* FUNCTION: ExternalPanel_Default_PowerUp()
*
* DESCRIPTION:
*   The default power up function for external display.
*
***********************************************************************************************/
MDP_Status ExternalPanel_Default_PowerUp(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status                    Status            = MDP_STATUS_OK;
  
  return Status;
}


/**********************************************************************************************
*
* FUNCTION: ExternalPanel_Default_PowerDown()
*
* DESCRIPTION:
*   The default power down function for external display.
*
***********************************************************************************************/
MDP_Status ExternalPanel_Default_PowerDown(MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams)
{
  MDP_Status                    Status            = MDP_STATUS_OK;
  
  return Status;
}

#ifdef __cplusplus
}
#endif
