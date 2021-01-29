//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_string_view_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019-2021, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "logger_tests.hpp"

#if !defined(IUTEST_USE_GTEST)

#define IUTEST_PRINTTOSTRING_EQ(expect, val)        \
    IUTEST_EXPECT_STREQ(static_cast<const char*>(expect), ::iutest::PrintToString(val))

#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)

#define IUTEST_PRINTTOSTRING_CHECK  IUTEST_PRINTTOSTRING_EQ

#else

#define IUTEST_PRINTTOSTRING_CHECK(expect, val)     \
    IUTEST_EXPECT_STRIN(static_cast<const char*>(expect), ::iutest::PrintToString(val))

#endif

#else

#define IUTEST_PRINTTOSTRING_EQ(expect, val)        \
    (void)(expect); \
    (void)(val)

#define IUTEST_PRINTTOSTRING_CHECK(expect, val)     \
    (void)(expect); \
    (void)(val)

#endif

#if !defined(IUTEST_USE_GTEST) && !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)

#define IUTEST_STREAMOUT_CHECK(val) \
    IUTEST_SUCCEED() << val

#else

#define IUTEST_STREAMOUT_CHECK(val) \
    IUTEST_SUCCEED() << ::iutest::PrintToString(val)

#endif

IUTEST(UnitTest, StringView)
{
    ::std::string s = "abc";
    ::iutest::detail::iu_string_view sv1 = "abc";
    ::iutest::detail::iu_string_view sv2 = s;
    ::iutest::detail::iu_string_view sv3 = "ABC";
    IUTEST_EXPECT_EQ(sv1, sv2);
    IUTEST_EXPECT_EQ(sv1, "abc");
    IUTEST_EXPECT_EQ(sv1, s);
    IUTEST_EXPECT_EQ("abc", sv1);
    IUTEST_EXPECT_EQ(s, sv1);

    IUTEST_EXPECT_STREQ(sv1, "abc");
    IUTEST_EXPECT_STREQ("abc", sv2);
    IUTEST_EXPECT_STREQ(sv1, sv2);
    IUTEST_EXPECT_STREQ(s, sv2);
    IUTEST_EXPECT_STREQ(sv1, s);

    IUTEST_EXPECT_NE(sv1, sv3);
    IUTEST_EXPECT_NE(sv3, s);
    IUTEST_EXPECT_NE(sv3, "Abc");
    IUTEST_EXPECT_NE("Abc", sv3);
    IUTEST_EXPECT_NE(s, sv3);

    //IUTEST_EXPECT_STRNE("Abc", sv1);
}

IUTEST(UnitTest, PrintStringView)
{
    LogChecker ck("XYZ");
    ::iutest::detail::iu_string_view view = "XYZ";
    IUTEST_PRINTTOSTRING_EQ(ck, view);
    IUTEST_STREAMOUT_CHECK(view);
}

struct StringViewConvertible
{
    ::std::string name;
    StringViewConvertible()
    : name("ABC")
    {
    }

    operator ::iutest::detail::iu_string_view () const
    {
        return name;
    }
};

IUTEST(UnitTest, PrintStringViewConvertible)
{
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    LogChecker ck("ABC");
#else
    LogChecker ck("-Byte object");
#endif
    StringViewConvertible v;
    IUTEST_PRINTTOSTRING_CHECK(ck, v);
    IUTEST_STREAMOUT_CHECK(v);
}
