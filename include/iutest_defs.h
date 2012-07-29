//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_defs.h
 * @brief		iris unit test 定義 ファイル
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
#ifndef INCG_IRIS_iutest_defs_H_839F06DB_E0B6_4e6a_84F2_D99C0A44E06C_
#define INCG_IRIS_iutest_defs_H_839F06DB_E0B6_4e6a_84F2_D99C0A44E06C_

//======================================================================
// include
#include "internal/iutest_compiler.h"
#include <stdio.h>
#include <vector>
#include <algorithm>

/**
 * @defgroup	IUTEST_CONFIG	IUTEST_CONFIG
 * @brief		設定マクロ
 * @note		ユーザーが事前定義することで変更可能
 * @{
*/

#ifndef IUTEST_VPRINTF
#  define IUTEST_VPRINTF(f, a)	vprintf(f, a)	//!< vprintf 呼び出しマクロ
#endif

#ifndef IUTEST_PRINTF
#  define IUTEST_PRINTF			printf			//!< printf 呼び出しマクロ
#endif

// support
#ifndef IUTEST_HAS_PARAM_METHOD_TEST
#  ifndef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_HAS_PARAM_METHOD_TEST	1	//!< パラメタライズ関数コールテストが使用可能かどうか
#  else
#    define IUTEST_HAS_PARAM_METHOD_TEST	0	//!< パラメタライズ関数コールテストが使用可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_PARAM_TEST
#  define IUTEST_HAS_PARAM_TEST		1	//!< 値をパラメータ化したテストが使用可能かどうか
#endif

#ifndef IUTEST_HAS_TYPED_TEST
#  define IUTEST_HAS_TYPED_TEST		1	//!< 型付けテストが使用可能かどうか
#endif

#ifndef IUTEST_HAS_TYPED_TEST_P
//! 型をパラメータ化したテストが使用可能かどうか
#  if IUTEST_HAS_TYPED_TEST && !defined(IUTEST_NO_VARIADIC_MACROS)
#    define IUTEST_HAS_TYPED_TEST_P	1
#  else
#    define IUTEST_HAS_TYPED_TEST_P	0
#  endif
#endif

#ifndef IUTEST_TYPED_TEST_P_STRICT
#  define IUTEST_TYPED_TEST_P_STRICT	1	//!< より厳しい構文チェックを行うかどうか
#endif

#if IUTEST_HAS_TYPED_TEST_P
#  if IUTEST_TYPED_TEST_P_STRICT
#    include <set>
#  endif
#endif

#ifndef IUTEST_HAS_COMBINE
//! ::iutest::Combine が使用可能かどうか
#  if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_TUPLE
#    define IUTEST_HAS_COMBINE		1
#  else
#    define IUTEST_HAS_COMBINE		0
#  endif
#endif

#ifndef IUTEST_HAS_VARIADIC_COMBINE
#  if IUTEST_HAS_COMBINE && IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_STD_TUPLE
#    define IUTEST_HAS_VARIADIC_COMBINE	1	//!< 可変長引数に対応した Combine が使用可能かどうか
#  else
#    define IUTEST_HAS_VARIADIC_COMBINE	0	//!< 可変長引数に対応した Combine が使用可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_PEEP
#  define IUTEST_HAS_PEEP			1	//!< private メンバーへのアクセスマクロが使用可能かどうか
#endif

#ifndef IUTEST_HAS_PEEP_FUNC
#  if IUTEST_HAS_PEEP && IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_MEMBER_FUNCTION
#    define IUTEST_HAS_PEEP_FUNC	1	//!< private メンバー関数へのアクセスが可能かどうか
#  else
#    define IUTEST_HAS_PEEP_FUNC	0	//!< private メンバー関数へのアクセスが可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_PEEP_STATIC_FUNC
#  if IUTEST_HAS_PEEP && IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_STATIC_MEMBER_FUNCTION
#    define IUTEST_HAS_PEEP_STATIC_FUNC	1	//!< private static メンバー関数へのアクセスが可能かどうか
#  else
#    define IUTEST_HAS_PEEP_STATIC_FUNC	0	//!< private static メンバー関数へのアクセスが可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_GENRAND
#  define IUTEST_HAS_GENRAND		1	//!< テストごとの genrand 関数が使用可能かどうか
#endif

