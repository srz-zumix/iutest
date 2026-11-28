//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        bazel_environment_tests.cpp
 * @brief       Bazel environment variable tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

#if defined(IUTEST_USE_GTEST)
int main() { return 0; }
#else

namespace
{

class SetUpBazelEnvironment
{
public:
    SetUpBazelEnvironment()
        : result(::iutest::internal::posix::SetEnv("TESTBRIDGE_TEST_ONLY", "BazelEnvironment.*", 1))
    {
        result |= ::iutest::internal::posix::SetEnv("TESTBRIDGE_TEST_RUNNER_FAIL_FAST", "1", 1);
    }
    int result;
};

static SetUpBazelEnvironment setup IUTEST_ATTRIBUTE_INIT_PRIORITY_(101);
int first_ran = 0;
int second_ran = 0;
int other_ran = 0;

}   // namespace

IUTEST(BazelEnvironment, First)
{
    ++first_ran;
    IUTEST_ADD_FAILURE();
}

IUTEST(BazelEnvironment, Second)
{
    ++second_ran;
}

IUTEST(OtherEnvironment, Test)
{
    ++other_ran;
}

int main(int argc, char* argv[])
{
    if( setup.result != 0 ) return 0;
    IUTEST_INIT(&argc, argv);
#if defined(DISABLE_FALSE_POSITIVE_XML)
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_FLAG_GET(filter) == "BazelEnvironment.*");
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_FLAG_GET(fail_fast));
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() != 0);
    IUTEST_TERMINATE_ON_FAILURE(first_ran == 1 && second_ran == 0 && other_ran == 0);

    IUTEST_FLAG_SET(fail_fast, false);
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() != 0);
    IUTEST_TERMINATE_ON_FAILURE(first_ran == 2 && second_ran == 1 && other_ran == 0);
    IUTEST_FLAG_SET(fail_fast, true);

    char name[] = "bazel_environment_tests";
    char filter[] = "--gtest_filter=*";
    char fail_fast[] = "--gtest_fail_fast=0";
    char* args[] = { name, filter, fail_fast, NULL };
    int count = 3;
    IUTEST_INIT(&count, args);
    IUTEST_TERMINATE_ON_FAILURE(count == 1);
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_FLAG_GET(filter) == "*");
    IUTEST_TERMINATE_ON_FAILURE(!IUTEST_FLAG_GET(fail_fast));
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() != 0);
    IUTEST_TERMINATE_ON_FAILURE(first_ran == 3 && second_ran == 2 && other_ran == 1);
    printf("*** Successful ***\n");
    return 0;
}

#endif
