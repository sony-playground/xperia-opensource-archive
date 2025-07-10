/*
 * Copyright (C) 2017 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */
#include "integration_emulator.h"
#include "integration_main.h"
#include "integration_core.h"
#include "integration_ta.h"
#include "integration_nv.h"
#include "integration_eroot.h"
#include "integration_xbpal.h"
#include "integration_xflattest.h"
#include "fcserr.h"
#include "fcstest_defines.h"
#include "ta_interface.h"
#include "rule_types.h"
#include <malloc.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

#define INTEMUL_TIMER_COUNT 4

struct called_counters {
	unsigned char pwr_button_pressed;
	unsigned char copy_hw_conf;
	unsigned char clear_wb_reason;
	unsigned char vibrate;
	unsigned char erase_user_sensitive;
	unsigned char erase_ta_dk;
	unsigned char write_sec_data;
	unsigned char write_ks_org;
	unsigned char write_ks_bak;
	unsigned char lock;
	unsigned char reset_vbmeta_arb;
};

struct timer_info {
	struct timespec trigger;
	void *arg;
	void (*timer_cb)(void *arg);
};

struct intemul_data {
	struct iterator_info *it;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	pthread_t timer_thread;
	struct timer_info timer[INTEMUL_TIMER_COUNT];
	bool is_fused;
	unsigned char *dev_id;
	unsigned int dev_id_len;
	unsigned char *hwconfig;
	unsigned int hwconfig_len;
	unsigned char *miscDK;
	unsigned int miscDK_len;
	unsigned char *ks;
	unsigned int ks_len;
	unsigned char *ksbak;
	unsigned int ksbak_len;
	unsigned char *hmac_key_low;
	unsigned int hmac_key_low_len;
	unsigned char *hmac_key_high;
	unsigned int hmac_key_high_len;
	unsigned int startup_flags;
	unsigned int wb_reason;
	char *sw_version;
	unsigned char *ta_version;
	unsigned int ta_version_len;
	unsigned char *boot_config;
	unsigned int boot_config_len;
	unsigned char *factory_mode;
	unsigned int factory_mode_len;
	unsigned char *reset_frp;
	unsigned int reset_frp_len;
	unsigned char *sl_signature;
	unsigned int sl_signature_len;
	unsigned char *sl_data;
	unsigned int sl_data_len;
	unsigned char *auth_channel_cmd;
	unsigned int auth_channel_cmd_len;
	unsigned char *urand;
	unsigned int urand_len;
	unsigned char reset_detect;
	unsigned char usb_vbus_detect;
	unsigned char usb_otg_detect;
	unsigned char boot_into_recovery;
	unsigned char pwr_button_pressed;
	unsigned char vldwn_button_pressed;
	unsigned char vlup_button_pressed;
	enum xbpal_rgb_led_cfg_t led;
	struct xfl_sec_data sec_data;
	void (*export_hwstate)(
		struct integration_hwstate *state);
	struct called_counters called;
	struct timespec start_boot;
	struct integration_context context;
	struct integration_core_context core_context;
	struct integration_ta_context ta_context;
	struct integration_nv_context nv_context;
	struct integration_eroot_context eroot_context;
	struct integration_xbpal_context xbpal_context;
	struct integration_xflattest_context xflattest_context;
};

static int gpio_vldwn_is_asserted(
		struct intemul_data *data,
		uint8_t chip,
		uint32_t pin) {
	if (data->vldwn_button_pressed && chip == 1 && pin == 5)
		return 1;
	return 0;
}

static int gpio_vlup_is_asserted(
		struct intemul_data *data,
		uint8_t chip,
		uint32_t pin) {
	if (data->vlup_button_pressed && chip == 1 && pin == 6)
		return 1;
	return 0;
}

static void *timer_thread_function(void *ptr)
{
	int res = 0;
	int i;
	struct timespec cur;
	struct timespec termwait;
	struct intemul_data *intdata = ptr;

	if (intdata == NULL)
		return NULL;

	pthread_mutex_lock(&(intdata->mutex));
	while (!res || res == ETIMEDOUT) {
		clock_gettime(CLOCK_REALTIME, &cur);
		termwait.tv_sec = cur.tv_sec + 1;
		termwait.tv_nsec = cur.tv_nsec;
		for (i = 0; i < INTEMUL_TIMER_COUNT; i++) {
			/* Active timers1 */
			if (intdata->timer[i].trigger.tv_sec == 0 ||
				intdata->timer[i].trigger.tv_nsec == 0)
				continue;

			/* Is timer timed out? */
			if (intdata->timer[i].trigger.tv_sec <=
					cur.tv_sec &&
				intdata->timer[i].trigger.tv_nsec <=
					cur.tv_nsec) {
				integration_log(
						"timer cb at %d, %ld!\n",
						(int)(cur.tv_sec),
						cur.tv_nsec);
				intdata->timer[i].trigger.tv_sec = 0;
				intdata->timer[i].trigger.tv_nsec = 0;
				intdata->timer[i].timer_cb(
					intdata->timer[i].arg);
				continue;
			}
			/* Timer is not timed out. */
			/* Is this timer nearest to timeout? */
			if (intdata->timer[i].trigger.tv_sec <
					termwait.tv_sec) {
				termwait = intdata->timer[i].trigger;
				continue;
			}
			if (intdata->timer[i].trigger.tv_sec  ==
					termwait.tv_sec &&
					intdata->timer[i].trigger.tv_nsec  <
					termwait.tv_nsec) {
				termwait = intdata->timer[i].trigger;
			}
		}
		res = pthread_cond_timedwait(&(intdata->cond),
				&(intdata->mutex),
				&termwait);
	}
	pthread_mutex_unlock(&(intdata->mutex));
	return NULL;
}

static int timer_set(
		struct intemul_data *intdata,
		void **ctx,
		void (*timer_cb)(void *arg),
		uint32_t timeout,
		void *arg)
{
	int res = -FCSERR_ENOTF;
	int i;
	time_t sec;
	long int nsec;
	struct timespec cur;

	if (intdata == NULL || ctx == NULL || timer_cb == NULL || arg == NULL)
		return -FCSERR_EINVAL;

	pthread_mutex_lock(&(intdata->mutex));
	clock_gettime(CLOCK_REALTIME, &cur);
	for (i = 0; i < INTEMUL_TIMER_COUNT; i++) {
		if (intdata->timer[i].trigger.tv_sec == 0 &&
				intdata->timer[i].trigger.tv_nsec == 0 &&
				intdata->timer[i].timer_cb == NULL) {
			sec = cur.tv_sec + timeout / 1E3;
			nsec = cur.tv_nsec + (timeout % (long int)1E3) * 1E6;
			sec += nsec / 1E9;
			nsec = nsec % (long int)1E9;
			intdata->timer[i].trigger.tv_sec = sec;
			intdata->timer[i].trigger.tv_nsec = nsec;
			intdata->timer[i].arg = arg;
			intdata->timer[i].timer_cb = timer_cb;
			res = FCSERR_OK;
			break;
		}
	}
	pthread_mutex_unlock(&(intdata->mutex));
	if (res == FCSERR_OK)
		pthread_cond_signal(&(intdata->cond));
	return res;
}

