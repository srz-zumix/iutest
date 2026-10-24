//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        compatible_printers_tests.cpp
 * @brief       gtest-compatible value printer tests
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

IUTEST(CompatiblePrintersTest, Character)
{
    IUTEST_EXPECT_STREQ("'a' (97, 0x61)", ::iutest::PrintToString('a'));
    IUTEST_EXPECT_STREQ("'\\n' (10, 0xA)", ::iutest::PrintToString('\n'));
    IUTEST_EXPECT_STREQ("'\\0'", ::iutest::PrintToString('\0'));
    IUTEST_EXPECT_STREQ("'\\t' (9)", ::iutest::PrintToString('\t'));
    IUTEST_EXPECT_STREQ("'\\'' (39, 0x27)", ::iutest::PrintToString('\''));
    IUTEST_EXPECT_STREQ("'\\\\' (92, 0x5C)", ::iutest::PrintToString('\\'));
    IUTEST_EXPECT_STREQ("'\\x7F' (127)", ::iutest::PrintToString('\177'));
    IUTEST_EXPECT_STREQ("'\\x80' (128)", ::iutest::PrintToString(static_cast<char>(0x80)));
    IUTEST_EXPECT_STREQ("L'a' (97, 0x61)", ::iutest::PrintToString(L'a'));
    IUTEST_EXPECT_STREQ("L'\\n' (10, 0xA)", ::iutest::PrintToString(L'\n'));
}

IUTEST(CompatiblePrintersTest, String)
{
    IUTEST_EXPECT_STREQ("\"ab\"", ::iutest::PrintToString(::std::string("ab")));
    IUTEST_EXPECT_STREQ("\"\"", ::iutest::PrintToString(::std::string()));
    IUTEST_EXPECT_STREQ("\" \"", ::iutest::PrintToString(::std::string(" ")));
    IUTEST_EXPECT_STREQ("\"a\\0b\"", ::iutest::PrintToString(::std::string("a\0b", 3)));
    IUTEST_EXPECT_STREQ("\"\\n\\t\\r\\\\\\\"'\"", ::iutest::PrintToString(::std::string("\n\t\r\\\"'")));
    IUTEST_EXPECT_STREQ("\"\\x1\" \"A\"", ::iutest::PrintToString(::std::string("\001A")));
    IUTEST_EXPECT_STREQ("L\"ab\"", ::iutest::PrintToString(::std::wstring(L"ab")));
    IUTEST_EXPECT_STREQ("L\"\"", ::iutest::PrintToString(::std::wstring()));
    IUTEST_EXPECT_STREQ("L\"a\\0b\"", ::iutest::PrintToString(::std::wstring(L"a\0b", 3)));
    IUTEST_EXPECT_STREQ("L\"\\x1234\"", ::iutest::PrintToString(::std::wstring(1, static_cast<wchar_t>(0x1234))));
}

#if IUTEST_HAS_CHAR8_T && (!defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01110000)
IUTEST(CompatiblePrintersTest, U8String)
{
    IUTEST_EXPECT_STREQ("u8\"ab\"", ::iutest::PrintToString(::std::u8string(u8"ab")));
    IUTEST_EXPECT_STREQ("u8\"\"", ::iutest::PrintToString(::std::u8string()));
    IUTEST_EXPECT_STREQ("u8\"a\\0b\"", ::iutest::PrintToString(::std::u8string(u8"a\0b", 3)));
}
#endif

#if IUTEST_HAS_CHAR16_T || (defined(IUTEST_USE_GTEST) && GTEST_VER >= 0x01110000)
IUTEST(CompatiblePrintersTest, U16String)
{
    IUTEST_EXPECT_STREQ("u\"ab\"", ::iutest::PrintToString(::std::u16string(u"ab")));
    IUTEST_EXPECT_STREQ("u\"\"", ::iutest::PrintToString(::std::u16string()));
    IUTEST_EXPECT_STREQ("u\"a\\0b\"", ::iutest::PrintToString(::std::u16string(u"a\0b", 3)));
}
#endif

#if IUTEST_HAS_CHAR32_T || (defined(IUTEST_USE_GTEST) && GTEST_VER >= 0x01110000)
IUTEST(CompatiblePrintersTest, U32String)
{
    IUTEST_EXPECT_STREQ("U\"ab\"", ::iutest::PrintToString(::std::u32string(U"ab")));
    IUTEST_EXPECT_STREQ("U\"\"", ::iutest::PrintToString(::std::u32string()));
    IUTEST_EXPECT_STREQ("U\"a\\0b\"", ::iutest::PrintToString(::std::u32string(U"a\0b", 3)));
}
#endif

#if IUTEST_HAS_NULLPTR
IUTEST(CompatiblePrintersTest, Nullptr)
{
    IUTEST_EXPECT_STREQ("(nullptr)", ::iutest::PrintToString(nullptr));
}
#endif

