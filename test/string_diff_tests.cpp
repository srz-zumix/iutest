//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        string_diff_tests.cpp
 * @brief       gtest-compatible multiline string comparison diagnostics
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

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01180000

namespace
{

::std::string Diff(const ::iutest::AssertionResult& result)
{
    const ::std::string message = result.message();
    const ::std::string::size_type start = message.find("\nWith diff:\n");
    return start == ::std::string::npos ? ::std::string() : message.substr(start);
}

::std::string EqDiff(const ::std::string& left, const ::std::string& right)
{
    const ::iutest::AssertionResult result = ::iutest::internal::CmpHelperEQ("left", "right", left, right);
    IUTEST_EXPECT_FALSE(result);
    return Diff(result);
}

const ::std::string left_text = "first\nleft\nlast";
const ::std::string right_text = "first\nright\nlast";

}   // end of namespace

IUTEST(StringDiffTest, Replacement)
{
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,3 +1,3 @@\n first\n-left\n+right\n last\n",
        EqDiff(left_text, right_text));
}

IUTEST(StringDiffTest, InsertionAndDeletion)
{
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,2 +1,3 @@\n first\n+middle\n last\n",
        EqDiff("first\nlast", "first\nmiddle\nlast"));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,3 +1,2 @@\n first\n-middle\n last\n",
        EqDiff("first\nmiddle\nlast", "first\nlast"));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,2 +1,2 @@\n-old1\n-old2\n+new1\n+new2\n",
        EqDiff("old1\nold2", "new1\nnew2"));
}

IUTEST(StringDiffTest, EmptyStringsAndLines)
{
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1 +1,2 @@\n-\"\"\n+a\n+b\n", EqDiff("", "a\nb"));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,2 +1 @@\n-a\n-b\n+\"\"\n", EqDiff("a\nb", ""));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,2 +1,3 @@\n a\n+\n b\n", EqDiff("a\nb", "a\n\nb"));
    IUTEST_EXPECT_EQ("", EqDiff("a", "a\n"));
    IUTEST_EXPECT_EQ("", EqDiff("a\n", "a"));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,2 +1,2 @@\n a\n-b\n+b\\n\n", EqDiff("a\nb", "a\nb\n"));
}

IUTEST(StringDiffTest, Escapes)
{
    IUTEST_EXPECT_EQ("", EqDiff("a\\nb", "a\\nc"));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1 +1,2 @@\n-a\\\\nb\n+a\n+b\n", EqDiff("a\\nb", "a\nb"));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,2 +1,2 @@\n a\\\\\n-b\\t\\r\\\"\\0\n+c\\t\\r\\\"\\0\n",
        EqDiff(::std::string("a\\\nb\t\r\"\0", 8), ::std::string("a\\\nc\t\r\"\0", 8)));
}

IUTEST(StringDiffTest, ContextAndHunks)
{
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -3,5 +3,5 @@\n 2\n 3\n-left\n+right\n 5\n 6\n",
        EqDiff("0\n1\n2\n3\nleft\n5\n6\n7\n8", "0\n1\n2\n3\nright\n5\n6\n7\n8"));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,3 +1,3 @@\n-left\n+right\n 1\n 2\n"
        "@@ -4,3 +4,3 @@\n 3\n 4\n-old\n+new\n",
        EqDiff("left\n1\n2\n3\n4\nold", "right\n1\n2\n3\n4\nnew"));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,5 +1,5 @@\n-left\n+right\n 1\n 2\n 3\n-old\n+new\n",
        EqDiff("left\n1\n2\n3\nold", "right\n1\n2\n3\nnew"));
}

IUTEST(StringDiffTest, RepeatedLines)
{
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,3 +1,3 @@\n-a\n-b\n-a\n+b\n+a\n+b\n", EqDiff("a\nb\na", "b\na\nb"));
}

IUTEST(StringDiffTest, LongRepeatedLines)
{
    const ::std::string common(1024, 'a');
    ::std::string left, right;
    for( int i = 0; i < 100; ++i )
    {
        left += common + (i == 50 ? "left" : "") + "\n";
        right += common + (i == 50 ? "right" : "") + "\n";
    }
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -49,5 +49,5 @@\n " + common + "\n " + common
        + "\n-" + common + "left\n+" + common + "right\n " + common + "\n " + common + "\n",
        EqDiff(left, right));
}

IUTEST(StringDiffTest, AssertionCoverage)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_EQ(left_text, right_text), "With diff:\n");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_EQ(left_text, right_text), "-left\n+right\n");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_STREQ(left_text.c_str(), right_text.c_str()), "-left\n+right\n");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_STREQ(left_text.c_str(), right_text.c_str()), "With diff:\n");
    IUTEST_EXPECT_NONFATAL_FAILURE(IUTEST_EXPECT_STRCASEEQ(left_text.c_str(), right_text.c_str()), "-left\n+right\n");
    IUTEST_EXPECT_FATAL_FAILURE(IUTEST_ASSERT_STRCASEEQ(left_text.c_str(), right_text.c_str()), "With diff:\n");
    IUTEST_EXPECT_EQ(Diff(::iutest::internal::CmpHelperEQ("left", "right", left_text, right_text)),
        Diff(::iutest::internal::CmpHelperSTREQ("left", "right", left_text.c_str(), right_text.c_str())));
    IUTEST_EXPECT_TRUE(::iutest::internal::CmpHelperSTRCASEEQ("left", "right", "a\nB", "A\nb"));
    IUTEST_EXPECT_TRUE(::iutest::internal::CmpHelperEQ("left", "right", left_text, left_text));
    IUTEST_EXPECT_TRUE(::iutest::internal::CmpHelperSTREQ("left", "right", "a\nb", "a\nb"));
}

