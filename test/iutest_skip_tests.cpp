//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_skip_tests.cpp
 * @brief		IUTEST_SKIP ‘Î‰žƒeƒXƒg
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
	int ret = IUTEST_RUN_ALL_TESTS();
	if( ret == 0 ) return 1;
	assert( ::iutest::UnitTest::GetInstance()->test_to_run_count() == 2 );
#if !defined(IUTEST_USE_GTEST)
	assert( ::iutest::UnitTest::GetInstance()->test_was_skipped_count() == 1 );
	assert( ::iutest::UnitTest::GetInstance()->reportable_test_was_skipped_count() == 1 );
	assert( ::iutest::UnitTest::GetInstance()->skip_test_count() == 2 );
	assert( ::iutest::UnitTest::GetInstance()->reportable_skip_test_count() == 2 );
#endif
	assert( ::iutest::UnitTest::GetInstance()->failed_test_count() == 1 );
	assert( skip_check );
	printf("*** Successful ***\n");
	return 0;
}
