#include "../include/esp_timer.h"
#include <mockoc.hpp>

int64_t esp_timer_get_time(void)
{
    return mock_call(
        "esp_timer_get_time", []() { return 0; });
}
