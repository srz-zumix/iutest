//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_filter_tests.cpp
 * @brief		filter 対応テスト
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

IUTEST(Test, Fail)
{
	IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Fail, Test)
{
	IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, Bar)
{
	IUTEST_ASSERT_EQ(3, 3);
}

IUTEST(Foo, Baz)
{
	IUTEST_ASSERT_EQ(3, 3);
}

IUTEST(Foo, BarFail)
{
	IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, Qux)
{
	IUTEST_ASSERT_EQ(3, 3);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	{
		::iutest::IUTEST_FLAG(filter) = "*Fail*";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret == 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 3 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 3 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
	{
		::iutest::IUTEST_FLAG(filter) = "-*Fail*";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 3 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 3 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
	{
		::iutest::IUTEST_FLAG(filter) = "Foo.Bar";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 1 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 5 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
	{
		::iutest::IUTEST_FLAG(filter) = "***.Bar";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 1 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 5 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
	{
		::iutest::IUTEST_FLAG(filter) = "???.Ba?";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 2 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 4 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
	{
		::iutest::IUTEST_FLAG(filter) = "Foo.Ba*-*Fail*";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 2 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 4 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
#if !defined(IUTEST_USE_GTEST)
	{
		::iutest::IUTEST_FLAG(filter) = "Foo.Ba*:-*Fail*";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret == 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 4 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 2 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
#endif
	{
		::iutest::IUTEST_FLAG(filter) = "*Baz*:*Qux*";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 2 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 4 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
	{
		::iutest::IUTEST_FLAG(filter) = ":::*Baz*:::::*Qux*:::";
		const int ret = IUTEST_RUN_ALL_TESTS();
		
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_count() == 2 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 0 );
#endif
#if !defined(IUTEST_USE_GTEST)
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 4 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 0 );
		IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->reportable_test_run_skipped_count() == 0 );
#endif
	}
	printf("*** Successful ***\n");
	return 0;
}
