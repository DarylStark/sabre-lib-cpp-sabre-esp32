#ifndef MOCK_MCU_GPIO_STATE_HPP
#define MOCK_MCU_GPIO_STATE_HPP

#include <cstdint>
#include <functional>
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
    std::function<void(int)> interrupt_handler = nullptr;
};

class GPIOBank
{
private:
    std::vector<GPIO> _pin_levels;

public:
    GPIOBank(uint32_t pin_count);
    void clear();

    int get_level(int pin) const;
    void set_level(int pin, int level);
    void set_isr_handler(int pin, std::function<void(int)> handler);
    void run_isr(int pin);
};

#endif // MOCK_MCU_GPIO_STATE_HPP