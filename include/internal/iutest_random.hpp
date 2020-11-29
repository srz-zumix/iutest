//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_random.hpp
 * @brief       iris unit test 乱数生成器 定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_RANDOM_HPP_89F260D7_9145_4B50_A8F0_B7A2696121B6_
#define INCG_IRIS_IUTEST_RANDOM_HPP_89F260D7_9145_4B50_A8F0_B7A2696121B6_

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
 * @brief   乱数生成器クラス
*/
class iuRandom
{
#if IUTEST_HAS_CXX_HDR_RANDOM && defined(IUTEST_USE_RANDOM_ENGINE_TYPENAME)
    typedef IUTEST_USE_RANDOM_ENGINE_TYPENAME Engine;
#else
    class Engine
    {
    public:
        typedef unsigned int result_type;
    public:
        explicit Engine(unsigned int s=0) IUTEST_CXX_NOEXCEPT_SPEC
        {
            seed(s);
        }
        result_type operator ()()
        {
            return gen();
        }
        bool operator == (const Engine& rhs)
        {
            return m_v1 == rhs.m_v1 && m_v2 == rhs.m_v2 && m_v3 == rhs.m_v3 && m_v4 == rhs.m_v4;
        }
        bool operator != (const Engine& rhs)
        {
            return m_v1 != rhs.m_v1 || m_v2 != rhs.m_v2 || m_v3 != rhs.m_v3 || m_v4 != rhs.m_v4;
        }
    public:
        void seed(unsigned int s)
        {
            m_v4 = s;
            m_v3 = 1812433253 * ((m_v4 ^ (m_v4 >> 30)) + 1);
            m_v2 = 1812433253 * ((m_v3 ^ (m_v3 >> 30)) + 2);
            m_v1 = 1812433253 * ((m_v2 ^ (m_v2 >> 30)) + 3);
        }
        void discard(unsigned int z)
        {
            for(unsigned int i=0; i < z; ++i)
            {
                gen();
            }
        }
    public:
#if !defined(IUTEST_NO_INCLASS_MEMBER_INITIALIZATION)
        static IUTEST_CXX_CONSTEXPR_OR_CONST result_type _Min = 0;
        static IUTEST_CXX_CONSTEXPR_OR_CONST result_type _Max = static_cast<result_type>(-1);
#endif

        static IUTEST_CXX_CONSTEXPR result_type (min)() { return 0; }
        static IUTEST_CXX_CONSTEXPR result_type (max)() { return static_cast<result_type>(-1); }

    private:
        result_type gen()
        {
            const unsigned int t = (m_v1 ^ (m_v1 << 11));
            m_v1 = m_v2;
            m_v2 = m_v3;
            m_v3 = m_v4;
            m_v4 = (m_v4 ^ (m_v4 >> 19)) ^ (t ^ (t >> 8));
            return m_v4;
        }
    private:
        unsigned int m_v1, m_v2, m_v3, m_v4;
    };
#endif

    Engine m_engine;

public:
    typedef unsigned int result_type;

    static IUTEST_CXX_CONSTEXPR result_type (min)() { return (Engine::min)(); }
    static IUTEST_CXX_CONSTEXPR result_type (max)() { return (Engine::max)(); }

#if defined(__clang__) && (IUTEST_CLANG_MAJOR < 3 || (IUTEST_CLANG_MAJOR == 3 && IUTEST_CLANG_MINOR < 3))
    static IUTEST_CXX_CONSTEXPR_OR_CONST result_type _Min = Engine::_Min;
    static IUTEST_CXX_CONSTEXPR_OR_CONST result_type _Max = Engine::_Max;
#endif

public:
    iuRandom()
    {
        init();
    }

    explicit iuRandom(unsigned int seed)
    {
        init(seed);
    }

public:
    /**
     * @brief   初期化
     * @details 時間でシードを決定
    */
    void init()
    {
        init(GetIndefiniteValue());
    }
    /**
     * @brief   初期化
     * @param [in]  seed    = シード
    */
    void init(unsigned int seed)
    {
        m_engine = Engine(seed);
    }

public:
    /**
     * @brief   乱数の生成
     * @return  乱数
    */
    result_type genrand()
    {
        return m_engine();
    }

