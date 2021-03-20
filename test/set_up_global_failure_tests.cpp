//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        set_up_global_failure_tests.cpp
 * @brief       Environment::SetUp で失敗したときのテスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

static bool setup_failure=true;

class SetUpFailureEnvironment IUTEST_CXX_FINAL : public ::iutest::Environment
{
private:
    virtual void SetUp(void) IUTEST_CXX_OVERRIDE
    {
        if( setup_failure )
        {
            IUTEST_FAIL();
        }
    }
};

class TearDownFailureEnvironment IUTEST_CXX_FINAL : public ::iutest::Environment
{
private:
    virtual void TearDown(void) IUTEST_CXX_OVERRIDE
    {
        IUTEST_FAIL();
    }
};

IUTEST(Hoge, Test)
{
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

    {
        SetUpFailureEnvironment* const env = new SetUpFailureEnvironment();
        ::iutest::AddGlobalTestEnvironment(env);

        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret == 0 ) return 1;

#if defined(IUTEST_USE_GTEST)
        setup_failure = false;
#else
        delete env;
#endif
    }

    {
        TearDownFailureEnvironment* const env = new TearDownFailureEnvironment();
        ::iutest::AddGlobalTestEnvironment(env);

        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret == 0 ) return 1;
    }

    printf("*** Successful ***\n");
    return 0;
}
