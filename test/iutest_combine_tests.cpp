//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_no_test_tests.cpp
 * @brief		テストが無いときの結果 対応テスト
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_COMBINE

static const int tble[] = {0, 1};
class CombineTest : public iutest::TestWithParam< iutest::tuple::tuple<bool, int, int> >
{
public:
	static const int TABLE_SIZE = sizeof(tble)/sizeof(tble[0]);
};

IUTEST_P(CombineTest, Num)
{
	EXPECT_EQ( 2*2*TABLE_SIZE, iutest::UnitTest::GetInstance()->current_test_case()->total_test_count() );
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, CombineTest
	, iutest::Combine(iutest::Bool(), iutest::Values(1, 10), iutest::ValuesIn(tble)));

#endif

