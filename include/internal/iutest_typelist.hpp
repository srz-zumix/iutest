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
 * Copyright (C) 2011-2013, Takazumi Shirayanagi\n
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
#if !defined(IUTEST_NO_TEMPLATE_TEMPLATES)
#  define IUTEST_TEMPLATE_TPARAM1	template<typename T> class
#endif

//======================================================================
// struct
/**
 * @brief	TypeList
 * @{
*/

// TypeList から 型を取得
template<typename TypeList, size_t N>
class typelist_get
{
	template<typename T, size_t I>
	struct impl
	{
		typedef typename impl<typename T::Tail, I-1>::type type;
	};
	template<typename T>
	struct impl<T, 0>
	{
		typedef typename T::Head type;
	};
public:
	typedef typename impl<TypeList, N>::type type;
};

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

#define IUTEST_DECL_TYPELIST_(n)	IUTEST_DECL_TYPELIST_I(n, IUTEST_PP_DEC(n))
#define IUTEST_DECL_TYPELIST_I(n, m)													\
	template<typename T0, IUTEST_PP_ENUM_SHIFTED_PARAMS(m, typename T)>					\
	struct IUTEST_PP_CAT(TypeList, n) {	typedef T0 Head;								\
	typedef IUTEST_PP_CAT(TypeList, m)< IUTEST_PP_ENUM_SHIFTED_PARAMS(m, T) > Tail;		\
}

IUTEST_DECL_TYPELIST_(2);
IUTEST_DECL_TYPELIST_(3);
IUTEST_DECL_TYPELIST_(4);
IUTEST_DECL_TYPELIST_(5);
IUTEST_DECL_TYPELIST_(6);
IUTEST_DECL_TYPELIST_(7);
IUTEST_DECL_TYPELIST_(8);
IUTEST_DECL_TYPELIST_(9);
IUTEST_DECL_TYPELIST_(10);
IUTEST_DECL_TYPELIST_(11);
IUTEST_DECL_TYPELIST_(12);
IUTEST_DECL_TYPELIST_(13);
IUTEST_DECL_TYPELIST_(14);
IUTEST_DECL_TYPELIST_(15);
IUTEST_DECL_TYPELIST_(16);
IUTEST_DECL_TYPELIST_(17);
IUTEST_DECL_TYPELIST_(18);
IUTEST_DECL_TYPELIST_(19);
IUTEST_DECL_TYPELIST_(20);
IUTEST_DECL_TYPELIST_(21);
IUTEST_DECL_TYPELIST_(22);
IUTEST_DECL_TYPELIST_(23);
IUTEST_DECL_TYPELIST_(24);
IUTEST_DECL_TYPELIST_(25);
IUTEST_DECL_TYPELIST_(26);
IUTEST_DECL_TYPELIST_(27);
IUTEST_DECL_TYPELIST_(28);
IUTEST_DECL_TYPELIST_(29);
IUTEST_DECL_TYPELIST_(30);
IUTEST_DECL_TYPELIST_(31);
IUTEST_DECL_TYPELIST_(32);
IUTEST_DECL_TYPELIST_(33);
IUTEST_DECL_TYPELIST_(34);
IUTEST_DECL_TYPELIST_(35);
IUTEST_DECL_TYPELIST_(36);
IUTEST_DECL_TYPELIST_(37);
IUTEST_DECL_TYPELIST_(38);
IUTEST_DECL_TYPELIST_(39);
IUTEST_DECL_TYPELIST_(40);
IUTEST_DECL_TYPELIST_(41);
IUTEST_DECL_TYPELIST_(42);
IUTEST_DECL_TYPELIST_(43);
IUTEST_DECL_TYPELIST_(44);
IUTEST_DECL_TYPELIST_(45);
IUTEST_DECL_TYPELIST_(46);
IUTEST_DECL_TYPELIST_(47);
IUTEST_DECL_TYPELIST_(48);
IUTEST_DECL_TYPELIST_(49);
IUTEST_DECL_TYPELIST_(50);

#undef IUTEST_DECL_TYPELIST_

#endif

/**
 * @}
*/


#if !defined(IUTEST_NO_TEMPLATE_TEMPLATES)

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

