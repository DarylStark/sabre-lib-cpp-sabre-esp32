#include "../include/esp_timer.h"
#include <chrono>
#include <mockoc.hpp>

int64_t esp_timer_get_time(void)
{
    return mock_call(
        "esp_timer_get_time",
        []()
        {
            return std::chrono::duration_cast<std::chrono::microseconds>(
                       std::chrono::steady_clock::now().time_since_epoch())
                .count();
        });
}
