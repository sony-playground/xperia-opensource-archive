/*
 * Copyright 2020, 2022 Sony Corporation.
 * All rights, including trade secret rights, reserved.
 */

/*
 * Protocol help functions
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <errno.h>
#include "sec_data_utils.h"
#include "fcslog.h"
#include "fcserr.h"
#include "fcs_defines.h"
#include "ta_interface.h"
#include "hwconf.h"
#include "fcsenv_def.h"
#include "fcs_fastboot_partitions.h"
#include "rooting_status.h"
#include "fcslist.h"
#include "protocol_utils.h"
#include "fastboot_utils.h"
#include "xboot_pal_types.h"
#include "authenticate.h"
#include "fcs_fastboot_partitions.h"
#include <eroot.h>
#include <core.h>
#include <cryp_util.h>
#include <digest.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
/* Constants for parsing S1_Roots */
#define CN_LEN_IDX 43
#define CN_IDX 44

#define FCSERR_EONE     (1)    /* for functions typically returning ssize_t */

/* copied form edk2/abl/QcomModulePkg/Include/Library/PartitionTableUpdate.h */
#define MAX_GPT_NAME_SIZE 72

/* copied from edk2/abl/QcomModulePkg/Include/Library/LinuxLoaderLib.h */
/* Macro to avoid integer overflow */
#define ADD_OF(a, b) (MAX_UINT32 - b > a) ? (a + b) : 0

/* copied from edk2/abl/QcomModulePkg/Include/Library/BootLinux.h */
#define ROUND_TO_PAGE(x,y) ((ADD_OF((x),(y))) & (~(y)))

/* copied from fcs/main/loader/protocol/protocol_util.c */
#define PU_DIGEST_CHUNK (8 * 1024 * 1024)

struct cms_valid_sin_entry {
    char *part_name;
    struct transport_verifier *transport_handle;
    struct list_entry list;
};

static LIST(cms_valid_sin);
static const char *VIRTPART_REPART = "partitionimage";

static int init_hwconfig(hwconfig_t *handle_p)
{
    int res = FCSERR_OK;
    size_t devid_len = 0;
    uint8_t *devid = NULL;
    struct embed_rootcert_item *embed_rootcert_list = NULL;
    size_t embed_rootcert_list_count = 0;

    devid_len = core_get_dieid_len();

    devid = malloc(devid_len);
    if (devid == NULL) {
        FCS_LOG_ERR("Out of memory\n");
        res = -FCSERR_ENOMEM;
        goto endfunction_init_hwconfig;
    }

    res = core_get_dieid(devid, devid_len);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get dev id from env: (%d)\n", res);
        goto endfunction_init_hwconfig;
    }

    res = get_embedded_roots(
        &embed_rootcert_list, &embed_rootcert_list_count);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
            res);
        goto endfunction_init_hwconfig;
    }

    res = setup_hwconfig(devid, devid_len,
            embed_rootcert_list, embed_rootcert_list_count,
            handle_p);

endfunction_init_hwconfig:
    free_embedded_roots(&embed_rootcert_list);
    free(devid);
    return res;
}

/*
 * Get data from miscta unit <ta_unit>. <buf> will be
 * null terminated and populated with data from <ta_unit> up
 * to max <buf_size>
 */
int get_miscta_unit_data(int ta_unit, char *buf, int buf_size)
{
    int res = FCSERR_OK;
    uint8_t *ta_buf = NULL;
    int ta_buf_size = 0;

    if (!buf || (buf_size < 1)) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    /* Get size of unit */
    res = get_ta_unit_size(TA_MISC_PART, ta_unit, &ta_buf_size);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Invalid unit (%d), error=%d\n", TA_MSN_UNIT, res);
        return res;
    }

    ta_buf = malloc(ta_buf_size);

    if (ta_buf == NULL) {
        FCS_LOG_ERR("Out of memory\n");
        return -FCSERR_ENOMEM;
    }

    res = read_ta(TA_MISC_PART, ta_unit, ta_buf, ta_buf_size);
    if (res != FCSERR_OK) {
        FCS_LOG_INF("Unable to read TA unit %d, error=%d\n",
            ta_unit, res);
        /* If unit is not found return an empty string and FCSERR_OK */
        buf[0] = '\0';
        free(ta_buf);
        return FCSERR_OK;
    }

    memcpy(buf, ta_buf, MIN(buf_size - 1, ta_buf_size));
    buf[MIN(buf_size - 1, ta_buf_size)] = 0;

    free(ta_buf);
    return res;
}

/*
 * Read phone id from HWConfig and return the result in <buf> which has
 * size <buf_size>. Result is converted to ASCII and the resulting string is
 * null terminated. Format: 0000:<imei_1>[,0000:<imei_2>]
 * Returns a FCSERR_x code.
 */
