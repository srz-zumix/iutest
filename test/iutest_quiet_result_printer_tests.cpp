//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_quiet_result_printer_tests.cpp
 * @brief		QuietResultPrinter test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "iutest_logger_tests.hpp"

IUTEST(Test, Ok)
{
}

IUTEST(Test, NG)
{
	IUTEST_ASSERT_TRUE(false);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
	// 実行対象テストがないので xml 出力しない
	::iutest::IUTEST_FLAG(output) = NULL;
#endif
	
#if !defined(IUTEST_USE_GTEST)
	TestLogger logger;
	::iutest::detail::iuConsole::SetLogger(&logger);
#endif
	
#if IUTEST_HAS_ASSERTION_RETURN
	IUTEST_ASSERT_NOTNULL( ::iuutil::QuietResultPrinter::SetUp() ) << ::iutest::AssertionReturn<int>(1);
#else
	if( ::iuutil::QuietResultPrinter::SetUp() == NULL ) return 1;
#endif

	if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_ASSERTION_RETURN
	IUTEST_ASSERT_STRNOTIN("[       OK ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
	IUTEST_ASSERT_STRIN   ("[  FAILED  ]", logger.c_str()) << ::iutest::AssertionReturn<int>(1);
#endif
	printf("*** Successful ***\n");
	return 0;
}
