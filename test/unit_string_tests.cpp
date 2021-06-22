//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_string_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(UnitStringTest, Stricmp)
{
    const char negative = -1;
    const char negative_sample[] = { 'a', 'a', 'a', negative, '\0' };
    IUTEST_EXPECT_EQ(0, ::iutest::detail::iu_stricmp("AAA", "aaa"));
    IUTEST_EXPECT_LT(0, ::iutest::detail::iu_stricmp("AAAa", "aaa"));
    IUTEST_EXPECT_LT(0, ::iutest::detail::iu_stricmp("AAAB", "aaaa"));
    IUTEST_EXPECT_GT(0, ::iutest::detail::iu_stricmp("AAAA", "aaab"));
    IUTEST_EXPECT_GT(0, ::iutest::detail::iu_stricmp("AAA", negative_sample));
    IUTEST_EXPECT_GT(0, ::iutest::detail::iu_stricmp("AAA", "aaaA"));
}

IUTEST(UnitStringTest, OwnStricmp)
{
    const char negative = -1;
    const char negative_sample[] = { 'a', 'a', 'a', negative, '\0' };
    IUTEST_EXPECT_EQ(0, ::iutest::detail::wrapper::iu_stricmp("AAA", "aaa"));
    IUTEST_EXPECT_LT(0, ::iutest::detail::wrapper::iu_stricmp("AAAa", "aaa"));
    IUTEST_EXPECT_LT(0, ::iutest::detail::wrapper::iu_stricmp("AAAB", "aaaa"));
    IUTEST_EXPECT_GT(0, ::iutest::detail::wrapper::iu_stricmp("AAAA", "aaab"));
    IUTEST_EXPECT_GT(0, ::iutest::detail::wrapper::iu_stricmp("AAA", negative_sample));
    IUTEST_EXPECT_GT(0, ::iutest::detail::wrapper::iu_stricmp("AAA", "aaaA"));
}

void WcsicmpNegativeTest()
{
    const wchar_t negative = static_cast<wchar_t>(-1);
    const wchar_t negative_sample[] = { L'a', L'a', L'a', negative, L'\0' };
    IUTEST_ASSUME_GE(sizeof(::std::wint_t), sizeof(int));
    IUTEST_EXPECT_LT(0, ::iutest::detail::iu_wcsicmp(L"AAA", negative_sample));
}

IUTEST(UnitStringTest, Wcsicmp)
{
    IUTEST_EXPECT_EQ(0, ::iutest::detail::iu_wcsicmp(L"AAA", L"aaa"));
    IUTEST_EXPECT_LT(0, ::iutest::detail::iu_wcsicmp(L"AAAa", L"aaa"));
    IUTEST_EXPECT_LT(0, ::iutest::detail::iu_wcsicmp(L"AAAB", L"aaaa"));
    IUTEST_EXPECT_GT(0, ::iutest::detail::iu_wcsicmp(L"AAAa", L"aaaB"));
    IUTEST_EXPECT_GT(0, ::iutest::detail::iu_wcsicmp(L"AAA", L"aaaA"));
}

IUTEST(UnitStringTest, WcsicmpNegativeLT)
{
    const wchar_t negative = static_cast<wchar_t>(-1);
    const wchar_t negative_sample[] = { L'a', L'a', L'a', negative, L'\0' };
    IUTEST_ASSUME(sizeof(::std::wint_t) >= sizeof(int) && (sizeof(wchar_t) > 2 || ::iutest_type_traits::is_signed<wchar_t>::value));
    IUTEST_EXPECT_LT(0, ::iutest::detail::iu_wcsicmp(L"AAA", negative_sample));
}

IUTEST(UnitStringTest, WcsicmpNegativeGT)
{
    const wchar_t negative = static_cast<wchar_t>(-1);
    const wchar_t negative_sample[] = { L'a', L'a', L'a', negative, L'\0' };
    IUTEST_ASSUME(!(sizeof(::std::wint_t) >= sizeof(int) && (sizeof(wchar_t) > 2 || ::iutest_type_traits::is_signed<wchar_t>::value)));
    IUTEST_EXPECT_GT(0, ::iutest::detail::iu_wcsicmp(L"AAA", negative_sample));
}