static int timer_clear(
		struct intemul_data *intdata,
		void *ctx)
{
	int res = -FCSERR_ENOTF;
	int i;

	if (intdata == NULL || ctx == NULL)
		return -FCSERR_EINVAL;

	pthread_mutex_lock(&(intdata->mutex));
	for (i = 0; i < INTEMUL_TIMER_COUNT; i++) {
		if (&(intdata->timer[i]) == ctx) {
			intdata->timer[i].trigger.tv_sec = 0;
			intdata->timer[i].trigger.tv_nsec = 0;
			intdata->timer[i].arg = NULL;
			intdata->timer[i].timer_cb = NULL;
			res = FCSERR_OK;
			break;
		}
	}
	pthread_mutex_unlock(&(intdata->mutex));
	return res;
}

struct release_button_info {
	struct intemul_data *intdata;
	void *ctx;
};

struct release_button_info g_release_pwr_button_info = { 0 };

static void release_pwr_button_cb(void *arg)
{
	struct release_button_info *info =
			(struct release_button_info *)arg;

	if (NULL == info || NULL == info->intdata)
		return;

	info->intdata->pwr_button_pressed = 0;

	timer_clear(
		info->intdata,
		info->ctx);
}

struct release_button_info g_release_vldwn_button_info = { 0 };

static void release_vldwn_button_cb(void *arg)
{
	struct release_button_info *info =
			(struct release_button_info *)arg;

	if (NULL == info || NULL == info->intdata)
		return;

	info->intdata->vldwn_button_pressed = 0;

	timer_clear(
		info->intdata,
		info->ctx);
}

struct release_button_info g_release_vlup_button_info = { 0 };

static void release_vlup_button_cb(void *arg)
{
	struct release_button_info *info =
			(struct release_button_info *)arg;

	if (NULL == info || NULL == info->intdata)
		return;

	info->intdata->vlup_button_pressed = 0;

	timer_clear(
		info->intdata,
		info->ctx);
}

static int set_property(
		unsigned char **property,
		unsigned int *property_len,
		const void *value,
		unsigned int value_len)
{
	free(*property);
	*property = malloc(value_len);
	if (*property == NULL)
		return -FCSERR_ENOMEM;
	memcpy(*property, value, value_len);
	*property_len = value_len;
	return FCSERR_OK;
}

