//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        output_env_var_tests.cpp
 * @brief       environment variable (output setting) test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2017-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include <errno.h>

int SetUpEnvironmentImpl(void)
{
    if( ::iutest::internal::posix::PutEnv("XML_OUTPUT_FILE=test:invalid_file_path") == -1 ) return -1;
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

IUTEST(OutputEnvVarTest, FlagCheck)
{
    IUTEST_ASSUME_EQ(0, g_result.setup_environment) << lasterror << ": " << strerror(lasterror);  // putenv に失敗した場合はテストしない
#if !defined(IUTEST_NO_ENV_XML_OUTPUT_FILE)
    IUTEST_EXPECT_STREQ( "xml:test:invalid_file_path", ::iutest::IUTEST_FLAG(output).c_str() );
#else
    IUTEST_EXPECT_STREQ( "", ::iutest::IUTEST_FLAG(output).c_str() );
#endif
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
    return IUTEST_RUN_ALL_TESTS();
}

