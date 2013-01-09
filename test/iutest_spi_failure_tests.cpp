//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_spi_failure_tests.cpp
 * @brief		iutest_spi failure test
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
#include "../include/iutest_spi.hpp"
#include <assert.h>

IUTEST(SPIAssertFailureTest, Failure)
{
	IUTEST_ASSERT_FATAL_FAILURE(return;, "");
}

IUTEST(SPIAssertFailureTest, NonFailure)
{
	IUTEST_ASSERT_NONFATAL_FAILURE(return;, "");
}

IUTEST(SPIExpectFailureTest, Failure)
{
	IUTEST_EXPECT_FATAL_FAILURE(return;, "");
}

IUTEST(SPIExpectFailureTest, NonFailure)
{
	IUTEST_EXPECT_NONFATAL_FAILURE(return;, "");
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
	
	assert( ::iutest::UnitTest::GetInstance()->failed_test_count() == 4 );
	printf("*** Successful ***\n");
	return 0;
}
