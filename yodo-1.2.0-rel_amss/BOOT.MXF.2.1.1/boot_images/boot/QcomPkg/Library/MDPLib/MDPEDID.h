#ifndef __MDPEDID_H__
#define __MDPEDID_H__
/*=============================================================================

  File: MDPEDID.h

  EDID headers and utilitiy functions

  Copyright (c) 2022 Qualcomm Technologies, Inc.  All Rights Reserved.
  Qualcomm Technologies Proprietary and Confidential.
=============================================================================*/

#include "MDPLib_i.h"
/*===========================================================================
                                Defines
===========================================================================*/
#define EDID_DISPLAY_DESC_DUMMY_TAG                         (0x10)  /* Tag value for dummy display descriptor */
#define EDID_DISPLAY_DESC_DATA_SIZE                         (0x0D)  /* Size of display descriptor data */
#define EDID_DISPLAY_DESC_MAX                               (0x03)  /* Maximum number of display descriptors in block 0 */
#define EDID_DISPLAY_DESC_PROPRIETARY_FIELD_DESC_TAG        (0xA)   /* Proprietary vendor-specific tag for 18-byte display descriptors */

/** Defines the EDID established timings.
*/
typedef struct {
    uint8 TimingI;              /**< Established timings table I. */
    uint8 TimingII;             /**< Established timings table II. */
    uint8 ManufacturesTiming;   /**< Manufacturer's timings table. */
} MDP_Panel_EDID_EstablishedTimings;

/** Defines the EDID standard timings.
*/
typedef struct {
   uint8  HorizontalPixels;     /**< Horizontal pixel width. */
   uint8  AspectRatio_Refresh;  /**< Aspect ratio and field refresh rate. */
} MDP_Panel_EDID_StandardTimings;

#pragma pack(push)
#pragma pack(1)
/** Defines the EDID detailed timings.
*/
typedef struct {
  uint16  PixelClock;
  /** Pixel clock frequency. */

  uint8   HPixels;
  /**< Lower eight bits of the horizontal addressable video pixels. */

  uint8   HBlanking;
  /**< Lower eight bits of the horizontal blanking pixels. */

  uint8   HPixels_Blanking;
  /**< Higher four bits of the horizontal active and blanking pixels. */

  uint8   VPixels;
  /**< Lower eight bits of the vertical addressable video pixels. */

  uint8   VBlanking;
  /**< Lower eight bits of the vertical blanking pixels. */

  uint8   VPixels_Blanking;
  /**< Higher four bits of the vertical active and blanking pixels. */

  uint8   HFrontPorch;
  /**< Lower eight bits of the horizontal front porch. */

  uint8   HSyncWidth;
  /**< Lower eight bits of the horizontal synchronization width. */

  uint8   VFrontPorch_SyncWidth;
  /**< Lower four bits of the vertical front porch and synchronization width. */

  uint8   HVPorchSyncWidths;
  /**< Higher two bits of the vertical/horizontal porch and synchronization
       widths. */

  uint8   HImageSize;
  /**< Lower eight bits of the video image width. */

  uint8   VImageSize;
  /**< Lower eight bits of the video image height. */

  uint8   HVImageSize;
  /**< Upper four bits of the video image width/height. */

  uint8   HBorder;
  /**< Horizontal border size. */

  uint8   VBorder;
  /**< Vertical border size. */

  uint8   SignalTimingInterface;
  /**< Detailed timing signal information. */
} MDP_Panel_EDID_DetailedTiming;
#pragma pack(pop)

/**  Defines the EDID display descriptor.
*/
typedef struct {
  uint16  DescriptorHeader;  /**< Header for this descriptor: 0x0 indicates
                                  that this is a descriptor block. */
  uint8   Reserved1;         /**< Reserved. */
  uint8   TagId;             /**< Indicates the tag for this descriptor. */
  uint8   Reserved2;         /**< Reserved. */
  uint8   Descriptor[13];    /**< Descriptor string. @newpagetable */
} Panel_EDID_DisplayDescriptor;

