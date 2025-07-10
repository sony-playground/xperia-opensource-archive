/*! \file pm_rpmh_target.c
*  \n
*  \brief This file contains PMIC functions to run sleep enter and sleep exit settings.
*  \n
*  &copy; Copyright 2013-2022 QUALCOMM Technologies Incorporated, All Rights Reserved
*/

/* =======================================================================
                             Edit History
  This section contains comments describing changes made to this file.
  Notice that changes are listed in reverse chronological order.

$Header: //components/dev/aop.ho/4.0/tmajumde.aop.ho.4.0.05202022_clarence_build_support/aop_proc/core/pmic/pm/target/netrani_pmnetraniB_pmnetraniC/src/init/pm_rpmh_target_init.c#1 $

when       who     what, where, why
--------   ---     ----------------------------------------------------------
09/10/15    kt      Initial version.
06/12/22    arua    Dynamic Modem Buck
13/03/23    arua    FR84771 MultiCard Tray
===========================================================================*/
/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

#include "CoreVerify.h"
#include "pm_comm.h"
#include "pm_target_information.h"
#include "pm_rpmh_target.h"
#include "pm_config.h"
#include "pm_config_target.h"
//#include "pm_prm_init.h"
#include "pm_rpmh.h"
#include "pm_vrm.h"
#include "pm_config_interface.h"
#include "PlatformInfoDefs.h"
#include "PlatformInfo.h"
#include "DALStdErr.h"


/*===========================================================================

                 LOCAL CONSTANT AND MACRO DEFINITIONS

===========================================================================*/
#define PMICA_INDEX  0  //PMIC index for primary pmic
#define PMICB_INDEX  1  //PMIC index for interface pmic
#define PMICE_INDEX  4  //PMIC index for interface pmic
#define PMICG_INDEX  6  //PMIC index for interface pmic

#define SMPS_BASE_ADDR         0x1400
#define SMPS_ADDR_OFFSET       0x300
#define SMPS_PERPH_TYPE_OFFSET 0x4
#define LDO_BASE_ADDR          0x4000
#define LDO_ADDR_OFFSET        0x100
#define BOB_BASE_ADDR          0xA000
#define BOB_ADDR_OFFSET        0x100
#define CLK_BASE_ADDR          0x5000
#define CLK_ADDR_OFFSET        0x100
#define MOSELLE                0x1
#define COMANCHE               0x2
#define SDCARDStatus1          0xD808
#define PX2Status1             0xDC08
#define VREG_Ready_MSK         0x80
/*===========================================================================

                        STATIC VARIABLES

===========================================================================*/

static volatile boolean g_pm_stub_pmic_type = FALSE;
boolean pm_v1_fts_allow_ret_mode = FALSE;

/*===========================================================================

                        FUNCTION DEFINITIONS

===========================================================================*/

/**
 * @name pm_rpmh_sleep_init
 *
 * @brief Initializes the sleep settings LUT.
 *
 * @param  sleep_mode: can be vdd_min/XO shutdown
 *
 * @return None.
 *
 * @sideeffects None.
 *
 * @sideeffects Sleep settings should be available in config.
 *
 */
