#!/bin/sh

set -exu

python --version
cmake --version
clang --version

# make working directory link
ln -sf "`pwd`/" /work

mkdir -p /tmp/build && cd /tmp/build

CC="clang" CXX="clang++" cmake -DCMAKE_C_COMPILER="clang" -DCMAKE_CXX_COMPILER="clang++" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON $*
iwyu_tool.py -p .
