//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_static_assertion.hpp
 * @brief       iris unit test static assertion 定義 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2017, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STATIC_ASSERTION_HPP_53842FD6_9E5D_40A6_905D_EC6DEBE5ED6A_
#define INCG_IRIS_IUTEST_STATIC_ASSERTION_HPP_53842FD6_9E5D_40A6_905D_EC6DEBE5ED6A_

//======================================================================
// define
#if IUTEST_HAS_STATIC_ASSERT_TYPEEQ

#if 0

namespace iutest
{

namespace detail
{
    template<typename T1, typename T2>
    struct StaticAssertTypeEqHelper;
}

/**
 * @ingroup IUTEST_UTIL
 * @brief   型アサーション
*/
template<typename T1, typename T2>
static bool StaticAssertTypeEq()
{
    return detail::StaticAssertTypeEqHelper<T1, T2>();
}

}   // end of namespace iutest

#else

/**
 * @ingroup IUTEST_UTIL
 * @brief   型アサーション
 * @note    マクロバージョン
 *          エラーが呼び出し位置に出る
*/
#define StaticAssertTypeEq  detail::StaticAssertTypeEqHelper

#endif

#endif

/**
 * @brief   static_assert
*/
#if IUTEST_HAS_STATIC_ASSERT
#if defined(_MSC_VER) || (defined(__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 8)))
#  define IUTEST_STATIC_ASSERT_MSG(B, Msg)  static_assert(B, "static_assert: " Msg)
#else
#  define IUTEST_STATIC_ASSERT_MSG(B, Msg)  static_assert(B, Msg)
#endif
#else
#  define IIUT_STATIC_ASSERT_SIZECHECK(B)   sizeof(::iutest::detail::static_assert_failure< (bool)(B) >)  // NOLINT
#  define IUTEST_STATIC_ASSERT_MSG(B, Msg)                                              \
    typedef ::iutest::detail::StaticAssertionTest< IIUT_STATIC_ASSERT_SIZECHECK(B) >    \
        IUTEST_PP_CAT(iutest_static_assert_typedef_, IUTEST_PP_COUNTER) IUTEST_ATTRIBUTE_UNUSED_
#endif

/**
 * @brief   static_assert
*/
#ifdef IUTEST_STATIC_ASSERT_MSG
#  ifdef IUTEST_NO_VARIADIC_MACROS
#    define IUTEST_STATIC_ASSERT(B)     IUTEST_STATIC_ASSERT_MSG((B), #B)
#  else
#    define IUTEST_STATIC_ASSERT(...)   IUTEST_STATIC_ASSERT_MSG((__VA_ARGS__), #__VA_ARGS__)
#  endif
#endif

/**
 * @brief   static assert if exists
*/
#ifndef IUTEST_STATIC_ASSERT_IF_EXISTS
#  if IUTEST_HAS_IF_EXISTS
#    define IUTEST_STATIC_ASSERT_IF_EXISTS(identifier, msg) \
        IUTEST_STATIC_ASSERT_MSG( IUTEST_IF_EXISTS(identifier, true) IUTEST_IF_NOT_EXISTS(identifier, false), msg)
#  else
#    define IUTEST_STATIC_ASSERT_IF_EXISTS(identifier, msg)
#  endif
#endif

/**
 * @brief   static assert if not exists
*/
#ifndef IUTEST_STATIC_ASSERT_IF_NOT_EXISTS
#  if IUTEST_HAS_IF_EXISTS
#    define IUTEST_STATIC_ASSERT_IF_NOT_EXISTS(identifier, msg) \
        IUTEST_STATIC_ASSERT_MSG(IUTEST_IF_NOT_EXISTS(identifier, true) IUTEST_IF_EXISTS(identifier, false), msg)
#  else
#    define IUTEST_STATIC_ASSERT_IF_NOT_EXISTS(identifier, msg)
#  endif
#endif

//======================================================================
// function
namespace iutest
{

namespace detail
{

/** @private */
template<typename T1, typename T2>
struct StaticAssertTypeEqHelper;

#if !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
namespace helper
{

/** @private */
template<bool b>struct static_assert_typeeq;
/** @overload */
template<>struct static_assert_typeeq<true> { operator bool() const { return true; } };

}

/** @private */
template<typename T1, typename T2>
struct StaticAssertTypeEqHelper
    : public helper::static_assert_typeeq< iutest_type_traits::is_same<T1, T2>::value >
{
};

#endif

/** @private */
template<bool b>struct static_assert_failure;
/** @overload */
template<> struct static_assert_failure<true> { enum { value = 1 }; };

/** @private */
template<int x>struct StaticAssertionTest {};

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_STATIC_ASSERTION_HPP_53842FD6_9E5D_40A6_905D_EC6DEBE5ED6A_
