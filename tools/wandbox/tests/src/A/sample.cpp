#include "../../../../../include/iutest.hpp"
#include "sample.h"

IUTEST(A, Bar)
{
    IUTEST_ASSERT_EQ(42, f());
}
