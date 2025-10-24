/**
 * @file:  cpr_image_target.c
 *
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/CPRTargetLib/image/xbl/target/kailua/cpr_image_target.c#1 $
 * $Change: 39147961 $
 */
#include "cpr_image_target.h"
#include "cpr_logs.h"
#include "cpr.h"
#include "cpr_smem.h"
#include "cpr_utils.h"

#include "XBLConfig.h"
#include "PlatformInfo.h"
#include <DDIPlatformInfo.h>

bool cpr_image_target_update_margins(cpr_bin_payload *cpr_bin_data)
{
    int i = 0;
    uint32 modesCount = 0;
    const cpr_versioned_voltage_plan *vvp = NULL;

    vvp = cpr_utils_get_versioned_voltage_plan(cpr_bin_data->rail);
    for (i = 0; i < vvp->count; i++)
    {
        struct voltage_plan_list *vplist = &(vvp->list[i]);

        //Todo: Use correct min and max chipversion instead of the
        //simplified chip.
        if ((vplist->version->min)>>16 == cpr_bin_data->chip &&
                (vplist->version->max)>>16 == cpr_bin_data->chip)
        {
            struct cpr_voltage_data *modeData = NULL;
            cpr_margin_data *margins = NULL;
            cpr_voltage_plan *cfg = NULL;

            cfg = vplist->cfg;
            modesCount = cfg->modesCount;
            modeData = &(cfg->modes[(cpr_bin_data->mode)-1]);
            margins = cpr_utils_get_margins(cpr_bin_data->max,
                    modeData->margins);
            CORE_VERIFY(margins);
            margins->openLoop = cpr_bin_data->ol;
            margins->closedLoop = cpr_bin_data->cl;
            margins->maxFloorToCeil = cpr_bin_data->fToc;

            return true;
        }
    }

    return false;
}

boolean cpr_image_target_parse_bin(void)
{
  uint32 xbl_cfg_handle = 0;
    uint32 xbl_cfg_size   = 0;
    uint32 offset = 0;
    int dataCount = 0;

    xblconfig_status_type xbl_cfg_status = XBLCONFIG_SUCCESS;
    cpr_bin_payload *cpr_bin_data = NULL;

    xbl_cfg_status = xblconfig_open("/cpr.bin", &xbl_cfg_handle,
            &xbl_cfg_size);
    CORE_VERIFY(xbl_cfg_status == XBLCONFIG_SUCCESS);

    dataCount = xbl_cfg_size/sizeof(cpr_bin_payload);
    CPR_LOG_INFO("CPR Bin: totalSize: %d dataCount: %d", xbl_cfg_size,
            dataCount);

    cpr_bin_data = (cpr_bin_payload*)
        cpr_image_malloc(dataCount * sizeof(cpr_bin_payload));
    CORE_VERIFY_PTR(cpr_bin_data);

    xbl_cfg_status = xblconfig_read(xbl_cfg_handle, offset,
            xbl_cfg_size, (void*)cpr_bin_data);
    CORE_VERIFY(xbl_cfg_status == XBLCONFIG_SUCCESS);

    xblconfig_close(xbl_cfg_handle);

    for (int i=0; i < dataCount; i++)
    {
        if (!cpr_image_target_update_margins(&cpr_bin_data[i]))
        {
            CPR_LOG_WARNING("\n");
            CPR_LOG_WARNING("Margin Update Failed.\n\
                    \tRail:%d Mode:%d\n\
                    \tchip:%d min:%d max:%d\n\
                    \tmargins:[%d,%d,%d]\n",
                    cpr_bin_data[i]->rail, cpr_bin_data[i]->mode,
                    cpr_bin_data[i]->chip, cpr_bin_data[i]->min,
                    cpr_bin_data[i]->max, cpr_bin_data[i]->ol,
                    cpr_bin_data[i]->cl, cpr_bin_data[i]->fToC);

            CORE_VERIFY(0);
        }
    }

    cpr_image_free(cpr_bin_data);
    return true;
}

const cpr_settings* cpr_image_target_get_settings(void)
{
    extern const cpr_settings cpr_settings_kailua;

    return &cpr_settings_kailua;
}

boolean cpr_image_target_is_turbo_mode_only(void)
{
    return true;
}

cpr_domain_id cpr_image_target_railway_rail_to_cpr_domain(int railway_rail)
{
    switch(railway_rail)
    {
        case 0: return CPR_RAIL_MX;
        case 1: return CPR_RAIL_MXC;
        case 2: return CPR_RAIL_CX;
        case 3: return CPR_RAIL_VDDA;
        case 4: return CPR_RAIL_LPI_MX;
        case 5: return CPR_RAIL_LPI_CX;
        case 6: return CPR_RAIL_WLAN;
        default:
            CPR_LOG_FATAL("Unsupported rail %u", railway_rail);
            break;
    }

    CPR_ASSERT(0);

    return (cpr_domain_id)0;
}

railway_corner cpr_image_target_cpr_mode_to_railway_corner(cpr_voltage_mode mode)
{
    switch (mode)
    {
        default:
            return (railway_corner)mode;
			break;
	}

	return (railway_corner)0;
}

cpr_voltage_mode cpr_image_target_railway_corner_to_cpr_mode(railway_corner corner)
{
    switch (corner)
    {
        default:
            return (cpr_voltage_mode)corner;
			break;
	}

	return (cpr_voltage_mode)0;
}

void cpr_image_target_enable_measurements(cpr_rail* rail, cpr_measurement_type type)
{
    /* TODO: set rail to PWM */
}

void cpr_image_target_disable_measurements(cpr_rail* rail, cpr_measurement_type type)
{
    /* TODO: reset rail */
}