int get_phone_id(char *buf, int buf_size)
{
    int res = FCSERR_OK;
    unsigned int i, j;
    uint8_t imei_count = 0;
    size_t imei_length = 0;
    uint8_t *parse_buff = NULL;
    char ascii_buff[32];
    hwconfig_t hwconf = NULL;

    if (buf == NULL) {
        FCS_LOG_ERR("Invalid argument, buf is NULL\n");
        res = -FCSERR_EINVAL;
        goto exit;
    }

    buf[0] = '\0';

    res = init_hwconfig(&hwconf);
    if (res) {
        FCS_LOG_ERR("hwconfig init failed (%d)\n", res);
        goto exit;
    }

    res = get_imei_count(&imei_count, hwconf);
    if (res) {
        FCS_LOG_ERR("get_imei_count failed (%d)\n", res);
        goto exit;
    }

    /*
     * "," + "0000:" => 6 bytes
     * Hexstring => 2 * MAX_PHONEID_SIZE
     */
    if (imei_count * (6 + 2 * MAX_PHONEID_SIZE) + 1 > buf_size) {
        FCS_LOG_ERR("Buffer to small\n");
        res = -FCSERR_EINVAL;
        goto exit;
    }

    for (i = 0; i < imei_count; i++) {

        parse_buff = calloc(1, MAX_PHONEID_SIZE + 1);
        if (!parse_buff) {
            FCS_LOG_ERR("Unable to allocate buffer for IMEI id\n");
            res = -FCSERR_ENOMEM;
            goto exit;
        }

        res = get_imei(i, parse_buff, MAX_PHONEID_SIZE + 1,
                &imei_length, hwconf);
        if (res != FCSERR_OK) {
            FCS_LOG_ERR("Unable to parse phone id, error=%d\n",
                res);
            goto exit;
        }

        strlcat(buf, "0000:", buf_size);

        /*
         * Reads 1 byte at a time and converts it to 2 ascii chars and
         * stores it in same buf. Skip last byte of imei.
         */
        for (j = 0; j < imei_length - 1; j++)
            snprintf(&ascii_buff[j * 2], 3, "%02X",
                *(parse_buff+j));

        ascii_buff[j * 2 + 1] = '\0';
        strlcat(buf, ascii_buff, buf_size);

        /* If more IMEI records exists */
        if ((i + 1) < imei_count)
            strlcat(buf, ",", buf_size);

        free(parse_buff);
        parse_buff = NULL;
    }

exit:
    if (hwconf)
        teardown_hwconfig(hwconf);
    if (parse_buff)
        free(parse_buff);

    return res;
}

int get_s1_root(char *buf, size_t buf_size)
{
    int res = FCSERR_OK;
    int i, index = 0;

    struct embed_rootcert_item *eroot_list = NULL;
    size_t eroot_count = 0;

    if (buf == NULL || buf_size == 0) {
        FCS_LOG_ERR("Invalid input parameters\n");
        return -FCSERR_EINVAL;
    }

    res = get_embedded_roots(
        &eroot_list, &eroot_count);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
            res);
        goto exit;
    }

    for (i = 0; i < (int)eroot_count; i++) {
        /* Locate the S1_Roots */
        if (eroot_list[i].cert_domain_flags & CERT_DOMAIN_S1) {
            /* Make sure there's room for a S1_ROOT CN */
            if (index + eroot_list[i].rootcerts[CN_LEN_IDX] >=
                    (int)buf_size) {
                FCS_LOG_ERR("Buffer too small\n");
                res = -FCSERR_EINVAL;
                goto exit;
            }
            if (index != 0) {
                /* If more than one root separate them with , */
                buf[index++] = ',';
            }
            memcpy(&buf[index],
                    &eroot_list[i].rootcerts[CN_IDX],
                    eroot_list[i].rootcerts[CN_LEN_IDX]);

            index += eroot_list[i].rootcerts[CN_LEN_IDX];
            buf[index] = '\0';
        }
    }

    if (index == 0) {
        FCS_LOG_ERR("No S1-root found\n");
        res = -FCSERR_ESTATE;
        goto exit;
    }

exit:
    if (eroot_list != NULL)
        free_embedded_roots(&eroot_list);

    return res;
}

int get_x_conf_root_hash(uint8_t *buf, size_t buf_len, int *nroots)
{
    int res = FCSERR_OK;
    uint32_t i;
    uint8_t hash[DIGEST_SHA1_HASH_SIZE];

    struct embed_rootcert_item *eroot_list = NULL;
    size_t eroot_count = 0;

    uint8_t *bt = buf;

    if (buf == NULL || buf_len == 0 || nroots == NULL) {
        FCS_LOG_ERR("Invalid input parameters\n");
        return -FCSERR_EINVAL;
    }
    *nroots = 0;

    res = get_embedded_roots(&eroot_list, &eroot_count);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get embedded_roots from env: (%d)\n",
            res);
        goto exit;
    }

    for (i = 0; i < eroot_count; i++) {
        /* Locate the X config root */
        if (eroot_list[i].cert_domain_flags & CERT_DOMAIN_CONFIG) {
            res = cryp_get_pk_hash(
                eroot_list[i].rootcerts,
                eroot_list[i].rootcerts_length,
                hash, sizeof(hash));
            if (res != FCSERR_OK) {
                FCS_LOG_ERR("Get PK hash failed\n");
                goto exit;
            }
            /* copy the first 2 bytes if there is enough space */
            if ((bt - buf + 2) > (long)buf_len) {
                FCS_LOG_ERR("Buffer is too small\n");
                res = -FCSERR_EINVAL;
                goto exit;
            }

            (*nroots)++;
            memcpy(bt, hash, 2);
            bt += 2;
        }
    }

    if (*nroots == 0) {
        FCS_LOG_ERR("No root found\n");
        res = -FCSERR_ESTATE;
        goto exit;
    }

