//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        recreate_environments_when_repeating_tests.cpp
 * @brief       繰り返し時のグローバル環境テスト
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
#include <cstdlib>

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01120000

int g_setup_count = 0;
int g_teardown_count = 0;
int g_test_count = 0;

class CountingEnvironment : public ::iutest::Environment
{
public:
    virtual void SetUp() IUTEST_CXX_OVERRIDE { ++g_setup_count; }
    virtual void TearDown() IUTEST_CXX_OVERRIDE { ++g_teardown_count; }
};

IUTEST(RecreateEnvironments, Runs)
{
    ++g_test_count;
    IUTEST_EXPECT_EQ(g_setup_count, g_teardown_count + 1);
}

class StopAfterThreeIterations : public ::iutest::EmptyTestEventListener
{
public:
    virtual void OnTestIterationEnd(const ::iutest::UnitTest&, int iteration) IUTEST_CXX_OVERRIDE
    {
        if( iteration == 2 )
        {
            ::std::exit(g_setup_count == 3 && g_teardown_count == 3 && g_test_count == 3 ? 0 : 1);
        }
    }
};

void RunThreeTimes(bool recreate, int expected_environment_count)
{
    g_setup_count = g_teardown_count = g_test_count = 0;
    ::iutest::IUTEST_FLAG(recreate_environments_when_repeating) = recreate;
    ::iutest::IUTEST_FLAG(repeat) = 3;
#if defined(IUTEST_USE_GTEST) && GTEST_VER >= 0x01150000
    ::iutest::AddGlobalTestEnvironment(new CountingEnvironment);
#endif
    IUTEST_TERMINATE_ON_FAILURE(IUTEST_RUN_ALL_TESTS() == 0);
    IUTEST_TERMINATE_ON_FAILURE(g_setup_count == expected_environment_count);
    IUTEST_TERMINATE_ON_FAILURE(g_teardown_count == expected_environment_count);
    IUTEST_TERMINATE_ON_FAILURE(g_test_count == 3);
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01120000
#if !defined(IUTEST_USE_GTEST) || GTEST_VER < 0x01150000
    ::iutest::AddGlobalTestEnvironment(new CountingEnvironment);
#endif
    RunThreeTimes(true, 3);
    RunThreeTimes(false, 1);

    g_setup_count = g_teardown_count = g_test_count = 0;
    ::iutest::IUTEST_FLAG(recreate_environments_when_repeating) = false;
    ::iutest::IUTEST_FLAG(repeat) = -1;
#if defined(IUTEST_USE_GTEST) && GTEST_VER >= 0x01150000
    ::iutest::AddGlobalTestEnvironment(new CountingEnvironment);
#endif
    ::iutest::UnitTest::GetInstance()->listeners().Append(new StopAfterThreeIterations);
    IUTEST_RUN_ALL_TESTS();
    return 1;
#else
    return 0;
#endif
}
