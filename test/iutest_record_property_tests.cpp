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
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/iutest.hpp"
#include "../include/iutest_spi.hpp"

#if !defined(IUTEST_USE_GTEST)
#if !IUTEST_HAS_ASSERTION_RETURN
void CheckProperty_(const ::iutest::TestResult* tr, const char* key, const char* value)
{
	IUTEST_ASSERT_EQ(1, tr->test_property_count());
	IUTEST_EXPECT_STREQ(key, tr->GetTestProperty(0).key());
	IUTEST_EXPECT_STREQ(value, tr->GetTestProperty(0).value());
}
#endif

bool CheckProperty(const ::iutest::TestResult* tr, const char* key, const char* value)
{
#if IUTEST_USE_THROW_ON_ASSERT_FAILURE
	try {
#endif
	
#if IUTEST_HAS_ASSERTION_RETURN
	IUTEST_ASSERT_EQ(1, tr->test_property_count()) << ::iutest::AssertionReturn<bool>(false);
	IUTEST_EXPECT_STREQ(key, tr->GetTestProperty(0).key()) << ::iutest::AssertionReturn<bool>(false);
	IUTEST_EXPECT_STREQ(value, tr->GetTestProperty(0).value()) << ::iutest::AssertionReturn<bool>(false);
#else
	CheckProperty_(tr, key, value);
#endif

#if IUTEST_USE_THROW_ON_ASSERT_FAILURE
	} catch(...) {}
#endif
	return ::iutest::UnitTest::GetInstance()->Passed();
}

class RecordTest : public ::iutest::Test
{
public:
	static void SetUpTestCase()
	{
		RecordProperty("foo", "A");
#if !defined(IUTEST_USE_GTEST)
		// ban list
		IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("name"     , "A"), "Reserved key");
		IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("tests"    , "A"), "Reserved key");
		IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("failures" , "A"), "Reserved key");
		IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("disabled" , "A"), "Reserved key");
		IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("skip"     , "A"), "Reserved key");
		IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("errors"   , "A"), "Reserved key");
		IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("time"     , "A"), "Reserved key");
#endif
		CheckProperty(::iutest::UnitTest::GetInstance()->current_test_case()->ad_hoc_testresult(), "foo", "A");
	}
};

IUTEST_F(RecordTest, A)
{
	RecordProperty("hoge", "B");
#if !defined(IUTEST_USE_GTEST)
	// ban list
	IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("name"       , "B"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("status"     , "B"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("time"       , "B"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("classname"  , "B"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("type_param" , "B"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( RecordProperty("value_param", "B"), "Reserved key");
#endif
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
#if !defined(IUTEST_USE_GTEST)
		// ban list
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("name"       , "C"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("tests"      , "C"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("failures"   , "C"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("disabled"   , "C"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("skip"       , "C"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("errors"     , "C"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("time"       , "C"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("timestamp"  , "C"), "Reserved key");
	IUTEST_EXPECT_NONFATAL_FAILURE( ::iutest::Test::RecordProperty("random_seed", "C"), "Reserved key");
#endif
	
	{
		const int ret = IUTEST_RUN_ALL_TESTS();
		if( ret != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST)
		if( !CheckProperty(::iutest::UnitTest::GetInstance()->ad_hoc_testresult(), "bar", "C") )
			return 1;
#endif
	}
#if !defined(IUTEST_USE_GTEST)
	{
		const int ret = IUTEST_RUN_ALL_TESTS();
		if( ret != 0 ) return 1;
		if( !CheckProperty(::iutest::UnitTest::GetInstance()->ad_hoc_testresult(), "bar", "C") )
			return 1;
	}
	{
		IUTEST_INIT(&argc, argv);
		const int ret = IUTEST_RUN_ALL_TESTS();
		if( ret != 0 ) return 1;
		if( CheckProperty(::iutest::UnitTest::GetInstance()->ad_hoc_testresult(), "bar", "C") )
			return 1;
	}
#endif
	printf("*** Successful ***\n");
	return 0;
}
