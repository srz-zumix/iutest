########################################################################
# CMake build script for iutest.
#

# CMake version required
cmake_minimum_required(VERSION 3.2)

# option
option(build_gtest_samples "gtest sample build." OFF)
option(build_use_gtest_configuration "use gtest build configuration." ON)
option(build_tests "tests build." ON)
option(build_namespace_tests "enable namespace test build." ON)

include(xcode_version.cmake)
# Xcode workarounds
if (CMAKE_VERSION VERSION_LESS 3.19)
  if (CMAKE_GENERATOR MATCHES Xcode)
    if (${XCODE_VERSION} VERSION_GREATER 10.0)
      option(RECURSIVE_GENERATE "Recursive call to cmake" OFF)

      if (NOT RECURSIVE_GENERATE)
        message(STATUS "Recursive generate started")
        execute_process(COMMAND ${CMAKE_COMMAND}
            -G "${CMAKE_GENERATOR}"
            -T "${CMAKE_GENERATOR_TOOLSET}"
            -A "${CMAKE_GENERATOR_PLATFORM}" 
            -DRECURSIVE_GENERATE:BOOL=ON 
            -Dbuild_gtest_samples:BOOL=${build_gtest_samples}
            -Dbuild_use_gtest_configuration:BOOL=${build_use_gtest_configuration}
            -Dbuild_tests:BOOL=${build_tests}
            -Dbuild_namespace_tests:BOOL=${build_namespace_tests}
            ${CMAKE_SOURCE_DIR})
        message(STATUS "Recursive generate done")
    
        # use the new build system workaround
        set(WORKSPACE_FILE iutest.xcodeproj/project.xcworkspace/xcshareddata/WorkspaceSettings.xcsettings)
        message("Deleting workspace file: ${WORKSPACE_FILE}")
        execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${WORKSPACE_FILE}
                      INPUT_FILE ${WORKSPACE_FILE})
        return()
      endif()
    endif()
  endif()
endif()

# Defines pre_project_set_up_hermetic_build() and set_up_hermetic_build().
include(cmake/hermetic_build.cmake OPTIONAL)

if (COMMAND pre_project_set_up_hermetic_build)
  pre_project_set_up_hermetic_build()
endif()

set(default_build_type "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
  set(default_build_type "Debug")
endif()

include(apple.cmake)

########################################################################
#
# Project-wide settings

# project name
project(iutest CXX C)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)

find_path(IUTEST_ROOT_DIR
        NAMES include/iutest.hpp
        HINTS
            ../../
            ${CMAKE_CURRENT_SOURCE_DIR}/../../
        NO_DEFAULT_PATH
        )

set(IUTEST_DIR ${IUTEST_ROOT_DIR})
list(APPEND CMAKE_PREFIX_PATH ${IUTEST_ROOT_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)

list(APPEND CMAKE_MODULE_PATH ${IUTEST_ROOT_DIR}/cmake)
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake)

find_package(IUTEST REQUIRED)

if (COMMAND set_up_hermetic_build)
  set_up_hermetic_build()
endif()

# include
include(internal_utils.cmake)
config_compiler_and_linker()  # Defined in internal_utils.cmake.

if (build_use_gtest_configuration)
  set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES};Debug_gtest")
  message(STATUS "configuration types: ${CMAKE_CONFIGURATION_TYPES}")
endif()

# include path
include_directories(${IUTEST_INCLUDE_DIR})
if (NOT "$ENV{GTEST_ROOT}" STREQUAL "")
  include_directories($ENV{GTEST_ROOT}/include)
endif()

########################################################################
#
# library
#
cxx_library(iutest "${cxx_strict}" ${IUTEST_ROOT_DIR}/src/iutest_all.cpp)
cxx_library(iutest_main "${cxx_strict}" ${IUTEST_ROOT_DIR}/src/iutest_main.cpp)

########################################################################
#
# Sample
#
cxx_executable_sample(iutest_sample
  ${IUTEST_ROOT_DIR}/samples/main.cpp
  ${IUTEST_ROOT_DIR}/samples/assertion.cpp
  ${IUTEST_ROOT_DIR}/samples/disabledtest.cpp
  ${IUTEST_ROOT_DIR}/samples/exception.cpp
  ${IUTEST_ROOT_DIR}/samples/fixture.cpp
  ${IUTEST_ROOT_DIR}/samples/japanese.cpp
  ${IUTEST_ROOT_DIR}/samples/matcher.cpp
  ${IUTEST_ROOT_DIR}/samples/parameterized.cpp
  ${IUTEST_ROOT_DIR}/samples/printto.cpp
  ${IUTEST_ROOT_DIR}/samples/simple.cpp
  ${IUTEST_ROOT_DIR}/samples/typed.cpp
)