#ifndef IUTEST_HAS_FOPEN
#  define IUTEST_HAS_FOPEN			1	//!< fopen が使用可能かどうか
#endif

#ifndef IUTEST_HAS_CTIME
#  if	defined(IUTEST_OS_WINDOWS_MOBILE)
#    define IUTEST_HAS_CTIME		0	//!< time 関数が使用可能かどうか
#  else
#    define IUTEST_HAS_CTIME		1	//!< time 関数が使用可能かどうか
#  endif
#endif

#ifndef IUTEST_HAS_STRINGSTREAM
#  define IUTEST_HAS_STRINGSTREAM	1	//!< std::stringstream が使用可能かどうか
#endif

#ifndef IUTEST_USE_STRSTREAM
#  define IUTEST_USE_STRSTREAM		0	//!< std::strstream が使用可能かどうか
#endif

#ifndef IUTEST_THROW_ON_ASSERT_FAILURE
/**
 * @brief	ASSERT マクロで失敗時に例外を throw します。
 * @note	サブ関数にアサーションを記述しても、その時点でテストが中断されるようになります
*/
#  define IUTEST_THROW_ON_ASSERT_FAILURE	0
#endif

#ifndef IUTEST_HAS_GETTIMEOFDAY
#  define IUTEST_HAS_GETTIMEOFDAY	0	//!< gettimeofday 関数が使用可能かどうか
#endif

#ifndef IUTEST_HAS_CLOCK
#  define IUTEST_HAS_CLOCK			0	//!< clock 関数が使用可能かどうか
#endif

// Doxygen 用
#ifdef IUTEST_BUILD_DOXYGEN
#define IUTEST_GetMillisec()	//!< 現在時刻のミリ秒取得関数を独自定義
#endif

/**
 * @}
*/

#if defined(_IUTEST_DEBUG)
#include "internal/iutest_debug.h"
#endif

namespace iutest
{

//======================================================================
// struct
namespace detail
{

/**
 * @brief	type_least_t
*/
template<int SIZE>
struct type_least_t {};

/** type_least_t<1> */
template<>
struct type_least_t<1>
{
	typedef char				Int;
	typedef unsigned char		UInt;
};

/** type_least_t<2> */
template<>
struct type_least_t<2>
{
	typedef short				Int;
	typedef unsigned short		UInt;
};

/** type_least_t<4> */
template<>
struct type_least_t<4>
{
	typedef int					Int;
	typedef unsigned int		UInt;
};

/** type_least_t<8> */
template<>
struct type_least_t<8>
{
#if defined(_MSC_VER)
	typedef __int64				Int;
	typedef unsigned __int64	UInt;
#else
	typedef long long			Int;
	typedef unsigned long long	UInt;
#endif
};

}

/**
 * @brief	浮動小数点数
*/
template<typename RawType>
class floating_point
{
private:
	typedef floating_point<RawType>	_Myt;

	template<typename T, typename DMY>
	struct impl				 { typedef detail::type_least_t<4>	type; };
	template<typename DMY>
	struct impl<double, DMY> { typedef detail::type_least_t<8>	type; };

	template<typename T, typename DMY>
	struct ieee 
	{
		static const int EXP	= 8;
		static const int FRAC	= 23;
	};
	template<typename DMY>
	struct ieee<double, DMY>
	{
		static const int EXP	= 11;
		static const int FRAC	= 52;
	};

	typedef typename impl<RawType, void>::type	type;
	typedef typename type::Int	Int;
	typedef typename type::UInt	UInt;
	union FInt
	{
		Int		iv;
		UInt	uv;
		RawType	fv;
	};

	static const int EXP	= ieee<RawType, void>::EXP;
	static const int FRAC	= ieee<RawType, void>::FRAC;

public:
	/**
	 * @brief	コンストラクタ
	*/
	floating_point(void)
	{
		m_v.uv = 0;
	}

	/**
	 * @brief	コンストラクタ
	 * @param [in]	f	= 浮動小数点数
	*/
	floating_point(RawType f)
	{
		m_v.fv = f;
	}