IUTEST(UnitStringTest, OwnWcsicmp)
{
    IUTEST_EXPECT_EQ(0, ::iutest::detail::wrapper::iu_wcsicmp(L"AAA", L"aaa"));
    IUTEST_EXPECT_LT(0, ::iutest::detail::wrapper::iu_wcsicmp(L"AAAa", L"aaa"));
    IUTEST_EXPECT_LT(0, ::iutest::detail::wrapper::iu_wcsicmp(L"AAAB", L"aaaa"));
    IUTEST_EXPECT_GT(0, ::iutest::detail::wrapper::iu_wcsicmp(L"AAAa", L"aaaB"));
    IUTEST_EXPECT_GT(0, ::iutest::detail::wrapper::iu_wcsicmp(L"AAA", L"aaaA"));
}

IUTEST(UnitStringTest, OwnWcsicmpNegativeLT)
{
    const wchar_t negative = static_cast<wchar_t>(-1);
    const wchar_t negative_sample[] = { L'a', L'a', L'a', negative, L'\0' };
    IUTEST_ASSUME(sizeof(::std::wint_t) >= sizeof(int) && (sizeof(wchar_t) > 2 || ::iutest_type_traits::is_signed<wchar_t>::value));
    IUTEST_EXPECT_LT(0, ::iutest::detail::wrapper::iu_wcsicmp(L"AAA", negative_sample));
}

IUTEST(UnitStringTest, OwnWcsicmpNegativeGT)
{
    const wchar_t negative = static_cast<wchar_t>(-1);
    const wchar_t negative_sample[] = { L'a', L'a', L'a', negative, L'\0' };
    IUTEST_ASSUME(!(sizeof(::std::wint_t) >= sizeof(int) && (sizeof(wchar_t) > 2 || ::iutest_type_traits::is_signed<wchar_t>::value)));
    IUTEST_EXPECT_GT(0, ::iutest::detail::wrapper::iu_wcsicmp(L"AAA", negative_sample));
}

IUTEST(UnitStringTest, StringStrip)
{
    ::std::string str = "   a1 a2  ";
    IUTEST_EXPECT_STREQ("a1 a2  " , ::iutest::detail::StripLeadingSpace(str));
    IUTEST_EXPECT_STREQ("   a1 a2", ::iutest::detail::StripTrailingSpace(str));
    IUTEST_EXPECT_STREQ("a1 a2"   , ::iutest::detail::StripSpace(str));
}

IUTEST(UnitStringTest, StringReplaceChar)
{
    ::std::string str = "a1a2a3a4b5";
    ::iutest::detail::StringReplace(str, 'a', "ii");
    IUTEST_EXPECT_STREQ("ii1ii2ii3ii4b5", str);
}

IUTEST(UnitStringTest, StringReplaceString)
{
    {
        ::std::string str = "a1a2a3a4b5";
        ::iutest::detail::StringReplace(str, "a1", 2, "ii");
        IUTEST_EXPECT_STREQ("iia2a3a4b5", str);
    }
    {
        ::std::string str = "a1a2a3a4b5";
        ::iutest::detail::StringReplace(str, "a1", 1, "ii");
        IUTEST_EXPECT_STREQ("ii1a2a3a4b5", str);
    }
}

IUTEST(UnitStringTest, StringReplaceToLF)
{
    ::std::string str = "a\r\nb\r\rc\r\n\nd";
    ::iutest::detail::StringReplaceToLF(str);
    IUTEST_EXPECT_STREQ("a\nb\n\nc\n\nd", str);
}

int test_print(char* dst, size_t size, const char* fmt, ...) IUTEST_ATTRIBUTE_FORMAT_PRINTF(3, 4);
int test_print(char* dst, size_t size, const char* fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    const int ret = ::iutest::detail::iu_vsnprintf(dst, size, fmt, va);
    va_end(va);
    return ret;
}
IUTEST(UnitStringTest, InvalidVsnprintf)
{
    IUTEST_EXPECT_EQ(-1, test_print(NULL, 1, "test"));
}

