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

#include "iutest_template_util_defs.hpp"

#define IUTEST_DECL_TYPELIST(n)	\
	template<typename T, IUTEST_TEMPLATE_UTIL_TEMPLATES_TYPENAME(IUTEST_PP_DEC(n))>struct IUTEST_PP_CAT(TypeList, n) {	\
	typedef T Head;																								\
	typedef IUTEST_PP_CAT(TypeList, IUTEST_PP_DEC(n))< IUTEST_TEMPLATE_UTIL_ARGS(IUTEST_PP_DEC(n)) > Tail;		\
}

IUTEST_DECL_TYPELIST(2);
IUTEST_DECL_TYPELIST(3);
IUTEST_DECL_TYPELIST(4);
IUTEST_DECL_TYPELIST(5);
IUTEST_DECL_TYPELIST(6);
IUTEST_DECL_TYPELIST(7);
IUTEST_DECL_TYPELIST(8);
IUTEST_DECL_TYPELIST(9);
IUTEST_DECL_TYPELIST(10);
IUTEST_DECL_TYPELIST(11);
IUTEST_DECL_TYPELIST(12);
IUTEST_DECL_TYPELIST(13);
IUTEST_DECL_TYPELIST(14);
IUTEST_DECL_TYPELIST(15);
IUTEST_DECL_TYPELIST(16);
IUTEST_DECL_TYPELIST(17);
IUTEST_DECL_TYPELIST(18);
IUTEST_DECL_TYPELIST(19);
IUTEST_DECL_TYPELIST(20);
IUTEST_DECL_TYPELIST(21);
IUTEST_DECL_TYPELIST(22);
IUTEST_DECL_TYPELIST(23);
IUTEST_DECL_TYPELIST(24);
IUTEST_DECL_TYPELIST(25);
IUTEST_DECL_TYPELIST(26);
IUTEST_DECL_TYPELIST(27);
IUTEST_DECL_TYPELIST(28);
IUTEST_DECL_TYPELIST(29);
IUTEST_DECL_TYPELIST(30);
IUTEST_DECL_TYPELIST(31);
IUTEST_DECL_TYPELIST(32);
IUTEST_DECL_TYPELIST(33);
IUTEST_DECL_TYPELIST(34);
IUTEST_DECL_TYPELIST(35);
IUTEST_DECL_TYPELIST(36);
IUTEST_DECL_TYPELIST(37);
IUTEST_DECL_TYPELIST(38);
IUTEST_DECL_TYPELIST(39);
IUTEST_DECL_TYPELIST(40);
IUTEST_DECL_TYPELIST(41);
IUTEST_DECL_TYPELIST(42);
IUTEST_DECL_TYPELIST(43);
IUTEST_DECL_TYPELIST(44);
IUTEST_DECL_TYPELIST(45);
IUTEST_DECL_TYPELIST(46);
IUTEST_DECL_TYPELIST(47);
IUTEST_DECL_TYPELIST(48);
IUTEST_DECL_TYPELIST(49);
IUTEST_DECL_TYPELIST(50);

#undef IUTEST_DECL_TYPELIST

#include "iutest_template_util_undef.hpp"

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

#include "iutest_template_util_defs.hpp"

#define IUTEST_DECL_TEMPLATETYPELIST(n)	\
	template< IUTEST_TEMPLATE_TPARAM1 TT, IUTEST_TEMPLATE_UTIL_TEMPLATES(IUTEST_PP_DEC(n), IUTEST_TEMPLATE_TPARAM1) >struct IUTEST_PP_CAT(TemplateTypeList, n) {	\
	typedef TemplateTypeSel<TT> Head;																					\
	typedef IUTEST_PP_CAT(TemplateTypeList, IUTEST_PP_DEC(n))< IUTEST_TEMPLATE_UTIL_ARGS(IUTEST_PP_DEC(n)) > Tail;		\
}

IUTEST_DECL_TEMPLATETYPELIST(2);
IUTEST_DECL_TEMPLATETYPELIST(3);
IUTEST_DECL_TEMPLATETYPELIST(4);
IUTEST_DECL_TEMPLATETYPELIST(5);
IUTEST_DECL_TEMPLATETYPELIST(6);
IUTEST_DECL_TEMPLATETYPELIST(7);
IUTEST_DECL_TEMPLATETYPELIST(8);
IUTEST_DECL_TEMPLATETYPELIST(9);
IUTEST_DECL_TEMPLATETYPELIST(10);
IUTEST_DECL_TEMPLATETYPELIST(11);
IUTEST_DECL_TEMPLATETYPELIST(12);
IUTEST_DECL_TEMPLATETYPELIST(13);
IUTEST_DECL_TEMPLATETYPELIST(14);
IUTEST_DECL_TEMPLATETYPELIST(15);
IUTEST_DECL_TEMPLATETYPELIST(16);
IUTEST_DECL_TEMPLATETYPELIST(17);
IUTEST_DECL_TEMPLATETYPELIST(18);
IUTEST_DECL_TEMPLATETYPELIST(19);
IUTEST_DECL_TEMPLATETYPELIST(20);
IUTEST_DECL_TEMPLATETYPELIST(21);
IUTEST_DECL_TEMPLATETYPELIST(22);
IUTEST_DECL_TEMPLATETYPELIST(23);
IUTEST_DECL_TEMPLATETYPELIST(24);
IUTEST_DECL_TEMPLATETYPELIST(25);
IUTEST_DECL_TEMPLATETYPELIST(26);
IUTEST_DECL_TEMPLATETYPELIST(27);
IUTEST_DECL_TEMPLATETYPELIST(28);
IUTEST_DECL_TEMPLATETYPELIST(29);
IUTEST_DECL_TEMPLATETYPELIST(30);
IUTEST_DECL_TEMPLATETYPELIST(31);
IUTEST_DECL_TEMPLATETYPELIST(32);
IUTEST_DECL_TEMPLATETYPELIST(33);
IUTEST_DECL_TEMPLATETYPELIST(34);
IUTEST_DECL_TEMPLATETYPELIST(35);
IUTEST_DECL_TEMPLATETYPELIST(36);
IUTEST_DECL_TEMPLATETYPELIST(37);
IUTEST_DECL_TEMPLATETYPELIST(38);
IUTEST_DECL_TEMPLATETYPELIST(39);
IUTEST_DECL_TEMPLATETYPELIST(40);
IUTEST_DECL_TEMPLATETYPELIST(41);
IUTEST_DECL_TEMPLATETYPELIST(42);
IUTEST_DECL_TEMPLATETYPELIST(43);
IUTEST_DECL_TEMPLATETYPELIST(44);
IUTEST_DECL_TEMPLATETYPELIST(45);
IUTEST_DECL_TEMPLATETYPELIST(46);
IUTEST_DECL_TEMPLATETYPELIST(47);
IUTEST_DECL_TEMPLATETYPELIST(48);
IUTEST_DECL_TEMPLATETYPELIST(49);
IUTEST_DECL_TEMPLATETYPELIST(50);

#undef IUTEST_DECL_TEMPLATETYPELIST

#include "iutest_template_util_undef.hpp"

#endif

/**
 * @}
*/

}	// end of namespace detail

}	// end of namespace iutest

#endif
