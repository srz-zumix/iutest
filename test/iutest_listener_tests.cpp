//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_listener_tests.cpp
 * @brief		リスナー 対応テスト
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

#include <assert.h>

class MyTestEventListener : public ::iutest::TestEventListener
{
public:
	bool called_OnTestProgramStart;
	bool called_OnTestIterationStart;
	bool called_OnEnvironmentsSetUpStart;
	bool called_OnEnvironmentsSetUpEnd;
	bool called_OnTestCaseStart;
	bool called_OnTestStart;
	bool called_OnTestPartResult;
	bool called_OnTestRecordProperty;
	bool called_OnTestEnd;
	bool called_OnTestCaseEnd;
	bool called_OnEnvironmentsTearDownStart;
	bool called_OnEnvironmentsTearDownEnd;
	bool called_OnTestIterationEnd;
	bool called_OnTestProgramEnd;
	
public:
	MyTestEventListener(void)
	: called_OnTestProgramStart(false)
	, called_OnTestIterationStart(false)
	, called_OnEnvironmentsSetUpStart(false)
	, called_OnEnvironmentsSetUpEnd(false)
	, called_OnTestCaseStart(false)
	, called_OnTestStart(false)
	, called_OnTestPartResult(false)
	, called_OnTestRecordProperty(false)
	, called_OnTestEnd(false)
	, called_OnTestCaseEnd(false)
	, called_OnEnvironmentsTearDownStart(false)
	, called_OnEnvironmentsTearDownEnd(false)
	, called_OnTestIterationEnd(false)
	, called_OnTestProgramEnd(false)
	{}
	
public:
	virtual void OnTestProgramStart(const ::iutest::UnitTest& /*test*/)
	{
		called_OnTestProgramStart = true;
	}
	virtual void OnTestIterationStart(const ::iutest::UnitTest& /*test*/
									, int /*iteration*/)
	{
		called_OnTestIterationStart = true;
	}
	virtual void OnEnvironmentsSetUpStart(const ::iutest::UnitTest& /*test*/)
	{
		called_OnEnvironmentsSetUpStart = true;
	}
	virtual void OnEnvironmentsSetUpEnd(const ::iutest::UnitTest& /*test*/)
	{
		called_OnEnvironmentsSetUpEnd = true;
	}
	virtual void OnTestCaseStart(const ::iutest::TestCase& /*test_case*/)
	{
		called_OnTestCaseStart = true;
	}
	virtual void OnTestStart(const ::iutest::TestInfo& /*test_info*/)
	{
		called_OnTestStart = true;
	}
	virtual void OnTestPartResult(const ::iutest::TestPartResult& /*test_part_result*/)
	{
		called_OnTestPartResult = true;
	}
	virtual void OnTestRecordProperty(const ::iutest::TestProperty& /*test_propterty*/)
	{
		called_OnTestRecordProperty = true;
	}
	virtual void OnTestEnd(const ::iutest::TestInfo& /*test_info*/)
	{
		called_OnTestEnd = true;
	}
	virtual void OnTestCaseEnd(const ::iutest::TestCase& /*test_case*/)
	{
		called_OnTestCaseEnd = true;
	}
	virtual void OnEnvironmentsTearDownStart(const ::iutest::UnitTest& /*test*/)
	{
		called_OnEnvironmentsTearDownStart = true;
	}
	virtual void OnEnvironmentsTearDownEnd(const ::iutest::UnitTest& /*test*/)
	{
		called_OnEnvironmentsTearDownEnd = true;
	}
	virtual void OnTestIterationEnd(const ::iutest::UnitTest& /*test*/
									, int /*iteration*/)
	{
		called_OnTestIterationEnd = true;
	}
	virtual void OnTestProgramEnd(const ::iutest::UnitTest& /*test*/)
	{
		called_OnTestProgramEnd = true;
	}
};

static MyTestEventListener* listener = NULL;

IUTEST(FlagTest, Check)
{
	IUTEST_ASSERT_TRUE( listener->called_OnTestProgramStart );
	IUTEST_ASSERT_TRUE( listener->called_OnTestIterationStart );
	IUTEST_ASSERT_TRUE( listener->called_OnEnvironmentsSetUpStart );
	IUTEST_ASSERT_TRUE( listener->called_OnEnvironmentsSetUpEnd );
	IUTEST_ASSERT_TRUE( listener->called_OnTestCaseStart );
	IUTEST_ASSERT_TRUE( listener->called_OnTestStart );
	
	IUTEST_ASSERT_FALSE( listener->called_OnTestEnd );
	IUTEST_ASSERT_FALSE( listener->called_OnTestCaseEnd );
	IUTEST_ASSERT_FALSE( listener->called_OnEnvironmentsTearDownStart );
	IUTEST_ASSERT_FALSE( listener->called_OnEnvironmentsTearDownEnd );
	IUTEST_ASSERT_FALSE( listener->called_OnTestIterationEnd );
	IUTEST_ASSERT_FALSE( listener->called_OnTestProgramEnd );

	IUTEST_ASSERT_FALSE( listener->called_OnTestPartResult );
	IUTEST_EXPECT_EQ(1, 2);
	IUTEST_ASSERT_TRUE( listener->called_OnTestPartResult );
	
	IUTEST_ASSERT_FALSE( listener->called_OnTestRecordProperty );
	RecordProperty("dummy", 0);
	IUTEST_ASSERT_TRUE( listener->called_OnTestRecordProperty );
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);

	listener = new MyTestEventListener();
	::iutest::TestEventListeners& listeners = ::iutest::UnitTest::GetInstance()->listeners();
	listeners.Append( listener );
	int ret = IUTEST_RUN_ALL_TESTS();	// run all
	
	assert( listener->called_OnTestEnd );
	assert( listener->called_OnTestCaseEnd );
	assert( listener->called_OnEnvironmentsTearDownStart );
	assert( listener->called_OnEnvironmentsTearDownEnd );
	assert( listener->called_OnTestIterationEnd );
	assert( listener->called_OnTestProgramEnd );

	if( ret == 1 ) printf("*** Successful ***\n");
	return ret != 0 ? 0 : 1;
}
