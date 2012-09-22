//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_internal_defs.hpp
 * @brief		iris unit test utility ファイル
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
#ifndef INCG_IRIS_iutest_internal_defs_HPP_4B0AF5C2_8E8D_43ef_BFC5_F385E68F18DB_
#define INCG_IRIS_iutest_internal_defs_HPP_4B0AF5C2_8E8D_43ef_BFC5_F385E68F18DB_

//======================================================================
// include
#include "../iutest_defs.hpp"
#include "iutest_string.hpp"
#include "iutest_type_traits.hpp"
#include "iutest_pp.hpp"

#if IUTEST_HAS_HDR_CXXABI
#  include <cxxabi.h>
#endif

//======================================================================
// define

/**
 * @brief	曖昧な else 文の警告抑制
*/
#ifdef __INTEL_COMPILER 
#  define IUTEST_AMBIGUOUS_ELSE_BLOCKER_
#else
#  define IUTEST_AMBIGUOUS_ELSE_BLOCKER_	switch(::iutest::detail::AlwaysZero()) case 0: default:
#endif

#define IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(statement)	if( ::iutest::detail::AlwaysTrue() ) statement

// console
#define IUTEST_MBS_CODE_UNKOWN		0
#define IUTEST_MBS_CODE_UTF8		1
#define	IUTEST_MBS_CODE_WINDOWS31J	2
#ifndef IUTEST_MBS_CODE
#  if	defined(IUTEST_OS_WINDOWS)
#    define IUTEST_MBS_CODE	IUTEST_MBS_CODE_WINDOWS31J
#  else
#    define IUTEST_MBS_CODE	IUTEST_MBS_CODE_UTF8
#  endif
#endif


#ifndef NULL
#  ifdef	__cplusplus
#    define NULL	0
#  else
#    define NULL	(void*)0
#  endif
#endif

#ifndef IUTEST_BREAK
#  if	defined(_MSC_VER)
#    define IUTEST_BREAK()	DebugBreak()
#  elif defined(__GUNC__) && (defined (__i386__) || defined (__x86_64__))
#    define IUTEST_BREAK()	do { __asm{ int 3 } } while(::iutest::detail::AlwaysFalse())
#  elif	defined(__ARMCC_VERSION)
#    define IUTEST_BREAK()	do { __breakpoint(0xF02C); } while(::iutest::detail::AlwaysFalse())
#  else
#    define IUTEST_BREAK()	*static_cast<volatile int*>(NULL) = 1;
//#    define IUTEST_BREAK()	(void)0
#  endif
#endif

namespace iutest
{

namespace type_traits = iutest_type_traits;

namespace detail
{

//======================================================================
// class

// detail から使えるようにする
using namespace iutest_type_traits;

template<typename Ite>
struct IteratorTraits
{
	typedef typename Ite::value_type	type;
};
template<typename T>
struct IteratorTraits<T*>
{
	typedef T	type;
};
template<typename T>
struct IteratorTraits<const T*>
{
	typedef T	type;
};

/**
 * @brief	delete
*/
template<typename T>
inline void Delete(T* ptr)
{
	delete ptr;
}

/**
 * @internal
 * @brief	空オブジェクト
*/
class None {};
template<typename T>
class NoneT1 {};

/**
 * @brief	型に依存したユニークなカウンタ
*/
template<typename T>
class TypeUniqueCounter
{
	static int value;
public:
	static int count(void) { return value++; }
};
template<typename T>int TypeUniqueCounter<T>::value = 0;

template<typename T>
inline int GetTypeUniqueCounter(void) { return TypeUniqueCounter<T>::count(); }

/**
 * @internal
 * @brief	auto_ptr
*/
template<typename TN>
class auto_ptr
{
	typedef auto_ptr<TN>	_Myt;
	mutable TN*	m_ptr;
public:
	auto_ptr(const _Myt& o) : m_ptr(o.m_ptr)	{ o.m_ptr = NULL; }
	auto_ptr(TN* p=NULL)	: m_ptr(p)		{}
	~auto_ptr(void) { if( m_ptr != NULL ) delete m_ptr; }
	TN* ptr(void) { return m_ptr; }

	TN*	operator ->(void) { return m_ptr; }
};

/**
  * @internal
  * @brief	NULL リテラルかどうか
*/
struct IsNullLiteralHelper
{
	class Object;

	static char	IsNullLiteral(Object*);
	static char (&IsNullLiteral(...))[2];
};


#define IUTEST_IS_NULLLITERAL(x)	\
	(sizeof(::iutest::detail::IsNullLiteralHelper::IsNullLiteral(x)) == 1)

/**
 * @internal
 * @brief	stl コンテナかどうか
*/
struct IsContainerHelper
{
	typedef int		yes_t;
	typedef char	no_t;

	template<typename T>
	static IUTEST_CONSTEXPR yes_t	IsContainer(int , typename T::iterator* =NULL, typename T::const_iterator* =NULL) { return 0; }

	template<typename T>
	static IUTEST_CONSTEXPR no_t	IsContainer(long)	{ return 0; }
};

/**
 * @brief	enable_if
*/
template<bool B, typename T>
struct enable_if
{
	typedef T	type;
};
template<typename T>
struct enable_if<false, T> {};

template<class COND, typename T = void>
struct enable_if_t : public enable_if<COND::value, T> {};

/**
 * @brief	disable_if
*/
template<bool B, typename T>
struct disable_if : public enable_if<!B, T> {};
template<class COND, typename T = void>
struct disable_if_t : public disable_if<COND::value, T> {};

template<typename TN>
struct enabler_t
{
	static void*	value;
};
template<typename TN>void*	enabler_t<TN>::value = NULL;

typedef enabler_t<void>	enabler;

/**
 * @brief	型名の取得
*/
template<typename T>
inline std::string	GetTypeName(void)
{
#if IUTEST_HAS_RTTI
	const char* const name = typeid(T).name();

#if IUTEST_HAS_HDR_CXXABI
	using abi::__cxa_demangle;
	int status=1;
	char* const read_name = __cxa_demangle(name, 0, 0, &status);
	std::string str = status == 0 ? read_name : name;
	free(read_name);
	return str;
#else
	return name;
#endif

#else
	return "<type>";
#endif
}

#if !IUTEST_HAS_RTTI

#define GeTypeNameSpecialization(type)	template<>inline std::string GetTypeName<type>(void) { return #type; }

GeTypeNameSpecialization(char)
GeTypeNameSpecialization(unsigned char)
GeTypeNameSpecialization(short)
GeTypeNameSpecialization(unsigned short)
GeTypeNameSpecialization(int)
GeTypeNameSpecialization(unsigned int)
GeTypeNameSpecialization(long)
GeTypeNameSpecialization(unsigned long)
GeTypeNameSpecialization(float)
GeTypeNameSpecialization(double)
GeTypeNameSpecialization(bool)

#undef GeTypeNameSpecialization

#endif

//======================================================================
// function

/**
 * @brief	true を返す(警告対策用)
*/
inline IUTEST_CONSTEXPR bool	AlwaysTrue(void)
{
	return true;
}
/**
 * @brief	false を返す(警告対策用)
*/
inline IUTEST_CONSTEXPR bool	AlwaysFalse(void)	{ return !AlwaysTrue(); }

/**
 * @brief	0 を返す(警告対策用)
*/
inline IUTEST_CONSTEXPR int		AlwaysZero(void)	{ return 0; }

}	// end of namespace detail
}	// end of namespace iutest


#endif
