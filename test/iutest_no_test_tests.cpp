//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_no_test_tests.cpp
 * @brief		テストが無いときの結果 対応テスト
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

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);

	IUTEST_EXPECT_EQ(0, 1);

	int ret = IUTEST_RUN_ALL_TESTS();	// run all
	if( ret != 0 ) printf("*** Successful ***\n");
	return ret != 0 ? 0 : 1;
}

