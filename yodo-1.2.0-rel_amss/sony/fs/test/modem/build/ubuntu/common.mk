FCS_MODEM_TEST=$(abspath $(FCS_MAIN)/test/modem)
OBJDIR=obj
CC=gcc
# Test environment specific: Ubuntu
CFLAGS=-g -c -Wall -Wno-pragmas -Werror -DCFG_ENABLE_FCS_LOG -DCFG_ENABLE_FCS_LOG_INF -DCFG_ENABLE_FCS_LOG_WRN
CFLAGS+=-DMBEDTLS_CONFIG_FILE=\"config-somc-modem.h\"
CFLAGS+=$(FCS_CFLAGS)

# Test framework
CFLAGS+=-I$(FCS_MODEM_TEST)/framework/include
CFLAGS+=-I$(FCS_MODEM_TEST)/framework
# Test integration
CFLAGS+=-I$(FCS_MODEM_TEST)/integration/include
# Test cases
#CFLAGS+=-I$(GENDIR)
# Test data
CFLAGS+=-I$(FCS_MODEM_TEST)/app/ubuntu
# Source under test
CFLAGS+=-I$(FCS_MAIN)/modem/include
CFLAGS+=-I$(FCS_MAIN)/modem/src
CFLAGS+=-I$(FCS_MAIN)/core/include
CFLAGS+=-I$(FCS_MAIN)/core/util/include
# Integration Core
CFLAGS+=-I$(FCS_MAIN)/integration/$(FCS_PLATFORM)/include
# Integration Root Certs
CFLAGS+=-I$(FCS_CERTS)
CFLAGS+=-DROOT_USAGE_HWCONF=\"root_usage_$(FCS_HWCONFIG).h\"
# Integration MBEDTLS
CFLAGS+=-I$(FCS_MBEDTLS)/configs
CFLAGS+=-I$(FCS_MBEDTLS)/include
CFLAGS+=-I$(FCS_MBEDTLS)/include/mbedtls
CFLAGS+=-I$(FCS_MAIN)/integration/crypto/mbedtls/include/

# Test environment specific: Ubuntu
SOURCES=$(FCS_MODEM_TEST)/app/ubuntu/devmain.c
SOURCES+=$(FCS_MODEM_TEST)/app/ubuntu/gen_tests.c
SOURCES+=$(FCS_MODEM_TEST)/app/ubuntu/$(FCS_PLATFORM)/dut_normal.c
SOURCES+=$(FCS_MODEM_TEST)/integration/ubuntu/integration_emulator.c
SOURCES+=$(FCS_MODEM_TEST)/integration/ubuntu/$(FCS_PLATFORM)/integration_emulator_eroot.c
# Test framework
SOURCES+=$(FCS_MODEM_TEST)/framework/iterator.c
SOURCES+=$(FCS_MODEM_TEST)/framework/integration_main.c

# Test cases
SOURCES+=$(FCS_MODEM_TEST)/module_test/mt_xm_common.c
SOURCES+=$(FCS_MODEM_TEST)/module_test/mt_xm_normal.c

# Integration Core
SOURCES+=$(FCS_MODEM_TEST)/framework/integration_core.c
# Integration TA
SOURCES+=$(FCS_MODEM_TEST)/framework/integration_ta_interface.c
# Integration embedded roots
SOURCES+=$(FCS_MODEM_TEST)/framework/integration_eroot.c

# Source under test
SOURCES+=$(FCS_MAIN)/modem/src/xmodem.c
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
SOURCES+=$(FCS_MAIN)/core/asahi/asahi_parser.c
SOURCES+=$(FCS_MAIN)/core/asahi/asahi_verifier.c
SOURCES+=$(FCS_MAIN)/core/sin/sin_parser.c
SOURCES+=$(FCS_MAIN)/core/sin/sin_verifier.c
SOURCES+=$(FCS_MAIN)/core/simlock/simlock.c
SOURCES+=$(FCS_MAIN)/core/simlock/simlock_parser.c
SOURCES+=$(FCS_MAIN)/core/cms/asn1pdu_cms.c
SOURCES+=$(FCS_MAIN)/core/cms/cms_verifier_derparser.c
SOURCES+=$(FCS_MAIN)/core/util/log_util.c
SOURCES+=$(FCS_MAIN)/core/util/convert.c

