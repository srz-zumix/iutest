//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_printers.hpp
 * @brief       iris unit test print 出力ヘルパー ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PRINTERS_HPP_A6A321C9_9279_4336_8167_058C59EC0FD0_
#define INCG_IRIS_IUTEST_PRINTERS_HPP_A6A321C9_9279_4336_8167_058C59EC0FD0_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_defs.hpp"
#include "internal/iutest_string_stream.hpp"
#include "internal/iutest_string_view.hpp"
// IWYU pragma: end_exports

#if IUTEST_USE_QUADMATH
#  include <quadmath.h>
#endif


namespace iutest
{

// PrintTo (User defined)
// PrintTo (iutest)
//   DefaultPrintTo
//      container
//      pointer
//      ostream operator <<
//      BiggestInt
//      bytes

//======================================================================
// declare
template<typename T>
std::string PrintToString(const T& v);

namespace detail
{

template<typename T>
void UniversalPrint(const T& value, iu_ostream* os);

inline void PrintBytesInObjectTo(const unsigned char* buf, size_t size, iu_ostream* os)
{
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
    const size_t kMaxCount = detail::kValues::MaxPrintContainerCount;
    *os << size << "-Byte object < ";
    if( buf != IUTEST_NULLPTR && size > 0 )
    {
        for( size_t i=0; i < size; ++i )
        {
            if( i == kMaxCount )
            {
                *os << "... ";
                break;
            }
#ifdef __clang_analyzer__
            const unsigned char n = 0;  // suppress
#else
            const unsigned char n = buf[i];
#endif
            *os << ToHex((n>>4)&0xF) << ToHex(n&0xF) << " ";
        }
    }
    *os << ">";
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
}

namespace printer_internal
{

namespace formatter
{

struct RawBytesPrinter
{
    template<typename T>
    static void Print(const T& value, iu_ostream* os)
    {
        const unsigned char* ptr = const_cast<const unsigned char*>(
            reinterpret_cast<const volatile unsigned char*>(&value));
        const size_t size = sizeof(T);
        PrintBytesInObjectTo(ptr, size, os);
    }
};

struct StringViewPrinter
{
    static void Print(iu_string_view value, iu_ostream* os)
    {
        UniversalPrint(value, os);
    }
};

struct BiggestIntPrinter
{
    static void Print(BiggestInt value, iu_ostream* os)
    {
#if IUTEST_HAS_BIGGESTINT_OSTREAM
        *os << value;
#else
        const Int32 v = value;
        *os << v;
#endif
    }
};

/** @private */
template<typename T>
struct PrinterTypeSelecter
{
    typedef typename iutest_type_traits::conditional<iutest_type_traits::is_convertible<T, BiggestInt>::value
        , BiggestIntPrinter
        , typename iutest_type_traits::conditional<iutest_type_traits::is_convertible<T, iu_string_view>::value
            , StringViewPrinter
            , RawBytesPrinter
        >::type
    >::type type;
};

}   // end of namespace formatter

/** @private */
class TypeWithoutFormatter
{
public:
    template<typename T>
    static void PrintValue(const T& value, iu_ostream* os)
    {
        typedef typename formatter::PrinterTypeSelecter<const T&>::type Printer;
        Printer::Print(value, os);
    }
};

#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)

#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
template<typename Elem, typename Traits, typename T>
::std::basic_ostream<Elem, Traits>& operator << (::std::basic_ostream<Elem, Traits>& os, const T& value)
{
    TypeWithoutFormatter::PrintValue(value, &os);
    return os;
}
#else
template<typename Elem, typename Traits, typename T>
detail::iu_basic_ostream<Elem, Traits>& operator << (detail::iu_basic_ostream<Elem, Traits>& os, const T& value)
{
    TypeWithoutFormatter::PrintValue(value, &os);
    return os;
}
#endif

#endif

}   // end of namespace printer_internal

namespace printer_internal2
{

// 解決順序
// foo::operator <<
// ::operator <<
// ::iutest::detail::printer_internal::operator <<
template<typename T>
void DefaultPrintNonContainerTo(const T& value, iu_ostream* os)
{
    using namespace ::iutest::detail::printer_internal; // NOLINT
    *os << value;
}

}   // end of namespace printer_internal2

//======================================================================
// declare

//======================================================================
// function
/**
 * @brief   デフォルト文字列変換関数
*/
template<typename T>
inline void DefaultPrintTo(IsContainerHelper::yes_t
                        , iutest_type_traits::false_type
                        , const T& container, iu_ostream* os)
{
    const size_t kMaxCount = kValues::MaxPrintContainerCount;
    size_t count = 0;
    *os << "{";
    for( typename T::const_iterator it=container.begin(), end=container.end(); it != end; ++it, ++count)
    {
        if( count > 0 )
        {
            *os << ",";
            if( count == kMaxCount )
            {
                *os << " ...";
                break;
            }
        }
        *os << " ";
        UniversalPrint(*it, os);
    }
    if( count > 0 )
    {
        *os << " ";
    }
    *os << "}";
}

template<typename T>
inline void DefaultPrintNonContainerTo(const T& value, iu_ostream* os)
{
#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    printer_internal2::DefaultPrintNonContainerTo(value, os);
#else
    printer_internal::formatter::RawBytesPrinter::Print(value, os);
#endif
}
/** @overload */
template<typename T>
inline void DefaultPrintTo(IsContainerHelper::no_t
                        , iutest_type_traits::false_type
                        , const T& value, iu_ostream* os)
{
    DefaultPrintNonContainerTo(value, os);
}

#if !defined(IUTEST_NO_SFINAE) && !defined(IUTEST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template<typename T>
inline void DefaultPtrPrintTo(T* ptr, iu_ostream* os
    , typename iutest_type_traits::enable_if_t< iutest_type_traits::is_convertible<T*, const void*> >::type*& = iutest_type_traits::enabler::value)
{
    *os << reinterpret_cast<iu_uintptr_t>(ptr);
}
template<typename T>
inline void DefaultPtrPrintTo(T* ptr, iu_ostream* os
    , typename iutest_type_traits::disable_if_t< iutest_type_traits::is_convertible<T*, const void*> >::type*& = iutest_type_traits::enabler::value)
{
    *os << reinterpret_cast<const void*>(reinterpret_cast<type_least_t<8>::UInt>(ptr));
}

#else

template<typename T>
inline void DefaultPtrPrintTo(T* ptr, iu_ostream* os)
{
    *os << reinterpret_cast<const void*>(reinterpret_cast<type_least_t<8>::UInt>(ptr));
}

#endif

template<typename T>
inline void DefaultPrintTo(IsContainerHelper::no_t
                        , iutest_type_traits::true_type
                        , T* ptr, iu_ostream* os)
{
    if( ptr == IUTEST_NULLPTR )
    {
        *os << kStrings::Null;
    }
    else
    {
        DefaultPtrPrintTo<T>(ptr, os);
    }
}


/** @private */
template<typename T>
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const T& value, iu_ostream* os)
{
    UniversalPrint(value, os);
}

inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char* str, iu_ostream* os)
{
    if( str == IUTEST_NULLPTR )
    {
        *os << kStrings::Null;
    }
    else
    {
        UniversalPrint(::std::string(str), os);
    }
}
template<size_t N>
void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char(&str)[N], iu_ostream* os)
{
    return UniversalTersePrint(static_cast<const char*>(str), os);
}
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const wchar_t* str, iu_ostream* os)
{
    UniversalPrint(detail::ShowAnyCString(str), os);
}
template<size_t N>
void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const wchar_t(&str)[N], iu_ostream* os)
{
    UniversalPrint(detail::ShowAnyCString(str), os);
}
#if IUTEST_HAS_CHAR16_T
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char16_t* str, iu_ostream* os)
{
    UniversalPrint(detail::ShowAnyCString(str), os);
}
template<size_t N>
void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char16_t(&str)[N], iu_ostream* os)
{
    UniversalPrint(detail::ShowAnyCString(str), os);
}
#endif
#if IUTEST_HAS_CHAR32_T && (IUTEST_HAS_CXX_HDR_CUCHAR || IUTEST_HAS_CXX_HDR_CODECVT)
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char32_t* str, iu_ostream* os)
{
    UniversalPrint(detail::ShowAnyCString(str), os);
}
template<size_t N>
void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char32_t(&str)[N], iu_ostream* os)
{
    UniversalPrint(detail::ShowAnyCString(str), os);
}
#endif

