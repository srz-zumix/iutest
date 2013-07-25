//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_throw_on_IUTEST_ASSERT_fialure_tests.cpp
 * @brief		IUTEST_USE_THROW_ON_ASSERT_FAILURE ‘Î‰žƒeƒXƒg
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

static int x = 0;

void Sub(void)
{
	IUTEST_ASSERT_EQ(2, 1);
}

IUTEST(Foo, Test1)
{
	Sub();
	++x;
}

IUTEST(Foo, Test2)
{
	IUTEST_EXPECT_EQ(0, x);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	int ret = IUTEST_RUN_ALL_TESTS();
	
#if IUTEST_USE_THROW_ON_ASSERT_FAILURE
	IUTEST_ASSERT( x == 0 );
#else
	IUTEST_ASSERT( x == 1 );
#endif
	if( ret != 0 ) 	printf("*** Successful ***\n");
	return ret ? 0 : 1;
}
