//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        print_utf8_tests.cpp
 * @brief       gtest-compatible UTF-8 diagnostic tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/iutest_spi.hpp"
#include "../include/gtest/iutest_switch.hpp"

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000

namespace
{

bool initial_print_utf8;
const ::std::string utf8("\xE3\x81\x82");
const ::std::string escaped_utf8("\"\\xE3\\x81\\x82\"");
const ::std::string other("other");

class PrintUtf8Test : public ::iutest::Test
{
protected:
    virtual void SetUp() IUTEST_CXX_OVERRIDE
    {
        IUTEST_ASSERT_EQ(initial_print_utf8, IUTEST_FLAG_GET(print_utf8));
    }
};

void CheckText(const ::std::string& text, const ::std::string& escaped)
{
    IUTEST_FLAG_SET(print_utf8, false);
    IUTEST_EXPECT_EQ(escaped, ::iutest::PrintToString(text));
    GTEST_FLAG_SET(print_utf8, true);
    IUTEST_EXPECT_EQ(escaped + "\n    As Text: \"" + text + "\"", ::iutest::PrintToString(text));
}

void CheckNoText(const ::std::string& text)
{
    IUTEST_FLAG_SET(print_utf8, false);
    const ::std::string escaped = ::iutest::PrintToString(text);
    IUTEST_FLAG_SET(print_utf8, true);
    IUTEST_EXPECT_EQ(escaped, ::iutest::PrintToString(text));
    IUTEST_EXPECT_EQ(::std::string::npos, escaped.find("As Text:"));
}

}   // namespace

IUTEST_F(PrintUtf8Test, FlagAPI)
{
    IUTEST_FLAG_SET(print_utf8, false);
    IUTEST_EXPECT_FALSE(GTEST_FLAG_GET(print_utf8));
    GTEST_FLAG_SET(print_utf8, true);
    IUTEST_EXPECT_TRUE(IUTEST_FLAG_GET(print_utf8));
    GTEST_FLAG_SET(print_utf8, !initial_print_utf8);
}

IUTEST_F(PrintUtf8Test, CommandLine)
{
#if !defined(IUTEST_USE_GTEST)
    const char* values[] = { "0", "1", "false", "False", "true", "", "no", "00" };
    const bool enabled[] = { false, true, false, false, true, true, true, false };
    const char* prefixes[] = {
        "--gtest_print_utf8", "--iutest_print_utf8"
    };
    for( size_t p = 0; p < sizeof(prefixes)/sizeof(prefixes[0]); ++p )
    {
        for( size_t i = 0; i < sizeof(values)/sizeof(values[0]); ++i )
        {
            char program[] = "print_utf8_tests";
            ::std::string option = ::std::string(prefixes[p]) + "=" + values[i];
            ::std::vector<char> argument(option.begin(), option.end());
            argument.push_back('\0');
            char* argv[] = { program, &argument[0], NULL };
            int argc = 2;
            IUTEST_FLAG_SET(print_utf8, !enabled[i]);
            IUTEST_INIT(&argc, argv);
            IUTEST_EXPECT_EQ(1, argc);
            IUTEST_EXPECT_EQ(enabled[i], IUTEST_FLAG_GET(print_utf8));
        }
        char program[] = "print_utf8_tests";
        ::std::string option(prefixes[p]);
        ::std::vector<char> argument(option.begin(), option.end());
        argument.push_back('\0');
        char* argv[] = { program, &argument[0], NULL };
        int argc = 2;
        IUTEST_FLAG_SET(print_utf8, false);
        IUTEST_INIT(&argc, argv);
        IUTEST_EXPECT_EQ(1, argc);
        IUTEST_EXPECT_TRUE(IUTEST_FLAG_GET(print_utf8));
    }
#else
    IUTEST_EXPECT_EQ(initial_print_utf8, GTEST_FLAG_GET(print_utf8));
#endif
}

IUTEST_F(PrintUtf8Test, PrintableUTF8)
{
    CheckText(utf8, escaped_utf8);
    CheckText("\xC2\x80", "\"\\xC2\\x80\"");
    CheckText("\xDF\xBF", "\"\\xDF\\xBF\"");
    CheckText("\xE0\xA0\x80", "\"\\xE0\\xA0\\x80\"");
    CheckText("\xED\x9F\xBF", "\"\\xED\\x9F\\xBF\"");
    CheckText("\xEE\x80\x80", "\"\\xEE\\x80\\x80\"");
    CheckText("\xEF\xBF\xBF", "\"\\xEF\\xBF\\xBF\"");
    CheckText("\xF0\x90\x80\x80", "\"\\xF0\\x90\\x80\\x80\"");
    CheckText("\xF4\x8F\xBF\xBF", "\"\\xF4\\x8F\\xBF\\xBF\"");
    CheckText(utf8 + "A\n\t\r\"\\", "\"\\xE3\\x81\\x82\" \"A\\n\\t\\r\\\"\\\\\"");
}

IUTEST_F(PrintUtf8Test, ASCII)
{
    CheckNoText("");
    CheckNoText("plain text");
    CheckNoText("\n\t\r\"\\");
}

