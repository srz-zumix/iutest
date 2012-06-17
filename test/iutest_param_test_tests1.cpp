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
 * Copyright (C) 2012, Takazumi Shirayanagi\n
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
}

int a[] = { 3, 2, 1, 0 };
IUTEST_INSTANTIATE_TEST_CASE_P(My1, ParamTest, ::iutest::Range<int>(0, 10));
IUTEST_INSTANTIATE_TEST_CASE_P(My3, ParamTest, ::iutest::Values(0, 1, 10));
IUTEST_INSTANTIATE_TEST_CASE_P(My4, ParamTest, ::iutest::ValuesIn(a));

class BoolParamTest : public ::iutest::TestWithParam<bool> {};

IUTEST_P(BoolParamTest, Test)
{
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, BoolParamTest, ::iutest::Bool());

IUTEST_INSTANTIATE_TEST_CASE_P(My1, MultiInstantiateParamTest, ::iutest::Range<int>(0, 10));

#endif

