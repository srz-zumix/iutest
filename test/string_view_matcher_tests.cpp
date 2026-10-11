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
}
#endif

#endif

int main(int argc, char** argv)
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