IUTEST(UnitStringTest, AddDefaultPackageName)
{
    const ::std::string prev_name = ::iutest::IUTEST_FLAG(default_package_name);
    ::iutest::IUTEST_FLAG(default_package_name) = "Test";
    IUTEST_EXPECT_STREQ("Test.a1a2a3a4b5", ::iutest::TestEnv::AddDefaultPackageName("a1a2a3a4b5"));
    IUTEST_EXPECT_STREQ("Hoge.a1a2a3a4b5", ::iutest::TestEnv::AddDefaultPackageName("Hoge.a1a2a3a4b5"));
    ::iutest::IUTEST_FLAG(default_package_name) = prev_name;
}

class HackXmlGeneratorListener : public ::iutest::DefaultXmlGeneratorListener
{
    HackXmlGeneratorListener() : ::iutest::DefaultXmlGeneratorListener("") {}
public:
    using DefaultXmlGeneratorListener::EscapeXmlAttribute;
    using DefaultXmlGeneratorListener::EscapeXmlText;
};

IUTEST(UnitStringTest, XmlEscape)
{
    IUTEST_EXPECT_STREQ("a&lt;&gt;&#x09;b&amp; &apos;&quot;c&#x0D;&#x0A;"
        , HackXmlGeneratorListener::EscapeXmlAttribute("a<>	b& \'\"c\r\n"));// NOLINT
    IUTEST_EXPECT_STREQ("a&lt;&gt;	b&amp; \'\"c\r\n"                       // NOLINT
        , HackXmlGeneratorListener::EscapeXmlText("a<>	b& \'\"c\r\n"));    // NOLINT
}

IUTEST(UnitStringTest, FileLocation)
{
    ::iutest::IUTEST_FLAG(file_location_style_msvc) = false;
    IUTEST_EXPECT_STREQ("main.cpp:1"
        , ::iutest::detail::FormatFileLocation("main.cpp", 1) );
    IUTEST_EXPECT_STREQ("unknown file:1"
        , ::iutest::detail::FormatFileLocation(NULL, 1) );
    IUTEST_EXPECT_STREQ("main.cpp"
        , ::iutest::detail::FormatFileLocation("main.cpp", -1) );

    ::iutest::IUTEST_FLAG(file_location_style_msvc) = true;
    IUTEST_EXPECT_STREQ("main.cpp(1)"
        , ::iutest::detail::FormatFileLocation("main.cpp", 1) );
    IUTEST_EXPECT_STREQ("unknown file(1)"
        , ::iutest::detail::FormatFileLocation(NULL, 1) );
    IUTEST_EXPECT_STREQ("main.cpp"
        , ::iutest::detail::FormatFileLocation("main.cpp", -1) );
}

IUTEST(UnitStringTest, ToHexString)
{
    IUTEST_EXPECT_STREQ(              "00", ::iutest::detail::ToHexString< ::iutest::UInt8  >(0));
    IUTEST_EXPECT_STREQ(            "0000", ::iutest::detail::ToHexString< ::iutest::UInt16 >(0));
    IUTEST_EXPECT_STREQ(        "00000000", ::iutest::detail::ToHexString< ::iutest::UInt32 >(0));
    IUTEST_EXPECT_STREQ("0000000000000000", ::iutest::detail::ToHexString< ::iutest::UInt64 >(0));
    IUTEST_EXPECT_STREQ("FFFFFFFFFFFFFFFF", ::iutest::detail::ToHexString< ::iutest::Int64 >(-1));
#if defined(INT64_MAX)
    IUTEST_EXPECT_STREQ("7FFFFFFFFFFFFFFF", ::iutest::detail::ToHexString< ::iutest::Int64 >(INT64_MAX));
    IUTEST_EXPECT_STREQ("8000000000000000", ::iutest::detail::ToHexString< ::iutest::Int64 >(INT64_MIN));
#endif
    IUTEST_EXPECT_STREQ(        "01234567", ::iutest::detail::ToHexString(0x01234567u));
    IUTEST_EXPECT_STREQ(          "414243", ::iutest::detail::ToHexString("ABC", -1));
    IUTEST_EXPECT_STREQ(            "4142", ::iutest::detail::ToHexString("ABC", 2));
    IUTEST_EXPECT_STREQ(                "", ::iutest::detail::ToHexString("ABC", 0));
}

