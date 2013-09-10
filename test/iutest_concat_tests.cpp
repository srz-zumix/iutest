//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_concat_tests.cpp
 * @brief		Concat ‘Î‰žƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_CONCAT

static const int tble[] = {0, 1};

class ConcatTest : public ::iutest::TestWithParam<int>
{
public:
};

IUTEST_P(ConcatTest, Dummy)
{
}

IUTEST_INSTANTIATE_TEST_CASE_P(A1, ConcatTest
	, ::iutest::Concat(::iutest::Bool(), ::iutest::Values(1, 10)));
IUTEST_INSTANTIATE_TEST_CASE_P(A2, ConcatTest
	, ::iutest::Concat(::iutest::Bool(), ::iutest::ValuesIn(tble)));
IUTEST_INSTANTIATE_TEST_CASE_P(A3, ConcatTest
	, ::iutest::Concat(::iutest::ValuesIn(tble), ::iutest::Range(1, 10)));
IUTEST_INSTANTIATE_TEST_CASE_P(A4, ConcatTest
	, ::iutest::Concat(::iutest::Values(1, 10)
		, ::iutest::Concat(::iutest::ValuesIn(tble), ::iutest::Range(1, 10))) );

#endif

