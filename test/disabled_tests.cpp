//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        disabled_tests.cpp
 * @brief       also_run_disabled_tests 対応テスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

IUTEST(DISABLED_Foo, Bar)
{
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, DISABLED_Bar)
{
    IUTEST_ASSERT_EQ(2, 3);
}

IUTEST(Foo, Bar)
{
    IUTEST_ASSERT_EQ(3, 3);
}

IUTEST(Foo, Bar_DISABLED_)
{
    IUTEST_ASSERT_EQ(3, 3);
}

#if IUTEST_HAS_PARAM_TEST

class FooP : public ::iutest::TestWithParam< int >
{
};

typedef FooP FooP_DISABLED_;
typedef FooP DISABLED_FooP;

IUTEST_P(FooP_DISABLED_, Bar)
{
}

IUTEST_P(FooP, DISABLED_Bar)
{
    int v = GetParam();
    IUTEST_FAIL() << v;
}

IUTEST_P(DISABLED_FooP, Bar)
{
    int v = GetParam();
    IUTEST_FAIL() << v;
}

IUTEST_INSTANTIATE_TEST_CASE_P(A, FooP, ::iutest::Values(0, 2));
IUTEST_INSTANTIATE_TEST_CASE_P(A, FooP_DISABLED_, ::iutest::Values(0, 2));
IUTEST_INSTANTIATE_TEST_CASE_P(A, DISABLED_FooP , ::iutest::Values(0, 2));

#endif

#if IUTEST_HAS_PARAM_METHOD_TEST

void TestFunction(int x, int y)
{
    IUTEST_ASSERT_EQ(x, y);
}

IUTEST_PMZ(ParamMethod_Foo_DISABLED_, EQ, TestFunction, 0, 0);
IUTEST_PMZ(ParamMethod_Foo, DISABLED_EQ, TestFunction, 0, 1);
IUTEST_PMZ(DISABLED_ParamMethod_Foo, EQ, TestFunction, 0, 1);

class ParamMethodF_Foo : public ::iutest::Test {};
typedef ParamMethodF_Foo ParamMethodF_Foo_DISABLED_;
typedef ParamMethodF_Foo DISABLED_ParamMethodF_Foo;

IUTEST_PMZ_F(ParamMethodF_Foo_DISABLED_, EQ, TestFunction, 0, 0);
IUTEST_PMZ_F(ParamMethodF_Foo, DISABLED_EQ, TestFunction, 0, 1);
IUTEST_PMZ_F(DISABLED_ParamMethodF_Foo, EQ, TestFunction, 0, 1);

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class TypedFoo : public ::iutest::Test {};
template<typename T>
class TypedFoo_DISABLED_ : public ::iutest::Test {};
template<typename T>
class DISABLED_TypedFoo : public ::iutest::Test {};

typedef ::iutest::Types<int> TypedTestTypes;
IUTEST_TYPED_TEST_CASE(TypedFoo, TypedTestTypes);
IUTEST_TYPED_TEST_CASE(TypedFoo_DISABLED_, TypedTestTypes);
IUTEST_TYPED_TEST_CASE(DISABLED_TypedFoo , TypedTestTypes);

IUTEST_TYPED_TEST(TypedFoo_DISABLED_, Bar)
{
}

IUTEST_TYPED_TEST(TypedFoo, DISABLED_Bar)
{
    IUTEST_FAIL();
}

IUTEST_TYPED_TEST(DISABLED_TypedFoo, Bar)
{
    IUTEST_FAIL();
}

#endif

#if IUTEST_HAS_TYPED_TEST_P

template<typename T>
class TypePFoo : public ::iutest::Test {};
template<typename T>
class TypedPFoo_DISABLED_ : public ::iutest::Test {};
template<typename T>
class DISABLED_TypedPFoo : public ::iutest::Test {};

IUTEST_TYPED_TEST_CASE_P(TypePFoo);
IUTEST_TYPED_TEST_CASE_P(TypedPFoo_DISABLED_);
IUTEST_TYPED_TEST_CASE_P(DISABLED_TypedPFoo);

IUTEST_TYPED_TEST_P(TypedPFoo_DISABLED_, Bar)
{
}

IUTEST_TYPED_TEST_P(TypePFoo, DISABLED_Bar)
{
    IUTEST_FAIL();
}

IUTEST_TYPED_TEST_P(DISABLED_TypedPFoo, Bar)
{
    IUTEST_FAIL();
}

IUTEST_REGISTER_TYPED_TEST_CASE_P(TypedPFoo_DISABLED_, Bar);
IUTEST_REGISTER_TYPED_TEST_CASE_P(TypePFoo, DISABLED_Bar);
IUTEST_REGISTER_TYPED_TEST_CASE_P(DISABLED_TypedPFoo, Bar);

IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(A, TypedPFoo_DISABLED_, int);
IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(A, TypePFoo, int);
IUTEST_INSTANTIATE_TYPED_TEST_CASE_P(A, DISABLED_TypedPFoo, int);

#endif


#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    IUTEST_INIT(&argc, argv);
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iutest::IUTEST_FLAG(output) = NULL;
#endif
    int expected_disable_test_count = 2;
    int expected_test_count = 4;
#if IUTEST_HAS_PARAM_TEST
    expected_disable_test_count += 4;
    expected_test_count += 6;
#endif
#if IUTEST_HAS_PARAM_METHOD_TEST
    expected_disable_test_count += 4;
    expected_test_count += 6;
#endif
#if IUTEST_HAS_TYPED_TEST
    expected_disable_test_count += 2;
    expected_test_count += 3;
#endif
#if IUTEST_HAS_TYPED_TEST_P
    expected_disable_test_count += 2;
    expected_test_count += 3;
#endif
    
    {
        const int ret = IUTEST_RUN_ALL_TESTS();
        if( ret != 0 ) return 1;
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->disabled_test_count() == expected_disable_test_count );
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == expected_disable_test_count );
#endif
#if !defined(IUTEST_USE_GTEST)
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->skip_test_count() == expected_disable_test_count );
#endif
    }
    
    {
        ::iutest::IUTEST_FLAG(also_run_disabled_tests) = true;
        const int ret = IUTEST_RUN_ALL_TESTS();
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->disabled_test_count() == expected_disable_test_count );
#if !defined(IUTEST_USE_GTEST) || (defined(GTEST_MINOR) && GTEST_MINOR >= 0x07)
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->reportable_disabled_test_count() == expected_disable_test_count );
#endif
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->test_to_run_count() == expected_test_count );
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->failed_test_count() == expected_disable_test_count );
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->total_test_count() == expected_test_count );
#if !defined(IUTEST_USE_GTEST)
        IUTEST_ASSERT_EXIT( ::iutest::UnitTest::GetInstance()->skip_test_count() == 0 );
#endif
        if( ret == 0 ) return 1;
    }
    printf("*** Successful ***\n");
    return 0;
}
