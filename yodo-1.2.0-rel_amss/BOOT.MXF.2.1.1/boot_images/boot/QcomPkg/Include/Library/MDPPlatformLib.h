#ifndef __MDPPLATFORMLIB_H__
#define __MDPPLATFORMLIB_H__
/*=============================================================================

  File: MDPPlatformLib.h

  Header file for MDP platform functions


  Copyright (c) 2011-2022 Qualcomm Technologies, Inc.
  All Rights Reserved.
  Confidential and Proprietary - Qualcomm Technologies, Inc.
=============================================================================*/
/*===========================================================================

                     INCLUDE FILES FOR MODULE

===========================================================================*/
#include <Uefi.h>
#include <Protocol/EFIPlatformInfo.h>
#include <Protocol/EFIChipInfo.h>
#include "MDPTypes.h"
#include "npa.h"

/*===========================================================================
                        RamDUmp Defines
===========================================================================*/
#define RAMDUMP_ALLOC_POOL_SIZE         0x10000       /* 64k */

/*===========================================================================
                        Defines
===========================================================================*/


/* Bit fields for uFlags in PlatformDSIDetectParams structure.
    Currently, it is used to define the clock lane config but this can be grown in future.
 */
#define MDPPLATFORM_PANEL_DETECT_FLAG_CLOCK_FORCEHS      0x00000001  /*Force clock lane in HS*/

/* Panel Reset related information
*/

/* Bit Fields for uFlags in the below structure */
#define MDDPLATFORM_PANEL_RESET_FLAG_USE_CUSTOM_DELAY    0x00000001  /* Wait for the specified delay instead of the default after reset */
#define MDDPLATFORM_PANEL_RESET_FLAG_FORCE_RESET         0x00000002  /* Force the panel reset */



/* Display Variable flags (DISPLAYCONFIG environment variable)
 */
#define   DISPLAY_FLAG_AMOLED                            0x80000000  /* Force AMOLED power configuration */

/* Maximum number of panels supported for a chip */
#define   MDPPLATFORM_PANELS_SUPPORTED_MAX               32

/* Maximum length of panel name
*/
#define DISPLAY_PANEL_NAME_MAX_LEN                       64

/* Maximum length of panel config item length
*/
#define DISPLAY_PANEL_CONFIG_ITEM_MAX_LEN                64

/* Maximum length of kernel mode info
*/
#define DISPLAY_PANEL_KERNELMODE_INFO_MAX_LEN            128

/* Maximum length of Device Tree tag
*/
#define DISPLAY_PANEL_DT_LABEL_MAX_LEN                   64

/* Maximum number of display topology
*/
#define DISPLAY_MODE_MAX                                 3

/* panel reset timing */
#define MDP_GPIO_RESET_ASSERT_TIME                       50
#define MDP_GPIO_PRE_RESET_TIME                          1000
#define MDP_GPIO_POST_RESET_TIME                         10000

/* Panel override - Stored in a environment variable
 */
#define PANEL_OVERRIDE_STRINGNAME                        L"DISPLAYID"
#define PANEL_OVERRIDE_ENABLE_MASK                       (0x80000000)
#define PANEL_OVERRIDE_PANELID(_ID_)                     (~PANEL_OVERRIDE_ENABLE_MASK & (_ID_))

/* Supported display list - TRUE: Enabled, FALSE: Disabled. */
extern bool32 gSupportedDisplayList[MDP_DISPLAY_MAX];

/* Macro to check whether display id is supported or not. */
#define MDP_SUPPORTED_DISPLAY(eDisplayId) (gSupportedDisplayList[eDisplayId])

/*===========================================================================
                        Enumerations
===========================================================================*/

/* List of support platform specific configurations
 */
typedef enum
{
  MDPPLATFORM_CONFIG_INIT           = 0x0,               /* Initialize MDP resources that should be done once */
  MDPPLATFORM_CONFIG_GETPANELCONFIG,                     /* Retrieve panel configuration */
  MDPPLATFORM_CONFIG_POWERUP,                            /* Power up power grid */
  MDPPLATFORM_CONFIG_POWERDOWN,                          /* Power down power grid */
  MDPPLATFORM_CONFIG_GETPANELID,                         /* Return the panel identifier */
  MDPPLATFORM_CONFIG_SETBACKLIGHT,                       /* Set a brightness or backlight level */
  MDPPLATFORM_CONFIG_GETPLATFORMINFO,                    /* Return platform configuration information */
  MDPPLATFORM_CONFIG_SW_RENDERER,                        /* Return SW render mode information */
  MDPPLATFORM_CONFIG_RESETPANEL,                         /* Physical reset of the panel */
  MDPPLATFORM_CONFIG_SETGPIOSTATE,                       /* Set the state of a GPIO */
  MDPPLATFORM_CONFIG_GETPANELDTINFO,                     /* Get panel config info */
  MDPPLATFORM_CONFIG_BYPASS,                             /* Configuration bypass */
  MDPPLATFORM_CONFIG_GETPANELXMLINFO,                    /* Get a specific panel configuration (xml config) */
  MDPPLATFORM_CONFIG_GETSPRXMLINFO,                      /* Get SPR configuration (xml config) */
  MDPPLATFORM_CONFIG_SELECTPANELCONFIG,                  /* Select panel config for physical/simulation panel */
  MDPPLATFORM_CONFIG_MAX
} MDPPlatformConfigType;

