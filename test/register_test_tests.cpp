//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        register_test_tests.cpp
 * @brief       runtime test registration tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2026, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_switch.hpp"
#include "../include/gtest/iutest_spi_switch.hpp"
#include "logger_tests.hpp"

#if IUTEST_HAS_REGISTER_TEST

namespace
{
int created = 0;
int destroyed = 0;
int executed = 0;
int suite_setup = 0;
int suite_teardown = 0;
int setup = 0;
int teardown = 0;
::iutest::TestInfo* registered_info = NULL;

class RuntimeFixture : public ::iutest::Test
{
protected:
    static void SetUpTestSuite() { ++suite_setup; }
    static void TearDownTestSuite() { ++suite_teardown; }

    virtual void SetUp() IUTEST_CXX_OVERRIDE { ++setup; }
    virtual void TearDown() IUTEST_CXX_OVERRIDE { ++teardown; }
};

class RuntimeTest : public RuntimeFixture
{
public:
    explicit RuntimeTest(int value) : m_value(value) { ++created; }
    virtual ~RuntimeTest() { ++destroyed; }

private:
#if defined(IUTEST_USE_GTEST)
    virtual void TestBody() IUTEST_CXX_OVERRIDE
#else
    virtual void Body() IUTEST_CXX_OVERRIDE
#endif
    {
        IUTEST_EXPECT_EQ(42, m_value);
        IUTEST_EXPECT_EQ(1, suite_setup - suite_teardown);
        ++executed;
    }
    int m_value;
};

RuntimeFixture* MakeTest()
{
    return new RuntimeTest(42);
}

struct MoveOnlyFactory
{
    MoveOnlyFactory() {}
    MoveOnlyFactory(MoveOnlyFactory&&) {}
    RuntimeFixture* operator()() { return MakeTest(); }

private:
    MoveOnlyFactory(const MoveOnlyFactory&);
    MoveOnlyFactory& operator=(const MoveOnlyFactory&);
};

IUTEST(RegisterTest, Metadata)
{
    IUTEST_ASSERT_NOTNULL(registered_info);
    IUTEST_EXPECT_STREQ("RuntimeSuite", registered_info->test_suite_name());
    IUTEST_EXPECT_STREQ("Captured", registered_info->name());
    IUTEST_EXPECT_STREQ("RuntimeType", registered_info->type_param());
    IUTEST_EXPECT_STREQ("value<&>", registered_info->value_param());
    IUTEST_EXPECT_STREQ("runtime_test.cpp", registered_info->file());
    IUTEST_EXPECT_EQ(123, registered_info->line());
}

#if !defined(IUTEST_USE_GTEST)
::iutest::Test* MakeOtherTest() { return new RuntimeTest(42); }

void RegisterMismatchedFixture()
{
    IUTEST_EXPECT_NULL(::iutest::RegisterTest("RuntimeSuite", "WrongFixture", NULL, NULL
        , __FILE__, __LINE__, &MakeOtherTest));
}

IUTEST(RegisterTest, RejectMismatchedFixture)
{
    IUTEST_EXPECT_NONFATAL_FAILURE(RegisterMismatchedFixture(), "same fixture type");
    IUTEST_EXPECT_NONFATAL_FAILURE(::iutest::RegisterTest("RegisterTest", "WrongFixture", NULL, NULL
        , __FILE__, __LINE__, &MakeTest), "same fixture type");
}
#endif
}   // namespace

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_STRINGSTREAM
class RegisterTestFile : public ::iutest::StringStreamFile
{
public:
    static ::std::string xml;
    virtual void Close() IUTEST_CXX_OVERRIDE { xml = ss.str(); }
};
::std::string RegisterTestFile::xml;
IUTEST_FILESYSTEM_INSTANTIATE(RegisterTestFile);
#endif

#else
IUTEST(RegisterTest, NotSupported) {}
#endif

int main(int argc, char* argv[])
{
#if IUTEST_HAS_REGISTER_TEST
    {
#if IUTEST_HAS_LAMBDA
        int value = 42;
#endif
        const ::std::string suite = "RuntimeSuite";
        const ::std::string name = "Captured";
        const ::std::string type = "RuntimeType";
        const ::std::string param = "value<&>";
        const ::std::string file = "runtime_test.cpp";
        registered_info = ::iutest::RegisterTest(suite.c_str(), name.c_str(), type.c_str(), param.c_str()
            , file.c_str(), 123
#if IUTEST_HAS_LAMBDA
            , [value]() -> RuntimeFixture* { return new RuntimeTest(value); });
#else
            , &MakeTest);
#endif
    }
#endif
    IUTEST_INIT(&argc, argv);
#if IUTEST_HAS_REGISTER_TEST
    ::testing::RegisterTest("RuntimeSuite", "Function", "RuntimeType", NULL, __FILE__, __LINE__, &MakeTest);
    ::iutest::TestInfo* plain = ::iutest::RegisterTest("PlainSuite", "MoveOnly", NULL, NULL
        , __FILE__, __LINE__, MoveOnlyFactory());
    if( plain == NULL || plain->type_param() != NULL || plain->value_param() != NULL || created != 0 ) return 1;
#if !defined(IUTEST_USE_GTEST)
    static TestLogger logger;
    ::iutest::detail::iuConsole::SetLogger(&logger);
#if IUTEST_HAS_STRINGSTREAM
    ::iutest::IUTEST_FLAG(output) = "xml:register_test.xml";
#endif
#endif
#endif
    const int result = IUTEST_RUN_ALL_TESTS();
    if( result != 0 ) return result;
#if IUTEST_HAS_REGISTER_TEST
    if( created != 3 || destroyed != 3 || executed != 3 || setup != 3 || teardown != 3
        || suite_setup != 2 || suite_teardown != 2 ) return 1;
#if !defined(IUTEST_USE_GTEST)
    IUTEST_EXPECT_STRIN("RuntimeSuite.Captured", logger.c_str());
    IUTEST_EXPECT_STRIN("TypeParam = RuntimeType", logger.c_str());
#if IUTEST_HAS_STRINGSTREAM
    IUTEST_EXPECT_STRIN("name=\"Captured\" file=\"runtime_test.cpp\" line=\"123\"", RegisterTestFile::xml);
    IUTEST_EXPECT_STRIN("type_param=\"RuntimeType\"", RegisterTestFile::xml);
    IUTEST_EXPECT_STRIN("value_param=\"value&lt;&amp;&gt;\"", RegisterTestFile::xml);
#endif
    ::iutest::IUTEST_FLAG(list_tests_with_where) = true;
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
    IUTEST_EXPECT_STRIN("value<&>", logger.c_str());
    ::iutest::detail::iuConsole::SetLogger(NULL);
    if( !::iutest::UnitTest::GetInstance()->Passed() ) return 1;
#endif
#endif
    return 0;
}
