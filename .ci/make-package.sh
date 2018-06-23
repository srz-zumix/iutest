#!/bin/sh

if git rev-parse --ls-include-work-tree > /dev/null 2>&1; then
    cd `pwd`/`git rev-parse --show-cdup`
fi

if [ ! -z $1 ]; then
    RELEASE_VERSION=$1
    #echo $RELEASE_VERSION
fi

if [ -z $RELEASE_VERSION ]; then
    BRANCH_NAME=`echo $(\git symbolic-ref --short HEAD) | sed s:/:-:g`
    RELEASE_VERSION=$BRANCH_NAME
fi

if [ `echo ${RELEASE_VERSION} | grep -o "^[0-9].[0.9].[0-9]$"` ]; then
    RELEASE_VERSION=`echo ${RELEASE_VERSION} | grep -o "v[0-9].[0.9].[0-9]"`
    if [ -z $RELEASE_VERSION ]; then
        RELEASE_VERSION=v0.0.0
    fi
    RELEASE_VERSION=${RELEASE_VERSION:1}
fi

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
echo version $RELEASE_VERSION > package/RELEASENOTE

# create changelog
echo Changes for $RELEASE_VERSION > package/CHANGELOG
if [ `grep 'Changes for $RELEASE_VERSION' CHANGES.md` ]; then
    echo CHANGELOG is not found.
else
    cat CHANGES.md | while read line
    out=0
    do
        if [ $line == "Changes for $RELEASE_VERSION" ]; then
            out = 1
        fi
        if [ out == 1 ]; then
            if [ `echo $line | grep "Changes for .*"` ]; then
                echo $line >> package/CHANGELOG
            else
                out = 0
                exit 0
            fi
        fi
    done
fi

