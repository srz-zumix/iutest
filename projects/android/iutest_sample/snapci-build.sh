#!/bin/bash
# -*- coding: utf-8 -*-

export ANDROID_HOME=`pwd`/android-sdk
export PATH=${PATH}:${ANDROID_HOME}/tools:${ANDROID_HOME}/platform-tools

# download SDK
download-android
echo y | android update sdk --no-ui --filter platform-tool > /dev/null
echo y | android update sdk --no-ui --filter android-18    > /dev/null

# download NDK
ANDROID_NDK_VERSION=android-ndk-r10c
ANDROID_NDK_URL=http://dl.google.com/android/ndk
# if [ `uname -m` = x86_64 ]; then
#	wget ${ANDROID_NDK_URL}/${ANDROID_NDK_VERSION}-linux-x86_64.bin -q -O ndk.bin
#else
#	wget ${ANDROID_NDK_URL}/${ANDROID_NDK_VERSION}-linux-x86.bin    -q -O ndk.bin
#fi
wget ${ANDROID_NDK_URL}/${ANDROID_NDK_VERSION}-linux-x86_64.bin -q -O ndk.bin
chmod a+x ndk.bin
./ndk.bin > /dev/null

# Build
export ANDROID_NDK_HOME=`pwd`/${ANDROID_NDK_VERSION}
export PATH=${PATH}:${ANDROID_NDK_HOME}
ndk-build
 