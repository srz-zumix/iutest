//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_charcode.hpp
 * @brief       iris unit test 文字コード対応 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_CHARCODE_HPP_D444FB3E_3AFA_46D0_AD69_33FAAF5615E3_
#define INCG_IRIS_IUTEST_CHARCODE_HPP_D444FB3E_3AFA_46D0_AD69_33FAAF5615E3_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_port.hpp"
#include "iutest_constant.hpp"
// IWYU pragma: end_exports

#if IUTEST_HAS_CXX_HDR_CODECVT
#  include <locale>
#  include <codecvt>
#endif

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

namespace iutest {
namespace detail
{

//======================================================================
// declare

/**
 * @brief   マルチバイト文字列をそのまま返す
 * @param [in]  str = 入力
 * @param [in]  num = 入力バッファサイズ
 * @return  マルチバイト文字列
*/
inline ::std::string AnyStringToMultiByteString(const char* str, int num = -1)
{
    return num < 0 ? str : ::std::string(str, static_cast<size_t>(num));
}

/**
 * @brief   マルチバイト文字列をそのまま返す
 * @param [in]  str = 入力
 * @param [in]  num = 入力バッファサイズ
 * @return  マルチバイト文字列
*/
inline ::std::string AnyStringToMultiByteString(const signed char* str, int num = -1)
{
    return AnyStringToMultiByteString(reinterpret_cast<const char*>(str), num);
}

/**
 * @brief   ワイド文字列からUTF8へ変換
 * @param [in]  str = 入力
 * @param [in]  num = 入力バッファサイズ
 * @return  UTF8 文字列
*/
::std::string AnyStringToUTF8(const wchar_t* str, int num=-1);

/**
 * @brief   ワイド文字列からマルチバイトへ変換
 * @param [in]  str = 入力
 * @param [in]  num = 入力バッファサイズ
 * @return  マルチバイト文字列
*/
::std::string AnyStringToMultiByteString(const wchar_t* str, int num=-1);

#if IUTEST_HAS_CHAR16_T

/**
 * @brief   ワイド文字列からマルチバイトへ変換
 * @param [in]  str = 入力
 * @param [in]  num = 入力バッファサイズ
 * @return  マルチバイト文字列
*/
::std::string AnyStringToUTF8(const char16_t* str, int num=-1);

/**
 * @brief   ワイド文字列からマルチバイトへ変換
 * @param [in]  str = 入力
 * @param [in]  num = 入力バッファサイズ
 * @return  マルチバイト文字列
*/
::std::string AnyStringToMultiByteString(const char16_t* str, int num=-1);

#endif

#if IUTEST_HAS_CHAR32_T

/**
 * @brief    ワイド文字列からマルチバイトへ変換
 * @param [in]   str = 入力
 * @param [in]   num = 入力バッファサイズ
 * @return   マルチバイト文字列
*/
::std::string AnyStringToUTF8(const char32_t* str, int num = -1);

/**
 * @brief    ワイド文字列からマルチバイトへ変換
 * @param [in]   str = 入力
 * @param [in]   num = 入力バッファサイズ
 * @return   マルチバイト文字列
*/
::std::string AnyStringToMultiByteString(const char32_t* str, int num = -1);

#endif

/**
 * @brief   文字列から ::std::wstring へ変換
 * @param [in]  str = 入力
 * @return  wstring
*/
::std::wstring MultiByteStringToWideString(const char* str);

/**
 * @brief   マルチバイト文字からUTF8へ変換
 * @param [in]  str = 入力
 * @param [in]  num = 入力バッファサイズ
 * @return  UTF8 文字列
*/
::std::string MultiByteStringToUTF8(const char* str, int num=-1);

/**
 * @brief   ワイド文字列から ::std::string へ変換
 * @param [in]  any_c_str  = 入力
 * @return  string
*/
template<typename CharType>
::std::string ShowAnyCString(const CharType* any_c_str)
{
    if( any_c_str == NULL )
    {
        return kStrings::Null;
    }
    return AnyStringToMultiByteString(any_c_str);
}

#if IUTEST_HAS_CXX_HDR_CODECVT

template<typename In, typename Out, typename State>
struct codecvt : public ::std::codecvt<In, Out, State> { ~codecvt() {} };

/**
 * @brief   文字コード変換
 * @param [in]  str = 入力
 * @return  文字列
*/
#if defined(_MSC_VER)
template<typename In, typename Out, typename State>
::std::basic_string<Out> CodeConvert(const In* str, ::std::locale loc = ::std::locale(""))
{
    ::std::wstring_convert< codecvt<In, Out, State>, In> conv(&::std::use_facet< codecvt<In, Out, State> >(loc));
    return conv.to_bytes(str);
}
#else
template<typename In, typename Out, typename State>
::std::basic_string<Out> CodeConvert(const In* str)
{
    ::std::wstring_convert< codecvt<In, Out, State>, In> conv;
    //::std::wstring_convert< codecvt<In, Out, State>, In> conv(&::std::use_facet< ::std::codecvt<In, Out, State> >(loc) );
    return conv.to_bytes(str);
}
#endif

#endif

//======================================================================
// struct
namespace mbs_ptr_impl
{

template<typename T>
struct to_mbs_ptr
{
    const char* ptr(const char* arg) { return arg; }
};
struct wcs_to_mbs_ptr
{
    ::std::string m_arg;
    const char* ptr(const wchar_t* arg)
    {
        m_arg = ShowAnyCString(arg);
        return m_arg.c_str();
    }
};
template<>
struct to_mbs_ptr<wchar_t> : public wcs_to_mbs_ptr {};
template<>
struct to_mbs_ptr<const wchar_t> : public wcs_to_mbs_ptr {};

}   // end of namespace mbs_ptr_impl

/**
 * @brief   mbs_ptr
*/
template<typename CharType>
struct mbs_ptr : public mbs_ptr_impl::to_mbs_ptr<CharType>
{
};

#if IUTEST_HAS_LIB

#if IUTEST_HAS_EXTERN_TEMPLATE

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_BEGIN()

extern template struct mbs_ptr<char>;
extern template struct mbs_ptr<wchar_t>;

IUTEST_PRAGMA_EXTERN_TEMPLATE_WARN_DISABLE_END()

#else

template struct mbs_ptr<char>;
template struct mbs_ptr<wchar_t>;

#endif
#endif

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}   // end of namespace detail
}   // end of namespace iutest

#if !IUTEST_HAS_LIB
#  include "../impl/iutest_charcode.ipp" // IWYU pragma: export
#endif

#endif // INCG_IRIS_IUTEST_CHARCODE_HPP_D444FB3E_3AFA_46D0_AD69_33FAAF5615E3_
