//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_random.hpp
 * @brief		iris unit test 乱数生成器 定義 ファイル
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
#ifndef INCG_IRIS_iutest_random_HPP_89F260D7_9145_4b50_A8F0_B7A2696121B6_
#define INCG_IRIS_iutest_random_HPP_89F260D7_9145_4b50_A8F0_B7A2696121B6_

//======================================================================
// include
#include "iutest_time.hpp"

#if IUTEST_HAS_CXX_HDR_RANDOM
#  include <random>
#endif

namespace iutest {
namespace detail
{

//======================================================================
// class
/**
 * @brief	乱数生成器クラス
*/
class iuRandom
{
#if IUTEST_HAS_CXX_HDR_RANDOM && 0
	typedef ::std::mt19937 Engine;
#else
	class Engine
	{
	public:
		typedef unsigned int result_type;
	public:
		explicit Engine(unsigned int seed=0)
		{
			m_v4 = seed;
			m_v3 = 1812433253 * ((m_v4 ^ (m_v4>>30)) + 1);
			m_v2 = 1812433253 * ((m_v3 ^ (m_v3>>30)) + 2);
			m_v1 = 1812433253 * ((m_v2 ^ (m_v2>>30)) + 3);
		}
		result_type operator ()(void)
		{
			const unsigned int t = (m_v1 ^ (m_v1<<11));
			m_v1 = m_v2;
			m_v2 = m_v3;
			m_v3 = m_v4;
			m_v4 = (m_v4 ^ (m_v4>>19)) ^ (t ^ (t>>8));
			return m_v4;
		}
		static IUTEST_CXX_CONSTEXPR result_type (min)(void) { return 0; }
		static IUTEST_CXX_CONSTEXPR result_type (max)(void) { return static_cast<result_type>(-1); }
	private:
		unsigned int m_v1, m_v2, m_v3, m_v4;
	};
#endif

	Engine m_engine;

public:
	typedef unsigned int result_type;

	static IUTEST_CXX_CONSTEXPR result_type (min)(void) { return (Engine::min)(); }
	static IUTEST_CXX_CONSTEXPR result_type (max)(void) { return (Engine::max)(); }
public:
	iuRandom(void)
	{
		init();
	}

	iuRandom(unsigned int seed)
	{
		init(seed);
	}

public:
	/**
	 * @brief	初期化
	 * @details	時間でシードを決定
	*/
	void	init(void)
	{
		init(GetIndefiniteValue());
	}
	/**
	 * @brief	初期化
	 * @param [in]	seed	= シード
	*/
	void	init(unsigned int seed)
	{
		m_engine = Engine(seed);
	}

public:
	/**
	 * @brief	乱数の生成
	 * @return	乱数
	*/
	result_type genrand(void)
	{
		return m_engine();
	}

	/**
	 * @brief	乱数の生成
	 * @details	[0,max) の乱数を生成
	 * @param [in]	max	= 上限値
	 * @return	乱数
	*/
	result_type genrand(unsigned int max)
	{
#if IUTEST_HAS_CXX_HDR_RANDOM
		return ::std::uniform_int_distribution<unsigned int>(0, max)(m_engine);
#else
		return genrand()%max;
#endif
	}

	/**
	 * @brief	乱数の生成
	 * @details	[0,1] の乱数を生成
	 * @return	乱数
	*/
	float				genrandf(void)
	{
#if IUTEST_HAS_CXX_HDR_RANDOM
		return ::std::uniform_real_distribution<float>(0.0f, 1.0f)(m_engine);
#else
		return static_cast<float>(genrand())*(1.0f/4294967295.0f);
#endif
	}

	/**
	 * @brief	乱数の生成
	 * @return	乱数
	*/
	template<typename T>
	T genrand(IUTEST_EXPLICIT_TEMPLATE_TYPE_(T))
	{
		return static_cast<T>(genrand( static_cast<unsigned int>( static_cast<T>(-1) ) ));
	}

#if IUTEST_HAS_CLASS_MEMBER_TEMPLATE_SPECIALIZATION && (defined(_MSC_VER) && _MSC_VER < 1300)
	template<>float		genrand<float>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(float))	{ return genrandf(); }
	template<>double	genrand<double>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(double))	{ return static_cast<double>(genrandf()); }
#endif

public:
	result_type operator ()(void)
	{
		return genrand();
	}
	result_type operator ()(unsigned int max)
	{
		return genrand(max);
	}
};

#if !(defined(_MSC_VER) && _MSC_VER < 1300)

template<> inline Int64		iuRandom::genrand<Int64>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(Int64))		{ return (static_cast<Int64>(genrand()) << 32) | genrand(); }
template<> inline UInt64	iuRandom::genrand<UInt64>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(UInt64))	{ return (static_cast<UInt64>(genrand()) << 32) | genrand(); }
template<> inline float		iuRandom::genrand<float>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(float))		{ return genrandf(); }
template<> inline double	iuRandom::genrand<double>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(double))	{ return static_cast<double>(genrandf()); }

#endif

}	// end of namespace detail
}	// end of namespace iutest

#endif
