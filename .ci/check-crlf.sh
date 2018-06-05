#!/bin/sh
GREP_OPT="dont_match_dummy_string"
for i in `grep -oP '(?<=\*\.)[\S]+(?=.*eol=crlf)' ../.gitattributes`
do
    GREP_OPT="$i|${GREP_OPT}"
done

git grep --cached -I -P '\r' .. | grep -v -P "${GREP_OPT}"
