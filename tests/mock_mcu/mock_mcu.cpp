#include "mock_mcu.hpp"

MockMCU::MockMCU(const MockMCUConfiguration config)
    : _gpio_bank(config.gpio_count), _time_synced(false)
{
}

void MockMCU::clear()
{
    _gpio_bank.clear();
    _time_synced = false;
}

GPIOBank &MockMCU::gpio_bank()
{
    return _gpio_bank;
}

void MockMCU::set_time_synced(bool synced)
{
    _time_synced = synced;
}

bool MockMCU::get_time_sync_status() const
{
    return _time_synced;
}