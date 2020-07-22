//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_charcode.ipp
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
#ifndef INCG_IRIS_IUTEST_CHARCODE_IPP_D444FB3E_3AFA_46D0_AD69_33FAAF5615E3_
#define INCG_IRIS_IUTEST_CHARCODE_IPP_D444FB3E_3AFA_46D0_AD69_33FAAF5615E3_

//======================================================================
// include
#include "../internal/iutest_charcode.hpp"
#if IUTEST_HAS_CXX_HDR_CUCHAR
#  include <cuchar>
#endif

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

namespace iutest {
namespace detail
{

//======================================================================
// variable
const UInt32 kMaxCodePoint1 = (static_cast<UInt32>(1) << 7) - 1;
const UInt32 kMaxCodePoint2 = (static_cast<UInt32>(1) << (5+6)) - 1;
const UInt32 kMaxCodePoint3 = (static_cast<UInt32>(1) << (4+2*6)) - 1;
const UInt32 kMaxCodePoint4 = (static_cast<UInt32>(1) << (3+3*6)) - 1;

//======================================================================
// function
/**
 * @brief   サロゲートペアかどうか
*/
IUTEST_IPP_INLINE IUTEST_CXX_CONSTEXPR bool IsUtf16SurrogatePair(wchar_t first, wchar_t second)
{
    return (sizeof(wchar_t) == 2)
        && ((first & 0xFC00) == 0xD800) && ((second & 0xFC00) == 0xDC00);
}
/**
 * @brief   サロゲートペアからコードポイントへ変換
*/
IUTEST_IPP_INLINE IUTEST_CXX_CONSTEXPR UInt32 CreateCodePointFromUtf16SurrogatePair(wchar_t first, wchar_t second)
{
    //const UInt32 mask = (1<<10) -1;   // 0x3FF
    return (sizeof(wchar_t)==2) ?
        static_cast<UInt32>((((first & 0x3FF) << 10) | (second & 0x3FF)) + 0x10000) :
        static_cast<UInt32>(first); // こっちは未対応
}
/**
 * @brief   下位から指定ビット数のビットを取得してシフトする
*/
IUTEST_IPP_INLINE UInt32 ChopLowBits(UInt32* bits, int n)
{
    const UInt32 lowbits = *bits & ((static_cast<UInt32>(1) << n) - 1);
    *bits >>= n;
    return lowbits;
}

/**
 * @brief   コードポイントからUTF8へ変換
 * @param [in]  code_point  = コードポイント
 * @param [out] buf         = 出力バッファ(32バイト以上を要求)
 * @param [in]  size        = 出力バッファサイズ
 * @return  出力バッファ
*/
IUTEST_IPP_INLINE char* CodePointToUtf8(UInt32 code_point, char* buf, size_t size)
{
    if( code_point <= kMaxCodePoint1 )
    {
        buf[1] = '\0';
        buf[0] = static_cast<char>(code_point);
    }
    else if( code_point <= kMaxCodePoint2 )
    {
        buf[2] = '\0';
        buf[1] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
        buf[0] = static_cast<char>(0xC0 | code_point);
    }
    else if( code_point <= kMaxCodePoint3 )
    {
        buf[3] = '\0';
        buf[2] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
        buf[1] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
        buf[0] = static_cast<char>(0xE0 | code_point);
    }
    else if( code_point <= kMaxCodePoint4 )
    {
        buf[4] = '\0';
        buf[3] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
        buf[2] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
        buf[1] = static_cast<char>(0x80 | ChopLowBits(&code_point, 6));
        buf[0] = static_cast<char>(0xF0 | code_point);
    }
    else
    {
        iu_snprintf(buf, size, "(Invalid UTF16 0x%s)", ToHexString(code_point).c_str());
    }
    return buf;
}

#if defined(_MSC_VER)
IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ UTF8ToSJIS(const char* str, int length)
{
    const int lengthWideChar = MultiByteToWideChar(CP_UTF8, 0, str, length, NULL, 0);
    if( lengthWideChar <= 0 )
    {
        IUTEST_LOG_(WARNING) << "UTF8ToSJIS: convert error";
        return "(convert error)";
    }

    wchar_t* wbuf = new wchar_t[lengthWideChar];
    MultiByteToWideChar(CP_UTF8, 0, str, length, wbuf, lengthWideChar);

    const int lengthSJIS = WideCharToMultiByte(CP_THREAD_ACP, 0, wbuf, -1, NULL, 0, NULL, NULL);
    if( lengthSJIS <= 0 )
    {
        delete[] wbuf;
        IUTEST_LOG_(WARNING) << "UTF8ToSJIS: convert error";
        return "(convert error)";
    }

    char* buf = new char[lengthSJIS];
    WideCharToMultiByte(CP_THREAD_ACP, 0, wbuf, -1, buf, lengthSJIS, NULL, NULL);

    ::std::string ret(buf);
    delete[] wbuf;
    delete[] buf;
    return ret;
}
IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ UTF8ToSJIS(const ::std::string& str)
{
    const int src_length = static_cast<int>(str.length() + 1);
    return UTF8ToSJIS(str.c_str(), src_length);
}
#if IUTEST_HAS_CHAR8_T
IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ UTF8ToSJIS(const char8_t* str, int length)
{
    const int src_length = length < 0 ? static_cast<int>(::std::char_traits<char8_t>::length(str)) : length;
    return UTF8ToSJIS(reinterpret_cast<const char*>(str), src_length);
}
#endif
#endif

IUTEST_IPP_INLINE ::std::string IUTEST_ATTRIBUTE_UNUSED_ AnyStringToUTF8(const wchar_t* str, int num)
{
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
    if(num == -1)
    {
        num = static_cast<int>(wcslen(str));
    }
    std::string s;
    for(int i=0; i < num; ++i )
    {
        UInt32 code_point = 0;
        if( str[i] == L'\0' )
        {
            break;
        }
        else if( i + 1 < num && IsUtf16SurrogatePair(str[i], str[i+1]) )
        {
            code_point = CreateCodePointFromUtf16SurrogatePair(str[i], str[i+1]);
            ++i;
        }
        else
        {
            code_point = static_cast<UInt32>(str[i]);
        }
        char buf[32];
        s += CodePointToUtf8(code_point, buf, sizeof(buf));
    }
    return s;
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
}

IUTEST_IPP_INLINE ::std::string IUTEST_ATTRIBUTE_UNUSED_ AnyStringToMultiByteString(const wchar_t* str, int num)
{
#if defined(IUTEST_OS_WINDOWS) && IUTEST_MBS_CODE == IUTEST_MBS_CODE_WINDOWS31J
    return win::WideStringToMultiByteString(str, num);
#else
    const size_t length = num < 0 ? (wcslen(str) * MB_CUR_MAX + 1) : static_cast<size_t>(num);
    char* mbs = new char [length];
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
    const size_t written = wcstombs(mbs, str, length - 1);
    if( written == static_cast<size_t>(-1))
    {
        delete [] mbs;
        IUTEST_LOG_(WARNING) << "AnyStringToMultiByteString: convert error";
        return ToHexString(str, num);
    }
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
    mbs[written] = '\0';
    ::std::string ret = mbs;
    delete [] mbs;
    return ret;
#endif
}

#if IUTEST_HAS_CHAR8_T

IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ AnyStringToUTF8(const char8_t* str, int num)
{
    ScopedEncoding loc(LC_CTYPE, "UTF8");
#if IUTEST_HAS_CXX_HDR_CUCHAR && IUTEST_HAS_STD_CHAR8_T
    return AnyStringToMultiByteString(str, num);
#else
    const char* p = reinterpret_cast<const char*>(str);
    return (num < 0) ? p : std::string(p, num);
#endif
}

IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ AnyStringToMultiByteString(const char8_t* str, int num)
{
#if IUTEST_HAS_CXX_HDR_CUCHAR && IUTEST_HAS_STD_CHAR8_T
    const size_t length = num < 0 ? ::std::char_traits<char8_t>::length(str) : static_cast<size_t>(num);
    char mbs[IU_MB_CUR_MAX];
    mbstate_t state = {};
    IUTEST_CHECK_(mbsinit(&state) != 0);
    ::std::string ret;

    IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
    for( size_t i = 0; i < length; ++i )
    {
        const size_t len = ::std::c8rtomb(mbs, str[i], &state);
        if( len != static_cast<size_t>(-1) )
        {
            mbs[len] = '\0';
            ret += mbs;
        }
    }
    IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
    return ret;
#else
    const char* p = reinterpret_cast<const char*>(str);
    return (num < 0) ? p : std::string(p, num);
#endif
}

#endif

#if IUTEST_HAS_CHAR16_T

IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ AnyStringToUTF8(const char16_t* str, int num)
{
#if IUTEST_HAS_CXX_HDR_CUCHAR || IUTEST_HAS_CXX_HDR_CODECVT
    ScopedEncoding loc(LC_CTYPE, "UTF8");
    return AnyStringToMultiByteString(str, num);
#else
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_CAST_ALIGN()
    return AnyStringToUTF8(reinterpret_cast<const wchar_t*>(str), num);
IUTEST_PRAGMA_WARN_POP()
#endif
}

IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ AnyStringToMultiByteString(const char16_t* str, int num)
{
#if IUTEST_HAS_CXX_HDR_CUCHAR
    const size_t length = num < 0 ? ::std::char_traits<char16_t>::length(str) : static_cast<size_t>(num);
    char16_t lead = 0, trail = 0;
    char32_t cp;
    char mbs[IU_MB_CUR_MAX];
    mbstate_t state = {};
    IUTEST_CHECK_(mbsinit(&state) != 0);
    ::std::string ret;

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
    for( size_t i = 0; i < length; ++i )
    {
        lead = str[i];

        if( lead > 0xD800 && lead < 0xDC00 )
        {
            ++i;
            trail = str[i];
            cp = (lead << 10) + trail + 0x10000 - (0xD800 << 10) - 0xDC00;
        }
        else
        {
            cp = lead;
        }
        const size_t len = ::std::c32rtomb(mbs, cp, &state);
        if( len != static_cast<size_t>(-1) )
        {
            mbs[len] = '\0';
            ret += mbs;
        }
    }
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
    return ret;
#elif IUTEST_HAS_CXX_HDR_CODECVT
    IUTEST_UNUSED_VAR(num);
    return CodeConvert<char16_t, char, ::std::mbstate_t>(str);
#elif defined(_MSC_VER)
    return UTF8ToSJIS(AnyStringToUTF8(str, num));
#else
    return AnyStringToMultiByteString(reinterpret_cast<const wchar_t*>(str), num);
#endif
}

#endif

#if IUTEST_HAS_CHAR32_T

IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ AnyStringToUTF8(const char32_t* str, int num)
{
    ScopedEncoding loc(LC_CTYPE, "UTF8");
    return AnyStringToMultiByteString(str, num);
}

IUTEST_IPP_INLINE::std::string IUTEST_ATTRIBUTE_UNUSED_ AnyStringToMultiByteString(const char32_t* str, int num)
{
#if IUTEST_HAS_CXX_HDR_CUCHAR
    const size_t length = num < 0 ? ::std::char_traits<char32_t>::length(str) : static_cast<size_t>(num);
    char mbs[IU_MB_CUR_MAX];
    mbstate_t state = {};
    IUTEST_CHECK_(mbsinit(&state) != 0);
    ::std::string ret;

    IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
    for( size_t i = 0; i < length; ++i )
    {
        const size_t len = ::std::c32rtomb(mbs, str[i], &state);
        if( len != static_cast<size_t>(-1) )
        {
            mbs[len] = '\0';
            ret += mbs;
    }
}
    IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
    return ret;
#elif IUTEST_HAS_CXX_HDR_CODECVT
    IUTEST_UNUSED_VAR(num);
    return CodeConvert<char32_t, char, ::std::mbstate_t>(str);
#else
    IUTEST_LOG_(WARNING) << "AnyStringToMultiByteString: convert error";
    return ToHexString(str, num);
#endif
}

#endif

IUTEST_IPP_INLINE ::std::wstring IUTEST_ATTRIBUTE_UNUSED_ MultiByteStringToWideString(const char* str)
{
    if(str == NULL)
    {
        return L"";
    }
    const size_t length = strlen(str) + 1;
    wchar_t* wcs = new wchar_t[length];
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
    if(mbstowcs(wcs, str, length) == static_cast<size_t>(-1))
    {
        delete[] wcs;
        IUTEST_LOG_(WARNING) << "MultiByteStringToWideString: convert error";
        return L"(convert error)";
    }
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
    ::std::wstring ret = wcs;
    delete[] wcs;
    return ret;
}

IUTEST_IPP_INLINE ::std::string IUTEST_ATTRIBUTE_UNUSED_ MultiByteStringToUTF8(const char* src, int num)
{
#if (defined(__STDC_ISO_10646__) || defined(_MSC_VER)) && !defined(IUTEST_OS_WINDOWS_MOBILE)
    if( num == -1 )
    {
        num = static_cast<int>(strlen(src));
    }
    ::std::string str;
    const char* p = src;
    for(const char* end = src + num; p < end; )
    {
        wchar_t wc=0;
        const int len = iu_mbtowc(&wc, p, MB_CUR_MAX);
        if( len > 1 )
        {
            str += AnyStringToUTF8(&wc, 1);
            p += len;
        }
        else
        {
            str += *p;
            ++p;
        }
    }
    return str;
#else
    IUTEST_UNUSED_VAR(num);
    return src;
#endif
}

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_CHARCODE_IPP_D444FB3E_3AFA_46D0_AD69_33FAAF5615E3_
