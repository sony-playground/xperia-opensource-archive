/**
 * @file:  cpr_image_target.c
 *
 * Copyright (c) 2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * QUALCOMM Proprietary and Confidential.
 *
 * $DateTime: 2022/08/18 10:15:46 $
 * $Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/CPRTargetLib/image/core/target/kailua/cpr_image_target.c#1 $
 * $Change: 39147961 $
 */
#include "cpr_image_target.h"
#include "cpr_image.h"
#include "cpr_logs.h"
#include "cpr_smem.h"

#include "voltage_level.h"
#include "cmd_db.h"
#include "rpmh_client.h"
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/EFIClock.h>
#include "gpu_clk_hwio.h"

static EFI_CLOCK_PROTOCOL *gpuClockProtocol = NULL;
static UINTN  gpuClkPwrDomainId;

static rpmh_client_handle aging_client_handle;

static uint32 cpr_pte_qc_spare_fuse;

boolean cpr_image_target_parse_bin(void)
{
    return true;
}

const cpr_settings* cpr_image_target_get_settings(void)
{
    int i = 0;

    cpr_settings *cpr_settings_kailua =
        (cpr_settings*)cpr_image_malloc(sizeof(cpr_settings));
    CPR_ASSERT(cpr_settings_kailua);

    cpr_settings_kailua->railsCount = 2;
    cpr_settings_kailua->enablementsCount = 2;
    cpr_settings_kailua->controllersCount = 2;

    cpr_settings_kailua->railVVPs = (cpr_versioned_voltage_plan **) \
        cpr_image_malloc(sizeof(cpr_versioned_voltage_plan *) * \
                cpr_settings_kailua->railsCount);
    for (i = 0; i < cpr_settings_kailua->railsCount; i++) {
        cpr_settings_kailua->railVVPs[i] = (cpr_versioned_voltage_plan *) \
            cpr_image_malloc(sizeof(cpr_versioned_voltage_plan));
    }

    cpr_settings_kailua->controllers = (cpr_hal_controller **) \
        cpr_image_malloc(sizeof(cpr_hal_controller *) * \
                cpr_settings_kailua->controllersCount);
    for (i = 0; i < cpr_settings_kailua->controllersCount; i++) {
        cpr_settings_kailua->controllers[i] = (cpr_hal_controller *) \
            cpr_image_malloc(sizeof(cpr_hal_controller));
    }

    cpr_settings_kailua->rails = (cpr_rail **) cpr_image_malloc(
            sizeof(cpr_rail *) * cpr_settings_kailua->railsCount);
    for (i = 0; i < cpr_settings_kailua->railsCount; i++) {
        cpr_settings_kailua->rails[i] =
            (cpr_rail *) cpr_image_malloc(sizeof(cpr_rail));
    }

    cpr_settings_kailua->enablements = (cpr_enablement **) \
        cpr_image_malloc(sizeof(cpr_enablement *) * \
                cpr_settings_kailua->enablementsCount);
    for (i = 0; i < cpr_settings_kailua->enablementsCount; i++) {
        cpr_settings_kailua->enablements[i] =
            (cpr_enablement *)cpr_image_malloc(sizeof(cpr_enablement));
    }

    cpr_settings_kailua->miscCfg = (cpr_misc_cfg *)
        cpr_image_malloc(sizeof(cpr_misc_cfg));

    cpr_rail gfx_rail;
    gfx_rail.id = CPR_RAIL_GFX;
    cpr_smem_deserialize_settings(&gfx_rail, cpr_settings_kailua, /*idx*/ 0);

    cpr_rail mm_rail;
    mm_rail.id = CPR_RAIL_MM;
    cpr_smem_deserialize_settings(&mm_rail, cpr_settings_kailua, /*idx*/ 1);

    return cpr_settings_kailua;
}