/**
 * @brief   文字列変換関数
*/
template<typename T>
inline void PrintTo(const T& value, iu_ostream* os) {
    DefaultPrintTo(
#if !defined(IUTEST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS)
        IsContainerHelper::IsContainer<T>(0)
#else
        IsContainerHelper::IsContainer(0, detail::explicit_type<T>())
#endif
        , iutest_type_traits::is_pointer<T>(), value, os);
}
inline void PrintTo(bool b, iu_ostream* os)         { *os << (b ? "true" : "false"); }
inline void PrintTo(const char* c, iu_ostream* os)  { *os << c; }
#if defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
inline void PrintTo(int v, iu_ostream* os)  { *os << v; }
#endif
inline void PrintTo(const ::std::string& str, iu_ostream* os)   { *os << str.c_str(); }
template<typename CharT, typename Traits, typename Alloc>
inline void PrintTo(const ::std::basic_string<CharT, Traits, Alloc>& str, iu_ostream* os) { UniversalTersePrint(str.c_str(), os); }
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
template<typename T>
inline void PrintToFloatingPoint(const floating_point<T>& f, iu_ostream* os)
{
    iu_stringstream ss;
#if IUTEST_HAS_IOMANIP
    ss << ::std::setprecision(::std::numeric_limits<T>::digits10 + 2);
#endif
    UniversalPrint(f.raw(), &ss);
    *os << ss.str() << "(0x" << ToHexString(f.bits()) << ")";
}
template<typename T>
inline void PrintTo(const floating_point<T>& f, iu_ostream* os)
{
    PrintToFloatingPoint(f, os);
}
template<typename T>
inline void PrintTo(const internal::FloatingPoint<T>& f, iu_ostream* os)
{
    PrintToFloatingPoint(f, os);
}
template<typename T1, typename T2>
inline void PrintTo(const ::std::pair<T1, T2>& value, iu_ostream* os)
{
    *os << "(";
    UniversalPrint(value.first, os);
    *os << ", ";
    UniversalPrint(value.second, os);
    *os << ")";
}
#endif

