//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        env_var_tests.cpp
 * @brief       environment variable tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if defined(USE_GTEST_PREFIX) || defined(IUTEST_USE_GTEST)
#  define ENV_PREFIX    "GTEST_"
#else
#  define ENV_PREFIX    "IUTEST_"
#endif

int SetUpEnvironmentImpl(void)
{
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "SHUFFLE=1") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "RANDOM_SEED=200") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "ALSO_RUN_DISABLED_TESTS=1") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "BREAK_ON_FAILURE=1") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "THROW_ON_FAILURE=1") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "CATCH_EXCEPTIONS=0") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "PRINT_TIME=0") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "REPEAT=2") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "FILTER=Flag*") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv(ENV_PREFIX "OUTPUT=test") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv("XML_OUTPUT_FILE=hoge") == -1 ) return -1; // OUTPUT environment takes precedence

    if( ::iutest::internal::posix::PutEnv("IUTEST_DEFAULT_PACKAGE_NAME=env_var") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv("IUTEST_FILE_LOCATION=vs") == -1 ) return -1;
    if( ::iutest::internal::posix::PutEnv("IUTEST_WARNING_INTO_ERROR=1") == -1 ) return -1;

    return 0;
}

static int lasterror = 0;

int SetUpEnvironment(void)
{
    if( SetUpEnvironmentImpl() == 0 ) return 0;
    lasterror = errno;
    return -1;
}

class SetUpResult
{
public:
    explicit SetUpResult(int n) : setup_environment(n) {}
    int setup_environment;
};
static volatile SetUpResult g_result IUTEST_ATTRIBUTE_INIT_PRIORITY_(101) = SetUpResult(SetUpEnvironment());

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

IUTEST(FlagTest, Check)
{
    IUTEST_ASSUME_EQ(0, g_result.setup_environment) << "\n" << lasterror << ": " << strerror(lasterror);  // putenv に失敗した場合はテストしない
    IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(also_run_disabled_tests) );
    IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(break_on_failure) );
    IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(throw_on_failure) );
    IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(shuffle) );
    IUTEST_EXPECT_FALSE( ::iutest::IUTEST_FLAG(catch_exceptions) );
    IUTEST_EXPECT_FALSE( ::iutest::IUTEST_FLAG(print_time) );
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STREQ( "env_var", ::iutest::IUTEST_FLAG(default_package_name).c_str() );
    IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(file_location_style_msvc) );
    IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(warning_into_error) );
#endif

    IUTEST_EXPECT_EQ( 200u, ::iutest::IUTEST_FLAG(random_seed) );
    IUTEST_EXPECT_EQ(   2 , ::iutest::IUTEST_FLAG(repeat) );

    IUTEST_EXPECT_STREQ( "Flag*", ::iutest::IUTEST_FLAG(filter).c_str() );
    IUTEST_EXPECT_STREQ( "test", ::iutest::IUTEST_FLAG(output).c_str() );
}

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    (void)argc;
    (void)argv;

#ifdef UNICODE
    wchar_t a[] = "";
    wchar_t* targv[] = { a };
#else
    char a[] = "";
    char* targv[] =  { a };
#endif
    int targc = 1;
    IUTEST_INIT(&targc, targv);
#if !defined(IUTEST_USE_GTEST)
    if( g_result.setup_environment == 0 && ::iutest::IUTEST_FLAG(warning_into_error) )
    {
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 1;
    }
    else
#endif
    {
        if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    }
    return 0;
}

