########################################################################
# CMake build script for iutest vcpkg port test.
#

cmake_minimum_required(VERSION 3.10)

project(iutest_vcpkg_test CXX)

find_package(iutest CONFIG REQUIRED)
find_package(IUTEST CONFIG REQUIRED)

enable_testing()

add_executable(iutest_vcpkg_test main.cpp)
target_link_libraries(iutest_vcpkg_test PRIVATE iutest::iutest_main)
add_test(NAME iutest_vcpkg_test COMMAND iutest_vcpkg_test)
