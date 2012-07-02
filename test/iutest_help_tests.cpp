//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_help_tests.cpp
 * @brief		help ‘Î‰žƒeƒXƒg
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

IUTEST(Foo, NotRun)
{
	IUTEST_ASSERT_EQ(0, 1);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	(void)argc;
	int targc = 2;
	const char* targv[] = {
		argv[0]
		, "--help"
	};
	IUTEST_INIT(&targc, targv);
	return IUTEST_RUN_ALL_TESTS();	// run all
}

