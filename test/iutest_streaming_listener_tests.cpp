//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_streaming_listener_tests.cpp
 * @brief		StreamResultListener test
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014-2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(Test, Ok)
{
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);
#if IUTEST_HAS_STREAM_RESULT
	::iutest::IUTEST_FLAG(stream_result_to) = "localhost:5103";
	if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;	
	printf("*** Successful ***\n");
	return 0;
#else
	return IUTEST_RUN_ALL_TESTS();
#endif
}
