//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        charcode_tests.cpp
 * @brief       iutest charcode test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if defined(_MSC_VER)
IUTEST(CharCodeTest, UTF8ToSJIS)
{
    (void)iutest::detail::UTF8ToSJIS("test");
}
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

