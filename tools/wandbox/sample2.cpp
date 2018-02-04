#include "../../include/iutest.hpp"
#include "sample2.h"
#include <iostream>

int g()
{
    return 0;
}

IUTEST_PACKAGE(sample2)
{

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT( g() == 0 );
}

}