exit:
    free_embedded_roots(&eroot_list);
    return res;
}

/*
 * Populates <buf> with ASCII coded rooting status.
 * Returns a FCSERR_x code.
 */
int get_rooting_status_string(char *buf, unsigned int buf_size)
{
    int res;
    uint8_t rooting_status;
    uint32_t is_xcs_rot;
    uint8_t rck_h[RCK_H_LENGTH];

    if (!buf) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    /* Get rooting status from sec data */
    res = sec_data_get_rooting_status(&rooting_status);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
        return res;
    }

    /* Rooting is not allowed if the keystore is XCS */
    res = sec_data_get_xcs_rot(&is_xcs_rot);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get xcs rot\n");
        return res;
    }

    if (is_xcs_rot) {
        FCS_LOG_INF("Unlock not allowed with XCS keystore\n");
        rooting_status = BOOT_NOT_UNLOCKABLE;
    } else if (rooting_status != BOOT_UNLOCKED) {
        /* Recalculate rooting status based on the simlock */
        res = get_simlock_unlock_data(&rooting_status, rck_h);
        if (res != FCSERR_OK) {
            FCS_LOG_ERR("Failed to get rooting status: (%d)\n",
                    res);
            rooting_status = BOOT_NOT_UNLOCKABLE;
            res = FCSERR_OK;
        }
    }


    switch (rooting_status) {
    case BOOT_NOT_UNLOCKABLE:
        snprintf(buf, MIN(buf_size, sizeof("NOT_ROOTABLE")),
                "NOT_ROOTABLE");
        break;
    case BOOT_UNLOCKABLE:
        snprintf(buf, MIN(buf_size, sizeof("ROOTABLE")),
                "ROOTABLE");
        break;
    case BOOT_UNLOCKED:
        snprintf(buf, MIN(buf_size, sizeof("ROOTED")),
                "ROOTED");
        break;
    case BOOT_UNLOCKABLE_SIMLOCK_LOCKED:
        snprintf(buf, MIN(buf_size, sizeof("SL_ROOTABLE")),
                "SL_ROOTABLE");
        break;
    case BOOT_UNLOCKABLE_SIMLOCK_UNLOCKED:
        snprintf(buf, MIN(buf_size, sizeof("SL_UNL_ROOTABLE")),
                "SL_UNL_ROOTABLE");
        break;
    default:
        snprintf(buf, MIN(buf_size, sizeof("ERROR")), "ERROR");
        break;
    }

    return res;

}

int fastboot_get_secure_state(char *buf, size_t buf_size)
{
    int res = FCSERR_OK;
    uint8_t rooting_status;

    if (!buf) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    /* Get rooting status */
    res = sec_data_get_rooting_status(&rooting_status);
    if (res) {
        FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
        return res;
    }

    if (rooting_status == BOOT_UNLOCKED)
        snprintf(buf, MIN(buf_size, sizeof("no")), "no");
    else
        snprintf(buf, MIN(buf_size, sizeof("yes")), "yes");

    return FCSERR_OK;
}

int bootloader_unlock_allowed(uint8_t *allow_unlock, uint8_t *rooting_status)
{
    int res = FCSERR_OK;
    uint8_t ggl_allow_unlock;
    uint8_t rck_h[RCK_H_LENGTH];
    uint32_t is_xcs_rot;

    if (!allow_unlock || !rooting_status) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    *allow_unlock = 0;
    *rooting_status = BOOT_NOT_UNLOCKABLE;

    /* Get rooting status from sec data */
    res = sec_data_get_rooting_status(rooting_status);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
        return res;
    }

    /* Rooting is not allowed if the keystore is XCS */
    res = sec_data_get_xcs_rot(&is_xcs_rot);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get xcs rot\n");
        return res;
    }

    if (is_xcs_rot) {
        FCS_LOG_INF("Unlock not allowed with XCS keystore\n");
        return FCSERR_OK;
    }

    if (*rooting_status == BOOT_UNLOCKED) {
        FCS_LOG_INF("Bootloader already unlocked\n");
        return FCSERR_OK;
    }

    /* Recalculate rooting status based on the simlock */
    res = get_simlock_unlock_data(rooting_status, rck_h);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get rooting status: (%d)\n", res);
        return res;
    }

    res = google_allow_unlock(&ggl_allow_unlock);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get bootloader unlock allowed state\n");
        return res;
    }

    if (((*rooting_status != BOOT_UNLOCKABLE) &&
        (*rooting_status != BOOT_UNLOCKABLE_SIMLOCK_UNLOCKED)) ||
        !ggl_allow_unlock)
        return res;

    *allow_unlock = 1;

    return res;
}

