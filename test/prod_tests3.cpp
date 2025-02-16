//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        prod_tests3.cpp
 * @brief       product code access test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2025, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"
#include "prod_tests.hpp"

#if IUTEST_HAS_PEEP

class IClassA
{
public:
    virtual void funcA() = 0;
};

class IClassB
{
public:
    virtual void funcB() = 0;
};

class ClassAB : public IClassA, public IClassB
{
private:
    int privateValue = 1;

public:
    void funcA() override {}
    void funcB() override {}
};

IUTEST_MAKE_PEEP(int ClassAB::*, ClassAB, privateValue);
IUTEST(ClassAB, getPrivateValue)
{
    ClassAB classAB;

    int actual = IUTEST_PEEP_GET(classAB, ClassAB, privateValue);
    IUTEST_EXPECT_EQ(1, actual);
}

#endif
