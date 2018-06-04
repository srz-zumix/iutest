#!/bin/sh
#git grep --cached -I $'\r'
GREP_OPT=
for i in `grep -oP '(?<=\*\.)[\S]+(?=.*eol=crlf)' ../.gitattributes`
do
    GREP_OPT=$i|${GREP_OPT}
done

echo "$GREP_OPT"