IUTEST(UnitStringTest, ToOctString)
{
    IUTEST_EXPECT_STREQ(                   "000", ::iutest::detail::ToOctString< ::iutest::UInt8  >(0));
    IUTEST_EXPECT_STREQ(                "000000", ::iutest::detail::ToOctString< ::iutest::UInt16 >(0));
    IUTEST_EXPECT_STREQ(           "00000000000", ::iutest::detail::ToOctString< ::iutest::UInt32 >(0));
    IUTEST_EXPECT_STREQ("0000000000000000000000", ::iutest::detail::ToOctString< ::iutest::UInt64 >(0));
    IUTEST_EXPECT_STREQ("1777777777777777777777", ::iutest::detail::ToOctString< ::iutest::Int64 >(-1));
#if defined(INT64_MAX)
    IUTEST_EXPECT_STREQ("0777777777777777777777", ::iutest::detail::ToOctString< ::iutest::Int64 >(INT64_MAX));
    IUTEST_EXPECT_STREQ("1000000000000000000000", ::iutest::detail::ToOctString< ::iutest::Int64 >(INT64_MIN));
#endif
    IUTEST_EXPECT_STREQ(                   "377", ::iutest::detail::ToOctString< ::iutest::UInt8  >(0377u));
}

IUTEST(UnitStringTest, FormatIntWidth2)
{
    IUTEST_EXPECT_STREQ(  "00", ::iutest::detail::FormatIntWidth2(0));
    IUTEST_EXPECT_STREQ( "128", ::iutest::detail::FormatIntWidth2(128));
    IUTEST_EXPECT_STREQ("-128", ::iutest::detail::FormatIntWidth2(-128));
}

IUTEST(UnitStringTest, FormatIntWidth3)
{
    IUTEST_EXPECT_STREQ( "000", ::iutest::detail::FormatIntWidthN(0, 3));
    IUTEST_EXPECT_STREQ( "128", ::iutest::detail::FormatIntWidthN(128, 3));
    IUTEST_EXPECT_STREQ("1024", ::iutest::detail::FormatIntWidthN(1024, 3));
}

IUTEST(UnitStringTest, FormatIntWidthN)
{
    IUTEST_EXPECT_STREQ("0000000000", ::iutest::detail::FormatIntWidthN(0, 10));
    IUTEST_EXPECT_STREQ("0000008096", ::iutest::detail::FormatIntWidthN(8096, 10));
    IUTEST_EXPECT_STREQ("1024",  ::iutest::detail::FormatIntWidthN(1024, -1));
    IUTEST_EXPECT_STREQ("-101",  ::iutest::detail::FormatIntWidthN(-101, 2));
    IUTEST_EXPECT_STREQ("-0101", ::iutest::detail::FormatIntWidthN(-101, 4));
}

IUTEST(UnitStringTest, FormatSizeByte)
{
    IUTEST_EXPECT_STREQ("0B", ::iutest::detail::FormatSizeByte(0));
    IUTEST_EXPECT_STREQ("2B", ::iutest::detail::FormatSizeByte(2));
}

IUTEST(UnitStringTest, FormatSizeKByte)
{
    IUTEST_EXPECT_STREQ("1KB", ::iutest::detail::FormatSizeByte(1024));
    IUTEST_EXPECT_STREQ("1.0KB", ::iutest::detail::FormatSizeByte(1025));
}

IUTEST(UnitStringTest, FormatSizeMByte)
{
    IUTEST_EXPECT_STREQ("1MB", ::iutest::detail::FormatSizeByte(1024 * 1024));
    IUTEST_EXPECT_STREQ("1.9MB", ::iutest::detail::FormatSizeByte(2 * 1024 * 1024 - 1));
}

IUTEST(UnitStringTest, FormatSizeGByte)
{
    IUTEST_EXPECT_STREQ("1GB", ::iutest::detail::FormatSizeByte(1024 * 1024 * 1024));
}

