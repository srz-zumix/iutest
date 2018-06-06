#!/bin/sh

if git rev-parse --ls-include-work-tree > /dev/nul 2>&1; then
    cd `pwd`/`git rev-parse --show-cdup`
fi
GREP_OPT=dont_match_dummy_string
for i in `grep -oP '(?<=\*\.)[\S]+(?=.*eol=crlf)' .gitattributes`
do
    GREP_OPT="$i|${GREP_OPT}"
done

git grep $* -I -P '\r' | grep -v -P "${GREP_OPT}"
