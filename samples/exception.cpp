//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        exception.cpp
 * @brief       exception sample
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#include "../include/iutest.hpp"


/* ---------------------------------------------------
 * 例外アサーション
*//*--------------------------------------------------*/
#if IUTEST_HAS_EXCEPTIONS

static void ExceptionFunction(int i)
{
    switch( i )
    {
    case 0:
        return;
    case 1:
        throw 2;
    case 2:
        throw ::std::bad_exception();
    case 3:
        throw "error";
    case 4:
        throw ::std::string("error");
    default:
        break;
    }
}

IUTEST(AssertionTest, Exception)
{
    IUTEST_EXPECT_THROW(ExceptionFunction(2), ::std::bad_exception);
    IUTEST_EXPECT_ANY_THROW(ExceptionFunction(1));
    IUTEST_EXPECT_NO_THROW(ExceptionFunction(0));

    IUTEST_EXPECT_THROW_VALUE_EQ(ExceptionFunction(1), int, 2);
    IUTEST_EXPECT_THROW_VALUE_NE(ExceptionFunction(1), int, 0);

    IUTEST_ASSERT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "error");
    IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "Error");
}

#if !defined(_MSC_VER) || _MSC_VER >= 1310

class exception_test
{
public:
    explicit exception_test(const ::std::vector<int>&)
    {
        IUTEST_SUPPRESS_UNREACHABLE_CODE_WARNING(throw ::std::exception());
    }
};

IUTEST(AssertionTest, Exception2)
{
    ::std::vector<int> a;
    IUTEST_ASSERT_THROW(exception_test(a), ::std::exception);
}

#endif

#if IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION
IUTEST(TestFailure, SEH)
{
    int* p = reinterpret_cast<int*>(0x1234);
    IUTEST_EXPECT_ANY_THROW(*p = 1);
}
#endif

#endif

/* ---------------------------------------------------
 * 失敗の確認
*//*--------------------------------------------------*/
#if IUTEST_HAS_EXCEPTIONS
IUTEST(DISABLED_TestFailure, Exception)
{
    IUTEST_EXPECT_THROW(ExceptionFunction(0), int);
    IUTEST_EXPECT_ANY_THROW(ExceptionFunction(0));
    IUTEST_EXPECT_NO_THROW(ExceptionFunction(2));
    IUTEST_EXPECT_NO_THROW(throw "error");

    IUTEST_EXPECT_THROW_VALUE_EQ(ExceptionFunction(1), int, 0);
    IUTEST_EXPECT_THROW_VALUE_NE(ExceptionFunction(1), int, 2);

    IUTEST_EXPECT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "Error");
    IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "rror");
}

IUTEST(DISABLED_TestFailure, UnexpectedException1)
{
    throw "fail";
}

IUTEST(DISABLED_TestFailure, UnexpectedException2)
{
IUTEST_PRAGMA_WARN_PUSH()
IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_BEGIN()
IUTEST_PRAGMA_WARN_DISABLE_NONNULL()

    strcpy(NULL, NULL);

IUTEST_PRAGMA_CRT_SECURE_WARN_DISABLE_END()
IUTEST_PRAGMA_WARN_POP()
}

#endif
