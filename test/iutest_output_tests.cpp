//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_output_tests.cpp
 * @brief		出力テスト
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "internal/iutest_log_stream.hpp"
#include "iutest_logger_tests.hpp"

TestLogger logger;

IUTEST(LoggerTest, Output)
{
	logger.clear();
	logger.output("%d", 1);
	
	IUTEST_EXPECT_STREQ("1", logger.c_str());
}

IUTEST(LogStreamTest, Write)
{
	logger.clear();
	::iutest::detail::LogStream stream;
	const char text[] = "test text";
	stream.Write(text, sizeof(text), 1);
	
	IUTEST_EXPECT_STREQ(text, logger.c_str());
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	::iutest::detail::iuConsole::SetLogger(&logger);
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

