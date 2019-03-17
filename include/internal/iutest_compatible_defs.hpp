//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_compatible_defs.hpp
 * @brief       internal gtest/iutest compatible definition
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2019, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_COMPATIBLE_DEFS_HPP_9BCFF3D0_A045_4B94_B51F_4C6E88D8654C_
#define INCG_IRIS_IUTEST_COMPATIBLE_DEFS_HPP_9BCFF3D0_A045_4B94_B51F_4C6E88D8654C_

namespace iutest_compatible
{

//======================================================================
// function

/**
 * @internal
 * @brief   NULL リテラルかどうか
*/
struct IsNullLiteralHelper
{
    class Object;

    static char IsNullLiteral(Object*);
    static char (&IsNullLiteral(...))[2];
};

}   // end of namespace iutest_compatible

#endif // INCG_IRIS_IUTEST_COMPATIBLE_DEFS_HPP_9BCFF3D0_A045_4B94_B51F_4C6E88D8654C_
