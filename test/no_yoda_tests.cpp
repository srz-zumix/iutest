//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        no_yoda_tests.cpp
 * @brief       iutest no yoda test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2021, Takazumi Shirayanagi\n
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
#if IUTEST_HAS_LONG_DOUBLE
long double gl = 0.0l;
#endif
::std::complex<float> gc(1.0f, 1.0f);
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

#if IUTEST_HAS_LONG_DOUBLE

IUTEST(NoYodaTest, LongDoubleEq)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_LONG_DOUBLE_EQ(gl, 1.0l), "Expected: 1.0" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_LONG_DOUBLE_EQ(gl, 1.0l), "Expected: 1.0" );
}

#endif

IUTEST(NoYodaTest, ComplexEq)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_COMPLEX_EQ(gc, 1.0f), "Expected: 1.0" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_COMPLEX_EQ(gc, 1.0f), "Expected: 1.0" );
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