int get_simlock_rck_h(uint8_t *rck_h)
{
    int ret;
    uint8_t unlock_status;

    ret = get_simlock_unlock_data(&unlock_status, rck_h);
    if (ret != FCSERR_OK)
        FCS_LOG_ERR("Failed to get unlock data: (%d)\n", ret);

    return ret;
}

int get_default_security(char *buf, size_t buf_size)
{
    int res = FCSERR_OK;
    bool is_fused = true;

    if (buf == NULL) {
        FCS_LOG_ERR("Invalid argument, buf is NULL\n");
        return -FCSERR_EINVAL;
    }

    res = core_is_fused(&is_fused);
    if (res < 0) {
        FCS_LOG_ERR("Failed to get fuse status\n");
        return res;
    }

    if (is_fused)
        strlcpy(buf, "ON", buf_size);
    else
        strlcpy(buf, "OFF", buf_size);

    return res;
}

int is_partition_restricted(char *partition, bool *is_restricted)
{
    int res = FCSERR_OK;
    int i;
    uint8_t rooting_status;
    bool is_fused = false;

    if (partition == NULL || is_restricted == NULL) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    *is_restricted = true;

    res = sec_data_get_rooting_status(&rooting_status);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get rooting status\n");
        return res;
    }

    if (rooting_status != BOOT_UNLOCKED) {
        FCS_LOG_INF("Bootloader is locked, partition is restricted\n");
        return FCSERR_OK;
    }

    res = core_is_fused(&is_fused);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to get fuse status\n");
        return res;
    }

    if (is_fused) {
        for (i = 0; i < no_of_allowed_ptns; i++) {
            if (strncmp(partition, allowed_ptns[i],
                    strlen(allowed_ptns[i]) + 1) == 0) {
                *is_restricted = false;
                return FCSERR_OK;
            }
        }
    } else {
        *is_restricted = false;
    }

    return FCSERR_OK;
}

int devid_to_buffer(uint8_t **outbuf, size_t *outbuf_len)
{
    int res = FCSERR_OK;
    size_t devid_len = 0;
    uint8_t *devid = NULL;

    if (!outbuf || !outbuf_len) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    devid_len = core_get_dieid_len();
    if (devid_len == 0) {
        FCS_LOG_ERR("Failed to alloc devid\n");
        res = -FCSERR_ENOMEM;
        goto devid_to_buffer_end;
    }

    devid = (uint8_t *)malloc(devid_len);
    if (devid == NULL) {
        FCS_LOG_ERR("Out of memory\n");
        res = -FCSERR_ENOMEM;
        goto devid_to_buffer_end;
    }

    res = core_get_dieid(devid, devid_len);
    if (res < 0) {
        FCS_LOG_ERR("Failed to get devid\n");
        goto devid_to_buffer_end;
    }

    *outbuf_len = devid_len;
    *outbuf = devid;
    devid = NULL;

devid_to_buffer_end:
    free(devid);
    return res;
}


static int is_slot(const char *part, bool *part_is_slot)
{
    size_t plen;

    if (!part || !part_is_slot) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    *part_is_slot = false;

    plen = strlen(part);
    if (plen < 3 || plen > PATH_MAX) {
        /* No room for slots */
        return FCSERR_OK;
    }

    if (part[plen - 2] == '_' &&
            (part[plen - 1] == 'a' || part[plen - 1] == 'b'))
        *part_is_slot = true;

    return FCSERR_OK;
}

int remove_auth_partition(const char *part)
{
    struct cms_valid_sin_entry *sin;
    bool part_is_slot;
    int res;

    if (!part) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    res = is_slot(part, &part_is_slot);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Bad input parameters\n");
        return res;
    }

    LIST_FOR_EACH_DATA(&cms_valid_sin, sin, list) {
        if (part_is_slot) {
            /* Remove partition without slot from list */
            if (!strncmp(part, sin->part_name, strlen(part) - 2))
                list_remove(&sin->list);
            /* Remove partition including slot from list */
            if (!strncmp(part, sin->part_name, strlen(part) + 1))
                list_remove(&sin->list);
        } else {
            if (!strncmp(part, sin->part_name, strlen(part) + 1))
                list_remove(&sin->list);
        }

    }

    return FCSERR_OK;
}

int add_auth_partition(const char *name,
        struct transport_verifier *transport_handle)
{
    struct cms_valid_sin_entry *ent;
    size_t part_name_size;