########################################################################
#
# gtest sample
#
if (build_gtest_samples)
  message(STATUS "add gtest samples")
  cxx_executable_gtest_sample(sample1_unittest  ${IUTEST_ROOT_DIR}/samples/gtest sample1.cc main.cc)
  cxx_executable_gtest_sample(sample2_unittest  ${IUTEST_ROOT_DIR}/samples/gtest sample2.cc main.cc)
  cxx_executable_gtest_sample(sample3_unittest  ${IUTEST_ROOT_DIR}/samples/gtest main.cc)
  cxx_executable_gtest_sample(sample4_unittest  ${IUTEST_ROOT_DIR}/samples/gtest sample4.cc main.cc)
  cxx_executable_gtest_sample(sample5_unittest  ${IUTEST_ROOT_DIR}/samples/gtest sample1.cc main.cc)
  cxx_executable_gtest_sample(sample6_unittest  ${IUTEST_ROOT_DIR}/samples/gtest main.cc)
  cxx_executable_gtest_sample(sample7_unittest  ${IUTEST_ROOT_DIR}/samples/gtest main.cc)
  cxx_executable_gtest_sample(sample8_unittest  ${IUTEST_ROOT_DIR}/samples/gtest main.cc)
  cxx_executable_gtest_sample(sample9_unittest  ${IUTEST_ROOT_DIR}/samples/gtest )
  cxx_executable_gtest_sample(sample10_unittest ${IUTEST_ROOT_DIR}/samples/gtest )
endif()

