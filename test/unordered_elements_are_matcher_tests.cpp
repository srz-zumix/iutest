//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unordered_elements_are_matcher_tests.cpp
 * @brief       Unordered element matcher tests
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

#if IUTEST_HAS_MATCHERS

using namespace ::iutest::matchers;

namespace {

const int actual_values[] = { 2, 1, 2 };
const int expected_values[] = { 1, 2, 2 };
const int missing[] = { 1, 2, 4 };
const int fewer[] = { 1, 2 };
const int duplicates[] = { 1, 1, 2 };
const int low = 1;
const int middle = 2;
const int high = 3;
#if !defined(IUTEST_USE_GMOCK)
typedef ::iutest::detail::GeMatcher<int> IntMatcher;
#else
typedef ::testing::Matcher<int> IntMatcher;
#endif

} // namespace

IUTEST(UnorderedElementsAreMatcher, Empty)
{
    const ::std::vector<int> empty;
    IUTEST_EXPECT_THAT(empty, UnorderedElementsAre());
    IUTEST_EXPECT_THAT(::std::vector< ::std::string>(), UnorderedElementsAre());
    IUTEST_EXPECT_THAT(::std::vector< ::std::string>(1, "value"), Not(UnorderedElementsAre()));
    IUTEST_EXPECT_THAT(empty, UnorderedElementsAreArray(empty));
    IUTEST_EXPECT_THAT(actual_values, Not(UnorderedElementsAre()));
    IUTEST_EXPECT_THAT(empty, Not(UnorderedElementsAreArray(expected_values)));
    IUTEST_EXPECT_THAT(empty, UnorderedElementsAreArray(static_cast<const int*>(NULL), 0));
}

IUTEST(UnorderedElementsAreMatcher, ArraysAndContainers)
{
    IUTEST_EXPECT_THAT(actual_values, UnorderedElementsAreArray(expected_values));
    const ::std::list<int> expectations(expected_values, expected_values + 3);
    const ::std::list<int> actual(actual_values, actual_values + 3);
    IUTEST_EXPECT_THAT(actual, UnorderedElementsAreArray(expectations));
    IUTEST_EXPECT_THAT(actual, UnorderedElementsAreArray(::std::vector<int>(expected_values, expected_values + 3)));
    IUTEST_EXPECT_THAT(actual, UnorderedElementsAreArray(expected_values, 3));
    IUTEST_EXPECT_THAT(actual, Not(UnorderedElementsAreArray(missing)));
    IUTEST_EXPECT_THAT(actual, Not(UnorderedElementsAreArray(duplicates)));
    IUTEST_EXPECT_THAT(actual, Not(UnorderedElementsAreArray(fewer)));
    IUTEST_EXPECT_THAT(fewer, Not(UnorderedElementsAreArray(expected_values)));
}

IUTEST(UnorderedElementsAreMatcher, BooleanValues)
{
    const bool actual[] = { true, false, true };
    const bool expectations[] = { true, true, false };
    IUTEST_EXPECT_THAT(::std::vector<bool>(actual, actual + 3),
        UnorderedElementsAreArray(::std::vector<bool>(expectations, expectations + 3)));
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING) && !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
IUTEST(UnorderedElementsAreMatcher, IteratorRange)
{
    const ::std::list<int> expectations(expected_values, expected_values + 3);
    IUTEST_EXPECT_THAT(actual_values, UnorderedElementsAreArray(expectations.begin(), expectations.end()));
    IUTEST_EXPECT_THAT(actual_values, UnorderedElementsAreArray(expected_values, expected_values + 3));
    IUTEST_EXPECT_THAT(::std::vector<int>(), UnorderedElementsAreArray(expected_values, expected_values));
    ::std::istringstream input("1 2 2");
    IUTEST_EXPECT_THAT(actual_values,
        UnorderedElementsAreArray(::std::istream_iterator<int>(input), ::std::istream_iterator<int>()));
}
#endif

IUTEST(UnorderedElementsAreMatcher, ArrayMatchersRequireReassignment)
{
    const int actual[] = { 3, 2, 1 };
    const IntMatcher matchers[] = { Ge(low), Ge(middle), Ge(high) };
    IUTEST_EXPECT_THAT(actual, UnorderedElementsAreArray(matchers));
    const int impossible[] = { 3, 1, 1 };
    IUTEST_EXPECT_THAT(impossible, Not(UnorderedElementsAreArray(matchers)));
}

