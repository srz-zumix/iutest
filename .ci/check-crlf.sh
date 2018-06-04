#!/bin/sh
#git grep --cached -I $'\r'
for i in `grep -oP '(?<=\*\.)[\S]+(?=.*eol=crlf)' ../.gitattributes`
do
    cat find.txt | grep -v $i
    exit
done

cat find.txt
