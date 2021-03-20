
#
# for compiler configs
#
macro(fix_default_compiler_settings_)
  if (MSVC)
    if(NOT (MSVC_VERSION LESS 1910))
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /permissive-")
    endif()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
    if (MSVC_VERSION LESS 1900)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -wd4505")
    endif()

    foreach (flag_var
              CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
              CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
            )
      if (NOT BUILD_SHARED_LIBS AND NOT iutest_force_shared_crt)
        string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
      endif()

      # Force to always compile with W4
      if(${flag_var} MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" ${flag_var} "${${flag_var}}")
      #else()
      #  set(${flag_var} "${${flag_var}} /W4")
      endif()

      # /EHsc
      # string(REPLACE "/EHsc" "" ${flag_var} "${${flag_var}}")
      if (build_no_exceptions)
        string(REPLACE "/EHsc" "/EHs-c- /D_HAS_EXCEPTIONS=0" ${flag_var} "${${flag_var}}")
      endif()
    endforeach()

    foreach (flag_var
              CMAKE_CXX_FLAGS
            )
      message(STATUS "${flag_var}=${${flag_var}}")
    endforeach()

    # experimental
    if (build_use_experimental)
      if(NOT (MSVC_VERSION LESS 1910))
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /experimental:preprocessor /Wv:18")
      endif()
    endif()
  elseif (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_LIBCPP_DISABLE_AVAILABILITY")
  endif()
  set(CMAKE_CXX_FLAGS_DEBUG_GTEST "${CMAKE_CXX_FLAGS_DEBUG} -DIUTEST_USE_GTEST")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG_GTEST ${CMAKE_EXE_LINKER_FLAGS_DEBUG})
endmacro()


#
# project configs
#
macro(config_compiler_and_linker)
  fix_default_compiler_settings_()
  if (MSVC)
    # Newlines inside flags variables break CMake's NMake generator.
    # TODO(vladl@google.com): Add -RTCs and -RTCu to debug builds.
    set(cxx_base_flags "-GS -nologo -J -Zi")
    set(cxx_base_flags "${cxx_base_flags} -D_UNICODE -DUNICODE -DWIN32 -D_WIN32")
    set(cxx_base_flags "${cxx_base_flags} -DSTRICT -DWIN32_LEAN_AND_MEAN")
    set(cxx_exception_flags "-EHsc -D_HAS_EXCEPTIONS=1")
    set(cxx_no_exception_flags "-EHs-c- -D_HAS_EXCEPTIONS=0")
    set(cxx_no_rtti_flags "-GR-")
  elseif (CMAKE_COMPILER_IS_GNUCXX)
    set(cxx_base_flags "-Wall -Wshadow")
    set(cxx_exception_flags "-fexceptions")
    set(cxx_no_exception_flags "-fno-exceptions")
    # Until version 4.3.2, GCC doesn't define a macro to indicate
    # whether RTTI is enabled.  Therefore we define IUTEST_HAS_RTTI
    # explicitly.
    set(cxx_no_rtti_flags "-fno-rtti -DIUTEST_HAS_RTTI=0")
    set(cxx_strict_flags "-Wextra")
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "SunPro")
    set(cxx_exception_flags "-features=except")
    # Sun Pro doesn't provide macros to indicate whether exceptions and
    # RTTI are enabled, so we define IUTEST_HAS_* explicitly.
    set(cxx_no_exception_flags "-features=no%except -DIUTEST_HAS_EXCEPTIONS=0")
    set(cxx_no_rtti_flags "-features=no%rtti -DIUTEST_HAS_RTTI=0")
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "VisualAge" OR
      CMAKE_CXX_COMPILER_ID STREQUAL "XL")
    # CMake 2.8 changes Visual Age's compiler ID to "XL".
    set(cxx_exception_flags "-qeh")
    set(cxx_no_exception_flags "-qnoeh")
    # Until version 9.0, Visual Age doesn't define a macro to indicate
    # whether RTTI is enabled.  Therefore we define IUTEST_HAS_RTTI
    # explicitly.
    set(cxx_no_rtti_flags "-qnortti -DIUTEST_HAS_RTTI=0")
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "HP")
    set(cxx_base_flags "-AA -mt")
    set(cxx_exception_flags "-DIUTEST_HAS_EXCEPTIONS=1")
    set(cxx_no_exception_flags "+noeh -DIUTEST_HAS_EXCEPTIONS=0")
    # RTTI can not be disabled in HP aCC compiler.
    set(cxx_no_rtti_flags "")
  endif()

  # For building gtest's own tests and samples.
  set(cxx_exception "${CMAKE_CXX_FLAGS} ${cxx_base_flags} ${cxx_exception_flags}")
  set(cxx_no_exception
    "${CMAKE_CXX_FLAGS} ${cxx_base_flags} ${cxx_no_exception_flags}")
  if (build_no_exceptions)
    set(cxx_default "${cxx_no_exception}")
  else()
    set(cxx_default "${cxx_exception}")
  endif()
  set(cxx_no_rtti "${cxx_default} ${cxx_no_rtti_flags}")
  set(cxx_use_own_tuple "${cxx_default}")

  # For building the iutest libraries.
  set(cxx_strict "${cxx_default} ${cxx_strict_flags}")
