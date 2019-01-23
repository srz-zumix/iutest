﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_printers.hpp
 * @brief       iris unit test print 出力ヘルパー ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PRINTERS_HPP_A6A321C9_9279_4336_8167_058C59EC0FD0_
#define INCG_IRIS_IUTEST_PRINTERS_HPP_A6A321C9_9279_4336_8167_058C59EC0FD0_

//======================================================================
// include
#include "iutest_defs.hpp"
#include "iutest_any.hpp"
#include "internal/iutest_printers_printto_defs.hpp"
#include "internal/iutest_string.hpp"

namespace iutest {
namespace detail
{

inline void PrintBytesInObjectTo(const unsigned char* buf, size_t size, iu_ostream* os)
{
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_BEGIN()
    const size_t kMaxCount = detail::kValues::MaxPrintContainerCount;
    *os << size << "-Byte object < ";
    for( size_t i=0; i < size; ++i )
    {
        const unsigned char n = buf[i];
        *os << detail::ToHex((n>>4)&0xF) << ToHex(n&0xF) << " ";
        if( i == kMaxCount )
        {
            *os << "... ";
            break;
        }
    }
    *os << ">";
IUTEST_PRAGMA_CONSTEXPR_CALLED_AT_RUNTIME_WARN_DISABLE_END()
}

namespace printer_internal
{

namespace formatter
{

/** @private */
template<bool convertible>
struct Printer
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

template<>
struct Printer<true>
{
    template<typename T>
    static void Print(const T& value, iu_ostream* os)
    {
#if IUTEST_HAS_BIGGESTINT_OSTREAM
        const BiggestInt v = value;
#else
        const Int32 v = value;
#endif
        *os << v;
    }
};

}   // end of namespace formatter

/** @private */
class TypeWithoutFormatter
{
public:
    template<typename T>
    static void PrintValue(const T& value, iu_ostream* os)
    {
        formatter::Printer<
            iutest_type_traits::is_convertible<const T&, BiggestInt>::value>::Print(value, os);
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
template<typename T>
iu_ostream& operator << (iu_ostream& os, const T& value)
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
    printer_internal::formatter::Printer<false>::Print(value, os);
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
    *os << ptr;
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
    if( ptr == NULL )
    {
        *os << kStrings::Null;
    }
    else
    {
        DefaultPtrPrintTo<T>(ptr, os);
    }
}

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

/** @private */
template<typename T>
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const T& value, iu_ostream* os)
{
    UniversalPrint(value, os);
}

inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char* str, iu_ostream* os)
{
    if( str == NULL )
    {
        *os << kStrings::Null;
    }
    else
    {
        UniversalPrint(::std::string(str), os);
    }
}
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const wchar_t* str, iu_ostream* os)
{
    UniversalPrint(detail::ShowWideCString(str), os);
}
#if IUTEST_HAS_CHAR16_T
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char16_t* str, iu_ostream* os)
{
    UniversalPrint(detail::ShowWideCString(str), os);
}
#endif
#if IUTEST_HAS_CHAR32_T && (IUTEST_HAS_CXX_HDR_CUCHAR || IUTEST_HAS_CXX_HDR_CODECVT)
inline void IUTEST_ATTRIBUTE_UNUSED_ UniversalTersePrint(const char32_t* str, iu_ostream* os)
{
    UniversalPrint(detail::ShowWideCString(str), os);
}
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
        *os << "{";
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
        *os << "}";
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
    using namespace ::iutest::detail::printer_iutest_printto; // NOLINT
    using namespace ::iutest::detail::printer_stdlib_printto; // NOLINT
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