    if (!name) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    ent = malloc(sizeof(struct cms_valid_sin_entry));
    if (!ent) {
        FCS_LOG_ERR("Unable to allocate memory\n");
        return -FCSERR_ENOMEM;
    }

    part_name_size = strlen(name) + 1;
    ent->part_name = malloc(part_name_size);

    if (!ent->part_name) {
        free(ent);
        FCS_LOG_ERR("Unable to allocate memory\n");
        return -FCSERR_ENOMEM;
    }

    strlcpy(ent->part_name, name, part_name_size);
    ent->transport_handle = transport_handle;

    list_add_tail(&cms_valid_sin, &ent->list);

    return FCSERR_OK;
}


//#define USE_MBEDTLS
static int verify_download_sha256(struct transport_verifier *transport_handle, uint8_t *cmsbuf, size_t cmsbuf_len)
{
    int res = FCSERR_OK;
    size_t bytes_read, bytes_left;
#ifdef USE_MBEDTLS
    struct digest *dgst = NULL;
#else
    void *dgst = NULL;
#endif
    uint8_t *hash;
    uint32_t hash_len;

    if (!transport_handle) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }
    if (cmsbuf == NULL || cmsbuf_len == 0) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    bytes_left = cmsbuf_len;

#ifdef USE_MBEDTLS
    res = digest_sha256_init(&dgst);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR(
            "Fail to init download hash\n");
        goto verify_download_end;
    }
#else
    dgst = xbpal_sha256_init();
#endif

    do {
        bytes_read = cmsbuf_len;
        if (bytes_read < 0) {
            FCS_LOG_ERR("Read fail\n");
            res = -FCSERR_EIO;
            goto verify_download_end;
        }

#ifdef USE_MBEDTLS
        res = digest_sha256_update(dgst, cmsbuf, cmsbuf_len);
        if (res != FCSERR_OK) {
            FCS_LOG_ERR(
                "Fail to calculate download hash\n");
            goto verify_download_end;
        }
#else
        xbpal_sha256_update(dgst, cmsbuf, cmsbuf_len);
#endif

        bytes_left -= bytes_read;
    } while (bytes_left);

#ifdef USE_MBEDTLS
    res = digest_sha256_final(dgst, &hash, &hash_len);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR(
            "Fail to finalize download hash\n");
        goto verify_download_end;
    }
#else
    hash = xbpal_sha256_final(dgst, &hash_len);
#endif

    res = transport_verify_hash(transport_handle, hash, hash_len);

verify_download_end:
#ifdef USE_MBEDTLS
    digest_sha256_deinit(dgst);
#else
    xbpal_sha256_deinit(dgst);
#endif

    return res;
}


static int is_partition_allowed(const char *cmspart,
                const char *part,
                bool *allowed)
{
    size_t cms_len, part_len;

    *allowed = false;

    if (!part || !cmspart) {
        FCS_LOG_ERR("Invalid argument\n");
        return -FCSERR_EINVAL;
    }

    cms_len = strlen(cmspart);
    part_len = strlen(part);

    /* Complete match? */
    if ((cms_len == part_len) &&
        (!strncmp(cmspart, part, cms_len))) {
        *allowed = true;
        return FCSERR_OK;
    }

    /* Check if cmspart is <partition> (without slot suffix)
     * and if part contains slot suffix
     * (<partition>_a or <partition>_b)
     */
    if (((cms_len + strlen("_?")) == part_len) &&
            !strncmp(cmspart, part, cms_len)) {
        /* Check for correct slot suffix */
        if ((part[part_len - 2] == '_') &&
            (part[part_len - 1] == 'a' ||
            part[part_len - 1] == 'b')) {
            *allowed = true;
        }
    }

    return FCSERR_OK;
}

