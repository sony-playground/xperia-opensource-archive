#include "iterator.h"
#include "mt_xm_common.h"
#include "xmodem.h"
#include "integration_main.h"

int module_setup_normal(fcsmt_log_t log)
{
	int res = FCSERR_OK;

	res = integration_set_property(
		INTG_PROP_FUSED,
		&const_dut_fuse,
		const_dut_fuse_len);
	if (res != FCSERR_OK) {
		log("set is_fused failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_DEV_ID,
		const_dut_dev_id,
		const_dut_dev_id_len);
	if (res != FCSERR_OK) {
		log("set dev_id failed with %d\n", res);
		return res;
	}
	res = integration_set_property(
		INTG_PROP_HWCONFIG,
		const_dut_hwconfig,
		const_dut_hwconfig_len);
	if (res != FCSERR_OK) {
		log("set hwconfig failed with %d\n", res);
		return res;
	}

	return FCSERR_OK;
}

