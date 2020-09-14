//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        exception_assertion_tests.cpp
 * @brief       iutest test 例外アサーションテスト
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2014-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

//======================================================================
// include
#include "../include/gtest/iutest_spi_switch.hpp"

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
    case 5:
        throw 0.1f;
    case -1:
        {
            int* p = reinterpret_cast<int*>(0x1234);
            *p = 1;
        }
        break;
    default:
        break;
    }
}

IUTEST(Exception, Throw)
{
    //IUTEST_ASSERT_THROW(throw ::std::bad_exception(), ::std::bad_exception);
    IUTEST_ASSERT_THROW(ExceptionFunction(2), ::std::bad_exception);
    IUTEST_EXPECT_THROW(ExceptionFunction(2), ::std::bad_exception);
    IUTEST_INFORM_THROW(ExceptionFunction(2), ::std::bad_exception);
    IUTEST_ASSUME_THROW(ExceptionFunction(2), ::std::bad_exception);
}

IUTEST(Exception, AnyThrow)
{
    IUTEST_ASSERT_ANY_THROW(throw ::std::bad_exception());
    IUTEST_ASSERT_ANY_THROW(throw 1);
    IUTEST_ASSERT_ANY_THROW(ExceptionFunction(1));
    IUTEST_EXPECT_ANY_THROW(ExceptionFunction(1));
    IUTEST_INFORM_ANY_THROW(ExceptionFunction(1));
    IUTEST_ASSUME_ANY_THROW(ExceptionFunction(1));
}

IUTEST(Exception, NoThrow)
{
    IUTEST_ASSERT_NO_THROW((void)0);
    IUTEST_ASSERT_NO_THROW(ExceptionFunction(0));
    IUTEST_EXPECT_NO_THROW(ExceptionFunction(0));
    IUTEST_INFORM_NO_THROW(ExceptionFunction(0));
    IUTEST_ASSUME_NO_THROW(ExceptionFunction(0));
}

IUTEST(Exception, ValueEQ)
{
    IUTEST_ASSERT_THROW_VALUE_EQ(throw 2, int, 2);
    IUTEST_ASSERT_THROW_VALUE_EQ(ExceptionFunction(1), int, 2);
    IUTEST_EXPECT_THROW_VALUE_EQ(ExceptionFunction(1), int, 2);
    IUTEST_INFORM_THROW_VALUE_EQ(ExceptionFunction(1), int, 2);
    IUTEST_ASSUME_THROW_VALUE_EQ(ExceptionFunction(1), int, 2);
}

IUTEST(Exception, ValueNE)
{
    IUTEST_ASSERT_THROW_VALUE_NE(throw 2, int, 0);
    IUTEST_ASSERT_THROW_VALUE_NE(ExceptionFunction(1), int, 0);
    IUTEST_EXPECT_THROW_VALUE_NE(ExceptionFunction(1), int, 0);
    IUTEST_INFORM_THROW_VALUE_NE(ExceptionFunction(1), int, 0);
    IUTEST_ASSUME_THROW_VALUE_NE(ExceptionFunction(1), int, 0);
}

IUTEST(Exception, ValueSTREQ)
{
    IUTEST_ASSERT_THROW_VALUE_STREQ(throw "error", const char *, "error");
    IUTEST_ASSERT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "error");
    IUTEST_EXPECT_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "error");
    IUTEST_INFORM_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "error");
    IUTEST_ASSUME_THROW_VALUE_STREQ(ExceptionFunction(3), const char *, "error");
    IUTEST_ASSERT_THROW_VALUE_STREQ(throw ::std::string("error"), ::std::string, "error");
    IUTEST_ASSERT_THROW_VALUE_STREQ(ExceptionFunction(4), ::std::string, "error");
    IUTEST_EXPECT_THROW_VALUE_STREQ(ExceptionFunction(4), ::std::string, "error");
    IUTEST_INFORM_THROW_VALUE_STREQ(ExceptionFunction(4), ::std::string, "error");
    IUTEST_ASSUME_THROW_VALUE_STREQ(ExceptionFunction(4), ::std::string, "error");
}

