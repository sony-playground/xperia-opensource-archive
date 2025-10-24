/*! \file
*  \n
*  \brief  pm_pvc_config.c
*  \n
*  \n This file contains pmic configuration data specific for SPMI Controller's
      Peripheral for SDM845 device..
*  \n
*  \n &copy; Copyright 2015-2020, 2022 Qualcomm Technologies Incorporated, All Rights Reserved
*/
/* =======================================================================
Edit History
This section contains comments describing changes made to this file.
Notice that changes are listed in reverse chronological order.

$Header: //components/dev/core.boot/6.1/dvaddem.core.boot.6.1.config_part1/QcomPkg/SocPkg/Kailua/Settings/PMIC/pm_pvc_config.c#1 $

when       who    what, where, why
--------   ---    ----------------------------------------------------------
03/22/18   aab    Updated MGPI2 Negative edge data to: 0xC0
12/19/17   aab    Updated MGPI configuration for SDM855 Target 
02/01/17   aab    Supported SDM845 target.  Added SPMI,PVC, MGPI and VIOCTL configurations
08/25/15   vtw    Created.
========================================================================== */

/*-------------------------------------------------------------------------
* Include Files
* ----------------------------------------------------------------------*/

#include "SpmiCfg.h"
#include "pm_config_setting.h"

/*-------------------------------------------------------------------------
* Preprocessor Definitions and Constants
* ----------------------------------------------------------------------*/

/* Converts a PVC port index to an overall PMIC Arbiter port index */
#define PVC_PORT_TO_PMIC_ARB_PORT(p) (p+1)

/*   Port assignment in Kona   */
#define APPS0_PORT      0   /* APPS Port 0  */
#define APPS1_PORT      1   /* APPS Port 1  */
#define MGPI_PVC_PORT   3   /* MGPI PVC Port 3*/

#define UPDATE_ENTRY(id, val) { .prop_id = id, .ptr = (void*)val},

/*-------------------------------------------------------------------------
* Static Variable Definitions
* ----------------------------------------------------------------------*/

/*
 * pm_pvc_apps0_addr
 *
 * PVC port addr for APPS0 Gold cluster.
 */
SpmiCfg_Ppid pm_pvc_apps0_addr[] =
{
  {0x2, 0xA440}, /* S4C_CTRL_VSET_LB */
  {0x2, 0xA441}, /* S4C_CTRL_VSET_UB */
  {0x2, 0xA445}, /* S4C_CTRL_MODE_CTL */
  {0x2, 0xA446}  /* S4C_CTRL_EN_CTL */
};

const SpmiCfg_PvcPortCfg pm_pvc_apps0_cfg = {APPS0_PORT, SPMI_ACCESS_PRIORITY_LOW, pm_pvc_apps0_addr, sizeof(pm_pvc_apps0_addr)/sizeof(SpmiCfg_Ppid)};

/*
 * pm_pvc_apps1_addr
 *
 * PVC port addr for APPS1 Silver cluster block.
 */
SpmiCfg_Ppid pm_pvc_apps1_addr[] =
{
  {0x2, 0xAA40}, /* S1B_CTRL_VSET_LB */
  {0x2, 0xAA41}, /* S1B_CTRL_VSET_UB */
  {0x2, 0xAA45}, /* S1B_CTRL_MODE_CTL */
  {0x2, 0xAA46}  /* S1B_CTRL_EN_CTL */
};

const SpmiCfg_PvcPortCfg pm_pvc_apps1_cfg = {APPS1_PORT, SPMI_ACCESS_PRIORITY_LOW, pm_pvc_apps1_addr, sizeof(pm_pvc_apps1_addr)/sizeof(SpmiCfg_Ppid)};

/*
 * pm_pvc_mgpi_addr
 *
 * PVC port addr for MGPI block.
 */
SpmiCfg_Ppid pm_pvc_mgpi_addr[] =
{
  {0x1, 0xC746}, /* MGPI0, UICC1, L7B */
  {0x0, 0x5A49}, /* MGPI1, NFC, CLK7 */
  {0x0, 0x0},    /* MGPI2, Spare */
  {0x0, 0x0},    /* MGPI3, Spare MGPI, used by WLAN to be configured by MGPI module */
  {0x1, 0xC946}, /* MGPI4, SD card, default disabled unless for QRD L9B*/
  {0x1, 0xC646}, /* MGPI5, UICC0, L6B */
  {0x3, 0xC244}, /* MGPI6, AOP PDC TRIGGER, L2D RM/NPM control*/
  {0x0, 0x0}     /* MGPI7, vioctl[1], Law communication */
};

const SpmiCfg_PvcPortCfg pm_pvc_mgpi_cfg = {MGPI_PVC_PORT, SPMI_ACCESS_PRIORITY_LOW, pm_pvc_mgpi_addr, sizeof(pm_pvc_mgpi_addr)/sizeof(SpmiCfg_Ppid)};

