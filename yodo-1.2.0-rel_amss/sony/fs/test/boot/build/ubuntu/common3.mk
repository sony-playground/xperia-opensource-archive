FCS_BOOT_TEST=$(FCS_MAIN)/test/boot
OBJDIR=obj
CC=gcc

# Test environment specific: Ubuntu
CFLAGS=-g -c -Wall -Wno-pragmas -Werror -DCFG_ENABLE_FCS_LOG -DCFG_ENABLE_FCS_LOG_INF -DCFG_ENABLE_FCS_LOG_WRN
# Test framework
CFLAGS+=-I$(FCS_BOOT_TEST)/framework/include
CFLAGS+=-I$(FCS_BOOT_TEST)/framework
# Test integration
CFLAGS+=-I$(FCS_BOOT_TEST)/integration/include
# Test cases
#CFLAGS+=-I$(GENDIR)
# Test data
CFLAGS+=-I$(FCS_BOOT_TEST)/app/ubuntu
# Source under test
CFLAGS+=-I$(FCS_MAIN)/boot/include
CFLAGS+=-I$(FCS_MAIN)/boot/src
CFLAGS+=-I$(FCS_MAIN)/core/include
CFLAGS+=-I$(FCS_MAIN)/core/util/include
CFLAGS+=-I$(FCS_MAIN)/core/ks/include
CFLAGS+=-I$(FCS_MAIN)/core/ks/generated
# Integration Core
CFLAGS+=-I$(FCS_MAIN)/integration/common/include
CFLAGS+=-I$(FCS_MAIN)/integration/$(FCS_PLATFORM)/include
# Integration TA
#CFLAGS+=-I$(FCS_MAIN)/../miscta/libta/inc
CFLAGS+=-I$(FCS_MAIN)/../miscta/tad/common
CFLAGS+=-I$(FCS_MAIN)/../miscta/tad/src
CFLAGS+=-I$(FCS_MAIN)/../miscta/libmiscta/inc
# Integration Root Certs
CFLAGS+=-I$(FCS_MAIN)/../xflcertificate
CFLAGS+=-DROOT_USAGE_HWCONF=\"root_usage_$(FCS_HWCONFIG).h\"

# Integration OpenSSL
CFLAGS_OPENSSL=-I$(FCS_MAIN)/../../edk2/abl/CryptoPkg/Library/OpensslLib/openssl-1.0.2j/include
LDFLAGS_OPENSSL=-L$(FCS_MAIN)/../../edk2/abl/CryptoPkg/Library/OpensslLib/openssl-1.0.2j -lssl -lcrypto -ldl -lpthread
# Integration mbedtls
CFLAGS_MBEDTLS=-I$(FCS_MAIN)/../mbedtls/include
CFLAGS_MBEDTLS+=-I$(FCS_MAIN)/../mbedtls/include/mbedtls
CFLAGS_MBEDTLS+=-I$(FCS_MAIN)/../mbedtls/configs
CFLAGS_MBEDTLS+=-DMBEDTLS_CONFIG_FILE=\"config-somc-xfl-xboot.h\"
LDFLAGS_MBEDTLS= -lcrypto -ldl -lpthread

