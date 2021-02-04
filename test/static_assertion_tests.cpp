//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        static_assertion_tests.cpp
 * @brief       StaticAssertTypeEq アサーション test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_STATIC_ASSERT_TYPEEQ

const bool IUTEST_ATTRIBUTE_UNUSED_ static_assert_typeeq_result_b = ::iutest::StaticAssertTypeEq<int, int>();

IUTEST(StaticAssertTypeEqTest, OK)
{
    ::iutest::StaticAssertTypeEq<float, float>();
    IUTEST_STATIC_ASSERT(true);
}

#endif
