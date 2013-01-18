//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_env_var_tests.cpp
 * @brief		ä¬ã´ïœêîëŒâûÉeÉXÉg
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

int SetUpEnvironment(void)
{
	::iutest::internal::posix::PutEnv("IUTEST_SHUFFLE=1");
	::iutest::internal::posix::PutEnv("IUTEST_RANDOM_SEED=200");
	::iutest::internal::posix::PutEnv("IUTEST_ALSO_RUN_DISABLED_TESTS=1");
	::iutest::internal::posix::PutEnv("IUTEST_BREAK_ON_FAILURE=1");
	::iutest::internal::posix::PutEnv("IUTEST_THROW_ON_FAILURE=1");
	::iutest::internal::posix::PutEnv("IUTEST_CATCH_EXCEPTIONS=1");
	::iutest::internal::posix::PutEnv("IUTEST_PRINT_TIME=1");
	::iutest::internal::posix::PutEnv("IUTEST_REPEAT=2");
	::iutest::internal::posix::PutEnv("IUTEST_FILTER=Flag*");
	::iutest::internal::posix::PutEnv("IUTEST_FILE_LOCATION=vs");
	return 0;
}

static volatile int g_dummy = SetUpEnvironment();

IUTEST(FlagTest, Check)
{
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(also_run_disabled_tests) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(break_on_failure) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(throw_on_failure) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(catch_exceptions) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(print_time) );
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(shuffle) );
#if !defined(IUTEST_USE_GTEST)
	IUTEST_EXPECT_TRUE( ::iutest::IUTEST_FLAG(file_location_style_msvc) );
#endif
	
	IUTEST_EXPECT_EQ( 200u, ::iutest::IUTEST_FLAG(random_seed) );
	IUTEST_EXPECT_EQ(   2 , ::iutest::IUTEST_FLAG(repeat) );
	
	IUTEST_EXPECT_STREQ( "Flag*", ::iutest::IUTEST_FLAG(filter).c_str() );
}

#if IUTEST_HAS_PEEP_STATIC_FUNC
//typedef void (* pfnLoadEnv)(void);
//IUTEST_MAKE_SCOPED_PEEP(pfnLoadEnv, iutest, TestEnv, LoadEnviromentVariable);
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
#if IUTEST_HAS_PEEP_STATIC_FUNC
//	SetUpEnvironment();
//	IUTEST_PEEP_STATIC_GET(TestEnv, LoadEnviromentVariable)();
#endif
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();	// run all
}