SOURCES+=$(FCS_MAIN)/integration/crypto/mbedtls/rule.c
SOURCES+=$(FCS_MAIN)/integration/crypto/mbedtls/digest.c
SOURCES+=$(FCS_MAIN)/integration/crypto/mbedtls/certificate_chain.c
SOURCES+=$(FCS_MAIN)/integration/crypto/mbedtls/signature.c
SOURCES+=$(FCS_MAIN)/integration/crypto/mbedtls/core.c

SOURCES+=$(FCS_MBEDTLS)/library/aes.c
SOURCES+=$(FCS_MBEDTLS)/library/aesni.c
SOURCES+=$(FCS_MBEDTLS)/library/arc4.c
SOURCES+=$(FCS_MBEDTLS)/library/asn1parse.c
SOURCES+=$(FCS_MBEDTLS)/library/asn1write.c
SOURCES+=$(FCS_MBEDTLS)/library/base64.c
SOURCES+=$(FCS_MBEDTLS)/library/bignum.c
SOURCES+=$(FCS_MBEDTLS)/library/blowfish.c
SOURCES+=$(FCS_MBEDTLS)/library/camellia.c
SOURCES+=$(FCS_MBEDTLS)/library/ccm.c
SOURCES+=$(FCS_MBEDTLS)/library/cipher.c
SOURCES+=$(FCS_MBEDTLS)/library/cipher_wrap.c
SOURCES+=$(FCS_MBEDTLS)/library/cmac.c
SOURCES+=$(FCS_MBEDTLS)/library/ctr_drbg.c
SOURCES+=$(FCS_MBEDTLS)/library/des.c
SOURCES+=$(FCS_MBEDTLS)/library/dhm.c
SOURCES+=$(FCS_MBEDTLS)/library/ecdh.c
SOURCES+=$(FCS_MBEDTLS)/library/ecdsa.c
SOURCES+=$(FCS_MBEDTLS)/library/ecjpake.c
SOURCES+=$(FCS_MBEDTLS)/library/ecp.c
SOURCES+=$(FCS_MBEDTLS)/library/ecp_curves.c
SOURCES+=$(FCS_MBEDTLS)/library/entropy.c
SOURCES+=$(FCS_MBEDTLS)/library/entropy_poll.c
SOURCES+=$(FCS_MBEDTLS)/library/error.c
SOURCES+=$(FCS_MBEDTLS)/library/gcm.c
SOURCES+=$(FCS_MBEDTLS)/library/havege.c
SOURCES+=$(FCS_MBEDTLS)/library/hmac_drbg.c
SOURCES+=$(FCS_MBEDTLS)/library/md.c
SOURCES+=$(FCS_MBEDTLS)/library/md2.c
SOURCES+=$(FCS_MBEDTLS)/library/md4.c
SOURCES+=$(FCS_MBEDTLS)/library/md5.c
SOURCES+=$(FCS_MBEDTLS)/library/md_wrap.c
SOURCES+=$(FCS_MBEDTLS)/library/memory_buffer_alloc.c
SOURCES+=$(FCS_MBEDTLS)/library/oid.c
SOURCES+=$(FCS_MBEDTLS)/library/padlock.c
SOURCES+=$(FCS_MBEDTLS)/library/pem.c
SOURCES+=$(FCS_MBEDTLS)/library/pk.c
SOURCES+=$(FCS_MBEDTLS)/library/pk_wrap.c
SOURCES+=$(FCS_MBEDTLS)/library/pkcs12.c
SOURCES+=$(FCS_MBEDTLS)/library/pkcs5.c
SOURCES+=$(FCS_MBEDTLS)/library/pkparse.c
SOURCES+=$(FCS_MBEDTLS)/library/pkwrite.c
SOURCES+=$(FCS_MBEDTLS)/library/platform.c
SOURCES+=$(FCS_MBEDTLS)/library/platform_util.c
SOURCES+=$(FCS_MBEDTLS)/library/ripemd160.c
SOURCES+=$(FCS_MBEDTLS)/library/rsa.c
SOURCES+=$(FCS_MBEDTLS)/library/rsa_internal.c
SOURCES+=$(FCS_MBEDTLS)/library/sha1.c
SOURCES+=$(FCS_MBEDTLS)/library/sha256.c
SOURCES+=$(FCS_MBEDTLS)/library/sha512.c
SOURCES+=$(FCS_MBEDTLS)/library/threading.c
SOURCES+=$(FCS_MBEDTLS)/library/timing.c
SOURCES+=$(FCS_MBEDTLS)/library/version.c
SOURCES+=$(FCS_MBEDTLS)/library/version_features.c
SOURCES+=$(FCS_MBEDTLS)/library/xtea.c

