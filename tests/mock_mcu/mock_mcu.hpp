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
    void set_gpio_level(int pin, int level);
    int get_gpio_level(int pin) const;
    void clear();
};