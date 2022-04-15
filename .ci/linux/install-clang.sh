#!/bin/sh

set -ex

if [ -z "${CLANG_VERSION}" ]; then
  echo "CLANG_VERSION is empty. skip install clang..."
  return
fi

. /etc/os-release
wget -qO - http://apt.llvm.org/llvm-snapshot.gpg.key | sudo apt-key add -
sudo add-apt-repository -y "deb http://apt.llvm.org/${VERSION_CODENAME}/ llvm-toolchain-${VERSION_CODENAME}-${CLANG_VERSION} main"
sudo apt-get -y --allow-unauthenticated update
sudo apt-get -qq install "clang-${CLANG_VERSION}"


if $INSATLL_CLANG_TOOLS; then
  sudo apt-get -y --force-yes -qq install "clang-tools-${CLANG_VERSION}"
  CLANG_SLAVES="--slave /usr/bin/scan-build scan-build /usr/bin/scan-build-${CLANG_VERSION}"
fi

# shellcheck disable=SC2086
sudo update-alternatives --install /usr/bin/clang   clang   "/usr/bin/clang-${CLANG_VERSION}" 1990  \
                         --slave   /usr/bin/clang++ clang++ "/usr/bin/clang++-${CLANG_VERSION}"     \
                        ${CLANG_SLAVES}

update-alternatives --display clang

"clang++-${CLANG_VERSION}" --version
clang++ --version
