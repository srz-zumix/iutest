//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_throw_on_failure_tests.cpp
 * @brief		throw_on_fialure 対応テスト
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
#include "../include/iutest.hpp"

#if IUTEST_HAS_EXCEPTIONS

IUTEST(Expect, Test)
{
	IUTEST_EXPECT_EQ(2, 1);
}

IUTEST(Expect, Dummy)
{
}

IUTEST(Assert, Test)
{
	IUTEST_ASSERT_EQ(2, 1);
}

IUTEST(Assert, Dummy)
{
}

IUTEST(Throw, Test)
{
	throw 2;
}

IUTEST(Throw, Dummy)
{
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	::iutest::IUTEST_FLAG(throw_on_failure) = true;
#if !defined(IUTEST_USE_GTEST)
	::iutest::IUTEST_FLAG(catch_exceptions_global) = false;
#endif
	
#if IUTEST_HAS_EXCEPTIONS
	try
	{
		::iutest::IUTEST_FLAG(filter) = "*Expect*";
		IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
		// 失敗テストを含むので xml 出力しない
		::iutest::IUTEST_FLAG(output) = NULL;
#endif
		if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;
		
		return 1;
	}
	catch(...)
	{
	}

	try
	{
		::iutest::IUTEST_FLAG(filter) = "*Assert*";
		IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
		// 失敗テストを含むので xml 出力しない
		::iutest::IUTEST_FLAG(output) = NULL;
#endif
		if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;
		
		return 1;
	}
	catch(...)
	{
	}

	try
	{
		::iutest::IUTEST_FLAG(filter) = "*Throw*";
		IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
		// 失敗テストを含むので xml 出力しない
		::iutest::IUTEST_FLAG(output) = NULL;
#endif
		if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;
		
		return 1;
	}
	catch(...)
	{
	}
#endif
	printf("*** Successful ***\n");
	return 0;
}
