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
// include

namespace iutest {
namespace detail {
namespace printer_internal
{

#if IUTEST_HAS_CXX_HDR_ANY
inline void PrintTo(const ::std::any& value, iu_ostream* os)
{
   *os << "-Any type-name: " << value.type().name();
   DefaultPrintNonContainerTo(value, os);
}
#endif

}   // end of namespace printer_internal
}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_DEFAULT_PRINTERS_HPP_52DAF156_7F2D_4AF2_B4CA_9412A1FBCE39_