#if IUTEST_HAS_INT128
inline void PrintTo(detail::type_fit_t<16>::Int v, iu_ostream* os)
{
    *os << "0x" << ToHexString(v);
}
inline void PrintTo(detail::type_fit_t<16>::UInt v, iu_ostream* os)
{
    *os << "0x" << ToHexString(v);
}
#endif

#if IUTEST_HAS_FLOAT128
template<typename T>
inline void PrintToFloat128(const T v, iu_ostream* os)
{
#if   IUTEST_USE_QUADMATH
    char buf[256] = {0};
    quadmath_snprintf(buf, sizeof(buf), "%Qf", v);
    *os << buf;
#elif IUTEST_HAS_LONG_DOUBLE && IUTEST_LONG_DOUBLE_AS_IS_DOUBLE
    *os << static_cast<long double>(v);
#else
    *os << static_cast<double>(v);
#endif
}

// NOTE: need libquadmath
inline void PrintTo(const internal::Float128::Float v, iu_ostream* os)
{
    PrintToFloat128(v, os);
}

#if IUTEST_HAS_LONG_DOUBLE && !IUTEST_LONG_DOUBLE_AS_IS_DOUBLE
inline void PrintTo(const long double v, iu_ostream* os)
{
    PrintToFloat128(v, os);
}
#endif

#endif

template<typename T>
void PrintToChar(const T value, iu_ostream* os)
{
    // char or unsigned char の時に、 0 が NULL 文字にならないように修正
    if( value == 0 )
    {
        *os << "\\0";
    }
    else if( static_cast<int>(value) < 0x20 )
    {
        *os << "0x" << ToHexString(value);
    }
    else
    {
        const T str[2] = { value, 0 };
        *os << "\'" << detail::ShowAnyCString(str) << "\'";
    }
}
inline void PrintTo(const char value, iu_ostream* os)
{
    PrintToChar(static_cast<signed char>(value), os);
}
inline void PrintTo(const wchar_t value, iu_ostream* os)
{
    PrintToChar(value, os);
}
#if IUTEST_HAS_CHAR16_T
inline void PrintTo(const char16_t value, iu_ostream* os)
{
    PrintToChar(value, os);
}
#endif
#if IUTEST_HAS_CHAR32_T
inline void PrintTo(const char32_t value, iu_ostream* os)
{
    PrintToChar(value, os);
}
#endif
inline void PrintTo(const unsigned char value, iu_ostream* os)
{
    *os << static_cast<unsigned int>(value);
}
#if IUTEST_USE_OWN_STRING_VIEW
template<typename CharT, typename Traits>
inline void PrintTo(const iu_basic_string_view<CharT, Traits>& value, iu_ostream* os)
{
    const ::std::basic_string<CharT, Traits> str = value.data();
    UniversalTersePrint(str.c_str(), os);
}
#else
template<typename CharT, typename Traits>
inline void PrintTo(const ::std::basic_string_view<CharT, Traits>& value, iu_ostream* os)
{
    const ::std::basic_string<CharT, Traits> str{ value };
    UniversalTersePrint(str.c_str(), os);
}
#endif

