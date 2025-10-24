/*=============================================================================
 
  File: dsipanel.c
 
  Source file for HAL DSI Panel configuration
  
     Copyright (c) 2011-2022 Qualcomm Technologies, Inc.
     All Rights Reserved.
     Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------
** Includes
** ----------------------------------------------------------------------- */
#include "MDPLib.h"
#include "MDPLib_i.h"
#include "MDPSystem.h"
#include "MDPPlatformLib.h"
#include "xmlparser.h"
#include "dsiHost.h"
#include "HALdsi_Phy.h"
#include "dsiHostShared.h"
#include "MDPPeripherals.h"
#include "dsiHostSystem.h"

/* -----------------------------------------------------------------------
** Defines
** ----------------------------------------------------------------------- */
#define DSI_LANE_SWAPNUM                      8  // Maximum DSI SWAP lanes supported
#define DSI_STATUS_POLLING_CYCLE              5  // DSI controller status polling cycle, 5ms
#define DSI_STATUS_CHECK_MAX_TIME            40  // Maximum DSI controller status check time. 40ms
#define DSI_SPLITDISPLAY_NUM                  2  // 2 DSI devices are used in DSI split display mode
#define DSI_CONTROLLER_0                   0x01  // Bit Mask for DSI controller 0
#define DSI_CONTROLLER_1                   0x02  // Bit Mask for DSI controller 1
#define DSI_DEFAULT_BITCLOCK_FREQ     543710000  // Bitclock frequency based on VGA resolution @60fps
#define DSI_STATUS_WAIT_IDLE_MAX_TIME        16  // The max waiting time for dsi controller not busy
#define DSI_READ_MAX_PACKET_SIZE             10  // The max packet size during one dsi read
#define DSI_DMA_CMD_DEFAULT_SCHEDULE_LINE   0x5  // Default line count for Scheduling DMA command

/* DSI Driver context */
typedef struct
{
  bool32                    bDualDSI;                          /* If DSI0/1 are working in Dual DSI mode   */
  DSI_HandleType            hDSIHandle[DSI_DeviceID_MAX];      /* DSI device handles for each controller   */
  DSI_HandleType            hDisplayHandle[DSI_DeviceID_MAX];  /* DSI display handles for each controller  */
  uint32                    uNumDSIControllers;
  void                     *pDSIBuffer;                        /* Pointer to DSI DMA command buffer*/
} DSI_DriverCtx;

/* -----------------------------------------------------------------------
** Global variables
** ----------------------------------------------------------------------- */
DSI_DriverCtx  gDsiDriverCtx[MDP_DISPLAY_MAX];

static const  DSI_LaneMapType  sDisplayLaneSetting[DSI_LANE_SWAPNUM][DSI_LaneMap_MAX] ={
        { DSI_LaneMap_0,  DSI_LaneMap_1, DSI_LaneMap_2,  DSI_LaneMap_3  },
        { DSI_LaneMap_3,  DSI_LaneMap_0, DSI_LaneMap_1,  DSI_LaneMap_2  },
        { DSI_LaneMap_2,  DSI_LaneMap_3, DSI_LaneMap_0,  DSI_LaneMap_1  },
        { DSI_LaneMap_1,  DSI_LaneMap_2, DSI_LaneMap_3,  DSI_LaneMap_0  },
        { DSI_LaneMap_0,  DSI_LaneMap_3, DSI_LaneMap_2,  DSI_LaneMap_1  },
        { DSI_LaneMap_1,  DSI_LaneMap_0, DSI_LaneMap_3,  DSI_LaneMap_2  },
        { DSI_LaneMap_2,  DSI_LaneMap_1, DSI_LaneMap_0,  DSI_LaneMap_3  },
        { DSI_LaneMap_3,  DSI_LaneMap_2, DSI_LaneMap_1,  DSI_LaneMap_0  }};

/*------------------------------------------------------------------------
Custom DSI commands types
-------------------------------------------------------------------------- */

#define DSI_CMD_CUSTOM_DELAY                        0xFF
#define DSI_CMD_CUSTOM_COLOR_FILL                   0xFE
#define DSI_CMD_CUSTOM_BROADCAST                    0xFD

#define DSI_CMD_CUSTOM_COLOR_FILL_PAYLOAD_LENGTH    (3)

#define DSI_GET_DRIVER_CTX(eDisplayId)              (&gDsiDriverCtx[((eDisplayId)<MDP_DISPLAY_MAX)?(eDisplayId):0])

#define DSI_CORE_CLOCK_MAPPING(DsiDeviceId)         ((DsiDeviceId == DSI_DeviceID_0) ? MDP_CLOCKTYPE_DSI0 : MDP_CLOCKTYPE_DSI1)

