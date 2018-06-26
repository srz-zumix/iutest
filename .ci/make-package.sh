#!/bin/bash

if git rev-parse --ls-include-work-tree > /dev/null 2>&1; then
    cd `pwd`/`git rev-parse --show-cdup`
fi

if [ ! -z $1 ]; then
    RELEASE_VERSION=$1
    #echo $RELEASE_VERSION
fi

if [ -z $RELEASE_VERSION ]; then
    BRANCH_NAME=`echo $(\git symbolic-ref --short HEAD) | sed s:/:-:g` 2>/dev/null
    RELEASE_VERSION=$BRANCH_NAME
fi

if [ -z $RELEASE_VERSION ]; then
    BRANCH_NAME=`git branch | grep -e "^*" | cut -d' ' -f 2`
    RELEASE_VERSION=$BRANCH_NAME
fi

echo ${RELEASE_VERSION} | grep -e "^[0-9].[0.9].[0-9]$" > /dev/null
if [ $? != 0 ]; then
    RELEASE_VERSION=`echo ${RELEASE_VERSION} | grep -e "v[0-9].[0.9].[0-9]"`
    if [ -z "$RELEASE_VERSION" ]; then
        echo set dummy version
        RELEASE_VERSION=v0.0.0
    fi
    echo ${RELEASE_VERSION#v}
    RELEASE_VERSION=${RELEASE_VERSION#v}
fi

if [ -e ./package ]; then
    rm -rf ./package
fi
mkdir package

echo $RELEASE_VERSION
PACKAGE_NAME=iutest-$RELEASE_VERSION

if [ `git diff --name-only` ]; then
    echo diff detected...
#    exit 1
else
    # make fused
    make -C tools/fused
    git add -f fused-src/*
    git stash -u

    # packaging
    mkdir -p package
    git archive --format=tar.gz 'stash@{0}' > package/$PACKAGE_NAME.tar.gz
    git archive --format=zip    'stash@{0}' > package/$PACKAGE_NAME.zip

    git stash drop
fi

# create release note
echo release note
echo version $RELEASE_VERSION > package/RELEASENOTE
cat package/RELEASENOTE
if [ $? != 0 ]; then
    echo "$(<package/RELEASENOTE)"
fi

# create changelog
CHANGELOG_FILE=package/CHANGELOG-ja
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
