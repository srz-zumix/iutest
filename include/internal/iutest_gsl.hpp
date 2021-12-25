//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_gsl.hpp
 * @brief       stdlib
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_GSL_HPP_8D0BC1A9_14B0_481B_9CB2_26B1520855DE_
#define INCG_IRIS_IUTEST_GSL_HPP_8D0BC1A9_14B0_481B_9CB2_26B1520855DE_

//======================================================================
// include
// IWYU pragma: begin_exports
#include "iutest_stdlib_defs.hpp"
// IWYU pragma: end_exports

//======================================================================
// define
#if !defined(IUTEST_HAS_GSL)
#  if defined(__has_include)
#    if __has_include(<gsl/gsl>)
#      define IUTEST_HAS_GSL    1
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1900
#      define IUTEST_HAS_GSL    1
#    endif
#  endif
#endif

#if !defined(IUTEST_HAS_GSL)
#  define IUTEST_HAS_GSL        0
#endif

#if IUTEST_HAS_GDL
#  include <gsl/gsl>
#endif

//======================================================================
// struct

namespace iutest
{

namespace gsl
{

template<typename T>
struct owner_t
{
#if IUTEST_HAS_GSL
    typedef gsl::owner<T>   type;
#else
    typedef T type;
#endif
};

}   // end of namespace gsl

}   // end of namespace iutest


#endif

