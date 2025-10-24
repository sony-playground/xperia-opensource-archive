/*===========================================================================

  Copyright (c) 2012,2016-2019, 2021 Qualcomm Technologies, Incorporated.
  All Rights Reserved.
  QUALCOMM Proprietary and Confidential.

  ===========================================================================*/

#include <stdlib.h>
#include <string.h>

#include "railway.h"
#include "railway_internal.h"
#include "railway_config.h"

#include "DALSys.h"
#include "CoreVerify.h"

railway_internals_t railway;
int mx_rail_id     = RAIL_NOT_SUPPORTED_BY_RAILWAY;
int mxc_rail_id    = RAIL_NOT_SUPPORTED_BY_RAILWAY;
int cx_rail_id     = RAIL_NOT_SUPPORTED_BY_RAILWAY;
int ebi_rail_id    = RAIL_NOT_SUPPORTED_BY_RAILWAY;
int ssc_cx_rail_id = RAIL_NOT_SUPPORTED_BY_RAILWAY;

int railway_get_rail_id(const char *name)
{
    int id = rail_id(name);
    CORE_VERIFY(RAIL_NOT_SUPPORTED_BY_RAILWAY!=id);
    return id;
}

void railway_init_voter(int rail_id, railway_voter_id voter_id,
        railway_corner corner)
{
    railway_voter_t voter = railway_create_voter(rail_id, voter_id);
    railway_corner_vote(voter, corner);
}

void railway_init(void)
{
	get_railway_cfg();
	CORE_VERIFY(RAILWAY_CONFIG_DATA!=NULL);
    uint32 num_rails = RAILWAY_CONFIG_DATA->num_rails;
    uint32 rail_state_size = num_rails * sizeof(railway_rail_state_t);

    DALResult dalResult =
        DALSYS_Malloc(rail_state_size, (void**)&railway.rail_state);
    CORE_VERIFY_PTR(railway.rail_state);
    CORE_VERIFY(dalResult==DAL_SUCCESS);

    memset(railway.rail_state, 0, rail_state_size);
    railway_transitioner_init(); // initialize all rails

    /* 
     * railway_target_init() should be called after railway_transitioner_init
     * since railway.rail_state[] are initialized with default values.
     */
    railway_target_init();
}
