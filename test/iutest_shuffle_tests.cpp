//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_shuffle_tests.cpp
 * @brief		シャッフルテスト対応テスト
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

#include <vector>
#include <assert.h>


static unsigned int seed = 0;
static int count = 0;

class MyEnvironment : public ::iutest::Environment
{
private:
	virtual void SetUp(void)	{}
	virtual void TearDown(void)	{ seed = ::iutest::UnitTest::GetInstance()->random_seed(); ++count; }
};

IUTEST(Foo, Bar)
{
	IUTEST_ASSERT_NE(seed, ::iutest::UnitTest::GetInstance()->random_seed());
	::iutest::internal::posix::SleepMillisec(10);
}

#if IUTEST_HAS_PARAM_TEST
const int kNumberOfParamTests = 10;

static ::std::vector<int> order[3];


class TestP : public ::iutest::TestWithParam<int> {};

IUTEST_INSTANTIATE_TEST_CASE_P(Foo, TestP, ::iutest::Range<int>(0, kNumberOfParamTests));

IUTEST_P(TestP, Bar)
{
	order[count].push_back(GetParam());
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	MyEnvironment* const env = new MyEnvironment();
	assert( ::iutest::AddGlobalTestEnvironment(env) == env );
	IUTEST_INIT(&argc, argv);
	
	::iutest::IUTEST_FLAG(repeat) = 3;
	::iutest::IUTEST_FLAG(shuffle) = true;

	int ret = IUTEST_RUN_ALL_TESTS();
	if( ret != 0 ) return ret;
	
	IUTEST_EXPECT_NE(order[0], order[1]);
	IUTEST_EXPECT_NE(order[0], order[2]);
	
	return ::iutest::UnitTest::GetInstance()->Passed() ? 0 : 1;
}