#define DISABLE_MULTITHREAD_DOWNLOAD_FLASH
#define ENABLE_USE_GBUF
#ifdef DISABLE_MULTITHREAD_DOWNLOAD_FLASH
#define DATA_BUF_SIZE (100*1024*1024)
static char __attribute__ ((aligned(8))) gcmsbuf[DATA_BUF_SIZE];
#endif
int fastboot_check_cmd_auth(const char *cmd, const char *param, void *data, uint32_t sz, uint8_t *cmsbuf, size_t cmsbuf_len, uint8_t auth_level)
{
    int res = FCSERR_OK;
    struct cms_valid_sin_entry *sin;
    uint8_t ta_partition = 0;
    uint32_t unit = 0;
    bool cmd_authenticated = false;
    char partition[MAX_GPT_NAME_SIZE];
    bool found_part = false;
    bool is_restricted = true;
    bool allowed = false;

    /* high MiscTA (unit nr > 65535 require PRODUCTION authentication */
    if(
        (!strncmp(cmd, "Read-TA:", strlen("Read-TA:")))  ||
        (!strncmp(cmd, "Write-TA:", strlen("Write-TA:")))
      ){
        res = extract_partition_and_unit((uint8_t *)param,
                                        &ta_partition, &unit);
        if (res != FCSERR_OK) {
            FCS_LOG_ERR("Fail to extract partition and/or unit\n");
            return res;
        }
        if ((ta_partition == TA_MISC_PART) && (unit > MISC_TA_MAX_PUBLIC_UNIT_ID)){
            if (auth_level == AUTH_LEVEL_PRODUCTION) {
                cmd_authenticated = true;
                goto done_check_cmd_auth_level;
            }else{
                cmd_authenticated = false;
                FCS_LOG_ERR("Invalid auth_level\n");
                return -FCSERR_AUTH;
            }
        }
    }

    /* command auth level = AUTH_LEVEL_NONE */
    if(
    (!strncmp(cmd, "getvar:", strlen("getvar:")))       ||
    (!strncmp(cmd, "download:", strlen("download:")))   ||
    (!strncmp(cmd, "signature:", strlen("signature:"))) ||
    (!strncmp(cmd, "signature", strlen("signature")))   ||
    (!strncmp(cmd, "boot", strlen("boot")))             ||
    (!strncmp(cmd, "continue", strlen("continue")))     ||
    (!strncmp(cmd, "reboot", strlen("reboot")))         ||
    (!strncmp(cmd, "reboot-bootloader", strlen("reboot-bootloader")))   ||
    (!strncmp(cmd, "powerdown", strlen("powerdown")))   ||
    (!strncmp(cmd, "set_active", strlen("set_active"))) ||
    (!strncmp(cmd, "Read-TA:", strlen("Read-TA:")))     ||
    (!strncmp(cmd, "Read-all-TA:", strlen("Read-all-TA:")))             ||  /* */
    (!strncmp(cmd, "Write-TA:", strlen("Write-TA:")))   ||
    (!strncmp(cmd, "Get-partition-list", strlen("Get-partition-list"))) ||
    (!strncmp(cmd, "SAKE-Authenticate:challeng", strlen("SAKE-Authenticate:challeng")))   ||
    (!strncmp(cmd, "SAKE-Authenticate:response", strlen("SAKE-Authenticate:response")))   ||
    (!strncmp(cmd, "Getnvlog", strlen("Getnvlog")))     ||
    (!strncmp(cmd, "Getlog", strlen("Getlog")))         ||
    (!strncmp(cmd, "Sync", strlen("Sync")))             ||
    (!strncmp(cmd, "Charge", strlen("Charge")))         ||
    (!strncmp(cmd, "Digest:", strlen("Digest:")))       ||
    (!strncmp(cmd, "Get-root-key-hash", strlen("Get-root-key-hash")))   ||
    (!strncmp(cmd, "Get-ufs-info", strlen("Get-ufs-info")))             ||
    (!strncmp(cmd, "Get-gpt-info:", strlen("Get-gpt-info:")))           ||
    (!strncmp(cmd, "Get-emmc-info", strlen("Get-emmc-info")))           ||
    (!strncmp(cmd, "Reboot-bootloader", strlen("Reboot-bootloader")))   ||
    (!strncmp(cmd, "Set-ship-mode", strlen("Set-ship-mode")))
    ){
        cmd_authenticated = true;
        goto done_check_cmd_auth_level;
    }

    /* command auth level = AUTH_LEVEL_PRODUCTION */
    if(
    (!strncmp(cmd, "flash:", strlen("flash:")))         ||
    (!strncmp(cmd, "erase:", strlen("erase:")))         ||
    (!strncmp(cmd, "oem unlock", strlen("oem unlock"))) ||
    (!strncmp(cmd, "oem lock", strlen("oem lock")))     ||
    (!strncmp(cmd, "Format-TA:", strlen("Format-TA:"))) ||
    (!strncmp(cmd, "Read-partition:", strlen("Read-partition:")))       ||
    (!strncmp(cmd, "Set-security", strlen("Set-security")))             ||
    (!strncmp(cmd, "Repartition:", strlen("Repartition:")))             ||
    (!strncmp(cmd, "Secure-erase:", strlen("Secure-erase:")))           ||
    (!strncmp(cmd, "Enable-display", strlen("Enable-display")))         ||
    (!strncmp(cmd, "Disable-display", strlen("Disable-display")))       ||
    (!strncmp(cmd, "Erase-sector:", strlen("Erase-sector:")))           ||
    (!strncmp(cmd, "Read-sector:", strlen("Read-sector:")))             ||
    (!strncmp(cmd, "Secure-erase-sector:", strlen("Secure-erase-sector:")))
    ){
        if (auth_level == AUTH_LEVEL_PRODUCTION) {
            cmd_authenticated = true;
            goto done_check_cmd_auth_level;
        }
    }


    /* command auth level = AUTH_LEVEL_CUSTOMER_SERVICE */
    if(
    (!strncmp(cmd, "Reset-rollback-counter", strlen("Reset-rollback-counter")))   ||
    (!strncmp(cmd, "Reset-frp", strlen("Reset-frp")))
    ){
        if (auth_level == AUTH_LEVEL_CUSTOMER_SERVICE) {
            cmd_authenticated = true;
            goto done_check_cmd_auth_level;
        }
        else if (auth_level == AUTH_LEVEL_PRODUCTION) {
            cmd_authenticated = true;
            goto done_check_cmd_auth_level;
        }
    }

    /* Reading apps_log partition does not require authentication */
    if(
    (!strncmp(cmd, "Read-partition:", strlen("Read-partition:")))
    ){
        if (!strncmp(param, "appslog:", strlen("appslog"))) {
            cmd_authenticated = true;
            goto done_check_cmd_auth_level;
        }else{
            cmd_authenticated = false;
            FCS_LOG_ERR("Invalid auth_level\n");
            return -FCSERR_AUTH;
        }
    }


done_check_cmd_auth_level:


    /* If signature is sent before the commande
     * for the corresponding partition and
     * verification passes then SAKE authentication
     * is not needed
    */
    if(
    (!strncmp(cmd, "flash:", strlen("flash:")))     ||
    (!strncmp(cmd, "erase:", strlen("erase:")))     ||
    (!strncmp(cmd, "Secure-erase:", strlen("Secure-erase:")))
    ){
        if(param != NULL){
            snprintf(partition, MAX_GPT_NAME_SIZE, "%s", param);
            FCS_LOG_INF("partition:%s\n", partition);
            found_part = true;
            goto done_check_partition;
        }else{
            cmd_authenticated = false;
            FCS_LOG_ERR("Invalid auth_level\n");
            return -FCSERR_AUTH;
        }
    }


    /* If signature is sent before Repartition
     * and verification passes then SAKE authentication
     * is not needed
    */
    if(
    (!strncmp(cmd, "Repartition:", strlen("Repartition:")))
    ){
        if(param != NULL){
            strlcpy(partition, VIRTPART_REPART, MAX_GPT_NAME_SIZE);
            if (strlen(param) > 0) {
                strlcat(partition, ":", MAX_GPT_NAME_SIZE);
                strlcat(partition, param, MAX_GPT_NAME_SIZE);
                FCS_LOG_INF("partition name:%s\n", partition);
                found_part = true;
                goto done_check_partition;
            }else{
                cmd_authenticated = false;
                FCS_LOG_ERR("Invalid auth_level\n");
                return -FCSERR_AUTH;
            }
        }else{
            cmd_authenticated = false;
            FCS_LOG_ERR("Invalid auth_level\n");
            return -FCSERR_AUTH;
        }
    }


done_check_partition:

    if (!found_part) {
        goto exit;
    }

    /* We should always allow to flash/erase a new keystore without
     * verification. Only allow flashing xflkeystore partition,
     * not bak partition.
     */
    if(
    (!strncmp(cmd, "flash:", strlen("flash:")))     ||
    (!strncmp(cmd, "erase:", strlen("erase:")))
    ){
        if( strncmp(partition, "xflkeystore", sizeof("xflkeystore")) == 0) {
            cmd_authenticated = true;
            res = FCSERR_OK;
            goto exit;
        }
    }


    /* If the bootloader is unlocked allow flashing or erasing
     * any partition without restriction as long as the device
     * is unfused. But if the device is fused, allow flashing or
     * erasing only platform specific selected partitions.
     */
    if(
    (!strncmp(cmd, "flash:", strlen("flash:")))     ||
    (!strncmp(cmd, "erase:", strlen("erase:")))
    ){
        res = is_partition_restricted(partition, &is_restricted);
        if (res == FCSERR_OK && !is_restricted) {
            /* TODO auth ok in XFL, but need to reconsider whether it is really good */
            cmd_authenticated = true;
            res = FCSERR_OK;
        }
    }


    /* verify external signature */
    LIST_FOR_EACH_DATA(&cms_valid_sin, sin, list) {
        FCS_LOG_INF("LIST_FOR_EACH_DATA\n");
        res = is_partition_allowed(sin->part_name,
                partition,
                &allowed);
        if (res == FCSERR_OK) {
            if (!allowed){
                continue;
            }
        } else {
            goto exit;
        }

        /*
         * FLASH and REPARTITION has downloaded content
         * which should be verified.
         */
        if(
        (!strncmp(cmd, "flash:", strlen("flash:")))     ||
        (!strncmp(cmd, "Repartition:", strlen("Repartition:")))
        ){
#ifdef ENABLE_USE_GBUF
            #ifdef DISABLE_MULTITHREAD_DOWNLOAD_FLASH
            gBS->CopyMem(gcmsbuf, cmsbuf, cmsbuf_len);
            #else
            uint8_t *gcmsbuf = NULL;
            uint8_t *gcmsbuf_temp = AllocatePool(cmsbuf_len + 0x07);
            if(gcmsbuf_temp != NULL){
                gcmsbuf = (uint8_t *)((UINT64)(gcmsbuf_temp + 0x07) & ~0x07);
                gBS->CopyMem(gcmsbuf, cmsbuf, cmsbuf_len);
            }else{
                gcmsbuf = cmsbuf;
            }
            #endif
            res = verify_download_sha256( sin->transport_handle,
                                          (uint8_t *)gcmsbuf,
                                          cmsbuf_len);
            #ifdef DISABLE_MULTITHREAD_DOWNLOAD_FLASH
            #else
            if(gcmsbuf_temp)
                FreePool(gcmsbuf_temp);
            #endif
#else
            res = verify_download_sha256( sin->transport_handle,
                                          cmsbuf,
                                          cmsbuf_len);
#endif
            if (res != FCSERR_OK) {
                list_remove(&sin->list);
                free(sin->part_name);
                transport_deinit(sin->transport_handle);
                free(sin);

                cmd_authenticated = false;
                FCS_LOG_ERR("Fail to verify download\n");
                break;
            }
            if (!transport_has_more(
                    sin->transport_handle)) {
                FCS_LOG_INF("not transport_has_more\n");
                list_remove(&sin->list);
                free(sin->part_name);
                transport_deinit(sin->transport_handle);
                free(sin);
            }
        }
        cmd_authenticated = true;
        break;
    }

exit:
    if(res == FCSERR_OK && !cmd_authenticated){
        res = -FCSERR_AUTH;
    }
    if(cmd_authenticated){
        res = FCSERR_OK;
    }
    return res;
}