/* GPIO Types */
typedef enum
{
  MDPPLATFORM_GPIOTYPE_TLMM = 0x0,                        /* TLMM GPIO */
  MDPPLATFORM_GPIOTYPE_PMIC,                              /* PMIC GPIO */
  MDPPLATFORM_GPIOTYPE_PMI,                               /* PMI GPIO */
} MDPPlatformGPIOType;

typedef enum
{
  DISP_INTF_NONE                          = 0x0,          /* No interface specified */
  DISP_INTF_HDMI                          = 0x1,          /* HDMI */
  DISP_INTF_DSI                           = 0x2,          /* DSI */
  DISP_INTF_DP                            = 0x3           /* DisplayPort */
} DisplayInterfaceType;

/* AMOLED Control Type
 */
typedef enum
{
  MDPPLATFORM_LABIBB_MODE_SWIRE           = 0x0,          /* SWIRE Control(Default) */
  MDPPLATFORM_LABIBB_MODE_SPMI                            /* SPMI Control */
} MDPPlatformLABIBBModeType;

/* Power Config Flag
 */
typedef enum
{
  POWERCONFIG_FLAGS_PANEL_POWER           = 0x1,          /* Panel Specific Power */
} PowerConfig_Flags;

/* Panel types
 */
typedef enum
{
  MDPPLATFORM_PANEL_BYPASS = 0,                          /* Panel not supported, but configuration is passed to kernel */
  MDPPLATFORM_PANEL_PHYSICAL,                            /* Physical panel */
  MDPPLATFORM_PANEL_SIMULATION,                          /* Simulation panel */
  MDPPLATFORM_PANEL_MAX,
} MDPPlatformPanelType;

/* Display auto detection types
 */
typedef enum
{
  MDP_DISPLAY_AUTODETECT_DISABLE = 0,                    /* Disable display auto detection */
  MDP_DISPLAY_AUTODETECT_MIPI_DPHY,                      /* Enable display auto detection for dphy */
  MDP_DISPLAY_AUTODETECT_MIPI_CPHY,                      /* Enable display auto detection for cphy */
  MDP_DISPLAY_AUTODETECT_MAX,
} MDPDisplayAutoDetectType;

/*===========================================================================
                        Structs
===========================================================================*/
/* Platform identification information
 */
typedef struct
{
   EFI_PLATFORMINFO_PLATFORM_INFO_TYPE  sEFIPlatformType;                   /* [out] EFI Platform information */
   EFIChipInfoIdType                    sEFIChipSetId;                      /* [out] EFI Chipset information */
   EFIChipInfoFamilyType                sEFIChipSetFamily;                  /* [out] EFI Chipset family information */
   uint32                               uPrimaryPanelId;                    /* [out] Primary panel ID */
   bool32                               bSWRender;                          /* [out] Indicates if the displayDxe is SW renderer only */
   uint32                               uPanelIdOverride;                   /* [out] Panel ID Override configuration */
   bool32                               bSWRenderOverrride;                 /* [in]  Force SW render mode */
   MDP_RotateFlipType                   uPanelOrientationOverride;          /* [out] Panel orientation override */
   bool32                               bPanelInitialized[MDP_DISPLAY_MAX]; /* [out] Indicates if panel configuration was done */
   uint8                                uPlatformID;                        /* [out] Platform ID information */
} MDPPlatformInfo;


typedef struct
{
    uint32 uResetGpio;            /* reset gpio pin number */
    uint32 uAssertState;          /* LEVEL_LOW, LEVEL_HIGH, EDGE_LOW2HIGH, EDGE_HIGH2LOW */
    uint32 uPreResetTimeUs;       /* Time from regulator ready to start of reset pin asserted */
    uint32 uResetAssertTimeUs;    /* Time of reset gpio pin asserted */
    uint32 uPostResetTimeUs;      /* Time between reset gpio pin de-asserted, can be extended by InitMaster */
    uint32 uAssertOnPowerDown;    /* assert during power down */
}MDPPlatformPanelResetInfo;

/* Panel XML configuration
 */
