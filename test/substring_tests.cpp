//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        substring_tests.cpp
 * @brief       Substring predicate formatter tests
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

namespace
{

template<typename T>
void CheckSubstring(const T& needle, const T& haystack, const T& missing, const char* quote)
{
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, needle, haystack);
    IUTEST_ASSERT_PRED_FORMAT2(::iutest::IsSubstring, needle, haystack);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsNotSubstring, missing, haystack);
    IUTEST_ASSERT_PRED_FORMAT2(::iutest::IsNotSubstring, missing, haystack);
    EXPECT_PRED_FORMAT2(::testing::IsSubstring, needle, haystack);
    EXPECT_PRED_FORMAT2(::testing::IsNotSubstring, missing, haystack);

    const ::iutest::AssertionResult substring =
        ::iutest::IsSubstring("missing", "haystack", missing, haystack);
    IUTEST_EXPECT_FALSE(substring);
    IUTEST_EXPECT_EQ(::std::string("Value of: missing\n  Actual: ") + quote + "xyz\"\n"
        "Expected: a substring of haystack\nWhich is: " + quote + "a needle here\"", substring.message());
    const ::iutest::AssertionResult not_substring =
        ::iutest::IsNotSubstring("needle", "haystack", needle, haystack);
    IUTEST_EXPECT_FALSE(not_substring);
    IUTEST_EXPECT_EQ(::std::string("Value of: needle\n  Actual: ") + quote + "needle\"\n"
        "Expected: not a substring of haystack\nWhich is: " + quote + "a needle here\"", not_substring.message());
}

template<typename T>
void CheckNullSubstring(const T* text, const T* empty)
{
    const T* const null = NULL;
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, null, null);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsNotSubstring, null, text);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsNotSubstring, text, null);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsNotSubstring, null, empty);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsNotSubstring, empty, null);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, empty, text);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, empty, empty);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, text, text);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsNotSubstring, text, empty);
    const ::iutest::AssertionResult result = ::iutest::IsNotSubstring("null", "null", null, null);
    IUTEST_EXPECT_FALSE(result);
    const char* const quote = sizeof(T) > 1 ? "L\"" : "\"";
    IUTEST_EXPECT_EQ(::std::string("Value of: null\n  Actual: ") + quote + "(null)\"\n"
        "Expected: not a substring of null\nWhich is: " + quote + "(null)\"", result.message());
}

template<typename T>
void CheckStringEdges(const T& empty, const T& text, const T& haystack, const T& needle, const T& missing)
{
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, empty, empty);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, empty, text);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, text, text);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsNotSubstring, text, empty);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, needle, haystack);
    IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsNotSubstring, missing, haystack);
    const ::iutest::AssertionResult result = ::iutest::IsNotSubstring("needle", "haystack", needle, haystack);
    IUTEST_EXPECT_FALSE(result);
    const char* const quote = sizeof(needle[0]) > 1 ? "L\"" : "\"";
    IUTEST_EXPECT_EQ(::std::string("Value of: needle\n  Actual: ") + quote + "\\0b\"\n"
        "Expected: not a substring of haystack\nWhich is: " + quote + "a\\0b\"", result.message());
}

template<typename T>
void CheckWideMessage(const T& text)
{
    const ::iutest::AssertionResult result = ::iutest::IsNotSubstring("text", "text", text, text);
    IUTEST_EXPECT_FALSE(result);
    IUTEST_EXPECT_STREQ("Value of: text\n  Actual: L\"\xE3\x81\x82\"\n"
        "Expected: not a substring of text\nWhich is: L\"\xE3\x81\x82\"", result.message());
}

}   // namespace

IUTEST(SubstringTest, CString)
{
    CheckSubstring<const char*>("needle", "a needle here", "xyz", "\"");
    CheckNullSubstring("text", "");
}

IUTEST(SubstringTest, WideCString)
{
    CheckSubstring<const wchar_t*>(L"needle", L"a needle here", L"xyz", "L\"");
    CheckNullSubstring(L"text", L"");
    CheckWideMessage<const wchar_t*>(L"\x3042");
}

IUTEST(SubstringTest, String)
{
    CheckSubstring(::std::string("needle"), ::std::string("a needle here"), ::std::string("xyz"), "\"");
    CheckStringEdges(::std::string(), ::std::string("text"), ::std::string("a\0b", 3)
        , ::std::string("\0b", 2), ::std::string("\0c", 2));
}

#if !defined(IUTEST_USE_GTEST) || GTEST_HAS_STD_WSTRING
IUTEST(SubstringTest, WideString)
{
    CheckSubstring(::std::wstring(L"needle"), ::std::wstring(L"a needle here"), ::std::wstring(L"xyz"), "L\"");
    CheckStringEdges(::std::wstring(), ::std::wstring(L"text"), ::std::wstring(L"a\0b", 3)
        , ::std::wstring(L"\0b", 2), ::std::wstring(L"\0c", 2));
    CheckWideMessage(::std::wstring(L"\x3042"));
}
#endif

IUTEST(SubstringTest, PredicateFailures)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, "xyz", "text"), "Expected: a substring of");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_PRED_FORMAT2(::iutest::IsNotSubstring, "text", "text"), "Expected: not a substring of");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, L"xyz", L"text"), "Actual: L\"xyz\"");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_PRED_FORMAT2(::iutest::IsNotSubstring, L"text", L"text"), "Which is: L\"text\"");
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, ::std::string("xyz"), ::std::string("text")), "Actual: \"xyz\"");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_PRED_FORMAT2(::iutest::IsNotSubstring, ::std::string("text"), ::std::string("text")), "Which is: \"text\"");
#if !defined(IUTEST_USE_GTEST) || GTEST_HAS_STD_WSTRING
    IUTEST_EXPECT_NONFATAL_FAILURE(
        IUTEST_EXPECT_PRED_FORMAT2(::iutest::IsSubstring, ::std::wstring(L"xyz"), ::std::wstring(L"text")), "Actual: L\"xyz\"");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_PRED_FORMAT2(::iutest::IsNotSubstring, ::std::wstring(L"text"), ::std::wstring(L"text")), "Which is: L\"text\"");
#endif
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
