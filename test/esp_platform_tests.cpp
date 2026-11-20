//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        esp_platform_tests.cpp
 * @brief       ESP platform and no-argument initialization tests
 *
 * @author      t.shirayanagi
 * @par         copyright
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include "gtest/iutest_switch.hpp"

#if !defined(IUTEST_USE_GTEST)
#if defined(ESP8266) || defined(ARDUINO_ARCH_ESP8266)
#  if !defined(IUTEST_OS_ESP8266) || !defined(GTEST_OS_ESP8266) || defined(GTEST_OS_ESP32)
#    error Incorrect ESP8266 platform macros
#  endif
#elif defined(ESP32) || defined(ARDUINO_ARCH_ESP32) || defined(ESP_PLATFORM)
#  if !defined(IUTEST_OS_ESP32) || !defined(GTEST_OS_ESP32) || defined(GTEST_OS_ESP8266)
#    error Incorrect ESP32 platform macros
#  endif
#elif defined(IUTEST_OS_ESP32) || defined(IUTEST_OS_ESP8266) || defined(GTEST_OS_ESP32) || defined(GTEST_OS_ESP8266)
#  error ESP platform macros must stay undefined on desktop builds
#endif

#if defined(IUTEST_OS_ESP8266) || defined(IUTEST_OS_ESP32)
#  if IUTEST_HAS_FOPEN || IUTEST_HAS_FILE_STAT || IUTEST_HAS_STD_FILESYSTEM || IUTEST_HAS_COLORCONSOLE \
      || IUTEST_HAS_SOCKET || IUTEST_HAS_STREAM_RESULT || IUTEST_HAS_STREAM_CAPTURE
#    error ESP builds should not enable desktop facilities by default
#  endif

#  include "logger_tests.hpp"

IUTEST(EspPlatform, NoEnvironment)
{
    IUTEST_EXPECT_EQ(-1, ::iutest::internal::posix::SetEnv("IUTEST_ESP_TEST", "1", 1));
    IUTEST_EXPECT_EQ(-1, ::iutest::internal::posix::PutEnv("IUTEST_ESP_TEST=1"));
    IUTEST_EXPECT_NULL(::iutest::internal::posix::GetEnv("IUTEST_ESP_TEST"));
}

IUTEST(EspPlatform, NoColor)
{
    ::iutest::IUTEST_FLAG(color) = "yes";
    TestLogger logger;
    typedef ::iutest::detail::iuConsole Console;
    ::iutest::detail::iuLogger* previous = Console::SetLogger(&logger);
    Console::color_output(Console::green, "plain text\n");
    Console::SetLogger(previous);
    IUTEST_EXPECT_STREQ("plain text\n", logger.c_str());
}
#endif

IUTEST(EspPlatform, TestRunsAfterInitializationWithoutArguments)
{
    IUTEST_SUCCEED();
}

#ifdef UNICODE
int wmain()
#else
int main()
#endif
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
#else
#  include "main.cpp"
#endif
