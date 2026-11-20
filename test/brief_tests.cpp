//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        brief_tests.cpp
 * @brief       brief result printer test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"
#include "logger_tests.hpp"

#if !defined(IUTEST_USE_GTEST)

IUTEST(BriefTest, Pass)
{
}

IUTEST(BriefTest, Fail)
{
    IUTEST_EXPECT_TRUE(false) << "brief failure marker";
}

IUTEST(BriefTest, Skip)
{
    IUTEST_SKIP() << "brief skip marker";
}

IUTEST(BriefTest, DISABLED_NotRun)
{
}

int main(int /*argc*/, char* /*argv*/[])
{
    TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);

    const char* normal_argv[] = { "brief_tests", "--iutest_color=no", "--gtest_brief=0" };
    int normal_argc = 3;
    IUTEST_INIT(&normal_argc, normal_argv);
    if( IUTEST_FLAG_GET(brief) || IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
    if( strstr(logger.c_str(), "[ RUN      ] BriefTest.Pass") == NULL
        || strstr(logger.c_str(), "[       OK ] BriefTest.Pass") == NULL
        || strstr(logger.c_str(), "brief failure marker") == NULL ) return 1;

    const char* brief_argv[] = { "brief_tests", "--iutest_brief=1" };
    int brief_argc = 2;
    IUTEST_INIT(&brief_argc, brief_argv);
    logger.clear();
    if( !IUTEST_FLAG_GET(brief) || IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
    const char* output = logger.c_str();
    if( strstr(output, "brief failure marker") == NULL
        || strstr(output, "[  FAILED  ] BriefTest.Fail") == NULL
        || strstr(output, "[  PASSED  ] 1 test") == NULL
        || strstr(output, "[  SKIPPED ] 1 test") == NULL
        || strstr(output, "[ DISABLED ] 1 test") == NULL
        || strstr(output, "[==========]") == NULL
        || strstr(output, "[ RUN      ]") != NULL
        || strstr(output, "[       OK ]") != NULL
        || strstr(output, "BriefTest.Pass") != NULL
        || strstr(output, "brief skip marker") != NULL
        || strstr(output, "[----------]") != NULL ) return 1;
    ::iutest::detail::iuConsole::SetLogger(NULL);
    return 0;
}

#endif
