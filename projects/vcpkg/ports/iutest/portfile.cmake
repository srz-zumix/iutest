# When this port is used as an overlay port inside the iutest repository,
# build from the local source tree. Otherwise, download the tagged release.
get_filename_component(IUTEST_LOCAL_SOURCE_PATH "${CURRENT_PORT_DIR}/../../../.." ABSOLUTE)
if(EXISTS "${IUTEST_LOCAL_SOURCE_PATH}/include/iutest.hpp"
    AND EXISTS "${IUTEST_LOCAL_SOURCE_PATH}/projects/vcpkg/ports/iutest/portfile.cmake")
  set(SOURCE_PATH "${IUTEST_LOCAL_SOURCE_PATH}")
else()
  # NOTE: update SHA512 when submitting this port for a tagged release.
  vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO srz-zumix/iutest
    REF "v${VERSION}"
    SHA512 0
    HEAD_REF master
  )
endif()

# iutest does not export symbols from a shared library.
vcpkg_check_linkage(ONLY_STATIC_LIBRARY)

string(COMPARE EQUAL "${VCPKG_CRT_LINKAGE}" "dynamic" IUTEST_FORCE_SHARED_CRT)

vcpkg_cmake_configure(
  SOURCE_PATH "${SOURCE_PATH}/projects/cmake"
  OPTIONS
    -Dbuild_tests=OFF
    -Dbuild_gtest_samples=OFF
    -Dbuild_use_gtest_configuration=OFF
    -Dtest_output_xml=OFF
    -Diutest_force_shared_crt=${IUTEST_FORCE_SHARED_CRT}
  MAYBE_UNUSED_VARIABLES
    iutest_force_shared_crt
)

vcpkg_cmake_install()
vcpkg_cmake_config_fixup(CONFIG_PATH "lib/cmake/iutest")

file(REMOVE_RECURSE
  "${CURRENT_PACKAGES_DIR}/debug/include"
  "${CURRENT_PACKAGES_DIR}/debug/share"
)

file(INSTALL "${CMAKE_CURRENT_LIST_DIR}/usage" DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}")
vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
