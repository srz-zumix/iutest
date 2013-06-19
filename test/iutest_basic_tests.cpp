//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_basic_tests.cpp
 * @brief		iutest Šî–{ test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

IUTEST(CommandLineFlagTest, CanBeAccessed)
{
	bool dummy = ::iutest::IUTEST_FLAG(also_run_disabled_tests)
	|| ::iutest::IUTEST_FLAG(break_on_failure)
	|| ::iutest::IUTEST_FLAG(catch_exceptions)
	|| ::iutest::IUTEST_FLAG(list_tests)
	|| ::iutest::IUTEST_FLAG(print_time)
	|| ::iutest::IUTEST_FLAG(random_seed)
	|| ::iutest::IUTEST_FLAG(repeat) > 0
	|| ::iutest::IUTEST_FLAG(shuffle)
	|| ::iutest::IUTEST_FLAG(throw_on_failure)
	|| ::iutest::IUTEST_FLAG(color) != "unkown"
	|| ::iutest::IUTEST_FLAG(filter) != "unkown"
	;
	IUTEST_EXPECT_TRUE(dummy || !dummy);
}

IUTEST(TestInformation, CurrentTestCase)
{
	IUTEST_ASSERT_STREQ("TestInformation", ::iutest::UnitTest::GetInstance()->current_test_case()->name());
	IUTEST_ASSERT_TRUE(::iutest::UnitTest::GetInstance()->current_test_case()->should_run());
}

IUTEST(TestInformation, CurrentTestInfo)
{
	IUTEST_ASSERT_STREQ("TestInformation", ::iutest::UnitTest::GetInstance()->current_test_info()->test_case_name());
	IUTEST_ASSERT_STREQ("CurrentTestInfo", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
	IUTEST_ASSERT_TRUE(::iutest::UnitTest::GetInstance()->current_test_info()->should_run());
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x06)
	IUTEST_ASSERT_EQ(NULL, ::iutest::UnitTest::GetInstance()->current_test_info()->type_param());
	IUTEST_ASSERT_EQ(NULL, ::iutest::UnitTest::GetInstance()->current_test_info()->value_param());
#endif
}

IUTEST(TestInformation, DISABLED_Test)
{
}

IUTEST(TestInformation, TestInfoCount)
{
	IUTEST_ASSERT_EQ(4, ::iutest::UnitTest::GetInstance()->current_test_case()->total_test_count());
	IUTEST_ASSERT_EQ(3, ::iutest::UnitTest::GetInstance()->current_test_case()->test_to_run_count());
	IUTEST_ASSERT_EQ(3, ::iutest::UnitTest::GetInstance()->current_test_case()->successful_test_count());
	IUTEST_ASSERT_EQ(0, ::iutest::UnitTest::GetInstance()->current_test_case()->failed_test_count());
	IUTEST_ASSERT_EQ(1, ::iutest::UnitTest::GetInstance()->current_test_case()->disabled_test_count());
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
	IUTEST_ASSERT_EQ(1, ::iutest::UnitTest::GetInstance()->current_test_case()->reportable_disabled_test_count());
	IUTEST_ASSERT_EQ(4, ::iutest::UnitTest::GetInstance()->current_test_case()->reportable_test_count());
#endif
#if !defined(IUTEST_USE_GTEST)
	IUTEST_ASSERT_EQ(0, ::iutest::UnitTest::GetInstance()->current_test_case()->test_was_skipped_count());
	IUTEST_ASSERT_EQ(0, ::iutest::UnitTest::GetInstance()->current_test_case()->reportable_test_was_skipped_count());
	IUTEST_ASSERT_EQ(1, ::iutest::UnitTest::GetInstance()->current_test_case()->skip_test_count());
	IUTEST_ASSERT_EQ(1, ::iutest::UnitTest::GetInstance()->current_test_case()->reportable_skip_test_count());
#endif
}

#if IUTEST_HAS_GENRAND

IUTEST(TestRandom, Genrand)
{
	IUTEST_ASSERT_LE(genrand(100), 100u);
}

#if IUTEST_HAS_CXX_HDR_RANDOM

IUTEST(TestRandom, Engine)
{
	IUTEST_ASSERT_LE( ::std::uniform_int_distribution<unsigned int>(0,100)(random_engine()), 100u);
}
#endif

#endif
