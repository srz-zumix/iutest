//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_defs.hpp
 * @brief       iris unit test definition
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_DEFS_HPP_839F06DB_E0B6_4E6A_84F2_D99C0A44E06C_
#define INCG_IRIS_IUTEST_DEFS_HPP_839F06DB_E0B6_4E6A_84F2_D99C0A44E06C_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "internal/iutest_compiler.hpp"
#include "internal/iutest_pp.hpp"
#include "internal/iutest_stdlib.hpp"
#include "iutest_config.hpp"
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "internal/iutest_debug.hpp"
// IWYU pragma: end_exports

#if IUTEST_HAS_TYPED_TEST_P
#  if IUTEST_TYPED_TEST_P_STRICT
#    include <set>
#  endif
#endif

namespace iutest
{

//======================================================================
// struct
namespace internal
{

typedef void* TypeId;       //!< テスト識別型

namespace helper
{

//======================================================================
// struct
/**
 * @brief   TypeId Generator Implementation
*/
template<typename T>
struct TestTypeIdHelper { public: static bool _dummy; };

template<typename T>bool TestTypeIdHelper<T>::_dummy = false;

}   // end of namespace helper

//======================================================================
// function
/**
 * @internal
 * @brief   TypeId Generator
*/
template<typename T>
inline TypeId GetTypeId()
{
    return &(helper::TestTypeIdHelper<T>::_dummy);
}

/**
 * @internal
 * @brief   TypeId Generator
*/
inline IUTEST_CXX_CONSTEXPR TypeId GetTestTypeId()
{
    return 0;
}

template<size_t SIZE>
struct TypeWithSize : public detail::type_fit_t<SIZE> {};

}   // end of namespace internal

//======================================================================
// class
namespace detail
{

template<size_t MANT>
struct ieee754_bits_from_mant {};

// float
template<>
struct ieee754_bits_from_mant<24>
{
    enum
    {
          EXP = 8
        , MANT = 23
        , MANT_HIDDEN = 1
    };
};

// double
template<>
struct ieee754_bits_from_mant<53>
{
    enum
    {
          EXP = 11
        , MANT = 52
        , MANT_HIDDEN = 1
    };
};

// 80bit
template<>
struct ieee754_bits_from_mant<64>
{
    enum
    {
          EXP = 15
        , MANT = 64
        , MANT_HIDDEN = 0
    };
};

// 128bit
template<>
struct ieee754_bits_from_mant<113>
{
    enum
    {
          EXP = 15
        , MANT = 113
        , MANT_HIDDEN = 0
    };
};

/**
 * @internal
 * @brief   IEEE754 floating point bits
*/
template<typename T>
struct ieee754_bits : ieee754_bits_from_mant<::std::numeric_limits<T>::digits> {};

}   // end of namespace detail

/**
 * @brief   浮動小数点数
*/
template<typename RawType>
class floating_point
{
private:
    typedef floating_point<RawType> _Myt;

private:
    typedef typename detail::type_fit_t<sizeof(RawType)> type;
    typedef typename type::Int  Int;
    typedef typename type::UInt UInt;
    union FInt
    {
        Int     iv;
        UInt    uv;
        RawType fv;
    };

public:
    /**
     * @brief   コンストラクタ
    */
    floating_point()
    {
        m_v.uv = 0;
    }

    /**
     * @brief   コンストラクタ
     * @param [in]  f   = 浮動小数点数
    */
    floating_point(RawType f)   // NOLINT
    {
        m_v.uv = 0;
        m_v.fv = f;
    }

    /**
     * @brief   コンストラクタ
    */
    floating_point(const floating_point& rhs)
        : m_v(rhs.m_v)
    {
    }

public:
    /**
     * @brief   浮動小数点数がほぼ一致するかどうか
    */
    bool    AlmostEquals(const _Myt& rhs) const
    {
        if( is_nan() || rhs.is_nan() )
        {
            return false;
        }
        return NanSensitiveAlmostEquals(rhs);
    }

    /**
     * @brief   浮動小数点数がほぼ一致するかどうか
     * @sa      https://www.cygnus-software.com/papers/comparingfloats/comparingfloats.htm
    */
    bool    NanSensitiveAlmostEquals(const _Myt& rhs) const
    {
        const UInt v1 = norm(bits());
        const UInt v2 = norm(rhs.bits());
        const UInt diff = (v1 > v2) ? v1 - v2 : v2 - v1;
        if( diff <= kMaxUlps )
        {
            return true;
        }
        return false;
    }

public:
    /**
     * @brief   浮動小数点数の差分が max_abs_error 以内に収まるかどうか
    */
    bool    AlmostNear(const _Myt& rhs, RawType max_abs_error) const
    {
        if( is_nan() || rhs.is_nan() )
        {
            return false;
        }
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_FLOAT_EQUAL()
        if( m_v.fv == rhs.m_v.fv )
        {
            return true;
        }
IUTEST_PRAGMA_WARN_POP()
        _Myt abs = Abs(rhs);
        if( abs.m_v.fv <= max_abs_error )
        {
            return true;
        }
        _Myt abs_error = _Myt(max_abs_error);
        if( abs.AlmostEquals(abs_error) ) {
            return true;
        }
        return false;
    }

