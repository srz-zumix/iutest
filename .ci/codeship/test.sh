#!/bin/bash
# Codeship Test Console Setting
# ==============================================================================
# doxygen --version
# python --version
# export GH_PAGES_BRANCH=0
# if echo "$CI_BRANCH" | grep -q "gh-pages"; then export GH_PAGES_BRANCH=1; fi
# if [ $GH_PAGES_BRANCH == 0 ]; then make -C test/cpplint; fi
# if [ $GH_PAGES_BRANCH == 0 ]; then make -C test check_incg; fi
# if [ $GH_PAGES_BRANCH == 0 ]; then ! find projects -type f -print0 | xargs -0 grep '[d-zD-Z]:\\.*'; fi
# if [ $GH_PAGES_BRANCH == 0 ]; then make -C test/docs version-test; fi
# if [ $GH_PAGES_BRANCH == 0 ]; then make -C test/docs doxygen-test; fi
# if [ $GH_PAGES_BRANCH == 0 ]; then sh .ci/check-crlf.sh; fi
# if [ $GH_PAGES_BRANCH == 0 ]; then make editorconfig-self-lint; fi
# if git grep --cached -I -l -P '\r'; then exit 1; fi
# ==============================================================================

doxygen --version
python --version
export GH_PAGES_BRANCH=0
if echo "$CI_BRANCH" | grep -q "gh-pages"; then
  export GH_PAGES_BRANCH=1;
fi
if [ "$GH_PAGES_BRANCH" = 0 ]; then
  echo
  make -C test/cpplint
  make -C test check_incg
  ! find projects -type f -print0 | xargs -0 grep '[d-zD-Z]:\\'
  make -C test/docs version-test
  make -C test/docs doxygen-test
  sh .ci/check-crlf.sh
  make editorconfig-self-lint
fi
if git grep --cached -I -l -P '\r'; then
  exit 1
fi