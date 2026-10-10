//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        test_info_location_tests.cpp
 * @brief       test definition location tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

namespace
{

void CheckLocation(int line)
{
#if !defined(IUTEST_USE_GTEST)
    const ::iutest::TestInfo* info = ::iutest::UnitTest::GetInstance()->current_test_info();
    IUTEST_ASSERT_TRUE(info != NULL);
    IUTEST_EXPECT_STREQ(__FILE__, info->file());
    IUTEST_EXPECT_EQ(line, info->line());
#else
    (void)line;
#endif
}

enum { kSimpleLine = __LINE__ + 1 };
IUTEST(Location, Simple)
{
    CheckLocation(kSimpleLine);
}

class LocationFixture : public ::iutest::Test {};

enum { kFixtureLine = __LINE__ + 1 };
IUTEST_F(LocationFixture, Fixture)
{
    CheckLocation(kFixtureLine);
}

class LocationParam : public ::iutest::TestWithParam<int> {};

enum { kParamLine = __LINE__ + 1 };
IUTEST_P(LocationParam, Parameterized)
{
    CheckLocation(kParamLine);
}
IUTEST_INSTANTIATE_TEST_SUITE_P(Instance, LocationParam, ::iutest::Values(1, 2));

#if IUTEST_HAS_TYPED_TEST
template<typename T>
class LocationTyped : public ::iutest::Test {};

typedef ::iutest::Types<int, long> LocationTypes;
IUTEST_TYPED_TEST_SUITE(LocationTyped, LocationTypes);

enum { kTypedLine = __LINE__ + 1 };
IUTEST_TYPED_TEST(LocationTyped, Typed)
{
    CheckLocation(kTypedLine);
}
#endif

#if IUTEST_HAS_TYPED_TEST_P
template<typename T>
class LocationTypedParam : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(LocationTypedParam);
enum { kTypedParamLine = __LINE__ + 1 };
IUTEST_TYPED_TEST_P(LocationTypedParam, TypedParameterized)
{
    CheckLocation(kTypedParamLine);
}
IUTEST_REGISTER_TYPED_TEST_SUITE_P(LocationTypedParam, TypedParameterized);
typedef ::iutest::Types<int, long> LocationTypedParamTypes;
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(Instance, LocationTypedParam, LocationTypedParamTypes);
#endif

}   // namespace

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