static int intemul_set_property(
		struct integration_context *context,
		unsigned int id,
		const void *value,
		unsigned int value_len)
{
	struct intemul_data *data = NULL;

	if ((context == NULL) ||
			(value == NULL) ||
			(value_len == 0)) {
		return -FCSERR_EINVAL;
	}
	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					context);
	switch (id) {
	case INTG_PROP_FUSED:
		if (value_len != 1)
			return -FCSERR_EINVAL;
		if (((char *)value)[0] != 0)
			data->is_fused = true;
		else
			data->is_fused = false;
		break;
	case INTG_PROP_DEV_ID:
		return set_property(&data->dev_id, &data->dev_id_len,
						value, value_len);
	case INTG_PROP_HWCONFIG:
		return set_property(&data->hwconfig, &data->hwconfig_len,
						value, value_len);
	case INTG_PROP_MISCTA_DK:
		return set_property(&data->miscDK, &data->miscDK_len,
						value, value_len);
	case INTG_PROP_KS:
		return set_property(&data->ks, &data->ks_len,
						value, value_len);
	case INTG_PROP_KS_BAK:
		return set_property(&data->ksbak, &data->ksbak_len,
						value, value_len);
	case INTG_PROP_SD_VERSION:
		if (value_len != sizeof(unsigned int))
			return -FCSERR_EINVAL;
		data->sec_data.version = *((unsigned int *)value);
		break;
	case INTG_PROP_SD_UNLOCK:
		if (value_len != sizeof(unsigned int))
			return -FCSERR_EINVAL;
		data->sec_data.bl_unlock_status = *((unsigned int *)value);
		break;
	case INTG_PROP_SD_KS_COUNT:
		if (value_len != sizeof(unsigned int))
			return -FCSERR_EINVAL;
		data->sec_data.rpmb_ks_counter = *((unsigned int *)value);
		break;
	case INTG_PROP_SD_KS_XCS:
		if (value_len != sizeof(unsigned int))
			return -FCSERR_EINVAL;
		data->sec_data.xcs_rot = *((unsigned int *)value);
		break;
	case INTG_PROP_SD_KS_HASH:
		if (value_len != sizeof(data->sec_data.keystore_hash_sha256))
			return -FCSERR_EINVAL;
		memcpy(&(data->sec_data.keystore_hash_sha256),
				value, value_len);
		break;
	case INTG_PROP_SD_NONCE:
		if (value_len != sizeof(data->sec_data.sake_nonce))
			return -FCSERR_EINVAL;
		memcpy(&(data->sec_data.sake_nonce),
				value, value_len);
		break;
	case INTG_PROP_SD_VBM_RB:
		if (value_len != sizeof(data->sec_data.rollback_counter))
			return -FCSERR_EINVAL;
		memcpy(&(data->sec_data.rollback_counter),
				value, value_len);
		break;
	case INTG_PROP_SW_VERSION:
		free(data->sw_version);
		data->sw_version = malloc(value_len + 1);
		if (data->sw_version == NULL)
			return -FCSERR_ENOMEM;
		memcpy(data->sw_version, value, value_len);
		data->sw_version[value_len] = '\0';
		break;
	case INTG_PROP_TA_VERSION:
		return set_property(&data->ta_version, &data->ta_version_len,
						value, value_len);
	case INTG_PROP_BOOT_CONFIG:
		/* Check if emulator supports config? */
		return set_property(&data->boot_config, &data->boot_config_len,
						value, value_len);
	case INTG_PROP_LED:
		if (value_len != sizeof(enum xbpal_rgb_led_cfg_t))
			return -FCSERR_EINVAL;
		memcpy(&(data->led), value, value_len);
		break;
	case INTG_PROP_FACTORY_MODE:
		return set_property(&data->factory_mode,
						&data->factory_mode_len,
						value, value_len);
	case INTG_PROP_RESET_FRP:
		return set_property(&data->reset_frp, &data->reset_frp_len,
						value, value_len);
	case INTG_PROP_SL_SIGNATURE:
		return set_property(&data->sl_signature,
						&data->sl_signature_len,
						value, value_len);
	case INTG_PROP_SL_DATA:
		return set_property(&data->sl_data, &data->sl_data_len,
						value, value_len);
	case INTG_PROP_AUTHCH_CMD:
		return set_property(&data->auth_channel_cmd,
						&data->auth_channel_cmd_len,
						value, value_len);
	case INTG_PROP_URAND:
		return set_property(&data->urand, &data->urand_len,
						value, value_len);
	case TA_KEYSTORE_HMAC_KEY:
		return set_property(&data->hmac_key_low,
						&data->hmac_key_low_len,
						value, value_len);
	case TA_KEYSTORE_HMAC_KEY_APPLY:
		return set_property(&data->hmac_key_high,
						&data->hmac_key_high_len,
						value, value_len);
	default:
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static int intemul_clear_property(
		struct integration_context *context,
		unsigned int id)
{
	struct intemul_data *data = NULL;

	if (context == NULL)
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					context);
	switch (id) {
	case INTG_PROP_COUNTERS:
		memset(&(data->called), 0, sizeof(data->called));
		break;
	case INTG_PROP_FACTORY_MODE:
		free(data->factory_mode);
		data->factory_mode = NULL;
		data->factory_mode_len = 0;
		break;
	case INTG_PROP_RESET_FRP:
		free(data->reset_frp);
		data->reset_frp = NULL;
		data->reset_frp_len = 0;
		break;
	case INTG_PROP_KS:
		free(data->ks);
		data->ks = NULL;
		data->ks_len = 0;
		break;
	case INTG_PROP_HWCONFIG:
		free(data->hwconfig);
		data->hwconfig = NULL;
		data->hwconfig_len = 0;
		break;
	case INTG_PROP_SD_VERSION:
		data->sec_data.version = 0;
		break;
	case INTG_PROP_SD_UNLOCK:
		data->sec_data.bl_unlock_status = 0;
		break;
	case INTG_PROP_SD_KS_COUNT:
		data->sec_data.rpmb_ks_counter = 0;
		break;
	case INTG_PROP_SD_KS_XCS:
		data->sec_data.xcs_rot = 0;
		break;
	case INTG_PROP_SD_KS_HASH:
		memset(&(data->sec_data.keystore_hash_sha256), 0,
			sizeof(data->sec_data.keystore_hash_sha256));
		break;
	case INTG_PROP_SD_NONCE:
		memset(&(data->sec_data.sake_nonce), 0,
			sizeof(data->sec_data.sake_nonce));
		break;
	case INTG_PROP_SD_VBM_RB:
		memset(&(data->sec_data.rollback_counter), 0,
			sizeof(data->sec_data.rollback_counter));
		break;

	default:
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static int intemul_is_equal_counter(
		struct intemul_data *data,
		unsigned char *count_ptr,
		const void *value,
		unsigned int value_len)
{
	if (value == NULL)
		return -FCSERR_EINVAL;
	if (value_len != sizeof(unsigned char))
		return -FCSERR_EINVAL;
	if (memcmp(value,
			count_ptr,
			sizeof(unsigned char)))
		return -FCSERR_EDATA;
	return FCSERR_OK;
}

static int get_keystore_size(const uint8_t *ks, uint ks_len, uint *ks_size)
{
	/*
	 * Byte 0 of a keystore has to be 0x30 and byte 1 has to be 0x82.
	 * Bytes 2 and 3 contain the size of the keystore. This size can
	 * be less than the length ks_len, but it cannot be higher.
	 */

	if (!ks || !ks_size)
		return -FCSERR_EINVAL;
	if (ks_len < 4)
		return -FCSERR_ESIZE;
	if (ks[0] != 0x30 || ks[1] != 0x82)
		return -FCSERR_EINFOR;

	*ks_size = (ks[2] << 8) | ks[3];

	if (ks_len < *ks_size)
		return -FCSERR_ESIZE;

	return FCSERR_OK;
}

static int is_equal_hmac_key(uint32_t unit, const void *value, uint value_len)
{
	uint8_t *hmac_key;
	int hmac_key_size;
	int res;

	res = get_ta_unit_size(TA_MISC_PART, unit, &hmac_key_size);
	if (res != FCSERR_OK)
		return res;
	if (hmac_key_size != value_len)
		return -FCSERR_EDATA;
	if (hmac_key_size == 0)
		return FCSERR_OK;

	hmac_key = malloc(hmac_key_size);
	if (!hmac_key)
		return -FCSERR_ENOMEM;
	res = read_ta(TA_MISC_PART, unit, hmac_key, hmac_key_size);
	if (res == FCSERR_OK && memcmp(hmac_key, value, hmac_key_size))
		res = -FCSERR_EDATA;
	free(hmac_key);
	return res;
}

static int intemul_is_equal_property(
		struct integration_context *context,
		unsigned int id,
		const void *value,
		unsigned int value_len)
{
	struct intemul_data *data = NULL;
	uint ks_size;
	uint ks2_size;
	int res;

	if ((context == NULL) ||
			((value == NULL) && (value_len > 0)) ||
			((value != NULL) && (value_len == 0)))
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					context);
	switch (id) {
	case INTG_PROP_COUNTERS:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(data->called))
			return -FCSERR_EINVAL;
		if (memcmp(value,
				&(data->called),
				sizeof(data->called)))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_CNT_PWRBUTPRS:
		return intemul_is_equal_counter(
				data,
				&(data->called.pwr_button_pressed),
				value,
				value_len);
		break;
	case INTG_PROP_CNT_CPHWCONF:
		return intemul_is_equal_counter(
				data,
				&(data->called.copy_hw_conf),
				value,
				value_len);
		break;
	case INTG_PROP_CNT_CLRWBRSN:
		return intemul_is_equal_counter(
				data,
				&(data->called.clear_wb_reason),
				value,
				value_len);
		break;
	case INTG_PROP_CNT_VIBRATE:
		return intemul_is_equal_counter(
				data,
				&(data->called.vibrate),
				value,
				value_len);
		break;
	case INTG_PROP_CNT_ERASEUSER:
		return intemul_is_equal_counter(
				data,
				&(data->called.erase_user_sensitive),
				value,
				value_len);
		break;
	case INTG_PROP_CNT_ERASETADK:
		return intemul_is_equal_counter(
				data,
				&(data->called.erase_ta_dk),
				value,
				value_len);
		break;
	case INTG_PROP_CNT_RSTVBMARB:
		return intemul_is_equal_counter(
				data,
				&(data->called.reset_vbmeta_arb),
				value,
				value_len);
		break;
	case INTG_PROP_LED:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(data->led))
			return -FCSERR_EINVAL;
		if (memcmp(value, &(data->led), sizeof(data->led)))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_RESET_FRP:
		/* NULL Ptr indicates empty property */
		if ((value == NULL) && (data->reset_frp == NULL))
			return FCSERR_OK;
		if (value == NULL)
			return -FCSERR_EDATA;
		if (data->reset_frp == NULL)
			return -FCSERR_EDATA;
		if (value_len != data->reset_frp_len)
			return -FCSERR_EDATA;
		if (memcmp(value, data->reset_frp, data->reset_frp_len))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_CNT_WRSECDATA:
		return intemul_is_equal_counter(
				data,
				&(data->called.write_sec_data),
				value,
				value_len);
		break;
	case INTG_PROP_SD_VERSION:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(unsigned int))
			return -FCSERR_EINVAL;
		if (*((unsigned int *)value) != data->sec_data.version)
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_SD_UNLOCK:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(unsigned int))
			return -FCSERR_EINVAL;
		if (*((unsigned int *)value) !=
				data->sec_data.bl_unlock_status)
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_SD_KS_COUNT:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(unsigned int))
			return -FCSERR_EINVAL;
		if (*((unsigned int *)value) !=
				data->sec_data.rpmb_ks_counter)
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_SD_KS_XCS:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(unsigned int))
			return -FCSERR_EINVAL;
		if (*((unsigned int *)value) !=
				data->sec_data.xcs_rot)
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_SD_KS_HASH:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(data->sec_data.keystore_hash_sha256))
			return -FCSERR_EINVAL;
		if (memcmp(value,
				&(data->sec_data.keystore_hash_sha256),
				value_len))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_SD_NONCE:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(data->sec_data.sake_nonce))
			return -FCSERR_EINVAL;
		if (memcmp(value,
				&(data->sec_data.sake_nonce),
				value_len))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_SD_VBM_RB:
		if (value == NULL)
			return -FCSERR_EINVAL;
		if (value_len != sizeof(data->sec_data.rollback_counter))
			return -FCSERR_EINVAL;
		if (memcmp(value,
				&(data->sec_data.rollback_counter),
				value_len))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_CNT_WRKSORG:
		return intemul_is_equal_counter(
				data,
				&(data->called.write_ks_org),
				value,
				value_len);
		break;
	case INTG_PROP_CNT_WRKSBAK:
		return intemul_is_equal_counter(
				data,
				&(data->called.write_ks_bak),
				value,
				value_len);
		break;
	case INTG_PROP_CNT_LOCK:
		return intemul_is_equal_counter(
				data,
				&(data->called.lock),
				value,
				value_len);
		break;
	case INTG_PROP_KS:
		res = get_keystore_size(data->ks, data->ks_len, &ks_size);
		if (res != FCSERR_OK)
			return res;
		res = get_keystore_size(value, value_len, &ks2_size);
		if (res != FCSERR_OK)
			return res;
		if (ks_size != ks2_size || memcmp(data->ks, value, ks_size))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_KS_BAK:
		res = get_keystore_size(data->ksbak, data->ksbak_len, &ks_size);
		if (res != FCSERR_OK)
			return res;
		res = get_keystore_size(value, value_len, &ks2_size);
		if (res != FCSERR_OK)
			return res;
		if (ks_size != ks2_size || memcmp(data->ksbak, value, ks_size))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_AUTHCH_CMD:
		/* NULL Ptr indicates empty property */
		if ((value == NULL) && (data->auth_channel_cmd == NULL))
			return FCSERR_OK;
		if (value == NULL)
			return -FCSERR_EDATA;
		if (data->auth_channel_cmd == NULL)
			return -FCSERR_EDATA;
		if (value_len != data->auth_channel_cmd_len)
			return -FCSERR_EDATA;
		if (memcmp(value,
				data->auth_channel_cmd,
				data->auth_channel_cmd_len))
			return -FCSERR_EDATA;
		break;
	case INTG_PROP_TA_HMAC_LOW:
		return is_equal_hmac_key(
				TA_KEYSTORE_HMAC_KEY, value, value_len);
	case INTG_PROP_TA_HMAC_HIGH:
		return is_equal_hmac_key(
				TA_KEYSTORE_HMAC_KEY_APPLY, value, value_len);
	default:
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static int intemul_prepare_hwstate(
		struct integration_context *context,
		struct integration_hwstate *state)
{
	struct intemul_data *data = NULL;

