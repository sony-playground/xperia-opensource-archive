/***********************************************************************
 * coldplug_priv_api.h
 *
 * Coldplug module.
 * Copyright (C) 2017-2021 QUALCOMM Technologies, Inc.
 *
 * Coldplug module private functions.
 ***********************************************************************/

/*===========================================================================

  EDIT HISTORY FOR MODULE

  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.

  $Header: //components/rel/core.boot/6.1.1/QcomPkg/Library/ColdplugLib/inc/coldplug_priv_api.h#1 $ $DateTime: 2022/08/18 10:15:46 $ $Author: pwbldsvc $

  when         who   what, where, why
  ----------   ---   ---------------------------------------------------------
  2021-02-04   rp    Avoid Coldplug calling EFS APIs to fit in Loader image.
  2017-05-18   rp    Create

 ===========================================================================*/

#ifndef __COLDPLUG_PRIV_API_H__
#define __COLDPLUG_PRIV_API_H__

#include "coldplug_config_i.h"
#include "coldplug_api.h"
#include "coldplug_device.h"

/*---------------------------------------------------------------------------
 * Private APIs exposed to EFS
 ---------------------------------------------------------------------------*/
const char* coldplug_search_and_get_partition_name(enum coldplug_device_type dev_type,
	int is_embedded_device, const struct coldplug_guid *guid);


/*---------------------------------------------------------------------------
 * These are internal coldplug functions created to help hotplug-clients
 * to help them move from Hotplug to Coldplug.
 *
 * All these APIs will be deprecated soon.
 ---------------------------------------------------------------------------*/
int coldplug_force_init(void);
struct coldplug_handle* coldplug_open_partition(const char *parti_name);

int coldplug_get_start_lba(struct coldplug_handle *chdl, uint64 *start_lba);

int coldplug_format(struct coldplug_handle *chdl);
int coldplug_get_internal_handle(struct coldplug_handle *chdl, void **handle);
int coldplug_release_internal_handle(struct coldplug_handle *chdl,
                                      void **handle);
int coldplug_configure_device(struct coldplug_handle *chdl, void *config_data);
enum coldplug_device_type coldplug_get_device_type(struct coldplug_handle *hd);
int coldplug_partition_get_info(struct coldplug_handle *chdl,
	struct coldplug_partition *cparti);

#endif /*  __COLDPLUG_PRIV_API_H__ */
