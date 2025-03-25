//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        japanese_tests.cpp
 * @brief       IUTEST_JAPANESE_NAME 対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_TESTNAME_ALIAS_JP

IUTEST_PRAGMA_MSC_WARN_DISABLE(4566)

IUTEST_PACKAGE(japanese_test)
{
IUTEST(JapaneseTest, IUTEST_JAPANESE_NAME(あいうえお))
{
//  IUTEST_SUCCEED() << "あいうえお";
    IUTEST_SUCCEED() << ::iutest::UnitTest::GetInstance()->current_test_info()->name();
    IUTEST_ASSERT_STREQ("あいうえお", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST(JapaneseTest, IUTEST_JAPANESE_NAME(かきくけこ))
{
    IUTEST_ASSERT_STREQ("かきくけこ", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST(IUTEST_JAPANESE_NAME(あいうえお), IUTEST_JAPANESE_NAME(かきくけこ))
{
#if IUTEST_HAS_PACKAGE
    IUTEST_ASSERT_STREQ("japanese_test.あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#else
    IUTEST_ASSERT_STREQ("あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#endif
    IUTEST_ASSERT_STREQ("かきくけこ", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

class FixedTest : public ::iutest::Test {};

IUTEST_F(IUTEST_JAPANESE_NAME_F(あいうえお, FixedTest), IUTEST_JAPANESE_NAME(かきくけこ))
{
#if IUTEST_HAS_PACKAGE
    IUTEST_ASSERT_STREQ("japanese_test.あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#else
    IUTEST_ASSERT_STREQ("あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#endif
    IUTEST_ASSERT_STREQ("かきくけこ", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

#if IUTEST_HAS_PARAM_TEST
class ParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_P(IUTEST_JAPANESE_NAME_F(あいうえお, ParamTest), IUTEST_JAPANESE_NAME(あいうえお))
{
#if IUTEST_HAS_PACKAGE
    IUTEST_ASSERT_STREQ("japanese_test.My1/あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#else
    IUTEST_ASSERT_STREQ("My1/あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#endif
    IUTEST_ASSERT_STREQ("あいうえお/0", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_P(IUTEST_JAPANESE_NAME_F(あいうえお, ParamTest), Japanese)
{
#if IUTEST_HAS_PACKAGE
    IUTEST_ASSERT_STREQ("japanese_test.My1/あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#else
    IUTEST_ASSERT_STREQ("My1/あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#endif
    IUTEST_ASSERT_STREQ("Japanese/0", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_INSTANTIATE_TEST_SUITE_P(My1, IUTEST_JAPANESE_NAME_F(あいうえお, ParamTest), ::iutest::Values(0));

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE(TypedTest, int);

IUTEST_TYPED_TEST(IUTEST_JAPANESE_NAME_F(あいうえお, TypedTest), IUTEST_JAPANESE_NAME(あいうえお))
{
#if IUTEST_HAS_PACKAGE
    IUTEST_ASSERT_STREQ("japanese_test.あいうえお/0", ::iuutil::GetCurrentTestSuite()->name());
#else
    IUTEST_ASSERT_STREQ("あいうえお/0", ::iuutil::GetCurrentTestSuite()->name());
#endif
    IUTEST_ASSERT_STREQ("あいうえお", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

#endif

#if 0   // 未サポート
#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(TypeParamTest);

IUTEST_TYPED_TEST_P(TypeParamTest, IUTEST_JAPANESE_NAME_F(あいうえお, aiueo))
{
    IUTEST_ASSERT_STREQ("あいうえお", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(TypeParamTest, aiueo);

IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(My1, TypeParamTest, int);

#endif

#endif

#if IUTEST_HAS_PARAM_METHOD_TEST

void TestFunction(int x, int y)
{
    IUTEST_ASSERT_EQ(x, y);
#if IUTEST_HAS_PACKAGE
    IUTEST_ASSERT_STREQ("japanese_test.あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#else
    IUTEST_ASSERT_STREQ("あいうえお", ::iuutil::GetCurrentTestSuite()->name());
#endif
    IUTEST_ASSERT_STREQ("イコール/0", ::iutest::UnitTest::GetInstance()->current_test_info()->name());
}
IUTEST_PMZ(IUTEST_JAPANESE_NAME(あいうえお), IUTEST_JAPANESE_NAME(イコール), TestFunction, 0, 0);

#endif

#if IUTEST_HAS_IGNORE_TEST

namespace ignore_test
{

IUTEST_IGNORE(IUTEST_JAPANESE_NAME(あいうえお), IUTEST_JAPANESE_NAME(あいうえお))
{
}

IUTEST_F_IGNORE(IUTEST_JAPANESE_NAME_F(あいうえお, FixedTest), IUTEST_JAPANESE_NAME(かきくけこ))
{
}

#if IUTEST_HAS_PARAM_TEST

IUTEST_P_IGNORE(IUTEST_JAPANESE_NAME_F(あいうえお, ParamTest), IUTEST_JAPANESE_NAME(かきくけこ))
{
}

#endif

#if IUTEST_HAS_TYPED_TEST

IUTEST_TYPED_TEST_IGNORE(IUTEST_JAPANESE_NAME_F(あいうえお, TypedTest), IUTEST_JAPANESE_NAME(あいうえお))
{
}

#endif

}   // end of namespace ignore_test

#endif
}

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);

    int ret = IUTEST_RUN_ALL_TESTS();
    if( ret != 0 ) return 1;

#if IUTEST_HAS_TESTNAME_ALIAS_JP

    int testsuite_count = 3;
    int test_count = 4;
#if IUTEST_HAS_PARAM_TEST
    testsuite_count+=1;
    test_count += 2;
#endif
#if IUTEST_HAS_TYPED_TEST
    testsuite_count+=1;
    test_count += 1;
#endif
#if IUTEST_HAS_PARAM_METHOD_TEST
    test_count += 1;
#endif

#if IUTEST_HAS_IGNORE_TEST
    test_count += 2;
#if IUTEST_HAS_PARAM_TEST
    test_count += 1;
#endif
#if IUTEST_HAS_TYPED_TEST
    test_count += 1;
#endif
#endif

#if IUTEST_HAS_ASSERTION_RETURN
    IUTEST_ASSERT_EQ( testsuite_count, ::iuutil::GetTotalTestSuiteCount()) << ::iutest::AssertionReturn(1);
    IUTEST_ASSERT_EQ( test_count, ::iutest::UnitTest::GetInstance()->total_test_count() ) << ::iutest::AssertionReturn(1);
#else
    IUTEST_TERMINATE_ON_FAILURE( ::iuutil::GetTotalTestSuiteCount() == testsuite_count );
    IUTEST_TERMINATE_ON_FAILURE( ::iutest::UnitTest::GetInstance()->total_test_count() == test_count );
#endif

#endif
    printf("*** Successful ***\n");
    return 0;
}
