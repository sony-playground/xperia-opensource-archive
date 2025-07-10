/*===========================================================================
                              aop_settings.c

DESCRIPTION: Looks up properties for drivers from the devcfg image

Copyright (c) 2020 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.
QUALCOMM Proprietary.  Export of this technology or software is regulated
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/
//---------------------------------------------------------------------------
// Include Files
//---------------------------------------------------------------------------
#include "aop_settings.h"
#include "aop_settings_target.h"
#include "CoreVerify.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
//---------------------------------------------------------------------------
// Typedefs
//---------------------------------------------------------------------------
struct aop_settings_handle_t{
  uint32_t device_id;
};

struct device_list{
  uint32_t id;
  struct device_list* next;
};

typedef struct{
  aop_devcfg_top_t* devcfg_data;

}settings_lookup_t;

//---------------------------------------------------------------------------
// Static Variable Definitions

//---------------------------------------------------------------------------
settings_lookup_t settings;
//---------------------------------------------------------------------------
// Function Definitions
//---------------------------------------------------------------------------
#if 0
volatile uint32_t query_data = 0x0;
void test_aop_settings_query(void)
{
  aop_settings_handle ash = get_settings_handle("test_driver");
  CORE_VERIFY(ash != NULL);
  query_data = get_aop_settings_prop_val(ash, "test_struct");
}
#endif

/**
 * <!-- crc32 -->
 *
 * @brief generates crc32 
 * @param crc: prev crc (defaults to 0) 
 * @param buf: unsigned char buffer 
 * @param len: length of the char buffer 
 *  
 * @return crc32 
 *
 * @return none
 */
static uint32_t crc32(uint32_t crc, unsigned char* buf, size_t len)
{
  crc = ~crc;
  while (len--)
  {
    crc ^= *buf++;
    for (int k = 0; k < 8; k++)
    {
      crc = crc & 1 ? ((crc >> 1) ^ 0xEDB88320) : (crc >> 1);
    }
  }
  return ~crc;
}

/**
 * <!-- aop_settings_lkup_init -->
 *
 * @brief Populates a the top structure with target devcfg addr
 * @return none
 */
void aop_settings_lkup_init(void)
{
  settings.devcfg_data = (aop_devcfg_top_t*)(AOP_DEVCFG_DATA_START);
  if (settings.devcfg_data->cookie != 0xA0DA7A)
  {
    //mark devcfg_data invalid
    settings.devcfg_data = 0x0;
  }
#if 0
  test_aop_settings_query();
#endif
}

/**
 * <!-- get_settings_handle -->
 *
 * @brief Get a handle for the device.   
 * @param sDeviceName: device name 
 * @return aop settings handle
 */
aop_settings_handle get_settings_handle(char* sDeviceName)
{
  CORE_VERIFY(sDeviceName);
  aop_settings_handle client_handle = malloc(sizeof(aop_settings_handle));
  CORE_VERIFY(client_handle);
  client_handle->device_id = crc32(0, (unsigned char*)sDeviceName, strlen(sDeviceName));
  return client_handle;
}

/**
 * <!-- get_aop_settings_prop_val -->
 *
 * @brief Get the val for the property for the driver   
 * @param aop settings handle created with get_settings_handle 
 * @param property name
 * @return uint32 val of the property
 */
uint32_t get_aop_settings_prop_val(aop_settings_handle pDevice, char* sPropName)
{
  CORE_VERIFY(pDevice);
  CORE_VERIFY(sPropName);
  uint32_t device_id = pDevice->device_id;
  uint32_t prop_id = crc32(0, (unsigned char*)sPropName, strlen(sPropName));
  for (int dev_indx = 0; dev_indx < settings.devcfg_data->num_devices; dev_indx++)
  {
    if(settings.devcfg_data->pDevices[dev_indx].device_id == device_id)
    {//found the device
      for (int prop_indx = 0; prop_indx < settings.devcfg_data->pDevices[dev_indx].num_props_for_device; prop_indx++)
      { property_type_t prop = settings.devcfg_data->pDevices[dev_indx].props[prop_indx];
        if (prop_id == prop.prop_id)
        {
          return prop.prop_val;
        }
      }
      
    }
  }
  return 0;
}
