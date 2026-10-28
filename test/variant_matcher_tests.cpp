//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        variant_matcher_tests.cpp
 * @brief       Variant matcher tests
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

#if IUTEST_HAS_MATCHERS && (IUTEST_HAS_CXX_HDR_VARIANT \
    || (defined(IUTEST_USE_GMOCK) && IUTEST_HAS_CXX17 && GMOCK_VER >= 0x01080100))

#include <memory>
#include <string>
#include <variant>

using ::iutest::matchers::AllOf;
using ::iutest::matchers::Eq;
using ::iutest::matchers::Gt;
using ::iutest::matchers::Lt;
using ::iutest::matchers::Not;
using ::iutest::matchers::Pointee;
using ::iutest::matchers::VariantWith;

namespace {

const ::std::variant<int, ::std::string> int_value(1);
const ::std::variant<int, ::std::string> string_value(::std::string("text"));

} // namespace

IUTEST(VariantMatcher, MatchingTypeAndValue)
{
    IUTEST_EXPECT_THAT(int_value, VariantWith<int>(Gt(0)));
    IUTEST_EXPECT_THAT(int_value, VariantWith<int>(Eq(1)));
    IUTEST_EXPECT_THAT(int_value, VariantWith<int>(1));
    IUTEST_EXPECT_THAT(string_value, VariantWith< ::std::string>(Eq("text")));
    IUTEST_EXPECT_THAT(string_value, VariantWith< ::std::string>("text"));
}

IUTEST(VariantMatcher, ValueMismatch)
{
    IUTEST_EXPECT_THAT(int_value, Not(VariantWith<int>(Gt(1))));
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(int_value, VariantWith<int>(Gt(1))), "");
}

IUTEST(VariantMatcher, TypeMismatch)
{
    IUTEST_EXPECT_THAT(string_value, Not(VariantWith<int>(Gt(0))));
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(string_value, VariantWith<int>(Gt(0))), "");
    const ::std::variant<int, long> value(1L);
    IUTEST_EXPECT_THAT(value, Not(VariantWith<int>(1)));
    IUTEST_EXPECT_THAT(value, VariantWith<long>(1));
}

IUTEST(VariantMatcher, CompositeAndStoredMatcher)
{
    const int lower = 0;
    const int upper = 2;
    const auto matcher = VariantWith<int>(AllOf(Gt(lower), Lt(upper)));
    IUTEST_EXPECT_THAT(int_value, matcher);
    int expected = 1;
    const auto value_matcher = VariantWith<int>(expected);
    expected = 2;
    IUTEST_EXPECT_THAT(int_value, value_matcher);
}

IUTEST(VariantMatcher, MoveOnlyAlternative)
{
    const ::std::variant<int, ::std::unique_ptr<int> > value(::std::unique_ptr<int>(new int(3)));
    IUTEST_EXPECT_THAT(value, VariantWith< ::std::unique_ptr<int> >(Pointee(3)));
}

IUTEST(VariantMatcher, FailureMessage)
{
#if !defined(IUTEST_USE_GMOCK)
    const ::std::string type = ::iutest::detail::GetTypeNameProxy<int>::GetTypeName();
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(string_value, VariantWith<int>(Gt(0))),
        "VariantWith<" + type + ">");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(int_value, VariantWith<int>(Gt(1))),
        "VariantWith<" + type + ">");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(int_value, VariantWith<int>(Gt(1))), "value = 1");
#else
#if IUTEST_HAS_RTTI
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(string_value, VariantWith<int>(Gt(0))), "value of type 'int'");
#endif
#endif
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(string_value, VariantWith<int>(Gt(0))), "index = 1");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(int_value, VariantWith<int>(Gt(1))), "index = 0");
}

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
