//======================================================================
//-----------------------------------------------------------------------
/**
 * @file		iutest_switch_gmock.hpp
 * @brief		gmock 切り替え定義 ファイル
 *
 * @author		t.shirayanagi
 * @par			copyright
 * Copyright (C) 2014-2015, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_SWITCH_GMOCK_HPP_4212321D_F709_4904_AAF7_5E1BE18C0947_
#define INCG_IRIS_IUTEST_SWITCH_GMOCK_HPP_4212321D_F709_4904_AAF7_5E1BE18C0947_

#if !defined(IUTEST_USE_GTEST)

//======================================================================
// define

#else // !defined(IUTEST_USE_GTEST)

//======================================================================
// undef
#if defined(INCG_IRIS_IUTEST_HPP_)

#undef IUTEST_ASSERT_THAT
#undef IUTEST_EXPECT_THAT
#undef IUTEST_INFORM_THAT
#undef IUTEST_ASSUME_THAT

#undef IUTEST_HAS_MATCHERS
#undef IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF
#undef IUTEST_HAS_MATCHER_ELEMENTSARE
#undef IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD
#undef IUTEST_HAS_MATCHER_REGEX

#endif

//======================================================================
// define

#if defined(IUTEST_USE_GMOCK)

#define IUTEST_HAS_MATCHERS							1
#define IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF			1
#define IUTEST_HAS_MATCHER_ELEMENTSARE				1
#define IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD	0
#define IUTEST_HAS_MATCHER_REGEX					1

#define IUTEST_ASSERT_THAT		ASSERT_THAT
#define IUTEST_EXPECT_THAT		EXPECT_THAT
#define IUTEST_INFORM_THAT		INFORM_THAT
#define IUTEST_ASSUME_THAT		ASSUME_THAT

#define INFORM_THAT(value, matcher) \
	INFORM_PRED_FORMAT1(::testing::internal::MakePredicateFormatterFromMatcher(matcher), value)
#define ASSUME_THAT(value, matcher) \
	ASSUME_PRED_FORMAT1(::testing::internal::MakePredicateFormatterFromMatcher(matcher), value)
#else

#define IUTEST_HAS_MATCHERS							0
#define IUTEST_HAS_MATCHER_ALLOF_AND_ANYOF			0
#define IUTEST_HAS_MATCHER_ELEMENTSARE				0
#define IUTEST_HAS_MATCHER_ELEMENTSAREARRAYFORWARD	0
#define IUTEST_HAS_MATCHER_REGEX					0

#endif

//======================================================================
// using
#if defined(IUTEST_USE_GMOCK)

namespace testing {
namespace matchers
{

	using ::testing::Not;
	using ::testing::Eq;
	using ::testing::Ne;
	using ::testing::Lt;
	using ::testing::Le;
	using ::testing::Gt;
	using ::testing::Ge;
	using ::testing::IsNull;
	using ::testing::NotNull;
	using ::testing::DoubleEq;
	using ::testing::FloatEq;

	using ::testing::NanSensitiveDoubleEq;
	using ::testing::NanSensitiveFloatEq;

	using ::testing::StrEq;
	using ::testing::StrNe;
	using ::testing::StrCaseEq;
	using ::testing::StrCaseNe;
	using ::testing::HasSubstr;
	using ::testing::StartsWith;
	using ::testing::EndsWith;

	using ::testing::Contains;
	using ::testing::Each;
	using ::testing::ContainerEq;
	using ::testing::Pointwise;
	using ::testing::Key;
	using ::testing::Pair;
	using ::testing::Field;
	using ::testing::Property;

	using ::testing::ResultOf;
	using ::testing::Pointee;

	using ::testing::ElementsAre;
	using ::testing::ElementsAreArray;

	using ::testing::MatchesRegex;
	using ::testing::ContainsRegex;

	using ::testing::AllOf;
	using ::testing::AnyOf;

	using ::testing::A;
	using ::testing::_;
	using ::testing::TypedEq;

	template<typename T>
	inline internal::EqMatcher<T> Equals(T x) { return Eq(x); }

#if GMOCK_VER >= 0x01070000
	// gmock 1.7 later
	using ::testing::IsEmpty;
	using ::testing::SizeIs;
#endif

}	// end of namespace matchers
}	// end of namespace testing

#endif

#endif // !defined(IUTEST_USE_GTEST)

#endif // INCG_IRIS_IUTEST_SWITCH_SKIP_HPP_3CFB2B8D_9C8D_4B4F_9843_2FE38126BB31_
