//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        concat_tests.cpp
 * @brief       Concat 対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_PARAM_TEST && IUTEST_HAS_CONCAT

static const int tble[] = {0, 1};
static const float ftble[] = {0.0f, 1.0f};

class ConcatTest : public ::iutest::TestWithParam<int>
{
public:
};

IUTEST_P(ConcatTest, Dummy)
{
}

IUTEST_INSTANTIATE_TEST_SUITE_P(A1, ConcatTest
    , ::iutest::Concat(::iutest::Bool(), ::iutest::Values(1, 10)));
IUTEST_INSTANTIATE_TEST_SUITE_P(A2, ConcatTest
    , ::iutest::Concat(::iutest::Bool(), ::iutest::ValuesIn(tble)));
IUTEST_INSTANTIATE_TEST_SUITE_P(A3, ConcatTest
    , ::iutest::Concat(::iutest::ValuesIn(tble), ::iutest::Range(1, 10)));
IUTEST_INSTANTIATE_TEST_SUITE_P(A4, ConcatTest
    , ::iutest::Concat(::iutest::Values(1, 10)
    , ::iutest::Concat(::iutest::ValuesIn(tble), ::iutest::Range(1, 10))) );
IUTEST_INSTANTIATE_TEST_SUITE_P(A5, ConcatTest
    , ::iutest::Concat(::iutest::ValuesIn(ftble), ::iutest::Range<char>(1, 10)));
#if IUTEST_HAS_RANDOMVALUES
IUTEST_INSTANTIATE_TEST_SUITE_P(A6, ConcatTest
    , ::iutest::Concat(::iutest::ValuesIn(tble), ::iutest::RandomValues(1)));
#endif

// operator +
IUTEST_INSTANTIATE_TEST_SUITE_P(P1, ConcatTest
    , ::iutest::Bool() + ::iutest::Values(1, 10));
IUTEST_INSTANTIATE_TEST_SUITE_P(P2, ConcatTest
    , ::iutest::Values(1, 10) + ::iutest::Bool() );
IUTEST_INSTANTIATE_TEST_SUITE_P(P3, ConcatTest
    , ::iutest::ValuesIn(ftble) + ::iutest::ValuesIn(tble) );
#if IUTEST_HAS_RANDOMVALUES
IUTEST_INSTANTIATE_TEST_SUITE_P(P4, ConcatTest
    , ::iutest::RandomValues(1) + ::iutest::Bool() );
#endif
IUTEST_INSTANTIATE_TEST_SUITE_P(P5, ConcatTest
    , ::iutest::Range(1, 10) + ::iutest::Bool() + ::iutest::Values(1, 10));

void ConcatTestCheckCount(const char* name, int num)
{
    const ::iutest::TestSuite* p = ::iuutil::FindTestSuite(name);
    IUTEST_ASSERT_NOTNULL(p);
    IUTEST_ASSERT_EQ(num, p->total_test_count());
}

IUTEST(ConcatTestCheck, A)
{
    ConcatTestCheckCount("A1/ConcatTest", 2+2);
    ConcatTestCheckCount("A2/ConcatTest", 2+2);
    ConcatTestCheckCount("A3/ConcatTest", 2+9);
    ConcatTestCheckCount("A4/ConcatTest", 2+2+9);
    ConcatTestCheckCount("A5/ConcatTest", 2+9);
#if IUTEST_HAS_RANDOMVALUES
    ConcatTestCheckCount("A6/ConcatTest", 2+1);
#endif
}

IUTEST(ConcatTestCheck, P)
{
    ConcatTestCheckCount("P1/ConcatTest", 2+2);
    ConcatTestCheckCount("P2/ConcatTest", 2+2);
    ConcatTestCheckCount("P3/ConcatTest", 2+2);
#if IUTEST_HAS_RANDOMVALUES
    ConcatTestCheckCount("P4/ConcatTest", 1+2);
#endif
    ConcatTestCheckCount("P5/ConcatTest", 9+2+2);
}

#endif

