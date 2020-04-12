#!/bin/sh

set -e

if [ -z ${CLANG_VERSION+x} ]; then
  echo "CLANG_VERSOIN is empty. skip install clang..."
  return
fi

. /etc/os-release
wget -qO - http://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
add-apt-repository -y 'deb http://apt.llvm.org/${VERSION_CODENAME}/ llvm-toolchain-${VERSION_CODENAME}-${CLANG_VERSION} main'
apt-get -y --allow-unauthenticated update
apt-get -qq install clang-${CLANG_VERSION}


if $INSATLL_CLANG_TOOLS; then
  apt-get -y --force-yes -qq install clang-$CLANG_VERSION clang-tools-$CLANG_VERSION
  CLANG_SLAVES="--slave /usr/bin/scan-build scan-build /usr/bin/scan-build-$CLANG_VERSION"
fi

update-alternatives --install /usr/bin/clang clang \
  /usr/bin/clang-${CLANG_VERSION} 360 \
  --slave /usr/bin/clang++ clang++ /usr/bin/clang++-${CLANG_VERSION} \
  ${CLANG_SLAVES}