/** Defines the EDID.
*/
typedef struct {
  uint8   Header[8];              /**< EDID header: 00 FF FF FF FF FF FF 00. */
  uint16  ManufactureID;          /**< EISA three-character ID. */
  uint16  ProductCode;            /**< Vendor-assigned code. */
  uint32  SerialNumber;           /**< Thirty-two-bit serial number. */
  uint8   WeekOfManufacture;      /**< Week number. */
  uint8   YearOfManufacture;      /**< Year number. */
  uint8   EdidVersion;            /**< EDID structure version. */
  uint8   EdidRevision;           /**< EDID structure revision. */
  uint8   VideoInputDefinition;   /**< Information on how the host's video
                                       outputs are to be configured to drive
                                       the attached display. */
  uint8   MaxHorizontalImageSize;  /**< Maximum horizontal size in centimeters. */
  uint8   MaxVerticalImageSize;    /**< Maximum vertical size in centimeters. */
  uint8   DisplayTransferCharacteristic;  /**< Characteristics of the display
                                               transfer. */
  uint8   FeatureSupport;          /**< Indicates which features are supported. */
  uint8   RedGreenLowBits;         /**< Rx1 Rx0 Ry1 Ry0 Gx1 Gx0 Gy1Gy0. */
  uint8   BlueWhiteLowBits;        /**< Bx1 Bx0 By1 By0 Wx1 Wx0 Wy1 Wy0. */
  uint8   RedX;                    /**< Red-x bits 9 to 2. */
  uint8   RedY;                    /**< Red-y bits 9 to 2. */
  uint8   GreenX;                  /**< Green-x bits 9 to 2. */
  uint8   GreenY;                  /**< Green-y bits 9 to 2. */
  uint8   BlueX;                   /**< Blue-x bits 9 to 2. */
  uint8   BlueY;                   /**< Blue-y bits 9 to 2. */
  uint8   WhiteX;                  /**< White-x bits 9 to 2. */
  uint8   WhiteY;                  /**< White-y bits 9 to 2. */

  MDP_Panel_EDID_EstablishedTimings EstablishedTimings;  /**< Established timings. */
  MDP_Panel_EDID_StandardTimings    StandardTiming[8];   /**< Standard timings. */
  MDP_Panel_EDID_DetailedTiming     DetailedTiming;      /**< Detailed timings. */

  /** Detailed descriptors. */
  union
  {
    /**< Detailed timing descriptors. */
    MDP_Panel_EDID_DetailedTiming    DetailedTimings[3];
    /**< Detailed display descriptors. */
    Panel_EDID_DisplayDescriptor     DisplayDescriptors[3];
  }EDID_DetailedInfo;

  uint8   ExtensionFlag;    /**< Number of optional 128-byte EDID extension
                                 blocks that follows. */
  uint8   Checksum;         /**< EDID checksum. */
} MDP_Panel_EDID_Config;

/***************************************************************************
**
**  FUNCTION: EDIDInitialize()
**
**  @brief
**    Initialize EDID structure with default values.
**
**  @params
**    [OUT] pEDID
**          Edid config.
**
**  @return
**      VOID.
****************************************************************************/
void EDIDInitialize(MDP_Panel_EDID_Config *pEDID);

/***************************************************************************
**
**  FUNCTION: EDIDGenerateDetailedTiming()
**
**  @brief
**    Generate EDID Detailed Timings.
**
**  @params
**    [OUT] pEDID
**          Edid config.
**    [IN]  pPanelAttr
**          Panel attributes.
**
**  @return
**    VOID.
****************************************************************************/
void EDIDGenerateDetailedTiming(MDP_Panel_EDID_Config *pEDID, MDP_Panel_AttrType *pPanelAttr);

/***************************************************************************
**  EDIDGenerateMonitorNameDescriptor
**
**  @brief
**    Generate EDID Monitor Name Descriptor.
**
**  @params
**    [OUT] pDisplayDescriptor
**          Edid display descriptor.
**    [IN]  pcName
**          Monitor name.
**
**  @return
**    VOID.
****************************************************************************/
void EDIDGenerateMonitorNameDescriptor(Panel_EDID_DisplayDescriptor *pDisplayDescriptor, char * pcName);

/** ----------------------------------------------------------------------------------------------
**  EDIDGenerateChecksum
**
**  @brief
**      Generate EDID checksum.
**
**  @params
**      [IN/OUT] pEDID
**          Edid config.
**
**  @return
**      VOID.
** ----------------------------------------------------------------------------------------------- */
void EDIDGenerateChecksum(MDP_Panel_EDID_Config *pEDID);

#endif  // __MDPEDID_H__
