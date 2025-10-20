#include "mock_mcu.hpp"

MockMCU::MockMCU(const MockMCUConfiguration config)
    : _gpio_bank(config.gpio_count)
{
}

void MockMCU::set_gpio_level(int pin, int level)
{
    _gpio_bank.set_level(pin, level);
}

int MockMCU::get_gpio_level(int pin) const
{
    return _gpio_bank.get_level(pin);
}

void MockMCU::clear()
{
    _gpio_bank.clear();
}