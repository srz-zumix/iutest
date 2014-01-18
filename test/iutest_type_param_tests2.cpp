//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_type_param_tests2.cpp
 * @brief		iutest type parameter test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
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

IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(My2, TypeParamTest, float);

}

#endif

