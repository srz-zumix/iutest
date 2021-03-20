//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        throw_on_failure_tests.cpp
 * @brief       throw_on_fialure test
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2012-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "iutest.hpp"

#if IUTEST_HAS_EXCEPTIONS

IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_WARN_DISABLE_MISSING_NORETURN()

IUTEST(Expect, Test)
{
    IUTEST_EXPECT_EQ(2, 1);
}

IUTEST(Expect, Dummy)
{
}

IUTEST(Assert, Test)
{
    IUTEST_ASSERT_EQ(2, 1);
}

IUTEST(Assert, Dummy)
{
}

IUTEST(Throw, Test)
{
    throw 2;
}

IUTEST(Throw, Test2)
{
    throw ::std::bad_exception();
}

IUTEST(Throw, Dummy)
{
}

class SetUpTestCaseThrow : public ::iutest::Test
{
public:
    IUTEST_ATTRIBUTE_NORETURN_ static void SetUpTestCase()
    {
        throw 2;
    }
};

IUTEST_F(SetUpTestCaseThrow, Test)
{
    throw 2;
}

class SetUpThrow : public ::iutest::Test
{
public:
    void SetUp() IUTEST_CXX_OVERRIDE IUTEST_CXX_FINAL
    {
        throw 2;
    }
};

IUTEST_F(SetUpThrow, Test)
{
    throw 2;
}

IUTEST_PRAGMA_WARN_POP()

#endif

#ifdef UNICODE
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    printf("start");
    IUTEST_INIT(&argc, argv);
    ::iutest::IUTEST_FLAG(throw_on_failure) = true;
#if !defined(IUTEST_USE_GTEST)
    ::iutest::IUTEST_FLAG(catch_exceptions_global) = false;
#endif
#if defined(OUTPUTXML)
    // 失敗テストを含むので xml 出力しない
    ::iuutil::ReleaseDefaultXmlGenerator();
#endif

    printf("dummy");

    {
        ::iutest::IUTEST_FLAG(filter) = "*Dummy*";
        IUTEST_INIT(&argc, argv);
        if( IUTEST_RUN_ALL_TESTS() ) return 1;
    }

#if IUTEST_HAS_EXCEPTIONS
    printf("expect");

    try
    {
        ::iutest::IUTEST_FLAG(filter) = "*Expect*";
        IUTEST_INIT(&argc, argv);
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;

        return 1;
    }
    catch(...)
    {
    }

    printf("assert");

    try
    {
        ::iutest::IUTEST_FLAG(filter) = "*Assert*";
        IUTEST_INIT(&argc, argv);
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;

        return 1;
    }
    catch(...)
    {
    }

    printf("throw");

    try
    {
        ::iutest::IUTEST_FLAG(filter) = "Throw*";
        IUTEST_INIT(&argc, argv);
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;

        return 1;
    }
    catch(...)
    {
    }

    printf("setup throw");

    try
    {
        ::iutest::IUTEST_FLAG(filter) = "SetUpThrow*";
        IUTEST_INIT(&argc, argv);
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;

        return 1;
    }
    catch(...)
    {
    }

    printf("setup testcase throw");

    try
    {
        ::iutest::IUTEST_FLAG(filter) = "SetUpTestCaseThrow*";
        IUTEST_INIT(&argc, argv);
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;

        return 1;
    }
    catch(...)
    {
    }

#if !defined(IUTEST_USE_GTEST)
    printf("throw");

    try
    {
        ::iutest::IUTEST_FLAG(catch_exceptions_global) = true;
        ::iutest::IUTEST_FLAG(filter) = "Throw*";
        IUTEST_INIT(&argc, argv);
        if( IUTEST_RUN_ALL_TESTS() == 0 ) return 2;
    }
    catch(...)
    {
        return 1;
    }
#endif

#endif
    printf("*** Successful ***\n");
    return 0;
}
