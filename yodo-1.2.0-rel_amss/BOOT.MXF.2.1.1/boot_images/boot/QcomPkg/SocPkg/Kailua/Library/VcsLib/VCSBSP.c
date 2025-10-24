/*
==============================================================================

FILE:         VCSBSP.c

DESCRIPTION:
  This file contains VCS bsp data for DAL based driver.

==============================================================================

                             Edit History

$Header: //components/rel/core.boot/6.1.1/QcomPkg/SocPkg/Kailua/Library/VcsLib/VCSBSP.c#1 $

==============================================================================
            Copyright (c) 2021 QUALCOMM Technologies Incorporated.  All Rights Reserved.
                    All Rights Reserved.
                  QUALCOMM Proprietary/GTDR
==============================================================================
*/

/*=========================================================================
      Include Files
==========================================================================*/

#include "Drivers/VcsDxe/VCSBSP.h"

// Components used in this image
#include "Drivers/VcsDxe/RailImpls/VCSRPMhRailImpl.h"


/*=========================================================================
      Externs
==========================================================================*/


/*=========================================================================
      Macros
==========================================================================*/


/*=========================================================================
      Data Declarations
==========================================================================*/

static VCSRPMhHandleType VCS_RPMh_Handle_Hlos =
{
  .eDRVId = RSC_DRV_HLOS,
};

/*
 * VCSRPMhRailImpl_MXA
 */
static VCSRPMhRailImplType VCSRPMhRailImpl_MXA =
{
  .szName = "mx.lvl",
  .pRPMh  = &VCS_RPMh_Handle_Hlos,
};


/*
 * VCSRPMhRailImpl_MXC
 */
static VCSRPMhRailImplType VCSRPMhRailImpl_MXC =
{
  .szName = "mxc.lvl",
  .pRPMh  = &VCS_RPMh_Handle_Hlos,
};


/*
 * VCSRPMhRailImpl_CX
 */
static VCSRPMhRailImplType VCSRPMhRailImpl_CX =
{
  .szName = "cx.lvl",
  .pRPMh  = &VCS_RPMh_Handle_Hlos,
};

/*
 * VCSRPMhRailImpl_MMCX
 */
static VCSRPMhRailImplType VCSRPMhRailImpl_MMCX =
{
  .szName = "mmcx.lvl",
  .pRPMh  = &VCS_RPMh_Handle_Hlos,
};


/*
 * VCSRPMhRailImpl_GFX
 */
static VCSRPMhRailImplType VCSRPMhRailImpl_GFX =
{
  .szName = "gfx.lvl",
  .pRPMh  = &VCS_RPMh_Handle_Hlos,
};

/*
 * VCSRPMhRailImpl_LPIMX
 */
static VCSRPMhRailImplType VCSRPMhRailImpl_LPIMX =
{
  .szName = "lmx.lvl",
  .pRPMh  = &VCS_RPMh_Handle_Hlos,
};


/*
 * VCSRPMhRailImpl_LPICX
 */
static VCSRPMhRailImplType VCSRPMhRailImpl_LPICX =
{
  .szName = "lcx.lvl",
  .pRPMh  = &VCS_RPMh_Handle_Hlos,
};


/*
 * VCSRPMhRailImpl_NSP
 */
static VCSRPMhRailImplType VCSRPMhRailImpl_NSP =
{
  .szName = "nsp.lvl",
  .pRPMh  = &VCS_RPMh_Handle_Hlos,
};


static const char *VCS_Aliases_MxA[] =
{
  "/vcs/vdd_mx",
};

static const char *VCS_Aliases_LPIMX[] =
{
  "/vcs/vdd_ssc_mx",
};


static const char *VCS_Aliases_LPICX[] =
{
  "/vcs/vdd_ssc_int",
};

/*
 * aRails
 *
 * Set of rail instances.
 */
