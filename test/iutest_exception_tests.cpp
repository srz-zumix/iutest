//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_exception_tests.cpp
 * @brief		iutest test 例外テスト
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_EXCEPTIONS
#include <stdexcept>

IUTEST(ExceptionTest, StdExceptionThrow)
{
	throw std::runtime_error("ExceptionTest");
}

IUTEST(ExceptionTest, Throw)
{
	throw "ExceptionTest";
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
#if IUTEST_HAS_EXCEPTIONS
#if defined(OUTPUTXML)
	// 失敗テストを含むので xml 出力しない
	::iutest::IUTEST_FLAG(output) = NULL;
#endif
	if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
	IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 2 );
#else
	if( IUTEST_RUN_ALL_TESTS() ) return 1;
#endif
	printf("*** Successful ***\n");
	return 0;
}

