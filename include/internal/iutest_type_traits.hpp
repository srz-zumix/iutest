//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_type_traits.hpp
 * @brief		iris unit test type traits ƒtƒ@ƒCƒ‹
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
#ifndef INCG_IRIS_iutest_type_traits_HPP_6F091F15_784A_4f50_BD18_B8F67C5AF0CF_
#define INCG_IRIS_iutest_type_traits_HPP_6F091F15_784A_4f50_BD18_B8F67C5AF0CF_

//======================================================================
// include

namespace iutest_type_traits
{

//======================================================================
// struct

/**
 * @brief	bool constant
*/
template<bool B>
struct bool_constant
{
	static const bool	value = B;
};
template<bool B>const bool bool_constant<B>::value;

typedef bool_constant<true>		true_type;
typedef bool_constant<false>	false_type;


/**
 * @brief	remove_const
*/
template<typename T>
class remove_const
{
	template<typename U>
	struct impl { typedef U type; };
	template<typename U>
	struct impl<const U> { typedef U type; };
public:
	typedef typename impl<T>::type	type;
};

/**
 * @brief	remove_volatile
*/
template<typename T>
class remove_volatile
{
	template<typename U>
	struct impl { typedef U type; };
	template<typename U>
	struct impl<volatile U> { typedef U type; };
public:
	typedef typename impl<T>::type	type;
};

/**
 * @brief	remove_cv
*/
template<typename T>
class remove_cv
{
public:
	typedef typename remove_const< typename remove_volatile<T>::type >::type	type;
};

/**
 * @brief	remove_ptr
*/
template<typename T>
struct remove_ptr		{ typedef T type; };
template<typename T>
struct remove_ptr<T*>	{ typedef T type; };

namespace helper
{

template<typename T>
class is_pointer_helper
{
	template<typename U, typename TMP> struct impl { typedef false_type type; };
	template<typename U, typename TMP> struct impl<U*, TMP> { typedef true_type type; };
	typedef typename remove_cv<T>::type	rmcv_type;
public:
	typedef typename impl<rmcv_type, void>::type type;
};

template<typename T>
class is_reference_helper
{
	template<typename U, typename TMP> struct impl { typedef false_type type; };
	template<typename U, typename TMP> struct impl<U&, TMP> { typedef true_type type; };
	typedef typename remove_cv<T>::type	rmcv_type;
public:
	typedef typename impl<rmcv_type, void>::type type;
};

}

/**
 * @brief	is_pointer
*/
template<typename T>
struct is_pointer : public helper::is_pointer_helper<T>::type {};

/**
 * @brief	is_reference
*/
template<typename T>
struct is_reference : public helper::is_reference_helper<T>::type {};

/**
 * @brief	is_same
*/
template<typename T1, typename T2>
struct is_same : public false_type {};
template<typename T>
struct is_same<T, T> : public true_type {};

namespace helper
{
template<typename T>
class is_void_helper
{
	template<typename U, typename TMP> struct impl { typedef false_type type; };
	template<typename TMP> struct impl<void, TMP> { typedef true_type type; };
	typedef typename remove_cv<T>::type	rmcv_type;
public:
	typedef typename impl<rmcv_type, void>::type type;
};

}

/**
 * @brief	is_void
*/
template<typename T>
class is_void : public helper::is_void_helper<T>::type {};

/**
 * @brief	is_const
*/
template<typename T>
struct is_const : public false_type {};
template<typename T>
struct is_const<T const> : public true_type {};

/**
 * @brief	is convertible
*/
template<typename From, typename To>
class is_convertible
{
	static From	MakeFrom(void);

