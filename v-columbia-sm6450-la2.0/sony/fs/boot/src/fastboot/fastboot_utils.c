/*
 * Copyright (C) 2020 Sony Mobile Communications Inc.
 * All rights, including trade secret rights, reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include "fcslist.h"
#include "fcserr.h"
#include "fcslog_ta.h"
#include "fcsenv_def.h"
#include "core.h"
#include "convert.h"    /* bin_to_ascii */
#include "fastboot_utils.h"
#include "protocol_utils.h"
#include "sec_data_utils.h"
#include "digest_types.h"
#include "ks.h"
#include "ks_util.h"
#include "authenticate.h"
#include "xflattest_int.h"    /* read_suid_data in fastboot_get_suid */
#include "xboot_pal_types.h"
#include <Library/BaseLib.h>


/* copied form edk2/abl/QcomModulePkg/Include/Library/PartitionTableUpdate.h */
#define MAX_GPT_NAME_SIZE (72 / 2)

/* copied form edk2/abl/StdLib/Include/X64/machine/int_fmtio.h */
#define PRIu64  "llu"    /* uint64_t        */

/*
 * This constant is used for the size of the variable value in handle_getvar().
 * We subtract with 4 because each response begins with "OKAY", "INFO", "FAIL"
 * or "DATA".
 * We add 1 to the size to be able to handle null terminated strings in the
 * variable value. (When the fastboot buffer is sent over USB and the buffer
 * is full, then it does not need to be null terminated.)
 */


#define MAX_RETRY_COUNT 5

struct fastboot_variable_entry {
    char *name;
    int (*get_value)(char *val);
    struct list_entry list;
};

static LIST(fastboot_var_list);


/*
 * Extract the argument from the command:
 * E g: <cmd>:<arg>
 * Return empty string if there is no <arg> in the command
 */
char *
get_string_arg_from_cmd(const char *cmd_name, const uint8_t *cmd)
{
    char *str = NULL;
    size_t str_len;

    if (!cmd_name || !cmd) {
        FCS_LOG_ERR("Invalid argument\n");
        return NULL;
    }

    /* Make sure we parse the right command */
    if (strncmp(cmd_name, (char *)cmd, strlen(cmd_name)))
        return NULL;
    /* Are there arguments after the command? */
    if (strlen((char *)cmd) >= strlen(cmd_name))
        str_len = strlen((char *)cmd) - strlen(cmd_name);
    else {
        FCS_LOG_ERR("Input value fail\n");
        return NULL;
    }

    /* Allocate argument string and copy argument to it */
    str = (char *)malloc(str_len + 1);
    if (str == NULL) {
        FCS_LOG_ERR("Out of memory\n");
        return NULL;
    }

    strlcpy(str, (char *)cmd+strlen(cmd_name),
            str_len + 1);

    /* Get rid of the ':' if there is one */
    if (str[0] == ':')
        strlcpy(str, &str[1], str_len + 1);

    return str;
}

int
extract_partition_and_unit(const uint8_t *arg,
        uint8_t *partition,
        uint32_t *unit)
{
    int res = FCSERR_OK;
    char buf[20];
    char *endptr;
    long value;

    if (!arg || !partition || !unit) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    /* First argument should be a partition between 0-9 */

    if (arg[0] < '0' || arg[0] > '9') {
        res = -FCSERR_EINVAL;
        return res;
    }

    *partition = arg[0] - '0';

    /* Next character should be ':' */
    if (arg[1] != ':') {
        res = -FCSERR_EINVAL;
        return res;
    }

    /* Next 1-5 characters should be unit number in decimal */
    /* Make sure we have a null terminated string */
    strlcpy(buf, (const char *)&arg[2], sizeof(buf));

    errno = 0;    /* To distinguish success/failure after call */
    /* Convert to integer */
    value = strtol(buf, &endptr, 10);

    /* Check for various possible errors */
    if ((errno == ERANGE && (value == LONG_MAX || value == LONG_MIN)) ||
        (errno != 0 && value == 0)) {
        res = -FCSERR_EINVAL;
        return res;
    }

    if (endptr == buf) {
        /* No digits were found */
        res = -FCSERR_EINVAL;
        return res;
    }

    *unit = (uint32_t) value;
    return res;
}

