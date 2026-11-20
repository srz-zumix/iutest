//======================================================================
//-----------------------------------------------------------------------
/**
 * @file        smoke.cpp
 * @brief       PlatformIO smoke test for the ESP Google Test switch
 *
 * @author      t.shirayanagi
 * @par         copyright
 * This software is released under the new BSD License,
 * see LICENSE
*/
//-----------------------------------------------------------------------
//======================================================================

#include <Arduino.h>

#include "gtest/iutest_switch.hpp"

#if defined(ARDUINO_ARCH_ESP8266)
#  if !defined(IUTEST_OS_ESP8266) || !defined(GTEST_OS_ESP8266)
#    error ESP8266 platform detection failed
#  endif
#elif defined(ARDUINO_ARCH_ESP32)
#  if !defined(IUTEST_OS_ESP32) || !defined(GTEST_OS_ESP32)
#    error ESP32 platform detection failed
#  endif
#else
#  error Expected an ESP8266 or ESP32 Arduino target
#endif

TEST(EspSmoke, Addition)
{
    EXPECT_EQ(4, 2 + 2);
}

void setup()
{
    ::testing::InitGoogleTest();
    (void)RUN_ALL_TESTS();
}

void loop()
{
}
