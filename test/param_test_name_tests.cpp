//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		param_test_name_tests.cpp
 * @brief		parameter test name
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

#include "main.cpp"

#if IUTEST_HAS_PARAM_TEST && !defined(IUTEST_USE_GTEST)

class RenameParamTest : public ::iutest::TestWithParam<bool>
{
public:
	template<typename T>
	static const ::std::string MakeTestParamName(const iutest::TestParamInfo<T>& info)
	{
		return ::iutest::StreamableToString(info.param);
	}
};

IUTEST_P(RenameParamTest, Test)
{
	if( GetParam() )
	{
		IUTEST_ASSERT_STREQ("Test/true", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
	}
	else
	{
		IUTEST_ASSERT_STREQ("Test/false", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
	}
}

IUTEST_INSTANTIATE_TEST_CASE_P(My1, RenameParamTest, ::iutest::Bool());


#endif

