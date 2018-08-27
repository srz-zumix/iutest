//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_string.hpp
 * @brief       iris unit test 文字列操作 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2018, Takazumi Shirayanagi\n
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
#if defined(IUTEST_OS_CYGWIN) || defined(IUTEST_OS_ARM)
#include <strings.h>
#endif
#if   IUTEST_HAS_STRINGSTREAM
#  include <sstream>
#elif IUTEST_HAS_STRSTREAM
#  include <strstream>
#endif
#include <string>
#include <cstring>
#include <cmath>

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

namespace iutest {
namespace detail
{

::std::string StringFormat(const char* format, ...);

/**
 * @internal
 * @brief   stricmp
*/
inline int iu_stricmp(const char* str1, const char* str2)
{
#if   defined(__BORLANDC__)
    return stricmp(str1, str2);
#elif defined(_MSC_VER)
    return _stricmp(str1, str2);
#elif defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MINGW) && !defined(__STRICT_ANSI__)
    return _stricmp(str1, str2);
#elif !defined(__MWERKS__) && !defined(IUTEST_OS_WINDOWS)
    return strcasecmp(str1, str2);

#else
    const char* l = str1;
    const char* r = str2;
    while(*l)
    {
        int ul = toupper(*l);
        int ur = toupper(*r);
        if( ul < ur )
        {
            return -1;
        }
        if( ul > ur )
        {
            return 1;
        }
        ++l;
        ++r;
    }
    if( *l < *r )
    {
        return -1;
    }
    if( *l > *r )
    {
        return 1;
    }
    return 0;
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
#elif defined(IUTEST_OS_LINUX) && !defined(IUTEST_OS_LINUX_ANDROID)
    return wcscasecmp(str1, str2);
#else
    const wchar_t* l = str1;
    const wchar_t* r = str2;
    while(*l)
    {
        wchar_t ul = towupper(*l);
        wchar_t ur = towupper(*r);
        if( ul < ur )
        {
            return -1;
        }
        if( ul > ur )
        {
            return 1;
        }
        ++l;
        ++r;
    }
    if( *l < *r )
    {
        return -1;
    }
    if( *l > *r )
    {
        return 1;
    }
    return 0;
#endif
}

namespace wrapper
{

inline int iu_vsnprintf(char* dst, size_t size, const char* format, va_list va)
{
    char buffer[4096];
    const int ret = vsprintf(buffer, format, va);
    if( dst != NULL )
    {
        const size_t length = static_cast<size_t>(ret);
        const size_t write = (size <= length) ? size - 1 : length;
        strncpy(dst, buffer, write);
        dst[write] = '\0';
    }
    return ret;
}

} // end of namespace wrapper

/**
 * @internal
 * @brief   vsnprintf
*/
inline int iu_vsnprintf(char* dst, size_t size, const char* format, va_list va)
{
#if   defined(__CYGWIN__) && defined(__STRICT_ANSI__) \
        && (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) && (__cplusplus >= 201103L)
    return wrapper::iu_vsnprintf(dst, size, format, va);
#elif (defined(__MINGW__) || defined(__MINGW32__) || defined(__MINGW64__)) && defined(__STRICT_ANSI__)
    return wrapper::iu_vsnprintf(dst, size, format, va);
#else
    if( dst == NULL && size > 0 )
    {
        return -1;
    }
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
inline bool IsStringCaseEqual(const char* str1, const char* str2) { return iu_stricmp(str1, str2) == 0; }
inline bool IsStringForwardMatching(const char* str1, const char* str2) { return strstr(str1, str2) == str1; }

inline void StringReplace(::std::string& str, char a, const char* to)
{
    ::std::string::size_type pos = 0;
    while( static_cast<void>(pos = str.find(a, pos)), pos != ::std::string::npos )
    {
        str.replace(pos, 1, to);
        ++pos;
    }
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
    ::std::string::size_type pos = 0;
    while( static_cast<void>(pos = str.find("\r\n", pos)), pos != ::std::string::npos )
    {
        str.replace(pos, 2, "\n");
        ++pos;
    }
    StringReplace(str, '\r', "\n");
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

inline IUTEST_CXX_CONSTEXPR char ToOct(unsigned int n)
{
    return '0' + (n & 0x7);
}

template<typename T>
inline ::std::string ToOctString(T value)
{
    const size_t kN = (sizeof(T) * 8 + 2) / 3;
    char buf[kN + 1] = { 0 };
    for(size_t i = 0; i < kN; ++i)
    {
        buf[i] = ToOct(static_cast<unsigned int>((value >> ((kN - i - 1) * 3))));
    }
    buf[kN] = '\0';
    return buf;
}

inline IUTEST_CXX_CONSTEXPR char ToHex(unsigned int n)
{
    return (n&0xF) >= 0xA ? 'A'+((n&0xF)-0xA) : '0'+(n&0xF);
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

inline ::std::string FormatIntWidth2(int value)
{
    char buf[3] = "00";
    buf[0] = (value/10)%10 + '0';
    buf[1] = (value   )%10 + '0';
    return buf;
}

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
    double view_value = value;
    while(view_value >= 1024 && index < suffixes_length)
    {
        ++index;
        view_value /= 1024;
    }

    const UInt64 n = static_cast<UInt64>(::std::floor(view_value));
    const UInt64 f = static_cast<UInt64>(view_value * 10.0 - n * 10.0);
    if(view_value - n == 0)
    {
        return StringFormat("%d%s", n, suffixes[index]);
    }
    else
    {
        return StringFormat("%d.%d%s", n, f, suffixes[index]);
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
    size_t n = strlen(format) * 2;
    {
        va_list va;
        va_start(va, format);
        const size_t ret = iu_vsnprintf(NULL, 0, format, va);
        va_end(va);
        if( ret > 0 )
        {
            n = ret;
        }
    }
    for( ;; )
    {
        char* dst = new char[n];
        va_list va;
        va_start(va, format);
        const int written = iu_vsnprintf(dst, n, format, va);
        va_end(va);
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

//======================================================================
// declare
#if !IUTEST_HAS_STRINGSTREAM && !IUTEST_HAS_STRSTREAM
template<class _Elem, class _Traits>class iu_basic_stream;
#endif

#if   IUTEST_HAS_STRINGSTREAM

typedef ::std::stringstream stlstream;

#elif IUTEST_HAS_STRSTREAM

IUTEST_PRAGMA_MSC_WARN_PUSH()
IUTEST_PRAGMA_MSC_WARN_DISABLE(4250)
class stlstream : public ::std::strstream
{
    char buf[512];
public:
    stlstream()
        : ::std::strstream(buf, sizeof(buf)-2, ::std::ios::out)
    {}
    explicit stlstream(const char* str)
        : ::std::strstream(buf, sizeof(buf)-2, ::std::ios::out)
    {
        *this << str;
    }
    explicit stlstream(const ::std::string& str)
        : ::std::strstream(buf, sizeof(buf)-2, ::std::ios::out)
    {
        *this << str;
    }
public:
    ::std::string str() const
    {
        return const_cast<stlstream*>(this)->str();
    }
    virtual ::std::string str()
    {
        *this << ::std::ends;
        ::std::string str = ::std::strstream::str();
        return str;
    }
};

IUTEST_PRAGMA_MSC_WARN_POP()

#else
    typedef iu_basic_stream<char, ::std::char_traits<char> >        iu_stream;
    typedef iu_basic_stream<wchar_t, ::std::char_traits<wchar_t> >  iu_wstream;
#endif

//======================================================================
// class

#if !IUTEST_HAS_STRINGSTREAM && !IUTEST_HAS_STRSTREAM

template<class _Elem, class _Traits>
class iu_basic_stream
{
    typedef iu_basic_stream<_Elem, _Traits>         _Myt;
    //typedef ::std::basic_streambuf<_Elem, _Traits>    streambuf;
    //typedef ::std::basic_ostream<_Elem, _Traits>  ostream;
    typedef ::std::basic_string<_Elem, _Traits>     string;
    string s;

    template<typename T>
    struct xcs
    {
    private:
        template<typename TMP, typename TN>
        struct impl_select
        {
            template<typename TA, typename TB>
            static const TA constant(const TA a, const TB b)
            {
                (void)b;
                return a;
            }
        };
        template<typename TMP>
        struct impl_select<TMP, wchar_t>
        {
            template<typename TA, typename TB>
            static const TB constant(const TA a, const TB b)
            {
                (void)a;
                return b;
            }
        };

    public:
        typedef impl_select<void, T> select;
    };
#define IIUT_PP_XCS(txt_)   xcs<_Elem>::select::constant(txt_, L##txt_)

    struct impl
    {
        template<typename E>
        static int vastring(E* dst, const E* fmt, va_list va);
        static int vastring(char* dst, size_t len, const char* fmt, va_list va)
        {
            (void)len;
            return vsprintf(dst, fmt, va);
        }
        static int vastring(wchar_t* dst, size_t len, const wchar_t* fmt, va_list va)
        {
#ifdef IUTEST_OS_WINDOWS_MINGW
            return _vsnwprintf(dst, len, fmt, va);
#else
            return vswprintf(dst, len, fmt, va);
#endif
        }

        template<typename E>
        static int tostring(E* dst, size_t len, const E* fmt, ...)
        {
            va_list va;
            va_start(va, fmt);
            int ret = vastring(dst, len, fmt, va);
            va_end(va);
            return ret;
        }
    };
public:
    iu_basic_stream() {}
    explicit iu_basic_stream(const char* str) : s(str) {}
    explicit iu_basic_stream(const ::std::string& str) : s(str) {}

public:
    inline _Myt& operator<< (char v)
    {
        s += v;
        return *this;
    }
    inline _Myt& operator<< (signed char v)
    {
        s += static_cast<char>(v);
        return *this;
    }
    inline _Myt& operator<< (unsigned char v)
    {
        s += static_cast<char>(v);
        return *this;
    }
    inline _Myt& operator<< (const _Elem* v)
    {
        s += v;
        return *this;
    }
    //inline _Myt& operator<< (const signed _Elem* v)
    //{
    //  s += v;
    //  return *this;
    //}
    //inline _Myt& operator<< (const unsigned _Elem* v)
    //{
    //  s += v;
    //  return *this;
    //}
    inline _Myt& operator<< (bool v)
    {
#if 0
        _Elem a[16];
        impl::tostring(a, 16, IIUT_PP_XCS("%i"), v);
        s += a;
#else
        s += (v ? IIUT_PP_XCS("true") : IIUT_PP_XCS("false"));
#endif
        return *this;
    }
    inline _Myt& operator<< (short v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%i"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (unsigned short v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%u"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (int v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%i"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (unsigned int v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%u"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (long v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%i"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (unsigned long v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%u"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (long long int v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%lld"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (unsigned long long int v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%llu"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (float v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%f"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (double v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%l"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (long double v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%L"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (const void* v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%t"), v);
        s += a;
        return *this;
    }
    inline _Myt& operator<< (const ::std::string& v)
    {
        s += v;
        return *this;
    }
public:
    const string& str() const { return s; }
    void copyfmt(const _Myt&) {}
};

#undef IIUT_PP_XCS

#endif

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}   // end of namespace detail

#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM

typedef ::std::ostream iu_ostream;
typedef ::std::ostream& (*iu_basic_iomanip)(::std::ostream&);
typedef detail::stlstream iu_stringstream;

#else

typedef detail::iu_stream iu_ostream;
typedef detail::iu_stream iu_stringstream;

#endif

#if !defined(IUTEST_HAS_BIGGESTINT_OSTREAM)
#  if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
#    if (defined(_STLPORT_VERSION) && !defined(_STLP_LONG_LONG)) || (defined(_MSC_VER) && _MSC_VER < 1310)
#      define IUTEST_HAS_BIGGESTINT_OSTREAM     0
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_BIGGESTINT_OSTREAM)
#  define IUTEST_HAS_BIGGESTINT_OSTREAM         1
#endif

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_STRING_HPP_E22B02D7_E9E7_412C_B609_DC3D9C66895D_
