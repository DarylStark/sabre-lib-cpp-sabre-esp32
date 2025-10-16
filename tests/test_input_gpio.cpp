#include <gtest/gtest.h>
#include <mockoc.hpp>
#include <sabre_esp32/gpio/input_gpio.hpp>
using namespace sabre::esp32;

class InputGPIOMockTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockoc.clear();
    }
};

TEST_F(InputGPIOMockTest, ResetCallsCorrectFunction)
{
    InputGPIO gpio(4);
    gpio.reset();
    ASSERT_TRUE(mockoc.was_called("gpio_reset_pin"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_reset_pin").args[0], "4");
}

TEST_F(InputGPIOMockTest, ConstructorSetsDirection)
{
    InputGPIO gpio(5);
    ASSERT_TRUE(mockoc.was_called("gpio_set_direction"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_direction").args[0], "5");
    ASSERT_EQ(mockoc.last_call_for_function("gpio_set_direction").args[1], "1");
}

TEST_F(InputGPIOMockTest, EnablePullupCallsCorrectFunction)
{
    InputGPIO gpio(6);
    gpio.enable_pullup();
    ASSERT_TRUE(mockoc.was_called("gpio_pullup_en"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_pullup_en").args[0], "6");
}

TEST_F(InputGPIOMockTest, EnablePulldownCallsCorrectFunction)
{
    InputGPIO gpio(7);
    gpio.enable_pulldown();
    ASSERT_TRUE(mockoc.was_called("gpio_pulldown_en"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_pulldown_en").args[0], "7");
}

TEST_F(InputGPIOMockTest, DisablePullupCallsCorrectFunction)
{
    InputGPIO gpio(8);
    gpio.disable_pullup();
    ASSERT_TRUE(mockoc.was_called("gpio_pullup_dis"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_pullup_dis").args[0], "8");
}

TEST_F(InputGPIOMockTest, DisablePulldownCallsCorrectFunction)
{
    InputGPIO gpio(9);
    gpio.disable_pulldown();
    ASSERT_TRUE(mockoc.was_called("gpio_pulldown_dis"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_pulldown_dis").args[0], "9");
}