//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        random_seed_tests.cpp
 * @brief       乱数シード対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2021, Takazumi Shirayanagi\n
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

#if IUTEST_HAS_PARAM_TEST
const int kNumberOfParamTests = 10;

class OrderTest : public ::iutest::TestWithParam<int> {};

IUTEST_INSTANTIATE_TEST_SUITE_P(Foo, OrderTest, ::iutest::Range<int>(0, kNumberOfParamTests));

IUTEST_P(OrderTest, Bar)
{
    order[random_speed_test_count].push_back(GetParam());
}

#else

#define DECL_ORDER_TEST(n) IUTEST(OrderTest, IUTEST_PP_CAT(Bar, n)) { order[random_speed_test_count].push_back(n); }

DECL_ORDER_TEST(0)
DECL_ORDER_TEST(1)
DECL_ORDER_TEST(2)
DECL_ORDER_TEST(3)
DECL_ORDER_TEST(4)
DECL_ORDER_TEST(5)
DECL_ORDER_TEST(6)
DECL_ORDER_TEST(7)
DECL_ORDER_TEST(8)
DECL_ORDER_TEST(9)

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    MyEnvironment* const env = new MyEnvironment();
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::AddGlobalTestEnvironment(env) == env );
    IUTEST_INIT(&argc, argv);

    ::iutest::IUTEST_FLAG(repeat) = kRepeatCount;
    ::iutest::IUTEST_FLAG(shuffle) = true;
    ::iutest::IUTEST_FLAG(random_seed) = kSeed;

    const int ret = IUTEST_RUN_ALL_TESTS();
    if( ret != 0 ) return ret;

    // シャッフルした順番を繰り返しシャッフルするため同じ順番にならない
    IUTEST_EXPECT_NE(order[0], order[1]);
    IUTEST_EXPECT_NE(order[0], order[2]);

    return ::iutest::UnitTest::GetInstance()->Passed() ? 0 : 1;
}

