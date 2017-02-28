########################################################################
# CMake build script for iutest.
#

# option
option(build_gtest_samples "gtest sample build." OFF)
option(build_tests "tests build." ON)

# Defines pre_project_set_up_hermetic_build() and set_up_hermetic_build().
include(cmake/hermetic_build.cmake OPTIONAL)

if (COMMAND pre_project_set_up_hermetic_build)
  pre_project_set_up_hermetic_build()
endif()

########################################################################
#
# Project-wide settings

# プロジェクト名
project(iutest CXX C)

# CMake バージョン
cmake_minimum_required(VERSION 2.6.2)

if (COMMAND set_up_hermetic_build)
  set_up_hermetic_build()
endif()

# include
include(internal_utils.cmake)
config_compiler_and_linker()  # Defined in internal_utils.cmake.

# インクルードパス
include_directories(
  ${PROJECT_SOURCE_DIR}/../../include
  )


########################################################################
#
# ライブラリ
#
cxx_library(iutest "${cxx_strict}" ../../src/iutest_all.cpp)
cxx_library(iutest_main "${cxx_strict}" ../../src/iutest_main.cpp)

########################################################################
#
# サンプル
#
cxx_executable_sample(iutest_sample
 ../../samples/main.cpp
 ../../samples/assertion.cpp
 ../../samples/disabledtest.cpp
 ../../samples/exception.cpp
 ../../samples/fixture.cpp
 ../../samples/matcher.cpp
 ../../samples/parameterized.cpp
 ../../samples/printto.cpp
 ../../samples/simple.cpp
 ../../samples/typed.cpp
)

########################################################################
#
# gtest サンプル
#
if (build_gtest_samples)
  cxx_executable_gtest_sample(sample1_unittest  ../../samples/gtest sample1.cc)
  cxx_executable_gtest_sample(sample2_unittest  ../../samples/gtest sample2.cc)
  cxx_executable_gtest_sample(sample3_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample4_unittest  ../../samples/gtest sample4.cc)
  cxx_executable_gtest_sample(sample5_unittest  ../../samples/gtest sample1.cc)
  cxx_executable_gtest_sample(sample6_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample7_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample8_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample9_unittest  ../../samples/gtest )
  cxx_executable_gtest_sample(sample10_unittest ../../samples/gtest )
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
   floatingpoint_tests.cpp
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
  cxx_executable_test(assertion_return_tests)
  cxx_executable_test(assume_tests)
  cxx_executable_test(break_on_failure_nobreak_tests)
  cxx_executable_test(catch_exceptions_tests)
  cxx_executable_test(commandline_tests)
  cxx_executable_test(csvparams_tests)
  cxx_executable_test(disabled_tests)
  cxx_executable_test(env_var_gtest_tests)
  cxx_executable_test(environment_tests)
  cxx_executable_test(exception_assertion_tests)
  cxx_executable_test(exception_tests)
  cxx_executable_test(expression_assertion_tests)
  cxx_executable_test(extension_tests)
  cxx_executable_test(file_system_tests)
  cxx_executable_test(filter_tests)
  cxx_executable_test(flagfile_gtest_tests)
  cxx_executable_test(help_tests)
  cxx_executable_test(invalid_commandline_tests)
  cxx_executable_test(japanese_tests)
  cxx_executable_test(list_test_tests)
  cxx_executable_test(listener_tests)
  cxx_executable_test(matcher_tests)
  cxx_executable_test(minimum_tests)
  cxx_executable_test(no_failure_fail_tests)
  cxx_executable_test(no_fatalfailure_tests)
  cxx_executable_test(no_test_tests)
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
  cxx_executable_test(util_tests)
  cxx_namespace_test(namespace_tests
   assertion_tests.cpp
   basic_tests.cpp
   combine_tests.cpp
   compatibility_tests.cpp
   filepath_tests.cpp
   fixture_tests.cpp
   floatingpoint_tests.cpp
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
  # iutest only
  cxx_executable_test(default_main_tests)
  cxx_executable_test(default_printer_listener_tests)
  cxx_executable_test(env_var_tests)
  cxx_executable_test(exit_tests)
  cxx_executable_test(filter_file_invalid_path_tests)
  cxx_executable_test(filter_file_syntax_tests)
  cxx_executable_test(filter_file_tests)
  cxx_executable_test(flagfile_env_var_tests)
  cxx_executable_test(flagfile_invalid_path_tests)
  cxx_executable_test(flagfile_tests)
  cxx_executable_test(ostream_formatter_tests)
  cxx_executable_test(output_tests)
  cxx_executable_test(output_xml_invalid_path_tests)
  cxx_executable_test(output_xml_repeat_tests)
  cxx_executable_test(param_test_name_invalid_tests)
  cxx_executable_test(param_test_name_tests)
  cxx_executable_test(no_yoda_tests)
  cxx_executable_test(tap_file_generator_listener_tests)
  cxx_executable_test(tap_printer_listener_tests)
  cxx_executable_test(type_param_strict_tests)
  cxx_executable_test(unit_tests)
endif()

