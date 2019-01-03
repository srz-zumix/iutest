//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_printers_printto_defs.hpp
 * @brief       iris unit test default print to operaters 
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_PRINTERS_PRINTTO_DEFS_HPP_52DAF156_7F2D_4AF2_B4CA_9412A1FBCE39_
#define INCG_IRIS_IUTEST_PRINTERS_PRINTTO_DEFS_HPP_52DAF156_7F2D_4AF2_B4CA_9412A1FBCE39_

//======================================================================
// define

namespace iutest {
namespace detail
{

//======================================================================
// declare
template<typename T>
void UniversalPrint(const T& value, iu_ostream* os);
template<typename T>
void DefaultPrintNonContainerTo(const T& value, iu_ostream* os);

//======================================================================
// function
#if defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
inline void PrintTo(int v, iu_ostream* os)  { *os << v; }
#endif

namespace printer_iutest_printto
{

inline void PrintTo(const any& value, iu_ostream* os)
{
    *os << value.to_string();
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)
template<typename T>
inline void PrintTo(const floating_point<T>& f, iu_ostream* os)
{
    *os << f.raw() << "(0x" << ToHexString(f.bits()) << ")";
}
#endif

}   // end of namespace printer_iutest_printto

namespace printer_stdlib_printto
{

template<typename CharT, typename Traits, typename Alloc>
inline void PrintTo(const ::std::basic_string<CharT, Traits, Alloc>& str, iu_ostream* os)
{
    *os << str.c_str();
}

#if !defined(IUTEST_NO_FUNCTION_TEMPLATE_ORDERING)

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

#if IUTEST_HAS_NULLPTR
inline void PrintTo(const ::std::nullptr_t&, iu_ostream* os)
{
    *os << "nullptr";
}
#endif


#if IUTEST_HAS_CXX_HDR_STRING_VIEW
template<typename CharT, typename Traits>
inline void PrintTo(const ::std::basic_string_view<CharT, Traits>& value, iu_ostream* os)
{
    const ::std::basic_string<CharT, Traits> tmp{ value };
    *os << tmp;
}
#endif

#if IUTEST_HAS_CXX_HDR_ANY
inline void PrintTo(const ::std::any& value, iu_ostream* os)
{
    *os << "-Any type-name: " << value.type().name();
    DefaultPrintNonContainerTo(value, os);
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

#if IUTEST_HAS_CXX_HDR_VARIANT
template<typename... Types>
inline void PrintTo(const ::std::variant<Types...>& value, iu_ostream* os)
{
    if (value.valueless_by_exception())
    {
        *os << "valueless_by_exception";
    }
    else
    {
        std::visit([&os](const auto& v) { UniversalPrint(v, os); }, value);
    }
}
inline void PrintTo(const ::std::monostate&, iu_ostream* os)
{
    *os << "monostate";
}
#endif

#if IUTEST_USE_CXX_FILESYSTEM
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
#if defined(IUTEST_OS_WINDOWS)
    IUTEST_PP_NAMESPACE_ENUM_CASE_RETURN_STRING(::std::filesystem::file_type, junction);
#endif
    default:
        break;
    }
    return PrintToString(static_cast<int>(value));
}
inline void PrintTo(const ::std::filesystem::path& value, iu_ostream* os)
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
    UniversalPrint(value.permissions(), os);
}
inline void PrintTo(const ::std::filesystem::space_info& value, iu_ostream* os)
{
    *os << "cpacity: " << detail::FormatSizeByte(value.capacity)
        << ", free: " << detail::FormatSizeByte(value.free)
        << ", available: " << detail::FormatSizeByte(value.available);
}
inline void PrintTo(const ::std::filesystem::directory_entry& value, iu_ostream* os)
{
    UniversalPrint(value.path(), os);
}
inline void PrintTo(const ::std::filesystem::directory_iterator& value, iu_ostream* os)
{
    UniversalPrint(*value, os);
}
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
    UniversalPrint(tuples::get<SIZE-I>(t), os);
}
template<typename T, int I, int SIZE>
inline void PrintTupleElemTo(const T& t, iu_ostream* os
    , typename iutest_type_traits::enable_if<(I&(~1)) != 0, void>::type*& = iutest_type_traits::enabler::value)
{
    UniversalPrint(tuples::get<SIZE-I>(t), os);
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

}   // end of namespace printer_stdlib_printto
}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_PRINTERS_PRINTTO_DEFS_HPP_52DAF156_7F2D_4AF2_B4CA_9412A1FBCE39_
