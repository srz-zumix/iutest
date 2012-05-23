//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_typed_util.hpp
 * @brief		iris unit test typed util ƒtƒ@ƒCƒ‹
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2011-2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_typed_util_HPP_32A6F7CF_36C6_4ede_AD19_04965FBFBB37_
#define INCG_IRIS_iutest_typed_util_HPP_32A6F7CF_36C6_4ede_AD19_04965FBFBB37_

//======================================================================
// include
#include "iutest_internal_defs.h"
#include "iutest_typelist.hpp"

namespace iutest
{

//======================================================================
// struct

/**
 * @brief	Types
 * @{
*/
#if IUTEST_HAS_VARIADIC_TEMPLATES

template<typename ...Args>
struct Types
{
	typedef detail::VariadicTypeList<Args...> type;
};

#else

template<typename T1 = detail::None, typename T2 = detail::None, typename T3 = detail::None, typename T4 = detail::None
, typename T5 = detail::None, typename T6 = detail::None, typename T7 = detail::None, typename T8 = detail::None, typename T9 = detail::None
, typename T10 = detail::None, typename T11 = detail::None, typename T12 = detail::None, typename T13 = detail::None, typename T14 = detail::None
, typename T15 = detail::None, typename T16 = detail::None, typename T17 = detail::None, typename T18 = detail::None, typename T19 = detail::None
, typename T20 = detail::None, typename T21 = detail::None, typename T22 = detail::None, typename T23 = detail::None, typename T24 = detail::None
, typename T25 = detail::None, typename T26 = detail::None, typename T27 = detail::None, typename T28 = detail::None, typename T29 = detail::None
, typename T30 = detail::None, typename T31 = detail::None, typename T32 = detail::None, typename T33 = detail::None, typename T34 = detail::None
, typename T35 = detail::None, typename T36 = detail::None, typename T37 = detail::None, typename T38 = detail::None, typename T39 = detail::None
, typename T40 = detail::None, typename T41 = detail::None, typename T42 = detail::None, typename T43 = detail::None, typename T44 = detail::None
, typename T45 = detail::None, typename T46 = detail::None, typename T47 = detail::None, typename T48 = detail::None, typename T49 = detail::None
, typename T50 = detail::None
>struct Types
{
	typedef detail::TypeList50<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
		, T50
	> type;
};

template<>
struct Types<detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList0	type;
};

template<typename T1>
struct Types<T1, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList1<T1>	type;
};

template<typename T1, typename T2>
struct Types<T1, T2, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList2<T1, T2>	type;
};

template<typename T1, typename T2, typename T3>
struct Types<T1, T2, T3, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList3<T1, T2, T3>	type;
};

