/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include "integration_ta.h"

struct integration_ta_context *g_integration_ta_context_ptr = NULL;

/* Implemented function from ta.h */
TA_ErrCode_t TA_SetConfig(const TA_Functions_t *pFuncs,
				uint32_t startAddr,
				uint32_t eBlkSize,
				uint8_t nbrOfBlks)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->SetConfig)) {
		return context->functions->SetConfig(context,
						pFuncs,
						startAddr,
						eBlkSize,
						nbrOfBlks);
	} else {
		return TA_UnsupportedCmd;
	}
}


TA_ErrCode_t TA_OpenPartition(uint8_t partition,
				uint8_t mode)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->OpenPartition)) {
		return context->functions->OpenPartition(context,
						partition,
						mode);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_Close(void)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->Close)) {
		return context->functions->Close(context);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_GetVersion(uint8_t *pVersion, uint8_t partition)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->GetVersion)) {
		return context->functions->GetVersion(context,
						pVersion,
						partition);
	} else {
		return TA_UnsupportedCmd;
	}
}

uint8_t TA_IsVersionSupported(uint8_t version)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->IsVersionSupported)) {
		return context->functions->IsVersionSupported(context,
						version);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_Format(uint8_t version)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->Format)) {
		return context->functions->Format(context,
						version);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_Flush(void)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->Flush)) {
		return context->functions->Flush(context);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_WriteData(uint32_t unit, const uint8_t *pData, uint32_t size)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->WriteData)) {
		return context->functions->WriteData(context,
						unit,
						pData,
						size);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_ReadData(uint32_t unit, uint8_t *pData, uint32_t size)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->ReadData)) {
		return context->functions->ReadData(context,
						unit,
						pData,
						size);
	} else {
		return TA_UnsupportedCmd;
	}
}

uint32_t TA_GetUnitSize(uint32_t unit)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->GetUnitSize)) {
		return context->functions->GetUnitSize(context,
						unit);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_DeleteUnit(uint32_t unit)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->DeleteUnit)) {
		return context->functions->DeleteUnit(context,
						unit);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_Open(const TA_Functions_t *pFuncs,
			uint8_t  mode,
			uint8_t  partition,
			uint32_t addr,
			uint32_t eBlkSize,
			uint8_t  nbrOfBlks)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->Open)) {
		return context->functions->Open(context,
						pFuncs,
						mode,
						partition,
						addr,
						eBlkSize,
						nbrOfBlks);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_Inc_GetSize(uint32_t *pSize)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->Inc_GetSize)) {
		return context->functions->Inc_GetSize(context,
						pSize);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_Inc_Read(uint32_t *pUnit, uint8_t *pData, uint32_t size)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->Inc_Read)) {
		return context->functions->Inc_Read(context,
						pUnit,
						pData,
						size);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_Inc_NextUnit(void)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->Inc_NextUnit)) {
		return context->functions->Inc_NextUnit(context);
	} else {
		return TA_UnsupportedCmd;
	}
}

TA_ErrCode_t TA_Inc_GetUnitID(uint32_t *pUnit)
{
	struct integration_ta_context *context =
		g_integration_ta_context_ptr;

	if ((NULL != context) &&
		(NULL != context->functions) &&
		(NULL != context->functions->Inc_GetUnitID)) {
		return context->functions->Inc_GetUnitID(context,
						pUnit);
	} else {
		return TA_UnsupportedCmd;
	}
}

