//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		benchmark_base.cpp
 * @brief		benchmark base file
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "iutest.hpp"

IUTEST_PACKAGE(PACKAGENAME)
{
	template<typename T>
	::std::vector<T> make_param(int n, T param)
	{
		::std::vector<T> v;
		for( int i=0; i < n; ++i )
		{
			v.push_back(param);
		}
		return v;
	}
	
	class ParamTest : public ::iutest::TestWithParam<int> {};
	
	IUTEST_P(ParamTest, Eq)
	{
		IUTEST_ASSERT_EQ(0, GetParam());
		IUTEST_EXPECT_EQ(0, GetParam());
		IUTEST_INFORM_EQ(0, GetParam());
		IUTEST_ASSUME_EQ(0, GetParam());
	}
	IUTEST_P(ParamTest, Ne)
	{
		IUTEST_ASSERT_NE(0, GetParam());
		IUTEST_EXPECT_NE(0, GetParam());
		IUTEST_INFORM_NE(0, GetParam());
		IUTEST_ASSUME_NE(0, GetParam());
	}
	
	IUTEST_INSTANTIATE_TEST_CASE_P(A, ParamTest, ::iutest::Range<int>(0, 100000));
	IUTEST_INSTANTIATE_TEST_CASE_P(B, ParamTest, ::iutest::Values(IUTEST_PP_ENUM_PARAMS(IUTEST_PP_LIMIT_ENUM, IUTEST_PP_EMPTY())));
	IUTEST_INSTANTIATE_TEST_CASE_P(C, ParamTest, ::iutest::ValuesIn(make_param(1000, 0)));

}
