#!/bin/bash

svn --version
export SVN_URL=svn+ssh://srz_zumix@svn.osdn.jp/svnroot/iutest
svn log "$SVN_URL/trunk" -l 1
if svn log $SVN_URL/trunk -l 1 | grep -q 'git@[0-9a-zA-Z]*' ; then
  PREVCOMMIT=$(svn log $SVN_URL/trunk -l 1 | grep 'git@[0-9a-zA-Z]*' | head -1 | sed -e 's/.*git@\([0-9a-zA-Z]*\).*/\1/g')
  export PREVCOMMIT
fi
echo "$PREVCOMMIT"
if [ "$CI_COMMIT_ID" = "$PREVCOMMIT" ]; then
  svn copy "$SVN_URL/trunk" "$SVN_URL/tags/$CI_BRANCH" -m "$CI_BRANCH"
fi
