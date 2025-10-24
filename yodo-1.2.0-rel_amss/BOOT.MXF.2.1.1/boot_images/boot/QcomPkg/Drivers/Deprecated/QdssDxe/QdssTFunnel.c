/*=============================================================================

FILE:         QdssTFunnel.c

DESCRIPTION:

================================================================================
                Copyright 2015 QUALCOMM Technologies Incorporated.
                         All Rights Reserved.
                QUALCOMM Proprietary and Confidential
================================================================================
  $Header: //components/dev/core.boot/6.1/boxiren.core.boot.6.1.boot_0314/QcomPkg/Drivers/QdssDxe/QdssTFunnel.c#1 $
==============================================================================*/

#include "HalQdssTFunnel.h"

void QdssTFunnel_PreInit(void)
{
  HAL_qdss_tfunnel_HalInit();
  return;
}

void QdssTFunnel_Init(void)
{
  HAL_qdss_tfunnel_EnableStm(); //Enable port and funnels for STM
  return;
}

