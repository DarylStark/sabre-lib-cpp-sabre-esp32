#pragma once

#include "gpio_bank.hpp"

struct MockMCUConfiguration
{
    int gpio_count;
};

class MockMCU
{
private:
    GPIOBank _gpio_bank;
    bool _time_synced;

public:
    MockMCU(const MockMCUConfiguration config);
    void clear();

    GPIOBank &gpio_bank();

    void set_time_synced(bool synced);
    bool get_time_sync_status() const;
};