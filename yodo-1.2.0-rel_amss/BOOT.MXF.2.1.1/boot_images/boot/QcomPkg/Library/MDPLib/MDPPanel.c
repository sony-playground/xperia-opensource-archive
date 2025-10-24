/*=============================================================================
 
  File: MDPPanel.c
 
  Source file for panel specific configuration
  
  Copyright (c) 2011-2021 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
/*=========================================================================
      Include Files
==========================================================================*/
#include "MDPLib.h"
#include "MDPPlatformLib.h"
#include "HALDSILib.h"
#include "ExternalDisplayDriver.h"
#include "DPInterface.h"

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */

/*=========================================================================
      Local prototypes
==========================================================================*/




/*=========================================================================
      Public functions
==========================================================================*/

/****************************************************************************
*
** FUNCTION: MDPPanelDeInit()
*/
/*!
* \brief
*   This function de-intializes the interfaces.
*
* \param [in] pPanelInfo    - The panel configuration
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPPanelDeInit(MDP_Panel_AttrType    *pPanelInfo)
{
  MDP_Status eStatus    = MDP_STATUS_OK;

  MDP_LOG_FUNC_ENTRY("MDPPanelDeInit", pPanelInfo->eDisplayId);

  switch (pPanelInfo->eDisplayId)
  {
    case MDP_DISPLAY_PRIMARY:
    case MDP_DISPLAY_SECONDARY:
      switch (pPanelInfo->ePhysConnect)
      {         
        case MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO:
        case MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD:
        case MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO:
        case MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD:
    
          // Graceful shutdown of the panel
          DsiPanelShutdown(pPanelInfo);
          
          DSIDriver_Close(pPanelInfo->eDisplayId);
          break;

        case MDP_DISPLAY_CONNECT_EDP:
          DPDriver_Term(pPanelInfo->eDisplayId);
          break;

        default:
          break;
      }
      break;
   
    case MDP_DISPLAY_EXTERNAL:
      eStatus = ExtDisp_Close(pPanelInfo->eDisplayId);
      break;

    default:
      break;
  }

  MDP_LOG_FUNC_EXIT("MDPPanelDeInit", pPanelInfo->eDisplayId);

  return eStatus;
}


/****************************************************************************
*
** FUNCTION: MDPPanelInit()
*/
/*!
* \brief
*   This function setup the display for a particular mode.
*
* \param [in] eDisplayId    - The display to initialize
* \param [in] uModeIndex    - The display mode to configure
*        [in] pPanelInfo    - The panel configuration
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPPanelInit(MDP_Display_IDType eDisplayId, uint32 uModeIndex, MDP_Panel_AttrType *pPanelInfo)
{
    MDP_Status eStatus    = MDP_STATUS_OK;

    MDP_LOG_FUNC_ENTRY("MDPPanelInit", pPanelInfo->eDisplayId);

    switch (pPanelInfo->eDisplayId)
    {
      case MDP_DISPLAY_PRIMARY:
      case MDP_DISPLAY_SECONDARY:
        switch (pPanelInfo->ePhysConnect)
        {
          case MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO:
          case MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD:
          case MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO:
          case MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD:
            /* Setup DSI Configuration */
            eStatus = DsiPanelInit(pPanelInfo);
            break;

          case MDP_DISPLAY_CONNECT_EDP:
          {
            eStatus = DPDriver_SetMode(pPanelInfo, 0x0);
            break;
          }
          default:
            break;
        }
        break;
     
      case MDP_DISPLAY_EXTERNAL:
        pPanelInfo->eDisplayFlags |= MDP_PANEL_FLAG_TIMING_FROM_EDID; /* always panel timing from EDID */
        eStatus = ExtDisp_SetMode(pPanelInfo, 0);
        break;
  
      default:
        break;
    }

    MDP_LOG_FUNC_EXIT("MDPPanelInit", pPanelInfo->eDisplayId);

    return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPPanelGetEDID()
*/
/*!
* \brief
*   This function read EDID info from panel.
*
* \param [in] pPanelInfo    - The panel configuration
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPPanelGetEDID( MDP_Panel_AttrType    *pPanelInfo)
{
  MDP_Status eStatus    = MDP_STATUS_OK;

  /* Configure the display */
  switch (pPanelInfo->ePhysConnect)
  {
    case MDP_DISPLAY_CONNECT_EDP:
    {
      //#TODO#IMPLEMENT
      eStatus = MDP_STATUS_NOT_SUPPORTED;
      break;
    }
    case MDP_DISPLAY_CONNECT_DP:
    {
      eStatus = MDP_STATUS_NOT_SUPPORTED;
      break;
    }
    default:
    {
      break;
    }
  }

  return eStatus;
}

