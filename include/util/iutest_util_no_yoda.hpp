//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        iutest_util_no_yoda.hpp
 * @brief       Redefinition no Yoda conditions
 *
 * @author      t.shirayanagi
 * @par         copyright
 * Copyright (C) 2015-2021, Takazumi Shirayanagi\n
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================
#ifndef INCG_IRIS_IUTEST_UTIL_NO_YODA_HPP_96129715_90AA_4BA1_BFF9_E0644D291E10_
#define INCG_IRIS_IUTEST_UTIL_NO_YODA_HPP_96129715_90AA_4BA1_BFF9_E0644D291E10_

#ifdef IUTEST_ASSERT_EQ
#  undef IUTEST_ASSERT_EQ
#  define   IUTEST_ASSERT_EQ(actual, expected)      IUTEST_TEST_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
#ifdef IUTEST_EXPECT_EQ
#  undef IUTEST_EXPECT_EQ
#  define   IUTEST_EXPECT_EQ(actual, expected)      IUTEST_TEST_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
#ifdef IUTEST_INFORM_EQ
#  undef IUTEST_INFORM_EQ
#  define   IUTEST_INFORM_EQ(actual, expected)      IUTEST_TEST_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
#ifdef IUTEST_ASSUME_EQ
#  undef IUTEST_ASSUME_EQ
#  define   IUTEST_ASSUME_EQ(actual, expected)      IUTEST_TEST_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif


#ifdef IUTEST_ASSERT_FLOAT_EQ
#  undef IUTEST_ASSERT_FLOAT_EQ
#  define   IUTEST_ASSERT_FLOAT_EQ(actual, expected)        IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
#ifdef IUTEST_EXPECT_FLOAT_EQ
#  undef IUTEST_EXPECT_FLOAT_EQ
#  define   IUTEST_EXPECT_FLOAT_EQ(actual, expected)        IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
#ifdef IUTEST_INFORM_FLOAT_EQ
#  undef IUTEST_INFORM_FLOAT_EQ
#  define   IUTEST_INFORM_FLOAT_EQ(actual, expected)        IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
#ifdef IUTEST_ASSUME_FLOAT_EQ
#  undef IUTEST_ASSUME_FLOAT_EQ
#  define   IUTEST_ASSUME_FLOAT_EQ(actual, expected)        IUTEST_TEST_FLOAT_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif


#ifdef IUTEST_ASSERT_DOUBLE_EQ
#  undef IUTEST_ASSERT_DOUBLE_EQ
#  define   IUTEST_ASSERT_DOUBLE_EQ(actual, expected)       IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
#ifdef IUTEST_EXPECT_DOUBLE_EQ
#  undef IUTEST_EXPECT_DOUBLE_EQ
#  define   IUTEST_EXPECT_DOUBLE_EQ(actual, expected)       IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
#ifdef IUTEST_INFORM_DOUBLE_EQ
#  undef IUTEST_INFORM_DOUBLE_EQ
#  define   IUTEST_INFORM_DOUBLE_EQ(actual, expected)       IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
#ifdef IUTEST_ASSUME_DOUBLE_EQ
#  undef IUTEST_ASSUME_DOUBLE_EQ
#  define   IUTEST_ASSUME_DOUBLE_EQ(actual, expected)       IUTEST_TEST_DOUBLE_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif

#ifdef IUTEST_ASSERT_LONG_DOUBLE_EQ
#  undef IUTEST_ASSERT_LONG_DOUBLE_EQ
#  define   IUTEST_ASSERT_LONG_DOUBLE_EQ(actual, expected)  IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
#ifdef IUTEST_EXPECT_LONG_DOUBLE_EQ
#  undef IUTEST_EXPECT_LONG_DOUBLE_EQ
#  define   IUTEST_EXPECT_LONG_DOUBLE_EQ(actual, expected)  IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
#ifdef IUTEST_INFORM_LONG_DOUBLE_EQ
#  undef IUTEST_INFORM_LONG_DOUBLE_EQ
#  define   IUTEST_INFORM_LONG_DOUBLE_EQ(actual, expected)  IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
#ifdef IUTEST_ASSUME_LONG_DOUBLE_EQ
#  undef IUTEST_ASSUME_LONG_DOUBLE_EQ
#  define   IUTEST_ASSUME_LONG_DOUBLE_EQ(actual, expected)  IUTEST_TEST_LONG_DOUBLE_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif

