# for apple
if (APPLE)
  get_filename_component(_iutest_root_dir "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
  get_filename_component(_iutest_source_dir "${CMAKE_SOURCE_DIR}" ABSOLUTE)
  set(_iutest_is_top_level OFF)
  if (_iutest_source_dir STREQUAL _iutest_root_dir OR _iutest_source_dir STREQUAL CMAKE_CURRENT_LIST_DIR)
    set(_iutest_is_top_level ON)
  endif()

  set(_iutest_is_ios_xcode OFF)
  if (CMAKE_SYSTEM_NAME STREQUAL "iOS" OR CMAKE_GENERATOR STREQUAL "Xcode")
    set(_iutest_is_ios_xcode ON)
  endif()

  # Do not touch the cache: an empty CMAKE_OSX_ARCHITECTURES means "host architecture".
  if (_iutest_is_top_level AND _iutest_is_ios_xcode AND CMAKE_SYSTEM_NAME STREQUAL "iOS")
    if (NOT CMAKE_OSX_ARCHITECTURES)
      set(_iutest_host_processor "${CMAKE_HOST_SYSTEM_PROCESSOR}")
      if (NOT _iutest_host_processor)
        execute_process(COMMAND uname -m
          OUTPUT_VARIABLE _iutest_host_processor
          OUTPUT_STRIP_TRAILING_WHITESPACE)
      endif()
      if (_iutest_host_processor MATCHES "arm64|aarch64")
        set(CMAKE_OSX_ARCHITECTURES "arm64")
      else()
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
      endif()
    endif()
  endif()
  message(STATUS "CMAKE_OSX_ARCHITECTURES: ${CMAKE_OSX_ARCHITECTURES}")

  if (_iutest_is_ios_xcode)
    # CMAKE_MACOSX_BUNDLE is needed to avoid the error "target specifies product type 'com.apple.product-type.tool'
    if (CMAKE_SYSTEM_NAME STREQUAL "iOS")
      set(CMAKE_MACOSX_BUNDLE YES)
    endif()
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED NO)
    set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED NO)
    if(NOT DEFINED CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY)
      set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")
    endif()
  endif()
endif()
