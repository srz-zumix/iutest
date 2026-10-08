//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        uninstantiated_param_tests.cpp
 * @brief       uninstantiated parameterized test verification
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2011-2022, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "../include/gtest/iutest_switch.hpp"

#if IUTEST_HAS_PARAM_TEST
class AllowedValueSuite : public ::iutest::TestWithParam<int> {};
IUTEST_P(AllowedValueSuite, Test) {}
IUTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(AllowedValueSuite);

class AllowedGTestSuite : public ::iutest::TestWithParam<int> {};
IUTEST_P(AllowedGTestSuite, Test) {}
IUTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(AllowedGTestSuite);

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_UNINSTANTIATED_PARAMETERIZED_TEST
class MissingValueSuite : public ::iutest::TestWithParam<int> {};
IUTEST_P(MissingValueSuite, Test) {}

class EmptyValueSuite : public ::iutest::TestWithParam<int> {};
IUTEST_P(EmptyValueSuite, Test) {}
IUTEST_INSTANTIATE_TEST_SUITE_P(Empty, EmptyValueSuite, ::iutest::Range(0, 0));

class NoPatternSuite : public ::iutest::TestWithParam<int> {};
IUTEST_INSTANTIATE_TEST_SUITE_P(Orphan, NoPatternSuite, ::iutest::Values(1));
#endif
#endif

#if IUTEST_HAS_TYPED_TEST_P
template<typename T> class AllowedTypedSuite : public ::iutest::Test {};
IUTEST_TYPED_TEST_SUITE_P(AllowedTypedSuite);
IUTEST_TYPED_TEST_P(AllowedTypedSuite, Test) {}
IUTEST_REGISTER_TYPED_TEST_SUITE_P(AllowedTypedSuite, Test);
IUTEST_ALLOW_UNINSTANTIATED_PARAMETERIZED_TEST(AllowedTypedSuite);

#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_UNINSTANTIATED_PARAMETERIZED_TEST
template<typename T> class MissingTypedSuite : public ::iutest::Test {};
IUTEST_TYPED_TEST_SUITE_P(MissingTypedSuite);
IUTEST_TYPED_TEST_P(MissingTypedSuite, Test) {}
IUTEST_REGISTER_TYPED_TEST_SUITE_P(MissingTypedSuite, Test);
#endif
#endif

IUTEST(Verification, Runs) {}

int main(int argc, char** argv)
{
    IUTEST_INIT(&argc, argv);
#if !defined(IUTEST_USE_GTEST) && IUTEST_HAS_UNINSTANTIATED_PARAMETERIZED_TEST
    const ::iutest::UnitTest* unit = ::iutest::UnitTest::GetInstance();
    const ::iutest::TestSuite* suite = NULL;
    for( int i=0; i < unit->total_test_suite_count(); ++i )
    {
        if( ::std::string(unit->GetTestSuite(i)->name()) == "GoogleTestVerification" )
        {
            suite = unit->GetTestSuite(i);
        }
    }
    const int expected = (IUTEST_HAS_PARAM_TEST ? 3 : 0) + (IUTEST_HAS_TYPED_TEST_P ? 1 : 0);
    if( (suite == NULL && expected != 0) || (suite != NULL && suite->total_test_count() != expected) ) return 1;
    const char* names[] = {
#if IUTEST_HAS_PARAM_TEST
        "UninstantiatedParameterizedTestSuite<MissingValueSuite>",
        "UninstantiatedParameterizedTestSuite<EmptyValueSuite>",
        "UninstantiatedParameterizedTestSuite<NoPatternSuite>",
#endif
#if IUTEST_HAS_TYPED_TEST_P
        "UninstantiatedTypeParameterizedTestSuite<MissingTypedSuite>",
#endif
        NULL
    };
    for( int i=0; i < expected; ++i )
    {
        bool found = false;
        for( int j=0; j < suite->total_test_count(); ++j )
        {
            if( ::std::string(suite->GetTestInfo(j)->name()) == names[i] ) found = true;
        }
        if( !found ) return 1;
    }
    ::iutest::IUTEST_FLAG(filter) = "Verification.*";
    if( IUTEST_RUN_ALL_TESTS() != 0 ) return 1;
#if IUTEST_HAS_PARAM_TEST || IUTEST_HAS_TYPED_TEST_P
    #if defined(DISABLE_FALSE_POSITIVE_XML)
        ::iuutil::ReleaseDefaultXmlGenerator();
    #endif
        ::iutest::IUTEST_FLAG(filter) = "GoogleTestVerification.*";
        if( IUTEST_RUN_ALL_TESTS() == 0 || unit->failed_test_count() != expected ) return 1;
#endif
    return 0;
#else
    return IUTEST_RUN_ALL_TESTS();
#endif
}
