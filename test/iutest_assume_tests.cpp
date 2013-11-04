//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_assume_tests.cpp
 * @brief		iutest assume test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

IUTEST(AssumeTest, A)
{
	IUTEST_ASSUME_TRUE(false);
}

IUTEST(AssumeTest, B)
{
	IUTEST_ASSUME_EQ(0, 1);
	IUTEST_ASSERT_EQ(0, 1);
}

IUTEST(AssumeTest, C)
{
	IUTEST_ASSERT_EQ(0, 1);
	IUTEST_ASSUME_EQ(0, 1);
}

#ifdef UNICODE
int wmain(int argc, wchar_t** argv)
#else
int main(int argc, char** argv)
#endif
{
	IUTEST_INIT(&argc, argv);
	int ret = IUTEST_RUN_ALL_TESTS();
	if( ret == 0 ) return 1;
#if !defined(IUTEST_USE_GTEST)
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->test_run_skipped_count() == 2 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 2 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 2 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 2 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->successful_test_case_count() == 0 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 1 );
#endif
	printf("*** Successful ***\n");
	return 0;
}

