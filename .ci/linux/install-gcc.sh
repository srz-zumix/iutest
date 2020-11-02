#!/bin/sh

set -e

if [ -z ${GCC_VERSION+x} ]; then
  echo "GCC_VERSION is empty. skip install gcc..."
  return
fi

. /etc/os-release
MAJOR_VERSION=$(echo ${VERSION_ID} | cut -d '.' -f1)

if [ "${MAJOR_VERSION}" -lt 19 ]; then
  sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
else
  sudo add-apt-repository -y ppa:ubuntu-toolchain-r/ppa
fi

sudo apt-get -y --allow-unauthenticated update
sudo apt-get -qq install "g++-${GCC_VERSION}"
sudo update-alternatives --install /usr/bin/gcc gcc \
  /usr/bin/gcc-${GCC_VERSION} 90 \
  --slave /usr/bin/g++ g++ /usr/bin/g++-${GCC_VERSION}
