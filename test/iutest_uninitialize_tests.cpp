//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_uninitialize_tests.cpp
 * @brief		filter ‘Î‰žƒeƒXƒg
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
