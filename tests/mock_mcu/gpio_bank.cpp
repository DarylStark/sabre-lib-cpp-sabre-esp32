#include "gpio_bank.hpp"

GPIOBank::GPIOBank(uint32_t pin_count) : _pin_levels(pin_count)
{
    clear();
}

void GPIOBank::clear()
{
    _pin_levels.assign(_pin_levels.size(), GPIO{});
}

int GPIOBank::get_level(int pin) const
{
    if (pin < 0 || pin >= _pin_levels.size())
        return -1;
    return _pin_levels[pin].level;
}

void GPIOBank::set_level(int pin, int level)
{
    if (pin < 0 || pin >= _pin_levels.size())
        return;
    _pin_levels[pin].level = level;
}

void GPIOBank::set_isr_handler(int pin, std::function<void(int)> handler)
{
    if (pin < 0 || pin >= _pin_levels.size())
        return;
    _pin_levels[pin].interrupt_handler = handler;
}

void GPIOBank::run_isr(int pin)
{
    if (pin < 0 || pin >= _pin_levels.size())
        return;
    if (_pin_levels[pin].interrupt_handler)
        _pin_levels[pin].interrupt_handler(pin);
}
