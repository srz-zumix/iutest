//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		sample.cpp
 * @brief		twilio sample
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../../include/iutest.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

int a=0;

IUTEST(Test, A)
{
    IUTEST_ASSERT_EQ(a, 1);
}

