//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        static_assertion_tests.cpp
 * @brief       StaticAssertTypeEq アサーション test
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
#include "iutest.hpp"

#if IUTEST_HAS_STATIC_ASSERT_TYPEEQ

const bool static_assert_typeeq_result_b = ::iutest::StaticAssertTypeEq<int, int>();

IUTEST(StaticAssertTypeEqTest, OK)
{
    ::iutest::StaticAssertTypeEq<float, float>();
    IUTEST_STATIC_ASSERT(true);
}

#endif
