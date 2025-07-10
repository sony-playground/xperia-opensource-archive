
/*! \file  pm_config_pam.c
 *  
 *  \brief  File Contains the PMIC NPA PAM Data
 *  \details  This file contains the PAM data for the PMIC NPA layer.
 *  
 *    Platform: Clarence.XX.1.0
 *    Revision: NO REVISIONS (Working Set)
 *    Template Version: 
 *    $Header: //components/dev/core.boot/6.0/aravapal.core.boot.6.0.tip_dev/QcomPkg/SocPkg/Clarence/Settings/PMIC/pm_config_pam.c#1 $ 
 *    $DateTime: 2022/04/30 21:50:34 $  $Author: aravapal $
 *  
 *  &copy; Copyright Jul. 20, 2021-2022 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        INCLUDE HEADER FILES

===========================================================================*/

#include "pmapp_npa.h"
#include "pm_prm_device_defs.h"
#include "npa_remote_resource.h"

/*===========================================================================

                        MACRO DEFINITIONS

===========================================================================*/

#define PMIC_NPA_CLIENT_NODE_DISP_EXT_DP "/node/pmic/client/disp_ext_dp"
#define PMIC_NPA_CLIENT_NODE_DISP_PRIM "/node/pmic/client/disp_prim"
#define PMIC_NPA_CLIENT_NODE_DISP_PRIM_AMOLED "/node/pmic/client/disp_prim_amoled"
#define PMIC_NPA_CLIENT_NODE_EMMC_VCC "/node/pmic/client/emmc_vcc"
#define PMIC_NPA_CLIENT_NODE_EMMC_VCCQ "/node/pmic/client/emmc_vccq"
#define PMIC_NPA_CLIENT_NODE_PCIE0 "/node/pmic/client/pcie0"
#define PMIC_NPA_CLIENT_NODE_PCIE1 "/node/pmic/client/pcie1"
#define PMIC_NPA_CLIENT_NODE_SD_MMC_VDD "/node/pmic/client/sd_mmc_vdd"
#define PMIC_NPA_CLIENT_NODE_SD_MMC_VDD_PX2 "/node/pmic/client/sd_mmc_vdd_px2"
#define PMIC_NPA_CLIENT_NODE_UFS0_VCC "/node/pmic/client/ufs0_vcc"
#define PMIC_NPA_CLIENT_NODE_UFS0_VCCQ "/node/pmic/client/ufs0_vccq"
#define PMIC_NPA_CLIENT_NODE_UFS0_VCCQ2 "/node/pmic/client/ufs0_vccq2"
#define PMIC_NPA_CLIENT_NODE_UFS0_VDDA "/node/pmic/client/ufs0_vdda"
#define PMIC_NPA_CLIENT_NODE_UFS0_VDDA_CORE "/node/pmic/client/ufs0_vdda_core"
#define PMIC_NPA_CLIENT_NODE_USB_HS1 "/node/pmic/client/usb_hs1"
#define PMIC_NPA_CLIENT_NODE_USB_SS1 "/node/pmic/client/usb_ss1"
/*===========================================================================

                        VARIABLES DEFINITION

===========================================================================*/

/*************************** DISP_EXT_DP Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_ext_dp_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_ext_dp_b_ldo16 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_disp_ext_dp_rails_info [] = 
{
    { (void*)pm_pam_disp_ext_dp_b_ldo5, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_ext_dp_b_ldo16, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_disp_ext_dp [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 16 ),
};

/*************************** DISP_PRIM Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_prim_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_b_ldo16 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_disp_prim_rails_info [] = 
{
    { (void*)pm_pam_disp_prim_b_ldo5, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_b_ldo16, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_disp_prim [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 16 ),
};

/*************************** DISP_PRIM_AMOLED Client ***************************/

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_b_ldo16 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_disp_prim_amoled_e_ldo4 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 3000, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 3000, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_disp_prim_amoled_rails_info [] = 
{
    { (void*)pm_pam_disp_prim_amoled_b_ldo5, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_b_ldo16, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_disp_prim_amoled_e_ldo4, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_disp_prim_amoled [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 16 ),
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 4 ),
};

