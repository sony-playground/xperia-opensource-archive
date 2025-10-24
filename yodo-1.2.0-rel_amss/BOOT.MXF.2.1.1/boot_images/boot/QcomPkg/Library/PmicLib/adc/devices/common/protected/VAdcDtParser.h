/*============================================================================
  FILE:         VAdcDtParser.c

  OVERVIEW:     Implementation of a parser for device tree configation node

  DEPENDENCIES: None

                Copyright (c) 2020 Qualcomm Technologies, Inc.
                All Rights Reserved.
                Qualcomm Technologies Proprietary and Confidential.
============================================================================*/


#include "VAdcBsp.h"

/*
 * Read the ADC DT config root and update the content of the BSP structure
 *
 * Input:
 * 	node       - Path to the root of the ADC DT config structure
 * Output:
 * 	pBsp       - Point to the BSP data structure
 *
 */
int vadc_read_dt_device_root(const char *node, VAdcBspType *pBsp);