    /**
     * @brief   乱数の生成
     * @details [0,max) の乱数を生成
     * @param [in]  max = 上限値
     * @return  乱数
    */
    result_type genrand(unsigned int max)
    {
#if IUTEST_HAS_CXX_HDR_RANDOM
        ::std::uniform_int_distribution<unsigned int> d(0, max-1);
        return d(m_engine);
#else
        return genrand()%max;
#endif
    }

    /**
     * @brief   乱数の生成
     * @details [0,max) の乱数を生成
     * @param [in]  max = 上限値
     * @return  乱数
    */
    template<typename T>
    T genrand(T max)
    {
#if IUTEST_HAS_CXX_HDR_RANDOM
        ::std::uniform_int_distribution<T> d(0, max-1);
        return d(m_engine);
#else
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
        return genrand<T>()%max;
#else
        return genrand(detail::explicit_type<result_type>())%max;
#endif
#endif
    }

    /**
     * @brief   乱数の生成
     * @details [0,1] の乱数を生成
     * @return  乱数
    */
    float genrandf()
    {
#if IUTEST_HAS_CXX_HDR_RANDOM
        return ::std::uniform_real_distribution<float>(0.0f, 1.0f)(m_engine);
#else
        return static_cast<float>(genrand())*(1.0f/4294967295.0f);
#endif
    }

    /**
     * @brief   乱数の生成
     * @return  乱数
    */
    template<typename T>
    T genrand(IUTEST_EXPLICIT_TEMPLATE_TYPE_(T))
    {
        return static_cast<T>(genrand( static_cast<unsigned int>( static_cast<T>(-1) ) ));
    }

#if IUTEST_HAS_CLASS_MEMBER_TEMPLATE_SPECIALIZATION && (defined(_MSC_VER) && _MSC_VER < 1300)
    template<>float  genrand<float>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(float)) { return genrandf(); }
    template<>double genrand<double>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(double)) { return static_cast<double>(genrandf()); }
#endif

public:
    result_type operator ()()
    {
        return genrand();
    }
    result_type operator ()(unsigned int max)
    {
        return genrand(max);
    }

public:
    template<typename It>
    void shuffle(It first, It last)
    {
#if IUTEST_HAS_CXX_HDR_RANDOM
        ::std::shuffle(first, last, m_engine);
#else
        ::std::random_shuffle(first, last, *this);
#endif
    }
};

#if !(defined(_MSC_VER) && _MSC_VER < 1300)

#define IIUT_WORKAROUND_GENRAND(type)   \
    template<> inline type  iuRandom::genrand<type>(IUTEST_EXPLICIT_TEMPLATE_TYPE_(type))

IIUT_WORKAROUND_GENRAND(Int64)  { return (static_cast<Int64>(genrand()) << 32) | genrand(); }
IIUT_WORKAROUND_GENRAND(UInt64) { return (static_cast<UInt64>(genrand()) << 32) | genrand(); }
IIUT_WORKAROUND_GENRAND(float)  { return genrandf(); }
IIUT_WORKAROUND_GENRAND(double) { return static_cast<double>(genrandf()); }

#undef IIUT_WORKAROUND_GENRAND

#endif

/**
 * @brief   型指定乱数生成器
*/
template<typename T>
class iuTypedRandom
{
    typedef T result_type;
public:
    iuTypedRandom() {}
    explicit iuTypedRandom(unsigned int seed)
        : m_rnd(seed) {}

    result_type operator ()()
    {
        return genrand();
    }

    result_type operator ()(result_type max)
    {
        return genrand(max);
    }

    result_type genrand()
    {
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
#if defined(__MWERKS__)
        return m_rnd.template genrand<result_type>();
#else
        return m_rnd.genrand<result_type>();
#endif
#else
        return m_rnd.genrand(detail::explicit_type<result_type>());
#endif
    }

    result_type genrand(result_type max)
    {
        return m_rnd.genrand(max);
    }
private:
    iuRandom m_rnd;
};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_RANDOM_HPP_89F260D7_9145_4B50_A8F0_B7A2696121B6_
