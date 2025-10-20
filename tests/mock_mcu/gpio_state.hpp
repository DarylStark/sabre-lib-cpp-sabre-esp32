#ifndef MOCK_MCU_GPIO_STATE_HPP
#define MOCK_MCU_GPIO_STATE_HPP

#include <array>

// Number of pins supported by the mock (covers GPIO_NUM_0 .. GPIO_NUM_39)
constexpr int GPIO_MAX_PINS = 40;

class GPIOState
{
private:
    std::array<int, GPIO_MAX_PINS> _pin_levels;

public:
    GPIOState();
    int get_level(int pin) const;
    void set_level(int pin, int level);
    void clear();
};

extern GPIOState gpio_state;

#endif // MOCK_MCU_GPIO_STATE_HPP