#if IUTEST_HAS_CXX_HDR_OPTIONAL
template<typename T>
inline void PrintTo(const ::std::optional<T>& value, iu_ostream* os)
{
    if (value)
    {
        UniversalPrint(value.value(), os);
    }
    else
    {
        *os << "nullopt";
    }
}
#endif

#if IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_CXX_HDR_VARIANT
template<typename... Types>
inline void PrintTo(const ::std::variant<Types...>& value, iu_ostream* os)
{
    if (value.valueless_by_exception())
    {
        *os << "valueless_by_exception";
    }
    else
    {
        ::std::visit([&os](const auto& v) { UniversalPrint(v, os); }, value);
    }
}
inline void PrintTo(const ::std::monostate&, iu_ostream* os)
{
    *os << "monostate";
}
#endif

#if IUTEST_HAS_CXX_HDR_ANY
inline void PrintTo(const ::std::any& value, iu_ostream* os)
{
    *os << "-Any type-name: " << value.type().name();
    DefaultPrintNonContainerTo(value, os);
}
#endif

#if IUTEST_HAS_STD_FILESYSTEM
inline ::std::string FileSystemFileTypeToString(const ::std::filesystem::file_type& value)
{
    switch(value)
    {
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, none);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, not_found);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, regular);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, directory);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, symlink);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, block);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, character);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, fifo);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, socket);
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, unknown);
#if defined(IUTEST_OS_WINDOWS) && !defined(IUTEST_OS_WINDOWS_MINGW)
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, junction);
#endif
    }
    return PrintToString(static_cast<int>(value));
}
template<>
inline void PrintTo< ::std::filesystem::path >(const ::std::filesystem::path& value, iu_ostream* os)
{
    *os << value.generic_string();
}
inline void PrintTo(const ::std::filesystem::file_type& value, iu_ostream* os)
{
    *os << FileSystemFileTypeToString(value);
}
inline void PrintTo(const ::std::filesystem::perms& value, iu_ostream* os)
{
    *os << ToOctString(static_cast<UInt16>(value));
}
inline void PrintTo(const ::std::filesystem::file_status& value, iu_ostream* os)
{
    *os << FileSystemFileTypeToString(value.type()) << ": ";
    PrintTo(value.permissions(), os);
}
inline void PrintTo(const ::std::filesystem::space_info& value, iu_ostream* os)
{
    *os << "cpacity: " << detail::FormatSizeByte(value.capacity)
        << ", free: " << detail::FormatSizeByte(value.free)
        << ", available: " << detail::FormatSizeByte(value.available);
}
inline void PrintTo(const ::std::filesystem::directory_entry& value, iu_ostream* os)
{
    PrintTo(value.path(), os);
}
inline void PrintTo(const ::std::filesystem::directory_iterator& value, iu_ostream* os)
{
    PrintTo(*value, os);
}
#endif

#if IUTEST_HAS_NULLPTR
inline void PrintTo(const ::std::nullptr_t&, iu_ostream* os) { *os << "nullptr"; }
#endif

#if IUTEST_HAS_TUPLE

template<typename T, int I, int SIZE>
inline void PrintTupleElemTo(const T& t, iu_ostream* os
    , typename iutest_type_traits::enable_if<I == 0, void>::type*& = iutest_type_traits::enabler::value)
{
    IUTEST_UNUSED_VAR(t);
    IUTEST_UNUSED_VAR(os);
}
template<typename T, int I, int SIZE>
inline void PrintTupleElemTo(const T& t, iu_ostream* os
    , typename iutest_type_traits::enable_if<I == 1, void>::type*& = iutest_type_traits::enabler::value)
{
    PrintTo(tuples::get<SIZE-I>(t), os);
}
template<typename T, int I, int SIZE>
inline void PrintTupleElemTo(const T& t, iu_ostream* os
    , typename iutest_type_traits::enable_if<(I&(~1)) != 0, void>::type*& = iutest_type_traits::enabler::value)
{
    PrintTo(tuples::get<SIZE-I>(t), os);
    *os << ", ";
    PrintTupleElemTo<T, I-1, SIZE>(t, os);
}

template<typename T>
inline void PrintTupleTo(const T& t, iu_ostream* os)
{
    *os << "(";
    PrintTupleElemTo<T, tuples::tuple_size<T>::value, tuples::tuple_size<T>::value>(t, os);
    *os << ")";
}

#if IUTEST_HAS_VARIADIC_TEMPLATES && IUTEST_HAS_TUPLE

