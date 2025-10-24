/**
 * @file:  cpr_measurements.h
 * @brief:
 *
 * Copyright (c) 2015-2016 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/CPRLib/common/inc/cpr_measurements.h#1 $
 * $Change: 39147961 $
 */
#ifndef CPR_MEASUREMENTS_H
#define	CPR_MEASUREMENTS_H

#include "cpr_types.h"
#include "cpr_cfg.h"

void cpr_measurements_settle(cpr_rail* rail, cpr_voltage_mode mode);
void cpr_measurements_thermal_update(cpr_thermal_region region);
void cpr_measurements_aging(cpr_rail* rail);

#endif