########################################################################
#
# test
#
if (build_tests)
  cxx_executable_test_with_main(all_tests
    assertion_tests.cpp
    basic_tests.cpp
    combine_tests.cpp
    compatibility_tests.cpp
    filepath_tests.cpp
    fixture_tests.cpp
    no_failure_tests.cpp
    nullptr_tests.cpp
    param_test_tests1.cpp
    param_test_tests2.cpp
    pred_tests.cpp
    prod_tests1.cpp
    prod_tests2.cpp
    spi_tests.cpp
    static_assertion_tests.cpp
    string_assertion_tests.cpp
    syntax_tests.cpp
    syntax_gtest_tests.cpp
    type_param_tests1.cpp
    type_param_tests2.cpp
    type_param_tests3.cpp
    typed_test_tests.cpp
    values_tests.cpp
  )
  cxx_executable_test(also_run_disabled_tests)
  cxx_executable_test(assertion_only_tests)
  cxx_executable_test(assertion_return_tests)
  cxx_executable_test(assume_tests)
  cxx_executable_test(break_on_failure_nobreak_tests)
  cxx_executable_test(catch_exceptions_tests)
  cxx_executable_test(charcode_tests)
  cxx_executable_test(csvparams_invalid_file_tests)
  cxx_executable_test(commandline_tests)
  cxx_executable_test(csvparams_tests)
  cxx_executable_test(cxx_feature_tests)
  cxx_executable_test(disabled_tests)
  cxx_executable_test(empty_testname_tests)
  cxx_executable_test(env_var_gtest_tests)
  cxx_executable_test(environment_tests)
  cxx_executable_test(exception_assertion_tests)
  cxx_executable_test(exception_set_up_testsuite_tests)
  cxx_executable_test(exception_tests)
  cxx_executable_test(expression_assertion_tests)
  cxx_executable_test_with_main(extension_tests
    concat_tests.cpp
    fixture_alias_tests.cpp
    ignore_tests.cpp
    package_tests1.cpp
    package_tests2.cpp
    pairwise_tests.cpp
    param_method_tests.cpp
    param_test_with_any_tests.cpp
    pp_tests.cpp
    random_values_tests.cpp
    values_gen_tests.cpp
    variadic_templates_tests.cpp
  )
  cxx_executable_test(file_system_tests)
  cxx_executable_test(filter_tests)
  cxx_executable_test(flagfile_gtest_tests)
  cxx_executable_test(floatingpoint_tests)
  cxx_executable_test(gtest_version_tests)
  cxx_executable_test(help_tests)
  cxx_executable_test(inform_tests)
  cxx_executable_test(internal_log_tests)
  cxx_executable_test(invalid_commandline_tests)
  cxx_executable_test(japanese_tests)
  cxx_executable_test(legacy_testcase_api_tests)
  cxx_executable_test(list_test_tests)
  cxx_executable_test(listener_tests)
  cxx_executable_test(matcher_tests)
  cxx_executable_test(minimum_tests)
  cxx_executable_test(no_failure_fail_tests)
  cxx_executable_test(no_fatalfailure_tests)
  cxx_executable_test(no_test_tests)
  cxx_executable_test(output_env_var_tests)
  cxx_executable_test(output_junit_xml_empty_tests)
  cxx_executable_test(output_junit_xml_tests)
  cxx_executable_test(output_xml_tests)
  cxx_executable_test(port_tests)
  cxx_executable_test(printers_tests)
  cxx_executable_test(progress_tests)
  cxx_executable_test(quiet_result_printer_tests)
  cxx_executable_test(random_seed_tests)
  cxx_executable_test(record_property_tests)
  cxx_executable_test(repeat_tests)
  cxx_executable_test(scoped_trace_tests)
  cxx_executable_test(set_up_failure_tests)
  cxx_executable_test(set_up_global_failure_tests)
  cxx_executable_test(set_up_testcase_failure_tests)
  cxx_executable_test(shuffle_tests)
  cxx_executable_test(skip_tests)
  cxx_executable_test(spi_failure_tests)
  cxx_executable_test(streaming_listener_tests)
  cxx_executable_test(throw_on_assertion_failure_tests)
  cxx_executable_test(throw_on_failure_tests)
  cxx_executable_test(tr1_tests)
  cxx_executable_test(uninitialize_tests)
  cxx_executable_test(util_release_default_xml_generator_tests)
  cxx_executable_test(util_tests)
  if (build_namespace_tests)
    cxx_executable_test_ns(namespace_tests
      assertion_tests.cpp
      basic_tests.cpp
      combine_tests.cpp
      compatibility_tests.cpp
      filepath_tests.cpp
      fixture_tests.cpp
      no_failure_tests.cpp
      nullptr_tests.cpp
      param_test_tests1.cpp
      param_test_tests2.cpp
      pred_tests.cpp
      prod_tests1.cpp
      prod_tests2.cpp
      spi_tests.cpp
      static_assertion_tests.cpp
      string_assertion_tests.cpp
      syntax_tests.cpp
      syntax_gtest_tests.cpp
      type_param_tests1.cpp
      type_param_tests2.cpp
      type_param_tests3.cpp
      typed_test_tests.cpp
      values_tests.cpp
    )
  endif()
  # iutest only
  cxx_executable_test(default_main_tests)
  cxx_executable_test(default_printer_listener_tests)
  cxx_executable_test(env_var_tests)
  cxx_executable_test(exit_tests)
  cxx_executable_test(feature_spec_tests)
  cxx_executable_test(filter_file_invalid_path_tests)
  cxx_executable_test(filter_file_syntax_tests)
  cxx_executable_test(filter_file_tests)
  cxx_executable_test(flagfile_env_var_tests)
  cxx_executable_test(flagfile_invalid_path_tests)
  cxx_executable_test(flagfile_tests)
  cxx_executable_test(invalid_both_suite_and_case_set_up_tests)
  cxx_executable_test(invalid_both_suite_and_case_teardown_tests)
  cxx_executable_test(invalid_locale_ctype_tests)
  cxx_executable_test(ostream_formatter_tests)
  cxx_executable_test(output_long_type_param_tests)
  cxx_executable_test(output_tests)
  cxx_executable_test(output_xml_invalid_path_tests)
  cxx_executable_test(output_xml_repeat_tests)
  cxx_executable_test(own_string_view_tests)
  cxx_executable_test(param_test_name_invalid_tests)
  cxx_executable_test(param_test_name_tests)
  cxx_executable_test(no_yoda_tests)
  cxx_executable_test(scoped_trace_exception_tests)
  cxx_executable_test(spec_tests)
  cxx_executable_test(tap_file_generator_listener_tests)
  cxx_executable_test(tap_printer_listener_tests)
  cxx_executable_test(type_param_register_exception_int_tests)
  cxx_executable_test(type_param_register_exception_std_tests)
  cxx_executable_test(type_param_strict_failure_tests)
  cxx_executable_test(type_param_strict_tests)
  cxx_executable_test_with_main(unit_tests
    unit_file_tests.cpp
    unit_macro_tests.cpp
    unit_misc_tests.cpp
    unit_string_tests.cpp
    unit_string_view_tests.cpp
    unit_typetraits_tests.cpp
  )
endif()

########################################################################
#
# CTest
#
enable_testing()

