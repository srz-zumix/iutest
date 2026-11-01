//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        when_sorted_matcher_tests.cpp
 * @brief       Sorted container matcher tests
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

#include <functional>
#include <list>
#include <vector>

using ::iutest::matchers::ElementsAreArray;
using ::iutest::matchers::Not;
using ::iutest::matchers::WhenSorted;
using ::iutest::matchers::WhenSortedBy;

#if IUTEST_HAS_MATCHER_ELEMENTSARE
using ::iutest::matchers::ElementsAre;
#endif

namespace {

const int unsorted[] = { 3, 1, 2, 1 };
const int ascending[] = { 1, 1, 2, 3 };
const int descending[] = { 3, 2, 1, 1 };
const int wrong[] = { 1, 1, 2, 4 };
const int wrong_descending[] = { 4, 2, 1, 1 };

bool Greater(int lhs, int rhs) { return lhs > rhs; }

struct Value
{
    explicit Value(int n) : number(n) {}
    int number;
};

struct CompareValue
{
    explicit CompareValue(bool reverse) : descending_order(reverse) {}
    bool operator ()(const Value& lhs, const Value& rhs) const
    {
        return descending_order ? lhs.number > rhs.number : lhs.number < rhs.number;
    }
    bool descending_order;
};

} // namespace

IUTEST(WhenSortedMatcher, Vector)
{
    const ::std::vector<int> values(unsorted, unsorted + 4);
    IUTEST_EXPECT_THAT(values, WhenSorted(ElementsAreArray(ascending)));
    IUTEST_EXPECT_THAT(values, WhenSortedBy(::std::greater<int>(), ElementsAreArray(descending)));
    IUTEST_EXPECT_THAT(values, ElementsAreArray(unsorted));
}

IUTEST(WhenSortedMatcher, List)
{
    const ::std::list<int> values(unsorted, unsorted + 4);
    IUTEST_EXPECT_THAT(values, WhenSorted(ElementsAreArray(ascending)));
    IUTEST_EXPECT_THAT(values, WhenSortedBy(::std::greater<int>(), ElementsAreArray(descending)));
    IUTEST_EXPECT_THAT(values, ElementsAreArray(unsorted));
}

IUTEST(WhenSortedMatcher, Array)
{
    int values[] = { 3, 1, 2, 1 };
    IUTEST_EXPECT_THAT(values, WhenSorted(ElementsAreArray(ascending)));
    IUTEST_EXPECT_THAT(values, WhenSortedBy(::std::greater<int>(), ElementsAreArray(descending)));
    IUTEST_EXPECT_THAT(values, ElementsAreArray(unsorted));
    IUTEST_EXPECT_THAT(unsorted, WhenSorted(ElementsAreArray(ascending)));
}

#if IUTEST_HAS_MATCHER_ELEMENTSARE
IUTEST(WhenSortedMatcher, ElementsAre)
{
    IUTEST_EXPECT_THAT(unsorted, WhenSorted(ElementsAre(1, 1, 2, 3)));
    IUTEST_EXPECT_THAT(unsorted, WhenSortedBy(::std::greater<int>(), ElementsAre(3, 2, 1, 1)));
}
#endif

IUTEST(WhenSortedMatcher, EmptyAndSingleElement)
{
    const ::std::vector<int> empty;
    IUTEST_EXPECT_THAT(empty, WhenSorted(ElementsAreArray(empty)));
    IUTEST_EXPECT_THAT(empty, WhenSortedBy(::std::greater<int>(), ElementsAreArray(empty)));
    const int single[] = { 7 };
    IUTEST_EXPECT_THAT(single, WhenSorted(ElementsAreArray(single)));
    IUTEST_EXPECT_THAT(single, WhenSortedBy(::std::greater<int>(), ElementsAreArray(single)));
}

IUTEST(WhenSortedMatcher, FunctionComparator)
{
    IUTEST_EXPECT_THAT(unsorted, WhenSortedBy(&Greater, ElementsAreArray(descending)));
}

#if IUTEST_HAS_MATCHER_ELEMENTSARE
IUTEST(WhenSortedMatcher, CustomComparatorWithoutLess)
{
    const Value values[] = { Value(3), Value(1), Value(2) };
    IUTEST_EXPECT_THAT(values, WhenSortedBy(CompareValue(true),
        ElementsAre(::iutest::matchers::Field(&Value::number, 3),
            ::iutest::matchers::Field(&Value::number, 2),
            ::iutest::matchers::Field(&Value::number, 1))));
    IUTEST_EXPECT_EQ(3, values[0].number);
    IUTEST_EXPECT_EQ(1, values[1].number);
    IUTEST_EXPECT_EQ(2, values[2].number);
}
#endif

IUTEST(WhenSortedMatcher, Mismatch)
{
    IUTEST_EXPECT_THAT(unsorted, Not(WhenSorted(ElementsAreArray(wrong))));
    IUTEST_EXPECT_THAT(unsorted, Not(WhenSortedBy(::std::greater<int>(), ElementsAreArray(wrong_descending))));
    IUTEST_EXPECT_THAT(unsorted, ElementsAreArray(unsorted));
}

IUTEST(WhenSortedMatcher, FailureMessage)
{
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(unsorted, WhenSorted(ElementsAreArray(wrong))),
        "{ 1, 1, 2, 3 }");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(unsorted, WhenSortedBy(::std::greater<int>(), ElementsAreArray(wrong_descending))),
        "{ 3, 2, 1, 1 }");
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
