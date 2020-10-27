//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_spi_switch.hpp
 * @brief       switching to iutest from gtest / gtest from iutest (spi)
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SPI_SWITCH_HPP_673AE7AC_6F80_4BE0_9209_581E3A568525_
#define INCG_IRIS_IUTEST_SPI_SWITCH_HPP_673AE7AC_6F80_4BE0_9209_581E3A568525_

// IWYU pragma: begin_exports
#include "iutest_switch.hpp"
// IWYU pragma: end_exports

#if !defined(IUTEST_USE_GTEST)

// IWYU pragma: begin_exports
#include "../iutest_spi.hpp"
// IWYU pragma: end_exports

#if defined(GTEST_INCLUDE_GTEST_GTEST_SPI_H_)
#undef EXPECT_FATAL_FAILURE
#undef EXPECT_FATAL_FAILURE_ON_ALL_THREADS
#undef EXPECT_NONFATAL_FAILURE
#undef EXPECT_NONFATAL_FAILURE_ON_ALL_THREADS
#endif

#define EXPECT_FATAL_FAILURE                    IUTEST_EXPECT_FATAL_FAILURE
#define EXPECT_FATAL_FAILURE_ON_ALL_THREADS     IUTEST_EXPECT_FATAL_FAILURE
#define EXPECT_NONFATAL_FAILURE                 IUTEST_EXPECT_NONFATAL_FAILURE
#define EXPECT_NONFATAL_FAILURE_ON_ALL_THREADS  IUTEST_EXPECT_NONFATAL_FAILURE

#else // !defined(IUTEST_USE_GTEST)

#include <gtest/gtest-spi.h>

#if defined(_MSC_VER) && !defined(__clang__)
// /ZI オプションだと __LINE__ が __LINE__Var+N(Nは番号) になりコンパイルエラーになるための対応
#  ifndef __LINE__Var
#    define __LINE__Var 0
#  endif
#endif

#if defined(INCG_IRIS_IUTEST_SPI_HPP_)
#undef IUTEST_ASSERT_FATAL_FAILURE
#undef IUTEST_EXPECT_FATAL_FAILURE
#undef IUTEST_ASSERT_NONFATAL_FAILURE
#undef IUTEST_EXPECT_NONFATAL_FAILURE
#endif

#define IUTEST_ASSERT_FATAL_FAILURE             EXPECT_FATAL_FAILURE
#define IUTEST_EXPECT_FATAL_FAILURE             EXPECT_FATAL_FAILURE
#define IUTEST_ASSERT_NONFATAL_FAILURE          EXPECT_NONFATAL_FAILURE
#define IUTEST_EXPECT_NONFATAL_FAILURE          EXPECT_NONFATAL_FAILURE

#endif // !defined(IUTEST_USE_GTEST)

#endif // INCG_IRIS_IUTEST_SPI_SWITCH_HPP_673AE7AC_6F80_4BE0_9209_581E3A568525_
