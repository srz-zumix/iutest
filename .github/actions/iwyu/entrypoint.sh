#!/bin/sh

set -exu

python --version
cmake --version
clang --version

LOGICAL_CPU_NUM=`grep processor /proc/cpuinfo | wc -l`
IWYU_TOOL_OPTION=${IWYU_TOOL_OPTION:--j${LOGICAL_CPU_NUM}}
IWYU_ARGS=${IWYU_ARGS:-}

# make working directory link
ln -sf "`pwd`/" /work

mkdir -p /tmp/build && cd /tmp/build

CC="clang" CXX="clang++" cmake -DCMAKE_C_COMPILER="clang" -DCMAKE_CXX_COMPILER="clang++" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON $*
iwyu_tool.py ${IWYU_TOOL_OPTION} -p . -- ${IWYU_ARGS}