__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_sleep_init()
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

    return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_platform_pre_init(void)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    pm_register_data_type  data = 0;
   
    DalPlatformInfoPlatformInfoType platform_info = {0};
   
    DALResult result = PlatformInfo_GetPlatformInfo(&platform_info);
   
    CORE_VERIFY(result == DAL_SUCCESS);
   
    DalPlatformInfoPlatformType platform = platform_info.platform;
   
    uint32 subtype = platform_info.subtype;
   
    uint8 wlan_mod = COMANCHE;
   
    /* WLAN MODULE
    1 - MOSELLE
    2 - COMANCHE */
   
    /* NETRANI PLATFORMS
    Platform  Subtype    Description
    ATP       0          Default (Comanche)
    IDP       0          Default (Comanche)
    IDP       0          Default (Comanche)
    IDP       1          Apache attach
    IDP       2          RCM+AMOLED (Comanche)
    IDP       3          IOT IDP with Moselle attach.
    IDP       4          IOT IDP with Hastings prime attach.
    IDP       5          RCM (Hastings prime)
    QRD       0          Default (Comanche)
 */

    if ((platform == DALPLATFORMINFO_TYPE_IDP) && ((subtype == 3) || (subtype == 4)||(subtype == 5)))
    {
        wlan_mod = MOSELLE;
    }
   
    pm_vrm_vreg_rail_info_type** rail_info = NULL;
    pm_vrm_vreg_rail_info_type* pm_rail_info = NULL;
     
    if (wlan_mod == MOSELLE)
    {
        // get local AOP address for the corresponding DDR address
        rail_info = (pm_vrm_vreg_rail_info_type**)pm_target_information_get_specific_info(PM_PROP_LDO_RAIL);
        CORE_VERIFY_PTR(rail_info);
         
        pm_rail_info = (pm_vrm_vreg_rail_info_type*)set_ddr_access((uint64_t)rail_info[PMICB_INDEX]);
        CORE_VERIFY_PTR(pm_rail_info);
        /* for moselle L11B to be disallowed */
        pm_rail_info[10].AccessAllowed = PM_ACCESS_DISALLOWED;
        /* for moselle L14B to be disallowed */
        pm_rail_info[13].AccessAllowed = PM_ACCESS_DISALLOWED;
         
        pm_rail_info = (pm_vrm_vreg_rail_info_type*)set_ddr_access((uint64_t)rail_info[PMICE_INDEX]);
        CORE_VERIFY_PTR(pm_rail_info);
        /* for moselle L7E to be disallowed */
        pm_rail_info[6].AccessAllowed = PM_ACCESS_DISALLOWED;       
   }
   
        pm_model_type pmic_model = PMIC_IS_INVALID;
        pmic_model =  pm_get_pmic_model(PMICG_INDEX);
   
   /*If Secojr is not present at index G, then single Buck Configuration*/
   if(pmic_model != PMIC_IS_SECOJR)
   {
        // get local AOP address for the corresponding DDR address
        rail_info = (pm_vrm_vreg_rail_info_type**)pm_target_information_get_specific_info(PM_PROP_SMPS_RAIL);
        CORE_VERIFY_PTR(rail_info);
         
        pm_rail_info = (pm_vrm_vreg_rail_info_type*)set_ddr_access((uint64_t)rail_info[PMICB_INDEX]);
        CORE_VERIFY_PTR(pm_rail_info);
        /* S2B to be allowed */
        pm_rail_info[1].AccessAllowed = PM_ACCESS_ALLOWED;
         
        pm_rail_info = (pm_vrm_vreg_rail_info_type*)set_ddr_access((uint64_t)rail_info[PMICG_INDEX]);
        CORE_VERIFY_PTR(pm_rail_info);
        /* S1G to be disallowed */
        pm_rail_info[0].AccessAllowed = PM_ACCESS_DISALLOWED;
   }
   
   /*If SD VDD and PX2 is OFF then default value in PSTM is 0*/
        pm_vrm_pstm_rsrc_info_type** pstm_info = NULL;
        pm_vrm_pstm_rsrc_info_type* pm_pstm_info = NULL;
        // get local AOP address for the corresponding DDR address
        pstm_info = (pm_vrm_pstm_rsrc_info_type**)pm_target_information_get_specific_info(PM_PROP_PSTM_INFO);
        CORE_VERIFY_PTR(pstm_info);
         
        pm_pstm_info = (pm_vrm_pstm_rsrc_info_type*)set_ddr_access((uint64_t)pstm_info[PMICA_INDEX]);
        CORE_VERIFY_PTR(pm_pstm_info);

        //Read SD CARD Vreg Ready
        err_flag = pm_comm_read_byte(PMICB_INDEX, SDCARDStatus1, &data, 0);
        if(!(data&VREG_Ready_MSK))
        {
        // SD CARD Default Value is 0
        pm_pstm_info[3].DefaultVal=0;
        }

        //Read PX2 Vreg Ready
        err_flag |= pm_comm_read_byte(PMICB_INDEX, PX2Status1, &data, 0);
        if(!(data&VREG_Ready_MSK))
        {
        // PX2 Default Value is 0
        pm_pstm_info[4].DefaultVal=0;
        }

   return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_platform_init(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

   return err_flag;
}

__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_platform_post_init(void)
{
   pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;

   return err_flag;
}


