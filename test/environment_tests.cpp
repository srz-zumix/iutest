//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        environment_tests.cpp
 * @brief       Environment tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

static int test_counter = 0;

class MyEnvironment IUTEST_CXX_FINAL : public ::iutest::Environment
{
public:
    static bool setup;
    static bool teardown;

public:
    void Reset(void)
    {
        setup = false;
        teardown = false;
    }

private:
    virtual void SetUp(void) IUTEST_CXX_OVERRIDE
    {
        setup = true;
        ++test_counter;
        Environment::SetUp();
    }

    virtual void TearDown(void) IUTEST_CXX_OVERRIDE
    {
        teardown = true;
        --test_counter;
        Environment::TearDown();
    }
};

class MyEnvironment2 IUTEST_CXX_FINAL : public ::iutest::Environment
{
private:
    virtual void SetUp(void) IUTEST_CXX_OVERRIDE
    {
        IUTEST_ASSERT_EQ(1, test_counter);
        ++test_counter;
    }

    virtual void TearDown(void) IUTEST_CXX_OVERRIDE
    {
        IUTEST_ASSERT_EQ(2, test_counter);
        --test_counter;
    }
};

bool MyEnvironment::setup = false;
bool MyEnvironment::teardown = false;

IUTEST(EnvironmentTest, FlagCheck)
{
    IUTEST_ASSERT_TRUE(MyEnvironment::setup);
    IUTEST_ASSERT_FALSE(MyEnvironment::teardown);
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    MyEnvironment* const env = new MyEnvironment();
    IUTEST_EXPECT_NULL( ::iutest::AddGlobalTestEnvironment(NULL) );
    IUTEST_EXPECT_EQ( env, ::iutest::AddGlobalTestEnvironment(env) );
    ::iutest::AddGlobalTestEnvironment(new MyEnvironment2());
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_NULL( ::iutest::TestEnv::ReleaseGlobalTestEnvironment(NULL) );
#endif
    env->Reset();
    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret != 0 ) return 1;

    IUTEST_EXPECT_TRUE( MyEnvironment::teardown );

    return ::iutest::UnitTest::GetInstance()->Passed() ? 0 : 1;
}