static int
partman_has_slot(const char *part_name, bool *has_slot)
{
    int res = FCSERR_OK;
    bool found_a = false;
    bool found_b = false;
    bool found_part_name = false;
    size_t part_name_len;
    uint64_t part_data_sz = 0;
    uint64_t part_data_sz_a = 0;
    uint64_t part_data_sz_b = 0;
    CHAR16 pname[MAX_GPT_NAME_SIZE] = {0};
    CHAR16 pname_a[MAX_GPT_NAME_SIZE] = {0};
    CHAR16 pname_b[MAX_GPT_NAME_SIZE] = {0};

    if (!part_name || !has_slot) {
        FCS_LOG_ERR("Invalid input values\n");
        return -FCSERR_EINVAL;
    }

    part_name_len = strlen(part_name);
    if (part_name_len < 2 || part_name_len > PATH_MAX - 2) {
        FCS_LOG_ERR("Bad partition name %s\n", part_name);
        return -FCSERR_EINVAL;
    }

    *has_slot = false;

    AsciiStrToUnicodeStr(part_name, pname);
    StrnCpyS(pname_a, MAX_GPT_NAME_SIZE, pname, StrLen(pname));
    StrnCpyS(pname_b, MAX_GPT_NAME_SIZE, pname, StrLen(pname));
    StrnCatS(pname_a, MAX_GPT_NAME_SIZE, L"_a", StrLen(L"_a"));
    StrnCatS(pname_b, MAX_GPT_NAME_SIZE, L"_b", StrLen(L"_b"));

    /* Whether partition exists */
    xbpal_get_partition_size(&part_data_sz, pname);
    if (part_data_sz > 0) {
        found_part_name = true;
    }

    /* Whether slot_a exists */
    xbpal_get_partition_size(&part_data_sz_a, pname_a);
    if (part_data_sz_a > 0) {
        found_a = true;
    }

    /* Whether slot_b exists */
    xbpal_get_partition_size(&part_data_sz_b, pname_b);
    if (part_data_sz_b > 0) {
        found_b = true;
    }

    if (found_a && found_b) {
        *has_slot = true;
    }

    /* Invalid partition, return error */
    if (!found_part_name && !*has_slot) {
        FCS_LOG_WRN("Partition does not exist\n");
        res = -FCSERR_ENOTF;
    }

    return res;

}

