//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        stdlib_config_check.cpp
 * @brief       stdlib config check
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2016-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <iostream>
#include "../../include/internal/iutest_pp.hpp"
#include "../../include/internal/iutest_compiler.hpp"
#include "../../include/internal/iutest_stdlib.hpp"
#include "../../include/internal/iutest_type_traits.hpp"

#ifdef STDLIB_CONFIG_CHECK_EXECUTABLE
#define SHOW_MACRO(macro)   ::std::cout << "#define " #macro " " IUTEST_PP_TOSTRING(macro) << ::std::endl
#else
#define SHOW_MACRO(macro)   define #macro macro
#endif

#ifdef UNICODE
int wmain(int , wchar_t* [])
#else
int main(int , char* [])
#endif
{
    #include "stdlib_config_check_macros.cpp"
    return 0;
}

