//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        type_param_register_exception_tests.hpp
 * @brief       type parameter exception in register test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IUTEST_TYPE_PARAM_REGISTER_EXCEPTION_TESTS_HPP_
#define INCG_IUTEST_TYPE_PARAM_REGISTER_EXCEPTION_TESTS_HPP_

#if defined(IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME)
#  undef IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME
#endif
#define IUTEST_HAS_TYPED_TEST_APPEND_TYPENAME   1
#define IUTEST_ABORT()  (void)0

#include "iutest.hpp"

#if IUTEST_HAS_TYPED_TEST_P && IUTEST_HAS_EXCEPTIONS && !defined(IUTEST_USE_GTEST) && !defined(IUTEST_USE_LIB)
#  define REGISTER_EXCEPTION_TEST   1
#endif

#if !defined(REGISTER_EXCEPTION_TEST)
#  define REGISTER_EXCEPTION_TEST   0
#endif

#endif
