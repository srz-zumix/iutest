//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_skip_tests.cpp
 * @brief		IUTEST_SKIP 対応テスト
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

static bool skip_check = true;

IUTEST(DISABLED_SkipTest, A)
{
}

IUTEST(SkipTest, CanSkip)
{
	IUTEST_SKIP() << "test";
	IUTEST_EXPECT_EQ(2, 3);
}

IUTEST(SkipTest, Failed)
{
	IUTEST_EXPECT_EQ(2, 3);
	IUTEST_SKIP();
	skip_check = false;
	IUTEST_EXPECT_EQ(2, 3);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
	// 失敗テストを含むので xml 出力しない
	::iutest::IUTEST_FLAG(output) = NULL;
#endif
	const int ret = IUTEST_RUN_ALL_TESTS();
	if( ret == 0 ) return 1;
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->test_to_run_count() == 2 );
#if !defined(IUTEST_USE_GTEST)
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->test_run_skipped_count() == 1 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 1 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 2 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 2 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->successful_test_count() == 0 );
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->successful_test_case_count() == 1 );
#endif
	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 1 );
	IUTEST_ASSERT( skip_check );
	printf("*** Successful ***\n");
	return 0;
}
