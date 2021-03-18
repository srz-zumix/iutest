#!/bin/sh

OUTIMP=`pwd`/iutest.imp

if git rev-parse --ls-include-work-tree > /dev/null 2>&1; then
  pushd `pwd`/`git rev-parse --show-cdup`/include
else
  pushd ../../include
fi

echo "# Mappings for iutest" > $OUTIMP
echo "[" >> $OUTIMP

for f in `git ls-files internal/*.hpp`
do
  echo "  { include: [ \"$f\", private, \"iutest.hpp\", public ] }," >> $OUTIMP
done

echo "]" >> $OUTIMP

popd