	/**
	 * @brief	コンストラクタ
	*/
	floating_point(const _Myt& rhs)
	{
		m_v.uv = rhs.m_v.uv;
	}

public:
	/**
	 * @brief	浮動小数点数がほぼ一致するかどうか
	 * @sa		http://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
	*/
	bool	AlmostEquals(const _Myt& rhs) const
	{
		const Int v1 = m_v.iv < 0 ? ~m_v.iv + 1 : m_v.iv;
		const Int v2 = rhs.m_v.iv < 0 ? ~rhs.m_v.iv + 1 : rhs.m_v.iv;
		const Int diff = (v1 > v2) ? v1 - v2 : v2 - v1;
		if( diff <= kMaxUlps ) return true;
		return false;
	}

public:
	/**
	 * @brief	ビット列の取得
	*/
	UInt	bit(void) const	{ return m_v.uv; }

	/**
	 * @brief	raw データの取得
	*/
	RawType	raw(void) const	{ return m_v.fv; }

public:
	//! ＋ inf
	static _Myt	PINF(void)
	{
		_Myt f;
		f.m_v.uv = ((1<<EXP)-1);
		f.m_v.uv <<= FRAC;
		return f;
	}
	//! － inf
	static _Myt	NINF(void)
	{
		_Myt f = PINF();
		f.m_v.uv |= static_cast<UInt>(1u) << (EXP+FRAC);
		return f;
	}
	//! ＋ nan
	static _Myt	PNAN(void)
	{
		_Myt f = PINF();
		f.m_v.uv |= 1;
		return f;
	}
	//! － nan
	static _Myt	NNAN(void)
	{
		_Myt f = NINF();
		f.m_v.uv |= 1;
		return f;
	}
	//! ＋ qnan
	static _Myt	PQNAN(void)
	{
		_Myt f;
		f.m_v.uv = ((1<<(EXP+1))-1);
		f.m_v.uv <<= FRAC-1;
		return f;
	}
	//! － qnan
	static _Myt	NQNAN(void)
	{
		_Myt f = PQNAN();
		f.m_v.uv |= static_cast<UInt>(1u) << (EXP+FRAC);
		return f;
	}

public:
	operator RawType (void) const	{ return m_v.fv; }
	_Myt&	operator = (RawType f)	{ m_v.fv = f; return *this; }

	bool	operator == (const _Myt& rhs) const	{ return m_v.uv == rhs.m_v.uv; }

private:
	static const Int	kMaxUlps = 4;
private:
	FInt	m_v;
};

namespace internal
{

typedef void*	TypeId;		//!< テスト識別型

namespace helper
{

//======================================================================
// struct
/**
 * @brief	TypeId Generator Implementation
*/
template<typename TN>
struct TestTypeIdHelper { public: static bool _dummy; };

template<typename TN>bool TestTypeIdHelper<TN>::_dummy = false;

}

//======================================================================
// function
/**
  * @internal
  * @brief	TypeId Generator
*/
template<typename TN>
inline IUTEST_CONSTEXPR TypeId	GetTypeId(void)
{
	return &(helper::TestTypeIdHelper<TN>::_dummy);
}

/**
  * @internal
  * @brief	TypeId Generator
*/
inline IUTEST_CONSTEXPR TypeId	GetTestTypeId(void)
{
	return 0;
}

}

//======================================================================
// typedef
typedef detail::type_least_t<4>::Int	Int32;	//!< 32 bit 符号付き整数型
typedef detail::type_least_t<4>::UInt	UInt32;	//!< 32 bit 符号なし整数型
typedef detail::type_least_t<8>::Int	Int64;	//!< 64 bit 符号付き整数型
typedef detail::type_least_t<8>::UInt	UInt64;	//!< 64 bit 符号なし整数型

typedef internal::TypeId TestTypeId;	//!< テスト識別型

typedef void (*SetUpMethod)(void);		//!< SetUp 関数型
typedef void (*TearDownMethod)(void);	//!< TearDown 関数型

typedef detail::type_least_t<8>::UInt	TimeInMillisec;	//!< ミリ秒単位を扱う型
typedef detail::type_least_t<8>::Int	BiggestInt;		//!< Biggest Int

}	// end of namespace iutest

#endif
