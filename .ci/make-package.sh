#!/bin/sh

if git rev-parse --ls-include-work-tree > /dev/null 2>&1; then
    cd `pwd`/`git rev-parse --show-cdup`
fi

if [ ! -z $1 ]; then
    RELEASE_VERSION=$1
fi

if [ -z $RELEASE_VERSION ]; then
    BRANCH_NAME=`echo $(\git symbolic-ref --short HEAD) | sed s:/:-:g`
    RELEASE_VERSION=$BRANCH_NAME
fi

echo $RELEASE_VERSION
PACKAGE_NAME=iutest-$RELEASE_VERSION

# make fused
make -C tools/fused
git add -f fused-src/*
git stash -u

# packaging
git archive --format=tar.gz 'stash@{0}' > $PACKAGE_NAME.tar.gz
git archive --format=zip    'stash@{0}' > $PACKAGE_NAME.zip

git stash drop
