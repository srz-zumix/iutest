//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        throw_on_assertion_failure_tests.cpp
 * @brief       IUTEST_USE_THROW_ON_ASSERTION_FAILURE test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#define IUTEST_USE_THROW_ON_ASSERTION_FAILURE   1

//======================================================================
// include
#include "iutest.hpp"

static int x = 0;

void Sub1(void)
{
    IUTEST_ASSERT_EQ(2, 1);
}
void Sub2(void)
{
    IUTEST_ASSUME_EQ(2, 1);
}
void Sub3(void)
{
    IUTEST_SKIP();
}

IUTEST(Foo, Test1)
{
    Sub1();
    ++x;
}

IUTEST(Foo, Test2)
{
    Sub2();
    ++x;
}

IUTEST(Foo, Test3)
{
    Sub3();
    ++x;
}

IUTEST(Foo, Test)
{
    IUTEST_EXPECT_EQ(0, x);
}

class TestFix : public ::iuutil::backward::Test<TestFix>
{
public:
    static void SetUpTestSuite(void)
    {
        Sub1();
        ++x;
    }
};

IUTEST_F(TestFix, Foo)
{
}

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif
    const int ret = IUTEST_RUN_ALL_TESTS();

#if IUTEST_USE_THROW_ON_ASSERTION_FAILURE
    IUTEST_TERMINATE_ON_FAILURE( x == 0 );
#else
    IUTEST_TERMINATE_ON_FAILURE( x == 4 );
#endif
    if( ret == 0 ) return 1;
    printf("*** Successful ***\n");
    return 0;
}
