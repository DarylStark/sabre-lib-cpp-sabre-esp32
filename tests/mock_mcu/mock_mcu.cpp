#include "mock_mcu.hpp"

MockMCU::MockMCU(const MockMCUConfiguration config)
    : _gpio_bank(config.gpio_count)
{
}

void MockMCU::clear()
{
    _gpio_bank.clear();
}

GPIOBank &MockMCU::gpio_bank()
{
    return _gpio_bank;
}