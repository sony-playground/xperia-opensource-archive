#ifndef __PM_PROP_IDS_H__
#define __PM_PROP_IDS_H__
/*! \file
 *
 *  \brief  pm_prop_id.h ----This file contains all the available PMIC device config property values.
 *  \details This file contains all the available PMIC DAL device config property values.
 *
 *  &copy; Copyright 2022 Qualcomm Technologies Incorporated, All Rights Reserved
 */

/*===========================================================================

                        EDIT HISTORY FOR MODULE

  This document is created by a code generator, therefore this section will
  not contain comments describing changes made to the module.


$Header: //components/dev/core.boot/6.1/dvaddem.core.boot.6.1.local_config2/QcomPkg/Library/PmicLib/framework/inc/pm_dal_prop_ids.h#2 $
$Author: dvaddem $
$DateTime: 2022/03/18 16:30:12 $
when       who     what, where, why
--------   ---     ----------------------------------------------------------
03/21/2022 dvaddem Creating a PMIC config property list
===========================================================================*/

/*===========================================================================

                     INCLUDE FILES

===========================================================================*/

typedef enum
{
    //PMIC HW peripheral specific dal properties -- starting from 1
    PM_PROP_LPG_SPECIFIC_DATA,
    PM_PROP_VIB_DATA,
    PM_PROP_PBS_CUSTOM_SEQ_DATA,
    PM_PROP_PBS_INFO,

    PM_PROP_SBL_PON_SPECIFIC_DATA,
    PM_PROP_SBL_SPECIFIC_DATA,
    PM_PROP_PRM_DEVICE_RSRCS,
    PM_PROP_PRM_PAM_RSRCS,
    PM_PROP_RPMH_DRV_ID,
    PM_PROP_RGB_SPECIFIC_DATA,

    PM_PROP_AFP_CONFIG,
    PM_PROP_HAPTICS_APP_CONFIG,
    PM_PROP_EXT_RSNS_TRIM,
    PM_PROP_QBG_TBAT_CAL_SPECIFIC_DATA,
    PM_PROP_CHARGER_CONFIG,
    PM_PROP_SLAVE_CHARGER_CONFIG,
    PM_PROP_QBG_EXT_RSNS_SCALE_LOCATION,

    //power grid specific dal properties -- starting from 101
    PM_PROP_PMIC_NUM,
    PM_PROP_SMPS_NUM,
    PM_PROP_CLK_NUM,
    PM_PROP_LDO_NUM,
    PM_PROP_VS_NUM,
    PM_PROP_BOOST_NUM,
    PM_PROP_GPIO_NUM,
    PM_PROP_PWM_NUM,
    PM_PROP_LPG_NUM,
    PM_PROP_RGB_NUM,
    PM_PROP_VIB_NUM,
    PM_PROP_WLED_NUM,
    PM_PROP_CHARGER_NUM,
    PM_PROP_IBB_NUM,
    PM_PROP_LAB_NUM,
    PM_PROP_RTC_NUM,
    PM_PROP_PAM_NODE_RSRCS,
    PM_PROP_PAM_NODE_NUM,

    PM_PROP_FG_NUM,
    PM_PROP_PBS_CLIENT_NUM,
    PM_PROP_FGB_NUM,

    PM_PROP_NUMBER_PERIPHERAL,
    PM_PROP_SPMI_PERIPH_CFG,

	PM_PROP_PERIPH_BITMAP,
    PM_PROP_HAPTICS_NUM,
    PM_PROP_COINCELL_NUM,
    PM_PROP_LONG_PWRKEY_HOLD_BOOT_TIME,
    PM_PROP_SPMI_CHANNEL_CFG,
    PM_PROP_SPMI_CHANNEL_CFG_SIZE,
    PM_PROP_PVC_PORT_CFG,
    PM_PROP_PVC_PORT_CFG_SIZE,
    PM_PROP_MGPI_PORT_CFG,
    PM_PROP_MGPI_PORT_CFG_SIZE,
    PM_PROP_VIOCTL_CFG,
    PM_PROP_VIOCTL_CFG_SIZE,
    PM_PROP_BOB_REG,
    PM_PROP_BOB_NUM,
    PM_PROP_PRM_PAM_RSRC_NUM,
    PM_PROP_PRM_PUB_PAM_RSRCS,
    PM_PROP_PM_DEVICE_INDEX_DATA,
    PM_PROP_BMD_NUM,
    PM_PROP_AB_NUM,
    PM_PROP_OLEDB_NUM,
    PM_PROP_LCDB_NUM,
    PM_PROP_SDAM_NUM,
    PM_PROP_SDAM_SUPPORTED,
    PM_PROP_LOCK_BY_BIT_DATA,
    PM_PROP_LOCK_BY_BIT_ARR_SIZE,
    PM_PROP_QGAUGE_NUM,
    PM_PROP_SDAM_ADDR_DATA,
    PM_PROP_PBS_CORE,                      
    PM_PROP_SWIRE_LUT,
    PM_PROP_EUSB_NUM,
    PM_PROP_PMBUS_INFO,
    PM_PROP_PMBUS_RSRC_INFO,
    PM_PROP_PMBUS_NUM,
    PM_PROP_OEM_PSI_WLIST_PERIPH_BITMAP,
    PM_PROP_MAX
} pm_prop_ids_type;


typedef struct
{
    uint32 prop_id;
    void   *ptr;
} pm_config_data_kvp;


#endif // __PM_PROP_IDS_H__