IUTEST(StringDiffTest, WideStrings)
{
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,3 +1,3 @@\n L\"first\n-left\n+right\n last\"\n",
        Diff(::iutest::internal::CmpHelperEQ("left", "right",
            ::std::wstring(L"first\nleft\nlast"), ::std::wstring(L"first\nright\nlast"))));
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,3 +1,3 @@\n L\"first\n-left\n+right\n last\"\n",
        Diff(::iutest::internal::CmpHelperSTREQ("left", "right", L"first\nleft\nlast", L"first\nright\nlast")));
}

#if IUTEST_HAS_CHAR16_T || (defined(IUTEST_USE_GTEST) && GTEST_VER >= 0x01110000)
IUTEST(StringDiffTest, U16Strings)
{
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,2 +1,2 @@\n u\"first\n-left\"\n+right\"\n",
        Diff(::iutest::internal::CmpHelperEQ("left", "right",
            ::std::u16string(u"first\nleft"), ::std::u16string(u"first\nright"))));
}
#endif

#if IUTEST_HAS_CHAR32_T || (defined(IUTEST_USE_GTEST) && GTEST_VER >= 0x01110000)
IUTEST(StringDiffTest, U32Strings)
{
    IUTEST_EXPECT_EQ("\nWith diff:\n@@ -1,2 +1,2 @@\n U\"first\n-left\"\n+right\"\n",
        Diff(::iutest::internal::CmpHelperEQ("left", "right",
            ::std::u32string(U"first\nleft"), ::std::u32string(U"first\nright"))));
}
#endif

IUTEST(StringDiffTest, UnaffectedDiagnostics)
{
    IUTEST_EXPECT_EQ("", EqDiff("left", "right"));
    IUTEST_EXPECT_EQ("", Diff(::iutest::internal::CmpHelperEQ("left", "right", 1, 2)));
    const char* left = "first\nleft";
    const char* right = "first\nright";
    IUTEST_EXPECT_EQ("", Diff(::iutest::internal::CmpHelperEQ("left", "right", left, right)));
    char left_array[] = "first\nleft";
    char right_array[] = "first\nright";
    IUTEST_EXPECT_EQ("", Diff(::iutest::internal::CmpHelperEQ("left", "right", left_array, &right_array[0])));
    const wchar_t* wide_right = L"first\nright";
    IUTEST_EXPECT_EQ("", Diff(::iutest::internal::CmpHelperEQ("left", "right", L"first\nleft", wide_right)));
    IUTEST_EXPECT_EQ(EqDiff(left_text, right_text),
        Diff(::iutest::internal::CmpHelperEQ("left", "right", left_text.c_str(), right_text)));
    IUTEST_EXPECT_EQ(EqDiff(left_text, right_text),
        Diff(::iutest::internal::CmpHelperEQ("left", "right", left_text, right_text.c_str())));
    IUTEST_EXPECT_EQ("", Diff(::iutest::internal::CmpHelperSTREQ("left", "right", "left", "right")));
    IUTEST_EXPECT_EQ("", Diff(::iutest::internal::CmpHelperSTRNE("left", "right", left, left)));
    IUTEST_EXPECT_EQ("", Diff(::iutest::internal::CmpHelperSTRCASENE("left", "right", left, left)));
    IUTEST_EXPECT_TRUE(::iutest::internal::CmpHelperSTREQ("left", "right",
        static_cast<const char*>(IUTEST_NULLPTR), static_cast<const char*>(IUTEST_NULLPTR)));
    IUTEST_EXPECT_FALSE(::iutest::internal::CmpHelperSTREQ("left", "right",
        static_cast<const char*>(IUTEST_NULLPTR), ""));
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ("error: Value of right\n  Actual: 2\nExpected: left\nWhich is: 1",
        ::iutest::internal::CmpHelperEQ("left", "right", 1, 2).message());
#endif
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(StringDiffTest, BoundedDiagnosticWork)
{
    ::std::string left, right;
    for( int i = 0; i < 1024; ++i )
    {
        left += "left\n";
        right += "right\n";
    }
    const ::iutest::AssertionResult result = ::iutest::internal::CmpHelperEQ("left", "right", left, right);
    IUTEST_EXPECT_FALSE(result);
    IUTEST_EXPECT_EQ("", Diff(result));
    IUTEST_EXPECT_STRIN("error: Value of right\n  Actual: ", result.message());
    IUTEST_EXPECT_STRIN("\nExpected: left\nWhich is: ", result.message());
    IUTEST_EXPECT_EQ("", ::iutest::internal::CreateStringDiff("", "\"a\\nb\""));
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