IUTEST(Exception, ValueSTRCASEEQ)
{
    IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(throw "error", const char *, "Error");
    IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "Error");
    IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "Error");
    IUTEST_INFORM_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "Error");
    IUTEST_ASSUME_THROW_VALUE_STRCASEEQ(ExceptionFunction(3), const char *, "Error");
}

IUTEST(Exception, ValueFormat)
{
    IUTEST_ASSERT_THROW_PRED_FORMAT2(::iutest::internal::CmpHelperFloatingPointEQ<float>, ExceptionFunction(5), float, 0.1f);
}

#if IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION
IUTEST(Exception, SEH)
{
    IUTEST_ASSERT_THROW(ExceptionFunction(-1), ::iutest::detail::seh_exception);
    IUTEST_ASSERT_ANY_THROW(ExceptionFunction(-1));
    IUTEST_EXPECT_ANY_THROW(ExceptionFunction(-1));
    IUTEST_INFORM_ANY_THROW(ExceptionFunction(-1));
    IUTEST_ASSUME_ANY_THROW(ExceptionFunction(-1));
}
#endif

IUTEST(ExceptionFailure, Throw)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_THROW(throw "test", int), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_THROW(throw "test", int), "" );
}

IUTEST(ExceptionFailure, AnyThrow)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_ANY_THROW((void)0), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_ANY_THROW((void)0), "" );
}

IUTEST(ExceptionFailure, NoThrow)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_NO_THROW(throw 1), "" );
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_NO_THROW(throw "error"), "" );
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_NO_THROW(throw ::std::bad_exception()), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_NO_THROW(throw 1), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_NO_THROW(throw "error"), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_NO_THROW(throw ::std::bad_exception()), "" );
}

IUTEST(ExceptionFailure, ValueEQ)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_THROW_VALUE_EQ(throw 2, char, 2), "" );
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_THROW_VALUE_EQ(throw 2,  int, 0), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_THROW_VALUE_EQ(throw 2, char, 2), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_THROW_VALUE_EQ(throw 2,  int, 0), "" );
}

IUTEST(ExceptionFailure, ValueSTREQ)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_THROW_VALUE_STREQ(throw 1, const char*, "Error"), "" );
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_THROW_VALUE_STREQ(throw "error", const char*, "Error"), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_THROW_VALUE_STREQ(throw 1, const char*, "Error"), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_THROW_VALUE_STREQ(throw "error", const char*, "Error"), "" );
}

IUTEST(ExceptionFailure, ValueSTRCASEEQ)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(throw 1, const char*, "Error"), "" );
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_THROW_VALUE_STRCASEEQ(throw "test", const char*, "Error"), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(throw 1, const char*, "Error"), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_THROW_VALUE_STRCASEEQ(throw "test", const char*, "Error"), "" );
}

#if IUTEST_HAS_NOEXCEPT && 0

void Noexcept() IUTEST_CXX_NOEXCEPT_SPEC
{
    throw 1;
}


IUTEST(NoThrowFailure, Noexcept)
{
    IUTEST_ASSERT_FATAL_FAILURE( IUTEST_ASSERT_NO_THROW(Noexcept()), "" );
}

#endif

#if IUTEST_HAS_CATCH_SEH_EXCEPTION_ASSERTION
IUTEST(ExceptionFailure, SEH)
{
    IUTEST_ASSERT_FATAL_FAILURE   ( IUTEST_ASSERT_NO_THROW(ExceptionFunction(-1)), "" );
    IUTEST_ASSERT_NONFATAL_FAILURE( IUTEST_EXPECT_NO_THROW(ExceptionFunction(-1)), "" );
}
#endif

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

