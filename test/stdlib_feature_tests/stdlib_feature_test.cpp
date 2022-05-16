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

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define PP_TOSTRING(x)      PP_TOSTRING_(x)
#define PP_TOSTRING_(x)     #x
#ifdef FEATURE_TEST_EXECUTABLE
#define SHOW_MACRO(macro)   printf("#define %s  %s\n", #macro, PP_TOSTRING(macro))
#define SHOW_UNDEF(macro)   printf("#undef  %s\n", #macro)
#else
#define SHOW_MACRO(macro)   define #macro macro
#define SHOW_UNDEF(macro)   undef  #macro
#endif

int main()
{
    #include "show_macros.i"    // NOLINT
    return 0;
}

