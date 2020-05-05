#!/bin/bash

svn --version
svn co svn+ssh://srz_zumix@svn.osdn.jp/svnroot/iutest/trunk svn
git clone git@github.com:srz-zumix/iutest.git git-svn
cp -r svn/.svn git-svn
rm -rf git-svn/.git
cd git-svn
ls
svn st
if svn st | grep -q '^!' ; then
  svn st | grep '^!' | awk '{print $2}' | xargs svn delete
fi
svn add * --force
svn st
export PREVCOMMIT=
svn log . -l 1
if svn log . -l 1 | grep -q 'git@[0-9a-zA-Z]*' ; then
  PREVCOMMIT=$(svn log . -l 1 | grep 'git@[0-9a-zA-Z]*' | head -1 | sed -e 's/.*git@\([0-9a-zA-Z]*\).*/\1/g')
  export PREVCOMMIT
fi
echo "$PREVCOMMIT"
git log "$CI_COMMIT_ID" -n 1 --pretty="%B%ngit@%H%nhttps://github.com/srz-zumix/iutest/commit/%H" > ../svn.msg
if [ -n "$PREVCOMMIT" ]; then
  git --no-pager log "$PREVCOMMIT..$CI_COMMIT_ID^" --pretty="---------------%n%B%ngit@%H%n" >> ../svn.msg;
fi
tr -d \\r < ../svn.msg > ../svn_lf.msg
cat ../svn_lf.msg
svn commit --file ../svn_lf.msg
