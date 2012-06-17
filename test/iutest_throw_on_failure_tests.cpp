//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_throw_on_fialure_tests.cpp
 * @brief		throw_on_fialure ‘Î‰žƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#include <assert.h>

#if IUTEST_HAS_EXCEPTIONS

IUTEST(Expect, Test)
{
	IUTEST_EXPECT_EQ(2, 1);
}

IUTEST(Expect, Dummy)
{
	IUTEST_EXPECT_EQ(2, 1);
}

IUTEST(Assert, Test)
{
	IUTEST_ASSERT_EQ(2, 1);
}

IUTEST(Assert, Dummy)
{
	IUTEST_ASSERT_EQ(2, 1);
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	::iutest::IUTEST_FLAG(throw_on_failure) = true;
	
#if IUTEST_HAS_EXCEPTIONS
	{
		::iutest::IUTEST_FLAG(filter) = "*Expect*";
		IUTEST_INIT(&argc, argv);
		int ret = IUTEST_RUN_ALL_TESTS();	// run all
		
		assert( ret != 0 );
		assert( ::iutest::UnitTest::GetInstance()->failed_test_count() == 1 );
	}

	{
		::iutest::IUTEST_FLAG(filter) = "*Assert*";
		IUTEST_INIT(&argc, argv);
		int ret = IUTEST_RUN_ALL_TESTS();	// run all
		
		assert( ret != 0 );
		assert( ::iutest::UnitTest::GetInstance()->failed_test_count() == 1 );
	}
#endif
	return 0;
}
