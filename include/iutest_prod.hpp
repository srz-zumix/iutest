//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_prod.hpp
 * @brief		iris unit test production code 対応用 ファイル
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_iutest_prod_HPP_7A316C18_042D_4e48_BC31_E6AE8B6C2E28_
#define INCG_IRIS_iutest_prod_HPP_7A316C18_042D_4e48_BC31_E6AE8B6C2E28_

//======================================================================
// define
/**
 * @brief	テストから見えるように fried 登録
*/
#define IUTEST_FRIEND_TEST(test_case_name, test_name)	\
	friend class IUTEST_TEST_CLASS_NAME_(test_case_name, test_name)

namespace iutest {
namespace detail
{

//======================================================================
// struct
/** 
 * @brief	private メンバー保持構造体
*/
template<typename Tag>
struct peep
{
	static typename Tag::type	value;
};
template<typename Tag>
typename Tag::type peep<Tag>::value;

}

//======================================================================
// define
/**
 * @brief	private メンバーへのアクセス権を作成
*/
#define IUTEST_MAKE_PEEP(member_type, class_name, member_name)		\
	IUTEST_MAKE_PEEP_TAG_(member_type, class_name, member_name);	\
	template struct IUTEST_PEEP_SETTER_NAME_(class_name, member_name)<	\
		IUTEST_PEEP_TAG_NAME_(class_name, member_name), &class_name::member_name>

/**
 * @brief	private メンバーへのアクセス権を作成
*/
#define IUTEST_MAKE_SCOPED_PEEP(member_type, scope_name, class_name, member_name)		\
	IUTEST_MAKE_PEEP_TAG_(member_type, class_name, member_name);	\
	template struct IUTEST_PEEP_SETTER_NAME_(class_name, member_name)<	\
		IUTEST_PEEP_TAG_NAME_(class_name, member_name), &scope_name::class_name::member_name>

/**
 * @brief	private	メンバーへのアクセス
*/
#define IUTEST_PEEP_GET(v, class_name, member_name)		(v.*::iutest::detail::peep< IUTEST_PEEP_TAG_NAME_(class_name, member_name) >::value)

/**
 * @brief	static private	メンバーへのアクセス
*/
#define IUTEST_PEEP_STATIC_GET(class_name, member_name)	(*::iutest::detail::peep< IUTEST_PEEP_TAG_NAME_(class_name, member_name) >::value)

/**
 * @brief	private メンバーへのアクセスクラス宣言
*/
#define IUTEST_PEEP(class_name, member_name)	::iutest::Peep< class_name, IUTEST_PEEP_TAG_NAME_(class_name, member_name) >::type

/**
 * @brief	private メンバーへのアクセスクラス宣言
*/
#define IUTEST_SCOPED_PEEP(scope_name, class_name, member_name)	::iutest::Peep< scope_name::class_name, IUTEST_PEEP_TAG_NAME_(class_name, member_name) >::type

/**
 * @private
 * @{
*/
#define IUTEST_MAKE_PEEP_TAG_(member_type, class_name, member_name)	\
struct IUTEST_PEEP_TAG_NAME_(class_name, member_name) { typedef member_type type; };	\
	template<typename Tag, typename Tag::type X>struct IUTEST_PEEP_SETTER_NAME_(class_name, member_name) {	\
	IUTEST_PEEP_SETTER_NAME_(class_name, member_name)(void) { ::iutest::detail::peep<Tag>::value = X; }		\
	static IUTEST_PEEP_SETTER_NAME_(class_name, member_name)	instance;									\
	};	\
	template<typename Tag, typename Tag::type X>IUTEST_PEEP_SETTER_NAME_(class_name, member_name)<Tag, X>	\
	IUTEST_PEEP_SETTER_NAME_(class_name, member_name)<Tag, X>::instance

#define IUTEST_PEEP_TAG_NAME_(class_name, member_name)		iu_peep_tag_##class_name##_##member_name
#define IUTEST_PEEP_SETTER_NAME_(class_name, member_name)	iu_peep_set_##class_name##_##member_name
/**
 * @}
*/

#include "internal/iutest_template_util_defs.hpp"

/**
 * @brief	private	メンバーアクセスオブジェクト
*/
template<typename T, typename Tag>
class Peep
{
private:
	typedef Tag	peep_tag;
	typedef typename Tag::type	peep_type;

private:
	template<typename U, typename Type>
	class peep_member_function_impl
	{
	private:
		typedef typename type_traits::function_return_type<Type>::type return_type;

