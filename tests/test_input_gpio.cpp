// #include <gpio_bank.hpp>
#include <gtest/gtest.h>
#include <mcu.hpp>
#include <mockoc.hpp>
#include <sabre_esp32/gpio/input_gpio.hpp>

using namespace sabre::esp32;

class InputGPIOMockTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mockoc.clear();
        mock_mcu.clear();
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

TEST_F(InputGPIOMockTest, AddISRCheckIfISRServiceIsInstalled)
{
    InputGPIO gpio(9);
    gpio.add_interrupt_handler([](int) {}, sabre::ISRTrigger::RISING);
    ASSERT_TRUE(mockoc.was_called("gpio_install_isr_service"));
}

TEST_F(InputGPIOMockTest, AddISRCheckIfISRServiceIsNotInstalledTwice)
{
    InputGPIO gpio_9(9);
    InputGPIO gpio_10(10);
    gpio_9.add_interrupt_handler([](int) {}, sabre::ISRTrigger::RISING);
    mockoc.clear();
    gpio_10.add_interrupt_handler([](int) {}, sabre::ISRTrigger::RISING);
    ASSERT_FALSE(mockoc.was_called("gpio_install_isr_service"));
}

TEST_F(InputGPIOMockTest, GetLevelReturnsCorrectValueFalse)
{
    InputGPIO gpio(11);
    mock_mcu.gpio_bank().set_level(11, 0);
    bool level = gpio.get_level();
    ASSERT_EQ(level, false);
}

TEST_F(InputGPIOMockTest, GetLevelReturnsCorrectValueTrue)
{
    InputGPIO gpio(11);
    mock_mcu.gpio_bank().set_level(11, 1);
    bool level = gpio.get_level();
    ASSERT_EQ(level, true);
}

TEST_F(InputGPIOMockTest, GetLevelReturnsCorrectValueFloating)
{
    InputGPIO gpio(11);
    bool level = gpio.get_level();
    ASSERT_EQ(level, false);
}

TEST_F(InputGPIOMockTest, SetAndRunISR)
{
    InputGPIO gpio(11);
    uint32_t gpio_number = 0;
    gpio.add_interrupt_handler([&gpio_number](int pin) { gpio_number = pin; },
                               sabre::ISRTrigger::RISING);
    mock_mcu.gpio_bank().run_isr(11);
    ASSERT_EQ(gpio_number, 11);
}

TEST_F(InputGPIOMockTest, IsResettedInDestructor)
{
    {
        InputGPIO gpio(12);
    }
    ASSERT_TRUE(mockoc.was_called("gpio_reset_pin"));
    ASSERT_EQ(mockoc.last_call_for_function("gpio_reset_pin").args[0], "12");
}