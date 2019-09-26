#!/bin/sh

cd test
DEFS="--specs=nosys.specs -mthumb -mcpu=cortex-m3"

make showcxxversion showcxxmacros DEFS="$DEFS"
make showcxxversion check_stdlib DEFS="$DEFS"
make DEFS="$DEFS"
