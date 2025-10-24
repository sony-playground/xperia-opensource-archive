#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
#extract and build the compiler
cd $DIR
tar -zxvf asn1c-0.9.27.tar.gz
cd asn1c-0.9.27
./configure
make

mkdir -p ../autogen
cd ../autogen
#ToDo use asn1 file from project: platform/vendor/semc/s1/docs
../asn1c-0.9.27/asn1c/asn1c ../../../core/sin/SonyMobileSigningExtensions.asn1

getmakevar() {
	makefile="$1"
	var="$2"

	make -s getmakevar -f -  << EOI
include $makefile

getmakevar:
	@echo \$($var)
EOI
}

asn_objs_file="../autogen_obj.mk"
asn_sources=$(getmakevar Makefile.am.sample ASN_MODULE_SOURCES)
asn_objects=$(echo "$asn_sources" | sed 's/\.c/.o/g')
echo "asn1-objs := $asn_objects" > $asn_objs_file
echo 'asn1-objs := $(addprefix tools/asn1c_compiler/autogen/,$(asn1-objs))' >> $asn_objs_file
echo 'fsobjs += $(asn1-objs)' >> $asn_objs_file
echo 'include_dirs += tools/asn1c_compiler/autogen' >> $asn_objs_file