template<typename T1, typename T2, typename T3, typename T4>
struct Types<T1, T2, T3, T4
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList4<T1, T2, T3, T4>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct Types<T1, T2, T3, T4, T5, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList5<T1, T2, T3, T4, T5>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct Types<T1, T2, T3, T4, T5, T6, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList6<T1, T2, T3, T4, T5, T6>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct Types<T1, T2, T3, T4, T5, T6, T7, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList7<T1, T2, T3, T4, T5, T6, T7>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList8<T1, T2, T3, T4, T5, T6, T7, T8>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList9<T1, T2, T3, T4, T5, T6, T7, T8, T9>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList10<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList11<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList12<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList13<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList14<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList15<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList16<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList17<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList18<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList19<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList20<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList21<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList22<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList23<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList24<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList25<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList26<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList27<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList28<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList29<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList30<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList31<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList32<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList33<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList34<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList35<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList36<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList37<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList38<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList39<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, detail::None, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList40<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, detail::None, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList41<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, detail::None, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList42<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, detail::None
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList43<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44
, detail::None, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList44<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, detail::None, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList45<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, T46, detail::None, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList46<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, T46, T47, detail::None, detail::None
, detail::None
>
{
	typedef detail::TypeList47<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, T46, T47, T48, detail::None
, detail::None
>
{
	typedef detail::TypeList48<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48>	type;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
struct Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
, detail::None
>
{
	typedef detail::TypeList49<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49>	type;
};

#endif

/**
 * @}
*/

namespace detail
{

/**
 * @brief	Templates
 * @{
*/
#if IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES
template<IUTEST_TEMPLATE_TPARAM1 ...Types>
struct Templates
{
	typedef VariadicTemplateTypeList<Types...> type;
};

#else

template<IUTEST_TEMPLATE_TPARAM1 T1 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T2 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T3 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T4 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T5 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T6 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T7 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T8 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T9 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T10 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T11 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T12 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T13 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T14 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T15 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T16 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T17 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T18 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T19 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T20 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T21 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T22 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T23 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T24 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T25 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T26 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T27 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T28 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T29 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T30 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T31 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T32 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T33 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T34 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T35 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T36 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T37 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T38 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T39 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T40 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T41 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T42 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T43 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T44 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T45 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T46 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T47 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T48 = detail::NoneT1, IUTEST_TEMPLATE_TPARAM1 T49 = detail::NoneT1
, IUTEST_TEMPLATE_TPARAM1 T50 = detail::NoneT1
>struct Templates
{
	typedef detail::TemplateTypeList50<T1, T2, T3, T4, T5, T6, T7, T8, T9
		, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
		, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
		, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
		, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
		, T50
	> type;
};

template<>
struct Templates<detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList0	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1>
struct Templates<T1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList1<T1>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2>
struct Templates<T1, T2, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList2<T1, T2>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3>
struct Templates<T1, T2, T3, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList3<T1, T2, T3>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4>
struct Templates<T1, T2, T3, T4
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList4<T1, T2, T3, T4>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5>
struct Templates<T1, T2, T3, T4, T5, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList5<T1, T2, T3, T4, T5>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6>
struct Templates<T1, T2, T3, T4, T5, T6, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList6<T1, T2, T3, T4, T5, T6>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7>
struct Templates<T1, T2, T3, T4, T5, T6, T7, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList7<T1, T2, T3, T4, T5, T6, T7>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList8<T1, T2, T3, T4, T5, T6, T7, T8>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList9<T1, T2, T3, T4, T5, T6, T7, T8, T9>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList10<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList11<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList12<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList13<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList14<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList15<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList16<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList17<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList18<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList19<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList20<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList21<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList22<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList23<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList24<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList25<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList26<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList27<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList28<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList29<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList30<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList31<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList32<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList33<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList34<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList35<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList36<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList37<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList38<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList39<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList40<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList41<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, detail::NoneT1, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList42<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, detail::NoneT1
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList43<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44
, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList44<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, detail::NoneT1, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList45<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, T46, detail::NoneT1, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList46<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46, IUTEST_TEMPLATE_TPARAM1 T47>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, T46, T47, detail::NoneT1, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList47<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46, IUTEST_TEMPLATE_TPARAM1 T47, IUTEST_TEMPLATE_TPARAM1 T48>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, T46, T47, T48, detail::NoneT1
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList48<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48>	type;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46, IUTEST_TEMPLATE_TPARAM1 T47, IUTEST_TEMPLATE_TPARAM1 T48, IUTEST_TEMPLATE_TPARAM1 T49>
struct Templates<T1, T2, T3, T4, T5, T6, T7, T8, T9
, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
, detail::NoneT1
>
{
	typedef detail::TemplateTypeList49<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49>	type;
};

#endif

/**
 * @}
*/

template<typename T>
struct TypeList
{
	typedef detail::TypeList1<T>	type;
};

#if IUTEST_HAS_VARIADIC_TEMPLATES

template<typename ...Args>
struct TypeList< Types<Args...> >
{
	typedef typename Types<Args...>::type type;
};

#else

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49
, typename T50>
struct TypeList< Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
	, T50>
>
{
	typedef typename Types<T1, T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
	, T50>::type type;
};

#endif

}	// end of namespace detail
}	// end of namespace iutest

#endif
