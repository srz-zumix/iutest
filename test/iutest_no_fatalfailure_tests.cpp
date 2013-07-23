//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_no_fatalfailure_tests.cpp
 * @brief		iutest_no fatal failure test
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
#if IUTEST_HAS_ASSERTION_RETURN
#include <assert.h>
#endif

bool bTest = false;

void OccurNonFatalFailure(void)
{
	IUTEST_EXPECT_TRUE(false);
}

IUTEST_PRAGMA_GCC_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_EMPTY_BODY()

IUTEST(NoFatalFailureTest, Assert)
{
	IUTEST_ASSERT_NO_FATAL_FAILURE(OccurNonFatalFailure());
	bTest = true;
}

IUTEST(NoFatalFailureTest, Expect)
{
	IUTEST_EXPECT_NO_FATAL_FAILURE(OccurNonFatalFailure());
}

IUTEST(NoFatalFailureTest, Inform)
{
	IUTEST_INFORM_NO_FATAL_FAILURE(OccurNonFatalFailure());
}

IUTEST_PRAGMA_GCC_WARN_POP()

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	int ret = IUTEST_RUN_ALL_TESTS();
	if( ret == 0 ) return 1;
	
#if IUTEST_HAS_ASSERTION_RETURN
	IUTEST_ASSERT_EQ(0, ::iutest::UnitTest::GetInstance()->successful_test_count()) << ::iutest::AssertionReturn(1);
	IUTEST_ASSERT_EQ(3, ::iutest::UnitTest::GetInstance()->failed_test_count()) << ::iutest::AssertionReturn(1);
	IUTEST_ASSERT_TRUE(bTest) << ::iutest::AssertionReturn(1);
#else
	assert( ::iutest::UnitTest::GetInstance()->successful_test_count() == 0 );
	assert( ::iutest::UnitTest::GetInstance()->failed_test_count() == 3 );
	assert( bTest );
#endif
	printf("*** Successful ***\n");
	return 0;
}