	static char	IsConvertibleHelper(To);
	static char (&IsConvertibleHelper(...))[2];
public:
	static const bool value = (sizeof(IsConvertibleHelper(is_convertible::MakeFrom())) == 1);
};

template<typename From, typename To>
const bool is_convertible<From, To>::value;


#ifndef IUTEST_HAS_RVALUE_REFS
#  if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#    define IUTEST_HAS_RVALUE_REFS	1
#  elif	defined(_MSC_VER) && (_MSC_VER >= 1700)
#    define IUTEST_HAS_RVALUE_REFS	1
#  endif
#endif

#ifndef IUTEST_HAS_RVALUE_REFS
#  define IUTEST_HAS_RVALUE_REFS	0
#endif

/**
 * @brief	add rvalue reference
*/
template<typename T>
class add_revalue_reference
{
	template<typename U, bool b>struct impl { typedef U type; };

#if IUTEST_HAS_RVALUE_REFS
	template<typename U>struct impl<U, true>
	{
		typedef U&& type;
	};
#endif

public:
	typedef typename impl<T, !is_void<T>::value && !is_reference<T>::value >::type type;
};

#include "iutest_template_util_defs.hpp"

/**
 * @brief	is function pointer
*/
template<typename T>
class is_function_pointer
{
	template<typename U>
	struct impl : public false_type {};

#if IUTEST_HAS_VARIADIC_TEMPLATES
	template<typename R, typename ...Args>
	struct impl<R (*)(Args...)> : public true_type {};
	template<typename R, typename ...Args>
	struct impl<R (*)(Args..., ...)> : public true_type {};

#else
	template<typename R>
	struct impl<R (*)()> : public true_type {};
	template<typename R>
	struct impl<R (*)(...)> : public true_type {};

#define IS_FUNCTION_PTR_IMPL(NUMBER)	\
	template<typename R, IUTEST_TEMPLATE_UTIL_TEMPLATES##NUMBER>struct impl<R (*)(IUTEST_TEMPLATE_UTIL_ARGS##NUMBER)> : public true_type {};	\
	template<typename R, IUTEST_TEMPLATE_UTIL_TEMPLATES##NUMBER>struct impl<R (*)(IUTEST_TEMPLATE_UTIL_ARGS##NUMBER, ...)> : public true_type {}

	IS_FUNCTION_PTR_IMPL(1);
	IS_FUNCTION_PTR_IMPL(2);
	IS_FUNCTION_PTR_IMPL(3);
	IS_FUNCTION_PTR_IMPL(4);
	IS_FUNCTION_PTR_IMPL(5);
	IS_FUNCTION_PTR_IMPL(6);
	IS_FUNCTION_PTR_IMPL(7);
	IS_FUNCTION_PTR_IMPL(8);
	IS_FUNCTION_PTR_IMPL(9);
	IS_FUNCTION_PTR_IMPL(10);
	IS_FUNCTION_PTR_IMPL(11);
	IS_FUNCTION_PTR_IMPL(12);
	IS_FUNCTION_PTR_IMPL(13);
	IS_FUNCTION_PTR_IMPL(14);
	IS_FUNCTION_PTR_IMPL(15);
	IS_FUNCTION_PTR_IMPL(16);
	IS_FUNCTION_PTR_IMPL(17);
	IS_FUNCTION_PTR_IMPL(18);
	IS_FUNCTION_PTR_IMPL(19);
	IS_FUNCTION_PTR_IMPL(20);

#undef IS_FUNCTION_PTR_IMPL

#endif

public:
	enum { value = impl< typename remove_cv<T>::type >::value };
};

/**
 * @brief	is member function pointer
*/
template<typename T>
class is_member_function_pointer
{
	template<typename U>
	struct impl : public false_type {};

#if IUTEST_HAS_VARIADIC_TEMPLATES

#define IS_MEMBER_FUNCTION_PTR_CV_IMPL(CV)	\
	template<typename R, typename U, typename ...Args>			\
	struct impl<R (U::*)(Args...) CV> : public true_type {};	\
	template<typename R, typename U, typename ...Args>			\
	struct impl<R (U::*)(Args..., ...) CV> : public true_type {}

	IS_MEMBER_FUNCTION_PTR_CV_IMPL();
	IS_MEMBER_FUNCTION_PTR_CV_IMPL(const);
	IS_MEMBER_FUNCTION_PTR_CV_IMPL(volatile);
	IS_MEMBER_FUNCTION_PTR_CV_IMPL(const volatile);

#undef IS_MEMBER_FUNCTION_PTR_CV_IMPL

#else

#define IS_MEMBER_FUNCTION_PTR_VOID_CV_IMPL(CV)	\
	template<typename R, typename U>struct impl<R (U::*)() CV> : public true_type {};	\
	template<typename R, typename U>struct impl<R (U::*)(...) CV> : public true_type {}

