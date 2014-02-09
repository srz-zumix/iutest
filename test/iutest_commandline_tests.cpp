//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_commandline_tests.cpp
 * @brief		CommandLine 対応テスト
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
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
#  define DECAL_ARGV(cmd) const wchar_t* targv[] = { argv[0], L cmd }
#else
#  define DECAL_ARGV(cmd) const char*    targv[] = { argv[0],   cmd }
#endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	(void)argc;
	int targc = 2;
	{
		DECAL_ARGV("--help");
		IUTEST_INIT(&targc, targv);
		if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
	}
	{
		DECAL_ARGV("--version");
		IUTEST_INIT(&targc, targv);
		if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
	}
#if !defined(USE_GTEST)
	{
		DECAL_ARGV("--feature");
		IUTEST_INIT(&targc, targv);
		if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
	}
	{
		::std::vector< ::std::string > argv;
		argv.push_back("--feature");
		::iutest::InitIrisUnitTest(argv);
		if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
	}
#endif
	return 0;
}

