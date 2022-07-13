//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_tchar.hpp
 * @brief       iris unit test char/wchar_t mediator
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_TCHAR_HPP_88D1A81F_A79B_48E9_B576_5A7D76DFC86E
#define INCG_IRIS_IUTEST_TCHAR_HPP_88D1A81F_A79B_48E9_B576_5A7D76DFC86E

//======================================================================
// include

// IWYU pragma: begin_exports
#include "iutest_string.hpp"
#include "iutest_string_view.hpp"
// IWYU pragma: end_exports

#if !defined(IUTEST_UNICODE)
#  if defined(UNICODE) || defined(_UNICODE)
#    define IUTEST_UNICODE    1
#  endif
#endif

#if !defined(IUTEST_UNICODE)
#  define IUTEST_UNICODE       0
#endif

namespace iutest {
namespace detail
{

#if IUTEST_UNICODE

#define IU_TSTR(_str)  L##_str

typedef wchar_t iu_tchar;

#else

#define IU_TSTR(_str)  _str

typedef char iu_tchar;

#endif

typedef ::std::basic_string<iu_tchar>   iu_tstring;
typedef iu_basic_string_view<iu_tchar>  iu_tstring_view;

}   // end of namespace detail
}   // end of namespace iutest

#endif // INCG_IRIS_IUTEST_TCHAR_HPP_88D1A81F_A79B_48E9_B576_5A7D76DFC86E