	template<typename R, typename U>struct impl<R (U::*)()> : public true_type {};
	template<typename R, typename U>struct impl<R (U::*)(...)> : public true_type {};
	IS_MEMBER_FUNCTION_PTR_VOID_CV_IMPL(const);
	IS_MEMBER_FUNCTION_PTR_VOID_CV_IMPL(volatile);
	IS_MEMBER_FUNCTION_PTR_VOID_CV_IMPL(const volatile);

#undef IS_MEMBER_FUNCTION_PTR_VOID_CV_IMPL

#define IS_MEMBER_FUNCTION_PTR_IMPL(NUMBER)	\
	IS_MEMBER_FUNCTION_PTR_IMPL2(NUMBER, );	\
	IS_MEMBER_FUNCTION_PTR_IMPL2(NUMBER, const);	\
	IS_MEMBER_FUNCTION_PTR_IMPL2(NUMBER, volatile);	\
	IS_MEMBER_FUNCTION_PTR_IMPL2(NUMBER, const volatile)

#define IS_MEMBER_FUNCTION_PTR_IMPL2(NUMBER, CV)	\
	template<typename R, typename U, IUTEST_TEMPLATE_UTIL_TEMPLATES##NUMBER>struct impl<R (U::*)(IUTEST_TEMPLATE_UTIL_ARGS##NUMBER) CV> : public true_type {};	\
	template<typename R, typename U, IUTEST_TEMPLATE_UTIL_TEMPLATES##NUMBER>struct impl<R (U::*)(IUTEST_TEMPLATE_UTIL_ARGS##NUMBER, ...) CV> : public true_type {}

	IS_MEMBER_FUNCTION_PTR_IMPL(1);
	IS_MEMBER_FUNCTION_PTR_IMPL(2);
	IS_MEMBER_FUNCTION_PTR_IMPL(3);
	IS_MEMBER_FUNCTION_PTR_IMPL(4);
	IS_MEMBER_FUNCTION_PTR_IMPL(5);
	IS_MEMBER_FUNCTION_PTR_IMPL(6);
	IS_MEMBER_FUNCTION_PTR_IMPL(7);
	IS_MEMBER_FUNCTION_PTR_IMPL(8);
	IS_MEMBER_FUNCTION_PTR_IMPL(9);
	IS_MEMBER_FUNCTION_PTR_IMPL(10);
	IS_MEMBER_FUNCTION_PTR_IMPL(11);
	IS_MEMBER_FUNCTION_PTR_IMPL(12);
	IS_MEMBER_FUNCTION_PTR_IMPL(13);
	IS_MEMBER_FUNCTION_PTR_IMPL(14);
	IS_MEMBER_FUNCTION_PTR_IMPL(15);
	IS_MEMBER_FUNCTION_PTR_IMPL(16);
	IS_MEMBER_FUNCTION_PTR_IMPL(17);
	IS_MEMBER_FUNCTION_PTR_IMPL(18);
	IS_MEMBER_FUNCTION_PTR_IMPL(19);
	IS_MEMBER_FUNCTION_PTR_IMPL(20);

#undef IS_MEMBER_FUNCTION_PTR_IMPL
#undef IS_MEMBER_FUNCTION_PTR_IMPL2

#endif

public:
	enum { value = impl< typename remove_cv<T>::type >::value };
};

/**
 * @brief	is member pointer
*/
template<typename T>
class is_member_pointer
{
	template<typename U>
	struct impl : public false_type {};
	template<typename U, typename C>
	struct impl<U C::*> : public true_type {};

public:
	enum { value = impl< typename remove_cv<T>::type >::value || is_member_function_pointer<T>::value ? true : false };
};

/**
 * @brief	function return type
*/
template<typename T>
class function_return_type
{
	template<typename U> struct impl {};

#if IUTEST_HAS_VARIADIC_TEMPLATES
	template<typename R, typename ...Args>struct impl<R (*)(Args...)>		{ typedef R type; };
	template<typename R, typename ...Args>struct impl<R (*)(Args..., ...)>	{ typedef R type; };
	template<typename R, typename U, typename ...Args>struct impl<R (U::*)(Args...)>		{ typedef R type; };
	template<typename R, typename U, typename ...Args>struct impl<R (U::*)(Args..., ...)>	{ typedef R type; };

#define FUNCTION_RETURN_TYPE_CV_IMPL(CV)	\
	template<typename R, typename U, typename ...Args>struct impl<R (U::*)(Args...) CV>		{ typedef R type; };	\
	template<typename R, typename U, typename ...Args>struct impl<R (U::*)(Args..., ...) CV>{ typedef R type; }

