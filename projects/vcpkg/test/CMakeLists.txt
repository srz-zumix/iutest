########################################################################
# CMake build script for iutest vcpkg port test.
#

cmake_minimum_required(VERSION 3.10)

project(iutest_vcpkg_test CXX)

find_package(iutest CONFIG REQUIRED)
find_package(IUTEST CONFIG REQUIRED)

if (NOT TARGET iutest::headers OR NOT TARGET iutest::iutest OR NOT TARGET iutest::iutest_main)
  message(FATAL_ERROR "Missing iutest CMake targets")
endif()

enable_testing()

add_executable(iutest_vcpkg_test main.cpp)
target_link_libraries(iutest_vcpkg_test PRIVATE iutest::iutest_main)
add_test(NAME iutest_vcpkg_test COMMAND iutest_vcpkg_test)

add_executable(iutest_headers_test main.cpp)
target_compile_definitions(iutest_headers_test PRIVATE IUTEST_USE_MAIN)
target_link_libraries(iutest_headers_test PRIVATE iutest::headers)
add_test(NAME iutest_headers_test COMMAND iutest_headers_test)
