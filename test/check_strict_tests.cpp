//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		check_strict_tests.cpp
 * @brief		IUTEST_CHECK_STRICT test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#if defined(IUTEST_CHECK_STRICT)
#  undef IUTEST_CHECK_STRICT
#endif

#define IUTEST_CHECK_STRICT 1

//======================================================================
// include
#include "iutest.hpp"

class TestFixture : public ::iutest::Test
{
public:
	virtual void SetUp() {}
};

IUTEST_TEST_STATICASSERT("TestFixture is fixture class, mistake the IUTEST_F?")
IUTEST(TestFixture, Test)
{
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

