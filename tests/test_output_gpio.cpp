#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/gpio/output_gpio.hpp>

using namespace sabre::esp32;

class OutputGPIOMockTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockoc.clear();
        mock_mcu.clear();
    }
};

TEST_F(OutputGPIOMockTest, ResetCallsCorrectFunction)
{
    OutputGPIO gpio(4);
    gpio.reset();
    ASSERT_TRUE(mockoc.was_called("gpio_reset_pin"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_reset_pin").args[0], "4");
}

TEST_F(OutputGPIOMockTest, SetHigh)
{
    OutputGPIO gpio(4);
    gpio.set_high();
    ASSERT_TRUE(mockoc.was_called("gpio_set_level"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_level").args[0], "4");
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_level").args[1], "1");
}

TEST_F(OutputGPIOMockTest, SetLow)
{
    OutputGPIO gpio(4);
    gpio.set_low();
    ASSERT_TRUE(mockoc.was_called("gpio_set_level"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_level").args[0], "4");
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_level").args[1], "0");
}

TEST_F(OutputGPIOMockTest, SetLevelHigh)
{
    OutputGPIO gpio(4);
    gpio.set_level(true);
    ASSERT_TRUE(mockoc.was_called("gpio_set_level"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_level").args[0], "4");
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_level").args[1], "1");
}

TEST_F(OutputGPIOMockTest, SetLevelLow)
{
    OutputGPIO gpio(4);
    gpio.set_level(false);
    ASSERT_TRUE(mockoc.was_called("gpio_set_level"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_level").args[0], "4");
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_level").args[1], "0");
}

TEST_F(OutputGPIOMockTest, IsResettedInDestructor)
{
    {
        OutputGPIO gpio(12);
    }
    ASSERT_TRUE(mockoc.was_called("gpio_reset_pin"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_reset_pin").args[0], "12");
}