endmacro()

#
# lib
#
function(cxx_library_with_type name type cxx_flags)
  # type can be either STATIC or SHARED to denote a static or shared library.
  # ARGN refers to additional arguments after 'cxx_flags'.
  add_library(${name} ${type} ${ARGN})
  set_target_properties(${name}
    PROPERTIES
    COMPILE_FLAGS "${cxx_flags}")
  if (BUILD_SHARED_LIBS OR type STREQUAL "SHARED")
    set_target_properties(${name}
      PROPERTIES
      COMPILE_DEFINITIONS)
  endif()
  if (CMAKE_USE_PTHREADS_INIT)
    target_link_libraries(${name} ${CMAKE_THREAD_LIBS_INIT})
  endif()
endfunction()

#
# target configs
#
function(cxx_shared_library name cxx_flags)
  cxx_library_with_type(${name} SHARED "${cxx_flags}" ${ARGN})
endfunction()

function(cxx_library name cxx_flags)
  cxx_library_with_type(${name} "" "${cxx_flags}" ${ARGN})
endfunction()

function(iutest_add_executable name)
if (MSVC)
  add_executable(${name} ${ARGN} ${IUTEST_ROOT_DIR}/tools/VisualStudio/Visualizers/iutest.natvis)
else()
  add_executable(${name} ${ARGN})
endif()
endfunction()

function(cxx_executable_with_flags name cxx_flags libs)
  # sources
  iutest_add_executable(${name} ${ARGN})
  if (cxx_flags)
    set_target_properties(${name}
      PROPERTIES
      COMPILE_FLAGS "${cxx_flags}")
  endif()
  # libraries
  foreach (lib "${libs}")
    target_link_libraries(${name} ${lib})
  endforeach()
endfunction()

#
# for sample
#
function(cxx_executable_sample name)
iutest_add_executable(${name} ${ARGN})
  set_target_properties(${name}
    PROPERTIES
    COMPILE_FLAGS "${cxx_default}")
endfunction()

#
# for gtest sample
#
function(cxx_executable_gtest_sample name dir)
  set(SRCS ${dir}/${name}.cc)
  foreach (src ${ARGN})
    set(SRCS ${SRCS} ${dir}/${src})
  endforeach()
  iutest_add_executable(${name} ${SRCS})
endfunction()

#
# for tests
#
function(cxx_executable_test name)
  set(SRCS ${IUTEST_ROOT_DIR}/test/${name}.cpp)
  foreach (src ${ARGN})
    set(SRCS ${SRCS} ${IUTEST_ROOT_DIR}/test/${src})
  endforeach()
  iutest_add_executable(${name} ${SRCS})
endfunction()

function(cxx_executable_test_with_main name)
  set(SRCS ${IUTEST_ROOT_DIR}/test/main.cpp)
  foreach (src ${ARGN})
    set(SRCS ${SRCS} ${IUTEST_ROOT_DIR}/test/${src})
  endforeach()
  iutest_add_executable(${name} ${SRCS})
endfunction()


function(cxx_executable_test_ns name)
  set(SRCS ${IUTEST_ROOT_DIR}/test/main.cpp)
  message(STATUS "create namespace test source:")
  file(RELATIVE_PATH test_relative_include_path ${IUTEST_ROOT_DIR}/test ${IUTEST_INCLUDE_DIR})
  foreach (src ${ARGN})
    get_filename_component(result "${src}" NAME_WE)
    set(ns_src ${IUTEST_ROOT_DIR}/test/${result}.ns.cpp)
    file(RELATIVE_PATH ns_src_relative_path ${IUTEST_ROOT_DIR} ${ns_src})
    message(STATUS "  - ${ns_src_relative_path}")
    file(WRITE  ${ns_src} "#include <cmath>\n")
    file(APPEND ${ns_src} "#include \"${test_relative_include_path}/gtest/iutest_spi_switch.hpp\"\n")
    file(APPEND ${ns_src} "#include \"${test_relative_include_path}/internal/iutest_filepath.hpp\"\n")
    file(APPEND ${ns_src} "namespace test { namespace iutest { class dummy; }\n")
    file(APPEND ${ns_src} "#include \"${src}\"\n")
    file(APPEND ${ns_src} "}\n")
    set(SRCS ${SRCS} ${ns_src})
  endforeach()
  iutest_add_executable(${name} ${SRCS})
endfunction()

#
# CTest
#
function(cxx_add_test name)
  add_test(
    NAME ${name}
    COMMAND $<TARGET_FILE:${name}>
    )
endfunction()

