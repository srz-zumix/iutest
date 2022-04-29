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
#define SHOW_MACRO(macro)   SHOW_MACRO_I(#macro, PP_TOSTRING(macro))
#define SHOW_MACRO_I(name, value)   printf("#define %s  %s\n", name, value)
#define SHOW_UNDEF(macro)           printf("#undef  %s\n", #macro)

int main()
{
    #include "show_macros.i"    // NOLINT
    return 0;
}