int pu_digest_partition(const char *part, uint8_t *val, size_t len)
{
    uint64_t sz = 0;
    int res = FCSERR_OK;
    uint8_t *buf = NULL;
    unsigned int nchunks;
    UINT32 chunk_size = 0;
    uint64_t proc_data = 0;
    struct digest *dgst = NULL;
    uint8_t *calc_hash = NULL;
    uint32_t calc_hash_length = 0;

    CHAR16 pname[(MAX_GPT_NAME_SIZE / 2)] = {0};
    AsciiStrToUnicodeStr(part, pname);
    res = xbpal_get_partition_size(&sz, pname);
    if (res != FCSERR_OK || sz < 0) {
        FCS_LOG_ERR("XGetPartitionSize failure\n");
        return res;
    }
    FCS_LOG_ERR("pu_digest_partition(): pname=%s partition size=%lld\n", pname, sz);

    uint32_t BlockSize;
    res = xbpal_get_block_size(&BlockSize, pname);
    if(res != FCSERR_OK){
        FCS_LOG_ERR("Failed to get block size (%d)\n", res);
       goto exit;
    }

    chunk_size = (MIN(sz, ROUND_TO_PAGE(PU_DIGEST_CHUNK, BlockSize - 1) ));
    buf = (uint8_t *)AllocatePool(chunk_size);
    nchunks = (sz / chunk_size);
    if (sz % chunk_size)
        nchunks++;

    FCS_LOG_ERR("chunk_size=%d BlockSize=%d nchunks=%d\n", chunk_size, BlockSize, nchunks);

    res = digest_sha256_init(&dgst);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to init digest calculation: (%d)\n", res);
        goto exit;
    }

    /*
     * This implementation assumes reading from flash is slower than
     * hashing.
     */
    uint64_t i = 0;
    while (proc_data < sz) {
        FCS_LOG_ERR("XReadPartitionChunk(): i=%d chunk_size=%d offset=%lld\n", i, chunk_size, (i*PU_DIGEST_CHUNK)/BlockSize);
        res = xbpal_reead_partition_chunk(buf, &chunk_size, pname, (i*PU_DIGEST_CHUNK)/BlockSize);
        if (res != FCSERR_OK) {
            FCS_LOG_ERR("XReadPartition failure\n");
            goto exit;
        }

        res = digest_sha224_update(dgst, buf, chunk_size);
        if (res != FCSERR_OK) {
            FCS_LOG_ERR("Failed to update digest: (%d)\n", res);
            goto exit;
        }

        i++;
        proc_data += chunk_size;
        FCS_LOG_ERR("proc_data=%lld\n", proc_data);
        chunk_size = MIN(sz - proc_data, PU_DIGEST_CHUNK);
    }

    res = digest_sha224_update(dgst, NULL, 0);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to update digest: (%d)\n", res);
        goto exit;
    }

    res = digest_sha256_final(dgst, &calc_hash, &calc_hash_length);
    if (res != FCSERR_OK) {
        FCS_LOG_ERR("Failed to finalize digest: (%d)\n", res);
        goto exit;
    }

    if (len < calc_hash_length) {
        FCS_LOG_ERR("hash length larger than buffer size\n");
        res = -FCSERR_ENOMEM;
        goto exit;
    }
    memcpy(val, calc_hash, calc_hash_length);

exit:
    digest_sha256_deinit(dgst);
    FreePool(buf);
    return res;
}

