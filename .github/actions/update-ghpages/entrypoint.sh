#!/bin/bash

set -eu

BASEDIR=$(dirname $0)

if [ -z "${GITHUB_SHA+x}" ]; then
  GITHUB_SHA=$(git rev-parse HEAD)
  export GITHUB_SHA
fi
export CI_COMMIT_ID="${GITHUB_SHA}"

if [ -z "${GITHUB_REF+x}" ]; then
  GITHUB_REF=$(git describe --tags)
  if [[ ! "${GITHUB_REF}" =~ v[0-9]*\.[0-9]*\.[0-9]*$ ]]; then
    GITHUB_REF=$(git symbolic-ref --short HEAD)
  fi
  export GITHUB_REF
fi
export DIRNAME_="${GITHUB_REF#refs/heads/}"
export DIRNAME="${DIRNAME_#refs/tags/}"

if [ "${DIRNAME}" != 'master' ]; then
  if [[ "${DIRNAME}" =~ v.* ]]; then
      DIRNAME=latest
  else
      DIRNAME=test
  fi
fi

echo ${DIRNAME}

#
# documents
#

doxygen --version
dot -V || true

cd docs
make clean

export PATH=$PATH:"$PWD"
git config --global http.sslverify false
if [ -z "${INPUT_GITHUB_TOKEN+x}" ]; then
  git clone --depth 1 -b gh-pages git@github.com:srz-zumix/iutest.git gh-pages
else
  git clone --depth 1 -b gh-pages https://github.com/srz-zumix/iutest.git gh-pages
fi

OUTDIR="gh-pages/${DIRNAME}"
if [ -d "${OUTDIR}" ]; then
  cd "${OUTDIR}"
  git rm -r *
  cd -
fi

make
make gh-pages GHPAGES_DIR="${OUTDIR}"
if [ "${DIRNAME}" = 'master' ]; then
  make gh-pages-for-master
fi

#
# cppcheck
#

cd ${BASEDIR}
make -C test/cppcheck html HTML_REPORT_DIR=${BASEDIR}/docs/gh-pages/${DIRNAME}/cppcheck

#
# commit
# 
cd ${BASEDIR}/docs/gh-pages

if [ -n "${INPUT_GITHUB_TOKEN+x}" ]; then
  if [ -z "${INPUT_GITHUB_EMAIL+x}" ]; then
  git config user.email "${GITHUB_ACTOR}@users.noreply.github.com"
  else
  git config user.email "${INPUT_GITHUB_EMAIL}"
  fi
  git config user.name "${GITHUB_ACTOR}"
fi
git add --all
#export GIT_COMMIT_MESSAGE='update gh-pages git@$CI_COMMIT_ID'
#git commit -m $GIT_COMMIT_MESSAGE
git commit -m "update gh-pages git@$CI_COMMIT_ID"

if [ -z "${INPUT_GITHUB_TOKEN+x}" ]; then
  git push
else
  git push "https://${GITHUB_ACTOR}:${INPUT_GITHUB_TOKEN}@github.com/srz-zumix/iutest.git"
fi
