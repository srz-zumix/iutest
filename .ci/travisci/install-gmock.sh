#!/bin/sh

set -e

if [ -e /usr/src/gmock ]; then
  cp -r /usr/src/gmock googletest
  mv googletest/gmock googletest/googlemock
fi
if [ -e googletest/googlemock ]; then
  cd googletest/googlemock
  cmake . && cmake --build .
  export CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:$PWD/include
  export LIBRARY_PATH=$LIBRARY_PATH:$PWD
  cd -
fi