# Test environment specific: Ubuntu
SOURCES=$(FCS_BOOT_TEST)/app/ubuntu/devmain.c
SOURCES+=$(FCS_BOOT_TEST)/app/ubuntu/gen_tests.c
SOURCES+=$(FCS_BOOT_TEST)/app/ubuntu/$(FCS_PLATFORM)/dut_normal.c
SOURCES+=$(FCS_BOOT_TEST)/app/ubuntu/$(FCS_PLATFORM)/dut_valid.c
SOURCES+=$(FCS_BOOT_TEST)/app/ubuntu/$(FCS_PLATFORM)/dut_wrong.c
SOURCES+=$(FCS_BOOT_TEST)/app/ubuntu/$(FCS_PLATFORM)/dut_cmdline.c
SOURCES+=$(FCS_BOOT_TEST)/integration/ubuntu/integration_emulator.c
SOURCES+=$(FCS_BOOT_TEST)/integration/ubuntu/$(FCS_PLATFORM)/integration_emulator_eroot.c
# Test framework
SOURCES+=$(FCS_BOOT_TEST)/framework/iterator.c
SOURCES+=$(FCS_BOOT_TEST)/framework/integration_main.c
# Test cases
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_common.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_normal.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_delay_normal.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_shortpress.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_xfl.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_factmode_xfl.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_charger.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_qcfb.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_force_reset.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_force_shutdown.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_watchdog.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_empty_ks_usb_no.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_empty_ks_usb_yes.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_empty_hwc_usb_no.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_empty_hwc_usb_yes.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_first_ks.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_apply_xcs_ks.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_reset_arb.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_hwc_wrong_payload_usb_no.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_hwc_wrong_payload_usb_yes.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_hwc_wrong_devid_usb_no.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_hwc_wrong_devid_usb_yes.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_wrong_payload.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_both_wrong_payload_usb_no.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_both_wrong_payload_usb_yes.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_wrong_devid.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_wrong_imei.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_both_wrong_devid_usb_no.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_both_wrong_imei_usb_no.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_both_wrong_devid_usb_yes.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_both_wrong_imei_usb_yes.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_insert_ks_failed_due_to_xcs.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_insert_ks_failed_due_to_counter.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_bound_to_hmac_devid_valid_key.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_bound_to_hmac_imei_valid_key.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_bound_to_hmac_devid_wrong_key.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_bound_to_hmac_imei_wrong_key.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_both_bad_counters.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_diff_payload_eq_counter.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_invalid_bak_xcs_set_higher_counter.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_xcs_sl_not_rootable.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_xcs_sl_not_rootable_bak_invalid.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_same_payload_imei_hmac.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_same_payload_imei_hmac_diff_key.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_ks_valid_high_key_invalid_low_key.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_xb_simlock_unlock_data.c
# General tests of internal interfaces
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_gen_hwconf_x_parser_normal.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_gen_hwconf_x_parser_error.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_gen_der_parser.c
SOURCES+=$(FCS_BOOT_TEST)/module_test/mt_gen_rule_verifier.c
# Integration Core
#SOURCES+=$(FCS_MAIN)/boot/xboot_int.c
SOURCES+=$(FCS_BOOT_TEST)/framework/integration_core.c
# Integration env
SOURCES+=$(FCS_BOOT_TEST)/framework/integration_env.c
# Integration TA
SOURCES+=$(FCS_BOOT_TEST)/framework/integration_ta.c
# Integration XBoot PAL
SOURCES+=$(FCS_BOOT_TEST)/framework/integration_xbpal.c
# Integration xflattest (replaces rpmb interface)
SOURCES+=$(FCS_BOOT_TEST)/framework/integration_xflattest.c
# Integration  keystore nv interface
SOURCES+=$(FCS_BOOT_TEST)/framework/integration_nv.c

# Integration embedded roots
SOURCES+=$(FCS_BOOT_TEST)/framework/integration_eroot.c


# Source under test
SOURCES+=$(FCS_MAIN)/boot/xboot_glue.c
SOURCES+=$(FCS_MAIN)/boot/xboot_auth_cmd.c
SOURCES+=$(FCS_MAIN)/boot/src/sony_boot_lib_api.c
SOURCES+=$(FCS_MAIN)/boot/src/sony_boot_service_detect.c
SOURCES+=$(FCS_MAIN)/boot/src/sony_boot_utils.c
SOURCES+=$(FCS_MAIN)/boot/src/sony_boot_config_parser.c
SOURCES+=$(FCS_MAIN)/core/hwconf/hwconf_parser.c
SOURCES+=$(FCS_MAIN)/core/hwconf/asn1pdu_hwconf_x.c
SOURCES+=$(FCS_MAIN)/core/hwconf/hwconf_x_parser.c
SOURCES+=$(FCS_MAIN)/core/hwconf/$(FCS_HWCONFIG).c
SOURCES+=$(FCS_MAIN)/core/rm/rule_verifier.c
SOURCES+=$(FCS_MAIN)/core/rm/asn1pdu_rule.c
SOURCES+=$(FCS_MAIN)/core/rm/rule_rootcert.c
SOURCES+=$(FCS_MAIN)/core/der/der_parser_handlers.c
SOURCES+=$(FCS_MAIN)/core/der/der_parser_iterator.c
SOURCES+=$(FCS_MAIN)/core/der/der_parser_objects.c
SOURCES+=$(FCS_MAIN)/core/der/der_parser_utils.c
SOURCES+=$(FCS_MAIN)/core/ta/ta_interface.c
SOURCES+=$(FCS_MAIN)/core/ks/ks_util.c
SOURCES+=$(FCS_MAIN)/core/ks/keystore.c
SOURCES+=$(FCS_MAIN)/core/ks/ksio.c
SOURCES+=$(FCS_MAIN)/core/ks/nvio.c
SOURCES+=$(FCS_MAIN)/core/ks/plf_nv.c
SOURCES+=$(FCS_MAIN)/core/ks/rpmbio.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/KeyStore.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/KeyStoreDB.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/KeyStoreEntry.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/KeyStoreEntryData.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/KeyStoreCertificate.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/KeyStorePublicKey.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/asn_codecs_prim.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/constraints.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/INTEGER.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/NativeInteger.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/BOOLEAN.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/OCTET_STRING.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/ber_decoder.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/ber_tlv_tag.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/ber_tlv_length.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/xer_decoder.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/xer_support.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/constr_CHOICE.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/constr_SEQUENCE.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/constr_SEQUENCE_OF.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/constr_SET_OF.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/asn_SET_OF.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/constr_TYPE.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/der_encoder.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/per_encoder.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/per_support.c
SOURCES+=$(FCS_MAIN)/core/ks/generated/per_opentype.c
SOURCES+=$(FCS_MAIN)/core/asahi/asahi_parser.c
SOURCES+=$(FCS_MAIN)/core/asahi/asahi_verifier.c
SOURCES+=$(FCS_MAIN)/core/sin/sin_parser.c
SOURCES+=$(FCS_MAIN)/core/sin/sin_verifier.c
SOURCES+=$(FCS_MAIN)/core/simlock/simlock.c
SOURCES+=$(FCS_MAIN)/core/simlock/simlock_parser.c
SOURCES+=$(FCS_MAIN)/core/simlock/simlock_engine.c
SOURCES+=$(FCS_MAIN)/core/rooting_status/rooting_status.c
SOURCES+=$(FCS_MAIN)/core/oemunlock_flag/oemunlock_flag.c
SOURCES+=$(FCS_MAIN)/core/util/convert.c
SOURCES+=$(FCS_MAIN)/core/util/log_util.c
SOURCES+=$(FCS_MAIN)/core/core.c
SOURCES+=$(FCS_MAIN)/core/sake/sake_alg.c
SOURCES+=$(FCS_MAIN)/core/sake/sake_cert.c
SOURCES+=$(FCS_MAIN)/core/sake/sake_engine.c
SOURCES+=$(FCS_MAIN)/core/sake/sake_hash.c

