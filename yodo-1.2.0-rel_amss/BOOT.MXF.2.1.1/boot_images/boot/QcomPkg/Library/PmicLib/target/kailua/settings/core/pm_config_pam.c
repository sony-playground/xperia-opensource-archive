
/*! \file  pm_config_pam.c
 *  
 *  \brief  File Contains the PMIC NPA PAM Data
 *  \details  This file contains the PAM data for the PMIC NPA layer.
 *  
 *    Platform: Kailua.XX.1.0
 *    Revision: KAILUA.XX.1.0-UEFI-00001 (Working Set)
 *    Template Version: 
 *    $Header: //components/dev/core.boot/6.1/dvaddem.core.boot.6.1.config_part1/QcomPkg/SocPkg/Kailua/Settings/PMIC/pm_config_pam.c#1 $ 
 *    $DateTime: 2022/04/11 14:24:51 $  $Author: dvaddem $
 *  
 *  &copy; Copyright Jan. 27, 2022 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/

#include "pmapp_npa.h"
#include "pm_prm_device_defs.h"
#include "npa_remote_resource.h"
#include "pm_config_setting.h"

/*===========================================================================

                        MACRO DEFINITIONS

===========================================================================*/

#define PMIC_NPA_CLIENT_NODE_DISP_EXT_DP "/node/pmic/client/disp_ext_dp"
#define PMIC_NPA_CLIENT_NODE_DISP_PRIM "/node/pmic/client/disp_prim"
#define PMIC_NPA_CLIENT_NODE_DISP_PRIM_AMOLED "/node/pmic/client/disp_prim_amoled"
#define PMIC_NPA_CLIENT_NODE_PCIE0 "/node/pmic/client/pcie0"
#define PMIC_NPA_CLIENT_NODE_PCIE1 "/node/pmic/client/pcie1"
#define PMIC_NPA_CLIENT_NODE_SD_MMC_VDD "/node/pmic/client/sd_mmc_vdd"
#define PMIC_NPA_CLIENT_NODE_UFS0_VCC "/node/pmic/client/ufs0_vcc"
#define PMIC_NPA_CLIENT_NODE_UFS0_VCCQ "/node/pmic/client/ufs0_vccq"
#define PMIC_NPA_CLIENT_NODE_UFS0_VDDA "/node/pmic/client/ufs0_vdda"
#define PMIC_NPA_CLIENT_NODE_UFS0_VDDA_CORE "/node/pmic/client/ufs0_vdda_core"
#define PMIC_NPA_CLIENT_NODE_USB_HS1 "/node/pmic/client/usb_hs1"
#define PMIC_NPA_CLIENT_NODE_USB_SS1 "/node/pmic/client/usb_ss1"
#define PMIC_NPA_CLIENT_NODE_VCCA_LS_SDC "/node/pmic/client/vcca_ls_sdc"
#define PMIC_NPA_CLIENT_NODE_VCCB_LS_SDC  "/node/pmic/client/vccb_ls_sdc "

#define UPDATE_ENTRY(id, val) { .prop_id = id, .ptr = (void*)val},

/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/

/*************************** DISP_EXT_DP Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_ext_dp_e_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_ext_dp_e_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_disp_ext_dp_rails_info [] = 
{
    { (void*)pm_pam_disp_ext_dp_e_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_ext_dp_e_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_disp_ext_dp [] =
{
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 3 ),
};

/*************************** DISP_PRIM Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_prim_e_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_e_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_disp_prim_rails_info [] = 
{
    { (void*)pm_pam_disp_prim_e_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_e_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_disp_prim [] =
{
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 3 ),
};

/*************************** DISP_PRIM_AMOLED Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo11 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    /* SONY_BEGIN (Disable L11B) */
    //{ PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    //{ PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE }, // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE }, // GENERIC_OFF
    /* SONY_END (Disable L11B) */
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo12 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo13 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 3000, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 3000, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_e_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_e_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

#ifdef FEATURE_XBOOT
const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo14 [] =
{
     /*     mode    voltage(mV)  enable*/
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 3300, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 3300, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_d_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1600, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1600, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};
#endif /* FEATURE_XBOOT */

const pm_prm_pam_client_cfg_type
pm_pam_disp_prim_amoled_rails_info [] = 
{
    { (void*)pm_pam_disp_prim_amoled_b_ldo11, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_b_ldo12, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_b_ldo13, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_e_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_e_ldo3, PM_PRM_RSRC_VRM_VREG },
#ifdef FEATURE_XBOOT
    { (void*)pm_pam_disp_prim_amoled_b_ldo4, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_b_ldo14, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_d_ldo3, PM_PRM_RSRC_VRM_VREG },
#endif /* FEATURE_XBOOT */
}; 

