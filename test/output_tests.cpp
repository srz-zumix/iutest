//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        output_tests.cpp
 * @brief       出力テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "../include/internal/iutest_log_stream.hpp"
#include "logger_tests.hpp"

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

IUTEST(CharCodeTest, ShowAnyCString)
{
    wchar_t* p1 = NULL;
    IUTEST_EXPECT_STREQ("(null)", ::iutest::detail::ShowAnyCString(p1));
#if IUTEST_HAS_CHAR16_T
    char16_t* p2 = NULL;
    IUTEST_EXPECT_STREQ("(null)", ::iutest::detail::ShowAnyCString(p2));
#endif
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