	if ((context == NULL) || (state == NULL))
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					context);
	if (NULL == data->export_hwstate)
		return -FCSERR_ENIMP;

	data->export_hwstate(state);

	exit(0);
}

static const struct integration_func intemul_func = {
	.set_property = intemul_set_property,
	.clear_property = intemul_clear_property,
	.is_equal_property = intemul_is_equal_property,
	.prepare_hwstate = intemul_prepare_hwstate
};

static int intemul_is_fused(
		struct integration_core_context *context,
		bool *is_fused)
{
	struct intemul_data *data = NULL;

	if ((context == NULL) || (is_fused == NULL))
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					core_context);

	*is_fused = data->is_fused;
	return FCSERR_OK;
}

static int intemul_get_dieid(
		struct integration_core_context *context,
		uint8_t *buf, size_t len)
{
	struct intemul_data *data = NULL;

	if ((context == NULL) || (buf == NULL) || (len == 0))
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					core_context);

	if ((data->dev_id == NULL) || (data->dev_id_len == 0))
		return -FCSERR_ENOTF;

	if (data->dev_id_len != len)
		return -FCSERR_EINVAL;

	memcpy(buf, data->dev_id, data->dev_id_len);
	return FCSERR_OK;
}

static int intemul_get_dieid_len(
		struct integration_core_context *context)
{
	struct intemul_data *data = NULL;

	if (context == NULL)
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					core_context);

	if ((data->dev_id == NULL) || (data->dev_id_len == 0))
		return -FCSERR_ENOTF;

	return data->dev_id_len;
}

static int intemul_is_test_cert_allowed(
		struct integration_core_context *context)
{
	return 1;
}

static const struct integration_core_func intemul_core_func = {
	.is_fused = intemul_is_fused,
	.get_dieid = intemul_get_dieid,
	.get_dieid_len = intemul_get_dieid_len,
	.is_test_cert_allowed = intemul_is_test_cert_allowed,
};

static TA_ErrCode_t intemul_TA_SetConfig(
		struct integration_ta_context *context,
		const TA_Functions_t *pFuncs,
		uint32_t startAddr,
		uint32_t eBlkSize,
		uint8_t  nbrOfBlks)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_OpenPartition(
		struct integration_ta_context *context,
		uint8_t partition,
		uint8_t mode)
{
	if (partition != TA_MISC_PART)
		return TA_Parameters;
	return TA_Success;
}

static TA_ErrCode_t intemul_TA_Close(
		struct integration_ta_context *context)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_GetVersion(
		struct integration_ta_context *context,
		uint8_t *pVersion,
		uint8_t partition)
{
	return TA_UnsupportedCmd;
}

static uint8_t intemul_TA_IsVersionSupported(
		struct integration_ta_context *context,
		uint8_t version)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_Format(
		struct integration_ta_context *context,
		uint8_t version)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_Flush(
		struct integration_ta_context *context)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_WriteData(
		struct integration_ta_context *context,
		uint32_t unit,
		const uint8_t *pData,
		uint32_t size)
{
	struct intemul_data *data = NULL;

	if (context == NULL || pData == NULL || size == 0)
		return TA_Parameters;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					ta_context);

	switch (unit) {
	case TA_AUTH_CH:
		free(data->auth_channel_cmd);
		data->auth_channel_cmd = malloc(size);
		if (data->auth_channel_cmd == NULL)
			return -FCSERR_ENOMEM;
		memcpy(data->auth_channel_cmd, pData, size);
		data->auth_channel_cmd_len = size;
		break;
	case TA_KEYSTORE_HMAC_KEY:
		free(data->hmac_key_low);
		data->hmac_key_low = malloc(size);
		if (data->hmac_key_low == NULL)
			return -FCSERR_ENOMEM;
		memcpy(data->hmac_key_low, pData, size);
		data->hmac_key_low_len = size;
		break;
	case TA_KEYSTORE_HMAC_KEY_APPLY:
		free(data->hmac_key_high);
		data->hmac_key_high = malloc(size);
		if (data->hmac_key_high == NULL)
			return -FCSERR_ENOMEM;
		memcpy(data->hmac_key_high, pData, size);
		data->hmac_key_high_len = size;
		break;
	default:
		return TA_UnitNotFound;
	}
	return TA_Success;
}

