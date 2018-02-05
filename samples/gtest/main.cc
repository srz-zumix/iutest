#include <stdio.h>

#include "gtest/iutest_switch.hpp"

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