if (build_tests)
  cxx_add_test(all_tests)
  cxx_add_test(also_run_disabled_tests)
  cxx_add_test(assertion_only_tests)
  cxx_add_test(assertion_return_tests)
  cxx_add_test(assume_tests)
  cxx_add_test(break_on_failure_nobreak_tests)
  cxx_add_test(catch_exceptions_tests)
  cxx_add_test(charcode_tests)
  cxx_add_test(commandline_tests)
  cxx_add_test(csvparams_invalid_file_tests)
  cxx_add_test(csvparams_tests)
  cxx_add_test(cxx_feature_tests)
  cxx_add_test(disabled_tests)
  cxx_add_test(empty_testname_tests)
  cxx_add_test(env_var_gtest_tests)
  cxx_add_test(environment_tests)
  cxx_add_test(exception_assertion_tests)
  cxx_add_test(exception_set_up_testsuite_tests)
  cxx_add_test(exception_tests)
  cxx_add_test(expression_assertion_tests)
  cxx_add_test(extension_tests)
  cxx_add_test(file_system_tests)
  cxx_add_test(filter_tests)
  cxx_add_test(flagfile_gtest_tests)
  cxx_add_test(floatingpoint_tests)
  cxx_add_test(gtest_version_tests)
  cxx_add_test(help_tests)
  cxx_add_test(inform_tests)
  cxx_add_test(internal_log_tests)
  cxx_add_test(invalid_commandline_tests)
  cxx_add_test(japanese_tests)
  cxx_add_test(legacy_testcase_api_tests)
  cxx_add_test(list_test_tests)
  cxx_add_test(listener_tests)
  cxx_add_test(matcher_tests)
  cxx_add_test(minimum_tests)
  cxx_add_test(no_failure_fail_tests)
  cxx_add_test(no_fatalfailure_tests)
  cxx_add_test(no_test_tests)
  cxx_add_test(output_env_var_tests)
  cxx_add_test(output_junit_xml_empty_tests)
  cxx_add_test(output_junit_xml_tests)
  cxx_add_test(output_xml_tests)
  cxx_add_test(port_tests)
  cxx_add_test(printers_tests)
  cxx_add_test(progress_tests)
  cxx_add_test(quiet_result_printer_tests)
  cxx_add_test(random_seed_tests)
  cxx_add_test(record_property_tests)
  cxx_add_test(repeat_tests)
  cxx_add_test(scoped_trace_tests)
  cxx_add_test(set_up_failure_tests)
  cxx_add_test(set_up_global_failure_tests)
  cxx_add_test(set_up_testcase_failure_tests)
  cxx_add_test(shuffle_tests)
  cxx_add_test(skip_tests)
  cxx_add_test(spi_failure_tests)
  cxx_add_test(streaming_listener_tests)
  cxx_add_test(throw_on_assertion_failure_tests)
  cxx_add_test(throw_on_failure_tests)
  cxx_add_test(tr1_tests)
  cxx_add_test(uninitialize_tests)
  cxx_add_test(util_release_default_xml_generator_tests)
  cxx_add_test(util_tests)
  if (build_namespace_tests)
    cxx_add_test(namespace_tests)
  endif()
  # iutest only
  cxx_add_test(default_main_tests)
  cxx_add_test(default_printer_listener_tests)
  cxx_add_test(env_var_tests)
  cxx_add_test(exit_tests)
  cxx_add_test(feature_spec_tests)
  cxx_add_test(filter_file_invalid_path_tests)
  cxx_add_test(filter_file_syntax_tests)
  cxx_add_test(filter_file_tests)
  cxx_add_test(flagfile_env_var_tests)
  cxx_add_test(flagfile_invalid_path_tests)
  cxx_add_test(flagfile_tests)
  cxx_add_test(invalid_both_suite_and_case_set_up_tests)
  cxx_add_test(invalid_both_suite_and_case_teardown_tests)
  cxx_add_test(invalid_locale_ctype_tests)
  cxx_add_test(ostream_formatter_tests)
  cxx_add_test(output_long_type_param_tests)
  cxx_add_test(output_tests)
  cxx_add_test(output_xml_invalid_path_tests)
  cxx_add_test(output_xml_repeat_tests)
  cxx_add_test(own_string_view_tests)
  cxx_add_test(param_test_name_invalid_tests)
  cxx_add_test(param_test_name_tests)
  cxx_add_test(no_yoda_tests)
  cxx_add_test(scoped_trace_exception_tests)
  cxx_add_test(spec_tests)
  cxx_add_test(tap_file_generator_listener_tests)
  cxx_add_test(tap_printer_listener_tests)
  cxx_add_test(type_param_register_exception_int_tests)
  cxx_add_test(type_param_register_exception_std_tests)
  cxx_add_test(type_param_strict_failure_tests)
  cxx_add_test(type_param_strict_tests)
  cxx_add_test(unit_tests)

  file(COPY ${IUTEST_ROOT_DIR}/test/testdata DESTINATION .)
endif()

install(TARGETS iutest
  EXPORT iutest-export
  ARCHIVE   DESTINATION lib
  LIBRARY   DESTINATION lib
  COMPONENT library
)
install(TARGETS iutest_main
  ARCHIVE   DESTINATION lib
  LIBRARY   DESTINATION lib
  COMPONENT library
)
install(DIRECTORY ${IUTEST_ROOT_DIR}/include/
  DESTINATION include/iutest
)
install(EXPORT iutest-export
  FILE IUTEST-config.cmake
  DESTINATION share/cmake/iutest/
)
