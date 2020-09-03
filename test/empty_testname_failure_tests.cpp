//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        empty_testname_failure_tests.cpp
 * @brief       iutest empty testname static_assert test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

// ill-formed test definitions..

namespace emptyname
{

IUTEST_TEST_STATICASSERT("testname_ must not be empty")
IUTEST(Test, )
{
}

}

namespace emptysuite
{

IUTEST_TEST_STATICASSERT("testsuite_ must not be empty")
IUTEST(, Test)
{
}

}

class BaseFixture : public ::iutest::Test
{
};

namespace emptyname
{

IUTEST_TEST_STATICASSERT("testname_ must not be empty")
IUTEST_F(BaseFixture, )
{
}

}

namespace emptysuite
{

IUTEST_TEST_STATICASSERT("testsuite_ must not be empty")
IUTEST_F(, Test)
{
}

}

#if IUTEST_HAS_TESTFIXTURE_ALIAS_BY_TUPLE
namespace fixture_alias
{

IUTEST_TEST_STATICASSERT("testsuite alias name must not be empty")
IUTEST_F((, BaseFixture), Test)
{
}

}
#endif

#if IUTEST_HAS_TYPED_TEST

namespace emptyname
{

IUTEST_TEST_STATICASSERT("testname_ must not be empty")
IUTEST_TYPED_TEST(TypedTest, )
{
}

}

namespace emptysuite
{

IUTEST_TEST_STATICASSERT("testsuite_ must not be empty")
IUTEST_TYPED_TEST(, Test)
{
}

}
#endif

#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypeParamTest : public ::iutest::Test {};

namespace emptyname
{

IUTEST_TEST_STATICASSERT("testname_ must not be empty")
IUTEST_TYPED_TEST_P(TypeParamTest, )
{
}

}

namespace emptysuite
{

IUTEST_TEST_STATICASSERT("testsuite_ must not be empty")
IUTEST_TYPED_TEST_P(, Test)
{
}

}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
