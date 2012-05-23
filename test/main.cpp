
/*
 * is not available vprintf, can be replaced.
*/
//#define IUTEST_VPRINTF

/*
 * include testing framework
*/
#include "../include/iutest.hpp"
#include "../include/gtest/iutest_switch.hpp"

#ifdef USE_TAP
#  include "../include/listener/iutest_tap_printer.hpp"
#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	IUTEST_INIT(&argc, argv);

#ifdef USE_TAP
	iutest::TestEventListeners& listeners = iutest::UnitTest::GetInstance()->listeners();
	delete listeners.Release(listeners.default_result_printer());
	listeners.Append( new iutest::TAPPrintListener );
#endif
	
	return IUTEST_RUN_ALL_TESTS();	// run all
}

