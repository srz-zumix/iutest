//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_type_param_tests1.cpp
 * @brief		iutest parameter test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest_param_test_tests.hpp"

#if IUTEST_HAS_PARAM_TEST

IUTEST_P(ParamTest, Test)
{
	IUTEST_SUCCEED() << GetParam();
}

int param_test_array[] = { 3, 2, 1, 0 };
::std::vector<int> va(param_test_array, param_test_array+(sizeof(param_test_array)/sizeof(param_test_array[0])));
IUTEST_INSTANTIATE_TEST_CASE_P(My1, ParamTest, ::iutest::Range<int>(0, 10));
IUTEST_INSTANTIATE_TEST_CASE_P(My3, ParamTest, ::iutest::Values(0, 1, 10));
IUTEST_INSTANTIATE_TEST_CASE_P(My4, ParamTest, ::iutest::ValuesIn(param_test_array));
IUTEST_INSTANTIATE_TEST_CASE_P(My5, ParamTest, ::iutest::ValuesIn(va));
#if IUTEST_HAS_INITIALIZER_LIST
IUTEST_INSTANTIATE_TEST_CASE_P(My6, ParamTest, ::iutest::ValuesIn({ 3, 2, 1, 0 }));
//IUTEST_INSTANTIATE_TEST_CASE_P(My7, ParamTest, ({ 3, 2, 1, 0 }));
#endif

class BoolParamTest : public ::iutest::TestWithParam<bool> {};

IUTEST_P(BoolParamTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, BoolParamTest, ::iutest::Bool());

IUTEST_P(MultiInstantiateParamTest, Test)
{
	int param = GetParam();
	IUTEST_ASSERT_EQ(0, value);
	IUTEST_ASSERT_EQ(param, param);
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, MultiInstantiateParamTest, ::iutest::Range<int>(0, 10));

#endif

