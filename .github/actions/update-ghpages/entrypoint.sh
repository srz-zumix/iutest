#!/bin/bash

set -exu

export CI_COMMIT_ID=${GITHUB_SHA}
export PREVCOMMIT=${CI_COMMIT_ID}^

export DIRNAME_=${GITHUB_REF#refs/heads/}
export DIRNAME=${DIRNAME_#refs/tags/}

if [ ${DIRNAME} != 'master' ]; then
  if [ ! ${DIRNAME} =~ v.* ]; then
      DIRNAME=test
  fi
fi

git clone -b gh-pages --depth 1 git@github.com:srz-zumix/iutest.git gh-pages-temp
cd gh-pages-temp
git log -n -1
if `git log -n 1 | grep -q 'git@[0-9a-zA-Z]*'` ; then export PREVCOMMIT=`git log -n 1 | grep 'git@[0-9a-zA-Z]*' | head -1 | sed -e 's/.*git@\([0-9a-zA-Z]*\).*/\1/g'`; fi
cd ../
echo $PREVCOMMIT
export GH_PAGES_UPDATE=0
if ! git diff $CI_COMMIT_ID:include $PREVCOMMIT:include --exit-code --quiet; then export GH_PAGES_UPDATE=1; fi
if ! git diff $CI_COMMIT_ID:docs $PREVCOMMIT:docs --exit-code --quiet; then export GH_PAGES_UPDATE=1; fi

doxygen --version
dot --version || true
cd docs
export PATH=$PATH:$PWD
echo $PATH
git clone -b gh-pages git@github.com:srz-zumix/iutest.git gh-pages

OUTDIR=gh-pages/${DIRNAME}

if [ -d "${OUTDIR}" ]; then
  cd ${OUTDIR}
  git rm -r *
  cd -
fi

make
make gh-pages GHPAGES_DIR=${OUTDIR}

cd gh-pages
git config user.email "zumix.cpp@gmail.com"
git config user.name "${GITHUB_ACTOR}"
git add --all
#export GIT_COMMIT_MESSAGE='update gh-pages git@$CI_COMMIT_ID'
#git commit -m $GIT_COMMIT_MESSAGE
git commit -m "update gh-pages git@$CI_COMMIT_ID"
echo $GH_PAGES_UPDATE
if [ $GH_PAGES_UPDATE == 1 ]; then git push; fi
