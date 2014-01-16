//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_type_param_tests1.cpp
 * @brief		iutest type parameter test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest_type_param_tests.hpp"

#if IUTEST_HAS_TYPED_TEST_P

namespace type_param_test
{

typedef ::iutest::Types<int, short, char> MyTypes1;

IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(My1, TypeParamTest, MyTypes1);

#if !defined(IUTEST_USE_GTEST)

IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(My12, TypeParamTest, ::iutest::Types<int, short, char>);

#endif

}

#endif

