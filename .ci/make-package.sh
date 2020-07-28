#!/bin/bash

set -e

if git rev-parse --ls-include-work-tree > /dev/null 2>&1; then
    IUTEST_ROOT=`pwd`/`git rev-parse --show-cdup`
    cd $IUTEST_ROOT
fi

if [ -n "$1" ]; then
    RELEASE_VERSION=$1
    echo $RELEASE_VERSION
fi

if [ -z $RELEASE_VERSION ]; then
    echo get branch name from HEAD
    git symbolic-ref --short HEAD >/dev/null 2>/dev/null && :
    if [ $? = 0 ]; then
      BRANCH_NAME=`echo $(\git symbolic-ref --short HEAD) | sed s:/:-:g` 2>/dev/null
      RELEASE_VERSION=$BRANCH_NAME
    fi
fi

if [ -z $RELEASE_VERSION ]; then
    echo get branch name from branch command
    BRANCH_NAME=`git branch | grep -e "^*" | cut -d' ' -f 2`
    if [ "${BRANCH_NAME}" = "(HEAD" ]; then
      BRANCH_NAME=`git branch | grep -e "^*" | cut -d' ' -f 5 | cut -d')' -f 1`
    fi
    RELEASE_VERSION=$BRANCH_NAME
fi

echo ${RELEASE_VERSION} | grep -e "^[0-9]*.[0.9]*.[0-9]*$" > /dev/null && :
if [ $? != 0 ]; then
    RELEASE_VERSION=`echo ${RELEASE_VERSION} | grep -e "v[0-9]*.[0.9]*.[0-9]*" || true`
    if [ -z "$RELEASE_VERSION" ]; then
        echo set dummy version
        RELEASE_VERSION=v0.0.0
    fi
    RELEASE_VERSION=${RELEASE_VERSION#v}
fi

if [ ! -e ./package ]; then
    mkdir package
fi

echo Release version $RELEASE_VERSION
RELEASE_NAME=v$RELEASE_VERSION
PACKAGE_NAME=iutest-$RELEASE_VERSION
#PACKAGE_ROOT=./package/v$RELEASE_VERSION
PACKAGE_ROOT=./package

if [ -e $PACKAGE_ROOT ]; then
    rm -rf $PACKAGE_ROOT
fi
mkdir $PACKAGE_ROOT

can_packaging=true

if [ -n "`git diff --cached --name-only`" ]; then
    echo staged diff detected...
    can_packaging=false
fi

if [ -n "`git diff --name-only`" ]; then
    echo diff detected...
    can_packaging=false
fi

if [ -n "`git clean -fdn`" ]; then
    echo untracked file detected...
    can_packaging=false
fi

if [ ${FORCE_PACKAGING:=0} -ne 0 ]; then
    can_packaging=true
fi

if $can_packaging; then
    echo create package
    # make fused
    make -C tools/fused --no-print-directory
    git add -f fused-src/*
    git -c user.name=make-package -c user.email=make-package@test.com stash -u

    # packaging
    mkdir -p package
    git archive --format=tar.gz 'stash@{0}' > $PACKAGE_ROOT/$PACKAGE_NAME.tar.gz
    git archive --format=zip    'stash@{0}' > $PACKAGE_ROOT/$PACKAGE_NAME.zip

    git stash drop
else
    echo skipped packaging...
fi

# create release note
echo release note
echo version $RELEASE_VERSION > $PACKAGE_ROOT/RELEASENOTE
cat $PACKAGE_ROOT/RELEASENOTE
if [ $? != 0 ]; then
    echo "$(<$PACKAGE_ROOT/RELEASENOTE)"
fi

# create changelog
CHANGELOG_FILE=$PACKAGE_ROOT/CHANGELOG-ja.md
echo change log
echo Changes for $RELEASE_VERSION > $CHANGELOG_FILE
if [ `grep 'Changes for $RELEASE_VERSION' CHANGES.md` ]; then
    echo CHANGELOG is not found.
else
    CHANGELOG_ENABLE=0
    while read
    do
        line=$REPLY
        if echo "$line" | grep -e "Changes for $RELEASE_VERSION$" > /dev/null; then
            CHANGELOG_ENABLE=1
        elif [ $CHANGELOG_ENABLE = 1 ]; then
            if echo "$line" | grep -e "Changes for .*" > /dev/null; then
                break
            elif echo "$line" | grep -v "^--*$" > /dev/null; then
                echo "$line" >> $CHANGELOG_FILE
            fi
        fi
    done < CHANGES.md
fi

echo --------------------
cat $CHANGELOG_FILE
if [ $? != 0 ]; then
    echo "$(<$CHANGELOG_FILE)"
fi
