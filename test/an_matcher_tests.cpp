//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        an_matcher_tests.cpp
 * @brief       An matcher alias tests
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

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::An;

IUTEST(AnMatcher, Values)
{
    IUTEST_EXPECT_THAT(0, An<int>());
    IUTEST_EXPECT_THAT(-1, An<int>());
    IUTEST_EXPECT_THAT(1.5, An<double>());
    IUTEST_EXPECT_THAT(::std::string("value"), An< ::std::string>());
}

IUTEST(AnMatcher, Pointers)
{
    int value = 0;
    IUTEST_EXPECT_THAT(&value, An<int*>());
    IUTEST_EXPECT_THAT(static_cast<int*>(NULL), An<int*>());
}

IUTEST(AnMatcher, ConstValue)
{
    const int constant = 1;
    IUTEST_EXPECT_THAT(constant, An<const int>());
}

IUTEST(AnMatcher, Composition)
{
    IUTEST_EXPECT_THAT(1, ::iutest::matchers::AllOf(An<int>(), ::iutest::matchers::A<int>()));
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(1, ::iutest::matchers::Not(An<int>())), "");
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
