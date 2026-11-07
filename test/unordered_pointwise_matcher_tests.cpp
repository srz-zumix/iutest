//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unordered_pointwise_matcher_tests.cpp
 * @brief       UnorderedPointwise matcher tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <list>
#include <sstream>
#include <vector>
#include "../include/gtest/iutest_spi_switch.hpp"

#if IUTEST_HAS_MATCHERS && IUTEST_HAS_MATCHER_UNORDERED_POINTWISE

using ::iutest::matchers::Eq;
using ::iutest::matchers::Ge;
using ::iutest::matchers::Not;
using ::iutest::matchers::UnorderedPointwise;

namespace {

const int actual_values[] = { 2, 1, 2 };
const int expected_values[] = { 1, 2, 2 };
const int missing[] = { 1, 2, 4 };
const int fewer[] = { 1, 2 };
const int duplicates[] = { 1, 1, 2 };
const ::std::vector<int> actual_container(actual_values, actual_values + 3);
const ::std::vector<int> expected_container(expected_values, expected_values + 3);
const ::std::vector<int> missing_expected(missing, missing + 3);
const ::std::vector<int> fewer_expected(fewer, fewer + 2);
const ::std::vector<int> duplicate_expected(duplicates, duplicates + 3);

} // namespace

IUTEST(UnorderedPointwiseMatcher, Empty)
{
    const ::std::vector<int> empty;
    IUTEST_EXPECT_THAT(empty, UnorderedPointwise(Eq(), empty));
    IUTEST_EXPECT_THAT(empty, Not(UnorderedPointwise(Eq(), expected_container)));
    IUTEST_EXPECT_THAT(actual_container, Not(UnorderedPointwise(Eq(), empty)));
}

IUTEST(UnorderedPointwiseMatcher, ContainersAndDuplicates)
{
    const ::std::list<int> list_actual(actual_values, actual_values + 3);
    const ::std::list<int> list_expected(expected_values, expected_values + 3);
    IUTEST_EXPECT_THAT(actual_container, UnorderedPointwise(Eq(), expected_container));
    IUTEST_EXPECT_THAT(list_actual, UnorderedPointwise(Eq(), expected_container));
    IUTEST_EXPECT_THAT(actual_container, UnorderedPointwise(Eq(), list_expected));
    IUTEST_EXPECT_THAT(actual_container, Not(UnorderedPointwise(Eq(), missing_expected)));
    IUTEST_EXPECT_THAT(actual_container, Not(UnorderedPointwise(Eq(), duplicate_expected)));
    IUTEST_EXPECT_THAT(actual_container, Not(UnorderedPointwise(Eq(), fewer_expected)));
    IUTEST_EXPECT_THAT(fewer_expected, Not(UnorderedPointwise(Eq(), expected_container)));
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
IUTEST(UnorderedPointwiseMatcher, Arrays)
{
    IUTEST_EXPECT_THAT(actual_values, UnorderedPointwise(Eq(), expected_values));
    IUTEST_EXPECT_THAT(actual_container, UnorderedPointwise(Eq(), expected_values));
    IUTEST_EXPECT_THAT(actual_values, UnorderedPointwise(Eq(), expected_container));
}
#endif

IUTEST(UnorderedPointwiseMatcher, MaximumMatching)
{
    const int values[] = { 2, 1 };
    const ::std::vector<int> lhs(values, values + 2);
    IUTEST_EXPECT_THAT(lhs, UnorderedPointwise(Ge(), fewer_expected));
    IUTEST_EXPECT_THAT(fewer_expected, Not(UnorderedPointwise(Ge(), ::std::vector<int>(2, 2))));
}

IUTEST(UnorderedPointwiseMatcher, DifferentElementTypes)
{
    const ::std::vector<long> rhs(expected_values, expected_values + 3);
    IUTEST_EXPECT_THAT(actual_container, UnorderedPointwise(Eq(), rhs));
    const bool bool_actual[] = { true, false, true };
    const bool bool_expected[] = { false, true, true };
    IUTEST_EXPECT_THAT(::std::vector<bool>(bool_actual, bool_actual + 3),
        UnorderedPointwise(Eq(), ::std::vector<bool>(bool_expected, bool_expected + 3)));
}

#if IUTEST_HAS_MATCHER_FLOATINGPOINT_NEAR
IUTEST(UnorderedPointwiseMatcher, FloatNear)
{
    const float lhs[] = { 1.1f, 1.0f };
    const float rhs[] = { 1.0f, 1.2f };
    IUTEST_EXPECT_THAT(::std::vector<float>(lhs, lhs + 2),
        UnorderedPointwise(::iutest::matchers::FloatNear(0.15f), ::std::vector<float>(rhs, rhs + 2)));
    IUTEST_EXPECT_THAT(::std::vector<float>(lhs, lhs + 2),
        Not(UnorderedPointwise(::iutest::matchers::FloatNear(0.01f), ::std::vector<float>(rhs, rhs + 2))));
}
#endif

IUTEST(UnorderedPointwiseMatcher, FailureMessages)
{
#if !defined(IUTEST_USE_GMOCK)
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_container, UnorderedPointwise(Eq(), fewer_expected)),
        "element count 3 differs from the expected count 2");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(fewer_expected, UnorderedPointwise(Eq(), expected_container)),
        "element count 2 differs from the expected count 3");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_container, UnorderedPointwise(Eq(), missing_expected)),
        "unmatched expectation #2: 4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_container, UnorderedPointwise(Eq(), missing_expected)),
        "unmatched element #2: 2");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_container, UnorderedPointwise(Eq(), duplicate_expected)),
        "matched 2 of 3 elements");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_container, UnorderedPointwise(Eq(), fewer_expected)), "2 elements");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_container, UnorderedPointwise(Eq(), missing_expected)), "4");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(actual_container, UnorderedPointwise(Eq(), duplicate_expected)),
        "2 of 3");
#endif
}

#if !defined(IUTEST_USE_GMOCK)
IUTEST(UnorderedPointwiseMatcher, OwnsExpectationsAndCanBeReused)
{
    typedef ::iutest::detail::UnorderedPointwiseMatcher< ::iutest::detail::TwofoldEqMatcher, int> Matcher;
    const Matcher matcher = UnorderedPointwise(Eq(), ::std::vector<int>(expected_values, expected_values + 3));
    const Matcher copy(matcher);
    IUTEST_EXPECT_THAT(actual_container, matcher);
    IUTEST_EXPECT_THAT(actual_container, copy);
    IUTEST_EXPECT_THAT(missing_expected, Not(matcher));
    IUTEST_EXPECT_THAT(actual_container, matcher);
}

IUTEST(UnorderedPointwiseMatcher, DescriptionAndExplanation)
{
    typedef ::iutest::detail::UnorderedPointwiseMatcher< ::iutest::detail::TwofoldEqMatcher, int> Matcher;
    const Matcher matcher = UnorderedPointwise(Eq(), expected_container);
    ::std::ostringstream description;
    matcher.DescribeTo(&description);
    IUTEST_EXPECT_EQ("UnorderedPointwise: Eq: { 1, 2, 2 }", description.str());
    ::std::ostringstream negation;
    matcher.DescribeNegationTo(&negation);
    IUTEST_EXPECT_EQ("not (" + description.str() + ")", negation.str());
    ::std::ostringstream explanation;
    IUTEST_EXPECT_FALSE(matcher.MatchAndExplain(missing_expected, &explanation));
    IUTEST_EXPECT_THAT(explanation.str(), ::iutest::matchers::HasSubstr("matched 2 of 3 elements"));
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
