//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        named_member_matcher_tests.cpp
 * @brief       Named Field and Property matcher tests
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

#if IUTEST_HAS_MATCHERS && (!defined(IUTEST_USE_GMOCK) || GMOCK_VER >= 0x01080100)

using ::iutest::matchers::Eq;
using ::iutest::matchers::Field;
using ::iutest::matchers::Ge;
using ::iutest::matchers::Property;

namespace {

struct MemberHolder
{
    int value;
    int GetValue() const { return value; }
    const int& GetReference() const { return value; }
};

const MemberHolder holder = { 7 };

} // namespace

IUTEST(NamedMemberMatcher, Field)
{
#if !defined(IUTEST_NO_SFINAE)
    IUTEST_EXPECT_THAT(holder, Field("named_field", &MemberHolder::value, 7));
    IUTEST_EXPECT_THAT(holder, Field(::std::string("named_field"), &MemberHolder::value, Ge(7)));
    IUTEST_EXPECT_THAT(holder, Field("", &MemberHolder::value, 7));
#endif
    IUTEST_EXPECT_THAT(&holder, Field("named_field", &MemberHolder::value, Eq(7)));
}

IUTEST(NamedMemberMatcher, Property)
{
#if !defined(IUTEST_NO_SFINAE)
    IUTEST_EXPECT_THAT(holder, Property("named_property", &MemberHolder::GetValue, 7));
    IUTEST_EXPECT_THAT(holder, Property(::std::string("named_property"), &MemberHolder::GetValue, Ge(7)));
    IUTEST_EXPECT_THAT(holder, Property("reference", &MemberHolder::GetReference, Eq(7)));
    IUTEST_EXPECT_THAT(holder, Property("", &MemberHolder::GetValue, 7));
#endif
    IUTEST_EXPECT_THAT(&holder, Property("named_property", &MemberHolder::GetValue, Eq(7)));
}

IUTEST(NamedMemberMatcher, FailureMessage)
{
#if !defined(IUTEST_NO_SFINAE)
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(holder, Field("named_field", &MemberHolder::value, 8)), "named_field");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(holder, Property("named_property", &MemberHolder::GetValue, 8)), "named_property");
#endif
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(&holder, Field("named_field", &MemberHolder::value, Eq(8))), "named_field");
    IUTEST_EXPECT_FATAL_FAILURE(
        IUTEST_ASSERT_THAT(&holder, Property("named_property", &MemberHolder::GetValue, Eq(8))), "named_property");
}

#if !defined(IUTEST_USE_GTEST)
IUTEST(NamedMemberMatcher, DescriptionAndLifetime)
{
    ::iutest::detail::FieldMatcher<int MemberHolder::*, int> field =
        Field(::std::string("saved_field"), &MemberHolder::value, 7);
    ::iutest::detail::PropertyMatcher<int (MemberHolder::*)() const, int> property =
        Property(::std::string("saved_property"), &MemberHolder::GetValue, 7);
    IUTEST_EXPECT_THAT(&holder, field);
    IUTEST_EXPECT_THAT(&holder, property);
    IUTEST_EXPECT_EQ("Field: 'saved_field' 7", field.WhichIs());
    IUTEST_EXPECT_EQ("Property: 'saved_property' 7", property.WhichIs());
    IUTEST_EXPECT_EQ("Field: 7", Field(&MemberHolder::value, 7).WhichIs());
    IUTEST_EXPECT_EQ("Property: 7", Property(&MemberHolder::GetValue, 7).WhichIs());
}

IUTEST(NamedMemberMatcher, Explanation)
{
    ::std::ostringstream field_explanation;
    ::std::ostringstream property_explanation;
    IUTEST_EXPECT_FALSE(Field("named_field", &MemberHolder::value, 8).MatchAndExplain(&holder, &field_explanation));
    IUTEST_EXPECT_FALSE(Property("named_property", &MemberHolder::GetValue, 8).MatchAndExplain(&holder, &property_explanation));
    IUTEST_EXPECT_EQ("whose field 'named_field' is 7", field_explanation.str());
    IUTEST_EXPECT_EQ("whose property 'named_property' is 7", property_explanation.str());
}
#endif

#endif

int main(int argc, char* argv[])
{
    IUTEST_INIT(&argc, argv);
    return IUTEST_RUN_ALL_TESTS();
}
