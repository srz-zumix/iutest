#!/bin/sh

set -ex

if [ -z "${GCC_VERSION}" ]; then
  echo "GCC_VERSION is empty. skip install gcc..."
  return
fi

. /etc/os-release
MAJOR_VERSION=$(echo ${VERSION_ID} | cut -d '.' -f1)

sudo apt-get -y --allow-unauthenticated update
sudo apt-get install software-properties-common
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
if [ "${MAJOR_VERSION}" -ge 19 ]; then
  sudo add-apt-repository -y ppa:ubuntu-toolchain-r/ppa
fi

sudo apt-get -y --allow-unauthenticated update
sudo apt-get -qq install "gcc-${GCC_VERSION}" "g++-${GCC_VERSION}"
sudo update-alternatives --install /usr/bin/gcc gcc \
  "/usr/bin/gcc-${GCC_VERSION}" 1990 \
  --slave /usr/bin/g++ g++ "/usr/bin/g++-${GCC_VERSION}"

update-alternatives --display gcc

"g++-${GCC_VERSION}" --version
g++ --version
