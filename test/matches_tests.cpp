//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        matches_tests.cpp
 * @brief       Matches predicate tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <algorithm>
#include <string>
#include <vector>
#include "../include/gtest/iutest_switch.hpp"

#if IUTEST_HAS_MATCHERS

using ::iutest::matchers::Contains;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Gt;
using ::iutest::matchers::Matches;
using ::iutest::matchers::StartsWith;

namespace {

template<typename Predicate>
void CheckPredicate(const Predicate& predicate)
{
    Predicate copy(predicate);
    IUTEST_EXPECT_TRUE(predicate(3));
    IUTEST_EXPECT_FALSE(predicate(4));
    IUTEST_EXPECT_TRUE(copy(3));
    IUTEST_EXPECT_FALSE(copy(4));
}

#if !defined(IUTEST_NO_SFINAE)
template<typename Predicate>
void CheckValueCopy(const Predicate& predicate, int* expected)
{
    *expected = 4;
    CheckPredicate(predicate);
}
#endif

}   // end of namespace

IUTEST(Matches, CountIf)
{
    const int values[] = { 1, 10, 11, 20 };
    const ::std::vector<int> v(values, values + 4);
    IUTEST_EXPECT_EQ(2, ::std::count_if(v.begin(), v.end(), Matches(Gt(10))));
}

IUTEST(Matches, DirectCall)
{
    const ::std::string s("abc");
    IUTEST_EXPECT_TRUE(Matches(StartsWith("a"))(s));
    IUTEST_EXPECT_FALSE(Matches(StartsWith("b"))(s));
    IUTEST_EXPECT_TRUE(Matches(Eq(3))(3));
    IUTEST_EXPECT_FALSE(Matches(Eq(3))(4));
}

IUTEST(Matches, FindIf)
{
    const ::std::string values[] = { "beta", "alpha", "gamma" };
    IUTEST_EXPECT_EQ(values + 1, ::std::find_if(values, values + 3, Matches(StartsWith("a"))));
    IUTEST_EXPECT_EQ(values + 3, ::std::find_if(values, values + 3, Matches(StartsWith("z"))));
}

IUTEST(Matches, ConstPredicateAndCopy)
{
    const int expected = 3;
    CheckPredicate(Matches(Eq(expected)));
}

IUTEST(Matches, ContainerMatcher)
{
    const int values[] = { 1, 3 };
    const ::std::vector<int> v(values, values + 2);
    IUTEST_EXPECT_TRUE(Matches(Contains(3))(v));
    IUTEST_EXPECT_FALSE(Matches(Contains(4))(v));
}

#if !defined(IUTEST_NO_SFINAE)
IUTEST(Matches, PlainValue)
{
    IUTEST_EXPECT_TRUE(Matches(3)(3));
    IUTEST_EXPECT_FALSE(Matches(3)(4));
    IUTEST_EXPECT_TRUE(Matches("abc")(::std::string("abc")));
    IUTEST_EXPECT_FALSE(Matches("abc")(::std::string("def")));
    const int values[] = { 3, 4, 3 };
    IUTEST_EXPECT_EQ(2, ::std::count_if(values, values + 3, Matches(3)));
}

IUTEST(Matches, StoresValueByCopy)
{
    int expected = 3;
    CheckValueCopy(Matches(expected), &expected);
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
