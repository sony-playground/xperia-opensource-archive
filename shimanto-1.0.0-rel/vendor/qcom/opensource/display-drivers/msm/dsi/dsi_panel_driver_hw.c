/* SPDX-License-Identifier: GPL-2.0 */
/*
 *  Copyright 2024 Sony Corporation
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */

#include "dsi_panel.h"

/* Brightness Adjust Type */
#define BR_ADJUST_TYPE1 1

static int dsi_panel_driver_adjust_brightness_default(struct dsi_panel *panel, u32 bl_lvl);
static int dsi_panel_driver_adjust_brightness_type1(struct dsi_panel *panel, u32 bl_lvl);

int dsi_panel_driver_adjust_brightness(struct dsi_panel *panel, u32 bl_lvl)
{
	u32 res = 0;
	/* store the value before adjustment for use in the update during FLM mode switching */
	panel->spec_pdata->bl_level = bl_lvl;

	switch (panel->spec_pdata->br_adjust_type) {
		case BR_ADJUST_TYPE1:
			res = dsi_panel_driver_adjust_brightness_type1(panel, bl_lvl);
			break;
		default:
			res = dsi_panel_driver_adjust_brightness_default(panel, bl_lvl);
	}

#ifdef DEBUG
	pr_info("[%s]adjust brightness : %d to %d type=%d flm=%d min=%d max=%d "
			"adj_min=%d adj_max=%d peak=%d tp=%d\n", __func__,
			bl_lvl, res, panel->spec_pdata->br_adjust_type, panel->spec_pdata->flm_mode,
			panel->bl_config.bl_min_level, panel->bl_config.bl_max_level,
			panel->spec_pdata->br_adjust_min_lvl, panel->spec_pdata->br_adjust_max_lvl,
			panel->spec_pdata->br_adjust_peak_lvl, panel->spec_pdata->br_adjust_tp);
#else
	pr_info("[%s] adjust brightness : %d to %d type=%d flm=%d\n", __func__,
			bl_lvl, res, panel->spec_pdata->br_adjust_type, panel->spec_pdata->flm_mode);
#endif
	return res;
}

// y = y0 + (x - x0) * (y1 - y0) / (x1 - x0)
static int dsi_panel_driver_adjust_brightness_default(struct dsi_panel *panel, u32 bl_lvl)
{
	struct dsi_backlight_config bl = panel->bl_config;
	u32 res = bl.bl_min_level + (bl_lvl - 0) * (bl.bl_max_level - bl.bl_min_level)
			/ (bl.brightness_max_level - 0);
	return (res > bl.bl_max_level) ? bl.bl_max_level : res;
}

//For FHD OLED
static int dsi_panel_driver_adjust_brightness_type1(struct dsi_panel *panel, u32 lvl)
{
	struct dsi_backlight_config bl = panel->bl_config;
	struct panel_specific_pdata *pdata = panel->spec_pdata;
	u32 res = 0;
	u32 tp_lvl = pdata->br_adjust_tp * pdata->br_adjust_max_lvl / bl.brightness_max_level;

	if (pdata->flm_mode != 0) {
		res = lvl * pdata->br_adjust_max_lvl / bl.brightness_max_level;
	} else {
		// Beyond transition point, a value higher than br_adjust_max_lvl can be set.
		if (lvl <= pdata->br_adjust_tp) {
			res = lvl * pdata->br_adjust_max_lvl / bl.brightness_max_level;
		} else {
			res = tp_lvl + (lvl - pdata->br_adjust_tp) * (pdata->br_adjust_peak_lvl - tp_lvl)
				/ (bl.brightness_max_level - pdata->br_adjust_tp);
		}
	}

	if (res < pdata->br_adjust_min_lvl) {
		res = pdata->br_adjust_min_lvl;
	} else if (res > pdata->br_adjust_peak_lvl) {
		res = pdata->br_adjust_peak_lvl;
	}

	return res;
}
