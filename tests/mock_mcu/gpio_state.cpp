#include "gpio_state.hpp"

GPIOState::GPIOState(uint32_t pin_count) : _pin_levels(pin_count)
{
    clear();
}

int GPIOState::get_level(int pin) const
{
    if (pin < 0 || pin >= GPIO_MAX_PINS)
        return -1;
    return _pin_levels[pin].level;
}

void GPIOState::set_level(int pin, int level)
{
    if (pin < 0 || pin >= GPIO_MAX_PINS)
        return;
    _pin_levels[pin].level = level;
}

void GPIOState::clear()
{
    _pin_levels.assign(_pin_levels.size(), GPIO{});
}