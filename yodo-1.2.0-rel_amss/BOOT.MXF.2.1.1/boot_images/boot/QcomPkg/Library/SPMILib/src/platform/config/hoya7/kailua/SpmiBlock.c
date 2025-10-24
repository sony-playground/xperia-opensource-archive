/**
 * @file:  SpmiBlock.c
 *
 * Copyright (c) 2013-2022 by Qualcomm Technologies
 * Incorporated. All Rights Reserved.
 *
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/SPMILib/src/platform/config/hoya7/kailua/SpmiBlock.c#1 $
 * $Change: 39147961 $
 *
 *                              Edit History
 * Date     Description
 * -------  -------------------------------------------------------------------
 * 10/1/13  Initial Version
 */

#include "SpmiInfo.h"
#include "SpmiTypes.h"
#include "SpmiHal.h"
#include "SpmiGenericConsts.h"
#include "SpmiUtils.h"
#include "SpmiOsTarget.h"
#include "SpmiBusCfg.h"

#define PMIC_ARB_BASE_ADDRESS 0x0C400000
#define QDSS_PMIC_ARB_BASE_ADDRESS   0x10B14000
#define SPMI_BARE_OWNER_NUMBER     0

#define FUSE_FEATURE_DEBUG_CONFIG_REG_ADDRESS   0x221C8784
#define FUSE_FEATURE_DEBUG_MASK    (1 << 18)
#define FUSE_FEATURE_DEBUG_VALUE   0x40000

#define SPMI_MAX_BUSES_SUPPORTED      (2)

static uint16 periphMap0[SPMI_MAX_PERIPH_ID + 1];
static uint16 periphMap1[SPMI_MAX_PERIPH_ID + 1];
static ChannelMapEntry channelMap0[SPMI0_MAX_CHANNELS_SUPPORTED];
static ChannelMapEntry channelMap1[SPMI1_MAX_CHANNELS_SUPPORTED];
static SpmiDeviceGenerics generics0 = INIT_SPMI0_DEV_GENERICS;
static SpmiDeviceGenerics generics1 = INIT_SPMI1_DEV_GENERICS;

static uint16 ownerMaskMap[SPMI_MAX_OWNER_IDS] = {
   SPMI_OWNER_APPS,    // ee id 0
   SPMI_OWNER_TZ,      // ee id 1
   SPMI_OWNER_MSS,     // ee id 2
   SPMI_OWNER_LPASS,   // ee id 3
   SPMI_OWNER_AOP,     // ee id 4
   SPMI_OWNER_SSC,     // ee id 5
   SPMI_OWNER_SECPROC, // ee id 6
   SPMI_OWNER_TME,     // ee id 7
};

static SpmiTargetConfig spmiTgt =
{
    .hwioAddrStr    = "AOSS",
    .interruptVec   = 0, // not used
};

SpmiDevInfo spmiDevices[] = {
   {
      .baseAddrs          = (uint8*)PMIC_ARB_BASE_ADDRESS,
      .baseAddrsDebugIf   = (uint8*)QDSS_PMIC_ARB_BASE_ADDRESS,
      .uDevIdx            = 0,
      .reservedChan       = SPMI0_MAX_CHANNELS_SUPPORTED - 1,
      .nextChanIdx        = 0,
      .reservedChanEn     = TRUE,
      .dynamicChannelMode = FALSE,
      .periphMap          = periphMap0,
      .channelMap         = channelMap0,
      .ownerMaskMap       = ownerMaskMap,
      .pGenerics          = &generics0,
      .target             = (void*) &spmiTgt,
      .numPmicArbChan     = 0,
      .busChanStart       = 0,
   },
   {
      .baseAddrs          = (uint8*)PMIC_ARB_BASE_ADDRESS,
      .baseAddrsDebugIf   = (uint8*)QDSS_PMIC_ARB_BASE_ADDRESS,
      .uDevIdx            = 1,
      .reservedChan       = SPMI1_MAX_CHANNELS_SUPPORTED - 1,
      .nextChanIdx        = 0,
      .reservedChanEn     = TRUE,
      .dynamicChannelMode = FALSE,
      .periphMap          = periphMap1,
      .channelMap         = channelMap1,
      .ownerMaskMap       = ownerMaskMap,
      .pGenerics          = &generics1,
      .target             = (void*) &spmiTgt,
      .numPmicArbChan     = 768,
      .busChanStart       = SPMI0_MAX_CHANNELS_SUPPORTED,
   },
};

SpmiInfo spmiInfo = {
  .owner              = SPMI_BARE_OWNER_NUMBER,
  .rgOwnerMask        = SPMI_OWNER_AOP|SPMI_OWNER_TZ|SPMI_OWNER_MSS,
  .uNumDevices        = SPMI_MAX_BUSES_SUPPORTED,
  .devices            = spmiDevices,
};

SpmiDebugFuseInfo spmiDbgFuse = {
	.regAddrsDebugFuse  = (uint32*)FUSE_FEATURE_DEBUG_CONFIG_REG_ADDRESS,
	.DebugFuseMask      = FUSE_FEATURE_DEBUG_MASK,
	.DebugFuseValueEn   = FUSE_FEATURE_DEBUG_VALUE,
}; 

SpmiInfo * pSpmiBlockInfo = &spmiInfo;