/****************************************************************************
*
** FUNCTION: MDPPanelSendCommandSequence()
*/
/*!
* \brief
*   Sends a predefined command set to the panel.
*        [in] pPanelInfo      - The panel configuration
*        [in] eCommandType    - Command type to send
*        [in] pCustomCommand  - Custom command buffer, only valid for MDP_PANEL_COMMAND_CUSTOM
*        [in] uFlags          - Reserved.
*
* \retval MDP_Status
*
****************************************************************************/
MDP_Status  MDPPanelSendCommandSequence(MDP_Panel_AttrType *pPanelInfo, MdpPanelCommandType eCommand, void *pCustomCommand, uint32 uFlags)
{
    MDP_Status eStatus    = MDP_STATUS_OK;

    MDP_LOG_FUNC_ENTRY("MDPPanelSendCommandSequence", pPanelInfo->eDisplayId);
 
    /* Configure the display */
    switch (pPanelInfo->ePhysConnect)
    {     
      case MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO:
      case MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD:
      case MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO:
      case MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD:
        /* Setup DSI Configuration */
        eStatus = DsiPanelSendCommandSequence(pPanelInfo, eCommand, pCustomCommand, uFlags);
        break;
      default: 
        break;
    }

    MDP_LOG_FUNC_EXIT("MDPPanelSendCommandSequence", pPanelInfo->eDisplayId);

    return eStatus;
}

/*-----------------------------------------------------------------------
 * MDP_GetPanelBitsPerPixel
 *
 * DESCRIPTION:
 *  This function is a translation of the MDP_ColorFormat_Type enum
----------------------------------------------------------------------- */
uint32 MDP_GetPanelBitsPerPixel(MDP_ColorFormat_Type eColorFormat)
{
  uint32         uBpp       = 0;

  switch(eColorFormat)
  {
    case MDP_COLORFORMAT_RGB_444_12BPP:
    case MDP_COLORFORMAT_RBG_444_12BPP:
    case MDP_COLORFORMAT_BGR_444_12BPP:
    case MDP_COLORFORMAT_BRG_444_12BPP:
    case MDP_COLORFORMAT_GRB_444_12BPP:
    case MDP_COLORFORMAT_GBR_444_12BPP:
      uBpp = 12;
      break;

    case MDP_COLORFORMAT_RGB_565_16BPP:
    case MDP_COLORFORMAT_RBG_565_16BPP:
    case MDP_COLORFORMAT_BGR_565_16BPP:
    case MDP_COLORFORMAT_BRG_565_16BPP:
    case MDP_COLORFORMAT_GRB_565_16BPP:
    case MDP_COLORFORMAT_GBR_565_16BPP:
      uBpp = 16;
      break;

    case MDP_COLORFORMAT_RGB_666_18BPP:
    case MDP_COLORFORMAT_RBG_666_18BPP:
    case MDP_COLORFORMAT_BGR_666_18BPP:
    case MDP_COLORFORMAT_BRG_666_18BPP:
    case MDP_COLORFORMAT_GRB_666_18BPP:
    case MDP_COLORFORMAT_GBR_666_18BPP:
      uBpp = 18;
      break;

    case MDP_COLORFORMAT_RGB_666_24BPP:
    case MDP_COLORFORMAT_RBG_666_24BPP:
    case MDP_COLORFORMAT_BGR_666_24BPP:
    case MDP_COLORFORMAT_BRG_666_24BPP:
    case MDP_COLORFORMAT_GRB_666_24BPP:
    case MDP_COLORFORMAT_GBR_666_24BPP:
    case MDP_COLORFORMAT_RGB_888_24BPP:
    case MDP_COLORFORMAT_RBG_888_24BPP:
    case MDP_COLORFORMAT_BGR_888_24BPP:
    case MDP_COLORFORMAT_BRG_888_24BPP:
    case MDP_COLORFORMAT_GRB_888_24BPP:
    case MDP_COLORFORMAT_GBR_888_24BPP:
      uBpp = 24;
      break;

    case MDP_COLORFORMAT_RGB_101010_30BPP:
    case MDP_COLORFORMAT_RBG_101010_30BPP:
    case MDP_COLORFORMAT_BGR_101010_30BPP:
    case MDP_COLORFORMAT_BRG_101010_30BPP:
    case MDP_COLORFORMAT_GRB_101010_30BPP:
    case MDP_COLORFORMAT_GBR_101010_30BPP:
      uBpp = 30;
      break;

    default:
      uBpp = 24;
      break;
  }

  return uBpp;
}