#ifdef IUTEST_ASSERT_COMPLEX_EQ
#  undef IUTEST_ASSERT_COMPLEX_EQ
#  define   IUTEST_ASSERT_COMPLEX_EQ(actual, expected)  IUTEST_TEST_COMPLEX_EQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
#ifdef IUTEST_EXPECT_COMPLEX_EQ
#  undef IUTEST_EXPECT_COMPLEX_EQ
#  define   IUTEST_EXPECT_COMPLEX_EQ(actual, expected)  IUTEST_TEST_COMPLEX_EQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
#ifdef IUTEST_INFORM_COMPLEX_EQ
#  undef IUTEST_INFORM_COMPLEX_EQ
#  define   IUTEST_INFORM_COMPLEX_EQ(actual, expected)  IUTEST_TEST_COMPLEX_EQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
#ifdef IUTEST_ASSUME_COMPLEX_EQ
#  undef IUTEST_ASSUME_COMPLEX_EQ
#  define   IUTEST_ASSUME_COMPLEX_EQ(actual, expected)  IUTEST_TEST_COMPLEX_EQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif

#ifdef IUTEST_ASSERT_STREQ
#  undef IUTEST_ASSERT_STREQ
#  define   IUTEST_ASSERT_STREQ(actual, expected)           IUTEST_TEST_STREQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
#ifdef IUTEST_EXPECT_STREQ
#  undef IUTEST_EXPECT_STREQ
#  define   IUTEST_EXPECT_STREQ(actual, expected)           IUTEST_TEST_STREQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
#ifdef IUTEST_INFORM_STREQ
#  undef IUTEST_INFORM_STREQ
#  define   IUTEST_INFORM_STREQ(actual, expected)           IUTEST_TEST_STREQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
#ifdef IUTEST_ASSUME_STREQ
#  undef IUTEST_ASSUME_STREQ
#  define   IUTEST_ASSUME_STREQ(actual, expected)           IUTEST_TEST_STREQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif


#ifdef IUTEST_ASSERT_STRCASEEQ
#  undef IUTEST_ASSERT_STRCASEEQ
#  define   IUTEST_ASSERT_STRCASEEQ(actual, expected)       IUTEST_TEST_STRCASEEQ(expected, actual, IUTEST_ASSERT_FAILURE)
#endif
#ifdef IUTEST_EXPECT_STRCASEEQ
#  undef IUTEST_EXPECT_STRCASEEQ
#  define   IUTEST_EXPECT_STRCASEEQ(actual, expected)       IUTEST_TEST_STRCASEEQ(expected, actual, IUTEST_EXPECT_FAILURE)
#endif
#ifdef IUTEST_INFORM_STRCASEEQ
#  undef IUTEST_INFORM_STRCASEEQ
#  define   IUTEST_INFORM_STRCASEEQ(actual, expected)       IUTEST_TEST_STRCASEEQ(expected, actual, IUTEST_INFORM_FAILURE)
#endif
#ifdef IUTEST_ASSUME_STRCASEEQ
#  undef IUTEST_ASSUME_STRCASEEQ
#  define   IUTEST_ASSUME_STRCASEEQ(actual, expected)       IUTEST_TEST_STRCASEEQ(expected, actual, IUTEST_ASSUME_FAILURE)
#endif


#endif // INCG_IRIS_IUTEST_UTIL_TESTS_HPP_4095FF9B_D6B8_4CD3_BF86_43DFED1760EA_
