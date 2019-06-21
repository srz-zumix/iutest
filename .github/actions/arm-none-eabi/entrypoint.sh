#!/bin/sh

set -exu

export PATH=$PATH:/usr/local/bin/gcc-arm-none-eabi-8-2018-q4-major/bin
arm-none-eabi-gcc --version

export CC=arm-none-eabi-gcc
export CXX=arm-none-eabi-g++

exec $*
