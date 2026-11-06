//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        is_superset_of_matcher_tests.cpp
 * @brief       IsSupersetOf matcher tests
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
using ::iutest::matchers::IsSupersetOf;
using ::iutest::matchers::Not;

namespace {

const int superset_values[] = { 3, 2, 1, 2 };
const int expectations[] = { 1, 2, 2 };
const int missing[] = { 1, 4 };
const int duplicates[] = { 1, 1 };
const int too_many[] = { 1, 2, 2, 3, 3 };
const int low = 1;
const int middle = 2;
const int high = 3;
const int above = 4;
#if !defined(IUTEST_USE_GMOCK)
typedef ::iutest::detail::GeMatcher<int> IntMatcher;
#else
typedef ::testing::Matcher<int> IntMatcher;
#endif
const IntMatcher unmatched_matchers[] = { Ge(low), Ge(above) };

} // namespace

IUTEST(IsSupersetOfMatcher, Empty)
{
    const ::std::vector<int> empty;
    IUTEST_EXPECT_THAT(superset_values, IsSupersetOf(empty));
    IUTEST_EXPECT_THAT(empty, IsSupersetOf(empty));
    IUTEST_EXPECT_THAT(empty, Not(IsSupersetOf(expectations)));
}

IUTEST(IsSupersetOfMatcher, Values)
{
    IUTEST_EXPECT_THAT(superset_values, IsSupersetOf(expectations));
    IUTEST_EXPECT_THAT(superset_values, IsSupersetOf(superset_values));
    IUTEST_EXPECT_THAT(superset_values, Not(IsSupersetOf(missing)));
    IUTEST_EXPECT_THAT(superset_values, Not(IsSupersetOf(duplicates)));
    IUTEST_EXPECT_THAT(superset_values, Not(IsSupersetOf(too_many)));
}

IUTEST(IsSupersetOfMatcher, Container)
{
    const ::std::list<int> expected(expectations, expectations + 3);
    const ::std::vector<int> actual(superset_values, superset_values + 4);
    IUTEST_EXPECT_THAT(actual, IsSupersetOf(expected));
    IUTEST_EXPECT_THAT(actual, IsSupersetOf(::std::vector<int>(expectations, expectations + 3)));
}

IUTEST(IsSupersetOfMatcher, BooleanValues)
{
    const bool values[] = { true, false, true };
    const ::std::vector<bool> expected(2, true);
    IUTEST_EXPECT_THAT(values, IsSupersetOf(expected));
    IUTEST_EXPECT_THAT(::std::vector<bool>(values, values + 3), IsSupersetOf(expected));
    IUTEST_EXPECT_THAT(::std::vector<bool>(1, true), Not(IsSupersetOf(expected)));
}

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
IUTEST(IsSupersetOfMatcher, IteratorRange)
{
    const ::std::list<int> expected(expectations, expectations + 3);
    IUTEST_EXPECT_THAT(superset_values, IsSupersetOf(expected.begin(), expected.end()));
    IUTEST_EXPECT_THAT(superset_values, IsSupersetOf(expectations, expectations + 3));
    IUTEST_EXPECT_THAT(::std::vector<int>(), IsSupersetOf(expectations, expectations));
    ::std::istringstream input("1 2 2");
    IUTEST_EXPECT_THAT(superset_values, IsSupersetOf(::std::istream_iterator<int>(input), ::std::istream_iterator<int>()));
}
#endif

IUTEST(IsSupersetOfMatcher, MatchersRequireReassignment)
{
    const int actual[] = { 3, 2, 1, 0 };
    const IntMatcher matchers[] = { Ge(low), Ge(middle), Ge(high) };
    IUTEST_EXPECT_THAT(actual, IsSupersetOf(matchers));
    IUTEST_EXPECT_THAT(actual, IsSupersetOf(::std::vector<IntMatcher>(matchers, matchers + 3)));
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
    IUTEST_EXPECT_THAT(actual, IsSupersetOf(matchers, matchers + 3));
#endif
}

IUTEST(IsSupersetOfMatcher, MatchersRequireDistinctElements)
{
    const int actual[] = { 3, 1, 0 };
    const IntMatcher matchers[] = { Ge(middle), Ge(high) };
    IUTEST_EXPECT_THAT(actual, Not(IsSupersetOf(matchers)));
}

#if IUTEST_HAS_INITIALIZER_LIST || (defined(IUTEST_USE_GMOCK) && IUTEST_HAS_CXX11)
IUTEST(IsSupersetOfMatcher, InitializerList)
{
    IUTEST_EXPECT_THAT(superset_values, IsSupersetOf({ 1, 2, 2 }));
    IUTEST_EXPECT_THAT(superset_values, IsSupersetOf({ Ge(1), Ge(2), Ge(3) }));
    IUTEST_EXPECT_THAT(::std::vector<int>(), IsSupersetOf(::std::initializer_list<int>()));
}
#endif

#if !defined(IUTEST_USE_GMOCK)
IUTEST(IsSupersetOfMatcher, CopiesExpectations)
{
    int values[] = { 1, 2 };
    const ::iutest::detail::IsSupersetOfMatcher<int> saved = IsSupersetOf(values);
    values[0] = 9;
    IUTEST_EXPECT_THAT(superset_values, saved);
#if IUTEST_HAS_INITIALIZER_LIST
    const ::iutest::detail::IsSupersetOfMatcher<int> from_list = IsSupersetOf({ 1, 2, 3 });
    IUTEST_EXPECT_THAT(superset_values, from_list);
#endif
}

IUTEST(IsSupersetOfMatcher, Explanation)
{
    ::std::ostringstream explanation;
    IUTEST_EXPECT_FALSE(IsSupersetOf(missing).MatchAndExplain(superset_values, &explanation));
    IUTEST_EXPECT_THAT(explanation.str(), ::iutest::matchers::HasSubstr("unmatched expectation #1: Eq: 4"));
    explanation.str("");
    IUTEST_EXPECT_FALSE(IsSupersetOf(duplicates).MatchAndExplain(superset_values, &explanation));
    IUTEST_EXPECT_THAT(explanation.str(), ::iutest::matchers::HasSubstr("unmatched expectation #1: Eq: 1"));
    explanation.str("");
    IUTEST_EXPECT_FALSE(IsSupersetOf(unmatched_matchers).MatchAndExplain(superset_values, &explanation));
    IUTEST_EXPECT_THAT(explanation.str(), ::iutest::matchers::HasSubstr("unmatched expectation #1: Ge: 4"));
}
#endif

IUTEST(IsSupersetOfMatcher, FailureMessages)
{
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(superset_values, IsSupersetOf(missing)),
        "unmatched expectation #1: Eq: 4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(superset_values, IsSupersetOf(duplicates)),
        "unmatched expectation #1: Eq: 1");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(superset_values, IsSupersetOf(too_many)),
        "unmatched expectation #4: Eq: 3");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(superset_values, IsSupersetOf(unmatched_matchers)),
        "unmatched expectation #1: Ge: 4");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(superset_values, IsSupersetOf(missing)),
        "matcher #1: is equal to 4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(superset_values, IsSupersetOf(duplicates)),
        "no permutation of the elements can satisfy all matchers");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(superset_values, IsSupersetOf(too_many)),
        "no permutation of the elements can satisfy all matchers");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(superset_values, IsSupersetOf(unmatched_matchers)),
        "matcher #1: is >= 4");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
