/*
 * Copyright (C) 2016 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#ifndef INTEGRATION_TA_H_
#define INTEGRATION_TA_H_

#include "xboot_pal_include.h"

struct integration_ta_context;

struct integration_ta_func {
	TA_ErrCode_t (*SetConfig)(
		struct integration_ta_context *context,
		const TA_Functions_t *pFuncs,
		uint32_t startAddr,
		uint32_t eBlkSize,
		uint8_t  nbrOfBlks);
	TA_ErrCode_t (*OpenPartition)(
		struct integration_ta_context *context,
		uint8_t partition,
		uint8_t mode);
	TA_ErrCode_t (*Close)(
		struct integration_ta_context *context);
	TA_ErrCode_t (*GetVersion)(
		struct integration_ta_context *context,
		uint8_t *pVersion,
		uint8_t partition);
	uint8_t (*IsVersionSupported)(
		struct integration_ta_context *context,
		uint8_t version);
	TA_ErrCode_t (*Format)(
		struct integration_ta_context *context,
		uint8_t version);
	TA_ErrCode_t (*Flush)(
		struct integration_ta_context *context);
	TA_ErrCode_t (*WriteData)(
		struct integration_ta_context *context,
		uint32_t unit,
		const uint8_t *pData,
		uint32_t size);
	TA_ErrCode_t (*ReadData)(
		struct integration_ta_context *context,
		uint32_t unit,
		uint8_t *pData,
		uint32_t size);
	uint32_t (*GetUnitSize)(
		struct integration_ta_context *context,
		uint32_t unit);
	TA_ErrCode_t (*DeleteUnit)(
		struct integration_ta_context *context,
		uint32_t unit);
	TA_ErrCode_t (*Open)(
		struct integration_ta_context *context,
		const TA_Functions_t *pFuncs,
		uint8_t  mode,
		uint8_t  partition,
		uint32_t addr,
		uint32_t eBlkSize,
		uint8_t  nbrOfBlks);
	TA_ErrCode_t (*Inc_GetSize)(
		struct integration_ta_context *context,
		uint32_t *pSize);
	TA_ErrCode_t (*Inc_Read)(
		struct integration_ta_context *context,
		uint32_t *pUnit,
		uint8_t *pData,
		uint32_t size);
	TA_ErrCode_t (*Inc_NextUnit)(
		struct integration_ta_context *context);
	TA_ErrCode_t (*Inc_GetUnitID)(
		struct integration_ta_context *context,
		uint32_t *pUnit);
};

struct integration_ta_context {
	struct integration_ta_func *functions;
};

extern struct integration_ta_context *g_integration_ta_context_ptr;

#endif

