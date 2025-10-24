#ifndef __PWR_UTILS_LVL_TARGET_H__
#define __PWR_UTILS_LVL_TARGET_H__

/*===========================================================================
                             pwr_utils_lvl_target.h

DESCRIPTION:
  This file implements the APIs to conver SW corner/levels (vlvl) to HW
  corner/level (hlvl) and vice versa.

Copyright (c) 2018 QUALCOMM Technologies, Inc. (QTI). All Rights Reserved.  
QUALCOMM Proprietary.  Export of this technology or software is regulated 
by the U.S. Government. Diversion contrary to U.S. law prohibited.
===========================================================================*/

#include <stddef.h>


/* Internal structure type containing supported level mapping for different
 * rail resources. */
typedef struct pwr_utils_lvl_res_s
{
  const char *name;          /* resource name e.g. cx.lvl, mx.lvl, etc */
  uint16 *vlvls;             /* Supported vlvls with hlvl denoted by index */
  size_t count;              /* vlvl count */
} pwr_utils_lvl_res_t;

typedef struct pwr_utils_mol_res_s
{
  const char *name;          /* resource name e.g. cx.lvl, mx.lvl, etc */
  uint16 mol;               /* MInimum operating level */
} pwr_utils_mol_res_t;

/* Target specific rail resources */
static pwr_utils_lvl_res_t res_target[] = 
{
  {"cx.lvl",  NULL, 0},
  {"mx.lvl",  NULL, 0},
  {"ebi.lvl", NULL, 0},
  {"lcx.lvl", NULL, 0},
  {"lmx.lvl", NULL, 0},
  {"gfx.lvl", NULL, 0},
  {"mss.lvl", NULL, 0},
  {"ddr.lvl", NULL, 0},
  {"mmcx.lvl", NULL, 0},
  {"nsp.lvl", NULL, 0},
  {"mxc.lvl", NULL, 0},
  {"lnoc.lvl", NULL, 0},
  {"xo.lvl",  NULL, 0}
};

static pwr_utils_mol_res_t res_mol_target[] = 
{
  {"cx.mol",  0},
  {"mx.mol",  0},
  {"ebi.mol", 0},
  {"lcx.mol", 0},
  {"lmx.mol", 0},
  {"gfx.mol", 0},
  {"mss.mol", 0},
  {"ddr.mol", 0},
  {"mmcx.mol", 0},
  {"nsp.mol", 0},
  {"mxc.mol", 0},
  {"lnoc.mol", 0},
  {"xo.mol",  0}
};

#endif