# OpenSSL integration
SOURCES_OPENSSL=$(FCS_MAIN)/integration/crypto/openssl/rule.c
SOURCES_OPENSSL+=$(FCS_MAIN)/integration/crypto/openssl/digest.c
SOURCES_OPENSSL+=$(FCS_MAIN)/integration/crypto/openssl/certificate_chain.c
SOURCES_OPENSSL+=$(FCS_MAIN)/integration/crypto/openssl/signature.c
SOURCES_OPENSSL+=$(FCS_MAIN)/integration/crypto/openssl/core.c
SOURCES_OPENSSL+=$(FCS_MAIN)/core/cms/cms_verifier.c
SOURCES_OPENSSL+=$(FCS_MAIN)/core/sake/authenticate_common.c
SOURCES_OPENSSL+=$(FCS_MAIN)/integration/crypto/openssl/authenticate.c

# MbedTLS integration
SOURCES_MBEDTLS=$(FCS_MAIN)/integration/crypto/mbedtls/rule.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/integration/crypto/mbedtls/digest.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/integration/crypto/mbedtls/certificate_chain.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/integration/crypto/mbedtls/signature.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/integration/crypto/mbedtls/core.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/integration/crypto/mbedtls/rng.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/core/cms/cms_verifier_derparser.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/core/cms/asn1pdu_cms.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/core/sake/authenticate_common.c
SOURCES_MBEDTLS+=$(FCS_MAIN)/integration/crypto/mbedtls/authenticate.c
CFLAGS+=-I$(FCS_MAIN)/integration/crypto/mbedtls/include/


# MbedTLS library
SOURCES_MBEDTLS_LIB=$(FCS_MAIN)/../mbedtls/library/aes.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/aesni.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/asn1parse.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/asn1write.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/base64.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/bignum.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/camellia.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/ccm.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/cipher.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/cipher_wrap.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/cmac.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/ctr_drbg.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/des.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/dhm.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/ecdh.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/ecdsa.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/ecjpake.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/ecp.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/ecp_curves.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/entropy.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/entropy_poll.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/error.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/gcm.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/havege.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/hmac_drbg.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/md.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/md5.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/memory_buffer_alloc.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/oid.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/padlock.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/pem.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/pk.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/pk_wrap.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/pkcs12.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/pkcs5.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/pkparse.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/pkwrite.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/platform.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/platform_util.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/ripemd160.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/rsa.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/rsa_alt_helpers.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/sha1.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/sha256.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/sha512.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/threading.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/timing.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/version.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/version_features.c

SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/x509.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/x509_create.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/x509_crl.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/x509_crt.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/x509_csr.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/x509write_crt.c
SOURCES_MBEDTLS_LIB+=$(FCS_MAIN)/../mbedtls/library/x509write_csr.c

RED='\033[1;31m'
NC='\033[0m'
OBJECTS=$(patsubst $(FCS_MAIN)/%,$(OBJDIR)/%,$(SOURCES:.c=.o))
OBJECTS_OPENSSL=$(patsubst $(FCS_MAIN)/%,$(OBJDIR)/%,$(SOURCES_OPENSSL:.c=.o))
OBJECTS_MBEDTLS=$(patsubst $(FCS_MAIN)/%,$(OBJDIR)/%,$(SOURCES_MBEDTLS:.c=.o))
OBJECTS_MBEDTLS_LIB=$(patsubst $(FCS_MAIN)/../%,$(OBJDIR)/%,$(SOURCES_MBEDTLS_LIB:.c=.o))
EXECUTABLE=device_test
MAIN=main_test.py

all: mbedtls
.PHONY : all

clean: clean-mbedtls
.PHONY : clean

openssl: preprocess-with-openssl executable-with-openssl
.PHONY : all

mbedtls: preprocess-with-mbedtls executable-with-mbedtls
.PHONY : mbedtls

clean-openssl: openssl-clean
	@rm -rf $(OBJDIR) rm -f $(EXECUTABLE) rm -f $(MAIN)
.PHONY : clean

clean-mbedtls:
	@rm -rf $(OBJDIR) rm -f $(EXECUTABLE) rm -f $(MAIN)
.PHONY : clean-mbedtls

preprocess-with-openssl:
	$(eval CFLAGS+= $(CFLAGS_OPENSSL))
	$(eval LDFLAGS:= $(LDFLAGS_OPENSSL))

executable-with-openssl: $(SOURCES) $(SOURCES_OPENSSL) openssl $(OBJECTS) $(OBJECTS_OPENSSL)
	@echo Linking $(EXECUTABLE)
	@$(CC) $(OBJECTS) $(OBJECTS_OPENSSL) -o $(EXECUTABLE) $(LDFLAGS)
	@cp -f $(FCS_BOOT_TEST)/app/ubuntu/main.py $(MAIN)
	@echo "${RED}**Remember to do a 'make clean' before attempting boot build**${NC}"

preprocess-with-mbedtls:
	@echo Add flags...
	$(eval CFLAGS+= $(CFLAGS_MBEDTLS))
	$(eval LDFLAGS:= $(LDFLAGS_MBEDTLS))
	@echo $(CFLAGS)
	@echo $(LDFLAGS)

executable-with-mbedtls: $(SOURCES) $(SOURCES_MBEDTLS) $(SOURCES_MBEDTLS_LIB) $(OBJECTS_MBEDTLS_LIB) $(OBJECTS) $(OBJECTS_MBEDTLS)
	@echo Linking $(EXECUTABLE)
	@$(CC) $(OBJECTS) $(OBJECTS_MBEDTLS) $(OBJECTS_MBEDTLS_LIB) -o $(EXECUTABLE) $(LDFLAGS)
	@cp -f $(FCS_BOOT_TEST)/app/ubuntu/main.py $(MAIN)
	@echo "${RED}**Remember to do a 'make clean' before attempting boot build**${NC}"

$(FCS_MAIN)/../../edk2/abl/CryptoPkg/Library/OpensslLib/openssl-1.0.2j/Makefile:
	@cd $(FCS_MAIN)/../../edk2/abl/CryptoPkg/Library/OpensslLib/openssl-1.0.2j \
	&& ./config

openssl: $(FCS_MAIN)/../../edk2/abl/CryptoPkg/Library/OpensslLib/openssl-1.0.2j/Makefile
	@cd $(FCS_MAIN)/../../edk2/abl/CryptoPkg/Library/OpensslLib/openssl-1.0.2j && make -j8

openssl-clean:
	@-cd $(FCS_MAIN)/../../edk2/abl/CryptoPkg/Library/OpensslLib/openssl-1.0.2j &&\
	make clean && git checkout crypto/opensslconf.h && git clean -f # To be able to do boot builds after building test

$(OBJDIR)/%.o: $(FCS_MAIN)/%.c
	@test -d $(dir $@) || mkdir -p $(dir $@)
	@echo Compiling $< into $@
	@$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) $< -o $@
$(OBJDIR)/mbedtls/%.o: $(FCS_MAIN)/../mbedtls/%.c
	@test -d $(dir $@) || mkdir -p $(dir $@)
	@echo Compiling $< into $@
	@$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) $< -o $@
-include $(OBJECTS:.o=.d)

