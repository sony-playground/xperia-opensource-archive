export FCS_MAIN=../../../../..
# The platform is Kumano-plus but this environment is for sdx50m (5G modem)
export FCS_PLATFORM=sdx50m
export FCS_HWCONFIG=hwconf_x
# Flag CFG_IGNORE_BINDING_DEVID should only be used for sdx50m
export FCS_CFLAGS=-DCFG_IGNORE_BINDING_DEVID
# Test environment generated from XFL manifest
export FCS_CERTS=$(abspath $(FCS_MAIN)/../certs)
export FCS_MBEDTLS=$(abspath $(FCS_MAIN)/../../../../external/mbedtls)

include ../common.mk

