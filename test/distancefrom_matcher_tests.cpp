//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        distancefrom_matcher_tests.cpp
 * @brief       DistanceFrom matcher tests
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

#if IUTEST_HAS_MATCHER_DISTANCEFROM

using ::iutest::matchers::DistanceFrom;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Le;

namespace {

struct Position
{
    explicit Position(int n) : value(n) {}
    int value;
};

Position operator-(const Position& lhs, const Position& rhs)
{
    return Position(lhs.value - rhs.value);
}

int abs(const Position& position)
{
    return position.value < 0 ? -position.value : position.value;
}

int SquaredDistance(int lhs, int rhs)
{
    const int delta = lhs - rhs;
    return delta * delta;
}

} // namespace

IUTEST(DistanceFromMatcher, Numeric)
{
    IUTEST_EXPECT_THAT(7, DistanceFrom(10, Eq(3)));
    IUTEST_EXPECT_THAT(13, DistanceFrom(10, Le(3)));
    IUTEST_EXPECT_THAT(0.5, DistanceFrom(0.6, Le(0.2)));
    IUTEST_EXPECT_THAT(0.6, DistanceFrom(0.5, Le(0.2)));
}

IUTEST(DistanceFromMatcher, AdlAbs)
{
    IUTEST_EXPECT_THAT(Position(7), DistanceFrom(Position(10), Eq(3)));
    IUTEST_EXPECT_THAT(Position(13), DistanceFrom(Position(10), Eq(3)));
}

IUTEST(DistanceFromMatcher, CustomDistance)
{
    IUTEST_EXPECT_THAT(7, DistanceFrom(10, SquaredDistance, Eq(9)));
    IUTEST_EXPECT_THAT(13, DistanceFrom(10, SquaredDistance, Le(9)));
}

IUTEST(DistanceFromMatcher, FailureMessage)
{
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(13, DistanceFrom(10, Eq(2))), "3 away from 10");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(13, DistanceFrom(10, SquaredDistance, Eq(8))), "9 away from 10");
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
