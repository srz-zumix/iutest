//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_string.hpp
 * @brief       iris unit test string utilities
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STRING_HPP_E22B02D7_E9E7_412C_B609_DC3D9C66895D_
#define INCG_IRIS_IUTEST_STRING_HPP_E22B02D7_E9E7_412C_B609_DC3D9C66895D_

//======================================================================
// include
#if defined(__MWERKS__)
#  define _MBSTATE_T
#endif

#include <wchar.h>
#include <wctype.h>
#include <stdarg.h>
#include <errno.h>
#if defined(IUTEST_OS_CYGWIN) || defined(__arm__)
#include <strings.h>
#endif
#include <string>
#include <cstring>
#include <cmath>

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

namespace iutest {
namespace detail
{

::std::string StringFormat(const char* format, ...) IUTEST_ATTRIBUTE_FORMAT_PRINTF(1, 2);
::std::string StringFormat(const char* format, va_list va) IUTEST_ATTRIBUTE_FORMAT_PRINTF(1, 0);

namespace wrapper
{

inline int iu_mbicmp(char l, char r)
{
    const int ul = static_cast<int>(static_cast<unsigned char>(toupper(l)));
    const int ur = static_cast<int>(static_cast<unsigned char>(toupper(r)));
    return ul - ur;
}

inline int iu_stricmp(const char* str1, const char* str2)
{
    const char* l = str1;
    const char* r = str2;
    while(*l)
    {
        const int ret = iu_mbicmp(*l, *r);
        if( ret != 0 )
        {
            return ret;
        }
        ++l;
        ++r;
    }
    return iu_mbicmp(*l, *r);
}

inline int iu_wcicmp(wchar_t l, wchar_t r)
{
    const ::std::wint_t ul = towupper(l);
    const ::std::wint_t ur = towupper(r);
    return ul - ur;
}

inline int iu_wcsicmp(const wchar_t * str1, const wchar_t * str2)
{
    const wchar_t* l = str1;
    const wchar_t* r = str2;
    while(*l)
    {
        const int ret = iu_wcicmp(*l, *r);
        if( ret != 0 )
        {
            return ret;
        }
        ++l;
        ++r;
    }
    return iu_wcicmp(*l, *r);
}

}   // end of namespace wrapper

/**
 * @internal
 * @brief   stricmp (unsigned char compare)
*/
inline int iu_stricmp(const char* str1, const char* str2)
{
#if   defined(__BORLANDC__)
    return stricmp(str1, str2);
#elif defined(_MSC_VER)
    return _stricmp(str1, str2);
#elif defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MINGW) && !defined(__STRICT_ANSI__)
    return _stricmp(str1, str2);
#elif !defined(__MWERKS__) && !defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_CYGWIN)
    // NOTE: Cygwin strcasecmp signed compare?
    return strcasecmp(str1, str2);
#else
    return wrapper::iu_stricmp(str1, str2);
#endif
}

/**
 * @internal
 * @brief   wcsicmp
*/
inline int iu_wcsicmp(const wchar_t * str1, const wchar_t * str2)
{
#if   defined(_MSC_VER)
    return _wcsicmp(str1, str2);
#elif defined(IUTEST_OS_LINUX) && !defined(IUTEST_ARCH_ARM)
    return wcscasecmp(str1, str2);
#else
    return wrapper::iu_wcsicmp(str1, str2);
#endif
}

namespace wrapper
{

int iu_vsnprintf(char* dst, size_t size, const char* format, va_list va) IUTEST_ATTRIBUTE_FORMAT_PRINTF(3, 0);

inline int iu_vsnprintf(char* dst, size_t size, const char* format, va_list va)
{
    char buffer[4096] = {0};
    char* write_buffer = dst != NULL && size >= 4096 ? dst : buffer;
    const int ret = vsprintf(write_buffer, format, va);
    if( dst != NULL )
    {
        const size_t length = static_cast<size_t>(ret);
        const size_t write = (size <= length) ? size - 1 : length;
        if( write_buffer == buffer ) {
            strncpy(dst, buffer, write);
        }
        dst[write] = '\0';
    }
    return ret;
}

} // end of namespace wrapper

int iu_vsnprintf(char* dst, size_t size, const char* format, va_list va) IUTEST_ATTRIBUTE_FORMAT_PRINTF(3, 0);
int iu_snprintf(char* dst, size_t size, const char* format, ...) IUTEST_ATTRIBUTE_FORMAT_PRINTF(3, 4);

/**
 * @internal
 * @brief   vsnprintf
*/
inline int iu_vsnprintf(char* dst, size_t size, const char* format, va_list va)
{
    if( dst == NULL && size > 0 )
    {
        return -1;
    }
#if   defined(_MSC_VER)
    if( dst == NULL || size <= 0 )
    {
        return _vscprintf(format, va);
    }
#  if IUTEST_HAS_WANT_SECURE_LIB
    return _vsnprintf_s(dst, size, _TRUNCATE, format, va);
#  else
    return _vsnprintf(dst, size, format, va);
#  endif
#elif defined(__CYGWIN__) \
        && (defined(__STRICT_ANSI__) && (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) && (__cplusplus >= 201103L))
    return wrapper::iu_vsnprintf(dst, size, format, va);
#elif (defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)) && defined(__STRICT_ANSI__)
    return wrapper::iu_vsnprintf(dst, size, format, va);
#else
    return vsnprintf(dst, size, format, va);
#endif
}

/**
 * @internal
 * @brief   snprintf
*/
inline int iu_snprintf(char* dst, size_t size, const char* format, ...)
{
    va_list va;
    va_start(va, format);
    const int ret = iu_vsnprintf(dst, size, format, va);
    va_end(va);
    return ret;
}

IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()

inline bool IsEmpty(const char* p) { return p == NULL || *p == '\0'; }
inline IUTEST_CXX_CONSTEXPR bool IsSpace(char ch) { return ch == ' ' || ch =='\t'; }
inline const char* NullableString(const char* str) { return str == NULL ? "" : str; }
inline IUTEST_CXX_CONSTEXPR const char* SkipSpace(const char* p)
{
    return p == NULL ? NULL : (IsSpace(*p) ? SkipSpace(++p) : p);
}
inline IUTEST_CXX_CONSTEXPR const char* FindComma(const char* p)
{
    return (p == NULL || *p == '\0') ? NULL : ((*p == ',') ? p : FindComma(++p));
}
inline bool IsStringEqual(const char* str1, const char* str2) { return strcmp(str1, str2) == 0; }
inline bool IsStringEqual(const ::std::string& str1, const char* str2) { return str1.compare(str2) == 0; }
inline bool IsStringEqual(const ::std::string& str1, const ::std::string& str2) { return str1.compare(str2) == 0; }
inline bool IsStringCaseEqual(const char* str1, const char* str2) { return iu_stricmp(str1, str2) == 0; }
inline bool IsStringCaseEqual(const ::std::string& str1, const char* str2) { return iu_stricmp(str1.c_str(), str2) == 0; }
inline bool IsStringCaseEqual(const ::std::string& str1, const ::std::string& str2) { return iu_stricmp(str1.c_str(), str2.c_str()) == 0; }
inline bool IsStringForwardMatching(const char* str1, const char* str2) { return strstr(str1, str2) == str1; }
inline bool IsStringForwardMatching(const ::std::string& str1, const char* str2) { return str1.find(str2) == 0; }
inline bool IsStringForwardMatching(const ::std::string& str1, const std::string& str2) { return str1.find(str2) == 0; }
inline bool IsStringContains(const char* str1, const char* str2) { return strstr(str1, str2) != NULL; }
inline bool IsStringContains(const ::std::string& str1, const char* str2) { return str1.find(str2) != ::std::string::npos; }
inline bool IsStringContains(const ::std::string& str1, const ::std::string& str2) { return str1.find(str2) != ::std::string::npos; }

inline void StringReplace(::std::string& str, const char* from, size_t n, const char* to)
{
    ::std::string::size_type pos = 0;
    while( static_cast<void>(pos = str.find(from, pos)), pos != ::std::string::npos )
    {
        str.replace(pos, n, to);
        ++pos;
    }
}
inline void StringReplace(::std::string& str, char a, const char* to)
{
    char s[] = { a, 0 };
    return StringReplace(str, s, 1, to);
}
inline ::std::string StripLeadingSpace(const ::std::string& str)
{
    ::std::string::const_iterator it = str.begin();
    while( it != str.end() && IsSpace(*it) )
    {
        ++it;
    }
    return ::std::string(it, str.end());
}
inline ::std::string StripTrailingSpace(const ::std::string& str)
{
    ::std::string::const_iterator it = str.end()-1;
    while(it != str.begin() && IsSpace(*it))
    {
        --it;
    }
    return ::std::string(str.begin(), it+1);
}
inline ::std::string StripSpace(const ::std::string& str)
{
    ::std::string::const_iterator start = str.begin();
    while( start != str.end() && IsSpace(*start) )
    {
        ++start;
    }
    ::std::string::const_iterator end = str.end()-1;
    while( end != str.begin() && IsSpace(*end) )
    {
        --end;
    }
    return ::std::string(start, end+1);
}

inline bool StringIsBlank(const ::std::string& str)
{
    ::std::string::const_iterator it = str.begin();
    while( it != str.end() )
    {
        const char ch = *it;
        if( !IsSpace(ch) && ch != '\r' && ch != '\n' )
        {
            return false;
        }
        ++it;
    }
    return true;
}

inline void StringReplaceToLF(::std::string& str)
{
    StringReplace(str, "\r\n", 2, "\n");
    StringReplace(str, "\r"  , 1, "\n");
}
inline ::std::string StringRemoveComment(const ::std::string& str)
{
    ::std::string r;
    ::std::string::size_type prev = 0;
    ::std::string::size_type pos = str.find('\n', 0);
    while( pos != ::std::string::npos )
    {
        ++pos;
        if( str[prev] != '#' ) {
            r += str.substr(prev, pos-prev);
        }
        prev = pos;
        pos = str.find('\n', pos);
    }
    if( str[prev] != '#' ) {
        r += str.substr(prev);
    }
    return r;
}

inline void StringSplit(const ::std::string& str, char delimiter, ::std::vector< ::std::string >& dst)
{
    ::std::string::size_type prev = 0;
    ::std::string::size_type pos = 0;
    ::std::vector< ::std::string > parsed;
    while(static_cast<void>(pos = str.find(delimiter, prev)), pos != ::std::string::npos)
    {
        parsed.push_back(str.substr(prev, pos - prev));
        ++pos;
        prev = pos;
    }
    parsed.push_back(str.substr(prev));
    dst.swap(parsed);
}

template<typename T>
inline ::std::string ToOctString(T value)
{
    const size_t kB = sizeof(T) * 8;
    const size_t kN = (kB + 2) / 3;
    const size_t kD = kB - (kN - 1) * 3;
    const size_t kMask = (1u << kD) - 1u;
    const T head = (value >> ((kN - 1) * 3)) & kMask;
    char buf[kN + 1] = { static_cast<char>('0' + (head & 0x7)), 0 };
    for(size_t i = 1; i < kN; ++i)
    {
        const T n = (value >> ((kN - i - 1) * 3));
        buf[i] = static_cast<char>('0' + (n & 0x7));
    }
    buf[kN] = '\0';
    return buf;
}

inline IUTEST_CXX_CONSTEXPR char ToHex(unsigned int n)
{
    return static_cast<char>((n&0xF) >= 0xA ? 'A'+((n&0xF)-0xA) : '0'+(n&0xF));
}

template<typename T>
inline ::std::string ToHexString(T value)
{
    const size_t kN = sizeof(T)*2;
    char buf[kN + 1] = {0};
    for( size_t i=0; i < kN; ++i )
    {
        buf[i] = ToHex(static_cast<unsigned int>((value>>((kN-i-1)*4))));
    }
    buf[kN] = '\0';
    return buf;
}

template<typename T>
inline ::std::string ToHexString(const T* str, int length)
{
    ::std::string r;
    for( int i=0; (length < 0 || i < length) && *str != 0; ++str, ++i)
    {
        r += ToHexString(*str);
    }
    return r;
}

inline ::std::string FormatIntWidthN(int value, int digit)
{
    char buf[128] = { 0 };
    int idx = IUTEST_PP_COUNTOF(buf) - 2;
    int x = value;
    for( int i=0; i < digit; ++i, --idx )
    {
        buf[idx] = static_cast<char>(::std::abs(x%10) + '0');
        x /= 10;
    }
    for( ; x; --idx )
    {
        buf[idx] = static_cast<char>(::std::abs(x%10) + '0');
        x /= 10;
    }
    if( value < 0 )
    {
        buf[idx--] = '-';
    }
    return buf + idx + 1;
}

inline ::std::string FormatIntWidth2(int value)
{
    return FormatIntWidthN(value, 2);
}

#if IUTEST_HAS_STD_TO_CHARS

template<typename T>
::std::string iu_to_string(const T& value)
{
    const size_t kN = 128;
    char buf[kN] = { 0 };
    const ::std::to_chars_result r = ::std::to_chars(buf, buf + kN, value);
    *r.ptr = '\0';
    return buf;
}

#else

#define IIUT_DECL_TOSTRING(fmt_, type_) \
    inline ::std::string iu_to_string(type_ value) {\
        char buf[128] = { 0 };                      \
        iu_snprintf(buf, sizeof(buf), fmt_, value); \
        return buf;                                 \
    }

IIUT_DECL_TOSTRING("%d", int)
IIUT_DECL_TOSTRING("%u", unsigned int)
IIUT_DECL_TOSTRING("%ld", long)
IIUT_DECL_TOSTRING("%lu", unsigned long)
IIUT_DECL_TOSTRING("%lld", long long)
IIUT_DECL_TOSTRING("%llu", unsigned long long)

#undef IIUT_DECL_TOSTRING

#endif

inline ::std::string FormatSizeByte(UInt64 value)
{
    const char* suffixes[] = {
        "B",
        "KB",
        "MB",
        "GB",
        "TB",
    };
    const size_t suffixes_length = IUTEST_PP_COUNTOF(suffixes);
    size_t index = 0;
    double view_value = static_cast<double>(value);
    while(view_value >= 1024 && index + 1 < suffixes_length)
    {
        ++index;
        view_value /= 1024;
    }

    const UInt32 n = static_cast<UInt32>(::std::floor(view_value));
    const UInt32 f = static_cast<UInt32>(view_value * 10.0 - n * 10.0);
    const char* suffix = suffixes[index];
    if(view_value - n <= 0.0)
    {
        return iu_to_string(n) + suffix;
    }
    else
    {
        return iu_to_string(n) + "." + iu_to_string(f) + suffix;
    }
}

inline ::std::string ShowStringQuoted(const char* str)
{
    ::std::string s = "\""; s += str; s += "\"";
    return s;
}
inline ::std::string ShowStringQuoted(const ::std::string& str)
{
    ::std::string s = "\""; s += str; s += "\"";
    return s;
}

inline ::std::string StringFormat(const char* format, ...)
{
    va_list va;
    va_start(va, format);
    ::std::string str = StringFormat(format, va);
    va_end(va);
    return str;
}
inline ::std::string StringFormat(const char* format, va_list va)
{
    size_t n = strlen(format) * 2 + 1;
    {
        va_list va2;
        iu_va_copy(va2, va);    // cppcheck-suppress va_list_usedBeforeStarted
        const int ret = iu_vsnprintf(NULL, 0u, format, va2);
        va_end(va2);
        if( ret > 0 )
        {
            n = static_cast<size_t>(ret + 1);
        }
    }
    for( ;; )
    {
        char* dst = new char[n];
        va_list va2;
        iu_va_copy(va2, va);    // cppcheck-suppress va_list_usedBeforeStarted
        const int written = iu_vsnprintf(dst, n, format, va2);
        va_end(va2);
        if( written < 0 )
        {
#if defined(EOVERFLOW)
            if( errno == EOVERFLOW )
            {
                break;
            }
#endif
#if defined(E2BIG)
            if( errno == E2BIG )
            {
                break;
            }
#endif
        }
        else if( static_cast<size_t>(written) < n )
        {
            ::std::string s = ::std::string(dst, static_cast<size_t>(written));
            delete[] dst;
            return s;
        }
        delete[] dst;
        n *= 2;
    }
    return "";
}

IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_STRING_HPP_E22B02D7_E9E7_412C_B609_DC3D9C66895D_
