ASN_MODULE_SOURCES=	\
	KeyStore.c	\
	KeyStoreDB.c	\
	KeyStoreEntry.c	\
	KeyStoreEntryData.c	\
	KeyStoreCertificate.c	\
	KeyStorePublicKey.c

ASN_MODULE_HEADERS=	\
	KeyStore.h	\
	KeyStoreDB.h	\
	KeyStoreEntry.h	\
	KeyStoreEntryData.h	\
	KeyStoreCertificate.h	\
	KeyStorePublicKey.h

ASN_MODULE_HEADERS+=INTEGER.h
ASN_MODULE_HEADERS+=NativeEnumerated.h
ASN_MODULE_SOURCES+=INTEGER.c
ASN_MODULE_SOURCES+=NativeEnumerated.c
ASN_MODULE_HEADERS+=NativeInteger.h
ASN_MODULE_SOURCES+=NativeInteger.c
ASN_MODULE_HEADERS+=asn_SEQUENCE_OF.h
ASN_MODULE_SOURCES+=asn_SEQUENCE_OF.c
ASN_MODULE_HEADERS+=asn_SET_OF.h
ASN_MODULE_SOURCES+=asn_SET_OF.c
ASN_MODULE_HEADERS+=constr_CHOICE.h
ASN_MODULE_SOURCES+=constr_CHOICE.c
ASN_MODULE_HEADERS+=constr_SEQUENCE.h
ASN_MODULE_SOURCES+=constr_SEQUENCE.c
ASN_MODULE_HEADERS+=constr_SEQUENCE_OF.h
ASN_MODULE_SOURCES+=constr_SEQUENCE_OF.c
ASN_MODULE_HEADERS+=constr_SET_OF.h
ASN_MODULE_SOURCES+=constr_SET_OF.c
ASN_MODULE_HEADERS+=asn_application.h
ASN_MODULE_HEADERS+=asn_system.h
ASN_MODULE_HEADERS+=asn_codecs.h
ASN_MODULE_HEADERS+=asn_internal.h
ASN_MODULE_HEADERS+=OCTET_STRING.h
ASN_MODULE_SOURCES+=OCTET_STRING.c
ASN_MODULE_HEADERS+=BIT_STRING.h
ASN_MODULE_SOURCES+=BIT_STRING.c
ASN_MODULE_SOURCES+=asn_codecs_prim.c
ASN_MODULE_HEADERS+=asn_codecs_prim.h
ASN_MODULE_HEADERS+=ber_tlv_length.h
ASN_MODULE_SOURCES+=ber_tlv_length.c
ASN_MODULE_HEADERS+=ber_tlv_tag.h
ASN_MODULE_SOURCES+=ber_tlv_tag.c
ASN_MODULE_HEADERS+=ber_decoder.h
ASN_MODULE_SOURCES+=ber_decoder.c
ASN_MODULE_HEADERS+=der_encoder.h
ASN_MODULE_SOURCES+=der_encoder.c
ASN_MODULE_HEADERS+=constr_TYPE.h
ASN_MODULE_SOURCES+=constr_TYPE.c
ASN_MODULE_HEADERS+=constraints.h
ASN_MODULE_SOURCES+=constraints.c
ASN_MODULE_HEADERS+=xer_support.h
ASN_MODULE_SOURCES+=xer_support.c
ASN_MODULE_HEADERS+=xer_decoder.h
ASN_MODULE_SOURCES+=xer_decoder.c
ASN_MODULE_HEADERS+=xer_encoder.h
ASN_MODULE_SOURCES+=xer_encoder.c
ASN_MODULE_HEADERS+=per_support.h
ASN_MODULE_SOURCES+=per_support.c
ASN_MODULE_HEADERS+=per_decoder.h
ASN_MODULE_SOURCES+=per_decoder.c
ASN_MODULE_HEADERS+=per_encoder.h
ASN_MODULE_SOURCES+=per_encoder.c
ASN_MODULE_HEADERS+=per_opentype.h
ASN_MODULE_SOURCES+=per_opentype.c

OUT ?= .
OBJDIR=$(OUT)
KEYSTORE_LIBRARY=$(OBJDIR)/libkeystore.a


CFLAGS += -I. -DPDU=KeyStore  -ffunction-sections -Wl,--gc-sections -fno-stack-protector -Os -DNDEBUG
OBJS=${ASN_MODULE_SOURCES:.c=.o} 
OBJS_OUT=$(addprefix $(OBJDIR)/, $(OBJS))

all: $(KEYSTORE_LIBRARY)

$(OUT):
	mkdir -p $(OUT)




$(KEYSTORE_LIBRARY): $(OUT) ${OBJS_OUT}
		     ar -r $(KEYSTORE_LIBRARY) $(OBJS_OUT)
	    
.SUFFIXES:
.SUFFIXES: .c .o

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS)  -o $@ -c $<
clean:
	rm -f $(KEYSTORE_LIBRARY)
	rm -f $(OBJS)

regen: regenerate-from-asn1-source

regenerate-from-asn1-source:
	asn1c ../keystore.asn