//Function to be called after SMEM is initialized to push out the CPR settings
//to SMEM. These settings are to be picked up by the RPM CPR driver during boot.
//Must be done before the RPM FW execution begins.
void cpr_externalize_state()
{
    CPR_LOG_INFO("Exporting CPR state");

    cpr_smem_serialize_config( cpr_utils_get_rail_state( CPR_RAIL_CX ),
            false );
    cpr_smem_serialize_config( cpr_utils_get_rail_state( CPR_RAIL_MX ),
            true );
    cpr_smem_serialize_config( cpr_utils_get_rail_state( CPR_RAIL_MXC ),
            true );
    cpr_smem_serialize_config( cpr_utils_get_rail_state( CPR_RAIL_VDDA ),
            true );
    cpr_smem_serialize_config( cpr_utils_get_rail_state( CPR_RAIL_LPI_CX),
            true );
    cpr_smem_serialize_config( cpr_utils_get_rail_state( CPR_RAIL_LPI_MX),
            true );
    cpr_smem_serialize_settings( cpr_utils_get_rail_state( CPR_RAIL_GFX),
            true );
    cpr_smem_serialize_settings( cpr_utils_get_rail_state( CPR_RAIL_MM),
            true );
    cpr_smem_serialize_settings( cpr_utils_get_rail_state( CPR_RAIL_MSS),
            true );
    cpr_smem_serialize_settings( cpr_utils_get_rail_state( CPR_RAIL_NSP),
            true );
    cpr_smem_serialize_settings( cpr_utils_get_rail_state( CPR_RAIL_WMSS_CX_1),
            true );
    cpr_smem_serialize_settings( cpr_utils_get_rail_state( CPR_RAIL_WMSS_CX_2),
            true );
    cpr_smem_serialize_settings( cpr_utils_get_rail_state( CPR_RAIL_WMSS_CX_3),
            true );
    cpr_smem_serialize_settings(cpr_utils_get_rail_state( CPR_RAIL_NAV_LDO),
            true );

    CPR_LOG_INFO("--- Done with CPR state export ---");
}

uint8 cpr_image_get_cprf_id(cpr_rail *rail)
{
    switch (rail->id)
    {
        case CPR_RAIL_MX: return 0;
        case CPR_RAIL_CX: return 1;
        case CPR_RAIL_VDDA: return 2;
        case CPR_RAIL_LPI_CX: return 3;
        case CPR_RAIL_LPI_MX: return 4;
        case CPR_RAIL_GFX: return 5;
        case CPR_RAIL_MSS: return 6;
        case CPR_RAIL_MM: return 7;
        case CPR_RAIL_MXC: return 8;
        case CPR_RAIL_NSP: return 9;
        default: return -1;
    }
}

void cpr_image_target_extra_init(void)
{
    return;
}

void cpr_image_target_init_rail_config(cpr_rail *rail)
{
    int modeIdx = 0;
    uint32 is_slt_platform = 0;
    uint32 is_aging_enabled = 0;
    DalDeviceHandle *phPlatformInfo = NULL;
    cpr_voltage_plan *vp = NULL;
    cpr_margin_cfg *margin_cfg = NULL;
    const cpr_versioned_voltage_plan* vvp =
        cpr_utils_get_versioned_voltage_plan( rail->id );

    if (DAL_SUCCESS ==
            DAL_DeviceAttach(DALDEVICEID_PLATFORMINFO, &phPlatformInfo))
    {
        DalPlatformInfo_GetKeyValue(phPlatformInfo,
                DALPLATFORMINFO_KEY_SLT, &is_slt_platform);
    }
    if(vvp->agingCfg &&
            (cpr_info.cprRev >= vvp->agingCfg->cprRevMinToRun))
    {
        is_aging_enabled = 1;
    }

    vp = rail->vp;
    for(modeIdx = 0; modeIdx < vp->modesCount; modeIdx++)
    {
        margin_cfg = vp->modes[modeIdx].margins;
        if(!margin_cfg)
        {
            continue;
        }

        for (int i = 0; i < margin_cfg->count; i++)
        {
            cpr_margin_data *margin_data = &margin_cfg->data[i];

            if (is_aging_enabled)
            {
                /*
                 * Add Aging Offset to OL and CL Margin
                 */
                margin_data->openLoop+=margin_data->agingOffset;
                CPR_LOG_INFO("Open loop margin %d updated by Aging Offset \
                        %d for rail:%d mode:%d", margin_data->openLoop,
                        margin_data->agingOffset, rail->id, modeIdx);

                margin_data->closedLoop+=margin_data->agingOffset;
                CPR_LOG_INFO("Closed loop margin %d updated by Aging Offset \
                        %d for rail:%d mode:%d", margin_data->closedLoop,
                        margin_data->agingOffset, rail->id, modeIdx);

                margin_data->agingOffset = 0;
            }

            if (is_slt_platform)
            {
                /*
                 * Add SLT Offset to OL and CL Margin
                 */
                margin_data->openLoop+=margin_data->sltOffset;
                CPR_LOG_INFO("Open loop margin %d updated by SLT Offset \
                        %d for rail:%d mode:%d", margin_data->openLoop,
                        margin_data->sltOffset, rail->id, modeIdx);

                margin_data->closedLoop+=margin_data->sltOffset;
                CPR_LOG_INFO("Closed loop margin %d updated by SLT Offset \
                        %d for rail:%d mode:%d", margin_data->closedLoop,
                        margin_data->sltOffset, rail->id, modeIdx);

                margin_data->sltOffset = 0;
            }
        }
    }
}

uint8 cpr_image_decode_vp_id(void)
{
    
    return 0; 
}
