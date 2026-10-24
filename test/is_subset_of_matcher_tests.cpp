//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        is_subset_of_matcher_tests.cpp
 * @brief       IsSubsetOf matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <iterator>
#include <list>
#include <sstream>
#include <vector>
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01080100)

using ::iutest::matchers::Ge;
using ::iutest::matchers::IsSubsetOf;
using ::iutest::matchers::Not;

namespace {

const int expected[] = { 1, 2, 2, 3 };
const int too_many[] = { 1, 2, 2, 3, 3 };
const int unmatched[] = { 1, 4 };
const int duplicates[] = { 1, 1 };

} // namespace

IUTEST(IsSubsetOfMatcher, Empty)
{
    const ::std::vector<int> empty;
    IUTEST_EXPECT_THAT(empty, IsSubsetOf(expected));
    IUTEST_EXPECT_THAT(empty, IsSubsetOf(empty));
    IUTEST_EXPECT_THAT(unmatched, Not(IsSubsetOf(empty)));
}

IUTEST(IsSubsetOfMatcher, Values)
{
    const int actual[] = { 3, 2, 1 };
    const int equal[] = { 3, 2, 1, 2 };
    const int repeated[] = { 2, 2 };
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(expected));
    IUTEST_EXPECT_THAT(equal, IsSubsetOf(expected));
    IUTEST_EXPECT_THAT(repeated, IsSubsetOf(expected));
    IUTEST_EXPECT_THAT(duplicates, Not(IsSubsetOf(expected)));
}

IUTEST(IsSubsetOfMatcher, Container)
{
    const ::std::list<int> values(expected, expected + 4);
    const ::std::vector<int> actual(expected, expected + 2);
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(values));
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(::std::vector<int>(expected, expected + 4)));
}

IUTEST(IsSubsetOfMatcher, BooleanValues)
{
    const bool values[] = { true, false, true };
    const ::std::vector<bool> actual(2, true);
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(values));
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(::std::vector<bool>(values, values + 3)));
    IUTEST_EXPECT_THAT(actual, Not(IsSubsetOf(::std::vector<bool>(1, true))));
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
IUTEST(IsSubsetOfMatcher, IteratorRange)
{
    const ::std::list<int> values(expected, expected + 4);
    const int actual[] = { 3, 1 };
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(values.begin(), values.end()));
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(expected, expected + 4));
    IUTEST_EXPECT_THAT(::std::vector<int>(), IsSubsetOf(expected, expected));
    ::std::istringstream input("1 2 3");
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(::std::istream_iterator<int>(input), ::std::istream_iterator<int>()));
}
#endif

IUTEST(IsSubsetOfMatcher, MatchersRequireReassignment)
{
    const int low = 1;
    const int middle = 2;
    const int high = 3;
    const int actual[] = { 3, 2, 1 };
#if !defined(IUTEST_USE_GMOCK)
    const ::iutest::detail::GeMatcher<int> matchers[] = { Ge(low), Ge(middle), Ge(high) };
#else
    const ::testing::Matcher<int> matchers[] = { Ge(low), Ge(middle), Ge(high) };
#endif
    IUTEST_EXPECT_THAT(actual, IsSubsetOf(matchers));
}

IUTEST(IsSubsetOfMatcher, MatchersRequireDistinctExpectations)
{
    const int low = 1;
    const int high = 3;
    const int actual[] = { 1, 2 };
#if !defined(IUTEST_USE_GMOCK)
    const ::iutest::detail::GeMatcher<int> matchers[] = { Ge(low), Ge(high) };
#else
    const ::testing::Matcher<int> matchers[] = { Ge(low), Ge(high) };
#endif
    IUTEST_EXPECT_THAT(actual, Not(IsSubsetOf(matchers)));
}

#if IUTEST_HAS_INITIALIZER_LIST || (defined(IUTEST_USE_GMOCK) && IUTEST_HAS_CXX11)
IUTEST(IsSubsetOfMatcher, InitializerList)
{
    const int actual[] = { 2, 1 };
    IUTEST_EXPECT_THAT(actual, IsSubsetOf({ 1, 2, 3 }));
    IUTEST_EXPECT_THAT(actual, IsSubsetOf({ Ge(1), Ge(2) }));
    IUTEST_EXPECT_THAT(::std::vector<int>(), IsSubsetOf<int>({}));
}

#endif

#if !defined(IUTEST_USE_GMOCK)
IUTEST(IsSubsetOfMatcher, CopiesExpectations)
{
    int values[] = { 1, 2 };
    const ::iutest::detail::IsSubsetOfMatcher<int> saved = IsSubsetOf(values);
    values[0] = 9;
    const int actual[] = { 1 };
    IUTEST_EXPECT_THAT(actual, saved);
#if IUTEST_HAS_INITIALIZER_LIST
    const ::iutest::detail::IsSubsetOfMatcher<int> from_list = IsSubsetOf({ 1, 2, 3 });
    IUTEST_EXPECT_THAT(actual, from_list);
#endif
}
#endif

IUTEST(IsSubsetOfMatcher, FailureMessages)
{
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(too_many, IsSubsetOf(expected)),
        "element count 5 exceeds the expected count 4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(unmatched, IsSubsetOf(expected)),
        "cannot be matched to distinct expectations (matched 1 of 2 elements)");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(duplicates, IsSubsetOf(expected)),
        "cannot be matched to distinct expectations (matched 1 of 2 elements)");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(too_many, IsSubsetOf(expected)),
        "not all elements can be matched");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(unmatched, IsSubsetOf(expected)),
        "don't match any matchers");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(duplicates, IsSubsetOf(expected)),
        "not all elements can be matched");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
