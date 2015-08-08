//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		uninitialize_tests.cpp
 * @brief		未初期化テスト
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2012-2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(Test, Dummy)
{
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	(void)argc;
	(void)argv;
	if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
	printf("*** Successful ***\n");
	return 0;
}
