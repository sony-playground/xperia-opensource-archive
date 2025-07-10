#include "../../RailwayLib/railway_config.h"
#include "railway.h"

/**
  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/

/* -----------------------------------------------------------------------
**                           FUNCTIONS
** ----------------------------------------------------------------------- */


typedef struct
{
    uint32 address;
    uint8 offset;
    uint8 mask;
} fuse_t;


typedef struct
{
    const uint32 *retention_table;
    const fuse_t  fuse;
} pvs_data_t;


static uint32 read_fuse_value(const fuse_t *fuse)
{
  return 0;
}


static uint32 set_sleep_voltage(int rail_id,
                                pvs_data_t *pvs_data_ptr)
{
  return 0;
}


const railway_config_data_t * const RAILWAY_CONFIG_DATA = NULL;


void railway_target_init(void)
{
}