	FUNCTION_RETURN_TYPE_CV_IMPL(const);
	FUNCTION_RETURN_TYPE_CV_IMPL(volatile);
	FUNCTION_RETURN_TYPE_CV_IMPL(const volatile);
#undef FUNCTION_RETURN_TYPE_CV_IMPL

#else

#define FUNCTION_RETURN_TYPE_IMPL(NUMBER)	\
	template<typename R, IUTEST_TEMPLATE_UTIL_TEMPLATES##NUMBER>struct impl<R (*)(IUTEST_TEMPLATE_UTIL_ARGS##NUMBER)>	\
	{ typedef R type; };	\
	template<typename R, IUTEST_TEMPLATE_UTIL_TEMPLATES##NUMBER>struct impl<R (*)(IUTEST_TEMPLATE_UTIL_ARGS##NUMBER, ...)>	\
	{ typedef R type; };	\
	FUNCTION_RETURN_TYPE_IMPL2(NUMBER, );	\
	FUNCTION_RETURN_TYPE_IMPL2(NUMBER, const);	\
	FUNCTION_RETURN_TYPE_IMPL2(NUMBER, volatile);	\
	FUNCTION_RETURN_TYPE_IMPL2(NUMBER, const volatile)	\

#define FUNCTION_RETURN_TYPE_IMPL2(NUMBER, CV)	\
	template<typename R, typename U, IUTEST_TEMPLATE_UTIL_TEMPLATES##NUMBER>struct impl<R (U::*)(IUTEST_TEMPLATE_UTIL_ARGS##NUMBER) CV>	\
	{ typedef R type; };	\
	template<typename R, typename U, IUTEST_TEMPLATE_UTIL_TEMPLATES##NUMBER>struct impl<R (U::*)(IUTEST_TEMPLATE_UTIL_ARGS##NUMBER, ...) CV>	\
	{ typedef R type; }

	template<typename R>struct impl<R (*)(void)>	{ typedef R type; };
	template<typename R, typename U>struct impl<R (U::*)(void)>	{ typedef R type; };

#define FUNCTION_RETURN_TYPE_VOID_IMPL(CV)	\
	template<typename R, typename U>struct impl<R (U::*)(void) CV>	{ typedef R type; }

	FUNCTION_RETURN_TYPE_VOID_IMPL(const);
	FUNCTION_RETURN_TYPE_VOID_IMPL(volatile);
	FUNCTION_RETURN_TYPE_VOID_IMPL(const volatile);

#undef FUNCTION_RETURN_TYPE_VOID_IMPL

	FUNCTION_RETURN_TYPE_IMPL(1);
	FUNCTION_RETURN_TYPE_IMPL(2);
	FUNCTION_RETURN_TYPE_IMPL(3);
	FUNCTION_RETURN_TYPE_IMPL(4);
	FUNCTION_RETURN_TYPE_IMPL(5);
	FUNCTION_RETURN_TYPE_IMPL(6);
	FUNCTION_RETURN_TYPE_IMPL(7);
	FUNCTION_RETURN_TYPE_IMPL(8);
	FUNCTION_RETURN_TYPE_IMPL(9);
	FUNCTION_RETURN_TYPE_IMPL(10);
	FUNCTION_RETURN_TYPE_IMPL(11);
	FUNCTION_RETURN_TYPE_IMPL(12);
	FUNCTION_RETURN_TYPE_IMPL(13);
	FUNCTION_RETURN_TYPE_IMPL(14);
	FUNCTION_RETURN_TYPE_IMPL(15);
	FUNCTION_RETURN_TYPE_IMPL(16);
	FUNCTION_RETURN_TYPE_IMPL(17);
	FUNCTION_RETURN_TYPE_IMPL(18);
	FUNCTION_RETURN_TYPE_IMPL(19);
	FUNCTION_RETURN_TYPE_IMPL(20);

#undef FUNCTION_RETURN_TYPE_IMPL
#undef FUNCTION_RETURN_TYPE_IMPL2

#endif

public:
	typedef typename impl< typename remove_cv<T>::type >::type type;
};

#include "iutest_template_util_undef.hpp"

}	// end of namespace iutest_type_traits


#endif
