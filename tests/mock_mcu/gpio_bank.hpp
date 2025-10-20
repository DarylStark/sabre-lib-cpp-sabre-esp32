#ifndef MOCK_MCU_GPIO_STATE_HPP
#define MOCK_MCU_GPIO_STATE_HPP

#include <cstdint>
#include <vector>

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

class GPIOBank
{
private:
    std::vector<GPIO> _pin_levels;

public:
    GPIOBank(uint32_t pin_count);
    int get_level(int pin) const;
    void set_level(int pin, int level);
    void clear();
};

#endif // MOCK_MCU_GPIO_STATE_HPP