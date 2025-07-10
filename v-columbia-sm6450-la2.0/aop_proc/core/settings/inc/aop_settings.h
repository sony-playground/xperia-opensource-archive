/*===========================================================================
                              aop_settings.h

DESCRIPTION: Looks up properties for drivers from the devcfg image

Copyright (c) 2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/
#include "comdef.h"

//---------------------------------------------------------------------------
// Typedefs
//---------------------------------------------------------------------------
typedef struct aop_settings_handle_t *aop_settings_handle;

typedef struct
{
  uint32_t prop_id;
  uint32_t prop_val;
}property_type_t;

typedef struct
{
  uint32_t device_id;
  uint32_t num_props_for_device;
  property_type_t* props; //This points to an array of props 
}device_type_t;

typedef struct
{
   device_type_t* pDevices;
   uint32_t num_devices;
   uint32_t cookie;
}aop_devcfg_top_t;

//---------------------------------------------------------------------------
// Function Definitions
//---------------------------------------------------------------------------
void aop_settings_init(void);

/**
 * <!-- aop_settings_lkup_init -->
 *
 * @brief Populates a the top structure with target devcfg addr
 * @return none
 */
void aop_settings_lkup_init(void);

/**
 * <!-- get_settings_handle -->
 *
 * @brief Get a handle for the device.   
 * @param sDeviceName: device name 
 * @return aop settings handle
 */
aop_settings_handle get_settings_handle(char* sDeviceName);

/**
 * <!-- get_aop_settings_prop_val -->
 *
 * @brief Get the val for the property for the driver   
 * @param aop settings handle created with get_settings_handle 
 * @param property name
 * @return uint32 val of the property
 */
uint32_t get_aop_settings_prop_val(aop_settings_handle pDevice, char* sPropName);