SOURCES+=$(FCS_MBEDTLS)/library/certs.c
SOURCES+=$(FCS_MBEDTLS)/library/pkcs11.c
SOURCES+=$(FCS_MBEDTLS)/library/x509.c
SOURCES+=$(FCS_MBEDTLS)/library/x509_create.c
SOURCES+=$(FCS_MBEDTLS)/library/x509_crl.c
SOURCES+=$(FCS_MBEDTLS)/library/x509_crt.c
SOURCES+=$(FCS_MBEDTLS)/library/x509_csr.c
SOURCES+=$(FCS_MBEDTLS)/library/x509write_crt.c
SOURCES+=$(FCS_MBEDTLS)/library/x509write_csr.c

RED='\033[1;31m'
NC='\033[0m'
OBJECTS=$(patsubst $(FCS_MODEM_TEST)/%,$(OBJDIR)/test/%,$(patsubst $(FCS_MBEDTLS)/%,$(OBJDIR)/mbedtls/%,$(patsubst $(FCS_MAIN)/%,$(OBJDIR)/main/%,$(SOURCES:.c=.o))))
EXECUTABLE=device_test
MAIN=main_test.py

all: $(SOURCES) $(EXECUTABLE)
.PHONY : all

clean:
	@rm -rf $(OBJDIR) rm -f $(EXECUTABLE) rm -f $(MAIN)
.PHONY : clean


$(EXECUTABLE): $(OBJECTS)
	@echo Linking $(EXECUTABLE)
	@$(CC) $(OBJECTS) -o $@ $(LDFLAGS)
	@cp -f $(FCS_MODEM_TEST)/app/ubuntu/main.py $(MAIN)
	@echo "${RED}**Remember to do a 'make clean' before attempting modem build**${NC}"


$(OBJDIR)/test/%.o: $(FCS_MODEM_TEST)/%.c
	@test -d $(dir $@) || mkdir -p $(dir $@)
	@echo Compiling $< into $@
	@$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) $< -o $@
-include $(OBJECTS:.o=.d)

$(OBJDIR)/main/%.o: $(FCS_MAIN)/%.c
	@test -d $(dir $@) || mkdir -p $(dir $@)
	@echo Compiling $< into $@
	@$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) $< -o $@
-include $(OBJECTS:.o=.d)

$(OBJDIR)/mbedtls/%.o: $(FCS_MBEDTLS)/%.c
	@test -d $(dir $@) || mkdir -p $(dir $@)
	@echo Compiling $< into $@
	@$(CC) $(CFLAGS) -MMD -MP -MF $(@:.o=.d) $< -o $@
-include $(OBJECTS:.o=.d)

