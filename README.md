[![GitHub Actions Status](https://github.com/srz-zumix/iutest/workflows/GitHub%20Actions/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions?query=workflow%3A%22GitHub+Actions%22)
[![Linux Tests](https://github.com/srz-zumix/iutest/actions/workflows/linux.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/linux.yml)
[![Windows Tests](https://github.com/srz-zumix/iutest/actions/workflows/windows.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/windows.yml)
[![Apple Platform Tests](https://github.com/srz-zumix/iutest/actions/workflows/apple.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/apple.yml)
[![Compiler Matrix Tests](https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml)
[![Config Tests](https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml)
[![GitLab CI pipeline status](https://gitlab.com/srz-zumix/iutest-test/badges/master/pipeline.svg)](https://gitlab.com/srz-zumix/iutest-test/commits/master)
  
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e6407b63c9c844d080ed71c7707bded9?branch=master)](https://www.codacy.com/app/srz-zumix/iutest?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=srz-zumix/iutest&amp;utm_campaign=Badge_Grade)
[![Codecov](https://codecov.io/gh/srz-zumix/iutest/branch/master/graph/badge.svg)](https://codecov.io/gh/srz-zumix/iutest)
[![Coveralls Coverage Status](https://coveralls.io/repos/github/srz-zumix/iutest/badge.svg?branch=master)](https://coveralls.io/github/srz-zumix/iutest?branch=master)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/1316/badge.svg)](https://scan.coverity.com/projects/srz-zumix-iutest)
[![GuardRails badge](https://badges.guardrails.io/srz-zumix/iutest.svg?token=fe1bb5ca5f743800d26e4d2b7282c5b316df83c0b228048f4192510bdd7280f0)](https://dashboard.guardrails.io/default/gh/srz-zumix/iutest)
[![GitHub Actions reviewdog Status](https://github.com/srz-zumix/iutest/workflows/GitHub%20Actions%20-%20reviewdog/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions?query=workflow%3A%22GitHub+Actions+-+reviewdog%22)  
[![New(3-clause) BSD License](https://img.shields.io/badge/license-New_BSD-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)
[![NuGet version](https://badge.fury.io/nu/iutest.svg)](https://badge.fury.io/nu/iutest)  
[![support](https://img.shields.io/badge/%24-support-orange.svg)](https://amzn.asia/6fNxDZU)

iutest
==========

iutest - iris unit test framework

Welcome to the iutest
--------------------------------------------------

iutest is framework for writing C++ tests.

Features
--------------------------------------------------

* An [XUnit](https://en.wikipedia.org/wiki/XUnit) test framework.
* Header only, no external dependencies.
* Test discovery.
* XML/JUnit test report generation.
* Assertions.
  + A rich set of assertions.
  + User-defined assertions.
  + Power-assert (expression-assert).
  + Matchers.
  + Fatal and non-fatal, warning, assume failures.
* Value-parameterized tests.
* Type-parameterized tests.
* Advanced parameter generation.
  + Pairwise parameter.
  + CSV parameter.
  + Any parameter.
  + Random parameter.
  + Multiple parameters can be concatenated.
* Test packages (grouping).
* Skip test.
* Private member test.
* Japanese test name (C++03). 
* Various options for running the tests.
* Compatible with [Google Test](https://github.com/google/googletest). (1.5 or later)

CMake builds of `projects/cmake` default to C++17 unless `CMAKE_CXX_STANDARD` is set.
When linking `iutest::iutest` or `iutest::iutest_main`, build the libraries with
the same C++ standard and settings as the consuming application. For header-only
use, link `iutest::headers` instead.

Platforms
--------------------------------------------------

* Windows
* Linux
  * PowerPC: `ppc64le` (little-endian), `ppc64` and 32-bit `ppc` (big-endian).
    CI cross-compiles with GCC on Ubuntu 24.04 and runs the tests with QEMU
    user mode. iutest's bit-based `long double` comparisons, including the
    dedicated assertions and matchers, do not support the IBM double-double ABI: its two
    binary64 components do not have a single IEEE 754 bit layout.
* MacOS
* FreeBSD
* Cygwin
* MinGW
* ESP8266 / ESP32 (see the PlatformIO and Arduino CLI builds below)

### ESP8266 and ESP32 PlatformIO builds

With [PlatformIO Core](https://docs.platformio.org/en/stable/core/index.html)
installed, run `pio run --project-dir test/platformio` from the repository root.
This compiles and links the same Google Test compatibility smoke test for both
Arduino targets. No hardware is required, and no firmware is uploaded or run.

### ESP32 Arduino build

Create `iutest_esp32/iutest_esp32.ino` with the following smoke test:

```cpp
#include <Arduino.h>
#include "gtest/iutest_switch.hpp"

#if !defined(IUTEST_OS_ESP32) || !defined(GTEST_OS_ESP32)
#  error ESP32 platform detection failed
#endif

TEST(Esp32Smoke, Addition)
{
    EXPECT_EQ(4, 2 + 2);
}

void setup()
{
    Serial.begin(115200);
    ::testing::InitGoogleTest();
    Serial.printf("iutest result: %d\n", RUN_ALL_TESTS());
}

void loop() {}
```

With [Arduino CLI](https://arduino.github.io/arduino-cli/) installed, run the
following from the repository root, with the sketch directory created there:

```sh
esp32_index=https://espressif.github.io/arduino-esp32/package_esp32_index.json
arduino-cli core update-index --additional-urls "$esp32_index"
arduino-cli core install esp32:esp32@2.0.17 --additional-urls "$esp32_index"
arduino-cli compile --fqbn esp32:esp32:esp32 \
  --build-property "compiler.cpp.extra_flags=-I\"$PWD/include\"" \
  "$PWD/iutest_esp32"
```

A board is not required to compile and link the sketch. On a board, the final
serial line should be `iutest result: 0`. ESP targets default to plain console
output, without the stdio file backend, environment variables, or socket result
streaming.

Compiler
--------------------------------------------------

* VC++6~
* GCC 3.4.6~
* Clang 3.1~
* Intel Compiler
* Zapcc

Documentation
--------------------------------------------------

* in repository  
  doc/index.html  
* online document  
  [latest released version](https://srz-zumix.github.io/iutest/latest)  
  [GitHub master branch](https://srz-zumix.github.io/iutest/master)  

Project page
--------------------------------------------------

* [OSDN Project page](https://iutest.osdn.jp/)  
* [GitHub](https://github.com/srz-zumix/iutest)  

Support
--------------------------------------------------

* Use [GitHub issues](https://github.com/srz-zumix/iutest/issues) to report bugs and feature requests.
* Ask questions at the twitter ([@srz_zumix](https://twitter.com/srz_zumix))

Tools
--------------------------------------------------

* fused  
  make fused-src.
* Twilio  
  notifies the test results using Twilio
* Wandbox (deprecated) 
  tools to make use of the iutest in [Wandbox](https://wandbox.org/)

Tests
--------------------------------------------------

|CI|master|develop|Tests|
|:--|:--|:--|:--|
|[Codacy](https://www.codacy.com/)|[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e6407b63c9c844d080ed71c7707bded9?branch=master)](https://www.codacy.com/app/srz-zumix/iutest?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=srz-zumix/iutest&amp;utm_campaign=Badge_Grade)|[![Codacy Badge](https://api.codacy.com/project/badge/Grade/e6407b63c9c844d080ed71c7707bded9?branch=develop)](https://www.codacy.com/app/srz-zumix/iutest?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=srz-zumix/iutest&amp;utm_campaign=Badge_Grade)|Shellcheck, Cppcheck, PyLint, etc...|
|[Coverity Scan](https://scan.coverity.com)|[![Coverity Scan Build Status](https://scan.coverity.com/projects/1316/badge.svg)](https://scan.coverity.com/projects/srz-zumix-iutest)||Coverity Scan|
|[GitHub Actions](https://github.com/srz-zumix/iutest/actions?query=workflow%3A"GitHub+Actions")|[![GitHub Actions Status](https://github.com/srz-zumix/iutest/workflows/GitHub%20Actions/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions?query=workflow%3A%22GitHub+Actions%22+branch%3Amaster)|[![GitHub Actions Status](https://github.com/srz-zumix/iutest/workflows/GitHub%20Actions/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions?query=workflow%3A%22GitHub+Actions%22+branch%3Adevelop)|Basic test (Windows LLVM clang and mingw and [zapcc](https://github.com/yrnkrn/zapcc)), EditorConfig Lint, Include What You Use, arm-none-eabi-gcc build|
|[GitHub Actions - Google Test Compatible](https://github.com/srz-zumix/iutest/actions?query=workflow%3A"Google+Test+Compatible")|[![Google Test Compatible](https://github.com/srz-zumix/iutest/actions/workflows/gtest-compat.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/gtest-compat.yml)|[![Google Test Compatible](https://github.com/srz-zumix/iutest/actions/workflows/gtest-compat.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/gtest-compat.yml)|Google Test/Mock compatible test for released versions|
|[GitHub Actions - reviewdog](https://github.com/srz-zumix/iutest/actions?query=workflow%3A"GitHub+Actions+reviewdog")|[![GitHub Actions Reviewdog Status](https://github.com/srz-zumix/iutest/workflows/GitHub%20Actions%20-%20reviewdog/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions?query=workflow%3A%22GitHub+Actions+-+reviewdog%22+branch%3Amaster)||Reviewdog (shellcheck, cpplint)|
|[GitHub Actions - Update GitHubPages](https://github.com/srz-zumix/iutest/actions?query=workflow%3A"GitHubPages")|[![Update GitHubPages Status](https://github.com/srz-zumix/iutest/workflows/GitHubPages/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions?query=workflow%3A%22GitHubPages%22+branch%3Amaster)||Update documents|
|[GitHub Actions - Linux Tests](https://github.com/srz-zumix/iutest/actions/workflows/linux.yml)|[![Linux Tests](https://github.com/srz-zumix/iutest/actions/workflows/linux.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/linux.yml)|[![Linux Tests](https://github.com/srz-zumix/iutest/actions/workflows/linux.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/linux.yml)|gcc/clang Basic tests, use lib, sample run, scan-build, optimize options, long double, arm64|
|[GitHub Actions - Windows Tests](https://github.com/srz-zumix/iutest/actions/workflows/windows.yml)|[![Windows Tests](https://github.com/srz-zumix/iutest/actions/workflows/windows.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/windows.yml)|[![Windows Tests](https://github.com/srz-zumix/iutest/actions/workflows/windows.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/windows.yml)|Visual Studio, Cygwin, MINGW, NMAKE, PREFAST (Code Analysis), package, NuGet, vcperf, MSVC on Wine|
|[GitHub Actions - Apple Platform Tests](https://github.com/srz-zumix/iutest/actions/workflows/apple.yml)|[![Apple Platform Tests](https://github.com/srz-zumix/iutest/actions/workflows/apple.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/apple.yml)|[![Apple Platform Tests](https://github.com/srz-zumix/iutest/actions/workflows/apple.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/apple.yml)|macOS std version tests, Xcode build, iOS build|
|[GitHub Actions - Android Build](https://github.com/srz-zumix/iutest/actions/workflows/android.yml)|[![Android Build](https://github.com/srz-zumix/iutest/actions/workflows/android.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/android.yml)|[![Android Build](https://github.com/srz-zumix/iutest/actions/workflows/android.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/android.yml)|Android NDK build|
|[GitHub Actions - FreeBSD Tests](https://github.com/srz-zumix/iutest/actions/workflows/freebsd.yml)|[![FreeBSD Tests](https://github.com/srz-zumix/iutest/actions/workflows/freebsd.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/freebsd.yml)|[![FreeBSD Tests](https://github.com/srz-zumix/iutest/actions/workflows/freebsd.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/freebsd.yml)|FreeBSD Basic tests|
|[GitHub Actions - Compiler Matrix Tests](https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml)|[![Compiler Matrix Tests](https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml)|[![Compiler Matrix Tests](https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/compiler-matrix.yml)|gcc/clang each version Basic test, C++98 syntax test|
|[GitHub Actions - Config Tests](https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml)|[![Config Tests](https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml)|[![Config Tests](https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/config-tests.yml)|Config matrix test, Visual Studio build option matrix|
|[GitHub Actions - Lint and Checks](https://github.com/srz-zumix/iutest/actions/workflows/lint.yml)|[![Lint and Checks](https://github.com/srz-zumix/iutest/actions/workflows/lint.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/lint.yml)|[![Lint and Checks](https://github.com/srz-zumix/iutest/actions/workflows/lint.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/lint.yml)|cpplint, cppcheck, include guard, documents, EditorConfig, goodcheck, markdown lint, iuwandbox unit tests|
|[GitHub Actions - Benchmark](https://github.com/srz-zumix/iutest/actions/workflows/benchmark.yml)|[![Benchmark](https://github.com/srz-zumix/iutest/actions/workflows/benchmark.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/benchmark.yml)|[![Benchmark](https://github.com/srz-zumix/iutest/actions/workflows/benchmark.yml/badge.svg?branch=develop)](https://github.com/srz-zumix/iutest/actions/workflows/benchmark.yml)|Benchmark test, gcc 8/9 all tests|
|[GitHub Actions - Wandbox](https://github.com/srz-zumix/iutest/actions/workflows/wandbox.yml)|[![Wandbox](https://github.com/srz-zumix/iutest/actions/workflows/wandbox.yml/badge.svg?branch=master)](https://github.com/srz-zumix/iutest/actions/workflows/wandbox.yml)||iuwandbox tests|
|[GitLab CI](https://about.gitlab.com/product/continuous-integration/)|[![GitLab CI pipeline status](https://gitlab.com/srz-zumix/iutest-test/badges/master/pipeline.svg)](https://gitlab.com/srz-zumix/iutest-test/commits/master)|[![GitLab CI pipeline status](https://gitlab.com/srz-zumix/iutest-test/badges/develop/pipeline.svg)](https://gitlab.com/srz-zumix/iutest-test/commits/develop)|Google Test/Google Mock compatibility (HEAD)|

Basic test

[Compiler and OS tests status](./docs/status/compiler_os_ci_status.rst)

Coverage
--------------------------------------------------

[![Coveralls Coverage Status](https://coveralls.io/repos/github/srz-zumix/iutest/badge.svg?branch=master)](https://coveralls.io/github/srz-zumix/iutest?branch=master)  

[![Codecov](https://codecov.io/gh/srz-zumix/iutest/branch/master/graph/badge.svg)](https://codecov.io/gh/srz-zumix/iutest)  
[![Codecov](https://codecov.io/gh/srz-zumix/iutest/branch/master/graphs/icicle.svg)](https://codecov.io/gh/srz-zumix/iutest)  

Contributing change
--------------------------------------------------

Please read the [`CONTRIBUTING.md`](CONTRIBUTING.md) for details on how to contribute to this project.

License
--------------------------------------------------

    Copyright (c) 2011-2021, Takazumi Shirayanagi,
    All rights reserved.

    This software is released under the New(3-clause) BSD License, see LICENSE

    If you distribute iutest, you might enjoy the [LICENSE-MIXING](docs/LICENSE-MIXING) document.