/*
 * pm_arb_pvc_cfg
 *
 * PMIC Arbiter PVC ports config.
 */
const SpmiCfg_PvcPortCfg* pm_arb_pvc_port_cfg[] = {&pm_pvc_apps0_cfg, &pm_pvc_apps1_cfg, &pm_pvc_mgpi_cfg};

uint32 pm_arb_pvc_port_cfg_size[] = {sizeof(pm_arb_pvc_port_cfg) / sizeof(SpmiCfg_PvcPortCfg*)};



/*
 * pm_mgpi_port_cfg
 *
 * PMIC MGPI ports config.
 */
 //UICC1
SpmiBusCfg_MgpiPortCfg pm_mgpi_port_0_cfg = 
{
  0,                 /* MGPI Port id */
  MGPI_PVC_PORT,     /* PVC Port id */
  FALSE,             /* Positive edge enable */
  0,                 /* Positive edge PVC port address index */
  0,                 /* Positive edge data */
  FALSE,             /* Negative edge enable */
  0,                 /* Negative edge PVC port address index */
  0,                 /* Negative edge data */
  TRUE,              /* MUX Sel Valid Flag*/
  0,                 /* MUX Sel Value */
};

//NFC: Kailua V1 has issue and MGPI is not tied correctly on V1 pmics ECO will route gpio31 to mux input 4 in V2 MSMs 
SpmiBusCfg_MgpiPortCfg pm_mgpi_port_1_cfg = 
{
  1,                 /* MGPI Port id */
  MGPI_PVC_PORT,     /* PVC Port id */
  TRUE,              /* Positive edge enable */
  1,                 /* Positive edge PVC port address index */
  0x80,              /* Positive edge data */
  TRUE,              /* Negative edge enable */
  1,                 /* Negative edge PVC port address index */
  0x0,               /* Negative edge data */
  TRUE,              /* MUX Sel Valid Flag*/
  4                  /* MUX Sel Value */
};


//Spare
SpmiBusCfg_MgpiPortCfg pm_mgpi_port_2_cfg = 
{
  2,                 /* MGPI Port id */
  MGPI_PVC_PORT,     /* PVC Port id */
  FALSE,             /* Positive edge enable */
  2,                 /* Positive edge PVC port address index */
  0x0,               /* Positive edge data */
  FALSE,             /* Negative edge enable */
  2,                 /* Negative edge PVC port address index */
  0,                 /* Negative edge data */
  FALSE,             /* MUX Sel Valid Flag*/
  0                  /* MUX Sel Value */
};

//Spare
SpmiBusCfg_MgpiPortCfg pm_mgpi_port_3_cfg = 
{
  3,                 /* MGPI Port id */
  MGPI_PVC_PORT,     /* PVC Port id */
  FALSE,             /* Positive edge enable */
  3,                 /* Positive edge PVC port address index */
  0x0,               /* Positive edge data */
  FALSE,             /* Negative edge enable */
  3,                 /* Negative edge PVC port address index */
  0x0,               /* Negative edge data */
  FALSE,             /* MUX Sel Valid Flag*/
  0                  /* MUX Sel Value */
};


//SD Card Removal
SpmiBusCfg_MgpiPortCfg pm_mgpi_port_4_cfg = 
{
  4,                 /* MGPI Port id */
  MGPI_PVC_PORT,     /* PVC Port id */
  FALSE,             /* Positive edge enable */
  4,                 /* Positive edge PVC port address index */
  0,                 /* Positive edge data */
  FALSE,             /* Negative edge enable */
  4,                 /* Negative edge PVC port address index */
  0,                 /* Negative edge data */
  TRUE,              /* MUX Sel Valid Flag*/
  0                  /* MUX Sel Value */
};

//UICC0
SpmiBusCfg_MgpiPortCfg pm_mgpi_port_5_cfg = 
{
  5,                 /* MGPI Port id */
  MGPI_PVC_PORT,     /* PVC Port id */
  FALSE,             /* Positive edge enable */
  5,                 /* Positive edge PVC port address index */
  0,                 /* Positive edge data */
  FALSE,             /* Negative edge enable */
  5,                 /* Negative edge PVC port address index */
  0,                 /* Negative edge data */
  FALSE,             /* MUX Sel Valid Flag*/
  0                  /* MUX Sel Value */
};

//AOP PDC Trigger
SpmiBusCfg_MgpiPortCfg pm_mgpi_port_6_cfg = 
{
  6,                 /* MGPI Port id */
  MGPI_PVC_PORT,     /* PVC Port id */
  TRUE,              /* Positive edge enable */
  6,                 /* Positive edge PVC port address index */
  3,                 /* Positive edge data */
  TRUE,              /* Negative edge enable */
  6,                 /* Negative edge PVC port address index */
  7,                 /* Negative edge data */
  TRUE,              /* MUX Sel Valid Flag*/
  0                  /* MUX Sel Value */
};

