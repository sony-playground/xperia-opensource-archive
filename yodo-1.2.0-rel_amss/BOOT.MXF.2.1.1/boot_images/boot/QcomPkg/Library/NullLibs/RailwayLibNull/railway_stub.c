/**
  Copyright (c) 2021, Qualcomm Technologies, Inc. All rights reserved.
**/

/*=============================================================================
                              EDIT HISTORY


 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 08/16/21   ck      Added edit history and copyright

=============================================================================*/


#include "railway.h"
#include "comdef.h"

void railway_init(void)
{
}

int rail_id(const char* rail)
{
    return 0;
}

void railway_transition_rails(void)
{}

railway_voter_t railway_create_voter(int rail, int id)
{
    return NULL;
}

void railway_corner_vote(railway_voter_t voter, railway_corner corner)
{
}

void railway_set_corner_voltage(int rail, railway_corner corner, uint32 microvolts)
{
}

uint32 railway_get_corner_voltage(int rail, railway_corner corner)
{
    return 0;
}

void railway_get_current_settings(int rail, railway_settings* settings)
{
}

void aop_mini_dump_init(void)
{
}
