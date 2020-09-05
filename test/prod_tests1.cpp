//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        prod_tests1.cpp
 * @brief       product code access test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2020, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "prod_tests.hpp"

namespace prod_test
{

int ProdClass::m_y = 0;
int ProtectedProdClass::m_y = 0;

}

namespace prod_test
{

static ProdClass s_prod;

// IUTEST_FRIEND_TEST を使ってのアクセス
IUTEST(ProdTest, Friend)
{
    s_prod.SetX(1);
    IUTEST_EXPECT_EQ(1, s_prod.GetX());

    s_prod.m_x = 2;
    IUTEST_EXPECT_EQ(2, s_prod.GetX());
}

class ProdFixtureTest : public ::iutest::Test {};

IUTEST_F(ProdFixtureTest, Friend)
{
    s_prod.SetX(1);
    IUTEST_EXPECT_EQ(1, s_prod.GetX());

    s_prod.m_x = 2;
    IUTEST_EXPECT_EQ(2, s_prod.GetX());
}

#if IUTEST_HAS_PARAM_TEST

class ProdParamTest : public ::iutest::TestWithParam<int> {};

IUTEST_INSTANTIATE_TEST_SUITE_P(X, ProdParamTest, ::iutest::Values(0));

IUTEST_P(ProdParamTest, Friend)
{
    s_prod.SetX(1);
    IUTEST_EXPECT_EQ(1, s_prod.GetX());

    s_prod.m_x = 2;
    IUTEST_EXPECT_EQ(2, s_prod.GetX());
}

#endif

#if IUTEST_HAS_TYPED_TEST

template<typename T>
class ProdTypedTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE(ProdTypedTest, int);

IUTEST_TYPED_TEST(ProdTypedTest, Friend)
{
    s_prod.SetX(1);
    IUTEST_ASSERT_EQ(1, s_prod.GetX());

    s_prod.m_x = 2;
    IUTEST_ASSERT_EQ(2, s_prod.GetX());
}

#endif

#if IUTEST_HAS_TYPED_TEST_P

typedef ::iutest::Types<int, float> ProdTypeParams;

template<typename T>
class ProdTypeParamTest : public ::iutest::Test {};

IUTEST_TYPED_TEST_SUITE_P(ProdTypeParamTest);

IUTEST_TYPED_TEST_P(ProdTypeParamTest, Friend)
{
    s_prod.SetX(1);
    IUTEST_ASSERT_EQ(1, s_prod.GetX());

    s_prod.m_x = 2;
    IUTEST_ASSERT_EQ(2, s_prod.GetX());
}

IUTEST_REGISTER_TYPED_TEST_SUITE_P(ProdTypeParamTest, Friend);
IUTEST_INSTANTIATE_TYPED_TEST_SUITE_P(A, ProdTypeParamTest, ::iutest::Types<int>);

#endif


#if IUTEST_HAS_PEEP

static ProdClass2 s_prod2;
static ProtectedProdClass s_protected;

// peep を使ってのアクセス
IUTEST_MAKE_PEEP(int* ProdClass::*, ProdClass, m_b);
IUTEST_MAKE_PEEP(int ProdClass::*, ProdClass, m_x);
IUTEST_MAKE_PEEP(const int ProdClass::*, ProdClass, m_c);

IUTEST_MAKE_PEEP(int ProdClass2::*, ProdClass2, m_x);

IUTEST_MAKE_PEEP(int ProtectedProdClass::*, ProtectedProdClass, m_x);

IUTEST(PeepTest, PeepMacro)
{
    IUTEST_PEEP_GET(s_prod, ProdClass, m_x) = 4;
    IUTEST_EXPECT_EQ(4, s_prod.GetX());

    IUTEST_EXPECT_EQ(4, IUTEST_PEEP_GET(s_prod, ProdClass, m_x));

    IUTEST_PEEP_GET(s_prod2, ProdClass2, m_x) = 42;
    IUTEST_EXPECT_EQ(42, s_prod2.GetX());

    IUTEST_EXPECT_EQ(42, IUTEST_PEEP_GET(s_prod2, ProdClass2, m_x));

    IUTEST_PEEP_GET(s_protected, ProtectedProdClass, m_x) = 42;
    IUTEST_EXPECT_EQ(42, s_protected.GetX());

    IUTEST_EXPECT_EQ(42, IUTEST_PEEP_GET(s_protected, ProtectedProdClass, m_x));
}

IUTEST(PeepTest, PeepPointer)
{
    int* pb = IUTEST_PEEP_GET(s_prod, ProdClass, m_b);
    *pb = 4;
    IUTEST_EXPECT_EQ(4, *s_prod.GetB());
}

#if IUTEST_HAS_PEEP_CLASS

IUTEST(PeepClassTest, PeepObject)
{
    IUTEST_PEEP(ProdClass, m_x) prod_class_x(&s_prod);
    prod_class_x = 5;
    IUTEST_EXPECT_EQ(5, s_prod.GetX());
    prod_class_x += prod_class_x;
    IUTEST_EXPECT_EQ(10, s_prod.GetX());

    IUTEST_EXPECT_EQ(10, prod_class_x);
}

IUTEST(PeepClassTest, PeepObject2)
{
    IUTEST_PEEP(ProdClass2, m_x) prod_class2_x(&s_prod2);
    prod_class2_x = 54;
    IUTEST_EXPECT_EQ(54, s_prod2.GetX());
    prod_class2_x += prod_class2_x;
    IUTEST_EXPECT_EQ(108, s_prod2.GetX());

    IUTEST_EXPECT_EQ(108, prod_class2_x);
}

#endif

IUTEST(PeepTest, A1)
{
    IUTEST_PEEP_GET(s_prod, ProdClass, m_a) = 1;
    IUTEST_EXPECT_EQ(1, s_prod.GetA());

    IUTEST_EXPECT_EQ(1, IUTEST_PEEP_GET(s_prod, ProdClass, m_a));
}

IUTEST(PeepTest, Const)
{
    // マクロ版
    IUTEST_EXPECT_EQ(42, IUTEST_PEEP_GET(s_prod, ProdClass, m_c));
}

#if IUTEST_HAS_PEEP_CLASS
IUTEST(PeepClassTest, Const)
{
    // object 版
    IUTEST_PEEP(ProdClass, m_c) prod_class_c(&s_prod);
    IUTEST_EXPECT_EQ(42, prod_class_c);
}
#endif

IUTEST_MAKE_PEEP(int *, ProdClass, m_y);
IUTEST_MAKE_PEEP(int *, ProtectedProdClass, m_y);

IUTEST(PeepTest, StaticPeep)
{
    IUTEST_PEEP_STATIC_GET(ProdClass, m_y) = 4;
    IUTEST_EXPECT_EQ(4, ProdClass::GetY());

    IUTEST_EXPECT_EQ(4, IUTEST_PEEP_STATIC_GET(ProdClass, m_y));
}

IUTEST(PeepTest, StaticProtectedPeep)
{
    IUTEST_PEEP_STATIC_GET(ProtectedProdClass, m_y) = 4;
    IUTEST_EXPECT_EQ(4, ProtectedProdClass::GetY());

    IUTEST_EXPECT_EQ(4, IUTEST_PEEP_STATIC_GET(ProtectedProdClass, m_y));
}

#if IUTEST_HAS_PEEP_CLASS
IUTEST(PeepClassTest, StaticPeep)
{
    // object 版
    IUTEST_PEEP(ProdClass, m_y) prod_class_y;
    prod_class_y = 5;
    IUTEST_EXPECT_EQ(5, ProdClass::GetY());
    prod_class_y *= 2;
    IUTEST_EXPECT_EQ(10, ProdClass::GetY());

    IUTEST_PEEP(ProdClass, m_y)(1);
    IUTEST_EXPECT_EQ(1, prod_class_y);

    IUTEST_PEEP(ProdClass, m_y) prod_class_y2 = 2;
    IUTEST_EXPECT_EQ(2, prod_class_y2);
}
#endif

#if IUTEST_HAS_PEEP_FUNC

IUTEST_MAKE_PEEP(void (ProdClass::*)(int), ProdClass, SetX);
IUTEST_MAKE_PEEP(int (ProdClass::*)() const, ProdClass, ConstGetX);
IUTEST_MAKE_PEEP(void (ProtectedProdClass::*)(int), ProtectedProdClass, SetX);
#if IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_OVERLOAD_MEMBER_FUNCTION
IUTEST_MAKE_PEEP(int (ProtectedProdClass::*)() const, ProtectedProdClass, GetProtectedX);
#endif

IUTEST(PeepTest, Function)
{
    IUTEST_PEEP_GET(s_prod, ProdClass, SetX)(100);
    IUTEST_EXPECT_EQ(100, s_prod.GetX());
    IUTEST_EXPECT_EQ(100, IUTEST_PEEP_GET(s_prod, ProdClass, ConstGetX)());
}

IUTEST(PeepTest, ProtectedFunction)
{
    IUTEST_PEEP_GET(s_protected, ProtectedProdClass, SetX)(100);
    IUTEST_EXPECT_EQ(100, s_protected.GetX());

#if IUTEST_EXPLICIT_INSTANTIATION_ACCESS_PRIVATE_OVERLOAD_MEMBER_FUNCTION
    IUTEST_EXPECT_EQ(100, IUTEST_PEEP_GET(s_protected, ProtectedProdClass, GetProtectedX)());
#endif
}

#if IUTEST_HAS_PEEP_CLASS
IUTEST(PeepClassTest, Function)
{
    IUTEST_PEEP(ProdClass, SetX) peep_set(&s_prod);
    peep_set(101);
    IUTEST_EXPECT_EQ(101, s_prod.GetX());

    IUTEST_PEEP(ProdClass, ConstGetX) peep_get(&s_prod);
    IUTEST_EXPECT_EQ(101, peep_get());
}
#endif

#endif

#if IUTEST_HAS_PEEP_STATIC_FUNC

IUTEST_MAKE_PEEP(void (*)(int), ProdClass, SetY);
IUTEST_MAKE_PEEP(void (*)(int), ProtectedProdClass, SetY);

IUTEST(PeepTest, StaticFunction)
{
    IUTEST_PEEP_STATIC_GET(ProdClass, SetY)(100);
    IUTEST_EXPECT_EQ(100, ProdClass::GetY());
}

IUTEST(PeepTest, StaticProtectedFunction)
{
    IUTEST_PEEP_STATIC_GET(ProtectedProdClass, SetY)(100);
    IUTEST_EXPECT_EQ(100, ProtectedProdClass::GetY());
}

// object 版
#if IUTEST_HAS_PEEP_CLASS
IUTEST(PeepClassTest, StaticFunction)
{
    IUTEST_PEEP(ProdClass, SetY) peep;
    peep(101);
    IUTEST_EXPECT_EQ(101, ProdClass::GetY());
}
#endif

#endif

#endif

}   // end of namespace prod_test


