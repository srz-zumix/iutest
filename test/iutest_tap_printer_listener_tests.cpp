//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_tap_printer_listener_tests.cpp
 * @brief		TAPPrintListener test
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
#include "../include/listener/iutest_tap_printer.hpp"
#include "iutest_logger_tests.hpp"

const char tap_test_str[] = 
"# Test started.\n"
"ok 1 - Ok\n"
"# Test ended.\n"
"1..1\n"
;

IUTEST(Test, Ok)
{
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST)
	::iutest::TAPPrintListener::SetUp();
	
	TestLogger logger;
	::iutest::detail::iuConsole::SetLogger(&logger);
#endif

	if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;	
	
#if !defined(IUTEST_USE_GTEST)
	IUTEST_EXPECT_STREQ(tap_test_str, logger.c_str());
#endif
	
	if( ::iutest::UnitTest::GetInstance()->Failed() ) return 1;
	printf("*** Successful ***\n");
	return 0;
}
