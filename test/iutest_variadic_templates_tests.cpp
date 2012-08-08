//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_variadic_templates_tests.cpp
 * @brief		Variadic Templates ‘Î‰žƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2012, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"


#if IUTEST_HAS_VARIADIC_VALUES

class TestPValuesN : public ::iutest::TestWithParam<int>
{
protected:
	static int a;
public:
	static void SetUpTestCase(void)
	{
		a = 1;
	}
};
int TestPValuesN::a = 1;
IUTEST_INSTANTIATE_TEST_CASE_P(TestPValuesNInstance, TestPValuesN, ::iutest::Values(1, 2, 3, 4, 5, 6, 7, 8, 9
																	, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
																	, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29
																	, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39
																	, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49
																	, 50
																	, 51
																	));

IUTEST_P(TestPValuesN, TestA)
{
	IUTEST_ASSERT_EQ(a++, GetParam());
}

bool pred_test(int a0, int a1, int a2, int a3, int a4, int a5)
{
	return a0+a2+a4 == a1+a3+a5;
}

IUTEST(PredTest, Variadic)
{
	IUTEST_ASSERT_PRED(pred_test, 0, 0, 0, 0, 0, 0);
	IUTEST_EXPECT_PRED(pred_test, 0, 0, 0, 0, 0, 0);
	IUTEST_INFORM_PRED(pred_test, 0, 0, 0, 0, 0, 0);
}

#endif

