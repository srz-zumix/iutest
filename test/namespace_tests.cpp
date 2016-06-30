//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        namespace_tests.cpp
 * @brief       iutest namespace 対応 test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"
#include "../include/internal/iutest_filepath.hpp"
#include <cmath>
#include "main.cpp"

namespace test
{

namespace iutest
{
    class dummy;
}

#include "assertion_tests.cpp"
#include "basic_tests.cpp"
#include "combine_tests.cpp"
#include "compatibility_tests.cpp"
#include "filepath_tests.cpp"
#include "fixture_tests.cpp"
#include "floatingpoint_tests.cpp"
#include "no_failure_tests.cpp"
#include "param_method_tests.cpp"
#include "param_test_tests1.cpp"
#include "param_test_tests2.cpp"
#include "pred_tests.cpp"
#include "prod_tests1.cpp"
#include "prod_tests2.cpp"
#include "spi_tests.cpp"
#include "static_assertion_tests.cpp"
#include "string_assertion_tests.cpp"
#include "type_param_tests1.cpp"
#include "type_param_tests2.cpp"
#include "type_param_tests3.cpp"
#include "typed_test_tests.cpp"
#include "util_tests.cpp"
#include "variadic_templates_tests.cpp"

}

