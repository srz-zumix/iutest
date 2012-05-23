//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_typelist.hpp
 * @brief		iris unit test type リスト ファイル
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
#ifndef INCG_IRIS_iutest_typelist_HPP_0AC27A0F_3EFF_48ad_9075_E439B4190DA5_
#define INCG_IRIS_iutest_typelist_HPP_0AC27A0F_3EFF_48ad_9075_E439B4190DA5_

//======================================================================
// include

namespace iutest {
namespace detail
{

//======================================================================
// define
#define IUTEST_TEMPLATE_TPARAM1	template<typename T> class

//======================================================================
// struct
/**
 * @brief	TypeList
 * @{
*/

// type list 終端
struct TypeList0 {};

template<typename T1>
struct TypeList1
{
	typedef T1	Head;
	typedef TypeList0	Tail;
};

#if IUTEST_HAS_VARIADIC_TEMPLATES

template<typename T, typename ...Args>
struct VariadicTypeList
{
	typedef T	Head;
	typedef VariadicTypeList<Args...>	Tail;
};
template<typename T>
struct VariadicTypeList<T>
{
	typedef T	Head;
	typedef TypeList0	Tail;
};

#else

template<typename T1, typename T2>
struct TypeList2
{
	typedef T1	Head;
	typedef TypeList1<T2>	Tail;
};

template<typename T1, typename T2, typename T3>
struct TypeList3
{
	typedef T1	Head;
	typedef TypeList2<T2, T3>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4>
struct TypeList4
{
	typedef T1	Head;
	typedef TypeList3<T2, T3, T4>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5>
struct TypeList5
{
	typedef T1	Head;
	typedef TypeList4<T2, T3, T4, T5>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
struct TypeList6
{
	typedef T1	Head;
	typedef TypeList5<T2, T3, T4, T5, T6>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
struct TypeList7
{
	typedef T1	Head;
	typedef TypeList6<T2, T3, T4, T5, T6, T7>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
struct TypeList8
{
	typedef T1	Head;
	typedef TypeList7<T2, T3, T4, T5, T6, T7, T8>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
struct TypeList9
{
	typedef T1	Head;
	typedef TypeList8<T2, T3, T4, T5, T6, T7, T8, T9>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10>
struct TypeList10
{
	typedef T1	Head;
	typedef TypeList9<T2, T3, T4, T5, T6, T7, T8, T9
	, T10>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11>
struct TypeList11
{
	typedef T1	Head;
	typedef TypeList10<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12>
struct TypeList12
{
	typedef T1	Head;
	typedef TypeList11<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13>
struct TypeList13
{
	typedef T1	Head;
	typedef TypeList12<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14>
struct TypeList14
{
	typedef T1	Head;
	typedef TypeList13<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
struct TypeList15
{
	typedef T1	Head;
	typedef TypeList14<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
struct TypeList16
{
	typedef T1	Head;
	typedef TypeList15<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17>
struct TypeList17
{
	typedef T1	Head;
	typedef TypeList16<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18>
struct TypeList18
{
	typedef T1	Head;
	typedef TypeList17<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19>
struct TypeList19
{
	typedef T1	Head;
	typedef TypeList18<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20>
struct TypeList20
{
	typedef T1	Head;
	typedef TypeList19<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21>
struct TypeList21
{
	typedef T1	Head;
	typedef TypeList20<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22>
struct TypeList22
{
	typedef T1	Head;
	typedef TypeList21<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23>
struct TypeList23
{
	typedef T1	Head;
	typedef TypeList22<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24>
struct TypeList24
{
	typedef T1	Head;
	typedef TypeList23<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25>
struct TypeList25
{
	typedef T1	Head;
	typedef TypeList24<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26>
struct TypeList26
{
	typedef T1	Head;
	typedef TypeList25<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27>
struct TypeList27
{
	typedef T1	Head;
	typedef TypeList26<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28>
struct TypeList28
{
	typedef T1	Head;
	typedef TypeList27<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
struct TypeList29
{
	typedef T1	Head;
	typedef TypeList28<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30>
struct TypeList30
{
	typedef T1	Head;
	typedef TypeList29<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31>
struct TypeList31
{
	typedef T1	Head;
	typedef TypeList30<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32>
struct TypeList32
{
	typedef T1	Head;
	typedef TypeList31<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33>
struct TypeList33
{
	typedef T1	Head;
	typedef TypeList32<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34>
struct TypeList34
{
	typedef T1	Head;
	typedef TypeList33<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35>
struct TypeList35
{
	typedef T1	Head;
	typedef TypeList34<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36>
struct TypeList36
{
	typedef T1	Head;
	typedef TypeList35<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37>
struct TypeList37
{
	typedef T1	Head;
	typedef TypeList36<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38>
struct TypeList38
{
	typedef T1	Head;
	typedef TypeList37<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39>
struct TypeList39
{
	typedef T1	Head;
	typedef TypeList38<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40>
struct TypeList40
{
	typedef T1	Head;
	typedef TypeList39<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41>
struct TypeList41
{
	typedef T1	Head;
	typedef TypeList40<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42>
struct TypeList42
{
	typedef T1	Head;
	typedef TypeList41<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43>
struct TypeList43
{
	typedef T1	Head;
	typedef TypeList42<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44>
struct TypeList44
{
	typedef T1	Head;
	typedef TypeList43<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45>
struct TypeList45
{
	typedef T1	Head;
	typedef TypeList44<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46>
struct TypeList46
{
	typedef T1	Head;
	typedef TypeList45<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47>
struct TypeList47
{
	typedef T1	Head;
	typedef TypeList46<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48>
struct TypeList48
{
	typedef T1	Head;
	typedef TypeList47<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49>
struct TypeList49
{
	typedef T1	Head;
	typedef TypeList48<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49>	Tail;
};

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9
, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16, typename T17, typename T18, typename T19
, typename T20, typename T21, typename T22, typename T23, typename T24, typename T25, typename T26, typename T27, typename T28, typename T29
, typename T30, typename T31, typename T32, typename T33, typename T34, typename T35, typename T36, typename T37, typename T38, typename T39
, typename T40, typename T41, typename T42, typename T43, typename T44, typename T45, typename T46, typename T47, typename T48, typename T49
, typename T50>
struct TypeList50
{
	typedef T1	Head;
	typedef TypeList49<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
	, T50>	Tail;
};

#endif

/**
 * @}
*/


/**
 * @brief	TemplateTypeListBind
*/
template<IUTEST_TEMPLATE_TPARAM1 U>
struct TemplateTypeSel
{
	template<typename T>
	struct bind
	{
		typedef U<T>	type;
	};
};

/**
 * @brief	TemplateTypeList
 * @{
*/

// template type list 終端
struct TemplateTypeList0 {};

#if IUTEST_HAS_VARIADIC_TEMPLATE_TEMPLATES

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 ...Types>
struct VariadicTemplateTypeList
{
	typedef TemplateTypeSel<T1>	Head;
	typedef VariadicTemplateTypeList<Types...>	Tail;
};
template<IUTEST_TEMPLATE_TPARAM1 T1>
struct VariadicTemplateTypeList<T1>
{
	typedef TemplateTypeSel<T1>	Head;
	typedef TemplateTypeList0	Tail;
};

#else

template<IUTEST_TEMPLATE_TPARAM1 T1>
struct TemplateTypeList1
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList0	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2>
struct TemplateTypeList2
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList1<T2>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3>
struct TemplateTypeList3
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList2<T2, T3>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4>
struct TemplateTypeList4
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList3<T2, T3, T4>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5>
struct TemplateTypeList5
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList4<T2, T3, T4, T5>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6>
struct TemplateTypeList6
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList5<T2, T3, T4, T5, T6>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7>
struct TemplateTypeList7
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList6<T2, T3, T4, T5, T6, T7>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8>
struct TemplateTypeList8
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList7<T2, T3, T4, T5, T6, T7, T8>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9>
struct TemplateTypeList9
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList8<T2, T3, T4, T5, T6, T7, T8, T9>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10>
struct TemplateTypeList10
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList9<T2, T3, T4, T5, T6, T7, T8, T9
	, T10>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11>
struct TemplateTypeList11
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList10<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12>
struct TemplateTypeList12
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList11<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13>
struct TemplateTypeList13
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList12<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14>
struct TemplateTypeList14
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList13<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15>
struct TemplateTypeList15
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList14<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16>
struct TemplateTypeList16
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList15<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17>
struct TemplateTypeList17
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList16<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18>
struct TemplateTypeList18
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList17<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19>
struct TemplateTypeList19
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList18<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20>
struct TemplateTypeList20
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList19<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21>
struct TemplateTypeList21
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList20<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22>
struct TemplateTypeList22
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList21<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23>
struct TemplateTypeList23
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList22<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24>
struct TemplateTypeList24
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList23<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25>
struct TemplateTypeList25
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList24<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26>
struct TemplateTypeList26
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList25<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27>
struct TemplateTypeList27
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList26<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28>
struct TemplateTypeList28
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList27<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29>
struct TemplateTypeList29
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList28<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30>
struct TemplateTypeList30
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList29<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31>
struct TemplateTypeList31
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList30<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32>
struct TemplateTypeList32
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList31<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33>
struct TemplateTypeList33
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList32<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34>
struct TemplateTypeList34
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList33<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35>
struct TemplateTypeList35
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList34<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36>
struct TemplateTypeList36
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList35<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37>
struct TemplateTypeList37
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList36<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38>
struct TemplateTypeList38
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList37<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39>
struct TemplateTypeList39
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList38<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40>
struct TemplateTypeList40
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList39<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41>
struct TemplateTypeList41
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList40<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42>
struct TemplateTypeList42
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList41<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43>
struct TemplateTypeList43
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList42<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44>
struct TemplateTypeList44
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList43<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45>
struct TemplateTypeList45
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList44<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46>
struct TemplateTypeList46
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList45<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46, IUTEST_TEMPLATE_TPARAM1 T47>
struct TemplateTypeList47
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList46<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46, IUTEST_TEMPLATE_TPARAM1 T47, IUTEST_TEMPLATE_TPARAM1 T48>
struct TemplateTypeList48
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList47<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46, IUTEST_TEMPLATE_TPARAM1 T47, IUTEST_TEMPLATE_TPARAM1 T48, IUTEST_TEMPLATE_TPARAM1 T49>
struct TemplateTypeList49
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList48<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49>	Tail;
};

template<IUTEST_TEMPLATE_TPARAM1 T1, IUTEST_TEMPLATE_TPARAM1 T2, IUTEST_TEMPLATE_TPARAM1 T3, IUTEST_TEMPLATE_TPARAM1 T4, IUTEST_TEMPLATE_TPARAM1 T5, IUTEST_TEMPLATE_TPARAM1 T6, IUTEST_TEMPLATE_TPARAM1 T7, IUTEST_TEMPLATE_TPARAM1 T8, IUTEST_TEMPLATE_TPARAM1 T9
, IUTEST_TEMPLATE_TPARAM1 T10, IUTEST_TEMPLATE_TPARAM1 T11, IUTEST_TEMPLATE_TPARAM1 T12, IUTEST_TEMPLATE_TPARAM1 T13, IUTEST_TEMPLATE_TPARAM1 T14, IUTEST_TEMPLATE_TPARAM1 T15, IUTEST_TEMPLATE_TPARAM1 T16, IUTEST_TEMPLATE_TPARAM1 T17, IUTEST_TEMPLATE_TPARAM1 T18, IUTEST_TEMPLATE_TPARAM1 T19
, IUTEST_TEMPLATE_TPARAM1 T20, IUTEST_TEMPLATE_TPARAM1 T21, IUTEST_TEMPLATE_TPARAM1 T22, IUTEST_TEMPLATE_TPARAM1 T23, IUTEST_TEMPLATE_TPARAM1 T24, IUTEST_TEMPLATE_TPARAM1 T25, IUTEST_TEMPLATE_TPARAM1 T26, IUTEST_TEMPLATE_TPARAM1 T27, IUTEST_TEMPLATE_TPARAM1 T28, IUTEST_TEMPLATE_TPARAM1 T29
, IUTEST_TEMPLATE_TPARAM1 T30, IUTEST_TEMPLATE_TPARAM1 T31, IUTEST_TEMPLATE_TPARAM1 T32, IUTEST_TEMPLATE_TPARAM1 T33, IUTEST_TEMPLATE_TPARAM1 T34, IUTEST_TEMPLATE_TPARAM1 T35, IUTEST_TEMPLATE_TPARAM1 T36, IUTEST_TEMPLATE_TPARAM1 T37, IUTEST_TEMPLATE_TPARAM1 T38, IUTEST_TEMPLATE_TPARAM1 T39
, IUTEST_TEMPLATE_TPARAM1 T40, IUTEST_TEMPLATE_TPARAM1 T41, IUTEST_TEMPLATE_TPARAM1 T42, IUTEST_TEMPLATE_TPARAM1 T43, IUTEST_TEMPLATE_TPARAM1 T44, IUTEST_TEMPLATE_TPARAM1 T45, IUTEST_TEMPLATE_TPARAM1 T46, IUTEST_TEMPLATE_TPARAM1 T47, IUTEST_TEMPLATE_TPARAM1 T48, IUTEST_TEMPLATE_TPARAM1 T49
, IUTEST_TEMPLATE_TPARAM1 T50>
struct TemplateTypeList50
{
	typedef TemplateTypeSel<T1> Head;
	typedef TemplateTypeList49<T2, T3, T4, T5, T6, T7, T8, T9
	, T10, T11, T12, T13, T14, T15, T16, T17, T18, T19
	, T20, T21, T22, T23, T24, T25, T26, T27, T28, T29
	, T30, T31, T32, T33, T34, T35, T36, T37, T38, T39
	, T40, T41, T42, T43, T44, T45, T46, T47, T48, T49
	, T50>	Tail;
};

#endif

/**
 * @}
*/

}	// end of namespace detail

}	// end of namespace iutest

#endif