IUTEST(UnitStringTest, FormatSizeTByte)
{
    IUTEST_EXPECT_STREQ("1TB", ::iutest::detail::FormatSizeByte(1024ull * 1024 * 1024 * 1024));
    IUTEST_EXPECT_STREQ("1024TB", ::iutest::detail::FormatSizeByte(1024ull * 1024 * 1024 * 1024 * 1024));
}

IUTEST(UnitStringTest, Utf8AsciiCode)
{
    IUTEST_EXPECT_STREQ("A", ::iutest::detail::AnyStringToUTF8(L"A", -1));
    IUTEST_EXPECT_STREQ("A", ::iutest::detail::AnyStringToUTF8(L"A", 1024));
}

IUTEST(UnitStringTest, SurrogatePair)
{
    {
        ::std::string s = ::iutest::detail::AnyStringToUTF8(L"\U00020BB7", -1);
        const unsigned char uexpect[4] = { 0xF0, 0xA0, 0xAE, 0xB7 };
        char expect[4];
        memcpy(expect, uexpect, sizeof(expect));
        IUTEST_EXPECT_EQ_RANGE(expect, s);
    }
    {
        ::std::string s = ::iutest::detail::AnyStringToUTF8(L"\U0001F600", -1);
        const unsigned char uexpect[4] = { 0xF0, 0x9F, 0x98, 0x80 };
        char expect[4];
        memcpy(expect, uexpect, sizeof(expect));
        IUTEST_EXPECT_EQ_RANGE(expect, s);
    }
}

IUTEST(UnitStringTest, StringToValue)
{
    {
        float f;
        IUTEST_EXPECT_TRUE(::iutest::detail::StringToValue("1.0", f));
        IUTEST_EXPECT_FLOAT_EQ(1.0f, f);
    }
    {
        double f;
        IUTEST_EXPECT_TRUE(::iutest::detail::StringToValue("1.0", f));
        IUTEST_EXPECT_DOUBLE_EQ(1.0, f);
    }
#if IUTEST_HAS_LONG_DOUBLE
    {
        long double f;
        IUTEST_EXPECT_TRUE(::iutest::detail::StringToValue("1.0", f));
        IUTEST_EXPECT_LONG_DOUBLE_EQ(1.0l, f);
    }
#endif
}

#if IUTEST_HAS_EXCEPTIONS
IUTEST(UnitStringTest, StringToValueException)
{
    {
        float f = -10.0f;
        IUTEST_EXPECT_THROW(::iutest::detail::StringToValue("ABC", f), ::std::invalid_argument);
        IUTEST_EXPECT_FLOAT_EQ(-10.0f, f);
    }
    {
        float f = -10.0f;
        IUTEST_EXPECT_THROW(::iutest::detail::StringToValue("123456789e1000", f), ::std::out_of_range);
        IUTEST_EXPECT_FLOAT_EQ(-10.0f, f);
    }
    {
        double f = -10.0;
        IUTEST_EXPECT_THROW(::iutest::detail::StringToValue("ABC", f), ::std::invalid_argument);
        IUTEST_EXPECT_DOUBLE_EQ(-10.0, f);
    }
    {
        double f = -10.0;
        IUTEST_EXPECT_THROW(::iutest::detail::StringToValue("123456789e1000", f), ::std::out_of_range);
        IUTEST_EXPECT_DOUBLE_EQ(-10.0, f);
    }
#if IUTEST_HAS_LONG_DOUBLE
    {
        long double f = -10.0l;
        IUTEST_EXPECT_THROW(::iutest::detail::StringToValue("ABC", f), ::std::invalid_argument);
        IUTEST_EXPECT_LONG_DOUBLE_EQ(-10.0l, f);
    }
    {
        long double f = -10.0l;
        IUTEST_EXPECT_THROW(::iutest::detail::StringToValue("123456789e1000000", f), ::std::out_of_range);
        IUTEST_EXPECT_LONG_DOUBLE_EQ(-10.0l, f);
    }
#endif
}
#endif