/*************************** EMMC_VCC Client ***************************/

const pm_prm_vreg_data_type
pm_pam_emmc_vcc_e_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0,  PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 2952, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 2952, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_emmc_vcc_rails_info [] = 
{
    { (void*)pm_pam_emmc_vcc_e_ldo5, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_emmc_vcc [] =
{
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 5 ),
};

/*************************** EMMC_VCCQ Client ***************************/

const pm_prm_vreg_data_type
pm_pam_emmc_vccq_b_ldo19 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_emmc_vccq_rails_info [] = 
{
    { (void*)pm_pam_emmc_vccq_b_ldo19, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_emmc_vccq [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 19 ),
};

/*************************** PCIE0 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_pcie0_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_pcie0_b_ldo16 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_pcie0_rails_info [] = 
{
    { (void*)pm_pam_pcie0_b_ldo5, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_pcie0_b_ldo16, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_pcie0 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 16 ),
};

/*************************** PCIE1 Client ***************************/

const pm_prm_pam_client_cfg_type
pm_pam_pcie1_rails_info [] = 
{
}; 

npa_node_dependency
pm_pam_deps_pcie1 [] =
{
};

/*************************** SD_MMC_VDD Client ***************************/

const pm_prm_vreg_data_type
pm_pam_sd_mmc_vdd_b_ldo24 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 2960, PM_PRM_DEV_DISABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 2960, PM_PRM_DEV_DISABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_sd_mmc_vdd_rails_info [] = 
{
    { (void*)pm_pam_sd_mmc_vdd_b_ldo24, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_sd_mmc_vdd [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 24 ),
};

/*************************** SD_MMC_VDD_PX2 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_sd_mmc_vdd_px2_b_ldo28 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_DISABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_DISABLE },  // GENERIC_ACTIVE
    { PM_PRM_VREG_MODE_LPM, 2960, PM_PRM_DEV_DISABLE },  // GENERIC_MV
    { PM_PRM_VREG_MODE_NPM, 2960, PM_PRM_DEV_DISABLE }  // GENERIC_HV
};

const pm_prm_pam_client_cfg_type
pm_pam_sd_mmc_vdd_px2_rails_info [] = 
{
    { (void*)pm_pam_sd_mmc_vdd_px2_b_ldo28, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_sd_mmc_vdd_px2 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 28 ),
};

/*************************** UFS0_VCC Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vcc_e_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 2504, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 2504, PM_PRM_DEV_ENABLE },  // GENERIC_ACTIVE
    { PM_PRM_VREG_MODE_NPM, 2952, PM_PRM_DEV_ENABLE }, // GENERIC_MV
    { PM_PRM_VREG_MODE_NPM, 2952, PM_PRM_DEV_ENABLE }  // GENERIC_HV
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vcc_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vcc_e_ldo5, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vcc [] =
{
    PM_PRM_CLIENT_VREG_DEP ( e,  ldo, 5 ),
};

/*************************** UFS0_VCCQ Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vccq_b_ldo13 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vccq_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vccq_b_ldo13, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vccq [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 13 ),
};

/*************************** UFS0_VCCQ2 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vccq2_b_ldo19 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vccq2_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vccq2_b_ldo19, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vccq2 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 19 ),
};

/*************************** UFS0_VDDA Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vdda_b_ldo16 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vdda_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vdda_b_ldo16, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vdda [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 16 ),
};

/*************************** UFS0_VDDA_CORE Client ***************************/

const pm_prm_vreg_data_type
pm_pam_ufs0_vdda_core_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_ufs0_vdda_core_rails_info [] = 
{
    { (void*)pm_pam_ufs0_vdda_core_b_ldo5, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_ufs0_vdda_core [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
};

/*************************** USB_HS1 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo16 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo23 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1800, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1800, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_hs1_b_ldo25 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 3072, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 3072, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_usb_hs1_rails_info [] = 
{
    { (void*)pm_pam_usb_hs1_b_ldo5, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_b_ldo16, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_b_ldo23, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_hs1_b_ldo25, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_usb_hs1 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 16 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 23 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 25 ),
};

/*************************** USB_SS1 Client ***************************/

const pm_prm_vreg_data_type
pm_pam_usb_ss1_b_ldo5 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 880, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 880, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_ss1_b_ldo7 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 912, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 912, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_vreg_data_type
pm_pam_usb_ss1_b_ldo16 [] =
{
     /*     mode    voltage(mV)  enable*/ 
    { PM_PRM_VREG_MODE_LPM, 0, PM_PRM_DEV_DISABLE },  // GENERIC_OFF
    { PM_PRM_VREG_MODE_LPM, 1200, PM_PRM_DEV_ENABLE },  // GENERIC_STANDBY
    { PM_PRM_VREG_MODE_NPM, 1200, PM_PRM_DEV_ENABLE }  // GENERIC_ACTIVE
};

const pm_prm_pam_client_cfg_type
pm_pam_usb_ss1_rails_info [] = 
{
    { (void*)pm_pam_usb_ss1_b_ldo5, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_ss1_b_ldo7, PM_PRM_RSRC_VRM_VREG },
    { (void*)pm_pam_usb_ss1_b_ldo16, PM_PRM_RSRC_VRM_VREG },
}; 

npa_node_dependency
pm_pam_deps_usb_ss1 [] =
{
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 5 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 7 ),
    PM_PRM_CLIENT_VREG_DEP ( b,  ldo, 16 ),
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
     PMIC_NPA_GROUP_ID_EMMC_VCC,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_emmc_vcc_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_EMMC_VCC, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_emmc_vcc,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_emmc_vcc),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_EMMC_VCCQ,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_emmc_vccq_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_EMMC_VCCQ, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_emmc_vccq,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_emmc_vccq),  // Deps Count
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
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_sd_mmc_vdd_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_SD_MMC_VDD, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_sd_mmc_vdd,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_sd_mmc_vdd),  // Deps Count
   },
   {
    PMIC_NPA_GROUP_ID_SD_MMC_VDD_PX2,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_HV,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_sd_mmc_vdd_px2_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_SD_MMC_VDD_PX2, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_sd_mmc_vdd_px2,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_sd_mmc_vdd_px2),  // Deps Count
   },
   {
     PMIC_NPA_GROUP_ID_UFS0_VCC,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_HV,   // Maximum Value
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
     PMIC_NPA_GROUP_ID_UFS0_VCCQ2,  // Resource Name
    PMIC_NPA_MODE_ID_GENERIC_ACTIVE,   // Maximum Value
    NPA_RESOURCE_SINGLE_CLIENT | NPA_RESOURCE_DRIVER_UNCONDITIONAL, // Resource Attribute
    (void*) pm_pam_ufs0_vccq2_rails_info, // Resource User Data
    PMIC_NPA_CLIENT_NODE_UFS0_VCCQ2, // Node Name
    NPA_NODE_DEFAULT,  // Node Attributes
    NULL,
    pm_pam_deps_ufs0_vccq2,  // Node Dependency
    NPA_ARRAY_SIZE(pm_pam_deps_ufs0_vccq2),  // Deps Count
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
};

uint32 num_of_pam_rsrcs [] = { sizeof(pm_prm_pam_rsrcs) / sizeof(pm_prm_node_resource_info) };

/*************************** Device Layer Resources ***************************/

pm_prm_rsrc_data_type
pm_prm_device_rsrc_data [] =
{
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 5, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_5),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 7, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_7),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 13, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_13),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 16, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_16),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 19, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_19),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 23, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_23),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 24, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_24),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 25, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_25),
    PM_PRM_DEV_RSRC_VREG ( b, ldo, 28, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_28),
    PM_PRM_DEV_RSRC_VREG ( e, ldo, 4, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_4),
    PM_PRM_DEV_RSRC_VREG ( e, ldo, 5, PM_PRM_RSRC_LDO,  PM_PRM_RPMH, PM_LDO_5),
};

pm_prm_resource_type
pm_prm_device_rsrcs [] =
{
    {
        pm_prm_device_rsrc_data, 
        sizeof(pm_prm_device_rsrc_data)/sizeof(pm_prm_rsrc_data_type), //Number of Resources
        11
    }
};

