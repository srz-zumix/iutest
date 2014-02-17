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
 * Copyright (C) 2013-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest_param_test_tests.hpp"

#if IUTEST_HAS_PARAM_TEST

#if !defined(IUTEST_USE_GTEST)

class WithAnyParamTest : public ::iutest::TestWithParam< ::iutest::any > {};

IUTEST_P(WithAnyParamTest, Test)
{
	int value = ::iutest::any_cast<int>(GetParam());
	IUTEST_ASSERT_EQ(0, value);
}

#if IUTEST_HAS_EXCEPTIONS
static ::iutest::any bad_any_cast_test_value;
IUTEST_P(WithAnyParamTest, BadCast)
{
	bad_any_cast_test_value = GetParam();
	IUTEST_ASSERT_THROW(::iutest::any_cast<float>(bad_any_cast_test_value), ::iutest::bad_any_cast);
}
#endif

IUTEST_INSTANTIATE_TEST_CASE_P(My1, WithAnyParamTest, ::iutest::Values(0));

#if IUTEST_HAS_ANY_PARAM_TEST

IUTEST_AP(AnyParamTest, Test)
{
	const int value = GetParam<int>();
	IUTEST_ASSERT_EQ(0, value);
}

IUTEST_INSTANTIATE_TEST_CASE_AP(My1, AnyParamTest, ::iutest::Values(0));

#endif

#if IUTEST_HAS_IF_EXISTS

IUTEST_P(NoFixtureAnyParamTest, Test)
{
	const int value = GetParam<int>();
	IUTEST_ASSERT_EQ(0, value);
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, NoFixtureAnyParamTest, ::iutest::Values(0));

#endif

#endif

#endif

