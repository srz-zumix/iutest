//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_default_printers.hpp
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
#ifndef INCG_IRIS_IUTEST_DEFAULT_PRINTERS_HPP_52DAF156_7F2D_4AF2_B4CA_9412A1FBCE39_
#define INCG_IRIS_IUTEST_DEFAULT_PRINTERS_HPP_52DAF156_7F2D_4AF2_B4CA_9412A1FBCE39_

//======================================================================
// define

namespace iutest {
namespace detail {
namespace printer_internal_default_printto {

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

}   // end of namespace printer_internal_default_printto

#if defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
inline void PrintTo(int v, iu_ostream* os)  { *os << v; }
#endif

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_DEFAULT_PRINTERS_HPP_52DAF156_7F2D_4AF2_B4CA_9412A1FBCE39_
