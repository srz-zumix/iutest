//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        base64_matcher_tests.cpp
 * @brief       WhenBase64Unescaped matcher tests
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

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01120000)

using ::iutest::matchers::HasSubstr;
using ::iutest::matchers::Not;
using ::iutest::matchers::StrEq;
using ::iutest::matchers::WhenBase64Unescaped;

namespace {

const char* const invalid_base64 = "SGVsbG8!";
const char* const mismatched_base64 = "SGVsbG8=";

} // namespace

IUTEST(Base64Matcher, StandardAndUnpadded)
{
    IUTEST_EXPECT_THAT("SGVsbG8=", WhenBase64Unescaped(StrEq("Hello")));
    IUTEST_EXPECT_THAT("SGVsbG8", WhenBase64Unescaped(HasSubstr("ell")));
    IUTEST_EXPECT_THAT("YQ==", WhenBase64Unescaped(StrEq("a")));
    IUTEST_EXPECT_THAT("YQ", WhenBase64Unescaped(StrEq("a")));
    IUTEST_EXPECT_THAT("", WhenBase64Unescaped(StrEq("")));
    IUTEST_EXPECT_THAT("+/8=", WhenBase64Unescaped(StrEq(::std::string("\xfb\xff", 2))));
}

#if !defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01140000
IUTEST(Base64Matcher, UrlSafe)
{
    IUTEST_EXPECT_THAT("-_8=", WhenBase64Unescaped(StrEq(::std::string("\xfb\xff", 2))));
    IUTEST_EXPECT_THAT("-_8", WhenBase64Unescaped(StrEq(::std::string("\xfb\xff", 2))));
}
#endif

IUTEST(Base64Matcher, RejectsInvalidEncodingAndMismatch)
{
    const char* const invalid[] = {
        "Y!", "SGVsbG8!", "YW@="
    };
    for( size_t i = 0; i < sizeof(invalid) / sizeof(invalid[0]); ++i )
    {
        IUTEST_EXPECT_THAT(invalid[i], Not(WhenBase64Unescaped(StrEq(""))));
    }
    IUTEST_EXPECT_THAT("SGVsbG8=", Not(WhenBase64Unescaped(StrEq("World"))));
#if !defined(IUTEST_USE_GMOCK)
    const char* const invalid_padding[] = {
        "A", "YQ=", "YQ===", "YW=J", "YR==", "YWJ=", "SGVs bG8="
    };
    for( size_t i = 0; i < sizeof(invalid_padding) / sizeof(invalid_padding[0]); ++i )
    {
        IUTEST_EXPECT_THAT(invalid_padding[i], Not(WhenBase64Unescaped(StrEq(""))));
    }
#endif
}

#if !defined(IUTEST_USE_GMOCK)
IUTEST(Base64Matcher, FailureMessage)
{
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(invalid_base64, WhenBase64Unescaped(StrEq("Hello"))),
        "invalid base64");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(mismatched_base64, WhenBase64Unescaped(StrEq("World"))),
        "decoded to Hello");
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
