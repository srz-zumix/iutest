#!/bin/bash
# Usage: release.sh [version]

set -e

# make-package
BASEDIR=$(dirname "$0")
. $BASEDIR/../make-package.sh $*

echo ====================
echo osdn release
echo ====================
#echo $RELEASE_VERSION
echo $RELEASE_NAME

if ! $can_packaging; then
    echo is not packaging...
    exit 1
fi

if [ -z $RELEASE_NAME ]; then
    echo release name is not set
    exit 1
fi

if [ ! -e $PACKAGE_ROOT ]; then
    echo package is not exist
    exit 1
fi

cd $BASEDIR

FRS_ROOT=osdn_frs
osdn vars set project iutest
PACKAGE_ID=`osdn package | grep -o '[0-9]* iutest ' | cut -d ' ' -f 1`
if [ -z "$PACKAGE_ID" ]; then
  echo osdn package not found..
  exit 1
fi
RELEASE_ID=`osdn release --package $PACKAGE_ID | grep -o "[0-9]* $RELEASE_NAME " | cut -d ' ' -f 1`
if [ -z "$RELEASE_ID" ]; then
    osdn release create -v hidden --package $PACKAGE_ID $RELEASE_NAME
else
    echo $RELEASE_NAME is already exist
fi
RELEASE_ID=`osdn release --package $PACKAGE_ID | grep -o "[0-9]* $RELEASE_NAME " | cut -d ' ' -f 1`
if [ -z "$RELEASE_ID" ]; then
    echo package release is not found...
    exit 1
fi

if [ -e $FRS_ROOT ]; then
    rm -rf $FRS_ROOT
fi
osdn frs_mkdirs $FRS_ROOT 2>/dev/null
FRS_RELEASE_ROOT=$FRS_ROOT/iutest/$RELEASE_NAME
if [ ! -d $FRS_RELEASE_ROOT ]; then
    echo $FRS_RELEASE_ROOT is not exist...
    exit 1
fi
cp -r $IUTEST_ROOT/$PACKAGE_ROOT/* $FRS_RELEASE_ROOT
osdn frs_upload --package $PACKAGE_ID --release $RELEASE_ID $FRS_RELEASE_ROOT
