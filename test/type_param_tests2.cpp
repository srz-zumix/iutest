//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        type_param_tests2.cpp
 * @brief       type parameter test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "type_param_tests.hpp"

#if IUTEST_HAS_TYPED_TEST_P

namespace type_param_test
{

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(My2, TypeParamTest, float);

}

#endif