#if IUTEST_HAS_CXX_HDR_OPTIONAL && (!defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01110000)
IUTEST(CompatiblePrintersTest, Optional)
{
    IUTEST_EXPECT_STREQ("(42)", ::iutest::PrintToString(::std::optional<int>(42)));
    IUTEST_EXPECT_STREQ("(nullopt)", ::iutest::PrintToString(::std::optional<int>()));
    IUTEST_EXPECT_STREQ("(\"ab\")", ::iutest::PrintToString(::std::optional< ::std::string >("ab")));
}
#endif

#if IUTEST_HAS_CXX_HDR_ANY && (!defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01110000)
IUTEST(CompatiblePrintersTest, Any)
{
    IUTEST_EXPECT_STREQ("no value", ::iutest::PrintToString(::std::any()));
#if IUTEST_HAS_RTTI
    IUTEST_EXPECT_STREQ("value of type int", ::iutest::PrintToString(::std::any(1)));
#if defined(IUTEST_USE_GTEST)
    const ::std::string type_name = ::testing::internal::GetTypeName< ::std::string >();
#else
    const ::std::string type_name = ::iutest::detail::PrintTypeName(typeid(::std::string));
#endif
    IUTEST_EXPECT_EQ("value of type " + type_name, ::iutest::PrintToString(::std::any(::std::string("ab"))));
#else
    IUTEST_EXPECT_STREQ("value of type <unknown_type>", ::iutest::PrintToString(::std::any(1)));
#endif
}
#endif

#if IUTEST_HAS_CXX_HDR_VARIANT && (!defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01110000)
IUTEST(CompatiblePrintersTest, Variant)
{
    ::std::variant<int, ::std::string, int> value(::std::in_place_index<0>, 1);
#if IUTEST_HAS_RTTI
    IUTEST_EXPECT_STREQ("('int(index = 0)' with value 1)", ::iutest::PrintToString(value));
    value.emplace<2>(42);
    IUTEST_EXPECT_STREQ("('int(index = 2)' with value 42)", ::iutest::PrintToString(value));
#else
    IUTEST_EXPECT_STREQ("('<unknown_type>(index = 0)' with value 1)", ::iutest::PrintToString(value));
#endif
    value.emplace<1>("ab");
#if IUTEST_HAS_RTTI
#if defined(IUTEST_USE_GTEST)
    const ::std::string type_name = ::testing::internal::GetTypeName< ::std::string >();
#else
    const ::std::string type_name = ::iutest::detail::PrintTypeName(typeid(::std::string));
#endif
    IUTEST_EXPECT_EQ("('" + type_name + "(index = 1)' with value \"ab\")", ::iutest::PrintToString(value));
#else
    IUTEST_EXPECT_STRIN("(index = 1)' with value \"ab\")", ::iutest::PrintToString(value));
#endif
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000
    IUTEST_EXPECT_STREQ("(monostate)", ::iutest::PrintToString(::std::monostate()));
#endif
}
#endif

#if IUTEST_HAS_CXX_HDR_STRING_VIEW && (!defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01110000)
IUTEST(CompatiblePrintersTest, StringView)
{
    IUTEST_EXPECT_STREQ("\"\"", ::iutest::PrintToString(::std::string_view()));
    IUTEST_EXPECT_STREQ("\"ab\"", ::iutest::PrintToString(::std::string_view("abcd", 2)));
    IUTEST_EXPECT_STREQ("\"a\\0b\"", ::iutest::PrintToString(::std::string_view("a\0b", 3)));
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ("L\"ab\"", ::iutest::PrintToString(::std::wstring_view(L"abcd", 2)));
#endif
}
#endif

namespace {
const ::std::string empty, space(" "), line("a\n"), other("b"), lhs("ab"), rhs("cd");
const ::std::wstring wide_lhs(L"ab"), wide_rhs(L"cd");
} // namespace

IUTEST(CompatiblePrintersTest, StringFailureMessage)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_EQ(empty, space), "\" \"");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_EQ(line, other), "\"a\\n\"");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_STREQ(lhs.c_str(), rhs.c_str()), "\"ab\"");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_STREQ(line.c_str(), other.c_str()), "\"a\\n\"");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_EQ(wide_lhs, wide_rhs), "L\"ab\"");
#if !defined(IUTEST_USE_GTEST)
    const ::iutest::AssertionResult result =
        ::iutest::internal::CmpHelperSTREQ("lhs", "rhs", lhs, rhs);
    const ::std::string message = result.message();
    IUTEST_EXPECT_STRIN("\"ab\"", message);
    IUTEST_EXPECT_EQ(::std::string::npos, message.find("\"\"ab\"\""));
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_STRNE(lhs, lhs), "\"ab\"");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_STRCASEEQ(lhs, rhs), "\"ab\"");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_STRCASENE(lhs, lhs), "\"ab\"");
#endif
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(CompatiblePrintersTest, MessageText)
{
    char text[] = "message";
    const char* null_text = IUTEST_NULLPTR;
    ::iutest::detail::iuStreamMessage message;
    message << "text: " << ::std::string("value") << " " << text << null_text;
    IUTEST_EXPECT_STREQ("text: value message(null)", message.GetString());
}
#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
