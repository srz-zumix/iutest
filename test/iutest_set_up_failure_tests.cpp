//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_setup_failure_tests.cpp
 * @brief		SetUp で失敗したときのテスト
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
#include "../include/iutest.hpp"

static int test_flag = 0;

class TestSetUpFailure : public ::iutest::Test
{
public:
	virtual void SetUp()
	{
		IUTEST_FAIL() << "SetUp Failed.";
	}
};

IUTEST_F(TestSetUpFailure, Test)
{
	++test_flag;
}


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
	// 失敗テストを含むので xml 出力しない
	::iutest::IUTEST_FLAG(output) = NULL;
#endif
	const int ret = IUTEST_RUN_ALL_TESTS();
	
	IUTEST_ASSERT_EXIT( ret != 0 );
	IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->failed_test_count() == 1 );
	IUTEST_ASSERT_EXIT( test_flag == 0);

	printf("*** Successful ***\n");
	return 0;
}