static TA_ErrCode_t intemul_TA_ReadData(
		struct integration_ta_context *context,
		uint32_t unit,
		uint8_t *pData,
		uint32_t size)
{
	struct intemul_data *data = NULL;

	if (context == NULL || pData == NULL)
		return TA_Parameters;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					ta_context);

	switch (unit) {
	case TA_HWCONFIG_UNIT:
		if (data->hwconfig == NULL)
			return TA_UnitNotFound;
		if (data->hwconfig_len > size)
			return TA_Parameters;
		memcpy(pData, data->hwconfig, data->hwconfig_len);
		break;
	case TA_DK_NUMBER_UNIT:
		if (data->miscDK == NULL)
			return TA_UnitNotFound;
		if (data->miscDK_len > size)
			return TA_Parameters;
		memcpy(pData, data->miscDK, data->miscDK_len);
		break;
	case TA_S1_BOOT_VERSION_UNIT:
		if (data->ta_version == NULL)
			return TA_UnitNotFound;
		if (data->ta_version_len > size)
			return TA_Parameters;
		memcpy(pData, data->ta_version, data->ta_version_len);
		break;

	case TA_BOOT_CONFIGURATION_UNIT:
		if (data->boot_config == NULL)
			return TA_UnitNotFound;
		if (data->boot_config_len > size)
			return TA_Parameters;
		memcpy(pData, data->boot_config, data->boot_config_len);
		break;
	case TA_FACTORY_MODE_UNIT:
		if (data->factory_mode == NULL)
			return TA_UnitNotFound;
		if (data->factory_mode_len > size)
			return TA_Parameters;
		memcpy(pData, data->factory_mode, data->factory_mode_len);
		break;
	case TA_RL_DATA_LOW_UNIT:
		if (data->reset_frp == NULL)
			return TA_UnitNotFound;
		if (data->reset_frp_len > size)
			return TA_Parameters;
		memcpy(pData, data->reset_frp, data->reset_frp_len);
		break;
	case TA_SIMLOCK_SIGNATURE_UNIT:
		if (data->sl_signature == NULL)
			return TA_UnitNotFound;
		if (data->sl_signature_len > size)
			return TA_Parameters;
		memcpy(pData, data->sl_signature, data->sl_signature_len);
		break;
	case TA_SIMLOCK_UNIT:
		if (data->sl_data == NULL)
			return TA_UnitNotFound;
		if (data->sl_data_len > size)
			return TA_Parameters;
		memcpy(pData, data->sl_data, data->sl_data_len);
		break;
	case TA_AUTH_CH:
		if (data->auth_channel_cmd == NULL)
			return TA_UnitNotFound;
		if (data->auth_channel_cmd_len > size)
			return TA_Parameters;
		memcpy(pData,
			data->auth_channel_cmd,
			data->auth_channel_cmd_len);
		break;
	case TA_KEYSTORE_HMAC_KEY:
		if (data->hmac_key_low == NULL)
			return TA_UnitNotFound;
		if (data->hmac_key_low_len > size)
			return TA_Parameters;
		memcpy(pData, data->hmac_key_low, data->hmac_key_low_len);
		break;
	case TA_KEYSTORE_HMAC_KEY_APPLY:
		if (data->hmac_key_high == NULL)
			return TA_UnitNotFound;
		if (data->hmac_key_high_len > size)
			return TA_Parameters;
		memcpy(pData, data->hmac_key_high, data->hmac_key_high_len);
		break;
	default:
		return TA_UnitNotFound;
	}
	return TA_Success;
}

static uint32_t intemul_TA_GetUnitSize(
		struct integration_ta_context *context,
		uint32_t unit)
{
	uint32_t ret = 0;
	struct intemul_data *data = NULL;

	if (context == NULL)
		return TA_Parameters;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					ta_context);

	switch (unit) {
	case TA_HWCONFIG_UNIT:
		if (data->hwconfig == NULL)
			ret = 0;
		else
			ret = data->hwconfig_len;
		break;
	case TA_DK_NUMBER_UNIT:
		if (data->miscDK == NULL)
			ret = 0;
		else
			ret = data->miscDK_len;
		break;
	case TA_S1_BOOT_VERSION_UNIT:
		if (data->ta_version == NULL)
			ret = 0;
		else
			ret = data->ta_version_len;
		break;
	case TA_BOOT_CONFIGURATION_UNIT:
		if (data->boot_config == NULL)
			ret = 0;
		else
			ret = data->boot_config_len;
		break;
	case TA_FACTORY_MODE_UNIT:
		if (data->factory_mode == NULL)
			ret = 0;
		else
			ret = data->factory_mode_len;
		break;
	case TA_RL_DATA_LOW_UNIT:
		if (data->reset_frp == NULL)
			ret = 0;
		else
			ret = data->reset_frp_len;
		break;
	case TA_SIMLOCK_SIGNATURE_UNIT:
		if (data->sl_signature == NULL)
			ret = 0;
		else
			ret = data->sl_signature_len;
		break;
	case TA_SIMLOCK_UNIT:
		if (data->sl_data == NULL)
			ret = 0;
		else
			ret = data->sl_data_len;
		break;
	case TA_AUTH_CH:
		if (data->auth_channel_cmd == NULL)
			ret = 0;
		else
			ret = data->auth_channel_cmd_len;
		break;
	case TA_KEYSTORE_HMAC_KEY:
		if (data->hmac_key_low == NULL)
			ret = 0;
		else
			ret = data->hmac_key_low_len;
		break;
	case TA_KEYSTORE_HMAC_KEY_APPLY:
		if (data->hmac_key_high == NULL)
			ret = 0;
		else
			ret = data->hmac_key_high_len;
		break;
	default:
		ret = 0;
	}
	return ret;
}

static TA_ErrCode_t intemul_TA_DeleteUnit(
		struct integration_ta_context *context,
		uint32_t unit)
{
	TA_ErrCode_t ret = TA_Success;
	struct intemul_data *data = NULL;

	if (context == NULL)
		return TA_Parameters;

	data = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					ta_context);

	switch (unit) {
	case TA_BOOT_PARAM_OVERRIDE_UNIT:
		break;
	case TA_RL_DATA_LOW_UNIT:
		free(data->reset_frp);
		data->reset_frp = NULL;
		data->reset_frp_len = 0;
		break;
	case TA_DK_NUMBER_UNIT:
		data->called.erase_ta_dk++;
		break;
	case TA_AUTH_CH:
		if (data->auth_channel_cmd != NULL) {
			free(data->auth_channel_cmd);
			data->auth_channel_cmd = NULL;
		}
		data->auth_channel_cmd_len = 0;
		break;
	case TA_KEYSTORE_HMAC_KEY:
		free(data->hmac_key_low);
		data->hmac_key_low = NULL;
		data->hmac_key_low_len = 0;
		break;
	case TA_KEYSTORE_HMAC_KEY_APPLY:
		free(data->hmac_key_high);
		data->hmac_key_high = NULL;
		data->hmac_key_high_len = 0;
		break;
	default:
		ret = TA_UnitNotFound;
	}
	return ret;
}

static TA_ErrCode_t intemul_TA_Open(
		struct integration_ta_context *context,
		const TA_Functions_t *pFuncs,
		uint8_t  mode,
		uint8_t  partition,
		uint32_t addr,
		uint32_t eBlkSize,
		uint8_t  nbrOfBlks)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_Inc_GetSize(
		struct integration_ta_context *context,
		uint32_t *pSize)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_Inc_Read(
		struct integration_ta_context *context,
		uint32_t *pUnit,
		uint8_t *pData,
		uint32_t size)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_Inc_NextUnit(
		struct integration_ta_context *context)
{
	return TA_UnsupportedCmd;
}

static TA_ErrCode_t intemul_TA_Inc_GetUnitID(
		struct integration_ta_context *context,
		uint32_t *pUnit)
{
	return TA_UnsupportedCmd;
}