int
fastboot_get_has_slot(const char *partition, char *val)
{
    int res;
    bool has_slot = false;

    if (!partition || !val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    res = partman_has_slot(partition, &has_slot);

    if (has_slot) {
        strlcpy(val, "yes", GETVAR_VALUE_SIZE);
    } else if (!has_slot && res == FCSERR_OK) {
        strlcpy(val, "no", GETVAR_VALUE_SIZE);
    } else if (!has_slot && res == -FCSERR_ENOTF) {
        snprintf(val, GETVAR_VALUE_SIZE,
            "Partition %s does not exist", partition);
        res = FCSERR_OK;
    }

    return res;
}

static int
fastboot_get_version(char *val)
{
    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    strlcpy(val, FB_VERSION, GETVAR_VALUE_SIZE);
    return FCSERR_OK;
}

static int
fastboot_get_sonyversion(char *val)
{
    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    strlcpy(val, FB_SONY_VERSION, GETVAR_VALUE_SIZE);
    return FCSERR_OK;
}

static int
fastboot_get_sector_size(char *val)
{
    return core_get_sector_size(val, GETVAR_VALUE_SIZE);
}

static int
fastboot_get_usb_version(char *val)
{
    return core_get_usb_version(val, GETVAR_VALUE_SIZE);
}

int
fastboot_get_loaderversion(char *val)
{
    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    char *xboot_version_string = NULL;
    /*
    * Obtain XBOOT version string
    */
    if ((xbpal_get_version_string(&xboot_version_string) != FCSERR_OK)){
        FCS_LOG_ERR("Failed to get xboot version\n");
        return -FCSERR_ESTATE;
    }
    snprintf(val, GETVAR_VALUE_SIZE, "%s", xboot_version_string);
    return FCSERR_OK;
}

static int
fastboot_get_phoneid(char *val)
{
    return get_phone_id(val, GETVAR_VALUE_SIZE);
}

static int
fastboot_get_deviceid(char *val)
{
    uint8_t bbuf[(GETVAR_VALUE_SIZE - 1) / 2];
    int res = core_get_dieid(bbuf, sizeof(bbuf));

    if (res != FCSERR_OK)
        return res;

    res = bin_to_ascii(val, GETVAR_VALUE_SIZE, bbuf, core_get_dieid_len());

    return res;
}

static int
fastboot_get_rootingstatus(char *val)
{
    return get_rooting_status_string(val, GETVAR_VALUE_SIZE);
}

static int
fastboot_get_storage_info(char *val)
{
    return core_get_storage_info(val, GETVAR_VALUE_SIZE);
}

static int
fastboot_get_default_security(char *val)
{
    int res = FCSERR_OK;

    res = get_default_security(val, GETVAR_VALUE_SIZE);

    if (res < 0)
        FCS_LOG_ERR("Failed to get default security\n");

    return res;
}

static int
fastboot_get_platformid(char *val)
{
    uint8_t bbuf[(GETVAR_VALUE_SIZE - 1) / 2];
    int res = core_get_platformid(bbuf, sizeof(bbuf));

    if (res != FCSERR_OK)
        return res;

    res = bin_to_ascii(
        val, GETVAR_VALUE_SIZE, bbuf, core_get_platformid_len());

    return res;
}

static int
fastboot_get_keystore_counter(char *val)
{
    int res = FCSERR_OK;
    uint32_t ks_counter;
    int retry_cnt = MAX_RETRY_COUNT;

    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    do {
        res = sec_data_get_ks_counter(&ks_counter);
        if (res == FCSERR_OK) {
            break;
        } else {
            FCS_LOG_ERR("Retry get keystore counter\n");
            retry_cnt--;
        }
    } while (retry_cnt > 0);

    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get keystore counter\n");
        return res;
    }

    snprintf(val, GETVAR_VALUE_SIZE, "%u", ks_counter);

    return res;
}

static int
fastboot_get_security_state(char *val)
{
    int res = FCSERR_OK;
    struct ks_ctx *ks_ctx = NULL;
    uint8_t sha256hash[SHA256_HASH_OUT_SIZE];
    uint8_t *hmac_key = NULL;
    uint32_t hmac_key_len = 0;
    int retry_cnt = MAX_RETRY_COUNT;

    res = core_get_hmac_key(&hmac_key, &hmac_key_len);
    if (res != FCSERR_OK) {
        hmac_key = NULL;
        hmac_key_len = 0;
        FCS_LOG_INF("Can't get hmac key: (%d)\n", res);
    }

    do {
        res = ksutil_keystore_init(&ks_ctx, true, XFLKEYSTORE_PRIM,
                hmac_key, hmac_key_len);
        if (res == FCSERR_OK) {
            break;
        } else {
            FCS_LOG_ERR("Retry hmac key\n");
            retry_cnt--;
        }
    } while (retry_cnt > 0);

    if (res != FCSERR_OK) {
        FCS_LOG_ERR("keystore init failed: (%d)\n", res);
        goto exit;
    }

    res = ks_get_hash(ks_ctx, sha256hash, SHA256_HASH_OUT_SIZE);
    if (res < 0) {
        FCS_LOG_ERR("Failed to get keystore hash (%d)\n", res);
        goto exit;
    }

    res = base64_encode(sha256hash,
                SHA256_HASH_OUT_SIZE,
                val,
                GETVAR_VALUE_SIZE);

exit:
    free(hmac_key);
    ks_destroy(ks_ctx);
    return res;
}

static int
fastboot_get_s1_root(char *val)
{
    int res = FCSERR_OK;

    res = get_s1_root(val, GETVAR_VALUE_SIZE);

    if (res < 0)
        FCS_LOG_ERR("Failed to get S1_Root\n");

    return res;
}

static int
fastboot_get_sake_root(char *val)
{
    struct authenticate_ctx *auth_ctx = NULL;
    int res = FCSERR_OK;

    char xboot_version_string[GETVAR_VALUE_SIZE];
    res = fastboot_get_loaderversion(xboot_version_string);
    if(res != FCSERR_OK){
        goto exit;
    }

    res = authenticate_init(&auth_ctx, SAKE_SSN_PRODUCTION,
                xboot_version_string, strlen(xboot_version_string));

    if (res != FCSERR_OK) {
        res = -FCSERR_ESTATE;
        goto exit;
    }

    res = authenticate_get_sake_root_name(
            &auth_ctx, val, GETVAR_VALUE_SIZE);
exit:
    authenticate_destroy(auth_ctx);
    return res;
}

