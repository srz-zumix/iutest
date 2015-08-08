//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		no_yoda_tests.cpp
 * @brief		iutest no yoda test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2015, Takazumi Shirayanagi\n
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

int a=0;
float f=0.0f;
double d=0.0;
char x[]="Hoge";
char y[]="Test";

IUTEST(NoYodaTest, Eq)
{
	IUTEST_ASSERT_FATAL_FAILURE( IUTEST_ASSERT_EQ(a, 1), "Expected: 1" );
	IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_EQ(a, 1), "Expected: 1" );
}

IUTEST(NoYodaTest, FloatEq)
{
	IUTEST_ASSERT_FATAL_FAILURE( IUTEST_ASSERT_FLOAT_EQ(f, 1.0f), "Expected: 1.0f" );
	IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_FLOAT_EQ(f, 1.0f), "Expected: 1.0f" );
}

IUTEST(NoYodaTest, DoubleEq)
{
	IUTEST_ASSERT_FATAL_FAILURE( IUTEST_ASSERT_FLOAT_EQ(d, 1.0), "Expected: 1.0" );
	IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_FLOAT_EQ(d, 1.0), "Expected: 1.0" );
}

IUTEST(NoYodaTest, StrEq)
{
	IUTEST_ASSERT_FATAL_FAILURE( IUTEST_ASSERT_STREQ(x, "hoge"), "Expected: \"hoge\"" );
	IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_STREQ(x, "hoge"), "Expected: \"hoge\"" );
}

IUTEST(NoYodaTest, StrCaseEq)
{
	IUTEST_ASSERT_FATAL_FAILURE( IUTEST_ASSERT_STRCASEEQ(y, "hoge"), "Expected: \"hoge\"" );
	IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_STRCASEEQ(y, "hoge"), "Expected: \"hoge\"" );
}