/*------------------------------------------------------------------------
Local Prototypes
-------------------------------------------------------------------------- */
static MDP_Status SendPanelXMLSequence(DSI_DriverCtx *pDriverCtx, void *pDSICommandBuffer, MDP_Panel_AttrType *pPanelConfig);
static MDP_Status SendPanelPPSRawBuffer(DSI_DriverCtx *pDriverCtx, MDP_Panel_AttrType *pPanelConfig);
MDP_Status DsiPanelSendCommandSequence(MDP_Panel_AttrType *pPanelInfo, MdpPanelCommandType eCommand, void *pCustomCommand, uint32 uFlags);

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_Read()
** 
** DESCRIPTION:
**   This allows to send the dsi read commands to the panel. 
** 
**
** -------------------------------------------------------------------- */
MDP_Status DSIDriver_Read(MDP_Display_IDType eDisplayId, uint8 uCmdType, void *pPayload, uint32 uPayloadSize, void *pReadData, uint32 *pReadSize, DSIDisplay_CmdFlags eFlags)
{
  MDP_Status          eStatus             = MDP_STATUS_OK;
  DSI_DriverCtx      *pDriverCtx          = DSI_GET_DRIVER_CTX(eDisplayId);
  MDP_Panel_AttrType *pPanelConfig        = MDP_GET_DISPLAYINFO(eDisplayId);
  DSI_ReadPacketType  sReadPacket;
  DSI_WritePacketType sWritePacket;
  uint32              uMaxPacketSize      = HAL_DSI_MAX_PACKETSIZE > 0 ? HAL_DSI_MAX_PACKETSIZE : DSI_READ_MAX_PACKET_SIZE;

  MDP_OSAL_MEMZERO(&sWritePacket, sizeof(DSI_WritePacketType));
  MDP_OSAL_MEMZERO(&sReadPacket,  sizeof(DSI_ReadPacketType));

  if (*pReadSize > uMaxPacketSize)
  {
    /* Max support packet size except check sum and header */
    sReadPacket.uReadPacketBufferSize = uMaxPacketSize;
  }
  else
  {
    sReadPacket.uReadPacketBufferSize = *pReadSize;
  }

  /* Setting or not setting max packet size during dsi read */
  if ((pPanelConfig->uAttrs.sDsi.uFlags & MDP_PANEL_DSI_FLAG_ENABLE_MAX_DSI_READ_SIZE) ||
      (eFlags                           & DSI_DISPLAY_CMDFLAG_MAXPACKETSIZE))
  {
    uint8 txBuffer[2] = {(sReadPacket.uReadPacketBufferSize &  0xFF),
                         (sReadPacket.uReadPacketBufferSize >> 0x08)};

    sWritePacket.eDisplayVC           = DSI_Display_VC_0;
    sWritePacket.uCmdDataType         = DSI_CMDMODE_DT_SETMAXRETSIZE;
    sWritePacket.uPayloadLen          = 2;
    sWritePacket.puPayload            = (uint8*)txBuffer;
    sWritePacket.bQueuePacket         = FALSE;

    if (DSI_STATUS_SUCCESS != DSI_Display_ClientWrite(pDriverCtx->hDisplayHandle[0], &sWritePacket))
    {
      DSI_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Failed to send max return size packet!\n");
    }
  }

  sReadPacket.eDisplayVC            = DSI_Display_VC_0;
  sReadPacket.uReadCmdDT            = uCmdType;
  sReadPacket.uReadParamInByte      = uPayloadSize;
  sReadPacket.puReadParam           = (uint8*)pPayload;
  sReadPacket.puReadPacket          = (uint8*)pReadData;
  sReadPacket.uRetPacketByte        = 0;

  /* Configure the DSI scheduling line number */
  if (eFlags & DSI_DISPLAY_CMDFLAG_DMA_SCHEDULE)
  {
    sReadPacket.uDmaScheduleLine = pPanelConfig->sActiveTiming.uVsyncBackPorchLines +
                                   pPanelConfig->sActiveTiming.uVsyncPulseWidthLines +
                                   pPanelConfig->uDisplayHeight;

    if ((0 == pPanelConfig->uAttrs.sDsi.uDmaScheduleLine) ||
        (pPanelConfig->uAttrs.sDsi.uDmaScheduleLine > pPanelConfig->sActiveTiming.uVsyncFrontPorchLines))
    {
      sReadPacket.uDmaScheduleLine += MDP_MIN(DSI_DMA_CMD_DEFAULT_SCHEDULE_LINE, pPanelConfig->sActiveTiming.uVsyncFrontPorchLines);
    }
    else
    {
      sReadPacket.uDmaScheduleLine += pPanelConfig->uAttrs.sDsi.uDmaScheduleLine;
    }
  }
  if (DSI_STATUS_SUCCESS != DSI_Display_ClientRead(pDriverCtx->hDisplayHandle[0], &sReadPacket))
  {
    eStatus = MDP_STATUS_FAILED;
  }
  else
  {
    // return number of bytes in the read buffer 
    *pReadSize = sReadPacket.uRetPacketByte;
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_Write()
** 
** DESCRIPTION:
**   This allows to send the dsi write commands to the panel. 
** 
**
** -------------------------------------------------------------------- */
MDP_Status DSIDriver_Write(MDP_Display_IDType eDisplayId, uint8 uCmdType, void *pPayload, uint32 uPayloadSize, DSIDisplay_CmdFlags eFlags)
{
  MDP_Status           eMDPStatus   = MDP_STATUS_OK;
  DSI_StatusType       eDSIStatus   = DSI_STATUS_SUCCESS;
  DSI_DriverCtx       *pDriverCtx   = DSI_GET_DRIVER_CTX(eDisplayId);
  MDP_Panel_AttrType  *pPanelConfig = MDP_GET_DISPLAYINFO(eDisplayId);
  DSI_WritePacketType  sWritePacket;

  MDP_OSAL_MEMZERO(&sWritePacket, sizeof(DSI_WritePacketType));

  if (DSI_CMDMODE_DT_DSCWRITE1PARA == uCmdType)
  {
    sWritePacket.uPayloadLen = HAL_DSI_EMBEDDED_SHORTPACKET_PAYLOAD_SIZE;
  }
  else
  {
    sWritePacket.uPayloadLen = uPayloadSize;
  }

  sWritePacket.eDisplayVC           = DSI_Display_VC_0;
  sWritePacket.uCmdDataType         = uCmdType;
  sWritePacket.puPayload            = (uint8*)pPayload;
  sWritePacket.bQueuePacket         = FALSE;
  sWritePacket.uFlags               = (uint32)eFlags;

  if (NULL == pPanelConfig)
  {
    DSI_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: DSIDriver_Write: pPanelConfig is NULL!\n");
  }
  else
  {
    sWritePacket.bHighSpeedMode = (pPanelConfig->uAttrs.sDsi.bPacketTransferHS)?TRUE:FALSE;
  }

  eDSIStatus = DSI_Display_ClientWrite(pDriverCtx->hDisplayHandle[0], &sWritePacket);
  if (DSI_STATUS_SUCCESS != eDSIStatus)
  {
    eMDPStatus = MDP_STATUS_FAILED;
    DSI_Log_Message(MDP_LOGLEVEL_ERROR,
	    "DisplayDxe: DSIDriver_Write: DSI_Display_ClientWrite failed! DSI Status: 0x%x\n",
		eDSIStatus);
  }

  return eMDPStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_Init()
** 
** DESCRIPTION:
**   Initialize the DSI Core
**
*//* -------------------------------------------------------------------- */
MDP_Status DSIDriver_Init(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status            eStatus       = MDP_STATUS_OK;
  DSI_DeviceConfigType  sDeviceConfig;
  DSI_DriverCtx        *pDriverCtx    = DSI_GET_DRIVER_CTX(pPanelConfig->eDisplayId);
  void                 *pDSIBuffer    = pDriverCtx->pDSIBuffer;
  uint32                uDevIdx;
  uint32                uFlags        = 0;

  if (0 == (pPanelConfig->eDisplayFlags & MDP_PANEL_FLAG_DSI_DCS_FIFO_ONLY))
  {
    if (NULL == pDSIBuffer)
    {
      if (NULL == (pDSIBuffer = MDP_OSAL_CALLOC(DSI_DMA_BUFFER_SIZE)))
      {
        DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: MDP_OSAL_CALLOC failed\n");
        eStatus = MDP_STATUS_NO_RESOURCES;
      }
    }
    uFlags = DSI_DEVICE_FLAGS_DSI_DCS_DMA_ONLY;
  }

  if (MDP_STATUS_OK == eStatus)
  {

    if (0x3 == pPanelConfig->uAttrs.sDsi.uControllerMappingMask)
    {
      pDriverCtx->bDualDSI           = TRUE;
      pDriverCtx->uNumDSIControllers = DSI_DeviceID_MAX;
    }
    else
    {
      pDriverCtx->uNumDSIControllers = 1;
    }


    for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)
    {
      DSI_Device_IDType eDSIDeviceId = (DSI_Device_IDType)pPanelConfig->uAttrs.sDsi.uControllerMapping[uDevIdx];

      if (DSI_DeviceID_MAX <= eDSIDeviceId)
      {
        DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: Invalid DSI Device ID %d\n", eDSIDeviceId);
        eStatus = MDP_STATUS_FAILED;
        break;
      }

      if (MDP_STATUS_OK != MDPSetupClocks(DSI_CORE_CLOCK_MAPPING(eDSIDeviceId), NULL))
      {
        DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: DSIDriver_Init(MDP_CLOCKTYPE_DSI%d) failed\n", eDSIDeviceId);
        // Non fatal, only a warning .
      }
    
      MDP_OSAL_MEMZERO(&sDeviceConfig, sizeof(DSI_DeviceConfigType));    
      sDeviceConfig.eDeviceID                            = eDSIDeviceId;
      sDeviceConfig.bDualDsi                             = pDriverCtx->bDualDSI;
      sDeviceConfig.bLittleEndian                        = TRUE;
      sDeviceConfig.bNonCompliantMode                    = FALSE;
      sDeviceConfig.bEnableCRCCheck                      = FALSE;
      sDeviceConfig.bEnableECCCheck                      = FALSE;
      sDeviceConfig.sMemoryConfig.pCPUAddress            = pDSIBuffer;
      sDeviceConfig.sMemoryConfig.sMDPAddress.iQuadPart  = (int64)pDSIBuffer;
      sDeviceConfig.sMemoryConfig.uSize                  = DSI_DMA_BUFFER_SIZE;
      sDeviceConfig.bCPhyMode                            = pPanelConfig->uAttrs.sDsi.bCPhyMode;
      sDeviceConfig.bEnableLP11AtInit                    = pPanelConfig->uAttrs.sDsi.bLP11AtInit;
      sDeviceConfig.bPhyDCDCMode                         = pPanelConfig->uAttrs.sDsi.bPhyDCDCMode;
      sDeviceConfig.uClockStrengthHS                     = pPanelConfig->uAttrs.sDsi.uClockStrengthHS;
      sDeviceConfig.uDataStrengthHS                      = pPanelConfig->uAttrs.sDsi.uDataStrengthHS;
      sDeviceConfig.uDataStrengthLP                      = pPanelConfig->uAttrs.sDsi.uDataStrengthLP;
      sDeviceConfig.uNullPacketInsertionLength           = pPanelConfig->uAttrs.sDsi.uNullPacketInsertionLength;
      sDeviceConfig.uFlags                               = uFlags; 
      sDeviceConfig.eSplitLinkConfig                     = (DSI_SplitLinkConfigType)pPanelConfig->uAttrs.sDsi.eSplitLinkConfig;

      if (DSI_STATUS_SUCCESS != DSI_Device_Open(&sDeviceConfig, &(pDriverCtx->hDSIHandle[uDevIdx])))
      {
        eStatus = MDP_STATUS_FAILED;
        break;
      }
    }

    // Check whether I2C needs to be initialized
    if ((MDP_STATUS_OK == eStatus) && 
        (NULL          != pPanelConfig->uAttrs.sDsi.sI2CConfig.pI2CInitSequence))
    {
      if (MDP_STATUS_OK != (eStatus = I2CDriver_Init(&pPanelConfig->uAttrs.sDsi.sI2CConfig)))
      {
        DSI_Log_Message(MDP_LOGLEVEL_ERROR, "DisplayDxe: I2CDriver_Init() failed eStatus=%d \n", eStatus);
      }
    }
  }
  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_Close()
** 
** DESCRIPTION:
**   Deinitialize the DSI Core
**
*//* -------------------------------------------------------------------- */
void DSIDriver_Close(MDP_Display_IDType eDisplayId)
{
  DSI_DriverCtx        *pDriverCtx = DSI_GET_DRIVER_CTX(eDisplayId);
  uint32                uDevIdx    = 0;

  if (0 == pDriverCtx->uNumDSIControllers)
  {
    pDriverCtx->uNumDSIControllers = 1;
  }

  // Only send a termination sequence if the panel has been setup already
  // First loop to close all DSI display handles, turning off DSI Clocks 
  // first to avoid turning off DSI PLL source before turning off DSI 1 clock
  for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)
  {
    DSI_HandleType        hDisplay = pDriverCtx->hDisplayHandle[uDevIdx];
    DSI_Device_IDType     eDeviceId;
    DSI_Channel_IDType    eChannelId;

    dsiShared_Handle2DisplayID(hDisplay, &eDeviceId, &eChannelId);
   
    if (eChannelId != DSI_ChannelID_NONE)
    {
      if (DSI_STATUS_SUCCESS != DSI_Display_Close(pDriverCtx->hDisplayHandle[uDevIdx]))
      {
        DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: DSI_Display_Close() failed on device%d\n", uDevIdx );
        break;
      }
      // Turn off DSI Clock turned on in DSIDriver_Init()
      if (MDP_STATUS_OK != MDPDisableClocks(DSI_CORE_CLOCK_MAPPING(eDeviceId)))
      {
        DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: DSIDriver_Close(MDP_CLOCKTYPE_DSI%d) failed\n", uDevIdx);
        // Non fatal, only a warning .
      }
    }
  }

  // Second loop to close all DSI device handles
  for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)
  {
    if (DSI_STATUS_SUCCESS != DSI_Device_Close(pDriverCtx->hDSIHandle[uDevIdx], 0x0))
    {
      DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: DSI_Device_Close() failed on device%d\n", uDevIdx );
      break;
    }
  }
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: ConvertPanelColorToDSIColorFormat()
**
** DESCRIPTION:
**   Convert Panel CorlorFormat to DSI ColorFormat
**
*//* -------------------------------------------------------------------- */

DSI_ColorFormatType ConvertPanelColorToDSIColorFormat(MDP_ColorFormat_Type eColorFormat)
{
  DSI_ColorFormatType eDsiColorFormat = DSI_COLOR_RGB_888_24BPP;
  
  switch (eColorFormat)
  {
    case MDP_COLORFORMAT_RGB_444_12BPP:
      eDsiColorFormat = DSI_COLOR_RGB_444_12BPP;
    break;
    case MDP_COLORFORMAT_RBG_444_12BPP:
      eDsiColorFormat = DSI_COLOR_RBG_444_12BPP;
    break;
    case MDP_COLORFORMAT_BGR_444_12BPP:
      eDsiColorFormat = DSI_COLOR_BGR_444_12BPP;
    break;
    case MDP_COLORFORMAT_BRG_444_12BPP:
      eDsiColorFormat = DSI_COLOR_BRG_444_12BPP;
    break;
    case MDP_COLORFORMAT_GRB_444_12BPP:
      eDsiColorFormat = DSI_COLOR_GRB_444_12BPP;
    break;
    case MDP_COLORFORMAT_GBR_444_12BPP:
      eDsiColorFormat = DSI_COLOR_GRB_444_12BPP;
    break;
    case MDP_COLORFORMAT_RGB_565_16BPP:
      eDsiColorFormat = DSI_COLOR_RGB_565_16BPP;
    break;
    case MDP_COLORFORMAT_RBG_565_16BPP:
      eDsiColorFormat = DSI_COLOR_RBG_565_16BPP;
    break;
    case MDP_COLORFORMAT_BGR_565_16BPP:
      eDsiColorFormat = DSI_COLOR_BGR_565_16BPP;
    break;
    case MDP_COLORFORMAT_BRG_565_16BPP:
      eDsiColorFormat = DSI_COLOR_BRG_565_16BPP;
    break;
    case MDP_COLORFORMAT_GRB_565_16BPP:
      eDsiColorFormat = DSI_COLOR_GRB_565_16BPP;
    break;
    case MDP_COLORFORMAT_GBR_565_16BPP:
      eDsiColorFormat = DSI_COLOR_GRB_565_16BPP;
    break;
    case MDP_COLORFORMAT_RGB_666_18BPP:
      eDsiColorFormat = DSI_COLOR_RGB_666_18BPP;
    break;
    case MDP_COLORFORMAT_RBG_666_18BPP:
      eDsiColorFormat = DSI_COLOR_RBG_666_18BPP;
    break;
    case MDP_COLORFORMAT_BGR_666_18BPP:
      eDsiColorFormat = DSI_COLOR_BGR_666_18BPP;
    break;
    case MDP_COLORFORMAT_BRG_666_18BPP:
      eDsiColorFormat = DSI_COLOR_BRG_666_18BPP;
    break;
    case MDP_COLORFORMAT_GRB_666_18BPP:
      eDsiColorFormat = DSI_COLOR_GRB_666_18BPP;
    break;
    case MDP_COLORFORMAT_GBR_666_18BPP:
      eDsiColorFormat = DSI_COLOR_GBR_666_18BPP;
    break;
    case MDP_COLORFORMAT_RGB_666_24BPP:
      eDsiColorFormat = DSI_COLOR_RGB_666_24BPP;
    break;
    case MDP_COLORFORMAT_RBG_666_24BPP:
      eDsiColorFormat = DSI_COLOR_RBG_666_24BPP;
    break;
    case MDP_COLORFORMAT_BGR_666_24BPP:
      eDsiColorFormat = DSI_COLOR_BGR_666_24BPP;
    break;
    case MDP_COLORFORMAT_BRG_666_24BPP:
      eDsiColorFormat = DSI_COLOR_BRG_666_24BPP;
    break;
    case MDP_COLORFORMAT_GRB_666_24BPP:
      eDsiColorFormat = DSI_COLOR_GRB_666_24BPP;
    break;
    case MDP_COLORFORMAT_GBR_666_24BPP:
      eDsiColorFormat = DSI_COLOR_GBR_666_24BPP;
    break;
    case MDP_COLORFORMAT_RGB_888_24BPP:
      eDsiColorFormat = DSI_COLOR_RGB_888_24BPP;
    break;
    case MDP_COLORFORMAT_RBG_888_24BPP:
      eDsiColorFormat = DSI_COLOR_RBG_888_24BPP;
    break;
    case MDP_COLORFORMAT_BGR_888_24BPP:
      eDsiColorFormat = DSI_COLOR_BGR_888_24BPP;
    break;
    case MDP_COLORFORMAT_BRG_888_24BPP:
      eDsiColorFormat = DSI_COLOR_BRG_888_24BPP;
    break;
    case MDP_COLORFORMAT_GRB_888_24BPP:
      eDsiColorFormat = DSI_COLOR_GRB_888_24BPP;
    break;
    case MDP_COLORFORMAT_GBR_888_24BPP:
      eDsiColorFormat = DSI_COLOR_GBR_888_24BPP;
    break;
    case MDP_COLORFORMAT_RGB_101010_30BPP:
      eDsiColorFormat = DSI_COLOR_RGB_101010_30BPP;
    break;
    case MDP_COLORFORMAT_RBG_101010_30BPP:
      eDsiColorFormat = DSI_COLOR_RBG_101010_30BPP;
    break;
    case MDP_COLORFORMAT_BGR_101010_30BPP:
      eDsiColorFormat = DSI_COLOR_BGR_101010_30BPP;
    break;
    case MDP_COLORFORMAT_BRG_101010_30BPP:
      eDsiColorFormat = DSI_COLOR_BRG_101010_30BPP;
    break;
    case MDP_COLORFORMAT_GRB_101010_30BPP:
      eDsiColorFormat = DSI_COLOR_GRB_101010_30BPP;
    break;
    case MDP_COLORFORMAT_GBR_101010_30BPP:
      eDsiColorFormat = DSI_COLOR_GBR_101010_30BPP;
    break;
    default:
      DSI_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: an invalid mapping\n");
    break;
  }
  return eDsiColorFormat;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_SetMode()
** 
** DESCRIPTION:
**   Initialize the DSI Core
**
*//* -------------------------------------------------------------------- */
MDP_Status DSIDriver_SetMode(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status            eStatus                =  MDP_STATUS_OK;
  uint32                i                      =  0;
  DSI_DisplayConfigType sDisplayConfig;
  DSI_DriverCtx        *pDriverCtx             = DSI_GET_DRIVER_CTX(pPanelConfig->eDisplayId);
  uint32                uDevIdx                = 0;
  uint32                uInterfaceWidth        = 0;
  uint32                uDscBytesInSlice       = 0;
  uint32                uDscSlicePerInterface  = 0;
  bool32                bSplitLinkEnabled      = FALSE;

  /* Sanity check for split check. */
  if (MDP_SPLIT_LINK_CONFIG_DISABLED != pPanelConfig->uAttrs.sDsi.eSplitLinkConfig)
  {
    if (MDP_INTERFACE_DUAL == pPanelConfig->uNumInterfaces)
    {
      DSI_Log_Message(MDP_LOGLEVEL_ERROR, "DSIDriver_SetMode: Split link can only be used on single interface\n");
    }
    else if ((TRUE == pPanelConfig->sDSCConfig.bDSCEnable) &&
             (2    == pPanelConfig->sDSCConfig.uDSCEncodersNum))
    {
      DSI_Log_Message(MDP_LOGLEVEL_ERROR, "DSIDriver_SetMode: Split link is only supported in DSC merge\n");
    }
    else 
    {
      bSplitLinkEnabled = TRUE;
    }
  }

  for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)
  {
    MDP_OSAL_MEMZERO(&sDisplayConfig, sizeof(DSI_DisplayConfigType));
    sDisplayConfig.sDisplayInfo.eDisplayId        = (DSI_Channel_IDType)pPanelConfig->uAttrs.sDsi.eChannelId;
    sDisplayConfig.sDisplayInfo.eDisplayVC        = (DSI_Display_VCType)pPanelConfig->uAttrs.sDsi.eDisplayVC;
    sDisplayConfig.sDisplayInfo.eColorFormat      = ConvertPanelColorToDSIColorFormat(pPanelConfig->uAttrs.sDsi.eColorFormat);
    sDisplayConfig.sDisplayInfo.uNumLanes         = pPanelConfig->uAttrs.sDsi.uDataLaneNum;
    sDisplayConfig.sDisplayInfo.bCPhyMode         = pPanelConfig->uAttrs.sDsi.bCPhyMode;
    sDisplayConfig.sDisplayInfo.uRefreshRate      = pPanelConfig->uAttrs.sDsi.uRefreshRate; 
    sDisplayConfig.sDisplayInfo.uBitClockFreq     = pPanelConfig->uAttrs.sDsi.uBitClockFrequency;
    sDisplayConfig.sDisplayInfo.bDisableEotp      = pPanelConfig->uAttrs.sDsi.bDisableEotpAfterHSXfer;
    sDisplayConfig.sDisplayInfo.uInitMasterTime   = pPanelConfig->uAttrs.sDsi.uInitMasterTime;  
    sDisplayConfig.sDisplayInfo.uEscapeDivisor    = pPanelConfig->uAttrs.sDsi.uEscapeClockDivisor;
    sDisplayConfig.sDisplayInfo.uEscapeFreq       = pPanelConfig->uAttrs.sDsi.uEscapeClockFreq;
    sDisplayConfig.sDisplayInfo.eSSCConfig        = (DSI_SSCConfigType)pPanelConfig->uAttrs.sDsi.eSSCConfig;
    sDisplayConfig.sDisplayInfo.ePHYTimingMargin  = (HAL_DSI_PhyTimingMargin)pPanelConfig->uAttrs.sDsi.uPHYTimingMargin;
  
    MDP_OSAL_MEMCPY(sDisplayConfig.sDisplayInfo.sDynamicRefreshInfo.uDynamicRefreshRates, pPanelConfig->uAttrs.sDsi.uDynamicRefreshRates, sizeof(sDisplayConfig.sDisplayInfo.sDynamicRefreshInfo.uDynamicRefreshRates));

    // Split link will divide total number lane in half for each sublink.  
    if (TRUE == bSplitLinkEnabled)
    {
      sDisplayConfig.sDisplayInfo.uNumLanes /= 2;
    }

    // Assign lanes
    if (pPanelConfig->uAttrs.sDsi.uLaneRemap >= DSI_LANE_SWAPNUM)
    {
      pPanelConfig->uAttrs.sDsi.uLaneRemap = 0;
      DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: DSIDriver_SetMode() Incorrect Lane remap parameter, defalting to 0\n" );
    }
    for (i=0;i<(DSI_LaneMap_MAX-1);i++)
    {
      if (i<pPanelConfig->uAttrs.sDsi.uDataLaneNum)
      {
        sDisplayConfig.eDisplayLane[i] = sDisplayLaneSetting[pPanelConfig->uAttrs.sDsi.uLaneRemap][i];
      }
      else
      {
        sDisplayConfig.eDisplayLane[i] = DSI_LaneMap_NONE;
      }
    }
    
    /* DSI Split Display or Split link display */
    if ((TRUE == pDriverCtx->bDualDSI) ||
        (TRUE == bSplitLinkEnabled))
    {
      uInterfaceWidth = pPanelConfig->uDisplayWidth / 2;
    }
    else
    {
      uInterfaceWidth = pPanelConfig->uDisplayWidth;
    }

    if ((TRUE == pPanelConfig->sDSCConfig.bDSCEnable) &&
        (1 < pPanelConfig->sDSCConfig.uDSCCompressionRatio))
    {
      sDisplayConfig.sDisplayInfo.bTwoPixelsPerPclk = TRUE;   /* DSC, enable two pixels per pclk */

      /* both uDSCSliceWidthByte and uDSCSlicePerPacket are calcualted at MDPSetupDSCProperty() */
      uDscBytesInSlice       = pPanelConfig->sDSCConfig.uDSCSliceWidthByte;  /* bytes in slice */
      uDscSlicePerInterface  = pPanelConfig->sDSCEncCfg.uSlicePerInterface;
    }

    if ((pPanelConfig->ePhysConnect == MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO) ||
        (pPanelConfig->ePhysConnect == MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO))
    {
      sDisplayConfig.sVideoModeConfg.bEnable                            = TRUE;
      sDisplayConfig.sDisplayInfo.iVisWidthPx                           = pPanelConfig->uDisplayWidth +
                                                                          pPanelConfig->sActiveTiming.uHLeftBorderDClk +
                                                                          pPanelConfig->sActiveTiming.uHRightBorderDClk;
      sDisplayConfig.sDisplayInfo.iVisHeightPx                          = pPanelConfig->uDisplayHeight +
                                                                          pPanelConfig->sActiveTiming.uVTopBorderLines +
                                                                          pPanelConfig->sActiveTiming.uVBottomBorderLines;
      sDisplayConfig.sDisplayInfo.iBlankHeightPx                        = pPanelConfig->sActiveTiming.uVsyncPulseWidthLines +
                                                                          pPanelConfig->sActiveTiming.uVsyncBackPorchLines +
                                                                          pPanelConfig->sActiveTiming.uVsyncFrontPorchLines;
      sDisplayConfig.sDisplayInfo.iBlankWidthPx                         = pPanelConfig->sActiveTiming.uHsyncPulseWidthDclk + 
                                                                          pPanelConfig->sActiveTiming.uHsyncBackPorchDclk + 
                                                                          pPanelConfig->sActiveTiming.uHsyncFrontPorchDclk;
      sDisplayConfig.sVideoModeConfg.eVideoTraffic                      = (DSI_TrafficModeType) pPanelConfig->uAttrs.sDsi.eTrafficMode;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iHsyncPulseWidthDclk  = pPanelConfig->sActiveTiming.uHsyncPulseWidthDclk;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iHsyncBackPorchDclk   = pPanelConfig->sActiveTiming.uHsyncBackPorchDclk;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iHsyncFrontPorchDclk  = pPanelConfig->sActiveTiming.uHsyncFrontPorchDclk;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iHsyncSkewDclk        = pPanelConfig->sActiveTiming.uHsyncSkewDclk;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iVsyncPulseWidthLines = pPanelConfig->sActiveTiming.uVsyncPulseWidthLines;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iVsyncBackPorchLine   = pPanelConfig->sActiveTiming.uVsyncBackPorchLines;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iVsyncFrontPorchLine  = pPanelConfig->sActiveTiming.uVsyncFrontPorchLines;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iVsyncSkewDclk        = 0;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iVsyncStart           = 0;
      sDisplayConfig.sVideoModeConfg.sVideoTiming.iVsyncEnd             = 0;
      // Panel power settings
      sDisplayConfig.sVideoModeConfg.sPowerOptions.bSendHsaHseAfterVsVe         = pPanelConfig->uAttrs.sDsi.bSendHsaHseAfterVsVe;
      sDisplayConfig.sVideoModeConfg.sPowerOptions.bEnableLowPowerModeInHFP     = pPanelConfig->uAttrs.sDsi.bLowPowerModeInHFP;
      sDisplayConfig.sVideoModeConfg.sPowerOptions.bEnableLowPowerModeInHBP     = pPanelConfig->uAttrs.sDsi.bLowPowerModeInHBP;
      sDisplayConfig.sVideoModeConfg.sPowerOptions.bEnableLowPowerModeInHSA     = pPanelConfig->uAttrs.sDsi.bLowPowerModeInHSA;
      sDisplayConfig.sVideoModeConfg.sPowerOptions.bEnableLowPowerModeInBLLPEOF = pPanelConfig->uAttrs.sDsi.bLowPowerModeInBLLPEOF;
      sDisplayConfig.sVideoModeConfg.sPowerOptions.bEnableLowPowerModeInBLLP    = pPanelConfig->uAttrs.sDsi.bLowPowerModeInBLLP; 

      if (pPanelConfig->sDSCConfig.bDSCEnable)
      {
        if (1 < pPanelConfig->sDSCConfig.uDSCCompressionRatio)
        {
          // DSC settings for the DSI controller
          // uDSCCompressionRatio multiplied by 1000 before
          sDisplayConfig.sDisplayInfo.iVisWidthPx                        = HAL_DSI_Phy_Roundup((float)(sDisplayConfig.sDisplayInfo.iVisWidthPx * 1000) / pPanelConfig->sDSCConfig.uDSCCompressionRatio);
          sDisplayConfig.sVideoModeConfg.sDSCVideoConfig.uDscEnable      = pPanelConfig->sDSCConfig.bDSCEnable;
          sDisplayConfig.sVideoModeConfg.sDSCVideoConfig.uDscStreamId    = 0;

          // The number of valid bytes at the end of the last horizontal slice width of data, 0 = 3 bytes, 1 = 1 byte, 2 = 2 bytes.
          sDisplayConfig.sVideoModeConfg.sDSCVideoConfig.uDscEolByteNum  = (uDscBytesInSlice * uDscSlicePerInterface) % 3;

          if (0 != pPanelConfig->sDSCConfig.uDSCSlicePerPacket)
          {
              sDisplayConfig.sVideoModeConfg.sDSCVideoConfig.uDscPktPerLine  = (uDscSlicePerInterface / pPanelConfig->sDSCConfig.uDSCSlicePerPacket) / 2;
              // This is the total WC per DSI interface, need to be multiplied with DSC Slice per interface, and divided by slice per packet.
              sDisplayConfig.sVideoModeConfg.sDSCVideoConfig.uDscBytesPerPkt = (pPanelConfig->sDSCEncCfg.uBytePerPkt * uDscSlicePerInterface) / pPanelConfig->sDSCConfig.uDSCSlicePerPacket;
          }
          else
          {
              sDisplayConfig.sVideoModeConfg.sDSCVideoConfig.uDscPktPerLine  = uDscSlicePerInterface / 2;
              // This is the total WC per DSI interface, need to be multiplied with DSC Slice per interface, and divided by slice per packet.
              sDisplayConfig.sVideoModeConfg.sDSCVideoConfig.uDscBytesPerPkt = (pPanelConfig->sDSCEncCfg.uBytePerPkt * uDscSlicePerInterface);

          }
        }
      }
    }
    else // QDI_DISPLAY_CONNECT_PRIMARY_DSI_CMD
    {
      sDisplayConfig.sDisplayInfo.iVisWidthPx    = pPanelConfig->uDisplayWidth;
      sDisplayConfig.sDisplayInfo.iBlankWidthPx  = pPanelConfig->sActiveTiming.uHsyncPulseWidthDclk +
                                                    pPanelConfig->sActiveTiming.uHsyncBackPorchDclk  +
                                                    pPanelConfig->sActiveTiming.uHsyncFrontPorchDclk;
      sDisplayConfig.sDisplayInfo.iVisHeightPx   = pPanelConfig->uDisplayHeight;
      sDisplayConfig.sDisplayInfo.iBlankHeightPx = pPanelConfig->sActiveTiming.uVsyncPulseWidthLines  +
                                                    pPanelConfig->sActiveTiming.uVsyncBackPorchLines   +
                                                    pPanelConfig->sActiveTiming.uVsyncFrontPorchLines;
      sDisplayConfig.sCmdModeConfg.uIdleTime     = pPanelConfig->uAttrs.sDsi.uCommandModeIdleTime;

      if (pPanelConfig->sDSCConfig.bDSCEnable)
      {
        if (1 < pPanelConfig->sDSCConfig.uDSCCompressionRatio)
        {
          /* uDSCCompressionRatio multiplied by 1000 before */ 
          sDisplayConfig.sDisplayInfo.iVisWidthPx                      = HAL_DSI_Phy_Roundup((float)(sDisplayConfig.sDisplayInfo.iVisWidthPx * 1000) / pPanelConfig->sDSCConfig.uDSCCompressionRatio);

          // DSC settings for the DSI controller
          sDisplayConfig.sCmdModeConfg.sDSCCmdConfig.uDscEnable        = pPanelConfig->sDSCConfig.bDSCEnable;
          sDisplayConfig.sCmdModeConfg.sDSCCmdConfig.uDscStreamId      = 0;
          
          sDisplayConfig.sDisplayInfo.uHeightTotal                     = pPanelConfig->uDisplayHeight;
          sDisplayConfig.sDisplayInfo.uWidthTotal                      = pPanelConfig->sDSCEncCfg.uPclkPerLine;
          sDisplayConfig.sDisplayInfo.uWordCount                       = pPanelConfig->sDSCEncCfg.uBytePerPkt + 1;  /* 1 is for insert DCS command byte */
          sDisplayConfig.sCmdModeConfg.sDSCCmdConfig.uDscBytesInSlice  = uDscBytesInSlice;

          // The number of valid bytes at the end of the last horizontal slice width of data, 0 = 3 bytes, 1 = 1 byte, 2 = 2 bytes.
          sDisplayConfig.sCmdModeConfg.sDSCCmdConfig.uDscEolByteNum    = (uDscBytesInSlice * uDscSlicePerInterface) % 3;

          if (0 != pPanelConfig->sDSCConfig.uDSCSlicePerPacket)
          {
              sDisplayConfig.sCmdModeConfg.sDSCCmdConfig.uDscPktPerLine = (uDscSlicePerInterface / pPanelConfig->sDSCConfig.uDSCSlicePerPacket) / 2;
          }
          else
          {
              sDisplayConfig.sCmdModeConfg.sDSCCmdConfig.uDscPktPerLine = uDscSlicePerInterface / 2;
          }
        }
        else
        {
            eStatus                                        = MDP_STATUS_BAD_PARAM;
            break;
        }
      }
      else
      {
        sDisplayConfig.sDisplayInfo.uHeightTotal = pPanelConfig->uDisplayHeight;
        sDisplayConfig.sDisplayInfo.uWidthTotal  = uInterfaceWidth;
        sDisplayConfig.sDisplayInfo.uWordCount   = uInterfaceWidth * 3 + 1;
      }
    }

    if ( MDP_STATUS_OK == eStatus)
    {
      // Timing Override
      sDisplayConfig.sTimingOverride.bTimingHSZeroOverride    = pPanelConfig->uAttrs.sDsi.bTimingHSZeroOverride;
      sDisplayConfig.sTimingOverride.uTimingHSZeroValue       = pPanelConfig->uAttrs.sDsi.uTimingHSZeroValue;
      sDisplayConfig.sTimingOverride.bTimingHSExitOverride    = pPanelConfig->uAttrs.sDsi.bTimingHSExitOverride;
      sDisplayConfig.sTimingOverride.uTimingHSExitValue       = pPanelConfig->uAttrs.sDsi.uTimingHSExitValue;
      sDisplayConfig.sTimingOverride.bTimingHSPrepareOverride = pPanelConfig->uAttrs.sDsi.bTimingHSPrepareOverride;
      sDisplayConfig.sTimingOverride.uTimingHSPrepareValue    = pPanelConfig->uAttrs.sDsi.uTimingHSPrepareValue;
      sDisplayConfig.sTimingOverride.bTimingHSTrailOverride   = pPanelConfig->uAttrs.sDsi.bTimingHSTrailOverride;
      sDisplayConfig.sTimingOverride.uTimingHSTrailValue      = pPanelConfig->uAttrs.sDsi.uTimingHSTrailValue;
      sDisplayConfig.sTimingOverride.bTimingHSRequestOverride = pPanelConfig->uAttrs.sDsi.bTimingHSRequestOverride;
      sDisplayConfig.sTimingOverride.uTimingHSRequestValue    = pPanelConfig->uAttrs.sDsi.uTimingHSRequestValue;
      sDisplayConfig.sTimingOverride.bTimingCLKZeroOverride   = pPanelConfig->uAttrs.sDsi.bTimingCLKZeroOverride;
      sDisplayConfig.sTimingOverride.uTimingCLKZeroValue      = pPanelConfig->uAttrs.sDsi.uTimingCLKZeroValue;
      sDisplayConfig.sTimingOverride.bTimingCLKTrailOverride  = pPanelConfig->uAttrs.sDsi.bTimingCLKTrailOverride;
      sDisplayConfig.sTimingOverride.uTimingCLKTrailValue     = pPanelConfig->uAttrs.sDsi.uTimingCLKTrailValue;
      sDisplayConfig.sTimingOverride.bTimingCLKPrepareOverride= pPanelConfig->uAttrs.sDsi.bTimingCLKPrepareOverride;
      sDisplayConfig.sTimingOverride.uTimingCLKPrepareValue   = pPanelConfig->uAttrs.sDsi.uTimingCLKPrepareValue;
      sDisplayConfig.sTimingOverride.bTimingCLKPreOverride    = pPanelConfig->uAttrs.sDsi.bTimingCLKPreOverride;
      sDisplayConfig.sTimingOverride.uTimingCLKPreValue       = pPanelConfig->uAttrs.sDsi.uTimingCLKPreValue;
      sDisplayConfig.sTimingOverride.bTimingCLKPostOverride   = pPanelConfig->uAttrs.sDsi.bTimingCLKPostOverride;
      sDisplayConfig.sTimingOverride.uTimingCLKPostValue      = pPanelConfig->uAttrs.sDsi.uTimingCLKPostValue;
      sDisplayConfig.sTimingOverride.bTimingTAGoOverride      = pPanelConfig->uAttrs.sDsi.bTimingTAGoOverride;
      sDisplayConfig.sTimingOverride.uTimingTAGoValue         = pPanelConfig->uAttrs.sDsi.uTimingTAGoValue;
      sDisplayConfig.sTimingOverride.bTimingTASureOverride    = pPanelConfig->uAttrs.sDsi.bTimingTASureOverride;
      sDisplayConfig.sTimingOverride.uTimingTASureValue       = pPanelConfig->uAttrs.sDsi.uTimingTASureValue;
      sDisplayConfig.sTimingOverride.bTimingTAGetOverride     = pPanelConfig->uAttrs.sDsi.bTimingTAGetOverride;
      sDisplayConfig.sTimingOverride.uTimingTAGetValue        = pPanelConfig->uAttrs.sDsi.uTimingTAGetValue;

      /* DSI Split Display */ 
      if (TRUE == pDriverCtx->bDualDSI)
      {
        sDisplayConfig.sDisplayInfo.iVisWidthPx >>=1;
        sDisplayConfig.ePLLSourceType                      = DSI_PLL_CONFIG_SPLIT_SOURCE;
      }
      else
      {
        sDisplayConfig.ePLLSourceType                      = DSI_PLL_CONFIG_INDEPENDENT_SOURCE;

        if (TRUE == bSplitLinkEnabled)
        {
          sDisplayConfig.sDisplayInfo.iVisWidthPx >>= 1;
        }
      }

      sDisplayConfig.sCmdModeConfg.bEnable                 = TRUE;
      sDisplayConfig.sCmdModeConfg.eImageTrigger           = DSI_Display_ImageTrigger_NONE;
      sDisplayConfig.sCmdModeConfg.eCMDTrigger             = DSI_Display_CMDTrigger_SW;
      sDisplayConfig.sCmdModeConfg.sExtTEConfig.eExtTEMode = DSI_ExtTEMode_VS_EDGE;

      if (DSI_STATUS_SUCCESS != DSI_Display_Open(pDriverCtx->hDSIHandle[uDevIdx], &sDisplayConfig, &(pDriverCtx->hDisplayHandle[uDevIdx])))
      {
        eStatus = MDP_STATUS_FAILED;
        break;
      }
      else if (DSI_STATUS_SUCCESS != DSI_Display_Commit(pDriverCtx->hDSIHandle[uDevIdx], 0x0))
      {
        eStatus = MDP_STATUS_FAILED;
        break;
      }
    }
  }

  if (MDP_STATUS_OK == eStatus)
  {
    DSI_Display_ClockLaneType eClockLaneCfg = (DSI_Display_ClockLaneType)pPanelConfig->uAttrs.sDsi.uClockHSForceRequest;

    // Option to force the clock lane in to HS _before_ the init sequence. 
    if (DSI_Display_ClockLane_ForceHS == eClockLaneCfg)
    {
      DSI_PropertyParamsType  sDSIProp;
      
      MDP_OSAL_MEMZERO(&sDSIProp, sizeof(DSI_PropertyParamsType));
      sDSIProp.eLaneState = DSI_LANE_STATE_CLOCK_HS;

      for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)    
      {
        if (DSI_STATUS_SUCCESS != DSI_Display_SetProperty(pDriverCtx->hDisplayHandle[uDevIdx], DSI_DISPLAY_PROPERTYID_LANESTATE, &sDSIProp))
        {
          DSI_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Clock lane failed to enter HS pre-init\n");
        }
      }
    }

  
    // If video transfer is required during DCS transactions then do not send the initialization sequence as it 
    // will be sent when the pixel transfer begins.
    if (FALSE == pPanelConfig->uAttrs.sDsi.bForceCmdInVideoHS)
    {
      eStatus = SendPanelXMLSequence(pDriverCtx, pPanelConfig->uAttrs.sDsi.pInitBuffer, pPanelConfig);

      // If DSC is enabled then send the PPS command to the panel
      if ((TRUE == pPanelConfig->sDSCConfig.bDSCEnable) &&
          (0 == (pPanelConfig->eDisplayFlags & MDP_PANEL_FLAG_DISABLE_PPS_CMD)))
      {
          DsiPanelSendCommandSequence(pPanelConfig, MDP_PANEL_COMMAND_PPS, NULL, 0);
      }
    }

    // Send I2C init sequence if it is required
    if (NULL != pPanelConfig->uAttrs.sDsi.sI2CConfig.pI2CInitSequence)
    {
      if (MDP_STATUS_OK != I2CPanelSendCommandSequence(&pPanelConfig->uAttrs.sDsi.sI2CConfig, MDP_PANEL_COMMAND_INIT,  NULL, 0))
      {
        DSI_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Failed to send I2C command \n");
      }
    }

    // Option to force the clock lane in to HS _after_ the init sequence. (ignore any panel command sequence failures)
    if (DSI_Display_ClockLane_ForceHS_PostInit == eClockLaneCfg)
    {
      DSI_PropertyParamsType  sDSIProp;
      
      MDP_OSAL_MEMZERO(&sDSIProp, sizeof(DSI_PropertyParamsType));
      sDSIProp.eLaneState = DSI_LANE_STATE_CLOCK_HS;

      for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)    
      {
        if (DSI_STATUS_SUCCESS != DSI_Display_SetProperty(pDriverCtx->hDisplayHandle[uDevIdx], DSI_DISPLAY_PROPERTYID_LANESTATE, &sDSIProp))
        {
          DSI_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Clock lane failed to enter HS post-init\n");
        }
      }
    }
  }
  
  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_RemapLane()
** 
** DESCRIPTION:
**   Remap DSI lane order
**
** ---------------------------------------------------------------------- */

MDP_Status DSIDriver_RemapLane(MDP_Display_IDType eDisplayId, uint32 uLaneRemapOrder)
{
  MDP_Status       eStatus        =  MDP_STATUS_OK;
  DSI_DriverCtx   *pDriverCtx     =  DSI_GET_DRIVER_CTX(eDisplayId);

  if (uLaneRemapOrder >= DSI_LANE_SWAPNUM)
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    DSI_PropertyParamsType   sDSIProp;
    
    MDP_OSAL_MEMZERO(&sDSIProp, sizeof(DSI_PropertyParamsType));
    MDP_OSAL_MEMCPY(&sDSIProp.aLaneMap, (void *)&sDisplayLaneSetting[uLaneRemapOrder], sizeof(sDSIProp.aLaneMap));
    
    if (DSI_STATUS_SUCCESS != DSI_Display_SetProperty(pDriverCtx->hDSIHandle[0], DSI_DISPLAY_PROPERTYID_LANEMAP, &sDSIProp))
    {
      eStatus = MDP_STATUS_FAILED;
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_ConfigClockLane()
** 
** DESCRIPTION:
**   Config the clock lane to HS or LP(default)
**
** ---------------------------------------------------------------------- */

MDP_Status DSIDriver_ConfigClockLane(MDP_Display_IDType eDisplayId, uint32 uClkConfig)
{
  MDP_Status               eStatus        =  MDP_STATUS_OK;
  DSI_DriverCtx           *pDriverCtx     =  DSI_GET_DRIVER_CTX(eDisplayId);
  DSI_PropertyParamsType   sDSIProp;
    
  MDP_OSAL_MEMZERO(&sDSIProp, sizeof(DSI_PropertyParamsType));

  sDSIProp.eLaneState = (MDPPLATFORM_PANEL_DETECT_FLAG_CLOCK_FORCEHS & uClkConfig)? DSI_LANE_STATE_CLOCK_HS : DSI_LANE_STATE_CLOCK_LP11;

  if (DSI_STATUS_SUCCESS != DSI_Display_SetProperty(pDriverCtx->hDSIHandle[0], DSI_DISPLAY_PROPERTYID_LANESTATE, &sDSIProp))
  {
    eStatus = MDP_STATUS_FAILED;
  }
   
  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_MinimalInit()
** 
** DESCRIPTION:
**   Minimal initialization needed to do DSI read commands
**
** ---------------------------------------------------------------------- */
MDP_Status DSIDriver_MinimalInit(MDP_Display_IDType eDisplayId, bool32 bCPhyMode)
{
  MDP_Status             eStatus              = MDP_STATUS_OK;
  DSI_DriverCtx         *pDriverCtx           = DSI_GET_DRIVER_CTX(eDisplayId);
  void                  *pDSIBuffer           = pDriverCtx->pDSIBuffer;
  bool32                 bDMAOnly             = TRUE;      // Use DMA VBIF only for DSI command data .
  DSI_DisplayConfigType  sDisplayConfig;
  DSI_DeviceConfigType   sDeviceConfig;
  MDPExternalClockEntry  sDSI0ExtClocks[] =
                                     {
                                       {"mdss_esc0_clk",            0, 1, 0, 0, 0, 0, 0},  // Index 0
                                       {"mdss_pclk0_clk",           0, 0, 0, 0, 0, 0, 0},  // Index 1
                                       {"mdss_byte0_clk",           0, 0, 0, 0, 0, 0, 0},  // Index 2
                                       {"mdss_byte0_intf_clk",      0, 0, 0, 0, 0, 0, 0},  // Index 3
                                       {"mdss_byte0_div_clk_src",   0, 0, 0, 0, 0, 0, 2},  // Index 4
                                       {"\0",                       0, 0, 0, 0, 0, 0, 0},
                                     };
  MDPExternalClockEntry  sDSI1ExtClocks[] =
                                     {
                                       {"mdss_esc1_clk",            0, 1, 0, 0, 0, 0, 0},  // Index 0
                                       {"mdss_pclk1_clk",           0, 0, 0, 0, 0, 0, 0},  // Index 1
                                       {"mdss_byte1_clk",           0, 0, 0, 0, 0, 0, 0},  // Index 2
                                       {"mdss_byte1_intf_clk",      0, 0, 0, 0, 0, 0, 0},  // Index 3
                                       {"mdss_byte1_div_clk_src",   0, 0, 0, 0, 0, 0, 2},  // Index 4
                                       {"\0",                       0, 0, 0, 0, 0, 0, 0},
                                     };

  if (TRUE == bDMAOnly)
  {
    if (NULL == pDSIBuffer)
    {
      if (NULL == (pDSIBuffer = MDP_OSAL_CALLOC(DSI_DMA_BUFFER_SIZE)))
      {
        DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: UncachedAllocateZeroPool failed\n");
        eStatus = MDP_STATUS_NO_RESOURCES;
      }
    }
  }

  if (MDP_STATUS_OK == eStatus)
  {
    DSI_Device_IDType eDeviceId = DSI_DeviceID_0;

    //
    // Setup clocks using default frequencies, any freq should work to do a DSI read
    //
    if (MDP_DISPLAY_SECONDARY == eDisplayId)
    {
      eDeviceId = DSI_DeviceID_1;
      eStatus   = MDPSetupClocks(MDP_CLOCKTYPE_DSI1, (MDPExternalClockEntry *)&sDSI1ExtClocks);
    }
    else
    {
      eDeviceId = DSI_DeviceID_0;
      eStatus   = MDPSetupClocks(MDP_CLOCKTYPE_DSI0, (MDPExternalClockEntry *)&sDSI0ExtClocks);
    }

    //
    // Open DSI Host
    //
    if (MDP_STATUS_OK == eStatus)  
    {
      MDP_OSAL_MEMZERO(&sDeviceConfig, sizeof(DSI_DeviceConfigType));
      sDeviceConfig.eDeviceID                            = eDeviceId;;
      sDeviceConfig.bLittleEndian                        = TRUE;
      sDeviceConfig.bNonCompliantMode                    = FALSE;
      sDeviceConfig.bEnableCRCCheck                      = FALSE;
      sDeviceConfig.bEnableECCCheck                      = FALSE;
      sDeviceConfig.sMemoryConfig.pCPUAddress            = pDSIBuffer;
      sDeviceConfig.sMemoryConfig.sMDPAddress.u.uLowPart = (UINTN)pDSIBuffer;
      sDeviceConfig.sMemoryConfig.uSize                  = DSI_DMA_BUFFER_SIZE;
      sDeviceConfig.bEnableLP11AtInit                    = FALSE;
      sDeviceConfig.uFlags                              |= (TRUE == bDMAOnly) ? DSI_DEVICE_FLAGS_DSI_DCS_DMA_ONLY : 0;
      sDeviceConfig.bPhyDCDCMode                         = TRUE;
      sDeviceConfig.bCPhyMode                            = bCPhyMode;

      if (DSI_STATUS_SUCCESS != DSI_Device_Open(&sDeviceConfig, &(pDriverCtx->hDSIHandle[0])))
      {
        eStatus = MDP_STATUS_FAILED;
      }
      else
      {
        MDPPlatformParams sMDPPlatformParam;
        int               i;

        /* Handle Panel reset */
        MDP_OSAL_MEMZERO(&sMDPPlatformParam, sizeof(sMDPPlatformParam));

        /* use default timing value here since panel reset info at xml files is not parsed yet */
        sMDPPlatformParam.sPlatformPanelReset.uResetGpio         = MDP_RESET_STATE_INVALID; /* use default reset gpio */
        sMDPPlatformParam.sPlatformPanelReset.uAssertState       = MDP_RESET_STATE_LEVEL_LOW;
        /* 
         * default to 1 ms for pre reset time should be sufficient 
         * since start from power on to here should be more than 10ms already
         */
        sMDPPlatformParam.sPlatformPanelReset.uPreResetTimeUs    = MDP_GPIO_PRE_RESET_TIME;  /* default to 1000 us */
        sMDPPlatformParam.sPlatformPanelReset.uResetAssertTimeUs = MDP_GPIO_RESET_ASSERT_TIME;  /* defuault to 10 us */
        sMDPPlatformParam.sPlatformPanelReset.uPostResetTimeUs   = MDP_GPIO_POST_RESET_TIME;  /* default to 10000 us */
      
        if (MDP_STATUS_OK != MDPPlatformConfigure(eDisplayId, MDPPLATFORM_CONFIG_RESETPANEL, &sMDPPlatformParam))
        {
          DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: MDPPlatformConfigure(MDPPLATFORM_CONFIG_RESETPANEL) failed\n" );
        }

        /* Setup DSI controller configuration */
        MDP_OSAL_MEMZERO(&sDisplayConfig, sizeof(DSI_DisplayConfigType));
        sDisplayConfig.sDisplayInfo.eDisplayId   = DSI_ChannelID_Video0;
        sDisplayConfig.sDisplayInfo.eDisplayVC   = DSI_Display_VC_0;
        sDisplayConfig.sDisplayInfo.eColorFormat = DSI_COLOR_RGB_888_24BPP;
        sDisplayConfig.sDisplayInfo.uNumLanes    = 4;
        sDisplayConfig.sDisplayInfo.bCPhyMode    = bCPhyMode;

        for (i=0; i<(DSI_LaneMap_MAX-1); i++)
        {
          sDisplayConfig.eDisplayLane[i] = sDisplayLaneSetting[0][i];
        }

        sDisplayConfig.sCmdModeConfg.bEnable                 = TRUE;
        sDisplayConfig.sCmdModeConfg.eImageTrigger           = DSI_Display_ImageTrigger_NONE;
        sDisplayConfig.sCmdModeConfg.eCMDTrigger             = DSI_Display_CMDTrigger_SW;
        sDisplayConfig.sCmdModeConfg.sExtTEConfig.eExtTEMode = DSI_ExtTEMode_NONE;

        if (TRUE == pDriverCtx->bDualDSI)
        {
          sDisplayConfig.ePLLSourceType                      = DSI_PLL_CONFIG_SPLIT_SOURCE;
        }
        else
        {
          sDisplayConfig.ePLLSourceType                      = DSI_PLL_CONFIG_INDEPENDENT_SOURCE;
        }

        /* During minimal init,as cxo is used to clock the lanes, clock lane won't enter the HS even if the corresponding register is programmed.  
           In the normal init, since DSI_PLL is selected as the clock source, HS mode works.
           Hence, to enable DSI_PLL in minimal init, the uBitClockFreq is hardcoded to a non-zero value. 
        */
        sDisplayConfig.sDisplayInfo.uBitClockFreq            = DSI_DEFAULT_BITCLOCK_FREQ;

        /* Save Display Config */
        if (DSI_STATUS_SUCCESS != DSI_Display_Open(pDriverCtx->hDSIHandle[0], &sDisplayConfig, &(pDriverCtx->hDisplayHandle[0])))
        {
          eStatus = MDP_STATUS_FAILED;
        }
        else if (DSI_STATUS_SUCCESS != DSI_Display_Commit(pDriverCtx->hDSIHandle[0], 0))
        {
          eStatus = MDP_STATUS_FAILED;
        }
      }
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_GetCalibrationCodes()
** 
** DESCRIPTION:
**   Get dynamic refresh calibration codes
**
** ---------------------------------------------------------------------- */
MDP_Status DSIDriver_GetCalibrationCodes(uint32 uDSIIndex, MDP_PLLCodesInfo *psPllCodesInfo)
{
  MDP_Status             eStatus              = MDP_STATUS_OK;
  DSI_DriverCtx         *pDriverCtx           = DSI_GET_DRIVER_CTX(MDP_DISPLAY_PRIMARY);
  DSI_PropertyParamsType sParams;
  DSI_Device_IDType      eDeviceId            = (DSI_Device_IDType)uDSIIndex;

  if ((NULL == psPllCodesInfo) ||
    (DSI_DeviceID_MAX <= eDeviceId))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    MDP_OSAL_MEMZERO(&sParams, sizeof(DSI_PropertyParamsType));

    /*
     * In split mode:
     *   DSI0 and DSI1 share same context: DSI_GET_DRIVER_CTX(MDP_DISPLAY_PRIMARY)
     *   DSI0 display handle: pDriverCtx->hDisplayHandle[0]
     *   DSI1 display handle: pDriverCtx->hDisplayHandle[1]
     * In dual panel mode:
     *   DSI0 use context:DSI_GET_DRIVER_CTX(MDP_DISPLAY_PRIMARY)
     *   DSI0 display handle: pDriverCtx->hDisplayHandle[0]
     *   DSI1 use context:DSI_GET_DRIVER_CTX(MDP_DISPLAY_SECONDARY)
     *   DSI1 display handle: pDriverCtx->hDisplayHandle[0]
     */
    if ((FALSE          == pDriverCtx->bDualDSI) &&
        (DSI_DeviceID_1 == uDSIIndex))
    {
      pDriverCtx = DSI_GET_DRIVER_CTX(MDP_DISPLAY_SECONDARY);
      eDeviceId  = 0;
    }

    if(DSI_STATUS_SUCCESS != DSI_Display_GetProperty(pDriverCtx->hDisplayHandle[eDeviceId], DSI_DISPLAY_PROPERTYID_GETCALCODES, &sParams))
    {
      eStatus = MDP_STATUS_FAILED;
    }
    else
    {
      DSI_OSAL_MemCpy((void *) psPllCodesInfo, (void*)&sParams.sDisplayInfo.sPllCodesInfo, sizeof(MDP_PLLCodesInfo));
    }
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_SetDynamicRefreshFreqs()
** 
** DESCRIPTION:
**   Set dynamic refresh frequencies
**
** ---------------------------------------------------------------------- */
MDP_Status DSIDriver_SetDynamicRefreshFreqs(uint32 *puFreqList, uint32 uFreqNum)
{
  MDP_Status                eStatus              = MDP_STATUS_OK;
  MDP_Panel_AttrType       *pDisplayInfo         = MDP_GET_DISPLAYINFO(MDP_DISPLAY_PRIMARY);

  if((NULL == puFreqList) ||
     (NULL == pDisplayInfo) ||
      (0 == uFreqNum))
  {
    eStatus = MDP_STATUS_BAD_PARAM;
  }
  else
  {
    uint32 uCount = (uFreqNum < MAX_NUM_DYNAMIC_REFRESH) ? uFreqNum : MAX_NUM_DYNAMIC_REFRESH;

    DSI_OSAL_MemCpy(pDisplayInfo->uAttrs.sDsi.uDynamicRefreshRates, puFreqList, uCount*sizeof(uint32));
  }

  return eStatus;
}

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DSIDriver_CalibratePLL()
** 
** DESCRIPTION:
**   Calibration and get PLL codes, should call DSIDriver_SetDynamicRefreshFreqs
**   before calling this function
**
** ---------------------------------------------------------------------- */
MDP_Status DSIDriver_CalibratePLL(uint32 *puPllCodes, uint32 *puPllCodesSize)
{
  MDP_Status                eStatus              = MDP_STATUS_OK;
  MDP_Panel_AttrType       *pDisplayInfo         = MDP_GET_DISPLAYINFO(MDP_DISPLAY_PRIMARY);

  if ((NULL == puPllCodes) ||
      (NULL == puPllCodesSize))
  {
    DSI_Log_Message(DSI_LOGLEVEL_WARN, "DSIDriver_CalibratePLL no valid pllcodes buffer provided\n");
  }
  else
  {
    uint32 uDynamicFreqNum = 0;

    /* Find out how many frequencies are set */
    while ((uDynamicFreqNum < MAX_NUM_DYNAMIC_REFRESH) &&
           (0 != pDisplayInfo->uAttrs.sDsi.uDynamicRefreshRates[uDynamicFreqNum]))
    {
      uDynamicFreqNum++;
    }
    if ((0 == uDynamicFreqNum) ||
      (MAX_NUM_DYNAMIC_REFRESH < uDynamicFreqNum))
    {
      DSI_Log_Message(DSI_LOGLEVEL_WARN, "DSIDriver_CalibratePLL dynamic refresh frequency number is invalid\n");
      eStatus = MDP_STATUS_FAILED;
    }
    else
    {
      uint32 j;

      eStatus = MDP_STATUS_FAILED;
      /* 
       * This function will trigger the dynamic refresh calibration, there is corruption druing the
       * call process but that is expected.
       */
      DSIDriver_SetMode(pDisplayInfo);

      /* bDynamicRefreshCalFinished will be set to TRUE only if dsiSystem_FrequencyCalibration succeed */
      for (j = 0 ; j < DSI_DeviceID_MAX; j++)
      {
        MDP_PLLCodesInfo sPllCodesInfo;

        DSI_OSAL_MemZero(&sPllCodesInfo, sizeof(sPllCodesInfo));
      
        if (MDP_STATUS_OK == DSIDriver_GetCalibrationCodes(j, &sPllCodesInfo))
        {
          /* uRefreshRateCount>0 indicates there are pll codes that can be retrived */
          if (sPllCodesInfo.uRefreshRateCount > 0)
          {
            uint32 uPllCodesSizePerFreq = sizeof(sPllCodesInfo.sPllCodes[0].uPllCodes);
            uint32 i;

            puPllCodesSize[j] = sPllCodesInfo.uRefreshRateCount * uPllCodesSizePerFreq;
            for (i = 0 ; i < sPllCodesInfo.uRefreshRateCount; i++)
            {
              DSI_OSAL_MemCpy(puPllCodes, sPllCodesInfo.sPllCodes[i].uPllCodes, uPllCodesSizePerFreq);
              puPllCodes += uPllCodesSizePerFreq / sizeof(uint32);
            }
            eStatus = MDP_STATUS_OK;
          }
        }
      }
    }
  }

  return eStatus;
}

/*------------------------------------------------------------------------
Panel Driver Helper Functions
-------------------------------------------------------------------------- */



/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DsiPanelInit()
** 
** DESCRIPTION:
**   DSI Clocks and timing initialization
**
** ---------------------------------------------------------------------- */
MDP_Status DsiPanelInit(MDP_Panel_AttrType    *pPanelInfo)
{
  MDP_Status        eStatus         = MDP_STATUS_OK;
  MDPPlatformParams sMDPPlatformParam;

  MDP_OSAL_MEMZERO(&sMDPPlatformParam, sizeof(MDPPlatformParams));  

  /* Initialize the DSI controller in to a known state */
  if (MDP_STATUS_OK != DSIDriver_Init(pPanelInfo)) 
  {
    DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: DSIDriver_Init() failed\n" );
    eStatus = MDP_STATUS_FAILED;
  }
  else 
  {
    sMDPPlatformParam.sPlatformPanelReset.uResetGpio         = pPanelInfo->uResetGpio;
    /* the unit for reset time is micro second */
    sMDPPlatformParam.sPlatformPanelReset.uAssertState       = pPanelInfo->uAttrs.sDsi.aResetInfo[0];
    sMDPPlatformParam.sPlatformPanelReset.uResetAssertTimeUs = pPanelInfo->uAttrs.sDsi.aResetInfo[1];
    sMDPPlatformParam.sPlatformPanelReset.uPreResetTimeUs    = pPanelInfo->uAttrs.sDsi.aResetInfo[2];
    sMDPPlatformParam.sPlatformPanelReset.uPostResetTimeUs   = pPanelInfo->uAttrs.sDsi.aResetInfo[3];
    sMDPPlatformParam.sPlatformPanelReset.uAssertOnPowerDown = pPanelInfo->uAttrs.sDsi.aResetInfo[4];

    if (sMDPPlatformParam.sPlatformPanelReset.uAssertState >=  MDP_RESET_STATE_MAX)
    {
       sMDPPlatformParam.sPlatformPanelReset.uAssertState =  MDP_RESET_STATE_LEVEL_LOW;
    }

    /* 
     * default to 1 ms for pre reset time should be sufficient 
     * since start from power on to here should be more than 10ms already
     */
    if (sMDPPlatformParam.sPlatformPanelReset.uPreResetTimeUs == 0)
    {
       sMDPPlatformParam.sPlatformPanelReset.uPreResetTimeUs = MDP_GPIO_PRE_RESET_TIME;  /* default to 1000 us */
    }

    if (sMDPPlatformParam.sPlatformPanelReset.uResetAssertTimeUs == 0)
    {
       sMDPPlatformParam.sPlatformPanelReset.uResetAssertTimeUs = MDP_GPIO_RESET_ASSERT_TIME;  /* defuault to 10 us */
    }

    if (sMDPPlatformParam.sPlatformPanelReset.uPostResetTimeUs == 0)
    {
       sMDPPlatformParam.sPlatformPanelReset.uPostResetTimeUs = MDP_GPIO_POST_RESET_TIME;  /* default to 10000 us */
    }

    /* Toggle panel reset */
    if (MDP_STATUS_OK != MDPPlatformConfigure(pPanelInfo->eDisplayId, MDPPLATFORM_CONFIG_RESETPANEL, &sMDPPlatformParam))   
    {
      DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: MDPPlatformConfigure(MDPPLATFORM_CONFIG_RESETPANEL) failed\n" );
      // Warning, non-fatal
    }

    /* Configure the Panel */
    if (MDP_STATUS_OK != DSIDriver_SetMode(pPanelInfo))   
    {
      DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: DSIDriver_SetMode() failed\n" );
      eStatus = MDP_STATUS_FAILED;
    }
  }
  return eStatus;
}


/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DsiPanelShutdown()
** 
** DESCRIPTION:
**   Gracefully shutdown the controller and panel
**
*//* -------------------------------------------------------------------- */
MDP_Status DsiPanelShutdown(MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status  eStatus =  MDP_STATUS_OK;

  if (NULL == pPanelConfig)
  {
    // Invalid panel config, nothing to turn off
  }
  else
  {
    DSI_DriverCtx        *pDriverCtx = DSI_GET_DRIVER_CTX(pPanelConfig->eDisplayId);
    uint32                uDevIdx;  
    uint32                uTimeout   = 0;  

    // Only send a termination sequence if the panel has been setup already
    for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)
    {    
      // Send termination sequence (if present) to controller 0
      if (DSI_DeviceID_0 == uDevIdx)
      {
        DSI_PropertyParamsType sParams;

        MDP_OSAL_MEMZERO(&sParams, sizeof(DSI_PropertyParamsType));

        // Wait for dsi idle by checking busy status
        while ((DSI_STATUS_SUCCESS         == DSI_Display_GetProperty(pDriverCtx->hDisplayHandle[uDevIdx],
                                                                      DSI_DISPLAY_PROPERTYID_CONTROLLERSTATUS,
                                                                     &sParams))                                &&
               (DSI_CONTROLLER_STATUS_IDLE != sParams.uControllerStatus)                                       &&
               (uTimeout                   <  DSI_STATUS_WAIT_IDLE_MAX_TIME))
        {
          gBS->Stall(1000);
          uTimeout ++;
        }

        // Force the DSI controller to idle, only required in video mode
        if ((MDP_DISPLAY_CONNECT_PRIMARY_DSI_VIDEO   == pPanelConfig->ePhysConnect) ||
            (MDP_DISPLAY_CONNECT_SECONDARY_DSI_VIDEO == pPanelConfig->ePhysConnect))
        {
          DSI_PropertyParamsType  sDSIProperty;
          
          MDP_OSAL_MEMZERO(&sDSIProperty, sizeof(DSI_PropertyParamsType));
          if (DSI_STATUS_SUCCESS != DSI_Display_SetProperty(pDriverCtx->hDisplayHandle[uDevIdx], DSI_DISPLAY_PROPERTYID_LP11, &sDSIProperty))
          {
            DSI_Log_Message(MDP_LOGLEVEL_INFO, "DSI_Display_SetProperty(DSI_DISPLAY_PROPERTYID_LP11) Failed");
          }

          if (DSI_STATUS_SUCCESS != DSI_Display_SetProperty(pDriverCtx->hDisplayHandle[uDevIdx], DSI_DISPLAY_PROPERTYID_RESETCORE, &sDSIProperty))
          {
            DSI_Log_Message(MDP_LOGLEVEL_INFO, "DSI_Display_SetProperty(DSI_DISPLAY_PROPERTYID_RESETCORE) Failed");
          }
        }
        
        // If video transfer is required during DCS transactions then do not send the termination sequence as 
        // the termination commands have been aleady sent.
        if (FALSE == pPanelConfig->uAttrs.sDsi.bForceCmdInVideoHS)
        {
          if (MDP_STATUS_OK != SendPanelXMLSequence(pDriverCtx, pPanelConfig->uAttrs.sDsi.pTermBuffer, pPanelConfig))
          {
            DSI_Log_Message(MDP_LOGLEVEL_INFO, "DisplayDxe: SendPanelXMLSequence() failed on device%d\n", uDevIdx );
              // Warn and continue
          }
        }
      }
    }

    // De-init I2C configuration: Ignore any errors
    if (NULL != pPanelConfig->uAttrs.sDsi.sI2CConfig.pI2CInitSequence)
    {
       I2CDriver_Deinit(&pPanelConfig->uAttrs.sDsi.sI2CConfig); 
    }
  }

  return eStatus;
}




/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DsiPanelSendCommandSequence()
** 
** DESCRIPTION:
**   Send DSI command sequence
**
** ---------------------------------------------------------------------- */
MDP_Status DsiPanelSendCommandSequence(MDP_Panel_AttrType *pPanelInfo, MdpPanelCommandType eCommand, void *pCustomCommand, uint32 uFlags)
{
  MDP_Status            eStatus     =  MDP_STATUS_OK;
  DSI_DriverCtx        *pDriverCtx  =  DSI_GET_DRIVER_CTX(pPanelInfo->eDisplayId);

  switch (eCommand)
  {
    case MDP_PANEL_COMMAND_INIT:
    {
      eStatus = SendPanelXMLSequence(pDriverCtx, pPanelInfo->uAttrs.sDsi.pInitBuffer, pPanelInfo);
    }
    break;

    case MDP_PANEL_COMMAND_TERM:
    {
      eStatus = SendPanelXMLSequence(pDriverCtx, pPanelInfo->uAttrs.sDsi.pTermBuffer, pPanelInfo);
    }
    break;

    case MDP_PANEL_COMMAND_PPS:
    {
      eStatus = SendPanelPPSRawBuffer(pDriverCtx, pPanelInfo);
    }
    break;

    default:
      eStatus = MDP_STATUS_NOT_SUPPORTED;     
  }
  return eStatus;
}




/* ---------------------------------------------------------------------- */
/**
** FUNCTION: DsiPanelDumpRegisters()
** 
** DESCRIPTION: Helper function to dump panel registers
** 
**
*//* -------------------------------------------------------------------- */
MDP_Status DsiPanelDumpRegisters(void)
{
  uint32 uReadSize  = 1024;
  uint32 uDataWidth = 4;

  uint16 uAddress = 0;
  uint32 uResponse[2];
  uint32 uReponseSize;

  uint16 uIndex;

  DSI_Log_Message(MDP_LOGLEVEL_ERROR, "Offset   Data\n");
  DSI_Log_Message(MDP_LOGLEVEL_ERROR, "-------+------------------------------------------------------------\n");

  for (uIndex=0;uIndex<uReadSize;uIndex++)
  {
      if (0 == (uIndex % uDataWidth))
      {
        DSI_Log_Message(MDP_LOGLEVEL_ERROR, "0x%04x   ", uIndex);
      }

      uAddress     = uIndex;
      uReponseSize = sizeof(uResponse);
      if (MDP_STATUS_OK == DSIDriver_Read(MDP_DISPLAY_PRIMARY,
                                          0x06,
                                          (void*)&uAddress, 
                                          sizeof(uAddress), 
                                          (void*) &uResponse,
                                          &uReponseSize,
                                          0))
      {
        DSI_Log_Message(MDP_LOGLEVEL_ERROR, "0x%08x ", uResponse[0]);        
      }
      else
      {
        DSI_Log_Message(MDP_LOGLEVEL_ERROR, "--ERROR-- ");        
     
      }


      // If last item, add carriage return
      if (0 == ((uIndex+1) % uDataWidth))
      {
         DSI_Log_Message(MDP_LOGLEVEL_ERROR, "\n");        
      }
  }

  return MDP_STATUS_OK;
}


/*------------------------------------------------------------------------
Local Functions
-------------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- */
/**
** FUNCTION: SendPanelPPSRawBuffer()
** 
** DESCRIPTION:
**   Local helper function to send a DSI command sequence to the panel
**   This will package the raw PPS buffer and convert it to the XML
**   header format and then send the command using the
**   SendPanelXMLSequence() API
** 
** ---------------------------------------------------------------------- */
static MDP_Status SendPanelPPSRawBuffer(DSI_DriverCtx *pDriverCtx, MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status  eStatus         = MDP_STATUS_OK;

  if ((TRUE == pPanelConfig->sDSCConfig.bDSCEnable) &&
      (NULL != pPanelConfig->sDSCConfig.pDSCPpsBuffer))
  {
    uint8 *pDscHeader         = (uint8 *)pPanelConfig->sDSCConfig.pDSCPpsBuffer;

    // First byte holds the length of the packet (128byte payload, 1byte = Command type)
    *pDscHeader++ = MDP_DSI_DSC_PAYLOAD_SIZE + MDP_DSI_DSC_XML_HEADER_SIZE;

    // Prepare DSC PPS header data
    *pDscHeader++ = 0;
    *pDscHeader++ = 0;
    *pDscHeader++ = 0;

    // PPS Command header 
    *pDscHeader++ = DSI_DATATYPE_PPSPACKET;

    // Send the PPS command to the panel
    eStatus = SendPanelXMLSequence(pDriverCtx, pPanelConfig->sDSCConfig.pDSCPpsBuffer, pPanelConfig);
  }

  return eStatus;
}

/** ---------------------------------------------------------------------- */
/**
** FUNCTION: SendPanelXMLSequence()
** 
** DESCRIPTION:
**   Local helper function to send a DSI command sequence to the panel
**
** ---------------------------------------------------------------------- */
static MDP_Status SendPanelXMLSequence(DSI_DriverCtx *pDriverCtx, void *pDSICommandBuffer, MDP_Panel_AttrType *pPanelConfig)
{
  MDP_Status            eStatus         = MDP_STATUS_OK;
  uint32                uDevIdx;
  static uint8          uBroadcastMask  = DSI_CONTROLLER_0;     //Default to sending commands over first DSI controller.
  
  if ((NULL == pDriverCtx  ) ||
      (NULL == pPanelConfig))
  {
      eStatus = MDP_STATUS_BAD_PARAM;
  }
  else if (NULL == pDSICommandBuffer)
  {
    // No commands, return successful
  }
  else
  {
    DSI_WritePacketType   sWritePacket;
    uint8                *pSrc              = (uint8 *)pDSICommandBuffer;
    XML_BinaryPacketType  sXMLBinaryData;
    uint32                uHeaderSize       = (uint32)((UINTN)&(((XML_BinaryPacketType*)pSrc)->pData) - (UINTN)&(((XML_BinaryPacketType*)pSrc)->uPacketLength));
    bool32                bColorFillEnabled = FALSE;

    // Use Unaligned Memory read from DSI Command buffer (Required for THUMB2 mode)
    MDP_ReadUnaligned_U32(&sXMLBinaryData.uPacketLength, pSrc);
    sXMLBinaryData.pData = (uint8* )&(((XML_BinaryPacketType*)pSrc)->pData);

    /*Send Config Command to configure DSI Panel */ 
    MDP_OSAL_MEMZERO(&sWritePacket, sizeof(DSI_WritePacketType));
    sWritePacket.eDisplayVC       = (DSI_Display_VCType)pPanelConfig->uAttrs.sDsi.eDisplayVC; 
    sWritePacket.bHighSpeedMode   = FALSE;
    sWritePacket.bQueuePacket     = FALSE;
    sWritePacket.bBTARequest      = FALSE;

    /* Parse init command packets */
    while (0 != sXMLBinaryData.uPacketLength)
    {
      uint8 *pDsiCmd = (uint8*)sXMLBinaryData.pData;

      if (0 == sXMLBinaryData.uPacketLength)
      {
        // A null packet signifies end of data
        break;
      }
      else if (DSI_CMD_CUSTOM_DELAY == *pDsiCmd)
      {
        uint8 uDelayLength = *(++pDsiCmd);

        // Milliseconds delay
        MDP_OSAL_DELAYMS(uDelayLength); 
      }
      else if (DSI_CMD_CUSTOM_COLOR_FILL == *pDsiCmd)
      {
        uint32                    uFilledColor   = 0;
        uint32                    uCount         = 0;
        DSI_PropertyParamsType    sParams;

        bColorFillEnabled = TRUE;
          
        /* if there's payload, then there must be 3 bytes for R, G, B */
        if (DSI_CMD_CUSTOM_COLOR_FILL_PAYLOAD_LENGTH == (sXMLBinaryData.uPacketLength-1))
        {
          /* uFilledColor is in RedCr, GreenY, BlueCb order */
          uFilledColor = ((pDsiCmd[1]<<16) | (pDsiCmd[2]<<8) | pDsiCmd[3]);
        }

        /* enable constant color output */
        MDPOutputConstantColor(pPanelConfig, uFilledColor, TRUE);

        /* In case of command mode panels, wait for constant color transfer done 
         * No wait is needed for video mode panels as frame xfer is via video engine and cmd engine is idle 
         */           
        if ((MDP_DISPLAY_CONNECT_PRIMARY_DSI_CMD   == pPanelConfig->ePhysConnect) ||
            (MDP_DISPLAY_CONNECT_SECONDARY_DSI_CMD == pPanelConfig->ePhysConnect))
        {
          for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)
          {
            do
            {
              /* sleep */
              MDP_OSAL_DELAYMS(DSI_STATUS_POLLING_CYCLE);

              /* check controller status. CMD_MDP_ENGINE should be idle once transfer done */
              MDP_OSAL_MEMZERO(&sParams, sizeof(DSI_PropertyParamsType));
              if (DSI_STATUS_SUCCESS == DSI_Display_GetProperty(pDriverCtx->hDisplayHandle[uDevIdx], DSI_DISPLAY_PROPERTYID_CONTROLLERSTATUS, &sParams))
              {
                if (0 == (DSI_CONTROLLER_STATUS_CMD_MDP_ENGINE_BUSY & sParams.uControllerStatus))
                {
                  break;
                }
              }
              else
              {
                eStatus = MDP_STATUS_FAILED ;
              }
              uCount ++;
            } while((uCount * DSI_STATUS_POLLING_CYCLE) <= DSI_STATUS_CHECK_MAX_TIME);
          }     
        }
      }
      else if (DSI_CMD_CUSTOM_BROADCAST ==  *pDsiCmd)
      {
        uBroadcastMask = ((DSI_CONTROLLER_0 | DSI_CONTROLLER_1) & (*(++pDsiCmd)));
        if (0 == uBroadcastMask)
        {
          uBroadcastMask = DSI_CONTROLLER_0;
        }

        if (MDP_SPLIT_LINK_CONFIG_DISABLED != pPanelConfig->uAttrs.sDsi.eSplitLinkConfig)
        {
          DSI_PropertyParamsType    sParams;

          MDP_OSAL_MEMZERO(&sParams, sizeof(DSI_PropertyParamsType));
          sParams.bSplitLinkCmdBroadcast = TRUE;

          if (DSI_STATUS_SUCCESS != DSI_Display_SetProperty(pDriverCtx->hDisplayHandle[0], DSI_DISPLAY_PROPERTYID_SPLITLINK_BROADCAST, &sParams))
          {
            // Warn and continue
            DSI_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Failed to switch to broadcast mode for split link panel\n");
          }
        }
      }
      else
      {
        sWritePacket.uCmdDataType     = *pDsiCmd++;
        sWritePacket.puPayload        = (uint8*)pDsiCmd;
        sWritePacket.uPayloadLen      = sXMLBinaryData.uPacketLength-1; // Packet length minus the command

        for (uDevIdx = 0; uDevIdx < pDriverCtx->uNumDSIControllers; uDevIdx++)
        {
          if ( 0 == (uBroadcastMask & (1<<uDevIdx))) 
          {
            //skip if broadcast mask is not set on this DSI controller device ID.
            continue;
          }

          if (DSI_STATUS_SUCCESS != DSI_Display_ClientWrite(pDriverCtx->hDisplayHandle[uDevIdx], &sWritePacket))
          {
            // Warn and continue
            DSI_Log_Message(MDP_LOGLEVEL_WARN, "DisplayDxe: Packet transmission failed CMD:0x%x Length:%d\n", sWritePacket.puPayload, sWritePacket.uPayloadLen);
            break;
          }
        }
      }

      // Go to next packet (header + payload size)
      pSrc += (uint8)(sXMLBinaryData.uPacketLength + uHeaderSize);
      // Unaligned Memory read 
      MDP_ReadUnaligned_U32(&sXMLBinaryData.uPacketLength, pSrc);
      sXMLBinaryData.pData = pSrc + uHeaderSize;
    }

    /* Panel init sequence done */
    
    if (TRUE == bColorFillEnabled)
    {
      /* Disable constant color output and revert to standard control path settings */      
      MDPOutputConstantColor(pPanelConfig, 0, FALSE);
    }    
  }

  return eStatus;
}



#ifdef __cplusplus
}
#endif

