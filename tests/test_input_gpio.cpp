#include <gtest/gtest.h>

#include <mockoc.hpp>
#include <sabre_esp32/gpio/input_gpio.hpp>

TEST(InputGPIO, ResetCheckCorrectNumber)
{
    mockoc.clear();
    sabre::esp32::InputGPIO gpio(4);
    gpio.reset();
    ASSERT_TRUE(mockoc.was_called("gpio_reset_pin"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_reset_pin").args[0], "4");
}