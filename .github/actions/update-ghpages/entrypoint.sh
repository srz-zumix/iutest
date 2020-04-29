#!/bin/bash

set -exu

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
git clone --depth 1 -b gh-pages https://github.com/srz-zumix/iutest.git gh-pages

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
if [ -z "${INPUT_GITHUB_EMAIL}" ]; then
git config user.email "${GITHUB_ACTOR}@users.noreply.github.com"
else
git config user.email "${INPUT_GITHUB_EMAIL}"
fi
git config user.name "${GITHUB_ACTOR}"
git add --all
#export GIT_COMMIT_MESSAGE='update gh-pages git@$CI_COMMIT_ID'
#git commit -m $GIT_COMMIT_MESSAGE
git commit -m "update gh-pages git@$CI_COMMIT_ID"

git push "https://${GITHUB_ACTOR}:${INPUT_GITHUB_TOKEN}@github.com/srz-zumix/iutest.git"
