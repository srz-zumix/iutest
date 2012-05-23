//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_util_tests.hpp
 * @brief		iris unit test テスト情報 utility ファイル
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
#ifndef INCG_IRIS_iutest_util_tests_HPP_4095FF9B_D6B8_4cd3_BF86_43DFED1760EA_
#define INCG_IRIS_iutest_util_tests_HPP_4095FF9B_D6B8_4cd3_BF86_43DFED1760EA_

//======================================================================
// include
namespace iuutil
{

//======================================================================
// function

/**
 * @brief	TestCase の検索
*/
inline const iutest::TestCase* FindTestCase(const char* testcase_name)
{
	if( testcase_name == NULL ) return NULL;
	int testcase_count = iutest::UnitTest::GetInstance()->total_test_case_count();
	for( int i=0; i < testcase_count; ++i )
	{
		const iutest::TestCase* testcase = iutest::UnitTest::GetInstance()->GetTestCase(i);
		if( strcmp(testcase->name(), testcase_name) == 0 )
		{
			return testcase;
		}
	}
	return NULL;
}

/**
 * @brief	TestInfo の検索
*/
inline const iutest::TestInfo* FindTestInfo(const char* testcase_name, const char* testinfo_name)
{
	if( testcase_name == NULL || testinfo_name == NULL ) return NULL;
	const iutest::TestCase* testcase = FindTestCase(testcase_name);
	if( testcase == NULL ) return NULL;

	if( strcmp(testcase->name(), testcase_name) == 0 )
	{
		int testinfo_count = testcase->total_test_count();
		for( int i=0; i < testinfo_count; ++i )
		{
			const iutest::TestInfo* testinfo = testcase->GetTestInfo(i);
			if( strcmp(testinfo->name(), testinfo_name) == 0 )
			{
				return testinfo;
			}
		}
	}
	return NULL;
}

}	// end of namespace iuutil

#endif