typedef struct
{
    CHAR8                       szName[DISPLAY_PANEL_NAME_MAX_LEN]; /* Panel Name */
    int8                       *pPanelXMLConfig;                    /* xml configuration for panel */
    uint32                      uConfigSize;                        /* size of the xml configuration data in bytes*/
    uint8                       uDefaultVendor;                     /* vendor ID */
    uint8                       uDefaultRevision;                   /* revision */
    uint32                      uPanelId;                           /* if set, find the panel that matches this panel ID */
    uint32                      uPowerGridId;                       /* power grid id */
    MDPDisplayAutoDetectType    eAutoDetect;                        /* dynamic detection type for the panel */
} MDPPlatformPanelInfo;


/* HDMI configuration*/
typedef struct
{
  uint32 uCecDataGpio;
  uint32 uDDCDataGpio;
  uint32 uDDDClkGpio;
  uint32 uHPDGpio;
} HDMI_PinInfo;


/* Backlight configuration */
typedef struct
{
    bool32                          bEnable;               /* Enable/disable the backlight/brightness power grid */
    uint32                          uLevel;                /* New brightness level in percentage, 0-100% */
    uint32                          uNumBits;              /* The bit width to control dcs brightness level, default is 8 for 8 bits */
    MDP_Panel_BacklightType         eBacklightType;        /* Configuration of the backlight interface module */
    union {
        MDP_PmicBacklightControlType  eBacklightCtrl;      /* PMIC module for backlight configuration  */
        MDP_I2C_Configuration         sI2CConfig;          /* I2C  module for backlight configuration  */
    } uBacklightCntrl;

} BacklightConfigType;

/* Power configuration */
typedef struct
{
    uint32                          uFlags;                   /* uFlags used to indicate the power type that needs to be powered up / down */
} PowerConfigType;


/* GPIO State */
typedef struct
{
    MDPPlatformGPIOType             eGPIOType;       /* Type of GPIO to be configured */
    uint32                         *pGPIOList;       /* Pointer to an list of GPIO's to be modified */
    uint32                          uListSize;       /* Number of entries in the list */
    uint32                          uState;          /* GPIO state */
} GpioStateType;


/* Power configuration
 */
typedef struct
{
  bool32                        bDisplayNPAStatus[MDP_DISPLAY_MAX];      /* NPA client status for power control */
  npa_client_handle             sNPAClient[MDP_DISPLAY_MAX];             /* NPA client handles for power control of panels */
  npa_client_handle             sTouchNPAClient;                         /* NPA client handles for power control of Touch */
  MDPPlatformLABIBBModeType     eOLEDPowerMode;                          /* Swire or spmi mode*/
  uint32                        uResetGpio;
  bool32                        bBacklightEnabled;
} Panel_PowerCtrlParams;

/* Display panel gpio type
 */
typedef struct
{
  uint32                uDispResetGpio;                                  /* Display reset gpio */
  uint32                uDispTeGpio;                                     /* Display te gpio */
  uint32                uDispTeGpioFuncSelect;                           /* Display te gpio function select */
} MDPPlatformPanelGpioType;

/* Display panel mode config
 */
typedef struct
{
  DisplayInterfaceType          eInterface;                              /* Interface type */
  uint32                        uModeFlag;                               /* Display operating modes for the panel, refer DisplayModeType */
} MDPPlatformModeInfoType;

/* Panel power / brightness control function type
 */
typedef struct
{
  /* The display gpio used by the panel selected.
   */
  MDPPlatformPanelGpioType        *pMDPPlatformPanelGpio;

  /* Panel power up function
   * - Enable all rails, gpios necessary to start driving the panel.
   */
  MDP_Status                     (*pPanel_PowerUp) (MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);

  /* Panel power down function
   * - Disable all rails, gpios, and backlight to put the peripheral in to the lowest power state.
   */
  MDP_Status                    (*pPanel_PowerDown) (MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);

  /* Panel reset
   * - Toggling the panels reset pin to reset the peripheral back to a idle state.
   */
  MDP_Status                    (*pPanel_Reset) (MDPPlatformPanelResetInfo *pResetInfo);

  /* Panel brightness enable (Optional)
   * - Configuration of the components required to drive the brightness,
   *   but should leave output level as 0% at exit of this function.
   */
  MDP_Status                    (*pPanel_Brightness_Enable) (MDP_Display_IDType eDisplayId, Panel_PowerCtrlParams *pPowerParams);

  /* Panel brightness level (Optional)
   * - Configure the brightness level of the panel.
   */
  MDP_Status                    (*pPanel_Brightness_Level) (MDP_Display_IDType eDisplayId, BacklightConfigType *pBacklightConfig);

} MDPPlatformHardwareConfig;

/* Physical panel config
 */
