//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        unit_string_view_tests.cpp
 * @brief       iutest test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

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