npa_node_dependency
pm_pam_deps_disp_prim_amoled [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 11 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 12 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 13 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 3 ),
#ifdef FEATURE_XBOOT
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 4 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 14 ),
    PM_PRM_CLIENT_VREG_DEP ( d,  ldo, 3 ),
#endif /* FEATURE_XBOOT */
};

/*************************** PCIE0 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_pcie0_e_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_pcie0_e_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_pcie0_rails_info [] = 
{
    { (void*)pm_pam_pcie0_e_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_pcie0_e_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_pcie0 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 3 ),
};

/*************************** PCIE1 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_pcie1_c_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 912, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 912, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_pcie1_e_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_pcie1_e_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_pcie1_rails_info [] = 
{
    { (void*)pm_pam_pcie1_c_ldo3, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_pcie1_e_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_pcie1_e_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_pcie1 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( c,  ldo, 3 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 3 ),
};

/*************************** SD_MMC_VDD Client ***************************/

const pm_prm_vreg_data_type
pm_pam_sd_mmc_vdd_b_ldo9 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 2960, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 2960, PM_PRM_DEV_ENABLE },  // GENERIC_ACTIVE
    { PM_PRM_VREG_MODE_NPM, 2960, PM_PRM_DEV_ENABLE },  // GENERIC_MV
    { PM_PRM_VREG_MODE_NPM, 2960, PM_PRM_DEV_ENABLE }  // GENERIC_HV
};

const pm_prm_pam_client_cfg_type
pm_pam_sd_mmc_vdd_rails_info [] = 
{
    { (void*)pm_pam_sd_mmc_vdd_b_ldo9, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_sd_mmc_vdd [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 9 ),
};

/*************************** UFS0_VCC Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vcc_b_ldo17 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 2504, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 2504, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vcc_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vcc_b_ldo17, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vcc [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 17 ),
};

/*************************** UFS0_VCCQ Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vccq_g_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vccq_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vccq_g_ldo1, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vccq [] =
{
    PM_PRM_CLIENT_VREG_DEP ( g,  ldo, 1 ),
};

/*************************** UFS0_VDDA Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vdda_e_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_ufs0_vdda_e_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vdda_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vdda_e_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_ufs0_vdda_e_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vdda [] =
{
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 3 ),
};

/*************************** UFS0_VDDA_CORE Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vdda_core_d_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vdda_core_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vdda_core_d_ldo1, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vdda_core [] =
{
    PM_PRM_CLIENT_VREG_DEP ( d,  ldo, 1 ),
};

/*************************** USB_HS1 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 3104, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 3104, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo15 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_e_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_e_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_usb_hs1_rails_info [] = 
{
    { (void*)pm_pam_usb_hs1_b_ldo5, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_b_ldo15, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_e_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_e_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_usb_hs1 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 15 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 3 ),
};

/*************************** USB_SS1 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_usb_ss1_e_ldo1 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_ss1_e_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_ss1_f_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 912, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 912, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_usb_ss1_rails_info [] = 
{
    { (void*)pm_pam_usb_ss1_e_ldo1, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_ss1_e_ldo3, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_ss1_f_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_usb_ss1 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 1 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 3 ),
    PM_PRM_CLIENT_VREG_DEP ( f,  ldo, 3 ),
};

/*************************** VCCA_LS_SDC Client ***************************/

const pm_prm_vreg_data_type
pm_pam_vcca_ls_sdc_g_ldo3 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_ACTIVE
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_MV
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_HV
};

