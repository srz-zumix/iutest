//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        streaming_listener_tests.cpp
 * @brief       StreamResultListener test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2017, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_STREAM_RESULT

#if defined(USE_GTEST_PREFIX) || defined(IUTEST_USE_GTEST)
#  define ENV_PREFIX    "GTEST_"
#else
#  define ENV_PREFIX    "IUTEST_"
#endif

int SetUpEnvironment(void)
{
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "STREAM_RESULT_TO=test") == -1 ) return -1;
    return 0;
}

class SetUpResult
{
public:
    explicit SetUpResult(int n) : setup_environment(n) {}
    int setup_environment;
};
static volatile SetUpResult g_result IUTEST_ATTRIBUTE_INIT_PRIORITY_(101) = SetUpResult(SetUpEnvironment());

#endif

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
    ::iutest::IUTEST_FLAG(warning_into_error) = false;
#endif
#if IUTEST_HAS_STREAM_RESULT
    if( g_result.setup_environment == 0 )
    {
        IUTEST_EXPECT_STREQ( "test", ::iutest::IUTEST_FLAG(stream_result_to).c_str() );
    }
    ::iutest::IUTEST_FLAG(stream_result_to) = "localhost:5103";
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    printf("*** Successful ***\n");
    return 0;
#else
    return IUTEST_RUN_ALL_TESTS();
#endif
}
