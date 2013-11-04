//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_setup_testcase_failure_tests.cpp
 * @brief		SetUpTestCase ‚ÅŽ¸”s‚µ‚½‚Æ‚«‚ÌƒeƒXƒg
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
#include "../include/iutest.hpp"

static int test_flag = 0;

class TestSetUpFailure : public ::iutest::Test
{
public:
	static void SetUpTestCase()
	{
		IUTEST_FAIL() << "SetUp TestCase Failed.";
	}
};

IUTEST_F(TestSetUpFailure, Test)
{
	++test_flag;
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

	IUTEST_ASSERT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 0 );
#if !defined(IUTEST_USE_GTEST)
	IUTEST_ASSERT( test_flag == 0 );
#else
	IUTEST_ASSERT( test_flag == 1 );
#endif

	printf("*** Successful ***\n");
	return 0;
}