    /**
     * @brief   浮動小数点数の差分が max_abs_error 以内に収まるかどうか
    */
    bool    NanSensitiveAlmostNear(const _Myt& rhs, RawType max_abs_error) const
    {
        if( is_nan() && rhs.is_nan() )
        {
            return true;
        }
        return AlmostNear(rhs, max_abs_error);
    }

public:
    _Myt    Abs(const _Myt& rhs) const
    {
        if( m_v.fv > rhs.m_v.fv )
        {
            return _Myt(m_v.fv - rhs.m_v.fv);
        }
        else
        {
            return _Myt(rhs.m_v.fv - m_v.fv);
        }
    }
public:
    /**
     * @brief   ビット列の取得
    */
    UInt    bits() const { return m_v.uv & kEnableBitMask; }

    /**
     * @brief   raw データの取得
    */
    RawType raw() const { return m_v.fv; }

    /**
     * @brief   exponent
    */
    UInt    exponent_bits() const { return m_v.uv & kExpMask; }

    /**
     * @brief   fraction
    */
    UInt    fraction_bits() const { return m_v.uv & kFracMask; }

    /**
     * @brief   sign
    */
    UInt    sign_bit() const { return m_v.uv & kSignMask; }

    /**
     * @brief   is nan
    */
    bool    is_nan() const { return exponent_bits() == kExpMask && fraction_bits() != 0; }

    /**
     * @brief   is inf
    */
    bool    is_inf() const { return exponent_bits() == kExpMask && fraction_bits() == 0; }

public:
    //! plus inf
    static _Myt PINF()
    {
        _Myt f;
        f.m_v.uv = kExpMask;
        return f;
    }
    //! minus inf
    static _Myt NINF()
    {
        _Myt f = PINF();
        f.m_v.uv |= kSignMask;
        return f;
    }
    //! plus nan
    static _Myt PNAN()
    {
        _Myt f;
        f.m_v.uv = kExpMask | 1;
        return f;
    }
    //! minus nan
    static _Myt NNAN()
    {
        _Myt f = PNAN();
        f.m_v.uv |= kSignMask;
        return f;
    }
    //! plus qnan
    static _Myt PQNAN()
    {
        _Myt f;
        f.m_v.uv = ((1 << (kEXP + 1)) - 1);
        f.m_v.uv <<= kMANT - 1;
        return f;
    }
    //! minus qnan
    static _Myt NQNAN()
    {
        _Myt f = PQNAN();
        f.m_v.uv |= kSignMask;
        return f;
    }

public:
#if !defined(_MSC_VER) || _MSC_VER >= 1310
    operator RawType () const   { return m_v.fv; }  //!< cast to RawType
#else
    operator float() const  { return m_v.fv; }
    operator double() const { return m_v.fv; }
#endif
    _Myt&   operator = (RawType f)  { m_v.fv = f; return *this; }   //!< 代入
    _Myt&   operator = (const _Myt& rhs) { m_v.fv = rhs.m_v; return *this; }   //!< 代入

