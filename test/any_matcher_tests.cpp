//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        any_matcher_tests.cpp
 * @brief       Any matcher tests
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

#if IUTEST_HAS_MATCHERS && IUTEST_HAS_CXX_HDR_ANY \
    && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01080100)

#include <any>
#include <string>

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
using ::iutest::matchers::AllOf;
#endif
using ::iutest::matchers::AnyWith;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Gt;
using ::iutest::matchers::Lt;
using ::iutest::matchers::Not;

namespace {

const ::std::any int_value(42);
const ::std::any string_value(::std::string("text"));
const ::std::any empty_value;

} // namespace

IUTEST(AnyMatcher, MatchingTypeAndValue)
{
    IUTEST_EXPECT_THAT(int_value, AnyWith<int>(Eq(42)));
    IUTEST_EXPECT_THAT(int_value, AnyWith<int>(42));
    IUTEST_EXPECT_THAT(int_value, AnyWith<int>(Gt(0)));
    IUTEST_EXPECT_THAT(string_value, AnyWith< ::std::string>(Eq("text")));
    IUTEST_EXPECT_THAT(string_value, AnyWith< ::std::string>("text"));
}

IUTEST(AnyMatcher, ValueMismatch)
{
    IUTEST_EXPECT_THAT(int_value, Not(AnyWith<int>(Eq(0))));
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(int_value, AnyWith<int>(Eq(0))), "");
}

IUTEST(AnyMatcher, TypeMismatch)
{
    IUTEST_EXPECT_THAT(string_value, Not(AnyWith<int>(Eq(42))));
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(string_value, AnyWith<int>(Eq(42))), "");
    const ::std::any value(42L);
    IUTEST_EXPECT_THAT(value, Not(AnyWith<int>(42)));
    IUTEST_EXPECT_THAT(value, AnyWith<long>(42));
}

IUTEST(AnyMatcher, Empty)
{
    IUTEST_EXPECT_THAT(empty_value, Not(AnyWith<int>(Eq(42))));
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(empty_value, AnyWith<int>(Eq(42))), "");
}

#if IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
IUTEST(AnyMatcher, CompositeAndStoredMatcher)
{
    const int lower = 0;
    const int upper = 43;
    const auto matcher = AnyWith<int>(AllOf(Gt(lower), Lt(upper)));
    IUTEST_EXPECT_THAT(int_value, matcher);
    IUTEST_EXPECT_THAT(empty_value, Not(matcher));
    IUTEST_EXPECT_THAT(string_value, Not(matcher));
    IUTEST_EXPECT_THAT(int_value, matcher);
    int expected = 42;
    const auto value_matcher = AnyWith<int>(expected);
    expected = 0;
    IUTEST_EXPECT_THAT(int_value, value_matcher);
}
#endif

IUTEST(AnyMatcher, FailureMessage)
{
#if !defined(IUTEST_USE_GMOCK)
    const ::std::string type = ::iutest::detail::GetTypeNameProxy<int>::GetTypeName();
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(string_value, AnyWith<int>(Eq(42))),
        "AnyWith<" + type + ">");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(string_value, AnyWith<int>(Eq(42))), "actual type does not match");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(empty_value, AnyWith<int>(Eq(42))), "empty");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(int_value, AnyWith<int>(Eq(0))), "value = 42");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(int_value, AnyWith<int>(Eq(0))), "Eq: 0");
#else
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(int_value, AnyWith<int>(Eq(0))), "whose value 42");
#endif
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
