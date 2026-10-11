//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        resultof_matcher_tests.cpp
 * @brief       ResultOf matcher tests
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

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01120000)

using ::iutest::matchers::Eq;
using ::iutest::matchers::ResultOf;

namespace {

int Double(int value) { return value * 2; }
int failure_value = 3;

} // namespace

IUTEST(ResultOfMatcher, DescribedResult)
{
    IUTEST_EXPECT_THAT(3, ResultOf("whose double is", Double, Eq(6)));
    IUTEST_EXPECT_THAT(3, ResultOf(::std::string("whose double is"), Double, 6));
}

IUTEST(ResultOfMatcher, DescribedFailure)
{
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(failure_value, ResultOf("whose double is", Double, Eq(7))),
        "whose double is");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(failure_value, ResultOf("whose double is", Double, 7)),
        "whose double is");
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
