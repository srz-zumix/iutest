//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_record_property_tests.cpp
 * @brief		iutest RecordProperty ‘Î‰žƒeƒXƒg
 *
 * @author		t.sirayanagi
 * @version		1.0
 *
 * @par			copyright
 * Copyright (C) 2013, Takazumi Shirayanagi\n
 * The new BSD License is applied to this software.
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"

#if !defined(IUTEST_USE_GTEST)
bool CheckProperty(const ::iutest::TestResult* tr, const char* key, const char* value)
{
#if IUTEST_HAS_ASSERTION_RETURN
	IUTEST_ASSERT_EQ(1, tr->test_property_count()) << ::iutest::AssertionReturn<bool>(false);
	IUTEST_ASSERT_STREQ(key, tr->GetTestProperty(0).key()) << ::iutest::AssertionReturn<bool>(false);
	IUTEST_ASSERT_STREQ(value, tr->GetTestProperty(0).value()) << ::iutest::AssertionReturn<bool>(false);
#endif
	return true;
}

class RecordTest : public ::iutest::Test
{
public:
	static void SetUpTestCase()
	{
		RecordProperty("foo", "A");
		
		CheckProperty(::iutest::UnitTest::GetInstance()->current_test_case()->ad_hoc_testresult(), "foo", "A");
	}
};

IUTEST_F(RecordTest, A)
{
	RecordProperty("hoge", "B");

	CheckProperty(::iutest::UnitTest::GetInstance()->current_test_info()->result(), "hoge", "B");
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
	::iutest::Test::RecordProperty("bar", "C");
	
	{
		int ret = IUTEST_RUN_ALL_TESTS();
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST)
		if( !CheckProperty(::iutest::UnitTest::GetInstance()->ad_hoc_testresult(), "bar", "C") )
			return 1;
#endif
	}
#if !defined(IUTEST_USE_GTEST)
	{
		int ret = IUTEST_RUN_ALL_TESTS();
		if( ret != 0 ) return 1;
		if( !CheckProperty(::iutest::UnitTest::GetInstance()->ad_hoc_testresult(), "bar", "C") )
			return 1;
	}
	{
		IUTEST_INIT(&argc, argv);
		int ret = IUTEST_RUN_ALL_TESTS();
		if( ret != 0 ) return 1;
		if( CheckProperty(::iutest::UnitTest::GetInstance()->ad_hoc_testresult(), "bar", "C") )
			return 1;
	}
#endif
	printf("*** Successful ***\n");
	return 0;
}
