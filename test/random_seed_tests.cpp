﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        random_seed_tests.cpp
 * @brief       randmom seed test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

static unsigned int kSeed = 9876;
static unsigned int seed = 0;
static const int kRepeatCount = 3;
static int random_speed_test_count = 0;

class MyEnvironment IUTEST_CXX_FINAL : public ::iutest::Environment
{
private:
    virtual void SetUp(void) IUTEST_CXX_OVERRIDE {}
    virtual void TearDown(void) IUTEST_CXX_OVERRIDE { seed = ::iutest::UnitTest::GetInstance()->random_seed(); ++random_speed_test_count; }
};

IUTEST(Foo, Bar)
{
    if( seed == 0 )
    {
        IUTEST_ASSERT_EQ(kSeed, ::iutest::UnitTest::GetInstance()->random_seed());
    }
    else
    {
        IUTEST_ASSERT_NE(seed, ::iutest::UnitTest::GetInstance()->random_seed());
    }
}

static ::std::vector<int> order[kRepeatCount];

#define NUMBEROF_PARAMTESTS 30

#if IUTEST_HAS_PARAM_TEST

class OrderTest : public ::iutest::TestWithParam<int> {};

IUTEST_INSTANTIATE_TEST_SUITE_P(Foo, OrderTest, ::iutest::Range<int>(0, NUMBEROF_PARAMTESTS));

IUTEST_P(OrderTest, Bar)
{
    order[random_speed_test_count].push_back(GetParam());
}

#else

#define DECL_ORDER_TEST(n, _x) IUTEST(OrderTest, IUTEST_PP_CAT(Bar, n)) { order[random_speed_test_count].push_back(n); }

IUTEST_PP_REPEAT(NUMBEROF_PARAMTESTS, DECL_ORDER_TEST, 0)

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    MyEnvironment* const env = new MyEnvironment();
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::AddGlobalTestEnvironment(env) == env );
#if defined(IUTEST_USE_GTEST) && (GTEST_VER >= 0x01120000)
    ::iutest::IUTEST_FLAG(recreate_environments_when_repeating) = true;
#endif
    ::iutest::IUTEST_FLAG(repeat) = kRepeatCount;
    ::iutest::IUTEST_FLAG(shuffle) = true;
    ::iutest::IUTEST_FLAG(random_seed) = kSeed;

    IUTEST_INIT(&argc, argv);

    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret != 0 ) return ret;

    // シャッフルした順番を繰り返しシャッフルするため同じ順番にならない
    IUTEST_EXPECT_NE(order[0], order[1]);
    IUTEST_EXPECT_NE(order[0], order[2]);

    return ::iutest::UnitTest::GetInstance()->Passed() ? 0 : 1;
}

