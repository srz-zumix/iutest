//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_namespace_tests.cpp
 * @brief		iutest namespace ‘Î‰ž test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"
#include "main.cpp"

namespace test
{

namespace iutest
{
	class dummy;
}

#include "iutest_assertion_tests.cpp"
#include "iutest_basic_tests.cpp"
#include "iutest_combine_tests.cpp"
#include "iutest_compatibility_tests.cpp"
#include "iutest_fixture_tests.cpp"
#include "iutest_no_fatalfailure_tests.cpp"
#include "iutest_param_test_tests1.cpp"
#include "iutest_param_test_tests2.cpp"
#include "iutest_pred_tests.cpp"
#include "iutest_prod_tests.cpp"
#include "iutest_spi_tests.cpp"
#include "iutest_string_assertion_tests.cpp"
#include "iutest_type_param_tests1.cpp"
#include "iutest_type_param_tests2.cpp"
#include "iutest_type_param_tests3.cpp"
#include "iutest_typed_test_tests.cpp"
#include "iutest_util_tests.cpp"
#include "iutest_variadic_templates_tests.cpp"

}

