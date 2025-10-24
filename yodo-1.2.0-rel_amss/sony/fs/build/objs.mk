cu-objs := log_util.o lz4.o gpt.o crc32.o convert.o
cu-objs := $(addprefix core/util/,$(cu-objs))
fsobjs := $(cu-objs)

lo-objs := loader.o write_image.o sparse.o partman.o handler_list.o\
	security_properties.o  sec_data_utils.o
ifeq ($(CFG_STUB_QSEE),y)
lo-objs += sake_nonce_stub.o
else
lo-objs += sake_nonce.o
endif
lo-objs := $(addprefix loader/,$(lo-objs))
fsobjs += $(lo-objs)

pt-objs := protocol_util.o fastboot.o
pt-objs := $(addprefix loader/protocol/,$(pt-objs))
fsobjs += $(pt-objs)

st-objs := storage.o
st-objs := $(addprefix loader/storage/,$(st-objs))
fsobjs += $(st-objs)

cr-objs := core.o
cr-objs += ks/ks_util.o
cr-objs += ks/keystore.o
cr-objs += ks/ksio.o
cr-objs += ks/nvio.o
cr-objs += ks/plf_nv.o
cr-objs += ks/rpmbio.o
cr-objs += ks/generated/asn_codecs_prim.o
cr-objs += ks/generated/asn_SEQUENCE_OF.o
cr-objs += ks/generated/asn_SET_OF.o
cr-objs += ks/generated/ber_decoder.o
cr-objs += ks/generated/ber_tlv_length.o
cr-objs += ks/generated/ber_tlv_tag.o
cr-objs += ks/generated/BIT_STRING.o
cr-objs += ks/generated/constraints.o
cr-objs += ks/generated/constr_CHOICE.o
cr-objs += ks/generated/constr_SEQUENCE.o
cr-objs += ks/generated/constr_SEQUENCE_OF.o
cr-objs += ks/generated/constr_SET_OF.o
cr-objs += ks/generated/constr_TYPE.o
cr-objs += ks/generated/der_encoder.o
cr-objs += ks/generated/INTEGER.o
cr-objs += ks/generated/BOOLEAN.o
cr-objs += ks/generated/KeyStore.o
cr-objs += ks/generated/KeyStoreCertificate.o
cr-objs += ks/generated/KeyStoreDB.o
cr-objs += ks/generated/KeyStoreEntry.o
cr-objs += ks/generated/KeyStoreEntryData.o
cr-objs += ks/generated/KeyStorePublicKey.o
cr-objs += ks/generated/NativeEnumerated.o
cr-objs += ks/generated/NativeInteger.o
cr-objs += ks/generated/OCTET_STRING.o
cr-objs += ks/generated/per_decoder.o
cr-objs += ks/generated/per_encoder.o
cr-objs += ks/generated/per_opentype.o
cr-objs += ks/generated/per_support.o
cr-objs += ks/generated/xer_decoder.o
cr-objs += ks/generated/xer_encoder.o
cr-objs += ks/generated/xer_support.o
cr-objs := $(addprefix core/,$(cr-objs))
fsobjs += $(cr-objs)

ta-objs := ta_functions.o ta_interface.o
ta-objs := $(addprefix integration/common/,$(ta-objs))
fsobjs += $(ta-objs)

hwc-objs := hwconf_x.o hwconf_x_parser.o asn1pdu_hwconf_x.o
hwc-objs := $(addprefix core/hwconf/,$(hwc-objs))
fsobjs += $(hwc-objs)

sp-objs := sin_parser.o sin_verifier.o
sp-objs := $(addprefix core/sin/,$(sp-objs))
fsobjs += $(sp-objs)

sl-objs := simlock.o simlock_parser.o simlock_engine.o
sl-objs := $(addprefix core/simlock/,$(sl-objs))
fsobjs += $(sl-objs)

ap-objs := asahi_parser.o asahi_verifier.o
ap-objs := $(addprefix core/asahi/,$(ap-objs))
fsobjs += $(ap-objs)

cms-objs := cms_verifier_derparser.o asn1pdu_cms.o
cms-objs := $(addprefix core/cms/,$(cms-objs))
fsobjs += $(cms-objs)

rm-objs := asn1pdu_rule.o rule_rootcert.o rule_verifier.o
rm-objs := $(addprefix core/rm/,$(rm-objs))
fsobjs += $(rm-objs)

der-objs := der_parser_objects.o der_parser_iterator.o der_parser_handlers.o
der-objs += der_parser_utils.o
der-objs := $(addprefix core/der/,$(der-objs))
fsobjs += $(der-objs)

rs-objs := rooting_status.o
rs-objs := $(addprefix core/rooting_status/,$(rs-objs))
fsobjs += $(rs-objs)

sa-objs := sake_engine.o sake_alg.o sake_cert.o sake_hash.o authenticate_common.o
sa-objs := $(addprefix core/sake/,$(sa-objs))
fsobjs += $(sa-objs)

tv-objs := transport_verifier.o
tv-objs := $(addprefix core/transport/,$(tv-objs))
fsobjs += $(tv-objs)

include_dirs += core/include
include_dirs += integration/common/include
include_dirs += core/ks/include
include_dirs += core/ks/generated
include_dirs += loader/include
include_dirs += loader/storage/include
include_dirs += security/include