#define IUTEST_DECL_TEMPLATETYPELIST_(n)	IUTEST_DECL_TEMPLATETYPELIST_I(n, IUTEST_PP_DEC(n))
#define IUTEST_DECL_TEMPLATETYPELIST_I(n, m)															\
	template< IUTEST_TEMPLATE_TPARAM1 T0, IUTEST_PP_ENUM_SHIFTED_PARAMS(m, IUTEST_TEMPLATE_TPARAM1 T) >	\
	struct IUTEST_PP_CAT(TemplateTypeList, n) { typedef TemplateTypeSel<T0> Head;						\
	typedef IUTEST_PP_CAT(TemplateTypeList, m)< IUTEST_PP_ENUM_SHIFTED_PARAMS(m, T) > Tail;				\
}

IUTEST_DECL_TEMPLATETYPELIST_(2);
IUTEST_DECL_TEMPLATETYPELIST_(3);
IUTEST_DECL_TEMPLATETYPELIST_(4);
IUTEST_DECL_TEMPLATETYPELIST_(5);
IUTEST_DECL_TEMPLATETYPELIST_(6);
IUTEST_DECL_TEMPLATETYPELIST_(7);
IUTEST_DECL_TEMPLATETYPELIST_(8);
IUTEST_DECL_TEMPLATETYPELIST_(9);
IUTEST_DECL_TEMPLATETYPELIST_(10);
IUTEST_DECL_TEMPLATETYPELIST_(11);
IUTEST_DECL_TEMPLATETYPELIST_(12);
IUTEST_DECL_TEMPLATETYPELIST_(13);
IUTEST_DECL_TEMPLATETYPELIST_(14);
IUTEST_DECL_TEMPLATETYPELIST_(15);
IUTEST_DECL_TEMPLATETYPELIST_(16);
IUTEST_DECL_TEMPLATETYPELIST_(17);
IUTEST_DECL_TEMPLATETYPELIST_(18);
IUTEST_DECL_TEMPLATETYPELIST_(19);
IUTEST_DECL_TEMPLATETYPELIST_(20);
IUTEST_DECL_TEMPLATETYPELIST_(21);
IUTEST_DECL_TEMPLATETYPELIST_(22);
IUTEST_DECL_TEMPLATETYPELIST_(23);
IUTEST_DECL_TEMPLATETYPELIST_(24);
IUTEST_DECL_TEMPLATETYPELIST_(25);
IUTEST_DECL_TEMPLATETYPELIST_(26);
IUTEST_DECL_TEMPLATETYPELIST_(27);
IUTEST_DECL_TEMPLATETYPELIST_(28);
IUTEST_DECL_TEMPLATETYPELIST_(29);
IUTEST_DECL_TEMPLATETYPELIST_(30);
IUTEST_DECL_TEMPLATETYPELIST_(31);
IUTEST_DECL_TEMPLATETYPELIST_(32);
IUTEST_DECL_TEMPLATETYPELIST_(33);
IUTEST_DECL_TEMPLATETYPELIST_(34);
IUTEST_DECL_TEMPLATETYPELIST_(35);
IUTEST_DECL_TEMPLATETYPELIST_(36);
IUTEST_DECL_TEMPLATETYPELIST_(37);
IUTEST_DECL_TEMPLATETYPELIST_(38);
IUTEST_DECL_TEMPLATETYPELIST_(39);
IUTEST_DECL_TEMPLATETYPELIST_(40);
IUTEST_DECL_TEMPLATETYPELIST_(41);
IUTEST_DECL_TEMPLATETYPELIST_(42);
IUTEST_DECL_TEMPLATETYPELIST_(43);
IUTEST_DECL_TEMPLATETYPELIST_(44);
IUTEST_DECL_TEMPLATETYPELIST_(45);
IUTEST_DECL_TEMPLATETYPELIST_(46);
IUTEST_DECL_TEMPLATETYPELIST_(47);
IUTEST_DECL_TEMPLATETYPELIST_(48);
IUTEST_DECL_TEMPLATETYPELIST_(49);
IUTEST_DECL_TEMPLATETYPELIST_(50);

#undef IUTEST_DECL_TEMPLATETYPELIST_

#endif

/**
 * @}
*/

#endif

}	// end of namespace detail

}	// end of namespace iutest

#endif
