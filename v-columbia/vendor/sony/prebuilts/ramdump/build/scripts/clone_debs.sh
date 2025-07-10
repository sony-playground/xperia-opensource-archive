#!/bin/bash

# Duplicates the debian packages from a common ramdump build.
#
# There is a limitation in C2D that any one package cannot be part of a
# snapshot with more than one version. To work around this we clone the
# packages from a common build creating unique debian package
# names for each product.

function dupe_deb()
{
    local _orig_deb=$1
    local _orig_product=$2
    local _product=$(echo $_orig_product | tr _ -)
    local _debfile=$(echo $_orig_deb | sed -r "s|.*?/||")
    local _newfile=$(echo $_debfile | sed -r "s/$SOURCE_PRODUCT/$_product/")
    local _tmpdir=$(mktemp -d --tmpdir=. debtmp_XXXXXXXX || exit 1)
    local _mbifile="$_tmpdir/util/data/mbi.xml"

    echo "Cloning '$_debfile' to '$_newfile' ..."
    dpkg-deb -x $_orig_deb $_tmpdir || exit 1
    dpkg-deb -e $_orig_deb $_tmpdir/DEBIAN || exit 1

    sed -r "s/$SOURCE_PRODUCT/$_product/" -i "$_tmpdir/DEBIAN/control" || exit 1
    if [ -f "$_mbifile" ] ; then
        sed -r "s/$ORIG_SOURCE_PRODUCT/$_orig_product/" -i "$_mbifile" || exit 1
    fi
    dpkg-deb -b $_tmpdir "$DEBOUTDIR/$_newfile" || exit 1
    if [ "$STORE_DEB" == "true" ]; then
			echo Saving $DEBOUTDIR/$_newfile
			repository addpackage $DEBOUTDIR/$_newfile
    fi
    rm -rf $_tmpdir

}

#######
# MAIN
#######
if [ ! -d ".repo" ] ; then
    echo "ERROR: $0 must be executed from the root of the build!" >&2
    exit 1
fi

usage() {
    echo "Usage: $0 [--save] <source_product> <list-of-clone-products>" >&2
    echo "Example: $0 rhine_cdb \"honami togari\"" >&2
}

argc=0
STORE_DEB="false"
while [ "$1" != "" ]; do
  if [ "$1" == "--save" ]; then
    STORE_DEB="true"
  else
		if [ $argc -eq 0 ]; then
			ORIG_SOURCE_PRODUCT=$1
			echo OrgSrc=$ORIG_SOURCE_PRODUCT
		elif  [ $argc -eq 1 ]; then
			TARGET_PRODUCTS=$1
			echo Targets=$TARGET_PRODUCTS
		else
			echo "Warning: To many arguments: " $argv
		fi
	  argc=`expr $argc + 1`
  fi
  shift
done

if [ $argc -lt 2 ] ; then
	usage
  exit 1
fi

DEBOUTDIR=$(readlink -e out/target/product/$ORIG_SOURCE_PRODUCT/deb/ || exit 1)
SOURCE_PRODUCT=$(echo $ORIG_SOURCE_PRODUCT | tr _ -)

_packages=$(find out/target/product/$ORIG_SOURCE_PRODUCT/ -name 'fw-*dump-*.deb')

for _package in $_packages; do
    for _product in $TARGET_PRODUCTS; do
        dupe_deb $_package $_product
    done
done

