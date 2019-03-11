#!/bin/sh

set -exu

export PATH=$PATH:/usr/local/bin/gcc-arm-none-eabi-8-2018-q4-major/bin
arm-none-eabi-gcc --version
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++

# sh -c $*

cd test
make CC=arm-none-eabi-gcc CXX=arm-none-eabi-g++ showcxxversion showcxxmacros DEFS="--specs=nosys.specs -mthumb -mcpu=cortex-m3"
make CC=arm-none-eabi-gcc CXX=arm-none-eabi-g++ DEFS="--specs=nosys.specs -mthumb -mcpu=cortex-m3"
