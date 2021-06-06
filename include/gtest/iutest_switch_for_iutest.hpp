//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_switch_for_iutest.hpp
 * @brief       switching to gtest from iutest
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_FOR_IUTEST_HPP_478A7B61_F2AE_480D_AF26_1AC5162F7B13
#define INCG_IRIS_IUTEST_SWITCH_FOR_IUTEST_HPP_478A7B61_F2AE_480D_AF26_1AC5162F7B13

#if !defined(IUTEST_USE_GTEST)

#ifdef GTEST_USE_OWN_TR1_TUPLE
#  define IUTEST_USE_EXTERNAL_TR1_TUPLE 1   // gtest の tuple を使用する
#endif

//======================================================================
// include
#include "../iutest.hpp"

//======================================================================
// define

#if defined(GTEST_INCLUDE_GTEST_GTEST_H_)

#undef SUCCEED
#undef FAIL
#undef ADD_FAILURE
#undef ADD_FAILURE_AT

#undef GTEST_HAS_DEATH_TEST
#if defined(GTEST_HAS_PARAM_TEST)
#  undef GTEST_HAS_PARAM_TEST
#endif
#undef GTEST_HAS_COMBINE
#undef GTEST_HAS_TYPED_TEST
#undef GTEST_HAS_TYPED_TEST_P

#undef GTEST_CAN_STREAM_RESULTS_

#undef GTEST_HAS_EXCEPTIONS
#undef GTEST_HAS_RTTI
#undef GTEST_HAS_SEH

#undef GTEST_IS_THREADSAFE

#endif

#define SUCCEED             IUTEST_SUCCEED
#define FAIL                IUTEST_FAIL
#define ADD_FAILURE         IUTEST_ADD_FAILURE
#define ADD_FAILURE_AT      IUTEST_ADD_FAILURE_AT

#define GTEST_HAS_DEATH_TEST    0
#define GTEST_HAS_PARAM_TEST    IUTEST_HAS_PARAM_TEST
#define GTEST_HAS_COMBINE       IUTEST_HAS_COMBINE
#define GTEST_HAS_TYPED_TEST    IUTEST_HAS_TYPED_TEST
#define GTEST_HAS_TYPED_TEST_P  IUTEST_HAS_TYPED_TEST_P

#define GTEST_CAN_STREAM_RESULTS_   0

#define GTEST_HAS_EXCEPTIONS    IUTEST_HAS_EXCEPTIONS
#define GTEST_HAS_RTTI          IUTEST_HAS_RTTI
#define GTEST_HAS_SEH           IUTEST_HAS_SEH

#define GTEST_IS_THREADSAFE     0

// IWYU pragma: begin_exports
#include "switch/iutest_switch_port.hpp"
#include "switch/iutest_switch_core.hpp"

#include "switch/iutest_switch_gmock.hpp"

#include "switch/iutest_switch_assert.hpp"
#include "switch/iutest_switch_expect.hpp"
#include "switch/iutest_switch_inform.hpp"
#include "switch/iutest_switch_assume.hpp"

#include "switch/iutest_switch_assertion_return.hpp"
#include "switch/iutest_switch_package.hpp"
#include "switch/iutest_switch_peep.hpp"
#include "switch/iutest_switch_pmz.hpp"
#include "switch/iutest_switch_pred.hpp"
#include "switch/iutest_switch_skip.hpp"
#include "switch/iutest_switch_throw_value.hpp"
#include "switch/iutest_switch_no_failure.hpp"

#include "switch/iutest_switch_filepath.hpp"

#include "switch/iutest_switch_cmphelper.hpp"
// IWYU pragma: end_exports

namespace iutest
{

//======================================================================
// function
inline void IUTEST_ATTRIBUTE_UNUSED_ InitGoogleTest(int* argc, char** argv)
{
    InitIrisUnitTest(argc, argv);
}
inline void IUTEST_ATTRIBUTE_UNUSED_ InitGoogleTest(int* argc, wchar_t** argv)
{
    InitIrisUnitTest(argc, argv);
}

#if defined(GMOCK_INCLUDE_GMOCK_GMOCK_H_)
inline void IUTEST_ATTRIBUTE_UNUSED_ InitGoogleMock(int* argc, char** argv)
{
    ::testing::InitGoogleMock(argc, argv);
}
inline void IUTEST_ATTRIBUTE_UNUSED_ InitGoogleMock(int* argc, wchar_t** argv)
{
    ::testing::InitGoogleMock(argc, argv);
}
#endif

}   // end of namespace iutest

#ifndef GMOCK_INCLUDE_GMOCK_GMOCK_H_

#if defined(GTEST_INCLUDE_GTEST_GTEST_H_)
// すでに testing namespace が存在するので、define で置き換え
#  define testing   iutest
#else
// それ以外は namespace の置き換えで対応
namespace testing = iutest;
#endif

#endif

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#  define GTEST_INCLUDE_GTEST_GTEST_H_  // 以降で、gtest が include されないようにする
#endif

#endif

#endif // INCG_IRIS_IUTEST_SWITCH_FOR_IUTEST_HPP_478A7B61_F2AE_480D_AF26_1AC5162F7B13
