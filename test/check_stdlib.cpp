//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        check_stdlib.cpp
 * @brief       stdlib config check
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <iostream>
#include "../include/internal/iutest_pp.hpp"
#include "../include/internal/iutest_compiler.hpp"
#include "../include/internal/iutest_stdlib.hpp"

#define SHOW_MACRO(x)   ::std::cout << "#define " #x " " IUTEST_PP_TOSTRING(x) << ::std::endl

#ifdef UNICODE
int wmain(int , wchar_t* [])
#else
int main(int , char* [])
#endif
{
    SHOW_MACRO(IUTEST_HAS_CXX_HDR_CHRONO);
    SHOW_MACRO(IUTEST_HAS_CXX_HDR_CODECVT);
    SHOW_MACRO(IUTEST_HAS_CXX_HDR_CSTDINT);
    SHOW_MACRO(IUTEST_HAS_CXX_HDR_RANDOM);
    SHOW_MACRO(IUTEST_HAS_CXX_HDR_REGEX);
    SHOW_MACRO(IUTEST_HAS_HDR_CXXABI);
    SHOW_MACRO(IUTEST_HAS_HDR_SYSTIME);
    SHOW_MACRO(IUTEST_HAS_HDR_UCHAR);
#ifdef IUTEST_LIBSTDCXX_VERSION
    SHOW_MACRO(IUTEST_LIBSTDCXX_VERSION);
#endif

    SHOW_MACRO(IUTEST_HAS_STD_BEGIN_END);
    SHOW_MACRO(IUTEST_HAS_STD_DECLVAL);
    SHOW_MACRO(IUTEST_HAS_STD_EMPLACE);
    SHOW_MACRO(IUTEST_HAS_STD_TUPLE);
    SHOW_MACRO(IUTEST_HAS_TR1_TUPLE);

#ifdef __GLIBCXX__
    SHOW_MACRO(__GLIBCXX__);
#endif
#ifdef __GLIBCPP__
    SHOW_MACRO(__GLIBCPP__);
#endif
#ifdef _LIBCPP_VERSION
    SHOW_MACRO(_LIBCPP_VERSION);
#endif
    return 0;
}

