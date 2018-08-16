#include "../../include/iutest.hpp"
#include "sample.h"
#if defined(SAMPLE2)
#include "sample2.h"
#endif
#include <iostream>

int main(int argc, char** argv)
{
    int x = 0;
    ::std::cout << "hoge" << ::std::endl;
    
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(42, f());
#if defined(SAMPLE2)
    IUTEST_ASSERT_EQ( 0, g());
#endif
}
