//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_template_util_defs.hpp
 * @brief		iris unit test template ヘルパー定義 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_template_util_defs_HPP_
#define INCG_IRIS_iutest_template_util_defs_HPP_

//======================================================================
// include
#include "iutest_pp.hpp"

//======================================================================
// define
#define IUTEST_TEMPLATE_UTIL_TEMPLATES(n, x)		IUTEST_PP_ENUM_SHIFTED_PARAMS(n, x T)
#define IUTEST_TEMPLATE_UTIL_TEMPLATES_TYPENAME(n)	IUTEST_PP_ENUM_SHIFTED_PARAMS(n, typename T)

#define IUTEST_TEMPLATE_UTIL_ARGS(n)				IUTEST_PP_ENUM_SHIFTED_PARAMS(n, T)

#define IUTEST_TEMPLATE_UTIL_FUNCTION_ARGS_M(param, i)	IUTEST_PP_CAT(T, i) IUTEST_PP_CAT(t, i)
#define IUTEST_TEMPLATE_UTIL_FUNCTION_ARGS(n)		IUTEST_PP_ENUM_SHIFTED_PARAMS_M(n, IUTEST_TEMPLATE_UTIL_FUNCTION_ARGS_M, dummy)

#define IUTEST_TEMPLATE_UTIL_VALUES(n)				IUTEST_PP_ENUM_SHIFTED_PARAMS(n, t)

#ifdef INCG_IRIS_iutest_template_util_undef_HPP_
#  undef INCG_IRIS_iutest_template_util_undef_HPP_
#endif

#endif
