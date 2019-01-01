//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        printers_overload_tests.cpp
 * @brief       overload default printers test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2018, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include <vector>
#include "iutest.hpp"
#include "logger_tests.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

#if IUTEST_HAS_CXX_HDR_ANY

void PrintTo(const ::std::any& value, iu_ostream* os)
{
    os << "std::any printto"
}

IUTEST(Any, PrintTo)
{
    PrintToLogChecker ck("std::any printto");
    ::std::any v = 1234;
    IUTEST_SUCCEED() << ::iutest::PrintToString(v);
}

#endif
