#include "../../../../../include/iutest.hpp"
#include "sample.h"

IUTEST(B, Bar)
{
    IUTEST_ASSERT_EQ(1, f());
}
