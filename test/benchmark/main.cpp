//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		main.cpp
 * @brief		test main
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

/*
 * include testing framework
*/
#include "gtest/iutest_switch.hpp"
#include "listener/iutest_tap_printer.hpp"
#include "listener/iutest_progress_printer.hpp"

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

