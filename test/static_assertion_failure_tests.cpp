//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        static_assertion_failure_tests.cpp
 * @brief       StaticAssertTypeEq fail test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_STATIC_ASSERT_TYPEEQ

template<bool a, bool b>struct test_struct : public iutest_type_traits::bool_constant<a> {};

IUTEST_TEST_COMPILEERROR("static_assert_typeeq")
bool b = ::iutest::StaticAssertTypeEq<int, float>();

IUTEST(StaticAssertTypeEqTest, Fail)
{
    IUTEST_TEST_COMPILEERROR("static_assert_typeeq")
    ::iutest::StaticAssertTypeEq<float, int>();
}

IUTEST(StaticAssertTypeEqTest, Fail2)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    IUTEST_STATIC_ASSERT(false);
}

IUTEST(StaticAssertTypeEqTest, Fail3)
{
    IUTEST_TEST_STATICASSERT("(static_assert|static assertion failed)")
    IUTEST_STATIC_ASSERT((test_struct<false, false>::value));
}

#endif
