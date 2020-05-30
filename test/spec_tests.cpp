//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        spec_tests.cpp
 * @brief       print spec
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if defined(iutest)
#  undef iutest
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_UNUSED_VAR(argc);
    IUTEST_UNUSED_VAR(argv);
    ::iutest::detail::iuOptionMessage::ShowFeature();
    ::iutest::detail::iuOptionMessage::ShowSpec();
    return 0;
}
