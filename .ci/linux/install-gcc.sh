#!/bin/sh

set -ex

if [ -z ${GCC_VERSION+x} ]; then
  echo "GCC_VERSION is empty. skip install gcc..."
  return
fi

sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
sudo apt-get -y update
sudo apt-get -qq install g++-${GCC_VERSION}
sudo update-alternatives --install /usr/bin/gcc gcc \
  /usr/bin/gcc-${GCC_VERSION} 90 \
  --slave /usr/bin/g++ g++ /usr/bin/g++-${GCC_VERSION}