typedef struct
{
  CHAR8                         szName[DISPLAY_PANEL_NAME_MAX_LEN];                     /* Name used by fastboot oem command */
  CHAR8                         szXmlName[DISPLAY_PANEL_NAME_MAX_LEN];                  /* Xml file name for this panel */
  CHAR8                         DTLabel[DISPLAY_PANEL_DT_LABEL_MAX_LEN];                /* Device tree node name */
  MDPPlatformModeInfoType      *pModeInfo;                                              /* Mode infomation */
  MDPPlatformHardwareConfig    *pHwConfig;                                              /* HW configs */
} PhysicalPanelConfigType;

/* Simulation panel config
 */
typedef struct
{
  CHAR8                         szName[DISPLAY_PANEL_NAME_MAX_LEN];                      /* Name used by fastboot oem command */
  CHAR8                         DTLabel[DISPLAY_PANEL_DT_LABEL_MAX_LEN]; /* Device tree node name */
  CHAR8                         szKernelModeInfo[DISPLAY_PANEL_KERNELMODE_INFO_MAX_LEN]; /* Includes topology and timing info */
} SimPanelConfigType;

/* Panel config of a physical panel or simulation panel */
typedef struct
{
  MDP_Display_IDType            eDisplayId;                                              /* Display device ID */
  MDPPlatformPanelType          ePanelType;                                              /* Panel type */
  CHAR8                         szName[DISPLAY_PANEL_NAME_MAX_LEN];                      /* Panel name */
  union
  {
    PhysicalPanelConfigType    *pPhysicalPanelConfig;                                    /* Points to panel config that built into binary */
    SimPanelConfigType          sSimPanelConfig;                                         /* Panel config that dynamically parsed out */
  };
} PanelConfigType;


/* Display port configuration for Type-C */
typedef struct
{
  bool32                     bInvertPlugPolarity;          /* cable plug orientation: only valid for DP over USB-type C */
  bool32                     bReversePhyDataPath;          /* DP PHY lane to pad mapping is reverse of DP alt mode on USB type-C spec */
} DP_InterfaceInfo;


/* Panel information and override struture  */
typedef struct
{
  uint32                     uIndex;                       /* Panel index to be queried */
  int8                      *pPanelXMLConfig;              /* Panel configuration (raw). */
  uint32                     uPanelXMLSize;                /* Size of the panel configuration in bytes */
} PanelXmlInfoType;

/* SPR XML information
 */
typedef struct
{
  int8                      *pSprXMLConfig;                /* SPR configuration (raw). */
  uint32                     uSprConfigSize;               /* Size of the SPR configuration in bytes */
} SprXmlInfoType;

/* Panel config information
 */
typedef struct
{
  PanelConfigType           *pPanelConfig;                 /* Panel Config */
} PanelConfigInfoType;

/* Union of panel properties passed to MDPPlatformConfigure() function
*/
typedef union
{
    MDPPlatformPanelInfo       sPlatformPanel;      /* MDPPLATFORM_CONFIG_GETPANELCONFIG(Primary) */
    HDMI_PinInfo               sHDMIPinConfig;      /* MDPPLATFORM_CONFIG_GETPANELCONFIG(HDMI) */
    DP_InterfaceInfo           sDPConfig;           /* MDPPLATFORM_CONFIG_GETPANELCONFIG(DP) */
    BacklightConfigType        sBacklightConfig;    /* MDPPLATFORM_CONFIG_SETBACKLIGHT */
    MDPPlatformInfo            sPlatformInfo;       /* MDPPLATFORM_CONFIG_GETPLATFORMINFO */
    MDPPlatformPanelResetInfo  sPlatformPanelReset; /* MDPPLATFORM_CONFIG_RESETPANEL */
    PowerConfigType            sPowerConfig;        /* MDPPLATFORM_CONFIG_POWERUP/MDPPLATFORM_CONFIG_POWERDOWN */
    GpioStateType              sGPIOState;          /* MDPPLATFORM_CONFIG_SETGPIOSTATE */
    PanelConfigType           *pPanelConfig;        /* MDPPLATFORM_CONFIG_GETPANELDTINFO */
    PanelXmlInfoType           sPanelXMLInfo;       /* MDPPLATFORM_CONFIG_GETPANELXMLINFO */
    SprXmlInfoType             sSprXMLInfo;         /* MDPPLATFORM_CONFIG_GETSPRXMLINFO */
    PanelConfigInfoType        sPanelConfigInfo;    /* MDPPLATFORM_CONFIG_SELECTPANELCONFIG */
} MDPPlatformParams;


/*===========================================================================

                        Public Functions

===========================================================================*/

/* MDP platform specific configuration function
 */
MDP_Status MDPPlatformConfigure(MDP_Display_IDType eDisplayId, MDPPlatformConfigType eConfig, MDPPlatformParams *pPlatformParams);


#endif // __MDPLIB_H__


