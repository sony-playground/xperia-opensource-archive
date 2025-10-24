/*
 * Copyright 2017, 2021 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

#include "iterator.h"
#include "xmodem.h"
#include "mt_xm_common.h"
#include <string.h>

int execute_module_xmodem_normal_setup(
		struct iterator_info *it,
		fcsmt_log_t log,
		const char *match)
{
	int res = FCSERR_OK;
	unsigned char phoneid[const_dut_imei_len];
	unsigned int range_offset;
	unsigned int range_length;

	switch (it->cur_module_item) {
	case 0:
		/* If unexpected shutdown goto 2 */
		set_next_module_item(it, 1);
		/* Must export tcstate because integration might
		 * shutdown/restart device
		 */
		export_tcstate(it);

		/* Starting up actual test */
		res = module_setup_normal(log);
		if (res != FCSERR_OK) {
			log("Module setup failed\n");
			return res;
		}

		res = xmodem_init();
		if (res != FCSERR_OK) {
			log("xmodem_init failed with %d\n", res);
			goto test_failure;
		}

		res = xmodem_get_phoneid(0, phoneid, const_dut_imei_len);
		if (res != FCSERR_OK) {
			log("xmodem_get_phoneid failed\n");
			goto test_failure;
		}

		log("xmodem_get_phoneid:0x%x\n",phoneid[0]);
		log("xmodem_get_phoneid:0x%x\n",phoneid[1]);
		log("xmodem_get_phoneid:0x%x\n",phoneid[2]);
		log("xmodem_get_phoneid:0x%x\n",phoneid[3]);
		log("xmodem_get_phoneid:0x%x\n",phoneid[4]);
		log("xmodem_get_phoneid:0x%x\n",phoneid[5]);
		log("xmodem_get_phoneid:0x%x\n",phoneid[6]);
		log("xmodem_get_phoneid:0x%x\n",phoneid[7]);

		if (memcmp(phoneid, const_dut_imei, const_dut_imei_len) != 0) {
			log("xmodem_get_phoneid returned unexpected imei\n");
			goto test_failure;
		}

		log("xmodem_get_phoneid_END:\n");

		res = xmodem_verify_simlock(
				(unsigned char *)const_dut_sl_data,
				const_dut_sl_data_len,
				(unsigned char *)const_dut_sl_signature,
				const_dut_sl_signature_len,
				const_dut_sl_asahi_opid,
				&range_offset,
				&range_length);
		if (res != FCSERR_OK) {
			log("xmodem_verify_simlock_signature returned %d\n",
				res);
			goto test_failure;
		}

		xmodem_deinit();

		/* We got through the test, goto next test */
		inc_n_executed(it);
		set_next_module_item(it, -1);
		break;
	default:
		/* Unexpected shutdown/restart */
		goto test_failure;
	}

	return FCSERR_OK;

test_failure:
	set_next_module_item(it, -1);
	inc_n_failed(it);
	inc_n_executed(it);
	return FCSERR_OK;
}


