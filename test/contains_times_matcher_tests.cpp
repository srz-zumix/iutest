//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        contains_times_matcher_tests.cpp
 * @brief       Contains Times matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <vector>
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01120000)

using ::iutest::matchers::Contains;
using ::iutest::matchers::Ge;
using ::iutest::matchers::Gt;
using ::iutest::matchers::Le;

namespace {

int repeated[] = { 1, 2, 1 };
int absent[] = { 3, 4 };

} // namespace

IUTEST(ContainsTimesMatcher, Count)
{
    IUTEST_EXPECT_THAT(repeated, Contains(1).Times(2));
    IUTEST_EXPECT_THAT(repeated, Contains(2).Times(1));
    IUTEST_EXPECT_THAT(repeated, Contains(3).Times(0));
    IUTEST_EXPECT_THAT(absent, Contains(1).Times(0));
    IUTEST_EXPECT_THAT(::std::vector<int>(), Contains(1).Times(0));
    IUTEST_EXPECT_THAT(repeated, Contains(Gt(0)).Times(3));
}

IUTEST(ContainsTimesMatcher, CountMatcher)
{
    IUTEST_EXPECT_THAT(repeated, Contains(1).Times(Ge(2)));
    IUTEST_EXPECT_THAT(repeated, Contains(Gt(1)).Times(Le(1)));
    IUTEST_EXPECT_THAT(absent, Contains(1).Times(Le(0)));
}

#if !defined(IUTEST_USE_GMOCK)
#  define CHECK_COUNT_FAILURE(x, text) IUTEST_EXPECT_FATAL_FAILURE(x, text)
#else
#  define CHECK_COUNT_FAILURE(x, text) IUTEST_EXPECT_FATAL_FAILURE(x, "")
#endif

IUTEST(ContainsTimesMatcher, FailureCount)
{
    CHECK_COUNT_FAILURE(IUTEST_ASSERT_THAT(repeated, Contains(1).Times(1)), "matched 2 times");
    CHECK_COUNT_FAILURE(IUTEST_ASSERT_THAT(repeated, Contains(3).Times(1)), "matched 0 times");
    CHECK_COUNT_FAILURE(IUTEST_ASSERT_THAT(repeated, Contains(1).Times(Le(1))), "matched 2 times");
    CHECK_COUNT_FAILURE(IUTEST_ASSERT_THAT(repeated, Contains(1).Times(0)), "matched 2 times");
}

#undef CHECK_COUNT_FAILURE

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