const pm_prm_pam_client_cfg_type
pm_pam_vcca_ls_sdc_rails_info [] = 
{
    { (void*)pm_pam_vcca_ls_sdc_g_ldo3, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_vcca_ls_sdc [] =
{
    PM_PRM_CLIENT_VREG_DEP ( g,  ldo, 3 ),
};

/*************************** VCCB_LS_SDC  Client ***************************/

const pm_prm_vreg_data_type
pm_pam_vccb_ls_sdc_b_ldo8 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_ACTIVE
    { PM_PRM_VREG_MODE_LPM, 2952, PM_PRM_DEV_ENABLE },  // GENERIC_MV
    { PM_PRM_VREG_MODE_NPM, 2952, PM_PRM_DEV_ENABLE }  // GENERIC_HV
};

const pm_prm_pam_client_cfg_type
pm_pam_vccb_ls_sdc_rails_info [] = 
{
    { (void*)pm_pam_vccb_ls_sdc_b_ldo8, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_vccb_ls_sdc  [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 8 ),
};

/*************************** NPA NODE RESOURCE ***************************/

const pm_prm_node_resource_info
pm_prm_pam_rsrcs [] =
{
   {
     PMIC_NPA_GROUP_ID_DISP_EXT_DP,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_disp_ext_dp_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_DISP_EXT_DP, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_disp_ext_dp,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_disp_ext_dp),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_DISP_PRIM,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_disp_prim_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_DISP_PRIM, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_disp_prim,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_disp_prim),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_DISP_PRIM_AMOLED,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_disp_prim_amoled_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_DISP_PRIM_AMOLED, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_disp_prim_amoled,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_disp_prim_amoled),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_PCIE0,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_DEFAULT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_pcie0_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_PCIE0, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_pcie0,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_pcie0),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_PCIE1,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_DEFAULT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_pcie1_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_PCIE1, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_pcie1,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_pcie1),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_SD_MMC_VDD,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_HV,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_sd_mmc_vdd_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_SD_MMC_VDD, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_sd_mmc_vdd,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_sd_mmc_vdd),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_UFS0_VCC,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_ufs0_vcc_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_UFS0_VCC, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_ufs0_vcc,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_ufs0_vcc),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_UFS0_VCCQ,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_ufs0_vccq_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_UFS0_VCCQ, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_ufs0_vccq,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_ufs0_vccq),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_UFS0_VDDA,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_ufs0_vdda_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_UFS0_VDDA, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_ufs0_vdda,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_ufs0_vdda),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_UFS0_VDDA_CORE,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_ufs0_vdda_core_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_UFS0_VDDA_CORE, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_ufs0_vdda_core,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_ufs0_vdda_core),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_USB_HS1,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_DEFAULT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_usb_hs1_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_USB_HS1, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_usb_hs1,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_usb_hs1),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_USB_SS1,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_DEFAULT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_usb_ss1_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_USB_SS1, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_usb_ss1,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_usb_ss1),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_VCCA_LS_SDC,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_HV,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_vcca_ls_sdc_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_VCCA_LS_SDC, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_vcca_ls_sdc,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_vcca_ls_sdc),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_VCCB_LS_SDC ,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_HV,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_vccb_ls_sdc_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_VCCB_LS_SDC , // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_vccb_ls_sdc ,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_vccb_ls_sdc ),  // Deps Count
   },
};

uint32 num_of_pam_rsrcs [] = { sizeof(pm_prm_pam_rsrcs) / sizeof(pm_prm_node_resource_info) };


/*************************** Device Layer Resources ***************************/

pm_prm_rsrc_data_type
pm_prm_device_rsrc_data [] =
{
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 5, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_5),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 8, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_8),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 9, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_9),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 11, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_11),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 12, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_12),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 13, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_13),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 15, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_15),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 17, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_17),
    PM_PRM_DEV_RSRC_VREG ( d, ldo, 1, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_1),
    PM_PRM_DEV_RSRC_VREG ( g, ldo, 1, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_1),
    PM_PRM_DEV_RSRC_VREG ( g, ldo, 3, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_3),
    PM_PRM_DEV_RSRC_VREG ( c, ldo, 3, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_3),
    PM_PRM_DEV_RSRC_VREG ( e, ldo, 1, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_1),
    PM_PRM_DEV_RSRC_VREG ( e, ldo, 3, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_3),
    PM_PRM_DEV_RSRC_VREG ( f, ldo, 3, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_3),
#ifdef FEATURE_XBOOT
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 4, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_4),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 14, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_14),
    PM_PRM_DEV_RSRC_VREG ( d, ldo, 3, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_3),
#endif /* FEATURE_XBOOT */
};

pm_prm_resource_type
pm_prm_device_rsrcs [] =
{
    {
     pm_prm_device_rsrc_data, 
     sizeof(pm_prm_device_rsrc_data)/sizeof(pm_prm_rsrc_data_type), //Number of Resources
#ifdef FEATURE_XBOOT
        18
#else /* !FEATURE_XBOOT */
        15
#endif /* !FEATURE_XBOOT */

    }
};

pm_config_data_kvp pm_pam_config_data[] = 
{
    UPDATE_ENTRY( PM_PROP_PRM_PAM_RSRCS, pm_prm_pam_rsrcs)
    UPDATE_ENTRY( PM_PROP_PRM_PAM_RSRC_NUM, num_of_pam_rsrcs)
    UPDATE_ENTRY( PM_PROP_PRM_DEVICE_RSRCS, pm_prm_device_rsrcs)
};

pm_err_flag_type
pm_config_pam_data(  pm_config_data_kvp **pam_config_data, 
                            uint32 *pam_config_data_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  if ((pam_config_data == NULL) || (pam_config_data_size == NULL))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    *pam_config_data = pm_pam_config_data;
    *pam_config_data_size = ((sizeof(pm_pam_config_data))/(sizeof(pm_pam_config_data[0])));
  }

  return err_flag;
}