#if IUTEST_HAS_PEEP

// peep を使ってのアクセス
IUTEST_MAKE_PEEP(int prod_test::ProdClass::*, prod_test::ProdClass, m_z);
IUTEST_MAKE_PEEP(int prod_test::ProdClass::*, prod_test::ProdClass, m_x);

IUTEST(PeepTest, ScopedPeep)
{
    // マクロ版
    {
        IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_z) = 4;
        IUTEST_EXPECT_EQ(4, prod_test::s_prod.GetZ());

        IUTEST_EXPECT_EQ(4, IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_z));
    }
    {
        IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_x) = 4;
        IUTEST_EXPECT_EQ(4, prod_test::s_prod.GetX());

        IUTEST_EXPECT_EQ(4, IUTEST_PEEP_GET(prod_test::s_prod, prod_test::ProdClass, m_x));
    }
}

#if IUTEST_HAS_PEEP_CLASS

IUTEST(PeepClassTest, ScopedPeep)
{
    {
        IUTEST_PEEP(prod_test::ProdClass, m_z) prod_class_z(&prod_test::s_prod);
        prod_class_z = 5;
        IUTEST_EXPECT_EQ(5, prod_test::s_prod.GetZ());

        IUTEST_EXPECT_EQ(5, prod_class_z);
    }
    {
        IUTEST_PEEP(prod_test::ProdClass, m_z) prod_class_z(&prod_test::s_prod);
        prod_class_z = 5;
        IUTEST_EXPECT_EQ(5, prod_test::s_prod.GetZ());

        IUTEST_EXPECT_EQ(5, prod_class_z);
    }
}
#endif

#endif
