#!/bin/bash

set -exu


if [ -z "${GITHUB_SHA}" ]; then
  export GITHUB_SHA=$(git rev-parse HEAD)
fi
export CI_COMMIT_ID="${GITHUB_SHA}"

export DIRNAME_="${GITHUB_REF#refs/heads/}"
export DIRNAME="${DIRNAME_#refs/tags/}"

if [ "${DIRNAME}" != 'master' ]; then
  if [[ ! "${DIRNAME}" =~ v.* ]]; then
      DIRNAME=test
  fi
fi

doxygen --version
dot -V || true

cd docs
export PATH=$PATH:"$PWD"
git config --global http.sslverify false
if [ -z "${INPUT_GITHUB_TOKEN}" ]; then
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
make gh-pages-ci

cd gh-pages

if [ -n "${INPUT_GITHUB_TOKEN}" ]; then
  if [ -z "${INPUT_GITHUB_EMAIL}" ]; then
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

if [ -z "${INPUT_GITHUB_TOKEN}" ]; then
  git push
else
  git push "https://${GITHUB_ACTOR}:${INPUT_GITHUB_TOKEN}@github.com/srz-zumix/iutest.git"
fi
