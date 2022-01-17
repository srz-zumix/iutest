//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_string_stream.hpp
 * @brief       iris unit test iu_basic_ostream implimentaion
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_STRING_STREAM_HPP_F446E84B_1C7D_49C4_9A2D_5002CCE3F486_
#define INCG_IRIS_IUTEST_STRING_STREAM_HPP_F446E84B_1C7D_49C4_9A2D_5002CCE3F486_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_string.hpp"
// IWYU pragma: end_exports

#if   IUTEST_HAS_STRINGSTREAM
#  include <sstream>
#elif IUTEST_HAS_STRSTREAM
#  include <strstream>
#endif
#if IUTEST_HAS_IOMANIP
#  include <iomanip>
#endif
#if IUTEST_HAS_EXCEPTIONS
#  include <stdexcept>
#endif

namespace iutest
{

namespace detail
{

template<typename T>
bool StringToValue(const ::std::string& s, T& out)
{
#if IUTEST_HAS_STRINGSTREAM
    ::std::istringstream strm(s);
    if( strm >> out )
    {
        return true;
    }
    return false;
#elif IUTEST_HAS_STD_STR_TO_VALUE
    out = static_cast<T>(::std::stoull(s));
    return true;
#else
    char* endptr=NULL;
    const char* p = s.c_str();
    errno = 0;
    const unsigned long long v = strtoull(p, &endptr, 10);
    if(p == endptr)
    {
#if IUTEST_HAS_EXCEPTIONS
        throw ::std::invalid_argument(p);
#else
        return false;
#endif
    }
    if(errno == ERANGE)
    {
#if IUTEST_HAS_EXCEPTIONS
        throw ::std::out_of_range(p);
#else
        return false;
#endif
    }
    out = static_cast<T>(v);
    return true;
#endif
}

inline bool StringToValue(const ::std::string& s, float& out)
{
#if IUTEST_HAS_STD_STR_TO_VALUE
    out = ::std::stof(s);
#else
    char* endptr=NULL;
    const char* p = s.c_str();
    errno = 0;
#if !defined(IUTEST_OS_WINDOWS_MINGW) || !defined(__STRICT_ANSI__)
    const floating_point<float> v = strtof(p, &endptr);
#else
    const floating_point<float> v = static_cast<float>(strtod(p, &endptr));
#endif
    if(p == endptr)
    {
#if IUTEST_HAS_EXCEPTIONS
        throw ::std::invalid_argument(p);
#else
        return false;
#endif
    }
    if((errno == ERANGE) || v.is_inf() )
    {
#if IUTEST_HAS_EXCEPTIONS
        throw ::std::out_of_range(p);
#else
        return false;
#endif
    }
    out = v;
#endif
    return true;
}

inline bool StringToValue(const ::std::string& s, double& out)
{
#if IUTEST_HAS_STD_STR_TO_VALUE
    out = ::std::stod(s);
#else
    char* endptr=NULL;
    const char* p = s.c_str();
    errno = 0;
    const floating_point<double> v = strtod(p, &endptr);
    if(p == endptr)
    {
#if IUTEST_HAS_EXCEPTIONS
        throw ::std::invalid_argument(p);
#else
        return false;
#endif
    }
    if((errno == ERANGE) || v.is_inf() )
    {
#if IUTEST_HAS_EXCEPTIONS
        throw ::std::out_of_range(p);
#else
        return false;
#endif
    }
    out = v;
#endif
    return true;
}

#if IUTEST_HAS_LONG_DOUBLE

inline bool StringToValue(const ::std::string& s, long double& out)
{
#if IUTEST_HAS_STD_STR_TO_VALUE
    out = ::std::stold(s);
#else
    char* endptr=NULL;
    const char* p = s.c_str();
    errno = 0;
    const floating_point<long double> v = strtold(p, &endptr);
    if(p == endptr)
    {
#if IUTEST_HAS_EXCEPTIONS
        throw ::std::invalid_argument(p);
#else
        return false;
#endif
    }
    if((errno == ERANGE) || v.is_inf() )
    {
#if IUTEST_HAS_EXCEPTIONS
        throw ::std::out_of_range(p);
#else
        return false;
#endif
    }
    out = v;
#endif
    return true;
}

#endif

#if !IUTEST_HAS_STRINGSTREAM && !IUTEST_HAS_STRSTREAM

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()

//======================================================================
// class

template<class _Elem, class _Traits>
class iu_basic_ostream
{
    typedef iu_basic_ostream<_Elem, _Traits>         _Myt;
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

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_FORMAT_NONLITERAL()
    struct impl
    {
        template<typename E>
        static int vastring(E* dst, const E* fmt, va_list va);
        static int vastring(char* dst, size_t len, const char* fmt, va_list va) IUTEST_ATTRIBUTE_FORMAT_PRINTF(3, 0)
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
            const int ret = vastring(dst, len, fmt, va);
            va_end(va);
            return ret;
        }
    };
IUTEST_PRAGMA_WARN_POP()

public:
    iu_basic_ostream() {}
    explicit iu_basic_ostream(const char* str) : s(str) {}
    explicit iu_basic_ostream(const ::std::string& str) : s(str) {}

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
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_DOUBLE_PROMOTION()
        impl::tostring(a, 64, IIUT_PP_XCS("%f"), v);
IUTEST_PRAGMA_WARN_POP()
        s += a;
        return *this;
    }
    inline _Myt& operator<< (double v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%lf"), v);
        s += a;
        return *this;
    }
#if IUTEST_HAS_LONG_DOUBLE
    inline _Myt& operator<< (long double v)
    {
        _Elem a[64];
        impl::tostring(a, 64, IIUT_PP_XCS("%Lf"), v);
        s += a;
        return *this;
    }
#endif
#if IUTEST_HAS_FLOAT128
    inline _Myt& operator<< (internal::Float128::Float v)
    {
        _Elem a[64];
        const double d = static_cast<double>(v);
        impl::tostring(a, 64, IIUT_PP_XCS("%L"), d);
        s += a;
        return *this;
    }
#endif
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

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

#endif

//======================================================================
// declare
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

#endif

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()

}   // end of namespace detail

#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM

typedef ::std::ostream iu_ostream;
typedef detail::stlstream iu_stringstream;

#else

typedef detail::iu_basic_ostream<char, ::std::char_traits<char> >        iu_ostream;
typedef detail::iu_basic_ostream<wchar_t, ::std::char_traits<wchar_t> >  iu_wostream;
typedef iu_ostream  iu_stringstream;

#endif

#if IUTEST_HAS_IOMANIP
typedef iu_ostream& (*iu_basic_iomanip)(iu_ostream&);
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

#endif // INCG_IRIS_IUTEST_STRING_STREAM_HPP_F446E84B_1C7D_49C4_9A2D_5002CCE3F486_