//EUD
SpmiBusCfg_MgpiPortCfg pm_mgpi_port_7_cfg = 
{
  7,                 /* MGPI Port id */
  MGPI_PVC_PORT,     /* PVC Port id */
  FALSE,             /* Positive edge enable */
  7,                 /* Positive edge PVC port address index */
  1,                 /* Positive edge data */
  FALSE,             /* Negative edge enable */
  7,                 /* Negative edge PVC port address index */
  0,                 /* Negative edge data */
  FALSE,             /* MUX Sel Valid Flag*/
  0                  /* MUX Sel Value */
};

SpmiBusCfg_MgpiPortCfg* pm_mgpi_port_cfg[] = {&pm_mgpi_port_0_cfg, &pm_mgpi_port_1_cfg, &pm_mgpi_port_2_cfg, &pm_mgpi_port_3_cfg, &pm_mgpi_port_4_cfg, &pm_mgpi_port_5_cfg, &pm_mgpi_port_6_cfg, &pm_mgpi_port_7_cfg};

uint32 pm_mgpi_port_cfg_size[] = {sizeof(pm_mgpi_port_cfg) / sizeof(SpmiBusCfg_MgpiPortCfg*)};

/*
 * pm_vioctl_cfg
 *
 * PMIC VIOCTL config.
 */
const SpmiBusCfg_VioctlCfg pm_vioctl_cfg0 =
{
   0,                    /**< SPMI BUS ID*/
   4,                    /**< VIOCTL port ID*/
   0x1,                  /**< Self clear enable*/
   TRUE,                 /**< Positive edge enable */
   0x02,                 /**< Positive Edge Slave id*/
   0xA4,                 /**< Positive Edge periph id*/
   0x02,                 /* Positive edge periph interrupt mask */
   FALSE,                /* Negative edge enable */
   0x0,                  /**< Negative Edge Slave id*/
   0x0,                  /**< Negative edge periph ID*/
   0,                    /* Negative edge periph interrupt mask */
};

const SpmiBusCfg_VioctlCfg pm_vioctl_cfg1 =
{
   0,                    /**< SPMI BUS ID*/
   5,                    /**< VIOCTL port ID*/
   0x01,                 /**< Self clear enable*/
   TRUE,                 /* Positive edge enable */
   0x02,                 /**< Positive Edge Slave id*/
   0xAA,                 /**< Positive Edge periph id*/
   0x02,                 /* Positive edge periph interrupt mask */
   FALSE,                /* Negative edge enable */
   0x0,                  /**< Negative Edge Slave id*/   
   0x0,                  /**< Negative edge periph ID*/
   0,                    /* Negative edge periph interrupt mask */
};

const SpmiBusCfg_VioctlCfg* pm_vioctl_cfg[] = {&pm_vioctl_cfg0, &pm_vioctl_cfg1};

uint32 pm_vioctl_cfg_size[] = {sizeof(pm_vioctl_cfg) / sizeof(SpmiBusCfg_VioctlCfg*)};


pm_config_data_kvp pm_pvc_mgpi_config_data[] =
{
  UPDATE_ENTRY( PM_PROP_PVC_PORT_CFG, pm_arb_pvc_port_cfg)
  UPDATE_ENTRY( PM_PROP_MGPI_PORT_CFG, pm_mgpi_port_cfg)
  UPDATE_ENTRY( PM_PROP_PVC_PORT_CFG_SIZE, pm_arb_pvc_port_cfg_size)
  UPDATE_ENTRY( PM_PROP_MGPI_PORT_CFG_SIZE, pm_mgpi_port_cfg_size)
  UPDATE_ENTRY( PM_PROP_VIOCTL_CFG, pm_vioctl_cfg)
  UPDATE_ENTRY( PM_PROP_VIOCTL_CFG_SIZE, pm_vioctl_cfg_size)
};

pm_err_flag_type
pm_config_arb_data(  pm_config_data_kvp **arb_config_data, 
                            uint32 *arb_config_data_size)
{
  pm_err_flag_type err_flag = PM_ERR_FLAG_SUCCESS;
  
  if ((arb_config_data == NULL) || (arb_config_data_size == NULL))
  {
    err_flag = PM_ERR_FLAG_INVALID_PARAMETER;
  }
  else
  {
    *arb_config_data = pm_pvc_mgpi_config_data;
    *arb_config_data_size = ((sizeof(pm_pvc_mgpi_config_data))/(sizeof(pm_pvc_mgpi_config_data[0])));
  }

  return err_flag;
}