static const struct integration_ta_func intemul_ta_func = {
	.SetConfig = intemul_TA_SetConfig,
	.OpenPartition = intemul_TA_OpenPartition,
	.Close = intemul_TA_Close,
	.GetVersion = intemul_TA_GetVersion,
	.IsVersionSupported = intemul_TA_IsVersionSupported,
	.Format = intemul_TA_Format,
	.Flush = intemul_TA_Flush,
	.WriteData = intemul_TA_WriteData,
	.ReadData = intemul_TA_ReadData,
	.GetUnitSize = intemul_TA_GetUnitSize,
	.DeleteUnit = intemul_TA_DeleteUnit,
	.Open = intemul_TA_Open,
	.Inc_GetSize = intemul_TA_Inc_GetSize,
	.Inc_Read = intemul_TA_Inc_Read,
	.Inc_NextUnit = intemul_TA_Inc_NextUnit,
	.Inc_GetUnitID = intemul_TA_Inc_GetUnitID
};

static int intemul_nv_read(
		struct integration_nv_context *context,
		ks_io_state_t *state,
		uint8_t *data,
		uint32_t *data_sz)
{
	struct intemul_data *intdata = NULL;
	struct nvio_state *the_nv_state;
	unsigned int max_len = 0;

	if (context == NULL || state == NULL || data_sz == NULL)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					nv_context);

	the_nv_state = (struct nvio_state *)state;
	/*
	 * Length of data is partition size =>
	 * should be the same for org and bak.
	 * The actual size of the keystore is
	 * given by the CMS format.
	 */
	max_len = intdata->ks_len;
	if (max_len < intdata->ksbak_len)
		max_len = intdata->ksbak_len;
	if (the_nv_state->partition == KS_NV_ORG) {
		if (intdata->ks == NULL || intdata->ks_len == 0)
			return -FCSERR_EINVAL;
		if (data != NULL)
			memcpy(data, intdata->ks, intdata->ks_len);
		*data_sz = max_len;
	} else if (the_nv_state->partition == KS_NV_BAK) {
		if (intdata->ksbak == NULL || intdata->ksbak_len == 0)
			return -FCSERR_EINVAL;
		if (data != NULL)
			memcpy(data, intdata->ksbak, intdata->ksbak_len);
		*data_sz = max_len;
	} else
		return -FCSERR_EINVAL;

	return FCSERR_OK;
}

static int intemul_nv_write(
		struct integration_nv_context *context,
		ks_io_state_t *state,
		uint8_t *data,
		const uint32_t data_sz)
{
	struct intemul_data *intdata = NULL;
	struct nvio_state *the_nv_state;

	if (context == NULL || state == NULL || data == NULL || data_sz == 0)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					nv_context);

	the_nv_state = (struct nvio_state *)state;
	if (the_nv_state->partition == KS_NV_ORG) {
		if (intdata->ks != NULL)
			free(intdata->ks);
		intdata->ks = malloc(data_sz);
		if (intdata->ks == NULL)
			return -FCSERR_ENOMEM;
		memcpy(intdata->ks, data, data_sz);
		intdata->ks_len = data_sz;
		intdata->called.write_ks_org++;
	} else if (the_nv_state->partition == KS_NV_BAK) {
		if (intdata->ksbak != NULL)
			free(intdata->ksbak);
		intdata->ksbak = malloc(data_sz);
		if (intdata->ksbak == NULL)
			return -FCSERR_ENOMEM;
		memcpy(intdata->ksbak, data, data_sz);
		intdata->ksbak_len = data_sz;
		intdata->called.write_ks_bak++;
	} else
		return -FCSERR_EINVAL;

	return FCSERR_OK;
}

static const struct integration_nv_func intemul_nv_func = {
	.read = intemul_nv_read,
	.write = intemul_nv_write
};

static int intemul_read_xfl_sec_data(
		struct integration_xflattest_context *context,
		struct xfl_sec_data *data)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL || data == NULL)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xflattest_context);
	memcpy(data, &(intdata->sec_data), sizeof(struct xfl_sec_data));
	return FCSERR_OK;
}

int intemul_write_xfl_sec_data(
		struct integration_xflattest_context *context,
		struct xfl_sec_data *data)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL || data == NULL)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xflattest_context);
	memcpy(&(intdata->sec_data), data, sizeof(struct xfl_sec_data));
	intdata->called.write_sec_data++;
	return FCSERR_OK;
}

static const struct integration_xflattest_func intemul_xflattest_func = {
	.read = intemul_read_xfl_sec_data,
	.write = intemul_write_xfl_sec_data
};

static int intemul_xbpal_gpio_get_pin(
		struct integration_xbpal_context *context,
		uint8_t chip, uint32_t pin, uint8_t *state)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL || state == NULL)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);
	if (gpio_vldwn_is_asserted(intdata, chip, pin))
		*state = 0x00; /* Expect pulled up */
	else if (gpio_vlup_is_asserted(intdata, chip, pin))
		*state = 0x00; /* Expect pulled up */
	else
		*state = 0XFF; /* Expect pulled up */
	return FCSERR_OK;
}

static int intemul_xbpal_gpio_set_config(
		struct integration_xbpal_context *context,
		uint8_t chip, uint32_t pin, struct xbpal_gpio_cfg *cfg)
{
	if (context == NULL || cfg == NULL)
		return -FCSERR_EINVAL;

	if (cfg->pullUpOrDown != XBPAL_GPIO_PULLUP) {
		integration_log("Expected GPIO to be pulled up!\n");
		return -FCSERR_EINVAL;
	}
	return FCSERR_OK;
}

static uint32_t intemul_xbpal_get_boot_time(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;
	struct timespec cur;
	uint32_t res = 0;

	if (context == NULL)
		return 0;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	clock_gettime(CLOCK_REALTIME, &cur);
	res = (cur.tv_sec - intdata->start_boot.tv_sec) * 1E3;
	res += (cur.tv_nsec - intdata->start_boot.tv_nsec) / 1E6;
	return res;
}

static int intemul_xbpal_timer_register(
		struct integration_xbpal_context *context,
		void **ctx,
		void (*timer_cb)(void *arg),
		uint32_t timeout,
		void *arg)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	return timer_set(
			intdata,
			ctx,
			timer_cb,
			timeout,
			arg);
}

static int intemul_xbpal_timer_deregister(
		struct integration_xbpal_context *context,
		void *timer_context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL || timer_context == NULL)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	return timer_clear(
			intdata,
			timer_context);
}

static void intemul_xbpal_delay_us(
		struct integration_xbpal_context *context,
		uint32_t time_us)
{
	struct timespec termwait;

	termwait.tv_sec = time_us / 1E6;
	termwait.tv_nsec = (time_us % (long int)1E6) * 1E3;
	nanosleep(&termwait, NULL);
}

static uint32_t intemul_xbpal_get_startup_bits(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return 0;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);
	return intdata->startup_flags;
}

static uint32_t intemul_xbpal_get_wb_reason(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return 0;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);
	return intdata->wb_reason;
}

static enum xbpal_warmboot_t intemul_xbpal_translate_wb_reason(
		struct integration_xbpal_context *context,
		uint32_t raw_reason)
{
	/* No need to translate reason */
	return raw_reason;
}

static void intemul_xbpal_clear_wb_reason(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	intdata->called.clear_wb_reason++;
	intdata->wb_reason = 0;
}

static bool intemul_xbpal_usb_vbus_detect(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return false;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	return (intdata->usb_vbus_detect != 0);
}

static bool intemul_xbpal_usb_otg_detect(
		struct integration_xbpal_context *context,
		enum xbpal_ServiceOtgRid_t *otg_state)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return false;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	return (intdata->usb_otg_detect != 0);
}

static bool intemul_xbpal_boot_into_recovery(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return false;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	return (intdata->boot_into_recovery != 0);
}

