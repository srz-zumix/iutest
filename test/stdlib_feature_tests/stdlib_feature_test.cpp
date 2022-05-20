//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        stdlib_feature_test.cpp
 * @brief       stdlib feature macro test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../../include/internal/iutest_pp.hpp"
#include "../../include/internal/iutest_compiler.hpp"
#include "../../include/internal/iutest_stdlib.hpp"

#ifdef FEATURE_TEST_EXECUTABLE
#define SHOW_MACRO(macro)   printf("#define %s  %s\n", #macro, IUTEST_PP_TOSTRING(macro))
#define SHOW_UNDEF(macro)   printf("#undef  %s\n", #macro)
#else
#define SHOW_MACRO(macro)   define #macro macro
#define SHOW_UNDEF(macro)   undef  #macro
#endif

#define SUPPRESS_WARNING    1
void f()
{
    SHOW_MACRO(SUPPRESS_WARNING)
    SHOW_UNDEF(SUPPRESS_WARNING)
}

int main()
{
    #include "show_macros.i"    // NOLINT
    return 0;
}

