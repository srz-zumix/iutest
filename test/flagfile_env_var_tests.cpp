//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        flagfile_env_var_tests.cpp
 * @brief       FLAGFILE environment test
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

#if IUTEST_HAS_FOPEN
#  define FLAGFILE_TEST 1
#else
#  define FLAGFILE_TEST 0
#endif

#if defined(USE_GTEST_PREFIX) || defined(IUTEST_USE_GTEST)
#  define ENV_PREFIX    "GTEST_"
#else
#  define ENV_PREFIX    "IUTEST_"
#endif

int SetUpEnvironment(void)
{
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "FILTER=Flag*") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "COLOR=on") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "FLAGFILE=testdata/flagfile.txt") == -1 ) return -1;
    return 0;
}

static volatile int g_dummy = SetUpEnvironment();

IUTEST(FlagFileTest, FlagCheck)
{
    if( g_dummy != 0 ) return;  // putenv に失敗した場合はテストしない
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ( "no", ::iutest::IUTEST_FLAG(color).c_str() );
#endif
    IUTEST_EXPECT_STREQ("*Run*:*OK*", ::iutest::IUTEST_FLAG(filter).c_str() );
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    (void)argc;
    (void)argv;

#if FLAGFILE_TEST

#ifdef UNICODE
    wchar_t** targv = NULL;
#else
    char** targv = NULL;
#endif
    int targc = 0;
    IUTEST_INIT(&targc, targv);
    return IUTEST_RUN_ALL_TESTS();

#else
    printf("*** FLAGFILE_TEST=0 ***\n");
    return 0;
#endif
}

