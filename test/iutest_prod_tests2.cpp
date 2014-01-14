//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_prod_tests2.cpp
 * @brief		product code access test
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012-2014, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest_prod_tests.hpp"

namespace prod_test
{

static ProdClass s_prod_2;

#if IUTEST_HAS_PEEP

IUTEST(ProdTest, PeepA2)
{
	IUTEST_PEEP_GET(s_prod_2, ProdClass, m_a) = 2;
	IUTEST_EXPECT_EQ(2, s_prod_2.GetA());

	IUTEST_EXPECT_EQ(2, IUTEST_PEEP_GET(s_prod_2, ProdClass, m_a));
}

#endif

}
