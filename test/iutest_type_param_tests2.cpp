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
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
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

