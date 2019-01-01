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
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
#  define IIUT_STREAM_OP_DECL(T) \
    template<typename Elem, typename Traits, typename T> \
    inline ::std::basic_ostream<Elem, Traits>& operator << (::std::basic_ostream<Elem, Traits>& os, const T& value)
#else
#  define IIUT_STREAM_OP_DECL(T) \
    template<typename T> \
    inline iu_ostream& operator << (iu_ostream& os, const T& value)
#endif

namespace iutest {
namespace detail {

namespace printer_internal
{

#if !defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)

#if IUTEST_HAS_CXX_HDR_ANY
IIUT_STREAM_OP_DECL(::std::any)
{
   *os << "-Any type-name: " << value.type().name();
   DefaultPrintNonContainerTo(value, os);
}
#endif

#endif

}   // end of namespace printer_internal

#if IUTEST_HAS_NULLPTR
inline void PrintTo(const ::std::nullptr_t&, iu_ostream* os) { *os << "nullptr"; }
#endif

#if defined(IUTEST_NO_ARGUMENT_DEPENDENT_LOOKUP)
inline void PrintTo(int v, iu_ostream* os)  { *os << v; }
#endif

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_DEFAULT_PRINTERS_HPP_52DAF156_7F2D_4AF2_B4CA_9412A1FBCE39_