boolean cpr_image_target_is_turbo_mode_only(void)
{
    /*
     * CR 1050500:
     * TURBO_MODE_ONLY fuse: QC Spare 16[45] - bit 13 of 0x780324/0x784324
     */
    cpr_pte_qc_spare_fuse =
        CPR_HWIO_IN(QFPROM_CORR_REG_BASE + 0x004324);

    return ((cpr_pte_qc_spare_fuse & (1 << 13)) != 0);
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

void cpr_image_target_cpr_to_arc_domain(cpr_domain_id railId, char **res_name)
{
    switch(railId)
    {
        case CPR_RAIL_MX 	 : *res_name = "mx.lvl";     break;
        case CPR_RAIL_MXC 	 : *res_name = "mxc.lvl";    break;
        case CPR_RAIL_CX	 : *res_name = "cx.lvl";     break;
        case CPR_RAIL_GFX	 : *res_name = "gfx.lvl";    break;
        case CPR_RAIL_MM	 : *res_name = "mmcx.lvl";   break;
		case CPR_RAIL_LPI_MX : *res_name = "lmx.lvl";    break;
        case CPR_RAIL_LPI_CX : *res_name = "lcx.lvl";    break;
        case CPR_RAIL_NSP    : *res_name = "nsp.lvl";    break;
        default:
            CPR_LOG_FATAL("Unsupported rail %u", railId);
            break;
    }

    CPR_LOG_TRACE("Got resource %s", res_name);
	return;
}

railway_corner cpr_image_target_cpr_mode_to_railway_corner(cpr_voltage_mode mode)
{
    switch (mode)
    {
        default:
            return (railway_corner)mode;
	}

	return (railway_corner)0;
}

cpr_voltage_mode cpr_image_target_railway_corner_to_cpr_mode(railway_corner corner)
{
    switch (corner)
    {
        default:
	        return (cpr_voltage_mode)corner;
	}

	return (cpr_voltage_mode)0;
}

rail_voltage_level cpr_image_target_cpr_mode_to_vlvl(cpr_voltage_mode mode)
{
    switch (mode)
    {
        case CPR_VOLTAGE_MODE_OFF        : return  RAIL_VOLTAGE_LEVEL_OFF;
        case CPR_VOLTAGE_MODE_RETENTION  : return  RAIL_VOLTAGE_LEVEL_RET;
        case CPR_VOLTAGE_MODE_MIN_SVS    : return  RAIL_VOLTAGE_LEVEL_MIN_SVS;
        case CPR_VOLTAGE_MODE_LOW_SVS_D1 : return  RAIL_VOLTAGE_LEVEL_LOW_SVS_D1;
        case CPR_VOLTAGE_MODE_LOW_SVS    : return  RAIL_VOLTAGE_LEVEL_LOW_SVS;
        case CPR_VOLTAGE_MODE_LOW_SVS_P1 : return  RAIL_VOLTAGE_LEVEL_LOW_SVS_P1;
        case CPR_VOLTAGE_MODE_LOW_SVS_L1 : return  RAIL_VOLTAGE_LEVEL_LOW_SVS_L1;
        case CPR_VOLTAGE_MODE_LOW_SVS_L2 : return  RAIL_VOLTAGE_LEVEL_LOW_SVS_L2;
        case CPR_VOLTAGE_MODE_SVS        : return  RAIL_VOLTAGE_LEVEL_SVS;
        case CPR_VOLTAGE_MODE_SVS_L0     : return  RAIL_VOLTAGE_LEVEL_SVS_L0;
        case CPR_VOLTAGE_MODE_SVS_L1     : return  RAIL_VOLTAGE_LEVEL_SVS_L1;
        case CPR_VOLTAGE_MODE_SVS_L2     : return  RAIL_VOLTAGE_LEVEL_SVS_L2;
        case CPR_VOLTAGE_MODE_NOMINAL    : return  RAIL_VOLTAGE_LEVEL_NOM;
        case CPR_VOLTAGE_MODE_NOMINAL_L0 : return  RAIL_VOLTAGE_LEVEL_NOM_L0;
        case CPR_VOLTAGE_MODE_NOMINAL_L1 : return  RAIL_VOLTAGE_LEVEL_NOM_L1;
        case CPR_VOLTAGE_MODE_NOMINAL_L2 : return  RAIL_VOLTAGE_LEVEL_NOM_L2;
        case CPR_VOLTAGE_MODE_TURBO      : return  RAIL_VOLTAGE_LEVEL_TUR;
        case CPR_VOLTAGE_MODE_TURBO_L1   : return  RAIL_VOLTAGE_LEVEL_TUR_L1;
        default:
            CPR_LOG_FATAL("Unsupported Voltage mode %u", mode);
			break;
	}

	CPR_ASSERT(0);
	return (rail_voltage_level)0;
}

void cpr_image_target_enable_measurements(cpr_rail* rail, cpr_measurement_type type)
{
    /* TODO: set rail to PWM */
}

void cpr_image_target_disable_measurements(cpr_rail* rail, cpr_measurement_type type)
{
    /* TODO: reset rail */
}

static uint32 cpr_image_target_query_rail_hlvl(const char *res_name,
        rail_voltage_level vlvl)
{
	uint32 data_len;
	uint8 aux_len;
	uint16 *res_vlvls;
	size_t res_count;
	uint32 i;

	data_len = cmd_db_query_len (res_name);
	aux_len = (uint8)data_len;

	res_vlvls = (uint16 *) cpr_image_malloc(data_len);
    CORE_VERIFY (res_vlvls != NULL);
    res_count = data_len / sizeof(uint16);

	cmd_db_query_aux_data (res_name, &aux_len, (uint8 *)res_vlvls);
    CORE_VERIFY (data_len == (uint32)aux_len);

	//checking if vlvl is a valid for this rail.
	if ( ((int)vlvl < 0) )
	{
        cpr_image_free(res_vlvls);
		return -1;
	}

	for (i = 0; i < res_count; i++)
	{
		if (res_vlvls[i] >= vlvl)
		{
            cpr_image_free(res_vlvls);
            return i;
		}
		else if ((res_vlvls[i]) == 0 && (i != 0))
		{
            break;
		}
	}

  /* Input vlvl is higher than highest vlvl supported by this resource -
   * return the hlvl corresponding highest vlvl */
  cpr_image_free(res_vlvls);
  return i-1;
}

static void cpr_image_target_get_gpu_power_domain_info(void)
{
    if (gpuClockProtocol==NULL)
    {
        //get global clock protocol info
        gBS->LocateProtocol(&gEfiClockProtocolGuid, NULL,
                (VOID **)&gpuClockProtocol);
    }
    CORE_VERIFY_PTR(gpuClockProtocol);

    //Get power domain info for GPU gx_gdsc
    if (gpuClkPwrDomainId)
        return;

    if (gpuClockProtocol->GetClockPowerDomainID(gpuClockProtocol,
                "gpu_cc_gx_gdsc", &gpuClkPwrDomainId) != EFI_SUCCESS)
	{
		CPR_LOG_ERROR("Failed to get GPU ClockPowerDomainID");
		CPR_ASSERT(0);
	}
}

static boolean cpr_image_target_set_mm_rail_mode(cpr_domain_id railId,
        cpr_domain_info* info)
{
	char *res_name = NULL;
    uint32 req_id = 0;
    uint32 arc_addr = 0;
    uint32 hlvl = 0;
    rail_voltage_level vlvl = RAIL_VOLTAGE_LEVEL_OFF;
    cpr_voltage_mode mode = CPR_VOLTAGE_MODE_NOMINAL;

	cpr_image_target_cpr_to_arc_domain(railId, &res_name );
	CORE_VERIFY_PTR(res_name);

    if (info->u.mode != CPR_VOLTAGE_MODE_OFF)
    {
        mode = info->u.mode;
    }
    else
    {
        mode = CPR_VOLTAGE_MODE_NOMINAL;
    }

	vlvl = cpr_image_target_cpr_mode_to_vlvl(mode);
    CPR_LOG_TRACE("CPR(%d) Mode: %d == vlvl %d", railId, mode, vlvl);

	hlvl = cpr_image_target_query_rail_hlvl (res_name,  vlvl);
    CPR_LOG_TRACE("CPR(%d) Mode: %d == hlvl %d", railId, mode, hlvl);

	//checking if hlvl is valid
	if(hlvl > 15)
	{
		CPR_LOG_ERROR("Invalid HLVL");
		CPR_ASSERT(0);
	}

	arc_addr = cmd_db_query_addr(res_name);
    CPR_LOG_TRACE("CPR:%d ARC address = %d", railId, arc_addr);

	if (aging_client_handle == NULL)
	{
		aging_client_handle = rpmh_create_handle(RSC_DRV_HLOS, "CPR_AGING");
		CORE_VERIFY_PTR(aging_client_handle);
	}

    req_id = rpmh_issue_command(aging_client_handle, RPMH_SET_ACTIVE, 1,
            arc_addr, hlvl);
    rpmh_barrier_single (aging_client_handle, req_id);

    return TRUE;
}

static boolean cpr_image_target_set_gfx_rail_mode(cpr_domain_id railId,
        cpr_domain_info* info)
{
	char *res_name = NULL;
    uint32 req_id = 0;
    uint32 arc_addr = 0;
    uint32 hlvl = 0;
    rail_voltage_level vlvl = RAIL_VOLTAGE_LEVEL_OFF;

    cpr_image_target_get_gpu_power_domain_info();

	cpr_image_target_cpr_to_arc_domain(railId, &res_name );
	CORE_VERIFY_PTR(res_name);

	vlvl = cpr_image_target_cpr_mode_to_vlvl(info->u.mode);
    CPR_LOG_TRACE("CPR Mode: %d == vlvl %d", info->u.mode, vlvl);

	hlvl = cpr_image_target_query_rail_hlvl (res_name,  vlvl);
    CPR_LOG_TRACE("CPR Mode: %d == hlvl %d", info->u.mode, hlvl);

	//checking if hlvl is valid
	if(hlvl > 15)
	{
		CPR_LOG_ERROR("Invalid HLVL");
		CPR_ASSERT(0);
	}

	arc_addr = cmd_db_query_addr(res_name);
    CPR_LOG_TRACE("ARC address = %d", arc_addr);

	if (aging_client_handle == NULL)
	{
		aging_client_handle = rpmh_create_handle(RSC_DRV_HLOS, "CPR_AGING");
		CORE_VERIFY_PTR(aging_client_handle);
	}

	if (info->u.mode == CPR_VOLTAGE_MODE_OFF)
	{
		//disable gpu power domain first and turn off rail
		if (gpuClockProtocol->DisableClockPowerDomain(gpuClockProtocol,
                    gpuClkPwrDomainId) != EFI_SUCCESS)
		{
			CPR_LOG_ERROR("Failed to Disable GPU ClockPowerDomain");
			CPR_ASSERT(0);
		}

		req_id = rpmh_issue_command(aging_client_handle, RPMH_SET_ACTIVE, 1,
                arc_addr, hlvl);
		rpmh_barrier_single (aging_client_handle, req_id);

		//done with using aging handle
		//rpmh_delete_handle(aging_client_handle);
	}
	else
	{
		//turn on rail first and enable gpu power domain 
		req_id = rpmh_issue_command(aging_client_handle, RPMH_SET_ACTIVE, 1,
                arc_addr, hlvl);
		rpmh_barrier_single (aging_client_handle, req_id);

		if (gpuClockProtocol->EnableClockPowerDomain(gpuClockProtocol,
                    gpuClkPwrDomainId) != EFI_SUCCESS)
		{
			CPR_LOG_ERROR("Failed to Enable GPU ClockPowerDomain");
			CPR_ASSERT(0);
		}
	}
    return TRUE;
}

boolean cpr_image_target_set_rail_mode(cpr_domain_id railId,
        cpr_domain_info* info)
{
    if (railId == CPR_RAIL_GFX)
        return cpr_image_target_set_gfx_rail_mode(railId, info);
    else if (railId == CPR_RAIL_MM)
        return cpr_image_target_set_mm_rail_mode(railId, info);

    return FALSE;
}

void cpr_image_target_extra_init(void)
{
    return;
}

void cpr_image_target_init_rail_config(cpr_rail *rail)
{
    return;
}

uint8 cpr_image_decode_vp_id(void)
{
    
    return 0; 
}
