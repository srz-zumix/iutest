//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		fixture_alias_tests.cpp
 * @brief		fixture test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_TESTNAME_ALIAS

class FixtureTest : public ::iutest::Test
{
public:
	int GetX() { return 42; }
};

IUTEST_F((AliasName, FixtureTest), Test)
{
	IUTEST_EXPECT_STREQ("AliasName", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
	IUTEST_EXPECT_STREQ("Test", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
	IUTEST_EXPECT_EQ(42, GetX());
}

#if IUTEST_HAS_PARAM_TEST

class ParamFixtureTest : public ::iutest::TestWithParam<int>
{
public:
	int GetX() { return 42; }
};

IUTEST_P((AliasName, ParamFixtureTest), Test)
{
	IUTEST_EXPECT_STREQ("My1/AliasName", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
	IUTEST_EXPECT_EQ(GetParam(), GetX());
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, (AliasName, ParamFixtureTest), ::iutest::Values(42));

#endif

#endif

