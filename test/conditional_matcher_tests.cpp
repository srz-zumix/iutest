//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        conditional_matcher_tests.cpp
 * @brief       Conditional matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHER_CONDITIONAL

using ::iutest::matchers::Conditional;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Ge;

namespace {
int conditional_matcher_test_value = 3;
} // namespace

IUTEST(ConditionalMatcher, SelectsMatcher)
{
    IUTEST_EXPECT_THAT(conditional_matcher_test_value, Conditional(true, Eq(3), Ge(4)));
    IUTEST_EXPECT_THAT(conditional_matcher_test_value, Conditional(false, Eq(4), Ge(0)));
    IUTEST_EXPECT_THAT(conditional_matcher_test_value, Conditional(true, 3, Ge(4)));
    IUTEST_EXPECT_THAT(conditional_matcher_test_value, Conditional(false, Eq(4), 3));
    IUTEST_EXPECT_THAT(::std::string("yes"), Conditional(true, "yes", Eq("no")));
}

IUTEST(ConditionalMatcher, SelectedMatcherFailure)
{
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(conditional_matcher_test_value, Conditional(true, Eq(4), Ge(0))), "Eq: 4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(conditional_matcher_test_value, Conditional(false, Eq(3), Ge(4))), "Ge: 4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(conditional_matcher_test_value, Conditional(true, 4, Ge(0))), "Eq: 4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(conditional_matcher_test_value, Conditional(false, Eq(3), 4)), "Eq: 4");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(conditional_matcher_test_value, Conditional(true, Eq(4), Ge(0))), "");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(conditional_matcher_test_value, Conditional(false, Eq(3), Ge(4))), "");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(conditional_matcher_test_value, Conditional(true, 4, Ge(0))), "");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(conditional_matcher_test_value, Conditional(false, Eq(3), 4)), "");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
