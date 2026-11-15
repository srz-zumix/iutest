//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_switch.hpp
 * @brief       switching to iutest from gtest / gtest from iutest
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
 *
 * @par Value-parameterized test feature detection
 * GoogleTest defined GTEST_HAS_PARAM_TEST through v1.8.0, but removed it
 * in v1.8.1; it is also absent in v1.18.0. The switch layer retains this
 * legacy macro for source compatibility, including samples/gtest/sample7_unittest.cc.
 * Native mode maps it to IUTEST_HAS_PARAM_TEST in iutest_switch_for_iutest.hpp.
 * GoogleTest mode preserves an upstream definition (including 0), or supplies
 * 1 when absent, in iutest_switch_for_gtest.hpp. GoogleTest versions supported
 * by this layer (v1.4.0 onward) provide value-parameterized tests.
 *
 * Use @c \#if @c IUTEST_HAS_PARAM_TEST for feature detection in new code.
 * Existing @c \#if @c GTEST_HAS_PARAM_TEST checks continue to work, including
 * with -Wundef. @c \#ifdef @c GTEST_HAS_PARAM_TEST remains true even when
 * native parameterized tests are disabled; it tests presence, not availability.
 * It must not be used to detect the GoogleTest version.
 *
 * No strict opt-in to omit the macro is provided: matching modern GoogleTest's
 * macro absence would break legacy @c \#if checks under -Wundef and change
 * @c \#ifdef behavior. Retaining the alias does not enable a disabled feature.
 *
 * @par Internal stringification compatibility
 * Native switch mode supplies GTEST_STRINGIFY_ when variadic macros are available
 * (IUTEST_NO_VARIADIC_MACROS is not defined) and the name is not already defined.
 * It matches GoogleTest v1.18.0: expand arguments, then stringify only the first
 * comma-separated argument, including an empty argument. IUTEST_PP_TOSTRING
 * remains unchanged; it is a single-argument macro, not a variadic replacement.
 * Without variadic macros no compatibility definition is supplied.
 * GoogleTest mode leaves upstream definitions (or their absence) untouched,
 * so the GTEST_STRINGIFY_ probe in iutest_gtest_ver.hpp is not affected.
 * Its presence in native mode must not be used to infer a GoogleTest version.
 *
 * gtest_stringify_tests.cpp checks ordinary tokens, expansion, empty arguments,
 * commas, escaping, and preservation of the upstream macro. Expansion cases run
 * against real GoogleTest v1.18.0 onward; older upstream behavior is preserved.
 * gtest_version_tests.cpp checks version detection.
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_HPP_
#define INCG_IRIS_IUTEST_SWITCH_HPP_

// IWYU pragma: begin_exports
#include "iutest_switch_for_gtest.hpp"
#include "iutest_switch_for_iutest.hpp"
// IWYU pragma: end_exports

#endif // INCG_IRIS_IUTEST_SWITCH_HPP_
