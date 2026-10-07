//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        set_up_testsuite_skip_on_failure_tests.cpp
 * @brief       Skip tests when SetUpTestSuite fails
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

static int test_runs = 0;
static int teardown_runs = 0;

class NonfatalSetUpFailure : public ::iuutil::backward::Test<NonfatalSetUpFailure>
{
public:
    static void SetUpTestSuite() { IUTEST_ADD_FAILURE() << "nonfatal setup failure"; }
    static void TearDownTestSuite() { ++teardown_runs; }
};

IUTEST_F(NonfatalSetUpFailure, First) { ++test_runs; }
IUTEST_F(NonfatalSetUpFailure, Second) { ++test_runs; }

class FatalSetUpFailure : public ::iuutil::backward::Test<FatalSetUpFailure>
{
public:
    static void SetUpTestSuite() { IUTEST_FAIL() << "fatal setup failure"; }
    static void TearDownTestSuite() { ++teardown_runs; }
};

IUTEST_F(FatalSetUpFailure, First) { ++test_runs; }
IUTEST_F(FatalSetUpFailure, Second) { ++test_runs; }

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(IUTEST_USE_GTEST) && GTEST_VER < 0x01120000 && !GTEST_LATEST
    return 0;
#else
#if defined(DISABLE_FALSE_POSITIVE_XML)
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    const int ret = IUTEST_RUN_ALL_TESTS();
    IUTEST_TERMINATE_ON_FAILURE( ret != 0 );
    IUTEST_TERMINATE_ON_FAILURE( test_runs == 0 );
    IUTEST_TERMINATE_ON_FAILURE( teardown_runs == 2 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->failed_test_count() == 0 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->test_to_run_count() == 4 );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->skip_test_count() == 4 );
    for( int i = 0; i < 2; ++i )
    {
        const ::iutest::TestSuite* suite = ::iuutil::GetTestSuite(i);
        IUTEST_TERMINATE_ON_FAILURE( suite->ad_hoc_test_result()->Failed() );
        IUTEST_TERMINATE_ON_FAILURE( suite->skip_test_count() == 2 );
    }
    printf("*** Successful ***\n");
    return 0;
#endif
}