IUTEST_F(PrintUtf8Test, InvalidUTF8)
{
    const char* invalid[] = {
        "\x80", "\xBF", "\xC0\xAF", "\xC1\xBF", "\xC2", "\xC2 ",
        "\xE0\x9F\xBF", "\xE0\xA0", "\xE1\x80 ", "\xED\xA0\x80",
        "\xED\xBF\xBF", "\xF0\x8F\xBF\xBF", "\xF0\x90\x80",
        "\xF1\x80\x80 ", "\xF4\x90\x80\x80", "\xF5\x80\x80\x80", "\xFF"
    };
    for( size_t i = 0; i < sizeof(invalid)/sizeof(invalid[0]); ++i )
    {
        CheckNoText(invalid[i]);
        CheckNoText(utf8 + invalid[i]);
    }
}

IUTEST_F(PrintUtf8Test, ControlCharacters)
{
    for( int code = 0; code <= 0x7F; ++code )
    {
        if( code >= 0x20 && code != 0x7F ) { continue; }
        if( code == '\n' || code == '\t' || code == '\r' ) { continue; }
        CheckNoText(utf8 + static_cast<char>(code));
    }
}

IUTEST_F(PrintUtf8Test, FailureMessage)
{
    IUTEST_FLAG_SET(print_utf8, true);
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_EQ(utf8, other), "\n    As Text: \"");
    IUTEST_FLAG_SET(print_utf8, false);
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_EQ(utf8, other), escaped_utf8.c_str());
}

IUTEST_F(PrintUtf8Test, OtherPrintersUnchanged)
{
    IUTEST_FLAG_SET(print_utf8, true);
    const char text[] = "\xE3\x81\x82";
    IUTEST_EXPECT_EQ(escaped_utf8, ::iutest::PrintToString(text));
    IUTEST_EXPECT_EQ(escaped_utf8 + "\n    As Text: \"" + utf8 + "\"", ::iutest::PrintToString(text + 0));
    IUTEST_EXPECT_STREQ("L\"\\x3042\"", ::iutest::PrintToString(::std::wstring(1, static_cast<wchar_t>(0x3042))));
#if IUTEST_HAS_CXX_HDR_STRING_VIEW
    IUTEST_EXPECT_EQ(escaped_utf8 + "\n    As Text: \"" + utf8 + "\"",
        ::iutest::PrintToString(::std::string_view(utf8.data(), utf8.size())));
    IUTEST_FLAG_SET(print_utf8, false);
    IUTEST_EXPECT_EQ(escaped_utf8, ::iutest::PrintToString(::std::string_view(utf8.data(), utf8.size())));
#endif
#if !defined(IUTEST_USE_GTEST)
    ::iutest::detail::iuStreamMessage message;
    message << utf8;
    IUTEST_EXPECT_EQ(utf8, message.GetString());
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
    IUTEST_FLAG_SET(print_utf8, true);
    ::iutest::iu_stringstream stream;
    stream << ::std::hex;
    const ::std::ios_base::fmtflags flags = stream.flags();
    ::iutest::detail::PrintTo(utf8, &stream);
    IUTEST_EXPECT_EQ(escaped_utf8 + "\n    As Text: \"" + utf8 + "\"", stream.str());
    IUTEST_EXPECT_EQ(flags, stream.flags());
#endif
#endif
}

#endif

int main(int argc, char* argv[])
{
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000
    const char* env = NULL;
#if !defined(IUTEST_USE_GTEST)
    env = getenv("IUTEST_PRINT_UTF8");
#endif
    if( env == NULL ) { env = getenv("GTEST_PRINT_UTF8"); }
    const bool expected = env == NULL || ::std::string(env) != "0";
    IUTEST_EXPECT_EQ(expected, IUTEST_FLAG_GET(print_utf8));
    if( expected != IUTEST_FLAG_GET(print_utf8) ) { return 1; }
    bool expected_cli = expected;
    const char* prefixes[] = {
        "--gtest_print_utf8"
#if !defined(IUTEST_USE_GTEST)
        , "--iutest_print_utf8"
#endif
    };
    for( int i = 1; i < argc; ++i )
    {
        for( size_t p = 0; p < sizeof(prefixes)/sizeof(prefixes[0]); ++p )
        {
            const ::std::string option(argv[i]);
            const ::std::string prefix(prefixes[p]);
            if( option == prefix ) { expected_cli = true; }
            else if( option.compare(0, prefix.size() + 1, prefix + "=") == 0 )
            {
                const char value = option.c_str()[prefix.size() + 1];
                expected_cli = value != '0' && value != 'f' && value != 'F';
            }
        }
    }
#endif
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000
    IUTEST_EXPECT_EQ(expected_cli, IUTEST_FLAG_GET(print_utf8));
    if( expected_cli != IUTEST_FLAG_GET(print_utf8) ) { return 1; }
    initial_print_utf8 = IUTEST_FLAG_GET(print_utf8);
#endif
    const int result = IUTEST_RUN_ALL_TESTS();
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000
    IUTEST_EXPECT_EQ(initial_print_utf8, IUTEST_FLAG_GET(print_utf8));
#endif
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000
    return result != 0 || initial_print_utf8 != IUTEST_FLAG_GET(print_utf8) ? 1 : 0;
#else
    return result;
#endif
}