static int
fastboot_get_battery_capacity(char *val)
{
    return core_get_battery_capacity(val, GETVAR_VALUE_SIZE);
}

static int
fastboot_get_frp_partition(char *val)
{
    strlcpy(val, FRP_PARTITION_NAME, GETVAR_VALUE_SIZE);
    return FCSERR_OK;
}

static int
fastboot_get_stored_security_state(char *val)
{
    int res = FCSERR_OK;
    uint8_t sha256hash[SHA256_HASH_OUT_SIZE];

    res = sec_data_get_keystore_hash(sha256hash, SHA256_HASH_OUT_SIZE);

    if (res == FCSERR_OK)
        res = base64_encode(sha256hash,
                SHA256_HASH_OUT_SIZE,
                val,
                GETVAR_VALUE_SIZE);

    return res;
}

static int
fastboot_get_keystore_xcs(char *val)
{
    int res = FCSERR_OK;
    uint32_t is_xcs_rot;

    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    res = sec_data_get_xcs_rot(&is_xcs_rot);

    if (res != FCSERR_OK) {
        FCS_LOG_INF("Failed to get xcs rot\n");
        return res;
    }

    snprintf(val, GETVAR_VALUE_SIZE, "%s", is_xcs_rot ? "yes" : "no");

    return res;
}

static int
fastboot_get_x_conf(char *val)
{
    uint8_t hash[4]; /* maximum 2 roots included */
    int res;
    int nroots;

    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    res = get_x_conf_root_hash(hash, sizeof(hash), &nroots);
    if (res != FCSERR_OK)
        return res;

    /* due to legacy requirements the test root (if available) needs to be
     * written first and get_x_conf_root_hash will output in reverse order,
     * so make the switch if needed here
     */
    snprintf(val, GETVAR_VALUE_SIZE, "%02x%02x",
         hash[2 * (nroots - 1)], hash[2 * (nroots - 1) + 1]);
    if (nroots == 2)
        snprintf(val + 4, GETVAR_VALUE_SIZE, ",%02x%02x",
             hash[0], hash[1]);

    return FCSERR_OK;
}

static int
fastboot_get_suid(char *val)
{
    int res;
    uint8_t bbuf[(GETVAR_VALUE_SIZE - 1) / 2];

    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    res = read_suid_data(bbuf, sizeof(bbuf));
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to read suid from RPMB (%d)\n", res);
        return res;
    }

    res = bin_to_ascii(val, GETVAR_VALUE_SIZE, bbuf, get_suid_len());

    return res;
}

static int
fastboot_get_has_been_unlocked(char *val)
{
    int res;
    uint32_t has_been_unlocked;

    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    res = sec_data_get_has_been_unlocked(&has_been_unlocked);

    if (res != FCSERR_OK) {
        FCS_LOG_INF("Failed to get has_been_unlocked flag\n");
        return res;
    }

    snprintf(val, GETVAR_VALUE_SIZE, "%s",
            has_been_unlocked == HAS_BEEN_UNLOCKED_MAGIC ?
            "yes" : "no");

    return FCSERR_OK;
}

static int
fastboot_get_rollback_index_count(char *val)
{
    if (!val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }
    snprintf(val, GETVAR_VALUE_SIZE, "%u",
         sec_data_get_num_rollback_counters());
    return FCSERR_OK;
}

static int
fastboot_get_rollback_counter(const char *index, char *val)
{
    int res;
    uint32_t rb_index;
    uint64_t rb_cnt_val;

    if (!index || !val) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    rb_index = strtol(index, NULL, 10);

    res = sec_data_get_rollback_counter(rb_index, &rb_cnt_val);
    if (res != FCSERR_OK)
        return res;

    snprintf(val, GETVAR_VALUE_SIZE, "%" PRIu64, rb_cnt_val);
    return res;
}

