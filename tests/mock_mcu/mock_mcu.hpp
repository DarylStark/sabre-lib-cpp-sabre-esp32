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

public:
    MockMCU(const MockMCUConfiguration config);
    void clear();

    GPIOBank &gpio_bank();
};