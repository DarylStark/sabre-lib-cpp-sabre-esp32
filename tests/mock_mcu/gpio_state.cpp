#include "gpio_state.hpp"

GPIOState gpio_state;

GPIOState::GPIOState()
{
    clear();
}

int GPIOState::get_level(int pin) const
{
    if (pin < 0 || pin >= GPIO_MAX_PINS)
        return -1;
    return _pin_levels[pin];
}

void GPIOState::set_level(int pin, int level)
{
    if (pin < 0 || pin >= GPIO_MAX_PINS)
        return;
    _pin_levels[pin] = level;
}

void GPIOState::clear()
{
    _pin_levels.fill(-1);
}