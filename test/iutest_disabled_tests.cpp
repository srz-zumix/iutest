//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_disabled_tests.cpp
 * @brief		also_run_disabled_tests ‘Î‰žƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#include <assert.h>

IUTEST(DISABLED_Foo, Bar)
{
	IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, DISABLED_Bar)
{
	IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, Bar)
{
	IUTEST_ASSERT_EQ(3, 3);
}

IUTEST(Foo, Bar_DISABLED_)
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
		int ret = IUTEST_RUN_ALL_TESTS();
		if( ret != 0 ) return 1;
		assert( ::iutest::UnitTest::GetInstance()->disabled_test_count() == 2 );
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		assert( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 2 );
#endif
#if !defined(IUTEST_USE_GTEST)
		assert( ::iutest::UnitTest::GetInstance()->skip_test_count() == 2 );
#endif
	}
	
	{
		::iutest::IUTEST_FLAG(also_run_disabled_tests) = true;
		int ret = IUTEST_RUN_ALL_TESTS();
		assert( ::iutest::UnitTest::GetInstance()->disabled_test_count() == 2 );
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
		assert( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == 2 );
#endif
		assert( ::iutest::UnitTest::GetInstance()->test_to_run_count() == 4 );
		assert( ::iutest::UnitTest::GetInstance()->failed_test_count() == 2 );
		assert( ::iutest::UnitTest::GetInstance()->total_test_count() == 4 );
#if !defined(IUTEST_USE_GTEST)
		assert( ::iutest::UnitTest::GetInstance()->skip_test_count() == 0 );
#endif
		if( ret == 0 ) return 1;
	}
	printf("*** Successful ***\n");
	return 0;
}
