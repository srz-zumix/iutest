//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_no_test_tests.cpp
 * @brief		テストが無いときの結果 対応テスト
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);

	IUTEST_EXPECT_EQ(0, 1);

	{
		const int ret = IUTEST_RUN_ALL_TESTS();
		if( ret == 0 ) return 1;
	}
	{
		const int ret = IUTEST_RUN_ALL_TESTS();
		if( ret == 0 ) return 1;
	}
#if !defined(IUTEST_USE_GTEST)
	{
		IUTEST_INIT(&argc, argv);
		const int ret = IUTEST_RUN_ALL_TESTS();
		if( ret != 0 ) return 1;
	}
#endif
	printf("*** Successful ***\n");
	return 0;
}

