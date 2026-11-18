//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        direct_scoped_trace_tests.cpp
 * @brief       Direct ScopedTrace compatibility tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_spi_switch.hpp"

#if !defined(IUTEST_USE_GTEST) || GTEST_VER >= 0x01080100

namespace
{

::std::string CaptureTraceFailure()
{
#if defined(IUTEST_USE_GTEST)
    ::testing::TestPartResultArray results;
    {
        ::testing::ScopedFakeTestPartResultReporter reporter(
            ::testing::ScopedFakeTestPartResultReporter::INTERCEPT_ONLY_CURRENT_THREAD, &results);
        IUTEST_ADD_FAILURE() << "captured failure";
    }
    return results.GetTestPartResult(0).message();
#else
    ::iutest::detail::SPIFailureChecker checker(::iutest::TestPartResult::kNonFatalFailure);
    IUTEST_ADD_FAILURE() << "captured failure";
    return checker.GetTestPartResult(0).message();
#endif
}

#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
struct TraceMessage {};

::std::ostream& operator << (::std::ostream& os, const TraceMessage&)
{
    return os << "streamed trace message";
}
#endif

::std::string TraceAndReturn()
{
    ::testing::ScopedTrace trace("return.cpp", 321, "return trace");
    return CaptureTraceFailure();
}

}   // namespace

IUTEST(DirectScopedTraceTest, LocationAndCString)
{
    ::iutest::ScopedTrace trace("example.cpp", 123, "literal trace");
    const ::std::string result = CaptureTraceFailure();
    IUTEST_EXPECT_STRIN("example.cpp", result);
    IUTEST_EXPECT_TRUE(result.find(":123") != ::std::string::npos
        || result.find("(123)") != ::std::string::npos);
    IUTEST_EXPECT_STRIN("literal trace", result);
}

IUTEST(DirectScopedTraceTest, StringIsCopied)
{
    ::std::string message = "original trace string";
    ::testing::ScopedTrace trace("string.cpp", 234, message);
    message = "changed trace string";
    const ::std::string result = CaptureTraceFailure();
    IUTEST_EXPECT_STRIN("original trace string", result);
    IUTEST_EXPECT_STRNOTIN("changed trace string", result);
}

IUTEST(DirectScopedTraceTest, MutableCStringIsCopied)
{
    char message[] = "mutable trace";
    ::iutest::ScopedTrace trace("mutable.cpp", 345, message);
    message[0] = 'X';
    const ::std::string result = CaptureTraceFailure();
    IUTEST_EXPECT_STRIN("mutable trace", result);
    IUTEST_EXPECT_STRNOTIN("Xutable trace", result);
}

IUTEST(DirectScopedTraceTest, StreamableMessages)
{
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
    ::iutest::ScopedTrace object_trace("stream.cpp", 456, TraceMessage());
#endif
    ::testing::ScopedTrace number_trace("number.cpp", 567, 987654);
    ::testing::ScopedTrace message_trace("message.cpp", 678, ::iutest::Message() << "message trace " << 42);
    const ::std::string result = CaptureTraceFailure();
#if IUTEST_HAS_STRINGSTREAM || IUTEST_HAS_STRSTREAM
    IUTEST_EXPECT_STRIN("streamed trace message", result);
#endif
    IUTEST_EXPECT_STRIN("987654", result);
    IUTEST_EXPECT_STRIN("message trace 42", result);
}

IUTEST(DirectScopedTraceTest, NullAndEmptyMessages)
{
    ::iutest::ScopedTrace null_trace("null.cpp", 789, static_cast<const char*>(NULL));
    ::testing::ScopedTrace empty_trace("empty.cpp", 890, "");
    const ::std::string result = CaptureTraceFailure();
    IUTEST_EXPECT_STRIN("null.cpp", result);
    IUTEST_EXPECT_STRIN("(null)", result);
    IUTEST_EXPECT_STRIN("empty.cpp", result);
}

IUTEST(DirectScopedTraceTest, NestedScopesAndMacros)
{
    ::std::string nested, outer, finished;
    {
        ::iutest::ScopedTrace outer_trace("outer.cpp", 12, "outer direct trace");
        IUTEST_SCOPED_TRACE("outer macro trace");
        {
            ::testing::ScopedTrace inner_trace("inner.cpp", 34, "inner direct trace");
            SCOPED_TRACE("inner macro trace");
            nested = CaptureTraceFailure();
        }
        outer = CaptureTraceFailure();
    }
    finished = CaptureTraceFailure();
    IUTEST_EXPECT_STRIN("outer direct trace", nested);
    IUTEST_EXPECT_STRIN("outer macro trace", nested);
    IUTEST_EXPECT_STRIN("inner direct trace", nested);
    IUTEST_EXPECT_STRIN("inner macro trace", nested);
    IUTEST_EXPECT_STRIN("outer direct trace", outer);
    IUTEST_EXPECT_STRIN("outer macro trace", outer);
    IUTEST_EXPECT_STRNOTIN("inner direct trace", outer);
    IUTEST_EXPECT_STRNOTIN("inner macro trace", outer);
    IUTEST_EXPECT_STRNOTIN("outer direct trace", finished);
    IUTEST_EXPECT_STRNOTIN("outer macro trace", finished);
    IUTEST_EXPECT_STRNOTIN("inner direct trace", finished);
    IUTEST_EXPECT_STRNOTIN("inner macro trace", finished);
}

IUTEST(DirectScopedTraceTest, ReturnRemovesTrace)
{
    IUTEST_EXPECT_STRIN("return trace", TraceAndReturn());
    IUTEST_EXPECT_STRNOTIN("return trace", CaptureTraceFailure());
}

#if IUTEST_HAS_EXCEPTIONS
IUTEST(DirectScopedTraceTest, ExceptionRemovesTrace)
{
    ::std::string caught;
    {
        ::testing::ScopedTrace outer("exception.cpp", 56, "surviving trace");
        try
        {
            ::iutest::ScopedTrace inner("exception.cpp", 78, "unwound direct trace");
            SCOPED_TRACE("unwound macro trace");
            throw 1;
        }
        catch(...)
        {
            caught = CaptureTraceFailure();
        }
    }
    const ::std::string finished = CaptureTraceFailure();
    IUTEST_EXPECT_STRIN("surviving trace", caught);
    IUTEST_EXPECT_STRNOTIN("unwound direct trace", caught);
    IUTEST_EXPECT_STRNOTIN("unwound macro trace", caught);
    IUTEST_EXPECT_STRNOTIN("surviving trace", finished);
    IUTEST_EXPECT_STRNOTIN("unwound direct trace", finished);
    IUTEST_EXPECT_STRNOTIN("unwound macro trace", finished);
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