int
fastboot_add_func(const char *name, int (*func)(char *val))
{
    struct fastboot_variable_entry *ent;
    size_t name_size;

    if (!name || !func) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    if (!list_empty(&fastboot_var_list)) {
        LIST_FOR_EACH_DATA(&fastboot_var_list, ent, list) {
            if (strncmp(ent->name, name,
                    strlen(ent->name)+1) == 0) {
                FCS_LOG_ERR("Variable already defined\n");
                return -FCSERR_EINVAL;
            }
        }
    }

    ent = calloc(1, sizeof(struct fastboot_variable_entry));
    if (!ent) {
        FCS_LOG_ERR("Unable to allocate memory\n");
        return -FCSERR_ENOMEM;
    }
    name_size = strlen(name) + 1;
    ent->name = calloc(1, name_size);
    if (!ent->name) {
        free(ent);
        FCS_LOG_ERR("Unable to allocate memory\n");
        return -FCSERR_ENOMEM;
    }

    strlcpy(ent->name, name, name_size);
    ent->get_value = func;

    list_add_tail(&fastboot_var_list, &ent->list);

    return FCSERR_OK;
}


int
fastboot_get_variable(const char *getvar_var_name, char *value)
{
    struct fastboot_variable_entry *var;
    char *partition;
    char *index;
    int res = -FCSERR_ENOTF;

    if (!getvar_var_name || !value) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    if (list_empty(&fastboot_var_list)) {
        FCS_LOG_ERR("List empty\n");
        return -FCSERR_ESTATE;
    }

    LIST_FOR_EACH_DATA(&fastboot_var_list, var, list) {
        if (strncmp(getvar_var_name, var->name,
                strlen(var->name)+1) == 0) {
            return var->get_value(value);
        }
    }

    /* has-slot
     * can be asked for any partition
     *
     * Rollback-index is parameterized.
     */
    if (strncmp(getvar_var_name, "has-slot:",
                strlen("has-slot:")) == 0) {
        partition = get_string_arg_from_cmd("has-slot:",
            (uint8_t *)getvar_var_name);
        if (partition) {
            res = fastboot_get_has_slot(partition, value);
            free(partition);
        }
        return res;
    } else if (strncmp(getvar_var_name, "Rollback-index:",
                strlen("Rollback-index:")) == 0) {
        index = get_string_arg_from_cmd("Rollback-index:",
            (uint8_t *)getvar_var_name);
        if (index) {
            res = fastboot_get_rollback_counter(index, value);
            free(index);
        }
        return res;
    }

    /* Failed to find variable in list */
    FCS_LOG_ERR("%s: Could not find variable %s\n", __func__,
        getvar_var_name);
    return -FCSERR_ENOTF;
}

int
fastboot_get_x_variable_list(X_FASTBOOT_VAR **x_fastboot_var)
{
    struct fastboot_variable_entry *var;
    X_FASTBOOT_VAR *XVarList;
    X_FASTBOOT_VAR *XVar;
    char name[MAX_GET_VAR_NAME_SIZE];
    char value[GETVAR_VALUE_SIZE];
    uint32_t rb_index;
    uint64_t rb_cnt_val;
    uint32_t num_rollback_counters = sec_data_get_num_rollback_counters();

    /* SOMC Variable */
    if (list_empty(&fastboot_var_list)) {
        FCS_LOG_ERR("List empty\n");
        return -FCSERR_ESTATE;
    }

    if (x_fastboot_var == NULL) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    *x_fastboot_var = (X_FASTBOOT_VAR *)malloc(sizeof (X_FASTBOOT_VAR));
    if (*x_fastboot_var == NULL) {
        FCS_LOG_ERR("x_fastboot_var malloc error!\n");
        return -FCSERR_ESTATE;
    }
    XVarList = *x_fastboot_var;

    LIST_FOR_EACH_DATA(&fastboot_var_list, var, list) {
        if (var->get_value(value) != FCSERR_OK) {
            FCS_LOG_ERR("get_value failed for %s\n", var->name);
            continue;
        }
        XVar = (X_FASTBOOT_VAR *)malloc(sizeof (X_FASTBOOT_VAR));
        if (XVar == NULL) {
            FCS_LOG_ERR("XVar malloc error!\n");
            return -FCSERR_ESTATE;
        }
        XVarList->next = XVar;
        strlcpy(XVarList->name, var->name, MAX_GET_VAR_NAME_SIZE);
        strlcpy(XVarList->value, value, GETVAR_VALUE_SIZE);
        XVarList = XVar;
    }
    /* Rollback Index */
    for (rb_index = 0; rb_index < num_rollback_counters; rb_index++) {
        if (sec_data_get_rollback_counter(rb_index, &rb_cnt_val) != FCSERR_OK) {
            FCS_LOG_ERR("sec_data_get_rollback_counter failed\n");
            return -FCSERR_ESTATE;
        }
        XVar = (X_FASTBOOT_VAR *)malloc(sizeof (X_FASTBOOT_VAR));
        if (XVar == NULL) {
            FCS_LOG_ERR("XVar malloc error!\n");
            return -FCSERR_ESTATE;
        }
        XVarList->next = XVar;
        snprintf(name, MAX_GET_VAR_NAME_SIZE, "Rollback-index:%u", rb_index);
        strlcpy(XVarList->name, name, MAX_GET_VAR_NAME_SIZE);
        snprintf(value, GETVAR_VALUE_SIZE, "%" PRIu64, rb_cnt_val);
        strlcpy(XVarList->value, value, GETVAR_VALUE_SIZE);
        XVarList = XVar;
    }
    XVarList->next = NULL;
    XVarList->name[0] = '\0';
    XVarList->value[0] = '\0';
    return FCSERR_OK;
}

