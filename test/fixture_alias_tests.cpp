//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        fixture_alias_tests.cpp
 * @brief       fixture test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

namespace fixture_alias_tests
{

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE

class FixtureTest : public ::iutest::Test
{
public:
    int GetX() { return 42; }
};

IUTEST_F((AliasName, FixtureTest), Test1)
{
    IUTEST_EXPECT_STREQ("AliasName", ::iuutil::GetCurrentTestSuite()->name());
    IUTEST_EXPECT_STREQ("Test1", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
    IUTEST_EXPECT_EQ(42, GetX());
}

IUTEST_F((AliasName, FixtureTest), Test2)
{
    IUTEST_EXPECT_STREQ("AliasName", ::iuutil::GetCurrentTestSuite()->name());
    IUTEST_EXPECT_STREQ("Test2", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

#if IUTEST_HAS_PARAM_TEST

#define ParamTestAliasName  (AliasName, ParamFixtureTest)

class ParamFixtureTest : public ::iutest::TestWithParam<int>
{
public:
    int GetX() { return 42; }
};

IUTEST_P(ParamTestAliasName, Test1)
{
    IUTEST_EXPECT_STREQ("AliasName", ::iuutil::TestSuiteNameRemoveInstantiateAndIndexName(
        ::iuutil::GetCurrentTestSuite()->name()) );
    IUTEST_EXPECT_EQ(GetParam(), GetX());
}

IUTEST_P(ParamTestAliasName, Test2)
{
    IUTEST_EXPECT_STREQ("AliasName", ::iuutil::TestSuiteNameRemoveInstantiateAndIndexName(
        ::iuutil::GetCurrentTestSuite()->name()) );
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, ParamTestAliasName, ::iutest::Values(42));

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedFixtureTest : public ::iutest::Test
{
public:
    static T value;
};

#define TypedTestAliasName  (AliasName, TypedFixtureTest)

template<typename T>
T TypedFixtureTest<T>::value = 0;

typedef ::iutest::Types<int, long, short> TypedTestTypes;
IUTEST_TYPED_TEST_SUITE(TypedTestAliasName, TypedTestTypes);

IUTEST_TYPED_TEST(TypedTestAliasName, Test1)
{
    IUTEST_EXPECT_STREQ("AliasName", ::iuutil::TestSuiteNameRemoveIndexName(
        ::iuutil::GetCurrentTestSuite()->name()) );
    TypeParam x = 1;
    IUTEST_ASSERT_EQ(x+x, 2*x);
}

IUTEST_TYPED_TEST(TypedTestAliasName, Test2)
{
    IUTEST_EXPECT_STREQ("AliasName", ::iuutil::TestSuiteNameRemoveIndexName(
        ::iuutil::GetCurrentTestSuite()->name()) );
}

#endif

#endif

}   // end of namespace fixture_alias_tests