static VCSRailNodeType aRails[] =
{
  /*-----------------------------------------------------------------------*/
  /* MXA                                                                   */
  /*-----------------------------------------------------------------------*/
  {
    VCS_DEF_RAIL_NAME("/vcs/vdd_mxa"),
    VCS_DEF_ALIASES(VCS_Aliases_MxA),
    /* no dependency */
    VCS_DEF_RAIL_ATTRIBUTES(NPA_RESOURCE_DEFAULT),
    VCS_DEF_RAIL_IMPL(RPMh, &VCSRPMhRailImpl_MXA),
  },

  /*-----------------------------------------------------------------------*/
  /* MXC                                                                   */
  /*-----------------------------------------------------------------------*/
  {
    VCS_DEF_RAIL_NAME("/vcs/vdd_mxc"),
    /* no dependency */
    VCS_DEF_RAIL_ATTRIBUTES(NPA_RESOURCE_DEFAULT),
    VCS_DEF_RAIL_IMPL(RPMh, &VCSRPMhRailImpl_MXC),
  },

  /*-----------------------------------------------------------------------*/
  /* CX                                                                    */
  /*-----------------------------------------------------------------------*/
  {
    VCS_DEF_RAIL_NAME("/vcs/vdd_cx"),
    /* no dependency */
    VCS_DEF_RAIL_ATTRIBUTES(NPA_RESOURCE_DEFAULT),
    VCS_DEF_RAIL_IMPL(RPMh, &VCSRPMhRailImpl_CX),
  },
  
  /*-----------------------------------------------------------------------*/
  /* MMCX                                                                  */
  /*-----------------------------------------------------------------------*/
  {
    VCS_DEF_RAIL_NAME("/vcs/vdd_mm"),
    /* no dependency */
    VCS_DEF_RAIL_ATTRIBUTES(NPA_RESOURCE_DEFAULT),
    VCS_DEF_RAIL_IMPL(RPMh, &VCSRPMhRailImpl_MMCX),
  },

  /*-----------------------------------------------------------------------*/
  /* GFX                                                                   */
  /*-----------------------------------------------------------------------*/
  {
    VCS_DEF_RAIL_NAME("/vcs/vdd_gx"),
    /* no dependency */
    VCS_DEF_RAIL_ATTRIBUTES(NPA_RESOURCE_DEFAULT),
    VCS_DEF_RAIL_IMPL(RPMh, &VCSRPMhRailImpl_GFX),
  },
  
  /*-----------------------------------------------------------------------*/
  /* LPI_MX                                                                */
  /*-----------------------------------------------------------------------*/
  {
    VCS_DEF_RAIL_NAME("/vcs/vdd_lpi_mx"),
    VCS_DEF_ALIASES(VCS_Aliases_LPIMX),
    /* no dependency */
    VCS_DEF_RAIL_ATTRIBUTES(NPA_RESOURCE_DEFAULT),
    VCS_DEF_RAIL_IMPL(RPMh, &VCSRPMhRailImpl_LPIMX),
  },

  /*-----------------------------------------------------------------------*/
  /* LPI_CX                                                                */
  /*-----------------------------------------------------------------------*/
  {
    VCS_DEF_RAIL_NAME("/vcs/vdd_lpi_cx"),
    VCS_DEF_ALIASES(VCS_Aliases_LPICX),
    /* no dependency */
    VCS_DEF_RAIL_ATTRIBUTES(NPA_RESOURCE_DEFAULT),
    VCS_DEF_RAIL_IMPL(RPMh, &VCSRPMhRailImpl_LPICX),
  },

  /*-----------------------------------------------------------------------*/
  /* NSP                                                                   */
  /*-----------------------------------------------------------------------*/
  {
    VCS_DEF_RAIL_NAME("/vcs/vdd_nsp"),
    /* no dependency */
    VCS_DEF_RAIL_ATTRIBUTES(NPA_RESOURCE_DEFAULT),
    VCS_DEF_RAIL_IMPL(RPMh, &VCSRPMhRailImpl_NSP),
  },
};


/*
 * VCS Log Default Configuration.
 */
const VCSLogType VCS_LogDefaultConfig[] =
{
  {
    /* .nLogSize = */ 4096,
  }
};


static VCSBaseType aBases[] =
{
  /* empty */
};


/*
 *  VCSBSP
 *
 *  List and length of Rail and LDO configurations.
 */
const VCSBSPType VCSBSP =
{
  VCS_DEF_ARR_FIELD(Bases, aBases),
  VCS_DEF_ARR_FIELD(Rails, aRails),
};
