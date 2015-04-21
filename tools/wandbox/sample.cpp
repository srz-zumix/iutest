#include "../../include/iutest.hpp"
#include "sample.h"
#include <iostream>

int main(int argc, char** argv)
{
	int x = 0;
	std::cout << "hoge" << std::endl;
	
	IUTEST_INIT(&argc, argv);
	return IUTEST_RUN_ALL_TESTS();
}

IUTEST(Foo, Bar)
{
	IUTEST_ASSERT_EQ(42, f());
}
