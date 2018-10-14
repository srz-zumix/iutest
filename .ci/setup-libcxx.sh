#!/bin/bash

# Checkout LLVM sources
git clone --depth=1 https://github.com/llvm-mirror/llvm.git llvm-source
git clone --depth=1 https://github.com/llvm-mirror/libcxx.git llvm-source/projects/libcxx
git clone --depth=1 https://github.com/llvm-mirror/libcxxabi.git llvm-source/projects/libcxxabi

# Setup libc++ options
if [ -z "$BUILD_32_BITS" ]; then
  export BUILD_32_BITS=OFF && echo disabling 32 bit build
fi

if [ -z "$COMPILER_CC" ]; then
  export COMPILER_CC=${CC}
fi

if [ -z "$COMPILER_CXX" ]; then
  export COMPILER_CC=${CXX}
fi

# Buid and Install
mkdir llvm-build
cd llvm-build
cmake -DCMAKE_C_COMPILER=${COMPILER_CC} -DCMAKE_CXX_COMPILER=${COMPILER_CXX} \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_INSTALL_PREFIX=/usr \
      -DLIBCXX_ABI_UNSTABLE=ON \
      -DLLVM_USE_SANITIZER=${LIBCXX_SANITIZER} \
      -DLLVM_BUILD_32_BITS=${BUILD_32_BITS} \
      ../llvm-source
make cxx -j4
make install-cxxabi install-cxx
cd ../