static bool intemul_xbpal_pwr_button_pressed(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return false;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);
	if (intdata->called.pwr_button_pressed > 3) {
		integration_log("Probably inside reset handling. Delay\n");
		intemul_xbpal_delay_us(context, 1E6);
	} else
		(intdata->called.pwr_button_pressed)++;

	return (intdata->pwr_button_pressed != 0);
}

static bool intemul_xbpal_rst_button_pressed(
		struct integration_xbpal_context *context)
{
	return false;
}

static bool intemul_xbpal_kbd_button_pressed(
		struct integration_xbpal_context *context,
		uint8_t row, uint8_t col)
{
	integration_log("kbd_button_pressed ?????????\n");
	return false;
}

static bool intemul_xbpal_erase_user_sensitive(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return false;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	integration_log("erase_user_sensitive !!!!!!!!!!!!!!\n");
	(intdata->called.erase_user_sensitive)++;
	return true;
}

static int intemul_xbpal_unlock_bootloader(
		struct integration_xbpal_context *context)
{
	integration_log("unlock_bootloader ?????????\n");
	return FCSERR_OK;
}

static int intemul_xbpal_lock_bootloader(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return false;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	intdata->called.lock++;
	integration_log("lock_bootloader !!!!!!!!!!!!!!\n");
	return FCSERR_OK;
}

static bool intemul_xbpal_reset_detect(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return false;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	return (intdata->reset_detect != 0);
}

static void intemul_xbpal_vibrate(
		struct integration_xbpal_context *context,
		uint32_t when_us, uint32_t duration_us)
{
	struct intemul_data *intdata = NULL;
	struct timespec cur;
	struct timespec wait;
	struct timespec sleep;

	if (context == NULL)
		return;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	clock_gettime(CLOCK_REALTIME, &cur);
	wait.tv_sec = cur.tv_sec + when_us / 1E6;
	wait.tv_nsec = cur.tv_nsec + (when_us % (long int)1E6) * 1E3;
	wait.tv_sec += wait.tv_nsec / 1E9;
	wait.tv_nsec = wait.tv_nsec % (long int)1E9;
	while (wait.tv_sec > cur.tv_sec ||
			wait.tv_nsec > cur.tv_nsec) {
		if (!(intdata->pwr_button_pressed))
			return;
		sleep.tv_sec = 0;
		sleep.tv_nsec = 1000000;
		nanosleep(&sleep, NULL);
		clock_gettime(CLOCK_REALTIME, &cur);
	}

	intdata->called.vibrate++;
	integration_log("Vibrate !!!!!!!!!!!!!!\n");

	sleep.tv_sec = duration_us / 1E6;
	sleep.tv_nsec = (duration_us % (unsigned int)1E6) * 1E3;
	nanosleep(&sleep, NULL);
}

static bool intemul_xbpal_rgb_led_ctl(
		struct integration_xbpal_context *context,
		enum xbpal_rgb_led_cfg_t cfg)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return false;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	intdata->led = cfg;

	switch (cfg) {
	case XBPAL_LED_TURN_ON_RED:
		integration_log("rgb_led_ctl: RED\n");
		break;
	case XBPAL_LED_TURN_ON_GREEN:
		integration_log("rgb_led_ctl: GREEN\n");
		break;
	case XBPAL_LED_TURN_ON_BLUE:
		integration_log("rgb_led_ctl: BLUE\n");
		break;
	case XBPAL_LED_TURN_OFF:
		integration_log("rgb_led_ctl: OFF\n");
		break;
	default:
		integration_log("rgb_led_ctl: INVALID\n");
		break;
		return false;
	}
	return true;
}

static void intemul_xbpal_shutdown(
		struct integration_xbpal_context *context,
		enum xbpal_shutdown_reason_t reason)
{
	integration_log("shutdown !!!!!!!!!!!!!!\n");

	if (context == NULL)
		return;

	exit(0);
}

static int intemul_xbpal_get_version_string(
		struct integration_xbpal_context *context,
		char **version_string)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL || version_string == NULL)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	if (intdata->sw_version == NULL)
		return -FCSERR_ENOTF;
	*version_string = intdata->sw_version;

	return FCSERR_OK;
}

static int intemul_xbpal_get_frp_data_size(
		struct integration_xbpal_context *context,
		uint32_t *data_sz)
{
	if (context == NULL || data_sz == NULL)
		return -FCSERR_EINVAL;

	return FCSERR_OK;
}

static int intemul_xbpal_read_frp_data(
		struct integration_xbpal_context *context,
		uint8_t *data,
		uint32_t data_sz)
{
	if (context == NULL || data == NULL)
		return -FCSERR_EINVAL;

	return FCSERR_OK;
}

static int intemul_xbpal_reset_vbmeta_counters(
		struct integration_xbpal_context *context)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);
	intdata->called.reset_vbmeta_arb++;

	return FCSERR_OK;
}

static int intemul_xbpal_read_vbmeta_counters(
		struct integration_xbpal_context *context,
		uint64_t *cnt_buf,
		uint32_t vector_size)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL || cnt_buf == NULL || vector_size == 0)
		return -FCSERR_EINVAL;

	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	if ((vector_size * sizeof(uint64_t)) !=
			sizeof(intdata->sec_data.rollback_counter))
		return -FCSERR_EINVAL;

	memcpy(cnt_buf,
		intdata->sec_data.rollback_counter,
		sizeof(intdata->sec_data.rollback_counter));

	return FCSERR_OK;
}

static int intemul_xbpal_fcs_urand(
		struct integration_xbpal_context *context,
		uint8_t *buf,
		uint16_t len)
{
	struct intemul_data *intdata = NULL;

	if (context == NULL || buf == NULL || len == 0)
		return -FCSERR_EINVAL;


	intdata = (struct intemul_data *)
		fcstest_container_of(context,
					struct intemul_data,
					xbpal_context);

	if ((intdata->urand == NULL) ||
			(intdata->urand_len == 0) ||
			(len != intdata->urand_len))
		return -FCSERR_EINVAL;

	memcpy(buf, intdata->urand, intdata->urand_len);

	return FCSERR_OK;
}


static const struct integration_xbpal_func intemul_xbpal_func = {
	.gpio_get_pin = intemul_xbpal_gpio_get_pin,
	.gpio_set_config = intemul_xbpal_gpio_set_config,
	.get_boot_time = intemul_xbpal_get_boot_time,
	.timer_register = intemul_xbpal_timer_register,
	.timer_deregister = intemul_xbpal_timer_deregister,
	.delay_us = intemul_xbpal_delay_us,
	.get_startup_bits = intemul_xbpal_get_startup_bits,
	.get_wb_reason = intemul_xbpal_get_wb_reason,
	.translate_wb_reason = intemul_xbpal_translate_wb_reason,
	.clear_wb_reason = intemul_xbpal_clear_wb_reason,
	.usb_vbus_detect = intemul_xbpal_usb_vbus_detect,
	.usb_otg_detect = intemul_xbpal_usb_otg_detect,
	.boot_into_recovery = intemul_xbpal_boot_into_recovery,
	.pwr_button_pressed = intemul_xbpal_pwr_button_pressed,
	.rst_button_pressed = intemul_xbpal_rst_button_pressed,
	.kbd_button_pressed = intemul_xbpal_kbd_button_pressed,
	.erase_user_sensitive = intemul_xbpal_erase_user_sensitive,
	.unlock_bootloader = intemul_xbpal_unlock_bootloader,
	.lock_bootloader = intemul_xbpal_lock_bootloader,
	.reset_detect = intemul_xbpal_reset_detect,
	.vibrate = intemul_xbpal_vibrate,
	.rgb_led_ctl = intemul_xbpal_rgb_led_ctl,
	.shutdown = intemul_xbpal_shutdown,
	.get_version_string = intemul_xbpal_get_version_string,
	.get_frp_data_size = intemul_xbpal_get_frp_data_size,
	.read_frp_data = intemul_xbpal_read_frp_data,
	.reset_vbmeta_counters = intemul_xbpal_reset_vbmeta_counters,
	.read_vbmeta_counters = intemul_xbpal_read_vbmeta_counters,
	.fcs_urand = intemul_xbpal_fcs_urand
};

