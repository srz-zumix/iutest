﻿//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_switch_assertion_return.hpp
 * @brief       AssertionReturn 切り替え対応 ファイル
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2013-2016, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_ASSERTION_RETURN_HPP_3913D1E7_E6FD_49B9_BB4C_795939FEB5C5_
#define INCG_IRIS_IUTEST_SWITCH_ASSERTION_RETURN_HPP_3913D1E7_E6FD_49B9_BB4C_795939FEB5C5_

#if !defined(IUTEST_USE_GTEST)

#else // !defined(IUTEST_USE_GTEST)

//======================================================================
// undef
#if defined(INCG_IRIS_IUTEST_HPP_)
#  undef IUTEST_HAS_ASSERTION_RETURN
#endif

//======================================================================
// define
#define IUTEST_HAS_ASSERTION_RETURN 1

#if defined(GTEST_MESSAGE_AT_)
#  undef GTEST_MESSAGE_AT_
#else
#  if defined(GTEST_MESSAGE_)
#    undef GTEST_MESSAGE_
#    define GTEST_MESSAGE_(message, result_type) GTEST_MESSAGE_AT_(__FILE__, __LINE__, message, result_type)
#  endif
#endif

#define GTEST_MESSAGE_AT_(file, line, message, result_type)                 \
    ::testing::internal::AssertHelperEx(result_type, file, line, message)   \
        = ::testing::AssertionMessage()

//======================================================================
// class
namespace testing
{

template<typename T>
struct AssertionReturnType
{
    T value;
    AssertionReturnType() {}
    AssertionReturnType(const T& v) : value(v) {}   // NOLINT
};
template<>
struct AssertionReturnType<void>
{
    AssertionReturnType() {}
};

template<typename T>
inline AssertionReturnType<T> AssertionReturn(const T& ret) { return AssertionReturnType<T>(ret); }
inline AssertionReturnType<void> AssertionReturn() { return AssertionReturnType<void>(); }

namespace internal
{

template<typename T>
struct AssertionFixed
{
    Message msg;
    AssertionReturnType<T> ret;
    AssertionFixed(const Message& message, const AssertionReturnType<T>& r) : msg(message), ret(r) {}
};

}   // end of namespace internal

class AssertionMessage : public Message
{
    typedef ::std::ostream& (*BasicNarrowIoManip)(::std::ostream&);
public:
    template<typename T>
    AssertionMessage& operator << (T val)
    {
        Message::operator << (val);
        return *this;
    }
    AssertionMessage& operator << (BasicNarrowIoManip val)
    {
        Message::operator << (val);
        return *this;
    }
    AssertionMessage& operator << (const AssertionReturnType<void>&)
    {
        return *this;
    }
    template<typename R>
    internal::AssertionFixed<R> operator << (const AssertionReturnType<R>& r)
    {
        return internal::AssertionFixed<R>(*this, r);
    }
private:
    void operator=(const AssertionMessage&);
};

namespace internal
{

class AssertHelperEx : public AssertHelper
{
public:
    AssertHelperEx(TestPartResult::Type type, const char* file, int line, const char* message)
        : AssertHelper(type, file, line, message) {}

    void operator = (const Message& message) const
    {
        AssertHelper::operator = (message);
    }
    template<typename R>
    R operator = (const AssertionFixed<R>& fixed) const
    {
        AssertHelper::operator = (fixed.msg);
        return fixed.ret.value;
    }
private:
    GTEST_DISALLOW_COPY_AND_ASSIGN_(AssertHelperEx);
};

}   // end of namespace internal
}   // end of namespace testing

#endif // !defined(IUTEST_USE_GTEST)

#endif // INCG_IRIS_IUTEST_SWITCH_ASSERTION_RETURN_HPP_3913D1E7_E6FD_49B9_BB4C_795939FEB5C5_
