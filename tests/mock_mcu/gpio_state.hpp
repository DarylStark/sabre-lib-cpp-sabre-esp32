#ifndef MOCK_MCU_GPIO_STATE_HPP
#define MOCK_MCU_GPIO_STATE_HPP

#include <cstdint>
#include <vector>

// Number of pins supported by the mock (covers GPIO_NUM_0 .. GPIO_NUM_39)
constexpr int GPIO_MAX_PINS = 40;

enum class GPIOType
{
    UNDEFINED,
    INPUT,
    OUTPUT
};

struct GPIO
{
    GPIOType type = GPIOType::UNDEFINED;
    int16_t level = -1;
};

class GPIOState
{
private:
    std::vector<GPIO> _pin_levels;

public:
    GPIOState(uint32_t pin_count);
    int get_level(int pin) const;
    void set_level(int pin, int level);
    void clear();
};

#endif // MOCK_MCU_GPIO_STATE_HPP