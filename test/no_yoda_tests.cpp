//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        no_yoda_tests.cpp
 * @brief       iutest no yoda test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"
#include "../include/util/iutest_util_no_yoda.hpp"


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

int ga = 0;
float gf = 0.0f;
double gd = 0.0;
char gx[] = "Hoge";
char gy[] = "Test";

IUTEST(NoYodaTest, Eq)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_EQ(ga, 1), "Expected: 1" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_EQ(ga, 1), "Expected: 1" );
}

IUTEST(NoYodaTest, FloatEq)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_FLOAT_EQ(gf, 1.0f), "Expected: 1.0f" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_FLOAT_EQ(gf, 1.0f), "Expected: 1.0f" );
}

IUTEST(NoYodaTest, DoubleEq)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_DOUBLE_EQ(gd, 1.0), "Expected: 1.0" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_DOUBLE_EQ(gd, 1.0), "Expected: 1.0" );
}

IUTEST(NoYodaTest, StrEq)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_STREQ(gx, "hoge"), "Expected: \"hoge\"" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_STREQ(gx, "hoge"), "Expected: \"hoge\"" );
}

IUTEST(NoYodaTest, StrCaseEq)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_STRCASEEQ(gy, "hoge"), "Expected: \"hoge\"" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_STRCASEEQ(gy, "hoge"), "Expected: \"hoge\"" );
}

