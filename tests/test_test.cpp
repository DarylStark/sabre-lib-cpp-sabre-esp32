#include <gtest/gtest.h>

#include <sabre_esp32/gpio/input_gpio.hpp>

TEST(InputGPIO, CheckCorrectNumber)
{
    sabre::esp32::InputGPIO gpio(4);
    gpio.reset();
}