#!/bin/sh

set -e

if [ "${USE_GTEST_HEAD}" = '1' ]; then
  git clone https://github.com/google/googletest.git googletest
else
  if [ -e /usr/src/googletest ]; then
    cp -r /usr/src/googletest googletest
  else
    mkdir googletest
    if [ -e /usr/src/gtest ]; then
      cp -r /usr/src/gtest googletest
    elif [ -e /usr/src/gmock/gtest ]; then
      cp -r /usr/src/gmock/gtest googletest
    else
      exit 1
    fi
    mv googletest/gtest googletest/googletest
    cd googletest
    ln -s googletest gtest
    cd -
  fi
fi

cd googletest/googletest
cmake . && cmake --build .
export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$PWD/include
export LIBRARY_PATH=$LIBRARY_PATH:$PWD
cd -
