#!/bin/sh

set -e

if [ -z ${GCC_VERSION+x} ]; then
  echo "GCC_VERSION is empty. skip install gcc..."
  return
fi

add-apt-repository -y ppa:ubuntu-toolchain-r/test
apt-get -y --allow-unauthenticated update
apt-get -qq install g++-${GCC_VERSION}
update-alternatives --install /usr/bin/gcc gcc \
  /usr/bin/gcc-${GCC_VERSION} 90 \
  --slave /usr/bin/g++ g++ /usr/bin/g++-${GCC_VERSION}
