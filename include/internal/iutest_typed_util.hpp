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
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_typed_util_HPP_32A6F7CF_36C6_4ede_AD19_04965FBFBB37_
#define INCG_IRIS_iutest_typed_util_HPP_32A6F7CF_36C6_4ede_AD19_04965FBFBB37_

//======================================================================
// include
#include "iutest_internal_defs.hpp"
#include "iutest_typelist.hpp"

namespace iutest
{

//======================================================================
// struct
#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

/**
 * @brief	Types
 * @{
*/
#if IUTEST_HAS_VARIADIC_TEMPLATES

template<typename ...Args>
struct Types
{
	typedef detail::VariadicTypeList<Args...> type;
	template<size_t N>struct get : public detail::typelist_get<type, N> {};
};

#else

#define IUTEST_DECL_DEFAULT_ARG_(i, param)	IUTEST_PP_CAT(param,i)=detail::None

template< IUTEST_PP_ENUM(50, IUTEST_DECL_DEFAULT_ARG_, typename T) >
struct Types
{
	typedef detail::TypeList50< IUTEST_PP_ENUM_PARAMS(50, T) > type;
	template<size_t N>struct get : public detail::typelist_get<type, N> {};
};

#undef IUTEST_DECL_DEFAULT_ARG_

#define IUTEST_DECL_SPEC_NONE_(i, param)	param
#define IUTEST_DECL_TYPES_(n, m)							\
	template< IUTEST_PP_ENUM_PARAMS(n, typename T) >		\
	struct Types< IUTEST_PP_ENUM_PARAMS(n, T)				\
		, IUTEST_PP_ENUM(m, IUTEST_DECL_SPEC_NONE_, detail::None) > {	\
		typedef IUTEST_PP_CAT(detail::TypeList, n)<			\
			IUTEST_PP_ENUM_PARAMS(n, T) > type;				\
		template<size_t N>struct get : public detail::typelist_get<type, N> {};	\
	}

template<>
struct Types< IUTEST_PP_ENUM(50, IUTEST_DECL_SPEC_NONE_, detail::None) >
{
	typedef detail::TypeList0	type;
};

IUTEST_DECL_TYPES_( 1, 49);
IUTEST_DECL_TYPES_( 2, 48);
IUTEST_DECL_TYPES_( 3, 47);
IUTEST_DECL_TYPES_( 4, 46);
IUTEST_DECL_TYPES_( 5, 45);
IUTEST_DECL_TYPES_( 6, 44);
IUTEST_DECL_TYPES_( 7, 43);
IUTEST_DECL_TYPES_( 8, 42);
IUTEST_DECL_TYPES_( 9, 41);
IUTEST_DECL_TYPES_(10, 40);
IUTEST_DECL_TYPES_(11, 39);
IUTEST_DECL_TYPES_(12, 38);
IUTEST_DECL_TYPES_(13, 37);
IUTEST_DECL_TYPES_(14, 36);
IUTEST_DECL_TYPES_(15, 35);
IUTEST_DECL_TYPES_(16, 34);
IUTEST_DECL_TYPES_(17, 33);
IUTEST_DECL_TYPES_(18, 32);
IUTEST_DECL_TYPES_(19, 31);
IUTEST_DECL_TYPES_(20, 30);
IUTEST_DECL_TYPES_(21, 29);
IUTEST_DECL_TYPES_(22, 28);
IUTEST_DECL_TYPES_(23, 27);
IUTEST_DECL_TYPES_(24, 26);
IUTEST_DECL_TYPES_(25, 25);
IUTEST_DECL_TYPES_(26, 24);
IUTEST_DECL_TYPES_(27, 23);
IUTEST_DECL_TYPES_(28, 22);
IUTEST_DECL_TYPES_(29, 21);
IUTEST_DECL_TYPES_(30, 20);
IUTEST_DECL_TYPES_(31, 19);
IUTEST_DECL_TYPES_(32, 18);
IUTEST_DECL_TYPES_(33, 17);
IUTEST_DECL_TYPES_(34, 16);
IUTEST_DECL_TYPES_(35, 15);
IUTEST_DECL_TYPES_(36, 14);
IUTEST_DECL_TYPES_(37, 13);
IUTEST_DECL_TYPES_(38, 12);
IUTEST_DECL_TYPES_(39, 11);
IUTEST_DECL_TYPES_(40, 10);
IUTEST_DECL_TYPES_(41,  9);
IUTEST_DECL_TYPES_(42,  8);
IUTEST_DECL_TYPES_(43,  7);
IUTEST_DECL_TYPES_(44,  6);
IUTEST_DECL_TYPES_(45,  5);
IUTEST_DECL_TYPES_(46,  4);
IUTEST_DECL_TYPES_(47,  3);
IUTEST_DECL_TYPES_(48,  2);
IUTEST_DECL_TYPES_(49,  1);

#undef IUTEST_DECL_SPEC_NONE_
#undef IUTEST_DECL_TYPES_

#endif

/**
 * @}
*/

namespace detail
{

#if !defined(IUTEST_NO_TEMPLATE_TEMPLATES)

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

#define IUTEST_DECL_DEFAULT_ARG_(i, param)	IUTEST_PP_CAT(param,i)=detail::NoneT1

template< IUTEST_PP_ENUM(50, IUTEST_DECL_DEFAULT_ARG_, IUTEST_TEMPLATE_TPARAM1 T) >
struct Templates
{
	typedef detail::TemplateTypeList50< IUTEST_PP_ENUM_PARAMS(50, T) > type;
};

#undef IUTEST_DECL_DEFAULT_ARG_

#define IUTEST_DECL_SPEC_NONE_(i, param)	param
#define IUTEST_DECL_TEMPLATES_(n, m)									\
	template< IUTEST_PP_ENUM_PARAMS(n, IUTEST_TEMPLATE_TPARAM1 T) >		\
	struct Templates< IUTEST_PP_ENUM_PARAMS(n, T)						\
		, IUTEST_PP_ENUM(m, IUTEST_DECL_SPEC_NONE_, detail::NoneT1) > {	\
		typedef IUTEST_PP_CAT(detail::TemplateTypeList, n)<				\
			IUTEST_PP_ENUM_PARAMS(n, T) > type;							\
	}

template<>
struct Templates< IUTEST_PP_ENUM(50, IUTEST_DECL_SPEC_NONE_, detail::NoneT1) >
{
	typedef detail::TemplateTypeList0	type;
};

IUTEST_DECL_TEMPLATES_( 1, 49);
IUTEST_DECL_TEMPLATES_( 2, 48);
IUTEST_DECL_TEMPLATES_( 3, 47);
IUTEST_DECL_TEMPLATES_( 4, 46);
IUTEST_DECL_TEMPLATES_( 5, 45);
IUTEST_DECL_TEMPLATES_( 6, 44);
IUTEST_DECL_TEMPLATES_( 7, 43);
IUTEST_DECL_TEMPLATES_( 8, 42);
IUTEST_DECL_TEMPLATES_( 9, 41);
IUTEST_DECL_TEMPLATES_(10, 40);
IUTEST_DECL_TEMPLATES_(11, 39);
IUTEST_DECL_TEMPLATES_(12, 38);
IUTEST_DECL_TEMPLATES_(13, 37);
IUTEST_DECL_TEMPLATES_(14, 36);
IUTEST_DECL_TEMPLATES_(15, 35);
IUTEST_DECL_TEMPLATES_(16, 34);
IUTEST_DECL_TEMPLATES_(17, 33);
IUTEST_DECL_TEMPLATES_(18, 32);
IUTEST_DECL_TEMPLATES_(19, 31);
IUTEST_DECL_TEMPLATES_(20, 30);
IUTEST_DECL_TEMPLATES_(21, 29);
IUTEST_DECL_TEMPLATES_(22, 28);
IUTEST_DECL_TEMPLATES_(23, 27);
IUTEST_DECL_TEMPLATES_(24, 26);
IUTEST_DECL_TEMPLATES_(25, 25);
IUTEST_DECL_TEMPLATES_(26, 24);
IUTEST_DECL_TEMPLATES_(27, 23);
IUTEST_DECL_TEMPLATES_(28, 22);
IUTEST_DECL_TEMPLATES_(29, 21);
IUTEST_DECL_TEMPLATES_(30, 20);
IUTEST_DECL_TEMPLATES_(31, 19);
IUTEST_DECL_TEMPLATES_(32, 18);
IUTEST_DECL_TEMPLATES_(33, 17);
IUTEST_DECL_TEMPLATES_(34, 16);
IUTEST_DECL_TEMPLATES_(35, 15);
IUTEST_DECL_TEMPLATES_(36, 14);
IUTEST_DECL_TEMPLATES_(37, 13);
IUTEST_DECL_TEMPLATES_(38, 12);
IUTEST_DECL_TEMPLATES_(39, 11);
IUTEST_DECL_TEMPLATES_(40, 10);
IUTEST_DECL_TEMPLATES_(41,  9);
IUTEST_DECL_TEMPLATES_(42,  8);
IUTEST_DECL_TEMPLATES_(43,  7);
IUTEST_DECL_TEMPLATES_(44,  6);
IUTEST_DECL_TEMPLATES_(45,  5);
IUTEST_DECL_TEMPLATES_(46,  4);
IUTEST_DECL_TEMPLATES_(47,  3);
IUTEST_DECL_TEMPLATES_(48,  2);
IUTEST_DECL_TEMPLATES_(49,  1);

#undef IUTEST_DECL_SPEC_NONE_
#undef IUTEST_DECL_TEMPLATES_

#endif

/**
 * @}
*/

#endif	// #if !defined(IUTEST_NO_TEMPLATE_TEMPLATES)

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

template< IUTEST_PP_ENUM_PARAMS(50, typename T) >
struct TypeList< Types< IUTEST_PP_ENUM_PARAMS(50, T) > >
{
	typedef typename Types< IUTEST_PP_ENUM_PARAMS(50, T) >::type type;
};

#endif

}	// end of namespace detail

#endif	// #if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

}	// end of namespace iutest

#endif
