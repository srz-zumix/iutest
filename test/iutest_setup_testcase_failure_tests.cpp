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
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"
#include <assert.h>

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

	assert( ::iutest::UnitTest::GetInstance()->failed_test_count() == 0 );
	assert( test_flag == 1 );

	printf("*** Successful ***\n");
	return 0;
}
