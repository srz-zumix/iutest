//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        param_test_with_any_tests.cpp
 * @brief       parameter with any test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "param_test_tests.hpp"  // IWYU pragma: keep

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

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, WithAnyParamTest, ::iutest::Values(0));

#if IUTEST_HAS_ANY_PARAM_TEST

IUTEST_AP(AnyParamTest, Test)
{
    IUTEST_EXPECT_STREQ("My1/AnyParamTest", ::iuutil::GetCurrentTestSuite()->name());
    const int value = GetParam<int>();
    IUTEST_ASSERT_EQ(0, value);
}

IUTEST_INSTANTIATE_TEST_SUITE_AP(My1, AnyParamTest, ::iutest::Values(0));

IUTEST_AP(AnyParamTest2, Test)
{
    const ::std::string value = GetParam< ::std::string >();
    IUTEST_ASSERT_EQ("0", value);
}

IUTEST_INSTANTIATE_TEST_SUITE_AP(My1, AnyParamTest2, ::iutest::Values("0"));

#endif

#if IUTEST_HAS_AUTOFIXTURE_PARAM_TEST

IUTEST_P(NoFixtureAnyParamTest, Test)
{
    IUTEST_EXPECT_STREQ("My1/NoFixtureAnyParamTest", ::iuutil::GetCurrentTestSuite()->name());
    const int value = GetParam<int>();
    IUTEST_ASSERT_EQ(0, value);
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, NoFixtureAnyParamTest, ::iutest::Values(0));

#if IUTEST_HAS_IGNORE_TEST
IUTEST_P(NoFixtureAnyParamIgnoreTest, Test)
{
    const int value = GetParam<int>();
    IUTEST_ASSERT_EQ(0, value);
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, NoFixtureAnyParamIgnoreTest, ::iutest::Values(0));
#endif

#endif

#endif

#endif