void
fastboot_x_variable_list_free(X_FASTBOOT_VAR *x_fastboot_var)
{
    X_FASTBOOT_VAR *XVarNext;

    while(x_fastboot_var != NULL) {
        XVarNext = x_fastboot_var->next;
        free(x_fastboot_var);
        x_fastboot_var = XVarNext;
    }
}

void
fastboot_init_getvar(void)
{
    fastboot_add_func("version", fastboot_get_version);
    fastboot_add_func("Version-sony", fastboot_get_sonyversion);
    fastboot_add_func("Sector-size", fastboot_get_sector_size);
    fastboot_add_func("USB-version", fastboot_get_usb_version);
    fastboot_add_func("Loader-version", fastboot_get_loaderversion);
    fastboot_add_func("Phone-id", fastboot_get_phoneid);
    fastboot_add_func("Device-id", fastboot_get_deviceid);
    fastboot_add_func("Rooting-status", fastboot_get_rootingstatus);
    if (strncmp(FLASH_TYPE, "UFS", strlen("UFS") + 1) == 0)
        fastboot_add_func("Ufs-info", fastboot_get_storage_info);
    if (strncmp(FLASH_TYPE, "eMMC", strlen("eMMC") + 1) == 0)
        fastboot_add_func("Emmc-info", fastboot_get_storage_info);
    fastboot_add_func("Default-security", fastboot_get_default_security);
    fastboot_add_func("Platform-id", fastboot_get_platformid);
    fastboot_add_func("Keystore-counter", fastboot_get_keystore_counter);
    fastboot_add_func("Security-state", fastboot_get_security_state);
    fastboot_add_func("S1-root", fastboot_get_s1_root);
    fastboot_add_func("Sake-root", fastboot_get_sake_root);
    fastboot_add_func("Battery", fastboot_get_battery_capacity);
    fastboot_add_func("Frp-partition", fastboot_get_frp_partition);
    fastboot_add_func("Stored-security-state",
        fastboot_get_stored_security_state);
    fastboot_add_func("Keystore-xcs", fastboot_get_keystore_xcs);
    fastboot_add_func("X-conf", fastboot_get_x_conf);
    fastboot_add_func("Soc-unique-id", fastboot_get_suid);
    fastboot_add_func("Has-been-unlocked", fastboot_get_has_been_unlocked);
    fastboot_add_func("Rollback-index-count",
        fastboot_get_rollback_index_count);
}


bool fastboot_get_secure(void)
{
    int res = FCSERR_OK;
    char val[GETVAR_VALUE_SIZE];

    res = fastboot_get_secure_state(val, GETVAR_VALUE_SIZE);
    if(res == FCSERR_OK){
        if (strncmp(val, "yes", strlen("yes")) == 0){
            return TRUE;
        }else{
            return FALSE;
        }
    }
    return FALSE;
}