#if IUTEST_HAS_MATCHER_ELEMENTSARE
IUTEST(UnorderedElementsAreMatcher, ValuesAndMatchers)
{
    IUTEST_EXPECT_THAT(actual_values, UnorderedElementsAre(1, 2, 2));
    IUTEST_EXPECT_THAT(actual_values, UnorderedElementsAre(Ge(2), 1, Eq(2)));
    IUTEST_EXPECT_THAT(actual_values, Not(UnorderedElementsAre(1, 1, 2)));
    IUTEST_EXPECT_THAT(actual_values, Not(UnorderedElementsAre(1, 2)));
    IUTEST_EXPECT_THAT(fewer, Not(UnorderedElementsAre(1, 2, 2)));
    const int one[] = { 1 };
    IUTEST_EXPECT_THAT(one, UnorderedElementsAre(1));
    const int ten[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    IUTEST_EXPECT_THAT(ten, UnorderedElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
}

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
IUTEST(UnorderedElementsAreMatcher, GreedyTrap)
{
    const int actual[] = { 1, 2 };
    IUTEST_EXPECT_THAT(actual, UnorderedElementsAre(AnyOf(1, 2), 1));
    IUTEST_EXPECT_THAT(actual, Not(UnorderedElementsAre(AnyOf(1, 2), 3)));
}
#endif

IUTEST(UnorderedElementsAreMatcher, StringLiterals)
{
    const ::std::string actual[] = { "two", "one" };
    IUTEST_EXPECT_THAT(actual, UnorderedElementsAre("one", "two"));
    IUTEST_EXPECT_THAT(actual, Not(UnorderedElementsAre("one", "three")));
}

IUTEST(UnorderedElementsAreMatcher, Nested)
{
    ::std::vector< ::std::vector<int> > actual;
    actual.push_back(::std::vector<int>(actual_values, actual_values + 3));
    actual.push_back(::std::vector<int>(fewer, fewer + 2));
    IUTEST_EXPECT_THAT(actual, UnorderedElementsAre(UnorderedElementsAre(1, 2), UnorderedElementsAre(2, 2, 1)));
}
#endif

#if IUTEST_HAS_INITIALIZER_LIST || (defined(IUTEST_USE_GMOCK) && IUTEST_HAS_CXX11)
IUTEST(UnorderedElementsAreMatcher, InitializerList)
{
    IUTEST_EXPECT_THAT(actual_values, UnorderedElementsAreArray({ 1, 2, 2 }));
    IUTEST_EXPECT_THAT(actual_values, UnorderedElementsAreArray({ Ge(1), Ge(2), Ge(2) }));
    IUTEST_EXPECT_THAT(::std::vector<int>(), UnorderedElementsAreArray(::std::initializer_list<int>()));
}
#endif

#if !defined(IUTEST_USE_GMOCK)
IUTEST(UnorderedElementsAreMatcher, Explanation)
{
    ::std::ostringstream explanation;
    IUTEST_EXPECT_FALSE(UnorderedElementsAreArray(missing).MatchAndExplain(actual_values, &explanation));
    IUTEST_EXPECT_THAT(explanation.str(), HasSubstr("unmatched expectation #2: is equal to 4"));
    IUTEST_EXPECT_THAT(explanation.str(), HasSubstr("unmatched element #2: 2"));
    explanation.str("");
    IUTEST_EXPECT_TRUE(UnorderedElementsAreArray(expected_values).MatchAndExplain(actual_values, &explanation));
    IUTEST_EXPECT_TRUE(explanation.str().empty());
}

IUTEST(UnorderedElementsAreMatcher, CopiesExpectations)
{
    int expectations[] = { 1, 2, 2 };
    const ::iutest::detail::UnorderedElementsAreMatcher< ::iutest::detail::UnorderedArrayExpectations<int> >
        saved = UnorderedElementsAreArray(expectations);
    expectations[0] = 9;
    IUTEST_EXPECT_THAT(actual_values, saved);
#if IUTEST_HAS_INITIALIZER_LIST
    const ::iutest::detail::UnorderedElementsAreMatcher< ::iutest::detail::UnorderedArrayExpectations<int> >
        from_list = UnorderedElementsAreArray({ 1, 2, 2 });
    IUTEST_EXPECT_THAT(actual_values, from_list);
#endif
}
#endif

IUTEST(UnorderedElementsAreMatcher, FailureMessages)
{
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAreArray(fewer)),
        "element count 3 differs from the expected count 2");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(fewer, UnorderedElementsAreArray(expected_values)),
        "element count 2 differs from the expected count 3");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAreArray(missing)),
        "unmatched expectation #2: is equal to 4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAreArray(missing)),
        "unmatched element #2: 2");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAreArray(duplicates)),
        "matched 2 of 3 elements");
#if IUTEST_HAS_MATCHER_ELEMENTSARE
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAre(1, 2)),
        "element count 3 differs from the expected count 2");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAre(1, 2, 4)),
        "unmatched expectation #2: is equal to 4");
#endif
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAreArray(fewer)), "2 elements");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAreArray(missing)), "4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_values, UnorderedElementsAreArray(duplicates)), "1");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