template<typename ...Args>
inline void PrintTo(const tuples::tuple<Args...>& t, iu_ostream* os)
{
    PrintTupleTo(t, os);
}

#else

#define IIUT_DECL_TUPLE_PRINTTO(n)                                              \
    template<IUTEST_PP_ENUM_PARAMS(n, typename A)>inline void PrintTo(          \
        const tuples::tuple<IUTEST_PP_ENUM_PARAMS(n, A)>& t, iu_ostream* os) {  \
            PrintTupleTo(t, os); }

inline void PrintTo(const tuples::tuple<>& t, iu_ostream* os) { PrintTupleTo(t, os); }

IIUT_DECL_TUPLE_PRINTTO(1)
IIUT_DECL_TUPLE_PRINTTO(2)
IIUT_DECL_TUPLE_PRINTTO(3)
IIUT_DECL_TUPLE_PRINTTO(4)
IIUT_DECL_TUPLE_PRINTTO(5)
IIUT_DECL_TUPLE_PRINTTO(6)
IIUT_DECL_TUPLE_PRINTTO(7)
IIUT_DECL_TUPLE_PRINTTO(8)
IIUT_DECL_TUPLE_PRINTTO(9)

#undef IIUT_DECL_TUPLE_PRINTTO

#endif

#endif

/**
 * @brief   配列の出力
*/
template<typename T>
inline void PrintRawArrayTo(const T* a, size_t cnt, iu_ostream* os)
{
    UniversalPrint<T>(a[0], os);
    for( size_t i=1; i < cnt; ++i )
    {
        *os << ", ";
        UniversalPrint<T>(a[i], os);
    }
}

/**
 * @brief   配列の出力
*/
template<typename T>
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalPrintArray(const T* begin, size_t N, iu_ostream* os)
{
    if( N == 0 )
    {
        *os << "{}";
    }
    else
    {
        *os << "{ ";
        const size_t kThreshold = kValues::PrintArrayThreshold;
        const size_t kChunksize = kValues::PrintArrayChunksize;
        if( N <= kThreshold )
        {
            PrintRawArrayTo(begin, N, os);
        }
        else
        {
            PrintRawArrayTo(begin, kChunksize, os);
            *os << ", ..., ";
            PrintRawArrayTo(begin + N - kChunksize, kChunksize, os);
        }
        *os << " }";
    }
}
/**
 * @brief   配列の出力
*/
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalPrintArray(const char* begin, size_t N, iu_ostream* os)
{
    IUTEST_UNUSED_VAR(N);
    UniversalTersePrint(begin, os);
}
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalPrintArray(const wchar_t* begin, size_t N, iu_ostream* os)
{
    IUTEST_UNUSED_VAR(N);
    UniversalTersePrint(begin, os);
}

/** @private */
template<typename T>
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalPrintTo(const T& value, iu_ostream* os)
{
    PrintTo(value, os);
}

//======================================================================
// class
/** @private */
template<typename T>
class iuUniversalPrinter
{
public:
    static void Print(const T& value, iu_ostream* os)
    {
        UniversalPrintTo(value, os);
    }
};

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)

/** @private */
template<typename T, size_t SIZE>
class iuUniversalPrinter<T[SIZE]>
{
public:
    static void Print(const T(&a)[SIZE], iu_ostream* os)
    {
        UniversalPrintArray(a, SIZE, os);
    }
};

#endif

//======================================================================
// function
/** @private */
template<typename T>
inline void UniversalPrint(const T& value, iu_ostream* os)
{
#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
    iuUniversalPrinter<T>::Print(value, os);
#else
    UniversalPrintTo(value, os);
#endif
}

}   // end of namespace detail

//======================================================================
// function

/**
 * @brief   文字列化
*/
template<typename T>
inline ::std::string PrintToString(const T& v)
{
    iu_global_format_stringstream strm;
    detail::UniversalTersePrint(v, &strm);
    return strm.str();
}

#if IUTEST_HAS_VARIADIC_TEMPLATES
/**
 * @brief   文字列化
*/
template<typename T>
inline ::std::string PrintToStrings(const char* separate, const T& v)
{
    IUTEST_UNUSED_VAR(separate);
    return PrintToString(v);
}
/**
 * @brief   文字列化
*/
template<typename T, typename ...Args>
inline ::std::string PrintToStrings(const char* separate, const T& v, Args... args)
{
    ::std::string str = PrintToString(v);
    str += separate;
    str += PrintToStrings(separate, args...);
    return str;
}
#endif

}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_PRINTERS_HPP_A6A321C9_9279_4336_8167_058C59EC0FD0_