    bool    operator == (const _Myt& rhs) const { return m_v.uv == rhs.m_v.uv; }    //!< 比較

public:
    enum
    {
          EXP = detail::ieee754_bits<RawType>::EXP
        , MANT = detail::ieee754_bits<RawType>::MANT
        , DIGITS = MANT + detail::ieee754_bits<RawType>::MANT_HIDDEN
    };

private:
    enum
    {
          kEXP = detail::ieee754_bits<RawType>::EXP
        , kMANT = detail::ieee754_bits<RawType>::MANT
        , kMaxUlps = 4
    };

private:
    static UInt norm(UInt v) { return (v & kSignMask) ? (~v + 1) : (v | kSignMask); }

#if !defined(IUTEST_NO_INCLASS_MEMBER_INITIALIZATION)
    static const UInt kSignMask = static_cast<UInt>(1u) << (kEXP + kMANT);
    static const UInt kExpMask = ((static_cast<UInt>(1u) << kEXP) - 1) << kMANT;
    static const UInt kFracMask = (static_cast<UInt>(1u) << kMANT) - 1;
    static const UInt kEnableBitMask = kSignMask | kExpMask | kFracMask;
#else
    static const UInt kSignMask;
    static const UInt kExpMask;
    static const UInt kFracMask;
    static const UInt kEnableBitMask;
#endif

private:
    FInt m_v;
};

// googletest compat

namespace detail
{

template<typename T>
class FloatingPoint : public floating_point<T>
{
public:
    explicit FloatingPoint(const T& rhs) : floating_point<T>(rhs) {}
};

typedef FloatingPoint<float> Float;
typedef FloatingPoint<double> Double;

}   // end of namespace detail

#if defined(IUTEST_NO_INCLASS_MEMBER_INITIALIZATION)

template<typename T>
const typename floating_point<T>::UInt floating_point<T>::kSignMask
    = static_cast<typename floating_point<T>::UInt>(1u) << (kEXP + kMANT);
template<typename T>
const typename floating_point<T>::UInt floating_point<T>::kExpMask
    = ((static_cast<typename floating_point<T>::UInt>(1u)
        << floating_point<T>::kEXP) - 1) << floating_point<T>::kMANT;
template<typename T>
const typename floating_point<T>::UInt floating_point<T>::kFracMask
    = ((static_cast<typename floating_point<T>::UInt>(1u) << floating_point<T>::kMANT) - 1);
template<typename T>
const typename floating_point<T>::UInt floating_point<T>::kEnableBitMask
    = floating_point<T>::kSignMask | floating_point<T>::kExpMask | floating_point<T>::kFracMask;

#endif

//======================================================================
// typedef
typedef detail::type_fit_t<1>::Int  Int8;   //!<  8 bit 符号付き整数型
typedef detail::type_fit_t<1>::UInt UInt8;  //!<  8 bit 符号なし整数型
typedef detail::type_fit_t<2>::Int  Int16;  //!< 16 bit 符号付き整数型
typedef detail::type_fit_t<2>::UInt UInt16; //!< 16 bit 符号なし整数型
typedef detail::type_fit_t<4>::Int  Int32;  //!< 32 bit 符号付き整数型
typedef detail::type_fit_t<4>::UInt UInt32; //!< 32 bit 符号なし整数型
typedef detail::type_fit_t<8>::Int  Int64;  //!< 64 bit 符号付き整数型
typedef detail::type_fit_t<8>::UInt UInt64; //!< 64 bit 符号なし整数型

#if IUTEST_HAS_CXX11 && IUTEST_HAS_CXX_HDR_CSTDINT
typedef ::std::uintmax_t    iu_off_t;
#else
typedef UInt64              iu_off_t;
#endif

#if IUTEST_HAS_CXX11 && IUTEST_HAS_CXX_HDR_CSTDINT
typedef ::std::uintptr_t                                iu_uintptr_t;
#else
typedef detail::type_fit_t<sizeof(ptrdiff_t)>::UInt     iu_uintptr_t;
#endif

typedef internal::TypeId TestTypeId;    //!< テスト識別型

typedef void (*SetUpMethod)();      //!< SetUp 関数型
typedef void (*TearDownMethod)();   //!< TearDown 関数型

typedef detail::type_least_t<8>::UInt   TimeInMillisec; //!< ミリ秒単位を扱う型
typedef detail::type_least_t<8>::Int    BiggestInt;     //!< Biggest Int

}   // end of namespace iutest

/*
#if IUTEST_HAS_ATTRIBUTE_DEPRECATED
namespace iutest {
namespace detail
{

template<typename T>
struct type_check_t { static const int IUTEST_ATTRIBUTE_DEPRECATED_ value = 0; };

#if IUTEST_HAS_RVALUE_REFS
template<typename T>
int type_check(T&& x) { return 0; }
#else
template<typename T>
int type_check(const T& x) { return 0; }
#endif

}   // end of namespace detail
}   // end of namespace iutest

#if defined(_MSC_VER)
#  if IUTEST_HAS_DECLTYPE
#    define IUTEST_CHECK_TYPE(x)    (void)::iutest::detail::type_check_t< decltype(x) >::value
#  endif
#else
#  define IUTEST_CHECK_TYPE(x)      ::iutest::detail::type_check(x)
#endif

#if !defined(IUTEST_CHECK_TYPE)
#  define IUTEST_CHECK_TYPE(x)      (void)0
#endif

#endif
*/

#endif // INCG_IRIS_IUTEST_DEFS_HPP_839F06DB_E0B6_4E6A_84F2_D99C0A44E06C_
