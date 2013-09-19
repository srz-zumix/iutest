//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_param_test_with_any_tests.cpp
 * @brief		iutest parameter test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest_param_test_tests.hpp"

#if IUTEST_HAS_PARAM_TEST

#if !defined(IUTEST_USE_GTEST)

class AnyParamTest : public ::iutest::TestWithParam< ::iutest::any > {};

IUTEST_P(AnyParamTest, Test)
{
	int value = ::iutest::any_cast<int>(GetParam());
	IUTEST_ASSERT_EQ(0, value);
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, AnyParamTest, ::iutest::Values(0));


#if IUTEST_HAS_TESTNAME_ALIAS

typedef ::iutest::TestWithAny WithAny;
IUTEST_P(IUTEST_ALIAS_TESTNAME_F(WithAny, WithAnyParamTest), Test)
{
	int value = GetParam<int>();
	IUTEST_ASSERT_EQ(0, value);
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, IUTEST_ALIAS_TESTNAME_F(WithAny, WithAnyParamTest), ::iutest::Values(0));

#endif

#endif

#endif