__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_update_rsrc_config(vrm_pmic_rsrc_data *data, uint8 *access_allowed)
{
    pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
    vrm_result result = VRM_SUCCESS;
    uint32 slave_id = 0;
    uint16 base_addr = 0;
    uint16 offset = 0;
    uint16 periph_addr = 0;
    uint8 slave_id_index = 0;

    if (g_pm_stub_pmic_type == TRUE)
    {
        data->mode_info.seq_type   = VRM_NO_PMIC_SEQ;
        data->volt_info.seq_type   = VRM_NO_PMIC_SEQ;
        data->enable_info.seq_type = VRM_NO_PMIC_SEQ;

        data->enable_info.current_state = data->enable_info.min_state;
        data->volt_info.current_state = data->volt_info.min_state;
        data->mode_info.current_state = data->mode_info.min_state;

        data->settling_en = 0;
        data->settling_err_en = 0;
        data->dep_en = 0;

        data->pstm_pbs_ready_en =0x00;
        
        if (*access_allowed == TRUE)
        {

            // Get VRM arbiter id
            if (data->periph_info.periph_type == PM_VRM_PERIPH_SMPS)
            {
                base_addr = SMPS_BASE_ADDR;
                offset = SMPS_ADDR_OFFSET;
                slave_id_index = 1;
            }
            else if (data->periph_info.periph_type == PM_VRM_PERIPH_LDO)
            {
                base_addr = LDO_BASE_ADDR;
                offset = LDO_ADDR_OFFSET;
                slave_id_index = 1;
            }
            else if (data->periph_info.periph_type == PM_VRM_PERIPH_BOB)
            {
                base_addr = BOB_BASE_ADDR;
                offset = BOB_ADDR_OFFSET;
                slave_id_index = 1;
            }
            else if (data->periph_info.periph_type == PM_VRM_PERIPH_CLK)
            {
                base_addr = CLK_BASE_ADDR;
                offset = CLK_ADDR_OFFSET;
                slave_id_index = 0;
                data->base_addr = base_addr;
            }

            if (base_addr != 0)
            {
                slave_id = (2 * data->periph_info.pmic_index) + slave_id_index;

                periph_addr = base_addr + (offset * data->periph_info.periph_index);

                err_flag = pm_comm_get_vrm_id (slave_id, periph_addr, &(data->vrm_arb_id)); 
                //CORE_VERIFY (err_flag == PM_ERR_FLAG_SUCCESS);
            }

            result = vrm_register_rsrc(data);
            CORE_VERIFY(result == VRM_SUCCESS);
        }

        *access_allowed = FALSE;
    }

    return PM_ERR_FLAG_SUCCESS;
}


__attribute__((section("rinit_code_sec_pool1")))
pm_err_flag_type pm_rpmh_pmic_detect_err_init(void)
{
    uint32 num_rsrc = 0;

    pm_target_information_init();

    vrm_init();

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, 1);
    pm_vrm_vreg_register_resources(1, PM_VRM_PERIPH_SMPS, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_SMPS_NUM, 6);
    pm_vrm_vreg_register_resources(1, PM_VRM_PERIPH_SMPS, num_rsrc);


    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_LDO_NUM, 1);
    pm_vrm_vreg_register_resources(1, PM_VRM_PERIPH_LDO, num_rsrc);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_LDO_NUM, 4);
    pm_vrm_vreg_register_resources(4, PM_VRM_PERIPH_LDO, num_rsrc);
    

    pm_vrm_clk_register_resources(0, PM_VRM_PERIPH_CLK, PM_MAX_NUM_CLKS - 1);

    num_rsrc = pm_target_information_get_periph_count_info(PM_PROP_PSTM_SEQ, 0);
    pm_vrm_pstm_register_resources(0, PM_VRM_PERIPH_PSTM, num_rsrc);

    pm_vrm_target_register_resources();

    vrm_post_init();

    pm_rpmh_init();

    //pm_prm_init();

    return PM_ERR_FLAG_SUCCESS;
}


__attribute__((section("rinit_code_sec_pool1")))
boolean pm_is_target_specific_stub_enable(void)
{
    pm_model_type pm_model = pm_get_pmic_model(PMICA_INDEX);

    if ((PMIC_IS_UNKNOWN == pm_model) || (PMIC_IS_INVALID == pm_model))
    {
        g_pm_stub_pmic_type = TRUE;
    }
    else
    {
        g_pm_stub_pmic_type = FALSE;
    }

   return g_pm_stub_pmic_type;
}
