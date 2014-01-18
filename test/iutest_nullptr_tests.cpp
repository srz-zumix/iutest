//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_nullptr_tests.cpp
 * @brief		iutest nullptr test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

IUTEST(NullTest, Null)
{
	int* p = NULL;
	IUTEST_ASSERT_NULL(p);
	IUTEST_EXPECT_NULL(p);
	IUTEST_INFORM_NULL(p);

	IUTEST_ASSERT_NULL(NULL);
#if IUTEST_HAS_NULLPTR
	IUTEST_ASSERT_NULL(nullptr);
#endif
}

IUTEST(NullTest, NotNull)
{
	void* p = this;
	IUTEST_ASSERT_NOTNULL(p);
	IUTEST_EXPECT_NOTNULL(p);
	IUTEST_INFORM_NOTNULL(p);
}

#if IUTEST_HAS_NULLPTR
IUTEST(NullTest, NullEq)
{
	int* p = NULL;
	IUTEST_ASSERT_EQ(nullptr, p);
}
#endif

