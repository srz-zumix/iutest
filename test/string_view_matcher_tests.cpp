//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        string_view_matcher_tests.cpp
 * @brief       iutest string view matcher test
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

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
#include <string_view>
#endif

#if IUTEST_HAS_MATCHERS

using namespace ::iutest::matchers;

#if IUTEST_HAS_CXX_HDR_STRING_VIEW && (!defined(IUTEST_USE_GTEST) || GMOCK_VER >= 0x01110000)
IUTEST(StringViewMatcher, StdStringView)
{
    const ::std::string_view value("xabcy", 5);
    IUTEST_EXPECT_THAT(value, StrEq("xabcy"));
    IUTEST_EXPECT_THAT(value, StrNe("abc"));
    IUTEST_EXPECT_THAT(value, StrCaseEq("XABCY"));
    IUTEST_EXPECT_THAT(value, StrCaseNe("other"));
    IUTEST_EXPECT_THAT(value, StartsWith("xa"));
    IUTEST_EXPECT_THAT(value, HasSubstr("abc"));
    IUTEST_EXPECT_THAT(value, EndsWith("cy"));
#if IUTEST_HAS_MATCHER_REGEX
    IUTEST_EXPECT_THAT(value, MatchesRegex("x.*y"));
    IUTEST_EXPECT_THAT(value, ContainsRegex("abc"));
#endif
    const ::std::string_view bounded("xabcy_extra", 5);
    IUTEST_EXPECT_THAT(bounded, StrEq("xabcy"));
    IUTEST_EXPECT_THAT(bounded, StartsWith("xa"));
    IUTEST_EXPECT_THAT(bounded, HasSubstr("cy"));
    IUTEST_EXPECT_THAT(bounded, EndsWith("cy"));
    IUTEST_EXPECT_THAT(bounded, Not(StartsWith("xabcy_extra")));
    IUTEST_EXPECT_THAT(bounded, Not(HasSubstr("extra")));
    IUTEST_EXPECT_THAT(bounded, Not(EndsWith("extra")));
#if IUTEST_HAS_MATCHER_REGEX
    IUTEST_EXPECT_THAT(bounded, Not(ContainsRegex("extra")));
#endif
}

IUTEST(StringViewMatcher, OwnsExpectedValue)
{
    ::std::string source("abc");
    const ::std::string_view value("abc");
    const auto eq = StrEq(::std::string_view(source));
    const auto ne = StrNe(::std::string_view(source));
    const auto case_eq = StrCaseEq(::std::string_view(source));
    const auto case_ne = StrCaseNe(::std::string_view(source));
    const auto starts = StartsWith(::std::string_view(source));
    const auto substr = HasSubstr(::std::string_view(source));
    const auto ends = EndsWith(::std::string_view(source));
#if IUTEST_HAS_MATCHER_REGEX
    const auto regex = MatchesRegex(::std::string_view(source));
    const auto contains_regex = ContainsRegex(::std::string_view(source));
#endif
    source[0] = 'z';
    IUTEST_EXPECT_THAT(value, eq);
    IUTEST_EXPECT_THAT(value, Not(ne));
    IUTEST_EXPECT_THAT(value, case_eq);
    IUTEST_EXPECT_THAT(value, Not(case_ne));
    IUTEST_EXPECT_THAT(value, starts);
    IUTEST_EXPECT_THAT(value, substr);
    IUTEST_EXPECT_THAT(value, ends);
#if IUTEST_HAS_MATCHER_REGEX
    IUTEST_EXPECT_THAT(value, regex);
    IUTEST_EXPECT_THAT(value, contains_regex);
#endif
}
#endif

#if IUTEST_HAS_CHAR8_T && !defined(IUTEST_USE_GTEST)
IUTEST(StringViewMatcher, Utf8String)
{
    const ::std::u8string value = u8"xabcy";
    IUTEST_EXPECT_THAT(value, StrEq(u8"xabcy"));
    IUTEST_EXPECT_THAT(u8"xabcy", StrEq(value));
    IUTEST_EXPECT_THAT(value, StrNe(u8"other"));
    IUTEST_EXPECT_THAT(value, StrCaseEq(u8"XABCY"));
    IUTEST_EXPECT_THAT(value, StrCaseNe(u8"other"));
    IUTEST_EXPECT_THAT(value, StartsWith(u8"xa"));
    IUTEST_EXPECT_THAT(value, HasSubstr(u8"abc"));
    IUTEST_EXPECT_THAT(value, EndsWith(u8"cy"));
    IUTEST_EXPECT_THAT(value, Not(HasSubstr(u8"missing")));
    char8_t mutable_value[] = u8"abc";
    char8_t* mutable_ptr = mutable_value;
    IUTEST_EXPECT_THAT(mutable_ptr, StrEq(mutable_ptr));
    IUTEST_EXPECT_THAT(mutable_ptr, StartsWith(mutable_ptr));
    IUTEST_EXPECT_THAT(::std::u8string(u8"テスト"), HasSubstr(u8"スト"));
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_THAT(u8"abc", StrEq(u8"abd")), "StrEq: abd");
#if IUTEST_HAS_MATCHER_REGEX
    IUTEST_EXPECT_THAT(value, MatchesRegex(u8"x.*y"));
    IUTEST_EXPECT_THAT(value, ContainsRegex(u8"abc"));
    IUTEST_EXPECT_THAT(value, Not(ContainsRegex(u8"missing")));
    IUTEST_EXPECT_THAT(mutable_ptr, MatchesRegex(mutable_ptr));