	private:
		U*	m_ptr;
	public:
		peep_member_function_impl(U* ptr) : m_ptr(ptr) {}

#if IUTEST_HAS_VARIADIC_TEMPLATES
	public:
		template<typename ...Args>
		return_type operator () (Args... args) { return ((*m_ptr).*detail::peep<peep_tag>::value)( std::forward<Args>(args)...); }
#else

#define PEEP_MEMBER_FUNC_IMPL(NUMBER)	\
	template<IUTEST_TEMPLATE_UTIL_TEMPLATES_TYPENAME(NUMBER)>return_type operator () (IUTEST_TEMPLATE_UTIL_FUNCTION_ARGS(NUMBER)) { \
		return ((*m_ptr).*detail::peep<peep_tag>::value)(IUTEST_TEMPLATE_UTIL_VALUES(NUMBER)); }

		return_type operator () (void) { return ((*m_ptr).*detail::peep<peep_tag>::value)(); }

		PEEP_MEMBER_FUNC_IMPL(1)
		PEEP_MEMBER_FUNC_IMPL(2)
		PEEP_MEMBER_FUNC_IMPL(3)
		PEEP_MEMBER_FUNC_IMPL(4)
		PEEP_MEMBER_FUNC_IMPL(5)
		PEEP_MEMBER_FUNC_IMPL(6)
		PEEP_MEMBER_FUNC_IMPL(7)
		PEEP_MEMBER_FUNC_IMPL(8)
		PEEP_MEMBER_FUNC_IMPL(9)
		PEEP_MEMBER_FUNC_IMPL(10)
		PEEP_MEMBER_FUNC_IMPL(11)
		PEEP_MEMBER_FUNC_IMPL(12)
		PEEP_MEMBER_FUNC_IMPL(13)
		PEEP_MEMBER_FUNC_IMPL(14)
		PEEP_MEMBER_FUNC_IMPL(15)
		PEEP_MEMBER_FUNC_IMPL(16)
		PEEP_MEMBER_FUNC_IMPL(17)
		PEEP_MEMBER_FUNC_IMPL(18)
		PEEP_MEMBER_FUNC_IMPL(19)
		PEEP_MEMBER_FUNC_IMPL(20)

#undef PEEP_MEMBER_FUNC_IMPL
#endif
	};
	template<typename U, typename Type, bool is_const>
	class peep_member_object_impl
	{
		typedef peep_member_object_impl<U, Type, false>	_Myt;
		typedef Type value_type;
	private:
		U*	m_ptr;
	public:
		peep_member_object_impl(U* ptr) : m_ptr(ptr) {}
	public:
		operator value_type (void) const { return (*m_ptr).*detail::peep<peep_tag>::value; }
	};
	template<typename U, typename Type>
	class peep_member_object_impl<U, Type, false>
	{
		typedef peep_member_object_impl<U, Type, false>	_Myt;
		typedef Type value_type;
	private:
		U*	m_ptr;
	public:
		peep_member_object_impl(U* ptr) : m_ptr(ptr) {}
	public:
		operator value_type (void) const { return (*m_ptr).*detail::peep<peep_tag>::value; }
		operator value_type& (void) { return (*m_ptr).*detail::peep<peep_tag>::value; }
		_Myt&	operator = (const value_type& value) { (*m_ptr).*detail::peep<peep_tag>::value = value; return *this; }
	};


	template<typename U, typename Type, bool Func>
	struct peep_member_impl
	{
		typedef peep_member_function_impl<U, Type> type;
	};
	template<typename U, typename Type>
	struct peep_member_impl<U, Type U::*, false>
	{
		typedef peep_member_object_impl<U, Type, type_traits::is_const<Type>::value> type;
	};

private:
	template<typename U, typename Type, bool Func>
	class peep_static_impl
	{
		typedef peep_static_impl<U, Type, Func>	_Myt;
		typedef typename type_traits::remove_ptr<Type>::type value_type;
	public:
		operator value_type (void) const { return *detail::peep<peep_tag>::value; }
		operator value_type& (void) { return *detail::peep<peep_tag>::value; }
		_Myt&	operator = (const value_type& value) { *detail::peep<peep_tag>::value = value; return *this; }
	};

	template<typename U, typename Type>
	class peep_static_impl<U, Type, true>
	{
	public:
		operator Type (void)	{ return *detail::peep<peep_tag>::value; }
	};
private:
	template<typename U, typename Type, bool is_member_ptr>
	struct peep_impl
	{
		typedef peep_static_impl<U, Type, type_traits::is_function_pointer<Type>::value > type;
	};
	template<typename U, typename Type>
	struct peep_impl<U, Type, true>
	{
		typedef typename peep_member_impl<U, Type, type_traits::is_member_function_pointer<Type>::value >::type type;
	};
public:
	typedef typename peep_impl<T, peep_type, type_traits::is_member_pointer<peep_type>::value >::type	type;	//!< private メンバーアクセスオブジェクト型
};

#include "internal/iutest_template_util_undef.hpp"

}

#endif