int integration_emulator_setup(
		void (*log)(const char *fmt, ...),
		struct iterator_info *it,
		struct integration_hwstate *state,
		void (*export_hwstate)(
			struct integration_hwstate *state))
{
	int res = -FCSERR_EINVAL;
	struct intemul_data *data = NULL;

	if (log == NULL || it == NULL || export_hwstate == NULL)
		return -FCSERR_EINVAL;

	data = (struct intemul_data *)malloc(
			sizeof(struct intemul_data));
	if (data == NULL)
		return -FCSERR_ENOMEM;

	memset(data, 0, sizeof(struct intemul_data));
	data->it = it;
	data->is_fused = true;
	data->dev_id = NULL;
	data->dev_id_len = 0;
	data->hwconfig = NULL;
	data->hwconfig_len = 0;
	data->miscDK = NULL;
	data->miscDK_len = 0;
	data->ks = NULL;
	data->ks_len = 0;
	data->ksbak = NULL;
	data->ksbak_len = 0;
	data->hmac_key_low = NULL;
	data->hmac_key_low_len = 0;
	data->hmac_key_high = NULL;
	data->hmac_key_high_len = 0;
	data->startup_flags = 0;
	data->wb_reason = 0;
	data->sw_version = NULL;
	data->ta_version = NULL;
	data->ta_version_len = 0;
	data->boot_config = NULL;
	data->boot_config_len = 0;
	data->factory_mode = NULL;
	data->factory_mode_len = 0;
	data->reset_frp = NULL;
	data->reset_frp_len = 0;
	data->sl_signature = NULL;
	data->sl_signature_len = 0;
	data->sl_data = NULL;
	data->sl_data_len = 0;
	data->auth_channel_cmd = NULL;
	data->auth_channel_cmd_len = 0;
	data->urand = NULL;
	data->urand_len = 0;
	data->reset_detect = 0;
	data->usb_vbus_detect = 0;
	data->usb_otg_detect = 0;
	data->boot_into_recovery = 0;
	data->pwr_button_pressed = 0;
	data->vldwn_button_pressed = 0;
	data->vlup_button_pressed = 0;
	data->export_hwstate = export_hwstate;
	data->context.functions = (struct integration_func *)&intemul_func;
	data->context.log = log;
	clock_gettime(CLOCK_REALTIME, &(data->start_boot));
	data->led = XBPAL_LED_TURN_OFF;

	data->core_context.functions =
		(struct integration_core_func *)&intemul_core_func;
	data->ta_context.functions =
		(struct integration_ta_func *)&intemul_ta_func;
	data->nv_context.functions =
		(struct integration_nv_func *)&intemul_nv_func;
	data->eroot_context.functions =
		(struct integration_eroot_func *)&intemul_eroot_func;
	data->xbpal_context.functions =
		(struct integration_xbpal_func *)&intemul_xbpal_func;
	data->xflattest_context.functions =
		(struct integration_xflattest_func *)&intemul_xflattest_func;

	pthread_mutex_init(&(data->mutex), NULL);
	pthread_cond_init(&(data->cond), NULL);
	res = pthread_create(
		&(data->timer_thread),
		NULL,
		timer_thread_function,
		(void *)data);
	if (res) {
		free(data);
		return -FCSERR_ENOMEM;
	}

	g_integration_context_ptr = &(data->context);
	g_integration_core_context_ptr = &(data->core_context);
	g_integration_ta_context_ptr = &(data->ta_context);
	g_integration_nv_context_ptr = &(data->nv_context);
	g_integration_eroot_context_ptr = &(data->eroot_context);
	g_integration_xbpal_context_ptr = &(data->xbpal_context);
	g_integration_xflattest_context_ptr = &(data->xflattest_context);

	if (NULL != state) {
		data->startup_flags = state->startup_flags;
		data->wb_reason = state->wb_reason;
		data->reset_detect = state->reset_detect;
		data->usb_vbus_detect = state->usb_vbus_detect;
		data->usb_otg_detect = state->usb_otg_detect;
		if (state->pwr_button_pressed_time > 0) {
			data->pwr_button_pressed = 1;
			g_release_pwr_button_info.intdata = data;
			res = timer_set(
				data,
				&(g_release_pwr_button_info.ctx),
				release_pwr_button_cb,
				state->pwr_button_pressed_time,
				&g_release_pwr_button_info);
			if (res != FCSERR_OK) {
				printf("register timer failed with %d\n", res);
				return res;
			}
		}
		if (state->vldwn_button_pressed_time > 0) {
			data->vldwn_button_pressed = 1;
			g_release_vldwn_button_info.intdata = data;
			res = timer_set(
				data,
				&(g_release_vldwn_button_info.ctx),
				release_vldwn_button_cb,
				state->vldwn_button_pressed_time,
				&g_release_vldwn_button_info);
			if (res != FCSERR_OK) {
				printf("register timer failed with %d\n", res);
				return res;
			}
		}
		if (state->vlup_button_pressed_time > 0) {
			data->vlup_button_pressed = 1;
			g_release_vlup_button_info.intdata = data;
			res = timer_set(
				data,
				&(g_release_vlup_button_info.ctx),
				release_vlup_button_cb,
				state->vlup_button_pressed_time,
				&g_release_vlup_button_info);
			if (res != FCSERR_OK) {
				printf("register timer failed with %d\n", res);
				return res;
			}
		}
	}

	integration_log("Integration is setup\n");

	return FCSERR_OK;
}

void integration_emulator_teardown(void)
{
	struct intemul_data *data = NULL;
	void *thread_res;

	if (NULL != g_integration_context_ptr) {
		data = (struct intemul_data *)
			fcstest_container_of(g_integration_context_ptr,
					struct intemul_data,
					context);

		pthread_cancel(data->timer_thread);
		pthread_join(data->timer_thread, &thread_res);
		free(data->dev_id);
		free(data->hwconfig);
		free(data->miscDK);
		free(data->ks);
		free(data->ksbak);
		free(data->hmac_key_low);
		free(data->hmac_key_high);
		free(data->sw_version);
		free(data->ta_version);
		free(data->boot_config);
		free(data->factory_mode);
		free(data->reset_frp);
		free(data->sl_signature);
		free(data->sl_data);
		free(data->auth_channel_cmd);
		free(data->urand);
		free(data);
	}
	g_integration_context_ptr = NULL;
	g_integration_core_context_ptr = NULL;
	g_integration_ta_context_ptr = NULL;
	g_integration_nv_context_ptr = NULL;
	g_integration_eroot_context_ptr = NULL;
	g_integration_xbpal_context_ptr = NULL;
	g_integration_xflattest_context_ptr = NULL;
}