#endif
}

#if IUTEST_HAS_CXX_HDR_STRING_VIEW
IUTEST(StringViewMatcher, Utf8StringView)
{
    const ::std::u8string_view bounded(u8"abc_extra", 3);
    IUTEST_EXPECT_THAT(bounded, StrEq(u8"abc"));
    IUTEST_EXPECT_THAT(bounded, StartsWith(u8"a"));
    IUTEST_EXPECT_THAT(bounded, HasSubstr(u8"b"));
    IUTEST_EXPECT_THAT(bounded, EndsWith(u8"c"));
    IUTEST_EXPECT_THAT(bounded, Not(HasSubstr(u8"extra")));
    const auto eq = StrEq(bounded);
    const auto starts = StartsWith(bounded);
    const auto substr = HasSubstr(bounded);
    const auto ends = EndsWith(bounded);
    IUTEST_EXPECT_THAT(::std::u8string(u8"abc"), eq);
    IUTEST_EXPECT_THAT(u8"abc", starts);
    IUTEST_EXPECT_THAT(u8"abc", substr);
    IUTEST_EXPECT_THAT(u8"abc", ends);
    ::std::u8string source = u8"abc";
    const auto owned = StrEq(source);
    source[0] = u8'z';
    IUTEST_EXPECT_THAT(bounded, owned);
#if IUTEST_HAS_MATCHER_REGEX
    IUTEST_EXPECT_THAT(bounded, MatchesRegex(::std::u8string_view(u8"a.c")));
    IUTEST_EXPECT_THAT(bounded, ContainsRegex(::std::u8string_view(u8"b")));
    IUTEST_EXPECT_THAT(bounded, Not(ContainsRegex(u8"extra")));
#endif
}
#endif
#endif

#if !defined(IUTEST_USE_GTEST)
IUTEST(StringViewMatcher, OwnStringView)
{
    const ::iutest::detail::iu_string_view value("xabcy", 5);
    IUTEST_EXPECT_THAT(value, StrEq("xabcy"));
    IUTEST_EXPECT_THAT(value, StrNe("abc"));
    IUTEST_EXPECT_THAT(value, StrCaseEq("XABCY"));
    IUTEST_EXPECT_THAT(value, StrCaseNe("other"));
    IUTEST_EXPECT_THAT(value, StartsWith("xa"));
    IUTEST_EXPECT_THAT(value, HasSubstr("abc"));
    IUTEST_EXPECT_THAT(value, EndsWith("cy"));
#if IUTEST_HAS_MATCHER_REGEX
    IUTEST_EXPECT_THAT(value, MatchesRegex("x.*y"));
    IUTEST_EXPECT_THAT(value, ContainsRegex("abc"));
#endif
    const ::iutest::detail::iu_string_view bounded("abc_extra", 3);
    IUTEST_EXPECT_THAT(bounded, StrEq(::iutest::detail::iu_string_view("abc")));
    IUTEST_EXPECT_THAT(bounded, StrCaseEq(::iutest::detail::iu_string_view("ABC")));
    IUTEST_EXPECT_THAT(bounded, StartsWith(::iutest::detail::iu_string_view("a")));
    IUTEST_EXPECT_THAT(bounded, HasSubstr(::iutest::detail::iu_string_view("b")));
    IUTEST_EXPECT_THAT(bounded, EndsWith(::iutest::detail::iu_string_view("c")));
    IUTEST_EXPECT_THAT(bounded, Not(HasSubstr("extra")));
    ::std::string source("abc");
    const ::iutest::detail::StrEqMatcher< ::std::string > eq =
        StrEq(::iutest::detail::iu_string_view(source));
    const ::iutest::detail::StartsWithMatcher< ::std::string > starts =
        StartsWith(::iutest::detail::iu_string_view(source));
    source[0] = 'z';
    IUTEST_EXPECT_THAT(bounded, eq);
    IUTEST_EXPECT_THAT(bounded, starts);
}
#endif

#endif

int main(int argc, char** argv)
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
